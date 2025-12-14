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
 *         \file  TcpIp_IpV6_Priv.h
 *        \brief  Implementation of Internet Protocol version 6 (IPv6) - Internal Functions
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv6 submodule. >> TcpIp_IpV6.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

#if !defined(IPV6_PRIV_H)
#define IPV6_PRIV_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_IpV6.h"
#include "SchM_TcpIp.h"

#include "Platform_Types.h"

#include "TcpIp_Priv.h"

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
# include "TcpIp_DhcpV6.h"
#endif

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* Macros improve code readability */

#define IPV6_ETHER_TYPE_ID                  0x86DDu /* network byte order */

#define IPV6_HEADER_VERSION                      6uL /* IPv6 version number */
#define IPV6_HEADER_NXT_HDR_FIELD_OFFS           6u /* position of NextHeader field in IPv6 header */
#define IPV6_HEADER_PLD_LEN_FIELD_OFFS           4u /* position of PayloadLength field in IPv6 header */

#define IPV6_MINIMUM_MTU                      1280U /* Minimum MTU value that every host must accept [RFC2460] */

# define IPV6_VENABLE_INTERNAL_DET_CHECKS    STD_OFF

#define IPV6_RSHIFT_DIV_2                        1u /*!< devide integer by  2 using right bitshift */
#define IPV6_RSHIFT_DIV_4                        2u /*!< devide integer by  4 using right bitshift */
#define IPV6_RSHIFT_DIV_8                        3u /*!< devide integer by  8 using right bitshift */
#define IPV6_RSHIFT_DIV_16                       4u /*!< devide integer by 16 using right bitshift */

#define IPV6_LSHIFT_MUL_2                        1u /*!< multiply integer by  2 using left bitshift */
#define IPV6_LSHIFT_MUL_4                        2u /*!< multiply integer by  4 using left bitshift */
#define IPV6_LSHIFT_MUL_8                        3u /*!< multiply integer by  8 using left bitshift */
#define IPV6_LSHIFT_MUL_16                       4u /*!< multiply integer by 16 using left bitshift */

#define IPV6_MASK_MOD_2                        0x01u /*!< use mask instead of modulo division by  2 */
#define IPV6_MASK_MOD_4                        0x03u /*!< use mask instead of modulo division by  4 */
#define IPV6_MASK_MOD_8                        0x07u /*!< use mask instead of modulo division by  8 */
#define IPV6_MASK_MOD_16                       0x0Fu /*!< use mask instead of modulo division by 16 */


/* compare results */
#define IPV6_CMP_RES_NO_PREFERENCE               0u
#define IPV6_CMP_RES_PREFER_A                    1u
#define IPV6_CMP_RES_PREFER_B                    2u

#define IPV6_MULTI_CONTROLLER_SUPPORT            (1 < IPV6_MAX_NUM_CONTROLLERS)

#define TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx) TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx)

#define IPV6_ADDR_ASSIGNMENT_FORGET   0x00U
#define IPV6_ADDR_ASSIGNMENT_STORE    0x01U

#define IPV6_MAX_ETHIF_FRAME_PRIO        7U

#define IPV6_DAD_FAIL_NS                 1u
#define IPV6_DAD_FAIL_NA                 2u

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
# define IPV6_FRAG_STATUS_UNUSED      0xFFU
# define IPV6_FRAG_STATUS_ACTIVE         0U
# define IPV6_FRAG_STATUS_COMPLETE       1U
# define IPV6_FRAG_STATUS_TOO_BIG        2U
# define IPV6_FRAG_STATUS_SEGM_ERROR     3U
# define IPV6_FRAG_STATUS_INV_UNFRAG_LEN 4U
#endif

#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
#define IPV6_FRAG_TX_STATUS_UNUSED       0U
#define IPV6_FRAG_TX_STATUS_PROVIDED     1U
#define IPV6_FRAG_TX_STATUS_TRANSMIT     2U
#endif

#define IPV6_DBG_COUNTER_RX_INC(VAR)

