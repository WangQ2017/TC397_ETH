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
 *         \file  TcpIp_Priv.h
 *        \brief  Implementation of TcpIp Module - Internal Functions
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined TCPIP_PRIV_H
# define TCPIP_PRIV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TcpIp_Priv_Types.h"

#include "TcpIp_Cfg.h"
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#include "TcpIp_Lcfg.h"
#include "SchM_TcpIp.h"

#include "EthIf.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define TCPIP_SOCK_CONN_NONE                          0u
#define TCPIP_SOCK_CONN_ALLOCATED                     1u
#define TCPIP_SOCK_CONN_LISTEN_ENABLED                2u
#if(TCPIP_SUPPORT_TCP == STD_ON)
# define TCPIP_SOCK_CONN_ACTIVE                       3u  /* any TCP state other than CLOSED and LISTEN */
#endif

#define TCPIP_ACTIVE_STATE_OFFLINE                    0u  /* module is offline / not initialized */
#define TCPIP_ACTIVE_STATE_ONHOLDE                    1u  /* module is shutting down, all sockets are about to being closed */
#define TCPIP_ACTIVE_STATE_ONLINE                     2u  /* module is initialized and ready for communication (if an IP address is available) */

/* Ethernet frame types */
#define TCPIP_ETH_FRAME_TYPE_IPV4                     0x0800u
#define TCPIP_ETH_FRAME_TYPE_ARP                      0x0806u
#define TCPIP_ETH_FRAME_TYPE_IPV6                     0x86DDu

/* Private constants of the TCPIP */
#define TCPIP_TX_CONF_LEN_MAX                         0xFFFFU

#define TCPIP_CHECKSUM_UNSET                          0U

#if defined(TCPIP_VENABLE_CANOE_WRITE_STRING)                                                                           /* COV_TCPIP_CANOE_DEBUG */
/* Use user defined value. */
#else
# define TCPIP_VENABLE_CANOE_WRITE_STRING STD_OFF
#endif

#define TCPIP_API_ID_V_INTERNAL_FUNCTION              0xFFu

#define TCPIP_DHCPV4_MULTIPLE_CONFIG_SETS             STD_ON
#define TCPIP_DHCPV4_MULTIPLE_INSTANCES               STD_ON

#define TCPIP_TCP_HDR_SOURCE_PORT_OFFSET              0u
#define TCPIP_TCP_HDR_TARGET_PORT_OFFSET              2u
#define TCPIP_UDP_HDR_SOURCE_PORT_OFFSET              0u
#define TCPIP_UDP_HDR_TARGET_PORT_OFFSET              2u

#define IP_MAX_ETHIF_FRAME_PRIO                       7u
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */

#if (TCPIP_VENABLE_CANOE_WRITE_STRING == STD_ON)                                                                        /* COV_TCPIP_CANOE_DEBUG */
  #include "stdio.h"
  #define CANOE_WRITE_STRING(Txt)                 CANoeAPI_WriteString((Txt));
  #define CANOE_WRITE_STRING_1(Txt, P1)           \
    _snprintf(TcpIp_CanoeWriteStr, 256, Txt, P1); CANoeAPI_WriteString((TcpIp_CanoeWriteStr));
  #define CANOE_WRITE_STRING_2(Txt, P1, P2)       \
    _snprintf(TcpIp_CanoeWriteStr, 256, Txt, P1, P2); \
    CANoeAPI_WriteString((TcpIp_CanoeWriteStr));
  #define CANOE_WRITE_STRING_3(Txt, P1, P2, P3)   \
    _snprintf(TcpIp_CanoeWriteStr, 256, Txt, P1, P2, P3); \
    CANoeAPI_WriteString((TcpIp_CanoeWriteStr));
  #define CANOE_WRITE_STRING_4(Txt, P1, P2, P3, P4)   \
    _snprintf(TcpIp_CanoeWriteStr, 256, Txt, P1, P2, P3, P4); \
    CANoeAPI_WriteString((TcpIp_CanoeWriteStr));
#else
  #define CANOE_WRITE_STRING(txt)
  #define CANOE_WRITE_STRING_1(txt, p1)
  #define CANOE_WRITE_STRING_2(txt, p1, p2)
  #define CANOE_WRITE_STRING_3(txt, p1, p2, p3)
  #define CANOE_WRITE_STRING_4(txt, p1, p2, p3, p4)
#endif

#define TCPIP_VENTER_CRITICAL_SECTION() SchM_Enter_TcpIp_TCPIP_EXCLUSIVE_AREA_0()
#define TCPIP_VLEAVE_CRITICAL_SECTION() SchM_Exit_TcpIp_TCPIP_EXCLUSIVE_AREA_0()


#define TCPIP_COND_INIT                     ( TCPIP_STATE_INIT == TcpIp_State )  /* TCPIP_E_NOTINIT */  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */





#define TCPIP_SOCKET_ID_TO_IDX(SOCKET_ID)   ((TcpIp_SizeOfSocketDynType)(SOCKET_ID))
#define TCPIP_SOCKET_IDX_TO_ID(SOCKET_IDX)  ((TcpIp_SocketIdType)(SOCKET_IDX))

#define TCPIP_SOCKET_IDX_TO_UDP_IDX(SOCKET_IDX)   ((TcpIp_SizeOfSocketUdpDynType)(SOCKET_IDX))
#define TCPIP_UDP_IDX_TO_SOCKET_IDX(UDP_IDX)      ((TcpIp_SizeOfSocketDynType)(UDP_IDX))

#define TCPIP_SOCKET_IDX_TO_TCP_IDX(SOCKET_IDX)  ((TcpIp_SizeOfSocketTcpDynType)((SOCKET_IDX) - TcpIp_GetSizeOfSocketUdpDyn()))
#define TCPIP_TCP_IDX_TO_SOCKET_IDX(TCP_IDX)     ((TcpIp_SizeOfSocketDynType)((TCP_IDX)       + TcpIp_GetSizeOfSocketUdpDyn()))

#define TCPIP_SOCKET_IDX_IS_TCP(SOCKET_IDX)      ((SOCKET_IDX) >= TcpIp_GetSizeOfSocketUdpDyn())  /*! Checks if a valid SocketId references a TCP socket. (Use TCPIP_COND_VALID_SOCKET_ID() in order to check if the socket ID is valid at all.) */
#define TCPIP_SOCKET_IDX_IS_UDP(SOCKET_IDX)      ((SOCKET_IDX) <  TcpIp_GetSizeOfSocketUdpDyn())  /*! Checks if a valid SocketId references a UDP socket.  */

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/* */
#else
# define TcpIp_GetSizeOfLocalAddrV4() 0
#endif

