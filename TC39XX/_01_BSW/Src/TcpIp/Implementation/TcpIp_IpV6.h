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
 *         \file  TcpIp_IpV6.h
 *        \brief  Implementation of Internet Protocol version 6 (IPv6)
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 *  Until version 7.xx.xx the following table lists the changes affecting the following files:
 *    TcpIp_IpV6.*
 *    TcpIp_IpV6_Cbk.h
 *    TcpIp_IpV6_Types.h
 *    TcpIp_IpV6_Priv.*
 *    TcpIp_IcmpV6.*
 *    TcpIp_Ndp.*
 *    TcpIp_Mld.*
 *    TcpIp_DhcpV6.*
 *    TcpIp_DhcpV6_Cbk.h
 *
 *  Since version 8.00.00 all changes are documented in TcpIp.h.
 *
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  All changes of Tp_IpV6 Implementation 3.00.01 are included.
 *  -
 *  01.00.00  2015-06-18  visfdn  ESCAN00083593 FEAT-1248: Configuration of the TCP/IP stack according to AR 4.2.1
 *            2015-07-09  visal   ESCAN00082693 FEAT-1283: Use hardware-based checksum calculation (IPv4, IPv6,
 *                                                TCP, UDP and ICMP) if it is supported by the microcontroller
 *            2015-07-09  visal   -             Remove parameter SockIdxPtr from the internal API TcpIp_Tcp_RxIndication
 *  01.00.01  2015-08-21  visfdn  ESCAN00084643 Compiler warning: Too many actual parameters in TcpIp_IpV6.c
 *            2015-08-21  visfdn  -             Resolved MISRA/PClint findings
 *  01.00.02  2015-10-14  visfdn  ESCAN00085857 Substitute Ethernet driver header file includes with includes of Ethernet Interface header files
 *  02.00.00  2015-11-27  visfdn  ESCAN00086828 Upper layer TX checksum calculation shall always by performed by IP or in HW
 *            2015-11-27  visfdn  ESCAN00086836 IPv6 does not accept fragmented multicast packets
 *            2015-11-27  visal   ESCAN00086833 FEAT-10: Send the FQDN option via DHCP to identify the ECU
 *            2015-11-27  visal   ESCAN00086834 FEAT-10: Support triggering of IP address assignment
 *            2015-11-27  visal   ESCAN00086835 FEAT-10: Implement API to read the local physical address
 *            2015-12-04  visfdn  ESCAN00086985 Configuration of IPv6 default controller shall be optional
 *  02.00.01  2016-01-29  visal   ESCAN00087917 Minor code rework due to MISRA / Code Review findings
 *  02.01.00  2016-01-29  visfdn  ESCAN00087558 Allow configuration of TcpIp lower layer other than EthIf
 *  02.01.01  2016-04-14  visfdn  ESCAN00089248 Received malformed ICMPv6 packet causes memory read access violation
 *  03.00.00  2016-05-18  visfdn  ESCAN00089362 FEAT-1498: IPv6: Static configuration of on-link prefixes
 *            2016-05-18  visfdn  ESCAN00089974 TcpIp_GetIpAddr() does not provide values for IPv6 netmask and default router.
 *            2016-05-18  visfdn  ESCAN00089902 DHCPv6 client FQDN option not included in messages after calling TcpIp_DhcpV6WriteOption
 *            2016-07-13  visal   ESCAN00090979 Compiler error: Pointer class ETH_VAR_NOINIT not available
 *  04.00.00  2016-10-14  visfdn  ESCAN00092048 Variable IpV6_State in ZERO_INIT section has no value assignment
 *            2016-10-14  visfdn  ESCAN00092053 Debug variables IpV6_DbgNeighborCache* and IpV6_DbgDestinationCache* are not initialized.
 *            2016-10-24  visfdn  ESCAN00091166 Adapted source file defines according to filenames
 *            2016-10-14  visfdn  FEATC-258     FEAT-1816: Split MainFunctions to optimize gateway use-case
 *            2016-11-22  visfdn  ESCAN00092912 TcpIp_DhcpV6ReadOption() returns E_NOT_OK when reading the FQDN option
 *  05.00.00  2017-03-22  visfdn  FEATC-935     FEAT-1824: Support a component-specific SafeBSW configuration switch
 *  06.00.00  2017-04-28  visjsb  STORYC-676    Enhancements for ETM (TcpIp: add "Clear NDP Cache" API)
 *  06.00.01  2017-05-15  viswnk  ESCAN00095181 Up_DADAddressConflict is called with wrong AddrId and wrong IP-address (pointed to by IpAddrPtr) in case a NA is sent for a preferred link-local address of the ECU.
 *  06.01.00  2017-05-18  visjsb  STORYC-1044   FEAT-2844,S-618 [ETH] Support of ASR4.3 APIs TcpIp_GetArpCacheEntries and TcpIp_GetNdpCacheEntries.
 *  06.02.00  2017-07-13  viswnk  -             Removed unnecessary non AUTOSAR API IpV6_GetVersionInfo
 *            2017-07-25  visfdn  STORYC-543    Support of AR4.3 API TcpIp_IcmpV6Transmit() and <Up_IcmpMsgHandler> callback for IPv6.
 *  06.03.00  2017-08-17  visfdn  STORYC-347    P3 Code Refactoring / CDD Step 1
 *  07.00.00  2018-03-15  visfdn  STORYC-352    Usage of ComStackLib for generated data.
 *            2018-03-15  visfdn  STORYC-2204   Code Refactoring in order to improve code metrics.
 *            2017-12-15  visfdn  ESCAN00097750 IpV6 retransmits DHCPv6 release message in response to reply message with failure status code
 *            2017-12-15  visfdn  ESCAN00092292 Retransmission of DHCPv6 Decline messages are not completed by a Reply message with a status code option indicating an error
 *  07.00.01  2017-04-18  visabn  STORYC-4950   Integration of code inspection findings
 *            2017-04-18  visabn  ESCAN00099024 ICMPv6 Parameter Problem message contains incorrect value in "Pointer" field
 *            2017-04-18  visabn  ESCAN00099032 DHCPv6 Decline Messages are not sent by ECU
 *            2017-04-18  visabn  ESCAN00099035 Solicited IPv6 Neighbor Advertisement messages sent during have incorrect Target Address Field
 *            2017-04-18  visabn  ESCAN00099040 During Duplicate Address Detection, IPv6 Neighbor Solicitation messages are not sent with Unspecified source address
 *            2017-04-18  visabn  ESCAN00099060 Request for DHCPv6 address assignment does not check if the requested IP address is DHCPv6 configurable
 *            2017-04-18  visabn  ESCAN00098929 NDP cache entry expires directly after it was created
 *  -------------------------------------------------------------------------------------------------------------------
 *  08.00.00  2018-06-11  visfdn  -             See TcpIp.h for changes in version 8.00.00 and above.
 *********************************************************************************************************************/

