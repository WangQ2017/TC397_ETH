/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  TcpIp_DhcpV4Server.c
 *        \brief  Implementation of Dynamic Host Configuration Protocol for IPv4 - Server (DHCPv4 Server)
 *
 *      \details  This file is part of the TcpIp DHCPv4 Server submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp DHCPv4 Server submodule. >> TcpIp_DhcpV4Server.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_DHCPV4SERVER_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_DHCPV4SERVER == STD_ON)                                                                              /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "IpBase.h"
#include "TcpIp_Priv.h"
#include "TcpIp.h"
#include "TcpIp_DhcpV4Server.h"
#include "TcpIp_Lcfg.h"
#if defined(TCPIP_DHCPV4SERVER_GET_PORT_MAC_ADDR_FUNC)
# include "EthIf.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (STATIC)
# define STATIC static
#endif

#define TCPIP_DHCPV4SERVER_MSG_FLAG_BROADCAST 0x8000U /* (1U << 15U) */

/* Lengths of DHCP message header field in bytes */
#define TCPIP_DHCPV4SERVER_MSG_LEN_OP                1U
#define TCPIP_DHCPV4SERVER_MSG_LEN_HTYPE             1U
#define TCPIP_DHCPV4SERVER_MSG_LEN_HLEN              1U
#define TCPIP_DHCPV4SERVER_MSG_LEN_HOPS              1U
#define TCPIP_DHCPV4SERVER_MSG_LEN_XID               4U
#define TCPIP_DHCPV4SERVER_MSG_LEN_SECS              2U
#define TCPIP_DHCPV4SERVER_MSG_LEN_FLAGS             2U
#define TCPIP_DHCPV4SERVER_MSG_LEN_CIADDR            4U
#define TCPIP_DHCPV4SERVER_MSG_LEN_YIADDR            4U
#define TCPIP_DHCPV4SERVER_MSG_LEN_SIADDR            4U
#define TCPIP_DHCPV4SERVER_MSG_LEN_GIAADR            4U
#define TCPIP_DHCPV4SERVER_MSG_LEN_CHADDR           16U
#define TCPIP_DHCPV4SERVER_MSG_LEN_SNAME            64U
#define TCPIP_DHCPV4SERVER_MSG_LEN_BOOTFILE        128U
#define TCPIP_DHCPV4SERVER_MSG_LEN_MAGIC_COOKIE      4U

/* Offsets of DHCP message header fields in bytes */
#define TCPIP_DHCPV4SERVER_MSG_OFS_OP              0U
#define TCPIP_DHCPV4SERVER_MSG_OFS_HTYPE           (TCPIP_DHCPV4SERVER_MSG_OFS_OP           + TCPIP_DHCPV4SERVER_MSG_LEN_OP)
#define TCPIP_DHCPV4SERVER_MSG_OFS_HLEN            (TCPIP_DHCPV4SERVER_MSG_OFS_HTYPE        + TCPIP_DHCPV4SERVER_MSG_LEN_HTYPE)
#define TCPIP_DHCPV4SERVER_MSG_OFS_HOPS            (TCPIP_DHCPV4SERVER_MSG_OFS_HLEN         + TCPIP_DHCPV4SERVER_MSG_LEN_HLEN)
#define TCPIP_DHCPV4SERVER_MSG_OFS_XID             (TCPIP_DHCPV4SERVER_MSG_OFS_HOPS         + TCPIP_DHCPV4SERVER_MSG_LEN_HOPS)
#define TCPIP_DHCPV4SERVER_MSG_OFS_SECS            (TCPIP_DHCPV4SERVER_MSG_OFS_XID          + TCPIP_DHCPV4SERVER_MSG_LEN_XID)
#define TCPIP_DHCPV4SERVER_MSG_OFS_FLAGS           (TCPIP_DHCPV4SERVER_MSG_OFS_SECS         + TCPIP_DHCPV4SERVER_MSG_LEN_SECS)
#define TCPIP_DHCPV4SERVER_MSG_OFS_CIADDR          (TCPIP_DHCPV4SERVER_MSG_OFS_FLAGS        + TCPIP_DHCPV4SERVER_MSG_LEN_FLAGS)
#define TCPIP_DHCPV4SERVER_MSG_OFS_YIADDR          (TCPIP_DHCPV4SERVER_MSG_OFS_CIADDR       + TCPIP_DHCPV4SERVER_MSG_LEN_CIADDR)
#define TCPIP_DHCPV4SERVER_MSG_OFS_SIADDR          (TCPIP_DHCPV4SERVER_MSG_OFS_YIADDR       + TCPIP_DHCPV4SERVER_MSG_LEN_YIADDR)
#define TCPIP_DHCPV4SERVER_MSG_OFS_GIADDR          (TCPIP_DHCPV4SERVER_MSG_OFS_SIADDR       + TCPIP_DHCPV4SERVER_MSG_LEN_SIADDR)
#define TCPIP_DHCPV4SERVER_MSG_OFS_CHADDR          (TCPIP_DHCPV4SERVER_MSG_OFS_GIADDR       + TCPIP_DHCPV4SERVER_MSG_LEN_GIAADR)
#define TCPIP_DHCPV4SERVER_MSG_OFS_SNAME           (TCPIP_DHCPV4SERVER_MSG_OFS_CHADDR       + TCPIP_DHCPV4SERVER_MSG_LEN_CHADDR)
#define TCPIP_DHCPV4SERVER_MSG_OFS_BOOTFILE        (TCPIP_DHCPV4SERVER_MSG_OFS_SNAME        + TCPIP_DHCPV4SERVER_MSG_LEN_SNAME)
#define TCPIP_DHCPV4SERVER_MSG_OFS_MAGIC_COOKIE    (TCPIP_DHCPV4SERVER_MSG_OFS_BOOTFILE     + TCPIP_DHCPV4SERVER_MSG_LEN_BOOTFILE)
#define TCPIP_DHCPV4SERVER_MSG_OFS_OPTIONS         (TCPIP_DHCPV4SERVER_MSG_OFS_MAGIC_COOKIE + TCPIP_DHCPV4SERVER_MSG_LEN_MAGIC_COOKIE)

/* Minimum length of a valid DHCP message: Header + DHCP Message Type Option (3 byte) + End Option (1 byte)  */
#define TCPIP_DHCPV4SERVER_MIN_MSG_LEN             (TCPIP_DHCPV4SERVER_MSG_OFS_OPTIONS + 4u)

#define TCPIP_DHCPV4SERVER_MSG_HTYPE_10MBIT_ETH  1U
#define TCPIP_DHCPV4SERVER_MSG_HLEN_10MBIT_ETH   6U
#define TCPIP_DHCPV4SERVER_MSG_HOPS              0U

#define TCPIP_DHCPV4SERVER_MSG_OP_BOOTREQUEST    1U
#define TCPIP_DHCPV4SERVER_MSG_OP_BOOTREPLY      2U

/* Magic cookie that follows the DHCP message header and marks the beginning of the options section [RFC2131 3. The Client-Server Protocol] and [RFC2132 2. BOOTP Extension/DHCP Option Field Format] */
#define TCPIP_DHCPV4SERVER_MSG_MAGIC_COOKIE      0x63825363U

/* DHCP Options and BOOTP Vendor Extensions [RFC2132]           Supported              */
/*                                                                 |                   */
#define TCPIP_DHCPV4SERVER_MSG_OPT_PAD                      0U /* [y] 3. 1. Pad Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_END                    255U /* [y] 3. 2. End Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_SUBNET_MASK              1U /* [y] 3. 3. Subnet Mask */
#define TCPIP_DHCPV4SERVER_MSG_OPT_TIME_OFFSET              2U /* [_] 3. 4. Time Offset */
#define TCPIP_DHCPV4SERVER_MSG_OPT_ROUTER                   3U /* [y] 3. 5. Router Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_TIME_SERVER              4U /* [_] 3. 6. Time Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NAME_SERVER              5U /* [_] 3. 7. Name Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_DOMAIN_NAME_SERVER       6U /* [_] 3. 8. Domain Name Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_LOG_SERVER               7U /* [_] 3. 9. Log Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_COOKIE_SERVER            8U /* [_] 3.10. Cookie Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_LPR_SERVER               9U /* [_] 3.11. LPR Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_IMPRESS_SERVER          10U /* [_] 3.12. Impress Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_RES_LOC_SERVER          11U /* [_] 3.13. Resource Location Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_HOSTNAME                12U /* [_] 3.14. Host Name Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_BOOTFILE_SIZE           13U /* [_] 3.15. Boot File Size Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_MERIT_DUMPFILE          14U /* [_] 3.16. Merit Dump File */
#define TCPIP_DHCPV4SERVER_MSG_OPT_DOMAIN_NAME             15U /* [_] 3.17. Domain Name */
#define TCPIP_DHCPV4SERVER_MSG_OPT_SWAP_SERVER             16U /* [_] 3.18. Swap Server */
#define TCPIP_DHCPV4SERVER_MSG_OPT_ROOT_PATH               17U /* [_] 3.19. Root Path */
#define TCPIP_DHCPV4SERVER_MSG_OPT_EXT_PATH                18U /* [_] 3.20. Extensions Path */
#define TCPIP_DHCPV4SERVER_MSG_OPT_IP_FORWARD              19U /* [_] 4. 1. IP Forwarding Enable/Disable Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NON_LOC_SRC_RT          20U /* [_] 4. 2. Non-Local Source Routing Enable/Disable Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_POLICY_FILTER           21U /* [_] 4. 3. Policy Filter Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_MAX_DATAGRAMSIZE        22U /* [_] 4. 4. Maximum Datagram Reassembly Size */
#define TCPIP_DHCPV4SERVER_MSG_OPT_DEFAULT_TTL             23U /* [_] 4. 5. Default IP Time-to-live */
#define TCPIP_DHCPV4SERVER_MSG_OPT_PMTU_TIMEOUT            24U /* [_] 4. 6. Path MTU Aging Timeout Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_PMTU_PLATEAU_TBL        25U /* [_] 4. 7. Path MTU Plateau Table Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_INTERFACE_MTU           26U /* [_] 5. 1. Interface MTU Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_ALL_SUBNETS_LOCAL       27U /* [_] 5. 2. All Subnets are Local Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_BROADCAST_ADDR          28U /* [_] 5. 3. Broadcast Address Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_PERFORM_MASK_DISC       29U /* [_] 5. 4. Perform Mask Discovery Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_MASK_SUPPLIER           30U /* [_] 5. 5. Mask Supplier Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_PERFORM_RTR_DISC        31U /* [_] 5. 6. Perform Router Discovery Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_RTR_SOLICIT_ADDR        32U /* [_] 5. 7. Router Solicitation Address Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_STATIC_ROUTE            33U /* [_] 5. 8. Static Route Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_TRAILER_ENCAP           34U /* [_] 6. 1. Trailer Encapsulation Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_ARP_CACHE_TIMEOUT       35U /* [_] 6. 2. ARP Cache Timeout Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_ETHRNET_ENCAP           36U /* [_] 6. 3. Ethernet Encapsulation Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_TCP_DEFAULT_TTL         37U /* [_] 7. 1. TCP Default TTL Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_TCP_KEEP_ALIVE_INT      38U /* [_] 7. 2. TCP Keepalive Interval Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_TCP_KEEP_ALIVE_DATA     39U /* [_] 7. 3. TCP Keepalive Garbage Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NET_INFO_SERVICE        40U /* [_] 8. 1. Network Information Service Domain Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NET_INFO_SERVERS        41U /* [_] 8. 2. Network Information Servers Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NTP_SERVERS             42U /* [_] 8. 3. Network Time Protocol Servers Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_VENDOR_INFO             43U /* [_] 8. 4. Vendor Specific Information */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NETBIOS_                44U /* [_] 8. 5. NetBIOS over TCP/IP Name Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NETBIOS_SERVERS         45U /* [_] 8. 6. NetBIOS over TCP/IP Datagram Distribution Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NETBIOS_NODE_TYPE       46U /* [_] 8. 7. NetBIOS over TCP/IP Node Type Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NETBIOS_SCOPE           47U /* [_] 8. 8. NetBIOS over TCP/IP Scope Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_XWINDOW_FONT_SERVER     48U /* [_] 8. 9. X Window System Font Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_XWINDOW_DISP_MGR        49U /* [_] 8.10. X Window System Display Manager Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NIS_DOMAIN              64U /* [_] 8.11. Network Information Service+ Domain Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NIS_SERVERS             65U /* [_] 8.12. Network Information Service+ Servers Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_MOBILE_IP_HOME_AGENT    68U /* [_] 8.13. Mobile IP Home Agent option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_SMTP_SERVER             69U /* [_] 8.14. Simple Mail Transport Protocol (SMTP) Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_POP3_SERVER             70U /* [_] 8.15. Post Office Protocol (POP3) Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_NNTP_SERVER             71U /* [_] 8.16. Network News Transport Protocol (NNTP) Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_WWW_SERVER              72U /* [_] 8.17. Default World Wide Web (WWW) Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_DEFAULT_FINGER_SERVER   73U /* [_] 8.18. Default Finger Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_IRC_SERVER              74U /* [_] 8.19. Default Internet Relay Chat (IRC) Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_ST_SERVER               75U /* [_] 8.20. StreetTalk Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_STDA_SERVER             76U /* [_] 8.21. StreetTalk Directory Assistance (STDA) Server Option */
#define TCPIP_DHCPV4SERVER_MSG_OPT_REQUESTED_IP_ADDR       50U /* [y] 9. 1. Requested IP Address */
#define TCPIP_DHCPV4SERVER_MSG_OPT_IP_ADDR_LEASE_TIME      51U /* [y] 9. 2. IP Address Lease Time */
#define TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD         52U /* [y] 9. 3. Option Overload (RX only) */
#define TCPIP_DHCPV4SERVER_MSG_OPT_TFTP_SERVER_NAME        66U /* [_] 9. 4. TFTP server name */
#define TCPIP_DHCPV4SERVER_MSG_OPT_BOOTFILE_NAME           67U /* [_] 9. 5. Bootfile name */
#define TCPIP_DHCPV4SERVER_MSG_OPT_DHCP_MSG_TYPE           53U /* [y] 9. 6. DHCP Message Type */
#define TCPIP_DHCPV4SERVER_MSG_OPT_SERVER_ID               54U /* [y] 9. 7. Server Identifier */
#define TCPIP_DHCPV4SERVER_MSG_OPT_PARAM_REQUEST_LIST      55U /* [y] 9. 8. Parameter Request List */
#define TCPIP_DHCPV4SERVER_MSG_OPT_MESSAGE                 56U /* [y] 9. 9. Message */
#define TCPIP_DHCPV4SERVER_MSG_OPT_MAX_DHCP_MSG_SIZE       57U /* [_] 9.10. Maximum DHCP Message Size */
#define TCPIP_DHCPV4SERVER_MSG_OPT_RENEVAL_TIME_T1         58U /* [_] 9.11. Renewal (T1) Time Value */
#define TCPIP_DHCPV4SERVER_MSG_OPT_REBINDING_TIME_T2       59U /* [_] 9.12. Rebinding (T2) Time Value */
#define TCPIP_DHCPV4SERVER_MSG_OPT_VENDOR_CLASS_ID         60U /* [_] 9.13. Vendor class identifier */
#define TCPIP_DHCPV4SERVER_MSG_OPT_CLIENT_ID               61U /* [y] 9.14. Client-identifier */

