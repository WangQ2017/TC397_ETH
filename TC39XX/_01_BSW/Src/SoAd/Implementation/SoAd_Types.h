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
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SoAd_Types.h
 *        \brief  Socket Adaptor types header file
 *
 *      \details  Vector static types header file for AUTOSAR Socket Adaptor module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined(SOAD_TYPES_H)
# define SOAD_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd_Cfg.h"
# include "ComStack_Types.h"
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
#  include "TcpIp_Types.h"
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
# include "IpBase.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* PRQA S 3453 FCT_LIKE_MACRO */ /* MD_MSR_FctLikeMacro */

# define SOAD_A_P2VAR(Type)           (P2VAR(Type, AUTOMATIC, AUTOMATIC))
# define SOAD_A_P2CONST(Type)         (P2CONST(Type, AUTOMATIC, AUTOMATIC))

# define SOAD_D_P2VAR(Type)           (P2VAR(Type, AUTOMATIC, SOAD_APPL_DATA))
# define SOAD_D_P2CONST(Type)         (P2CONST(Type, AUTOMATIC, SOAD_APPL_DATA))

# define SOAD_V_P2VAR(Type)           (P2VAR(Type, AUTOMATIC, SOAD_APPL_VAR))
# define SOAD_V_P2CONST(Type)         (P2CONST(Type, AUTOMATIC, SOAD_APPL_VAR))

# define SOAD_P2CONST(Type)           P2CONST(Type, AUTOMATIC, SOAD_APPL_DATA)
# define SOAD_P2VAR(Type)             P2VAR(Type, AUTOMATIC, SOAD_APPL_VAR)
# define SOAD_CONSTP2VAR(Type)        CONSTP2VAR(Type, AUTOMATIC, SOAD_APPL_VAR)
# define SOAD_CONSTP2CONST(Type)      CONSTP2CONST(Type, AUTOMATIC, SOAD_CONST)

/* PRQA L:FCT_LIKE_MACRO */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES DEFINES
 *********************************************************************************************************************/

/*! Physical address length. */
# define SOAD_UHWID_LEN_BYTE              TCPIP_PHYS_ADDR_LEN_BYTE

/*! IPv4 address length. */
# define SOAD_IPV4_ADDR_LEN_BYTE          (4u)
/*! IPv6 address length. */
# define SOAD_IPV6_ADDR_LEN_BYTE          (16u)
/*! IPv6 address length for 32 bit. */
# define SOAD_IPV6_ADDR_LEN_32            (4u)

/*! Invalid index for array of type uint16. */
# define SOAD_INV_BUF_IDX_16              (0xFFFFu)
/*! Invalid index for array of type uint32. */
# define SOAD_INV_BUF_IDX_32              (0xFFFFFFFFu)

/*! Invalid physical address value. */
# define SOAD_INV_PHYS_ADDR               (0u)

/*! Invalid value to indicate that no keep alive is configured. */
# define SOAD_INV_KEEP_ALIVE_VALUE        (0xFFFFFFFFu)

/*! Maximum value for type uint8. */
# define SOAD_MAX_UINT_8                  (0xFFu)
/*! Maximum value for type uint32. */
# define SOAD_MAX_UINT_32                 (0xFFFFFFFFu)
/*! Maximum value for type uint32 used for uint32 timeouts. */
# define SOAD_MAX_TIMEOUT_32              (0xFFFFFFFFu)

/*! Value to indicate if file descriptor has not been changed. */
# define SOAD_BSD_FD_NO_CHANGE            (0u)

/*! Value to indicate if a TCP connection has been established. */
# define SOAD_BSD_TCP_CONNECTED           (0u)

/*! Positive return value of BSD API. */
# define SOAD_BSD_NO_ERROR                (0u)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Module state type. */
typedef uint8                                 SoAd_StateType;

/*! Module internal return type used for Rx PDU verification. */
typedef uint8                                 SoAd_ReturnType;
# define SOAD_E_OK                            (0u)    /*!< Rx PDU verification succeeded. */
# define SOAD_E_NOT_OK                        (1u)    /*!< Rx PDU verification failed. */
# define SOAD_E_PENDING                       (2u)    /*!< Rx PDU verification pending. */

/*! Module internal return type used for INTEGRITY reception. */
typedef uint8                                 SoAd_IntegrityRxReturnType;
# define SOAD_INTEGRITY_RX_E_OK               (0u)    /*!< Reception succeeded. */
# define SOAD_INTEGRITY_RX_E_NOT_OK           (1u)    /*!< Reception failed. */
# define SOAD_INTEGRITY_RX_E_AGAIN            (2u)    /*!< Retry reception later.  */

/*! State of an INTEGRITY socket. */
typedef uint8                                 SoAd_IntegritySocketStateType;
# define SOAD_INTEGRITY_SOCKET_S_UNUSED               (0u)  /*!< Integrity socket not used for any SoAd socket. */
# define SOAD_INTEGRITY_SOCKET_S_USED                 (1u)  /*!< Integrity socket used for at least one SoAd socket. */
# define SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_AVAILABLE  (2u)  /*!< Integrity Os socket is mapped */
# define SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_BOUND      (3u)  /*!< Integrity Os socket is bound. */

