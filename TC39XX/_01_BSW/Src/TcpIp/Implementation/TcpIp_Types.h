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
 *         \file  TcpIp_Types.h
 *        \brief  Implementation of TcpIp Module - Type Definitions
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#ifndef TCPIP_TYPES_H
#define TCPIP_TYPES_H

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "ComStack_Types.h"
#include "Std_Types.h"
#include "IpBase_Types.h"

/**************************************************************************************************
* Global defines
**************************************************************************************************/
#define TCPIP_PHYS_ADDR_LEN_BYTE   6

#define TCPIP_IPSEC_GMAC_NONCE_LEN     12u  /* Length in bytes of the Nonce for Gmac */

#define TCPIP_LOCALADDRID_INV 0xFFU
#define TCPIP_LOCALADDRID_ANY 0xFEU /* Any IP address on any IPvX controller */

#define TCPIP_IP_ADDR_ID_ANY  0xFFU

#define TCPIP_NDP_ENTRY_STATIC  0x00U
#define TCPIP_NDP_ENTRY_VALID   0x01U
#define TCPIP_NDP_ENTRY_STALE   0x02U

#define TCPIP_IPV4_TIME_MS          1000uL
#define TCPIP_IPV4_TIME_MAX         0xFFFFFFFFuL
#define TCPIP_IPSEC_SECSELAPSED     0xFFFFu

/**************************************************************************************************
* Macros
**************************************************************************************************/
#define TCPIP_P2V(ptrtype) P2VAR(ptrtype, AUTOMATIC, TCPIP_APPL_VAR)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define TCPIP_P2C(ptrtype) P2CONST(ptrtype, AUTOMATIC, TCPIP_APPL_DATA)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/
/* new types for ASR 4.2.1 -- start ----------------------------- */

typedef uint8  TcpIp_SocketIdType;   /* uint8 and uint16 is allowed */
typedef uint8  TcpIp_SockHndType; /* legacy type for compatibility. Will be removed in future. */

#define TCPIP_INV_SOCKET_ID      0xFFU

/* start ENUMERATION types */
typedef uint16 TcpIp_DomainType;
#define TCPIP_AF_UNDEFINED       0x0000U
#define TCPIP_AF_INET            0x0002U  /* IPv4 */
#define TCPIP_AF_INET6           0x001CU  /* IPv6 */

typedef uint8 TcpIp_ProtocolType;  /* enum */
#define TCPIP_IPPROTO_TCP        0x06U
#define TCPIP_IPPROTO_UDP        0x11U

typedef IpBase_TcpIpEventType TcpIp_EventType;  /* uint8 */
#define TCPIP_TCP_RESET                  0x01U  /* TCP connection was reset, TCP socket and all related resources have been released. */
#define TCPIP_TCP_CLOSED                 0x02U  /* TCP connection was closed successfully, TCP socket and all related resources have been released. */
#define TCPIP_TCP_FIN_RECEIVED           0x03U  /* A FIN signal was received on the TCP connection, TCP socket is still valid. */
#define TCPIP_UDP_CLOSED                 0x04U  /* UDP socket and all related resources have been released. */
#define TCPIP_TLS_HEARTBEAT_NO_RESPONSE  0x05u  /* Vector ext: TLS heartbeat response has not been received in time. */
#define TCPIP_TCP_CONNECTED              0x06U  /* Vector ext: TCP client connection to an external server was established successfully. (only used by TLS) */
#define TCPIP_TCP_ACCEPTED               0x07U  /* Vector ext: TCP server has accepted a connection from an external client. (only used by TLS) */

typedef uint8 TcpIp_ReturnType;
#define TCPIP_OK                 0x00U  /* operation completed successfully */
#define TCPIP_E_NOT_OK           0x01U  /* operation failed */
#define TCPIP_E_PHYS_ADDR_MISS   0x02U  /* operation failed because of an ARP cache miss */