/*
Datatype                                Variable Name      Description
uint8                                   CtrlIdx            EthIf Controller Index (AUTOSAR)
TcpIp_SizeOfIpV4CtrlType                IpV4CtrlIdx        IpV4/IpV6 controller index
TcpIp_SizeOfIpV6CtrlType                IpV6CtrlIdx        IpV4/IpV6 controller index

TcpIp_LocalAddrIdType                   LocalAddrId        Local IP Address Id (AUTOSAR)
TcpIp_SizeOfLocalAddrType               LocalAddrIdx       All IPv4 addresses + All IPv6 addresses

TcpIp_SizeOfLocalAddrV4Type             LocalAddrV4Idx     All IPv4 addresses
TcpIp_SizeOfUnicastAddrV4Type           SrcAddrIdx         All Unicast/Source IPv4 addresses
TcpIp_SizeOfMulticastAddrV4Type         McAddrIdx          All Multicast IPv4 addresses
TcpIp_SizeOfDefaultUnicastAddrV4Type    DefaultUcAddrIdx   All Unicast IPv4 address default values
TcpIp_SizeOfDefaultMulticastAddrV4Type  DefaultMcAddrIdx   All Multicast IPv4 address default values

TcpIp_SizeOfLocalAddrV6Type             LocalAddrV6Idx     All IPv6 addresses
TcpIp_SizeOfIpV6SourceAddressType       SrcAddrIdx         All Unicast/Source IPv6 addresses
TcpIp_SizeOfIpV6MulticastAddrType       McAddrIdx          All Multicast IPv6 addresses
TcpIp_SizeOfDefaultAddrV6Type           DefAddrIdx         All IPv6 address default values

TcpIp_SocketIdType                      SocketId           Socket Id (AUTOSAR)
TcpIp_SizeOfSocketType                  SocketIdx          All UDP sockets + All TCP sockets
TcpIp_SizeOfSocketTcpType               SocketTcpIdx       All TCP sockets
TcpIp_SizeOfSocketUdpType               SocketUdpIdx       All UDP sockets


AUTOSAR:                CtrlIdx                       LocalAddrId                      SocketId
                           |                               |                               |
                           |                               |                               |
TcpIp:                     |                          LocalAddrIdx                     SocketIdx
                     ______|______                  _______|_______                 _______|______
                    |             |                |               |               |              |
IpVX/Tcp/Udp:  IpV4CtrlIdx   IpV6CtrlIdx    LocalAddrV4Idx   LocalAddrV6Idx   SocketTcpIdx   SocketUdpIdx


Name           | Valid Check                                         | Conversion to (and back)                            | Target
=====================================================================|=====================================================|==================
Controller:
----------------------------------------------------------------------------------------------------------------------------------------------
CtrlIdx        | TcpIp_IsIpV4CtrlUsedOfEthIfCtrl                     | TcpIp_GetIpV4CtrlIdxOfEthIfCtrl                     | IpV4CtrlIdx
               |                                                     | TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl                     |
----------------------------------------------------------------------------------------------------------------------------------------------
CtrlIdx        | TcpIp_IsIpV6CtrlUsedOfEthIfCtrl                     | TcpIp_GetIpV6CtrlIdxOfEthIfCtrl                     | IpV6CtrlIdx
               |                                                     | TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl                     |
----------------------------------------------------------------------------------------------------------------------------------------------

IP Addresses:
----------------------------------------------------------------------------------------------------------------------------------------------
LocalAddrId    | TCPIP_LOCAL_ADDR_ID_IS_VALID                        | TCPIP_LOCAL_ADDR_ID_TO_IDX                          | LocalAddrIdx
               |                                                     | TCPIP_LOCAL_ADDR_IDX_TO_ID                          |
----------------------------------------------------------------------------------------------------------------------------------------------


IPv4 Addresses:
----------------------------------------------------------------------------------------------------------------------------------------------
LocalAddrIdx   | TCPIP_LOCAL_ADDR_IDX_IS_IPV4                        | TCPIP_LOCAL_ADDR_IDX_TO_IPV4                        | LocalAddrV4Idx
               |                                                     | TCPIP_IPV4_TO_LOCAL_ADDR_IDX                        |
----------------------------------------------------------------------------------------------------------------------------------------------
LocalAddrV4Idx | TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4              | TcpIp_GetUnicastAddrV4IdxOfLocalAddrV4              | SrcAddrIdx
               |                                                     | X                                                   |
----------------------------------------------------------------------------------------------------------------------------------------------
LocalAddrV4Idx | TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4            | TcpIp_GetMulticastAddrV4IdxOfLocalAddrV4            | McAddrIdx
               |                                                     | TcpIp_GetLocalAddrV4IdxOfMulticastAddrV4            |
----------------------------------------------------------------------------------------------------------------------------------------------
SrcAddrIdx     | TcpIp_IsDefaultUnicastAddrV4UsedOfUnicastAddrV4     | TcpIp_GetDefaultUnicastAddrV4IdxOfUnicastAddrV4     | DefaultUcAddrIdx
               |                                                     | X                                                   |
----------------------------------------------------------------------------------------------------------------------------------------------
McAddrIdx      | TcpIp_IsDefaultMulticastAddrV4UsedOfMulticastAddrV4 | TcpIp_GetDefaultMulticastAddrV4IdxOfMulticastAddrV4 | DefaultMcAddrIdx
               |                                                     | X                                                   |
----------------------------------------------------------------------------------------------------------------------------------------------

IPv6 Addresses:
----------------------------------------------------------------------------------------------------------------------------------------------
LocalAddrIdx   | TCPIP_LOCAL_ADDR_IDX_IS_IPV6                        | TCPIP_LOCAL_ADDR_IDX_TO_IPV6                        | LocalAddrV6Idx
               |                                                     | TCPIP_IPV6_TO_LOCAL_ADDR_IDX                        |
----------------------------------------------------------------------------------------------------------------------------------------------
LocalAddrV6Idx | TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6          | TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6          | SrcAddrIdx
               |                                                     | TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress          |
----------------------------------------------------------------------------------------------------------------------------------------------
LocalAddrV6Idx | TcpIp_IsIpV6MulticastAddrUsedOfLocalAddrV6          | TcpIp_GetIpV6MulticastAddrIdxOfLocalAddrV6          | McAddrIdx
               |                                                     | TcpIp_GetLocalAddrV6IdxOfIpV6MulticastAddr          |
----------------------------------------------------------------------------------------------------------------------------------------------
SrcAddrIdx     | TcpIp_IsDefaultAddrV6UsedOfIpV6SourceAddress        | TcpIp_GetDefaultAddrV6IdxOfIpV6SourceAddress        | DefAddrIdx
               |                                                     | X                                                   |
----------------------------------------------------------------------------------------------------------------------------------------------
McAddrIdx      | TcpIp_IsDefaultAddrV6UsedOfIpV6MulticastAddr        | TcpIp_GetDefaultAddrV6IdxOfIpV6MulticastAddr        | DefAddrIdx
               |                                                     | X
----------------------------------------------------------------------------------------------------------------------------------------------

Sockets:
----------------------------------------------------------------------------------------------------------------------------------------------
SocketId       | TCPIP_SOCKET_ID_IS_VALID                            | TCPIP_SOCKET_ID_TO_IDX                              | SocketIdx
               |                                                     | TCPIP_SOCKET_IDX_TO_ID                              |
----------------------------------------------------------------------------------------------------------------------------------------------
SocketIdx      | TCPIP_SOCKET_IDX_IS_TCP                             | TCPIP_SOCKET_IDX_TO_TCP_IDX                         | SocketTcpIdx
               |                                                     | TCPIP_TCP_IDX_TO_SOCKET_IDX                         |
----------------------------------------------------------------------------------------------------------------------------------------------
SocketIdx      | TCPIP_SOCKET_IDX_IS_UDP                             | TCPIP_SOCKET_IDX_TO_UDP_IDX                         | SocketUdpIdx
               |                                                     | TCPIP_UDP_IDX_TO_SOCKET_IDX                         |
----------------------------------------------------------------------------------------------------------------------------------------------
*/

#define TCPIP_LOCAL_ADDR_ID_TO_IDX(LOCAL_ADDR_ID)           (LOCAL_ADDR_ID)
#define TCPIP_LOCAL_ADDR_IDX_TO_ID(LOCAL_ADDR_IDX)          ((TcpIp_SizeOfLocalAddrType)(LOCAL_ADDR_IDX))
#define TCPIP_LOCAL_ADDR_ID_IS_VALID(LOCAL_ADDR_ID)         ((LOCAL_ADDR_ID) < TCPIP_LOCAL_ADDR_IDX_COUNT)
#define TCPIP_LOCAL_ADDR_ID_IS_VALID_OR_ANY(LOCAL_ADDR_ID)  (TCPIP_LOCAL_ADDR_ID_IS_VALID(LOCAL_ADDR_ID) || ((LOCAL_ADDR_ID) == TCPIP_LOCALADDRID_ANY))

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
/* IPv4 and IPv6 */
#  define TCPIP_LOCAL_ADDR_IDX_COUNT                         ((TcpIp_SizeOfLocalAddrType)((TcpIp_GetSizeOfLocalAddrV4() + TcpIp_GetSizeOfLocalAddrV6())))
#  define TCPIP_LOCAL_ADDR_IDX_IS_IPV4(LOCAL_ADDR_IDX)       ((LOCAL_ADDR_IDX) <  TcpIp_GetSizeOfLocalAddrV4())  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define TCPIP_LOCAL_ADDR_IDX_IS_IPV6(LOCAL_ADDR_IDX)       (((LOCAL_ADDR_IDX) >= TcpIp_GetSizeOfLocalAddrV4()) && ((LOCAL_ADDR_IDX) < (TcpIp_LocalAddrIterType)(TcpIp_GetSizeOfLocalAddrV4() + TcpIp_GetSizeOfLocalAddrV6())))
#  define TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LOCAL_ADDR_IDX)       ((TcpIp_SizeOfLocalAddrType)((TCPIP_LOCAL_ADDR_IDX_IS_IPV4(LOCAL_ADDR_IDX) ? (LOCAL_ADDR_IDX) : ((LOCAL_ADDR_IDX) - TcpIp_GetSizeOfLocalAddrV4()))))
#  define TCPIP_LOCAL_ADDR_IDX_TO_IPV4(LOCAL_ADDR_IDX)       (LOCAL_ADDR_IDX)
#  define TCPIP_LOCAL_ADDR_IDX_TO_IPV6(LOCAL_ADDR_IDX)       ((TcpIp_SizeOfLocalAddrV6Type)((LOCAL_ADDR_IDX) - TcpIp_GetSizeOfLocalAddrV4()))
#  define TCPIP_IPV4_TO_LOCAL_ADDR_IDX(IP_ADDR_IDX)          (IP_ADDR_IDX)
#  define TCPIP_IPV6_TO_LOCAL_ADDR_IDX(IP_ADDR_IDX)          ((TcpIp_SizeOfLocalAddrType)((IP_ADDR_IDX) + TcpIp_GetSizeOfLocalAddrV4()))
#  define TCPIP_IS_ADDR_FAMILY_SUPPORTED(DOMAIN_TYPE) (((DOMAIN_TYPE) == TCPIP_AF_INET) || ((DOMAIN_TYPE) == TCPIP_AF_INET6))
# else
/* IPv4 only */
#  define TCPIP_LOCAL_ADDR_IDX_COUNT                         TcpIp_GetSizeOfLocalAddrV4()
#  define TCPIP_LOCAL_ADDR_IDX_IS_IPV4(LOCAL_ADDR_IDX)       ((LOCAL_ADDR_IDX) <  TcpIp_GetSizeOfLocalAddrV4())  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define TCPIP_LOCAL_ADDR_IDX_IS_IPV6(LOCAL_ADDR_IDX)       (TRUE  == FALSE)
#  define TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LOCAL_ADDR_IDX)       (LOCAL_ADDR_IDX)
#  define TCPIP_LOCAL_ADDR_IDX_TO_IPV4(LOCAL_ADDR_IDX)       (LOCAL_ADDR_IDX)
#  define TCPIP_IPV4_TO_LOCAL_ADDR_IDX(IP_ADDR_IDX)          (IP_ADDR_IDX)
#  define TCPIP_IS_ADDR_FAMILY_SUPPORTED(DOMAIN_TYPE) ((DOMAIN_TYPE) == TCPIP_AF_INET)
# endif
#else
/* IPv6 only */
# define TCPIP_LOCAL_ADDR_IDX_COUNT                         TcpIp_GetSizeOfLocalAddrV6()
# define TCPIP_LOCAL_ADDR_IDX_IS_IPV4(LOCAL_ADDR_IDX)       (TRUE == FALSE)
# define TCPIP_LOCAL_ADDR_IDX_IS_IPV6(LOCAL_ADDR_IDX)       (TRUE == TRUE)
# define TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LOCAL_ADDR_IDX)       (LOCAL_ADDR_IDX)
# define TCPIP_LOCAL_ADDR_IDX_TO_IPV6(LOCAL_ADDR_IDX)       (LOCAL_ADDR_IDX)
# define TCPIP_IPV6_TO_LOCAL_ADDR_IDX(IP_ADDR_IDX)          (IP_ADDR_IDX)
# define TCPIP_IS_ADDR_FAMILY_SUPPORTED(DOMAIN_TYPE) ((DOMAIN_TYPE) == TCPIP_AF_INET6)
#endif