#if !defined(IPV6_H)
#define IPV6_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "TcpIp_IpV6_Types.h"
#include "TcpIp_Cfg.h"
#include "TcpIp_Lcfg.h"

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "IpBase_Copy.h"

#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#include "TcpIp_Cbk.h"


/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* vendor and module identification */
#define IPV6_VENDOR_ID               30u
#define IPV6_MODULE_ID              170u
#define IPV6_VINSTANCE_ID             3u   /*!< 0=SoAd, 1=TcpIp, 2=IpV4, 3=IpV6 */

/* External API IDs */
#define IPV6_API_ID_GET_VERSION_INFO         0x00u
#define IPV6_API_ID_INIT_MEMORY              0x01u
#define IPV6_API_ID_INIT                     0x02u

#define IPV6_API_ID_MAIN_FUNCTION            0x03u
#define IPV6_API_ID_PROVIDE_TX_BUFFER        0x04u
#define IPV6_API_ID_TRANSMIT                 0x05u
#define IPV6_API_ID_RX_INDICATION            0x06u
#define IPV6_API_ID_TX_CONFIRMATION          0x07u
#define IPV6_API_ID_CBK_TRCV_LINK_STATE_CHG  0x08u
#define IPV6_API_ID_SET_ADDRESS              0x09u
#define IPV6_API_ID_GET_SRC_ADDR             0x0Au
#define IPV6_API_ID_GET_DST_ADDR             0x0Bu
#define IPV6_API_ID_SET_TRAFFIC_CLASS        0x0Cu
#define IPV6_API_ID_SET_FLOW_LABEL           0x0Du
#define IPV6_API_ID_IS_VALID_DST_ADDR        0x0Eu
#define IPV6_API_ID_GET_SRC_ADDR_CFG_SRC     0x0Fu
#define IPV6_API_ID_GET_CURRENT_HOP_LIMIT    0x10u
#define IPV6_API_ID_GET_PHYS_ADDR            0x11u
#define IPV6_API_ID_GET_AS_BC_ADDR_ID        0x12u
#define IPV6_API_ID_MATCH_IP_ADDR_IDS        0x13u

#define IPV6_API_ID_SET_HOP_LIMIT            0x14u
#define IPV6_API_ID_SET_ETHIF_FRAME_PRIO     0x15u
#define IPV6_API_ID_RESET_SOCKET             0x16u

#define IPV6_API_ID_CANCEL_TRANSMIT          0x17u

#define IPV6_API_ID_GET_LOCAL_ADDRESS        0x18u
#define IPV6_API_ID_GET_DEF_ROUTER_ADDRESS   0x19u

/* - ICMP - */
#define IPV6_API_ID_ICMP_PROVIDE_TX_BUFFER   0x20u
#define IPV6_API_ID_ICMP_TX_ECHO_REQUEST     0x21u
#define IPV6_API_ID_ICMP_PACKET_RECEIVED     0x22u
#define IPV6_API_ID_ICMP_TRANSMIT            0x23u
#define IPV6_API_ID_ICMP_MAIN_FUNCTION       0x24u

/* - NDP - */
#define IPV6_API_ID_NDP_MAIN_FUNCTION        0x30u

/* - MLD - */
#define IPV6_API_ID_MLD_MAIN_FUNCTION        0x40u
#define IPV6_API_ID_MLD_INIT                 0x41u

