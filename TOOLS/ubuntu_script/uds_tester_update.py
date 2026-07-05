#!/usr/bin/env python3
"""DoIP / UDS 诊断测试工具 (优化版)

主要特性:
  - 可靠的请求/响应关联 (线程安全队列 + 超时), 消除原版 last_response 竞态
  - 完整的 DoIP 诊断确认处理: Diagnostic Message ACK(0x8002) / NACK(0x8003)
  - UDS 否定响应 0x7F 解析 + NRC 名称表
  - 自动处理 0x78 (responsePending / 响应挂起), 按 P2* 继续等待
  - 自动识别 suppressPositiveResponse (子函数 bit7), 不再傻等响应
  - 通用 DoIP 报文发送 send_doip(); 支持 Alive Check, 自动应答服务器的 Alive Check 请求
  - 连接异常 / RST / 对端关闭 的清晰报错与状态复位
  - 可选的 Tester Present 后台保活线程
  - 收发带 hexdump 与分级日志 (--verbose 控制)
"""

import argparse
import logging
import queue
import select
import socket
import struct
import threading
import time
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Tuple

logger = logging.getLogger("doip")


# --------------------------------------------------------------------------- #
# 协议常量
# --------------------------------------------------------------------------- #
class DoIP:
    PROTOCOL_VERSION = 0x02
    INVERSE_PROTOCOL_VERSION = 0xFD
    HEADER_SIZE = 8

    # Payload 类型
    GENERIC_NACK = 0x0000
    VEHICLE_ID_REQUEST = 0x0001
    VEHICLE_ID_REQUEST_EID = 0x0002
    VEHICLE_ID_REQUEST_VIN = 0x0003
    VEHICLE_ID_RESPONSE = 0x0004
    ROUTING_ACTIVATION_REQUEST = 0x0005
    ROUTING_ACTIVATION_RESPONSE = 0x0006
    ALIVE_CHECK_REQUEST = 0x0007
    ALIVE_CHECK_RESPONSE = 0x0008
    DIAGNOSTIC_MESSAGE = 0x8001
    DIAGNOSTIC_MESSAGE_ACK = 0x8002
    DIAGNOSTIC_MESSAGE_NACK = 0x8003

    PAYLOAD_TYPE_NAMES = {
        0x0000: "Generic NACK",
        0x0001: "Vehicle Identification Request",
        0x0004: "Vehicle Identification Response",
        0x0005: "Routing Activation Request",
        0x0006: "Routing Activation Response",
        0x0007: "Alive Check Request",
        0x0008: "Alive Check Response",
        0x8001: "Diagnostic Message",
        0x8002: "Diagnostic Message ACK",
        0x8003: "Diagnostic Message NACK",
    }

    # 路由激活响应码
    ROUTING_RESP_CODES = {
        0x00: "拒绝: 未知源地址",
        0x01: "拒绝: 所有 socket 已被注册/激活",
        0x02: "拒绝: 源地址与已激活的不一致",
        0x03: "拒绝: 源地址已在其它 socket 注册",
        0x04: "拒绝: 缺少认证",
        0x05: "拒绝: 确认被拒",
        0x06: "拒绝: 不支持的路由激活类型",
        0x07: "拒绝: 需要加密链路 (TLS)",
        0x10: "成功: 路由已激活",
        0x11: "成功: 需要进一步处理 (确认后激活)",
    }
    ROUTING_SUCCESS = 0x10

    # Diagnostic Message NACK 码
    DIAG_NACK_CODES = {
        0x00: "无效源地址",
        0x01: "未知目标地址",
        0x02: "诊断报文过大",
        0x03: "内存溢出",
        0x04: "目标不可达",
        0x05: "未知网络",
        0x06: "传输协议错误",
    }