#define TCPIP_SOCKET_IDX_INV                             TcpIp_GetSizeOfSocketDyn()
#define TCPIP_SOCKET_ID_IS_VALID(SOCKET_ID)              ((SOCKET_ID)  < TcpIp_GetSizeOfSocketDyn())

#define TCPIP_PORT_NOT_SET                               0x0000u
#define TCPIP_DYNAMIC_PORT_COUNT                         0x3FFFu
#define TCPIP_DYNAMIC_PORT_START                         0xC000u


#define TCPIP_V_IP_TRANSMIT_FLAG_TX_CONFIRMATION         1u
#define TCPIP_V_IP_TRANSMIT_FLAG_RETRY_ON_PHYS_ADDR_MISS 2u

/* TcpIp TxBuf */

#define TCPIP_DLIST_GET_NEXT(NodeIdx, DList) ((DList).DescPtr->NodePtr[(NodeIdx)].NextIdx)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define TCPIP_DLIST_GET_PREV(NodeIdx, DList) ((DList).DescPtr->NodePtr[(NodeIdx)].PrevIdx)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define TCPIP_DLIST_SET_NEXT(NodeIdx, DList) ((NodeIdx) = TCPIP_DLIST_GET_NEXT(NodeIdx, DList))  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define TCPIP_DLIST_SET_PREV(NodeIdx, DList) ((NodeIdx) = TCPIP_DLIST_GET_PREV(NodeIdx, DList))  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define TCPIP_DLIST_IS_EMPTY(DList)           (TCPIP_DLIST_END_IDX == (DList).FirstIdx)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define TCPIP_DLIST_END_IDX 0xFFu

/* TCP */

/* RAM array access macros: */

/* TxRstQueue */
#define TcpIp_Tcp_IncTxRstQueueIdx(Idx)  ((Idx) = (uint8)(((Idx) + 1u) % (TcpIp_GetSizeOfTcpResetQElement())))  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* RxBuffers */
#define TcpIp_Tcp_GetRxBuffersElemPtr(SocketTcpIdx, IndexInsideRxBuffer)  (TcpIp_GetAddrTcpRxBuffer(  \
                    TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx)) +  \
                    (IndexInsideRxBuffer)))  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Development Error Tracer */
#if ( TCPIP_DEV_ERROR_REPORT == STD_ON )
# define TcpIp_CheckDetErrorReturnVoid(CONDITION, API_ID, ERROR_CODE)           { if(!(CONDITION)) {    \
    (void)Det_ReportError( TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, (API_ID), (ERROR_CODE)); return; } }
# define TcpIp_CheckDetErrorReturnValue(CONDITION, API_ID, ERROR_CODE, RET_VAL)  { if(!(CONDITION)) {    \
    (void)Det_ReportError( TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, (API_ID), (ERROR_CODE)); return (RET_VAL); } }
# define TcpIp_CheckDetErrorContinue(CONDITION, API_ID, ERROR_CODE)           { if(!(CONDITION)) {    \
    (void)Det_ReportError( TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, (API_ID), (ERROR_CODE)); } }
# define TcpIp_CallDetReportError(API_ID, ERROR_CODE)  (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, (API_ID), (ERROR_CODE))
#else
# define TcpIp_CheckDetErrorReturnVoid(  CONDITION, API_ID, ERROR_CODE )
# define TcpIp_CheckDetErrorReturnValue( CONDITION, API_ID, ERROR_CODE, RET_VAL )
# define TcpIp_CheckDetErrorContinue(    CONDITION, API_ID, ERROR_CODE )
# define TcpIp_CallDetReportError(                  API_ID, ERROR_CODE )
#endif  /* TCPIP_DEV_ERROR_REPORT */

/* CHECK CONDITIONS to be used in ASSERT and DET macros: */

#define TCPIP_IPADDR_ASSIGNMENT_MAX_VALUE  TCPIP_IPADDR_ASSIGNMENT_IPV6_ROUTER

/* implementation limit: max message length is 64kB */
#define TCPIP_COND_LEN_MAX_UINT16(Len)      ( (uint32)(Len) <= (uint32)0xFFFFu )        /* TCPIP_E_INV_ARG */  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define TCPIP_COND_VALID_DOMAIN(Domain)      ( (IPBASE_AF_INET == (Domain)) || \
                                               (IPBASE_AF_INET6 == (Domain)))          /* TCPIP_E_INV_ARG */  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#if (TCPIP_SUPPORT_TCP == STD_ON)
#define TCPIP_COND_VALID_PROT(Prot)          ( (TCPIP_SOCK_PROT_UDP == (Prot)) || \
                                               (TCPIP_SOCK_PROT_TCP == (Prot)) )       /* TCPIP_E_INV_ARG */  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#else
#define TCPIP_COND_VALID_PROT(Prot)          ( TCPIP_SOCK_PROT_UDP == (Prot) )         /* TCPIP_E_INV_ARG */  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#define TCPIP_TCP_COND_VALID_TCPIDX(SocketTcpIdx)   (TcpIp_GetSizeOfSocketTcpDyn() > (SocketTcpIdx))  /* TCPIP_E_INV_SOCK_ID */  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define TCPIP_UNUSED_PARAMETER(Parameter) TCPIP_DUMMY_STATEMENT(Parameter)

#define TCPIP_ASSERT(CONDITION)                TCPIP_ASSERT_MSG(CONDITION, NULL_PTR)
#define TCPIP_ASSERT_UNREACHABLE()             TCPIP_ASSERT_UNREACHABLE_MSG("This statement must not be reached!")
#if defined(TCPIP_ASSERT_HANDLER)                                                                                       /* COV_TCPIP_CANOE_DEBUG */
# define TCPIP_ASSERT_MSG(CONDITION, MSG)                (void)TCPIP_ASSERT_HANDLER(CONDITION, MSG)
# define TCPIP_ASSERT_UNREACHABLE_MSG(MSG)               (void)TCPIP_ASSERT_HANDLER(FALSE, MSG)
#else
# define TCPIP_ASSERT_MSG(CONDITION, MSG)
# define TCPIP_ASSERT_UNREACHABLE_MSG(MSG)
#endif

#define TCPIP_CYCLES_PER_SECOND             (1000u / TCPIP_MAIN_FCT_PERIOD_MSEC)
#define TCPIP_MAX_SEC_IN_UINT32_CYCLE_VAR   (0xFFFFFFFFu / TCPIP_CYCLES_PER_SECOND)

/* UDP */
/* Configuration access (depending on configuration variant)*/

/* The following macros write unsigned integers into a linear buffer. (host byte order -> network byte order). */

# define TCPIP_PUT_UINT8(Buffer, Offset, Value)          ((Buffer)[(Offset)] = (Value))
# define TCPIP_PUT_UINT16(Buffer, Offset, Value)         TcpIp_WriteUInt16((Buffer), (Offset), (Value))
# define TCPIP_PUT_UINT32(Buffer, Offset, Value)         TcpIp_WriteUInt32((Buffer), (Offset), (Value))

/* The following macros write unsigned integers into a linear buffer without modyfiying the byte order. */

# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)                                                                                /* COV_TCPIP_BYTE_ORDER */
#  define TCPIP_PUT_UINT16_RAW(Buffer, Offset, Value)     TcpIp_WriteUInt16((Buffer), (Offset), (Value))
#  define TCPIP_PUT_UINT32_RAW(Buffer, Offset, Value)     TcpIp_WriteUInt32((Buffer), (Offset), (Value))
# else
#  define TCPIP_PUT_UINT16_RAW(Buffer, Offset, Value)     TcpIp_WriteUInt16Le((Buffer), (Offset), (Value))
#  define TCPIP_PUT_UINT32_RAW(Buffer, Offset, Value)     TcpIp_WriteUInt32Le((Buffer), (Offset), (Value))
# endif

/* The following macros read unsigned integers from a linear (buffer network byte order -> host byte order). */