#define IPV6_DBG_COUNTER_TX_INC(VAR)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# define IPV6_CHANGE_STATE(IpCtrlIdx, NEW_STATE) TcpIp_SetCtrlStateOfIpV6CtrlDyn(IpCtrlIdx, NEW_STATE)

#if (TCPIP_SUPPORT_IPV6_ETHIF_ADDR_FILTER_API == STD_ON)
# define IPV6_VJOIN_MULTICAST_GROUP(IP_CTRL_IDX, ADDR_PTR, JOIN)                 (void)IpV6_VJoinMulticastGroup((IP_CTRL_IDX), (ADDR_PTR), (JOIN))
# define IPV6_VJOIN_SOLICITED_NODE_MULTICAST_GROUP(IP_CTRL_IDX, ADDR_PTR, JOIN)  IpV6_VJoinSolicitedNodeMulticastGroup((IP_CTRL_IDX), (ADDR_PTR), (JOIN))
#else
# define IPV6_VJOIN_MULTICAST_GROUP(IP_CTRL_IDX, ADDR_PTR, JOIN)
# define IPV6_VJOIN_SOLICITED_NODE_MULTICAST_GROUP(IP_CTRL_IDX, ADDR_PTR, JOIN)
#endif

/* Development Error Tracer */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
# define IpV6_CheckDetErrorReturnVoid(CONDITION, API_ID, ERROR_CODE) { if(!(CONDITION)) { \
  (void)Det_ReportError(IPV6_MODULE_ID, IPV6_VINSTANCE_ID, (API_ID), (ERROR_CODE)); return; }}

# define IpV6_CheckDetErrorReturnValue(CONDITION, API_ID, ERROR_CODE, RET_VAL) { if(!(CONDITION)) { \
  (void)Det_ReportError(IPV6_MODULE_ID, IPV6_VINSTANCE_ID, (API_ID), (ERROR_CODE)); return (RET_VAL); }}

# define IpV6_CheckDetErrorContinue(CONDITION, API_ID, ERROR_CODE) { if(!(CONDITION)) { \
  (void)Det_ReportError(IPV6_MODULE_ID, IPV6_VINSTANCE_ID, (API_ID), (ERROR_CODE)); }}

# define IpV6_DetReportError(API_ID, ERROR_CODE) (void)Det_ReportError(IPV6_MODULE_ID, IPV6_VINSTANCE_ID, (API_ID), (ERROR_CODE))
#else
# define IpV6_CheckDetErrorReturnVoid(CONDITION, API_ID, ERROR_CODE)
# define IpV6_CheckDetErrorReturnValue(CONDITION, API_ID, ERROR_CODE, RET_VAL)
# define IpV6_CheckDetErrorContinue(CONDITION, API_ID, ERROR_CODE)
# define IpV6_DetReportError(API_ID, ERROR_CODE)
#endif /* (IPV6_DEV_ERROR_REPORT == STD_ON) */

#if (IPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
# define IpV6_DetReportInternalError(ERROR_CODE) IpV6_DetReportError(IPV6_API_ID_V_INTERNAL_FUNCTION, ERROR_CODE)
#else
# define IpV6_DetReportInternalError(ERROR_CODE)
#endif

#define IPV6_CALC_EXT_HEADER_LENGTH(OPT_LEN_BYTE) (8u + (8u * (OPT_LEN_BYTE)))

/* Timestamp handling functions */

#define IPV6_TIME_ADD_MS(TIME_VAR, MSECS)             IpV6_VTimeAddMs(&(TIME_VAR), (MSECS))
#define IPV6_SET_LIFETIME_S(TIME_VAR, LIFETIME_S, NEXT_EVENT_TIME_VAR_PTR)   IpV6_VSetLifetimeS(&(TIME_VAR), (LIFETIME_S), (NEXT_EVENT_TIME_VAR_PTR))
#define IPV6_TIME_SET_INFINITY(TIME_VAR)            ((TIME_VAR).S = IPV6_LIFETIME_UNLIMITED)

