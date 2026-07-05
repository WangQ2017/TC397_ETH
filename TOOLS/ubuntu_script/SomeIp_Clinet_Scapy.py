#!/usr/bin/env python3
"""
SOME/IP 订阅客户端 - TCP/UDP混合版本
UDP: 直接发送SD订阅报文
TCP: 先建立连接，再通过TCP连接发送SD订阅报文
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

class SOMEIPSD:
    """SOME/IP Service Discovery 报文构建类"""
    
    @staticmethod
    def get_service_port(protocol: int) -> int:
        """根据协议类型返回对应的服务端口号"""
        if protocol == 0x11:  # UDP
            return 0x40000  # 262144
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
                 interface: str = None):
        self.server_ip = server_ip
        self.client_ip = client_ip
        self.interface = interface
        
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
        
        # 显示配置
        self.show_config()
    
    def show_config(self):
        """显示配置信息"""
        print("=" * 80)
        print("SOME/IP 订阅客户端 - TCP/UDP混合版本")
        print("=" * 80)
        print(f"服务器IP: {self.server_ip}")
        print(f"客户端IP: {self.client_ip}")
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
    
    def send_udp_subscribe(self, service_name: str, config: dict) -> bool:
        """发送UDP订阅请求"""
        print(f"\n[UDP] 发送 {service_name} 订阅请求...")
        
        try:
            # 生成客户端端口 (用于发送SD报文)
            client_port = 45000 + list(self.services.keys()).index(service_name)
            
            # 构建报文
            message = SOMEIPSD.create_subscribe_message(
                service_config=config,
                server_ip=self.server_ip,
                client_ip=self.client_ip,  # SD data IP in option
                client_port=40000     # SD data PORT in option
            )
            
            # 使用Scapy发送UDP包
            ip_layer = IP(src=self.client_ip, dst=self.server_ip)
            udp_layer = UDP(sport=client_port, dport=30490)  # SOME/IP SD端口
            
            udp_layer.len = 8 + len(message)
            
            if self.interface:
                send(ip_layer/udp_layer/Raw(message), iface=self.interface, verbose=0)
            else:
                send(ip_layer/udp_layer/Raw(message), verbose=0)
            
            service_port = SOMEIPSD.get_service_port(config["protocol"])
            print(f"  ✓ UDP订阅请求发送成功!")
            print(f"    目标: {self.server_ip}:30490 (SOME/IP SD端口)")
            print(f"    服务端口: {service_port} (UDP)")
            print(f"    报文大小: {len(message)} 字节")
            
            # 等待UDP响应
            return self.wait_for_udp_response(service_name, client_port)
            
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



            # 4. 构建SOME/IP SD订阅报文
            message = SOMEIPSD.create_subscribe_message(
                service_config=config,
                server_ip=self.server_ip,
                client_ip=self.client_ip,  # SD data IP in option
                client_port=local_port     # SD data PORT in option
            )

            #5 使用Scapy发送UDP包
            ip_layer = IP(src=self.client_ip, dst=self.server_ip)
            udp_layer = UDP(sport=local_port, dport=30490)  # SOME/IP SD端口
            
            udp_layer.len = 8 + len(message)
            
            if self.interface:
                send(ip_layer/udp_layer/Raw(message), iface=self.interface, verbose=0)
            else:
                send(ip_layer/udp_layer/Raw(message), verbose=0)

            # # 5. 通过TCP连接发送报文
            # # bytes_sent = tcp_socket.send(message)
            # # print(f"  ✓ SOME/IP SD订阅报文发送成功!")
            # # print(f"    发送字节数: {bytes_sent}")
            # # print(f"    报文大小: {len(message)} 字节")
            
            # # 6. 存储TCP连接（用于后续接收）
            # self.tcp_connections[service_name] = tcp_socket
            
            # # 7. 等待TCP响应
            # return self.wait_for_tcp_response(service_name, tcp_socket)
            return True
            
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
    
    def wait_for_udp_response(self, service_name: str, client_port: int) -> bool:
        """等待UDP响应"""
        print(f"\n等待UDP响应...")
        
        try:
            # 设置过滤器
            filter_str = f"udp and host {self.server_ip} and port {client_port}"
            
            if self.interface:
                packets = sniff(filter=filter_str, timeout=3, iface=self.interface)
            else:
                packets = sniff(filter=filter_str, timeout=3)
            
            if packets:
                print(f"  捕获到 {len(packets)} 个UDP响应包")
                
                for i, pkt in enumerate(packets[:2]):
                    if UDP in pkt and Raw in pkt:
                        data = pkt[Raw].load
                        
                        if len(data) >= 16:
                            try:
                                message_type = data[14]
                                return_code = data[15]
                                
                                if message_type == 0x03 and return_code == 0x00:
                                    print(f"  ✓ 收到有效的SOME/IP RESPONSE")
                                    return True
                            except:
                                pass
                print(f"  ✗ 未收到有效UDP响应")
            else:
                print(f"  ✗ 未捕获到UDP响应包")
                
        except Exception as e:
            print(f"  等待UDP响应时出错: {e}")
        
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
        
        if config["protocol"] == 0x11:  # UDP
            return self.send_udp_subscribe(service_name, config)
        elif config["protocol"] == 0x06:  # TCP
            return self.send_tcp_subscribe(service_name, config)
        else:
            print(f"  ✗ 不支持的协议类型: 0x{config['protocol']:02X}")
            return False
    
    def close_all_connections(self):
        """关闭所有TCP连接"""
        print(f"\n关闭所有TCP连接...")
        for service_name, sock in self.tcp_connections.items():
            try:
                sock.close()
                print(f"  已关闭 {service_name} 的TCP连接")
            except:
                pass
        self.tcp_connections.clear()
    
    def subscribe_all(self):
        """订阅所有服务"""
        print("\n开始订阅所有服务...")
        
        results = {}
        10
        for service_name in self.services.keys():
            success = self.send_subscribe_request(service_name)
            results[service_name] = success
            
            if service_name != list(self.services.keys())[-1]:
                print("\n" + "="*80)
                print("准备下一个服务...")
                time.sleep(2)
        
        # 显示结果
        print("\n" + "="*80)
        print("订阅结果汇总")
        print("="*80)
        
        success_count = 0
        for service_name, success in results.items():
            config = self.services[service_name]
            port = SOMEIPSD.get_service_port(config["protocol"])
            proto = "UDP" if config["protocol"] == 0x11 else "TCP"
            
            status = "✓ 成功" if success else "✗ 失败"
            print(f"{service_name:12} {status:6} 协议: {proto:4} 端口: {port:6} (0x{port:04X})")
            if success:
                success_count += 1
        
        print(f"\n总计: {success_count}/{len(results)} 个服务订阅成功")
        print("="*80)
        
        # 关闭所有连接
        self.close_all_connections()
        
        return results

def main():
    """主函数"""
    parser = argparse.ArgumentParser(
        description='SOME/IP 订阅客户端 - TCP/UDP混合版本',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  sudo python %(prog.py                       # 订阅所有服务
  sudo python %(prog.py --iface ens33.23      # 指定网卡订阅
  sudo python %(prog.py --service Fault_Info  # 仅订阅Fault_Info
  
传输方式:
  - UDP服务 (Fault_Info, Sen_State): 直接发送UDP SD报文到端口30490
  - TCP服务 (Ecu_Status): 先建立TCP连接到端口47843，再通过TCP连接发送SD报文
  
注意:
  - TCP连接使用本地随机分配的端口
  - 需要SOME/IP服务器支持TCP连接
        """)
    
    parser.add_argument('--server', type=str, default='10.23.0.33',
                       help='SOME/IP服务器IP地址 (默认: 10.23.0.33)')
    parser.add_argument('--client', type=str, default='10.23.0.10',
                       help='客户端IP地址 (默认: 10.23.0.10)')
    parser.add_argument('--iface', type=str,
                       help='指定网卡名称 (如: ens33.23)')
    parser.add_argument('--service', type=str,
                       choices=['Fault_Info', 'Sen_State', 'Ecu_Status', 'all'],
                       default='all', help='要订阅的服务')
    
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
        interface=args.iface
    )
    
    try:
        if args.service == 'all':
            client.subscribe_all()
        else:
            success = client.send_subscribe_request(args.service)
            client.close_all_connections()
            
    except KeyboardInterrupt:
        print("\n程序被用户中断")
        client.close_all_connections()
    except Exception as e:
        print(f"\n程序运行出错: {e}")
        client.close_all_connections()

if __name__ == "__main__":
    main()