# define TCPIP_GET_UINT8(Buffer, Offset)                                       ((uint8)(Buffer)[(Offset)])

# define TCPIP_GET_UINT16(Buffer, Offset)                                     ((uint16)(((uint16)((Buffer)[(Offset)]) << 8) | \
                                                                                        ((uint16)((Buffer)[(Offset) + 1u]))))

# define TCPIP_GET_UINT32(Buffer, Offset)                                     ((uint32)(((uint32)((Buffer)[(Offset)]) << 24) | \
                                                                                        ((uint32)((Buffer)[(Offset) + 1u]) << 16) | \
                                                                                        ((uint32)((Buffer)[(Offset) + 2u]) <<  8) | \
                                                                                        ((uint32)((Buffer)[(Offset) + 3u]))))

/* The following macros read unsigned integers from a linear buffer without modyfiying the byte order. */

#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)                                                                                 /* COV_TCPIP_BYTE_ORDER */
# define TCPIP_GET_UINT16_RAW(Buffer, Offset)    TCPIP_GET_UINT16(Buffer, Offset)
# define TCPIP_GET_UINT32_RAW(Buffer, Offset)    TCPIP_GET_UINT32(Buffer, Offset)
#else
# define TCPIP_GET_UINT16_RAW(Buffer, Offset)                                 ((uint16)(((uint16)((Buffer)[(Offset) + 1u]) << 8) | \
                                                                                        ((uint16)((Buffer)[(Offset)]))) )

# define TCPIP_GET_UINT32_RAW(Buffer, Offset)                                 ((uint32)(((uint32)((Buffer)[(Offset) + 3u]) << 24) | \
                                                                                        ((uint32)((Buffer)[(Offset) + 2u]) << 16) | \
                                                                                        ((uint32)((Buffer)[(Offset) + 1u]) <<  8) | \
                                                                                        ((uint32)((Buffer)[(Offset)]))))
#endif

#define TCPIP_NTOHS(UINT16_VALUE) IPBASE_NTOH16(UINT16_VALUE)
#define TCPIP_HTONS(UINT16_VALUE) IPBASE_HTON16(UINT16_VALUE)
#define TCPIP_NTOHL(UINT32_VALUE) IPBASE_NTOH32(UINT32_VALUE)
#define TCPIP_HTONL(UINT32_VALUE) IPBASE_HTON32(UINT32_VALUE)

/* PRQA L:FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(TcpIp_TcpIpErrorType, TCPIP_VAR_NOINIT) TcpIp_LastSockError;

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ----- */
#define TCPIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */


#if (TCPIP_VENABLE_CANOE_WRITE_STRING == STD_ON)                                                                        /* COV_TCPIP_CANOE_DEBUG */
extern VAR(sint8, TCPIP_VAR_NOINIT)                TcpIp_CanoeWriteStr[];
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ----- */
#define TCPIP_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if (TCPIP_SUPPORT_TCP == STD_ON)
extern VAR(uint16, TCPIP_VAR_NOINIT)               TcpIp_Tcp_DynamicPortCount;
# endif
extern VAR(uint16, TCPIP_VAR_NOINIT)               TcpIp_Udp_DynamicPortCount;

#define TCPIP_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ----- */
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
extern CONST(IpBase_AddrIn6Type, TCPIP_CONST) TcpIp_IpV6AddrUnspecified;  /* PRQA S 0759 */ /* MD_MSR_Union */
#endif

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if !defined (STATIC)                                                                                                   /* COV_TCPIP_COMPATIBILITY */
# define STATIC static
#endif

#if !defined (TCPIP_LOCAL)                                                                                              /* COV_TCPIP_COMPATIBILITY */
# define TCPIP_LOCAL static
#endif

#if !defined (TCPIP_LOCAL_INLINE)                                                                                       /* COV_TCPIP_COMPATIBILITY */
# define TCPIP_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * TcpIp_WriteUInt16()
 *********************************************************************************************************************/
/*! \brief          Writes a 16 bit unsigned integer at the given position into a byte buffer.
 *  \details        The value is written in network byte order.
 *  \param[out]     BufferPtr   Target buffer.
 *  \param[in]      BufferPos   Position in target buffer. (bytes)
 *                              CONSTRAINT: [0...sizeof(Buffer)-2]
 *  \param[in]      Value       Value that shall be written into the buffer.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt16(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint16 Value);

/**********************************************************************************************************************
 * TcpIp_WriteUInt32()
 *********************************************************************************************************************/
/*! \brief          Writes a 32 bit unsigned integer at the given position into a byte buffer.
 *  \details        The value is written in network byte order.
 *  \param[out]     BufferPtr   Target buffer.
 *  \param[in]      BufferPos   Position in target buffer. (bytes)
 *                              CONSTRAINT: [0...sizeof(Buffer)-4]
 *  \param[in]      Value       Value that shall be written into the buffer.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt32(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint32 Value);

#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)                                                                                 /* COV_TCPIP_BYTE_ORDER */
/* No conversion of datatypes required if platform uses network byte order. */
#else
/**********************************************************************************************************************
 * TcpIp_WriteUInt16Le()
 *********************************************************************************************************************/
/*! \brief          Writes a 16 bit unsigned integer at the given position into a byte buffer.
 *  \details        The value is written in little endian byte order.
 *  \param[out]     BufferPtr   Target buffer.
 *  \param[in]      BufferPos   Position in target buffer. (bytes)
 *                              CONSTRAINT: [0...sizeof(Buffer)-2]
 *  \param[in]      Value       Value that shall be written into the buffer.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt16Le(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint16 Value);

/**********************************************************************************************************************
 * TcpIp_WriteUInt32Le()
 *********************************************************************************************************************/
/*! \brief          Writes a 32 bit unsigned integer at the given position into a byte buffer.
 *  \details        The value is written in little endian byte order.
 *  \param[out]     BufferPtr   Target buffer.
 *  \param[in]      BufferPos   Position in target buffer. (bytes)
 *                              CONSTRAINT: [0...sizeof(Buffer)-4]
 *  \param[in]      Value       Value that shall be written into the buffer.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt32Le(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint32 Value);
#endif

/**********************************************************************************************************************
 * TcpIp_VCopyPhysAddr()
 *********************************************************************************************************************/
/*! \brief          Copies a 6 byte long physical (link layer) address from source to target.
 *  \details        -
 *  \param[out]     DstAddrPtr   Destination buffer into which the address is copied.
 *                               CONSTRAINT: Must point to 6 bytes of memory.
 *  \param[in]      SrcAddrPtr   Source buffer from which the address is copied.
 *                               CONSTRAINT: Must point to 6 bytes of memory.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_VCopyPhysAddr(TCPIP_P2V(uint8) DstAddrPtr, TCPIP_P2C(uint8) SrcAddrPtr);

/* PRQA S 3219 InlineFunction */ /* MD_MSR_8.10 */

#if !defined(NO_INLINE_FUNCTION_DEFINITIONS)                                                                            /* COV_TCPIP_UNIT_TEST */

/**********************************************************************************************************************
 * TcpIp_WriteUInt16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt16(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint16 Value)
{
  BufferPtr[BufferPos] = (uint8)(Value >> 8);                                                                       /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos + 1u] = (uint8)(Value);                                                                            /* SBSW_TCPIP_WriteUInt */
}

/**********************************************************************************************************************
 * TcpIp_WriteUInt32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt32(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint32 Value)
{
  BufferPtr[BufferPos] = (uint8)(Value >> 24);                                                                      /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos + 1u] = (uint8)(Value >> 16);                                                                      /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos + 2u] = (uint8)(Value >>  8);                                                                      /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos + 3u] = (uint8)(Value);                                                                            /* SBSW_TCPIP_WriteUInt */
}

# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)                                                                                /* COV_TCPIP_BYTE_ORDER */
/* No conversion of datatypes required if platform uses network byte order. */
# else
/**********************************************************************************************************************
 * TcpIp_WriteUInt16Le()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt16Le(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint16 Value)
{
  BufferPtr[BufferPos + 1u] = (uint8)(Value >> 8);                                                                       /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos] = (uint8)(Value);                                                                            /* SBSW_TCPIP_WriteUInt */
}

/**********************************************************************************************************************
 * TcpIp_WriteUInt32Le()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_WriteUInt32Le(TCPIP_P2V(uint8) BufferPtr, uint16_least BufferPos, uint32 Value)
{
  BufferPtr[BufferPos + 3u] = (uint8)(Value >> 24);                                                                      /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos + 2u] = (uint8)(Value >> 16);                                                                      /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos + 1u] = (uint8)(Value >>  8);                                                                      /* SBSW_TCPIP_WriteUInt */
  BufferPtr[BufferPos] = (uint8)(Value);                                                                            /* SBSW_TCPIP_WriteUInt */
}
# endif