#define IPV6_API_ID_V_INTERNAL_FUNCTION      0xFFu

/* Det Error Codes */
#define IPV6_E_NOT_INITIALIZED               0x01u


#define IPV6_E_INV_POINTER                   0x02u

#define IPV6_E_INV_SOCK_IDX                  0x03u
#define IPV6_E_INV_BUFF_IDX                  0x04u
#define IPV6_E_INV_CTRL_IDX                  0x05u
#define IPV6_E_INV_DATA_IDX                  0x06u
#define IPV6_E_INV_PARAM                     0x07u
#define IPV6_E_DLIST_BUFFER_EMPTY            0x08u
#define IPV6_E_INV_ADDR_ID                   0x09u
#define IPV6_E_INV_ADDR_CONFIG               0x0au
#define IPV6_E_NOT_SUPPORTED                 0x0bu

/* IpV6 States */
#define IPV6_STATE_UNINIT                    0x00u
#define IPV6_STATE_INIT                      0x01u

#define IPV6_CTRL_STATE_UNINIT               0x00u /* uninitialized */
#define IPV6_CTRL_STATE_INIT                 0x01u /* offline */
#define IPV6_CTRL_STATE_LINK_READY           0x02u /* startup */
#define IPV6_CTRL_STATE_LLADDR_READY         0x03u /* online  */
#define IPV6_CTRL_STATE_GBLADDR_READY        0x04u /* online  */

#define IPV6_CTRL_STATE_LLADDR_DAD_FAIL      0xF0u

#define IPV6_INV_LIST_IDX                    0xFFU

#define IPV6_LIFETIME_UNLIMITED (0xFFFFFFFFu)


#define IPV6_SRC_ADDR_DAD_MODE_NORMAL      0u /* FALSE */
#define IPV6_SRC_ADDR_DAD_MODE_NONE        1u /* TRUE */
#define IPV6_SRC_ADDR_DAD_MODE_OPTIMISTIC  2u

#define IPV6_ADDR_MATCH_NONE               0U
#define IPV6_ADDR_MATCH_EXACT              1U
#define IPV6_ADDR_MATCH_IF                 2U
#define IPV6_ADDR_MATCH_EVER               3U

#define IPV6_MULTICAST_PREFIX_LEN_BIT      8U /* ff00::/8 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */

#define IpV6_MemCpy(DstPtr, SrcPtr, LenByte) (IpBase_Copy((IPV6_P2V(IpBase_CopyDataType))(DstPtr), (IPV6_P2C(IpBase_CopyDataType))(SrcPtr), (LenByte)))

/* Address Type check macros [RFC4291 2.4. Address Type Identification] */

/* FF00::/8 [RFC4291 2.7. Multicast Addresses] */
#define IPV6_ADDR_IS_MULTICAST(ADDR)         (0xFFU == (ADDR).addr[0])
#define IPV6_ADDR_MCAST_SCOPE_BYTE(ADDR)     ((uint16)((ADDR).addr[1]))
#define IPV6_ADDR_MULTICAST_SCOPE(ADDR)      ((IPV6_ADDR_MCAST_SCOPE_BYTE(ADDR) &  0x000FU))
#define IPV6_ADDR_MULTICAST_FLAGS(ADDR)      (((ADDR).addr[1] >> 4) & (uint8) 0x0FU)

#define IPV6_ADDR_MULTICAST_SCOPE_FILTER_MASK 0x4134U
#define IPV6_ADDR_MULTICAST_HAS_VALID_SCOPE(MC_ADDR) ((((0x1uL << (uint16) IPV6_ADDR_MULTICAST_SCOPE((MC_ADDR)))) & IPV6_ADDR_MULTICAST_SCOPE_FILTER_MASK) != 0u)

/* FE80::/10 [RFC4291 2.5.6. Link-Local IPv6 Unicast Addresses] */
#define IPV6_ADDR_IS_LINK_LOCAL(ADDR)        ((0xFEu == (ADDR).addr[0]) && (0x80u == (0xC0u & (ADDR).addr[1])))

/* ::/128 [RFC4291 2.5.2. The Unspecified Address] */
#define IPV6_ADDR_IS_UNSPECIFIED(ADDR)       IPV6_ADDR_EQUALS((ADDR), IpV6_AddrUnspecified)

/* ::1/128 [RFC4291 2.5.3. The Loopback Address] */
#define IPV6_ADDR_IS_LOOPBACK(ADDR)          IPV6_ADDR_EQUALS((ADDR), IpV6_AddrLoopback)

/* [RFC4291 2.7.1. Pre-Defined Multicast Addresses] */
#define IPV6_ADDR_IS_ALL_NODES_LL(ADDR)      IPV6_ADDR_EQUALS((ADDR), IpV6_AddrAllNodesLL)

/* For all unicast addresses, except those that start with the binary value 000,
 * Interface IDs are required to be 64 bits long and to be constructed in Modified EUI-64 format.
 * [RFC4291 2.5.1. Interface Identifiers]
 * [RFC4291 2.5.4. Global Unicast Addresses]
 * [RFC3587 IPv6 Global Unicast Address Format]
 */