#define IPV6_TIME_IS_LOWER(TIMEA, TIMEB)              IpV6_VTimeCompare(TIMEA, TIMEB)
#define IPV6_TIME_EXPIRED(TIME_VAR)                   (IPV6_TIME_IS_LOWER((TIME_VAR), IpV6_Time))
#define IPV6_SET_CURRENT_TIME(TIME_VAR)               ((TIME_VAR) = IpV6_Time)

#define IPV6_TIME_SET(TIME_VAR, S_VAL, MS_VAL)        IpV6_VTimeSet(&(TIME_VAR), (S_VAL), (MS_VAL))
#define IPV6_SET_EVENT_TIME_MS(TIME_VAR, TIME_MS)     IpV6_VSetEventTime(&(TIME_VAR), (TIME_MS))


#define IPV6_MIN(VALUE1, VALUE2)             (((VALUE1) < (VALUE2)) ? (VALUE1) : (VALUE2))

#define IPV6_PREFIX_LEN_BYTE                     8u /* 64 bit prefix */
#define IPV6_INTERFACE_IDENTIFIER_LEN_BYTE       8u /* 64 bit interface identifier */

#define IPV6_CMP_64BIT_PREFIX(ADDR1, ADDR2)               (IpV6_MemCmp(&(ADDR1).addr[0], &(ADDR2).addr[0], IPV6_PREFIX_LEN_BYTE))
#define IPV6_CMP_64BIT_INTERFACE_IDENTIFIER(ADDR1, ADDR2) (IpV6_MemCmp(&(ADDR1).addr[IPV6_PREFIX_LEN_BYTE], &(ADDR2).addr[IPV6_PREFIX_LEN_BYTE], (IPV6_INTERFACE_IDENTIFIER_LEN_BYTE)))

#define TCPIP_IPV6_SRC_ADDR_IDX_INV               TcpIp_GetSizeOfIpV6SourceAddress()
#define TCPIP_IPV6_MC_ADDR_IDX_INV                TcpIp_GetSizeOfIpV6MulticastAddr()

#define IPV6_UNUSED_PARAMETER(VAR_NAME) TCPIP_DUMMY_STATEMENT(VAR_NAME)

#define IPV6_SOCKET_DATA_FLAG_ETHIF_FRAME_PRIO   1u
#define IPV6_SOCKET_DATA_FLAG_HOP_LIMIT          2u
#define IPV6_SOCKET_DATA_FLAG_TRAFFIC_CLASS      4u
#define IPV6_SOCKET_DATA_FLAG_FLOW_LABEL         8u

#define IPV6_GET_SOCKET_ETHIF_FRAME_PRIO(IpCtrlIdx, IpV6SocketIdx) ((0u != (TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) & IPV6_SOCKET_DATA_FLAG_ETHIF_FRAME_PRIO)) ? TcpIp_GetEthIfFramePrioOfIpV6SocketDyn(IpV6SocketIdx) : TcpIp_GetFramePrioDefaultOfIpV6Ctrl(IpCtrlIdx))
#define IPV6_GET_SOCKET_HOP_LIMIT(IpCtrlIdx, IpV6SocketIdx)        ((0u != (TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) & IPV6_SOCKET_DATA_FLAG_HOP_LIMIT       )) ? TcpIp_GetHopLimitOfIpV6SocketDyn(IpV6SocketIdx)       : TcpIp_GetCurHopLimitOfIpV6CtrlDyn(IpCtrlIdx))

/* Byte-Order conversion macros */

/* PRQA L:FctLikeMacros */


/* Critical section defines */
#define IPV6_BEGIN_CRITICAL_SECTION()     SchM_Enter_TcpIp_TCPIP_EXCLUSIVE_AREA_0()
#define IPV6_END_CRITICAL_SECTION()       SchM_Exit_TcpIp_TCPIP_EXCLUSIVE_AREA_0()

#define IPV6_BEGIN_CRITICAL_SECTION_SAT() IPV6_BEGIN_CRITICAL_SECTION()
#define IPV6_END_CRITICAL_SECTION_SAT()   IPV6_END_CRITICAL_SECTION()