# UDS 否定响应码 (NRC)
UDS_NRC = {
    0x10: "generalReject",
    0x11: "serviceNotSupported",
    0x12: "subFunctionNotSupported",
    0x13: "incorrectMessageLengthOrInvalidFormat",
    0x14: "responseTooLong",
    0x21: "busyRepeatRequest",
    0x22: "conditionsNotCorrect",
    0x24: "requestSequenceError",
    0x31: "requestOutOfRange",
    0x33: "securityAccessDenied",
    0x35: "invalidKey",
    0x36: "exceedNumberOfAttempts",
    0x37: "requiredTimeDelayNotExpired",
    0x70: "uploadDownloadNotAccepted",
    0x71: "transferDataSuspended",
    0x72: "generalProgrammingFailure",
    0x73: "wrongBlockSequenceCounter",
    0x78: "requestCorrectlyReceived-ResponsePending",
    0x7E: "subFunctionNotSupportedInActiveSession",
    0x7F: "serviceNotSupportedInActiveSession",
}

NRC_RESPONSE_PENDING = 0x78


# --------------------------------------------------------------------------- #
# 结果对象
# --------------------------------------------------------------------------- #
@dataclass
class UdsResult:
    ok: bool
    data: bytes = b""                 # 完整 UDS 响应 (含 SID)
    error: str = ""
    negative: bool = False
    nrc: Optional[int] = None

    @property
    def hex(self) -> str:
        return self.data.hex().upper()


def hexdump(data: bytes) -> str:
    return " ".join(f"{b:02X}" for b in data)