#define TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN                  2U /* All options except PAD and END option have a header with to fields 'Code' (1 byte) and 'Len' (1 byte) [RFC2132 2. BOOTP Extension/DHCP Option Field Format] */
#define TCPIP_DHCPV4SERVER_MSG_OPT_DHCP_MSG_TYPE_LEN        1U /* Option payload is always 1 byte */
#define TCPIP_DHCPV4SERVER_MSG_OPT_SUBNET_MASK_LEN          4U /* Option payload is always 4 bytes */
#define TCPIP_DHCPV4SERVER_MSG_OPT_ROUTER_LEN               4U /* Option payload is always 4 bytes.*/
#define TCPIP_DHCPV4SERVER_MSG_OPT_SERVER_ID_LEN            4U /* Option payload is always 4 bytes */
#define TCPIP_DHCPV4SERVER_MSG_OPT_IP_ADDR_LEASE_TIME_LEN   4U /* Option payload is always 4 bytes */
#define TCPIP_DHCPV4SERVER_MSG_OPT_REQUESTED_IP_ADDR_LEN    4U /* Option payload is always 4 bytes */
#define TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD_LEN      1U /* Option payload is always 1 bytes */
#define TCPIP_DHCPV4SERVER_MSG_OPT_MESSAGE_MIN_LEN          1U /* Option payload is at least 1 bytes */


/* Internal flags of requestable (supported) options. These flags are set in the ClientParamReqSet (TcpIp_DhcpV4Server_AddrLeaseRecType) */
#define TCPIP_DHCPV4SERVER_MSG_OPT_REQ_FLAG_SUBNET_MASK    (1u << 0)
#define TCPIP_DHCPV4SERVER_MSG_OPT_REQ_FLAG_ROUTER         (1u << 1)

#define TCPIP_DHCPV4SERVER_REQUESTABLE_OPTIONS_COUNT        2U

#define TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD_FILE     1U
#define TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD_SNAME    2U

#define TCPIP_DHCPV4SERVER_MSG_INVALID                      0U /* Indicates that the message has no or an invalid DHCP message type */
#define TCPIP_DHCPV4SERVER_RX_MSG_DHCPDISCOVER              1U /* RX / Client broadcast to locate available servers. */
#define TCPIP_DHCPV4SERVER_TX_MSG_DHCPOFFER                 2U /* TX / Server to client in response to DHCPDISCOVER with offer of configuration parameters.*/
#define TCPIP_DHCPV4SERVER_RX_MSG_DHCPREQUEST               3U /* RX / Client message to servers either (a) requesting offered parameters from one server and implicitly
                                                                *      declining offers from all others, (b) confirming correctness of previously allocated address after,
                                                                *      e.g., system reboot, or (c) extending the lease on a particular network address. */
#define TCPIP_DHCPV4SERVER_RX_MSG_DHCPDECLINE               4U /* RX / Client to server indicating network address is already in use. */
#define TCPIP_DHCPV4SERVER_TX_MSG_DHCPACK                   5U /* TX / Server to client with configuration parameters, including committed network address. */
#define TCPIP_DHCPV4SERVER_TX_MSG_DHCPNAK                   6U /* TX / Server to client indicating client's notion of network address is incorrect
                                                                *      (e.g., client has moved to new subnet) or client's lease as expired */
#define TCPIP_DHCPV4SERVER_RX_MSG_DHCPRELEASE               7U /* RX / Client to server relinquishing network address and canceling remaining lease. */
#define TCPIP_DHCPV4SERVER_RX_MSG_DHCPINFORM                8U /* RX / Client to server, asking only for local configuration parameters; client already has externally configured network address. */

#define TCPIP_DHCPV4SERVER_SERVER_PORT                     67U /* "DHCP messages from a client to a server are sent to the 'DHCP server' port (67)" [RFC2131 4.1 Constructing and sending DHCP messages] */
#define TCPIP_DHCPV4SERVER_CLIENT_PORT                     68U /* "DHCP messages from a server to a client are sent to the 'DHCP client' port (68)" [RFC2131 4.1 Constructing and sending DHCP messages] */

#define TCPIP_DHCPV4SERVER_ERROR_MESSAGE_NONE                          0U
#define TCPIP_DHCPV4SERVER_ERROR_MESSAGE_CLIENT_MOVED_SUBNET           1U
#define TCPIP_DHCPV4SERVER_ERROR_MESSAGE_INVALID_IP_ADDRESS_REQUESTED  2U
#define TCPIP_DHCPV4SERVER_ERROR_MESSAGE_COUNT                         2U /* Number of different error messages, the server may return in DHCKNAK messages. */

#define TCPIP_DHCPV4SERVER_TIME_INFINITE  0xFFFFFFFFU /* Infinity time value [RFC2131 3.3 Interpretation and representation of time values] */


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */

#define TcpIp_DhcpV4Server_VCfgGetServerSocketId(SERVER_INSTANCE_IDX)                    (TcpIp_DhcpV4Server_SocketId[(SERVER_INSTANCE_IDX)])
#define TcpIp_DhcpV4Server_VCfgGetServerConfigPtr(SERVER_INSTANCE_IDX)                   (TcpIp_DhcpV4Server_Socket2AddrAssignmentCfgsMap[(SERVER_INSTANCE_IDX)].ServerConfigPtr)
#define TcpIp_DhcpV4Server_VCfgGetAddrLeaseRecArray(SERVER_INSTANCE_IDX)                 (TcpIp_DhcpV4Server_Socket2AddrAssignmentCfgsMap[(SERVER_INSTANCE_IDX)].AddrLeaseRecsPtr)
#define TcpIp_DhcpV4Server_VCfgGetAddrLeaseRecPtr(SERVER_INSTANCE_IDX, ADDR_LEASE_IDX)   (&TcpIp_DhcpV4Server_Socket2AddrAssignmentCfgsMap[(SERVER_INSTANCE_IDX)].AddrLeaseRecsPtr[ADDR_LEASE_IDX])


/* PRQA L:FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct
{
  uint16                                                           TxData_Length;
  uint8                                                            TxData_ServerConfigIdx;
  uint8                                                            TxData_AddrAssignmentCfgIdx;
  uint8                                                            TxData_AddrLeaseRecIdx;
  uint8                                                            TxData_MsgType;
} TcpIp_DhcpV4Server_TxDataInfoType;

typedef struct
{
  TCPIP_DHCPV4SERVER_P2C(uint8) Text;
  uint8                         Length;
} TcpIp_DhcpV4Server_ErrorMsgType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* ==== VAR_ZERO_INIT_8BIT ==== */

#define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Initialization state of the module */
STATIC VAR(uint8, TCPIP_VAR_ZERO_INIT) TcpIp_DhcpV4Server_State = TCPIP_DHCPV4SERVER_STATE_UNINIT;

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ==== VAR_NOINIT_16BIT ==== */

#define TCPIP_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

STATIC VAR(uint16, TCPIP_VAR_NOINIT) TcpIp_DhcpV4Server_TimeMsec;

#define TCPIP_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ==== VAR_NOINIT_32BIT ==== */

#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

STATIC VAR(uint32, TCPIP_VAR_NOINIT) TcpIp_DhcpV4Server_TimeSec;

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ==== VAR_NOINIT_UNSPECIFIED ==== */

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

STATIC VAR(TcpIp_DhcpV4Server_TxDataInfoType, TCPIP_VAR_NOINIT) TcpIp_DhcpV4Server_TxDataInfo;

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ==== CONST_UNSPECIFIED ==== */

#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 0310 3 */ /* MD_TCPIP_Rule11.3_0310_Uint8ToStruct */
STATIC CONST(TcpIp_DhcpV4Server_ErrorMsgType, TCPIP_CONST) TcpIp_DhcpV4Server_ErrorMsgs[TCPIP_DHCPV4SERVER_ERROR_MESSAGE_COUNT] = { /* PRQA S 3218 */ /* MD_DHCPV4SERVER_Rule8.9_3218 */
  { (TCPIP_DHCPV4SERVER_P2C(uint8))"Client moved subnet.",          20 },
  { (TCPIP_DHCPV4SERVER_P2C(uint8))"Invalid IP address requested.", 29 },
};

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_ConfigureClient()
 *********************************************************************************************************************/
/*! \brief        Configures the dhcp client by parsing the message
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx   Server config index
 *  \param[in]    BufPtr                  Poniter to received data.
 *  \param[in]    Length                  Length of the received data in bytes.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_ConfigureClient(
  TcpIp_DhcpV4ServerConfigIterType            DhcpV4ServerConfigIdx,
  TCPIP_DHCPV4SERVER_P2V(uint8)               BufPtr,         /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  uint16                                      Length);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VInitAddrLeaseRec()
 *********************************************************************************************************************/
/*! \brief         Create an Address Lease Record.
 *  \details       This function verifys if the client id length is smaller than the configured space,
 *                 and accordingly stores the client id into the address lease records to create a new record.
 *  \param[in]     DhcpV4ServerConfigIdx DHCP Server Configuration Index.
 *  \param[in]     AddrLeaseRecIdx       IP address lease record index.
 *  \param[in]     ClientIdPtr           Client identifier (array of bytes).
 *  \param[in]     ClientIdLen           Length of the client identifier in bytes.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VInitAddrLeaseRec(
  TcpIp_DhcpV4ServerConfigIterType           DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)              ClientIdPtr,
  uint8                                      ClientIdLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetAddrAssignmentCfgIdxForMacAddr()
 *********************************************************************************************************************/
/*! \brief        Retrieves a suitable address assignment configuration based on the clients MAC address.
 *  \details      If no MAC address specific configuration is found this function returns a default configuration or
 *                no configuration if there is no default.
 *  \param[in]    DhcpV4ServerConfigIdx   DHCP Server Configuration Index.
 *  \param[in]    PhysAddrPtr             Physical (MAC) address of the client (6 byte).
 *  \return                               AddressAssignmentConfigIndex or TCPIP_DHCPV4SERVER_INV_ADDR_ASSIGN_IDX
 *                                        if no matching configuration was found.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetAddrAssignmentCfgIdxForMacAddr(
  TcpIp_DhcpV4ServerConfigIterType    DhcpV4ServerConfigIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)       PhysAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetServerConfigIdxForSocket()
 *********************************************************************************************************************/
/*! \brief         Retrieves the corresponding DHCP server instance for a UDP socket handle.
 *  \details       -
 *  \param[in]     SoHandle  Handle of the TcpIp (UDP) socket.
 *  \return                  Index of the DHCP server config or TCPIP_DHCPV4SERVER_INV_SERVER_CONF_IDX
 *                           if the socket does not belong to a DHCP server.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(TcpIp_DhcpV4ServerConfigIterType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetServerConfigIdxForSocket(TcpIp_SockHndType SoHandle);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VCopyAndPad()
 *********************************************************************************************************************/
/*! \brief        Copies bytes from source to destination.
 *  \details      If source is shorter that the destination, the destination will be filled up with zeroes.
 *  \param[in]    DstPtr    Destination buffer.
 *  \param[out]   DstLen    Length of destination in bytes (MUST at least be equal to srcLen).
 *  \param[in]    SrcPtr    Source buffer.
 *  \param[in]    SrcLen    Length of source in bytes.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VCopyAndPad(
  TCPIP_DHCPV4SERVER_P2V(uint8)  DstPtr,
  uint16                         DstLen,
  TCPIP_DHCPV4SERVER_P2C(uint8)  SrcPtr,
  uint16                         SrcLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VAddOptions()
 *********************************************************************************************************************/
/*! \brief        Adds DHCP options to a message based on the received client information and the message type.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx   DHCP Server Configuration Index.
 *  \param[out]   BufPtr                  DHCP message buffer. (May be NULL_PTR in order to perform a dry run that
 *                                        calculates the required buffer size)
 *  \param[in]    AddrLeaseRecIdx         Client address lease record.
 *  \param[in]    MsgType                 DHCP Message Type.
 *  \return                               Length of all added options in byte.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV4Server_VAddOptions(
  TcpIp_SizeOfDhcpV4ServerConfigType         DhcpV4ServerConfigIdx,
  TCPIP_DHCPV4SERVER_P2V(uint8)              BufPtr,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  uint8                                      MsgType);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetServerAddr()
 *********************************************************************************************************************/
/*! \brief        Returns the IP address of the specified DHCP server instance.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx   DHCP Server Config Index.
 *  \return                               IPv4 address of the DHCP server Config.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetServerAddr(
  TcpIp_DhcpV4ServerConfigIterType DhcpV4ServerConfigIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetClientAddr()
 *********************************************************************************************************************/
/*! \brief        Returns the IP address corresponding to the specified address lease record.
 *  \details      -
 *  \param[in]    DhcpV4ServerAddrAssignmentCfgIdx    Address assignment configuration Index.
 *  \param[in]    AddrLeaseRecIdx                     Client address lease record.
 *  \return                                           Client IPv4 address corresponding to the address lease record.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetClientAddr(
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  DhcpV4ServerAddrAssignmentCfgIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType            AddrLeaseRecIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VTxMessage()
 *********************************************************************************************************************/
/*! \brief        Transmits a DHCP message to the client.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx DHCP Server Configuration Index.
 *  \param[in]    AddrAssignmentCfgIdx  IP address assignment configuration.
 *  \param[in]    AddrLeaseRecIdx       Client address lease record.
 *  \param[in]    MsgType               DHCP Message Type.
 *  \return       E_OK                  Message successfully transmitted.
 *  \return       E_NOT_OK              Transmit failed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VTxMessage(
  TcpIp_SizeOfDhcpV4ServerConfigType                   DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  AddrAssignmentCfgIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType            AddrLeaseRecIdx,
  uint8                                                MsgType);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VSetupUdpSocket()
 *********************************************************************************************************************/
/*! \brief        Opens and binds a DHCPv4 server UDP socket to the specified IP address.
 *  \details      -
 *  \param[in]    BindLocalAddrId  Id of the local address the socket shall be bind to.
 *  \return                        TcpIp socket handle to the DHCP server socket.
 *  \return                        TCPIP_INV_SOCKET_ID if the socket could not be opened or bound.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(TcpIp_SocketIdType, TCPIP_CODE) TcpIp_DhcpV4Server_VSetupUdpSocket(
  TcpIp_LocalAddrIdType  BindLocalAddrId);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VInitSocketConfig
 *********************************************************************************************************************/
/*! \brief        Initializes all IP address assignment configurations for a socket (DHCP server instance).
 *  \details      Resets all address lease records of all address assignment configurations for the specified socket.
 *  \param[in]    DhcpV4ServerConfigIdx     DHCP Server configuration Index. (Not a socket handle).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VInitSocketConfig(
  TcpIp_DhcpV4ServerConfigIterType  DhcpV4ServerConfigIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VOpenSocket
 *********************************************************************************************************************/