/*! Type to describe the different event queues. */
typedef uint8                                 SoAd_EventQueueEnumType;
# define SOAD_EVENT_QUEUE_SOCK_IDX            (0u)    /*!< Queue for module internal socket index. */
# define SOAD_EVENT_QUEUE_LOCAL_ADDR          (1u)    /*!< Queue for local address. */
# define SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE    (2u)    /*!< Queue for socket connection with UDP IF Tx PDU. */
# define SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP     (3u)    /*!< Queue for socket connection with IF Tx RouteGrp. */
# define SOAD_EVENT_QUEUE_TCP_TX_SO_CON       (4u)    /*!< Queue for socket connection with TCP Tx. */
# define SOAD_EVENT_QUEUE_TP_TX_SO_CON        (5u)    /*!< Queue for socket connection with TP Tx PDU. */
# define SOAD_EVENT_QUEUE_TP_RX_SO_CON        (6u)    /*!< Queue for socket connection with TP Rx PDU. */
# define SOAD_EVENT_QUEUE_SO_CON_STATE        (7u)    /*!< Queue for socket connection (state) */

/*! EventQueue flag type used to indicate if a handle is already in list. */
typedef uint8                                 SoAd_EventQueueFlagType;

/*! Bit pattern type used to define the specific bit pattern of an EventQueue. */
typedef uint8                                           SoAd_EventQueueBitPatternType;
/*! Queue bit pattern for module internal socket index. */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_TCPIP_SOCKETS     0x01u
/*! Queue bit pattern for local address. */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_LOCAL_ADDR        0x02u
/*! Queue bit pattern for socket connection with UDP IF Tx PDU. */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_IF_UDP_PDU_ROUTE  0x04u
/*! Queue bit pattern for socket connection with IF Tx RouteGrp. */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_IF_TX_ROUTE_GRP   0x08u
/*! Queue bit pattern for socket connection with TCP Tx. */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_TCP_TX_SO_CON     0x10u
/*! Queue bit pattern for socket connection with TP Tx PDU. */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_TP_TX_SO_CON      0x20u
/*! Queue bit pattern for socket connection with TP Rx PDU. */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_TP_RX_SO_CON      0x40u
/*! Queue bit pattern for socket connection (state) */
# define SOAD_EVENT_QUEUE_BIT_PATTERN_STATE_SO_CON      0x80u

/*! Type to describe the different timeout lists. */
typedef uint8                                 SoAd_TimeoutListEnumType;
# define SOAD_TIMEOUT_LIST_UDP_ALIVE          (0u)            /*!< List for UDP alive supervision timeout. */
# define SOAD_TIMEOUT_LIST_N_PDU              (1u)            /*!< List for nPdu timeout. */

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Socket identifier type for AUTOSAR Socket API. */
typedef TcpIp_SocketIdType                    SoAd_SocketIdType;
#  define SOAD_INV_SOCKET_ID                  TCPIP_INV_SOCKET_ID   /*!< Invalid socket identifier. */
# else
/*! Socket identifier type for BSD-like Socket API. */
typedef sint32                                SoAd_SocketIdType;
#  define SOAD_INV_SOCKET_ID                  (-1)                  /*!< Invalid socket identifier. */
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Socket event type defined for AUTOSAR Socket API. */
typedef TcpIp_EventType                       SoAd_EventType;
#  define SOAD_TCP_RESET                      (TCPIP_TCP_RESET)         /*!< TCP socket connection reset by remote. */
#  define SOAD_TCP_CLOSED                     (TCPIP_TCP_CLOSED)        /*!< TCP socket connection closed. */
#  define SOAD_TCP_FIN_RECEIVED               (TCPIP_TCP_FIN_RECEIVED)  /*!< TCP socket connection received a FIN. */
#  define SOAD_UDP_CLOSED                     (TCPIP_UDP_CLOSED)        /*!< UDP socket closed. */
# else
/*! Socket event type defined for BSD-like Socket API. */
typedef uint8                                 SoAd_EventType;
#  define SOAD_TCP_RESET                      (1u)       /*!< TCP socket connection reset by remote entity. */
#  define SOAD_TCP_CLOSED                     (2u)       /*!< TCP socket connection closed. */
#  define SOAD_TCP_FIN_RECEIVED               (3u)       /*!< TCP socket connection received a FIN. */
#  define SOAD_UDP_CLOSED                     (4u)       /*!< UDP socket closed. */
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
typedef TcpIp_DhcpEventType                   SoAd_DhcpEventType;
#  define SOAD_DHCP_EVENT_TX_DISCOVER_SOLICIT (TCPIP_DHCP_EVENT_TX_DISCOVER_SOLICIT)
#  define SOAD_DHCP_EVENT_RX_OFFER_ADVERTISE  (TCPIP_DHCP_EVENT_RX_OFFER_ADVERTISE)
#  define SOAD_DHCP_EVENT_TX_REQUEST          (TCPIP_DHCP_EVENT_TX_REQUEST)
#  define SOAD_DHCP_EVENT_RX_ACK_REPLY        (TCPIP_DHCP_EVENT_RX_ACK_REPLY)
#  define SOAD_DHCP_EVENT_TX_V6_CONFIRM       (TCPIP_DHCP_EVENT_TX_V6_CONFIRM)
#  define SOAD_DHCP_EVENT_TX_V6_RENEW         (TCPIP_DHCP_EVENT_TX_V6_RENEW)
#  define SOAD_DHCP_EVENT_TX_V6_REBIND        (TCPIP_DHCP_EVENT_TX_V6_REBIND)
#  define SOAD_DHCP_EVENT_TX_V6_RELEASE       (TCPIP_DHCP_EVENT_TX_V6_RELEASE)
#  define SOAD_DHCP_EVENT_TX_V6_DECLINE       (TCPIP_DHCP_EVENT_TX_V6_DECLINE)
#  define SOAD_DHCP_EVENT_INVALID             (TCPIP_DHCP_EVENT_INVALID)
# else
typedef uint8                                 SoAd_DhcpEventType;
#  define SOAD_DHCP_EVENT_TX_DISCOVER_SOLICIT (0u)
#  define SOAD_DHCP_EVENT_RX_OFFER_ADVERTISE  (1u)
#  define SOAD_DHCP_EVENT_TX_REQUEST          (2u)
#  define SOAD_DHCP_EVENT_RX_ACK_REPLY        (3u)
#  define SOAD_DHCP_EVENT_TX_V6_CONFIRM       (4u)
#  define SOAD_DHCP_EVENT_TX_V6_RENEW         (5u)
#  define SOAD_DHCP_EVENT_TX_V6_REBIND        (6u)
#  define SOAD_DHCP_EVENT_TX_V6_RELEASE       (7u)
#  define SOAD_DHCP_EVENT_TX_V6_DECLINE       (8u)
#  define SOAD_DHCP_EVENT_INVALID             (255u)
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/*! Socket sate type. */
typedef uint8                                 SoAd_SockStateType;
# define SOAD_SOCK_STATE_ESTABLISHED          (0u)      /*!< Socket state established. */
# define SOAD_SOCK_STATE_CONNECT              (1u)      /*!< Socket state connecting to remote entity. */
# define SOAD_SOCK_STATE_LISTEN               (2u)      /*!< Socket state listen for incoming connections. */
# define SOAD_SOCK_STATE_CLOSING              (3u)      /*!< Socket state closing. */
# define SOAD_SOCK_STATE_CLOSED               (4u)      /*!< Socket state closed. */