# --------------------------------------------------------------------------- #
# DoIP 客户端
# --------------------------------------------------------------------------- #
class DoIPClient:
    def __init__(self,
                 local_ip: str = "169.254.1.10",
                 local_port: int = 13400,
                 tester_address: int = 0x0E80,
                 target_address: int = 0x1212,
                 network_interface: Optional[str] = None,
                 connect_timeout: float = 5.0,
                 p2_timeout: float = 2.0,
                 p2_star_timeout: float = 5.0):
        self.local_ip = local_ip
        self.local_port = local_port
        self.tester_address = tester_address
        self.target_address = target_address
        self.network_interface = network_interface
        self.connect_timeout = connect_timeout
        self.p2_timeout = p2_timeout            # 普通响应等待
        self.p2_star_timeout = p2_star_timeout  # 收到 0x78 后的延长等待

        self.tcp_socket: Optional[socket.socket] = None
        self.udp_socket: Optional[socket.socket] = None
        self.tcp_connected = False
        self.routing_activated = False

        self.target_ip: Optional[str] = None
        self.target_port = 13400
        self.vehicle_info: Dict = {}

        # 接收线程 / 同步原语
        self._running = False
        self._rx_thread: Optional[threading.Thread] = None
        self._diag_queue: "queue.Queue[Tuple[str, object]]" = queue.Queue()
        self._routing_event = threading.Event()
        self._routing_code: Optional[int] = None
        self._tx_lock = threading.Lock()        # 串行化 UDS 请求 + 发送

        # Tester Present 保活
        self._keepalive_thread: Optional[threading.Thread] = None
        self._keepalive_stop = threading.Event()

    # ----------------------------- 底层 socket ---------------------------- #
    def _bind_to_interface(self, sock: socket.socket) -> bool:
        if not self.network_interface:
            return True
        try:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_BINDTODEVICE,
                            self.network_interface.encode())
            return True
        except PermissionError:
            logger.warning("绑定接口 %s 需要 root 权限 (SO_BINDTODEVICE)", self.network_interface)
            return False
        except OSError as e:
            logger.warning("绑定接口 %s 失败: %s", self.network_interface, e)
            return False

    @staticmethod
    def make_header(payload_type: int, payload_length: int) -> bytes:
        return struct.pack("!BBHI",
                           DoIP.PROTOCOL_VERSION,
                           DoIP.INVERSE_PROTOCOL_VERSION,
                           payload_type,
                           payload_length)

    # ------------------------- 通用 DoIP 报文发送 ------------------------- #
    def send_doip(self, payload_type: int, payload: bytes = b"") -> bool:
        """构造并通过 TCP 发送任意 DoIP 报文 (头部长度字段自动与 payload 一致)。"""
        if not (self.tcp_connected and self.tcp_socket):
            logger.error("TCP 未连接, 无法发送 DoIP 报文")
            return False
        msg = self.make_header(payload_type, len(payload)) + payload
        name = DoIP.PAYLOAD_TYPE_NAMES.get(payload_type, f"0x{payload_type:04X}")
        try:
            self.tcp_socket.sendall(msg)
            logger.info("→ 发送 %s, len=%d", name, len(payload))
            logger.debug("   报文: %s", hexdump(msg))
            return True
        except (BrokenPipeError, ConnectionResetError) as e:
            logger.error("发送失败, 连接已断开: %s", e)
            self._on_disconnect()
            return False
        except OSError as e:
            logger.error("发送 DoIP 报文失败: %s", e)
            return False

    # ----------------------------- 车辆发现 ------------------------------- #
    def setup_udp(self) -> bool:
        try:
            self.udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
            self.udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self._bind_to_interface(self.udp_socket)
            self.udp_socket.bind((self.local_ip, self.local_port))
            logger.info("UDP socket 绑定到 %s:%d", self.local_ip, self.local_port)
            return True
        except OSError as e:
            logger.error("设置 UDP socket 失败: %s", e)
            return False

    def send_vehicle_discovery(self) -> bool:
        try:
            msg = self.make_header(DoIP.VEHICLE_ID_REQUEST, 0)
            self.udp_socket.sendto(msg, ("255.255.255.255", self.local_port))
            logger.info("→ 发送车辆发现请求 (广播)")
            return True
        except OSError as e:
            logger.error("发送车辆发现请求失败: %s", e)
            return False

    @staticmethod
    def parse_vehicle_response(data: bytes) -> Dict:
        if len(data) < DoIP.HEADER_SIZE:
            return {}
        _, _, payload_type, _ = struct.unpack("!BBHI", data[:DoIP.HEADER_SIZE])
        if payload_type != DoIP.VEHICLE_ID_RESPONSE:
            return {}
        p = data[DoIP.HEADER_SIZE:]
        info: Dict = {}
        if len(p) >= 17:
            info["VIN"] = p[0:17].decode("ascii", errors="ignore").strip("\x00")
        if len(p) >= 19:
            info["logical_address"] = struct.unpack("!H", p[17:19])[0]
        if len(p) >= 25:
            info["EID"] = p[19:25].hex()
        if len(p) >= 31:
            info["GID"] = p[25:31].hex()
        if len(p) >= 33:
            info["further_action"] = p[31]
            info["vin_sync_status"] = p[32]
        return info

    def listen_for_vehicle(self, timeout: float) -> bool:
        self.udp_socket.settimeout(0.5)
        deadline = time.time() + timeout
        while time.time() < deadline:
            try:
                data, addr = self.udp_socket.recvfrom(4096)
            except socket.timeout:
                continue
            except OSError as e:
                logger.error("接收 UDP 出错: %s", e)
                break
            info = self.parse_vehicle_response(data)
            if info:
                self.vehicle_info = info
                self.target_ip = addr[0]
                la = info.get("logical_address")
                if la is not None:
                    self.target_address = la
                logger.info("✓ 发现车辆 %s: VIN=%s, 逻辑地址=%s",
                            addr[0], info.get("VIN", "?"),
                            hex(la) if la is not None else "?")
                return True
        return False

    def discover_vehicle(self, timeout: float = 5.0) -> bool:
        logger.info("开始车辆发现 ...")
        if not self.udp_socket and not self.setup_udp():
            return False
        if self.listen_for_vehicle(2.0):
            return True
        logger.info("未收到主动声明, 发送发现请求 ...")
        if not self.send_vehicle_discovery():
            return False
        return self.listen_for_vehicle(timeout)

    # ----------------------------- TCP 连接 ------------------------------- #
    def setup_tcp_connection(self) -> bool:
        if not self.target_ip:
            logger.error("未发现目标车辆 IP")
            return False
        try:
            self.tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self._bind_to_interface(self.tcp_socket)
            self.tcp_socket.settimeout(self.connect_timeout)
            logger.info("连接 %s:%d ...", self.target_ip, self.target_port)
            self.tcp_socket.connect((self.target_ip, self.target_port))
            self.tcp_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            self.tcp_connected = True
            self._start_rx_thread()
            logger.info("✓ TCP 连接建立")
            return True
        except socket.timeout:
            logger.error("✗ TCP 连接超时")
        except ConnectionRefusedError:
            logger.error("✗ 连接被拒绝 (目标未监听 13400?)")
        except OSError as e:
            logger.error("✗ 建立 TCP 连接失败: %s", e)
        return False

    # ----------------------------- 路由激活 ------------------------------- #
    def activate_routing(self, activation_type: int = 0x00,
                         oem_specific: bytes = b"") -> bool:
        logger.info("发送路由激活请求 (源=%s, 类型=0x%02X) ...",
                    hex(self.tester_address), activation_type)
        # SA(2) + 激活类型(1) + 保留(4) [+ OEM(4, 可选)]
        payload = struct.pack("!HB4s", self.tester_address, activation_type, b"\x00" * 4)
        if oem_specific:
            payload += oem_specific
        self._routing_event.clear()
        self._routing_code = None
        if not self.send_doip(DoIP.ROUTING_ACTIVATION_REQUEST, payload):
            return False
        if not self._routing_event.wait(timeout=self.p2_timeout):
            logger.error("✗ 等待路由激活响应超时")
            return False
        if self._routing_code == DoIP.ROUTING_SUCCESS:
            self.routing_activated = True
            logger.info("✓ 路由激活成功")
            return True
        desc = DoIP.ROUTING_RESP_CODES.get(self._routing_code, "未知")
        logger.error("✗ 路由激活失败: 0x%02X (%s)", self._routing_code or 0, desc)
        return False

    def send_alive_check(self) -> bool:
        """主动发送 Alive Check 请求 (一般由服务器发起, 这里提供主动能力)。"""
        return self.send_doip(DoIP.ALIVE_CHECK_REQUEST, b"")

    # --------------------------- 自动连接流程 ----------------------------- #
    def auto_connect(self) -> bool:
        return (self.discover_vehicle()
                and self.setup_tcp_connection()
                and self.activate_routing())

    def ensure_connection(self) -> bool:
        if self.tcp_connected and self.routing_activated:
            return True
        logger.info("连接未就绪, 执行自动连接 ...")
        return self.auto_connect()

    # ----------------------------- 发送 UDS ------------------------------- #
    def send_uds(self, uds_payload: bytes,
                 expect_response: Optional[bool] = None) -> UdsResult:
        """发送一条原始 UDS 报文 (含 SID), 处理 ACK/NACK 与否定响应。

        expect_response=None 时, 根据 suppressPositiveResponse 位自动判断。
        """
        if not uds_payload:
            return UdsResult(False, error="空 UDS 报文")
        if not self.ensure_connection():
            return UdsResult(False, error="连接建立失败")

        # suppressPositiveResponse: 子函数 (第2字节) 的 bit7
        suppress = len(uds_payload) >= 2 and bool(uds_payload[1] & 0x80)
        if expect_response is None:
            expect_response = not suppress

        diag_payload = struct.pack("!HH", self.tester_address,
                                   self.target_address) + uds_payload

        with self._tx_lock:
            # 清空可能残留的旧事件
            self._drain_queue()
            logger.info("→ UDS 请求: %s", hexdump(uds_payload))
            if not self.send_doip(DoIP.DIAGNOSTIC_MESSAGE, diag_payload):
                return UdsResult(False, error="DoIP 发送失败")

            acked = False
            deadline = time.time() + self.p2_timeout
            while True:
                remaining = deadline - time.time()
                if remaining <= 0:
                    if not expect_response:
                        return UdsResult(True, error="(已抑制正响应)")
                    if acked:
                        return UdsResult(False, error="收到 ACK 但等待 UDS 响应超时")
                    return UdsResult(False, error="等待 UDS 响应超时")
                try:
                    kind, value = self._diag_queue.get(timeout=min(remaining, 0.5))
                except queue.Empty:
                    continue

                if kind == "nack":
                    code = value
                    desc = DoIP.DIAG_NACK_CODES.get(code, "未知")
                    return UdsResult(False, error=f"DoIP Diagnostic NACK 0x{code:02X} ({desc})")
                if kind == "ack":
                    acked = True
                    logger.info("  收到 Diagnostic ACK 0x%02X", value)
                    if not expect_response:
                        return UdsResult(True, error="(已抑制正响应, 仅 ACK)")
                    continue
                if kind == "disconnect":
                    return UdsResult(False, error="连接被对端关闭/复位 (RST)")
                if kind == "diag":
                    uds_resp: bytes = value
                    # 否定响应 0x7F SID NRC
                    if len(uds_resp) >= 3 and uds_resp[0] == 0x7F:
                        nrc = uds_resp[2]
                        if nrc == NRC_RESPONSE_PENDING:
                            logger.info("  收到 0x78 responsePending, 继续等待 (P2*) ...")
                            deadline = time.time() + self.p2_star_timeout
                            continue
                        name = UDS_NRC.get(nrc, "unknown")
                        return UdsResult(False, data=uds_resp, error=f"否定响应 NRC 0x{nrc:02X} ({name})",
                                         negative=True, nrc=nrc)
                    return UdsResult(True, data=uds_resp)

    def send_uds_service(self, service_id: int, sub_function: Optional[int] = None,
                         data: bytes = b"") -> UdsResult:
        """按 服务ID + 子函数 + 数据 组装并发送。"""
        if sub_function is not None:
            uds = struct.pack("!BB", service_id, sub_function) + data
        else:
            uds = struct.pack("!B", service_id) + data
        return self.send_uds(uds)

    # --------------------------- Tester Present 保活 ---------------------- #
    def start_keepalive(self, period: float = 2.0) -> None:
        if self._keepalive_thread and self._keepalive_thread.is_alive():
            return
        self._keepalive_stop.clear()

        def _loop():
            while not self._keepalive_stop.wait(period):
                if self.tcp_connected and self.routing_activated:
                    # 3E 80 (抑制正响应)
                    self.send_uds(b"\x3E\x80", expect_response=False)

        self._keepalive_thread = threading.Thread(target=_loop, daemon=True)
        self._keepalive_thread.start()
        logger.info("已启动 Tester Present 保活 (周期 %.1fs)", period)

    def stop_keepalive(self) -> None:
        self._keepalive_stop.set()
        logger.info("已停止 Tester Present 保活")

    # ----------------------------- 接收线程 ------------------------------- #
    def _start_rx_thread(self) -> None:
        self._running = True
        self._rx_thread = threading.Thread(target=self._rx_loop, daemon=True)
        self._rx_thread.start()

    def _rx_loop(self) -> None:
        buffer = b""
        while self._running and self.tcp_connected:
            try:
                readable, _, _ = select.select([self.tcp_socket], [], [], 0.2)
                if not readable:
                    continue
                data = self.tcp_socket.recv(4096)
                if not data:
                    logger.warning("对端关闭了连接 (FIN)")
                    self._on_disconnect()
                    break
                buffer += data
                buffer = self._consume_buffer(buffer)
            except ConnectionResetError:
                logger.error("对端发送了 RST (连接被复位)")
                self._on_disconnect()
                break
            except OSError as e:
                if self._running:
                    logger.error("接收出错: %s", e)
                break

    def _consume_buffer(self, buffer: bytes) -> bytes:
        while len(buffer) >= DoIP.HEADER_SIZE:
            ver, inv, ptype, plen = struct.unpack("!BBHI", buffer[:DoIP.HEADER_SIZE])
            # 协议版本校验
            if ver != DoIP.PROTOCOL_VERSION or (ver ^ 0xFF) != inv:
                logger.warning("DoIP 头部版本异常 ver=0x%02X inv=0x%02X, 丢弃 1 字节重同步", ver, inv)
                buffer = buffer[1:]
                continue
            total = DoIP.HEADER_SIZE + plen
            if len(buffer) < total:
                break  # 等待更多数据
            self._handle_message(ptype, buffer[DoIP.HEADER_SIZE:total], plen)
            buffer = buffer[total:]
        return buffer

    def _handle_message(self, ptype: int, payload: bytes, declared_len: int) -> None:
        name = DoIP.PAYLOAD_TYPE_NAMES.get(ptype, f"0x{ptype:04X}")
        logger.info("← 收到 %s, len=%d", name, len(payload))
        logger.debug("   payload: %s", hexdump(payload))

        # 头部声明长度与实际不一致 (本工程曾出现的故障特征)
        if declared_len != len(payload):
            logger.warning("   ⚠ DoIP 声明长度=%d 与实际 payload=%d 不一致!", declared_len, len(payload))

        if ptype == DoIP.ROUTING_ACTIVATION_RESPONSE:
            if len(payload) >= 5:
                ta, la, code = struct.unpack("!HHB", payload[:5])
                desc = DoIP.ROUTING_RESP_CODES.get(code, "未知")
                logger.info("   Tester=%s 车辆=%s 响应码=0x%02X (%s)", hex(ta), hex(la), code, desc)
                self._routing_code = code
            self._routing_event.set()

        elif ptype == DoIP.DIAGNOSTIC_MESSAGE:
            if len(payload) >= 4:
                uds = payload[4:]
                if uds:
                    self._diag_queue.put(("diag", uds))
                else:
                    logger.warning("   ⚠ 诊断报文无 UDS 数据")
            else:
                logger.warning("   ⚠ 诊断报文过短")

        elif ptype == DoIP.DIAGNOSTIC_MESSAGE_ACK:
            code = payload[4] if len(payload) >= 5 else 0
            self._diag_queue.put(("ack", code))

        elif ptype == DoIP.DIAGNOSTIC_MESSAGE_NACK:
            code = payload[4] if len(payload) >= 5 else 0
            self._diag_queue.put(("nack", code))

        elif ptype == DoIP.ALIVE_CHECK_REQUEST:
            # 服务器在检查 tester 是否存活, 自动回应 Alive Check Response
            resp = struct.pack("!H", self.tester_address)
            logger.info("   收到 Alive Check 请求, 自动回应")
            self.send_doip(DoIP.ALIVE_CHECK_RESPONSE, resp)

        elif ptype == DoIP.GENERIC_NACK:
            code = payload[0] if payload else 0
            logger.error("   收到 Generic NACK code=0x%02X", code)

    def _on_disconnect(self) -> None:
        self.tcp_connected = False
        self.routing_activated = False
        self._running = False
        self._routing_event.set()
        try:
            self._diag_queue.put_nowait(("disconnect", None))
        except queue.Full:
            pass

    def _drain_queue(self) -> None:
        try:
            while True:
                self._diag_queue.get_nowait()
        except queue.Empty:
            pass

    # ------------------------------- 清理 -------------------------------- #
    def cleanup(self) -> None:
        self.stop_keepalive()
        self._running = False
        if self.tcp_socket:
            try:
                self.tcp_socket.close()
            except OSError:
                pass
        if self.udp_socket:
            try:
                self.udp_socket.close()
            except OSError:
                pass
        if self._rx_thread:
            self._rx_thread.join(timeout=2)