typedef uint8 TcpIp_ParamIdType;
#define TCPIP_PARAMID_TCP_RXWND_MAX             0x00U  /* uint32 */ /* Specifies the maximum TCP receive window for the socket. */
#define TCPIP_PARAMID_FRAMEPRIO                 0x01U  /* uint8 */  /* Specifies the frame priority for outgoing frames on the socket. */
#define TCPIP_PARAMID_TCP_NAGLE                 0x02U  /* uint8 */  /* Specifies if the Nagle Algorithm according to IETF RFC 896 is enabled or not. */
#define TCPIP_PARAMID_TCP_KEEPALIVE             0x03U  /* uint8 */ /* Specifies if TCP Keep Alive Probes are sent on the socket connection. (default = false) */
#define TCPIP_PARAMID_TTL                       0x04U  /* uint8 */  /* Specifies the time to live value for outgoing frames on the socket. */
#define TCPIP_PARAMID_TCP_KEEPALIVE_TIME        0x05U  /* uint32 */ /* Specifies the time in [s] between the last data packet sent (simple ACKs are not considered data) and the first keepalive probe. (0..INV, default = 7200) */
#define TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX  0x06U  /* uint16 */ /* Specifies the maximum number of times that a keepalive probe is retransmitted. (0..65535) */
#define TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL    0x07U  /* uint32 */ /* Specifies the interval in [s] between subsequent keepalive probes. (0..INV) */
/* TCPIP_PARAMID_VENDOR_SPECIFIC             0x80U     Start of vendor specific range of parameter IDs. */
#define TCPIP_PARAMID_V_TCP_UTOUPDATE           0x80U  /* uint16 */ /* new value for user timerout */
#define TCPIP_PARAMID_V_TCP_UTOENABLED          0x81U  /* BOOL */   /* enable usage of user timerout option */
#define TCPIP_PARAMID_V_TCP_UTOCHANGEABLE       0x82U  /* BOOL */   /* allow change of user timerout by received option */
#define TCPIP_PARAMID_V_TCP_TXBUFSIZE           0x83U  /* uint32 */ /* Specifies the TCP tx buffer size (to choose the matching buffer) */
#define TCPIP_PARAMID_V_IPV4_TYPE_OF_SERVICE    0x84U  /* uint8 */  /* specify the 'type of service' value used for sending IPv4 messages */
#define TCPIP_PARAMID_V_IPV6_FLOW_LABEL         0x85U  /* uint32 */ /* specify the 'flow label' value used for sending IPv6 messages */
#define TCPIP_PARAMID_V_IPV6_TRAFFIC_CLASS      0x86U  /* uint8 */  /* specify the 'traffic class' value used for sending IPv6 messages */
#define TCPIP_PARAMID_V_UDP_TXREQLISTSIZE       0x87U  /* uint8 */  /* choose the desired TxRequestList size */
#define TCPIP_PARAMID_V_UDP_TXRETRYLISTSIZE     0x88U  /* uint8 */  /* set the number of Eth tx buffers used in case of PhysAddrMiss */
#define TCPIP_PARAMID_V_PHYS_DEST_ADDR          0x89U  /* uint8[6] */ /* set physical destination address for outgoing packets (override ARP). */

#define TCPIP_PARAMID_V_USE_TLS                 0x8AU  /* uint8 */  /* Enable / disable the usage of TLS for the (TCP) socket */

#define TCPIP_PARAMID_V_TLS_TXBUFSIZE           0xC0U  /* uint32 */ /* Specifies the TLS tx buffer size */
#define TCPIP_PARAMID_V_TLS_RXBUFSIZE           0xC1U  /* uint32 */ /* Specifies the TLS rx buffer size */
#define TCPIP_PARAMID_V_TLS_SELECT_OCSP_REQEST  0xC2U  /* uint8 */  /* select OCSP requests for the connection */
#define TCPIP_PARAMID_V_TLS_HEARTBEAT_MODE      0xC3U  /* uint8 */  /* select heartbeat mode for the connection */
#define TCPIP_PARAMID_V_TLS_HEARTBEAT_PERIOD_S  0xC4U  /* uint32 */ /* specify heartbeat period for the connection */