#define IPV6_BEGIN_CRITICAL_SECTION_DC()  IPV6_BEGIN_CRITICAL_SECTION()
#define IPV6_END_CRITICAL_SECTION_DC()    IPV6_END_CRITICAL_SECTION()

#define IPV6_BEGIN_CRITICAL_SECTION_NC()  IPV6_BEGIN_CRITICAL_SECTION()
#define IPV6_END_CRITICAL_SECTION_NC()    IPV6_END_CRITICAL_SECTION()

#define IPV6_BEGIN_CRITICAL_SECTION_PL()  IPV6_BEGIN_CRITICAL_SECTION()
#define IPV6_END_CRITICAL_SECTION_PL()    IPV6_END_CRITICAL_SECTION()

#define IPV6_BEGIN_CRITICAL_SECTION_DRL() IPV6_BEGIN_CRITICAL_SECTION()
#define IPV6_END_CRITICAL_SECTION_DRL()   IPV6_END_CRITICAL_SECTION()

#define IPV6_BEGIN_CRITICAL_SECTION_DOPT() IPV6_BEGIN_CRITICAL_SECTION()
#define IPV6_END_CRITICAL_SECTION_DOPT()   IPV6_END_CRITICAL_SECTION()

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(uint8, IPV6_VAR_ZERO_INIT) IpV6_State;

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(IpV6_TimeType, IPV6_VAR_NOINIT) IpV6_Time;

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * IpV6_VGetSolicitedNodeAddr
 *********************************************************************************************************************/
/*! \brief         Obtain solicited node multicast address from network address
 *  \details       -
 *  \param[in]     MulticastAddrPtr    Solicited node multicast address
 *  \param[in]     NetAddrPtr          Solicited network address
 *  \param[in]     Scope               Scope of the address
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VGetSolicitedNodeAddr(
  IPV6_P2V(IpV6_AddrType) MulticastAddrPtr,
  IPV6_P2C(IpV6_AddrType) NetAddrPtr,
  IpV6_MulticastScopeType Scope);

/**********************************************************************************************************************
 *  IpV6_MemSet()
 *********************************************************************************************************************/
/*! \brief         Fill target buffer with given value
 *  \details       -
 *  \param[in]     TargetPtr     Target buffer
 *  \param[in]     Value         Fill value
 *  \param[in]     Length        Length of buffer
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_MemSet(
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_DATA) TargetPtr, uint8 Value, uint16 Length);

/**********************************************************************************************************************
 *  IpV6_MemCmp()
 *********************************************************************************************************************/
/*! \brief         Compare two buffers
 *  \details       -
 *  \param[in]     Data1Ptr     Data Buffer 1
 *  \param[in]     Data2Ptr     Data Buffer 2
 *  \param[in]     Blocks       Length in bytes
 *  \return        TRUE         Buffers are the similar
 *  \return        FALSE        Buffers are not similar
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(boolean, IPV6_CODE) IpV6_MemCmp(
  IPV6_P2C(uint8) Data1Ptr,
  IPV6_P2C(uint8) Data2Ptr,
  uint8 Blocks);

/**********************************************************************************************************************
 *  IpV6_VGetAddrType()
 *********************************************************************************************************************/
/*! \brief         Determine the type of an IPv6 address according to RFC4291 2.4.
 *  \details       -
 *  \param[in]     pointer to the IPv6 address
 *  \return        IPV6_ADDR_TYPE_MULTICAST    address is a multicast address
 *  \return        IPV6_ADDR_TYPE_LL_UNICAST   address is a link-local unicast address
 *  \return        IPV6_ADDR_TYPE_LOOPBACK     address is the local loopback address
 *  \return        IPV6_ADDR_TYPE_UNSPECIFIED  address is the unspecified (all-zeros) address
 *  \return        IPV6_ADDR_TYPE_UNICAST      address is a unicast address (none of the special types above)
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(IpV6_AddrTypeType, IPV6_CODE) IpV6_VGetAddrType(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) AddrPtr);

/* PREFIX LIST FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VMatchPrefix()
 *********************************************************************************************************************/