#define IPV6_ADDR_IS_EUI64(ADDR)             (0u != ((ADDR).addr[0] & 0xE0u))

/* Link-layer address type check macros */

#define IPV6_LL_ADDR_IS_GROUP(ADDR)          (0u != ((ADDR)[0] & 0x01u))
#define IPV6_LL_ADDR_IS_EMPTY(ADDR)          ((0x00u == (ADDR)[5]) && (0x00u == (ADDR)[4]) && (0x00u == (ADDR)[3]) && (0x00u == (ADDR)[2]) && (0x00u == (ADDR)[1]) && (0x00u == (ADDR)[0]))
#define IPV6_LL_ADDR_IS_INVALID(ADDR)        (IPV6_LL_ADDR_IS_GROUP((ADDR)) || IPV6_LL_ADDR_IS_EMPTY((ADDR)))

#define IPV6_LL_ADDR_COPY(DestinationPtr, SourcePtr) IpBase_Copy( (DestinationPtr),  (SourcePtr), IPBASE_ETH_PHYS_ADDR_LEN_BYTE)
#define IPV6_ADDR_COPY(Destination,    Source)       IpBase_Copy(&(Destination),    &(Source),    IPV6_ADDRESS_LEN_BYTE)

#define IPV6_ADDR_EQUALS(ADDR_A, ADDR_B)     (TRUE == IpV6_CmpNetAddr(&(ADDR_A), &(ADDR_B)))

# define TCPIP_IPV6_ADDR_IDX_IS_ASAN(LocalAddrV6Idx) ((TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == FALSE) && (TcpIp_IsIpV6MulticastAddrUsedOfLocalAddrV6(LocalAddrV6Idx) == FALSE))

#define TCPIP_LOCAL_ADDR_V6_IDX_ANY             0xFFu

/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef P2FUNC(void, IPV6_APPL_CODE, IpV6_NotificationType) (void);

typedef struct
{
  uint8 NrOfChannels;
  IpV6_NotificationType Notification;
} IpV6_ConfigType;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern CONST(IpV6_AddrPrefixType, IPV6_CONST)                  IpV6_PrefixLinkLocal;
extern CONST(IpV6_AddrPrefixType, IPV6_CONST)                  IpV6_PrefixSolicitedNode;
/* PRQA S 0759 5 */ /* MD_MSR_Union */
extern CONST(IpV6_AddrType, IPV6_CONST)                        IpV6_AddrLoopback;
extern CONST(IpV6_AddrType, IPV6_CONST)                        IpV6_AddrUnspecified;
extern CONST(IpV6_AddrType, IPV6_CONST)                        IpV6_AddrAllNodesIL;
extern CONST(IpV6_AddrType, IPV6_CONST)                        IpV6_AddrAllNodesLL;
extern CONST(IpV6_AddrType, IPV6_CONST)                        IpV6_AddrAllRoutersLL;

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  IpV6_InitMemory()
 *********************************************************************************************************************/
/*! \brief         This function has to be called before any other function of this module.
 *  \details      -
 *  \pre           Interrupts must be disabled
 *  \synchronous   TRUE
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_InitMemory(void);


/**********************************************************************************************************************
 *  IpV6_Init()
 *********************************************************************************************************************/
/*! \brief         Initialization of the IpV6 module.
 *  \details      -
 *  \note          This function has to be called after IpV6_InitMemory() and before any other function of this module.
 *  \param[in]     ConfigPtr         Configuration structure for initializing the module
 *  \pre           Interrupts must be disabled
 *  \synchronous   TRUE
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_Init(void);


/**********************************************************************************************************************
 *  IpV6_MainFunctionState()
 *********************************************************************************************************************/
/*! \brief         Periodically called MainFunction that handles the IPv6 global state.
 *  \details       -
 *  \pre           IpV6_InitMemory() and IpV6_Init() must have been called first.
 *  \synchronous   TRUE
 *  \context       TASK
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_MainFunctionState(void);

/**********************************************************************************************************************
 *  IpV6_MainFunctionRx()
 *********************************************************************************************************************/
/*! \brief         Periodically called MainFunction that forwards reassembled IPv6 fragments to the upper-layer.
 *  \details       -
 *  \pre           IpV6_InitMemory() and IpV6_Init() must have been called first.
 *  \synchronous   TRUE
 *  \context       TASK
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_MainFunctionRx(void);

/**********************************************************************************************************************
 *  IpV6_MainFunctionTx()
 *********************************************************************************************************************/
/*! \brief         Periodically called MainFunction that handles transmission of fragmented IPv6 packets.
 *  \details       -
 *  \pre           IpV6_InitMemory() and IpV6_Init() must have been called first.
 *  \synchronous   TRUE
 *  \context       TASK
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_MainFunctionTx(void);


/**********************************************************************************************************************
 *  IpV6_ProvideTxBuffer()
 *********************************************************************************************************************/