/* define use in callback TcpIp_SocketOwnerTlsValidationResult */
#define TCPIP_TLS_VALIDATION_OK                 0x00u  /* The certificate chain is validated and ok, or the socket owner accepts the connection explicitly */
#define TCPIP_TLS_VALIDATION_UNKNOWN_CA         0x01u  /* The cert chain could not be validated because of an unknown CA */
#define TCPIP_TLS_VALIDATION_LAST_SIGN_INVALID  0x02u  /* The signature of the last cert chain element is invalid */
#define TCPIP_TLS_VALIDATION_INT_SIGN_INVALID   0x03u  /* The signature of an intermediate element of the cert chain is invalid */
#define TCPIP_TLS_VALIDATION_REFUSED_BY_OWNER   0x04u  /* The socket owner refused the connection explicitly */

#define DHCPV4_SRCPORT_OFS    0u
#define DHCPV4_TGTPORT_OFS    2u
#define DHCPV4_LEN_BYTE_OFS   4u
#define DHCPV4_CHECKSUM_OFS   6u

/* UDP header field Offset */
#define UDP_HDR_OFF_SRCPORT             0u
#define UDP_HDR_OFF_TGTPORT             (UDP_HDR_OFF_SRCPORT + 2u)
#define UDP_HDR_OFF_LENBYTE             (UDP_HDR_OFF_TGTPORT + 2u)
#define UDP_HDR_OFF_CHKSUM              (UDP_HDR_OFF_LENBYTE + 2u)

/* new types for ASR 4.2.1 -- end ----------------------------- */

typedef uint32         TcpIp_NetAddrType;

typedef uint8          TcpIp_LocalAddrIdType;

/* Values of TcpIp_IpAddrStateType */
#define TCPIP_IPADDR_STATE_ASSIGNED   0U
#define TCPIP_IPADDR_STATE_ONHOLD     1U
#define TCPIP_IPADDR_STATE_UNASSIGNED 2U
typedef uint8          TcpIp_IpAddrStateType;

typedef uint16      TcpIp_TcpIpErrorType;

typedef struct
{
  TcpIp_DomainType   domain;
} TcpIp_SockAddrType;

typedef struct
{
  TcpIp_DomainType   domain;
  uint16             port;
  uint32             addr[1]; /* PRQA S 1039 */ /* MD_TCPIP_Rule1.2_1039 */
} TcpIp_SockAddrInetType;

typedef struct
{
  TcpIp_DomainType   domain;
  uint16             port;
  uint32             addr[4];
} TcpIp_SockAddrInet6Type;

typedef uint8          TcpIp_StateType;  /* module state */

typedef IpBase_SockAddrIn6Type TcpIp_SockAddrInXType; /* Still used by Etm. */

typedef struct
{
  TcpIp_DomainType   domain;
  uint16             port;
} TcpIp_SockDomainAndPortType;

typedef union
{ /* PRQA S 750 */ /* MD_MSR_Union */
  IpBase_FamilyType           sa_family;
  IpBase_SockAddrType         SockAddr;
  IpBase_SockAddrInType       SockAddrIn;
  IpBase_SockAddrIn6Type      SockAddrIn6;
  TcpIp_SockDomainAndPortType DomainAndPort;
  TcpIp_SockAddrType          TcpIpSockAddr;
} TcpIp_SockAddrBaseType;

typedef void (*TcpIp_SocketOwnerRxIndicationType)(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(TcpIp_SockAddrType) RemoteAddrPtr,
  TCPIP_P2V(uint8)              BufPtr,
  uint16                        Length);

typedef void (*TcpIp_SocketOwnerTxConfirmationType)(
  TcpIp_SocketIdType            SocketId,
  uint16                        Length);

typedef Std_ReturnType (*TcpIp_SocketOwnerTcpAcceptedType)(
  TcpIp_SocketIdType            SocketId,
  TcpIp_SocketIdType            SocketIdConnected,
  TCPIP_P2V(TcpIp_SockAddrType) RemoteAddrPtr);

typedef void (*TcpIp_SocketOwnerTcpConnectedType)(
  TcpIp_SocketIdType            SocketId);