/*! \brief        Opens the specified DHCP server UDP socket.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx   DHCP server configuration Index(Not a socket handle).
 *  \return       E_OK                    Socket successfully opened.
 *  \return       E_NOT_OK                Socket could not be opened.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VOpenSocket(
  TcpIp_DhcpV4ServerConfigIterType  DhcpV4ServerConfigIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VCloseSocket
 *********************************************************************************************************************/
/*! \brief        Closes the specified DHCP server UDP socket.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx   DHCP server configuration Index (Not a socket handle).
 *  \return       E_OK                    Socket closed.
 *  \return       E_NOT_OK                Socket could not be closed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VCloseSocket(
  TcpIp_DhcpV4ServerConfigIterType DhcpV4ServerConfigIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VUpdateLeaseTime
 *********************************************************************************************************************/
/*! \brief        Updates the lease time of an address lease record based on the requested lease time.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx     DHCP Server Configuration Index.
 *  \param[in]    AddrLeaseRecIdx           Address lease record.
 *  \param[in]    RequestedLeaseTime        Requested lease time in seconds (0 means default).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VUpdateLeaseTime(
  TcpIp_DhcpV4ServerConfigIterType           DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  uint32                                     RequestedLeaseTime);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VParseParamReqestListOption
 *********************************************************************************************************************/
/*! \brief        Parses a received 'Parameter Request List' option and returns a set of requested and supported options.
 *  \details      -
 *  \param[in]    MsgDataPtr        Received DHCP message.
 *  \param[in]    MsgDataOfs        Position of the 'Parameter Request List' option payload in received DHCP message (byte).
 *  \param[in]    OptLen            Length of parameter request list in bytes.
 *  \return                         Set (bit-field) of the requested and supported DHCP options.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4Server_VParseParamReqestListOption(
  TCPIP_DHCPV4SERVER_P2C(uint8)  MsgDataPtr,
  uint16                         MsgDataOfs,
  uint8                          OptLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VUpdateClientInfo
 *********************************************************************************************************************/
/*! \brief        Updates/stores client specific information in an address lease record.
 *  \details      -
 *  \param[in]    AddrLeaseRecIdx   IP address lease record Index.
 *  \param[in]    MsgDataPtr        Received DHCP message.
 *  \param[in]    MsgDataLen        Length of received DHCP message in bytes.
 *  \param[in]    KnownOptionsPtr   Value/Position of known options that are contained in the message.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VUpdateClientInfo(
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType                        AddrLeaseRecIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetAddrLeaseRecIdxByIpAddr
 *********************************************************************************************************************/
/*! \brief        Retrieves an address lease record based on the IP address of the client.
 *  \details      -
 *  \param[in]    DhcpV4ServerAddrAssignmentCfgIdx  IP address assignment configuration Index.
 *  \param[in]    ClientAddr                        IPv4 address of the client.
 *  \return                                         IP address lease record or TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX
 *                                                  if IP address does not belong to any record.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetAddrLeaseRecIdxByIpAddr(
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  DhcpV4ServerAddrAssignmentCfgIdx,
  IpBase_AddrInType                                    ClientAddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx
 *********************************************************************************************************************/
/*! \brief        Searches (and optionally creates) an address lease record using the client identifier.
 *  \details      If there exists no record for the client, the record belonging to the requested IP address will be
 *                provided if is is not already in use.
 *  \param[in]    DhcpV4ServerConfigIdx             DHCP Server Configuration Index.
 *  \param[in]    DhcpV4ServerAddrAssignmentCfgIdx  IP address assignment configuration.
 *  \param[in]    ClientIdPtr                       Client identifier.
 *  \param[in]    ClientIdLen                       Length of client identifier in bytes.
 *  \param[in]    ReqIpAddr                         Requested IPv4 address or 0 if no specific address is requested.
 *  \param[in]    CreateIfNotExist                  Specifies whether a free entry shall be returned and assigned to the client if possible.
 *  \return                                         Index of the IP address lease record or TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX
 *                                                  if no lease exists or could be assigned.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx(
  TcpIp_DhcpV4ServerConfigIterType                     DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                        ClientIdPtr,
  uint8                                                ClientIdLen,
  IpBase_AddrInType                                    ReqIpAddr,
  boolean                                              CreateIfNotExist);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VCmpClientId
 *********************************************************************************************************************/
/*! \brief        Checks if a client identifier is bound to a specific IP address lease record.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx DHCP Server Configuration Index.
 *  \param[in]    AddrLeaseRecIdx       IP address lease record.
 *  \param[in]    ClientIdPtr           Client identifier
 *  \param[in]    ClientIdLen           Length of the client identifier in bytes.
 *  \return       TRUE                  Client identifier belongs the the IP address lease record.
 *  \return       FALSE                 Client identifier does not belong the the IP address lease record.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4Server_VCmpClientId(
  TcpIp_DhcpV4ServerConfigIterType           DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)              ClientIdPtr,
  uint8                                      ClientIdLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VHandleDhcpDiscover
 *********************************************************************************************************************/
/*! \brief        Handles received DHCP DISCOVER message.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx             DHCP Server Configuration Index.
 *  \param[in]    DhcpV4ServerAddrAssignmentCfgIdx  IP address assignment configuration.
 *  \param[in]    MsgDataPtr                        Received DHCP message.
 *  \param[in]    MsgDataLen                        Length of received DHCP message in bytes.
 *  \param[in]    KnownOptionsPtr                   Value/Position of known options that are contained in the message.
 *  \pre          -
 *  \context      ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VHandleDhcpDiscover(
  TcpIp_DhcpV4ServerConfigIterType                                 DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType              DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VHandleDhcpRequest
 *********************************************************************************************************************/
/*! \brief        Handles received DHCP REQUEST message.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx             DHCP Server Configuration Index.
 *  \param[in]    DhcpV4ServerAddrAssignmentCfgIdx  IP address assignment configuration.
 *  \param[in]    MsgDataPtr                        Received DHCP message.
 *  \param[in]    MsgDataLen                        Length of received DHCP message in bytes.
 *  \param[in]    KnownOptionsPtr                   Value/Position of known options that are contained in the message.
 *  \pre          -
 *  \context      ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VHandleDhcpRequest(
  TcpIp_DhcpV4ServerConfigIterType                                 DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType              DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VHandleDhcpDeclineRelease
 *********************************************************************************************************************/
/*! \brief        Handles received DHCP DECLINE or RELEASE message.
 *  \details      -
 *  \param[in]    DhcpV4ServerConfigIdx             DHCP Server Configuration Index.
 *  \param[in]    DhcpV4ServerAddrAssignmentCfgIdx  IP address assignment configuration.
 *  \param[in]    MsgDataPtr                        Received DHCP message.
 *  \param[in]    MsgDataLen                        Length of received DHCP message in bytes.
 *  \param[in]    KnownOptionsPtr                   Value/Position of known options that are contained in the message.
 *  \pre          -
 *  \context      ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VHandleDhcpDeclineRelease(
  TcpIp_DhcpV4ServerConfigIterType                                 DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType              DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VInitKnownOptionsInfo
 *********************************************************************************************************************/
/*! \brief        Initializes a known DHCP options structure.
 *  \details      -
 *  \param[out]   KnownOptionsPtr       Structure containing values or position of known DHCP options.
 *  \pre          -
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VInitKnownOptionsInfo(
  TCPIP_DHCPV4SERVER_P2V(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VParseOptions
 *********************************************************************************************************************/
/*! \brief         Parses all DHCP options contained in a received message.
 *  \details       -
 *  \param[in]     MsgDataPtr       Received DHCP message.
 *  \param[in]     MsgDataOfs       Position of the first option in the message that shall be parsed.
 *  \param[in]     MsgDataLen       Length of the complete message in bytes.
 *  \param[in,out] KnownOptionsPtr  Structure containing values or position of known DHCP options.
 *  \pre          -
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VParseOptions(
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataOfs,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2V(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VInitAddrLeaseRec()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VInitAddrLeaseRec(
  TcpIp_DhcpV4ServerConfigIterType           DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)              ClientIdPtr,
  uint8                                      ClientIdLen)
{
  uint8  localClientIdLen = ClientIdLen;

  TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_INIT;
  if (ClientIdLen > TcpIp_GetMaxClientIdLenOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx))
  {
    /* The client identifier is longer than the configured storage space.
     * Identifier will be truncated. This is no problem if the truncated identifier is still unique
     * but it is highly recommended to configure more storage space for the client identifiers */
    localClientIdLen = TcpIp_GetMaxClientIdLenOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
    TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_GET_CLIENT_REC_IDX, TCPIP_DHCPV4SERVER_E_OUT_OF_MEMORY);
  }

  /* create new record */
  TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientIdLen = localClientIdLen;
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IpBase_Copy((IpBase_CopyDataType *)&TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientId[0],
        (const IpBase_CopyDataType *)ClientIdPtr, localClientIdLen);

} /* TcpIp_DhcpV4Server_VInitAddrLeaseRec() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VCmpClientId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4Server_VCmpClientId(
  TcpIp_DhcpV4ServerConfigIterType           DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)              ClientIdPtr,
  uint8                                      ClientIdLen)
{
  uint8   localClientIdLen = ClientIdLen;
  boolean result;

  if (ClientIdLen > TcpIp_GetMaxClientIdLenOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx))
  {
    /* The client identifier is longer than the configured storage space.
     * Identifier will be truncated. This is no problem if the truncated identifier is still unique
     * but it is highly recommended to configure more storage space for the client identifiers */
    localClientIdLen = TcpIp_GetMaxClientIdLenOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
    TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_GET_CLIENT_REC_IDX, TCPIP_DHCPV4SERVER_E_OUT_OF_MEMORY);
  }

  if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientIdLen == localClientIdLen)
  {
    uint8_least clientIdDataIdx;
    result = TRUE;

    for (clientIdDataIdx = 0; clientIdDataIdx < localClientIdLen; clientIdDataIdx++)
    {
      if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientId[clientIdDataIdx] != ClientIdPtr[clientIdDataIdx])
      {
        /* client identifier does not match */
        result = FALSE;
        break;
      }
    }
  }
  else
  {
    result = FALSE;
  }

  return result;
} /* TcpIp_DhcpV4Server_VCmpClientId() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx(
  TcpIp_DhcpV4ServerConfigIterType                     DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                        ClientIdPtr,
  uint8                                                ClientIdLen,
  IpBase_AddrInType                                    ReqIpAddr,
  boolean                                              CreateIfNotExist)
{
  TcpIp_DhcpV4ServerAddrLeaseRecsIterType addrLeaseRecIdxMatch  = TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX;
  TcpIp_DhcpV4ServerAddrLeaseRecsIterType addrLeaseRecIdxNew    = TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX;
  TcpIp_DhcpV4ServerAddrLeaseRecsIterType addrLeaseRecIdx;

  TCPIP_ASSERT_MSG(DhcpV4ServerAddrAssignmentCfgIdx < TcpIp_GetDhcpV4ServerAddressAssignmentConfigEndIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx), "addrAssignmentCfgIdx < TcpIp_GetDhcpV4ServerAddressAssignmentConfigEndIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx)");
  for (addrLeaseRecIdx = TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx);
       addrLeaseRecIdx < TcpIp_GetDhcpV4ServerAddrLeaseRecsEndIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx);
       addrLeaseRecIdx++)
  {
    if (TcpIp_DhcpV4Server_VCmpClientId(DhcpV4ServerConfigIdx, (TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType)addrLeaseRecIdx, ClientIdPtr, ClientIdLen) == TRUE)
    {
      /* Valid address lease record found. Stop searching. */
      addrLeaseRecIdxMatch = addrLeaseRecIdx;
      break;
    }
    /* Record oldest expired lease record. (will be required later if no matching lease is found) */
    if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState == TCPIP_DHCPV4SERVER_LEASE_STATE_EXPIRED)
    {
      if (   (addrLeaseRecIdxNew == TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX)  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseTimeSec
           < TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdxNew)->LeaseTimeSec))
      {
        addrLeaseRecIdxNew = addrLeaseRecIdx;
      }
    }
  }

  if (addrLeaseRecIdxMatch == TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX)
  {
    /* No matching address lease record found. */
    if (ReqIpAddr != 0u)
    {
      /* Client has explicitly requested an IP address. Check if requested IP address is available. */
      TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType addrLeaseRecIdxRequested = TcpIp_DhcpV4Server_VGetAddrLeaseRecIdxByIpAddr(DhcpV4ServerAddrAssignmentCfgIdx, ReqIpAddr);

      if (addrLeaseRecIdxRequested != TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX)
      {
        if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdxRequested)->LeaseState == TCPIP_DHCPV4SERVER_LEASE_STATE_EXPIRED)
        {
          /* Requested IP address is available. */
          addrLeaseRecIdxNew = addrLeaseRecIdxRequested;
        }
      }
    }

    if ((CreateIfNotExist == TRUE) && (addrLeaseRecIdxNew != TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX))  /* PRQA S 3415 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      /* Assign address lease received to client. */
      addrLeaseRecIdxMatch = addrLeaseRecIdxNew;
      TcpIp_DhcpV4Server_VInitAddrLeaseRec(DhcpV4ServerConfigIdx, (TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType)addrLeaseRecIdxMatch, ClientIdPtr, ClientIdLen);
    }
  }

  return (TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType)addrLeaseRecIdxMatch;
} /* TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetAddrAssignmentCfgIdxForMacAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetAddrAssignmentCfgIdxForMacAddr(
  TcpIp_DhcpV4ServerConfigIterType    DhcpV4ServerConfigIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)       PhysAddrPtr)
{
  /* Get switch port information and check if there is an address assignment configuration */