/*! \brief         Called by upper layer to get a transmit buffer.
 *  \details       -
 *  \param[in,out] LocalAddrV6IdxPtr   Pointer to IP address identifier of the source address that shall be used.
 *                                     If *AddrIdPtr is not the ID of a local unicast address the value will be
 *                                     overwritten with the id of the automatically selected IPv6 address.
 *  \param[in]     IpV6SocketIdx       index of the socket on which the data should be sent
 *  \param[out]    TxReqDescrPtr       pointer to TX request descriptor (initialized by this function)
 *  \param[in]     DstAddrPtr          IPv6 address of the destination node
 *  \param[out]    BufPtrPtr           pointer to the beginning of the packet payload
 *  \param[in,out] BufLenPtr           minimum desired buffer length.
 *                                     If the function succeeds the available buffer length (>= specified minimum)
 *                                     is returned
 *  \return        BUFREQ_OK           destination is reachable and buffer available.
 *                 BUFREQ_E_OVFL       requested buffer length cannot be provided.
 *                 BUFREQ_E_BUSY       currently no free buffer available, address resolution for destination has been
 *                                     triggered or has not finished yet. Try again later.
 *                 BUFREQ_E_NOT_OK     ProvideTxBuffer of lower layer failed, no source address available or invalid
 *                                     parameters.
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_ProvideTxBuffer(
  IPV6_P2V(TcpIp_LocalAddrIterType)         LocalAddrV6IdxPtr,
  TcpIp_SocketDynIterType                   IpV6SocketIdx,
  IPV6_P2C(IpV6_AddrType)                   DstAddrPtr,
  IPV6_P2V(uint8*)                          BufPtrPtr,
  IPV6_P2V(uint16)                          BufLenPtr,
  IPV6_P2V(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr,
  boolean                                   ForceProvideBuffer);

/**********************************************************************************************************************
 *  IpV6_CancelTransmit()
 *********************************************************************************************************************/
 /*! \brief        Cancel transmit.
 *  \details       This function may be called instead of IpV6_Transmit() in order to free a buffer provided by
 *                 IpV6_ProvideTxBuffer().
 *  \param[in]     TxReqDescrPtr  pointer to TX request descriptor (initialized by IpV6_ProvideTxBuffer())
 *  \note          Cancel transmit is only possible after calling IpV6_ProvideTxBuffer() and before calling IpV6_Transmit()
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_CancelTransmit(
    IPV6_P2C(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr);


/**********************************************************************************************************************
 *  IpV6_Transmit()
 *********************************************************************************************************************/
/*! \brief         Transmit an IPv6 packet.
 *  \details       -
 *  \param[in]     IpV6SocketIdx  TcpIp socket index (used for optimization and tx confirmation)
 *  \param[in]     TxReqDescrPtr  pointer to TX request descriptor (initialized by IpV6_ProvideTxBuffer())
 *  \param[in]     NextHeader     NextHeader value (payload stored in buffer must directly start with this header type)
 *  \param[in]     PayloadLen     length of the payload including the header which has been written to the buffer
 *  \param[in]     TxConfirm      if set to TRUE TcpIp_Udp_TxConfirmation() will be called when the packet has been sent.
 *                                (only valid for UDP packets)
 *  \param[in]     UlTxReqTabIdx  index of a tx request element that is passed back to the UDP in TcpIp_Udp_TxConfirmation()
 *  \param[in]     RetryOnPhysAddrMiss      FALSE: Ethernet buffer is released if physical address has not been resolved yet.
 *                                                 Only Std_ReturnType compatible values (TCPIP_OK, TCPIP_E_NOT_OK) are returned.
 *                                          TRUE:  TCPIP_E_PHYS_ADDR_MISS is returned if physical address has not been resolved yet.
 *                                                 The ethernet buffer is not released in this case.
 *  \return        TCPIP_OK                 operation completed successfully
 *  \return        TCPIP_OK                 operation completed successfully
 *  \return        TCPIP_E_NOT_OK           operation failed
 *  \return        TCPIP_E_PHYS_ADDR_MISS   operation failed because of an ARP cache miss
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(TcpIp_ReturnType, IPV6_CODE) IpV6_Transmit(
  TcpIp_SizeOfSocketDynType                 IpV6SocketIdx,
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr,
  uint8                                     NextHeader,
  uint16                                    PayloadLen,
  boolean                                   TxConfirm,
  uint8                                     UlTxReqTabIdx,
  boolean                                   RetryOnPhysAddrMiss);

/**********************************************************************************************************************
 *  IpV6_GetSrcAddress()
 *********************************************************************************************************************/
/*! \brief         Get the source address which has been stored in the IPv6 header by IpV6_ProvideTxBuffer()
 *  \details       -
 *  \param[in]     IpTxReqDescPtr pointer to IP tx request descriptor (initialized by IpV6_ProvideTxBuffer())
 *  \return        Source address value in the IPv6 header
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(IpV6_AddrType, IPV6_CODE) IpV6_GetSrcAddress(
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr);

/**********************************************************************************************************************
 *  IpV6_SetSrcAddress()
 *********************************************************************************************************************/
/*! \brief         Set the source address into the IPv6 header by IpV6_ProvideTxBuffer()
 *  \details       -
 *  \param[in]     TxReqDescrPtr  pointer to TX request descriptor (initialized by IpV6_ProvideTxBuffer())
 *  \return        E_OK
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_SetSrcAddress(
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  IpV6_AddrType SrcAddr);

/**********************************************************************************************************************
 *  IpV6_VSelectSourceAddress()
 *********************************************************************************************************************/