/*! Socket connection identifier type. */
typedef uint16                                SoAd_SoConIdType;
# define SOAD_INV_SO_CON_ID                   (65535u)
/*! Invalid value for socket connection identifier type. */

/*! Socket connection mode type. */
typedef uint8                                 SoAd_SoConModeType;
# define SOAD_SOCON_ONLINE                    (0u)      /*!< Socket connection mode online. */
# define SOAD_SOCON_RECONNECT                 (1u)      /*!< Socket connection mode reconnect. */
# define SOAD_SOCON_OFFLINE                   (2u)      /*!< Socket connection mode offline. */

/*! Socket connection close mode type. */
typedef uint8                                 SoAd_SoConCloseModeType;
/*! Indicates that no close is requested for a socket connection. */
# define SOAD_CLOSE_NONE                      (0u)
/*! Indicates that a socket connection is requested to be closed by a socket close event and reconnect is required. */
# define SOAD_CLOSE_SOCKET_RECONNECT          (1u)
/*! Indicates that a socket connection is requested to be closed by a socket close event. */
# define SOAD_CLOSE_SOCKET                    (2u)
/*! Indicates that a socket connection is requested to be closed and set to reconnect. */
# define SOAD_CLOSE_RECONNECT                 (3u)
/*! Indicates that a socket connection is requested to be closed and set to offline by service call. */
# define SOAD_CLOSE_OFFLINE                   (4u)
/*! Indicates that a socket connection is requested to be closed and set to offline in case of any error. */
# define SOAD_CLOSE_OFFLINE_RESET             (5u)

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! IP address state type defined for AUTOSAR Socket API. */
typedef TcpIp_IpAddrStateType                 SoAd_IpAddrStateType;
#  define SOAD_IPADDR_STATE_ASSIGNED          (TCPIP_IPADDR_STATE_ASSIGNED)   /*!< IP address is assigned. */
#  define SOAD_IPADDR_STATE_ONHOLD            (TCPIP_IPADDR_STATE_ONHOLD)     /*!< IP address is not available. */
#  define SOAD_IPADDR_STATE_UNASSIGNED        (TCPIP_IPADDR_STATE_UNASSIGNED) /*!< IP address is unassigned. */
# else
/*! IP address state type defined for BSD-like Socket API. */
typedef uint8                                 SoAd_IpAddrStateType;
#  define SOAD_IPADDR_STATE_ASSIGNED          (0u)     /*!< IP address is assigned. */
#  define SOAD_IPADDR_STATE_ONHOLD            (1u)     /*!< IP address is not (yet) available. */
#  define SOAD_IPADDR_STATE_UNASSIGNED        (2u)     /*!< IP address is unassigned. */
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/*! IPv4 IP address type. */
typedef IpBase_AddrInType                     SoAd_IpAddrInetType;