typedef void (*TcpIp_SocketOwnerTcpIpEventType)(
  TcpIp_SocketIdType            SocketId,
  IpBase_TcpIpEventType         Event);

typedef void (*TcpIp_SocketOwnerTlsValidationResultType)(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(uint8)              ValidationResultPtr,
  TCPIP_P2C(uint8)              CertChainPtr,
  uint32                        CertChainLen);

typedef BufReq_ReturnType (*TcpIp_SocketOwnerCopyTxDataType)(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(uint8)              BufPtr,
  uint16                        BufLength);

typedef BufReq_ReturnType (*TcpIp_SocketOwnerCopyTxDataDynType)(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(uint8)              BufPtr,
  TCPIP_P2V(uint16)             BufLengthPtr);

typedef void (*TcpIp_SocketOwnerLocalIpAddrAssignmentChgType)(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TcpIp_IpAddrStateType         State);

typedef void (*TcpIp_PhysAddrTableChgCbkType)(
  uint8                         CtrlIdx,
  TCPIP_P2V(TcpIp_SockAddrType) IpAddrPtr,
  TCPIP_P2V(uint8)              PhysAddrPtr,
  boolean                       Valid);

typedef void (*TcpIp_DuplicateAddrDetectionCbkType)(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TCPIP_P2C(TcpIp_SockAddrType) IpAddrPtr,
  TCPIP_P2C(uint8)              LocalPhysAddrPtr,
  TCPIP_P2C(uint8)              RemotePhysAddrPtr);

typedef void (*TcpIp_IcmpMsgHandlerCbkType)(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TCPIP_P2C(TcpIp_SockAddrType) RemoteAddrPtr,
  uint8                         Ttl,
  uint8                         Type,
  uint8                         Code,
  uint16                        DataLength,
  TCPIP_P2V(uint8)              DataPtr);

typedef void (*TcpIp_IcmpMultiPartMsgHandlerCbkType)(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TCPIP_P2C(TcpIp_SockAddrType) RemoteAddrPtr,
  uint8                         Ttl,
  uint8                         Type,
  uint8                         Code,
  uint16                        DataLength,
  TCPIP_P2V(uint8)              DataPtr,
  uint16                        MultiPartDataLength,
  TCPIP_P2V(uint8)              MultiPartDataPtr);

typedef uint16 (*TcpIp_GetRandomNumberType)(void);

typedef struct
{
  TcpIp_SocketOwnerRxIndicationType          RxIndicationFuncPtr;
  TcpIp_SocketOwnerTxConfirmationType        TxConfirmationFuncPtr;
  TcpIp_SocketOwnerTcpAcceptedType           TcpAcceptedFuncPtr;
  TcpIp_SocketOwnerTcpConnectedType          TcpConnectedFuncPtr;
  TcpIp_SocketOwnerTcpIpEventType            TcpIpEventFuncPtr;
  TcpIp_SocketOwnerTlsValidationResultType   TlsValidationResultFuncPtr;
  TcpIp_SocketOwnerCopyTxDataType            CopyTxDataFuncPtr;
  TcpIp_SocketOwnerCopyTxDataDynType         CopyTxDataDynFuncPtr;
} TcpIp_SocketOwnerCfgType;

typedef struct
{
  IpBase_PortType SrcPort;
  IpBase_PortType TgtPort;
  uint16          LenByte;
  uint16          Checksum;
} TcpIp_Udp_HdrType;

typedef IpBase_PbufType        TcpIp_PbufType;

typedef uint8 TcpIp_DhcpV4_OptSelectorType;

/* Specification of IP address assignment policy. */
typedef uint8 TcpIp_IpAddrAssignmentType;
#define TCPIP_IPADDR_ASSIGNMENT_NONE             0u
#define TCPIP_IPADDR_ASSIGNMENT_STATIC           1u  /* Static configured IPv4/IPv6 address */
#define TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL        2u  /* Linklocal IPv4/IPv6 address assignment. */
#define TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP   2u  /* Linklocal IPv4/IPv6 address assignment using DoIP parameters.
                                                        (same value as TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL because TcpIp
                                                        internal handling is identical) */