/*! \brief         Select source address for destination
 *  \details       Get the index of the source address that should be used to reach a specific destination.
 *  \param[in]     IpCtrlIdx      IP Controller Index
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     DstAddrPtr     IPv6 address of the destination that shall be reached
 *  \param[out]    SrcAddrIdxPtr  Index of the source address table entry
 *  \return        E_OK           Suitable address found (Idx is valid)
 *  \return        E_NOT_OK       No suitable address found (Idx unchanged)
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSelectSourceAddress(
  TcpIp_IpV6CtrlIterType                        IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                       DstAddrPtr,
  TCPIP_P2V(TcpIp_SizeOfIpV6SourceAddressType)  SrcAddrIdxPtr);

/**********************************************************************************************************************
 *  IpV6_GetDstAddress()
 *********************************************************************************************************************/
/*! \brief         Get the destination address which has been stored in the IPv6 header by IpV6_ProvideTxBuffer()
 *  \details       -
 *  \param[in]     IpTxReqDescPtr pointer to IP tx request descriptor (initialized by IpV6_ProvideTxBuffer())
 *  \return        Destination address value in the IPv6 header
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(IpV6_AddrType, IPV6_CODE) IpV6_GetDstAddress(
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr);
/**********************************************************************************************************************
 *  IpV6_Ip_RequestIpAddrAssignment
 *********************************************************************************************************************/
/*! \brief        Initiate the local IP address assignment for the IP address specified by IpAddrId.
 *  \details      -
 *  \param[in]    LocalAddrV6Idx      IP address index specifying the IP address for which an
 *                                    assignment shall be initiated.
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    Type                type of IP address assignment which shall be initiated
 *  \param[in]    LocalIpAddrPtr      pointer to structure containing the IP address which shall be
 *                                    assigned to the EthIf controller indirectly specified via
 *                                    LocalAddrId. Note: This parameter is only used in case the
 *                                    parameters Type is set to TCPIP_IPADDR_ASSIGNMENT_STATIC.
 *  \param[in]    Netmask             Network mask of IPv4 address or address prefix of IPv6 address in CIDR Notation.
 *  \param[in]    DefaultRouterPtr    Pointer to struct where the IP address of the default router
 *                                    (gateway) is stored (struct member 'port' is not used and of
 *                                    arbitrary value) (IPv4 only)
 *  \return       E_OK                The request has been accepted
 *                E_NOT_OK            The request has not been accepted
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) IpV6_Ip_RequestIpAddrAssignment(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  TcpIp_IpAddrAssignmentType  Type,
  TCPIP_P2C(IpV6_AddrType)    LocalIpAddrPtr,
  uint8                       Netmask,
  TCPIP_P2C(IpV6_AddrType)    DefaultRouterPtr);


/**********************************************************************************************************************
 *  IpV6_SetAddress()
 *********************************************************************************************************************/
/*! \brief        Assign an IPv6 address to the node.
 *  \details      If the address is already assigned to the node, only the lifetimes will be updated.
 *                Specifying an address with ValidLifetime of zero will remove the address from the node.
 *  \param[in]    LocalAddrV6Idx    Ip address index specified  by caller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    AddressPtr        Address to be assigned/removed (If this parameter is NULL_PTR, the configured default address will be set)
 *  \param[in]    PreferredLifetime Time in seconds this address may be used as preferred address
 *  \param[in]    ValidLifetime     Time in seconds this address is valid
 *  \param[in]    NoDad             Do not perform DAD for this address (address may be used immediately)
 *  \return       E_OK              Address assigned, removed or lifetimes updated
 *  \return       E_NOT_OK          Assignment failed (maximum number of source addresses reached or invalid parameters)
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_SetAddress(
  TcpIp_SizeOfLocalAddrV6Type                        LocalAddrV6Idx,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  boolean                                            NoDad);


/**********************************************************************************************************************
 *  IpV6_GetLocalAddress()
 *********************************************************************************************************************/
/*! \brief        Get address configured for address identifier.
 *  \details      -
 *  \param[in]    LocalAddrV6Idx         Ip address index specified  by caller
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[out]   AddressPtr             Address configured for specified address identifier
 *  \param[out]   AddressPrefixBitLenPtr Length of the CIDR address prefix in bit. (parameter not used if set to NULL_PTR)
 *  \return       E_OK                   Returned valid address
 *  \return       E_NOT_OK               The address identifier is invalid or actually no address configured for this identifier
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_GetLocalAddress(
  TcpIp_LocalAddrV6IterType   LocalAddrV6Idx,
  IPV6_P2V(IpV6_AddrType)     AddressPtr,
  IPV6_P2V(uint8)             AddressPrefixBitLenPtr);


/**********************************************************************************************************************
 *  IpV6_GetDefaultRouterAddress()
 *********************************************************************************************************************/