/*! IPv6 IP address type. */
typedef IpBase_AddrIn6Type                    SoAd_IpAddrInet6Type;

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Socket domain type defined for AUTOSAR Socket API. */
typedef TcpIp_DomainType                      SoAd_DomainType;
#  define SOAD_AF_INET                        (TCPIP_AF_INET)           /*!< Domain type for IPv4. */
#  define SOAD_AF_INET6                       (TCPIP_AF_INET6)          /*!< Domain type for IPv6. */
#  define SOAD_AF_INVALID                     (TCPIP_AF_UNDEFINED)      /*!< Invalid domain type. */
# else
/*! Socket domain type defined for BSD-like Socket API. */
typedef uint16                                SoAd_DomainType;
#  define SOAD_AF_INET                        (0x02u)                   /*!< Domain type for IPv4. */
#  define SOAD_AF_INET6                       (0x1Cu)                   /*!< Domain type for IPv6. */
#  define SOAD_AF_INVALID                     (0x00u)                   /*!< Invalid domain type. */
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/*! IP address type for BSD-like Socket API. */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Generic socket address type for AUTOSAR Socket API. */
typedef TcpIp_SockAddrType                    SoAd_SockAddrType;
/*! IPv4 socket address type for AUTOSAR Socket API. */
typedef TcpIp_SockAddrInetType                SoAd_SockAddrInetType;
/*! IPv6 socket address type for AUTOSAR Socket API. */
typedef TcpIp_SockAddrInet6Type               SoAd_SockAddrInet6Type;
# else
/*! Generic socket address type for BSD-like Socket API. */
typedef struct
{
  SoAd_DomainType                             domain;     /*!< Domain type (IPv4/IPv6). */
} SoAd_SockAddrType;

/*! IPv4 socket address type for BSD-like Socket API. */
typedef struct
{
  SoAd_DomainType                             domain;    /*!< Domain type (IPv4/IPv6). */
  uint16                                      port;      /*!< Port number. */
  uint32                                      addr[1];   /*!< IPv4 address. */
} SoAd_SockAddrInetType;

/*! IPv6 socket address type for BSD-like Socket API. */
typedef struct
{
  SoAd_DomainType                             domain;    /*!< Domain type (IPv4/IPv6). */
  uint16                                      port;      /*!< Port number. */
  uint32                                      addr[4];   /*!< IPv6 address. */
} SoAd_SockAddrInet6Type;

#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/*! Largest IP address struct in case of IPv6 for BSD-like Socket API in AUTOSAR format. */
#   define SoAd_IpAddrInetXType               SoAd_IpAddrInet6Type
/*! Largest IP address struct in case of IPv6 for BSD-like Socket API in BSD format. */
#   define sockaddr_inX                       sockaddr_in6
#  else
/*! Largest IP address struct in case of IPv4 only for BSD-like Socket API in AUTOSAR format. */
#   define SoAd_IpAddrInetXType               SoAd_IpAddrInetType
/*! Largest IP address struct in case of IPv4 only for BSD-like Socket API in BSD format. */
#   define sockaddr_inX                       sockaddr_in
#  endif /* SOAD_IPV6 == STD_ON */
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

# if ( SOAD_IPV6 == STD_ON )
/*! Largest IP address struct in case of IPv6 in AUTOSAR format. */
  typedef SoAd_SockAddrInet6Type              SoAd_SockAddrInetXType;
# else
/*! Largest IP address struct in case of IPv4 in AUTOSAR format. */
  typedef SoAd_SockAddrInetType               SoAd_SockAddrInetXType;
# endif /* SOAD_IPV6 == STD_ON */

/*! Type to indicate state (set, wildcard, not set) of remote address. */
typedef uint8                                 SoAd_RemAddrStateType;
                                                    /* --  NOT ANY SET */
