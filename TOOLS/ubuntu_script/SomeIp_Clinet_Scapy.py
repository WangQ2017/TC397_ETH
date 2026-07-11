#!/usr/bin/env python3
"""
SOME/IP 订阅客户端 - TCP/UDP混合版本

UDP: 单客户端 (--client) 订阅 Fault_Info / Sen_State
     Event 监听同时覆盖单播 (client:40000) 和组播 (239.23.0.1:40000)
TCP: Ecu_Status 先建 TCP 连接再发 SD 订阅
     默认: 监听一段时间后优雅关闭 TCP 并退出
     --hold: 保持 TCP 长连接, 脚本不退出 (持续收 Event)
"""

from scapy.all import *
import argparse
import time
import socket
import struct
import sys
import os
import select
import random
import threading

UDP_EVENT_PORT = 40000
SD_PORT = 30490
MULTICAST_GROUP = "239.23.0.1"

# 服务名 -> Event AUTOSAR PDU Header ID
UDP_EVENT_PDU_IDS = {
    "Fault_Info": 0xC3C08001,
    "Sen_State": 0xC3C18001,
}

class SOMEIPSD:
    """SOME/IP Service Discovery 报文构建类"""
    
    @staticmethod
    def get_service_port(protocol: int) -> int:
        """根据协议类型返回对应的服务端口号"""
        if protocol == 0x11:  # UDP
            return 40000
        elif protocol == 0x06:  # TCP
            return 47843    # 0xBAE3
        else:
            return 30490  # 默认SOME/IP SD端口
    
    @staticmethod
    def create_subscribe_message(service_config: dict, 
                                server_ip: str, client_ip: str, 
                                client_port: int) -> bytes:
        """构建完整的订阅报文（只有一个server option）"""
        
        print(f"构建 {service_config['name']} 订阅报文...")
        
        # ==================== SD Header (8字节) ====================
        sd_header = bytearray(8)
        
        # Flags: 1字节
        sd_header[0] = service_config["sd_flag"]  # Flags
        
        # Reserved: 3字节
        sd_header[1] = 0x00
        sd_header[2] = 0x00
        sd_header[3] = 0x00
        
        # Entry Array Length: 4字节 (SD Entry长度=16字节)
        entry_length = 16
        sd_header[4] = (entry_length >> 24) & 0xFF
        sd_header[5] = (entry_length >> 16) & 0xFF
        sd_header[6] = (entry_length >> 8) & 0xFF
        sd_header[7] = entry_length & 0xFF
        
        # ==================== Subscribe Eventgroup Entry (16字节) ====================
        sd_entry = bytearray(16)
        
        # Type: 0x06 (SubscribeEventgroup)
        sd_entry[0] = 0x06
        
        # Index1stOptions: 指向唯一的option (option array索引从1开始)
        sd_entry[1] = 0x00  # 指向第一个(也是唯一一个)option
        
        # Index2ndOptions: 没有第二个option
        sd_entry[2] = 0x00
        
        # NumOpt1(4bit) + NumOpt2(4bit): 只有第一个option
        sd_entry[3] = 0x10
        
        # ServiceID: 2字节
        service_id = service_config["service_id"]
        sd_entry[4] = (service_id >> 8) & 0xFF
        sd_entry[5] = service_id & 0xFF
        
        # InstanceID: 2字节
        instance_id = service_config["instance_id"]
        sd_entry[6] = (instance_id >> 8) & 0xFF
        sd_entry[7] = instance_id & 0xFF
        
        # Major Version: 1字节
        sd_entry[8] = 0x01
        
        # TTL: 3字节 (0xFFFFFF = infinite)
        sd_entry[9] = 0xFF
        sd_entry[10] = 0xFF
        sd_entry[11] = 0xFF
        
        # Reserved: 1字节
        sd_entry[12] = 0x00
        
        # InitialDataRequested(1bit) + Reserved(3bit) + Counter(4bit): 1字节
        sd_entry[13] = 0x00
        
        # EventgroupID: 2字节
        eventgroup_id = service_config["eventgroup_id"]
        sd_entry[14] = (eventgroup_id >> 8) & 0xFF
        sd_entry[15] = eventgroup_id & 0xFF
        
        # ==================== Option Array Length (4字节) ====================
        option_length = 12  # 一个option的长度
        option_array_length = bytearray(4)
        
        option_array_length[0] = (option_length >> 24) & 0xFF
        option_array_length[1] = (option_length >> 16) & 0xFF
        option_array_length[2] = (option_length >> 8) & 0xFF
        option_array_length[3] = option_length & 0xFF
        
        # ==================== IPv4 Endpoint Option (12字节) ====================
        client_ip_bytes = bytes(map(int, client_ip.split('.')))
        
        server_option = bytearray(12)
        
        # Length: 2字节 (12字节 = 3 words)
        server_option[0] = 0x00
        server_option[1] = 0x09
        
        # Type: 1字节 (0x04 = IPv4 Endpoint)
        server_option[2] = 0x04
        
        # Reserved: 1字节
        server_option[3] = 0x00
        
        # IPv4 Address: 4字节
        server_option[4:8] = client_ip_bytes
        
        # Reserved: 1字节
        server_option[8] = 0x00
        
        # Protocol Type: 1字节
        protocol_type = service_config["protocol"]
        server_option[9] = protocol_type
        
        # Port Number: 2字节
        #service_port = service_config["service_port"]
        #print(f"  !!!!!!!!协议: {protocol_type}, 服务端口: {service_port}")
        server_option[10] = (client_port >> 8) & 0xFF
        server_option[11] = client_port & 0xFF
        
        # ==================== 组装SD消息 ====================
        sd_message = (bytes(sd_header) + bytes(sd_entry) + 
                     bytes(option_array_length) + bytes(server_option))
        
        # ==================== SOME/IP Header (16字节) ====================
        someip_length = len(sd_message) + 8
        
        someip_header = bytearray(16)
        
        # ServiceID: 0xFFFF
        someip_header[0] = 0xFF
        someip_header[1] = 0xFF
        
        # MethodID: 0x8100
        someip_header[2] = 0x81
        someip_header[3] = 0x00
        
        # Length: 4字节
        someip_header[4] = (someip_length >> 24) & 0xFF
        someip_header[5] = (someip_length >> 16) & 0xFF
        someip_header[6] = (someip_length >> 8) & 0xFF
        someip_header[7] = someip_length & 0xFF
        
        # ClientID: 0x0000
        someip_header[8] = 0x00
        someip_header[9] = 0x00
        
        # SessionID: 0x0000
        someip_header[10] = 0x00
        someip_header[11] = 0x01
        
        # ProtocolVersion: 0x01
        someip_header[12] = 0x01
        
        # InterfaceVersion: 0x01
        someip_header[13] = 0x01
        
        # MessageType: 0x02 (REQUEST)
        someip_header[14] = 0x02
        
        # ReturnCode: 0x00 (E_OK)
        someip_header[15] = 0x00
        
        # ==================== 完整报文 ====================
        full_message = bytes(someip_header) + sd_message
        
        # 显示摘要信息
        # proto = "UDP" if protocol_type == 0x11 else "TCP"
        # print(f"  协议: {proto}, 服务端口: {service_port} (0x{service_port:04X})")
        # print(f"  报文大小: {len(full_message)} 字节")
        
        return full_message