/*! \brief        Get address of a default router of an IP controller.
 *  \details      -
 *  \param[in]    LocalAddrV6Idx         Ip address index specified  by caller
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[out]   RouterAddrPtr          IPv6 address of the default router.
 *  \param[out]   RouterIsReachablePtr   Specifies whether the link-layer address of the router is in the Neighbor Chache.
 *  \return       E_OK                   Default router returned.
 *  \return       E_NOT_OK               No default router available.
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_GetDefaultRouterAddress(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2V(IpBase_AddrIn6Type) RouterAddressPtr,
  IPV6_P2V(boolean)            RouterIsReachablePtr);


/**********************************************************************************************************************
 *  IpV6_SetTrafficClass()
 *********************************************************************************************************************/
/*! \brief        Set value of 'Traffic Class' field in IPv6 header for all packets sent over a specific socket.
 *                (override controller specific default)
 *  \details      -
 *  \param[in]    IpV6SocketIdx     TcpIp socket index
 *  \param[in]    TrafficClass      Value of the 'Traffic Class' field.
 *                                  (see [RFC2460 3. IPv6 Header Format, 7. Traffic Classes])
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_SetTrafficClass(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint8                   TrafficClass);


/**********************************************************************************************************************
 *  IpV6_SetFlowLabel()
 *********************************************************************************************************************/
/*! \brief        Set value of 'Flow Label' field in IPv6 header for all packets sent over a specific socket.
 *                (override controller specific default)
 *  \details      -
 *  \param[in]    IpV6SocketIdx     TcpIp socket index
 *  \param[in]    FlowLabel         Value of the 'Flow Label' field. (the most 12 significant bits will be ignored)
 *                                  (see [RFC2460 3. IPv6 Header Format, 6. Flow Labels])
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_SetFlowLabel(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint32                  FlowLabel);


/**********************************************************************************************************************
 *  IpV6_SetHopLimit()
 *********************************************************************************************************************/
/*! \brief        Set value of 'Hop Limit' field in IPv6 header for all packets sent over a specific socket.
 *                (override controller specific default)
 *  \details      -
 *  \param[in]    IpV6SocketIdx     TcpIp socket index
 *  \param[in]    HopLimit          'Hop Limit' value that shall be set in the IPv6 header of outgoing packets of the
 *                                  socket.
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_SetHopLimit(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint8                   HopLimit);


/**********************************************************************************************************************
 *  IpV6_SetEthIfFramePrio()
 *********************************************************************************************************************/
/*! \brief        Set 'EthIf Frame Priority' for all packets sent over a specific socket.
 *                (override controller specific default)
 *  \details      -
 *  \param[in]    IpV6SocketIdx     TcpIp socket index
 *  \param[in]    FramePrio         VLAN frame priority value (0..7)
 *  \return       E_OK              success
 *  \return       E_NOT_OK          invalid priority value
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_SetEthIfFramePrio(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint8                   FramePrio);


/**********************************************************************************************************************
 *  IpV6_ResetSocket()
 *********************************************************************************************************************/
/*! \brief        Reset socket specific parameters like 'Hop Limit', 'Traffic Class', 'Flow Label' and
 *                'EthIf Frame Priority' to the controller specific defaults.
 *  \details      -
 *  \param[in]    IpV6SocketIdx      TcpIp socket index
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_ResetSocket(
  TcpIp_IpV6SocketDynIterType IpV6SocketIdx);


/**********************************************************************************************************************
 *  IpV6_IsValidDestinationAddress()
 *********************************************************************************************************************/
/*! \brief        Determine whether or not an IPv6 address is a valid destination address.
 *  \details      Before calling IpV6_ProvideTxBuffer() the destination address should be checked for validity using
 *                this function.
 *                The following destination addresses are invalid:
 *                 - Multicast addresses with interface-local scope.
 *                 - The Loopback address [::1]
 *                 - The Unspecified (all-zeros) address [::]
 *                 - Any address assigned to this node
 *  \param[in]    IpCtrlIdx      ip controller index
 *  \param[in]    DstAddrPtr     Destination address to be checked.
 *  \return       TRUE           Address is a valid destination address
 *  \return       FALSE          Address is NOT a valid destination address
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(boolean, IPV6_CODE) IpV6_IsValidDestinationAddress(
  TcpIp_SizeOfIpV6CtrlType IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType) DstAddrPtr);


/**********************************************************************************************************************
 *  IpV6_GetLocalAddressCfgSrc()
 *********************************************************************************************************************/
/*! \brief        Determine the configuration source of an address assigned to this node.
 *  \details      -
 *  \param[in]    LocalAddrV6Idx Ip address index specified  by caller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[out]   CfgSrcPtr      Configuration source of the given address
 *  \return       TRUE           Address is a valid destination address
 *  \return       E_OK           Address assigned to this node. Configuration source has been stored in *CfcSrcPtr.
 *  \return       E_NOT_OK       Address is NOT assigned to this node. *CfgSrcPtr not modified.
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(uint8, IPV6_CODE) IpV6_GetLocalAddressCfgSrc(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx);


/**********************************************************************************************************************
 *  IpV6_GetCurrentHopLimit()
 *********************************************************************************************************************/
/*! \brief         Get current HopLimit value of IP controller.
 *                 This may be the configured HopLimit or the dynamically set value by Router Advertisements
 *  \details       -
 *  \param[in]     IpCtrlIdx     ip controller index
 *  \return        HopLimit value
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(uint8, IPV6_CODE) IpV6_GetCurrentHopLimit(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_GetPhysAddr()
 *********************************************************************************************************************/