#define TCPIP_IPADDR_ASSIGNMENT_DHCP             3u  /* Dynamic configured IPv4/IPv6 address by DHCP. */
#define TCPIP_IPADDR_ASSIGNMENT_IPV6_ROUTER      4u  /* Dynamic configured IPv4/IPv6 address by Router Advertisement. */
#define TCPIP_IPADDR_ASSIGNMENT_ANY           0xFFu  /* Specifies ANY address assignment type for use with Vector specific API TcpIp_ReleaseSpecificIpAddrAssignment(). */

/* Parameter IDs for diagnostic read access */
typedef uint32 TcpIp_DiagParamsType;
#define TCPIP_DP_SOCKET_LOCAL_PORT               0x00U
#define TCPIP_DP_SOCKET_TCP_CURRENT_ACK_NUM      0x01U
#define TCPIP_DP_SOCKET_TCP_NEXT_SEQ_NUM         0x02U
#define TCPIP_DP_INVALID                         0x03U  /* this id is the highest supported parameter id */


typedef uint8 TcpIp_DListIdxType;

/* DList element (array of elements is managed by descriptor) */
typedef struct
{
  TcpIp_DListIdxType             PrevIdx; /* index of the predecessor */
  TcpIp_DListIdxType             NextIdx; /* index of the successor */
} TcpIp_DListNodeType;

/* DList descriptor (can be shared by multiple instances) */
typedef struct
{
  TcpIp_DListIdxType             FirstFreeIdx;      /* index of first element in free list */
  TcpIp_DListIdxType             LastFreeIdx;       /* index of last element in free list */
  uint8                          ElementFreeCount;  /* number of elements in free list */
  uint8                          ElementTotalCount; /* number of elements at NodePtr */
  TCPIP_P2V(TcpIp_DListNodeType) NodePtr;           /* pointer to element array of this list */
} TcpIp_DListDescType;

/* DList instance */
typedef struct
{
  TcpIp_DListIdxType             FirstIdx;     /* index of first element in list */
  TcpIp_DListIdxType             LastIdx;      /* index of last element in list */
  uint8                          ElementCount; /* number of elements in list */
  TCPIP_P2V(TcpIp_DListDescType) DescPtr;      /* pointer to list descriptor of the list */
} TcpIp_DListType;

/* Struct for function TcpIp_GetArpCacheEntries */
typedef struct
{
  uint32   InetAddr[1];   /* IpV4 address in Network byte order */
  uint8    PhysAddr[6];   /* Physical address in Network byte order */
  uint8    State;         /* State of the address Entry */
} TcpIp_ArpCacheEntryType;

#define TCPIP_ARP_ENTRY_STATIC  0u
#define TCPIP_ARP_ENTRY_VALID   1u
#define TCPIP_ARP_ENTRY_STALE   2u

typedef struct
{
  uint32 Inet6Addr[4]; /* IPv6 address in network byte order */
  uint8  PhysAddr[6];  /* physical address in network byte order */
  uint8  State;        /* state of the address entry */
} TcpIp_NdpCacheEntryType;

typedef uint8 TcpIp_DhcpEventType;
#define TCPIP_DHCP_EVENT_TX_DISCOVER_SOLICIT    0u
#define TCPIP_DHCP_EVENT_RX_OFFER_ADVERTISE     1u
#define TCPIP_DHCP_EVENT_TX_REQUEST             2u
#define TCPIP_DHCP_EVENT_RX_ACK_REPLY           3u
#define TCPIP_DHCP_EVENT_TX_V6_CONFIRM          4u
#define TCPIP_DHCP_EVENT_TX_V6_RENEW            5u
#define TCPIP_DHCP_EVENT_TX_V6_REBIND           6u
#define TCPIP_DHCP_EVENT_TX_V6_RELEASE          7u
#define TCPIP_DHCP_EVENT_TX_V6_DECLINE          8u
#define TCPIP_DHCP_EVENT_INVALID                255u

typedef uint8 TcpIp_DhcpUserOptionDirectionType;
#define TCPIP_DHCP_USER_OPTION_RX                0u
#define TCPIP_DHCP_USER_OPTION_TX                1u
#define TCPIP_DHCP_USER_OPTION_RX_REQUESTED      2u