class SOMEIPClient:
    """SOME/IP 客户端 - 支持TCP和UDP"""
    
    def __init__(self, server_ip: str = "10.23.0.33", 
                 client_ip: str = "10.23.0.10",
                 interface: str = None,
                 event_port: int = UDP_EVENT_PORT,
                 sd_port_base: int = 45000):
        self.server_ip = server_ip
        self.client_ip = client_ip
        self.interface = interface
        self.event_port = event_port
        self.sd_port_base = sd_port_base
        
        # 服务配置
        self.services = {
            "Fault_Info": {
                "name": "Fault_Info",
                "service_id": 0xC3C0,
                "instance_id": 0x0017,
                "protocol": 0x11,  # UDP
                "service_port": 40000,
                "eventgroup_id": 0x0001,
                "sd_flag": 0xC0
            },
            "Sen_State": {
                "name": "Sen_State",
                "service_id": 0xC3C1,
                "instance_id": 0x0017,
                "protocol": 0x11,  # UDP
                "service_port": 40000,
                "eventgroup_id": 0x0001,
                "sd_flag": 0xC0
            },
            "Ecu_Status": {
                "name": "Ecu_Status",
                "service_id": 0xC3C2,
                "instance_id": 0x0017,
                "protocol": 0x06,  # TCP
                "service_port": 47843,
                "eventgroup_id": 0x0001,
                "sd_flag": 0xC0
            }
        }
        
        # 存储TCP连接
        self.tcp_connections = {}
        self.multicast_sock = None
        
        # 显示配置
        self.show_config()
    
    def show_config(self):
        """显示配置信息"""
        print("=" * 80)
        print("SOME/IP 订阅客户端 - TCP/UDP混合版本")
        print("=" * 80)
        print(f"服务器IP: {self.server_ip}")
        print(f"客户端IP: {self.client_ip}")
        print(f"Event端口: {self.event_port} (组播目的端口固定 {UDP_EVENT_PORT})")
        print(f"SD源端口基址: {self.sd_port_base}")
        print(f"Event监听: 单播 {self.client_ip}:{self.event_port} + 组播 {MULTICAST_GROUP}:{UDP_EVENT_PORT}")
        if self.interface:
            print(f"网卡接口: {self.interface}")
        
        print("\n服务配置详情:")
        print("  名称          ServiceID   InstanceID  Protocol  端口号      传输方式  SD Flag")
        print("  " + "-" * 75)
        for name, config in self.services.items():
            proto = "UDP" if config["protocol"] == 0x11 else "TCP"
            port = SOMEIPSD.get_service_port(config["protocol"])
            port_hex = f"0x{port:04X}"
            transport = "直接UDP发送" if config["protocol"] == 0x11 else "TCP连接后发送"
            print(f"  {name:12}   0x{config['service_id']:04X}     0x{config['instance_id']:04X}      {proto:6}   {port:6} {port_hex:8}  {transport:12}  0x{config['sd_flag']:02X}")
        print("=" * 80)
    
    def send_udp_subscribe(self, service_name: str, config: dict,
                           event_port: int = None) -> bool:
        """发送UDP订阅请求"""
        if event_port is None:
            event_port = self.event_port
        print(f"\n[UDP] 发送 {service_name} 订阅请求 (client={self.client_ip})...")
        
        try:
            sd_sport = self.sd_port_base + list(self.services.keys()).index(service_name)
            
            message = SOMEIPSD.create_subscribe_message(
                service_config=config,
                server_ip=self.server_ip,
                client_ip=self.client_ip,
                client_port=event_port
            )
            
            sniffer = self.start_ack_sniffer(self.client_ip, sd_sport)
            
            ip_layer = IP(src=self.client_ip, dst=self.server_ip)
            udp_layer = UDP(sport=sd_sport, dport=SD_PORT)
            udp_layer.len = 8 + len(message)
            
            if self.interface:
                send(ip_layer/udp_layer/Raw(message), iface=self.interface, verbose=0)
            else:
                send(ip_layer/udp_layer/Raw(message), verbose=0)
            
            print(f"  ✓ UDP订阅请求发送成功!")
            print(f"    源: {self.client_ip}:{sd_sport} -> {self.server_ip}:{SD_PORT}")
            print(f"    Endpoint Option: {self.client_ip}:{event_port}")
            print(f"    报文大小: {len(message)} 字节")
            
            return self.wait_for_udp_response(service_name, sniffer)
            
        except Exception as e:
            print(f"  ✗ UDP发送失败: {e}")
            return False
    
    def send_tcp_subscribe(self, service_name: str, config: dict) -> bool:
        """建立TCP连接并发送订阅请求"""
        print(f"\n[TCP] 发送 {service_name} 订阅请求...")
        
        tcp_socket = None
        try:
            # 获取TCP服务端口
            # local_port = 40008
            tcp_port = SOMEIPSD.get_service_port(config["protocol"])
            
            # 1. 创建TCP socket
            tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            tcp_socket.settimeout(5.0)
            
            # 绑定到指定网卡（如果支持）
            if self.interface:
                try:
                    tcp_socket.setsockopt(socket.SOL_SOCKET, 25, self.interface.encode())
                    print(f"  绑定到网卡: {self.interface}")
                except:
                    print(f"  警告: 无法绑定到网卡")
            
            # 2. 绑定到随机本地端口
            tcp_socket.bind((self.client_ip, 0))  # 0表示随机端口
            local_port = tcp_socket.getsockname()[1]
            
            print(f"  本地TCP端口: {local_port}")
            print(f"  目标TCP端口: {tcp_port}")
            
            # 3. 建立TCP连接
            print(f"  正在连接到 {self.server_ip}:{tcp_port}...")
            tcp_socket.connect((self.server_ip, tcp_port))
            print(f"  ✓ TCP连接建立成功!")
            tcp_socket.settimeout(None)

            # 4. 构建SOME/IP SD订阅报文
            message = SOMEIPSD.create_subscribe_message(
                service_config=config,
                server_ip=self.server_ip,
                client_ip=self.client_ip,  # SD data IP in option
                client_port=local_port     # SD data PORT in option
            )

            # SubscribeAck 通过 UDP 返回到 client_ip:local_port
            sniffer = self.start_ack_sniffer(self.client_ip, local_port)

            #5 使用Scapy发送UDP包
            ip_layer = IP(src=self.client_ip, dst=self.server_ip)
            udp_layer = UDP(sport=local_port, dport=30490)  # SOME/IP SD端口
            
            udp_layer.len = 8 + len(message)
            
            if self.interface:
                send(ip_layer/udp_layer/Raw(message), iface=self.interface, verbose=0)
            else:
                send(ip_layer/udp_layer/Raw(message), verbose=0)

            # 6. 存储TCP连接 (保持不断开, 用于持续接收 Event)
            self.tcp_connections[service_name] = tcp_socket

            # 7. 等待并校验SubscribeAck
            return self.wait_for_udp_response(service_name, sniffer)
            
        except socket.timeout:
            print(f"  ✗ TCP连接超时")
            return False
        except ConnectionRefusedError:
            print(f"  ✗ TCP连接被拒绝")
            return False
        except Exception as e:
            print(f"  ✗ TCP发送失败: {e}")
            if tcp_socket:
                tcp_socket.close()
            return False
    
    @staticmethod
    def _is_valid_subscribe_ack(data: bytes) -> bool:
        """判断报文是否为有效的SubscribeEventgroupAck (SOME/IP-SD)"""
        # SOME/IP头(16) + SD头(8) + Entry(16) = 至少40字节
        if len(data) < 40:
            return False
        # ServiceID=0xFFFF, MethodID=0x8100 (SD报文标识)
        if data[0:2] != b"\xff\xff" or data[2:4] != b"\x81\x00":
            return False
        # 注意: SD报文的MessageType为0x02(NOTIFICATION), 而不是0x03(RESPONSE)
        if data[14] != 0x02:
            return False
        # SD Entry从偏移量24开始 (16 SOME/IP头 + 8 SD头)
        entry_type = data[24]
        ttl = (data[33] << 16) | (data[34] << 8) | data[35]
        # 0x07=SubscribeEventgroupAck; 若TTL=0则为Nack(订阅被拒绝)
        return entry_type == 0x07 and ttl != 0
    
    def start_ack_sniffer(self, client_ip: str, sd_sport: int):
        """在发送订阅报文前启动异步抓包, 返回已启动的AsyncSniffer"""
        filter_str = f"udp and src host {self.server_ip} and dst host {client_ip} and port {sd_sport}"
        
        # 收到有效SubscribeAck即可提前停止抓包
        def _stop(pkt):
            return Raw in pkt and self._is_valid_subscribe_ack(bytes(pkt[Raw].load))
        
        kwargs = {"filter": filter_str, "timeout": 3, "stop_filter": _stop}
        if self.interface:
            kwargs["iface"] = self.interface
        
        sniffer = AsyncSniffer(**kwargs)
        sniffer.start()
        # 给抓包线程一点启动时间, 确保send之前已开始监听
        time.sleep(0.3)
        return sniffer
    
    def wait_for_udp_response(self, service_name: str, sniffer) -> bool:
        """等待并校验SubscribeEventgroupAck"""
        print(f"\n等待SubscribeAck...")
        
        try:
            sniffer.join()  # 等待timeout结束或stop_filter命中
            packets = sniffer.results
        except Exception as e:
            print(f"  等待响应时出错: {e}")
            return False
        
        if not packets:
            print(f"  ✗ 未捕获到UDP响应包")
            return False
        
        print(f"  捕获到 {len(packets)} 个UDP响应包")
        for pkt in packets:
            if Raw not in pkt:
                continue
            data = bytes(pkt[Raw].load)
            if self._is_valid_subscribe_ack(data):
                print(f"  ✓ 收到有效的SubscribeEventgroupAck (SD Entry Type=0x07)")
                return True
        
        print(f"  ✗ 未收到有效的SubscribeEventgroupAck")
        return False
    
    def wait_for_tcp_response(self, service_name: str, tcp_socket: socket.socket) -> bool:
        """等待TCP响应"""
        print(f"\n等待TCP响应...")
        
        try:
            # 设置socket超时
            tcp_socket.settimeout(30.0)
            
            # 尝试接收数据
            try:
                data = tcp_socket.recv(1024)
                
                if data:
                    print(f"  收到TCP响应: {len(data)} 字节")
                    
                    if len(data) >= 16:
                        try:
                            message_type = data[14]
                            return_code = data[15]
                            
                            print(f"  MessageType: 0x{message_type:02X}")
                            print(f"  ReturnCode: 0x{return_code:02X}")
                            
                            if message_type == 0x03 and return_code == 0x00:
                                print(f"  ✓ 收到有效的SOME/IP RESPONSE")
                                return True
                            else:
                                print(f"  ✗ 非成功响应")
                        except Exception as e:
                            print(f"  解析响应失败: {e}")
                    else:
                        print(f"  ✗ 响应数据太短")
                else:
                    print(f"  ✗ TCP连接已关闭")
                    
            except socket.timeout:
                print(f"  ✗ 等待TCP响应超时")
            except Exception as e:
                print(f"  接收TCP数据时出错: {e}")
                
        except Exception as e:
            print(f"  等待TCP响应时出错: {e}")
        
        return False
    
    def send_subscribe_request(self, service_name: str) -> bool:
        """发送订阅请求（根据协议类型选择UDP或TCP）"""
        if service_name not in self.services:
            print(f"错误: 未知的服务 '{service_name}'")
            return False
        
        config = self.services[service_name]
        
        print(f"\n{'='*80}")
        print(f"处理服务: {service_name}")
        print(f"{'='*80}")
        
        if config["protocol"] == 0x11:
            return self.send_udp_subscribe(service_name, config)
        elif config["protocol"] == 0x06:
            return self.send_tcp_subscribe(service_name, config)
        else:
            print(f"  ✗ 不支持的协议类型: 0x{config['protocol']:02X}")
            return False

    def subscribe_all(self):
        """订阅所有服务"""
        print("\n开始订阅所有服务...")
        results = {}
        udp_services = ["Fault_Info", "Sen_State"]

        for service_name in udp_services:
            results[service_name] = self.send_subscribe_request(service_name)
            if service_name != udp_services[-1]:
                time.sleep(1)

        print("\n" + "="*80)
        print("准备订阅 Ecu_Status (TCP)...")
        time.sleep(1)
        results["Ecu_Status"] = self.send_subscribe_request("Ecu_Status")
        
        self._print_subscribe_summary(results)
        return results

    @staticmethod
    def _event_mode(pkt) -> str:
        """根据目的地址判断 Event 为单播还是组播"""
        if IP in pkt and pkt[IP].dst == MULTICAST_GROUP:
            return "MULTICAST"
        return "UNICAST"

    @staticmethod
    def _print_event_packet(pkt, index: int, mode: str = None):
        """解析并打印 AUTOSAR PDU Event"""
        if Raw not in pkt:
            return
        mode = mode or SOMEIPClient._event_mode(pkt)
        data = bytes(pkt[Raw].load)
        if len(data) < 8:
            return
        pdu_id = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]
        pdu_len = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]
        payload = data[8:8 + pdu_len] if len(data) >= 8 + pdu_len else data[8:]
        svc_name = next((n for n, pid in UDP_EVENT_PDU_IDS.items() if pid == pdu_id), "Unknown")
        if IP in pkt and UDP in pkt:
            src = f"{pkt[IP].src}:{pkt[UDP].sport}"
            dst = f"{pkt[IP].dst}:{pkt[UDP].dport}"
        else:
            src = dst = "?"
        print(f"  [{index}] [{mode}] {svc_name:12} {src} -> {dst}, "
              f"PduId=0x{pdu_id:08X}, PduLen={pdu_len}, Payload={payload[:16].hex()}")
    
    def close_all_connections(self):
        """关闭所有TCP连接 (优雅关闭)"""
        self.close_all_tcp_gracefully()

    def _print_subscribe_summary(self, results: dict):
        """打印订阅结果汇总"""
        print("\n" + "="*80)
        print("订阅结果汇总")
        print("="*80)
        success_count = 0
        for service_name, success in results.items():
            config = self.services.get(service_name, {})
            port = SOMEIPSD.get_service_port(config.get("protocol", 0x11))
            proto = "UDP" if config.get("protocol") == 0x11 else "TCP"
            status = "✓ 成功" if success else "✗ 失败"
            print(f"{service_name:12} {status:6} 协议: {proto:4} 端口: {port:6} (0x{port:04X})")
            if success:
                success_count += 1
        print(f"\n总计: {success_count}/{len(results)} 个服务订阅成功")
        print(f"Event 监听: 单播 {self.client_ip}:{self.event_port}, "
              f"组播 {MULTICAST_GROUP}:{UDP_EVENT_PORT}")
        print("="*80)

    def join_multicast_group(self) -> bool:
        """加入组播组, 使本机可接收 ECU 发往 239.23.0.1 的 Event"""
        if self.multicast_sock:
            return True
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            if hasattr(socket, 'SO_REUSEPORT'):
                sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
            # 组播目的端口固定为 UDP_EVENT_PORT, 与 Endpoint Option 中的单播端口无关
            sock.bind(('', UDP_EVENT_PORT))
            mreq = struct.pack(
                '=4s4s',
                socket.inet_aton(MULTICAST_GROUP),
                socket.inet_aton(self.client_ip)
            )
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
            self.multicast_sock = sock
            print(f"  ✓ 已加入组播组 {MULTICAST_GROUP} (接口 {self.client_ip})")
            return True
        except Exception as e:
            print(f"  警告: 加入组播组失败: {e}")
            return False

    def leave_multicast_group(self):
        """离开组播组并关闭 socket"""
        if not self.multicast_sock:
            return
        try:
            mreq = struct.pack(
                '=4s4s',
                socket.inet_aton(MULTICAST_GROUP),
                socket.inet_aton(self.client_ip)
            )
            self.multicast_sock.setsockopt(socket.IPPROTO_IP, socket.IP_DROP_MEMBERSHIP, mreq)
            self.multicast_sock.close()
            print(f"  已离开组播组 {MULTICAST_GROUP}")
        except Exception:
            pass
        self.multicast_sock = None

    def _parse_tcp_pdus(self, recv_buf: bytearray, pkt_count: int) -> int:
        """从 TCP 接收缓冲区解析并打印完整的 AUTOSAR PDU (8B头 + payload)"""
        offset = 0
        while offset + 8 <= len(recv_buf):
            pdu_id = ((recv_buf[offset] << 24) | (recv_buf[offset + 1] << 16) |
                      (recv_buf[offset + 2] << 8) | recv_buf[offset + 3])
            pdu_len = ((recv_buf[offset + 4] << 24) | (recv_buf[offset + 5] << 16) |
                       (recv_buf[offset + 6] << 8) | recv_buf[offset + 7])
            frame_len = 8 + pdu_len
            if offset + frame_len > len(recv_buf):
                break
            payload = bytes(recv_buf[offset + 8:offset + frame_len])
            pkt_count += 1
            print(f"  [{pkt_count}] PduId=0x{pdu_id:08X}, PduLen={pdu_len}, "
                  f"Payload={payload[:16].hex()}")
            offset += frame_len
        if offset:
            del recv_buf[:offset]
        return pkt_count

    def _close_tcp(self, service_name: str, graceful: bool = False):
        """关闭指定 TCP 连接并从字典移除; graceful=True 时先 shutdown 发送 FIN"""
        sock = self.tcp_connections.pop(service_name, None)
        if not sock:
            return
        if graceful:
            try:
                sock.shutdown(socket.SHUT_RDWR)
            except OSError:
                pass
        try:
            sock.close()
        except OSError:
            pass

    def close_all_tcp_gracefully(self):
        """优雅关闭所有 TCP 连接 (退出前调用, 避免进程退出时发 RST)"""
        if not self.tcp_connections:
            return
        print("\n优雅关闭 TCP 连接 (发送 FIN)...")
        for service_name in list(self.tcp_connections.keys()):
            print(f"  关闭 {service_name} ...")
            self._close_tcp(service_name, graceful=True)
        print("  TCP 连接已全部关闭")

    def _tcp_recv_for(self, duration: int):
        """限时接收 Ecu_Status TCP Event, 超时后返回"""
        if "Ecu_Status" not in self.tcp_connections:
            return

        tcp_sock = self.tcp_connections["Ecu_Status"]
        print(f"\n监听 Ecu_Status TCP Event ({duration}s)...")
        print("  期望报文: [AUTOSAR Hdr 8B: ID=0xC3C28001] + [16B Payload]")

        tcp_sock.settimeout(1.0)
        end_time = time.time() + duration
        pkt_count = 0
        recv_buf = bytearray()

        while time.time() < end_time:
            try:
                data = tcp_sock.recv(4096)
                if not data:
                    print("  对端关闭写方向 (FIN)")
                    self._close_tcp("Ecu_Status")
                    return
                recv_buf.extend(data)
                pkt_count = self._parse_tcp_pdus(recv_buf, pkt_count)
            except socket.timeout:
                continue
            except (ConnectionResetError, OSError) as e:
                print(f"  TCP 接收异常: {e}")
                self._close_tcp("Ecu_Status")
                return

        if pkt_count == 0:
            print("  未收到 TCP Event 数据")
        else:
            print(f"  共收到 {pkt_count} 个 TCP Event")

    def _tcp_recv_forever(self, reconnect: bool = True):
        """持续接收 Ecu_Status TCP Event; 默认断线后自动重连, 进程不退出"""
        recv_buf = bytearray()
        pkt_count = 0

        print("\n持续监听 Ecu_Status TCP Event (进程保持运行, 请勿退出)...")
        print("  期望报文: [AUTOSAR Hdr 8B: ID=0xC3C28001] + [16B Payload]")
        print("  Ctrl+C 结束进程")

        try:
            while True:
                tcp_sock = self.tcp_connections.get("Ecu_Status")
                if tcp_sock is None:
                    if not reconnect:
                        time.sleep(1.0)
                        continue
                    print("\n  TCP 未连接, 5s 后尝试重新订阅 Ecu_Status...")
                    time.sleep(5)
                    if self.send_subscribe_request("Ecu_Status"):
                        recv_buf.clear()
                        pkt_count = 0
                        print("  ✓ TCP 重连并重新订阅成功")
                    else:
                        print("  ✗ TCP 重连/重新订阅失败, 继续重试...")
                    continue

                try:
                    tcp_sock.settimeout(1.0)
                    data = tcp_sock.recv(4096)
                    if not data:
                        print("  对端关闭写方向 (FIN), 等待重连...")
                        self._close_tcp("Ecu_Status")
                        continue
                    recv_buf.extend(data)
                    pkt_count = self._parse_tcp_pdus(recv_buf, pkt_count)
                except socket.timeout:
                    continue
                except (ConnectionResetError, OSError) as e:
                    print(f"  TCP 连接异常: {e}, 等待重连...")
                    self._close_tcp("Ecu_Status")
        except KeyboardInterrupt:
            print("\n用户中断, 准备关闭 TCP...")

    def sniff_udp_events(self, duration: int = 15):
        """同时监听单播和组播 UDP Event"""
        filter_str = (
            f"udp and ((host {self.client_ip} and port {self.event_port}) "
            f"or (host {MULTICAST_GROUP} and port {UDP_EVENT_PORT}))"
        )
        print(f"\n监听 UDP Event (单播+组播): {filter_str} ({duration}s)")
        print(f"  单播期望: {self.server_ip} -> {self.client_ip}:{self.event_port}")
        print(f"  组播期望: {self.server_ip} -> {MULTICAST_GROUP}:{UDP_EVENT_PORT}")
        print(f"  期望: [AUTOSAR Hdr] Fault=0xC3C08001 / SenState=0xC3C18001 + Payload")

        self.join_multicast_group()
        try:
            kwargs = {"filter": filter_str, "timeout": duration}
            if self.interface:
                kwargs["iface"] = self.interface
            packets = sniff(**kwargs)
            self._print_sniff_results(packets)
        finally:
            self.leave_multicast_group()

    def _print_sniff_results(self, packets):
        if not packets:
            print("  未捕获到 UDP Event")
            return
        unicast_cnt = sum(1 for p in packets if self._event_mode(p) == "UNICAST")
        multicast_cnt = len(packets) - unicast_cnt
        print(f"  捕获 {len(packets)} 个 UDP Event 包 "
              f"(单播 {unicast_cnt}, 组播 {multicast_cnt})")
        shown = 0
        for pkt in packets:
            if shown >= 20:
                print(f"  ... 省略后续 {len(packets) - shown} 个包")
                break
            shown += 1
            self._print_event_packet(pkt, shown)

    def run_after_subscribe(self, service: str, sniff_events: int, results: dict,
                            hold: bool = False):
        """订阅完成后的监听阶段

        hold=False (默认): 监听一段时间后优雅关闭 TCP 并返回 (脚本退出)
        hold=True: 持续监听并保持 TCP, 仅 Ctrl+C 结束
        """
        want_udp = service in ('all', 'Fault_Info', 'Sen_State')
        want_tcp = service in ('all', 'Ecu_Status')
        tcp_ok = bool(results.get('Ecu_Status')) and ('Ecu_Status' in self.tcp_connections)

        if hold:
            if want_udp and sniff_events > 0:
                if tcp_ok:
                    udp_thread = threading.Thread(
                        target=self.sniff_udp_events,
                        args=(sniff_events,),
                        daemon=True
                    )
                    udp_thread.start()
                    print(f"\nUDP Event 监听 {sniff_events}s (后台), TCP 长连接 (--hold)...")
                    self._tcp_recv_forever(reconnect=True)
                    return
                self.sniff_udp_events(sniff_events)

            if tcp_ok:
                self._tcp_recv_forever(reconnect=True)
                return

            if want_tcp and not results.get('Ecu_Status'):
                print("\nEcu_Status 订阅未成功, 无法接收 TCP Event")
            return

        # 默认定时监听后退出
        listen_sec = sniff_events if sniff_events > 0 else (15 if tcp_ok else 0)

        if want_udp and sniff_events > 0:
            if tcp_ok:
                udp_thread = threading.Thread(
                    target=self.sniff_udp_events,
                    args=(sniff_events,),
                    daemon=True
                )
                udp_thread.start()
                self._tcp_recv_for(listen_sec)
            else:
                self.sniff_udp_events(sniff_events)
        elif tcp_ok:
            self._tcp_recv_for(listen_sec)

        if want_tcp and not results.get('Ecu_Status'):
            print("\nEcu_Status 订阅未成功, 无法接收 TCP Event")

        self.close_all_tcp_gracefully()
        self.leave_multicast_group()
        print("\n监听结束, 脚本正常退出")