/**********************************************************************************************************************
*  TcpIp_VCopyPhysAddr
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_VCopyPhysAddr(TCPIP_P2V(uint8) DstAddrPtr, TCPIP_P2C(uint8) SrcAddrPtr)
{
  TCPIP_ASSERT(SrcAddrPtr != NULL_PTR);
  TCPIP_ASSERT(DstAddrPtr != NULL_PTR);
  TCPIP_VENTER_CRITICAL_SECTION();

  /* Do a byte-wise copy of the 6 physical address bytes. */
  DstAddrPtr[0] = SrcAddrPtr[0];                                                                                        /* SBSW_TCPIP_WritePhysAddr */
  DstAddrPtr[1] = SrcAddrPtr[1];                                                                                        /* SBSW_TCPIP_WritePhysAddr */
  DstAddrPtr[2] = SrcAddrPtr[2];                                                                                        /* SBSW_TCPIP_WritePhysAddr */
  DstAddrPtr[3] = SrcAddrPtr[3];                                                                                        /* SBSW_TCPIP_WritePhysAddr */
  DstAddrPtr[4] = SrcAddrPtr[4];                                                                                        /* SBSW_TCPIP_WritePhysAddr */
  DstAddrPtr[5] = SrcAddrPtr[5];                                                                                        /* SBSW_TCPIP_WritePhysAddr */

  TCPIP_VLEAVE_CRITICAL_SECTION();
} /* TcpIp_VCopyPhysAddr() */

/* PRQA L:InlineFunction */

#endif

/**********************************************************************************************************************
 * MISCELLANEOUS SERVICE FUNCTIONS - START
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_VPreconfigSocket()
 *********************************************************************************************************************/
/*! \brief          Pre-configures a (TCP or UDP) socket
 *  \details        -
 *  \param[in]      SocketIdx   Index of a UDP or TCP socket.
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VPreconfigSocket(TcpIp_SocketDynIterType SocketIdx);

/**********************************************************************************************************************
 *  TcpIp_VRxUdpSockIdxIdent()
 *********************************************************************************************************************/
/*! \brief          Identifies an incoming UDP socket.
 *  \details        -
 *  \param[in]      RxSockLocAddrPtr    Local address of the received packet.
 *  \param[in]      LocalAddrIdx        Index of a local address.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1]
 *  \return         Socket index of the given socket address in case the UDP socket was identified.
 *  \return         TCPIP_SOCKET_IDX_INV in case the UDP socket could NOT be identified.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_SocketDynIterType, TCPIP_CODE) TcpIp_VRxUdpSockIdxIdent(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TcpIp_LocalAddrIterType           LocalAddrIdx);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VRxTcpSockIdxIdent()
 *********************************************************************************************************************/
/*! \brief          Identifies an incoming TCP socket.
 *  \details        -
 *  \param[in]      RxSockRemAddrPtr    Remote address of the received packet.
 *  \param[in]      RxSockLocAddrPtr    Local address of the received packet.
 *  \param[in]      LocalAddrIdx        Index of a local address.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1]
 *  \return         Socket index of the given socket address in case the TCP socket was identified.
 *  \return         TCPIP_SOCKET_IDX_INV in case the TCP socket could NOT be identified.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_SocketDynIterType, TCPIP_CODE) TcpIp_VRxTcpSockIdxIdent(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TcpIp_LocalAddrIterType           LocalAddrIdx);
#endif

/**********************************************************************************************************************
 *  TcpIp_SetLastSockError()
 *********************************************************************************************************************/
/*! \brief         Sets the last socket error.
 *  \details       -
 *  \param[in]     Error               Error code.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_SetLastSockError(TcpIp_TcpIpErrorType Error);

/**********************************************************************************************************************
 *  TcpIp_VInitSockets()
 *********************************************************************************************************************/
/*! \brief         Initializes all sockets.
 *  \details       -
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VInitSockets(void);

/**********************************************************************************************************************
 *  TcpIp_VInitSocket()
 *********************************************************************************************************************/
/*! \brief         Initializes the admin data of one single socket.
 *  \details       Called in the context of the initialization of the TcpIp.
 *  \param[in]     SocketIdx   Index of a UDP or TCP socket.
 *                 CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VInitSocket(TcpIp_SocketDynIterType SocketIdx);

/**********************************************************************************************************************
 *  TcpIp_VDelSockAddrMapping()
 *********************************************************************************************************************/
/*! \brief         Deletes a socket address mapping.
 *  \details       Called in the context of the initialization of the TcpIp.
 *  \param[in]     SocketIdx   Index of a UDP or TCP socket.
 *                 CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VDelSockAddrMapping(TcpIp_SocketDynIterType SocketIdx);

/**********************************************************************************************************************
 *  TcpIp_VSockIpAddrIsEqual()
 *********************************************************************************************************************/
/*! \brief         Checks if the IP addresses of two given sockets are equal.
 *  \details       -
 *  \param[in]     SockAPtr             Pointer to first socket address.
 *  \param[in]     SockBPtr             Pointer to second socket address.
 *  \return        TRUE                 IP address family and address values are equal.
 *  \return        FALSE                IP address family does not match or address values differ.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_VSockIpAddrIsEqual(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockBPtr);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VSockAddrIpAndPortIsEqual()
 *********************************************************************************************************************/
/*! \brief         Checks if IP addresses and ports of two given sockets are equal.
 *  \details       This function does the same as TcpIp_VSockIpAddrIsEqual() plus a comparison of the port value.
 *  \param[in]     SockAPtr             Pointer to first socket address.
 *  \param[in]     SockBPtr             Pointer to second socket address.
 *  \return        TRUE                 IP address family, address values and port values are equal.
 *  \return        FALSE                IP address family, address values or ports values differ.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_VSockAddrIpAndPortIsEqual(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockBPtr);

/**********************************************************************************************************************
 *  TcpIp_VNetAddrIsUnicast()
 *********************************************************************************************************************/
/*! \brief         Checks if the given SockAddr is a unicast address.
 *  \details       -
 *  \param[in]     SockAddrPtr      Socket address containing the IP address
 *  \return        TRUE             The socket address contains a unicast IP address
 *  \return        FALSE            The socket address does not contain a unicast IP address
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_VNetAddrIsUnicast(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr);
#endif

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/**********************************************************************************************************************
*  TcpIp_VCalcIpV4PseudoHdrChecksum()
***********************************************************************************************************************/
/*! \brief         Calculates the pseudo header checksum for IPv4.
 *  \details       The returened checksum value is not finalized (wrapped to 16 bit) in order to allow adding payload
 *                 bytes to the checksum.
 *                 IpBase_TcpIpChecksumAdd(..., TRUE) must be called to finalize the checksum.
 *  \param[in]     RemAddr               Remote IPv4 address.
 *  \param[in]     LocAddr               Local IPv4 address.
 *  \param[in]     Protocol              IP Protocol (TCP, UDP, ICMP, ...)
 *  \param[in]     ProtocolPayloadLen    Payload length following the IP header.
 *  \return                              Partial uint32 checksum value.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(uint32, TCPIP_CODE) TcpIp_VCalcIpV4PseudoHdrChecksum(
  IpBase_AddrInType RemAddr,
  IpBase_AddrInType LocAddr,
  uint8             Protocol,
  uint16            ProtocolPayloadLen);
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_VCalcIpV6PseudoHdrChecksum()
 *********************************************************************************************************************/
/*! \brief         Calculates the pseudo header checksum for IPv6.
 *  \details       The returened checksum value is not finalized (wrapped to 16 bit) in order to allow adding payload
 *                 bytes to the checksum.
 *                 IpBase_TcpIpChecksumAdd(..., TRUE) must be called to finalize the checksum.
 *  \param[in]     RemAddrPtr            Remote IPv6 address.
 *  \param[in]     LocAddrPtr            Local IPv6 address.
 *  \param[in]     Protocol              IP Protocol (TCP, UDP, ICMP, ...)
 *  \param[in]     ProtocolPayloadLen    Payload length following the IP header.
 *  \return                              Partial uint32 checksum value.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(uint32, TCPIP_CODE) TcpIp_VCalcIpV6PseudoHdrChecksum(
  TCPIP_P2C(IpBase_AddrIn6Type) RemAddrPtr,
  TCPIP_P2C(IpBase_AddrIn6Type) LocAddrPtr,
  uint8                         Protocol,
  uint16                        ProtocolPayloadLen);
#endif

/**********************************************************************************************************************
 *  TcpIp_VCalcPseudoHdrAndChecksum()
 *********************************************************************************************************************/
/*! \brief         Calculates the pseudo header checksum depending on the IP version used in the socket adresses.
 *  \details       -
 *  \param[in]     RxSockRemAddrPtr      pointer to remote address value
 *  \param[in]     RxSockLocAddrPtr      pointer to local address value
 *  \param[in]     DataPtr               pointer to payload data
 *  \param[in]     DataLen               length payload data in bytes
 *  \param[in]     Protocol              protocol identifier
 *  \return                              Checksum value finalized to uint16 range.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(uint16, TCPIP_CODE) TcpIp_VCalcPseudoHdrAndChecksum(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            DataLen,
  uint8                             Protocol);

/**********************************************************************************************************************
 * TcpIp_CmpLLAddr()
 *********************************************************************************************************************/
/*! \brief          This method compares two Link Layer addresses (Ethernet physical addresses).
 *  \details        -
 *  \param[in]      LLAddr1Ptr      pointer to first physical layer address to compare.
 *  \param[in]      LLAddr2Ptr      pointer to second physical layer address to compare.
 *  \return         TRUE in case the addresses are equal, FALSE otherwise.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_CmpLLAddr(
  TCPIP_P2C(uint8) LLAddr1Ptr,
  TCPIP_P2C(uint8) LLAddr2Ptr);

/**********************************************************************************************************************
 *  TcpIp_VIpTransmit()
 *********************************************************************************************************************/