/*! \brief        Get physical address of IP controller
 *  \details      -
 *  \param[in]    IpCtrlIdx     ip controller index
 *  \param[out]   PhysAddrPtr   physical address
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_GetPhysAddr(TcpIp_IpV6CtrlIterType IpCtrlIdx, IPV6_P2V(uint8) PhysAddrPtr);

/**********************************************************************************************************************
 *  IpV6_GetPhysAddrByIpAddrId
 *********************************************************************************************************************/
/*! \brief        Obtains the physical source address used by the EthIf controller implicitly specified via IpAddrId.
 *  \details      -
 *  \param[in]    IpAddrId           Local address identifier implicitely specifing the EthIf controller for which the
 *                                   physical address shall be obtained.
 *  \param[out]   PhysAddrPtr        Pointer to the memory where the physical source address (MAC address) in network
 *                                   byte order is stored
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) IpV6_GetPhysAddrByIpAddrId(
  TcpIp_LocalAddrV6IterType LocalAddrV6Idx,
  IPV6_P2V(uint8)           PhysAddrPtr);

/**********************************************************************************************************************
 *  IpV6_GetRemotePhysAddr
 *********************************************************************************************************************/
/*! \brief        Lookup the physical address for a remote network address.
 *  \details      TcpIp_GetRemotePhysAddr queries the IP/physical address translation table specified by CtrlIdx and
 *                returns the physical address related to the IP address specified by IpAddrPtr. In case no physical
 *                address can be retrieved and parameter initRes is TRUE, address resolution for the specified IP
 *                address is initiated on the local network.
 *  \param[in]    EthIfCtrlIdx        EthIf controller index to identify the related ARP/NDP table.
 *  \param[in]    IpAddrPtr           specifies the IP address for which the physical address shall be retrieved
 *  \param[in]    initRes             specifies if the address resolution shall be initiated (TRUE) or not (FALSE) in
 *                                    case the physical address related to the specified IP address is currently
 *                                    unknown.
 *  \param[out]   PhysAddrPtr         Pointer to the memory where the physical address (MAC address) related to the
 *                                    specified IP address is stored in network byte order.
 *  \return       TCPIP_E_OK               specified IP address resolved, physical address provided via PhysAddrPtr
 *                TCPIP_E_PHYS_ADDR_MISS   physical address currently unknown (address resolution initiated if initRes set to TRUE)
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(TcpIp_ReturnType, TCPIP_CODE) IpV6_GetRemotePhysAddr(
  TcpIp_SizeOfEthIfCtrlType EthIfCtrlIdx,
  TCPIP_P2C(IpV6_AddrType)  IpAddrPtr,
  TCPIP_P2V(uint8)          PhysAddrPtr,
  boolean                   InitRes);

/**********************************************************************************************************************
 *  IpV6_IsAddrIdAcceptable()
 *********************************************************************************************************************/
/*! \brief        This function checks whether the address identifier of a received packet is acceptable for a socket
 *                bound to a specific address identifier.
 *  \details      The check is performed according to the acceptance filter given in [SWS_TCPIP_00106].
 *  \param[in]    BindLocalAddrV6Idx  Ip address identifier to which the socket has been bound
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    RecvLocalAddrV6Idx  Ip address identifier of the received packet
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[out]   MatchType           specifies the type of the match (e.g. TCPIP_IF_MATCH, TCPIP_EXACT_MATCH)
 *  \return       TRUE                packet is acceptable
 *  \return       FALSE               packet is not acceptable
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(boolean, IPV6_CODE) IpV6_IsAddrIdAcceptable(
  TcpIp_LocalAddrV6IterType   BindLocalAddrV6Idx,
  TcpIp_LocalAddrV6IterType   RecvLocalAddrV6Idx,
  IPV6_P2V(uint8)             MatchType);

/**********************************************************************************************************************
 * IpV6_CmpNetAddr
 *********************************************************************************************************************/
/*! \brief        Compare two IPv6 addresses.
 *  \details      -
 *  \param[in]    NetAddr1Ptr   first address
 *  \param[in]    NetAddr2Ptr   second address
 *  \return       TRUE          addresses are equal
 *                FALSE         addresses are not equal
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(boolean, IPV6_CODE) IpV6_CmpNetAddr(
  IPV6_P2C(IpV6_AddrType) NetAddr1Ptr,
  IPV6_P2C(IpV6_AddrType) NetAddr2Ptr);



/**********************************************************************************************************************
 *  IpV6_TrcvLinkStateChgInternal
 *********************************************************************************************************************/
/*! \brief          Called by TcpIp on request communication mode.
 *  \details        -
 *  \param[in]      EthIfCtrlIdx  Controller index
 *  \param[in]      TrcvLinkState Transceiver link state
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV6_TrcvLinkStateChgInternal(
  uint8                 EthIfCtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState);

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */
#endif  /* IPV6_H */
/**********************************************************************************************************************
 *  END OF FILE: IpV6.h
 *********************************************************************************************************************/