# define SOAD_SOCON_IP_SET_PORT_SET           0x03u /* 00  00  00  11  */ /*!< IP address set, port set. */
# define SOAD_SOCON_IP_SET_PORT_ANY           0x06u /* 00  00  01  10  */ /*!< IP address set, port wildcard. */
# define SOAD_SOCON_IP_SET_PORT_NOT           0x12u /* 00  01  00  10  */ /*!< IP address set, port not set. */
# define SOAD_SOCON_IP_ANY_PORT_SET           0x09u /* 00  00  10  01  */ /*!< IP address wildcard, port set. */
# define SOAD_SOCON_IP_ANY_PORT_ANY           0x0Cu /* 00  00  11  00  */ /*!< IP address wildcard, port wildcard. */
# define SOAD_SOCON_IP_ANY_PORT_NOT           0x18u /* 00  01  10  00  */ /*!< IP address wildcard, port not set. */
# define SOAD_SOCON_IP_NOT_PORT_SET           0x21u /* 00  10  00  01  */ /*!< IP address not set, port set. */
# define SOAD_SOCON_IP_NOT_PORT_ANY           0x24u /* 00  10  01  00  */ /*!< IP address not set, port wildcard. */
# define SOAD_SOCON_IP_NOT_PORT_NOT           0x30u /* 00  11  00  00  */ /*!< IP address not set, port not set. */
# define SOAD_SOCON_MASK_IPADDR               0x2Au /* 00  10  10  10  */ /*!< Bit mask for IP address state. */
# define SOAD_SOCON_MASK_PORT                 0x15u /* 00  01  01  01  */ /*!< Bit mask for port state. */
# define SOAD_SOCON_MASK_SET                  0x03u /* 00  00  00  11  */ /*!< Bit mask for state set. */
# define SOAD_SOCON_MASK_ANY                  0x0Cu /* 00  00  11  00  */ /*!< Bit mask for state is wildcard. */
# define SOAD_SOCON_MASK_NOT                  0x30u /* 00  11  00  00  */ /*!< Bit mask for state not set. */

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Socket protocol type defined for AUTOSAR Socket API. */
typedef TcpIp_ProtocolType                    SoAd_ProtocolType;
#  define SOAD_IPPROTO_TCP                    (TCPIP_IPPROTO_TCP)       /*!< Protocol type for TCP. */
#  define SOAD_IPPROTO_UDP                    (TCPIP_IPPROTO_UDP)       /*!< Protocol type for UDP. */
# else
/*! Socket protocol type defined for BSD-like Socket API. */
typedef uint8                                 SoAd_ProtocolType;
#  define SOAD_IPPROTO_TCP                    (0x06u)                   /*!< Protocol type for TCP. */
#  define SOAD_IPPROTO_UDP                    (0x11u)                   /*!< Protocol type for UDP. */
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/*! Socket port type. */
typedef uint16                                SoAd_PortType;
# define SOAD_PORT_ANY                        (0x0000u)                 /*!< Any/wildcard value for port. */

/*! Best match algorithm priority. */
typedef uint8                                 SoAd_BestMatchPrioType;
# define SOAD_BEST_MATCH_IP_MATCH_PORT_MATCH  (4u)                      /*!< IP and port match. */
# define SOAD_BEST_MATCH_IP_MATCH_PORT_ANY    (3u)                      /*!< IP match and port wildcard. */
# define SOAD_BEST_MATCH_IP_ANY_PORT_MATCH    (2u)                      /*!< IP wildcard and port match. */
# define SOAD_BEST_MATCH_IP_ANY_PORT_ANY      (1u)                      /*!< IP and port wildcard. */
# define SOAD_BEST_MATCH_NONE                 (0u)                      /*!< No match. */

/*! TCP no delay type to indicate if enabled, disabled or not specified. */
typedef uint8                                 SoAd_TcpNoDelayType;
# define SOAD_TCP_NO_DELAY_ENABLED            (0u)                      /*!< TCP no delay is enabled. */
# define SOAD_TCP_NO_DELAY_DISABLED           (1u)                      /*!< TCP no delay is disabled. */
# define SOAD_TCP_NO_DELAY_NOT_SPECIFIED      (2u)                      /*!< TCP no delay is not specified. */

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Parameter identifier type to change socket specific parameter for AUTOSAR Socket API. */
typedef TcpIp_ParamIdType                       SoAd_ParamIdType;
/*! TCP Rx buffer size. */
#  define SOAD_PARAMID_TCP_RXWND_MAX            (TCPIP_PARAMID_TCP_RXWND_MAX)
/*! Frame priority (VLAN). */
#  define SOAD_PARAMID_FRAMEPRIO                (TCPIP_PARAMID_FRAMEPRIO)
/*! Indicates if nagle algorithm enabled. */
#  define SOAD_PARAMID_TCP_NAGLE                (TCPIP_PARAMID_TCP_NAGLE)
/*! Indicates if keep alive enabled. */
#  define SOAD_PARAMID_TCP_KEEPALIVE            (TCPIP_PARAMID_TCP_KEEPALIVE)
/*! Time to live. */
#  define SOAD_PARAMID_TTL                      (TCPIP_PARAMID_TTL)
/*! Keep alive time. */
#  define SOAD_PARAMID_TCP_KEEPALIVE_TIME       (TCPIP_PARAMID_TCP_KEEPALIVE_TIME)
/*! Number of keep alive probes. */
#  define SOAD_PARAMID_TCP_KEEPALIVE_PROBES_MAX (TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX)
/*! Interval time of keep alive probes. */
#  define SOAD_PARAMID_TCP_KEEPALIVE_INTERVAL   (TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL)
/*! TCP Tx buffer size. */
#  define SOAD_PARAMID_TCP_TXWND_MAX            (TCPIP_PARAMID_V_TCP_TXBUFSIZE)
/*! UDP Tx request list size to store transmissions if TxConfirmation is required. */
#  define SOAD_PARAMID_UDP_TXREQLISTSIZE        (TCPIP_PARAMID_V_UDP_TXREQLISTSIZE)
/*! UDP Tx retry list size to store transmissions if address resolution (e.g. ARP) is not yet finished. */
#  define SOAD_PARAMID_UDP_TXRETRYLISTSIZE      (TCPIP_PARAMID_V_UDP_TXRETRYLISTSIZE)
/*! Indicates if TCP shall be used. */
#  define SOAD_PARAMID_USE_TLS                  (TCPIP_PARAMID_V_USE_TLS)
/*! TLS Tx buffer size. */
#  define SOAD_PARAMID_TLS_TXBUFSIZE            (TCPIP_PARAMID_V_TLS_TXBUFSIZE)
/*! TLS Rx buffer size. */
#  define SOAD_PARAMID_TLS_RXBUFSIZE            (TCPIP_PARAMID_V_TLS_RXBUFSIZE)
# else
/*! Parameter identifier type to change socket specific parameter for BSD-like Socket API. */
typedef uint8                                   SoAd_ParamIdType;
/*! TCP Rx buffer size. */
#  define SOAD_PARAMID_TCP_RXWND_MAX            (0u)
/*! TCP Tx buffer size. */
#  define SOAD_PARAMID_TCP_TXWND_MAX            (1u)
/*! UDP Tx request list size to store transmissions if TxConfirmation is required. */
#  define SOAD_PARAMID_UDP_TXREQLISTSIZE        (255u)
/*! UDP Tx retry list size to store transmissions if address resolution (e.g. ARP) is not yet finished. */
#  define SOAD_PARAMID_UDP_TXRETRYLISTSIZE      (255u)
/*! Indicates if TCP shall be used. */
#  define SOAD_PARAMID_USE_TLS                  (255u)
/*! TLS Tx buffer size. */
#  define SOAD_PARAMID_TLS_TXBUFSIZE            (255u)
/*! TLS Rx buffer size. */
#  define SOAD_PARAMID_TLS_RXBUFSIZE            (255u)
/*! Indicates if keep alive enabled. */
#  define SOAD_PARAMID_TCP_KEEPALIVE            (2u)
/*! Keep alive time. */
#  define SOAD_PARAMID_TCP_KEEPALIVE_TIME       (3u)
/*! Number of keep alive probes. */
#  define SOAD_PARAMID_TCP_KEEPALIVE_PROBES_MAX (4u)
/*! Interval time of keep alive probes. */
#  define SOAD_PARAMID_TCP_KEEPALIVE_INTERVAL   (5u)
/*! Indicates if nagle algorithm enabled. */
#  define SOAD_PARAMID_TCP_NAGLE                (6u)
/*! Frame priority (VLAN). */
#  define SOAD_PARAMID_FRAMEPRIO                (7u)
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
/*! TcpIp stack specific parameter used by SoAd to set parameter which has to be set for a specific stack. */
# define SOAD_PARAMID_STACK_SPECIFIC            (254u)