/*! \brief          Wraps the call to transmit function of IP layer. (IPV4/IPv6)
 *  \details        -
 *  \param[in]      IpTxReqDescPtr          Pointer to TX request descriptor that was used at the
 *                                          "provide tx buffer call" of the related IPv4 or IPv6 protocol, i.e.:
 *                                          IPv4: The IpV4_Ip_ProvideTxBuffer() call.
 *  \param[in]      IpPayloadLen            Number of bytes to transmit.
 *                                          This implementations allows two special cases:
 *                                          1: The value of ipPayloadLen may be larger than requested by IpV4_Ip_ProvideTxBuffer() if
 *                                             there was enough space left in the last provided buffer fragment.
 *                                          2: The value of ipPayloadLen may be less than requested by IpV4_ProvideTxBuffer().
 *                                             Even if there were multiple buffers provided, only the required number of fragments will be sent.
 *                                             Previously provided but unused buffers will be released by this function.
 *  \param[in]      IpProtocol              IP protocol value. (TCP, UDP, ICMP)
 *  \param[in]      UlTxReqIdx              Upper layer TX request identifier.
 *  \param[in]      Flags                   Any combination of the following flags:
 *                                          - TCPIP_V_IP_TRANSMIT_FLAG_TX_CONFIRMATION:
 *                                            Request TX confirmation from EthIf.
 *                                          - TCPIP_V_IP_TRANSMIT_FLAG_RETRY_ON_PHYS_ADDR_MISS:
 *                                            Do not cancel transmit if link layer address of destination is not (yet)
 *                                            in link layer address resolution cache.
 *  \return         TCPIP_OK                Transmission triggered.
 *  \return         TCPIP_E_NOT_OK          Transmit failed.
 *  \return         TCPIP_E_PHYS_ADDR_MISS  Transmit failed due to ARP cache miss.
 *  \pre            A previous call of IpVx_ProvideTxBuffer() must have been successful.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_ReturnType, TCPIP_CODE) TcpIp_VIpTransmit(
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  uint16                                     IpPayloadLen,
  uint8                                      IpProtocol,
  uint8                                      UlTxReqIdx,
  uint8                                      Flags);

/**********************************************************************************************************************
 *  TcpIp_VIpTransmitCancel()
 *********************************************************************************************************************/
/*! \brief          Cancels the transmit after a preceding call to ProvideTxBuffer.
 *  \details        -
 *  \param[in,out]  IpTxReqDescrPtr       IP TX request descriptor.
 *  \param[in]      UlTxReqTabIdx         TX request index.
 *  \param[in]      IpProtocol            IP protocol (UDP, TCP, ICMP).
 *  \pre            A previous call of IpVx_ProvideTxBuffer() must have been successful.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VIpTransmitCancel(
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr,
  uint8                                      UlTxReqTabIdx,
  uint8                                      IpProtocol);

/**********************************************************************************************************************
 *  TcpIp_VRstCtrl()
 *********************************************************************************************************************/
/*! \brief         Resets some variables for one controller
 *  \details       Called in the context of transceiver link loss, or IP address expiration.
 *  \param[in]     LocalAddrIdx     Index of the local address that cannot be used by sockets anymore.
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VRstCtrl(TcpIp_LocalAddrIterType LocalAddrIdx);

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VIncMeasurementDataCounter()
 *********************************************************************************************************************/
/*! \brief         Increments the corresponding measurement data counter.
 *  \details       The function ensures that the data counter does not overflow.
 *  \param[in]     MeasurementIdx         Index of measurement data.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VIncMeasurementDataCounter(
  TcpIp_MeasurementIdxType  MeasurementIdx);
#endif

/**********************************************************************************************************************
 * MISCELLANEOUS SERVICE FUNCTIONS - STOP
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * FUNCTIONS CONDUCTING CALLOUTS TO UPPER LAYERS - START
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_VPhysAddrTableChg()
 *********************************************************************************************************************/
/*! \brief         Called by the IpV4 or IpV6 in case of a change in the ARP/NDP table related to the
 *                 controller specified by CtrlIdx.
 *  \details       -
 *  \param[in]     CtrlIdx     EthIf controller index of the related ARP/NDP table.
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfEthIfCtrl()-1]
 *  \param[in]     IpAddrPtr   specifies the IP address of the changed ARP/NDP table entry
 *  \param[in]     PhysAddrPtr specifies the physical address of the changed ARP/NDP table entry
 *  \param[in]     Valid       specifies if the ARP/NDP table entry is added or changed (TRUE) or has been removed (FALSE)
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VPhysAddrTableChg(
  uint8                             CtrlIdx,
  TCPIP_P2V(TcpIp_SockAddrBaseType) IpAddrPtr,
  TCPIP_P2V(uint8)                  PhysAddrPtr,
  boolean                           Valid);

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_VDuplicateAddrDetected()
 *********************************************************************************************************************/
/*! \brief         Informs upper layers about an IPv6 address conflict.
 *  \details       Does NOT trigger the named DEM event.
 *  \param[in]     LocalAddrId        IP address Identifier, representing an IP address specified in the TcpIp module
 *                                    configuration.
 *  \param[in]     SrcAddrPtr         Pointer to the memory where the affected source IP address is stored in
 *                                    network byte order.
 *  \param[in]     RemotePhysAddrPtr  Pointer to the memory where the remote physical address (MAC address) related
 *                                    to the specified IP address is stored in network byte order.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         DSGN-TcpIpDuplicateAddrDetection
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_VDuplicateAddrDetected(
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2C(uint8)      SrcAddrPtr,
  TCPIP_P2C(uint8)      RemotePhysAddrPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_RxIndicationFunctions()
 *********************************************************************************************************************/
/*! \brief         Informs upper layers about the finalization of a reception of data.
 *  \details       -
 *  \param[in]     SocketIdx         Index of a UDP or TCP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     RemoteSockAddrPtr Address info of the socket connected newly.
 *  \param[in]     DataPtr           Payload of the data received.
 *  \param[in]     DataLenByte       Payload length of the data received.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_RxIndicationFunctions(
  TcpIp_SocketDynIterType           SocketIdx,
  TCPIP_P2V(TcpIp_SockAddrBaseType) RemoteSockAddrPtr,
  TCPIP_P2V(uint8)                  DataPtr,
  uint16                            DataLenByte);

/**********************************************************************************************************************
 *  TcpIp_TxConfirmationFunctions()
 *********************************************************************************************************************/
/*! \brief         Informs upper layers about a transmitted packet.
 *  \details       -
 *  \param[in]     SocketIdx         Index of a UDP or TCP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     DataLenByte       Length of data that was transmitted. [bytes]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TxConfirmationFunctions(
  TcpIp_SocketDynIterType SocketIdx,
  uint16                  DataLenByte);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TcpAcceptedFunctions()
 *********************************************************************************************************************/
/*! \brief         Informs upper layers about a new socket connection on a listen socket and asks them for acceptance.
 *  \details       -
 *  \param[in]     SocketOwnerIdx        Index of a socket owner.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfSocketOwnerConfig()-1]
 *  \param[in]     SocketTcpIdx          Index of a TCP socket that is in state listen.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SocketTcpIdxConnected Index of a newly allocated TCP socket that represents the accepted connection.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     RemoteSockAddrPtr     Pointer to remote socket address of the accepted connection.
 *  \return        E_OK                  Upper layer has accepted the new connection.
 *  \return        E_NOT_OK              Upper layer has rejected the new connection.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpAcceptedFunctions(
  TcpIp_SocketOwnerConfigIterType SocketOwnerCfgIdx,
  TcpIp_SocketTcpDynIterType      SocketTcpIdx,
  TcpIp_SocketTcpDynIterType      SocketTcpIdxConnected,
  TCPIP_P2V(TcpIp_SockAddrType)   RemoteSockAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_TcpConnectedFunctions()
 *********************************************************************************************************************/
/*! \brief         Informs upper layers about the "connect" event on a socket.
 *  \details       -
 *  \param[in]     SocketTcpIdx      Index of a TCP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TcpConnectedFunctions(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);
#endif

/**********************************************************************************************************************
 *  TcpIp_TcpIpEventFunctions()
 *********************************************************************************************************************/
/*! \brief         Informs upper layers about TcpIp events of active sockets.
 *  \details       -
 *  \param[in]     SocketOwnerCfgIdx Index of a socket owner.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketOwnerConfig()-1]
 *  \param[in]     SocketIdx         Index of the TCP/UDP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     EventType         Status event that occurred in the connection related to the given socket.
 *  \pre           -
 *  \note          Use TcpIp_TcpIpClosedEventFunctions() for the events TCPIP_TCP_CLOSED and TCPIP_UDP_CLOSED.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TcpIpEventFunctions(
  TcpIp_SocketOwnerConfigIterType SocketOwnerCfgIdx,
  TcpIp_SocketDynIterType         SocketIdx,
  IpBase_TcpIpEventType           EventType);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_TlsValidationResultFunctions()
 *********************************************************************************************************************/