typedef void (*TcpIp_SocketOwnerDhcpEventType)(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  TcpIp_DhcpEventType   Event);

#define TCPIP_IPSEC_SPI_ANY                  0u

/* Presently only a single traffic selector is supported */
#define TCPIP_IPSEC_TRAFFICSEL_INDEX         0u

typedef uint8 TcpIp_IpSecPolicyType;
/* IP Security policy */
#define TCPIP_IPSEC_POLICY_BYPASS            0u    /* Bypass security policy */
#define TCPIP_IPSEC_POLICY_PROTECT           1u    /* Protect security policy */
#define TCPIP_IPSEC_POLICY_OPTIONAL          2u    /* Optional security policy */
#define TCPIP_IPSEC_POLICY_DISCARD           3u    /* Discard security policy */
#define TCPIP_IPSEC_POLICY_INVALID           4u

typedef uint8 TcpIp_SaDirectionType;
/* IpSec traffic direction */
#define TCPIP_IPSEC_TRAFFIC_INBOUND          0u    /* Inbound traffic */
#define TCPIP_IPSEC_TRAFFIC_OUTBOUND         1u    /* Outbound traffic */
#define TCPIP_IPSEC_TRAFFIC_INVALID          255u  /* Invalid traffic */

typedef uint8 TcpIp_IpSecHeaderType;
/* IpSec header types */
#define TCPIP_IPSEC_HDR_NONE       0u      /* invalid value */
#define TCPIP_IPSEC_HDR_AH_ESP     1u      /* support both AH and ESP - not supported */
#define TCPIP_IPSEC_HDR_AH         2u      /* only AH  */
#define TCPIP_IPSEC_HDR_ESP        3u      /* only ESP */

typedef uint8 TcpIp_IpSecIntegrityTransformJobStatusType;
/* Status of the JobPair */
#define TCPIP_IPSEC_STATUS_JOBPAIR_UNUSED     0u /* Job pair is unused */
#define TCPIP_IPSEC_STATUS_JOBPAIR_ALLOCATED  1u /* Job pair has been allocated */

typedef uint8 TcpIp_IpSecEventType;
/* IpSec events */
#define TCPIP_IPSEC_NO_EVENT                0u /* No IpSec Auditable event */
#define TCPIP_IPSEC_EVENT_INVALID_HDR       1u /* Invalid IpSec header  */
#define TCPIP_IPSEC_EVENT_DISCARD_POLICY    2u /* Discard IpSec security policy */
#define TCPIP_IPSEC_EVENT_SEQ_OVERFLOW      3u /* AH sequence number overflow */
#define TCPIP_IPSEC_EVENT_ANTIREPLAY        4u /* AH anti replay attack */
#define TCPIP_IPSEC_EVENT_VERIFY_FAILED     5u /* AH authentication data verification failed */
#define TCPIP_IPSEC_EVENT_GEN_FAILED        6u /* AH authentication data generation failed */
#define TCPIP_IPSEC_EVENT_FRAGMENT          7u /* Fragmented IpSec Ip packet */
#define TCPIP_IPSEC_EVENT_SAENTRY_NOTFOUND  8u /* SA entry lookup failure */

typedef uint8 TcpIp_IpProtocolType;