/*! Indicates if local address is unicast or multicast. */
typedef uint8                                 SoAd_AddressTypeType;
# define SOAD_ADDRESS_TYPE_UNICAST            (0u)      /*!< Unicast local address. */
# define SOAD_ADDRESS_TYPE_MULTICAST          (1u)      /*!< Multicast local address. */

/*! Indicates if local address assignment is triggered manually by user or automatically. */
typedef uint8                                 SoAd_AssignTriggerType;
# define SOAD_ASSIGN_TRIGGER_AUTOMATIC        (0u)      /*!< Local address assignment triggered automatically. */
# define SOAD_ASSIGN_TRIGGER_MANUAL           (1u)      /*!< Local address assignment triggered manually. */

/*! Local IP address request state. */
typedef uint8                                 SoAd_LocalIpAddrReqStateType;
# define SOAD_LOCAL_IP_ADDR_REQ_STATE_NONE    (0u)      /*!< IP address has no requests. */
# define SOAD_LOCAL_IP_ADDR_REQ_STATE_REQUEST (1u)      /*!< IP address requested. */
# define SOAD_LOCAL_IP_ADDR_REQ_STATE_RELEASE (2u)      /*!< IP address requested to release. */

/*! Any/wildcard value for IPv4 address. */
# define SOAD_IPADDR_ANY                      (0x00000000u)
/*! Any/wildcard value for IPv6 address. */
# define SOAD_IP6ADDR_ANY                     (0x00000000u)

/*! Prefix of multicast address for IPv4. */
# define SOAD_IPV4_MULTICAST_PREFIX           (0x000000E0U)
/*! Prefix mask of multicast address for IPv4. */
# define SOAD_IPV4_MULTICAST_PREFIX_MASK      (0x000000F0U)
/*! Prefix of multicast address for IPv6. */
# define SOAD_IPV6_MULTICAST_PREFIX           (0x000000FFU)
/*! Prefix mask of multicast address for IPv6. */
# define SOAD_IPV6_MULTICAST_PREFIX_MASK      (0x000000FFU)

/*! PDU header identifier type. */
typedef uint32                                SoAd_PduHdrIdType;
/*! PDU header length type. */
typedef uint32                                SoAd_PduHdrLenType;
/*! Invalid value for PDU header identifier. */
# define SOAD_INV_PDU_HDR_ID                  (0xFFFFFFFFu)
/*! PDU header size. */
# define SOAD_PDU_HDR_SIZE                    (8u)
/*! PDU header identifier size. */
# define SOAD_PDU_HDR_ID_SIZE                 (4u)
/*! PDU header length size. */
# define SOAD_PDU_HDR_LEN_SIZE                (4u)