/*! \brief         Determine if a given prefix does match to a specific address
 *  \details       -
 *  \param[in]     AddrPtr    pointer to the address that will be machted against the prefix
 *  \param[in]     PrefixPtr  pointer to the prefix
 *  \return        TRUE       the address starts with the given prefix
 *  \return        FALSE      the address does not start with the given prefix
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VMatchPrefix(
  IPV6_P2C(IpV6_AddrType) AddrPtr,
  IPV6_P2C(uint8)         PrefixPtr,
  uint8                   PrefixLenBits);

#if (TCPIP_IPV6STATICONLINKPREFIX == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VIsStaticOnLinkPrefix()
 *********************************************************************************************************************/
/*! \brief         Determines whether a prefix is coverd by a statically configured prefix in the on link prefix list.
 *  \details       -
 *  \param[in]     IpCtrlIdx     IP controller index
 *  \param[in]     PrefixPtr     Prefix that shall be searched in the prefix list.
 *  \param[in]     PrefixBitLen  Length (in bits) of the prefix at PrefixPtr.
 *  \return        TRUE          Prefix is covered by one of the entries in the static on link prefix list.
 *  \return        FALSE         Prefix is not covered by any entry in the static on link prefix list.
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(boolean, IPV6_CODE) IpV6_VIsStaticOnLinkPrefix(
  TcpIp_IpV6CtrlIterType  IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType) PrefixPtr,
  uint8                   PrefixBitLen);
#endif

/**********************************************************************************************************************
 *  IpV6_VIsDestinationOnLink()
 *********************************************************************************************************************/
/*! \brief         Verify if the given address is on link for the Ip controller
 *  \details       -
 *  \param[in]     IpCtrlIdx           Index of Ip Controller
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     DstAddrPtr          Destination address
 *  \return        TRUE                Destination is on link
 *  \return        FALSE               Destination not on link
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, IPV6_CODE) IpV6_VIsDestinationOnLink(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr);

/* DEFAULT ROUTER TABLE FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VGetDefaultRouterAddr()
 *********************************************************************************************************************/
/*! \brief         Obtain default router address to reach a destination
 *  \details       -
 *  \param[in]     IpCtrlIdx                  Index of Ip Controller
 *                                            CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     IpCtrlIdx                  Index of local IpV6 Address
 *                                            CONSTRAINT: [0...TcpIp_GetSizeOfIpV6Addr()-1]
 *  \param[in]     DstAddrPtr                 Destination address
 *  \param[in]     IsReachable                Flag specifies if address is reachable
 *  \param[out]    DrlEntryIdxPtr             Index from where Default router address is obtained
 *  \return        E_OK                       Default router was found and DrlEntryIdxPtr was updated.
 *  \return        E_NOT_OK                   No default router available.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VGetDefaultRouterAddr(
  TcpIp_IpV6CtrlIterType                               IpCtrlIdx,
  TcpIp_LocalAddrV6IterType                            LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)                              DstAddrPtr,
  IPV6_P2V(boolean)                                    IsReachable,
  IPV6_P2V(TcpIp_SizeOfIpV6DefaultRouterListEntryType) DrlEntryIdxPtr);

/* SOURCE ADDRESS HANDLING FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VBuildSourceAddress()
 *********************************************************************************************************************/
/*! \brief         Create a source IPv6 address from an interface identifier and prefix
 *  \details       -
 *  \param[in]     IfIdPtr         pointer to the interface identifier
 *  \param[in]     PrefixPtr       pointer to an IPv6 address that starts with the given prefix
 *  \param[in]     PrefixLenBits   length of the prifix in bits (1-128)
 *  \param[out]    SrcAddrPtr      pointer to an IPv6 address variable where the source address is written to
 *  \return        E_OK            no error
 *  \return        E_NOT_OK        the prefix length does not fit to the interface identifier length
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VBuildSourceAddress(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) IfIdPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) PrefixPtr,
  P2VAR(IpV6_AddrType, AUTOMATIC, IPV6_APPL_VAR) SrcAddrPtr);

/**********************************************************************************************************************
 *  IpV6_VSATCreateEntry()
 *********************************************************************************************************************/
