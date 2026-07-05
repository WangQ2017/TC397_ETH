#!/usr/bin/env python3
"""
SOME/IP SD服务端实现 - 完整版本
订阅成功后按100ms周期发送Event Notification
"""

import socket
import struct
import time
import threading
from datetime import datetime

# 配置参数
LOCAL_IP = "10.23.0.10"
INTERFACE = "ens33.23"
MULTICAST_IP = "239.23.0.2"          # SD组播地址
SOMEIP_SD_PORT = 30490
EVENT_MULTICAST_IP = "239.23.0.1"    # 事件组播地址(工程配置)
EVENT_PORT = 40000                   # UDP事件端口(工程: SCG_SD_UDP_fixe_10_23_0_33_40000)
EVENT_INTERVAL_SEC = 0.1             # 100ms周期

# 服务定义(与工程Sd/SoAd配置对齐)
SERVICES = {
    "Vechicle_Speed": {
        "service_id": 0xC3CB,
        "instance_id": 23,
        "eventgroup_id": 1,
        "event_id": 0x8001,
        "pdu_header_id": 0xC3CB8001,
        "pdu_length": 16,
        "sd_flag": 0xC0,
        "protocol": "UDP",
        "port": 40000,
        "major_version": 0x01,
        "minor_version": 0x00,
        "ttl": 0xFFFFFF,
        "send_multicast": True,
    },
    "Vechicle_Status": {
        "service_id": 0xC3CC,
        "instance_id": 23,
        "eventgroup_id": 1,
        "event_id": 0x8001,
        "pdu_header_id": 0xC3CC8001,
        "pdu_length": 16,
        "sd_flag": 0xC0,
        "protocol": "UDP",
        "port": 40000,
        "major_version": 0x01,
        "minor_version": 0x00,
        "ttl": 0xFFFFFF,
        "send_multicast": True,
    },
    "Vechicle_Info": {
        "service_id": 0xC3CD,
        "instance_id": 23,
        "eventgroup_id": 1,
        "event_id": 0x8001,
        "pdu_header_id": 0xC3CD8001,
        "pdu_length": 4,
        "sd_flag": 0xC0,
        "protocol": "TCP",
        "port": 40002,
        "major_version": 0x01,
        "minor_version": 0x00,
        "ttl": 0xFFFFFF,
        "send_multicast": False,
    }
}

class TCPServerManager:
    """TCP服务端 - 在OFFER端口监听, 等待DUT主动连接(SoAdSocketTcpInitiate=true, 本地47842)"""

    def __init__(self, local_ip, port):
        self.local_ip = local_ip
        self.port = port
        self.connections = {}
        self.lock = threading.Lock()
        self.running = True
        self.server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_sock.bind((self.local_ip, self.port))
        self.server_sock.listen(5)
        self.server_sock.settimeout(1.0)
        print(f"  [TCP] Listening on {self.local_ip}:{self.port} (await DUT connect)")
        self.accept_thread = threading.Thread(target=self._accept_loop, daemon=True)
        self.accept_thread.start()

    def _accept_loop(self):
        while self.running:
            try:
                conn, addr = self.server_sock.accept()
                client_ip, client_port = addr
                conn.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
                with self.lock:
                    old = self.connections.pop(client_ip, None)
                    if old:
                        try:
                            old.close()
                        except Exception:
                            pass
                    self.connections[client_ip] = conn
                print(f"  [TCP] Accepted {client_ip}:{client_port} -> {self.local_ip}:{self.port}")
            except socket.timeout:
                continue
            except OSError as e:
                if self.running:
                    print(f"  [TCP] Accept error on port {self.port}: {e}")
                break

    def has_connection(self, client_ip):
        with self.lock:
            return client_ip in self.connections

    def send(self, client_ip, data):
        with self.lock:
            conn = self.connections.get(client_ip)
        if conn is None:
            return False
        try:
            conn.sendall(data)
            return True
        except Exception as e:
            print(f"  [TCP] Send to {client_ip} failed: {e}")
            self.close(client_ip)
            return False

    def close(self, client_ip):
        with self.lock:
            conn = self.connections.pop(client_ip, None)
        if conn:
            try:
                conn.close()
            except Exception:
                pass

    def stop_all(self):
        self.running = False
        with self.lock:
            for conn in self.connections.values():
                try:
                    conn.close()
                except Exception:
                    pass
            self.connections.clear()
        try:
            self.server_sock.close()
        except Exception:
            pass