# --------------------------------------------------------------------------- #
# 交互式诊断工具
# --------------------------------------------------------------------------- #
class UDSDiagnosticTool:
    UDS_SERVICES = {
        "10": "诊断会话控制 (Diagnostic Session Control)",
        "11": "ECU 重置 (ECU Reset)",
        "14": "清除故障码 (Clear Diagnostic Information)",
        "19": "读取故障码 (Read DTC Information)",
        "22": "通过 ID 读数据 (Read Data By Identifier)",
        "2E": "通过 ID 写数据 (Write Data By Identifier)",
        "27": "安全访问 (Security Access)",
        "28": "通信控制 (Communication Control)",
        "31": "例程控制 (Routine Control)",
        "3E": "待机握手 (Tester Present)",
        "85": "故障码设置控制 (Control DTC Setting)",
    }

    UDS_EXAMPLES = {
        "10 01": "默认会话",
        "10 03": "扩展会话",
        "11 01": "硬重置",
        "22 F190": "读取 VIN",
        "27 01": "安全访问 - 请求种子",
        "3E 00": "待机握手 (需响应)",
        "3E 80": "待机握手 (抑制响应)",
    }

    def __init__(self, client: DoIPClient):
        self.client = client

    # ------------------------------ 界面 -------------------------------- #
    def print_banner(self) -> None:
        c = self.client
        print("=" * 60)
        print("            UDS / DoIP 诊断工具 (优化版)")
        print("=" * 60)
        print(f"本地: {c.local_ip}:{c.local_port}   接口: {c.network_interface or '(默认)'}")
        print(f"Tester 地址: {hex(c.tester_address)}   目标地址: {hex(c.target_address)}")
        print("=" * 60)

    def print_help(self) -> None:
        print("""
可用命令:
  <hex...>        直接发送 UDS, 例: 10 01 / 22 F190 / 31 01 FF00
  send            交互输入并发送 UDS
  raw <hex>       发送原始 DoIP payload (诊断报文) — 调试用
  connect         手动执行 发现+连接+路由激活
  alive           发送 Alive Check 请求
  keepalive on|off  开/关 Tester Present 后台保活
  status          显示连接状态
  services        列出常用 UDS 服务
  examples        列出 UDS 示例
  help            帮助
  exit/quit       退出
""")

    def print_status(self) -> None:
        c = self.client
        print("\n状态:")
        print(f"  车辆 IP : {c.target_ip or '未发现'}")
        print(f"  TCP     : {'已连接' if c.tcp_connected else '未连接'}")
        print(f"  路由激活: {'已激活' if c.routing_activated else '未激活'}")
        if c.vehicle_info.get("VIN"):
            print(f"  VIN     : {c.vehicle_info['VIN']}")

    # --------------------------- 命令解析 ------------------------------- #
    @staticmethod
    def parse_uds_command(cmd: str) -> bytes:
        """把 '22 F190' / '2710' 这类字符串解析为 UDS 字节。"""
        tokens = cmd.replace(",", " ").split()
        if len(tokens) == 1:
            return bytes.fromhex(tokens[0])
        return bytes.fromhex("".join(t.zfill(2) if len(t) % 2 else t for t in tokens))

    def send_command(self, cmd: str) -> None:
        try:
            uds = self.parse_uds_command(cmd)
        except ValueError as e:
            print(f"✗ 无法解析为十六进制: {e}")
            return
        if not uds:
            print("✗ 空命令")
            return

        result = self.client.send_uds(uds)
        self._print_result(uds, result)

    def _print_result(self, request: bytes, r: UdsResult) -> None:
        print(f"\n请求: {hexdump(request)}")
        if r.ok:
            if r.data:
                print(f"✓ 正响应: {hexdump(r.data)}")
                sid = r.data[0] & 0xBF
                print(f"  对应服务: 0x{sid:02X}")
                if len(r.data) > 1:
                    print(f"  数据    : {hexdump(r.data[1:])}")
            else:
                print(f"✓ 完成 {r.error}")
        else:
            if r.negative:
                print(f"✗ 否定响应: {hexdump(r.data)}  -> {r.error}")
            else:
                print(f"✗ 失败: {r.error}")

    # ------------------------------ 主循环 ------------------------------ #
    def run(self) -> None:
        self.print_banner()
        self.print_help()
        while True:
            try:
                line = input("\n>>> ").strip()
            except (EOFError, KeyboardInterrupt):
                print()
                break
            if not line:
                continue

            low = line.lower()
            if low in ("exit", "quit", "q"):
                break
            elif low in ("help", "?"):
                self.print_help()
            elif low == "status":
                self.print_status()
            elif low == "services":
                for sid, desc in self.UDS_SERVICES.items():
                    print(f"  {sid}: {desc}")
            elif low == "examples":
                for cmd, desc in self.UDS_EXAMPLES.items():
                    print(f"  {cmd:<10} - {desc}")
            elif low == "connect":
                print("✓ 连接成功" if self.client.auto_connect() else "✗ 连接失败")
            elif low == "alive":
                self.client.send_alive_check()
            elif low.startswith("keepalive"):
                arg = low.split()[1] if len(low.split()) > 1 else ""
                if arg == "on":
                    self.client.start_keepalive()
                elif arg == "off":
                    self.client.stop_keepalive()
                else:
                    print("用法: keepalive on|off")
            elif low == "send":
                uds_cmd = input("输入 UDS 指令: ").strip()
                if uds_cmd:
                    self.send_command(uds_cmd)
            elif low.startswith("send "):
                self.send_command(line[5:].strip())
            elif low.startswith("raw "):
                try:
                    payload = bytes.fromhex(line[4:].replace(" ", ""))
                    self.client.send_doip(DoIP.DIAGNOSTIC_MESSAGE, payload)
                except ValueError as e:
                    print(f"✗ 十六进制错误: {e}")
            else:
                # 直接当作 UDS hex 处理
                try:
                    int(line.split()[0], 16)
                    self.send_command(line)
                except ValueError:
                    print(f"未知命令: {line} (输入 help)")

        self.client.cleanup()