/*! \brief          Create source address table entry for given address
 *  \details        -
 *  \param[in]      SrcAddrPtr   Source address to create
 *  \param[in,out]  EntryIdxPtr  Index of the created entry
 *  \return         E_OK         Source address table entry createds
 *  \return         E_NOT_OK     Entry not created
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSATCreateEntry(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) SrcAddrPtr,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR) EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_VSATLookupPrefix()
 *********************************************************************************************************************/
/*! \brief           Lookup index of an entry in the source address table by address prefix
 *  \details         -
 *  \param[in]       IpCtrlIdx      ip controller index
 *  \param[in]       AddrPrefixPtr  ip address prefix (64bit)
 *  \param[in,out]   CtrlAddrIdxPtr in: start index, out: matching index
 *  \param[in]       AddrCfgSrc     Filter for specific configuration source of address.
 *                                  (If set to IPV6_ADDR_CFG_SRC_UNSPECIFIED, CfgSrc is ignored)
 *  \return          E_OK      entry has been found (EntryIdx is valid)
 *  \return          E_NOT_OK  entry not found (EntryIdx unchanged)
 *  \pre             -
 *  \synchronous     TRUE
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSATLookupPrefix(
  TcpIp_IpV6CtrlIterType                      IpCtrlIdx,
  IPV6_P2C(uint8)                             AddrPrefixPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressType) SrcAddrIdxPtr,
  uint8                                       AddrCfgSrc);

/**********************************************************************************************************************
 *  IpV6_VSATLookup()
 *********************************************************************************************************************/
/*! \brief         Look up given address in the source address table
 *  \details       -
 *  \param[in]     IpCtrlIdx             Index of Ip Controller
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     SrcAddrPtr            Address to be looked up
 *  \param[in]     SrcAddrIdxPtr         Source address index of the SAT entry
 *                                       Valid only if SAT entry found
 *  \return        E_OK                  SAT entry was found
 *  \return        E_NOT_OK              No SAT entry found
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSATLookup(
  TcpIp_IpV6CtrlIterType                                             IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_VAR)                   SrcAddrPtr,
  P2VAR(TcpIp_SizeOfIpV6SourceAddressType, AUTOMATIC, IPV6_APPL_VAR) SrcAddrIdxPtr
  );

/**********************************************************************************************************************
 *  IpV6_VSATRemoveEntry()
 *********************************************************************************************************************/
/*! \brief         Remove an entry from the source address table
 *  \details       -
 *  \param[in]     SrcAddrIdx     Ip address index
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VSATRemoveEntry(TcpIp_SizeOfIpV6SourceAddressType SrcAddrIdx);

/**********************************************************************************************************************
 *  IpV6_VSATRemoveAllEntries()
 *********************************************************************************************************************/
/*! \brief         Invalidate all SAT entries
 *  \details       -
 *  \param[in]     IpCtrlIdx      Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VSATRemoveAllEntries(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_VHandleDADFailure()
 *********************************************************************************************************************/
/*! \brief         Handle duplicate address detection
 *  \details       -
 *  \param[in]     PhysAddrPtr       Remote physical address
 *  \param[in]     IpV6SrcAddrIdx    Source address index of duplicate address
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]     EventType         Debug print message type
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VHandleDADFailure(
  IPV6_P2C(uint8)                   PhysAddrPtr,
  TcpIp_SizeOfIpV6SourceAddressType IpV6SrcAddrIdx,
  uint8                             EventType);


/**********************************************************************************************************************
 *  IpV6_VHandleSourceAddrAssignmentChange()
 *********************************************************************************************************************/