/*! NPdu UDP Tx return type used in nPdu related functions to add elements to buffer or queue. */
typedef uint8                                 SoAd_NPduReturnType;
# define SOAD_NPDU_OK                         (0u)      /*!< Added or updated element. */
# define SOAD_NPDU_OVFL_NEW                   (1u)      /*!< New PDU does not fit into nPdu. */
# define SOAD_NPDU_OVFL_UPDATE                (2u)      /*!< Updated PDU does not fit into nPdu. */
# define SOAD_NPDU_NOT_OK                     (3u)      /*!< Did not add or update nPdu. */

/*! Routing group identifier type . */
typedef uint16                                SoAd_RoutingGroupIdType;
# define SOAD_INV_ROUT_GRP_ID                 (65535u)

/*! Upper layer type. */
typedef uint8                                 SoAd_UpperLayerApiType;
# define SOAD_UL_API_TP                       (1u)      /*!< Upper layer API is TP. */
# define SOAD_UL_API_IF                       (0u)      /*!< Upper layer API is IF. */

/*! Trigger mode type for UDP Tx PDUs. */
typedef uint8                                 SoAd_TxUdpTriggerModeType;
# define SOAD_TX_UDP_TRIGGER_ALWAYS           (0u)      /*!< Triggers transmission with transmit request. */
# define SOAD_TX_UDP_TRIGGER_NEVER            (1u)      /*!< Does not trigger transmission with transmit request. */
# define SOAD_TX_UDP_TRIGGER_NONE             (2u)      /*!< No trigger mode configured. */

/*! Trigger transmit mode type for IF PDUs. */
typedef uint8                                 SoAd_IfTriggerTransmitModeType;
# define SOAD_IF_TRIGGER_TRANSMIT_MODE_SINGLE (0u)      /*!< Trigger transmit must be called only once. */
# define SOAD_IF_TRIGGER_TRANSMIT_MODE_MULTI  (1u)      /*!< Trigger transmit can be called multiple times. */
# define SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE   (2u)      /*!< No trigger transmit configured. */

/*! Socket connection mode filter type used in best match algorithm. */
typedef uint8                                 SoAd_SoConModeFilterType;
# define SOAD_SOCON_FILTER_DISABLED           (0u)      /*!< No filter active. */
# define SOAD_SOCON_FILTER_ON_OFF             (1u)      /*!< Consider online or offline only. */

/*! DHCP hostname option for IPv4. */
# define SOAD_DHCP_OPT_V4_HOSTNAME            (81u)
/*! DHCP hostname option for IPv6. */
# define SOAD_DHCP_OPT_V6_HOSTNAME            (39u)

/* TcpIp IP address assignment */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Parameter identifier type to change socket specific parameter for AUTOSAR Socket API. */
typedef TcpIp_IpAddrAssignmentType              SoAd_IpAddrAssignmentType;
/*! Static IP address. */
#  define SOAD_IPADDR_ASSIGNMENT_STATIC         (TCPIP_IPADDR_ASSIGNMENT_STATIC)
/*! Link local IP address with parameters for DoIP use-case. */
#  define SOAD_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP (TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP)
/*! DHCP IP address. */
#  define SOAD_IPADDR_ASSIGNMENT_DHCP           (TCPIP_IPADDR_ASSIGNMENT_DHCP)
/*! Link local IP address. */
#  define SOAD_IPADDR_ASSIGNMENT_LINKLOCAL      (TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL)
/*! Dynamic configured IPv6 address by Router Advertisement. */
#  define SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER    (TCPIP_IPADDR_ASSIGNMENT_IPV6_ROUTER)
# else
/*! Parameter identifier type to change socket specific parameter for BSD-like Socket API. */
typedef uint8                                   SoAd_IpAddrAssignmentType;
/*! Static IP address. */
#  define SOAD_IPADDR_ASSIGNMENT_STATIC         (1u)
/*! Link local IP address with parameters for DoIP use-case. */
#  define SOAD_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP (2u)
/*! DHCP IP address. */
#  define SOAD_IPADDR_ASSIGNMENT_DHCP           (3u)
/*! Link local IP address. */
#  define SOAD_IPADDR_ASSIGNMENT_LINKLOCAL      (4u)
/*! Dynamic configured IPv6 address by Router Advertisement. */
#  define SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER    (5u)
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/*! Pointer to constant IP address. */
typedef P2CONST(uint32, AUTOMATIC, SOAD_CONST)  SoAd_IpAddrConstPtrType;

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/*! Local address identifier type for AUTOSAR Socket API. */
typedef TcpIp_LocalAddrIdType                   SoAd_LocalAddrIdType;
# else
/*! Local address identifier type for BSD-like Socket API. */
typedef uint8                                   SoAd_LocalAddrIdType;
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/*! Measure counter max value. */
# define SOAD_MEASURE_COUNTER_MAX_VALUE         65535u

/*! Index to select specific measurement data. */
typedef uint8 SoAd_MeasurementIdxType;
# define SOAD_MEAS_DROP_TCP                     0x01u
# define SOAD_MEAS_DROP_UDP                     0x02u
# define SOAD_MEAS_DROP_TCP_CONNECTION          0x80u
# define SOAD_MEAS_DROP_UDP_FRAME               0x81u
# define SOAD_MEAS_ALL                          0xFFu

typedef P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) SoAd_DataPtrType;