typedef uint16 TcpIp_IpSecEncrTransformType;
/* Encryption Algorithm Transform IDs according to IANA */
#define TCPIP_IPSEC_TRANSFORM_ENCR_DES_IV64               1u  /**< encr_des_iv64 */
#define TCPIP_IPSEC_TRANSFORM_ENCR_DES                    2u  /**< encr_des      */
#define TCPIP_IPSEC_TRANSFORM_ENCR_3DES                   3u  /**< encr_3des     */
#define TCPIP_IPSEC_TRANSFORM_ENCR_RC5                    4u  /**< encr_rc5      */
#define TCPIP_IPSEC_TRANSFORM_ENCR_IDEA                   5u  /**< encr_idea     */
#define TCPIP_IPSEC_TRANSFORM_ENCR_CAST                   6u  /**< encr_cast     */
#define TCPIP_IPSEC_TRANSFORM_ENCR_BLOWFISH               7u  /**< encr_blowfish */
#define TCPIP_IPSEC_TRANSFORM_ENCR_3IDEA                  8u  /**< encr_3idea    */
#define TCPIP_IPSEC_TRANSFORM_ENCR_DES_IV32               9u  /**< encr_des_iv32 */
#define TCPIP_IPSEC_TRANSFORM_ENCR_NULL                   11u /**< encr_null     */
#define TCPIP_IPSEC_TRANSFORM_ENCR_AES_CBC                12u /**< encr_aes_cbc  */
#define TCPIP_IPSEC_TRANSFORM_ENCR_AES_CTR                13u /**< encr_aes_ctr  */

typedef uint16 TcpIp_IpSecIntegrityTransformType;
/* Integrity Algorithm Transform IDs according to IANA */
#define TCPIP_IPSEC_TRANSFORM_AUTH_NONE                   0u /**< No authentication algorithm  */
#define TCPIP_IPSEC_TRANSFORM_AUTH_HMAC_MD5_96            1u /**< Hmac MD5 algorithm           */
#define TCPIP_IPSEC_TRANSFORM_AUTH_HMAC_SHA1_96           2u /**< Hmac sha1 96 algorithm       */
#define TCPIP_IPSEC_TRANSFORM_AUTH_DES_MAC                3u /**< Des algorithm                */
#define TCPIP_IPSEC_TRANSFORM_AUTH_KPDK_MD5               4u /**< Kpdk MD5 algorithm           */
#define TCPIP_IPSEC_TRANSFORM_AUTH_AES_XCBC_96            5u /**< Aes XCBC 96 algorithm        */
#define TCPIP_IPSEC_TRANSFORM_AUTH_HMAC_MD5_128           6u /**< Hmac MD5 algorithm           */
#define TCPIP_IPSEC_TRANSFORM_AUTH_HMAC_SHA1_160          7u /**< Hmac sha1 algorithm          */
#define TCPIP_IPSEC_TRANSFORM_AUTH_AES_CMAC_96            8u /**< Aes Cmac algorithm           */
#define TCPIP_IPSEC_TRANSFORM_AUTH_AES_128_GMAC           9u /**< Aes Gmac 128 algorithm       */
#define TCPIP_IPSEC_TRANSFORM_AUTH_AES_192_GMAC           10u /**< Aes Gmac 192 algorithm      */
#define TCPIP_IPSEC_TRANSFORM_AUTH_AES_256_GMAC           11u /**< Aes Gmac 256 algorithm      */
#define TCPIP_IPSEC_TRANSFORM_AUTH_HMAC_SHA2_256_128      12u /**< Hmac sha2 256/128 algorithm */
#define TCPIP_IPSEC_TRANSFORM_AUTH_HMAC_SHA2_384_192      13u /**< Hmac sha2 384/192 algorithm */
#define TCPIP_IPSEC_TRANSFORM_AUTH_HMAC_SHA2_512_256      14u /**< Hmac sha2 512/256 algorithm */

typedef struct {
  uint8 Nonce[TCPIP_IPSEC_GMAC_NONCE_LEN];
}TcpIp_IpSec_GmacNonceType;


typedef struct
{
  TCPIP_P2C(TcpIp_SockAddrType)            RemoteAddr;           /**< Remote Ip address (in network byte order) */
  uint16                                   LocalPortRangeStart;  /**< Local port range start (in host byte order) */
  uint16                                   LocalPortRangeEnd;    /**< Local port range start (in host byte order) */
  uint16                                   RemotePortRangeStart; /**< Remote port range start (in host byte order) */
  uint16                                   RemotePortRangeEnd;   /**< Remote port range start (in host byte order) */
  TcpIp_IpProtocolType                     IpProtocol;           /**< Upper layer protocols supported */
} TcpIp_IpSecTrafficSelectorType;