#if defined(TCPIP_DHCPV4SERVER_GET_PORT_MAC_ADDR_FUNC)
  uint8 ethIfSwitchIdx     = 0;
  uint8 ethIfSwitchPortIdx = 0;
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType dhcpV4ServerAddrAssignmentCfgIdxMatch = TCPIP_DHCPV4SERVER_INV_ADDR_ASSIGN_IDX;

  if (TCPIP_DHCPV4SERVER_GET_PORT_MAC_ADDR_FUNC(PhysAddrPtr, &ethIfSwitchIdx, &ethIfSwitchPortIdx) == E_OK)
  {
    /* Switch port information available for the clients MAC address */
    if (ethIfSwitchIdx == TcpIp_GetEthIfSwitchIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx))
    {
      TcpIp_DhcpV4ServerAddressAssignmentConfigIterType iterDhcpV4ServerAddrAssignmentCfgIdx;
      for (iterDhcpV4ServerAddrAssignmentCfgIdx = TcpIp_GetDhcpV4ServerAddressAssignmentConfigStartIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
           iterDhcpV4ServerAddrAssignmentCfgIdx < (TcpIp_GetDhcpV4ServerAddressAssignmentConfigEndIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx));
           iterDhcpV4ServerAddrAssignmentCfgIdx++)
      {
        if (ethIfSwitchPortIdx == TcpIp_GetEthSwitchPortIdxOfDhcpV4ServerAddressAssignmentConfig(iterDhcpV4ServerAddrAssignmentCfgIdx))
        {
          /* Found address assignment configuration */
          dhcpV4ServerAddrAssignmentCfgIdxMatch = (TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType)iterDhcpV4ServerAddrAssignmentCfgIdx;
        }
      }
    }
  }

  if (dhcpV4ServerAddrAssignmentCfgIdxMatch == TCPIP_DHCPV4SERVER_INV_ADDR_ASSIGN_IDX)
  {
    if (TcpIp_IsDhcpV4ServerAddressAssignmentConfigUsedOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx) == TRUE)
    {
      TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType dhcpV4ServerAddrAssignmentCfgIdx = TcpIp_GetDhcpV4ServerAddressAssignmentConfigStartIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
      /* no default address assignment configuration found.
      * Check if a default address assignment configuration exists (will always be at index 0)
      */
      if (TcpIp_GetEthSwitchPortIdxOfDhcpV4ServerAddressAssignmentConfig(dhcpV4ServerAddrAssignmentCfgIdx) == TCPIP_DHCPV4SERVER_ANY_SWITCH_OR_PORT_IDX)
      {
        /* there exists no switch independent address assignment configuration */
        dhcpV4ServerAddrAssignmentCfgIdxMatch = dhcpV4ServerAddrAssignmentCfgIdx;
      }
    }
  }

  return dhcpV4ServerAddrAssignmentCfgIdxMatch;
#else
  /* PRQA S 2983 2 */ /* MD_MSR_DummyStmt */
  TCPIP_DHCPV4SERVER_UNUSED_PARAMETER(DhcpV4ServerConfigIdx);
  TCPIP_DHCPV4SERVER_UNUSED_PARAMETER(PhysAddrPtr);
  /* return default address assignment configuration */
  return 0;
#endif
} /* TcpIp_DhcpV4Server_VGetAddrAssignmentCfgIdxForMacAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetServerConfigIdxForSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(TcpIp_DhcpV4ServerConfigIterType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetServerConfigIdxForSocket(TcpIp_SockHndType SoHandle)
{
  TcpIp_DhcpV4ServerConfigIterType serverConfigIdxSelected = TCPIP_DHCPV4SERVER_INV_SERVER_CONF_IDX;

  if (SoHandle != TCPIP_INV_SOCKET_ID)
  {
    TcpIp_DhcpV4ServerConfigIterType dhcpV4ServerConfigIdx;
    for(dhcpV4ServerConfigIdx = 0; dhcpV4ServerConfigIdx < TcpIp_GetSizeOfDhcpV4ServerConfig(); dhcpV4ServerConfigIdx++)
    {
      if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) == SoHandle)
      {
        serverConfigIdxSelected = dhcpV4ServerConfigIdx;
        break;
      }
    }
  }

  return serverConfigIdxSelected;
} /* TcpIp_DhcpV4Server_VGetServerConfigIdxForSocket() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VCopyAndPad()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VCopyAndPad(
  TCPIP_DHCPV4SERVER_P2V(uint8)  DstPtr,
  uint16                         DstLen,
  TCPIP_DHCPV4SERVER_P2C(uint8)  SrcPtr,
  uint16                         SrcLen)

{
  uint16_least bufPos;

  TCPIP_ASSERT(DstPtr != NULL_PTR);
  TCPIP_ASSERT((SrcPtr != NULL_PTR) || (SrcLen == 0u));
  TCPIP_ASSERT(DstLen >= SrcLen);

  if (SrcPtr != NULL_PTR)
  {
    for (bufPos = 0; bufPos < SrcLen; bufPos++)
    {
      DstPtr[bufPos] = SrcPtr[bufPos];
    }
  }

  for (bufPos = SrcLen; bufPos < DstLen; bufPos++)
  {
    DstPtr[bufPos] = 0;
  }

} /* TcpIp_DhcpV4Server_VCopyAndPad() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VAddOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV4Server_VAddOptions(
  TcpIp_SizeOfDhcpV4ServerConfigType         DhcpV4ServerConfigIdx,
  TCPIP_DHCPV4SERVER_P2V(uint8)              BufPtr,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  uint8                                      MsgType)
{
  uint16 dataLen = 0;

  /* [RFC2132 9.7. Server Identifier] */
  if (BufPtr != NULL_PTR)
  {
    IpBase_AddrInType serverAddr = TcpIp_DhcpV4Server_VGetServerAddr(DhcpV4ServerConfigIdx);

    BufPtr[dataLen] = TCPIP_DHCPV4SERVER_MSG_OPT_SERVER_ID;
    BufPtr[dataLen + 1u] = TCPIP_DHCPV4SERVER_MSG_OPT_SERVER_ID_LEN;

    TCPIP_PUT_UINT32(BufPtr, dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN, serverAddr);
  }
  dataLen += TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + TCPIP_DHCPV4SERVER_MSG_OPT_SERVER_ID_LEN;

  /* [RFC2132 9.14. Client-identifier] */
  if (BufPtr != NULL_PTR)
  {
    BufPtr[dataLen] = TCPIP_DHCPV4SERVER_MSG_OPT_CLIENT_ID;
    BufPtr[dataLen + 1u] = TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientIdLen;

    TcpIp_DhcpV4Server_VCopyAndPad(&BufPtr[dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN], TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientIdLen,
                                   &TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientId[0], TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientIdLen);
  }
  dataLen += TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + (uint16) TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientIdLen;

  /* [RFC2132 9.2. IP Address Lease Time] */
  if ((MsgType == TCPIP_DHCPV4SERVER_TX_MSG_DHCPOFFER) || (MsgType == TCPIP_DHCPV4SERVER_TX_MSG_DHCPACK))
  {
    if (BufPtr != NULL_PTR)
    {
      BufPtr[dataLen] = TCPIP_DHCPV4SERVER_MSG_OPT_IP_ADDR_LEASE_TIME;
      BufPtr[dataLen + 1u] = TCPIP_DHCPV4SERVER_MSG_OPT_IP_ADDR_LEASE_TIME_LEN;

      if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->LeaseTimeSec < TCPIP_DHCPV4SERVER_TIME_INFINITE)
      {
        uint32 LeaseTimeRemainSec = TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->LeaseTimeSec - TcpIp_DhcpV4Server_TimeSec;
        TCPIP_PUT_UINT32(BufPtr, dataLen+TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN, LeaseTimeRemainSec);
      }
      else
      {
        /* Write infinite time value */
        BufPtr[dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN] = 0xFF;
        BufPtr[dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + 1u] = 0xFF;
        BufPtr[dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + 2u] = 0xFF;
        BufPtr[dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + 3u] = 0xFF;
      }
    }
    dataLen += TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + TCPIP_DHCPV4SERVER_MSG_OPT_IP_ADDR_LEASE_TIME_LEN;
  }

  /* "If both the subnet mask and the router option are specified in a DHCP reply,
   *  the subnet mask option MUST be first." [RFC2132 3.3. Subnet Mask]
   */

  /* [RFC2132 3.3. Subnet Mask] */
  if (   (TCPIP_DHCPV4SERVER_TX_MSG_DHCPOFFER == MsgType)  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TCPIP_DHCPV4SERVER_TX_MSG_DHCPACK   == MsgType)
      || ((TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientParamReqSet & TCPIP_DHCPV4SERVER_MSG_OPT_REQ_FLAG_SUBNET_MASK) != 0u))
  {
    if (TcpIp_GetAddrPrefixLengthOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx) != 0u)
    {
      if (BufPtr != NULL_PTR)
      {
        uint32 SubnetMask = (0xFFFFFFFFU << (32U-TcpIp_GetAddrPrefixLengthOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx)));

        BufPtr[dataLen] = TCPIP_DHCPV4SERVER_MSG_OPT_SUBNET_MASK;
        BufPtr[dataLen + 1u] = TCPIP_DHCPV4SERVER_MSG_OPT_SUBNET_MASK_LEN;
        TCPIP_PUT_UINT32(BufPtr, dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN, SubnetMask);
      }
      dataLen += TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + TCPIP_DHCPV4SERVER_MSG_OPT_SUBNET_MASK_LEN;
    }
  }

  /* [RFC2132 3.5. Router Option] */
  if ((TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientParamReqSet & TCPIP_DHCPV4SERVER_MSG_OPT_REQ_FLAG_ROUTER) != 0u)
  {
    if (TcpIp_GetDefaultRouterAddrOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx) != 0u)
    {
      if (NULL_PTR != BufPtr)
      {
        BufPtr[dataLen] = TCPIP_DHCPV4SERVER_MSG_OPT_ROUTER;
        BufPtr[dataLen + 1u] = TCPIP_DHCPV4SERVER_MSG_OPT_ROUTER_LEN;
        TCPIP_PUT_UINT32(BufPtr, dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN, TcpIp_GetDefaultRouterAddrOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx));
      }
      dataLen += TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + 4u;
    }
  }

  /* [RFC2132 9.9. Message] */
  TCPIP_ASSERT(TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ErrorMsgId <= TCPIP_DHCPV4SERVER_ERROR_MESSAGE_COUNT);

  if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ErrorMsgId > 0u)
  {
    uint8_least msgIdx    = (uint8_least)TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ErrorMsgId - (uint8_least)1;
    uint8       msgLength = TcpIp_DhcpV4Server_ErrorMsgs[msgIdx].Length;

    TCPIP_ASSERT(MsgType == TCPIP_DHCPV4SERVER_TX_MSG_DHCPNAK); /* Error messages shall only be sent in NAK messages. */

    if (NULL_PTR != BufPtr)
    {
      BufPtr[dataLen] = TCPIP_DHCPV4SERVER_MSG_OPT_MESSAGE;
      BufPtr[dataLen + 1u] = msgLength;
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(&BufPtr[dataLen + TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN], &TcpIp_DhcpV4Server_ErrorMsgs[msgIdx].Text[0], msgLength);

      TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ErrorMsgId = TCPIP_DHCPV4SERVER_ERROR_MESSAGE_NONE;
    }

    dataLen += TCPIP_DHCPV4SERVER_MSG_OPT_HDR_LEN + (uint16) msgLength;
  }

  return dataLen;
} /* TcpIp_DhcpV4Server_VAddOptions() */ /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetServerAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetServerAddr(
  TcpIp_DhcpV4ServerConfigIterType  DhcpV4ServerConfigIdx)
{
  IpBase_SockAddrInType ServerSockAddrIn;
  (void)TcpIp_GetIpAddr(TcpIp_GetLocalAddrV4IdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx), (TcpIp_SockAddrType*)&ServerSockAddrIn, NULL_PTR, NULL_PTR); /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */

  return TCPIP_HTONL(ServerSockAddrIn.sin_addr);
} /* TcpIp_DhcpV4Server_VGetServerAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetClientAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetClientAddr(
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  DhcpV4ServerAddrAssignmentCfgIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType            AddrLeaseRecIdx)
{
  uint8 dhcpAddrIdx;
  TCPIP_ASSERT(AddrLeaseRecIdx >= TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx));
  TCPIP_ASSERT(AddrLeaseRecIdx < TcpIp_GetDhcpV4ServerAddrLeaseRecsEndIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx));

  dhcpAddrIdx = (uint8)(AddrLeaseRecIdx - TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx));

  return (TcpIp_GetDhcpAddrFirstOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx) + dhcpAddrIdx);
} /* TcpIp_DhcpV4Server_VGetClientAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VGetAddrLeaseRecIdxByIpAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType, TCPIP_CODE) TcpIp_DhcpV4Server_VGetAddrLeaseRecIdxByIpAddr(
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  DhcpV4ServerAddrAssignmentCfgIdx,
  IpBase_AddrInType                                    ClientAddr)
{
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType addrLeaseRecIdx;

  if (   (ClientAddr >= TcpIp_GetDhcpAddrFirstOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx))  /* PRQA S 3415 4 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (ClientAddr < ((uint32) TcpIp_GetDhcpAddrFirstOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx)
                        + ((uint32) TcpIp_GetDhcpV4ServerAddrLeaseRecsEndIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx)
                        - (uint32) TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx) ))))
  {
    uint8 dhcpAddrIdx = (uint8)(ClientAddr - TcpIp_GetDhcpAddrFirstOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx));

    TCPIP_ASSERT(dhcpAddrIdx < (  TcpIp_GetDhcpV4ServerAddrLeaseRecsEndIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx)
                                - TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx)));

    addrLeaseRecIdx = (TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType)(TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(DhcpV4ServerAddrAssignmentCfgIdx) + dhcpAddrIdx);
  }
  else
  {
    /* ClientAddr is not in the IP address range of the given address assignment configuration. */
    addrLeaseRecIdx = TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX;
  }

  return addrLeaseRecIdx;
} /* TcpIp_DhcpV4Server_VGetAddrLeaseRecIdxByIpAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VTxMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VTxMessage(
  TcpIp_SizeOfDhcpV4ServerConfigType                   DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType  AddrAssignmentCfgIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType            AddrLeaseRecIdx,
  uint8                                                MsgType)
{
  uint16                  msgLen = TCPIP_DHCPV4SERVER_MIN_MSG_LEN;
  TcpIp_SockAddrInetType  destSockAddr;
  Std_ReturnType          retVal = E_OK;

  destSockAddr.domain = TCPIP_AF_INET;

  /* Set destination IP address and UDP port of the message based on previously received message from the client. */

  if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientGiAddr == 0u)
  {
    if (   ((TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientFlags & TCPIP_DHCPV4SERVER_MSG_FLAG_BROADCAST) != 0u)
        || (MsgType == TCPIP_DHCPV4SERVER_TX_MSG_DHCPNAK))
    {
      destSockAddr.addr[0] = 0xFFFFFFFFU;
    }
    else
    {
      IpBase_AddrInType clientAddr = TcpIp_DhcpV4Server_VGetClientAddr(AddrAssignmentCfgIdx, AddrLeaseRecIdx);
      destSockAddr.addr[0] = TCPIP_HTONL(clientAddr);

      /* Override physical destination address */

      if (TcpIp_ChangeParameter( TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx),
                                  TCPIP_PARAMID_V_PHYS_DEST_ADDR,
                                  &TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientChAddr[0] )
          != E_OK)
      {
        TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_TX_MESSAGE, TCPIP_DHCPV4SERVER_E_INTERNAL_ERROR);
      }
    }

    destSockAddr.port = TCPIP_HTONS(TCPIP_DHCPV4SERVER_CLIENT_PORT);
  }
  else
  {
    /* "If the 'giaddr' field in a DHCP message from a client is non-zero,
     *  the server sends any return messages to the 'DHCP server' port on the
     *  BOOTP relay agent whose address appears in 'giaddr'."
     *  [IETF RFC 2131 4.1 Constructing and sending DHCP messages (p. 23)]
     */
    destSockAddr.addr[0] = TCPIP_HTONL(TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientGiAddr);
    destSockAddr.port = TCPIP_HTONS(TCPIP_DHCPV4SERVER_SERVER_PORT);
  }

  /* Calculate Message Length. */

  msgLen += TcpIp_DhcpV4Server_VAddOptions(DhcpV4ServerConfigIdx, NULL_PTR, AddrLeaseRecIdx, MsgType);

  /* Prepare for indirect data provision via CopyTxData. */

  TcpIp_DhcpV4Server_TxDataInfo.TxData_ServerConfigIdx      = DhcpV4ServerConfigIdx;
  TcpIp_DhcpV4Server_TxDataInfo.TxData_MsgType              = MsgType;
  TcpIp_DhcpV4Server_TxDataInfo.TxData_Length               = msgLen;
  TcpIp_DhcpV4Server_TxDataInfo.TxData_AddrAssignmentCfgIdx = AddrAssignmentCfgIdx;
  TcpIp_DhcpV4Server_TxDataInfo.TxData_AddrLeaseRecIdx      = AddrLeaseRecIdx;

  /* Call TcpIp_UdpTransmit(). */

  if (TcpIp_UdpTransmit( TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx),
                         NULL_PTR,
                         (TCPIP_DHCPV4SERVER_P2V(TcpIp_SockAddrType))&destSockAddr,  /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */
                         msgLen )
      != TCPIP_OK)
  {
    /* Transmit failed. */
    retVal = E_NOT_OK;
  }

  /* Unset physical destination address in IP. */

  if (TcpIp_ChangeParameter(TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx), TCPIP_PARAMID_V_PHYS_DEST_ADDR, NULL_PTR) != E_OK)
  {
    TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_TX_MESSAGE, TCPIP_DHCPV4SERVER_E_INTERNAL_ERROR);
  }

  TcpIp_DhcpV4Server_TxDataInfo.TxData_Length               = 0; /* No TcpIp_UdpTransmit() pending */

  return retVal;
} /* TcpIp_DhcpV4Server_VTxMessage() */  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_InitMemory(void)
{
    TcpIp_DhcpV4Server_State = TCPIP_DHCPV4SERVER_STATE_UNINIT;

} /* TcpIp_DhcpV4Server_InitMemory() */