/*! \brief         Handle source address assignment change
 *  \details       -
 *  \param[in]     IpV6SrcAddrIdx  Source address index which is getting changed
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]     AddrAssigned    TRUE   Ip address is ready for use
 *                                 FALSE  Ip address not ready for use
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VHandleSourceAddrAssignmentChange(
  TcpIp_IpV6SourceAddressIterType    IpV6SrcAddrIdx,
  boolean                            AddrAssigned);

#if (TCPIP_SUPPORT_IPV6_ETHIF_ADDR_FILTER_API == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VJoinMulticastGroup()
 *********************************************************************************************************************/
/*! \brief         Subscribe to multicast group
 *  \details       -
 *  \param[in]     IpCtrlIdx           Index of Ip Controller
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     MulticastAddrPtr    Multicast address to subscribe to
 *  \param[in]     Join                TRUE   Join multicast group
 *                                     FALSE  Leave multicast group
 *  \return        E_OK                Multicast group added to physical address table
 *  \return        E_NOT_OK            Multicast group was not added to physical address table
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VJoinMulticastGroup(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) MulticastAddrPtr,
  boolean                                           Join);

/**********************************************************************************************************************
 *  IpV6_VJoinSolicitedNodeMulticastGroup()
 *********************************************************************************************************************/
/*! \brief         Obtain the solicited node multicast address and join the multicast group
 *  \details       -
 *  \param[in]     IpCtrlIdx           Index of Ip Controller
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     UnicastAddrPtr      Solicited node address
 *  \param[in]     Join                TRUE   Join solicited node group
 *                                     FALSE  Leave solicited node group
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VJoinSolicitedNodeMulticastGroup(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) UnicastAddrPtr,
  boolean                                           Join);
#endif

/**********************************************************************************************************************
 *  IpV6_VGetRandomValue()
 *********************************************************************************************************************/
/*! \brief         Get a random value between [MinValue...MaxValue]
 *  \details       -
 *  \param[in]     MinValue   minimum value
 *  \param[in]     MaxValue   maximum value
 *  \return        Random value between [MinValue...MaxValue]
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(uint32, IPV6_CODE) IpV6_VGetRandomValue(uint32 MinValue, uint32 MaxValue);

/**********************************************************************************************************************
 *  IpV6_VRandomizeValue()
 *********************************************************************************************************************/
/*! \brief       Randomize a value by multiplying it with a random factor
 *  \details     -
 *  \param[in]   BaseValue value to be multiplied with random factor
 *  \return      BaseValue multiplied with random factor
 *  \pre         -
 *  \synchronous   TRUE
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *********************************************************************************************************************/
FUNC(uint32, IPV6_CODE) IpV6_VRandomizeValue(
  TcpIp_IpV6CtrlIterType  IpCtrlIdx,
  uint32 BaseValue);

/* TIMESTAMP FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VSetEventTime()
 *********************************************************************************************************************/
/*! \brief        Configure the next event timestamp by adding value to the IpV6 time
 *  \details      -
 *  \param[out]   TimestampPtr       Timestamp to update
 *  \param[in]    Miliseconds        Milliseconds to add
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VSetEventTime(
  P2VAR(IpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                            Milliseconds);

/**********************************************************************************************************************
 *  IpV6_VTimeCompare()
 *********************************************************************************************************************/
/*! \brief        Compare reference timestamp with given timestamp and return TRUE if ref time is lower
 *  \details      -
 *  \param[in]    RefTimestamp      Reference timestamp
 *  \param[in]    Timestamp         Timestamp to check
 *  \return       TRUE              Reference Timestamp is lower
 *  \return       FALSE             Given Timestamp is lower
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) IpV6_VTimeCompare(
  IpV6_TimeType RefTimestamp,
  IpV6_TimeType Timestamp);

/**********************************************************************************************************************
 *  IpV6_VTimeSet()
 *********************************************************************************************************************/
/*! \brief        Set timestamp variable with given value
 *  \details      -
 *  \param[out]   TimestampPtr       Timestamp variable to update
 *  \param[in]    Seconds            Seconds to add
 *  \param[in]    Miliseconds        Milliseconds to add
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) IpV6_VTimeSet(
  P2VAR(IpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)   TimestampPtr,
  uint32                                             Seconds,
  uint32                                             Milliseconds);

/**********************************************************************************************************************
 *  IpV6_VTimeAddMs()
 *********************************************************************************************************************/
