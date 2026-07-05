#!/usr/bin/env python3
"""
极简DHCP服务器 - Ubuntu 22.04
确保收到Discover后能正确响应Offer
"""

import socket
import struct
import time
import os
import sys

class SimpleDHCPServer:
    def __init__(self):
        # 固定配置
        self.interface = 'ens33.1'
        self.server_ip = '169.254.1.10'
        self.subnet_mask = '255.255.255.0'
        self.router = '169.254.1.10'
        self.dns_servers = ['8.8.8.8', '8.8.4.4']
        self.domain_name = 'local.net'
        self.lease_time = 3600
        
        # IP地址池
        self.start_ip = '169.254.1.135'
        self.end_ip = '169.254.1.143'
        
        # 当前分配的IP
        self.next_ip = self.start_ip
        
        print(f"DHCP服务器配置:")
        print(f"  网卡: {self.interface}")
        print(f"  服务器IP: {self.server_ip}")
        print(f"  IP范围: {self.start_ip} - {self.end_ip}")
        print(f"  子网掩码: {self.subnet_mask}")
        print(f"  网关: {self.router}")
        print(f"  DNS: {', '.join(self.dns_servers)}")
        print("-" * 50)
    
    def ip_to_int(self, ip):
        """IP地址转整数"""
        octets = list(map(int, ip.split('.')))
        return (octets[0] << 24) + (octets[1] << 16) + (octets[2] << 8) + octets[3]
    
    def int_to_ip(self, num):
        """整数转IP地址"""
        return f"{(num >> 24) & 0xFF}.{(num >> 16) & 0xFF}.{(num >> 8) & 0xFF}.{num & 0xFF}"
    
    def get_next_ip(self):
        """获取下一个可用IP"""
        current_int = self.ip_to_int(self.next_ip)
        end_int = self.ip_to_int(self.end_ip)
        
        # 如果超出范围，回到起始
        if current_int > end_int:
            self.next_ip = self.start_ip
            current_int = self.ip_to_int(self.next_ip)
        
        ip = self.next_ip
        
        # 计算下一个IP
        current_int += 1
        self.next_ip = self.int_to_ip(current_int)
        
        return ip
    
    def create_dhcp_response(self, request_data, msg_type, yiaddr):
        """创建DHCP响应包"""
        # 解析请求包中的必要字段
        xid = struct.unpack('!I', request_data[4:8])[0]  # 事务ID
        chaddr = request_data[28:44]  # 客户端MAC地址
        
        # 构建DHCP响应头部
        response = bytearray(300)  # 固定长度
        
        # BOOTP头部
        response[0] = 2  # op: BOOTREPLY
        response[1] = 1  # htype: Ethernet
        response[2] = 6  # hlen: 6字节MAC地址
        response[3] = 0  # hops
        
        # xid (事务ID，与请求一致)
        response[4:8] = struct.pack('!I', xid)
        
        # secs, flags
        response[8:12] = struct.pack('!HH', 0, 0)
        
        # ciaddr (客户端IP，全0)
        response[12:16] = b'\x00\x00\x00\x00'
        
        # yiaddr (分配给客户端的IP)
        response[16:20] = socket.inet_aton(yiaddr)
        
        # siaddr (服务器IP)
        response[20:24] = socket.inet_aton(self.server_ip)
        
        # giaddr (中继代理IP，全0)
        response[24:28] = b'\x00\x00\x00\x00'
        
        # chaddr (客户端MAC地址)
        response[28:44] = chaddr
        
        # sname, file (全0)
        response[44:236] = b'\x00' * 192
        
        # 魔术cookie
        response[236:240] = b'\x63\x82\x53\x63'
        
        # DHCP选项开始位置
        pos = 240
        
        # 1. 消息类型 (53)
        response[pos:pos+3] = b'\x35\x01' + bytes([msg_type])  # 53 1 <msg_type>
        pos += 3
        
        # 2. 服务器标识符 (54)
        response[pos:pos+6] = b'\x36\x04' + socket.inet_aton(self.server_ip)  # 54 4 <server_ip>
        pos += 6
        
        # 3. 租约时间 (51)
        response[pos:pos+6] = b'\x33\x04' + struct.pack('!I', self.lease_time)  # 51 4 <lease_time>
        pos += 6
        
        # 4. 子网掩码 (1)
        response[pos:pos+6] = b'\x01\x04' + socket.inet_aton(self.subnet_mask)  # 1 4 <subnet_mask>
        pos += 6
        
        # 5. 路由器/网关 (3)
        response[pos:pos+6] = b'\x03\x04' + socket.inet_aton(self.router)  # 3 4 <router>
        pos += 6
        
        # 6. DNS服务器 (6)
        dns_data = socket.inet_aton(self.dns_servers[0])
        if len(self.dns_servers) > 1:
            dns_data += socket.inet_aton(self.dns_servers[1])
        
        response[pos:pos+2] = struct.pack('BB', 6, len(dns_data))
        response[pos+2:pos+2+len(dns_data)] = dns_data
        pos += 2 + len(dns_data)
        
        # 7. 结束标记 (255)
        response[pos] = 255
        pos += 1
        
        return bytes(response[:pos])
    
    def setup_interface(self):
        """设置网络接口"""
        try:
            # 检查是否以root运行
            if os.geteuid() != 0:
                print("❌ 错误：必须使用root权限运行！")
                print("   请使用: sudo python3 dhcp_simple.py")
                return False
            
            print("设置网络接口...")
            
            # 检查网卡是否存在，如果不存在则创建
            os.system(f"ip link show {self.interface} > /dev/null 2>&1")
            if os.system(f"ip link show {self.interface} > /dev/null 2>&1") != 0:
                print(f"网卡 {self.interface} 不存在，尝试创建...")
                # 如果是VLAN接口，需要先创建
                if '.' in self.interface:
                    base_iface = self.interface.split('.')[0]
                    vlan_id = self.interface.split('.')[1]
                    os.system(f"ip link add link {base_iface} name {self.interface} type vlan id {vlan_id}")
            
            # 设置IP地址
            os.system(f"ip addr flush dev {self.interface} 2>/dev/null")
            os.system(f"ip addr add {self.server_ip}/24 dev {self.interface}")
            os.system(f"ip link set {self.interface} up")
            
            print(f"✅ 接口 {self.interface} 已配置: {self.server_ip}/24")
            return True
            
        except Exception as e:
            print(f"❌ 接口设置失败: {e}")
            return False
    
    def setup_socket(self):
        """设置socket"""
        try:
            # 创建socket
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            
            # 允许地址重用和广播
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
            
            # 绑定到指定网卡（Linux系统）
            interface = 'ens33.1'
            if hasattr(socket, 'SO_BINDTODEVICE'):
                # Linux特有选项：绑定到具体网卡
                sock.setsockopt(socket.SOL_SOCKET, socket.SO_BINDTODEVICE, 
                            interface.encode('utf-8'))
                print(f"已绑定到网卡: {interface}")

            # 绑定到端口67 (DHCP服务器端口)
            sock.bind(('0.0.0.0', 67))
            
            print("✅ Socket已绑定到 0.0.0.0:67")
            return sock
            
        except PermissionError:
            print("❌ 权限错误：需要root权限绑定到端口67")
            return None
        except Exception as e:
            print(f"❌ Socket设置失败: {e}")
            return None
    
    def run(self):
        """运行DHCP服务器"""
        print("\n正在启动DHCP服务器...")
        
        # 1. 设置接口
        if not self.setup_interface():
            return
        
        # 2. 设置socket
        sock = self.setup_socket()
        if not sock:
            return
        
        print("\n✅ DHCP服务器已启动！")
        print("等待客户端请求...")
        print("按 Ctrl+C 停止服务器\n")
        
        client_count = 0
        
        try:
            while True:
                # 接收数据
                data, addr = sock.recvfrom(1024)
                client_ip, client_port = addr
                
                # 只处理来自端口68的DHCP客户端请求
                if client_port != 68:
                    continue
                
                # 检查是否为有效的DHCP包
                if len(data) < 240:
                    continue
                
                # 检查魔术cookie
                magic_cookie = data[236:240]
                if magic_cookie != b'\x63\x82\x53\x63':
                    continue
                
                # 解析消息类型
                msg_type = None
                for i in range(240, len(data)-2):
                    if data[i] == 53:  # DHCP消息类型选项
                        msg_type = data[i+2]
                        break
                
                if msg_type == 1:  # DHCP Discover
                    client_count += 1
                    print(f"\n[{client_count}] 收到DHCP Discover请求")
                    
                    # 分配IP地址
                    allocated_ip = self.get_next_ip()
                    print(f"   分配IP: {allocated_ip}")
                    
                    # 创建Offer响应
                    response = self.create_dhcp_response(data, 2, allocated_ip)  # 2 = DHCP Offer
                    
                    # 发送响应到广播地址
                    sock.sendto(response, ('255.255.255.255', 68))
                    print(f"   已发送DHCP Offer")
                    
                elif msg_type == 3:  # DHCP Request
                    print(f"\n收到DHCP Request请求")
                    
                    # 获取请求的IP
                    requested_ip = None
                    for i in range(240, len(data)-5):
                        if data[i] == 50:  # 请求的IP地址选项
                            requested_ip = socket.inet_ntoa(data[i+2:i+6])
                            break
                    
                    if requested_ip:
                        allocated_ip = requested_ip
                    else:
                        allocated_ip = self.get_next_ip()
                    
                    print(f"   确认IP: {allocated_ip}")
                    
                    # 创建ACK响应
                    response = self.create_dhcp_response(data, 5, allocated_ip)  # 5 = DHCP ACK
                    
                    # 发送响应
                    sock.sendto(response, ('255.255.255.255', 68))
                    print(f"   已发送DHCP ACK")
                    
                elif msg_type == 4:  # DHCP Decline
                    print(f"\n收到DHCP Decline")
                    # 客户端拒绝我们提供的IP，重新分配
                    
                elif msg_type == 7:  # DHCP Release
                    print(f"\n收到DHCP Release")
                    # 客户端释放IP
                    
        except KeyboardInterrupt:
            print("\n\n正在停止DHCP服务器...")
        finally:
            sock.close()
            print("DHCP服务器已停止")


def print_banner():
    """打印横幅"""
    print("\n" + "="*60)
    print("        极简DHCP服务器 - Ubuntu 22.04")
    print("="*60)
    print("说明：")
    print("  1. 此脚本会自动配置网卡 eno1.1")
    print("  2. 服务器IP: 169.254.1.10")
    print("  3. 分配范围: 169.254.1.133 - 169.254.1.143")
    print("  4. 需要root权限运行")
    print("="*60 + "\n")


if __name__ == "__main__":
    print_banner()
    
    # 创建并运行服务器
    server = SimpleDHCPServer()
    server.run()