# --------------------------------------------------------------------------- #
# 入口
# --------------------------------------------------------------------------- #
def main() -> None:
    parser = argparse.ArgumentParser(description="UDS / DoIP 诊断工具 (优化版)")
    parser.add_argument("--ip", default="169.254.1.10", help="本地 IP")
    parser.add_argument("--port", type=int, default=13400, help="本地端口")
    parser.add_argument("--tester", default="0xE80", help="Tester 源地址 (hex)")
    parser.add_argument("--target", default="0x1212", help="目标逻辑地址 (hex)")
    parser.add_argument("--interface", default=None, help="网络接口 (如 ens33.1, 需 root)")
    parser.add_argument("--p2", type=float, default=2.0, help="普通响应超时 (秒)")
    parser.add_argument("--p2star", type=float, default=5.0, help="responsePending 后超时 (秒)")
    parser.add_argument("--command", default="", help="非交互: 直接执行一条或多条 UDS, 用 ';' 分隔")
    parser.add_argument("--keepalive", action="store_true", help="连接后启用 Tester Present 保活")
    parser.add_argument("-v", "--verbose", action="store_true", help="输出 DoIP 报文 hexdump")

    args = parser.parse_args()
    logging.basicConfig(level=logging.DEBUG if args.verbose else logging.INFO,
                        format="%(message)s")

    client = DoIPClient(
        local_ip=args.ip,
        local_port=args.port,
        tester_address=int(args.tester, 16),
        target_address=int(args.target, 16),
        network_interface=args.interface,
        p2_timeout=args.p2,
        p2_star_timeout=args.p2star,
    )
    tool = UDSDiagnosticTool(client)

    try:
        if args.command:
            if not client.ensure_connection():
                print("✗ 连接失败")
                return
            if args.keepalive:
                client.start_keepalive()
            for cmd in args.command.split(";"):
                cmd = cmd.strip()
                if cmd:
                    tool.send_command(cmd)
        else:
            tool.run()
    except Exception as e:  # noqa: BLE001 - 顶层兜底
        logger.exception("程序异常: %s", e)
    finally:
        client.cleanup()


if __name__ == "__main__":
    main()