/*! \brief        Add milliseconds to timestamp
 *  \details      -
 *  \param[in]    TimestampPtr  pointer to the timestamp variable
 *  \param[in]    Milliseconds  number of milliseconds to add
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) IpV6_VTimeAddMs(
  P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_DATA)  TimestampPtr,
  uint32                                           Milliseconds);

/**********************************************************************************************************************
 *  IpV6_VSetLifetimeS()
 *********************************************************************************************************************/
/*! \brief         Set timestamp to a lifetime value
 *  \details       -
 *  \param[in]     TimestampPtr        pointer to the timestamp variable
 *  \param[in]     LifetimeS           lifetime value in seconds
 *  \param[in]     NextEventTimePtr    pointer to a variable in which the timestamp value will be stored
 *                                     if it is less than the current stored value
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VSetLifetimeS(
  P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_VAR)  TimestampPtr,
  uint32                                          LifetimeS,
  P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_VAR)  NextEventTimePtr);

/**********************************************************************************************************************
 *  IpV6_VSetLifetimeS()
 *********************************************************************************************************************/
/*! \brief         Set timestamp to a lifetime value
 *  \details       -
 *  \param[in]     TimestampPtr        pointer to the timestamp variable
 *  \param[in]     LifetimeS           lifetime value in seconds
 *  \param[in]     NextEventTimePtr    pointer to a variable in which the timestamp value will be stored
 *                                      if it is less than the current stored value
 *  \pre           -
 *  \synchronous   TRUE
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_VUpdateDefaultLinkMtu(TcpIp_IpV6CtrlIterType IpCtrlIdx, uint16 Mtu);

#if !defined(NO_INLINE_FUNCTION_DEFINITIONS)
/**********************************************************************************************************************
 *  IpV6_VTimeSet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) IpV6_VTimeSet(  /* PRQA S 3219 */ /* MD_MSR_8.10 */
  P2VAR(IpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                            Seconds,
  uint32                                            Milliseconds)
{
  TimestampPtr->S = Seconds;                                                                                            /* SBSW_TCPIP_NonNullPtrParameter */
  TimestampPtr->Ms = Milliseconds;                                                                                      /* SBSW_TCPIP_NonNullPtrParameter */
} /* End of IpV6_VTimeSet() */

/**********************************************************************************************************************
 *  IpV6_VTimeCompare()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) IpV6_VTimeCompare(  /* PRQA S 3219 */ /* MD_MSR_8.10 */
  IpV6_TimeType  RefTimestamp,
  IpV6_TimeType  Timestamp)
{
  boolean result = FALSE;
  if((RefTimestamp.S < Timestamp.S) || ((RefTimestamp.S == Timestamp.S) && (RefTimestamp.Ms < Timestamp.Ms)))
  {
    result = TRUE;
  }
  return result;
} /* End of IpV6_VTimeCompare() */

/**********************************************************************************************************************
 *  IpV6_VTimeAddMs()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) IpV6_VTimeAddMs(  /* PRQA S 3219 */ /* MD_MSR_8.10 */
  P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_DATA) TimestampPtr,
  uint32                                          Milliseconds)
{
  TimestampPtr->Ms += Milliseconds;                                                                                     /* SBSW_TCPIP_NonNullPtrParameter */

  if (TimestampPtr->Ms >= 1000u)
  {
    TimestampPtr->S += (TimestampPtr->Ms / 1000u);                                                                       /* SBSW_TCPIP_NonNullPtrParameter */
    TimestampPtr->Ms = (TimestampPtr->Ms % 1000u);                                                                       /* SBSW_TCPIP_NonNullPtrParameter */
  }
} /* End of IpV6_VTimeAddMs() */
#endif /* NO_INLINE_FUNCTION_DEFINITIONS */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */
#endif  /* IPV6_PRIV_H */

/**********************************************************************************************************************
 *  END OF FILE: IpV6_Priv.h
 *********************************************************************************************************************/