/*! \brief         Informs upper layers about Tls validation results.
 *  \details       -
 *  \param[in]     SocketOwnerCfgIdx    Index of a socket owner.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketOwnerConfig()-1]
 *  \param[in]     SocketIdx            Index of a TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in,out] ValidationResultPtr  Result of the certificate validation in Tls.
 *  \param[in]     CertChainPtr         Pointer to the received certificate chain.
 *  \param[in]     CertChainLen         Length of the received certificate chain.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsValidationResultFunctions(
  TcpIp_SizeOfSocketOwnerConfigType SocketOwnerCfgIdx,
  TcpIp_SizeOfSocketDynType         SocketIdx,
  TCPIP_P2V(uint8)                  ValidationResultPtr,
  TCPIP_P2C(uint8)                  CertChainPtr,
  uint32                            CertChainLen);
#endif

/**********************************************************************************************************************
 *  TcpIp_CopyTxDataFunctions()
 *********************************************************************************************************************/
/*! \brief         Calls the configured CopyTxData function of the socket owner.
 *  \details       -
 *  \param[in]     SocketIdx         Index of a UDP or TCP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[out]    BufferPtr         Buffer into which the socket owner shall copy the data.
 *  \param[in,out] BufferLenBytePtr  Length of the buffer. [byte]
 *                                   Out: Updated value if the socket owner has written less bytes.
 *  \return        BUFREQ_OK         Data was copied.
 *  \return        BUFREQ_E_NOT_OK   No data copied. Transmit shall be aborted.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_CopyTxDataFunctions(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2V(uint8)          BufferPtr,
  TCPIP_P2V(uint16)         BufferLenBytePtr);

/**********************************************************************************************************************
 *  TcpIp_LocalIpAssignmentChgFunctions()
 *********************************************************************************************************************/
/*! \brief         Calls the configured IP address assignment change callbacks of the socket owners.
 *  \details       -
 *  \param[in]     LocalAddrIdx     Index of a local IPv4 or IPv6 address.
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     AddrState        Assignment state of the IP address. (ASSIGNED, UNASSIGNED)
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_LocalIpAssignmentChgFunctions(
  TcpIp_LocalAddrIterType LocalAddrIdx,
  TcpIp_IpAddrStateType   AddrState);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VSockTcpStateChg()
 *********************************************************************************************************************/
/*! \brief         Conducts the "TCP socket state change" event callback to upper layers.
 *  \details       The callback is conducted for the given socket index and socket user.
 *  \param[in]     SocketIdx               Index of a TCP socket.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     FormerSocketOwnerCfgIdx Index of the owner that is (or was) assigned to the socket before closing.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfSocketOwnerConfig()-1]
 *  \param[in]     State                   New socket state.
 *  \param[in]     SocketUsesTls           Indicates whether the socket uses TLS.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VSockTcpStateChg(
  TcpIp_SocketDynIterType         SocketIdx,
  TcpIp_SocketOwnerConfigIterType FormerSocketOwnerCfgIdx,
  TcpIp_StateType                 State,
  boolean                         SocketUsesTls);
#endif

/**********************************************************************************************************************
 *  TcpIp_VSockTxConfirmation()
 *********************************************************************************************************************/
/*! \brief         Conducts the transmit confirmation callback to upper layers.
 *  \details       -
 *  \param[in]     SocketIdx         Index of a UDP or TCP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     DataLenByte       Length of transmitted data. [bytes]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VSockTxConfirmation(
  TcpIp_SocketDynIterType SocketIdx,
  uint32                  DataLenByte);

/**********************************************************************************************************************
 *  TcpIp_Cbk_VLocalIpAssignmentChg()
 *********************************************************************************************************************/
/*! \brief         Conducts the IP state change event callback to upper layers.
 *  \details       The callback is conducted to for the given local address index
 *  \param[in]     LocalAddrIdx          Index of a local address.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     State                 New state of address (ASSIGNED, UNASSIGNED, ONHOLD).
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Cbk_VLocalIpAssignmentChg(
  TcpIp_LocalAddrIterType LocalAddrIdx,
  TcpIp_IpAddrStateType   State);

/**********************************************************************************************************************
 *  TcpIp_Cbk_VPathMtuChg()
 *********************************************************************************************************************/
/*! \brief          Conducts the "path MTU has changed" event callout to upper layers.
 *  \details        The callback is conducted for the given ethernet ctrl index and destination address.
 *  \param[in]      CtrlIdx               controller index
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfEthIfCtrl()-1]
 *  \param[in]      SockAddrPtr           net address that changed its state
 *  \param[in]      PathMtuSize           new size of the Path-MTU (transport layer part)
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Cbk_VPathMtuChg(
  uint8                             CtrlIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr,
  uint16                            PathMtuSize);

/**********************************************************************************************************************
 *  TcpIp_Cbk_VAddrResTimeout()
 *********************************************************************************************************************/
/*! \brief          Notifies the TcpIp that the link layer address resolution for the specified destination timed out.
 *  \details        -
 *  \param[in]      DestAddrPtr    Pointer to remote IP address for which the link layer address could not be resolved.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Cbk_VAddrResTimeout(
  TCPIP_P2C(TcpIp_SockAddrBaseType) DestAddrPtr);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VSockTcpStateChgAccepted()
 *********************************************************************************************************************/
/*! \brief          Conducts the "TCP state change accepted" event callback to upper layers.
 *  \details        This function is derived from TcpIp_VSockTcpStateChg but implements a the following special handling:
 *                  1. It provides a return value from the called upper layer function.
 *                  2. It checks the given SoUserIdx.
 *                  3. It looks up the ListenSockIdx using the runtime-data-array TcpIp_SocketList at index SockIdx.
 *  \param[in]      SocketTcpIdx          Index of a TCP socket.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return         E_OK                  The user accepted the accepted connection.
 *                  E_NOT_OK              The user refused the accepted connection.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VSockTcpStateChgAccepted(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);
#endif
/* (STD_ON == TCPIP_SUPPORT_TCP) */

/**********************************************************************************************************************
 * FUNCTIONS CONDUCTING CALLOUTS TO UPPER LAYERS - STOP
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * PUBLIC FUNCTIONS OF THE DYNAMIC LIST FUNCTIONALITY ("DList") - START
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DListInitDesc()
 *********************************************************************************************************************/
/*! \brief          Initializes a Dlist descriptor. All nodes from the node storage array will be linked and inserted
 *                  into the free list. This descriptor can be used by multiple DList instances. See TcpIp_DListInit().
 *  \details        -
 *  \param[in]      DescPtr       Descriptor to be initialized.
 *  \param[in]      NodePtr       Node storage array
 *  \param[in]      NodeCount     Number of nodes in node storage array
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DListInitDesc(
  TCPIP_P2V(TcpIp_DListDescType) DescPtr,
  TCPIP_P2V(TcpIp_DListNodeType) NodePtr,
  uint8                          NodeCount);

/**********************************************************************************************************************
 *  TcpIp_DListInit()
 *********************************************************************************************************************/
/*! \brief          Initializes a DList instance. After initialization the list is empty.
 *                  New elements can be inserted by TcpIp_DListAddElement().
 *  \details        -
 *  \param[in]      ListPtr       DList instance
 *  \param[in]      DescPtr       DList descriptor that will by used by this instance.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DListInit(
  TCPIP_P2V(TcpIp_DListType)     ListPtr,
  TCPIP_P2V(TcpIp_DListDescType) DescPtr);

/**********************************************************************************************************************
 *  TcpIp_DListAddElement()
 *********************************************************************************************************************/
/*! \brief          Adds an element to a DList instance by moving it from the free list.
 *  \details        -
 *  \param[in]      DListPtr   Handle to the list into that the new element should be inserted.
 *  \param[in]      AfterIdx   Index of a list item that shall be the predecessor of the new item.
 *                             If the index is TCPIP_DLIST_END_IDX the new item will be inserted at the beginning of the list.
 *  \param[out]     NewIdxPtr  Index of the inserted item. Only valid if result is E_OK.
 *  \return         E_OK       success
 *  \return         E_NOT_OK   No elements in free list. (NewIdxPtr not modified)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DListAddElement(
  TCPIP_P2V(TcpIp_DListType)    DListPtr,
  TcpIp_DListIdxType            AfterIdx,
  TCPIP_P2V(TcpIp_DListIdxType) NewIdxPtr);

/**********************************************************************************************************************
 *  TcpIp_DListRemoveElement()
 *********************************************************************************************************************/
/*! \brief          Removes a single element from a DList instance and adds it to the free list of the descriptor
 *  \details        -
 *  \param[in]      DListPtr  Handle to the DList instnace containing the element to be removed.
 *  \param[in]      RemIdx    Index of the element that shall be removed.
 *                            CONSTRAINT: [0...<#Elements at DListPtr>-1]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DListRemoveElement(
  TCPIP_P2V(TcpIp_DListType) DListPtr,
  TcpIp_DListIdxType         RemIdx);

/**********************************************************************************************************************
 *  TcpIp_DListRemoveElementRange()
 *********************************************************************************************************************/
/*! \brief          Removes a chain of linked elements from the list and adds them to the free list of the descriptor.
 *  \details        -
 *  \param[in]      DListPtr    Handle to the DList instnace containing the elements to be removed.
 *  \param[in]      RemStartIdx Index of the first item of the element chain that shall be removed.
 *                              CONSTRAINT: [0...<#Elements at DListPtr>-1]
 *  \param[in]      RemEndIdx   Index of the lest item of the element chain that shall be removed.
 *                              CONSTRAINT: [0...<#Elements at DListPtr>-1]
 *  \note           RemStartIdx and RemEndIdx may be equal but for performance reasons TcpIp_DListRemoveElement() should be
 *                  used for removing single elements.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DListRemoveElementRange(
  TCPIP_P2V(TcpIp_DListType) DListPtr,
  TcpIp_DListIdxType         RemStartIdx,
  TcpIp_DListIdxType         RemEndIdx);

/**********************************************************************************************************************
 *  TcpIp_DListClear()
 *********************************************************************************************************************/