/**********************************************************************************************************************
 * TcpIp_DhcpV4Server_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_Init(void)   /* PRQA S 2889 */ /* MD_DHCPV4SERVER_Rule15.5_2889 */
{
  TcpIp_DhcpV4ServerConfigIterType dhcpV4ServerConfigIdx;

  /* ----- Development Error Checks ------------------------------------- */
  TcpIp_DhcpV4Server_CheckDetErrorReturnVoid(TcpIp_DhcpV4Server_State == TCPIP_DHCPV4SERVER_STATE_UNINIT,
                                             TCPIP_DHCPV4SERVER_SID_INIT,
                                             TCPIP_DHCPV4SERVER_E_ALREADY_INITIALIZED);
  /* ----- */

  for (dhcpV4ServerConfigIdx = 0; dhcpV4ServerConfigIdx <  TcpIp_GetSizeOfDhcpV4ServerConfig(); dhcpV4ServerConfigIdx++)
  {
    TcpIp_DhcpV4Server_VInitSocketConfig((uint8)dhcpV4ServerConfigIdx);
    TcpIp_SetIpAddrAssignmentStateOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx, TCPIP_IPADDR_STATE_UNASSIGNED);
  }

  TcpIp_DhcpV4Server_TimeSec  = 0;
  TcpIp_DhcpV4Server_TimeMsec = 0;

  TcpIp_DhcpV4Server_TxDataInfo.TxData_Length = 0; /* No TcpIp_UdpTransmit() pending */

  TcpIp_DhcpV4Server_State = TCPIP_DHCPV4SERVER_STATE_INIT;

} /* TcpIp_DhcpV4Server_Init() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_GetVersionInfo(  /* PRQA S 2889 */ /* MD_DHCPV4SERVER_Rule15.5_2889 */
  P2VAR(Std_VersionInfoType, AUTOMATIC, TCPIP_APPL_DATA)  VersionInfoPtr)
{
  /* ----- Development Error Checks ------------------------------------- */
  TcpIp_DhcpV4Server_CheckDetErrorReturnVoid(NULL_PTR != VersionInfoPtr,
                                             TCPIP_DHCPV4SERVER_SID_GET_VERSION_INFO,
                                             TCPIP_DHCPV4SERVER_E_INV_PTR);
  /* ----- */

  VersionInfoPtr->vendorID         = TCPIP_DHCPV4SERVER_VENDOR_ID;
  VersionInfoPtr->moduleID         = TCPIP_DHCPV4SERVER_MODULE_ID;
  VersionInfoPtr->sw_major_version = TCPIP_SW_MAJOR_VERSION;
  VersionInfoPtr->sw_minor_version = TCPIP_SW_MINOR_VERSION;
  VersionInfoPtr->sw_patch_version = TCPIP_SW_PATCH_VERSION;

} /* TcpIp_DhcpV4Server_GetVersionInfo() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_LocalIpAddrAssignmentChg(
  TcpIp_LocalAddrIdType  LocalAddrId,
  TcpIp_IpAddrStateType  State)
{
  TcpIp_DhcpV4ServerConfigIterType dhcpV4ServerConfigIdx;

  /* Locate DHCP server instance that uses the LocalAddrId. */

  for (dhcpV4ServerConfigIdx = 0; dhcpV4ServerConfigIdx <  TcpIp_GetSizeOfDhcpV4ServerConfig(); dhcpV4ServerConfigIdx++)
  {
    if (LocalAddrId == TcpIp_GetLocalAddrV4IdxOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx))
    {
      TCPIP_ASSERT(TcpIp_GetIpAddrAssignmentStateOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) != State);

      TcpIp_SetIpAddrAssignmentStateOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx, State);

      /* Open/close DHCP server UDP socket based on the new state of the IP address. */

      if (State == TCPIP_IPADDR_STATE_ASSIGNED)
      {
        (void)TcpIp_DhcpV4Server_VOpenSocket((uint8)dhcpV4ServerConfigIdx);
      }
      else
      {
        if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) != TCPIP_INV_SOCKET_ID)
        {
          (void)TcpIp_DhcpV4Server_VCloseSocket((uint8)dhcpV4ServerConfigIdx);
        }
      }

      break; /* max one socket for each LocalAddrId */
    }
  }
} /* TcpIp_DhcpV4Server_LocalIpAddrAssignmentChg() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_CopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_CopyTxData(
  TcpIp_SocketIdType             SocketId,
  TCPIP_DHCPV4SERVER_P2V(uint8)  BufPtr,
  uint16                         BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = TCPIP_E_NO_ERROR;
  BufReq_ReturnType retVal  = BUFREQ_E_NOT_OK;
  TcpIp_DhcpV4ServerConfigDynIterType dhcpV4ServerConfigIdx = TcpIp_DhcpV4Server_TxDataInfo.TxData_ServerConfigIdx;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  if (BufPtr == NULL_PTR)
  {
    errorId = TCPIP_DHCPV4SERVER_E_INV_PTR;
  }
  else if (   (TcpIp_DhcpV4Server_TxDataInfo.TxData_Length == 0u)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
           || (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) != SocketId))
  {
    /* unexpected call of CopyTxData. No transmit requested for this socket id. */
    errorId = TCPIP_DHCPV4SERVER_E_INV_PARAM;
  }
  else if (BufLength != TcpIp_DhcpV4Server_TxDataInfo.TxData_Length)
  {
    /* TcpIp must call CopyTxData only once during TcpIp_UdpTransmit(). Value of parameter Length must match value of parameter Length supplied in TcpIp_UdpTransmit(). */
    errorId = TCPIP_DHCPV4SERVER_E_OUT_OF_MEMORY;
  }
  else
#else
  TCPIP_UNUSED_PARAMETER(SocketId);
#endif
  {
    /* ----- Implementation ---------------------------------------------- */
    TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType addrLeaseRecIdx                              =  TcpIp_DhcpV4Server_TxDataInfo.TxData_AddrLeaseRecIdx;
    TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType dhcpV4ServeraddrAssignmentCfgIdx   =  TcpIp_DhcpV4Server_TxDataInfo.TxData_AddrAssignmentCfgIdx;
    uint8                               msgType                                            =  TcpIp_DhcpV4Server_TxDataInfo.TxData_MsgType;
    IpBase_AddrInType                   clientAddr                                         =  TcpIp_DhcpV4Server_VGetClientAddr(dhcpV4ServeraddrAssignmentCfgIdx, addrLeaseRecIdx);
    uint16 dhcpHostNameLen;
    dhcpHostNameLen = ( (uint16) TcpIp_GetDhcpV4ServerHostnameEndIdxOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx)
                       - (uint16) TcpIp_GetDhcpV4ServerHostnameStartIdxOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx) );
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_OP]     = TCPIP_DHCPV4SERVER_MSG_OP_BOOTREPLY;
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_HTYPE]  = TCPIP_DHCPV4SERVER_MSG_HTYPE_10MBIT_ETH;
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_HLEN]   = TCPIP_DHCPV4SERVER_MSG_HLEN_10MBIT_ETH;
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_HOPS]   = TCPIP_DHCPV4SERVER_MSG_HOPS;

    TCPIP_PUT_UINT32(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_XID, TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientXid);
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_SECS] = 0u;
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_SECS + 1u] = 0u;

    /* Set broadcast flag if NAK shall be sent as broadcast. */
    if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState == TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK_BROADCAST)
    {
      TCPIP_PUT_UINT16(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_FLAGS, (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientFlags | TCPIP_DHCPV4SERVER_MSG_FLAG_BROADCAST));
    }
    else
    {
      TCPIP_PUT_UINT16(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_FLAGS, (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientFlags));
    }

    /* Set address fields depending on message type. */
    {
      IpBase_AddrInType ciAddr = 0;                             /* "Client IP address; only filled in if client is in BOUND, RENEW or REBINDING state and can respond to ARP requests." */
      IpBase_AddrInType yiAddr = 0;                             /* "'your' (client) IP address." */
      IpBase_AddrInType siAddr = 0;                             /* "IP address of next server to use in bootstrap; returned in DHCPOFFER, DHCPACK by server." */
      IpBase_AddrInType giAddr = TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientGiAddr; /* "Relay agent IP address, used in booting via a relay agent." */

      switch (msgType)
      {
       case TCPIP_DHCPV4SERVER_TX_MSG_DHCPOFFER:
        yiAddr = clientAddr;
        break;

      case TCPIP_DHCPV4SERVER_TX_MSG_DHCPACK:
        yiAddr = clientAddr;
        break;

      default:
        /* Nothing to set. */
        break;
      }

      TCPIP_PUT_UINT32(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_CIADDR, ciAddr);
      TCPIP_PUT_UINT32(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_YIADDR, yiAddr);
      TCPIP_PUT_UINT32(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_SIADDR, siAddr);
      TCPIP_PUT_UINT32(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_GIADDR, giAddr);
    }

    /* Write client hardware address to 16 byte 'chaddr' field and pad with zeroes */
    TcpIp_DhcpV4Server_VCopyAndPad( &BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_CHADDR], TCPIP_DHCPV4SERVER_MSG_LEN_CHADDR,
                                    &TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientChAddr[0], TCPIP_DHCPV4SERVER_MSG_HLEN_10MBIT_ETH );

    if (   ((msgType == TCPIP_DHCPV4SERVER_TX_MSG_DHCPOFFER ) /* PRQA S 3415 3 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
        ||  (msgType == TCPIP_DHCPV4SERVER_TX_MSG_DHCPACK))
        && (TcpIp_IsDhcpV4ServerHostnameUsedOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx) == TRUE))
    {
      TcpIp_SizeOfDhcpV4ServerHostnameType hostNameIdx = TcpIp_GetDhcpV4ServerHostnameStartIdxOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx);
      /* Write server host name to 64 byte 'sname' field and pad with zeroes */
      TcpIp_DhcpV4Server_VCopyAndPad( &BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_SNAME],
                                     TCPIP_DHCPV4SERVER_MSG_LEN_SNAME,
                                     TcpIp_GetAddrDhcpV4ServerHostname(hostNameIdx),
                                     dhcpHostNameLen );
    }
    else
    {
      /* Clear (zero fill) 'sname' and 'file' fields since they are only used in OFFER and ACK */
      TcpIp_DhcpV4Server_VCopyAndPad(&BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_SNAME], TCPIP_DHCPV4SERVER_MSG_LEN_SNAME, NULL_PTR, 0u);
    }

    TcpIp_DhcpV4Server_VCopyAndPad(&BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_BOOTFILE], TCPIP_DHCPV4SERVER_MSG_LEN_BOOTFILE, NULL_PTR, 0u);

    /* Write DHCP magic cookie */
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_MAGIC_COOKIE] = (uint8)((TCPIP_DHCPV4SERVER_MSG_MAGIC_COOKIE & 0xFF000000u) >> 24u);
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_MAGIC_COOKIE + 1u] = (uint8)((TCPIP_DHCPV4SERVER_MSG_MAGIC_COOKIE & 0x00FF0000u) >> 16u);
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_MAGIC_COOKIE + 2u] = (uint8)((TCPIP_DHCPV4SERVER_MSG_MAGIC_COOKIE & 0x0000FF00u) >> 8u);
    BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_MAGIC_COOKIE + 3u] = (uint8)((TCPIP_DHCPV4SERVER_MSG_MAGIC_COOKIE & 0x000000FFu) >> 0u);

    /* Add Options */
    {
      uint16 payloadOfs = TCPIP_DHCPV4SERVER_MSG_OFS_OPTIONS;

      /* [RFC2132 9.6. DHCP Message Type] */
      BufPtr[payloadOfs] = TCPIP_DHCPV4SERVER_MSG_OPT_DHCP_MSG_TYPE;
      payloadOfs++;
      BufPtr[payloadOfs] = TCPIP_DHCPV4SERVER_MSG_OPT_DHCP_MSG_TYPE_LEN;
      payloadOfs++;
      BufPtr[payloadOfs] = msgType;
      payloadOfs++;

      payloadOfs += TcpIp_DhcpV4Server_VAddOptions(TcpIp_DhcpV4Server_TxDataInfo.TxData_ServerConfigIdx, &BufPtr[payloadOfs], addrLeaseRecIdx, msgType);

      /* [RFC2132 3.2. End Option] */
      BufPtr[payloadOfs] = TCPIP_DHCPV4SERVER_MSG_OPT_END;
      payloadOfs++;

#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
      if (payloadOfs != BufLength)
      {
        TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_TX_MESSAGE, TCPIP_DHCPV4SERVER_E_INV_MSG_LEN);
      }
#else
      TCPIP_UNUSED_PARAMETER(BufLength);