class SOMEIPSD_Server:
    def __init__(self, interface, local_ip):
        """初始化SOME/IP SD服务端"""
        self.interface = interface
        self.local_ip = local_ip
        
        # TCP服务: 在OFFER端口监听, DUT收到OFFER后主动连入(工程TcpInitiate=true)
        self.tcp_servers = {}
        for name, cfg in SERVICES.items():
            if cfg["protocol"] == "TCP":
                port = cfg["port"]
                if port not in self.tcp_servers:
                    self.tcp_servers[port] = TCPServerManager(local_ip, port)
        
        # 创建原始套接字并绑定到指定网卡
        self.sock = self._create_socket_with_interface()
        
        # UDP事件发送socket(绑定本地40000端口)
        self.event_sock = self._create_event_socket()
        
        # 加入多播组
        self._join_multicast()
        
        # 设置超时
        self.sock.settimeout(1.0)
        
        print(f"SOME/IP SD Server initialized on {interface}")
        print(f"Local IP: {local_ip}")
        print(f"SD Port: {SOMEIP_SD_PORT}")
        print(f"SD Multicast Group: {MULTICAST_IP}")
        print(f"Event Multicast: {EVENT_MULTICAST_IP}:{EVENT_PORT}")
        print(f"Event Interval: {EVENT_INTERVAL_SEC * 1000:.0f}ms")
        print("=" * 60)
        
        # 存储订阅状态
        self.subscriptions = {}
        self.sub_lock = threading.Lock()
        self.running = True
        
        # SD/ Event Session ID
        self.session_id = 1
        self.event_session_id = 1
        self.event_counters = {name: 0 for name in SERVICES}
        
        # 显示服务信息
        self._print_service_info()
        
        # 启动周期Event发送线程
        self.event_thread = threading.Thread(target=self.event_send_loop, daemon=True)
        self.event_thread.start()
    
    def _create_socket_with_interface(self):
        """创建套接字并绑定到指定网卡"""
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(('', SOMEIP_SD_PORT))
        
        try:
            # 获取接口索引并绑定
            iface_index = socket.if_nametoindex(self.interface)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF, 
                           socket.inet_aton(self.local_ip))
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF, 
                           struct.pack('I', iface_index))
            
            ttl = struct.pack('b', 1)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, 0)
            
        except Exception as e:
            print(f"Warning: Could not bind to interface {self.interface}: {e}")
        
        return sock
    
    def _create_event_socket(self):
        """创建UDP Event发送socket, 绑定本地40000端口"""
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            sock.bind((self.local_ip, EVENT_PORT))
        except OSError as e:
            print(f"Warning: bind event socket to {self.local_ip}:{EVENT_PORT} failed: {e}")
            sock.bind(('', EVENT_PORT))
        try:
            ttl = struct.pack('b', 1)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF,
                           socket.inet_aton(self.local_ip))
        except Exception as e:
            print(f"Warning: event socket multicast setup failed: {e}")
        return sock

    def _print_service_info(self):
        """打印服务信息"""
        print("\nAvailable Services:")
        print("-" * 80)
        for name, config in SERVICES.items():
            protocol = config["protocol"]
            port = config["port"]
            print(f"  {name:20s} | SID: 0x{config['service_id']:04X} | "
                  f"Inst: {config['instance_id']:2d} | "
                  f"Event: 0x{config['event_id']:04X} | "
                  f"PDU: {config['pdu_length']:2d}B | "
                  f"{protocol:4s} :{port}")
        print("-" * 80)
    
    def _join_multicast(self):
        """加入SOME/IP SD多播组"""
        try:
            mreq = struct.pack("4s4s", socket.inet_aton(MULTICAST_IP), socket.inet_aton(self.local_ip))
            self.sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
            print(f"Joined multicast group {MULTICAST_IP} on interface {self.interface}")
        except Exception as e:
            print(f"Warning: Could not join multicast group: {e}")
    
    def create_sd_header(self, flags, entries_length):
        """创建SD头部"""
        sd_header = bytearray(8)
        sd_header[0] = flags & 0xFF
        sd_header[1] = 0x00
        sd_header[2] = 0x00
        sd_header[3] = 0x00
        sd_header[4] = (entries_length >> 24) & 0xFF
        sd_header[5] = (entries_length >> 16) & 0xFF
        sd_header[6] = (entries_length >> 8) & 0xFF
        sd_header[7] = entries_length & 0xFF
        return bytes(sd_header)
    
    def create_offer_service_entry(self, service_config):
        """创建Offer Service Entry"""
        entry = bytearray(16)
        entry[0] = 0x01
        entry[1] = 0x00
        entry[2] = 0x00
        entry[3] = 0x10
        
        service_id = service_config["service_id"]
        entry[4] = (service_id >> 8) & 0xFF
        entry[5] = service_id & 0xFF
        
        instance_id = service_config["instance_id"]
        entry[6] = (instance_id >> 8) & 0xFF
        entry[7] = instance_id & 0xFF
        
        entry[8] = service_config["major_version"] & 0xFF
        
        ttl = service_config["ttl"]
        entry[9] = (ttl >> 16) & 0xFF
        entry[10] = (ttl >> 8) & 0xFF
        entry[11] = ttl & 0xFF
        
        minor_version = service_config["minor_version"]
        entry[12] = (minor_version >> 24) & 0xFF
        entry[13] = (minor_version >> 16) & 0xFF
        entry[14] = (minor_version >> 8) & 0xFF
        entry[15] = minor_version & 0xFF
        
        return bytes(entry)
    
    def create_subscribe_eventgroup_entry(self, service_config, entry_type=0x06):
        """创建Subscribe Eventgroup Entry"""
        entry = bytearray(16)
        entry[0] = entry_type & 0xFF
        entry[1] = 0x00
        entry[2] = 0x00
        entry[3] = 0x10
        
        service_id = service_config["service_id"]
        entry[4] = (service_id >> 8) & 0xFF
        entry[5] = service_id & 0xFF
        
        instance_id = service_config["instance_id"]
        entry[6] = (instance_id >> 8) & 0xFF
        entry[7] = instance_id & 0xFF
        
        entry[8] = service_config["major_version"] & 0xFF
        
        ttl = service_config["ttl"]
        entry[9] = (ttl >> 16) & 0xFF
        entry[10] = (ttl >> 8) & 0xFF
        entry[11] = ttl & 0xFF
        
        entry[12] = 0x00
        
        if entry_type == 0x06:
            entry[13] = 0x80
        elif entry_type == 0x07:
            entry[13] = 0x80
        else:
            entry[13] = 0x00
        
        eventgroup_id = service_config["eventgroup_id"]
        entry[14] = (eventgroup_id >> 8) & 0xFF
        entry[15] = eventgroup_id & 0xFF
        
        return bytes(entry)
    
    def create_option_array_length(self, option_length):
        """创建Option数组长度"""
        option_array_length = bytearray(4)
        option_array_length[0] = (option_length >> 24) & 0xFF
        option_array_length[1] = (option_length >> 16) & 0xFF
        option_array_length[2] = (option_length >> 8) & 0xFF
        option_array_length[3] = option_length & 0xFF
        return bytes(option_array_length)
    
    def create_ipv4_endpoint_option(self, service_config):
        """创建IPv4 Endpoint Option"""
        option = bytearray(12)
        option[0] = 0x00
        option[1] = 0x09  # 3 words
        
        option[2] = 0x04
        option[3] = 0x00
        
        ip_parts = self.local_ip.split('.')
        option[4] = int(ip_parts[0])
        option[5] = int(ip_parts[1])
        option[6] = int(ip_parts[2])
        option[7] = int(ip_parts[3])
        
        option[8] = 0x00
        
        protocol = service_config["protocol"]
        if protocol == "UDP":
            option[9] = 0x11
        elif protocol == "TCP":
            option[9] = 0x06
        
        port = service_config["port"]
        option[10] = (port >> 8) & 0xFF
        option[11] = port & 0xFF
        
        return bytes(option)
    
    def create_someip_header(self, service_id=0xFFFF, method_id=0x8100, length=0):
        """创建SOME/IP头部"""
        header = bytearray(16)
        header[0] = (service_id >> 8) & 0xFF
        header[1] = service_id & 0xFF
        header[2] = (method_id >> 8) & 0xFF
        header[3] = method_id & 0xFF
        
        length_from_client_id = length + 8
        header[4] = (length_from_client_id >> 24) & 0xFF
        header[5] = (length_from_client_id >> 16) & 0xFF
        header[6] = (length_from_client_id >> 8) & 0xFF
        header[7] = length_from_client_id & 0xFF
        
        header[8] = 0x00
        header[9] = 0x00
        # SessionID: 使用递增的会话ID (SD要求每条报文的SessionID递增)
        session_id = getattr(self, "session_id", 1)
        header[10] = (session_id >> 8) & 0xFF
        header[11] = session_id & 0xFF
        # 递增并在到达0xFFFF后回绕到1
        self.session_id = session_id + 1
        if self.session_id > 0xFFFF:
            self.session_id = 1
        header[12] = 0x01
        header[13] = 0x01
        header[14] = 0x02
        header[15] = 0x00
        
        return bytes(header)
    
    def create_event_message(self, service_config, payload):
        """构建Event Notification报文 (SoAd PDU Header + SOME/IP Header + Payload)"""
        service_id = service_config["service_id"]
        event_id = service_config["event_id"]
        pdu_header_id = service_config["pdu_header_id"]
        payload_len = len(payload)
        
        # SOME/IP Header (MessageType=0x02 NOTIFICATION)
        someip_header = bytearray(16)
        someip_header[0] = (service_id >> 8) & 0xFF
        someip_header[1] = service_id & 0xFF
        someip_header[2] = (event_id >> 8) & 0xFF
        someip_header[3] = event_id & 0xFF
        someip_length = 8 + payload_len
        someip_header[4] = (someip_length >> 24) & 0xFF
        someip_header[5] = (someip_length >> 16) & 0xFF
        someip_header[6] = (someip_length >> 8) & 0xFF
        someip_header[7] = someip_length & 0xFF
        someip_header[8] = 0x00
        someip_header[9] = 0x00
        session_id = self.event_session_id
        self.event_session_id = (self.event_session_id + 1) & 0xFFFF
        if self.event_session_id == 0:
            self.event_session_id = 1
        someip_header[10] = (session_id >> 8) & 0xFF
        someip_header[11] = session_id & 0xFF
        someip_header[12] = 0x01
        someip_header[13] = 0x01
        someip_header[14] = 0x02  # NOTIFICATION
        someip_header[15] = 0x00
        
        someip_msg = bytes(someip_header) + payload
        
        # SoAd PDU Header (工程SoAd PduHeaderEnable=true)
        soad_header = bytearray(8)
        soad_header[0] = (pdu_header_id >> 24) & 0xFF
        soad_header[1] = (pdu_header_id >> 16) & 0xFF
        soad_header[2] = (pdu_header_id >> 8) & 0xFF
        soad_header[3] = pdu_header_id & 0xFF
        soad_header[4] = (len(someip_msg) >> 24) & 0xFF
        soad_header[5] = (len(someip_msg) >> 16) & 0xFF
        soad_header[6] = (len(someip_msg) >> 8) & 0xFF
        soad_header[7] = len(someip_msg) & 0xFF
        
        return bytes(soad_header) + someip_msg
    
    def _make_event_payload(self, service_name, service_config):
        """生成测试用Event Payload"""
        pdu_len = service_config["pdu_length"]
        counter = self.event_counters.get(service_name, 0)
        self.event_counters[service_name] = (counter + 1) & 0xFF
        payload = bytearray(pdu_len)
        payload[0] = counter & 0xFF
        payload[1] = (counter >> 8) & 0xFF
        for i in range(2, pdu_len):
            payload[i] = (counter + i) & 0xFF
        return bytes(payload)
    
    def send_udp_event(self, sub, payload):
        """发送UDP Event (单播+组播)"""
        service_name = sub["service"]
        service_config = SERVICES[service_name]
        message = self.create_event_message(service_config, payload)
        
        if sub.get("event_ip") and sub.get("event_port"):
            try:
                self.event_sock.sendto(message, (sub["event_ip"], sub["event_port"]))
            except Exception as e:
                print(f"  [Event] UDP unicast to {sub['event_ip']}:{sub['event_port']} failed: {e}")
        
        if service_config.get("send_multicast"):
            try:
                self.event_sock.sendto(message, (EVENT_MULTICAST_IP, EVENT_PORT))
            except Exception as e:
                print(f"  [Event] UDP multicast failed: {e}")
    
    def send_tcp_event(self, sub, payload):
        """发送TCP Event (在DUT已建立的TCP连接上发送)"""
        service_name = sub["service"]
        service_config = SERVICES[service_name]
        message = self.create_event_message(service_config, payload)
        client_ip = sub["client_ip"]
        tcp_server = self.tcp_servers.get(service_config["port"])
        if tcp_server is None:
            return
        if not tcp_server.send(client_ip, message):
            if sub.get("event_count", 0) % 50 == 0:
                print(f"  [Event] {service_name}: waiting for TCP from {client_ip} "
                      f"on port {service_config['port']}")
    
    def event_send_loop(self):
        """100ms周期发送已订阅服务的Event"""
        print("\nEvent send loop started (interval=100ms)")
        send_log_interval = 50
        while self.running:
            try:
                with self.sub_lock:
                    active_subs = [s for s in self.subscriptions.values() if s.get("active")]
                
                for sub in active_subs:
                    service_name = sub["service"]
                    service_config = SERVICES[service_name]
                    payload = self._make_event_payload(service_name, service_config)
                    
                    if service_config["protocol"] == "UDP":
                        self.send_udp_event(sub, payload)
                    elif service_config["protocol"] == "TCP":
                        self.send_tcp_event(sub, payload)
                    
                    sub["event_count"] = sub.get("event_count", 0) + 1
                    if sub["event_count"] % send_log_interval == 1:
                        print(f"  [Event] {service_name}: sent #{sub['event_count']} "
                              f"(PDU {service_config['pdu_length']}B)")
                
                time.sleep(EVENT_INTERVAL_SEC)
            except Exception as e:
                if self.running:
                    print(f"  [Event] loop error: {e}")
                time.sleep(EVENT_INTERVAL_SEC)
    
    def send_offer_service(self, service_name, dest_ip=None, dest_port=SOMEIP_SD_PORT):
        """发送Offer Service报文"""
        if service_name not in SERVICES:
            print(f"Error: Service {service_name} not found!")
            return False
        
        service_config = SERVICES[service_name]
        
        timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        dest_type = "UNICAST" if dest_ip else "MULTICAST"
        dest_addr = dest_ip if dest_ip else MULTICAST_IP
        
        print(f"[{timestamp}] Sending OFFER for {service_name} ({dest_type} to {dest_addr}):")
        print(f"  Service ID: 0x{service_config['service_id']:04X}")
        print(f"  Instance ID: {service_config['instance_id']}")
        print(f"  Protocol: {service_config['protocol']}")
        print(f"  Port: {service_config['port']}")
        
        try:
            entry = self.create_offer_service_entry(service_config)
            entry_length = len(entry)
            
            option = self.create_ipv4_endpoint_option(service_config)
            option_length = len(option)
            
            sd_header = self.create_sd_header(service_config["sd_flag"], entry_length)
            option_array_len = self.create_option_array_length(option_length)
            
            sd_message = sd_header + entry + option_array_len + option
            someip_header = self.create_someip_header(0xFFFF, 0x8100, len(sd_message))
            full_message = someip_header + sd_message
            
            if dest_ip:
                self.sock.sendto(full_message, (dest_ip, dest_port))
                print(f"  OFFER sent via unicast to {dest_ip}:{dest_port}")
            else:
                self.sock.sendto(full_message, (MULTICAST_IP, SOMEIP_SD_PORT))
                print(f"  OFFER sent via multicast to {MULTICAST_IP}:{SOMEIP_SD_PORT}")
            
            return True
            
        except Exception as e:
            print(f"  Error sending OFFER: {e}")
            import traceback
            traceback.print_exc()
            return False
    
    def send_subscribe_ack(self, service_name, client_ip, client_port, options=None):
        """发送SubscribeEventgroupAck报文, 并激活周期Event发送"""
        if service_name not in SERVICES:
            print(f"Error: Service {service_name} not found!")
            return False
        
        service_config = SERVICES[service_name]
        options = options or []
        
        timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        print(f"[{timestamp}] Sending SUBSCRIBE ACK for {service_name} to {client_ip}:{client_port}:")
        print(f"  Service ID: 0x{service_config['service_id']:04X}")
        print(f"  Instance ID: {service_config['instance_id']}")
        print(f"  EventGroup ID: {service_config['eventgroup_id']}")
        
        try:
            entry = bytearray(self.create_subscribe_eventgroup_entry(service_config, entry_type=0x07))
            entry[1] = 0x00
            entry[2] = 0x00
            entry[3] = 0x00
            entry[13] = 0x00
            entry = bytes(entry)
            
            option_array_len = self.create_option_array_length(0)
            sd_header = self.create_sd_header(service_config["sd_flag"], len(entry))
            sd_message = sd_header + entry + option_array_len
            someip_header = self.create_someip_header(0xFFFF, 0x8100, len(sd_message))
            
            full_message = someip_header + sd_message
            self.sock.sendto(full_message, (client_ip, client_port))
            print(f"  SUBSCRIBE ACK sent to {client_ip}:{client_port} ({len(full_message)} bytes)")
            
            if service_config["protocol"] == "UDP":
                event_ip = client_ip
                event_port = None
                for opt in options:
                    if opt.get("type") == 0x04:
                        event_ip = opt.get("ip_address", client_ip)
                        event_port = opt.get("port")
                        print(f"  Client event endpoint: {event_ip}:{event_port} (UDP)")
                        break
            else:
                event_ip = client_ip
                event_port = service_config["port"]
                tcp_server = self.tcp_servers.get(event_port)
                if tcp_server and tcp_server.has_connection(client_ip):
                    print(f"  TCP connection ready: {client_ip} -> {self.local_ip}:{event_port}")
                else:
                    print(f"  TCP connection pending: expect {client_ip}:47842 -> "
                          f"{self.local_ip}:{event_port} (DUT connects after OFFER)")
            
            key = f"{service_name}_{client_ip}"
            with self.sub_lock:
                self.subscriptions[key] = {
                    "service": service_name,
                    "client_ip": client_ip,
                    "client_sd_port": client_port,
                    "event_ip": event_ip,
                    "event_port": event_port,
                    "active": True,
                    "subscribe_time": time.time(),
                    "event_count": 0,
                }
            print(f"  Event periodic send ENABLED for {service_name} "
                  f"(every {EVENT_INTERVAL_SEC * 1000:.0f}ms, PDU={service_config['pdu_length']}B)")
            
            return True
            
        except Exception as e:
            print(f"  Error sending SUBSCRIBE ACK: {e}")
            import traceback
            traceback.print_exc()
            return False
    
    def parse_someip_header(self, data):
        """解析SOME/IP头部"""
        if len(data) < 16:
            return None
        
        header = {}
        header['service_id'] = (data[0] << 8) | data[1]
        header['method_id'] = (data[2] << 8) | data[3]
        header['length'] = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]
        header['client_id'] = (data[8] << 8) | data[9]
        header['session_id'] = (data[10] << 8) | data[11]
        header['protocol_version'] = data[12]
        header['interface_version'] = data[13]
        header['message_type'] = data[14]
        header['return_code'] = data[15]
        
        return header
    
    def parse_sd_header(self, data):
        """解析SD头部"""
        if len(data) < 8:
            return None
        
        header = {}
        header['flags'] = data[0]
        header['reserved'] = data[1:4]
        header['entry_array_length'] = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]
        
        return header
    
    def parse_entry(self, data, offset):
        """解析Entry"""
        if len(data) < offset + 16:
            return None, offset
        
        entry = {}
        entry['type'] = data[offset]
        entry['index_1st_options'] = data[offset + 1]
        entry['index_2nd_options'] = data[offset + 2]
        entry['num_options'] = data[offset + 3]
        entry['num_opt1'] = (data[offset + 3] >> 4) & 0x0F
        entry['num_opt2'] = data[offset + 3] & 0x0F
        
        entry['service_id'] = (data[offset + 4] << 8) | data[offset + 5]
        entry['instance_id'] = (data[offset + 6] << 8) | data[offset + 7]
        entry['major_version'] = data[offset + 8]
        entry['ttl'] = (data[offset + 9] << 16) | (data[offset + 10] << 8) | data[offset + 11]
        
        entry_type = entry['type']
        
        if entry_type == 0x00 or entry_type == 0x01 or entry_type == 0x02:
            entry['minor_version'] = (data[offset + 12] << 24) | (data[offset + 13] << 16) | \
                                    (data[offset + 14] << 8) | data[offset + 15]
        elif entry_type == 0x06 or entry_type == 0x07 or entry_type == 0x08 or entry_type == 0x09:
            entry['reserved_byte'] = data[offset + 12]
            entry['option_byte'] = data[offset + 13]
            entry['initial_data_requested'] = (data[offset + 13] >> 7) & 0x01
            entry['counter'] = data[offset + 13] & 0x0F
            entry['eventgroup_id'] = (data[offset + 14] << 8) | data[offset + 15]
        
        return entry, offset + 16
    
    def parse_option(self, data, offset):
        """解析Option (AUTOSAR: Length字段为covered length, 不含2B Length+1B Type)"""
        if len(data) < offset + 3:
            return None, offset + 1
        
        covered_length = (data[offset] << 8) | data[offset + 1]
        option_total = 2 + 1 + covered_length  # Length(2) + Type(1) + covered
        
        if len(data) < offset + option_total:
            return None, offset + max(option_total, 1)
        
        option = {}
        option['covered_length'] = covered_length
        option['type'] = data[offset + 2]
        option['reserved'] = data[offset + 3]
        
        if option['type'] == 0x04 and covered_length >= 0x09:
            option['ip_address'] = f"{data[offset + 4]}.{data[offset + 5]}." \
                                  f"{data[offset + 6]}.{data[offset + 7]}"
            option['protocol'] = data[offset + 9]
            option['port'] = (data[offset + 10] << 8) | data[offset + 11]
        elif option['type'] == 0x14 and covered_length >= 0x09:
            option['ip_address'] = f"{data[offset + 4]}.{data[offset + 5]}." \
                                  f"{data[offset + 6]}.{data[offset + 7]}"
            option['protocol'] = data[offset + 9]
            option['port'] = (data[offset + 10] << 8) | data[offset + 11]
        
        return option, offset + option_total
    
    def process_received_packet(self, data, client_ip, client_port):
        """处理接收到的数据包"""
        someip_header = self.parse_someip_header(data)
        if not someip_header:
            return
        
        if someip_header['service_id'] != 0xFFFF or someip_header['method_id'] != 0x8100:
            return
        
        sd_data = data[16:]
        if len(sd_data) < 8:
            return
        
        sd_header = self.parse_sd_header(sd_data)
        if not sd_header:
            return
        
        timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        
        entry_array_length = sd_header['entry_array_length']
        entry_offset = 8
        entries_end = entry_offset + entry_array_length
        
        if entries_end > len(sd_data):
            return
        
        entries = []
        offset = entry_offset
        while offset < entries_end:
            entry, next_offset = self.parse_entry(sd_data, offset)
            if not entry or next_offset <= offset:
                break
            entries.append(entry)
            offset = next_offset
        
        options_offset = entries_end
        if len(sd_data) < options_offset + 4:
            return
        
        option_array_length = (sd_data[options_offset] << 24) | (sd_data[options_offset + 1] << 16) | \
                             (sd_data[options_offset + 2] << 8) | sd_data[options_offset + 3]
        offset = options_offset + 4
        
        options = []
        options_end = offset + option_array_length
        prev_offset = offset
        while offset < options_end and offset < len(sd_data):
            option, offset = self.parse_option(sd_data, offset)
            if option:
                options.append(option)
            if offset <= prev_offset:
                offset = prev_offset + 1
            prev_offset = offset
        
        entry_type_names = {
            0x00: "FIND",
            0x01: "OFFER",
            0x02: "STOP_OFFER",
            0x06: "SUBSCRIBE",
            0x07: "SUBSCRIBE_ACK",
            0x08: "STOP_SUBSCRIBE",
            0x09: "STOP_SUBSCRIBE_ACK"
        }
        
        for entry in entries:
            entry_type = entry['type']
            service_id = entry['service_id']
            instance_id = entry['instance_id']
            
            service_name = None
            for name, config in SERVICES.items():
                if config["service_id"] == service_id and config["instance_id"] == instance_id:
                    service_name = name
                    break
            
            entry_name = entry_type_names.get(entry_type, f"UNKNOWN(0x{entry_type:02X})")
            
            print(f"\n[{timestamp}] Received {entry_name} from {client_ip}:{client_port}")
            print(f"  Service: {service_name or 'Unknown'}")
            print(f"  Service ID: 0x{service_id:04X}, Instance ID: {instance_id}")
            print(f"  Session ID: {someip_header['session_id']:04X}")
            
            if entry_type == 0x00:
                if service_name:
                    print(f"  Responding to FIND with unicast OFFER...")
                    self.send_offer_service(service_name, dest_ip=client_ip, dest_port=client_port)
                else:
                    print(f"  Service not found for ID 0x{service_id:04X}/{instance_id}")
            
            elif entry_type == 0x06:
                if service_name:
                    print(f"  EventGroup ID: {entry['eventgroup_id']}")
                    self.send_subscribe_ack(service_name, client_ip, client_port, options)
                else:
                    print(f"  Error: Unknown service 0x{service_id:04X}/{instance_id}")
            
            elif entry_type == 0x07:
                print(f"  Received SUBSCRIBE ACK confirmation")
            
            elif entry_type == 0x01:
                print(f"  Received OFFER from another instance")
            
            elif entry_type == 0x02:
                print(f"  Received STOP OFFER")
            
            elif entry_type == 0x08:
                print(f"  Received STOP SUBSCRIBE request")
                if service_name:
                    key = f"{service_name}_{client_ip}"
                    with self.sub_lock:
                        if key in self.subscriptions:
                            sub = self.subscriptions.pop(key)
                            if service_config := SERVICES.get(service_name):
                                if service_config["protocol"] == "TCP":
                                    tcp_server = self.tcp_servers.get(service_config["port"])
                                    if tcp_server:
                                        tcp_server.close(client_ip)
                            print(f"  Subscription removed for {service_name}, event send stopped")
    
    def receive_loop(self):
        """接收循环"""
        print(f"\nStarting receive loop on {MULTICAST_IP}:{SOMEIP_SD_PORT}...")
        
        while self.running:
            try:
                data, addr = self.sock.recvfrom(65535)
                client_ip, client_port = addr
                
                if client_ip == MULTICAST_IP or client_ip.startswith("10.23."):
                    self.process_received_packet(data, client_ip, client_port)
                
            except socket.timeout:
                continue
            except Exception as e:
                if self.running:
                    print(f"Error in receive loop: {e}")
                break
    
    def offer_all_services(self, interval=10):
        """定期广播所有服务的Offer"""
        print("\nStarting periodic multicast OFFER broadcasts...")
        
        offer_count = 0
        while self.running:
            offer_count += 1
            print(f"\n{'='*60}")
            print(f"Multicast OFFER Cycle #{offer_count}")
            print(f"{'='*60}")
            
            for service_name in SERVICES:
                self.send_offer_service(service_name, dest_ip=None)
                time.sleep(1.0)
            
            if self.subscriptions:
                print(f"\nActive Subscriptions ({len(self.subscriptions)}):")
                for key, sub in self.subscriptions.items():
                    age = time.time() - sub["subscribe_time"]
                    evt = sub.get("event_count", 0)
                    ep = f"{sub.get('event_ip')}:{sub.get('event_port')}" if sub.get("event_port") else "multicast"
                    print(f"  {sub['service']:20s} from {sub['client_ip']:15s} "
                          f"endpoint={ep} events={evt} (age: {age:.1f}s)")
            
            for i in range(interval):
                if not self.running:
                    break
                time.sleep(1)
    
    def start(self):
        """启动服务端"""
        print("\nStarting SOME/IP SD Server...")
        print("=" * 60)
        print(f"Interface: {self.interface}")
        print(f"Local IP: {self.local_ip}")
        print(f"Multicast: {MULTICAST_IP}:{SOMEIP_SD_PORT}")
        print("=" * 60)
        print("Operation modes:")
        print("  1. Periodic multicast OFFER broadcasts")
        print("  2. Unicast OFFER in response to FIND messages")
        print("  3. Unicast SUBSCRIBE_ACK in response to SUBSCRIBE messages")
        print(f"  4. Periodic Event Notification every {EVENT_INTERVAL_SEC * 1000:.0f}ms after subscribe")
        for port, srv in self.tcp_servers.items():
            print(f"  5. TCP listen {self.local_ip}:{port} (DUT connects before Subscribe)")
        print("=" * 60)
        print("Press Ctrl+C to stop")
        print("=" * 60)
        
        offer_thread = threading.Thread(target=self.offer_all_services, args=(15,))
        offer_thread.daemon = True
        offer_thread.start()
        
        receive_thread = threading.Thread(target=self.receive_loop)
        receive_thread.daemon = True
        receive_thread.start()
        
        try:
            while True:
                time.sleep(1)
                
        except KeyboardInterrupt:
            print("\n\nStopping SOME/IP SD Server...")
            self.running = False
            for tcp_server in self.tcp_servers.values():
                tcp_server.stop_all()
            try:
                self.event_sock.close()
            except Exception:
                pass
            self.sock.close()
            print("Server stopped.")
    
    def stop(self):
        """停止服务端"""
        self.running = False
        for tcp_server in self.tcp_servers.values():
            tcp_server.stop_all()
        try:
            self.event_sock.close()
        except Exception:
            pass
        self.sock.close()

def main():
    """主函数"""
    print("SOME/IP SD Server - Complete Version")
    print("=" * 60)
    print(f"Interface: {INTERFACE}")
    print(f"Local IP: {LOCAL_IP}")
    print(f"Multicast: {MULTICAST_IP}:{SOMEIP_SD_PORT}")
    print("=" * 60)
    
    try:
        server = SOMEIPSD_Server(INTERFACE, LOCAL_IP)
        server.start()
        
    except PermissionError:
        print("\nError: Permission denied!")
        print("Please run: sudo python3 someip_sd_server.py")
    except Exception as e:
        print(f"\nError: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()