/*! \brief          Clears a DList instance by moving all elements to the free list of the descriptor.
 *  \details        -
 *  \param[in]      DListPtr  Handle to the DList instance.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DListClear(
  TCPIP_P2V(TcpIp_DListType) DListPtr);

/**********************************************************************************************************************
 * PUBLIC FUNCTIONS OF THE DYNAMIC LIST FUNCTIONALITY ("DList") - STOP
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_VIsPortAndAddrUsedBySocket()
 *********************************************************************************************************************/
/*! \brief          Checks whether any active socket in the specified range uses the given IP address and port.
 *  \details        -
 *  \param[in]      Port                Port number (host byte order)
 *  \param[in]      LocalAddrIdx        Index of a local address.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCALADDRID_ANY.
 *  \param[in]      SocketStartIdx      Index of the first a UDP/TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      SocketEndIdx        Index of the last a UDP/TCP socket + 1.
 *                                      CONSTRAINT: [SocketStartIdx...TcpIp_GetSizeOfSocketDyn()]
 *                                      If SocketStartIdx <= SocketEndIdx the function returns FALSE.
 *  \param[in]      SocketIgnoreIdx     Index of a UDP/TCP socket that shall be ignored.
 *                                      If the value is in range [SocketStartIdx...SocketEndIdx-1] this socket
 *                                      will be ignored.
 *  \return         TRUE                A matching socket was found.
 *  \return         FALSE               No matching socket was found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_VIsPortAndAddrUsedBySocket(
  uint16                    Port,
  TcpIp_LocalAddrIterType   LocalAddrIdx,
  TcpIp_SocketDynIterType   SocketStartIdx,
  TcpIp_SocketDynIterType   SocketEndIdx,
  TcpIp_SocketDynIterType   SocketIgnoreIdx);

/**********************************************************************************************************************
 *  TcpIp_VFindUnusedDynamicPort()
 *********************************************************************************************************************/
/*! \brief          Selects a port number from the dynamic port range that is not currently in use by another socket.
 *  \details        -
 *  \param[in]      Protocol            IP Protocol.
 *                                      CONSTRAINT: [TCPIP_PROTOCOL_UDP, TCPIP_PROTOCOL_TCP]
 *  \param[in]      LocalAddrIdx        Index of a local address.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCALADDRID_ANY.
 *  \param[in]      SocketStartIdx      Index of the first a UDP/TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      SocketEndIdx        Index of the last a UDP/TCP socket + 1.
 *                                      CONSTRAINT: [SocketStartIdx...TcpIp_GetSizeOfSocketDyn()]
 *                                      If SocketStartIdx <= SocketEndIdx the function returns FALSE.
 *  \param[in]      SocketIgnoreIdx     Index of a UDP/TCP socket that shall be ignored.
 *                                      If the value is in range [SocketStartIdx...SocketEndIdx-1] this socket
 *                                      will be ignored.
 *  \return         > 0                 Port number that is not in used by any other socket.
 *  \return         TCPIP_PORT_NOT_SET  No unused port was found.
 *  \note                               The current implementation will never return TCPIP_PORT_NOT_SET since it just
 *                                      iterates sequentially over the dynamic port range and will find an unused port
 *                                      after a maximum of (SocketEndIdx - SocketStartIdx) iterations.
 *                                      But future implementations may not guarantee this behavior and therefore the
 *                                      caller must be able to handle the raturn value TCPIP_PORT_NOT_SET.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(uint16, TCPIP_CODE) TcpIp_VFindUnusedDynamicPort(
  uint8                     Protocol,
  TcpIp_LocalAddrIterType   LocalAddrIdx,
  TcpIp_SocketDynIterType   SocketStartIdx,
  TcpIp_SocketDynIterType   SocketEndIdx,
  TcpIp_SocketDynIterType   SocketIgnoreIdx);

/**********************************************************************************************************************
 *  TcpIp_VGetNextDynamicPort()
 *********************************************************************************************************************/
/*! \brief          Returns the next number from the dynamic port range (49152-65535) defined by tha IANA.
 *  \details        This function uses a counter and will return the next port within the dynamic port range considering
 *                  the overflow.
 *  \param[in]      Protocol            IP Protocol identifier.
 *                                      CONSTRAINT: [TCPIP_PROTOCOL_UDP, TCPIP_PROTOCOL_TCP]
 *  \return                             Dynamic port number.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(uint16, TCPIP_CODE) TcpIp_VGetNextDynamicPort(uint8 Protocol);

/**********************************************************************************************************************
 *  TcpIp_VSetSocketSpecificFramePriority()
 *********************************************************************************************************************/
/*! \brief          Sets the ethernet frame priority value for all outgoing packets of the given socket.
 *  \details        -
 *  \param[in]      SocketIdx           Index of a UDP or TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      Value               EthIf frame priority.
 *                                      CONSTRAINT: [0..7]
 *  \return         E_OK                The value has been updated in the configured IP submodules.
 *  \return         E_NOT_OK            IP submodule returned negative result. (Value not in range)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different socket IDs.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VSetSocketSpecificFramePriority(
  TcpIp_SocketDynIterType SocketIdx,
  uint8                   Value);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
*  TcpIp_VGetSocketSpecificFramePriority()
*********************************************************************************************************************/
/*! \brief          Reads the ethernet frame priority value from listen socket,set through TcpIp_ChangeParameter.
*  \details        -
*  \param[in]      SocketIdx           Index of a UDP or TCP socket.
*                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
*  \param[in,out]  Priority            Pointer to EthIf frame priority.
*                                      CONSTRAINT: [Must be non null pointer]
*  \return         E_OK                The value has been read from the configured IP submodules.
*  \return         E_NOT_OK            IP submodule returned negative result. (Value not in range)
*  \pre            -
*  \context        TASK
*  \reentrant      TRUE for different socket IDs.
*  \synchronous    TRUE
*********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VGetSocketSpecificFramePriority(
  TcpIp_SocketDynIterType           SocketIdx,
  TCPIP_P2V(uint8)                  Priority);

/**********************************************************************************************************************
*  TcpIp_VCopySocketSpecificFramePriority()
*********************************************************************************************************************/
/*! \brief         Copy the ethernet frame priority value from listen socket to new(duplicate) created Tcp socket.
*  \details        -
*  \param[in]      SocketIdx           Index of new created duplicate socket.
*                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
*  \param[in]      ListenSocketIdx     Index of a Listen socket.
*                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
*  \pre            -
*  \context        TASK
*  \reentrant      TRUE for different socket IDs.
*  \synchronous    TRUE
*********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VCopySocketSpecificFramePriority(
  TcpIp_SocketDynIterType      SocketIdx,
  TcpIp_SocketDynIterType      ListenSocketIdx);
#endif

/**********************************************************************************************************************
 *  TcpIp_VSetSocketSpecificTimeToLive()
 *********************************************************************************************************************/
/*! \brief          Sets the TTL (IPv4) or HopLimit (IPv6) value for all outgoing packets of the given socket.
 *  \details        -
 *  \param[in]      SocketIdx           Index of a UDP or TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      Value               Value of the TTL/HopLimit field in the IP header.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different socket IDs.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VSetSocketSpecificTimeToLive(
  TcpIp_SocketDynIterType SocketIdx,
  uint8                   Value);

/**********************************************************************************************************************
*  TcpIp_VIpV4NetmaskToCidr()
**********************************************************************************************************************/
/*! \brief          Converts an IPv4 netmask to the CIDR notation.
 *  \details        The function counts the number of set most significant bits.
 *  \param[in]      IpV4Netmask         IPv4 netmask. (i.e.: 255.255.0.0 = 0xFFFF0000)
 *  \return                             CIDR notation of the netmask. (i.e.: 16 for IpV4Netmask = 0xFFFF0000)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(uint8, TCPIP_CODE) TcpIp_VIpV4NetmaskToCidr(IpBase_AddrInType IpV4Netmask);

/**********************************************************************************************************************
*  TcpIp_VRequestComModeInternal()
*********************************************************************************************************************/
/*! \brief         Forwards the communication mode state change request to internal function.
*  \details        Forwards the requested ComMode state to the transceiver link state change of the IP layer.
*  \param[in]      CtrlIdx             Index of a Eth controller.
*                                      CONSTRAINT: [0...TcpIp_GetSizeOfEthIfCtrl()-1]
*  \param[in]      TrcvLinkState       Requested state of the Eth controller.
*                                      CONSTRAINT: [TCPIP_ACTIVE_STATE_OFFLINE...TCPIP_ACTIVE_STATE_ONLINE]
*  \pre            -
*  \context        TASK
*  \reentrant      TRUE for different CtrlIdx.
*  \synchronous    TRUE
*********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_VRequestComModeInternal(
  uint8                                     CtrlIdx,
  CONST(EthTrcv_LinkStateType, TCPIP_CONST) TrcvLinkState);


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
  /* TCPIP_PRIV_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Priv.h
 *********************************************************************************************************************/