def main():
    """主函数"""
    parser = argparse.ArgumentParser(
        description='SOME/IP 订阅客户端 - TCP/UDP混合版本',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  sudo python %(prog)s                                    # 默认: 监听15s 后优雅关 TCP 并退出
  sudo python %(prog)s --hold                             # 保持 TCP 长连接, 脚本不退出
  sudo python %(prog)s --service Ecu_Status --hold      # 仅 Ecu_Status, 持续收 TCP Event
  sudo python %(prog)s --iface ens33.23                   # 指定网卡
  sudo python %(prog)s --service Sen_State                # 仅订阅 Sen_State
  sudo python %(prog)s --client 10.23.0.10                # 指定客户端 IP

同机双客户端 (同一 IP, 不同端口, 用于触发 ECU MulticastThreshold=2):
  终端1: sudo python %(prog)s --client 10.23.0.10 --event-port 40000 --sd-port-base 45000
  终端2: sudo python %(prog)s --client 10.23.0.10 --event-port 40001 --sd-port-base 45100 --sniff-events 0
  (终端2 仅负责第二条 SD 订阅; 终端1 负责收 Event)

协议:
  - UDP (Fault_Info, Sen_State): 单客户端 SD 订阅, 同时监听单播和组播 Event
  - TCP (Ecu_Status): 先建 TCP 连接再 SD 订阅
  - 默认: --sniff-events 秒监听后优雅关闭 TCP (FIN) 并退出脚本
  - --hold: 保持 TCP 长连接持续收 Event, 脚本不退出 (ECU 需客户端在线才能发)
        """)
    
    parser.add_argument('--server', type=str, default='10.23.0.33',
                       help='SOME/IP 服务器 (ECU) IP (默认: 10.23.0.33)')
    parser.add_argument('--client', type=str, default='10.23.0.10',
                       help='客户端 IP (默认: 10.23.0.10)')
    parser.add_argument('--iface', type=str,
                       help='指定网卡名称 (如: ens33.23)')
    parser.add_argument('--event-port', type=int, default=UDP_EVENT_PORT,
                       help=f'UDP Event 本地端口 / Endpoint Option 端口 (默认: {UDP_EVENT_PORT})')
    parser.add_argument('--sd-port-base', type=int, default=45000,
                       help='SD 订阅报文 UDP 源端口基址, 按服务索引递增 (默认: 45000)')
    parser.add_argument('--service', type=str,
                       choices=['Fault_Info', 'Sen_State', 'Ecu_Status', 'all'],
                       default='all', help='要订阅的服务')
    parser.add_argument('--sniff-events', type=int, default=15,
                       help='Event 监听秒数 (默认15); 非 --hold 时到期后优雅关 TCP 并退出; 0=跳过 UDP 监听')
    parser.add_argument('--hold', action='store_true',
                       help='保持脚本运行不退出, TCP 长连接持续收 Event (默认: 监听结束后退出)')
    
    args = parser.parse_args()
    
    # 检查权限（UDP发送需要root）
    if os.geteuid() != 0:
        print("警告: UDP发送原始包需要root权限")
        print("TCP连接不需要root权限，但UDP部分可能失败")
        print("建议使用sudo运行此脚本")
    
    # 创建客户端
    client = SOMEIPClient(
        server_ip=args.server,
        client_ip=args.client,
        interface=args.iface,
        event_port=args.event_port,
        sd_port_base=args.sd_port_base
    )
    
    try:
        if args.service == 'all':
            results = client.subscribe_all()
        else:
            success = client.send_subscribe_request(args.service)
            results = {args.service: success}
            client._print_subscribe_summary(results)

        client.run_after_subscribe(args.service, args.sniff_events, results,
                                   hold=args.hold)
            
    except KeyboardInterrupt:
        print("\n程序被用户中断")
        client.close_all_tcp_gracefully()
        client.leave_multicast_group()
    except Exception as e:
        print(f"\n程序运行出错: {e}")
        client.close_all_tcp_gracefully()
        client.leave_multicast_group()

if __name__ == "__main__":
    main()