typedef struct
{
  TCPIP_P2C(uint8)                         InboundKeyMatPtr;  /**< Key material for inbound job */
  TCPIP_P2C(uint8)                         OutboundKeyMatPtr; /**< Key material for outbound job */
  uint16                                   InboundKeyMatLen;  /**< Key length for inbound job */
  uint16                                   OutboundKeyMatLen; /**< Key length for outbound job */
} TcpIp_IpSecKeyMaterialInfoType;

typedef struct
{
  TcpIp_IpSecIntegrityTransformType        IntegTransformIdent;    /**< Transform identifier for the integrity transform  */
  TcpIp_IpSecEncrTransformType             EncryptTransformIdent;  /**< Transform identifier for the encryption transform */
  boolean                                  EsnEnabled;             /**< Esn support flag                                  */
} TcpIp_IpSecTransformInfoType;

typedef struct
{
  TcpIp_IpSecKeyMaterialInfoType              KeyMaterial;         /**< struct for storing key materials     */
  TcpIp_IpSecTransformInfoType                SecurityTransform;   /**< struct containing ipsec transform    */
  uint32                                      InboundSpi;          /**< inbound Spi                          */
  uint32                                      OutboundSpi;         /**< Outbound Spi                         */
  TCPIP_P2C(TcpIp_IpSecTrafficSelectorType)   TrafficSelectors;    /**< struct for storing traffic selectors */
  uint16                                      NumTrafficSelectors; /**< Number of traffic selectors          */
  TcpIp_IpSecHeaderType                       IpsecHdrType;        /**< Ipsec header type                    */
} TcpIp_IpSecSaInfoType;

typedef struct
{
  uint32                                      InboundSpi;          /**< inbound Spi                          */
  uint32                                      OutboundSpi;         /**< Outbound Spi                         */
  uint32                                      IncomingPktCnt;      /**< Incoming packet count                */
  uint32                                      OutgoingPktCnt;      /**< Outgoing packet count                */
  uint16                                      SecsSinceLastRx;     /**< Seconds since last Rx                */
  uint16                                      SecsSinceLastTx;     /**< Seconds since last Tx                */
  TcpIp_IpSecHeaderType                       IpsecProtocol;       /**< Ipsec protocol type                  */
} TcpIp_IpSecSaStatusType;

typedef void (*TcpIp_IpSecSpdCalloutFunctionType)(
  TCPIP_P2V(TcpIp_IpSecPolicyType)   SecurityPolicyPtr,
  uint8                              Protocol,
  TCPIP_P2C(TcpIp_SockAddrType)      RemSock,
  TCPIP_P2C(TcpIp_SockAddrType)      LocSock);

typedef void (*TcpIp_IpSecAuditEventCalloutFunctionType)(
  uint32                         Spi,
  uint32                         SeqNum,
  TCPIP_P2C(TcpIp_SockAddrType)  RemSock,
  TCPIP_P2C(TcpIp_SockAddrType)  LocSock,
  TcpIp_IpSecEventType           ErrorId);

/* datatype for function TcpIp_GetAndResetMeasurementData */
typedef uint8 TcpIp_MeasurementIdxType;
#define TCPIP_MEAS_DROP_TCP         0x01u
#define TCPIP_MEAS_DROP_UDP         0x02u
#define TCPIP_MEAS_DROP_IPV4        0x03u
#define TCPIP_MEAS_DROP_IPV6        0x04u

/* Vendor specific measurement indices */
#define TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6     0x80u
#define TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4          0x81u

#define TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_TX_BUFFER            0x84u
#define TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER            0x85u
#define TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER  0x086u

/* IPsec Diagnostic measurement indices */
#define TCPIP_MEAS_VENDOR_SPECIFIC_NR_SA_PAIRS          0x82u
#define TCPIP_MEAS_VENDOR_SPECIFIC_SA_PAIRS             0x83u

#define TCPIP_MEAS_ALL              0xFFu

#define TCPIP_MEASUREMENTDATA_IDX   0u
#define TCPIP_MEASUREMENTDATA_MAX   0xFFFFFFFFuL

#endif
/* TCPIP_TYPES_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Types.h
 *********************************************************************************************************************/