/*! Function pointer to <Up>_[SoAd][If]RxIndication. */
typedef P2FUNC(void, SOAD_CODE, SoAd_IfRxIndicationCbkType) (
  PduIdType RxPduId,
  CONSTP2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr);

/*! Function pointer to <Up>_[SoAd][Tp]StartOfReception. */
typedef P2FUNC(BufReq_ReturnType, SOAD_CODE, SoAd_TpStartOfReceptionCbkType) (
  PduIdType RxPduId,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) info,
  PduLengthType TpSduLength,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) bufferSizePtr);

/*! Function pointer to <Up>_[SoAd][Tp]StartOfReception with const data pointer. */
typedef P2FUNC(BufReq_ReturnType, SOAD_CODE, SoAd_TpStartOfReceptionConstCbkType) (
  PduIdType RxPduId,
  CONSTP2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) info,
  PduLengthType TpSduLength,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) bufferSizePtr);

/*! Function pointer to <Up>_[SoAd][Tp]CopyRxData. */
typedef P2FUNC(BufReq_ReturnType, SOAD_CODE, SoAd_TpCopyRxDataCbkType) (
  PduIdType id,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) info,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) bufferSizePtr);

/*! Function pointer to <Up>_[SoAd][Tp]CopyRxData with const data pointer. */
typedef P2FUNC(BufReq_ReturnType, SOAD_CODE, SoAd_TpCopyRxDataConstCbkType) (
  PduIdType id,
  CONSTP2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) info,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) bufferSizePtr);

/*! Function pointer to <Up>_[SoAd][Tp]RxIndication. */
typedef P2FUNC(void, SOAD_CODE, SoAd_TpRxIndicationCbkType) (
  PduIdType RxPduId,
  Std_ReturnType result);

/*! Function pointer to <Up>_[SoAd][If]TriggerTransmit. */
typedef P2FUNC(Std_ReturnType, SOAD_CODE, SoAd_IfTriggerTransmitCbkType) (
  PduIdType TxPduId,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr);

/*! Function pointer to <Up>_[SoAd][If]TxConfirmation. */
typedef P2FUNC(void, SOAD_CODE, SoAd_IfTxConfirmationCbkType) (
  PduIdType TxPduId);

/*! Function pointer to <Up>_[SoAd][Tp]CopyTxData. */
typedef P2FUNC(BufReq_ReturnType, SOAD_CODE, SoAd_TpCopyTxDataCbkType) (
  PduIdType id,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) info,
  CONSTP2VAR(RetryInfoType, AUTOMATIC, SOAD_APPL_DATA) retry,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) availableDataPtr);

/*! Function pointer to <Up>_[SoAd][Tp]CopyTxData with const data pointer. */
typedef P2FUNC(BufReq_ReturnType, SOAD_CODE, SoAd_TpCopyTxDataConstCbkType) (
  PduIdType id,
  CONSTP2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) info,
  CONSTP2VAR(RetryInfoType, AUTOMATIC, SOAD_APPL_DATA) retry,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) availableDataPtr);

/*! Function pointer to <Up>_[SoAd][Tp]TxConfirmation. */
typedef P2FUNC(void, SOAD_CODE, SoAd_TpTxConfirmationCbkType) (
  PduIdType TxPduId,
  Std_ReturnType result);

/*! Function pointer to <Up>_SoConModeChg. */
typedef P2FUNC(void, SOAD_CODE, SoAd_SoConModeChgCbkType) (
  SoAd_SoConIdType SoConId,
  SoAd_SoConModeType Mode);

/*! Function pointer to <Up>_LocalIpAddrAssignmentChg. */
typedef P2FUNC(void, SOAD_CODE, SoAd_LocalIpAddrAssignmentChgCbkType) (
  SoAd_SoConIdType SoConId,
  SoAd_IpAddrStateType State);

/*! Function pointer to <Up>_ShutdownFinished. */
typedef P2FUNC(void, SOAD_CODE, SoAd_ShutdownFinishedCbkType) (void);

/*! Function pointer to <Up_TcpTlsSocketCreatedNotification>. */
typedef P2FUNC(void, SOAD_CODE, SoAd_TcpTlsSocketCreatedNotificationCbkType) (
  SoAd_SoConIdType SoConId,
  SoAd_SocketIdType SocketId);

/*! Function pointer to <Up_VerifyRxPdu>. */
typedef P2FUNC(Std_ReturnType, SOAD_CODE, SoAd_VerifyRxPduCbkType) (
  CONSTP2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) LocalAddrPtr,
  CONSTP2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr,
  SoAd_PduHdrIdType PduHdrId,
  CONSTP2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr);

/*! Function pointer to <Up_SocketReportError>. */
typedef P2FUNC(void, SOAD_CODE, SoAd_SocketReportErrorCbkType) (
  uint8 ApiId,
  uint8 BsdApiId,
  sint32 Param,
  sint32 Value1,
  sint32 Value2,
  sint32 Errno);

/*! Function pointer to <Up>_DhcpEvent. */
typedef P2FUNC(void, SOAD_CODE, SoAd_DhcpEventCbkType) (
  SoAd_LocalAddrIdType IpAddrId,
  SoAd_DhcpEventType Event);

#endif /* !defined(SOAD_TYPES_H) */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Types.h
 *********************************************************************************************************************/