#endif
    }

    retVal = BUFREQ_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_DHCPV4SERVER_MODULE_ID, TCPIP_DHCPV4SERVER_INSTANCE_ID_DET, TCPIP_DHCPV4SERVER_SID_TX_MESSAGE, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_DhcpV4Server_CopyTxData() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VHandleDhcpDiscover()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VHandleDhcpDiscover(
  TcpIp_DhcpV4ServerConfigIterType                                 DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType              DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr)
{
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType addrLeaseRecIdx = TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx( DhcpV4ServerConfigIdx,
                                                                                                      DhcpV4ServerAddrAssignmentCfgIdx,
                                                                                                      &MsgDataPtr[KnownOptionsPtr->ClientId.OptOfs],
                                                                                                      KnownOptionsPtr->ClientId.OptLen,
                                                                                                      KnownOptionsPtr->ReqIpAddr,
                                                                                                      TRUE );

  if (addrLeaseRecIdx != TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX)
  {
    TcpIp_DhcpV4Server_VUpdateClientInfo(addrLeaseRecIdx, MsgDataPtr, MsgDataLen, KnownOptionsPtr);
    TcpIp_DhcpV4Server_VUpdateLeaseTime(DhcpV4ServerConfigIdx, addrLeaseRecIdx, KnownOptionsPtr->LeaseTime);

    TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_OFFER;
  }
} /* TcpIp_DhcpV4Server_VHandleDhcpDiscover() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VHandleDhcpRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VHandleDhcpRequest(
  TcpIp_DhcpV4ServerConfigIterType                                 DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType              DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr)
{
  /* Get address lease record for the client. */
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType addrLeaseRecIdx = TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx( DhcpV4ServerConfigIdx,
                                                                                                      DhcpV4ServerAddrAssignmentCfgIdx,
                                                                                                      &MsgDataPtr[KnownOptionsPtr->ClientId.OptOfs],
                                                                                                      KnownOptionsPtr->ClientId.OptLen,
                                                                                                      0,
                                                                                                      FALSE );

  if (addrLeaseRecIdx == TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX)
  {
    /* No address lease record for this client.
      * -> Ignore message.
      */
  }
  else
  {
    IpBase_AddrInType  clientIpAddr    = TcpIp_DhcpV4Server_VGetClientAddr(DhcpV4ServerAddrAssignmentCfgIdx, addrLeaseRecIdx);
    IpBase_AddrInType  msgGiAddr;
    boolean            clientMovedToOtherSubnet;

    /* If value of 'giaddr' differs from the previous received value, the client has moved to another subnet. */
    IPBASE_GET_UINT32(MsgDataPtr, TCPIP_DHCPV4SERVER_MSG_OFS_GIADDR, msgGiAddr);
    clientMovedToOtherSubnet = (boolean)(TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientGiAddr != msgGiAddr);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

    /* Determine state of the client. */
    if (KnownOptionsPtr->ServerId != 0u)
    {
      /* "If the DHCPREQUEST message contains a 'server identifier' option,
        *  the message is in response to a DHCPOFFER message."
        *   -> Client is in SELECTING state.
        */
      IpBase_AddrInType thisServerAddr = TcpIp_DhcpV4Server_VGetServerAddr(DhcpV4ServerConfigIdx);

      if (KnownOptionsPtr->ServerId != thisServerAddr)
      {
        /* Message addressed to different server.
         * -> Ignore message.
         */
      }
      else if (KnownOptionsPtr->ReqIpAddr == 0u)
      {
        /* Requested IP address MUST be specified by client in SELECTING state.
         * -> Ignore message.
         */
      }
      else
      {
        /* Store client information from the message for later usage. */
        TcpIp_DhcpV4Server_VUpdateClientInfo(addrLeaseRecIdx, MsgDataPtr, MsgDataLen, KnownOptionsPtr);

        /* If value of 'giaddr' differs from the previous received value, the client has moved to another subnet. */
        if (clientMovedToOtherSubnet == TRUE)
        {
          /* Client has moved to new subnet.
            * -> Tx NAK.
            */
          TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ErrorMsgId = TCPIP_DHCPV4SERVER_ERROR_MESSAGE_CLIENT_MOVED_SUBNET;
          TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK;
        }
        else if (KnownOptionsPtr->ReqIpAddr != clientIpAddr)
        {
          /* Requested IP address does not match currently assigned IP address.
            * -> Tx NAK.
            */
          TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ErrorMsgId = TCPIP_DHCPV4SERVER_ERROR_MESSAGE_INVALID_IP_ADDRESS_REQUESTED;
          TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK;
        }
        else
        {
          /* Update lease time and tx ACK. */
          TcpIp_DhcpV4Server_VUpdateLeaseTime(DhcpV4ServerConfigIdx, addrLeaseRecIdx, KnownOptionsPtr->LeaseTime);
          TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_ACK;
        }
      }
    }
    else
    {
      /* 'Server Identifier' is not set in REQUEST message.
       * -> Client is in INIT-REBOOT, RENEWING or REBINDING state.
       */
      if (KnownOptionsPtr->ReqIpAddr != 0u)
      {
        /* REQUEST message contains 'Requested IP Address' Option.
         * -> client is in INIT-REBOOT state.
         */

        TcpIp_DhcpV4Server_VUpdateClientInfo(addrLeaseRecIdx, MsgDataPtr, MsgDataLen, KnownOptionsPtr);

        if ((KnownOptionsPtr->ReqIpAddr != clientIpAddr) || (clientMovedToOtherSubnet == TRUE))
        {
          /* "Server SHOULD send a DHCPNAK message to the client if the 'requested IP address'
            *  is incorrect, or is on the wrong network."
            */
          TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ErrorMsgId = TCPIP_DHCPV4SERVER_ERROR_MESSAGE_INVALID_IP_ADDRESS_REQUESTED;

          if (msgGiAddr == 0u)
          {
            TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK;
          }
          else
          {
            /* "If 'giaddr' is set in the DHCPREQUEST message, the client is on a
              *  different subnet.  The server MUST set the broadcast bit in the
              *  DHCPNAK, so that the relay agent will broadcast the DHCPNAK to the
              *  client, because the client may not have a correct network address
              *  or subnet mask, and the client may not be answering ARP requests."
              *  [RFC2131 4.3.2 DHCPREQUEST message]
              */
            TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK_BROADCAST;
          }
        }
        else
        {
          /* Update IP address lease time and tx ACK. */
          TcpIp_DhcpV4Server_VUpdateLeaseTime(DhcpV4ServerConfigIdx, addrLeaseRecIdx, KnownOptionsPtr->LeaseTime);
          TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_ACK;
        }
      }
      else
      {
        /* REQUEST message does not contain 'Server Identifier' and 'Requested IP Address' Option but 'ciaddr' field is set.
         * -> Client is in RENEWING (unicast) or REBINDING (broadcast) state.
         */

        IpBase_AddrInType msgCiAddr;

        IPBASE_GET_UINT32(MsgDataPtr, TCPIP_DHCPV4SERVER_MSG_OFS_CIADDR, msgCiAddr); /* ciaddr        4  Client IP address; only filled in if client is in BOUND, RENEW or REBINDING state and can respond to ARP requests. */

        if (msgCiAddr == 0u)
        {
          /* Invalid request message.
            * -> Ignore message.
            */
        }
        else
        {
          TcpIp_DhcpV4Server_VUpdateClientInfo(addrLeaseRecIdx, MsgDataPtr, MsgDataLen, KnownOptionsPtr);

          if (msgCiAddr != clientIpAddr)
          {
            /* IP address of the client does not match assigned Ip address.
              * -> Ignore message.
              */
          }
          else if (clientMovedToOtherSubnet == TRUE)
          {
            /* Client has moved to new subnet.
              * -> Tx NAK.
              */
            TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ErrorMsgId = TCPIP_DHCPV4SERVER_ERROR_MESSAGE_CLIENT_MOVED_SUBNET;
            TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK;
          }
          else
          {
            /* Update IP address lease time and tx ACK. */
            TcpIp_DhcpV4Server_VUpdateLeaseTime(DhcpV4ServerConfigIdx, addrLeaseRecIdx, KnownOptionsPtr->LeaseTime);
            TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState = TCPIP_DHCPV4SERVER_LEASE_STATE_TX_ACK;
          }
        }
      }
    }
  }
} /* TcpIp_DhcpV4Server_VHandleDhcpRequest() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VHandleDhcpDeclineRelease()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VHandleDhcpDeclineRelease(
  TcpIp_DhcpV4ServerConfigIterType                                 DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType              DhcpV4ServerAddrAssignmentCfgIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr)
{
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType addrLeaseRecIdx;

  TCPIP_ASSERT((KnownOptionsPtr->ClientId.OptOfs + KnownOptionsPtr->ClientId.OptLen) <= MsgDataLen);

#if !defined(TCPIP_DHCPV4SEVER_VENABLE_ASSERTIONS)
  TCPIP_DHCPV4SERVER_UNUSED_PARAMETER(MsgDataLen); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

  addrLeaseRecIdx = TcpIp_DhcpV4Server_VGetAddrLeaseRecIdx( DhcpV4ServerConfigIdx,
                                                            DhcpV4ServerAddrAssignmentCfgIdx,
                                                            &MsgDataPtr[KnownOptionsPtr->ClientId.OptOfs],
                                                            KnownOptionsPtr->ClientId.OptLen,
                                                            0,
                                                            FALSE );

  if (addrLeaseRecIdx != TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX)
  {
    /* set lease of this client to expired. It may bu used for the same client again. */
    TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState  = TCPIP_DHCPV4SERVER_LEASE_STATE_EXPIRED;

    if (KnownOptionsPtr->MessageType == TCPIP_DHCPV4SERVER_RX_MSG_DHCPDECLINE)
    {
      TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientIdLen = 0;
    }
  }
} /* TcpIp_DhcpV4Server_VHandleDhcpDeclineRelease() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VInitKnownOptionsInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VInitKnownOptionsInfo(
  TCPIP_DHCPV4SERVER_P2V(TcpIp_DhcpV4Server_KnownOptionsInfoType) KnownOptionsPtr)
{
  KnownOptionsPtr->ClientId.OptOfs = 0;
  KnownOptionsPtr->ClientId.OptLen = 0;
  KnownOptionsPtr->MessageType     = TCPIP_DHCPV4SERVER_MSG_INVALID;
#if (TCPIP_DHCPV4SERVER_REQUEST_LEASE_TIME_ENABLED == STD_ON)
  KnownOptionsPtr->LeaseTime       = 0;
#endif
  KnownOptionsPtr->ParamReqSet     = 0;
  KnownOptionsPtr->ReqIpAddr       = 0;
  KnownOptionsPtr->ServerId        = 0;
  KnownOptionsPtr->OptionOverload  = 0;
} /* TcpIp_DhcpV4Server_VInitKnownOptionsInfo() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VParseOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VParseOptions(
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataOfs,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2V(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr)
{
  Std_ReturnType retVal          = E_OK;
  uint16         localMsgDataOfs = MsgDataOfs;
  boolean        endOptFound     = FALSE;

  TCPIP_ASSERT(   (MsgDataOfs == TCPIP_DHCPV4SERVER_MSG_OFS_OPTIONS)
               || (MsgDataOfs == TCPIP_DHCPV4SERVER_MSG_OFS_BOOTFILE)
               || (MsgDataOfs == TCPIP_DHCPV4SERVER_MSG_OFS_SNAME));

  while ((endOptFound == FALSE) && (retVal == E_OK) && (localMsgDataOfs < MsgDataLen))
  {
    uint8 optType = MsgDataPtr[localMsgDataOfs];
    localMsgDataOfs++;

    /* Check for single byte END and PAD options. All other options have a 1 byte length field */

    if (optType == TCPIP_DHCPV4SERVER_MSG_OPT_END)
    {
      /* End option has been found. Stop Processing of the following data. */
      endOptFound = TRUE;
    }
    else if (optType == TCPIP_DHCPV4SERVER_MSG_OPT_PAD)
    {
      /* Skip pad option */
    }
    else if (localMsgDataOfs < MsgDataLen)
    {
      uint8 optLen = MsgDataPtr[localMsgDataOfs];
      localMsgDataOfs++;

      if ((localMsgDataOfs + optLen) < MsgDataLen)
      {
        switch(optType)
        {
        /* [RFC2132 9.6. DHCP Message Type] */
        case TCPIP_DHCPV4SERVER_MSG_OPT_DHCP_MSG_TYPE:
          if (optLen == TCPIP_DHCPV4SERVER_MSG_OPT_DHCP_MSG_TYPE_LEN)
          {
            KnownOptionsPtr->MessageType = MsgDataPtr[localMsgDataOfs];
          }
          else
          {
            retVal = E_NOT_OK;
          }
          break;

        /* [RFC2132 9.14. Client-identifier] */
        case TCPIP_DHCPV4SERVER_MSG_OPT_CLIENT_ID:
          /* ClientIdPtr currently points the 'chaddr' field in the DHCP message header since the hardware address
           * is also used as client identifier if no client identifier option is received.
           * Update ClientIdPtr and ClientIdLen:
           */
          KnownOptionsPtr->ClientId.OptOfs = localMsgDataOfs;
          KnownOptionsPtr->ClientId.OptLen = optLen;
          break;


        /* [RFC2132 9.1. Requested IP Address] */
        case TCPIP_DHCPV4SERVER_MSG_OPT_REQUESTED_IP_ADDR:
          if (optLen == TCPIP_DHCPV4SERVER_MSG_OPT_REQUESTED_IP_ADDR_LEN)
          {
            IPBASE_GET_UINT32(MsgDataPtr, localMsgDataOfs, KnownOptionsPtr->ReqIpAddr);
          }
          else
          {
            retVal = E_NOT_OK;
          }
          break;

        /* [RFC2132 9.2. IP Address Lease Time] */
#if (TCPIP_DHCPV4SERVER_REQUEST_LEASE_TIME_ENABLED == STD_ON)
        case TCPIP_DHCPV4SERVER_MSG_OPT_IP_ADDR_LEASE_TIME:
          if (optLen == TCPIP_DHCPV4SERVER_MSG_OPT_IP_ADDR_LEASE_TIME_LEN)
          {
            IPBASE_GET_UINT32(MsgDataPtr, localMsgDataOfs, KnownOptionsPtr->LeaseTime);
          }
          else
          {
            retVal = E_NOT_OK;
          }
          break;
#endif

        /* [RFC2132 9.3. Option Overload] */
        case TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD:
          if (optLen == TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD_LEN)
          {
            KnownOptionsPtr->OptionOverload = MsgDataPtr[localMsgDataOfs];
          }
          else
          {
            retVal = E_NOT_OK;
          }
          break;

        /* [RFC2132 9.8. Parameter Request List] */
        case TCPIP_DHCPV4SERVER_MSG_OPT_PARAM_REQUEST_LIST:
          if(optLen >= TCPIP_DHCPV4SERVER_MSG_OPT_MESSAGE_MIN_LEN)
          {
            KnownOptionsPtr->ParamReqSet = TcpIp_DhcpV4Server_VParseParamReqestListOption(MsgDataPtr, localMsgDataOfs, optLen);
          }
          else
          {
            retVal = E_NOT_OK;
          }
          break;

        /* [RFC2132 9.7. Server Identifier] */
        case TCPIP_DHCPV4SERVER_MSG_OPT_SERVER_ID:
          if (optLen == TCPIP_DHCPV4SERVER_MSG_OPT_SERVER_ID_LEN)
          {
            IPBASE_GET_UINT32(MsgDataPtr, localMsgDataOfs, KnownOptionsPtr->ServerId);
          }
          else
          {
            retVal = E_NOT_OK;
          }
          break;

        default:
          /* Unknown Option will be skipped */
          break;
        }

        if (retVal == E_OK)
        {
          localMsgDataOfs += optLen;
        }
      }
      else
      {
        /* ERROR: Option length exceeds remaining message length. */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* ERROR: Option length field missing. */
      retVal = E_NOT_OK;
    }
  }

  if (endOptFound == FALSE)
  {
    /* "The last option must always be the 'end' option."
     * [RFC2131 4.1 Constructing and sending DHCP messages]
     */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_DhcpV4Server_VParseOptions() */ /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VParseParamReqestListOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4Server_VParseParamReqestListOption(
  TCPIP_DHCPV4SERVER_P2C(uint8)  MsgDataPtr,
  uint16                         MsgDataOfs,
  uint8                          OptLen)
{
  /* client has send parameter request list option */
  uint8_least reqParamIdx;
  uint8 paramReqSet = 0;

  for (reqParamIdx = 0; reqParamIdx < OptLen; reqParamIdx++)
  {
    /* filter requestable parameters */
    switch (MsgDataPtr[MsgDataOfs + reqParamIdx])
    {
    case TCPIP_DHCPV4SERVER_MSG_OPT_SUBNET_MASK:
      paramReqSet |= TCPIP_DHCPV4SERVER_MSG_OPT_REQ_FLAG_SUBNET_MASK;
      break;

    case TCPIP_DHCPV4SERVER_MSG_OPT_ROUTER:
      paramReqSet |= TCPIP_DHCPV4SERVER_MSG_OPT_REQ_FLAG_ROUTER;
      break;

    default:
      /* this parameter may not be requested and is ignored. */
      break;
    }
  }

  return paramReqSet;
} /* TcpIp_DhcpV4Server_VParseParamReqestListOption() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VUpdateLeaseTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VUpdateLeaseTime(
  TcpIp_DhcpV4ServerConfigIterType           DhcpV4ServerConfigIdx,
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType  AddrLeaseRecIdx,
  uint32                                     RequestedLeaseTime)
{
  uint32 updatedLeaseTimeSec;

#if (TCPIP_DHCPV4SERVER_REQUEST_LEASE_TIME_ENABLED == STD_ON)
  if (RequestedLeaseTime > 0u)
  {
    if (RequestedLeaseTime < TcpIp_GetLeaseTimeSecMinOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx))
    {
      updatedLeaseTimeSec = TcpIp_GetLeaseTimeSecMinOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
    }
    else if (RequestedLeaseTime > TcpIp_GetLeaseTimeSecMaxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx))
    {
      updatedLeaseTimeSec = TcpIp_GetLeaseTimeSecMaxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
    }
    else
    {
      updatedLeaseTimeSec = RequestedLeaseTime;
    }
  }
  else
#endif
  {
    updatedLeaseTimeSec = TcpIp_GetLeaseTimeSecDefaultOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
  }

  if ((TCPIP_DHCPV4SERVER_TIME_INFINITE - TcpIp_DhcpV4Server_TimeSec) < updatedLeaseTimeSec)
  {
    TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->LeaseTimeSec = TCPIP_DHCPV4SERVER_TIME_INFINITE;
  }
  else
  {
    TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->LeaseTimeSec = TcpIp_DhcpV4Server_TimeSec + updatedLeaseTimeSec;
  }
} /* TcpIp_DhcpV4Server_VUpdateLeaseTime() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VUpdateClientInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VUpdateClientInfo(
  TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType                        AddrLeaseRecIdx,
  TCPIP_DHCPV4SERVER_P2C(uint8)                                    MsgDataPtr,
  uint16                                                           MsgDataLen,
  TCPIP_DHCPV4SERVER_P2C(TcpIp_DhcpV4Server_KnownOptionsInfoType)  KnownOptionsPtr)
{
  TCPIP_ASSERT(MsgDataLen >= TCPIP_DHCPV4SERVER_MSG_OFS_OPTIONS);

#if !defined(TCPIP_DHCPV4SEVER_VENABLE_ASSERTIONS)
  TCPIP_DHCPV4SERVER_UNUSED_PARAMETER(MsgDataLen); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

  /* Record received client parameters that will be needed when we send the response */
  IPBASE_GET_UINT32(MsgDataPtr, TCPIP_DHCPV4SERVER_MSG_OFS_XID,    TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientXid);    /* Transaction ID, a random number chosen by the client */
  IPBASE_GET_UINT16(MsgDataPtr, TCPIP_DHCPV4SERVER_MSG_OFS_FLAGS,  TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientFlags);  /* Flags */
  IPBASE_GET_UINT32(MsgDataPtr, TCPIP_DHCPV4SERVER_MSG_OFS_GIADDR, TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientGiAddr); /* gateway ip address */
  TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientParamReqSet = KnownOptionsPtr->ParamReqSet;

  /* Store client hardware address */
  TcpIp_DhcpV4Server_VCopyAndPad( &TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(AddrLeaseRecIdx)->ClientChAddr[0], TCPIP_DHCPV4SERVER_MSG_HLEN_10MBIT_ETH,
                                  &MsgDataPtr[TCPIP_DHCPV4SERVER_MSG_OFS_CHADDR],
                                  TCPIP_DHCPV4SERVER_MSG_HLEN_10MBIT_ETH );
} /* TcpIp_DhcpV4Server_VUpdateClientInfo() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_ConfigureClient()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_ConfigureClient(
  TcpIp_DhcpV4ServerConfigIterType            DhcpV4ServerConfigIdx,
  TCPIP_DHCPV4SERVER_P2V(uint8)               BufPtr,         /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  uint16                                      Length)
{
  Std_ReturnType                            optionParseResult;
  TcpIp_DhcpV4Server_KnownOptionsInfoType   knownOptions;

  TcpIp_DhcpV4Server_VInitKnownOptionsInfo(&knownOptions);

  optionParseResult = TcpIp_DhcpV4Server_VParseOptions(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_OPTIONS, Length, &knownOptions);

  if ((optionParseResult == E_OK) && ((knownOptions.OptionOverload & TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD_FILE) != 0u))
  {
    optionParseResult = TcpIp_DhcpV4Server_VParseOptions( BufPtr,
                                                          TCPIP_DHCPV4SERVER_MSG_OFS_BOOTFILE,
                                                          TCPIP_DHCPV4SERVER_MSG_OFS_BOOTFILE + TCPIP_DHCPV4SERVER_MSG_LEN_BOOTFILE,
                                                          &knownOptions );
  }

  if ((optionParseResult == E_OK) && ((knownOptions.OptionOverload & TCPIP_DHCPV4SERVER_MSG_OPT_OPTION_OVERLOAD_SNAME) != 0u))
  {
    optionParseResult = TcpIp_DhcpV4Server_VParseOptions( BufPtr,
                                                          TCPIP_DHCPV4SERVER_MSG_OFS_SNAME,
                                                          TCPIP_DHCPV4SERVER_MSG_OFS_SNAME + TCPIP_DHCPV4SERVER_MSG_LEN_SNAME,
                                                          &knownOptions );
  }

  if (optionParseResult == E_OK)
  {
    TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType dhcpV4ServerAddrAssignmentCfgIdx;

    if (knownOptions.ClientId.OptLen == 0u)
    {
      knownOptions.ClientId.OptOfs = TCPIP_DHCPV4SERVER_MSG_OFS_CHADDR;
      knownOptions.ClientId.OptLen = TCPIP_DHCPV4SERVER_MSG_HLEN_10MBIT_ETH;
    }

    /* DHCP message options parsed */
    /* Get or create the client record which holds the lease information for this client */

    dhcpV4ServerAddrAssignmentCfgIdx = TcpIp_DhcpV4Server_VGetAddrAssignmentCfgIdxForMacAddr(DhcpV4ServerConfigIdx, &BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_CHADDR]);

    if (dhcpV4ServerAddrAssignmentCfgIdx != TCPIP_DHCPV4SERVER_INV_ADDR_ASSIGN_IDX)
    {
      /* Check DHCP message type option */
      switch (knownOptions.MessageType)
      {
      case TCPIP_DHCPV4SERVER_RX_MSG_DHCPDISCOVER:
        /* [RFC2131 4.3.1 DHCPDISCOVER message]
          * - Choose network address for client
          *   - If no address available report error to DEM (MAY)
          *   - Normal address selection
          *     - active client binding
          *     - expired client binding
          *     - address of requested ip address option (if valid and available)
          *     - use any or configured address from the pool
          *   - If client has requested a specific lease time this time MAY be used
          * - Send OFFER to client
          */

        TcpIp_DhcpV4Server_VHandleDhcpDiscover(DhcpV4ServerConfigIdx, dhcpV4ServerAddrAssignmentCfgIdx, BufPtr, Length, &knownOptions);
        break;

      case TCPIP_DHCPV4SERVER_RX_MSG_DHCPREQUEST:
        /* "A DHCPREQUEST message may come from a client responding to a DHCPOFFER message from a server, #
          *  from a client verifying a previously allocated IP address or from a client extending the lease on a
          *  network address. [RFC2131 4.3.2 DHCPREQUEST message]
          */

        TcpIp_DhcpV4Server_VHandleDhcpRequest(DhcpV4ServerConfigIdx, dhcpV4ServerAddrAssignmentCfgIdx, BufPtr, Length, &knownOptions);
        break;

      case TCPIP_DHCPV4SERVER_RX_MSG_DHCPDECLINE:
        /* fall through */
      case TCPIP_DHCPV4SERVER_RX_MSG_DHCPRELEASE:
        TcpIp_DhcpV4Server_VHandleDhcpDeclineRelease(DhcpV4ServerConfigIdx, dhcpV4ServerAddrAssignmentCfgIdx, BufPtr, Length, &knownOptions);
        break;

      default:
        /* DHCPINFORM  message is not supported and will be ignored. */
        break;
      }
    }
    else
    {
      /* no address assignment configuration for this client at the current switch port on this socket/interface/VLAN has been found */
    }
  }
} /* TcpIp_DhcpV4Server_ConfigureClient() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_RxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_RxIndication(  /* PRQA S 2889 */ /* MD_DHCPV4SERVER_Rule15.5_2889 */
  TcpIp_SocketIdType                          SocketId,
  TCPIP_DHCPV4SERVER_P2V(TcpIp_SockAddrType)  RemoteAddrPtr,  /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  TCPIP_DHCPV4SERVER_P2V(uint8)               BufPtr,         /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  uint16                                      Length)
{
  TcpIp_DhcpV4ServerConfigIterType                            dhcpV4ServerConfigIdx;
  uint32                                                      dhcpMagicCookie;

  /* ----- Development Error Checks ------------------------------------- */
  TcpIp_DhcpV4Server_CheckDetErrorReturnVoid(NULL_PTR != BufPtr, TCPIP_DHCPV4SERVER_SID_RX_INDICATION, TCPIP_DHCPV4SERVER_E_INV_PTR);
  /* ----- */

  TCPIP_DHCPV4SERVER_UNUSED_PARAMETER(RemoteAddrPtr); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* Check if there are address assignment configurations for this socket handle */
  dhcpV4ServerConfigIdx = TcpIp_DhcpV4Server_VGetServerConfigIdxForSocket(SocketId);

  /* Extract the DHCP magic cookie which is located directly after the DHCP header */
  IPBASE_GET_UINT32(BufPtr, TCPIP_DHCPV4SERVER_MSG_OFS_MAGIC_COOKIE, dhcpMagicCookie);

  /* no address assignment configuration for this socket/interface/VLAN */
  if (   (dhcpV4ServerConfigIdx == TCPIP_DHCPV4SERVER_INV_SERVER_CONF_IDX)
  /* Each DHCP message must contain at least the header, the DHCP options cookie, the DHCP message option and an end option */
      || (Length < TCPIP_DHCPV4SERVER_MIN_MSG_LEN)
  /* Message op code / message type. 1 = BOOTREQUEST, 2 = BOOTREPLY */
      || (BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_OP] != TCPIP_DHCPV4SERVER_MSG_OP_BOOTREQUEST)
  /* Hardware address type, see ARP section in "Assigned Numbers" RFC; e.g., '1' = 10mb ethernet. */
      || (BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_HTYPE] != TCPIP_DHCPV4SERVER_MSG_HTYPE_10MBIT_ETH)
  /* Hardware address length (e.g.  '6' for 10mb ethernet). */
      || (BufPtr[TCPIP_DHCPV4SERVER_MSG_OFS_HLEN] != TCPIP_DHCPV4SERVER_MSG_HLEN_10MBIT_ETH)
  /* Magic cookie value */
      || (dhcpMagicCookie != TCPIP_DHCPV4SERVER_MSG_MAGIC_COOKIE))
  /* Contents of filed 'hops'   (1 byte) is ignored by the server */
  /* Contents of field 'sname' (64 bytes, Optional server host name, null terminated string) is ignored by the server */
  /* Contents of field 'file' (128 bytes, Boot file name, null terminated string; "generic" name or null in DHCPDISCOVER, fully qualified directory-path name in DHCPOFFER) is ignored by the server */

  {
    /* ignore invalid message */
  }
  else
  {
    /* Message header seems to be ok. */

    /* DHCP client configuration has been found. Client can be configured by the server */
    TcpIp_DhcpV4Server_ConfigureClient(dhcpV4ServerConfigIdx, BufPtr, Length);
  }
} /* TcpIp_DhcpV4Server_RxIndication() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_TcpIpEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_TcpIpEvent(
  TcpIp_SocketIdType     SocketId,
  IpBase_TcpIpEventType  Event)
{
  if (Event == TCPIP_UDP_CLOSED)
  {
    TcpIp_DhcpV4ServerConfigIterType dhcpV4ServerConfigIdx;

    for (dhcpV4ServerConfigIdx = 0; dhcpV4ServerConfigIdx < TcpIp_GetSizeOfDhcpV4ServerConfig(); dhcpV4ServerConfigIdx++)
    {
      if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) == SocketId)
      {
        TcpIp_SetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx, TCPIP_INV_SOCKET_ID);
      }
    }
  }
} /* TcpIp_DhcpV4Server_TcpIpEvent() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_MainFunction(void)  /* PRQA S 2889 */ /* MD_DHCPV4SERVER_Rule15.5_2889 */
{
  TcpIp_DhcpV4ServerConfigIterType dhcpV4ServerConfigIdx;

  /* ------------------------------------------------- */
  /* DET */
  TcpIp_DhcpV4Server_CheckDetErrorReturnVoid( TcpIp_DhcpV4Server_State != TCPIP_DHCPV4SERVER_STATE_UNINIT,
                                              TCPIP_DHCPV4SERVER_SID_MAIN_FUNCTION,
                                              TCPIP_DHCPV4SERVER_E_UNINIT );
  /* ------------------------------------------------- */

  /* #10 Increment module time counter used for timeout handling. */
  TcpIp_DhcpV4Server_TimeMsec += TCPIP_MAIN_FCT_PERIOD_MSEC;

  if (TcpIp_DhcpV4Server_TimeMsec >= 1000u)
  {
    TcpIp_DhcpV4Server_TimeMsec -= 1000u;
    TcpIp_DhcpV4Server_TimeSec++;
  }

  /* #20 Iterate over all configured DHCP Server instances. */
  for (dhcpV4ServerConfigIdx = 0; dhcpV4ServerConfigIdx < TcpIp_GetSizeOfDhcpV4ServerConfig(); dhcpV4ServerConfigIdx++)
  {
    /* #30 Check if UDP socket is set up for DHCP Server instance. */
    if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) != TCPIP_INV_SOCKET_ID)
    {
      TcpIp_DhcpV4ServerAddressAssignmentConfigIterType dhcpV4ServeraddrAssignmentCfgIdx;
      /* #40 Iterate over all Address Assignment Configurations of the DHCP Server instance. */
      for (dhcpV4ServeraddrAssignmentCfgIdx = TcpIp_GetDhcpV4ServerAddressAssignmentConfigStartIdxOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx);
           dhcpV4ServeraddrAssignmentCfgIdx < TcpIp_GetDhcpV4ServerAddressAssignmentConfigEndIdxOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx);
           dhcpV4ServeraddrAssignmentCfgIdx++)
      {
       TcpIp_DhcpV4ServerAddrLeaseRecsIterType addrLeaseRecIdx;
       /* #50 Iterate over all Address Lease Records of the current Address Assignment Configuration. */
        for (addrLeaseRecIdx = TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(dhcpV4ServeraddrAssignmentCfgIdx);
             addrLeaseRecIdx < TcpIp_GetDhcpV4ServerAddrLeaseRecsEndIdxOfDhcpV4ServerAddressAssignmentConfig(dhcpV4ServeraddrAssignmentCfgIdx);
             addrLeaseRecIdx++)
        {
          /* #60 Update Address Lease Record based on current status. */
          switch (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState)
          {
          case TCPIP_DHCPV4SERVER_LEASE_STATE_TX_OFFER:
            /* #70 [TX_OFFER] Transmit OFFER to client and switch to state RX_REQUEST. */
            if (   TcpIp_DhcpV4Server_VTxMessage((TcpIp_SizeOfDhcpV4ServerConfigType)dhcpV4ServerConfigIdx,
                                              (TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType)dhcpV4ServeraddrAssignmentCfgIdx,
                                              (TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType)addrLeaseRecIdx,
                                              TCPIP_DHCPV4SERVER_TX_MSG_DHCPOFFER)
                == E_OK )
            {
              /* Lease entry will be set to expired if the client does not request the lease within TCPIP_DHCPV4SERVER_OFFER_VALID_TIME_SEC */
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState        = TCPIP_DHCPV4SERVER_LEASE_STATE_RX_REQUEST;
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ExpirationTimeSec = (TcpIp_DhcpV4Server_TimeSec + TcpIp_GetOfferValidTimeSecOfDhcpV4ServerConfig(dhcpV4ServerConfigIdx));
            }
            break;

          case TCPIP_DHCPV4SERVER_LEASE_STATE_RX_REQUEST:
            /* #80 [RX_REQUEST] Switch state to EXPIRED if client did not sent REQUEST(Server did not receive Request) until timeout expired. */
            if (TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ExpirationTimeSec < TcpIp_DhcpV4Server_TimeSec)
            {
              /* OFFER expired. Did not receive REQUEST in time */
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState        = TCPIP_DHCPV4SERVER_LEASE_STATE_EXPIRED;
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseTimeSec      = 0u;
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ExpirationTimeSec = 0u;
            }
            break;

          case TCPIP_DHCPV4SERVER_LEASE_STATE_TX_ACK:
            /* #90 [TX_ACK] Transmit ACK to client and switch to state REQUEST. */
            if (   TcpIp_DhcpV4Server_VTxMessage((TcpIp_SizeOfDhcpV4ServerConfigType)dhcpV4ServerConfigIdx,
                                              (TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType)dhcpV4ServeraddrAssignmentCfgIdx,
                                              (TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType)addrLeaseRecIdx,
                                              TCPIP_DHCPV4SERVER_TX_MSG_DHCPACK)
                == E_OK )
            {
              /* Lease entry will be set to expired if the lease time is not updated before it has been expired */
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState        = TCPIP_DHCPV4SERVER_LEASE_STATE_RX_REQUEST;
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ExpirationTimeSec = TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseTimeSec;
            }
            break;


          case TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK:
            /* fall through. */
          case TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK_BROADCAST:
            /* #100 [TX_NAK] Transmit Negative ACK to client and switch to state EXPIRED. */
            if (   TcpIp_DhcpV4Server_VTxMessage((TcpIp_SizeOfDhcpV4ServerConfigType)dhcpV4ServerConfigIdx,
                                               (TcpIp_SizeOfDhcpV4ServerAddressAssignmentConfigType)dhcpV4ServeraddrAssignmentCfgIdx,
                                               (TcpIp_SizeOfDhcpV4ServerAddrLeaseRecsType)addrLeaseRecIdx,
                                               TCPIP_DHCPV4SERVER_TX_MSG_DHCPNAK)
                == E_OK)
            {
              /* Lease entry will be set to expired if the lease time is not updated before it has been expired */
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState        = TCPIP_DHCPV4SERVER_LEASE_STATE_EXPIRED;
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseTimeSec      = 0u;
              TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ExpirationTimeSec = 0u;
            }
            break;

          default:
            /* No action required for this lease record */
            break;
          }
        }
      }
    }
  }
} /* TcpIp_DhcpV4Server_MainFunction() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VSetupUdpSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(TcpIp_SocketIdType, TCPIP_CODE) TcpIp_DhcpV4Server_VSetupUdpSocket(
  TcpIp_LocalAddrIdType  BindLocalAddrId)
{
  TcpIp_SocketIdType dhcpServerSocketId = TCPIP_INV_SOCKET_ID;
  TcpIp_SocketIdType dhcpServerSocketIdSelected = TCPIP_INV_SOCKET_ID;
  uint16             dhcpServerPort     = TCPIP_DHCPV4SERVER_SERVER_PORT;

  /* Open UDP socket */
  if (E_OK != TcpIp_TcpIp_DhcpV4ServerGetSocket(TCPIP_AF_INET, TCPIP_IPPROTO_UDP, &dhcpServerSocketId))
  {
    /* ERROR: UDP socket could not be bound to the server address and port combination */
    TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_VINTERNAL_FUNCTION, TCPIP_DHCPV4SERVER_E_UDP_SOCKET_GET_ERROR);
  }
  else if (E_OK != TcpIp_Bind(dhcpServerSocketId, BindLocalAddrId, &dhcpServerPort))
  {
    /* ERROR: UDP socket could not be opened */
    TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_VINTERNAL_FUNCTION, TCPIP_DHCPV4SERVER_E_UDP_SOCKET_BIND_ERROR);
  }
  else
  {
    /* Socket Id was obtained successfully */
    dhcpServerSocketIdSelected = dhcpServerSocketId;
  }

  return dhcpServerSocketIdSelected;

} /* TcpIp_DhcpV4Server_VSetupUdpSocket() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VInitSocketConfig
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_VInitSocketConfig(
  TcpIp_DhcpV4ServerConfigIterType  DhcpV4ServerConfigIdx)
{
  TcpIp_DhcpV4ServerAddressAssignmentConfigIterType dhcpV4ServerAddrAssignmentCfgIdx;
  /* #10 Iterate over all configured DHCP address assignment configurations. */
  for (dhcpV4ServerAddrAssignmentCfgIdx = TcpIp_GetDhcpV4ServerAddressAssignmentConfigStartIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
       dhcpV4ServerAddrAssignmentCfgIdx < TcpIp_GetDhcpV4ServerAddressAssignmentConfigEndIdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx);
       dhcpV4ServerAddrAssignmentCfgIdx++)
  {
    TcpIp_DhcpV4ServerAddrLeaseRecsIterType addrLeaseRecIdx;
    /* #20 Iterate over all Address Lease Records of the current Address Assignment Configuration. */
    for (addrLeaseRecIdx = TcpIp_GetDhcpV4ServerAddrLeaseRecsStartIdxOfDhcpV4ServerAddressAssignmentConfig(dhcpV4ServerAddrAssignmentCfgIdx);
         addrLeaseRecIdx < TcpIp_GetDhcpV4ServerAddrLeaseRecsEndIdxOfDhcpV4ServerAddressAssignmentConfig(dhcpV4ServerAddrAssignmentCfgIdx);
         addrLeaseRecIdx++)
    {
      /* #30 Initialize lease record. */
      TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseState        = TCPIP_DHCPV4SERVER_LEASE_STATE_EXPIRED;
      TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ErrorMsgId        = TCPIP_DHCPV4SERVER_ERROR_MESSAGE_NONE;
      TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ClientIdLen       = 0;
      TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->LeaseTimeSec      = 0;
      TcpIp_GetAddrDhcpV4ServerAddrLeaseRecs(addrLeaseRecIdx)->ExpirationTimeSec = 0;
    }
  }

  TcpIp_SetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx, TCPIP_INV_SOCKET_ID);
} /* TcpIp_DhcpV4Server_VInitSocketConfig() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VOpenSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VOpenSocket(
  TcpIp_DhcpV4ServerConfigIterType DhcpV4ServerConfigIdx)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx) == TCPIP_INV_SOCKET_ID)
  {
    /* #10 Setup UDP socket if not already open. */
    TcpIp_SetSocketIdOfDhcpV4ServerConfigDyn( DhcpV4ServerConfigIdx,
                                             (TcpIp_DhcpV4Server_VSetupUdpSocket(TcpIp_GetLocalAddrV4IdxOfDhcpV4ServerConfig(DhcpV4ServerConfigIdx))) );

    if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx) != TCPIP_INV_SOCKET_ID)
    {
      retVal = E_OK;
    }
  }
  else
  {
    TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_VINTERNAL_FUNCTION, TCPIP_DHCPV4SERVER_E_INTERNAL_ERROR);
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_DhcpV4Server_VOpenSocket() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_VCloseSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_VCloseSocket(
  TcpIp_DhcpV4ServerConfigIterType DhcpV4ServerConfigIdx)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* IP address of the DHCPv4 server socket has been lost */
  if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx) != TCPIP_INV_SOCKET_ID)
  {
    /* close socket */
    uint8 socketId = TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx);
    if (TcpIp_Close(socketId, FALSE) == E_OK)
    {
      /* OK: UDP socket closed */
      TcpIp_SetSocketIdOfDhcpV4ServerConfigDyn(DhcpV4ServerConfigIdx, TCPIP_INV_SOCKET_ID);
      TcpIp_DhcpV4Server_VInitSocketConfig(DhcpV4ServerConfigIdx);
      retVal = E_OK;
    }
    else
    {
      /* ERROR: UDP socket could not be closed. */
      TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_VINTERNAL_FUNCTION, TCPIP_DHCPV4SERVER_E_UDP_SOCKET_CLOSE_ERROR);
    }
  }
  else
  {
    /* UDP socket is not open. */
    TcpIp_DhcpV4Server_ReportDetError(TCPIP_DHCPV4SERVER_SID_VINTERNAL_FUNCTION, TCPIP_DHCPV4SERVER_E_UDP_SOCKET_CLOSE_ERROR);
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_DhcpV4Server_VCloseSocket() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_Start
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_Start(void)
{
  Std_ReturnType retVal = E_OK;
  TcpIp_DhcpV4ServerConfigIterType    dhcpV4ServerConfigIdx;

  for (dhcpV4ServerConfigIdx = 0; dhcpV4ServerConfigIdx < TcpIp_GetSizeOfDhcpV4ServerConfig(); dhcpV4ServerConfigIdx++)
  {
    if (   (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) == TCPIP_INV_SOCKET_ID)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetIpAddrAssignmentStateOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) == TCPIP_IPADDR_STATE_ASSIGNED))
    {
      if (TcpIp_DhcpV4Server_VOpenSocket((TcpIp_SizeOfDhcpV4ServerConfigType)dhcpV4ServerConfigIdx) == E_NOT_OK)
      {
        retVal = E_NOT_OK;
      }
    }
  }

  return retVal;
} /* TcpIp_DhcpV4Server_Start() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_Stop
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_Stop(void)
{
  Std_ReturnType retVal = E_OK;
  TcpIp_DhcpV4ServerConfigIterType dhcpV4ServerConfigIdx;

  for (dhcpV4ServerConfigIdx = 0; dhcpV4ServerConfigIdx < TcpIp_GetSizeOfDhcpV4ServerConfig(); dhcpV4ServerConfigIdx++)
  {
    if (TcpIp_GetSocketIdOfDhcpV4ServerConfigDyn(dhcpV4ServerConfigIdx) != TCPIP_INV_SOCKET_ID)
    {
      if (TcpIp_DhcpV4Server_VCloseSocket((TcpIp_SizeOfDhcpV4ServerConfigType)dhcpV4ServerConfigIdx) == E_NOT_OK)
      {
        retVal = E_NOT_OK;
      }
    }
  }

  if (retVal == E_OK)
  {
    TcpIp_DhcpV4Server_TimeSec  = 0;
    TcpIp_DhcpV4Server_TimeMsec = 0;

    TcpIp_DhcpV4Server_TxDataInfo.TxData_Length = 0; /* No TcpIp_UdpTransmit() pending */
  }

  return retVal;
} /* TcpIp_DhcpV4Server_Stop() */


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif  /* (TCPIP_DHCPV4SERVER_ENABLED == STD_ON) */


/* Justification for module-specific MISRA deviations:
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRAC2004_PES.pdf'

   module global deviations -> see file TcpIp.c

   MD_DHCPV4SERVER_Rule8.9_3218: File scope static, '%s', only accessed in one function.
   Reason:      Vector style guide prevents usage of static variables in function scope
   Risk:        None.
   Prevention:  None.

   MD_DHCPV4SERVER_Rule15.5_2889: A function should have a single point of exit at the end
   Reason:      The extra return is present due to a DET Error check macro.
   Risk:        None.
   Prevention:  None.
*/

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_DhcpV4Server.c
 *********************************************************************************************************************/
