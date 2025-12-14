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
 *         \file  TcpIp_IpV6.c
 *        \brief  Implementation of Internet Protocol version 6 (IPv6)
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv6 submodule. >> TcpIp_IpV6.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_IPV6_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "TcpIp_IpV6_Priv.h"
#include "TcpIp_IcmpV6.h"
#include "TcpIp_Ndp.h"
#include "TcpIp_IpV6_Cbk.h"
#include "TcpIp_Priv.h"

#if (TCPIP_SUPPORT_TCP == STD_ON)
# include "TcpIp_Tcp_Cbk.h"
#endif

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
# include "TcpIp_DhcpV6.h"
# include "TcpIp_DhcpV6_Cbk.h"
#endif

#include "TcpIp_Udp_Cbk.h"

#include "EthIf.h"
#include "IpBase_String.h"

# include "EthSM.h"

#if (TCPIP_SUPPORT_IPV6_NVM_ADDR_STORAGE == STD_ON)
# include "NvM.h"
#endif

#if defined(IPV6_JOIN_MULTICAST_GROUP_CALLOUT_INCLUDE)
# include IPV6_JOIN_MULTICAST_GROUP_CALLOUT_INCLUDE
#endif

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (STATIC)
# define STATIC static
#endif

#define IPV6_VENABLE_HOP_BY_HOP_EXT_HDR_SKIPPING        STD_OFF
#define IPV6_VENABLE_DESTINATION_OPT_EXT_HDR_SKIPPING   STD_OFF

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */

#define IPV6_HEADER_VERSION_OFFS   28u
#define IPV6_HEADER_TC_OFFS        20u

#define IPV6_HEADER_GET_VERSION(x) ((x) >> IPV6_HEADER_VERSION_OFFS)
#define IPV6_HEADER_GET_TC(x)      (((x) >> IPV6_HEADER_TC_OFFS) & 0x000000FFu)
#define IPV6_HEADER_GET_FL(x)      ((x) & 0x000FFFFFu)

#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
# define IPV6_HEADER_VERSION_TC_FL_ZERO_NBO  (IPV6_HEADER_VERSION << IPV6_HEADER_VERSION_OFFS)
# define IPV6_HEADER_MASK_VERSION_NBO        0xF0000000u
# define IPV6_HEADER_MASK_TRAFFIC_CLASS_NBO  0x0FF00000u
# define IPV6_HEADER_MASK_FLOW_LABEL_NBO     0x000FFFFFu
#else
# define IPV6_HEADER_VERSION_TC_FL_ZERO_NBO  (IPV6_HEADER_VERSION << 4)
# define IPV6_HEADER_MASK_VERSION_NBO        0x000000F0u
# define IPV6_HEADER_MASK_TRAFFIC_CLASS_NBO  0x0000F00Fu
# define IPV6_HEADER_MASK_FLOW_LABEL_NBO     0xFFFF0F00u
#endif

/* PRQA S 3453 5 */ /* MD_MSR_FctLikeMacro */
# define ETHSM_TCPIP_MODE_INDICATION(CtrlIdx, IsIpAddrAssigned) \
  (void)EthSM_VTcpIpModeIndication((CtrlIdx), (IsIpAddrAssigned))

/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
typedef struct
{
  boolean UseUnspecifiedAddr;

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  boolean SrcAddrOptimistic;
#endif

} IpV6_SrcAddrFlagsType;
#endif

typedef struct
{
  boolean NextHopReachable;
  boolean DstAddrOnLink;
} IpV6_DstAddrFlagsType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(uint8, IPV6_VAR_ZERO_INIT) IpV6_State = IPV6_STATE_UNINIT; /* current state of the IPv6 node */

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(IpV6_TimeType, IPV6_VAR_NOINIT) IpV6_Time; /* holds the current time since initialization of the the IpV6 module */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**/

#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* link-local prefix [fe80::]/64 */
CONST(IpV6_AddrPrefixType, IPV6_CONST) IpV6_PrefixLinkLocal = /* PRQA S 1533 */ /* MD_IPV6_Rule8.9_1533 */
{
  {
    {
      0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }
  },
  64
};

/* [ff02::1:ff__:_____/104 */
CONST(IpV6_AddrPrefixType, IPV6_CONST) IpV6_PrefixSolicitedNode =
{
  {
    {
      0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00
    }
  },
  104
};

/* [::1] */
CONST(IpV6_AddrType, IPV6_CONST) IpV6_AddrLoopback = /* PRQA S 0759 */ /* MD_MSR_Union */
{
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
  }
};

/* [::] */
CONST(IpV6_AddrType, IPV6_CONST) IpV6_AddrUnspecified = /* PRQA S 0759 */ /* MD_MSR_Union */
{
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
};

/* [ff01::1] IL = interface local scope */
CONST(IpV6_AddrType, IPV6_CONST) IpV6_AddrAllNodesIL = /* PRQA S 0759 */ /* MD_MSR_Union */
{
  {
    0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
  }
};

/* [ff02::1] LL = link local scope */
CONST(IpV6_AddrType, IPV6_CONST) IpV6_AddrAllNodesLL = /* PRQA S 0759 */ /* MD_MSR_Union */
{
  {
    0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
  }
};

/* All-routers [ff02::2] LL = link local scope */
CONST(IpV6_AddrType, IPV6_CONST) IpV6_AddrAllRoutersLL = /* PRQA S 0759, 1533 */ /* MD_MSR_Union, MD_IPV6_Rule8.9_1533 */
{
  {
    0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02
  }
};

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  IpV6_VIsValidSourceAddress()
 *********************************************************************************************************************/
/*! \brief        Check if a source address belongs to this node and is in state PREFERRED or DEPRECATED.
 *                Other addresses must not be used as source address for outgoing packets.
 *  \details      -
 *  \param[in]    IpCtrlIdx         Ip controller index
 *  \param[in]    SrcAddrPtr        Source address
 *  \param[in]    AllowUnspecAddr   If TRUE the unspecified (::) address will be accepted as valid source address
 *  \param[out]   SrcAddrStatePtr   Specifies the status of the source address
 *  \param[out]   CtrlAddrIdxPtr    Specifies the controller-specific address index. Afterwards caller must check validity!
 *  \return       TRUE              Address belongs to this node and may be used as source address for outgoing packets
 *  \return       FALSE             Address not valid as source address for outgoing packets
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(boolean, IPV6_CODE) IpV6_VIsValidSourceAddress(
  TcpIp_IpV6CtrlIterType                       IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                      SrcAddrPtr,
  boolean                                      AllowUnspecAddr,
  IPV6_P2V(IpV6_LocAddrStateType)              SrcAddrStatePtr,
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressType)  SrcAddrIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VCompareScopeOfAddress()
 *********************************************************************************************************************/
/*! \brief      Compare and determine which address has larger scope
 *  \details    Decide which of two Addresses should be preferred based on Scope of the Address
 *              (see RFC 6724 5.)
 *  \param[in]  IpV6AddrPtr                IPv6 Address whose scope is checked
 *  \param[in]  SatEntryAPtr               Source Address A SAT Entry
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]  SatEntryBPtr               Source Address B SAT Entry
  *                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \return     IPV6_CMP_RES_PREFER_A      use Source Address A
 *  \return     IPV6_CMP_RES_PREFER_B      use Source Address B
 *  \return     IPV6_CMP_RES_NO_PREFERENCE no preference was evaluated
 *  \pre        -
 *  \context    TASK|ISR
 *  \reentrant  FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_Ip_VCompareScopeOfAddress(
  IPV6_P2C(IpV6_AddrType)                     IpV6AddrPtr,
  TCPIP_P2C(IpV6_SourceAddressTableEntryType) SatEntryAPtr,
  TCPIP_P2C(IpV6_SourceAddressTableEntryType) SatEntryBPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VCompareStateOfAddress()
 *********************************************************************************************************************/
/*! \brief      Compare and determine which address valid state
 *  \details    Decide which of two Addresses should be preferred based on State of the Address
 *              (see RFC 6724 5.)
 *  \param[in]  StateA                     State of IPv6 Address A
 *  \param[in]  StateB                     State of IPv6 Address B
 *  \return     IPV6_CMP_RES_PREFER_A      use address A
 *  \return     IPV6_CMP_RES_PREFER_B      use address B
 *  \pre        -
 *  \context    TASK|ISR
 *  \reentrant  FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_Ip_VCompareStateOfAddress(
  IpV6_LocAddrStateType  StateA,
  IpV6_LocAddrStateType  StateB);

/**********************************************************************************************************************
 *  IpV6_Ip_VComparePrefixLenOfAddress()
 *********************************************************************************************************************/
/*! \brief      Compare the prefix lengths of two addresses
 * \details     Decide which of two Addresses should be preferred based on prefix Lengths of the Address
 *              (see RFC 6724 5.)
 *  \param[in]  PrefixLenA  Prefix Length of IPv6 Address A
 *  \param[in]  PrefixLenB  Prefix Length of IPv6 Address B
 *  \return     IPV6_CMP_RES_PREFER_A      use address A
 *  \return     IPV6_CMP_RES_PREFER_B      use address B
 *  \pre        -
 *  \context    TASK|ISR
 *  \reentrant  FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_Ip_VComparePrefixLenOfAddress(
  uint8 PrefixLenA,
  uint8 PrefixLenB);

/**********************************************************************************************************************
 *  IpV6_Ip_VFragLenValidate()
 *********************************************************************************************************************/
/*! \brief      Validation of Fragment Length
 *  \details    Validate the length of the Fragment packet. If the More Fragments flag is set
 *              the length of the fragment payload must be a multiple of 8.
 *  \param[in]  LocalAddrV6Idx   Ip address index specified  by caller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]  DataPtr          Pointer to IP Packet data buffer
 *  \param[in]  DataLen          Length of IP Packet data buffer
 *  \param[in]  FragHdrOfs       Offset of Fragment Extension Header in IP Payload
 *  \return     E_OK             Length of the fragment packet is valid
 *  \return     E_NOT_OK         Length of the fragment packet is invalid
 *  \pre        DataPtr          points to the IP packet
 *  \context    TASK|ISR
 *  \reentrant  FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VFragLenValidate(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      DataLen,
  uint16                      FragHdrOfs);

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VRaBuffDescValidate()
 *********************************************************************************************************************/
/*! \brief      Validate the Reassembly Buffer Descriptor parameters
 *  \details    -
 *  \param[in]  IpV6FragConfigIdx   Index of Fragment Configuration Data
 *  \param[in]  RaBufferDescIdx     Index of Reassembly Buffer
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor()-1]
 *  \param[in]  FragHdrOfs          Offset of Fragment Extension Header in IP Payload
 *  \param[in]  FragLen             Length of Fragment payload
 *  \param[in]  FragOfs             Offset of the Fragment in the reassembled packet
 *  \return     E_OK                Reassembly Buffer Descriptor is valid
 *  \return     E_NOT_OK            Reassembly Buffer Descriptor is invalid
 *  \pre        FragConfigIdx was configured by TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl
 *              RaBufferDescIdx was configured by IpV6_VGetReassemblyBufferIdx()
 *  \context    TASK|ISR
 *  \reentrant  FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VRaBuffDescValidate(
  TcpIp_SizeOfIpV6FragmentationConfigType         IpV6FragConfigIdx,
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx,
  uint16                                          FragHdrOfs,
  uint16                                          FragLen,
  uint16                                          FragOfs);
#endif

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessValidFragment()
 *********************************************************************************************************************/
/*! \brief      Processing for the fragment
 *  \details    Validate and Copy the fragment into reassembly buffer
 *  \param[in]  RaBufferDescIdx  Index of Reassembly Buffer
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor()-1]
 *  \param[in]  FragHdrOfs       Offset of Fragment Extension Header in IP Payload
 *  \param[in]  DataPtr          Pointer to IP fragment packet
 *  \param[in]  DataLen          Length of IP fragment packet
 *  \param[in]  PrevHdrOfs       Offset of previous header
 *  \return     E_OK             Fragment reassembly was successful
 *  \return     E_NOT_OK         Fragment reassembly was successful
 *  \pre        -
 *  \context    TASK|ISR
 *  \reentrant  FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessValidFragment(
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType RaBufferDescIdx,
  uint16                                         FragHdrOfs,
  IPV6_P2C(uint8)                                DataPtr,
  uint16                                         DataLen,
  uint16                                         PrevHdrOfs);
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VIsSourceAddressActive()
 *********************************************************************************************************************/
/*! \brief           Check if the Source Address is in active state
 *                   for the IP controller
 *  \details         -
 *  \param[in]       IpCtrlIdx        Index of IP controller
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in,out]   SrcAddrFlagsPtr  Source Address flags (only used if DAD Support is enabled)
 *  \param[in]       SrcAddrIdx       Index of the source address
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \return          BUFREQ_OK        Source address is in valid state
 *  \return          BUFREQ_E_NOT_OK  Source address is in invalid state
 *  \pre             SrcAddrIdx is configured by TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6()
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VIsSourceAddressActive(
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  TcpIp_IpV6CtrlIterType                      IpCtrlIdx,
  IPV6_P2V(IpV6_SrcAddrFlagsType)             SrcAddrFlagsPtr,
#endif
  TcpIp_SizeOfIpV6SourceAddressTableEntryType SrcAddrIdx);

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VNextHopLLDadOptimistic()
 *********************************************************************************************************************/
/*! \brief           Perform optimistic link layer address resolution
 *  \details         Check if the Destination is an optimistic address. perform Address resolution
 *                   only if address is not optimistic else use default next hop address
 *  \param[in]       IpCtrlIdx          Index of IP controller
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]       LocalAddrV6Idx     Index of local IpV6 Address
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6Addr()-1]
 *  \param[in]       DcEntryIdx         Index to entry in Destination Cache
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6DestinationCacheEntry()-1]
 *  \param[in,out]   NextHopAddrPtrPtr  Pointer to the Next hop IP address Ptr. If destination is not next hop reachable,
 *                                      the next hop address Ptr points to default router address.
 *  \param[in]       DstAddrPtr         Pointer to destination address
 *  \param[out]      PhysAddrPtr        Link layer address of destination
 *  \param[in,out]   DstAddrFlagsPtr    Destination Address Flags
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VNextHopLLDadOptimistic(
  TcpIp_SizeOfIpV6CtrlType        IpCtrlIdx,
  TcpIp_LocalAddrV6IterType       LocalAddrV6Idx,
  IpV6_ListIdxType                DcEntryIdx,
  IPV6_P2C(IpV6_AddrType *)       NextHopAddrPtrPtr,
  IPV6_P2C(IpV6_AddrType)         DstAddrPtr,
  IPV6_P2V(uint8)                 PhysAddrPtr,
  IPV6_P2V(IpV6_DstAddrFlagsType) DstAddrFlagsPtr);
#endif

#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VRequestTxFragmentBuffer()
 *********************************************************************************************************************/
/*! \brief           Request for fragment buffer for transmission and update fields
 *                   in fragment tx buffer descriptor
 *  \details         -
 *  \param[in]       IpCtrlIdx        Index of IP controller
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]       PathMtu          MTU of the transmission path
 *  \param[out]      BufPtrPtr        Pointer to the tx fragmentation buffer allocated
 *                                    The pointer is valid only if return value is BUFREQ_OK
 *  \param[in,out]   BufLenPtr        Length of the IP payload
 *  \param[in]       TxReqDescrPtr    Tx request descriptor
 *  \return          BUFREQ_OK        Buffer allocated successfully
 *  \return          BUFREQ_E_NOT_OK  Tx payload length too big to allocate buffer
 *  \return          BUFREQ_E_BUSY    No fragmentation tx buffers available
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VRequestTxFragmentBuffer(
  TcpIp_SizeOfIpV6CtrlType                  IpCtrlIdx,
  uint16                                    PathMtu,
  IPV6_P2V(uint8*)                          BufPtrPtr,
  IPV6_P2V(uint16)                          BufLenPtr,
  IPV6_P2V(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr);
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VGetIpControllerIdx()
 *********************************************************************************************************************/
/*! \brief           Determine IP controller index from the ip address index
 *  \details         -
 *  \param[in,out]   LocalAddrV6IdxPtr  Index of ip address. if index is invalid,
 *                                      assign broadcast address of default controller
 *  \param[out]      IpV6CtrlIdxPtr     IP controller index for the ip address
 *  \return          E_OK               IP controller index determined successfully for the ip address
 *  \return          E_NOT_OK           no default IP controller index configured
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VGetIpControllerIdx(
  IPV6_P2V(TcpIp_LocalAddrIterType)   LocalAddrV6IdxPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6CtrlType)  IpV6CtrlIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VDetermineValidSourceAddressIdx()
 *********************************************************************************************************************/
/*! \brief       Determine the appropriate source address to use for the given destination address
 *  \details     -
 *  \param[in]   IpCtrlIdx             IP controller index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]  SrcAddrIdxPtr         Source address index
 *  \param[in]   DcEntryIdx            Index of the destination address in destination cache
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6DestinationCacheEntry()-1]
 *  \param[out]  SrcAddrOptimisticPtr  Optimistic source address indication flag
 *  \param[in]   DstAddrPtr            Destination address
 *  \return      BUFREQ_OK             Appropriate source address index found for given destination address
 *  \return      BUFREQ_E_NOT_OK       No matching source address index found
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VDetermineValidSourceAddressIdx(
 TcpIp_SizeOfIpV6CtrlType                              IpCtrlIdx,
 IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType) SrcAddrIdxPtr,
 IpV6_ListIdxType                                      DcEntryIdx,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
 IPV6_P2V(boolean)                                     SrcAddrOptimisticPtr,
#endif
 IPV6_P2C(IpV6_AddrType)                               DstAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VObtainPathMtu()
 *********************************************************************************************************************/
/*! \brief      Obtain the Mtu for the packet. If Path Mtu is enabled, assign path Mtu
 *              otherwise assign default Mtu.
 *  \details    -
 *  \param[in]  DcEntryIdx      Index of entry in destination cache
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6DestinationCacheEntry()-1]
 *  \param[in]  IpCtrlIdx       IP controller index
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \return     pathMtu         Mtu to be used
 *  \pre        -
 *  \context    TASK|ISR
 *  \reentrant  FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint16, IPV6_CODE) IpV6_Ip_VObtainPathMtu(
#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
  IpV6_ListIdxType         DcEntryIdx,
#endif
 TcpIp_SizeOfIpV6CtrlType  IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ip_VCallerSpecifiedSourceAddress()
 *********************************************************************************************************************/
/*! \brief       Determine the source address to use from the Ip address index provided by caller
 *  \details     -
*  \param[in]    IpCtrlIdx             Ip controller index
*                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]   LocalAddrV6Idx        Ip address index specified  by caller
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[out]  SrcAddrFlagsPtr       Source Address flags (only used if DAD Support is enabled)
 *  \param[out]  SrcAddrIdxPtr         Source address index
 *  \return      BUFREQ_OK             Suitable source address found
 *  \return      BUFREQ_E_NOT_OK       No suitable source address found
 *  \pre        -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VCallerSpecifiedSourceAddress(
  TcpIp_IpV6CtrlIterType                                IpCtrlIdx,
  TcpIp_LocalAddrV6IterType                             LocalAddrV6Idx,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  IPV6_P2V(IpV6_SrcAddrFlagsType)                       SrcAddrFlagsPtr,
#endif
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType) SrcAddrIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VDCSourceAddressLookup()
 *********************************************************************************************************************/
/*! \brief       Check if Source address can be determined from destination cache entry
 *               of destination address, otherwise use source address selection algorithm
 *  \details     -
 *  \param[in]   IpCtrlIdx             Ip controller index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]   SrcAddrIdxPtr         Source address index to be used to send packet to destination
 *  \param[out]  SrcAddrOptimisticPtr  Optimistic source address indication flag
 *  \param[out]  DcEntryIdxPtr         Index of entry in destination cache
 *  \param[in]   DstAddrPtr            Destination address
 *  \return      BUFREQ_OK             Suitable source address found
 *  \return      BUFREQ_E_NOT_OK       No suitable source address found
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VDCSourceAddressLookup(
TcpIp_SizeOfIpV6CtrlType                                IpCtrlIdx,
 IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType)  SrcAddrIdxPtr,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
 IPV6_P2V(boolean)                                      SrcAddrOptimisticPtr,
#endif
 IPV6_P2V(IpV6_ListIdxType)                             DcEntryIdxPtr,
 IPV6_P2C(IpV6_AddrType)                                DstAddrPtr);

/**********************************************************************************************************************
 *  IpV6_VHandleCrtlTransitionStates()
 *********************************************************************************************************************/
/*! \brief       Handle IP controller state transitions
 *  \details     -
 *  \param[in]   IpCtrlIdx  Ip controller index
 *               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre         Ip controller is initialised
 *  \context     TASK
 *  \reentrant   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VHandleCrtlTransitionStates(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_VSearchforAddressinPrefixList()
 *********************************************************************************************************************/
/*! \brief       Determine if destination address has prefix present in the dynamic prefix list
 *  \details     -
 *  \param[in]   IpCtrlIdx   Ip controller index
 *                           CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]   DstAddrPtr  Destination address
 *  \return      TRUE        Destination address has prefix present in the prefix list
 *  \return      FALSE       Destination address prefix not present in the prefix list
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(boolean, IPV6_CODE) IpV6_VSearchforAddressinPrefixList(
  TcpIp_IpV6CtrlIterType                             IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA)  DstAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VObtainSourceAddress()
 *********************************************************************************************************************/
/*! \brief        Obtain Source address for sending packet to the destination, obtained either from caller,
 *                or from destination cache entry or source selection algorithm
 *  \details      -
 *  \param[in]    LocalAddrV6Idx        Ip address index specified by caller
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[out]   SrcAddrIdxPtr         Index to source address to be used
 *  \param[out]   SrcAddrFlagsPtr       Source Address flags (only used if DAD Support is enabled)
 *  \param[out]   DcEntryIdxPtr         Index of Destination entry in destination cache
 *  \param[in]    DstAddrPtr            Destination address
 *  \return       BUFREQ_OK             Suitable source address found
 *  \return       BUFREQ_E_NOT_OK       No suitable source address found
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VObtainSourceAddress(
  TcpIp_LocalAddrIterType                               LocalAddrV6Idx,
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType) SrcAddrIdxPtr,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  IPV6_P2V(IpV6_SrcAddrFlagsType)                       SrcAddrFlagsPtr,
#endif
  IPV6_P2V(IpV6_ListIdxType)                            DcEntryIdxPtr,
  IPV6_P2C(IpV6_AddrType)                               DstAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VNextHopLLResolution()
 *********************************************************************************************************************/
/*! \brief        Next hop link layer address resolution for transmission of Ip packet
 *  \details      -
 *  \param[in]    LocalAddrV6Idx           Ip address index
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    DcEntryIdx               index of entry in destination cache
 *  \param[in]    DstAddrPtr               Destination address pointer
 *  \param[in]    SrcAddrOptimistic        Optimistic source address indication flag
 *  \param[out]   NextHopAddrPtrPtr        Pointer to the next hop Ip address pointer
 *  \param[in]    ForceProvideBuffer       Flag to indicate Tx buffer must be provided even if address resolution
 *                                         not complete
 *  \return       BUFREQ_OK                Next hop address resolution completed
 *  \return       BUFREQ_E_BUSY            Next hop address resolution in progress
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VNextHopLLResolution(
  TcpIp_LocalAddrIterType    LocalAddrV6Idx,
  IpV6_ListIdxType           DcEntryIdx,
  IPV6_P2C(IpV6_AddrType)    DstAddrPtr,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  boolean                    SrcAddrOptimistic,
#endif
  IPV6_P2C(IpV6_AddrType *)  NextHopAddrPtrPtr,
  boolean                    ForceProvideBuffer);

/**********************************************************************************************************************
 *  IpV6_Ip_VConfigureSourceAddress()
 *********************************************************************************************************************/
/*! \brief        Configure source address for building ip packet
 *  \details      -
 *  \param[in]    IpCtrlIdx            Ip controller index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    SrcAddrIdx           Source Ip address index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]    UseUnspecifiedAddr   Flag indicating if unspecified address can be used
 *  \param[out]   SrcAddrPtr           Configured source Ip address is stored here
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VConfigureSourceAddress(
  TcpIp_SizeOfIpV6CtrlType                        IpCtrlIdx,
  TcpIp_SizeOfIpV6SourceAddressTableEntryType     SrcAddrIdx,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  boolean                                         UseUnspecifiedAddr,
#endif
  P2VAR(IpV6_AddrType, AUTOMATIC, IPV6_APPL_VAR)  SrcAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VObtainNextHopAddress()
 *********************************************************************************************************************/
/*! \brief           Obtain the next hop address to send the packet.
 *  \details         -
 *  \param[in]       LocalAddrV6Idx     Ip local address index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6Addr()-1]
 *  \param[in,out]   DcEntryIdxPtr      Index to entry in destination cache. By default the destination
 *                                      cache entry hint index is stored for search optimization.
 *  \param[in]       DstAddrPtr         Destination address
 *  \param[out]      DstAddrFlagsPtr    Destination address flags
 *  \param[out]      NextHopAddrPtrPtr  Pointer to next hop address
 *                                      NULL_PTR in this argument indicates no next hop address was obtained
 *  \return          BUFREQ_OK          Next hop address was obtained successfully
 *  \return          BUFREQ_E_NOT_OK    No Next hop address was obtained
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VObtainNextHopAddress(
 TcpIp_LocalAddrV6IterType           LocalAddrV6Idx,
 IPV6_P2V(IpV6_ListIdxType)          DcEntryIdxPtr,
 IPV6_P2C(IpV6_AddrType)             DstAddrPtr,
 IPV6_P2V(IpV6_DstAddrFlagsType)     DstAddrFlagsPtr,
 IPV6_P2C(IpV6_AddrType *)           NextHopAddrPtrPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VSetVersionTcFlNbo()
 *********************************************************************************************************************/
/*! \brief           Set Version, traffic class and flow control fields for Ipv6 packet
 *  \details         -
 *  \param[in]       IpCtrlIdx         IP Controller Index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]       IpV6SocketIdx     IP Socket Index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \return          VersionTcFlNbo    The version, traffic class and flow control fields are returned as
 *                                     uint32 in network byte order
 *  \pre             -
 *  \context         TASK
 *  \reentrant       TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint32, IPV6_CODE) IpV6_Ip_VSetVersionTcFlNbo(
  TcpIp_SizeOfIpV6CtrlType   IpCtrlIdx,
  TcpIp_SizeOfSocketDynType  IpV6SocketIdx);

/**********************************************************************************************************************
 *  IpV6_Ip_VStoreChecksumInHeader()
 *********************************************************************************************************************/
/*! \brief           Store Checksum in appropriate Protocol Header
 *  \details         -
 *  \param[in]       ProtHeader         Protocol Header
 *  \param[in]       ProtocolChecksum   Checksum value
 *  \param[in,out]   PayloadPtr         Payload Pointer to store the checksum into
 *  \pre             -
 *  \context         TASK
 *  \reentrant       TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VStoreChecksumInHeader(
  uint8            ProtHeader,
  uint32           ProtocolChecksum,
  IPV6_P2V(uint8)  PayloadPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VCheckIPv6HeaderValid()
 *********************************************************************************************************************/
/*! \brief           Validate the IPv6 Header Fields
 *  \details         -
 *  \param[in]       IpCtrlIdx             IP Controller Index
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]       LocalAddrV6IdxPtr     IP Address Index
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]       IpV6HdrPtr            Pointer to IpV6 Header
 *  \param[in]       PhysAddrPtr           Link Layer Physical Address
 *  \param[in]       LenByte               Packet length in bytes
 *  \return          E_OK                  Ip header is valid
 *  \return          E_NOT_OK              Ip header is not valid
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VCheckIPv6HeaderValid(
  TcpIp_SizeOfIpV6CtrlType                IpCtrlIdx,
  IPV6_P2V(TcpIp_SizeOfLocalAddrV6Type)   LocalAddrV6IdxPtr,
  IPV6_P2C(IpV6_HdrType)                  IpV6HdrPtr,
  IPV6_P2C(uint8)                         PhysAddrPtr,
  uint16                                  LenByte);

#if (IPV6_VENABLE_HOP_BY_HOP_EXT_HDR_SKIPPING != STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessHopByHopOptions()
 *********************************************************************************************************************/
/*! \brief           Process Hop by Hop Options
 *  \details         -
 *  \param[in]       LocalAddrV6Idx      IP Address Index
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]       DataPtr             Pointer to IpV6 Packet
 *  \param[in]       ThisHdrOfs          Offset of the Destination Header
 *  \param[in]       ThisHdrLen          Length of Destination header
 *  \param[in]       DataLen             length of IPv6 Packet
 *  \return          E_OK                Hop by hop options processed successfully
 *  \return          E_NOT_OK            Invalid hop by hop options received
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessHopByHopOptions(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       ThisHdrOfs,
  uint16                       ThisHdrLen,
  uint16                       DataLen);
#endif

#if (IPV6_VENABLE_DESTINATION_OPT_EXT_HDR_SKIPPING != STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessDstOptions()
 *********************************************************************************************************************/
/*! \brief          Process Destination Header Options
 *  \details        -
 *  \param[in]      LocalAddrV6Idx     IP Address Index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]      DataPtr            Pointer to IpV6 Packet
 *  \param[in]      ThisHdrOfs         Offset of the Destination Header
 *  \param[in]      ThisHdrLen         Length of Destination header
 *  \param[in]      DataLen            length of IPv6 Packet
 *  \return         E_OK               Destination options processed successfully
 *  \return         E_NOT_OK           Invalid Destination options received
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessDstOptions(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      ThisHdrOfs,
  uint16                      ThisHdrLen,
  uint16                      DataLen);
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VProcessUdpHeader()
 *********************************************************************************************************************/
/*! \brief             Process IPv6 Udp Header Fields
 *  \details           -
 *  \param[in]         IpCtrlIdx                IP Controller Index
 *                                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]         LocalAddrV6Idx           IP Address Index
 *                                              CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in,out]     DataPtr                  Pointer to IpV6 Packet
 *  \param[in]         ThisHdrOfs               Offset of the Udp Header
 *  \param[in]         DataLen                  length of IPv6 Packet
 *  \param[in]         ChecksumVerified         Flag to determine if checksum is verified by HW
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VProcessUdpHeader(
  TcpIp_SizeOfIpV6CtrlType                 IpCtrlIdx,
  TcpIp_SizeOfLocalAddrV6Type              LocalAddrV6Idx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   ThisHdrOfs,
  uint16                                   DataLen,
  boolean                                  ChecksumVerified);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessTcpHeader()
 *********************************************************************************************************************/
/*! \brief             Process IPv6 Tcp Header Fields
 *  \details           -
 *  \param[in]         LocalAddrV6Idx           IP Address Index
 *                                              CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in,out]     DataPtr                  Pointer to IpV6 Packet
 *  \param[in]         ThisHdrOfs               Offset of the Tcp Header
 *  \param[in]         DataLen                  length of IPv6 Packet
 *  \param[in]         ChecksumVerified         Flag to determine if checksum is verified by HW
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VProcessTcpHeader(
  TcpIp_LocalAddrV6IterType                 LocalAddrV6Idx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                    ThisHdrOfs,
  uint16                                    DataLen,
  boolean                                   ChecksumVerified);
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VProcessExtHeaders()
 *********************************************************************************************************************/
/*! \brief             Process IPv6 Extension Header Fields
 *  \details           -
 *  \param[in]       IpCtrlIdx                  IP Controller Index
 *                                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]       LocalAddrV6Idx             IP Address Index
 *                                              CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in,out]   DataPtr                    Pointer to IpV6 Packet
 *  \param[in]       PhysAddrPtr                Link Layer Physical Address
 *  \param[in]       IsReassembledPacket        indicates that the frame is a reassembled IpV6 packet
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VProcessExtHeaders(
  TcpIp_SizeOfIpV6CtrlType                   IpCtrlIdx,
  TcpIp_SizeOfLocalAddrV6Type                LocalAddrV6Idx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)   DataPtr,
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA)  PhysAddrPtr,
  boolean                                    IsReassembledPacket);

/**********************************************************************************************************************
 *  IpV6_Ip_VUpdateValidSourceAddress()
 *********************************************************************************************************************/
/*! \brief        Update Lifetimes of Valid Source Address
 *  \details      -
 *  \param[in]    LocalAddrV6Idx          IP Address Index
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    PreferredLifetime       Preferred Address Lifetime of source address
 *  \param[in]    ValidLifetime           Valid Address Lifetime of source address
 *  \param[in]    AddressPtr              Pointer to source Ip address
 *  \return       E_OK                    Address Lifetimes updated successfully (always E_OK)
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VUpdateValidSourceAddress(
  TcpIp_SizeOfLocalAddrV6Type                        LocalAddrV6Idx,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VSetUnicastAddress()
 *********************************************************************************************************************/
/*! \brief        Set IPv6 Unicast Source Address
 *  \details      -
 *  \param[in]    LocalAddrV6Idx            IP Address Index
 *                                          CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    PreferredLifetime         Preferred Address Lifetime
 *  \param[in]    ValidLifetime             Valid Address Lifetime
 *  \param[in]    AddressPtr                Pointer to Source Address
 *  \param[in]    NoDad                     Do not perform DAD for this address (address may be used immediately)
 *  \return       E_OK                      Unciast Address Set successfully
 *  \return       E_NOT_OK                  Unciast Address Set failed due to Nvm error
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VSetUnicastAddress(
  TcpIp_SizeOfLocalAddrV6Type                        LocalAddrV6Idx,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr,
  boolean                                            NoDad);

/**********************************************************************************************************************
 *  IpV6_Ip_VSetMulticastAddress()
 *********************************************************************************************************************/
/*! \brief          Sets an IPv6 multicast source address.
 *  \details        Checks whether the socket may be bound, using the given parameters, and does the actual binding.
 *  \param[in]      IpV6MulticastAddrIdx    Index of a local IPv6 multicast address.
 *                                          CONSTRAINT: [0...TcpIp_GetSizeOfIpV6MulticastAddr()-1]
 *  \param[in]      AddressPtr              IPv6 muticast address.
 *                                          CONSTRAINT: TCPIP_ADDR_ID_MULTICAST(*AddressPtr)
 *  \return         E_OK                    The request has been accepted
 *  \return         E_NOT_OK                The request has not been accepted (e.g. address in use)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VSetMulticastAddress(
  TcpIp_IpV6MulticastAddrIterType  IpV6MulticastAddrIdx,
  TCPIP_P2C(IpV6_AddrType)         AddressPtr);

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessFirstFragment()
 *********************************************************************************************************************/
/*! \brief        Processing for the First received fragment
 *  \details      -
 *  \param[in]    RaBufferDescIdx   Index to the reassembly buffer
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor()-1]
 *  \param[in]    FragHdrOfs        Header offset of fragment extension header
 *  \param[in]    PrevHdrOfs        Offset of previous extension header
 *  \param[in]    DataPtr           Pointer to IpV6 Packet
 *  \param[in]    DataLen           Length of IpV6 packet
 *  \return       E_OK              First fragment received processed successfully
 *  \return       E_NOT_OK          Fragment not processed successfully
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessFirstFragment(
 TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx,
 uint16                                          FragHdrOfs,
 uint16                                          PrevHdrOfs,
 IPV6_P2C(uint8)                                 DataPtr,
 uint16                                          DataLen);
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VAddNewSourceAddress()
 *********************************************************************************************************************/
/*! \brief        Add and update Lifetimes of new Valid Source Address
 *  \details      -
 *  \param[in]    IpV6SrcAddrIdx       IP Source Address Index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]    PreferredLifetime    Preferred Address Lifetime
 *  \param[in]    ValidLifetime        Valid Address Lifetime
 *  \param[in]    AddressPtr           Pointer to Source Address
 *  \param[in]    NoDad                Do not perform DAD for this address (address may be used immediately)
 *  \return       E_OK                 Address added successfully
 *  \return       E_NOT_OK             Address not added because of invalid Lifetime or Nvm error
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VAddNewSourceAddress(
  TcpIp_SizeOfIpV6SourceAddressType                  IpV6SrcAddrIdx,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr,
  boolean                                            NoDad);

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VFragReassemblyTimeExpired()
 *********************************************************************************************************************/
/*! \brief        Handle reassembly time expiry
 *  \details      Send TimeExceeded Message if Fragment Reassembly Time is expired
 *  \param[in]    IpCtrlIdx         IP Controller Index
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    RaBufferDescIdx   Index to the reassembly buffer
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor()-1]
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VFragReassemblyTimeExpired(
  TcpIp_IpV6CtrlIterType                          IpCtrlIdx,
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx);
#endif

/**********************************************************************************************************************
 *  IpV6_VGetInterfaceIdentifier()
 *********************************************************************************************************************/
/*! \brief         Obtain interface identifier
 *  \details       Get 64bit interface identifier from physical address of a given controller
 *  \param[in]     IpCtrlIdx     IP Controller Index
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]    DstBufPtr     Destination buffer to store the interface identifier
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VGetInterfaceIdentifier(
  uint8                                  IpCtrlIdx,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR) DstBufPtr);


/**********************************************************************************************************************
 *  IpV6_VGetCommonPrefixLen()
 *********************************************************************************************************************/
/*! \brief         Obtain common prefix of two addresses
 *  \details       Returns longest common prefix length of two addresses in bits
 *  \param[in]     Addr1Ptr         Address 1
 *  \param[in]     Addr1Ptr         Address 2
 *  \return        MatchingBits     Number of matching prefix bits
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_VGetCommonPrefixLen(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) Addr1Ptr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) Addr2Ptr);

/**********************************************************************************************************************
 *  IpV6_VMakeInterfaceIdentifier()
 *********************************************************************************************************************/
/*! \brief         Create an interface identifier
 *  \details       Convert an ethernet link-layer address (48bit MAC address) into a 64bit interface
 *                 identifier (according to RFC 2464 4.)
 *  \param[in]     EthPhysAddrPtr      Physical address
 *  \param[out]    DstBufPtr           Buffer to store interface identifier
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VMakeInterfaceIdentifier(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) EthPhysAddrPtr,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)    DstBufPtr);

/**********************************************************************************************************************
 *  IpV6_VHandleUnknownTlvOption()
 *********************************************************************************************************************/
/*! \brief         Handle unknown TLV options
 *  \details       Called when an unknown option in destination or hop-by-hop extension header has been found
 *  \param[in]     LocalAddrV6Idx           Ip Address Index
 *                                          CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     IpV6PktDataPtr           IPv6 packet data
 *  \param[in]     IpV6PktDataLen           Length of the IPv6 packet (IPv6 header and playload) in bytes
 *  \param[in]     UnknownOptOffset         Offset of the unknown option in bytes relative to IpV6PktDataPtr
 *  \return        E_OK                     Option can be skipped (processing of the packet can be continued)
 *  \return        E_NOT_OK                 Option must not be skipped (discard whole IPv6 packet)
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VHandleUnknownTlvOption(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2C(uint8)              IpV6PktDataPtr,
  uint16                       IpV6PktDataLen,
  uint16                       UnknownOptOffset);

/**********************************************************************************************************************
 *  IpV6_VSourceAddrIsBetterThan()
 *********************************************************************************************************************/
/*! \brief         Compare two source addresses to reach destination
 *  \details       Decide which of two source addresses should be preferred to reach a specific destination.
 *                 (see RFC 6724 5.)
 *                                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     SrcAddrIdxA                   Source address table index of first address
 *  \param[in]     SrcAddrIdxB                   Source address table index of second address
 *  \param[out]    DstAddrPtr                    Destination address
 *  \return        IPV6_CMP_RES_PREFER_A         Use address A
 *  \return        IPV6_CMP_RES_PREFER_B         Use address B
 *  \return        IPV6_CMP_RES_NO_PREFERENCE    No preference
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_VSourceAddrIsBetterThan(
  TcpIp_SizeOfIpV6SourceAddressType                 SrcAddrIdxA,
  TcpIp_SizeOfIpV6SourceAddressType                 SrcAddrIdxB,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr);

/**********************************************************************************************************************
 *  IpV6_VMulticastAddr2LinkLayerAddr()
 *********************************************************************************************************************/
/*! \brief         Multicast address to link layer conversion
 *  \details       Map an IPv6 multicast network-layer address to the corresponding link-layer multicast address
 *  \param[out]    PhysAddrPtr       Link-layer address of the corresponding multicast address
 *  \param[in]     NetAddrPtr        Network-layer IPv6 multicast address
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VMulticastAddr2LinkLayerAddr(
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)            PhysAddrPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) NetAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VValidateDestAddr()
 *********************************************************************************************************************/
/*! \brief         Determine if destination address is valid
 *                 If destination address validation is enabled, validate the destination address
 *  \details       -
 *  \param[in]     LocalAddrV6IdxPtr        Ip address index
 *  \param[out]    IpCtrlIdxPtr             Ip controller index corresponding to the ip address index
 *  \param[in]     DstAddrPtr               Destination address
 *  \return        BUFREQ_OK                Destination address is valid
 *  \return        BUFREQ_E_NOT_OK          Destination address is not valid
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VValidateDestAddr(
 IPV6_P2V(TcpIp_LocalAddrIterType)   LocalAddrV6IdxPtr,
 IPV6_P2V(TcpIp_SizeOfIpV6CtrlType)  IpCtrlIdxPtr,
 IPV6_P2C(IpV6_AddrType)             DstAddrPtr);

/**********************************************************************************************************************
 *  IpV6_VIngressFilter()
 *********************************************************************************************************************/
/*! \brief         Verify that destination is not a local address of controller
 *  \details       -
  *  \param[in]    IpCtrlIdx         IP Controller Index
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     DstAddrPtr        Destination address
 *  \param[out]    TempAddrIdxPtr    Temporary Source address table entry index (only if privacy extensions enabled)
 *  \param[out]    McAddrIdxPtr      Multicast address index is stored here (only if MLD is supported)
 *  \param[out]    LocalAddrV6IdxPtr Ip address index for destinationa addres is stored here
 *  \return        E_OK              Destination address can be used
 *  \return        E_NOT_OK          Destination address is a local address of controller
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VIngressFilter(
  uint8                                 IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)               DstAddrPtr,
  IPV6_P2V(TcpIp_SizeOfLocalAddrV6Type) LocalAddrV6IdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VCalculateandStoreChecksum()
 *********************************************************************************************************************/
/*! \brief         Calculate and Store Checksum in appropriate Protocol Header
 *  \details       -
 *  \param[in]     NextHeader         Protocol header of the next header in the buffer
 *  \param[in]     PayloadPtr         Payload buffer
 *  \param[in]     DstAddrPtr         Destination address to generate pseudoheader
 *  \param[in]     SrcAddrPtr         Source address to generate pseudoheader
 *  \param[in]     PayloadLen         Pazload length
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VCalculateandStoreChecksum(
  uint8                                               NextHeader,
  IPV6_P2V(uint8)                                     PayloadPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA)   DstAddrPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA)   SrcAddrPtr,
  uint16                                              PayloadLen);

/**********************************************************************************************************************
 *  IpV6_VResolveLinkLayerAddr()
 *********************************************************************************************************************/
/*! \brief          Resolve link layer address
 *  \details        Lookup the link-layer address of a node in the neighbor cache or start address resolution.
 *                  If the provided network address is a multicast address the corresponding ethernet
 *                  multicast address will be returned.
  *  \param[in]     IpCtrlIdx           IP Controller Index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]      SrcAddrIdx          IP Source Address Index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]      DstAddrPtr          IPv6 network address of the node
 *  \param[out]     PhysAddrPtr         Link layer address of the node
 *  \param[in,out]  NcEntryIdxPtr       Neighbor cache entry index. This index will be used as lookup hint.
 *  \return         E_OK                Link-layer address known
 *  \return         E_NOT_OK            Link-layer (currently) unknown, address resolution triggered
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VResolveLinkLayerAddr(
  uint8                                              IpCtrlIdx,
  TcpIp_SizeOfIpV6SourceAddressTableEntryType        SrcAddrIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA)  DstAddrPtr,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)             PhysAddrPtr,
  P2VAR(IpV6_ListIdxType, AUTOMATIC, IPV6_APPL_VAR)  NcEntryIdxPtr);

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VSegmentListInsert()
 *********************************************************************************************************************/
/*! \brief        Insert new element in reassembly segment list
 *  \details      Shift elements to the right to make space for new element
 *  \param[in]    RaBufferDescIdx   Index to the reassembly buffer
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor()-1]
 *  \param[in]    SegInsertIdx      Index to insert the segment into
 *  \return       E_OK              Element inserted into list successfully
 *  \return       E_NOT_OK          Segment list full, element not inserted
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSegmentListInsert(
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx,
  uint8                                           SegInsertIdx);

/**********************************************************************************************************************
 *  IpV6_VSegmentListRemove()
 *********************************************************************************************************************/
/*! \brief         Remove element from segment list
 *  \details       Shift elements of the list to the left to remove the element
 *  \param[in]     RaBufferDescIdx   Index to the reassembly buffer
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor()-1]
 *  \param[in]     SegRemoveIdx      Index of the element to remove
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VSegmentListRemove(
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx,
  uint8                                           SegRemoveIdx);

/**********************************************************************************************************************
 *  IpV6_VSegmentListAdd()
 *********************************************************************************************************************/
/*! \brief          Add new fragment into the segment list
 *                  Insert the fragment into the appropriate position
 *  \details        -
 *  \param[in]      RaBufferDescIdx   Index to the reassembly buffer
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor()-1]
 *  \param[in]      SegOfs            Start offset of where the fragment has to be inserted in the list
 *  \param[in]      SegLen            Length of the fragment to be inserted
 *  \return         E_OK              Fragment inserted into list successfully
 *  \return         E_NOT_OK          Fragment not inserted into list because of overlap with other elements
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSegmentListAdd(
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType RaBufferDescIdx,
  uint16                                         SegOfs,
  uint16                                         SegLen);

/**********************************************************************************************************************
 *  IpV6_VGetReassemblyBufferIdx()
 *********************************************************************************************************************/
/*! \brief            Obtain Reassembly buffer index for fragment reassembly
 *  \details          Check if reassembly buffer has already been allocated, else allocate unused buffer index
 *  \param[in]        LocalAddrV6Idx           IP Address Index
 *                                             CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]        SrcAddrPtr               Source address of the fragment
 *  \param[in]        FragmentId               Fragment Id
 *  \param[in]        RaBufferDescIdxPtr       The reassembly buffer index obtained is stored here
 *                                             The value is valid only if E_OK is returned
 *  \return           E_OK                     Reassembly index was obtained successfully
 *  \return           E_NOT_OK                 Reassembly buffers in used, no index obtained.
 *  \pre              -
 *  \context          TASK|ISR
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VGetReassemblyBufferIdx(
  TcpIp_SizeOfLocalAddrV6Type                                LocalAddrV6Idx,
  TCPIP_P2C(IpV6_AddrType)                                   SrcAddrPtr,
  uint32                                                     FragmentId,
  TCPIP_P2V(TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType)  RaBufferDescIdxPtr);

/**********************************************************************************************************************
 *  IpV6_VRxFragments()
 *********************************************************************************************************************/
/*! \brief         Receive Ip fragments
 *  \details       Invoke Rx indication for pending rx fragments
 *  \param[in]     IpCtrlIdx    IP Controller Index
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VRxFragments(TcpIp_IpV6CtrlIterType IpCtrlIdx);

#endif /* (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON) */

/**********************************************************************************************************************
 *  IpV6_VProcessFragmentHeader()
 *********************************************************************************************************************/
/*! \brief          Process Ip fragment extension header
 *  \details        -
 *  \param[in]      LocalAddrV6Idx   IP Address Index
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]      DataPtr          Ip packet buffer
 *  \param[in]      DataLen          Ip packet length
 *  \param[in]      FragHdrOfs       Header offset of fragment extension header
 *  \param[in]      PrevHdrOfs       Header offset of previous extension header
 *  \return         E_OK             Processing of fragment header was successful
 *  \return         E_NOT_OK         Procesing of fragment failed
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VProcessFragmentHeader(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      DataLen,
  uint16                      FragHdrOfs,
  uint16                      PrevHdrOfs);

#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VGetFragmentTxBufferIdx()
 *********************************************************************************************************************/
/*! \brief         Obtain Fragment tx buffer descriptor index
 *  \details       Traverse through fragment tx buffer descriptor list for unused index
 *  \param[in]     IpCtrlIdx               IP Controller Index
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     FragTxBufDescIdxPtr     Fragment tx buffer descriptor index obtained is stored here
 *                                         Valid only if E_OK is returned
 *  \return        E_OK                    Fragment Tx buffer descriptor obtained successfully
 *  \return        E_NOT_OK                No unused fragment tx buffer descriptors available
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VGetFragmentTxBufferIdx(
  TcpIp_SizeOfIpV6CtrlType                                  IpCtrlIdx,
  TCPIP_P2V(TcpIp_SizeOfIpV6FragmentTxBufferDescriptorType) FragTxBufDescIdxPtr);

/**********************************************************************************************************************
 *  IpV6_VTxFragments()
 *********************************************************************************************************************/
/*! \brief            Transmit pending Ip fragments
 *  \details          -
 *  \param[in]        IpCtrlIdx    IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VTxFragments(TcpIp_IpV6CtrlIterType IpCtrlIdx);
#endif

#if ((TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON) || (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON))
/**********************************************************************************************************************
 *  IpV6_VInitFragments()
 *********************************************************************************************************************/
/*! \brief            Initialize Fragment and reassembly descriptors
 *  \details          -
 *  \param[in]        IpCtrlIdx    IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VInitFragments(TcpIp_IpV6CtrlIterType IpCtrlIdx);
#endif

/**********************************************************************************************************************
 *  IpV6_VConfigureSourceAddresses()
 *********************************************************************************************************************/
/*! \brief            Configure source Ip addresses
 *  \details          Assign stored NvM or default addresses to all source indexes
 *  \param[in]        IpCtrlIdx    IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VConfigureSourceAddresses(TcpIp_IpV6CtrlIterType IpCtrlIdx);

#if (TCPIP_SUPPORT_IPV6_NVM_ADDR_STORAGE == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VNvmGetAddress()
 *********************************************************************************************************************/
/*! \brief         Copy stored address from NvM Block
 *  \details       Obtain stored NvM address
 *  \param[in]     IpV6SrcAddrIdx   Source Address Index
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[out]    AddrPtr          Address obtained from NvM
 *                                  only valid if E_OK returned
 *  \return        E_OK             Address was obtained successfully from NvM
 *  \return        E_NOT_OK         Address was not obtained from NvM
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VNvmGetAddress(
  TcpIp_IpV6SourceAddressTableEntryIterType  IpV6SrcAddrIdx,
  TCPIP_P2V(IpV6_AddrType)                   AddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ip_VNvmSetAddress()
 *********************************************************************************************************************/
/*! \brief         Store address into NvM Block
 *  \details       Store Address into NvM
 *  \param[in]     IpV6SrcAddrIdx   Source Address Index
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]     AddrPtr          Pointer to Address to store in NvM
 *  \return        E_OK             Address was obtained successfully from NvM
 *  \return        E_NOT_OK         Address was not obtained from NvM
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VNvmSetAddress(
  TcpIp_IpV6SourceAddressTableEntryIterType  IpV6SrcAddrIdx,
  TCPIP_P2C(IpV6_AddrType)                   AddrPtr);
#endif

/**********************************************************************************************************************
 *  IpV6_VConfigureMulticastAddresses()
 *********************************************************************************************************************/
/*! \brief           Configure multicast addresses
 *  \details         Assign default address to all dynamic multicast address indexs. If no default address is
 *                   configured, assign to unspcified address.
 *  \param[in]       IpCtrlIdx     IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre             -
 *  \context         TASK
 *  \reentrant       FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VConfigureMulticastAddresses(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_VCtrlStateStartup()
 *********************************************************************************************************************/
/*! \brief            Control State startup routine
 *  \details          -
 *  \param[in]        IpCtrlIdx    IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VCtrlStateStartup(uint8 IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_VCtrlStateOnline()
 *********************************************************************************************************************/
/*! \brief            Control state online address assignment routine
 *  \details          Configure link local, source an dmulticast addresses
 *  \param[in]        IpCtrlIdx    IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VCtrlStateOnline(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_VCtrlStateShutdown()
 *********************************************************************************************************************/
/*! \brief            Control state shut down routine
 *  \details          Remove all assigned addresses, notify Eth layer
 *  \param[in]        IpCtrlIdx    IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VCtrlStateShutdown(uint8 IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_VIsMatchingSolicitedNodeAddress()
 *********************************************************************************************************************/
/*! \brief         Check for solicited node address
 *  \details       Check if address has solicited-node prefix [FF02:0:0:0:0:1:FF__:____]/104
 *                 and is soliciting a local source address
 *  \param[in]     IpCtrlIdx       IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     IpAddrPtr       Ip multicast solicited node address
 *  \return        E_OK            Solicited-node multicast for a local source addresses
 *  \return        E_NOT_OK        Solicited address not for local source address
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VIsMatchingSolicitedNodeAddress(
  uint8                                 IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)               IpAddrPtr);

/**********************************************************************************************************************
 *  IpV6_VLookupMulticastAddress()
 *********************************************************************************************************************/
/*! \brief         Check if given multicast address matches any local multicast address
 *  \details       -
 *  \param[in]     IpCtrlIdx                    IP Controller Index
 *                                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     IpAddrPtr                    Multicast address for lookup
 *  \return        matchingMcAddrIdx            Multicast address index of the matched multicast address
 *  \return        TCPIP_IPV6_MC_ADDR_IDX_INV   If no multicast address is configured for Ip controller
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_IpV6MulticastAddrIterType, IPV6_CODE) IpV6_VLookupMulticastAddress(
  uint8                                 IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)               IpAddrPtr);

/**********************************************************************************************************************
 *  IpV6_RxIndication_Internal()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer (e.g. EthIf) and signals receiption of a new ethernet packet
 *  \details       -
 *  \param[in]     EthIfCtrlIdx          index of the controller that received the frame
 *  \param[in]     PhysAddrPtr           physical address (source of the ethernet frame)
 *  \param[in]     DataPtr               pointer to the received payload starting with the IPv6 header
 *  \param[in]     LenByte               length of the received payload in bytes
 *  \param[in]     IsReassembledPacket   indicates that the frame is a reassembled IpV6 packet
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_RxIndication_Internal(
  uint8                                    EthIfCtrlIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) PhysAddrPtr, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   LenByte,
  boolean                                  IsReassembledPacket);

/**********************************************************************************************************************
 *  IpV6_CreateStaticDefaultRouterEntry()
 *********************************************************************************************************************/
 /*! \brief         This function create a new static default router entry and set values
  *  \details       -
  *  \param[in]     LocalAddrV6Idx       index of the controller that received the frame
  *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6Addr()-1]
  *  \param[in]     RouterAddrPtr        physical address (source of the ethernet frame)
  *                                      CONSTRAINT: value != null
  *  \pre           -
  *  \context       TASK|ISR
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_CreateStaticDefaultRouterEntry(
  TcpIp_LocalAddrV6IterType                             LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)                               RouterAddrPtr);

/**********************************************************************************************************************
 *  IpV6_SelectDefaultRouterConfigAndCreateEntry()
 *********************************************************************************************************************/
 /*! \brief         Select the manual or static default router and create entry
  *  \details       -
  *  \param[in]     LocalAddrV6Idx       index of the controller that received the frame
  *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6Addr()-1]
  *  \param[in]     RouterAddrPtr        physical address (source of the ethernet frame)
  *                                      CONSTRAINT: value != null
  *  \pre           -
  *  \context       TASK|ISR
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_SelectDefaultRouterConfigAndCreateEntry(
  TcpIp_LocalAddrV6IterType                             LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)                               DefaultRouterPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  IpV6_VMakeInterfaceIdentifier()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VMakeInterfaceIdentifier(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) EthPhysAddrPtr,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)    DstBufPtr)
{
  TCPIP_ASSERT(NULL_PTR != EthPhysAddrPtr);
  TCPIP_ASSERT(NULL_PTR != DstBufPtr);

  /* #10  Generate 64-bit interface identifier from the physical address */
  DstBufPtr[0] = (uint8)(EthPhysAddrPtr[0] ^ 0x02U); /* toggle "Universal/Local" bit */
  DstBufPtr[1] = EthPhysAddrPtr[1];
  DstBufPtr[2] = EthPhysAddrPtr[2];

  DstBufPtr[3] = 0xFF;
  DstBufPtr[4] = 0xFE;

  DstBufPtr[5] = EthPhysAddrPtr[3];
  DstBufPtr[6] = EthPhysAddrPtr[4];
  DstBufPtr[7] = EthPhysAddrPtr[5];

} /* End of IpV6_VMakeInterfaceIdentifier() */


/**********************************************************************************************************************
 *  IpV6_VGetInterfaceIdentifier()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VGetInterfaceIdentifier(
  uint8                                  IpCtrlIdx,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR) DstBufPtr)
{
  Eth_PhysAddrType EthPhysAddr;

  TCPIP_ASSERT(NULL_PTR != DstBufPtr);

  /* #10 Obtain 64-bit interface identifier for the Ip controller index */
  TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), &EthPhysAddr[0]);
  IpV6_VMakeInterfaceIdentifier(&EthPhysAddr[0], DstBufPtr);

} /* End of IpV6_VGetInterfaceIdentifier() */


/**********************************************************************************************************************
 *  IpV6_VMulticastAddr2LinkLayerAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VMulticastAddr2LinkLayerAddr(
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)            PhysAddrPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) NetAddrPtr)
{
  TCPIP_ASSERT(NULL_PTR != PhysAddrPtr);
  TCPIP_ASSERT(NULL_PTR != NetAddrPtr);
  /* #10 Generate link layer address from multicast address */
  /* map IPv6 multicast address to ethernet multicast address according to RFC 2464 section 7 */
  PhysAddrPtr[0] = 0x33;
  PhysAddrPtr[1] = 0x33;
  PhysAddrPtr[2] = NetAddrPtr->addr[12];
  PhysAddrPtr[3] = NetAddrPtr->addr[13];
  PhysAddrPtr[4] = NetAddrPtr->addr[14];
  PhysAddrPtr[5] = NetAddrPtr->addr[15];

} /* End of IpV6_VMulticastAddr2LinkLayerAddr() */

/**********************************************************************************************************************
 *  IpV6_VResolveLinkLayerAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VResolveLinkLayerAddr(
  uint8                                             IpCtrlIdx,
  TcpIp_SizeOfIpV6SourceAddressTableEntryType       SrcAddrIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)            PhysAddrPtr,
  P2VAR(IpV6_ListIdxType, AUTOMATIC, IPV6_APPL_VAR) NcEntryIdxPtr)
{
  Std_ReturnType Result = E_OK;
  TCPIP_P2V(IpV6_NeighborCacheEntryType) ncEntryPtr;
  TcpIp_SizeOfNdpConfigType ndpConfigIdx;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(ndpConfigIdx < TcpIp_GetSizeOfNdpConfig());
  TCPIP_ASSERT(NULL_PTR != PhysAddrPtr);
  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);
  TCPIP_ASSERT(NULL_PTR != NcEntryIdxPtr);

  /* #10 Check if the destination is multicast */
  if (IPV6_ADDR_IS_MULTICAST(*DstAddrPtr))
  {
    /* #20 map IPv6 multicast address to ethernet multicast address according to RFC 2464 section 7 */
    IpV6_VMulticastAddr2LinkLayerAddr(PhysAddrPtr, DstAddrPtr);
  }
  else
  {
    IPV6_BEGIN_CRITICAL_SECTION_NC();

    /* #30 lookup neighbor cache for link-layer address of the next hop neighbor */
    IpV6_Ndp_VNCGetOrCreateEntry(IpCtrlIdx, DstAddrPtr, NcEntryIdxPtr);

    TCPIP_ASSERT(NcEntryIdxPtr != NULL_PTR);
    TCPIP_ASSERT(*NcEntryIdxPtr >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
    TCPIP_ASSERT(*NcEntryIdxPtr <  TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

    ncEntryPtr = TcpIp_GetAddrIpV6NeighborCacheEntry(*NcEntryIdxPtr);

    /* #40 Check if the neighbor cache entry is in valid state, send packet only if state is not incomplete */
    if ((IPV6_REACHABLE_STATE_INCOMPLETE != ncEntryPtr->State))
    {
      /* ok, we can send the packet */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_LL_ADDR_COPY(PhysAddrPtr, &ncEntryPtr->LinkLayerAddress[0]);

      /* #50 start NUD if entry is stale */
      if (IPV6_REACHABLE_STATE_STALE == ncEntryPtr->State)
      {
        /* delay sending of NUD probes */
        IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, *NcEntryIdxPtr, IPV6_REACHABLE_STATE_DELAY);
        ncEntryPtr->RetryCount = 0;
        IPV6_SET_EVENT_TIME_MS(ncEntryPtr->NextEventTime, TcpIp_GetNudFirstProbeDelayOfNdpConfig(ndpConfigIdx));
      }
    }
    else
    {
      /* address resolution in progress */
      /* FEAT-5752 Update the source address index as the source address of the
       * triggering interface is known
       */
      ncEntryPtr->NsSrcAddressIdx = SrcAddrIdx;
      Result = E_NOT_OK;
    }

    IPV6_END_CRITICAL_SECTION_NC();
  }
  return Result;
} /* End of IpV6_VResolveLinkLayerAddr() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_VIsMatchingSolicitedNodeAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VIsMatchingSolicitedNodeAddress(
  uint8                                 IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)               IpAddrPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(IpAddrPtr != NULL_PTR);

  /* #10 Check for solicited-node prefix [FF02:0:0:0:0:1:FF__:____]/104 */
  if (IpV6_VMatchPrefix(IpAddrPtr, &IpV6_PrefixSolicitedNode.Prefix.addr[0], IpV6_PrefixSolicitedNode.PrefixLenBits) == E_OK)
  {
    TcpIp_IpV6SourceAddressIterType srcAddrIdx;
    /* #20 Traverse the source address table to see if last 3 bytes of solicited address matches local address */
    for (srcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
         srcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
         srcAddrIdx++)
    {
      /* compare last three bytes of address */

      if (IPV6_LADDR_STATE_INVALID == TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State)
      {
        /* skip invalid entry */
        continue;
      }

      if (   (TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->Address.addr[13] == IpAddrPtr->addr[13])  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->Address.addr[14] == IpAddrPtr->addr[14])
          && (TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->Address.addr[15] == IpAddrPtr->addr[15]))
      {
        /* solicited-node multicast for one of our source addresses */
        Result = E_OK;
        break;
      }
    }
  }
  else
  {
    /* do nothing */
  }

  return Result;
} /* IpV6_VIsMatchingSolicitedNodeAddress() */

/**********************************************************************************************************************
 *  IpV6_VLookupMulticastAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(TcpIp_IpV6MulticastAddrIterType, IPV6_CODE) IpV6_VLookupMulticastAddress(
  uint8                                 IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)               IpAddrPtr)
{
  TcpIp_IpV6MulticastAddrIterType ipV6MulticastAddrIdx;
  TcpIp_IpV6MulticastAddrIterType matchingMcAddrIdx = TCPIP_IPV6_MC_ADDR_IDX_INV;
  IPV6_P2C(IpV6_AddrType) mcAddrPtr;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(IpAddrPtr != NULL_PTR);

  /* #10 Check if any multicast address is configured for the Ip controller index */
  if (   (TcpIp_GetIpV6MulticastAddrEndIdxOfIpV6Ctrl(IpCtrlIdx)   == TCPIP_NO_IPV6MULTICASTADDRENDIDXOFIPV6CTRL)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetIpV6MulticastAddrStartIdxOfIpV6Ctrl(IpCtrlIdx) == TCPIP_NO_IPV6MULTICASTADDRSTARTIDXOFIPV6CTRL))
  {
    matchingMcAddrIdx = TCPIP_IPV6_MC_ADDR_IDX_INV;
  }
  else
  {
    /* #20 Traverse through list of configured multicast addresses for a matching address */
    for (ipV6MulticastAddrIdx = TcpIp_GetIpV6MulticastAddrStartIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6MulticastAddrIdx < TcpIp_GetIpV6MulticastAddrEndIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6MulticastAddrIdx++)
    {
      if (TcpIp_IsIpV6MulticastAddrActiveUsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE)
      {
        TcpIp_SizeOfIpV6MulticastAddrActiveType activeMcAddrIdx = TcpIp_GetIpV6MulticastAddrActiveIdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);
        mcAddrPtr = TcpIp_GetAddrIpV6MulticastAddrActive(activeMcAddrIdx);
      }
      else if (TcpIp_IsDefaultAddrV6UsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE)
      {
        TcpIp_SizeOfDefaultAddrV6Type defaultAddrIdx = TcpIp_GetDefaultAddrV6IdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);
        mcAddrPtr = TcpIp_GetAddrDefaultAddrV6(defaultAddrIdx);
      }
      else
      {
        mcAddrPtr = (IpV6_AddrType*) NULL_PTR;
        TCPIP_ASSERT_UNREACHABLE();
      }

      if (   (mcAddrPtr != NULL_PTR) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (IPV6_ADDR_EQUALS(*IpAddrPtr, *mcAddrPtr)))
      {
        matchingMcAddrIdx = ipV6MulticastAddrIdx;
        break;
      }
    }
  }
  return matchingMcAddrIdx;
} /* End of IpV6_VLookupMulticastAddress()*/ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_VIngressFilter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VIngressFilter(
  uint8                                 IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)               DstAddrPtr,
  IPV6_P2V(TcpIp_SizeOfLocalAddrV6Type) LocalAddrV6IdxPtr)
{
  Std_ReturnType        retVal = E_NOT_OK;
  IpV6_AddrTypeType     DstAddrType;

  /*
   * Check whether destination address is one of the following:
   * - Unicast
   *   - Address in SourceAddressTable | CtrlAddrIdx
   *   - Temporaray Address of an address in SourceAddressTable (PrivExt) | CtrlAddrIdx + TempAddrIdx
   * - Multicast
   *   - All-Nodes Multicast Address | CtrlAddrIdx
   *   - Solicited Node Multicast Address
   *     - If PrivExt are active the node may have multiple interface
   *       identifiers an thus multiple solicited node addresses
   *   - Joinded Multicast Address (MLDv2)
   */

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(LocalAddrV6IdxPtr != NULL_PTR);
  TCPIP_ASSERT(DstAddrPtr != NULL_PTR);

  /* determine type of destination address */
  DstAddrType = IpV6_VGetAddrType(DstAddrPtr);

  if ((IPV6_ADDR_TYPE_LL_UNICAST == DstAddrType) || (IPV6_ADDR_TYPE_UNICAST == DstAddrType))
  {
    /* #10 If destination is unicast determine if it matches a valid local source address */
    TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx;
    if (E_OK == IpV6_VSATLookup(IpCtrlIdx, DstAddrPtr, &ipV6SrcAddrIdx))
    {
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      IpV6_LocAddrStateType SrcAddrState;
      SrcAddrState = TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx)->State;

      if (IPV6_LADDR_STATE_TENTATIVE != SrcAddrState)
#endif
      {
        /* accept packets going to one of our unicast source addresses */
        (*LocalAddrV6IdxPtr) = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);
        retVal = E_OK;
      }
    }
  }
  /* packet destination is multicast with valid scope */
  else if (   (IPV6_ADDR_TYPE_MULTICAST == DstAddrType)
           && (IPV6_ADDR_MULTICAST_HAS_VALID_SCOPE(*DstAddrPtr)))
  {
    /* #20 If destination is multicast with valid scope determine if it is solicited node address or all-nodes
      * multicast address. If not either, check in list of configured multicast addresses */
    TcpIp_IpV6MulticastAddrIterType ipV6MulticastAddrIdx = IpV6_VLookupMulticastAddress(IpCtrlIdx, DstAddrPtr);

    /* Check if the address is a solicited node or all nodes multicast */
    if (   (IpV6_VIsMatchingSolicitedNodeAddress(IpCtrlIdx, DstAddrPtr) == E_OK)  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    /* all-nodes link-local address [FF02:0:0:0:0:0:0:1] */
        || (IPV6_ADDR_EQUALS(*DstAddrPtr, IpV6_AddrAllNodesLL)))
    {
      (*LocalAddrV6IdxPtr) = TCPIP_LOCAL_ADDR_V6_IDX_ANY;
      retVal = E_OK;
    }
    /* Check if a valid multicast address index, */
    else if (ipV6MulticastAddrIdx != TCPIP_IPV6_MC_ADDR_IDX_INV)
    {
      (*LocalAddrV6IdxPtr) = TcpIp_GetLocalAddrV6IdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);
      retVal = E_OK;
    }
    else
    {
      /* Not a valid address index */
    }
  }
  else
  {
    /* Ignore destination address with invalid scope
     * Ignore the following destination address types:
     * - Unspecified ::/128
     * - Loopback    ::1/128
     */
  }

  return retVal; /* drop all other packets */
} /* End of IpV6_VIngressFilter() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_VGetCommonPrefixLen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_VGetCommonPrefixLen(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) Addr1Ptr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) Addr2Ptr)
{
  uint8 MatchingBits = 0;
  uint8 AddrByteIdx;

  TCPIP_ASSERT(NULL_PTR != Addr1Ptr);
  TCPIP_ASSERT(NULL_PTR != Addr2Ptr);

  /*
  * The implementation of the CommonPrefixLen function is as per RFC 3484 2.2
  * This implementation is made obsolete by RFC 6724. However since there
  * is no side effects expected, the old implementation is retained
  */
  /* #10 Get the longest common prefix length in bits */
  for (AddrByteIdx = 0; AddrByteIdx < IPV6_ADDRESS_LEN_BYTE; AddrByteIdx++)
  {
    if (Addr1Ptr->addr[AddrByteIdx] != Addr2Ptr->addr[AddrByteIdx])
    {
      uint8 diffBits = (uint8)(Addr1Ptr->addr[AddrByteIdx] ^ Addr2Ptr->addr[AddrByteIdx]);

      while ((diffBits & 0x80u) == 0u) /* 0x80 = 10000000 */
      {
        diffBits <<= 1;
        MatchingBits++;
      }
      break;
    }

    MatchingBits += IPV6_BITS_IN_BYTE;
  }

  return MatchingBits;
} /* End of IpV6_VGetCommonPrefixLen() */


/**********************************************************************************************************************
 *  IpV6_VHandleUnknownTlvOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VHandleUnknownTlvOption(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2C(uint8)              IpV6PktDataPtr,
  uint16                       IpV6PktDataLen,
  uint16                       UnknownOptOffset)
{
  Std_ReturnType Result;
  uint8 OptType;

  TCPIP_ASSERT(NULL_PTR != IpV6PktDataPtr);
  TCPIP_ASSERT(UnknownOptOffset <= IpV6PktDataLen);

  OptType = IpV6PktDataPtr[UnknownOptOffset];
  /* OptLength = IpV6PktDataPtr[UnknownOptOffset+1]; */

  /* #10 Parse the two most significant bits of the OptionType and decide handling of option */
  switch (OptType >> 6)
  {
    case 0: /* skip over this option and continue processing the header */
      /* just ignore the option */
      Result = E_OK;
    break;

    case 1: /* silently discard the packet */

      Result = E_NOT_OK; /* stop processing the packet */
    break;

    case 2: /* discard the packet, send ICMP parameter problem message Code 2 to source address of the packet */

#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
      IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_UNKNOWN_OPTION, IpV6PktDataPtr, IpV6PktDataLen, UnknownOptOffset);
#endif

      Result = E_NOT_OK; /* stop processing the packet */
    break;

    /* only 4 possible cases */
    default: /* case 3: discard the packet, only if not multicast destination: ICMP Message Parameter problem code 2 */
      {
        IpV6_AddrType destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(destAddr, IpV6PktDataPtr[IPV6_HDR_OFF_DSTADDR]);

#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
        if (!IPV6_ADDR_IS_MULTICAST(destAddr))
        {
          IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_UNKNOWN_OPTION, IpV6PktDataPtr, IpV6PktDataLen, UnknownOptOffset);
        }
#endif
      }
      Result = E_NOT_OK; /* stop processing the packet */
    break;
  }

  return Result;
} /* End of IpV6_VHandleUnknownTlvOption() */


/**********************************************************************************************************************
 *  IpV6_MemCmp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, IPV6_CODE) IpV6_MemCmp(
  IPV6_P2C(uint8) Data1Ptr,
  IPV6_P2C(uint8) Data2Ptr,
  uint8           Blocks)
{
  boolean result = TRUE;
  uint8 blocksToCmp = Blocks;

  TCPIP_ASSERT(NULL_PTR != Data1Ptr);
  TCPIP_ASSERT(NULL_PTR != Data2Ptr);

  /* #10 Compare two data buffers */
  while (0u < blocksToCmp)
  {
    blocksToCmp--;

    if (Data1Ptr[blocksToCmp] != Data2Ptr[blocksToCmp])
    {
      result = FALSE;
      break;
    }
  }

  return result;
} /* End of IpV6_MemCmp() */


/**********************************************************************************************************************
 *  IpV6_CmpNetAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, IPV6_CODE) IpV6_CmpNetAddr(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) NetAddr1Ptr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) NetAddr2Ptr)
{
  boolean result = TRUE;

  TCPIP_ASSERT(NULL_PTR != NetAddr1Ptr);
  TCPIP_ASSERT(NULL_PTR != NetAddr2Ptr);

  /* #10 Compare two network addresses */
  if (   (NetAddr1Ptr->addr32[3] != NetAddr2Ptr->addr32[3])
      || (NetAddr1Ptr->addr32[2] != NetAddr2Ptr->addr32[2])
      || (NetAddr1Ptr->addr32[1] != NetAddr2Ptr->addr32[1])
      || (NetAddr1Ptr->addr32[0] != NetAddr2Ptr->addr32[0]))
  {
    result = FALSE;
  }

  return result;
} /* End of IpV6_CmpNetAddr() */

/**********************************************************************************************************************
 *  IpV6_VGetSolicitedNodeAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VGetSolicitedNodeAddr(
  IPV6_P2V(IpV6_AddrType) MulticastAddrPtr,
  IPV6_P2C(IpV6_AddrType) NetAddrPtr,
  IpV6_MulticastScopeType Scope)
{
  TCPIP_ASSERT(NULL_PTR != MulticastAddrPtr);

  /*#10 Obtain solicited node multicast address from network address */
  MulticastAddrPtr->addr[0] = (uint8)0xFF;
  MulticastAddrPtr->addr[1] = (uint8)(Scope & 0x0Fu);

  IpV6_MemSet(&MulticastAddrPtr->addr[2], 0u, 9u);

  MulticastAddrPtr->addr[11] = 1;
  MulticastAddrPtr->addr[12] = 0xFF;
  MulticastAddrPtr->addr[13] = NetAddrPtr->addr[13];
  MulticastAddrPtr->addr[14] = NetAddrPtr->addr[14];
  MulticastAddrPtr->addr[15] = NetAddrPtr->addr[15];
} /* End of IpV6_VGetSolicitedNodeAddr() */

/**********************************************************************************************************************
 *  IpV6_MemSet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_MemSet(
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_DATA) TargetPtr,
  uint8                                   Value,
  uint16                                  Length)
{
  uint16 i;

  /* #10 Fill buffer with a certain value */
  for (i = 0; i < Length; i++)
  {
    TargetPtr[i] = Value;
  }
} /* End of IpV6_MemSet() */


/**********************************************************************************************************************
 *  IpV6_VGetAddrType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(IpV6_AddrTypeType, IPV6_CODE) IpV6_VGetAddrType(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) AddrPtr)
{
  IpV6_AddrTypeType AddrType;

  TCPIP_ASSERT(NULL_PTR != AddrPtr);

  /* #10 Get the type of network address */
  if (IPV6_ADDR_IS_MULTICAST(*AddrPtr)) /* multicast prefix: FF00::/8 */
  {
    AddrType = IPV6_ADDR_TYPE_MULTICAST;
  }
  else if (IPV6_ADDR_IS_LINK_LOCAL(*AddrPtr)) /* link-local unicast prefix: FE80::/10 */
  {
    AddrType = IPV6_ADDR_TYPE_LL_UNICAST;
  }
  else if (IPV6_ADDR_IS_LOOPBACK(*AddrPtr)) /* loopback address ::1/128 */
  {
    AddrType = IPV6_ADDR_TYPE_LOOPBACK;
  }
  else if (IPV6_ADDR_IS_UNSPECIFIED(*AddrPtr)) /* unspecified address ::/128 */
  {
    AddrType = IPV6_ADDR_TYPE_UNSPECIFIED;
  }
  else
  {
    AddrType = IPV6_ADDR_TYPE_UNICAST;
  }

  return AddrType;
} /* End of IpV6_VGetAddrType() */


/* PREFIX LIST FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VMatchPrefix()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VMatchPrefix(
  IPV6_P2C(IpV6_AddrType) AddrPtr,
  IPV6_P2C(uint8)         PrefixPtr,
  uint8                   PrefixLenBits)
{
  uint8 i = 0;
  Std_ReturnType result = E_OK;
  uint8 lenBits = PrefixLenBits;

  TCPIP_ASSERT(NULL_PTR != AddrPtr);
  TCPIP_ASSERT(NULL_PTR != PrefixPtr);

  /* #10 Check if the address has matching prefix by comparing first n bytes of the prefix */
  while (IPV6_BITS_IN_BYTE <= lenBits)
  {
    if (AddrPtr->addr[i] != PrefixPtr[i])
    {
      result = E_NOT_OK;
      break;
    }

    i++;
    lenBits -= IPV6_BITS_IN_BYTE;
  }

  /* if prefix length is not multiple of 8, we have to compare the first PrefixLenBits bits of the next byte */
  if (   (result == E_OK)
      && (0u < lenBits))
  {
    uint8 ByteMask;
    /* create a mask that masks the first PrefixLenBits bits in a byte */
    ByteMask = (uint8)(0xFFu << (IPV6_BITS_IN_BYTE - lenBits)); /* 11..00.. */

    /* check if the first PrefixLenBits of prefix and address are equal */
    if ((AddrPtr->addr[i] & ByteMask) != (PrefixPtr[i] & ByteMask))
    {
      result = E_NOT_OK;
    }
  }

  return result;
} /* End of IpV6_VMatchPrefix() */

/**********************************************************************************************************************
 *  IpV6_VIsStaticOnLinkPrefix()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, IPV6_CODE) IpV6_VIsStaticOnLinkPrefix(
  TcpIp_IpV6CtrlIterType  IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType) PrefixPtr,
  uint8                   PrefixBitLen)
{
  boolean result = FALSE;
  TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx;
#if (TCPIP_IPV6STATICONLINKPREFIX == STD_ON)
  TcpIp_SizeOfIpV6StaticOnLinkPrefixType ipV6StaticOnLinkPrefixIdx;
#endif
  TcpIp_SizeOfNdpConfigType ndpConfigIdx;

  ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(ndpConfigIdx < TcpIp_GetSizeOfNdpConfig());

#if (TCPIP_IPV6STATICONLINKPREFIX == STD_ON)
  /* #10 Determine whether the given prefix is covered by one of the statically
   * configured on-link prefixes of the controller.*/

  for (ipV6StaticOnLinkPrefixIdx = TcpIp_GetIpV6StaticOnLinkPrefixStartIdxOfNdpConfig(ndpConfigIdx);
       ipV6StaticOnLinkPrefixIdx < TcpIp_GetIpV6StaticOnLinkPrefixEndIdxOfNdpConfig(ndpConfigIdx);
       ipV6StaticOnLinkPrefixIdx++)
  {
    if (   (TcpIp_GetBitLengthOfIpV6StaticOnLinkPrefix(ipV6StaticOnLinkPrefixIdx) <= PrefixBitLen)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (E_OK == IpV6_VMatchPrefix(PrefixPtr, &TcpIp_GetAddrPrefixOfIpV6StaticOnLinkPrefix(ipV6StaticOnLinkPrefixIdx)->addr[0], TcpIp_GetBitLengthOfIpV6StaticOnLinkPrefix(ipV6StaticOnLinkPrefixIdx))))
    {
      /* Given prefix is covered by one of the statically configured on-link address prefixes. */
      result = TRUE;
      break;
    }
  }
#else
  IPV6_UNUSED_PARAMETER(PrefixBitLen);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

  if (result == FALSE)
  {
    /* #20 Determine whether the given prefix is covered by the prefix of a
     * local source address that has been marked to be on-link in the configuration.*/
    for (ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6SrcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6SrcAddrIdx++)
    {
      if (   (TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx)->State != IPV6_LADDR_STATE_INVALID)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (TcpIp_IsPrefixIsOnLinkOfIpV6SourceAddress(ipV6SrcAddrIdx) == TRUE)
          && (IPV6_CMP_64BIT_PREFIX(*PrefixPtr, TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx)->Address) == TRUE))
      {
        /* Given prefix is covered by the prefix of a statically configured source address with an on-link prefix. */
        result = TRUE;
        break;
      }
    }
  }

  return result;
} /* End of IpV6_VIsStaticOnLinkPrefix() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_VSearchforAddressinPrefixList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(boolean, IPV6_CODE) IpV6_VSearchforAddressinPrefixList(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr
)
{
  boolean result = FALSE;
  TcpIp_SizeOfIpV6PrefixListEntryType plEntryIdx;

  IPV6_BEGIN_CRITICAL_SECTION();
  /* #10 Check if address is covered by a prefix in the dynamic on-link prefix list */
  for (plEntryIdx = TcpIp_GetIpV6PrefixListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       plEntryIdx < TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       plEntryIdx++)
  {
    TCPIP_P2C(IpV6_PrefixListEntryType) plEntryPtr = TcpIp_GetAddrIpV6PrefixListEntry(plEntryIdx);

    if (IPV6_TIME_EXPIRED(plEntryPtr->ExpireTime) == TRUE)
    {
      IpV6_Ndp_VPLRemoveEntry(IpCtrlIdx, plEntryIdx);
    }
    else if (E_OK == IpV6_VMatchPrefix(DstAddrPtr, &plEntryPtr->Prefix.addr[0], plEntryPtr->PrefixLenBits))
    {
      /* destination is on-link, so next hop is the destination node */
      result = TRUE;
      break;
    }
    else
    {
      /* do nothing */
    }
  }

  IPV6_END_CRITICAL_SECTION();

  return result;
} /* IpV6_VSearchforAddressinPrefixList() */

/**********************************************************************************************************************
 *  IpV6_VIsDestinationOnLink()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, IPV6_CODE) IpV6_VIsDestinationOnLink(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr)
{
  boolean result;
  IpV6_AddrTypeType DstAddrType;

  DstAddrType = IpV6_VGetAddrType(DstAddrPtr);

  /* #10 Check whether destination address is a link-local fe80::/10 or multicast address. */

  /* we have to determine the next hop neighbor first */
  if (   (IPV6_ADDR_TYPE_MULTICAST == DstAddrType)
      || (IPV6_ADDR_TYPE_LL_UNICAST == DstAddrType)) /* multicast and link local prefix is always on-link */
  {
    result = TRUE;
  }

  /* #20 Check whether destination address is covered by a statically configured on-link prefix. */

  else if (IpV6_VIsStaticOnLinkPrefix(IpCtrlIdx, DstAddrPtr, 128u) == TRUE)
  {
    result = TRUE;
  }

  /* #30 Check whether destination address is covered by a prefix in the dynamic on-link prefix list. */
  else
  {
    result = IpV6_VSearchforAddressinPrefixList(IpCtrlIdx, DstAddrPtr);
  }
  return result;
} /* End of IpV6_VIsDestinationOnLink() */


/* DEFAULT ROUTER TABLE FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VGetDefaultRouterAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VGetDefaultRouterAddr(
  TcpIp_IpV6CtrlIterType                               IpCtrlIdx,
  TcpIp_LocalAddrV6IterType                            LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)                              DstAddrPtr,
  IPV6_P2V(boolean)                                    IsReachable,
  IPV6_P2V(TcpIp_SizeOfIpV6DefaultRouterListEntryType) DrlEntryIdxPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx;
  boolean reachableRouterFound = FALSE;

  IPV6_UNUSED_PARAMETER(DstAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Check if list of default routers is empty. */

  if (TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) == TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    /* #20 Iterate over list of default routers and stop if a reachable router is found. */

    for (drlEntryIdx = TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
         drlEntryIdx < TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
         drlEntryIdx++)
    {
      TCPIP_P2V(IpV6_DefaultRouterListEntryType) drlEntryPtr = TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx);
      TcpIp_SizeOfIpV6NeighborCacheEntryType ncEntryIdx;

      if ((drlEntryPtr->LocalIpV6Idx != TCPIP_LOCAL_ADDR_V6_IDX_ANY) && (drlEntryPtr->LocalIpV6Idx != LocalAddrV6Idx))
      {
        continue;
      }

      ncEntryIdx = TcpIp_GetIpV6DefaultRouterListEntry(drlEntryIdx).NcIdxHint;

      if (E_OK == IpV6_Ndp_VNCLookup(IpCtrlIdx, &drlEntryPtr->NextHopAddress, &ncEntryIdx))
      {
        /* store updated neighbor cache index */
        drlEntryPtr->NcIdxHint = ncEntryIdx;

        if (IPV6_REACHABLE_STATE_INCOMPLETE != TcpIp_GetIpV6NeighborCacheEntry(ncEntryIdx).State)
        {
          /* we found a router which is known to be reachable. select this router. */
          reachableRouterFound = TRUE;
          retVal = E_OK;
          break;
        }
      }
    }

    /* #30 If not reachable router was found select default router from the list using round-robin strategy. */
    if (reachableRouterFound == FALSE)
    {
      TcpIp_SizeOfIpV6DefaultRouterListEntryType drLstStartIdx = TcpIp_GetNextRouterProbeIdxOfIpV6CtrlDyn(IpCtrlIdx);
      boolean wrap = FALSE;

      drlEntryIdx = TcpIp_GetNextRouterProbeIdxOfIpV6CtrlDyn(IpCtrlIdx);

      /* Iterate over the default router list to skip unusable static default router entries */
      while ((drLstStartIdx != drlEntryIdx) || (wrap != TRUE))
      {
        TCPIP_P2C(IpV6_DefaultRouterListEntryType) drlEntryPtr;
        TcpIp_IncNextRouterProbeIdxOfIpV6CtrlDyn(IpCtrlIdx);
        if (  TcpIp_GetNextRouterProbeIdxOfIpV6CtrlDyn(IpCtrlIdx)
            < TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
        {
          drlEntryIdx = TcpIp_GetNextRouterProbeIdxOfIpV6CtrlDyn(IpCtrlIdx);
        }
        else
        {
          drlEntryIdx = TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
          TcpIp_SetNextRouterProbeIdxOfIpV6CtrlDyn(IpCtrlIdx, drlEntryIdx);
          wrap = TRUE;
        }

        drlEntryPtr = TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx);

        /* Check if the current router can be used for the provided source address Idx */
        if ((drlEntryPtr->LocalIpV6Idx == TCPIP_LOCAL_ADDR_V6_IDX_ANY) || (drlEntryPtr->LocalIpV6Idx == LocalAddrV6Idx))
        {
          retVal = E_OK;
          break;
        }
      }

    }

    (*IsReachable) = reachableRouterFound;
    *DrlEntryIdxPtr = drlEntryIdx;
  }

  return retVal;
} /* End of IpV6_VGetDefaultRouterAddr() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/* SOURCE ADDRESS HANDLING FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VBuildSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VBuildSourceAddress(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA)         IfIdPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) PrefixPtr,
  P2VAR(IpV6_AddrType, AUTOMATIC, IPV6_APPL_VAR)    SrcAddrPtr) /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  TCPIP_ASSERT(NULL_PTR != PrefixPtr);
  TCPIP_ASSERT(NULL_PTR != SrcAddrPtr);

  /* #10 Build a network address using given prefix and interface identifier */
  /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
  IpV6_MemCpy(&SrcAddrPtr->addr[0], &PrefixPtr->addr[0], IPV6_PREFIX_LEN_BYTE);
  IpV6_MemCpy(&SrcAddrPtr->addr[IPV6_PREFIX_LEN_BYTE], &IfIdPtr[0], IPV6_INTERFACE_IDENTIFIER_LEN_BYTE);

} /* End of IpV6_VBuildSourceAddress() */


/**********************************************************************************************************************
 *  IpV6_VIsValidSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*/
TCPIP_LOCAL FUNC(boolean, IPV6_CODE) IpV6_VIsValidSourceAddress(
  TcpIp_IpV6CtrlIterType                       IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                      SrcAddrPtr,
  boolean                                      AllowUnspecAddr,
  IPV6_P2V(IpV6_LocAddrStateType)              SrcAddrStatePtr,
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressType)  SrcAddrIdxPtr)
{
  boolean Result;

  TCPIP_ASSERT(SrcAddrPtr != NULL_PTR);

  IPV6_BEGIN_CRITICAL_SECTION_SAT();

  /* #10 Look up for the address in source address table */
  if (E_OK == IpV6_VSATLookup(IpCtrlIdx, SrcAddrPtr, SrcAddrIdxPtr))
  {
    IpV6_LocAddrStateType SrcAddrState;

    SrcAddrState = TcpIp_GetIpV6SourceAddressTableEntry(*SrcAddrIdxPtr).State;

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    if (IPV6_LADDR_STATE_TENTATIVE == SrcAddrState)
    {
      Result = FALSE;
    }
    else
#endif
    {
      Result = TRUE;
    }

    (*SrcAddrStatePtr) = SrcAddrState;
  }
  /* #20 Check if address is unspecified address and is allowed to be used */
  else if (   (TRUE == AllowUnspecAddr) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
           && (IPV6_ADDR_IS_UNSPECIFIED(*SrcAddrPtr)))
  {
    (*SrcAddrIdxPtr)   = TCPIP_IPV6_SRC_ADDR_IDX_INV;
    (*SrcAddrStatePtr) = IPV6_LADDR_STATE_INVALID;
    Result = TRUE;
  }
  else
  {
    (*SrcAddrIdxPtr)  = TCPIP_IPV6_SRC_ADDR_IDX_INV;
    (*SrcAddrStatePtr) = IPV6_LADDR_STATE_INVALID;
    Result = FALSE;
  }

  IPV6_END_CRITICAL_SECTION_SAT();

  return Result;
} /* End of IpV6_VIsValidSourceAddress() */

/**********************************************************************************************************************
 *  IpV6_Ip_VCompareScopeOfAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_Ip_VCompareScopeOfAddress(
  IPV6_P2C(IpV6_AddrType)                     IpV6AddrPtr,
  TCPIP_P2C(IpV6_SourceAddressTableEntryType) SatEntryAPtr,
  TCPIP_P2C(IpV6_SourceAddressTableEntryType) SatEntryBPtr
)
{
  IpV6_MulticastScopeType dstAddrScope;
  uint8 preference = IPV6_CMP_RES_NO_PREFERENCE;

  /* Determine scope of the two addresses being comapred
   * Since source addresses are unicast, scope shall be either link local or global
   */
  IpV6_MulticastScopeType srcAddrScopeA = IPV6_ADDR_IS_LINK_LOCAL(SatEntryAPtr->Address)?IPV6_MULTICAST_SCOPE_LINK_LOCAL: IPV6_MULTICAST_SCOPE_GLOBAL;
  IpV6_MulticastScopeType srcAddrScopeB = IPV6_ADDR_IS_LINK_LOCAL(SatEntryBPtr->Address)?IPV6_MULTICAST_SCOPE_LINK_LOCAL: IPV6_MULTICAST_SCOPE_GLOBAL;

  /* #10 Determine the scope of the destination address */
  if (IPV6_ADDR_IS_MULTICAST(*IpV6AddrPtr))
  {
    /* If the address is multicast, determine scope from the scope field */
    dstAddrScope = (IpV6_MulticastScopeType) IPV6_ADDR_MULTICAST_SCOPE(*IpV6AddrPtr);
  }
  else if (IPV6_ADDR_IS_LINK_LOCAL(*IpV6AddrPtr))
  {
    /* unicast link-local is mapped to multicast link-local scope [RFC 6724 3.1. Scope Comparisons] */
    dstAddrScope = IPV6_MULTICAST_SCOPE_LINK_LOCAL;
  }
  else
  {
    /* unicast global mapped to multicast global scope [RFC 6724 3.1. Scope Comparisons] */
    dstAddrScope = IPV6_MULTICAST_SCOPE_GLOBAL;
  }

  /* #20 Prefer source address with appropriate scope (as per RFC 6724 5. Source Address Selection) */
  if (srcAddrScopeA < srcAddrScopeB)
  {
    if (srcAddrScopeA < dstAddrScope)
    {
      preference = IPV6_CMP_RES_PREFER_B;
    }
    else
    {
      preference = IPV6_CMP_RES_PREFER_A;
    }
  }
  else if (srcAddrScopeB < srcAddrScopeA)
  {
    if (srcAddrScopeB < dstAddrScope)
    {
      preference = IPV6_CMP_RES_PREFER_A;
    }
    else
    {
      preference = IPV6_CMP_RES_PREFER_B;
    }
  }
  else
  {
    /* Do nothing, IPV6_CMP_RES_NO_PREFERENCE is returned */
  }

  return preference;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VCompareStateOfAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_Ip_VCompareStateOfAddress(
  IpV6_LocAddrStateType StateA,
  IpV6_LocAddrStateType StateB)
{
  uint8 preference = IPV6_CMP_RES_NO_PREFERENCE;

  /* #10 Compare the states of two given addresses, choose the address with preferred state */
  if (   (IPV6_LADDR_STATE_PREFERRED == StateA)
      && (IPV6_LADDR_STATE_PREFERRED != StateB))
  {
    preference = IPV6_CMP_RES_PREFER_A;
  }
  else if (   (IPV6_LADDR_STATE_PREFERRED == StateB)
           && (IPV6_LADDR_STATE_PREFERRED != StateA))
  {
    preference = IPV6_CMP_RES_PREFER_B;
  }
  else
  {
    /* do nothing */
  }

  return preference;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VComparePrefixLenOfAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_Ip_VComparePrefixLenOfAddress(
  uint8 PrefixLenA,
  uint8 PrefixLenB)
{
  uint8 preference = IPV6_CMP_RES_NO_PREFERENCE;

  /* #10 Compare the prefix lengths of two addresses, choose the address with longer prefix */
  if (PrefixLenA > PrefixLenB)
  {
    preference = IPV6_CMP_RES_PREFER_A; /* Select source address A */
  }
  else if (PrefixLenB > PrefixLenA)
  {
    preference = IPV6_CMP_RES_PREFER_B; /* Select source address B */
  }
  else
  {
    /* do nothing */
  }
  return preference;
}

/**********************************************************************************************************************
 *  IpV6_VSourceAddrIsBetterThan()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(uint8, IPV6_CODE) IpV6_VSourceAddrIsBetterThan(
  TcpIp_SizeOfIpV6SourceAddressType                 SrcAddrIdxA,
  TcpIp_SizeOfIpV6SourceAddressType                 SrcAddrIdxB,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr)
{
  uint8 PrefixLenA;
  uint8 PrefixLenB;
  uint8 preference;
  TCPIP_P2C(IpV6_SourceAddressTableEntryType) satEntryAPtr;
  TCPIP_P2C(IpV6_SourceAddressTableEntryType) satEntryBPtr;

  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);
  TCPIP_ASSERT(SrcAddrIdxA < TcpIp_GetSizeOfIpV6SourceAddress());
  TCPIP_ASSERT(SrcAddrIdxB < TcpIp_GetSizeOfIpV6SourceAddress());

  satEntryAPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(SrcAddrIdxA);
  satEntryBPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(SrcAddrIdxB);

  if (SrcAddrIdxA == SrcAddrIdxB)
  {
    preference = IPV6_CMP_RES_NO_PREFERENCE;
  }
  /* #10 Check if the destination address directly matches one of the addresses based on RFC 6724 5 */
  /* Rule 1: Prefer same address */
  else if (IPV6_ADDR_EQUALS(satEntryAPtr->Address, *DstAddrPtr))
  {
    preference = IPV6_CMP_RES_PREFER_A;
  }
  else if (IPV6_ADDR_EQUALS(satEntryBPtr->Address, *DstAddrPtr))
  {
    preference = IPV6_CMP_RES_PREFER_B;
  }
  else
  {
    /* #20 Select preferred address by selecting the address with appropriate scope */
    /* Rule 2: Prefer appropriate scope */

    /* The scope of in IPv6 unicast address can be either link-local or global.
     * The deprecated site-local scope is handled like global scope according
     * to [RFC4291 2.5.7. Site-Local IPv6 Unicast Addresses]
     */
    preference = IpV6_Ip_VCompareScopeOfAddress(DstAddrPtr, satEntryAPtr, satEntryBPtr);

    /* Rule 3: Avoid deprecated addresses */
    if (preference == IPV6_CMP_RES_NO_PREFERENCE)
    {
      preference = IpV6_Ip_VCompareStateOfAddress(satEntryAPtr->State, satEntryBPtr->State);
    }
    /* Rule 4: Prefer home addresses */
    /* NOT IMPLEMENTED */

    /* Rule 5: Prefer outgoing interface */
    /* ONLY ONE INTERFACE SUPPORTED */

    /* Rule 6: Prefer matching label */

    /* Rule 7: Prefer public addresses (over temporary addresses) */
    /* Rule implemented outside this function */

    /* #30 If no preferred address was obtained, use the address with the longest prefix length */
    /* Rule 8: Use longest matching prefix */
    if (preference == IPV6_CMP_RES_NO_PREFERENCE)
    {
      PrefixLenA = IpV6_VGetCommonPrefixLen(&satEntryAPtr->Address, DstAddrPtr);
      PrefixLenB = IpV6_VGetCommonPrefixLen(&satEntryBPtr->Address, DstAddrPtr);
      preference = IpV6_Ip_VComparePrefixLenOfAddress(PrefixLenA, PrefixLenB);
    }
  }

  return preference;
} /* End of IpV6_VSourceAddrIsBetterThan() */

/**********************************************************************************************************************
 *  IpV6_VSelectSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSelectSourceAddress(
  TcpIp_IpV6CtrlIterType                       IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                      DstAddrPtr,
  TCPIP_P2V(TcpIp_SizeOfIpV6SourceAddressType) SrcAddrIdxPtr)
{
  Std_ReturnType                       retVal = E_OK;
  TcpIp_SizeOfIpV6SourceAddressType    satEntryIdx;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);

  if (IPV6_CTRL_STATE_LLADDR_READY > TcpIp_GetCtrlStateOfIpV6CtrlDyn(IpCtrlIdx))
  {
    /* we have no source adresses */
    retVal = E_NOT_OK;
    *SrcAddrIdxPtr = TcpIp_GetSizeOfIpV6SourceAddress();
  }
  else
  {
      /* #10 Set the link local address as the default selection */
      TcpIp_SizeOfIpV6SourceAddressType    satEntryIdxSelected = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);

      /* #20 traverse through the source address table, select the most preferred address */
      for (satEntryIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx) + 1u;
        satEntryIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
        satEntryIdx++)
      {
        if (IPV6_LADDR_STATE_INVALID == TcpIp_GetIpV6SourceAddressTableEntry(satEntryIdx).State)
        {
          /* skip invalid entry */
          continue;
        }

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      if (IPV6_LADDR_STATE_TENTATIVE != TcpIp_GetIpV6SourceAddressTableEntry(satEntryIdx).State)
#endif
        {
          if (IPV6_CMP_RES_PREFER_A == IpV6_VSourceAddrIsBetterThan(satEntryIdx, satEntryIdxSelected, DstAddrPtr))
          {
            satEntryIdxSelected = satEntryIdx;
          }
        }
      }


    /* #30 Verfiy that scope of selected source address is big enough for destination address */
    if (satEntryIdxSelected == TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx))
    {
      /* link-local address shall be used as source address? */
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      if (IPV6_LADDR_STATE_TENTATIVE == TcpIp_GetIpV6SourceAddressTableEntry(satEntryIdxSelected).State)
      {
        retVal = E_NOT_OK;
      }
#endif
      if (   (!(IPV6_ADDR_IS_LINK_LOCAL(*DstAddrPtr)))
          && (   (!(IPV6_ADDR_IS_MULTICAST(*DstAddrPtr)))
              && ((IPV6_ADDR_MULTICAST_SCOPE(*DstAddrPtr)) <= IPV6_MULTICAST_SCOPE_LINK_LOCAL)))
      {
        retVal = E_NOT_OK;
      }
    }

    /* Update the src address index if selected successfully */
    if (retVal == E_OK)
    {
      *SrcAddrIdxPtr = satEntryIdxSelected;
    }
  }


  return retVal;
} /* End of IpV6_VSelectSourceAddress() */

/**********************************************************************************************************************
 *  IpV6_VSATLookupPrefix()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSATLookupPrefix(
  TcpIp_IpV6CtrlIterType                      IpCtrlIdx,
  IPV6_P2C(uint8)                             AddrPrefixPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressType) SrcAddrIdxPtr,
  uint8                                       AddrCfgSrc)
{
  Std_ReturnType result = E_NOT_OK;
  TcpIp_SizeOfIpV6SourceAddressTableEntryType ipV6SrcAddrIdx;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NULL_PTR != AddrPrefixPtr);
  TCPIP_ASSERT(NULL_PTR != SrcAddrIdxPtr);
  TCPIP_ASSERT(*SrcAddrIdxPtr >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(*SrcAddrIdxPtr <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx));

  /* #10 Traverse through source address table for entries with valid state */
  for (ipV6SrcAddrIdx = *SrcAddrIdxPtr;
       ipV6SrcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
       ipV6SrcAddrIdx++)
  {
    if (IPV6_LADDR_STATE_INVALID != TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx)->State)
    {
      if (TRUE == IpV6_MemCmp(&TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx)->Address.addr[0], AddrPrefixPtr, (IPV6_PREFIX_LEN_BYTE)))
      {
        /* #20 If source address with matching prefix is found, check if
         *     any specific address configuration has been requested */
        if (   (TCPIP_IPADDR_ASSIGNMENT_ANY == AddrCfgSrc) /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
            || (TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(ipV6SrcAddrIdx) == AddrCfgSrc))
        {
          *SrcAddrIdxPtr = ipV6SrcAddrIdx;
          result = E_OK;
          break;
        }
      }
    }
  }

  return result;
} /* End of IpV6_VSATLookupPrefix() */


/**********************************************************************************************************************
 *  IpV6_VSATLookup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSATLookup(
  TcpIp_IpV6CtrlIterType                                IpCtrlIdx,
  P2CONST(IpV6_AddrType,      AUTOMATIC, IPV6_APPL_VAR)              SrcAddrPtr,
  P2VAR(TcpIp_SizeOfIpV6SourceAddressType, AUTOMATIC, IPV6_APPL_VAR) SrcAddrIdxPtr)
{
  Std_ReturnType Result = E_NOT_OK;
  TcpIp_SizeOfIpV6SourceAddressType srcAddrIdx;

  TCPIP_ASSERT(NULL_PTR != SrcAddrPtr);
  TCPIP_ASSERT(NULL_PTR != SrcAddrIdxPtr);

  /* #10 Traverse through source address table for entries with valid state */
  for (srcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx++)
  {
    if (TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State == IPV6_LADDR_STATE_INVALID)
    {
      /* skip invalid entry */
      continue;
    }

    if (TRUE == IPV6_CMP_64BIT_PREFIX(TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->Address, *SrcAddrPtr))
    {
      /* #20 If matching prefix is found store source address index */
      (*SrcAddrIdxPtr) = srcAddrIdx;

      if (IPV6_CMP_64BIT_INTERFACE_IDENTIFIER(TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->Address, *SrcAddrPtr) == TRUE)
      {
        Result = E_OK;
        break;
      }
      else
      {
        /* interface identifier odes not match */
      }
    }
  }

  return Result;
} /* End of IpV6_VSATLookup() */

/**********************************************************************************************************************
 *  IpV6_VSATRemoveEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VSATRemoveEntry(TcpIp_SizeOfIpV6SourceAddressType SrcAddrIdx)
{
  /* #10 Remove specific entry from source address table */
  TcpIp_GetAddrIpV6SourceAddressTableEntry(SrcAddrIdx)->State = IPV6_LADDR_STATE_INVALID;

  TCPIP_ASSERT(SrcAddrIdx < TcpIp_GetSizeOfIpV6SourceAddress());
} /* End of IpV6_VSATRemoveEntry() */


/**********************************************************************************************************************
 *  IpV6_VSATRemoveAllEntries()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VSATRemoveAllEntries(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_IpV6SourceAddressIterType srcAddrIdx;

  /* #10 Traverse through source address table */
  for (srcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx++)
  {
    /* #20 Invalidate all temporary addresses */
    TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State = IPV6_LADDR_STATE_INVALID;
  }
} /* End of IpV6_VSATRemoveAllEntries() */


/**********************************************************************************************************************
 *  IpV6_VHandleSourceAddrAssignmentChange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VHandleSourceAddrAssignmentChange(
  TcpIp_IpV6SourceAddressIterType    IpV6SrcAddrIdx,
  boolean                            AddrAssigned)
{
  TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);

  TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

  TCPIP_ASSERT(IpV6SrcAddrIdx >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(ipCtrlIdx));
  TCPIP_ASSERT(IpV6SrcAddrIdx <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(ipCtrlIdx));

  /* #10 If address is ready for use and is link local, change control state to ready */
  if (TRUE == AddrAssigned)
  {
    /* Address is now ready for use */

    if (IpV6SrcAddrIdx == TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(ipCtrlIdx))
    {
      /* Autoconfigured link-local address fe80::/10 */

      if (IPV6_CTRL_STATE_LLADDR_READY > TcpIp_GetCtrlStateOfIpV6CtrlDyn(ipCtrlIdx))
      {
        IPV6_CHANGE_STATE(ipCtrlIdx, IPV6_CTRL_STATE_LLADDR_READY);
      }

      /* after the link-local address is ready we start sending router solicitations (if enabled) */
    }
    else
    {
      /* Global address is ready */
      if (IPV6_CTRL_STATE_GBLADDR_READY > TcpIp_GetCtrlStateOfIpV6CtrlDyn(ipCtrlIdx))
      {
        IPV6_CHANGE_STATE(ipCtrlIdx, IPV6_CTRL_STATE_GBLADDR_READY);
      }
    }
  }
  /* #20 If address is no longer ready for use, unassign the address */
  else
  {

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
    /* #30 If Dhcp is enabled, perform dhcp reset to initialize the Dhcp state to INIT */
    if (IPV6_DHCPV6_MODE_DISABLED != TcpIp_GetDhcpModeOfIpV6Ctrl(ipCtrlIdx))
    {
      TcpIp_DhcpV6_NotifyAddressReset(ipCtrlIdx);
    }
#endif

    /* Leave solicited node multicast group of this address.
     * Note: The same interface identifier may be used for multiple source addresses.
     *       So the IpV6 will join and leave the same solicited-node multicast group multiple times.
     *       The number of "joins" is consistent with the number of "leaves" for the same multicast group.
     */
    IPV6_VJOIN_SOLICITED_NODE_MULTICAST_GROUP(ipCtrlIdx,
      &(TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->Address), FALSE);
  }

  /* #40 Notify upper-layer by invoking adddress change callback function */
  {
    TcpIp_IpAddrStateType AddrState;

    if (TRUE == AddrAssigned)
    {
      AddrState = TCPIP_IPADDR_STATE_ASSIGNED;
    }
    else
    {
      AddrState = TCPIP_IPADDR_STATE_UNASSIGNED;
    }

    TcpIp_Cbk_VLocalIpAssignmentChg(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx)), AddrState);
  }

} /* End of IpV6_VHandleSourceAddrAssignmentChange() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VHandleDADFailure()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VHandleDADFailure(
  IPV6_P2C(uint8)                    PhysAddrPtr,
  TcpIp_SizeOfIpV6SourceAddressType  IpV6SrcAddrIdx,
  uint8                              EventType)
{
  TcpIp_SizeOfLocalAddrV6Type  localAddrV6Idx;
  TcpIp_SizeOfIpV6CtrlType     ipCtrlIdx;

  localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

  TCPIP_ASSERT(IpV6SrcAddrIdx >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(ipCtrlIdx));
  TCPIP_ASSERT(IpV6SrcAddrIdx <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(ipCtrlIdx));

  IPV6_UNUSED_PARAMETER(EventType);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Check if DAD failure is hit for local or dhcpv6 address */
  if (IpV6SrcAddrIdx == TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(ipCtrlIdx))
  {
    /* Address configuration for link-local address has failed */
    /* #20 Handle link-local duplicate address. This handling includes PhysAddr comparison! */
    TcpIp_VDuplicateAddrDetected(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(localAddrV6Idx), &(TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->Address.addr[0]), PhysAddrPtr);

    IPV6_CHANGE_STATE(ipCtrlIdx, IPV6_CTRL_STATE_LLADDR_DAD_FAIL);
  }
  else
  {
# if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
    if (IPV6_DHCPV6_MODE_DISABLED != TcpIp_GetDhcpModeOfIpV6Ctrl(ipCtrlIdx))
    {
      /* #30 If DAD for dhcpv6 configured address failed, notify dhcpv6 */
      if (TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(IpV6SrcAddrIdx) == TCPIP_IPADDR_ASSIGNMENT_DHCP)
      {
        TCPIP_ASSERT(TcpIp_IsDhcpV6DataUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE); /* Assert that Dhcp is configured for the controller index */

        (void)TcpIp_DhcpV6_Decline(ipCtrlIdx,
          (IpBase_AddrIn6Type*)&(TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->Address));
      }
    }
# endif
  }
} /* End of IpV6_VHandleDADFailure() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

#endif /* TCPIP_SUPPORT_NDP_DAD */

#if (TCPIP_SUPPORT_IPV6_ETHIF_ADDR_FILTER_API == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VJoinMulticastGroup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_VJoinMulticastGroup(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) MulticastAddrPtr,
  boolean                                           Join)
{
  Std_ReturnType Result;

#if (TCPIP_SUPPORT_IPV6_ETHIF_ADDR_FILTER_API == STD_ON)
  Eth_PhysAddrType PhysMulticastAddr;
#endif

  TCPIP_ASSERT(NULL_PTR != MulticastAddrPtr);

#if defined(IPV6_JOIN_MULTICAST_GROUP_CALLOUT)
  IPV6_JOIN_MULTICAST_GROUP_CALLOUT(IpCtrlIdx, MulticastAddrPtr, Join);
#endif

#if (TCPIP_SUPPORT_IPV6_ETHIF_ADDR_FILTER_API == STD_ON)
  IpV6_VMulticastAddr2LinkLayerAddr(&PhysMulticastAddr[0], MulticastAddrPtr);

  /* #10 Check whether to join or leave multicast group and update physical address filter accordingly
   *     Joining a multicast group will enable all packets sent to with the multicast address to be recieved
   *     by the controller */
  if (TRUE == Join)
  {
    Result = TCPIP_LL_UpdatePhysAddrFilter(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx),
                                            &PhysMulticastAddr[0], ETH_ADD_TO_FILTER);
  }
  else
  {
    Result = TCPIP_LL_UpdatePhysAddrFilter(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx),
                                        &PhysMulticastAddr[0], ETH_REMOVE_FROM_FILTER);
  }
#endif

  return Result;
} /* End of IpV6_VJoinMulticastGroup() */


/**********************************************************************************************************************
 *  IpV6_VJoinSolicitedNodeMulticastGroup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VJoinSolicitedNodeMulticastGroup(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) UnicastAddrPtr,
  boolean                                           Join)
{
  IpV6_AddrType UnicastAddrSolicitedNodeAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

  /* #10 Obtain the solicited node multicast address and join the multicast group */
  IpV6_VGetSolicitedNodeAddr(&UnicastAddrSolicitedNodeAddr, UnicastAddrPtr, IPV6_MULTICAST_SCOPE_LINK_LOCAL);

  (void)IpV6_VJoinMulticastGroup(IpCtrlIdx, &UnicastAddrSolicitedNodeAddr, Join);

} /* End of IpV6_VJoinSolicitedNodeMulticastGroup() */
#endif

/**********************************************************************************************************************
 *  IpV6_VGetRandomValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint32, IPV6_CODE) IpV6_VGetRandomValue(
  uint32 MinValue,
  uint32 MaxValue)
{
  uint32 ValueRange;
  uint32 RndValue;

  ValueRange = (MaxValue + 1u) - MinValue;

  /* #10 Generate and return random unsigned 32 bit int value within specified range */
  if (ValueRange <= 0xFFFFU)
  {
    /* 16bit random number [0..0xFFFF] is sufficient */
    RndValue = (uint32) TcpIp_GetRandomNumber();
  }
  else
  {
    /* create 32bit random number [0..0xFFFFFFFF] by combining two 16bit random numbers */
    RndValue = ((uint32) TcpIp_GetRandomNumber() << 8) | (uint32) TcpIp_GetRandomNumber();
  }

  return MinValue + (RndValue % ValueRange);

} /* End of IpV6_VGetRandomValue() */


/**********************************************************************************************************************
 *  IpV6_VRandomizeValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint32, IPV6_CODE) IpV6_VRandomizeValue(
  TcpIp_IpV6CtrlIterType  IpCtrlIdx,
  uint32                  BaseValue)
{
  uint32 MinValue;
  uint32 MaxValue;
  TcpIp_SizeOfNdpConfigType ndpConfigIdx;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  /* #10 Generate a randomized unsigned 32-bit int from a base value */
  ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(ndpConfigIdx < TcpIp_GetSizeOfNdpConfig());

  MinValue = (BaseValue * TcpIp_GetMinRandomFactorOfNdpConfig(ndpConfigIdx)) / 10U;
  MaxValue = (BaseValue * TcpIp_GetMaxRandomFactorOfNdpConfig(ndpConfigIdx)) / 10U;

  return IpV6_VGetRandomValue(MinValue, MaxValue);

} /* End of IpV6_VRandomizeValue() */

/* RX HEADER PROCESSING FUNCTIONS */
#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VSegmentListInsert()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSegmentListInsert(
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType RaBufferDescIdx,
  uint8                                          SegInsertIdx)
{
  Std_ReturnType retVal;
  TcpIp_SizeOfIpV6ReassemblySegmentType segEndIdx =
    TcpIp_GetIpV6ReassemblySegmentEndIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx);

  TcpIp_SizeOfIpV6ReassemblySegmentType segEndActiveIdx =
    TcpIp_GetIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx).IpV6ReassemblySegmentActiveEndIdx;

  TCPIP_ASSERT(RaBufferDescIdx < TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor());
  TCPIP_ASSERT(TcpIp_GetIpV6ReassemblySegmentStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx) <= segEndActiveIdx);
  TCPIP_ASSERT(segEndActiveIdx <= segEndIdx);
  TCPIP_ASSERT(SegInsertIdx    <  segEndIdx);
  TCPIP_ASSERT(SegInsertIdx    <= segEndActiveIdx);

  /* #10 Check if there is space to insert a new element */
  if (segEndActiveIdx < segEndIdx)
  {
    TcpIp_SizeOfIpV6ReassemblySegmentType segIdx;

    /* #20 Copy all segments after insert position to the right to create space for new element */
    for (segIdx = segEndActiveIdx; segIdx > SegInsertIdx; segIdx--)
    {
      IpV6_SegmentType reassSeg;
      reassSeg.StartOfs = (TcpIp_GetIpV6ReassemblySegment(segIdx - 1u)).StartOfs;
      reassSeg.EndOfs = (TcpIp_GetIpV6ReassemblySegment(segIdx - 1u)).EndOfs;
      TcpIp_SetIpV6ReassemblySegment(segIdx, reassSeg);
    }

    TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx)->IpV6ReassemblySegmentActiveEndIdx += 1u;
    retVal = E_OK;
  }
  else
  {
    /* list full */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* End of IpV6_VSegmentListInsert() */

/**********************************************************************************************************************
 *  IpV6_VSegmentListRemove()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VSegmentListRemove(
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx,
  uint8                                           SegRemoveIdx)
{
  TcpIp_SizeOfIpV6ReassemblySegmentType segEndActiveIdx =
    TcpIp_GetIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx).IpV6ReassemblySegmentActiveEndIdx;
  TcpIp_SizeOfIpV6ReassemblySegmentType segIdx;

  TCPIP_ASSERT(RaBufferDescIdx < TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor());
  TCPIP_ASSERT_MSG(TcpIp_GetIpV6ReassemblySegmentStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx) <  segEndActiveIdx, "List must contain at least on element.");

  TCPIP_ASSERT(segEndActiveIdx <= TcpIp_GetIpV6ReassemblySegmentEndIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx));

  TCPIP_ASSERT(SegRemoveIdx < segEndActiveIdx);

  /* #10 Shift segments after the delete position to the left to remove the element */
  for (segIdx = SegRemoveIdx + 1u; segIdx < segEndActiveIdx; segIdx++)
  {
    IpV6_SegmentType reassSeg;
    reassSeg.StartOfs = (TcpIp_GetIpV6ReassemblySegment(segIdx)).StartOfs;
    reassSeg.EndOfs = (TcpIp_GetIpV6ReassemblySegment(segIdx)).EndOfs;
    TcpIp_SetIpV6ReassemblySegment(segIdx - 1u, reassSeg);
  }

  TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx)->IpV6ReassemblySegmentActiveEndIdx -= 1u;
} /* End of IpV6_VSegmentListRemove() */


/**********************************************************************************************************************
 *  IpV6_VSegmentListAdd()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VSegmentListAdd(
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx,
  uint16                                          SegOfs,
  uint16                                          SegLen)
{
  TcpIp_SizeOfIpV6ReassemblySegmentType segIdx;
  uint16 segEndOfs;
  Std_ReturnType Result = E_OK;

  TcpIp_SizeOfIpV6ReassemblySegmentType segStartIdx =
    TcpIp_GetIpV6ReassemblySegmentStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx);

  TcpIp_SizeOfIpV6ReassemblySegmentType segEndActiveIdx =
    TcpIp_GetIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx).IpV6ReassemblySegmentActiveEndIdx;

  TCPIP_ASSERT(RaBufferDescIdx <  TcpIp_GetSizeOfIpV6ReassemblyBufferDescriptor());
  TCPIP_ASSERT(segStartIdx <= segEndActiveIdx);
  TCPIP_ASSERT(segEndActiveIdx <= TcpIp_GetIpV6ReassemblySegmentEndIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx));

  segEndOfs = SegOfs + SegLen;

  /* #10 Locate insert position */
  for (segIdx = segStartIdx; segIdx < segEndActiveIdx; segIdx++)
  {
    if (TcpIp_GetIpV6ReassemblySegment(segIdx).StartOfs >= segEndOfs)
    {
      break;
    }
  }

  /* #20 Check if there is enough space to insert the element in the insert position */
  if (   (segIdx > segStartIdx)
      && (SegOfs < TcpIp_GetIpV6ReassemblySegment(segIdx - 1u).EndOfs))
  {
    /* segment overlaps with previous segment */
    Result = E_NOT_OK;
  }
  else if (   (segIdx < segEndActiveIdx)
           && (segEndOfs > TcpIp_GetIpV6ReassemblySegment(segIdx).StartOfs))
  {
    /* segment overlaps with next segment */
    Result = E_NOT_OK;
  }
  /* #30 Insert the element into the list and update the start and end offsets of the appropriate reassembly segment */
  else if (   (segIdx > segStartIdx)
           && (SegOfs == TcpIp_GetIpV6ReassemblySegment(segIdx - 1u).EndOfs))
  {
    /* new segment can be appended to previous segment */
    /* ----|#PREV#|*NEW*|----|#NEXT#|---- */
    (TcpIp_GetAddrIpV6ReassemblySegment(segIdx - 1u))->EndOfs += SegLen;

    if (   (segIdx < segEndActiveIdx)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && ((TcpIp_GetAddrIpV6ReassemblySegment(segIdx - 1u))->EndOfs == TcpIp_GetIpV6ReassemblySegment(segIdx).StartOfs))
    {
      /* new segment fits exactly between previous and next segment */
      /* ----|#PREV#|***NEW***|#NEXT#|---- */
      (TcpIp_GetAddrIpV6ReassemblySegment(segIdx - 1u))->EndOfs = TcpIp_GetAddrIpV6ReassemblySegment(segIdx)->EndOfs;

      IpV6_VSegmentListRemove(RaBufferDescIdx, segIdx);
    }
  }
  else if (   (segIdx < segEndActiveIdx)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           && (segEndOfs == TcpIp_GetAddrIpV6ReassemblySegment(segIdx)->StartOfs))
  {
    /* new segment can be prepended to next segment */
    /* ----|#PREV#|----|*NEW*|#NEXT#|---- */
    TcpIp_GetAddrIpV6ReassemblySegment(segIdx)->StartOfs = SegOfs;
  }
  else if (E_OK == IpV6_VSegmentListInsert(RaBufferDescIdx, segIdx))
  {
    /* new segment is isolated */
    /* ----|?PREV?|--|*NEW*|--|?NEXT?|---- */
    TcpIp_GetAddrIpV6ReassemblySegment(segIdx)->StartOfs = SegOfs;
    TcpIp_GetAddrIpV6ReassemblySegment(segIdx)->EndOfs   = segEndOfs;
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of IpV6_VSegmentListAdd() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  IpV6_VGetReassemblyBufferIdx()
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
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VGetReassemblyBufferIdx(
  TcpIp_SizeOfLocalAddrV6Type                               LocalAddrV6Idx,
  TCPIP_P2C(IpV6_AddrType)                                  SrcAddrPtr,
  uint32                                                    FragmentId,
  TCPIP_P2V(TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType) RaBufferDescIdxPtr)
{
  Std_ReturnType result = E_NOT_OK;
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType raBufferDescUnusedIdx = IPV6_INV_LIST_IDX;
  TcpIp_SizeOfIpV6CtrlType    ipCtrlIdx;
  TcpIp_SizeOfIpV6FragmentationConfigType ipV6FragConfigIdx;
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType raBufDescIdx;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  TCPIP_ASSERT(ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());


  ipV6FragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(ipCtrlIdx);

  TCPIP_ASSERT(ipV6FragConfigIdx < TcpIp_GetSizeOfIpV6FragmentationConfig());

  /* #10 Traverse through the reassembly buffer descriptor list */
  for (raBufDescIdx = TcpIp_GetIpV6ReassemblyBufferDescriptorStartIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       raBufDescIdx < TcpIp_GetIpV6ReassemblyBufferDescriptorEndIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       raBufDescIdx++)
  {
    /* #20 If the buffer descriptor is used, check if it matches the requesting fragment parameters and
     *     return descriptor index if match is found. */
    if (TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(raBufDescIdx)->Status != IPV6_FRAG_STATUS_UNUSED)
    {
      if (   (FragmentId == TcpIp_GetIpV6ReassemblyBufferDescriptorDyn(raBufDescIdx).FragmentId)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (IPV6_ADDR_EQUALS(*SrcAddrPtr, TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(raBufDescIdx)->SrcAddr))
          && (TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(raBufDescIdx)->IpAddrIdx == LocalAddrV6Idx))
      {
        /* match found. */
        (*RaBufferDescIdxPtr) = raBufDescIdx;
        result = E_OK;
        break;
      }
    }
    /* #30 Keep track of unused buffer descriptors */
    else if (raBufferDescUnusedIdx == IPV6_INV_LIST_IDX)
    {
      /* store index of free buffer in case we need one */
      raBufferDescUnusedIdx = raBufDescIdx;
    }
    else
    {
      /* buffer in use for other fragments */
    }
  }

  /* #40 If no matching descriptor has been found, update unused descriptor with
   * requesting fragment parameters */
  if (   (result == E_NOT_OK)
      && (raBufferDescUnusedIdx != IPV6_INV_LIST_IDX))
  {
    TCPIP_P2V(IpV6_ReassemblyBufferDescType) raBufDescPtr =
      TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(raBufferDescUnusedIdx);

    raBufDescPtr->Status            = IPV6_FRAG_STATUS_ACTIVE;
    raBufDescPtr->FragmentId        = FragmentId;
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(raBufDescPtr->SrcAddr, *SrcAddrPtr);
    raBufDescPtr->IpAddrIdx         = LocalAddrV6Idx;
    raBufDescPtr->IpV6ReassemblySegmentActiveEndIdx =
      TcpIp_GetIpV6ReassemblySegmentStartIdxOfIpV6ReassemblyBufferDescriptor(raBufferDescUnusedIdx);
    raBufDescPtr->FirstFragHdrOfs   = 0;
    raBufDescPtr->FirstFragPktLen   = 0;
    raBufDescPtr->OrigPktPayloadLen = 0;
    raBufDescPtr->FirstReceived     = FALSE;
    raBufDescPtr->LastReceived      = FALSE;
    IPV6_SET_EVENT_TIME_MS(raBufDescPtr->ReassemblyTimeout,
        TcpIp_GetReassemblyTimeoutOfIpV6FragmentationConfig(ipV6FragConfigIdx));
    (*RaBufferDescIdxPtr) = raBufferDescUnusedIdx;
    result = E_OK;
  }

  return result;
} /* End of IpV6_VGetReassemblyBufferIdx() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif


#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VGetFragmentTxBufferIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VGetFragmentTxBufferIdx(
  TcpIp_SizeOfIpV6CtrlType                                  IpCtrlIdx,
  TCPIP_P2V(TcpIp_SizeOfIpV6FragmentTxBufferDescriptorType) FragTxBufDescIdxPtr)
{
  Std_ReturnType result = E_NOT_OK;
  TcpIp_SizeOfIpV6FragmentTxBufferDescriptorType fragTxBufDescIdx;
  TcpIp_SizeOfIpV6FragmentationConfigType ipV6FragConfigIdx;

  ipV6FragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(ipV6FragConfigIdx < TcpIp_GetSizeOfIpV6FragmentationConfig());

  /* #10 Traverse through the fragment tx buffer descriptor list and return unused descriptor */
  for (fragTxBufDescIdx = TcpIp_GetIpV6FragmentTxBufferDescriptorStartIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       fragTxBufDescIdx < TcpIp_GetIpV6FragmentTxBufferDescriptorEndIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       fragTxBufDescIdx++)
  {
    if (TcpIp_GetAddrIpV6FragmentTxBufferDescriptorDyn(fragTxBufDescIdx)->Status == IPV6_FRAG_TX_STATUS_UNUSED)
    {
      TcpIp_GetAddrIpV6FragmentTxBufferDescriptorDyn(fragTxBufDescIdx)->Status = IPV6_FRAG_TX_STATUS_PROVIDED;
      *FragTxBufDescIdxPtr = fragTxBufDescIdx;
      result = E_OK;
      break;
    }
  }

  return result;
} /* End of IpV6_VGetFragmentTxBufferIdx() */
#endif

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VFragLenValidate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VFragLenValidate(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      DataLen,
  uint16                      FragHdrOfs)
{
  boolean lastFrag; /* M(ore) bit is not set */
  Std_ReturnType Result = E_OK;

  /* #10 Discard packet if fragment header length exceeds remaining payload length */
  if ((FragHdrOfs + IPV6_FRAGMENT_EXT_HDR_LEN) > DataLen)
  {
    IPV6_DBG_COUNTER_RX_INC(DropInvNxtHdrLen);
    Result = E_NOT_OK;
  }
  else
  {
    lastFrag = (boolean)(0u == (DataPtr[FragHdrOfs + 3u] & 1u)); /* M(ore) bit is not set */  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

    if (FALSE == lastFrag)
    {
      /* #20 Discard fragment packet if the M-bit in the fragment header is set and the
       * payload of the packet is not a multiple of 8 octets and send icmpv6 parameter
       * message with problem code 0 */
      if (0u != (DataLen & IPV6_MASK_MOD_8)) /* Payload not a multiple of 8 */
      {
        /* Send ICMP Parameter Problem Code 0 according to [RFC2460 4.5.] */
  #if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
        IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_ERR_HDR_FIELD, DataPtr, DataLen, IPV6_HEADER_PLD_LEN_FIELD_OFFS);
  #endif
        Result = E_NOT_OK;
      }
    }
  }
  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VRaBuffDescValidate()
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
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VRaBuffDescValidate(
 TcpIp_SizeOfIpV6FragmentationConfigType        IpV6FragConfigIdx,
 TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType RaBufferDescIdx,
 uint16                                         FragHdrOfs,
 uint16                                         FragLen,
 uint16                                         FragOfs)
{
  Std_ReturnType Result;
  TCPIP_P2V(IpV6_ReassemblyBufferDescType) raBufferDescPtr =
    TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx);

  /* #10 Validate that the reassembly buffer descriptor can be used for reassembly of the fragment */
  if (raBufferDescPtr->Status != IPV6_FRAG_STATUS_ACTIVE)
  {
    /* #20 If Buffer state indicates error or already completed assembly. Ignore this fragment */
    Result = E_NOT_OK;
  }
  else if (TcpIp_GetReassemblyBufferSizeOfIpV6FragmentationConfig(IpV6FragConfigIdx) < (FragHdrOfs + FragOfs + FragLen))
  {
    /* #30 If reassembled packet is too large for reassembly buffer, packet cannot be received, ignore all fragments */
    raBufferDescPtr->Status = IPV6_FRAG_STATUS_TOO_BIG;
    Result = E_NOT_OK;
  }
  else if (raBufferDescPtr->IpV6ReassemblySegmentActiveEndIdx == TcpIp_GetIpV6ReassemblySegmentStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx))
  {
    /* #40 first received fragment. This may not be the first fragment (FragOfs == 0)!
     * the length of the unfragmentable part in each fragment should be equal */
    raBufferDescPtr->FirstFragHdrOfs = FragHdrOfs;
    Result = E_OK;
  }
  else if (   (0u == FragOfs)
           && (raBufferDescPtr->FirstFragHdrOfs != FragHdrOfs))
  {
    /* #50 length of unfragmentable part has changed between first received and first (FragOfs == 0) fragment!
     * We would have to move the entire reassembly buffer content in order to adjust the offset in the original packet.
     * This is not supported. */
    raBufferDescPtr->Status = IPV6_FRAG_STATUS_INV_UNFRAG_LEN;
    Result = E_NOT_OK;
  }
  else
  {
    /* #60 length of unfragmentable part in received fragments may change as long as the unfragmentable parts
      * of the first received and the first fragment (FrgOfs == 0) have equal lengths.
      * According to [RFC2460 4.5 Fragment Header] this is should not occur but is not considered as an error. */
    Result = E_OK;
  }
  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VProcessFirstFragment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessFirstFragment(
 TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType  RaBufferDescIdx,
 uint16                                          FragHdrOfs,
 uint16                                          PrevHdrOfs,
 IPV6_P2C(uint8)                                 DataPtr,
 uint16                                          DataLen)
{
  Std_ReturnType Result = E_OK;
  TCPIP_P2V(IpV6_ReassemblyBufferDescType) raBufferDescPtr =
    TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx);

  TcpIp_IpV6ReassemblyDataBufferStartIdxOfIpV6ReassemblyBufferDescriptorType raBufferStartIdx =
      TcpIp_GetIpV6ReassemblyDataBufferStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx);

  uint8 FragExtNextHdr = TCPIP_GET_UINT8(DataPtr, FragHdrOfs);

  /* this is the first fragment */
  raBufferDescPtr->FirstReceived = TRUE;
  raBufferDescPtr->FirstFragPktLen = DataLen;

  /* #10 Copy unfragmentable part (all headers before fragment header) of the first fragment into reassembly buffer
   *     and add to to the begining of the segment reassembly list */
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IpV6_MemCpy(TcpIp_GetAddrIpV6ReassemblyDataBuffer(raBufferStartIdx), &DataPtr[0], FragHdrOfs);

  /* add unfragmentable part to segment list */
  if (E_OK != IpV6_VSegmentListAdd(RaBufferDescIdx, 0, FragHdrOfs))
  {
    /* Too much out-of-order segements received. Check for overlapping fragments according to [RFC5722] not possible.
     * Discard all fragments.
     */
    raBufferDescPtr->Status = IPV6_FRAG_STATUS_SEGM_ERROR;
    Result = E_NOT_OK;
  }
  else
  {
    /* #20 Set next header value of the last header in unfragmentable part to the header
     *     value of the header following the fragment header */
    if (0u == PrevHdrOfs)
    {
      /* there are no extension headers between IPv6 header and fragment header.
        * Set next header value in IPv6 header to the value of the header following the fragment header. */

      TcpIp_SetIpV6ReassemblyDataBuffer(raBufferStartIdx + IPV6_HEADER_NXT_HDR_FIELD_OFFS, FragExtNextHdr);
      raBufferDescPtr->NextHdrFieldOfs = IPV6_HEADER_NXT_HDR_FIELD_OFFS;
    }
    else
    {
      /* there is at least one extension header between the IPv6 header and the fragment header */
      /* set next header value in the extension header before the fragment header to the
       * next header value of the header following the fragment header
       */
      TcpIp_SetIpV6ReassemblyDataBuffer(raBufferStartIdx + PrevHdrOfs, FragExtNextHdr);
      raBufferDescPtr->NextHdrFieldOfs = PrevHdrOfs;
    }

    /* add length of headers between IPv6 and fragment extension header (unfragmentable part) */
    raBufferDescPtr->OrigPktPayloadLen += (FragHdrOfs - IPV6_HDR_LEN);
  }

  return Result;
} /* IpV6_Ip_VProcessFirstFragment() */

/**********************************************************************************************************************
 *  IpV6_Ip_VProcessValidFragment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessValidFragment(
 TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType RaBufferDescIdx,
 uint16                                         FragHdrOfs,
 IPV6_P2C(uint8)                                DataPtr,
 uint16                                         DataLen,
 uint16                                         PrevHdrOfs)
{
  Std_ReturnType result = E_OK;
  TCPIP_P2V(IpV6_ReassemblyBufferDescType) raBufferDescPtr =
    TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx);

  TcpIp_IpV6ReassemblyDataBufferStartIdxOfIpV6ReassemblyBufferDescriptorType raBufferStartIdx =
    TcpIp_GetIpV6ReassemblyDataBufferStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx);

  boolean LastFrag = (boolean)(0u == (DataPtr[FragHdrOfs + 3u] & 0x01u)); /* M(ore) bit is not set */  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  uint16 fragmentOffsetNbo = TCPIP_GET_UINT16_RAW(DataPtr, FragHdrOfs + IPV6_FRAG_EXT_HDR_OFF_FRAGOFFNBO);

  uint16 FragOfs;
  uint16 FragPayloadOfs;
  uint16 FragLen;

  FragOfs = (uint16)(TCPIP_NTOHS(fragmentOffsetNbo) & 0xFFF8U); /* fragment offset in bytes (original packet) */
  FragPayloadOfs = (FragHdrOfs + IPV6_FRAGMENT_EXT_HDR_LEN);   /* offset of fragment payload (in current packet) */
  FragLen = (DataLen - FragPayloadOfs);                        /* length of fragment */

  /* #10 Process the first fragment when recieved */
  if (   (0u == FragOfs) /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (E_NOT_OK == IpV6_Ip_VProcessFirstFragment(RaBufferDescIdx, FragHdrOfs, PrevHdrOfs, DataPtr, DataLen)))
  {
    result = E_NOT_OK;
  }
  /* #20 Add all subsequent fragments into the segment reassembly list */
  else
  {
    /* copy fragment payload into reassembly buffer */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpV6_MemCpy(TcpIp_GetAddrIpV6ReassemblyDataBuffer(raBufferStartIdx + raBufferDescPtr->FirstFragHdrOfs + FragOfs), &DataPtr[FragPayloadOfs], FragLen);

    if (E_OK != IpV6_VSegmentListAdd(RaBufferDescIdx, raBufferDescPtr->FirstFragHdrOfs + FragOfs, FragLen))
    {
      raBufferDescPtr->Status = IPV6_FRAG_STATUS_SEGM_ERROR;
      result = E_NOT_OK;
    }
    else
    {
      if (TRUE == LastFrag)
      {
        /* this is the last fragment */
        raBufferDescPtr->LastReceived = TRUE;

        /* add length of fragmentable part */
        raBufferDescPtr->OrigPktPayloadLen += (FragOfs + FragLen);
      }

      if (   (TRUE == raBufferDescPtr->FirstReceived)
          && (TRUE == raBufferDescPtr->LastReceived))
      {
        TcpIp_SizeOfIpV6ReassemblySegmentType raSegStartIdx =
          TcpIp_GetIpV6ReassemblySegmentStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx);
        /* #30 Once first and last fragments recieved, check if all intermediate packets have
         * been recieved, and then update reassembly status as COMPLETE */
        if (   ((raSegStartIdx + 1u) == raBufferDescPtr->IpV6ReassemblySegmentActiveEndIdx)
            && (TcpIp_GetIpV6ReassemblySegment(raSegStartIdx).StartOfs == 0u))
        {
          /* reassembly of packet complete. Reassembled packet will be processed within next main function */
          raBufferDescPtr->Status = IPV6_FRAG_STATUS_COMPLETE;
        }
      }
    }
  }

  return result;
} /* IpV6_Ip_VProcessValidFragment() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_VProcessFragmentHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_VProcessFragmentHeader(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      DataLen,
  uint16                      FragHdrOfs,
  uint16                      PrevHdrOfs)
{
  Std_ReturnType                          result;
  TcpIp_SizeOfIpV6CtrlType                ipCtrlIdx;
  uint16                                  FragOfs;
  uint16                                  FragPayloadOfs;
  uint16                                  FragLen;
  uint32                                  FragId;
  TcpIp_SizeOfIpV6FragmentationConfigType fragConfigIdx;
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType raBufferDescIdx;
  uint32 fragIdNbo;
  uint16 fragmentOffsetNbo;
  uint8  fragExtNextHdr;
  IpV6_AddrType srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(DataPtr != NULL_PTR);
  TCPIP_ASSERT(0u < DataLen);
  TCPIP_ASSERT(FragHdrOfs < DataLen);

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  TCPIP_ASSERT(ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_OFF)
  IPV6_UNUSED_PARAMETER(PrevHdrOfs);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
  fragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(ipCtrlIdx);

  /*                                               |FragPayloadOfs
   *                                               | _________________________________________fragmentable_part_..
   *                                                /
   *    unfragmentable_part   IPV6_FRAGMENT_EXT_HDR_LEN                      FragmentLen
   *   __/\_____________________   ______/\_______   _____________________________/\____________________________
   *  /                         \ /               \ /                                                           \
   * +-------------+- - - - - - -+-----------------+- - - - - - -+--------------------+---------------------- - -+
   * | IPv6 Header | ext headers | fragment header | ext headers | UL protocol header | UL payload               |
   * +-------------+- - - - - - -+-----------------+- - - - - - -+--------------------+---------------------- - -+
   *                \____________________________________________  _____________________________________________/
   *                             |                               \/
   *                             |FragHdrOfs                IPv6 payload
   *  \_______________________________________________  ________________________________________________________/
   *                                                  \/
   *                                                DataLen
   */
  fragExtNextHdr = TCPIP_GET_UINT8(DataPtr, FragHdrOfs);
  fragIdNbo = TCPIP_GET_UINT32(DataPtr, FragHdrOfs + IPV6_FRAG_EXT_HDR_OFF_IDNBO);
  fragmentOffsetNbo = TCPIP_GET_UINT16_RAW(DataPtr, FragHdrOfs + IPV6_FRAG_EXT_HDR_OFF_FRAGOFFNBO);

  srcAddr.addr32[0] = TCPIP_GET_UINT32(DataPtr, IPV6_HDR_OFF_SRCADDR);
  srcAddr.addr32[1] = TCPIP_GET_UINT32(DataPtr, IPV6_HDR_OFF_SRCADDR + 4u);
  srcAddr.addr32[2] = TCPIP_GET_UINT32(DataPtr, IPV6_HDR_OFF_SRCADDR + 8u);
  srcAddr.addr32[3] = TCPIP_GET_UINT32(DataPtr, IPV6_HDR_OFF_SRCADDR + 12u);

  FragId = TCPIP_NTOHL(fragIdNbo);
  FragOfs = (uint16)(TCPIP_NTOHS(fragmentOffsetNbo) & 0xFFF8U); /* fragment offset in bytes (original packet) */
  FragPayloadOfs = (FragHdrOfs + IPV6_FRAGMENT_EXT_HDR_LEN); /* offset of fragment payload (in current packet) */
  FragLen = (DataLen - FragPayloadOfs);                      /* length of fragment */

  /* #10 Verify that the fragment length does not exceed 65,535 octets and
   * that the header following the fragment header is not an unrecognized header */
  if (0x0000FFFFU < ((uint32)FragHdrOfs + FragOfs + FragLen))
  {
#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
    IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_ERR_HDR_FIELD,
                DataPtr, DataLen, FragHdrOfs + IPV6_FRAGMENT_EXT_HDR_FIELD_POS_FRAGMENT_OFFSET);
#endif
    result = E_NOT_OK;
  }
  else if (IPV6_EXT_HDR_ID_HOP_BY_HOP == fragExtNextHdr)
  {
#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
    IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_UNKNOWN_NXT_HDR,
                      DataPtr, DataLen, FragHdrOfs);
#endif

    IPV6_DBG_COUNTER_RX_INC(DropHdrOrder);
    result = E_NOT_OK;
  }
  /* #20 If fragment header is validated, request for reassembly buffer descriptor and
   * begin processing the fragments */
  else if (E_OK == IpV6_VGetReassemblyBufferIdx(LocalAddrV6Idx, &srcAddr, FragId, &raBufferDescIdx))
  {
    /* got index of fragment reassembly buffer */
    if (E_NOT_OK == IpV6_Ip_VRaBuffDescValidate(fragConfigIdx, raBufferDescIdx, FragHdrOfs, FragLen, FragOfs))
    {
      result = E_NOT_OK;
    }
    else if (E_NOT_OK == IpV6_Ip_VProcessValidFragment(raBufferDescIdx, FragHdrOfs, DataPtr, DataLen, PrevHdrOfs))
    {
      result = E_NOT_OK;
    }
    else
    {
      result = E_OK;
    }
  }
  else
  {
    /* all fragment reassembly buffers in use */
    /* packet cannot be received */
    result = E_NOT_OK;
  }

  return result;
#endif
} /* End of IpV6_VProcessFragmentHeader() */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV6_VFragReassemblyTimeExpired()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VFragReassemblyTimeExpired(
  TcpIp_IpV6CtrlIterType                         IpCtrlIdx,
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType RaBufferDescIdx
)
{
  TCPIP_P2C(IpV6_ReassemblyBufferDescType) raBufferDescPtr =
    TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(RaBufferDescIdx);

  TcpIp_SizeOfIpV6ReassemblyDataBufferType raDataBufStartIdx =
    TcpIp_GetIpV6ReassemblyDataBufferStartIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx);

  if ((TRUE == raBufferDescPtr->FirstReceived) &&
      (IPV6_FRAG_STATUS_ACTIVE == raBufferDescPtr->Status))
  {
    TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx;

    IPV6_P2V(uint8)                   OrigPktBufPtr;
    uint16                            OrigPktBufLen;
    IpV6_AddrType                     srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(srcAddr, (TcpIp_GetAddrIpV6ReassemblyDataBuffer(raDataBufStartIdx))[IPV6_HDR_OFF_SRCADDR]);

    OrigPktBufLen = (raBufferDescPtr->FirstFragPktLen);

    if (TCPIP_LOCAL_ADDR_V6_IDX_ANY == raBufferDescPtr->IpAddrIdx)
    {
      localAddrV6Idx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);
    }
    else
    {
      localAddrV6Idx = raBufferDescPtr->IpAddrIdx;
    }

    /* #10 Rebuild the first fragment packet into the icmpv6 buffer and send icmpv6 time exceeded message to sender */
    if (E_OK == IpV6_Icmp_VTxTimeExceeded(localAddrV6Idx, &srcAddr, IPV6_ICMP_MSG_TIME_EXCEEDED_CODE_TIME_EXCEEDED, &OrigPktBufPtr, &OrigPktBufLen, NULL_PTR, 0u))
    {
      uint16 OrigPktBufPos;

      /* copy original packet unfragmentable part into icmp tx buffer */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpV6_MemCpy(OrigPktBufPtr, TcpIp_GetAddrIpV6ReassemblyDataBuffer(raDataBufStartIdx), raBufferDescPtr->FirstFragHdrOfs);

      OrigPktBufPos = raBufferDescPtr->FirstFragHdrOfs;

      /* rebuild first segment by injecting fragment header between unfragmentable and fragmentable part */
      TCPIP_PUT_UINT16(OrigPktBufPtr, OrigPktBufPos, OrigPktBufPtr[raBufferDescPtr->NextHdrFieldOfs]);
      OrigPktBufPtr[OrigPktBufPos + IPV6_FRAG_EXT_HDR_OFF_RESERVED] = 0U;
      TCPIP_PUT_UINT16_RAW(OrigPktBufPtr, OrigPktBufPos + IPV6_FRAG_EXT_HDR_OFF_FRAGOFFNBO, 1U);
      TCPIP_PUT_UINT32_RAW(OrigPktBufPtr, OrigPktBufPos + IPV6_FRAG_EXT_HDR_OFF_IDNBO, raBufferDescPtr->FragmentId);

      OrigPktBufPos += (uint16) sizeof(IpV6_FragmentExtHdrType);
      OrigPktBufPtr[raBufferDescPtr->NextHdrFieldOfs] = IPV6_EXT_HDR_ID_FRAGMENT;

      /* copy original packet fragmentable part into icmp tx buffer */
      TCPIP_ASSERT((raDataBufStartIdx + raBufferDescPtr->FirstFragHdrOfs) < TcpIp_GetIpV6ReassemblyDataBufferEndIdxOfIpV6ReassemblyBufferDescriptor(RaBufferDescIdx));
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpV6_MemCpy(&OrigPktBufPtr[OrigPktBufPos], TcpIp_GetAddrIpV6ReassemblyDataBuffer(raDataBufStartIdx + raBufferDescPtr->FirstFragHdrOfs), ((uint32) OrigPktBufLen - (uint32) OrigPktBufPos));
    }
    else
    {
      /* cannot sent TimeExceeded message */
    }
  }
} /* IpV6_VFragReassemblyTimeExpired */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_VRxFragments()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VRxFragments(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfIpV6ReassemblyBufferDescriptorType raBufferDescIdx;
  TcpIp_SizeOfIpV6FragmentationConfigType ipV6FragConfigIdx;

  ipV6FragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(ipV6FragConfigIdx < TcpIp_GetSizeOfIpV6FragmentationConfig());

  /* #10 Traverse through the reassembly buffer descriptors */
  for (raBufferDescIdx = TcpIp_GetIpV6ReassemblyBufferDescriptorStartIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       raBufferDescIdx < TcpIp_GetIpV6ReassemblyBufferDescriptorEndIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       raBufferDescIdx++)
  {
    TCPIP_P2V(IpV6_ReassemblyBufferDescType) raBufferDescPtr =
      TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(raBufferDescIdx);

    TcpIp_SizeOfIpV6ReassemblyDataBufferType raDataBufStartIdx =
      TcpIp_GetIpV6ReassemblyDataBufferStartIdxOfIpV6ReassemblyBufferDescriptor(raBufferDescIdx);

    if (IPV6_FRAG_STATUS_UNUSED == raBufferDescPtr->Status)
    {
      /* skip */
    }
    /* #20 Invoke ipv6 rx indication routine for descriptors for which fragment reassembly has been completed */
    else if (IPV6_FRAG_STATUS_COMPLETE == raBufferDescPtr->Status)
    {
      /* fragment reassembly complete */

      /* update payload length field in IPv6 header of reassembled packet */
      TcpIp_SetIpV6ReassemblyDataBuffer(raDataBufStartIdx + 4u, (uint8)(raBufferDescPtr->OrigPktPayloadLen >> 8));
      TcpIp_SetIpV6ReassemblyDataBuffer(raDataBufStartIdx + 5u, (uint8)(raBufferDescPtr->OrigPktPayloadLen));

      /* call IpV6_RxIndication_Internal() with reassembled packet */
      IpV6_RxIndication_Internal(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), (uint8*)NULL_PTR, TcpIp_GetAddrIpV6ReassemblyDataBuffer(raDataBufStartIdx), IPV6_HDR_LEN + raBufferDescPtr->OrigPktPayloadLen, TRUE);

      raBufferDescPtr->Status = IPV6_FRAG_STATUS_UNUSED;
    }
    else if (IPV6_TIME_EXPIRED(raBufferDescPtr->ReassemblyTimeout) == TRUE)
    {
      /* fragment reassembly time expired */
      IpV6_VFragReassemblyTimeExpired(IpCtrlIdx, raBufferDescIdx);
      raBufferDescPtr->Status = IPV6_FRAG_STATUS_UNUSED;
    }
    else
    {
      /* fragment reassembly still in progress */
    }
  }
} /* End of IpV6_VRxFragments() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif

#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_VTxFragments()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VTxFragments(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfIpV6FragmentTxBufferDescriptorType ipV6FragTxBufferDescIdx;
  TcpIp_SizeOfIpV6FragmentationConfigType ipV6FragConfigIdx;

  ipV6FragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(ipV6FragConfigIdx < TcpIp_GetSizeOfIpV6FragmentationConfig());
  /* #10 Traverse through the fragment tx buffer descriptors */
  for (ipV6FragTxBufferDescIdx = TcpIp_GetIpV6FragmentTxBufferDescriptorStartIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       ipV6FragTxBufferDescIdx < TcpIp_GetIpV6FragmentTxBufferDescriptorEndIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
       ipV6FragTxBufferDescIdx++)
  {

    TCPIP_P2V(IpV6_FragmentTxBufferDescType) fragTxBufferDescPtr =
      TcpIp_GetAddrIpV6FragmentTxBufferDescriptorDyn(ipV6FragTxBufferDescIdx);

    TcpIp_SizeOfIpV6FragmentTxDataBufferType fragTxBufferStartIdx =
      TcpIp_GetIpV6FragmentTxDataBufferStartIdxOfIpV6FragmentTxBufferDescriptor(ipV6FragTxBufferDescIdx);

    uint8  EthBufIdx;
    IPV6_P2V(Eth_DataType) EthBufPtr;
    uint16 EthBufLen;
    uint16 FragLen;
    uint8 MoreDataBit = 0u;

    /* #20 If fragment is ready for transmission, request for eth buffer and transmit fragment */
    if (IPV6_FRAG_TX_STATUS_TRANSMIT == fragTxBufferDescPtr->Status)
    {
      IpV6_AddrType destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
      IpV6_AddrType srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
      uint8         *ipV6PacketHdr = TcpIp_GetAddrIpV6FragmentTxDataBuffer(fragTxBufferStartIdx);
      uint8         nextHdr = TCPIP_GET_UINT8(ipV6PacketHdr, IPV6_HDR_OFF_NEXTHDR);

      FragLen = (fragTxBufferDescPtr->FragPartLen - fragTxBufferDescPtr->TxOfs); /* remaining fragment length */

      /* Calculate and store Upper Layer protocol Checksum into the header */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(destAddr, ipV6PacketHdr[IPV6_HDR_OFF_DSTADDR]);
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(srcAddr, ipV6PacketHdr[IPV6_HDR_OFF_SRCADDR]);

      IpV6_Ip_VCalculateandStoreChecksum(nextHdr, &ipV6PacketHdr[IPV6_HDR_LEN], &destAddr, &srcAddr, FragLen);

      if (FragLen > fragTxBufferDescPtr->MaxFragLen)
      {
        /* remaining fragmnetable part does not fit into one fragment */
        FragLen = fragTxBufferDescPtr->MaxFragLen;
        FragLen -= (FragLen & IPV6_MASK_MOD_8);
        MoreDataBit = 1u;
      }

      EthBufLen = FragLen + IPV6_FRAGMENT_EXT_HDR_LEN + fragTxBufferDescPtr->UnfragPartLen;

      if (BUFREQ_OK == TCPIP_LL_ProvideTxBuffer(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), IPV6_ETHER_TYPE_ID, TcpIp_GetFramePrioDefaultOfIpV6Ctrl(IpCtrlIdx), &EthBufIdx, &EthBufPtr, &EthBufLen))
      {
        uint16 EthBufOfs;
        TCPIP_P2V(uint8) EthBufUint8Ptr = (TCPIP_P2V(uint8))EthBufPtr; /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_CastToUInt8 */

        /* copy unfragmentable part into tx buffer of fragment packet */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpV6_MemCpy(EthBufUint8Ptr, TcpIp_GetAddrIpV6FragmentTxDataBuffer(fragTxBufferStartIdx), fragTxBufferDescPtr->UnfragPartLen);
        EthBufOfs = fragTxBufferDescPtr->UnfragPartLen;

        EthBufUint8Ptr[IPV6_HDR_OFF_NEXTHDR] = IPV6_EXT_HDR_ID_FRAGMENT;

        /* add payload length to the ipv6 header */
        TCPIP_PUT_UINT16(EthBufUint8Ptr, IPV6_HDR_OFF_PAYLOADLENNBO, (fragTxBufferDescPtr->UnfragPartLen - IPV6_HDR_LEN) + IPV6_FRAGMENT_EXT_HDR_LEN + FragLen);

        /* add fragment header for fragment packet */
        TCPIP_PUT_UINT16(EthBufUint8Ptr, EthBufOfs + IPV6_FRAG_EXT_HDR_OFF_FRAGOFFNBO, (fragTxBufferDescPtr->TxOfs & (uint16)0xFFF8U) | (uint16)MoreDataBit);



        /* add fragment Id for fragment packet */
        TCPIP_PUT_UINT32(EthBufUint8Ptr, EthBufOfs + IPV6_FRAG_EXT_HDR_OFF_IDNBO, fragTxBufferDescPtr->FragmentId);

        EthBufUint8Ptr[EthBufOfs] = nextHdr;
        EthBufUint8Ptr[EthBufOfs + IPV6_FRAG_EXT_HDR_OFF_RESERVED] = 0u;

        EthBufOfs += IPV6_FRAGMENT_EXT_HDR_LEN;

        /* add fragment payload */
        TCPIP_ASSERT((fragTxBufferStartIdx + fragTxBufferDescPtr->UnfragPartLen + fragTxBufferDescPtr->TxOfs) < TcpIp_GetIpV6FragmentTxDataBufferEndIdxOfIpV6FragmentTxBufferDescriptor(ipV6FragTxBufferDescIdx));
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpV6_MemCpy(&EthBufUint8Ptr[EthBufOfs], TcpIp_GetAddrIpV6FragmentTxDataBuffer(fragTxBufferStartIdx + fragTxBufferDescPtr->UnfragPartLen + fragTxBufferDescPtr->TxOfs), FragLen);
        EthBufOfs += FragLen;

        if (E_OK == TCPIP_LL_Transmit(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), EthBufIdx, IPV6_ETHER_TYPE_ID, FALSE, EthBufOfs, &fragTxBufferDescPtr->NextHopPhysAddr[0]))
        {
          /* fragment successfully sent */
          fragTxBufferDescPtr->TxOfs += FragLen;

          if (fragTxBufferDescPtr->TxOfs >= fragTxBufferDescPtr->FragPartLen)
          {
            /* all fragments have been transmitted, mark packet buffer as free */
            fragTxBufferDescPtr->Status = IPV6_FRAG_TX_STATUS_UNUSED;
          }
        }
      }
    }
  }
} /* End of IpV6_VTxFragments() */ /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_TcpIp_STCAL_CslAccess */
#endif


#if ((TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON) || (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON))
/**********************************************************************************************************************
 *  IpV6_VInitFragments()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VInitFragments(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  if (TcpIp_IsIpV6FragmentationConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE)
  {
    TcpIp_SizeOfIpV6FragmentationConfigType ipV6FragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(IpCtrlIdx);

    /*#10 Initialise all fragment tx and reassembly buffer descriptors states to UNUSED */
# if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
    if (TcpIp_GetReassemblyBufferCountOfIpV6FragmentationConfig(ipV6FragConfigIdx) > 0u)
    {
      TcpIp_IpV6ReassemblyBufferDescriptorIterType raBufferDescIdx;

      for (raBufferDescIdx = TcpIp_GetIpV6ReassemblyBufferDescriptorStartIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
           raBufferDescIdx < TcpIp_GetIpV6ReassemblyBufferDescriptorEndIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
           raBufferDescIdx++)
      {
        TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(raBufferDescIdx)->Status = IPV6_FRAG_STATUS_UNUSED;
        TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(raBufferDescIdx)->IpV6ReassemblySegmentActiveEndIdx = TcpIp_GetIpV6ReassemblySegmentStartIdxOfIpV6ReassemblyBufferDescriptor(raBufferDescIdx);
      }
    }
# endif

# if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
    /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
    if (TcpIp_GetTxFragmentBufferCountOfIpV6FragmentationConfig(ipV6FragConfigIdx) > 0u)
    {
      TcpIp_SizeOfIpV6FragmentTxBufferDescriptorType fragTxBuffDescIdx;

      TcpIp_SetNextTxFragmentIdOfIpV6CtrlDyn(IpCtrlIdx, 0);

      for (fragTxBuffDescIdx = TcpIp_GetIpV6FragmentTxBufferDescriptorStartIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
           fragTxBuffDescIdx < TcpIp_GetIpV6FragmentTxBufferDescriptorEndIdxOfIpV6FragmentationConfig(ipV6FragConfigIdx);
           fragTxBuffDescIdx++)
      {
        TcpIp_GetAddrIpV6ReassemblyBufferDescriptorDyn(fragTxBuffDescIdx)->Status = IPV6_FRAG_TX_STATUS_UNUSED;
      }
    }
# endif
  }
} /* End of IpV6_VInitFragments() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif

#if (TCPIP_SUPPORT_IPV6_NVM_ADDR_STORAGE == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VNvmGetAddress
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VNvmGetAddress(
  TcpIp_IpV6SourceAddressTableEntryIterType  IpV6SrcAddrIdx,
  TCPIP_P2V(IpV6_AddrType)                   AddrPtr
)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfNvmDataType  nvmDataIdx;
  Std_ReturnType          retVal    = E_NOT_OK;
  uint8                   nvMStatus = NVM_REQ_PENDING;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_IsNvmDataUsedOfIpV6SourceAddress(IpV6SrcAddrIdx) == TRUE);

  nvmDataIdx = TcpIp_GetNvmDataIdxOfIpV6SourceAddress(IpV6SrcAddrIdx);

  /* #10 Update the error status of the TcpIps NvM block */
  (void)NvM_GetErrorStatus((NvM_BlockIdType) TCPIP_NVM_BLOCK_ID, &nvMStatus);

  /* #20 Check if the NvM operation was successfully completed */
  if(   (nvMStatus == NVM_REQ_OK)
     || (nvMStatus == NVM_REQ_RESTORED_FROM_ROM))
  {
    /* #30 If successful, copy the address from NvM to the pointer */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(*AddrPtr, (TcpIp_GetAddrNvmData(nvmDataIdx))[IPV6_SAT_ENTRY_OFF_ADDR]);

    /* #40 If the NvM block contains a valid unicast address and return E_OK */
    if (   (IPV6_ADDR_IS_EUI64(*AddrPtr))
        && (!IPV6_ADDR_IS_MULTICAST(*AddrPtr)))
    {
      retVal = E_OK;
    }
  }
  else
  {
    /* #50 If not successful, copy unspecified address and return E_NOT_OK */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(*AddrPtr, IpV6_AddrUnspecified);
  }

  return retVal;
} /* IpV6_Ip_VNvmGetAddress() */
#endif

/**********************************************************************************************************************
 *  IpV6_VConfigureSourceAddresses()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VConfigureSourceAddresses(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfIpV6SourceAddressTableEntryType ipV6SrcAddrIdx;

  /* #10 Traverse through all available source indexes and configure address for each index */
  for (ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
       ipV6SrcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
       ipV6SrcAddrIdx++)
  {
    TCPIP_P2C(IpV6_AddrType) addressPtr = NULL_PTR;

#if (TCPIP_SUPPORT_IPV6_NVM_ADDR_STORAGE == STD_ON)
    IpV6_AddrType NvmAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

    /* #20 If Nvm block is configured, try to obtain stored address */
    if (TcpIp_IsNvmDataUsedOfIpV6SourceAddress(ipV6SrcAddrIdx) == TRUE)
    {
      if (IpV6_Ip_VNvmGetAddress(ipV6SrcAddrIdx, &NvmAddr) == E_OK)
      {
        addressPtr = &NvmAddr;
      }
    }
#endif

    /* #30 If no stored address present, assign configured default addresses for the source index */
    if (   (addressPtr == NULL_PTR)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_IsDefaultAddrV6UsedOfIpV6SourceAddress(ipV6SrcAddrIdx) == TRUE))
    {
      /* no valid address found in the NvM. Check for configured default address */
      addressPtr = TcpIp_GetAddrDefaultAddrV6(TcpIp_GetDefaultAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx));
    }

    if (addressPtr != NULL_PTR)
    {
      /* Address has been found in the NvM or default address will be configured */
      if (E_NOT_OK == IpV6_Ndp_VAddSourceAddress(ipV6SrcAddrIdx, addressPtr, IPV6_LIFETIME_UNLIMITED,
                                                 IPV6_LIFETIME_UNLIMITED, 0, IPV6_SRC_ADDR_DAD_MODE_NONE))
      {
        IpV6_DetReportInternalError(IPV6_E_INV_ADDR_CONFIG);
      }

      /* #40 Select Default Router and create Entry */
      IpV6_SelectDefaultRouterConfigAndCreateEntry(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx), NULL_PTR);
    }
  }

} /* End of IpV6_VConfigureSourceAddresses() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_VConfigureDynamicMulticastAddresses()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VConfigureMulticastAddresses(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  /* #10 Check if any multicast address indexes are configured for the ip controller */
  if (   (TcpIp_GetIpV6MulticastAddrEndIdxOfIpV6Ctrl(IpCtrlIdx)   == TCPIP_NO_IPV6MULTICASTADDRENDIDXOFIPV6CTRL)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetIpV6MulticastAddrStartIdxOfIpV6Ctrl(IpCtrlIdx) == TCPIP_NO_IPV6MULTICASTADDRSTARTIDXOFIPV6CTRL))
  {
    /* do nothing */
  }
  else
  {
    TcpIp_SizeOfIpV6MulticastAddrType ipV6MulticastAddrIdx;
    /* #20 Traverse through list of dynamic multicast address indexes and configure addresses for each index */
    for (ipV6MulticastAddrIdx = TcpIp_GetIpV6MulticastAddrStartIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6MulticastAddrIdx < TcpIp_GetIpV6MulticastAddrEndIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6MulticastAddrIdx++)
    {
      TcpIp_SizeOfIpV6MulticastAddrActiveType mcAddrActiveIdx = TcpIp_GetIpV6MulticastAddrActiveIdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);

      /* #30 If default address has been configured, assign address and join multicast group for the address */
      if (TcpIp_IsDefaultAddrV6UsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE)
      {
        TCPIP_P2C(IpV6_AddrType) defaultAddrPtr =
          TcpIp_GetAddrDefaultAddrV6(TcpIp_GetDefaultAddrV6IdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx));

        /* Set dynamic multicast address to the default value */

        if (TcpIp_IsIpV6MulticastAddrActiveUsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE)
        {
          /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
          IPV6_ADDR_COPY(*TcpIp_GetAddrIpV6MulticastAddrActive(mcAddrActiveIdx), *defaultAddrPtr);
        }

        IPV6_VJOIN_MULTICAST_GROUP(IpCtrlIdx, defaultAddrPtr, TRUE);

        TcpIp_Cbk_VLocalIpAssignmentChg(
          TCPIP_IPV6_TO_LOCAL_ADDR_IDX(TcpIp_GetLocalAddrV6IdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx)),
          TCPIP_IPADDR_STATE_ASSIGNED);
      }
      /* #40 If no default address configured assign unspcified address to index */
      else
      {
        /* Dynamic address has no default value.
         * Set address to unspecified address in order to indicate that no address is assigned
         */
        TCPIP_ASSERT(TcpIp_IsIpV6MulticastAddrActiveUsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE);

        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(*TcpIp_GetAddrIpV6MulticastAddrActive(mcAddrActiveIdx), IpV6_AddrUnspecified);
      }
    }
  }
} /* End of IpV6_VConfigureDynamicMulticastAddresses() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_VCtrlStateStartup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VCtrlStateStartup(uint8 IpCtrlIdx)
{
  TcpIp_InterfaceIdentifierStartIdxOfIpV6CtrlType interfaceIdentifierStartIdx =
    TcpIp_GetInterfaceIdentifierStartIdxOfIpV6Ctrl(IpCtrlIdx);

  /* #10 Perform Ip controller state startup routine */
  /* set 64bit interface identifier, generated from local MAC address */
  IpV6_VGetInterfaceIdentifier(IpCtrlIdx, TcpIp_GetAddrInterfaceIdentifier(interfaceIdentifierStartIdx));

  IPV6_CHANGE_STATE(IpCtrlIdx, IPV6_CTRL_STATE_LINK_READY);

  IpV6_Ndp_VStart(IpCtrlIdx);

} /* End of IpV6_VCtrlStateStartup */


/**********************************************************************************************************************
 *  IpV6_VCtrlStateOnline()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VCtrlStateOnline(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  /* Link-local address is configured */

  TcpIp_Cbk_VLocalIpAssignmentChg(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(
    TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx)), TCPIP_IPADDR_STATE_ASSIGNED);

  /* #10 Setup all configured unicast and multicast addresses that have default values */
  IpV6_VConfigureSourceAddresses(IpCtrlIdx);
  IpV6_VConfigureMulticastAddresses(IpCtrlIdx);

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
  /* #20 Perform dhcpv6 address configuration if dhcp mode is automatic */
  if (TcpIp_GetDhcpModeOfIpV6Ctrl(IpCtrlIdx) == IPV6_DHCPV6_MODE_AUTOMATIC)
  {
    TcpIp_SizeOfIpV6SourceAddressType srcAddrIdxDhcp;

    TCPIP_ASSERT(TcpIp_IsIpV6SourceAddressDhcpUsedOfIpV6Ctrl(IpCtrlIdx));

    srcAddrIdxDhcp = TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx);

    if (TcpIp_GetIpV6SourceAddressTableEntry(srcAddrIdxDhcp).State == IPV6_LADDR_STATE_INVALID)
    {
      TcpIp_DhcpV6_StartAddressAssignment(IpCtrlIdx);
    }
  }
#endif

  /* notify EthSM that an IP address is available on controller */
  ETHSM_TCPIP_MODE_INDICATION(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), TRUE);
} /* End of IpV6_VCtrlStateOnline() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_VCtrlStateShutdown()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VCtrlStateShutdown(uint8 IpCtrlIdx)
{
  TcpIp_SizeOfIpV6SourceAddressTableEntryType srcAddrIdx;

  /* notify EthSM that no IP address is available on controller */
  ETHSM_TCPIP_MODE_INDICATION(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), FALSE);

  /* #10 Remove all source/unicast address assignments */
  IPV6_BEGIN_CRITICAL_SECTION_SAT();

  for (srcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx++)
  {
    if (IPV6_LADDR_STATE_INVALID != TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State)
    {
      IpV6_VHandleSourceAddrAssignmentChange(srcAddrIdx, FALSE);
    }
  }

  IPV6_END_CRITICAL_SECTION_SAT();

  /* block used for limitation of variable scope */
  {
    TcpIp_SizeOfIpV6MulticastAddrType ipV6MulticastAddrIdx;

    /* #20 Remove all dynamic multicast address assignments */
    for (ipV6MulticastAddrIdx = TcpIp_GetIpV6MulticastAddrStartIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6MulticastAddrIdx < TcpIp_GetIpV6MulticastAddrEndIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6MulticastAddrIdx++)
    {
      TCPIP_P2C(IpV6_AddrType) mcAddrPtr = NULL_PTR;

      if (TcpIp_IsIpV6MulticastAddrActiveUsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE)
      {
        TcpIp_SizeOfIpV6MulticastAddrActiveType mcAddrActiveIdx =
          TcpIp_GetIpV6MulticastAddrActiveIdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);

        /* check if dynamic multicast address is configured. The value may be [::] if no address is configured */
        if (IPV6_ADDR_IS_MULTICAST(*TcpIp_GetAddrIpV6MulticastAddrActive(mcAddrActiveIdx)))
        {
          mcAddrPtr = TcpIp_GetAddrIpV6MulticastAddrActive(mcAddrActiveIdx);
        }
      }
      else if (TcpIp_IsDefaultAddrV6UsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE)
      {
        TcpIp_SizeOfDefaultAddrV6Type defaultAddrIdx =
          TcpIp_GetDefaultAddrV6IdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);

        mcAddrPtr = TcpIp_GetAddrDefaultAddrV6(defaultAddrIdx);
      }
      else
      {
        TCPIP_ASSERT_UNREACHABLE_MSG("A multicast address must have a dynamic address or a default value");
      }

      if (mcAddrPtr != NULL_PTR)
      {
        IPV6_VJOIN_MULTICAST_GROUP(IpCtrlIdx, mcAddrPtr, FALSE);

        TcpIp_Cbk_VLocalIpAssignmentChg(
          TCPIP_IPV6_TO_LOCAL_ADDR_IDX(TcpIp_GetLocalAddrV6IdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx)),
          TCPIP_IPADDR_STATE_UNASSIGNED);
      }
    }

  }

  /* #30 Remove all-nodes multicast address assignment and leave all nodes multicast group */
  TcpIp_Cbk_VLocalIpAssignmentChg(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx)),
    TCPIP_IPADDR_STATE_UNASSIGNED);

  /* leave all-nodes multicast group */
  IPV6_VJOIN_MULTICAST_GROUP(IpCtrlIdx, &IpV6_AddrAllNodesLL, FALSE);

  IpV6_Icmp_Init(IpCtrlIdx);
  IpV6_Ndp_Init(IpCtrlIdx);

  IPV6_CHANGE_STATE(IpCtrlIdx, IPV6_CTRL_STATE_INIT);

  TcpIp_SetLastBcAddrPtrOfIpV6CtrlDyn(IpCtrlIdx, NULL_PTR);

} /* End of IpV6_VCtrlStateShutdown */  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/* TIMESTAMP FUNCTIONS */

/**********************************************************************************************************************
 *  IpV6_VSetEventTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VSetEventTime(
  P2VAR(IpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                            Milliseconds)
{
   /* #10 Configure the next event timestamp by adding value to the IpV6 time */
   *TimestampPtr = IpV6_Time;
   IpV6_VTimeAddMs(TimestampPtr, Milliseconds);
} /* End of IpV6_VSetEventTime() */

/**********************************************************************************************************************
 *  IpV6_VSetLifetimeS()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VSetLifetimeS(
  P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_VAR) TimestampPtr,
  uint32                                         LifetimeS,
  P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_VAR) NextEventTimePtr)
{
  /* #10 Calculate lifetime using time stamp and update time structure */
  if ((IPV6_LIFETIME_UNLIMITED - IpV6_Time.S) > LifetimeS)
  {
    TimestampPtr->S  = IpV6_Time.S + LifetimeS;
    TimestampPtr->Ms = IpV6_Time.Ms;
  }
  else
  {
    TimestampPtr->S  = IPV6_LIFETIME_UNLIMITED;
    TimestampPtr->Ms = 0;
  }

  if ((NULL_PTR != NextEventTimePtr) && (IPV6_TIME_IS_LOWER(*TimestampPtr, *NextEventTimePtr) == TRUE)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    *NextEventTimePtr = *TimestampPtr;
  }
} /* End of IpV6_VSetLifetimeS() */

/**********************************************************************************************************************
 *  IpV6_VUpdateDefaultLinkMtu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_VUpdateDefaultLinkMtu(
  TcpIp_IpV6CtrlIterType IpCtrlIdx,
  uint16                 Mtu)
{
  /* #10 Update default Link Mtu for destination cache entries */
  if ((IPV6_MINIMUM_MTU <= Mtu) && (TcpIp_GetDefaultLinkMtuOfIpV6Ctrl(IpCtrlIdx) >= Mtu)) /* PRQA S 3415 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* reconfigure MTU value [IPV6_MINIMUM_MTU...IPV6_LINK_MTU] (e.g. [1280...1500]) */
    TcpIp_SetDefaultLinkMtuOfIpV6CtrlDyn(IpCtrlIdx, Mtu);

# if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
    if (TcpIp_IsEnablePathMtuOfIpV6Ctrl(IpCtrlIdx) == TRUE)
    {
      TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;

      TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
      TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) < TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

      for (dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
           dcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
           dcEntryIdx++)
      {
        TCPIP_P2V(IpV6_DestinationCacheEntryType) dcEntryPtr = TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx);

        if (dcEntryPtr->Mtu > Mtu)
        {
          dcEntryPtr->Mtu = Mtu;
        }
      }
    }
# endif
  }
} /* End of IpV6_VUpdateDefaultLinkMtu() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  IpV6_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_InitMemory(void)
{
  /* #10 Initialize Ipv6 state */
  IpV6_State = IPV6_STATE_UNINIT;

  return;
} /* End of IpV6_InitMemory() */


/**********************************************************************************************************************
 *  IpV6_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Init(void)
{
  TcpIp_IpV6SocketDynIterType socketIdx;
  TcpIp_IpV6CtrlIterType    ipCtrlIdx;

  /* #10 Invoke init routines for all ip controllers */
  /* module initialisation */

  IPV6_TIME_SET(IpV6_Time, 0, 0u);


  for (socketIdx = 0; socketIdx < TcpIp_GetSizeOfIpV6SocketDyn(); socketIdx++)
  {
    IpV6_ResetSocket(socketIdx);
  }

  /* Invoke init routines for all ip controllers */
  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    TcpIp_SetCtrlPreviousStateOfIpV6CtrlDyn(ipCtrlIdx, IPV6_CTRL_STATE_UNINIT);
    TcpIp_SetCtrlStateOfIpV6CtrlDyn(ipCtrlIdx, IPV6_CTRL_STATE_INIT);

    TcpIp_SetLastBcAddrPtrOfIpV6CtrlDyn(ipCtrlIdx, NULL_PTR);

    IpV6_Icmp_Init(ipCtrlIdx);
    IpV6_Ndp_Init(ipCtrlIdx);

#if ((TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON) || (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON))
    if (TcpIp_IsIpV6FragmentationConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      IpV6_VInitFragments(ipCtrlIdx);
    }
#endif

#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
    TcpIp_SetIcmpNextHopLLAddrOverrideOfIpV6CtrlDyn(ipCtrlIdx, FALSE);
#endif

  }

  IpV6_State = IPV6_STATE_INIT;

  /* Initialize the DHCPv6 client submodule, if configured. */
#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
  TcpIp_DhcpV6_Init(NULL_PTR);
#endif

} /* End of IpV6_Init() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_MainFunctionRx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_MainFunctionRx(void)
{
#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
  TcpIp_IpV6CtrlIterType ipCtrlIdx;

  /* #10 Iterate over all configured IP instances. */
  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    /* #20 Try to reassemble received fragments and forward reassembled packets to upper layer. */
    if (TcpIp_IsIpV6FragmentationConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      IpV6_VRxFragments(ipCtrlIdx);
    }
  }
#endif
}  /* IpV6_MainFunctionRx() */

/**********************************************************************************************************************
 *  IpV6_MainFunctionTx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_MainFunctionTx(void)
{
#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
  TcpIp_IpV6CtrlIterType ipCtrlIdx;

  /* #10 Iterate over all configured IP instances. */
  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {

    /* #20 Transmit pending IP fragments. */
    if (TcpIp_IsIpV6FragmentationConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      IpV6_VTxFragments(ipCtrlIdx);
    }
  }
#endif
}  /* IpV6_MainFunctionTx() */

/**********************************************************************************************************************
 *  IpV6_VHandleCrtlTransitionStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_VHandleCrtlTransitionStates(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  /* #10 Handle IP controller state transitions. */
  if (TcpIp_GetCtrlStateOfIpV6CtrlDyn(IpCtrlIdx) != TcpIp_GetCtrlPreviousStateOfIpV6CtrlDyn(IpCtrlIdx))
  {
    /* controller state has changed */

    switch (TcpIp_GetCtrlPreviousStateOfIpV6CtrlDyn(IpCtrlIdx))
    {
    case IPV6_CTRL_STATE_INIT:
      /* fall through */
    case IPV6_CTRL_STATE_LINK_READY:
      if (IPV6_CTRL_STATE_LLADDR_READY == TcpIp_GetCtrlStateOfIpV6CtrlDyn(IpCtrlIdx))
      {
        /* IPV6_CTRL_STATE_INIT --> (IPV6_CTRL_STATE_LINK_READY -->) IPV6_CTRL_STATE_LLADDR_READY */
        IpV6_VCtrlStateOnline(IpCtrlIdx);
      }
      break;

      default:
        /* No deferred state transition necessary */
      break;
    }

    TcpIp_SetCtrlPreviousStateOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetCtrlStateOfIpV6CtrlDyn(IpCtrlIdx));
  }
}

/**********************************************************************************************************************
 *  IpV6_MainFunctionState()
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
FUNC(void, IPV6_CODE) IpV6_MainFunctionState(void)
{
  Std_ReturnType result = E_OK;
  /* #10 Check if module is initialized. */
  if (IpV6_State == IPV6_STATE_UNINIT)
  {
    /* module is not initialized. Do nothing. */
  }
  else
  {
    TcpIp_IpV6CtrlIterType ipCtrlIdx;

    /* #20 Increment module time counter used for timeout handling. */
    IpV6_Time.Ms += TCPIP_MAIN_FCT_PERIOD_MSEC;

    if (1000u <= IpV6_Time.Ms)
    {
      IpV6_Time.Ms -= 1000u;
      IpV6_Time.S += 1u;
    }

    /* #30 Iterate over all configured IP controller instances. */
    for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
    {
      /* #40 Handle IP controller state transitions. */
      IpV6_VHandleCrtlTransitionStates(ipCtrlIdx);

      if (IPV6_CTRL_STATE_LLADDR_DAD_FAIL == TcpIp_GetCtrlStateOfIpV6CtrlDyn(ipCtrlIdx))
      {
        result = E_NOT_OK;
        break;
      }

      TcpIp_SetNextRouterProbeIdxOfIpV6CtrlDyn(ipCtrlIdx,
        TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(ipCtrlIdx));

      /* #50 Call MainFunctions of submodules ICMP, NDP, Privacy Extensions and MLD if ethernet link is established. */
      if (IPV6_CTRL_STATE_LINK_READY <= TcpIp_GetCtrlStateOfIpV6CtrlDyn(ipCtrlIdx))
      {
        IpV6_Icmp_MainFunction(ipCtrlIdx);
        IpV6_Ndp_MainFunction(ipCtrlIdx);
      }
    }

    if (result == E_OK)
    {
      /* #60 Call MainFunction of DHCPv6 submodule. */
#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
      TcpIp_DhcpV6_MainFunction();
#endif
    }
  }
} /* IpV6_MainFunctionState() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_Ip_VIsSourceAddressActive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VIsSourceAddressActive(
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  TcpIp_IpV6CtrlIterType                      IpCtrlIdx,
  IPV6_P2V(IpV6_SrcAddrFlagsType)             SrcAddrFlagsPtr,
#endif
  TcpIp_SizeOfIpV6SourceAddressTableEntryType SrcAddrIdx)
{
  IpV6_LocAddrStateType srcAddrState;
  BufReq_ReturnType Result;

  /* Caller provided a source address, we have to respect this choice if the provided address
   * is suitable for sending the packet to the destination.
   */
  srcAddrState = TcpIp_GetAddrIpV6SourceAddressTableEntry(SrcAddrIdx)->State;

  /* #10 Check the state of the source address provided and decide if it can be used to send packet */
  switch (srcAddrState)
  {
  case IPV6_LADDR_STATE_INVALID:
    Result = BUFREQ_E_NOT_OK;
    break;

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  case IPV6_LADDR_STATE_TENTATIVE:
    if (SrcAddrIdx == TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx))
    {
      /* send with unspecified address */
      SrcAddrFlagsPtr->UseUnspecifiedAddr = TRUE;
      Result = BUFREQ_OK;
    }
    else
    {
      /* do not allow transmit with unspecified address */
      Result = BUFREQ_E_NOT_OK;
    }
    break;

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  case IPV6_LADDR_STATE_OPTIMISTIC:
    /* store information that source addres is optimistic.
     * We must not not start link-layer address resolution from optimistic addresses.
     */
    SrcAddrFlagsPtr->SrcAddrOptimistic = TRUE;
    Result = BUFREQ_OK;
    break;
#endif
#endif

  default:
    /* IPV6_LADDR_STATE_PREFERRED */
    /* IPV6_LADDR_STATE_DEPRECATED */
    Result = BUFREQ_OK;
    break;
  }

  return Result;
}

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VNextHopLLDadOptimistic()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VNextHopLLDadOptimistic(
  TcpIp_SizeOfIpV6CtrlType        IpCtrlIdx,
  TcpIp_LocalAddrV6IterType       LocalAddrV6Idx,
  IpV6_ListIdxType                DcEntryIdx,
  IPV6_P2C(IpV6_AddrType *)       NextHopAddrPtrPtr,
  IPV6_P2C(IpV6_AddrType)         DstAddrPtr,
  IPV6_P2V(uint8)                 PhysAddrPtr,
  IPV6_P2V(IpV6_DstAddrFlagsType) DstAddrFlagsPtr)
{
  /* For non-multicast destinations we must resolve the link-layer address of the next hop neighbor.
    * If the link-layer address is not in the neighbor cache IpV6_VGetLinkLayerAddress() will create
    * an INCOMPLETE entry, trigger address resolution and return BUFREQ_E_BUSY.
    * If the source address is an optimistic address, triggering of address resolution will be inhibited.
    *
    * "A node MUST NOT use an Optimistic Address as the source address of a Neighbor Solicitation."
    * [RFC4429 3.2. Modifications to RFC 2461 Neighbor Discovery]
    */
  boolean nextHopReachable = FALSE;
  IpV6_ListIdxType ncEntryIdx = TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->NcIdxHint;

  /* #10 Check if link-layer address of the next hop is available in neighbor cache */
  if (E_OK == IpV6_Ndp_VNCLookup(IpCtrlIdx, *NextHopAddrPtrPtr, &ncEntryIdx))
  {
    TCPIP_ASSERT(ncEntryIdx < TcpIp_GetSizeOfIpV6NeighborCacheEntry());

    if (IPV6_REACHABLE_STATE_INCOMPLETE != TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State)
    {
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_LL_ADDR_COPY(PhysAddrPtr, &TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LinkLayerAddress[0]);
      nextHopReachable = TRUE;
    }
  }
  /* #20 If destination address is optimistic, send packet to default router instead */
  if (   (FALSE == nextHopReachable)
      && (TRUE == (DstAddrFlagsPtr->DstAddrOnLink)))
  {
    TcpIp_SizeOfIpV6DefaultRouterListEntryType  drlEntryIdx;
      /* send the packet to a default router (if there is one) although the destination is on-link
      * since we must not do link-layer address resolution using an optimistic source address */

    if (E_NOT_OK != IpV6_VGetDefaultRouterAddr(IpCtrlIdx, LocalAddrV6Idx, DstAddrPtr, &nextHopReachable, &drlEntryIdx))
    {
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      *NextHopAddrPtrPtr = &(TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->NextHopAddress);
    }
    else
    {
      IPV6_DBG_COUNTER_TX_INC(ProvTxBufNoDefRouterOptimistic);
    }
  }

  DstAddrFlagsPtr->NextHopReachable = nextHopReachable;
} /* IpV6_Ip_VNextHopLLDadOptimistic() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VRequestTxFragmentBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VRequestTxFragmentBuffer(
  TcpIp_SizeOfIpV6CtrlType                  IpCtrlIdx,
  uint16                                    PathMtu,
  IPV6_P2V(uint8*)                          BufPtrPtr,
  IPV6_P2V(uint16)                          BufLenPtr,
  IPV6_P2V(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr)
{
  BufReq_ReturnType Result;
  TcpIp_SizeOfIpV6FragmentationConfigType ipV6FragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  /* #10 Request fragment transmission buffer */
  if ((*BufLenPtr) <= TcpIp_GetTxFragmentBufferSizeOfIpV6FragmentationConfig(ipV6FragConfigIdx))
  {
    TcpIp_SizeOfIpV6FragmentTxBufferDescriptorType ipV6FragTxBufferDescIdx;

    if (E_OK == IpV6_VGetFragmentTxBufferIdx(IpCtrlIdx, &ipV6FragTxBufferDescIdx))
    {
      TCPIP_P2V(IpV6_FragmentTxBufferDescType) fragTxBufDescPtr;
      TcpIp_SizeOfIpV6FragmentTxDataBufferType fragTxDataBufferStartIdx;

      TCPIP_ASSERT(ipV6FragTxBufferDescIdx < TcpIp_GetSizeOfIpV6FragmentTxBufferDescriptor());

      fragTxBufDescPtr = TcpIp_GetAddrIpV6FragmentTxBufferDescriptorDyn(ipV6FragTxBufferDescIdx);

      TcpIp_IncNextTxFragmentIdOfIpV6CtrlDyn(IpCtrlIdx);

      IPV6_BEGIN_CRITICAL_SECTION();

      fragTxBufDescPtr->FragmentId = TcpIp_GetNextTxFragmentIdOfIpV6CtrlDyn(IpCtrlIdx);
      fragTxBufDescPtr->UnfragPartLen = (uint16) sizeof(IpV6_HdrType);
      fragTxBufDescPtr->FragPartLen = ((*BufLenPtr) - fragTxBufDescPtr->UnfragPartLen);
      fragTxBufDescPtr->MaxFragLen = (uint16)(PathMtu - fragTxBufDescPtr->UnfragPartLen - IPV6_FRAGMENT_EXT_HDR_LEN);
      fragTxBufDescPtr->TxOfs = 0;
      /* IPV6_CTRL_VAR(IpV6_FragmentTxBufferDescriptors)[BufIdx].NextHopPhysAddr  will be set in IpV6_Transmit() */

      IPV6_END_CRITICAL_SECTION();

      fragTxDataBufferStartIdx =
        TcpIp_GetIpV6FragmentTxDataBufferStartIdxOfIpV6FragmentTxBufferDescriptor(ipV6FragTxBufferDescIdx);

      (*BufPtrPtr) = TcpIp_GetAddrIpV6FragmentTxDataBuffer(fragTxDataBufferStartIdx);
      (*BufLenPtr) = TcpIp_GetTxFragmentBufferSizeOfIpV6FragmentationConfig(ipV6FragConfigIdx);
      TxReqDescrPtr->BufIdx = ipV6FragTxBufferDescIdx;
      TxReqDescrPtr->IsEthBufV6 = FALSE; /* indicates that we are not using an ethernet buffer for this packet */

      IPV6_DBG_COUNTER_TX_INC(ProvTxBufFragmentation);
      Result = BUFREQ_OK;
    }
    else
    {
      IPV6_DBG_COUNTER_TX_INC(ProvTxBufBusyNoFragBuf);
      Result = BUFREQ_E_BUSY; /* currently no free tx fragment buffer available */
    }
  }
  else
  {
    IPV6_DBG_COUNTER_TX_INC(ProvTxBufFailBufLenTooBig);
    Result = BUFREQ_E_NOT_OK; /* requested buffer length too big */
  }
  return Result;
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VGetIpControllerIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VGetIpControllerIdx(
  IPV6_P2V(TcpIp_LocalAddrIterType)   LocalAddrV6IdxPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6CtrlType)  IpV6CtrlIdxPtr)
{
  Std_ReturnType Result;
  /* #10 Obtain controller index for a given Ip address index */

  if (*LocalAddrV6IdxPtr == TCPIP_LOCAL_ADDR_V6_IDX_ANY)
  {
    /* Use default Ip controller if LocalAddrV6IdxPtr does not reference a specific IP controller */
    /* #20 If no index provided, return default controller index, if present */
    if (TcpIp_IsIpV6CtrlDefaultUsedOfIpV6General(TCPIP_IPV6GENERAL_IDX) == TRUE)
    {
      TcpIp_IpV6CtrlDefaultIdxOfIpV6GeneralType defIpV6CtrlIdx =
        TcpIp_GetIpV6CtrlDefaultIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX);
      (*LocalAddrV6IdxPtr) = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(defIpV6CtrlIdx);
      *IpV6CtrlIdxPtr = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(*LocalAddrV6IdxPtr);
      Result = E_OK;
    }
    else
    {
      /* No default controller configured. */
      Result = E_NOT_OK;
    }
  }
  else
  {
    /* #30 If valid address index provided, return controller index */
    *IpV6CtrlIdxPtr = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(*LocalAddrV6IdxPtr);
    Result = E_OK;
  }
  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VDetermineValidSourceAddressIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VDetermineValidSourceAddressIdx(
  TcpIp_SizeOfIpV6CtrlType                              IpCtrlIdx,
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType) SrcAddrIdxPtr,
  IpV6_ListIdxType                                      DcEntryIdx,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  IPV6_P2V(boolean)                                     SrcAddrOptimisticPtr,
#endif
 IPV6_P2C(IpV6_AddrType)                               DstAddrPtr)
{
  BufReq_ReturnType Result = BUFREQ_OK;

  TcpIp_SizeOfIpV6SourceAddressTableEntryType srcAddrIdx = TCPIP_IPV6_SRC_ADDR_IDX_INV;
  TCPIP_P2V(IpV6_DestinationCacheEntryType) dcEntryPtr = TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx);

  /* #10 Select and assign a valid source address index to send packet to destination */
  if (IpV6_VSelectSourceAddress(IpCtrlIdx, DstAddrPtr, &srcAddrIdx) == E_OK)
  {
    TCPIP_ASSERT(srcAddrIdx < TcpIp_GetSizeOfIpV6SourceAddress());

    /* store selected source address index in destination cache.
     * The cached source address will be valid until one of the source addresses of this node change.
     */

    dcEntryPtr->SourceAddressIdx = srcAddrIdx;

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
    if (IPV6_LADDR_STATE_OPTIMISTIC == TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State)
    {
      *SrcAddrOptimisticPtr = TRUE;
    }
#endif

    /* Update Source Address Idx */
    *SrcAddrIdxPtr = srcAddrIdx;
  }
  else
  {
    /* #20  If no address selected, assign TCPIP_IPV6_SRC_ADDR_IDX_INV */
    Result = BUFREQ_E_NOT_OK;
    dcEntryPtr->SourceAddressIdx = TCPIP_IPV6_SRC_ADDR_IDX_INV;

    IPV6_DBG_COUNTER_TX_INC(ProvTxBufFailNoSrcAddr);
  }


  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VObtainPathMtu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(uint16, IPV6_CODE) IpV6_Ip_VObtainPathMtu(
#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
  IpV6_ListIdxType          DcEntryIdx,
#endif
  TcpIp_SizeOfIpV6CtrlType  IpCtrlIdx)
{
  uint16 pathMtu;

  /* #10 Obtain the path mtu of a destination */
#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
  if (TcpIp_IsEnablePathMtuOfIpV6Ctrl(IpCtrlIdx) == TRUE)
  {
    pathMtu = TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->Mtu;
  }
  else
#endif
  if (TcpIp_IsAllowLinkMtuReconfigurationOfIpV6Ctrl(IpCtrlIdx) == TRUE)
  {
    pathMtu = TcpIp_GetDefaultLinkMtuOfIpV6CtrlDyn(IpCtrlIdx);
  }
  else
  {
    pathMtu = TcpIp_GetDefaultLinkMtuOfIpV6Ctrl(IpCtrlIdx);
  }
  return pathMtu;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VCallerSpecifiedSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VCallerSpecifiedSourceAddress(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  TcpIp_LocalAddrV6IterType                              LocalAddrV6Idx,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  IPV6_P2V(IpV6_SrcAddrFlagsType)                        SrcAddrFlagsPtr,
#endif
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType)  SrcAddrIdxPtr)
{
  BufReq_ReturnType Result = BUFREQ_OK;

#if (TCPIP_SUPPORT_NDP_DAD == STD_OFF)
  TCPIP_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  /* #10 Check if the Ip address index provided is a valid source address */
  if (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE)
  {
    TcpIp_SizeOfIpV6SourceAddressTableEntryType srcAddrIdx;

    /* #20 Derive the source address index from the Ip Address index provided by the caller */
    srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);

    /* #30 Check if the provide source address is active */
    Result = IpV6_Ip_VIsSourceAddressActive(
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      IpCtrlIdx,
      SrcAddrFlagsPtr,
#endif
      srcAddrIdx);

    if (Result == BUFREQ_E_NOT_OK)
    {
      /* the provided source address is not suitable for sending to the destination */
      IPV6_DBG_COUNTER_TX_INC(ProvTxBufFailInvSrcAddr);
    }
    else
    {
      /* #40 If the source address is active, return the source index to be used */
      *SrcAddrIdxPtr = srcAddrIdx;
    }
  }
  else
  {
    /* #50 If Ip address index is not a valid source address index, return invalid index to caller */
    *SrcAddrIdxPtr = TCPIP_IPV6_SRC_ADDR_IDX_INV;
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VDCSourceAddressLookup()
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
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VDCSourceAddressLookup(
  TcpIp_SizeOfIpV6CtrlType                               IpCtrlIdx,
  IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType)  SrcAddrIdxPtr,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  IPV6_P2V(boolean)                                      SrcAddrOptimisticPtr,
#endif
  IPV6_P2V(IpV6_ListIdxType)                             DcEntryIdxPtr,
  IPV6_P2C(IpV6_AddrType)                                DstAddrPtr)
{
  BufReq_ReturnType Result = BUFREQ_OK;

  /* #10 Determine if suitable source address is present in the destination cache */
  if ((E_OK == IpV6_Ndp_VDCLookup(IpCtrlIdx, DstAddrPtr, DcEntryIdxPtr)))
  {
    TCPIP_P2V(IpV6_DestinationCacheEntryType) dcEntryPtr = TcpIp_GetAddrIpV6DestinationCacheEntry(*DcEntryIdxPtr);
    TCPIP_ASSERT((*DcEntryIdxPtr) < TcpIp_GetSizeOfIpV6DestinationCacheEntry());

    /* #20 Check if the source address index has not been determined yet (caller specified address index) */
    if ((*SrcAddrIdxPtr) < TcpIp_GetSizeOfIpV6SourceAddress())
    {
      /* #30 If there is a valid source index available, update the destination cache entry with the new value */
      dcEntryPtr->SourceAddressIdx = *SrcAddrIdxPtr;
    }
    else
    {
      /* #40 Otherwise, check if the destination cache entry contains a valid source address index that can be used */
      if (dcEntryPtr->SourceAddressIdx < TcpIp_GetSizeOfIpV6SourceAddress())
      {
        /* #50 Use cached source address index, if present */
        (*SrcAddrIdxPtr) = dcEntryPtr->SourceAddressIdx;

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
        /* PRQA S 4304 2 */ /* MD_MSR_AutosarBoolean */
        *SrcAddrOptimisticPtr =
         (boolean)(IPV6_LADDR_STATE_OPTIMISTIC == TcpIp_GetAddrIpV6SourceAddressTableEntry((*SrcAddrIdxPtr))->State);
#endif
      }
      else
      {
        /* #60 If not cached address, Source Address will be determined by source selection algorithm */
      }
    }
  }

  if ((*SrcAddrIdxPtr) == TCPIP_IPV6_SRC_ADDR_IDX_INV)
  {
    /* #70 If no valid source index determined, use source selection algorithm */
    Result = IpV6_Ip_VDetermineValidSourceAddressIdx(IpCtrlIdx, SrcAddrIdxPtr, (*DcEntryIdxPtr),
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
      SrcAddrOptimisticPtr,
#endif
      DstAddrPtr);
    if (Result == BUFREQ_OK)
    {
      TCPIP_ASSERT((*SrcAddrIdxPtr) < TcpIp_GetSizeOfIpV6SourceAddress());
    }
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VObtainNextHopAddress()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VObtainNextHopAddress(
 TcpIp_LocalAddrV6IterType           LocalAddrV6Idx,
 IPV6_P2V(IpV6_ListIdxType)          DcEntryIdxPtr,
 IPV6_P2C(IpV6_AddrType)             DstAddrPtr,
 IPV6_P2V(IpV6_DstAddrFlagsType)     DstAddrFlagsPtr,
 IPV6_P2C(IpV6_AddrType *)           NextHopAddrPtrPtr)
{
  BufReq_ReturnType Result = BUFREQ_OK;
  TcpIp_SizeOfIpV6CtrlType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* #10 If destination is present in the destination cache, use cached next hop address */
  if (E_OK == IpV6_Ndp_VDCLookup(ipCtrlIdx, DstAddrPtr, DcEntryIdxPtr))
  {
    TCPIP_P2C(IpV6_DestinationCacheEntryType) dcEntryPtr = TcpIp_GetAddrIpV6DestinationCacheEntry((*DcEntryIdxPtr));

    TCPIP_ASSERT((*DcEntryIdxPtr) < TcpIp_GetSizeOfIpV6DestinationCacheEntry());

    /* Found Destination Cache entry with cached source and next hop addresses. */
    IPV6_DBG_COUNTER_TX_INC(ProvTxBufDcHits);

    DstAddrFlagsPtr->DstAddrOnLink = dcEntryPtr->DestinationOnLink;

    /* use cached next hop address */
    (*NextHopAddrPtrPtr) = &(TcpIp_GetAddrIpV6DestinationCacheEntry((*DcEntryIdxPtr))->NextHopAddress);
  }
  else
  {
    /* No corresponding Destination Cache entry has been found.
     * We have to select a matching source and next hop address.
     */

    /* Begin next hop determination */

    DstAddrFlagsPtr->DstAddrOnLink = IpV6_VIsDestinationOnLink(ipCtrlIdx, DstAddrPtr);

    /* #20 If destination is on link, next hop is the destination itself */
    if (TRUE == DstAddrFlagsPtr->DstAddrOnLink)
    {
      /* The destination is on-link (a neighbor), so we can sent the packet directly. */
      (*NextHopAddrPtrPtr) = DstAddrPtr;
    }
    else
    {
      /* #30 If destination is considered to be off-link, send the packet to one of the default routers */
      if (E_NOT_OK == IpV6_VGetDefaultRouterAddr(ipCtrlIdx, LocalAddrV6Idx, DstAddrPtr, &(DstAddrFlagsPtr->NextHopReachable), DcEntryIdxPtr))
      {
        /* No default routers known, we cannot sent the packet. */

        IPV6_DBG_COUNTER_TX_INC(ProvTxBufFailNoDefRouter);
        Result =  BUFREQ_E_NOT_OK;
      }
      else
      {
        *NextHopAddrPtrPtr = &(TcpIp_GetAddrIpV6DefaultRouterListEntry(*DcEntryIdxPtr)->NextHopAddress);
      }
    }

    if(Result == BUFREQ_OK)
    {
      /* #40 If next hop address was successfully resolved, create a new destination cache entry if not present */
      IpV6_Ndp_VDCGetOrCreateEntry(ipCtrlIdx, DstAddrPtr, DcEntryIdxPtr);
    }
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VValidateDestAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VValidateDestAddr(
  IPV6_P2V(TcpIp_LocalAddrIterType)   LocalAddrV6IdxPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6CtrlType)  IpCtrlIdxPtr,
  IPV6_P2C(IpV6_AddrType)             DstAddrPtr)
{
  BufReq_ReturnType Result = BUFREQ_OK;

  /*#10 Validate the destination address */
  /* Get Ip Controller index */
  if (IpV6_Ip_VGetIpControllerIdx(LocalAddrV6IdxPtr, IpCtrlIdxPtr) == E_NOT_OK)
  {
    /* No default controller configured. */
    Result = BUFREQ_E_NOT_OK;
  }
  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  else if (   (TcpIp_IsExtDestAddrValidationEnabledOfIpV6General(TCPIP_IPV6GENERAL_IDX) == TRUE)
           && (IpV6_IsValidDestinationAddress((*IpCtrlIdxPtr), DstAddrPtr) == FALSE))
  {
    IPV6_DBG_COUNTER_TX_INC(ProvTxBufFailInvDstAddr);
    /* Do not allow sending packets to invalid destination address! */
    Result = BUFREQ_E_NOT_OK;
  }
  else
  {
    /* do nothing */
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VNextHopLLResolution()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VNextHopLLResolution(
 TcpIp_LocalAddrIterType    LocalAddrV6Idx,
 IpV6_ListIdxType           DcEntryIdx,
 IPV6_P2C(IpV6_AddrType)    DstAddrPtr,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
 boolean                    SrcAddrOptimistic,
#endif
 IPV6_P2C(IpV6_AddrType *)  NextHopAddrPtrPtr,  /* PRQA S 3673 */ /* MD_IPV6_Rule8.3_3673 */
 boolean                    ForceProvideBuffer)
{
  BufReq_ReturnType result = BUFREQ_OK;
  TcpIp_SizeOfIpV6CtrlType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
  TcpIp_SizeOfIpV6SourceAddressTableEntryType srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
  IpV6_ListIdxType       NcEntryIdx;
  IpV6_DstAddrFlagsType  DstAddrFlags;
  Eth_PhysAddrType       NextHopLLAddr;

  DstAddrFlags.NextHopReachable = FALSE;
  DstAddrFlags.DstAddrOnLink =  TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->DestinationOnLink;

  /* Start link-layer address resolution for next hop address */
  /* Get index hint for neighbor cache entry */
  NcEntryIdx = TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->NcIdxHint;

  if (IPV6_ADDR_IS_MULTICAST(*DstAddrPtr))
  {
    DstAddrFlags.NextHopReachable = TRUE;
  }
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  /* #10 Perform optimistic DAD link layer address resolution if enabled */
  else if (SrcAddrOptimistic == TRUE)
  {
    IpV6_Ip_VNextHopLLDadOptimistic(ipCtrlIdx, LocalAddrV6Idx, DcEntryIdx, NextHopAddrPtrPtr,
                             DstAddrPtr, &NextHopLLAddr[0], &DstAddrFlags);
  }
#endif
  /* #20 Perform link layer address resolution */
  else if (E_OK == IpV6_VResolveLinkLayerAddr(ipCtrlIdx, srcAddrIdx, *NextHopAddrPtrPtr, &NextHopLLAddr[0], &NcEntryIdx))
  {
    /* ok. link-layer address of next hop has been stored in NextHopLLAddr. */
    /* store current index of neighbor cache entry as a hint for next lookup */
    TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->NcIdxHint = NcEntryIdx;
    DstAddrFlags.NextHopReachable = TRUE;
  }
  else
  {
    /* link-layer address of next hop unknown. Will be handled below. */
  }
  /* #30 If no link layer address was obtained, send BUFREQ_E_BUSY to indicate address resolution in progress */
  if ((FALSE == DstAddrFlags.NextHopReachable) && (FALSE == ForceProvideBuffer))
  {
    IPV6_P2C(IpV6_AddrType) nextHopAddrPtr = *NextHopAddrPtrPtr;
    /* link-layer address of NextHopAddr not cached in neighbor cache,
     * address resolution in progress...
     */
    /* update next hop address in destination cache entry */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->NextHopAddress, *nextHopAddrPtr);

    IPV6_DBG_COUNTER_TX_INC(ProvTxBufBusyNextHopUnreachable);
    result =  BUFREQ_E_BUSY;
  }
  return result;
} /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV6_Ip_VObtainSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_Ip_VObtainSourceAddress(
 TcpIp_LocalAddrIterType                                LocalAddrV6Idx,
 IPV6_P2V(TcpIp_SizeOfIpV6SourceAddressTableEntryType)  SrcAddrIdxPtr,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
 IPV6_P2V(IpV6_SrcAddrFlagsType)                        SrcAddrFlagsPtr,
#endif
 IPV6_P2V(IpV6_ListIdxType)                             DcEntryIdxPtr,
 IPV6_P2C(IpV6_AddrType)                                DstAddrPtr)
{
  BufReq_ReturnType result = BUFREQ_OK;
  TcpIp_SizeOfIpV6CtrlType  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* #10 Obtain Source Address from LocalAddrV6Idx if caller has provided */
  if (BUFREQ_E_NOT_OK == IpV6_Ip_VCallerSpecifiedSourceAddress(ipCtrlIdx, LocalAddrV6Idx,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    SrcAddrFlagsPtr,
#endif
    SrcAddrIdxPtr))
  {
    /* The source address provided by caller is unusable */
    result = BUFREQ_E_NOT_OK;
  }

  /* #20 Otherwise, determine the source address index from Destination cache entry / source selection algorithm */
  else if (BUFREQ_E_NOT_OK == IpV6_Ip_VDCSourceAddressLookup(ipCtrlIdx, SrcAddrIdxPtr,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
    &SrcAddrFlagsPtr->SrcAddrOptimistic,
#endif
    DcEntryIdxPtr, DstAddrPtr))
  {
    /* no matching source address found */
    IPV6_DBG_COUNTER_TX_INC(ProvTxBufFailNoSrcAddr);
    result = BUFREQ_E_NOT_OK;
  }
  else
  {
    /* do nothing */
  }

  return result;
}

/**********************************************************************************************************************
 *  IpV6_Ip_VConfigureSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VConfigureSourceAddress(
 TcpIp_SizeOfIpV6CtrlType                        IpCtrlIdx,
 TcpIp_SizeOfIpV6SourceAddressTableEntryType     SrcAddrIdx,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
 boolean                                         UseUnspecifiedAddr,
#endif
 P2VAR(IpV6_AddrType, AUTOMATIC, IPV6_APPL_VAR)  SrcAddrPtr)
{
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  TCPIP_ASSERT(ndpConfigIdx < TcpIp_GetSizeOfNdpConfig());

  /* #10 Assign source address from source address table if valid index, or assign unspecified address */
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if ((0u < TcpIp_GetDadTransmitsOfNdpConfig(ndpConfigIdx)) && (TRUE == UseUnspecifiedAddr))
  {
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(*SrcAddrPtr, IpV6_AddrUnspecified);
  }
  else
#endif
  {
    /* PRQA S 0315, 2842 1 */ /* MD_MSR_VStdLibCopy, MD_TCPIP_CERT-ARR30-C_2842 */
    IPV6_ADDR_COPY(*SrcAddrPtr, TcpIp_GetAddrIpV6SourceAddressTableEntry(SrcAddrIdx)->Address);
  }
}
/**********************************************************************************************************************
 *  IpV6_ProvideTxBuffer()
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
 */
FUNC(BufReq_ReturnType, IPV6_CODE) IpV6_ProvideTxBuffer(  /* PRQA S 2889 */ /* MD_IPV6_Rule15.5_ComplexFunction */
    IPV6_P2V(TcpIp_LocalAddrIterType)         LocalAddrV6IdxPtr,
    TcpIp_SocketDynIterType                   IpV6SocketIdx,
    IPV6_P2C(IpV6_AddrType)                   DstAddrPtr,
    IPV6_P2V(uint8*)                          BufPtrPtr,
    IPV6_P2V(uint16)                          BufLenPtr,
    IPV6_P2V(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr,
    boolean                                   ForceProvideBuffer)
{
  TcpIp_SizeOfIpV6CtrlType ipCtrlIdx;
  TcpIp_SizeOfIpV6SourceAddressTableEntryType ipV6SrcAddrIdx = TCPIP_IPV6_SRC_ADDR_IDX_INV;

  IPV6_P2C(IpV6_AddrType)NextHopAddrPtr;
  IpV6_ListIdxType                                   DcEntryIdx;
  BufReq_ReturnType                                  Result;
  IpV6_DstAddrFlagsType                              DstAddrFlags;

#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
  uint16                                             PathMtu;
#endif

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  IpV6_SrcAddrFlagsType                           SrcAddrFlags;
#endif

  /* Det checks */
  TCPIP_ASSERT(IpV6_State != IPV6_STATE_UNINIT);

  TCPIP_ASSERT((LocalAddrV6IdxPtr != NULL_PTR) && ((*LocalAddrV6IdxPtr < TcpIp_GetSizeOfLocalAddrV6()) || (*LocalAddrV6IdxPtr == TCPIP_LOCAL_ADDR_V6_IDX_ANY)));
  TCPIP_ASSERT(IpV6SocketIdx < TcpIp_GetSizeOfIpV6SocketDyn());


  TCPIP_ASSERT(NULL_PTR != TxReqDescrPtr);
  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);
  TCPIP_ASSERT(NULL_PTR != BufPtrPtr);
  TCPIP_ASSERT(NULL_PTR != BufLenPtr);
  /**/

  IPV6_DBG_COUNTER_TX_INC(ProvTxBufTotalCalls);

  /* Initialise Address Flags */
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
  SrcAddrFlags.UseUnspecifiedAddr = FALSE;
#endif

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  SrcAddrFlags.SrcAddrOptimistic = FALSE;
#endif
  DstAddrFlags.NextHopReachable = FALSE;

  /* #10 Perform destination address validation */
  if (BUFREQ_E_NOT_OK == IpV6_Ip_VValidateDestAddr(LocalAddrV6IdxPtr, &ipCtrlIdx, DstAddrPtr))
  {
    /* no Controller Idx found or invalid destination address */
    return BUFREQ_E_NOT_OK;
  }

  IPV6_BEGIN_CRITICAL_SECTION();

  /* Get index hint for destination cache entry */
  DcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryHintIdxOfIpV6SocketDyn(IpV6SocketIdx);

  /* #20 Perform next hop address resolution */
  if (BUFREQ_E_NOT_OK ==
    IpV6_Ip_VObtainNextHopAddress(*LocalAddrV6IdxPtr, &DcEntryIdx, DstAddrPtr,
    &DstAddrFlags, (const IpV6_AddrType**)&NextHopAddrPtr))   /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_Uint8ToStruct */
  {
    IPV6_END_CRITICAL_SECTION();
    return BUFREQ_E_NOT_OK;
  }

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
  TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->DestinationOnLink = DstAddrFlags.DstAddrOnLink;
#endif

  /* Optimization: store index of destination cache for this socket,
   * so we can check this index first the next time ProvideTxBuffer is called
   */
  TcpIp_SetIpV6DestinationCacheEntryHintIdxOfIpV6SocketDyn(IpV6SocketIdx, DcEntryIdx);

  /* #30 Invoke routine to obtain Source Address to send packet to destination */
  if (BUFREQ_E_NOT_OK == IpV6_Ip_VObtainSourceAddress((*LocalAddrV6IdxPtr), &ipV6SrcAddrIdx,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    &SrcAddrFlags,
#endif
    &DcEntryIdx, DstAddrPtr))
  {
    /* no matching source address found */
    TCPIP_P2V(IpV6_DestinationCacheEntryType) dcEntryPtr = TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx);

    /* uninitiallize the destination cache source address index */
    dcEntryPtr->SourceAddressIdx = TCPIP_IPV6_SRC_ADDR_IDX_INV;

    /* update next hop address in destination cache entry */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(dcEntryPtr->NextHopAddress.addr[0], NextHopAddrPtr->addr[0]);

    IPV6_END_CRITICAL_SECTION();
    return BUFREQ_E_NOT_OK;
  }

  TCPIP_ASSERT(ipV6SrcAddrIdx < TcpIp_GetSizeOfIpV6SourceAddress());

  (*LocalAddrV6IdxPtr) = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);

  /* Source address and next hop determination completed. (srcAddrIdx and NextHopAddrPtr valid) */

  /* #40 Perform link-layer address resolution for next hop address */
  if (FALSE == DstAddrFlags.NextHopReachable)
  {
    if (BUFREQ_E_BUSY == IpV6_Ip_VNextHopLLResolution(*LocalAddrV6IdxPtr, DcEntryIdx, DstAddrPtr,
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
      SrcAddrFlags.SrcAddrOptimistic,
#endif
      (const IpV6_AddrType**)&NextHopAddrPtr, ForceProvideBuffer))   /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_Uint8ToStruct */
    {
      /* link-layer address of NextHopAddr not cached in neighbor cache,
       * address resolution in progress...
       */
      IPV6_END_CRITICAL_SECTION();
      return BUFREQ_E_BUSY;
    }
  }

  /* update next hop address in destination cache entry */
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->NextHopAddress, *NextHopAddrPtr);

  /* get tx buffer */

  /* we need additional space for the IPv6 header */
  (*BufLenPtr) += (uint16) sizeof(IpV6_HdrType);

#if(TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
  PathMtu = IpV6_Ip_VObtainPathMtu(
# if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
    DcEntryIdx,
# endif
    ipCtrlIdx);

  /* #50 Check if packet needs to be sent as fragmented packets (if path Mtu is less than reported Mtu)
   *  and request fragmented tx buffer if required */
   /* PRQA S 3415 6 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if ((   (TcpIp_IsIpV6FragmentationConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
       && (TcpIp_GetTxFragmentBufferCountOfIpV6FragmentationConfig(TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(ipCtrlIdx)) > 0u))
       && (   ((*BufLenPtr) > PathMtu)
# if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
           || (TcpIp_GetAddrIpV6DestinationCacheEntry(DcEntryIdx)->MtuReported < PathMtu)
# endif
    ))
  {
    /* Requested payload length does not fit into the MTU of the path.
      * Send fragmented IPv6 packet if possible.
      */
    Result = IpV6_Ip_VRequestTxFragmentBuffer(ipCtrlIdx, PathMtu, BufPtrPtr, BufLenPtr, TxReqDescrPtr);
  }
  else
#endif
  /* #60 If no fragmentation necessary request ethernet buffer */
  {
    /* try to obtain ethernet tx buffer */
    Result = TCPIP_LL_ProvideTxBuffer(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(ipCtrlIdx),
      IPV6_ETHER_TYPE_ID, IPV6_GET_SOCKET_ETHIF_FRAME_PRIO(ipCtrlIdx, IpV6SocketIdx),
      &TxReqDescrPtr->BufIdx, (Eth_DataType **)BufPtrPtr, BufLenPtr);                                                  /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_Uint8ToEth_DataType */

#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
    TxReqDescrPtr->IsEthBufV6 = TRUE;
#endif
  }
  /* #70 If buffer provided, write IPv6 header directly into the buffer */
  if (BUFREQ_OK == Result)
  {
    IpV6_AddrType  srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

    /* IpV6Hdr.HopLimit will be set in IpV6_Transmit() */
    /* IpV6Hdr.VersionTcFlNbo will be set in IpV6_Transmit() */
    IpV6_Ip_VConfigureSourceAddress(ipCtrlIdx, ipV6SrcAddrIdx,
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      SrcAddrFlags.UseUnspecifiedAddr,
#endif
      &srcAddr);

    /* copy source and destination address into buffer */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY((*BufPtrPtr)[IPV6_HDR_OFF_DSTADDR], *DstAddrPtr);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY((*BufPtrPtr)[IPV6_HDR_OFF_SRCADDR], srcAddr);

    /* Store CtrlIdx and BufIdx that belong to the socket until IpV6_Transmit is called.
     * This information is used by IpV6_Transmit(SocketIdx, ...)
     */
    TxReqDescrPtr->SrcAddrIdx    = ipV6SrcAddrIdx;
    TxReqDescrPtr->CtrlIdx       = TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(ipCtrlIdx);
    TxReqDescrPtr->EthPayloadPtr = (*BufPtrPtr);
    TxReqDescrPtr->EthPayloadLen = (*BufLenPtr);
    TxReqDescrPtr->IpPayloadOfs  = (uint16) sizeof(IpV6_HdrType);
    TxReqDescrPtr->SockIdx       = (TcpIp_SizeOfSocketDynType)IpV6SocketIdx;
    TxReqDescrPtr->AddressFamily = TCPIP_AF_INET6;

    /* ok, next hop mac address could be determined */
    /* move buffer pointer to beginning of IP payload and set the length */
    (*BufPtrPtr)  = &(*BufPtrPtr)[sizeof(IpV6_HdrType)];
    (*BufLenPtr) -= (uint16) sizeof(IpV6_HdrType);

    IPV6_DBG_COUNTER_TX_INC(ProvTxBufSuccess);
  }

  IPV6_END_CRITICAL_SECTION();
  return Result;
} /* End of IpV6_ProvideTxBuffer() */ /* PRQA S 6010, 6050, 6060 */ /* MD_MSR_STPTH, MD_MSR_STCAL, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV6_CancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_CancelTransmit(
    IPV6_P2C(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr)
{
  TcpIp_SizeOfIpV6CtrlType ipCtrlIdx;
  TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx;
  TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx;

  Eth_PhysAddrType NextHopLLAddr =
  {
    0, 0, 0, 0, 0, 0
  };

  TCPIP_ASSERT(TxReqDescrPtr != NULL_PTR);
  TCPIP_ASSERT(TxReqDescrPtr->SrcAddrIdx < TcpIp_GetSizeOfIpV6SourceAddress());

  ipV6SrcAddrIdx = TxReqDescrPtr->SrcAddrIdx;

  localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

  TCPIP_ASSERT(TxReqDescrPtr->SrcAddrIdx >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(ipCtrlIdx));
  TCPIP_ASSERT(TxReqDescrPtr->SrcAddrIdx <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(ipCtrlIdx));

  /* #10 Cancel ipv6 packet transmit by invoking eth transmit with zero length */
  (void)TCPIP_LL_Transmit(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(ipCtrlIdx),
    TxReqDescrPtr->BufIdx, IPV6_ETHER_TYPE_ID, FALSE, 0, NextHopLLAddr);
} /* End of IpV6_CancelTransmit() */


/**********************************************************************************************************************
 *  IpV6_Ip_VSetVersionTcFlNbo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(uint32, IPV6_CODE) IpV6_Ip_VSetVersionTcFlNbo(
  TcpIp_SizeOfIpV6CtrlType   IpCtrlIdx,
  TcpIp_SizeOfSocketDynType  IpV6SocketIdx)
{

  uint32 versionTcFlNbo = IPV6_HEADER_VERSION_TC_FL_ZERO_NBO;

  /* #10 Set value of version, traffic flow and flow control of ipv6 header */
  if (0u != (TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) & IPV6_SOCKET_DATA_FLAG_TRAFFIC_CLASS))
  {
    /* use socket specific 'Traffic Class' value */
    versionTcFlNbo |=
      (TcpIp_GetIpV6HdrVersionTcFlNboOfIpV6SocketDyn(IpV6SocketIdx) & IPV6_HEADER_MASK_TRAFFIC_CLASS_NBO);
  }
  else
  {
    /* use controller specific 'Traffic Class' value */
    versionTcFlNbo |=
      (TcpIp_GetDefaultTrafficClassFlowLabelNboOfIpV6Ctrl(IpCtrlIdx) & IPV6_HEADER_MASK_TRAFFIC_CLASS_NBO);
  }

  if (0u != (TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) & IPV6_SOCKET_DATA_FLAG_FLOW_LABEL))
  {
    /* use socket specific 'Flow Label' value */
    versionTcFlNbo |=
      (TcpIp_GetIpV6HdrVersionTcFlNboOfIpV6SocketDyn(IpV6SocketIdx) & IPV6_HEADER_MASK_FLOW_LABEL_NBO);
  }
  else
  {
    /* use controller specific 'Flow Label' value */
    versionTcFlNbo |=
      (TcpIp_GetDefaultTrafficClassFlowLabelNboOfIpV6Ctrl(IpCtrlIdx) & IPV6_HEADER_MASK_FLOW_LABEL_NBO);
  }
  return versionTcFlNbo;
}


/**********************************************************************************************************************
 *  IpV6_Ip_VStoreChecksumInHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VStoreChecksumInHeader(
  uint8           ProtHeader,
  uint32          ProtocolChecksum,
  IPV6_P2V(uint8) PayloadPtr)
{
  /* #10 Store calculated checksum in upper layer protocol header */
  switch (ProtHeader)
  {
#if (TCPIP_SUPPORT_TCP == STD_ON)
    case TCPIP_PROTOCOL_TCP:
      TcpIp_Tcp_StoreChecksumInHeader((uint16)ProtocolChecksum, PayloadPtr);
      break;
#endif
    case TCPIP_PROTOCOL_UDP:
      TcpIp_Udp_StoreChecksumInHeader((uint16)ProtocolChecksum, PayloadPtr);
      break;

    case IPV6_HDR_ID_ICMP:
      IpV6_Icmp_StoreChecksumInHeader((uint16)ProtocolChecksum, PayloadPtr);
      break;

    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      /* Default case left blank intentionally */
      {
        /* unsupported protocol.
          * -> do nothing
          */
        IpV6_DetReportInternalError(IPV6_E_NOT_SUPPORTED);
      }
      break;
  }  /* switch(Protocol) */
}

/**********************************************************************************************************************
 *  IpV6_Ip_VCalculateandStoreChecksum()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VCalculateandStoreChecksum(
  uint8                                               NextHeader,
  IPV6_P2V(uint8)                                     PayloadPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA)   DstAddrPtr,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA)   SrcAddrPtr,
  uint16                                              PayloadLen)
{
  uint32 protocolChecksum;

  /* #10 calculate upper layer protocol checksum and store in the protocol header */
  protocolChecksum = TcpIp_VCalcIpV6PseudoHdrChecksum(DstAddrPtr, SrcAddrPtr, NextHeader, PayloadLen);
  protocolChecksum = IpBase_TcpIpChecksumAdd(PayloadPtr, PayloadLen, protocolChecksum, TRUE);

  IpV6_Ip_VStoreChecksumInHeader(NextHeader, protocolChecksum, PayloadPtr);
}

/**********************************************************************************************************************
 *  IpV6_Transmit()
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
 */
FUNC(TcpIp_ReturnType, IPV6_CODE) IpV6_Transmit(
    TcpIp_SizeOfSocketDynType                 IpV6SocketIdx,
    IPV6_P2C(TcpIp_IpTxRequestDescriptorType) TxReqDescrPtr,
    uint8                                     NextHeader,
    uint16                                    PayloadLen,
    boolean                                   TxConfirm,
    uint8                                     UlTxReqTabIdx,
    boolean                                   RetryOnPhysAddrMiss)
{
  TcpIp_SizeOfIpV6CtrlType                       ipCtrlIdx;
  Eth_PhysAddrType                               NextHopLLAddr = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  TcpIp_SizeOfIpV6DestinationCacheEntryType      dcEntryIdx;
  TcpIp_ReturnType                               Result;
  TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx;
  TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx;
  IpV6_AddrType destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  IpV6_AddrType srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

  TCPIP_ASSERT(IpV6SocketIdx < TcpIp_GetSizeOfIpV6SocketDyn());
  TCPIP_ASSERT(TxReqDescrPtr != NULL_PTR);
  TCPIP_ASSERT(TxReqDescrPtr->SrcAddrIdx < TcpIp_GetSizeOfIpV6SourceAddress());


  ipV6SrcAddrIdx = TxReqDescrPtr->SrcAddrIdx;

  localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

  TCPIP_ASSERT(ipV6SrcAddrIdx >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(ipCtrlIdx));
  TCPIP_ASSERT(ipV6SrcAddrIdx <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(ipCtrlIdx));

  IPV6_DBG_COUNTER_TX_INC(TransmitCalls);

  /* #10 Update IpV6 header fields in the tx descriptor */
  TCPIP_PUT_UINT16(TxReqDescrPtr->EthPayloadPtr, IPV6_HDR_OFF_PAYLOADLENNBO, PayloadLen);
  TxReqDescrPtr->EthPayloadPtr[IPV6_HDR_OFF_NEXTHDR]  = NextHeader;
  TxReqDescrPtr->EthPayloadPtr[IPV6_HDR_OFF_HOPLIMIT] = IPV6_GET_SOCKET_HOP_LIMIT(ipCtrlIdx, IpV6SocketIdx);
  TCPIP_PUT_UINT32(TxReqDescrPtr->EthPayloadPtr, IPV6_HDR_OFF_VERSIONTCFLNBO,
    TCPIP_NTOHL(IpV6_Ip_VSetVersionTcFlNbo(ipCtrlIdx, IpV6SocketIdx)));

  /* SrcAddr and DstAddr are already set by IpV6_ProvideTxBuffer() */
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(destAddr, TxReqDescrPtr->EthPayloadPtr[IPV6_HDR_OFF_DSTADDR]);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(srcAddr, TxReqDescrPtr->EthPayloadPtr[IPV6_HDR_OFF_SRCADDR]);

  /*
   * Next hop address should have been stored in destination cache by IPv6_ProvideTxBuffer().
   * Link-layer address of next hop should have been stored in neighbor cache since IPv6_ProvideTxBuffer()
   * returns BUFREQ_BUSY until address resolution for next hop has been completed.
   */

  IPV6_BEGIN_CRITICAL_SECTION_DC();

  dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryHintIdxOfIpV6SocketDyn(IpV6SocketIdx);
  Result = IpV6_Ndp_VDCLookup(ipCtrlIdx, &destAddr, &dcEntryIdx);
  TcpIp_SetIpV6DestinationCacheEntryHintIdxOfIpV6SocketDyn(IpV6SocketIdx, dcEntryIdx);

  if (TCPIP_OK == Result)
  {
#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
    TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx);

    TCPIP_ASSERT(ndpConfigIdx < TcpIp_GetSizeOfNdpConfig());
    /* Destination Cache entry found */

    /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
    /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    if (   (TcpIp_IsEnableNdpInvNsOfNdpConfig(ndpConfigIdx) == TRUE)
        && (TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX) == IpV6SocketIdx)
        && (TcpIp_IsIcmpNextHopLLAddrOverrideOfIpV6CtrlDyn(ipCtrlIdx) == TRUE))
    {
      /* #20 If inverse neighbor solicitation is enabled, physical address
       * is allowed for IcmpV6 packets */
      /* For the ICMP socket, we allow overriding the next hop link-layer address.
       * This is neccessary only for sending Inverse Neighbor Discovery Solicitations.
       * "Although the destination IP address is the all-node multicast address,
       *  the message is sent only to the target node."
       *  [RFC3122 4.1 Sender Node Processing]
       */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_LL_ADDR_COPY(&NextHopLLAddr[0], &(TcpIp_GetAddrIcmpNextHopLLAddrOverrideValueOfIpV6CtrlDyn(ipCtrlIdx))[0]);
      TcpIp_SetIcmpNextHopLLAddrOverrideOfIpV6CtrlDyn(ipCtrlIdx, FALSE); /* reset flag */
    }
    else
#endif
    {
      /* #30 Resolve link layer address of the next hop address */
      TCPIP_P2V(IpV6_DestinationCacheEntryType) dcEntryPtr;

      TCPIP_ASSERT(dcEntryIdx >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(ipCtrlIdx));
      TCPIP_ASSERT(dcEntryIdx  < TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(ipCtrlIdx));

      dcEntryPtr = TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx);

      TCPIP_ASSERT((dcEntryPtr->SourceAddressIdx == TCPIP_IPV6_SRC_ADDR_IDX_INV) || (dcEntryPtr->SourceAddressIdx >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(ipCtrlIdx)));
      TCPIP_ASSERT((dcEntryPtr->SourceAddressIdx == TCPIP_IPV6_SRC_ADDR_IDX_INV) || (dcEntryPtr->SourceAddressIdx <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(ipCtrlIdx)));

      if (E_OK != IpV6_VResolveLinkLayerAddr(ipCtrlIdx, dcEntryPtr->SourceAddressIdx, &dcEntryPtr->NextHopAddress, &NextHopLLAddr[0], &dcEntryPtr->NcIdxHint))
      {
        Result = TCPIP_E_PHYS_ADDR_MISS;
      }
    }
  }

  IPV6_END_CRITICAL_SECTION_DC();

  if (TCPIP_OK == Result)
  {
   /* tx possible */
#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
    if (FALSE == TxReqDescrPtr->IsEthBufV6)
    {
      TCPIP_P2V(IpV6_FragmentTxBufferDescType) fragTxBufferDescPtr;

      TCPIP_ASSERT(TcpIp_IsIpV6FragmentationConfigUsedOfIpV6Ctrl(ipCtrlIdx));
      TCPIP_ASSERT(TxReqDescrPtr->BufIdx >= TcpIp_GetIpV6FragmentTxBufferDescriptorStartIdxOfIpV6FragmentationConfig(TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(ipCtrlIdx)));
      TCPIP_ASSERT(TxReqDescrPtr->BufIdx < TcpIp_GetIpV6FragmentTxBufferDescriptorEndIdxOfIpV6FragmentationConfig(TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(ipCtrlIdx)));

      fragTxBufferDescPtr = TcpIp_GetAddrIpV6FragmentTxBufferDescriptorDyn(TxReqDescrPtr->BufIdx);

      /* lint -e(645) In case Result == E_OK NextHopLLAddr is always initialized.
       * If Result != E_OK this statement will not be reached.
       */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_LL_ADDR_COPY(fragTxBufferDescPtr->NextHopPhysAddr, NextHopLLAddr);
      fragTxBufferDescPtr->Status = IPV6_FRAG_TX_STATUS_TRANSMIT;
    }
    else
#endif
    {
      boolean CalculateProtocolChecksum;
      /* #40 Store socket information if tx confirmation has been requested
       * and calculate and store checksum into header */
      if (TRUE == TxConfirm)
      {
        /* Store which socket index belongs to the BufIdx of CtrlIdx.
         * This information is used in IpV6_TxConfirmation(CtrlIdx, BufIdx, ...).
         */

        TcpIp_SizeOfIpV6EthBufDataType ipV6EthBufDataIdx =
          TcpIp_GetIpV6EthBufDataStartIdxOfIpV6Ctrl(ipCtrlIdx) + TxReqDescrPtr->BufIdx;

        TCPIP_ASSERT(ipV6EthBufDataIdx < TcpIp_GetIpV6EthBufDataEndIdxOfIpV6Ctrl(ipCtrlIdx));

        TcpIp_SetIpV6SocketDynIdxOfIpV6EthBufData(ipV6EthBufDataIdx, IpV6SocketIdx);
        TcpIp_SetUlTxReqTabIdxOfIpV6EthBufData(ipV6EthBufDataIdx, UlTxReqTabIdx);
      }

      switch(NextHeader)
      {
# if (TCPIP_SUPPORT_TCP == STD_ON)
        case IPV6_HDR_ID_TCP:
          CalculateProtocolChecksum = (boolean)(TcpIp_IsHwChecksumTcpOfIpV6Ctrl(ipCtrlIdx) == FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
          break;
# endif
        case IPV6_HDR_ID_UDP:
          CalculateProtocolChecksum = (boolean)(TcpIp_IsHwChecksumUdpOfIpV6Ctrl(ipCtrlIdx) == FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
          break;

        case IPV6_HDR_ID_ICMP:
          CalculateProtocolChecksum = (boolean)(TcpIp_IsHwChecksumIcmpOfIpV6Ctrl(ipCtrlIdx) == FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
          break;

        default:
          /* not supported protocol type */
          IpV6_DetReportInternalError(IPV6_E_NOT_SUPPORTED);
          CalculateProtocolChecksum = FALSE;
          break;
      }

      if (TRUE == CalculateProtocolChecksum)
      {
        P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR) payloadPtr = &TxReqDescrPtr->EthPayloadPtr[IPV6_HDR_LEN];
        IpV6_Ip_VCalculateandStoreChecksum(NextHeader, payloadPtr, &destAddr, &srcAddr, PayloadLen);
      }
      /* #50 Invoke link layer transmit function for valid packet */
      Result = TCPIP_LL_Transmit(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(ipCtrlIdx),
        TxReqDescrPtr->BufIdx, IPV6_ETHER_TYPE_ID, TxConfirm, (uint16) sizeof(IpV6_HdrType) + PayloadLen, NextHopLLAddr);
    }
  }

  /* #60 If transmission failed, cancel link layer transmission and release ethernet buffer */
  if ((TCPIP_E_NOT_OK == Result) || ((TCPIP_E_PHYS_ADDR_MISS == Result) && (FALSE == RetryOnPhysAddrMiss)))
  {
#if (TCPIP_SUPPORT_IPV6_TX_FRAGMENTATION == STD_ON)
    if (FALSE == TxReqDescrPtr->IsEthBufV6)
    {
      /* release fragment tx buffer */
      TCPIP_P2V(IpV6_FragmentTxBufferDescType) fragTxBufferDescPtr =
        TcpIp_GetAddrIpV6FragmentTxBufferDescriptorDyn(TxReqDescrPtr->BufIdx);
      fragTxBufferDescPtr->Status = IPV6_FRAG_TX_STATUS_UNUSED;
    }
    else
#endif
    {
      /* cancel transmit, calling TCPIP_LL_Transmit with zero length payload will release the buffer */
      (void)TCPIP_LL_Transmit(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(ipCtrlIdx),
        TxReqDescrPtr->BufIdx, IPV6_ETHER_TYPE_ID, TxConfirm, 0, NextHopLLAddr);
    }

    IPV6_DBG_COUNTER_TX_INC(TransmitFailures);
    Result = TCPIP_E_NOT_OK;
  }

  return Result;
} /* End of IpV6_Transmit() */ /* PRQA S 6010, 6030, 6050, 6060  */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV6_GetSrcAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(IpV6_AddrType, IPV6_CODE) IpV6_GetSrcAddress(
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr)
{
  /* #10 Obtain the source address from the IpV6 packet header */
  IpV6_AddrType srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  TCPIP_ASSERT(IpTxReqDescPtr                != NULL_PTR);
  TCPIP_ASSERT(IpTxReqDescPtr->EthPayloadPtr != NULL_PTR);

  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(srcAddr, IpTxReqDescPtr->EthPayloadPtr[IPV6_HDR_OFF_SRCADDR]);
  return srcAddr;
} /* End of IpV6_GetSrcAddress() */


/**********************************************************************************************************************
 *  IpV6_SetSrcAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_SetSrcAddress(
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  IpV6_AddrType                             SrcAddr)  /* PRQA S 0759 */ /* MD_MSR_Union */
{
  TCPIP_ASSERT(IpTxReqDescPtr                != NULL_PTR);
  TCPIP_ASSERT(IpTxReqDescPtr->EthPayloadPtr != NULL_PTR);

  /* #10 Write into the source address field of the Ipv6 packet */
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(IpTxReqDescPtr->EthPayloadPtr[IPV6_HDR_OFF_SRCADDR], SrcAddr);
  return E_OK;
} /* End of IpV6_SetSrcAddress() */

/**********************************************************************************************************************
 *  IpV6_GetDstAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(IpV6_AddrType, IPV6_CODE)  IpV6_GetDstAddress(
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr)
{
  /*#10 Obtain the destination address from the IpV6 packet header */
  IpV6_AddrType dstAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  TCPIP_ASSERT(IpTxReqDescPtr                != NULL_PTR);
  TCPIP_ASSERT(IpTxReqDescPtr->EthPayloadPtr != NULL_PTR);

  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(dstAddr, IpTxReqDescPtr->EthPayloadPtr[IPV6_HDR_OFF_DSTADDR]);
  return dstAddr;
} /* End of IpV6_GetDstAddress() */

/**********************************************************************************************************************
 *  IpV6_Ip_VCheckIPv6HeaderValid()
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
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VCheckIPv6HeaderValid(
  TcpIp_SizeOfIpV6CtrlType                IpCtrlIdx,
  IPV6_P2V(TcpIp_SizeOfLocalAddrV6Type)   LocalAddrV6IdxPtr,
  IPV6_P2C(IpV6_HdrType)                  IpV6HdrPtr,
  IPV6_P2C(uint8)                         PhysAddrPtr,
  uint16                                  LenByte)
{
  IpV6_LocAddrStateType  SrcAddrState;
  TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx;
  Std_ReturnType Result;
  uint16 dataLen;
  uint32 VersionTcFl;

  IPV6_DBG_COUNTER_RX_INC(RxTotal);

  /* process main IPv6 header */
  VersionTcFl = TCPIP_NTOHL(IpV6HdrPtr->VersionTcFlNbo);
  dataLen = IPV6_HDR_LEN + TCPIP_NTOHS(IpV6HdrPtr->PayloadLenNbo);

  /* #10 Validate the IpV6 packet length and version */
  /* discard packet if it doesn't contain a complete IPv6 header */
  if (IPV6_HDR_LEN > LenByte)
  {
    IPV6_DBG_COUNTER_RX_INC(DropInvHdr);
    Result = E_NOT_OK; /* silently ignore invalid packet */
  }
  /* ignore packet if IPv6 version != 6 */
  else if (IPV6_HEADER_VERSION != IPV6_HEADER_GET_VERSION(VersionTcFl))
  {

    IPV6_DBG_COUNTER_RX_INC(DropInvHdr);
    Result = E_NOT_OK; /* silently ignore invalid packet */
  }
  /* ignore packet if payload length exceeds ethernet payload length */
  else if (dataLen > LenByte)
  {

    IPV6_DBG_COUNTER_RX_INC(DropInvLen);
    Result = E_NOT_OK; /* silently ignore invalid packet */
  }
  else if (   (IPV6_ADDR_IS_MULTICAST(IpV6HdrPtr->SrcAddr)) /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
           || (IPV6_ADDR_IS_LOOPBACK(IpV6HdrPtr->SrcAddr))
           || (IPV6_ADDR_EQUALS(IpV6HdrPtr->DstAddr, IpV6HdrPtr->SrcAddr)))
  {
   /* #20 Discard packets recieved from multicast and loopback addresses or
    * if destination and source address are the same */
    IPV6_DBG_COUNTER_RX_INC(DropInvSrc);
    /* do not accept packets sent from multicast or loopback source address or
      * packets with equal source and destination address */
    Result = E_NOT_OK;
  }
  else
  {
    Result = E_OK;
  }

  if(Result == E_OK)
  {
    /* #30 Check if source address of IpV6 header is assigned to the controller */
    if (TRUE == IpV6_VIsValidSourceAddress(IpCtrlIdx, &IpV6HdrPtr->SrcAddr, FALSE, &SrcAddrState, &ipV6SrcAddrIdx))
    {
#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
      /* #40 Accept the packet if sender address is used as optimistic by controller */
      if (IPV6_LADDR_STATE_OPTIMISTIC == SrcAddrState)
      {
        /* do not filter out packets sent from an address we currently use as optimistic.
         * Otherwise DAD would not detect NA sent in response to DAD NS.
         */
      }
      else
#endif
      {
        /* #50 Otherwise silently ignore the packet sent from an address that is
         * assigned to this node. (packet is sent by this node) */
        IPV6_DBG_COUNTER_RX_INC(DropOwn);
        /* In this error case the SATLookup is repeated
        * (It has already been done with result E_OK within the
        * call to IpV6_VIsValidSourceAddress(allowUnspecAddr=FALSE), above!
        */
        (void)IpV6_VSATLookup(IpCtrlIdx, &IpV6HdrPtr->SrcAddr, &ipV6SrcAddrIdx);
        /* #60 In case it is not a multicast address, calculate the TcpIp LocalAddrId */
        if (ipV6SrcAddrIdx != TCPIP_IPV6_SRC_ADDR_IDX_INV)
        {
          /* #70 Handle duplicate address. This handling includes PhysAddr comparison! */
          TcpIp_VDuplicateAddrDetected(
            TCPIP_IPV6_TO_LOCAL_ADDR_IDX(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx)),
            &IpV6HdrPtr->SrcAddr.addr[0], PhysAddrPtr);
        }
        Result = E_NOT_OK;
      }
    }
  }

  if(Result == E_OK)
  {
    /* #80 Verify if destination address is an address of controller */
    Result = IpV6_VIngressFilter(IpCtrlIdx, &IpV6HdrPtr->DstAddr, LocalAddrV6IdxPtr);

    if(Result == E_NOT_OK)
    {
      /* packet for other host */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
      /* Increment the counter for the dropped IpV6 packets due to invalid destination address. */
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_DROP_IPV6);
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6);
#endif
    }
  }
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
  else
  {
    /* Packet dropped due to incorrect packet format */
    TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6);
  }
#endif

  return Result;
} /* IpV6_Ip_VCheckIPv6HeaderValid() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

#if (IPV6_VENABLE_HOP_BY_HOP_EXT_HDR_SKIPPING != STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessHopByHopOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessHopByHopOptions(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      ThisHdrOfs,
  uint16                      ThisHdrLen,
  uint16                      DataLen)
{
  Std_ReturnType         Result = E_OK;
  uint8                  OptType;       /* type of the currently processed TLV option (Hop-by-Hop Opt, DestOpt) */
  uint16                 OptDataLen;    /* option data length of the currently processed TLV option */
  uint16                 optOfs;        /* offset to the currently processed TLV option relative to PayloadPtr */
  /* process Type-Length-Value (TLV) encoded options */

  optOfs = ThisHdrOfs + 2u; /* first option starts after NextHeader and HdrExtLen bytes */

  /*#10 Process the defined hop by hop options according to RFC2460 4.3 (the Pad0 and PadN option) */
  /* option loop */
  while (optOfs < (ThisHdrOfs + ThisHdrLen))
  {
    OptType = DataPtr[optOfs]; /* first byte of TLV option indicates Type */

    if (OptType == IPV6_EXT_HDR_OPT_TYPE_PAD_1) /* Pad1 option */
    {
      /* Pad1 option consists only of the OptType (1 byte padding) */
      optOfs++; /* next option starts directly after this one-byte option */
      continue;
    }

    OptDataLen = DataPtr[optOfs + 1u]; /* second byte of TLV option indicates DataLength in bytes */

    /* ignore packet if option length exceeds HopByHop header length */
    if ((optOfs + IPV6_TLV_OPT_DATA_OFFS + OptDataLen) > (ThisHdrOfs + ThisHdrLen))
    {
      Result = E_NOT_OK;
      IPV6_DBG_COUNTER_RX_INC(DropInvOptLen);
    }
    else
    {
      switch (OptType)
      {
        /* The only defined options by RFC2460 4.3 are the Pad0 and PadN options.
          * Pad0 is handled above, since it's a special 1-byte option.
          */

      case IPV6_EXT_HDR_OPT_TYPE_PAD_N: /* PadN option */
        /* ignore padding data (2 + N byte padding) */
        break;

      default:
        if (E_OK != IpV6_VHandleUnknownTlvOption(LocalAddrV6Idx, DataPtr, DataLen, optOfs))
        {
          Result = E_NOT_OK;
          /* we have to discard the packet */
          IPV6_DBG_COUNTER_RX_INC(DropUknOpt);
        }
        break;
      }
    }

    if(Result == E_NOT_OK)
    {
      /* Packet needs to be discared */
      break;
    }

    optOfs += IPV6_TLV_OPT_DATA_OFFS + OptDataLen; /* skip to next option */
  }

  return Result;
}
#endif /* (IPV6_VENABLE_HOP_BY_HOP_EXT_HDR_SKIPPING != STD_ON) */

#if (IPV6_VENABLE_DESTINATION_OPT_EXT_HDR_SKIPPING != STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessDstOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VProcessDstOptions(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      ThisHdrOfs,
  uint16                      ThisHdrLen,
  uint16                      DataLen)
{
  Std_ReturnType         Result = E_OK;
  uint8                  OptType;       /* type of the currently processed TLV option (Hop-by-Hop Opt, DestOpt) */
  uint16                 OptDataLen;    /* option data length of the currently processed TLV option */
  uint16                 optOfs;        /* offset to the currently processed TLV option relative to PayloadPtr */
  /* process TLV encoded options */

  optOfs = ThisHdrOfs + 2u; /* first option starts after NextHeader and HdrExtLen bytes */

  /*#10 Process the defined destination options according to RFC2460 4.3 (the Pad0 and PadN option) */
  /* option loop */
  while (optOfs < (ThisHdrOfs + ThisHdrLen))
  {
    OptType = DataPtr[optOfs]; /* first byte of TLV option indicates Type */

    if (OptType == IPV6_EXT_HDR_OPT_TYPE_PAD_1) /* Pad1 option */
    {
      /* Pad1 option consists only of the OptType (1 byte padding) */

      optOfs++; /* next option starts directly after this one-byte option */
      continue;
    }

    OptDataLen = DataPtr[optOfs + 1u]; /* second byte of TLV option indicates DataLength in bytes */

    /* ignore packet if option length exceeds DestinationOpt header length */
    if ((optOfs + IPV6_TLV_OPT_DATA_OFFS + OptDataLen) > (ThisHdrOfs + ThisHdrLen))
    {
      IPV6_DBG_COUNTER_RX_INC(DropInvOptLen);
      Result = E_NOT_OK;
    }
    else
    {
      switch (OptType)
      {
        /* The only defined options by RFC2460 4.6 are the Pad0 and PadN options.
          * Pad0 is handled above, since it's a special 1-byte option.
          */

      case IPV6_EXT_HDR_OPT_TYPE_PAD_N: /* PadN option */
        /* ignore padding data (2 + N byte padding) */
        break;

      default:
        if (E_OK != IpV6_VHandleUnknownTlvOption(LocalAddrV6Idx, DataPtr, DataLen, optOfs))
        {
          /* we have to discard the packet */
          IPV6_DBG_COUNTER_RX_INC(DropUknOpt);
          Result = E_NOT_OK;
        }
        break;
      }
    }

    if (Result == E_NOT_OK)
    {
      /* if unknown option, exit loop */
      break;
    }

    optOfs += IPV6_TLV_OPT_DATA_OFFS + OptDataLen; /* skip to next option */
  }
  return Result;
}
#endif /* (IPV6_VENABLE_DESTINATION_OPT_EXT_HDR_SKIPPING != STD_ON) */

/**********************************************************************************************************************
 *  IpV6_Ip_VProcessUdpHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VProcessUdpHeader(
  TcpIp_SizeOfIpV6CtrlType                 IpCtrlIdx,
  TcpIp_SizeOfLocalAddrV6Type              LocalAddrV6Idx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   ThisHdrOfs,
  uint16                                   DataLen,
  boolean                                  ChecksumVerified)
{
  /* generic socket address structures for passing packets to UDP */
  TcpIp_SockAddrBaseType SrcSockAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  IpV6_AddrType srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  IpV6_AddrType destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  IpBase_PortType srcPort;
  IpBase_PortType tgtPort;

#if (TCPIP_SUPPORT_DHCPV6 == STD_OFF)
  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  /* #10 If Udp packet is from DhcpV6 server, invoke DhcpV6 rx indication routine, else
   * invoke Udp rx indicationcopy source and destination address */
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(destAddr, DataPtr[IPV6_HDR_OFF_DSTADDR]);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(srcAddr, DataPtr[IPV6_HDR_OFF_SRCADDR]);
  srcPort = TCPIP_GET_UINT16(DataPtr, ThisHdrOfs);
  tgtPort = TCPIP_GET_UINT16(DataPtr, ThisHdrOfs + UDP_HDR_OFF_TGTPORT);

  if (!IPV6_ADDR_IS_UNSPECIFIED(srcAddr))
  {
    SrcSockAddr.SockAddrIn6.sin6_family = IPBASE_AF_INET6;
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(SrcSockAddr.SockAddrIn6.sin6_addr, srcAddr);

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
    if (   (srcPort == TCPIP_DHCPV6_SERVER_PORT)
        && (tgtPort == TCPIP_DHCPV6_CLIENT_PORT))
    {
      /* This is a packet from a DHCPv6 server for a DHCPv6 client. */
      TcpIp_DhcpV6_RxIndication(IpCtrlIdx, &DataPtr[ThisHdrOfs], DataLen - ThisHdrOfs,
        ChecksumVerified,
        &srcAddr,
        &destAddr
      );
    }
    else
#endif
    {
      (void)TcpIp_Udp_RxIndication(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(LocalAddrV6Idx),
        &SrcSockAddr,
        &DataPtr[ThisHdrOfs], DataLen - ThisHdrOfs,
        ChecksumVerified
        );
    }
  }
  else
  {
    /* UDP packets sent from unspecified address [::] or sent to a multicast address are invalid. */
    /* ignore packet */
    /* Packet dropped due to invalid source address */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
    TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4);
#endif
  }
  return;
}  /* PRQA S 6060 */ /* MD_MSR_STPAR */

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VProcessTcpHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VProcessTcpHeader(
  TcpIp_LocalAddrV6IterType                LocalAddrV6Idx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   ThisHdrOfs,
  uint16                                   DataLen,
  boolean                                  ChecksumVerified)
{
  IpV6_AddrType  srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

  /*#10 Invoke Tcp rx indication routine */
  /* generic socket address structures for passing packets to TCP */
  TcpIp_SockAddrBaseType SrcSockAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(srcAddr, DataPtr[IPV6_HDR_OFF_SRCADDR]);

  if (   (!IPV6_ADDR_IS_UNSPECIFIED(srcAddr)) /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE))
  {
    SrcSockAddr.SockAddrIn6.sin6_family = IPBASE_AF_INET6;
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(SrcSockAddr.SockAddrIn6.sin6_addr, srcAddr);

    TcpIp_Tcp_RxIndication(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(LocalAddrV6Idx), &SrcSockAddr,
      &DataPtr[ThisHdrOfs], (DataLen - ThisHdrOfs), ChecksumVerified);
  }
  else
  {
    /* TCP packets sent from unspecified address [::] or sent to a multicast address are invalid. */
    /* ignore packet */
    /* Packet dropped due to invalid source address */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
    TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4);
#endif
  }
  return;
}
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VProcessExtHeaders()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_Ip_VProcessExtHeaders(
  TcpIp_SizeOfIpV6CtrlType                  IpCtrlIdx,
  TcpIp_SizeOfLocalAddrV6Type               LocalAddrV6Idx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) PhysAddrPtr,
  boolean                                   IsReassembledPacket)
{
  uint16                 dataLen;     /* length of the IPv6 packet in bytes */
  uint16                 thisHdrOfs = IPV6_HDR_LEN;  /* offset of the current header relative to DataPtr */
  uint16                 prevHdrOfs = 0;  /* offset of the previous header relative to DataPtr */
#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
  /* position of the Next Header field of the current header relative to EthDataPtr */
  uint16                 nxtHdrFieldOfs = IPV6_HEADER_NXT_HDR_FIELD_OFFS;
#endif

  uint8                  nextHdrValue;  /* holds next header type value */
  uint16                 hdrLenCalculated; /* contains the length of the currently parsed header */
  uint16                 payloadLenNbo;

  /* If the frame is a reassembled packet, checksum has to be verified by SW all the time */
  boolean checksumVerified = (IsReassembledPacket == TRUE)? FALSE : TRUE;

  /* copy payload length from header */
  payloadLenNbo = TCPIP_GET_UINT16_RAW(DataPtr, IPV6_HDR_OFF_PAYLOADLENNBO);
  dataLen = IPV6_HDR_LEN + TCPIP_NTOHS(payloadLenNbo);
  /* read extension or uppler-layer headers */
  nextHdrValue = DataPtr[IPV6_HDR_OFF_NEXTHDR];

  /*#10 Process the IpV6 extension headers until all headers are processed */
  do
  {
    uint16                 thisHdrLen = 0;

    /* ignore packet if end of payload is reached and we're expecting a next header */
    if (thisHdrOfs >= dataLen)
    {
      /* Packet dropped due to invalid extension header */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6);
#endif
      IPV6_DBG_COUNTER_RX_INC(DropInvNxtHdr);
      nextHdrValue = IPV6_HDR_ID_NO_NEXT_HDR;
      TCPIP_DUMMY_STATEMENT(thisHdrLen);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    }
    else
    {
      Std_ReturnType  result = E_OK;

      switch (nextHdrValue)
      {
        /***********************************************
         * Extension Header: Hop-by-Hop                *
         ***********************************************/
      case IPV6_EXT_HDR_ID_HOP_BY_HOP:
        {
          uint16 optLenByte = (uint16)DataPtr[thisHdrOfs + 1u];
          nextHdrValue = DataPtr[thisHdrOfs];
          thisHdrLen = IPV6_CALC_EXT_HEADER_LENGTH(optLenByte);

          /* this header (when present) MUST immediately follow the IPv6 header (see RFC2460 4. IPv6 Extension Headers) */
          if (IPV6_HDR_LEN != thisHdrOfs)
          {
#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
            IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_UNKNOWN_NXT_HDR,
              DataPtr, dataLen, nxtHdrFieldOfs);
#endif
            result = E_NOT_OK;
            IPV6_DBG_COUNTER_RX_INC(DropHdrOrder);
          }
          /* ignore packet if hop by hop header length exceeds remaining payload length */
          else if ((thisHdrOfs + thisHdrLen) > dataLen)
          {
            result = E_NOT_OK;
            IPV6_DBG_COUNTER_RX_INC(DropInvNxtHdrLen);
          }
          else
          {

#if (IPV6_VENABLE_HOP_BY_HOP_EXT_HDR_SKIPPING != STD_ON)
            result = IpV6_Ip_VProcessHopByHopOptions(LocalAddrV6Idx, DataPtr, thisHdrOfs, thisHdrLen, dataLen);
#endif /* (IPV6_VENABLE_HOP_BY_HOP_EXT_HDR_SKIPPING != STD_ON) */
          }
        }
        break;

      /***********************************************
       * Extension Header: Destination Options       *
       ***********************************************/
      case IPV6_EXT_HDR_ID_DST_OPT:
        {
          uint16 optLenByte = (uint16)DataPtr[thisHdrOfs + 1u];
          nextHdrValue = DataPtr[thisHdrOfs];
          thisHdrLen = IPV6_CALC_EXT_HEADER_LENGTH(optLenByte);

          /* ignore packet if destination options header length exceeds remaining payload length */
          if ((thisHdrOfs + thisHdrLen) > dataLen)
          {
            result = E_NOT_OK;
            IPV6_DBG_COUNTER_RX_INC(DropInvNxtHdrLen);
          }
          else
          {
#if (IPV6_VENABLE_DESTINATION_OPT_EXT_HDR_SKIPPING != STD_ON)
            result = IpV6_Ip_VProcessDstOptions(LocalAddrV6Idx, DataPtr, thisHdrOfs, thisHdrLen, dataLen);
#endif /* (IPV6_VENABLE_DESTINATION_OPT_EXT_HDR_SKIPPING != STD_ON) */
          }
        }
        break;

      /***********************************************
       * Extension Header: Routing                   *
       ***********************************************/
      case IPV6_EXT_HDR_ID_ROUTING:
        {
          uint16 optLenByte = (uint16)DataPtr[thisHdrOfs + 1u];
          nextHdrValue = DataPtr[thisHdrOfs];
          thisHdrLen = IPV6_CALC_EXT_HEADER_LENGTH(optLenByte);

          /* [RFC2460 4.4.] */
          /* we do not have support for any Routing Type, so this field contains always an unrecognized type */

          /* ignore packet if routing header length exceeds remaining payload length */
          if ((thisHdrOfs + thisHdrLen) > dataLen)
          {
            result = E_NOT_OK;
            IPV6_DBG_COUNTER_RX_INC(DropInvNxtHdrLen);
          }
          else if (0u == DataPtr[thisHdrOfs + 3u]) /* Segments Left */
          {
            /* We have to ignore the routing header and proceed to the next header */
          }
          else /* Segments Left is non-zero */
          {
            /* We have to discard the packet and send an ICMP Parameter Problem message (Code 0)
              * pointing to the unrecognized Routing Type
              */
#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
            IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_ERR_HDR_FIELD,
              DataPtr, dataLen, thisHdrOfs + 2u);
#endif
            result = E_NOT_OK;
          }

          if (TcpIp_IsHwChecksumIpRoutingOfIpV6Ctrl(IpCtrlIdx) == FALSE)
          {
            checksumVerified = FALSE;
          }
        }
        break;

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
      /***********************************************
       * Extension Header: Fragment                  *
       ***********************************************/
      case IPV6_EXT_HDR_ID_FRAGMENT:
        {
          TcpIp_SizeOfIpV6FragmentationConfigType ipV6FragConfigIdx = TcpIp_GetIpV6FragmentationConfigIdxOfIpV6Ctrl(IpCtrlIdx);
          /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          if ((IpV6_Ip_VFragLenValidate(LocalAddrV6Idx, DataPtr, dataLen, thisHdrOfs) == E_OK)
            && ((TcpIp_IsIpV6FragmentationConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE)
              && (TcpIp_GetReassemblyBufferCountOfIpV6FragmentationConfig(ipV6FragConfigIdx) > 0u)))
          {
            (void)IpV6_VProcessFragmentHeader(LocalAddrV6Idx, DataPtr, dataLen, thisHdrOfs, prevHdrOfs);
          }
          /* Stop processing of fragmented packet here.
           * Other headers will be processed if all fragments haven been reassembled.
           */
          nextHdrValue = IPV6_HDR_ID_NO_NEXT_HDR;
          thisHdrLen = IPV6_FRAGMENT_EXT_HDR_LEN; /* fixed length */
        }
        break;
#endif

      /***********************************************
       * Extension Header: AH                        *
       ***********************************************/
      case IPV6_EXT_HDR_ID_AUTH:
        {
          result = E_NOT_OK;
          checksumVerified = FALSE;  /* if IPSec is used no upper layer checksums can be calculated in HW */
        }
        break;

      /***********************************************
       * Extension Header: ESP                       *
       ***********************************************/
      case IPV6_EXT_HDR_ID_ESP:
        {
          result = E_NOT_OK;
          checksumVerified = FALSE;  /* if IPSec is used no upper layer checksums can be calculated in HW */
        }
        break;

      /***********************************************
       * Upper Layer Header: ICMP                    *
       ***********************************************/
      case IPV6_HDR_ID_ICMP:
        {
          if (TcpIp_IsHwChecksumIcmpOfIpV6Ctrl(IpCtrlIdx) == FALSE)
          {
            checksumVerified = FALSE;
          }

          IpV6_Icmp_RxIndication(LocalAddrV6Idx, DataPtr, dataLen, PhysAddrPtr, thisHdrOfs, checksumVerified);
          nextHdrValue = IPV6_HDR_ID_NO_NEXT_HDR;
          thisHdrLen = 0;
        }
        break;

#if (TCPIP_SUPPORT_TCP == STD_ON)
      /***********************************************
       * Upper Layer Header: TCP                     *
       ***********************************************/
      case IPV6_HDR_ID_TCP:
        {
          if (TcpIp_IsHwChecksumTcpOfIpV6Ctrl(IpCtrlIdx) == FALSE)
          {
            /* If HW checksum offloading is not enabled, set flag to FALSE */
            checksumVerified = FALSE;
          }

          IpV6_Ip_VProcessTcpHeader(LocalAddrV6Idx, DataPtr, thisHdrOfs, dataLen, checksumVerified);
          nextHdrValue = IPV6_HDR_ID_NO_NEXT_HDR;
          thisHdrLen = 0;
        }
        break;
#endif /* (TCPIP_SUPPORT_TCP == STD_ON) */

      /***********************************************
       * Upper Layer Header: UDP                     *
       ***********************************************/
      case IPV6_HDR_ID_UDP:
        {
          if (TcpIp_IsHwChecksumUdpOfIpV6Ctrl(IpCtrlIdx) == FALSE)
          {
            /* If HW checksum offloading is not enabled, set flag to FALSE */
            checksumVerified = FALSE;
          }

          IpV6_Ip_VProcessUdpHeader(IpCtrlIdx, LocalAddrV6Idx, DataPtr, thisHdrOfs, dataLen, checksumVerified);
          nextHdrValue = IPV6_HDR_ID_NO_NEXT_HDR;
          thisHdrLen = 0;
        }
        break;

      /***********************************************
       *                NO NEXT HEADER               *
       ***********************************************/
      case IPV6_HDR_ID_NO_NEXT_HDR:
        {
          /* packet doesn't contain any payload */
          thisHdrLen = 0;
          nextHdrValue = IPV6_HDR_ID_NO_NEXT_HDR;
        }
        break;

      /***********************************************
       *              UNSUPPORTED HEADER             *
       ***********************************************/
      default:
        {
          /* Unknown header found. We should send an ICMP Parameter Problem message Code 1 according to RFC2460 4. */

#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
          IpV6_Icmp_VTxErrParameterProblem(LocalAddrV6Idx, IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_UNKNOWN_NXT_HDR,
            DataPtr, dataLen, nxtHdrFieldOfs);
#endif
          result = E_NOT_OK;
        }
        break;
      }

      if (result == E_NOT_OK)
      {
        /* Packet dropped due to invalid extension header */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
        TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6);
#endif
        nextHdrValue = IPV6_HDR_ID_NO_NEXT_HDR; /* stop processing */
        hdrLenCalculated = 0;
      }
      else
      {
        hdrLenCalculated = thisHdrLen;
      }

#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
      nxtHdrFieldOfs = thisHdrOfs;
#endif

      /* move to next header */
      prevHdrOfs = thisHdrOfs;
      thisHdrOfs += hdrLenCalculated;
    }
  } while (IPV6_HDR_ID_NO_NEXT_HDR != nextHdrValue);
} /* IpV6_Ip_VProcessExtHeaders() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV6_RxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_RxIndication(
  uint8                                    CtrlIdx,
  Eth_FrameType                            FrameType,
  boolean                                  IsBroadcast,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) PhysAddrPtr, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   LenByte)
{

  IPV6_UNUSED_PARAMETER(FrameType);    /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  IPV6_UNUSED_PARAMETER(IsBroadcast);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Invoke the internal IpV6 Rx indication */
  IpV6_RxIndication_Internal(CtrlIdx, PhysAddrPtr, DataPtr, LenByte, FALSE);
} /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV6_RxIndication_Internal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_RxIndication_Internal(
  uint8                                    EthIfCtrlIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) PhysAddrPtr, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   LenByte,
  boolean                                  IsReassembledPacket)
{
  Std_ReturnType                    result = E_OK;
  TcpIp_SizeOfIpV6CtrlType          ipCtrlIdx;           /* ip controller index */
  TcpIp_SizeOfLocalAddrV6Type       localAddrV6Idx;      /* ip address identifier */

  IpV6_HdrType ipV6Hdr;

  TCPIP_ASSERT(DataPtr != NULL_PTR);

  /* #10 Copy IpV6 header fields from packet */
  ipV6Hdr.VersionTcFlNbo = TCPIP_GET_UINT32_RAW(DataPtr, IPV6_HDR_OFF_VERSIONTCFLNBO);
  ipV6Hdr.PayloadLenNbo  = TCPIP_GET_UINT16_RAW(DataPtr, IPV6_HDR_OFF_PAYLOADLENNBO);
  ipV6Hdr.NextHdr        = TCPIP_GET_UINT8(DataPtr, IPV6_HDR_OFF_NEXTHDR);
  ipV6Hdr.HopLimit       = TCPIP_GET_UINT8(DataPtr, IPV6_HDR_OFF_HOPLIMIT);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(ipV6Hdr.DstAddr, DataPtr[IPV6_HDR_OFF_DSTADDR]);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(ipV6Hdr.SrcAddr, DataPtr[IPV6_HDR_OFF_SRCADDR]);

  if (TcpIp_IsIpV6CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == FALSE)
  {
    /* no IPv6 instance configured for this EthIf controller
     * discard packet
     */
  }
  else
  {
    ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);
    localAddrV6Idx = TCPIP_LOCAL_ADDR_V6_IDX_ANY;
    /* #20 Validate the IpV6 header fields */
    if (IPV6_CTRL_STATE_LINK_READY > TcpIp_GetCtrlStateOfIpV6CtrlDyn(ipCtrlIdx))
    {
      result = E_NOT_OK; /* ignore received packets until transceiver link is active */
    }
    /*
     * We do not have to verify the hop limit.
     * This would only be neccessary if we have to forward the packet.
     * Conformance Test v6LC.1.1.8: Hop Limit Zero - End Node checks this
     */

    /* Compare source address of the received packet with our own local (source) addresses.
     * Since the unspecified address [::] is not allowed for TCP/UDP packets but for
     * NDP packets, this check is done later.
     */
    else if (IpV6_Ip_VCheckIPv6HeaderValid(ipCtrlIdx, &localAddrV6Idx, &ipV6Hdr, PhysAddrPtr, LenByte) == E_NOT_OK)
    {
      result = E_NOT_OK;
    }
    else if (localAddrV6Idx != TCPIP_LOCAL_ADDR_V6_IDX_ANY)
    {

      TCPIP_ASSERT(TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(localAddrV6Idx) || TcpIp_IsIpV6MulticastAddrUsedOfLocalAddrV6(localAddrV6Idx));
      TcpIp_SetLastBcAddrPtrOfIpV6CtrlDyn(ipCtrlIdx, NULL_PTR);
    }
    else
    {
      /* all-nodes multicast destination */
      localAddrV6Idx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(ipCtrlIdx);
      TcpIp_SetLastBcAddrPtrOfIpV6CtrlDyn(ipCtrlIdx, &ipV6Hdr.DstAddr);
      IPV6_DBG_COUNTER_RX_INC(RxMulticast);
    }

    /***********************************************
     *        Extension HEADER Processing          *
     ***********************************************/
    /* #30 Process the extension headers if IpV6 headers are valid */
    if (result == E_OK)
    {
      TCPIP_ASSERT(localAddrV6Idx != TcpIp_GetSizeOfLocalAddrV6());
      IpV6_Ip_VProcessExtHeaders(ipCtrlIdx, localAddrV6Idx, DataPtr, PhysAddrPtr, IsReassembledPacket);
    }
  }
} /* End of IpV6_RxIndication_Internal() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_TxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_TxConfirmation(
  uint8 EthIfCtrlIdx,
  uint8 BufIdx)
{
  /* #10 Invoke Udp tx confirmation routine */
  if (TcpIp_IsIpV6CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE)
  {
    TcpIp_SizeOfIpV6CtrlType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);
    TcpIp_SizeOfIpV6EthBufDataType ipV6EthBufDataIdx = TcpIp_GetIpV6EthBufDataStartIdxOfIpV6Ctrl(ipCtrlIdx) + BufIdx;

    TCPIP_ASSERT(ipV6EthBufDataIdx <  TcpIp_GetIpV6EthBufDataEndIdxOfIpV6Ctrl(ipCtrlIdx));

    TcpIp_Udp_TxConfirmation(TcpIp_GetIpV6SocketDynIdxOfIpV6EthBufData(ipV6EthBufDataIdx),
      TcpIp_GetUlTxReqTabIdxOfIpV6EthBufData(ipV6EthBufDataIdx));
  }
} /* End of IpV6_TxConfirmation() */


/**********************************************************************************************************************
 *  IpV6_Cbk_TrcvLinkStateChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Cbk_TrcvLinkStateChg(
  uint8                 CtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Currently this function has no functionality, thus simply return. */
  TCPIP_DUMMY_STATEMENT(CtrlIdx);        /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  TCPIP_DUMMY_STATEMENT(TrcvLinkState);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

} /* End of IpV6_Cbk_TrcvLinkStateChg() */

/**********************************************************************************************************************
 *  IpV6_TrcvLinkStateChgInternal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV6_TrcvLinkStateChgInternal(
  uint8                 EthIfCtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState)
{
  /* #10 Check if IP instance is configured for this controller */
  if (TcpIp_IsIpV6CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE)
  {
    TcpIp_SizeOfIpV6CtrlType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);

    if (ETHTRCV_LINK_STATE_ACTIVE != TrcvLinkState)
    {
      /* LINK DOWN */
      /* #20 Invoke shutdown routine if link state is down */
      IpV6_VCtrlStateShutdown(ipCtrlIdx);
    }
    else
    {
      /* LINK UP */
      /* #30 Invoke startup routine if link state is up */
      IpV6_VCtrlStateStartup(ipCtrlIdx);
    }
  }
} /* End of IpV6_TrcvLinkStateChgInternal() */



/**********************************************************************************************************************
 *  IpV6_Ip_RequestIpAddrAssignment
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) IpV6_Ip_RequestIpAddrAssignment(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx,
  TcpIp_IpAddrAssignmentType  Type,
  TCPIP_P2C(IpV6_AddrType)    LocalIpAddrPtr,
  uint8                       Netmask,
  TCPIP_P2C(IpV6_AddrType)    DefaultRouterPtr)
{
  Std_ReturnType RetVal = E_NOT_OK;
  TcpIp_IpV6CtrlIterType ipCtrlIdx;

  IPV6_UNUSED_PARAMETER(Netmask);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  if (TcpIp_GetCtrlStateOfIpV6CtrlDyn(ipCtrlIdx) > IPV6_CTRL_STATE_INIT)
  {
    /* #10 Set address statically if static address assignment is selected */
    if (Type == TCPIP_IPADDR_ASSIGNMENT_STATIC)
    {
      uint32  preferredLifetime = IPV6_LIFETIME_UNLIMITED;
      uint32  validLifetime     = IPV6_LIFETIME_UNLIMITED;
      boolean NoDad             = FALSE;
      RetVal = IpV6_SetAddress(LocalAddrV6Idx, LocalIpAddrPtr, preferredLifetime, validLifetime, NoDad);

      /* #20 Use manual or configurated default router value */
      if (RetVal == E_OK)
      {
        IpV6_SelectDefaultRouterConfigAndCreateEntry(LocalAddrV6Idx, DefaultRouterPtr);
      }
    }
#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
    /* #30 Request for dhcpV6 address assignment if dhcp assignment is selected */
    else if (Type == TCPIP_IPADDR_ASSIGNMENT_DHCP)
    {
      if (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE)
      {
        TcpIp_IpV6SourceAddressIterType ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
        /* Trigger address assignment only if the Ip address index is Dhcp configurable */
        if (TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(ipV6SrcAddrIdx) == TCPIP_IPADDR_ASSIGNMENT_DHCP)
        {
          TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

          /* trigger DHCPv6 address assignment */
          TcpIp_DhcpV6_StartAddressAssignment(ipCtrlIdx);
          RetVal = E_OK;
        }
      }
    }
#endif
    else
    {
      /* RetVal remains E_NOT_OK */
    }
  }
  else
  {
    /* offline, no address assignment can be triggered */
    /* RetVal remains E_NOT_OK */
  }

  return RetVal;
} /* IpV6_Ip_RequestIpAddrAssignment() */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV6_Ip_VUpdateValidSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VUpdateValidSourceAddress(
  TcpIp_SizeOfLocalAddrV6Type                        LocalAddrV6Idx,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr)
{
  TcpIp_SizeOfIpV6SourceAddressType srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
  TCPIP_P2V(IpV6_SourceAddressTableEntryType) srcAddrPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx);

  /* #10 Compare the current SAT entry with the provided address */
  if (TRUE == IpV6_CmpNetAddr(AddressPtr, &srcAddrPtr->Address))
  {
    /* #20 If address has not changed, just update lifetimes */

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    if (IPV6_LADDR_STATE_TENTATIVE == srcAddrPtr->State)
    {
      /* do not update next event time here, if Duplicate Address Detection is still in progress */
      IPV6_SET_LIFETIME_S(srcAddrPtr->PreferredTime, PreferredLifetime, NULL_PTR);
      IPV6_SET_LIFETIME_S(srcAddrPtr->ValidTime,     ValidLifetime,     NULL_PTR);
    }
    else
#endif
    {
      /* This address is already configured, so we just need to update the lifetimes */
      IPV6_SET_LIFETIME_S(srcAddrPtr->PreferredTime, PreferredLifetime, &srcAddrPtr->NextEventTime);
      IPV6_SET_LIFETIME_S(srcAddrPtr->ValidTime,     ValidLifetime,     &srcAddrPtr->NextEventTime);
    }
  }
  else
  {
    /* #30 If address has changed, unassign the address and remove the old SAT entry */
    IpV6_VHandleSourceAddrAssignmentChange(srcAddrIdx, FALSE);
    IpV6_VSATRemoveEntry(srcAddrIdx); /* changes state to IPV6_LADDR_STATE_INVALID */
  }
  return E_OK;
}

#if (TCPIP_SUPPORT_IPV6_NVM_ADDR_STORAGE == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ip_VNvmSetAddress
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VNvmSetAddress(
  TcpIp_IpV6SourceAddressTableEntryIterType  IpV6SrcAddrIdx,
  TCPIP_P2C(IpV6_AddrType)                   AddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
 TcpIp_SizeOfNvmDataType  nvmDataIdx;
  Std_ReturnType          retVal    = E_OK;
  uint8                   nvMStatus = NVM_REQ_PENDING;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_IsNvmDataUsedOfIpV6SourceAddress(IpV6SrcAddrIdx) == TRUE);

  nvmDataIdx = TcpIp_GetNvmDataIdxOfIpV6SourceAddress(IpV6SrcAddrIdx);

  /* #10 Update the error status of the NvM block */
  (void)NvM_GetErrorStatus((NvM_BlockIdType) TCPIP_NVM_BLOCK_ID, &nvMStatus);

  if (NVM_REQ_PENDING == nvMStatus)
  {
    /* #20 If any previous NvM operation is pending, return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  else
  {
    /* #30 If not pending, store the new address into the Nvm address block */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrNvmData(nvmDataIdx)->data[0], *AddrPtr);

    /* #40 Signal the NvM that the value of the permanent RAM block has been changed */
    (void)NvM_SetRamBlockStatus((NvM_BlockIdType) TCPIP_NVM_BLOCK_ID, TRUE);
  }

  return retVal;
}
#endif

/**********************************************************************************************************************
 *  IpV6_Ip_VAddNewSourceAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VAddNewSourceAddress(
  TcpIp_SizeOfIpV6SourceAddressType                  IpV6SrcAddrIdx,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr,
  boolean                                            NoDad)
{
  Std_ReturnType Result = E_OK;

  /* #10 Add address to source address table if a valid address has been specified */
  if (!IPV6_ADDR_IS_UNSPECIFIED(*AddressPtr))
  {
    Result = IpV6_Ndp_VAddSourceAddress(IpV6SrcAddrIdx, AddressPtr, PreferredLifetime, ValidLifetime, 0,
                  (TRUE == NoDad) ? IPV6_SRC_ADDR_DAD_MODE_NONE : IPV6_SRC_ADDR_DAD_MODE_OPTIMISTIC);
  }
#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
  /* #20 Otherwise, if dhcpv6 is enabled, perform dhcp reset to reset the dhcp state */
  else
  {
    TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
    TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

    if (TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      (void)TcpIp_DhcpV6_Reset(ipCtrlIdx);
    }
  }
#endif

#if (TCPIP_SUPPORT_IPV6_NVM_ADDR_STORAGE == STD_ON)
  /* #30 Check if the new source address was successfully added into the SAT */
  if (E_OK == Result)
  {
    /* #40 Check If Nvm block has been configured for the source address index */
    if (TcpIp_IsNvmDataUsedOfIpV6SourceAddress(IpV6SrcAddrIdx) == TRUE)
    {
      /* #50 Set the new address in the NvM block */
      Result = IpV6_Ip_VNvmSetAddress(IpV6SrcAddrIdx, AddressPtr);
    }
  }
#endif
  return Result;
} /* IpV6_Ip_VAddNewSourceAddress() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ip_VSetUnicastAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VSetUnicastAddress(
  TcpIp_SizeOfLocalAddrV6Type                        LocalAddrV6Idx,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr,
  boolean                                            NoDad)
{
  Std_ReturnType Result = E_OK;
  TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
  TCPIP_P2C(IpV6_SourceAddressTableEntryType) srcAddrPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx);
  TCPIP_P2C(IpV6_AddrType) addrLocalPtr;
  uint32 preferredLt, validLt;

  /* Set Unicast address */
  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if ((TCPIP_IPADDR_ASSIGNMENT_STATIC != TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(ipV6SrcAddrIdx)) &&
      (TCPIP_IPADDR_ASSIGNMENT_DHCP   != TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(ipV6SrcAddrIdx)))
  {
    /* only STATIC and DHCP addresses can be changed via this api */
    Result = E_NOT_OK;
  }
  else
  {
    /* #10 Check if an address has been specified, set address to default address if available
     *     else assign unspecified address */
    if (NULL_PTR == AddressPtr)
    {
      /* Set default address (if available) or unspecified address */
      if (TcpIp_IsDefaultAddrV6UsedOfIpV6SourceAddress(ipV6SrcAddrIdx) == TRUE)
      {
        TcpIp_SizeOfDefaultAddrV6Type defaultAddrIdx = TcpIp_GetDefaultAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);
        addrLocalPtr = TcpIp_GetAddrDefaultAddrV6(defaultAddrIdx);
      }
      else
      {
        addrLocalPtr = &IpV6_AddrUnspecified;
      }

      preferredLt = IPV6_LIFETIME_UNLIMITED;
      validLt     = IPV6_LIFETIME_UNLIMITED;
    }
    else
    {
      addrLocalPtr = AddressPtr;
      preferredLt = PreferredLifetime;
      validLt     = ValidLifetime;
    }

    IPV6_BEGIN_CRITICAL_SECTION_SAT();

    /* #20 If the current SAT entry is already in a valid state, the update the entry with the new parameters */
    if (IPV6_LADDR_STATE_INVALID != srcAddrPtr->State)
    {
      Result = IpV6_Ip_VUpdateValidSourceAddress(LocalAddrV6Idx, preferredLt, validLt, (const IpV6_AddrType*) addrLocalPtr);
    }

    /* #30 If the current SAT entry is in invalid state, add a new SAT entry with the new parameters */
    /* Current SAT entry may be invalid due to
     * (1) address of the entry has been updated (or released)
     * (2) the SAT entry has not been configured yet (in case of DHCP address assignment is in progress)
     * For case (1), the invalid SAT entry is overwritten with new parameters
     * For case (2), dhcp state must be reset
     */
    if (IPV6_LADDR_STATE_INVALID == srcAddrPtr->State)
    {
      Result = IpV6_Ip_VAddNewSourceAddress(ipV6SrcAddrIdx, preferredLt, validLt, (const IpV6_AddrType*) addrLocalPtr, NoDad);
    }

    IPV6_END_CRITICAL_SECTION_SAT();
  }
  return Result;
} /* IpV6_Ip_VSetUnicastAddress() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ip_VSetMulticastAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ip_VSetMulticastAddress(
  TcpIp_IpV6MulticastAddrIterType IpV6MulticastAddrIdx,
  TCPIP_P2C(IpV6_AddrType)        AddressPtr)
{
  Std_ReturnType           Result = E_OK;
  TCPIP_P2C(IpV6_AddrType) addrLocalPtr;

  if (NULL_PTR == AddressPtr)
  {
    /* Set default address */
    if (TcpIp_IsDefaultAddrV6UsedOfIpV6MulticastAddr(IpV6MulticastAddrIdx) == TRUE)
    {
      TcpIp_SizeOfDefaultAddrV6Type defaultAddrIdx = TcpIp_GetDefaultAddrV6IdxOfIpV6MulticastAddr(IpV6MulticastAddrIdx);

      addrLocalPtr = TcpIp_GetAddrDefaultAddrV6(defaultAddrIdx);
    }
    else
    {
      addrLocalPtr = &IpV6_AddrUnspecified;
    }
  }
  else
  {
    addrLocalPtr = AddressPtr;
  }

  if (IPV6_ADDR_IS_MULTICAST(*addrLocalPtr) || IPV6_ADDR_IS_UNSPECIFIED(*addrLocalPtr)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
  {
    /* OK: A multicast or the unspecified address shall be assigned. */

    /* #10 If multicast address is configured to be runtime changeable, update the
     * multicast address table with the new multicast address */
    if (TcpIp_IsIpV6MulticastAddrActiveUsedOfIpV6MulticastAddr(IpV6MulticastAddrIdx) == TRUE)
    {
      TcpIp_SizeOfIpV6MulticastAddrActiveType activeMcAddrIdx =
        TcpIp_GetIpV6MulticastAddrActiveIdxOfIpV6MulticastAddr(IpV6MulticastAddrIdx);

      if (!IPV6_ADDR_EQUALS(*TcpIp_GetAddrIpV6MulticastAddrActive(activeMcAddrIdx), *addrLocalPtr))
      {
        /* Change IP Address assignment */
        TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6MulticastAddr(IpV6MulticastAddrIdx);
#if (TCPIP_SUPPORT_IPV6_ETHIF_ADDR_FILTER_API == STD_ON)
        TcpIp_SizeOfIpV6CtrlType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);
#endif

        if (IPV6_ADDR_IS_MULTICAST(*TcpIp_GetAddrIpV6MulticastAddrActive(activeMcAddrIdx)))
        {
          /* There is curretly a different muticast assigned for this IpAddrId.
            * Notify upper-layer about removed assignment...
            */
          IPV6_VJOIN_MULTICAST_GROUP(ipCtrlIdx, TcpIp_GetAddrIpV6MulticastAddrActive(activeMcAddrIdx), FALSE);

          TcpIp_Cbk_VLocalIpAssignmentChg(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(localAddrV6Idx), TCPIP_IPADDR_STATE_UNASSIGNED);
        }

        /* Change IP address */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(*TcpIp_GetAddrIpV6MulticastAddrActive(activeMcAddrIdx), *addrLocalPtr);

        if (IPV6_ADDR_IS_MULTICAST(*TcpIp_GetAddrIpV6MulticastAddrActive(activeMcAddrIdx)))
        {
          /* A new address has been assigned for this IpAddrId.
            * Notify upper-layer...
            */
          IPV6_VJOIN_MULTICAST_GROUP(ipCtrlIdx, TcpIp_GetAddrIpV6MulticastAddrActive(activeMcAddrIdx), TRUE);

          TcpIp_Cbk_VLocalIpAssignmentChg(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(localAddrV6Idx), TCPIP_IPADDR_STATE_ASSIGNED);
        }
      }
      else
      {
        /* The value of *AddressPtr is already assigned to this IpAddrId. No action neccessary. */
        Result = E_OK;
      }
    }
    else
    {
      /* ERROR: The multicast address of this IpAddrId was not configured to be changeable during runtime. */
      Result = E_NOT_OK;
    }
  }
  else
  {
    /* ERROR: The value of *AddressPtr does not represent the unspecified [::] or a multicast address ff00::/8 */
    Result = E_NOT_OK;
  }

  return Result;
} /* IpV6_Ip_VSetMulticastAddress() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_SetAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_SetAddress(
  TcpIp_SizeOfLocalAddrV6Type                        LocalAddrV6Idx,
  P2CONST(IpV6_AddrType, AUTOMATIC, TCPIP_APPL_DATA) AddressPtr,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  boolean                                            NoDad)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  /* #10 Configure unicast or multicast address for given ip address index */
  if (ValidLifetime < PreferredLifetime)
  {
    /* #20 ValidLifetime must not be less than PrefrerredLifetime, return failure  */
    Result = E_NOT_OK;
  }
  else if (TCPIP_IPV6_ADDR_IDX_IS_ASAN(LocalAddrV6Idx)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* #30 Return failure if AutoSelect/Broadcast addresses is to be set */
    Result = E_NOT_OK;
  }
  else if (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE)
  {
    /* #40 configure unicast address with parameters passed */
    Result = IpV6_Ip_VSetUnicastAddress(LocalAddrV6Idx, PreferredLifetime, ValidLifetime, AddressPtr, NoDad);
  }
  else
  {
    /* #50 If address index is multicast Set Muticast address */
    TcpIp_SizeOfIpV6MulticastAddrType mcAddrIdx;

    TCPIP_ASSERT(TcpIp_IsIpV6MulticastAddrUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE);
    TCPIP_ASSERT((AddressPtr == NULL_PTR) || IPV6_ADDR_IS_MULTICAST(*AddressPtr) || IPV6_ADDR_IS_UNSPECIFIED(*AddressPtr));

    mcAddrIdx = TcpIp_GetIpV6MulticastAddrIdxOfLocalAddrV6(LocalAddrV6Idx);

    Result = IpV6_Ip_VSetMulticastAddress(mcAddrIdx, AddressPtr);
  }

  return Result;
} /* End of IpV6_SetAddress() */

/**********************************************************************************************************************
 *  IpV6_GetLocalAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_GetLocalAddress(
  TcpIp_LocalAddrV6IterType   LocalAddrV6Idx,
  IPV6_P2V(IpV6_AddrType)     AddressPtr,
  IPV6_P2V(uint8)             AddressPrefixBitLenPtr)
{
  Std_ReturnType         Result;
  TcpIp_SizeOfIpV6CtrlType ipCtrlIdx;
  uint8                  PrefixBitLen;

  TCPIP_ASSERT(LocalAddrV6Idx   < TcpIp_GetSizeOfLocalAddrV6()); /* why is this here? */
  TCPIP_ASSERT(AddressPtr != NULL_PTR);

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* #10 If autoselect address index is selected, assign last recieved all nodes multicast address */
  if (TCPIP_IPV6_ADDR_IDX_IS_ASAN(LocalAddrV6Idx)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* Return Last received all-nodes multicast address */
    if (TcpIp_GetLastBcAddrPtrOfIpV6CtrlDyn(ipCtrlIdx) != NULL_PTR)
    {
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(*AddressPtr, *TcpIp_GetLastBcAddrPtrOfIpV6CtrlDyn(ipCtrlIdx));
      Result = E_OK;
    }
    else
    {
      /* no all-nodes muticast received on this controller so far */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(*AddressPtr, IpV6_AddrAllNodesLL);
      Result = E_OK;
    }

    PrefixBitLen = IPV6_MULTICAST_PREFIX_LEN_BIT;
  }
  /* #20 If address index is unicast, return unicast ipv6 address if the source address
   *     table entry is valid */
  else if (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE)
  {
    /* Return unicast address */
    TcpIp_SizeOfIpV6SourceAddressType srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
    TCPIP_P2C(IpV6_SourceAddressTableEntryType) srcAddrPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx);

    IPV6_BEGIN_CRITICAL_SECTION_SAT();

    if (IPV6_LADDR_STATE_INVALID != srcAddrPtr->State)
    {
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(*AddressPtr, srcAddrPtr->Address);
      Result = E_OK;
    }
    else
    {
      /* There is currently no unicast address assigned to this AddrId */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(*AddressPtr, IpV6_AddrUnspecified);
      Result = E_OK;
    }

    /* Prefix of unicast address is always 64 bit. */
    PrefixBitLen = (IPV6_PREFIX_LEN_BYTE * IPV6_BITS_IN_BYTE);

    IPV6_END_CRITICAL_SECTION_SAT();
  }
  /* #30 If address index is not unicast, return dynamic multicast address if configured or default
   *     static address */
  else
  {
    /* Return multicast address */
    TcpIp_SizeOfIpV6MulticastAddrType ipV6MulticastAddrIdx = TcpIp_GetIpV6MulticastAddrIdxOfLocalAddrV6(LocalAddrV6Idx);

    if (TcpIp_IsIpV6MulticastAddrActiveUsedOfIpV6MulticastAddr(ipV6MulticastAddrIdx) == TRUE)
    {
      /* Return dynamic (runtime changeable) multicast address */
      TcpIp_SizeOfIpV6MulticastAddrActiveType mcAddrActiveIdx =
        TcpIp_GetIpV6MulticastAddrActiveIdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);

      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(*AddressPtr, *TcpIp_GetAddrIpV6MulticastAddrActive(mcAddrActiveIdx));
      PrefixBitLen = IPV6_MULTICAST_PREFIX_LEN_BIT;
      Result = E_OK;
    }
    else
    {
      /* Return static multicast address */
      TcpIp_SizeOfDefaultAddrV6Type defaultAddrIdx = TcpIp_GetDefaultAddrV6IdxOfIpV6MulticastAddr(ipV6MulticastAddrIdx);

      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(*AddressPtr, *TcpIp_GetAddrDefaultAddrV6(defaultAddrIdx));
      PrefixBitLen = IPV6_MULTICAST_PREFIX_LEN_BIT;
      Result = E_OK;
    }
  }

  if (AddressPrefixBitLenPtr != NULL_PTR)
  {
    *AddressPrefixBitLenPtr = PrefixBitLen;
  }

  return Result;
} /* End of IpV6_GetLocalAddress() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_GetDefaultRouterAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_GetDefaultRouterAddress(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2V(IpBase_AddrIn6Type) RouterAddressPtr,
  IPV6_P2V(boolean)            RouterIsReachablePtr)
{
  Std_ReturnType          retVal;
  TcpIp_SizeOfIpV6CtrlType ipCtrlIdx;
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(RouterAddressPtr     != NULL_PTR);
  TCPIP_ASSERT(RouterIsReachablePtr != NULL_PTR);

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* #10 Call internal service IpV6_VGetDefaultRouterAddr(). */

  IPV6_BEGIN_CRITICAL_SECTION_DRL();

  if (IpV6_VGetDefaultRouterAddr(ipCtrlIdx, LocalAddrV6Idx, NULL_PTR, RouterIsReachablePtr, &drlEntryIdx) != E_NOT_OK)
  {
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(*RouterAddressPtr, TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->NextHopAddress);
    retVal = E_OK;
  }
  else
  {
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(*RouterAddressPtr, IpV6_AddrUnspecified);
    retVal = E_NOT_OK;
  }

  IPV6_END_CRITICAL_SECTION_DRL();

  return retVal;
} /* IpV6_GetDefaultRouterAddress() */


/**********************************************************************************************************************
 *  IpV6_SetTrafficClass()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_SetTrafficClass(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint8                   TrafficClass)
{
  TcpIp_IpV6HdrVersionTcFlNboOfIpV6SocketDynType verTcFlValue = TcpIp_GetIpV6HdrVersionTcFlNboOfIpV6SocketDyn(IpV6SocketIdx);
  /* #10 Set the traffic class value in the IpV6 header */
  /* clear current 'Traffic Class' value */
  verTcFlValue &= ~(IPV6_HEADER_MASK_TRAFFIC_CLASS_NBO);
  /* set new 'Traffic Class' value */
  verTcFlValue |= (IPV6_HEADER_MASK_TRAFFIC_CLASS_NBO & TCPIP_HTONL((((uint32)TrafficClass) << IPV6_HEADER_TC_OFFS)));

  TcpIp_SetIpV6HdrVersionTcFlNboOfIpV6SocketDyn(IpV6SocketIdx, verTcFlValue);
  /* set use 'Traffic Class' flag */
  TcpIp_SetFlagsOfIpV6SocketDyn(IpV6SocketIdx, TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) | IPV6_SOCKET_DATA_FLAG_TRAFFIC_CLASS);

} /* End of IpV6_SetTrafficClass() */


/**********************************************************************************************************************
 *  IpV6_SetFlowLabel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_SetFlowLabel(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint32                  FlowLabel)
{
/* if (IPV6_ENABLE_TRAFFIC_CLASS_API == STD_ON) */
  TcpIp_IpV6HdrVersionTcFlNboOfIpV6SocketDynType verTcFlValue =
    TcpIp_GetIpV6HdrVersionTcFlNboOfIpV6SocketDyn(IpV6SocketIdx);

  /* #10 Set flow label field in the IpV6 header */
  verTcFlValue &= ~(IPV6_HEADER_MASK_FLOW_LABEL_NBO);                         /* clear current 'Flow Label' value */
  verTcFlValue |=  (IPV6_HEADER_MASK_FLOW_LABEL_NBO & TCPIP_HTONL(FlowLabel)); /* set new 'Flow Label' value */

  TcpIp_SetIpV6HdrVersionTcFlNboOfIpV6SocketDyn(IpV6SocketIdx, verTcFlValue);
  /* set use 'Flow Label' flag */
  TcpIp_SetFlagsOfIpV6SocketDyn(IpV6SocketIdx, TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) | IPV6_SOCKET_DATA_FLAG_FLOW_LABEL);

} /* End of IpV6_SetFlowLabel() */


/**********************************************************************************************************************
 *  IpV6_SetHopLimit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_SetHopLimit(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint8                   HopLimit)
{
  /* #10 Set hop limit field in the IpV6 header */
  TcpIp_SetHopLimitOfIpV6SocketDyn(IpV6SocketIdx, HopLimit);
  /* set use 'Hop Limit' flag */
  TcpIp_SetFlagsOfIpV6SocketDyn(IpV6SocketIdx, TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) | IPV6_SOCKET_DATA_FLAG_HOP_LIMIT);
} /* End of IpV6_SetHopLimit() */


/**********************************************************************************************************************
 *  IpV6_SetEthIfFramePrio()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_SetEthIfFramePrio(
  TcpIp_SocketDynIterType IpV6SocketIdx,
  uint8                   FramePrio)
{
  Std_ReturnType retVal;

  /* #10 Set ethernet priority flag in the IpV6 header */
  if (FramePrio <= IPV6_MAX_ETHIF_FRAME_PRIO)
  {
    TcpIp_SetEthIfFramePrioOfIpV6SocketDyn(IpV6SocketIdx, FramePrio);
    /* set use 'Frame Prio' flag */
    TcpIp_SetFlagsOfIpV6SocketDyn(IpV6SocketIdx, TcpIp_GetFlagsOfIpV6SocketDyn(IpV6SocketIdx) | IPV6_SOCKET_DATA_FLAG_ETHIF_FRAME_PRIO);
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* End of IpV6_SetEthIfFramePrio() */


/**********************************************************************************************************************
 *  IpV6_ResetSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_ResetSocket(
  TcpIp_IpV6SocketDynIterType IpV6SocketIdx)
{
  TcpIp_SetIpV6DestinationCacheEntryHintIdxOfIpV6SocketDyn(IpV6SocketIdx,
            TCPIP_NO_IPV6DESTINATIONCACHEENTRYHINTIDXOFIPV6SOCKETDYN);

  /* #10 Reset the parameters of the socket descriptor structure */
  TcpIp_SetEthIfFramePrioOfIpV6SocketDyn(IpV6SocketIdx, 0);
  TcpIp_SetHopLimitOfIpV6SocketDyn(IpV6SocketIdx, 0);

  TcpIp_SetIpV6HdrVersionTcFlNboOfIpV6SocketDyn(IpV6SocketIdx, IPV6_HEADER_VERSION_TC_FL_ZERO_NBO);

  TcpIp_SetFlagsOfIpV6SocketDyn(IpV6SocketIdx, 0);
} /* End of IpV6_SetFlowLabel() */


/**********************************************************************************************************************
 *  IpV6_IsValidDestinationAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, IPV6_CODE) IpV6_IsValidDestinationAddress(
  TcpIp_SizeOfIpV6CtrlType IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)  DstAddrPtr)
{
  boolean result = TRUE;
  IpV6_LocAddrStateType SrcAddrState;
  TcpIp_SizeOfIpV6SourceAddressTableEntryType srcAddrIdx;

  TCPIP_ASSERT(DstAddrPtr != NULL_PTR);

  /* #10 Check if the destination is valid to send packet */
  if (IPV6_ADDR_IS_MULTICAST(*DstAddrPtr) && (!IPV6_ADDR_MULTICAST_HAS_VALID_SCOPE(*DstAddrPtr)))
  {
    /* #20 Do not allow sending to multicast addresses with invalid scope */
    result = FALSE;
  }
  else if (IPV6_ADDR_IS_LOOPBACK(*DstAddrPtr))
  {
    result = FALSE;
  }
  else if (IPV6_ADDR_IS_UNSPECIFIED(*DstAddrPtr))
  {
    result = FALSE;
  }
  else
  {
    IPV6_BEGIN_CRITICAL_SECTION();
    if (TRUE == IpV6_VIsValidSourceAddress(IpCtrlIdx, DstAddrPtr, TRUE, &SrcAddrState, &srcAddrIdx))
    {
      /* #30 Do not allow sending packets to itself! */
      result = FALSE;
    }
    IPV6_END_CRITICAL_SECTION();
  }
  return result;
} /* End of IpV6_IsValidDestinationAddress() */


/**********************************************************************************************************************
 *  IpV6_GetLocalAddressCfgSrc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint8, IPV6_CODE) IpV6_GetLocalAddressCfgSrc(
  TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx)
{
  uint8 ipAddrCfgSrc;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  /* #10 Obtain the type of configuration for the given address index */
  if (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE)
  {
    /* Return configuration source of unicast address */
    TcpIp_SizeOfIpV6SourceAddressTableEntryType ipV6SrcAddrIdx =
      TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);

    ipAddrCfgSrc = TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(ipV6SrcAddrIdx);
  }
  else
  {
    /* Configuration source off All-Nodes and other multicast addresses is always STATIC */
    ipAddrCfgSrc = TCPIP_IPADDR_ASSIGNMENT_STATIC;
  }

  return ipAddrCfgSrc;
} /* End of IpV6_GetLocalAddressCfgSrc() */



/**********************************************************************************************************************
 *  IpV6_GetCurrentHopLimit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint8, IPV6_CODE) IpV6_GetCurrentHopLimit(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  /* #10 Obtain the current hop limit for the Ip controller */
  return TcpIp_GetCurHopLimitOfIpV6CtrlDyn(IpCtrlIdx);
} /* End of IpV6_GetCurrentHopLimit() */


/**********************************************************************************************************************
 *  IpV6_GetPhysAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_GetPhysAddr(
  TcpIp_IpV6CtrlIterType IpCtrlIdx,
  IPV6_P2V(uint8)        PhysAddrPtr)
{
  TCPIP_ASSERT(PhysAddrPtr != NULL_PTR);

  /* #10 Obtain physical address of the ethernet controller from the Ip controller index */
  TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), PhysAddrPtr);
} /* End of IpV6_GetPhysAddr() */

/**********************************************************************************************************************
 *  IpV6_GetPhysAddrByIpAddrId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) IpV6_GetPhysAddrByIpAddrId(
  TcpIp_LocalAddrV6IterType LocalAddrV6Idx,
  IPV6_P2V(uint8)           PhysAddrPtr)
{
  /* #10 Obtain physical address of the ethernet controller from the Ip adress index */
  IpV6_GetPhysAddr(TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx), PhysAddrPtr);
}

/**********************************************************************************************************************
 *  IpV6_GetRemotePhysAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_ReturnType, TCPIP_CODE) IpV6_GetRemotePhysAddr(
  TcpIp_SizeOfEthIfCtrlType EthIfCtrlIdx,
  TCPIP_P2C(IpV6_AddrType)  IpAddrPtr,
  TCPIP_P2V(uint8)          PhysAddrPtr,
  boolean                   InitRes)
{
  TcpIp_ReturnType        retVal;

  /* #10 Obtain the physical address of a remote destination from the neighbor cache */
  if (TcpIp_IsIpV6CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE)
  {
    if (IPV6_ADDR_IS_MULTICAST(*IpAddrPtr))
    {
      /* map IPv6 multicast address to ethernet multicast address according to RFC 2464 section 7 */
      IpV6_VMulticastAddr2LinkLayerAddr(PhysAddrPtr, IpAddrPtr);
      retVal = TCPIP_OK;
    }
    else
    {
      TcpIp_SizeOfIpV6CtrlType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);
      boolean entryFound = FALSE;
      TcpIp_SizeOfIpV6NeighborCacheEntryType ncEntryIdx;

      if (InitRes == TRUE)
      {
        /* get or create entry in the Neighbor Cache */
        IpV6_Ndp_VNCGetOrCreateEntry(ipCtrlIdx, IpAddrPtr, &ncEntryIdx);
        /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        if (   (ncEntryIdx >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(ipCtrlIdx))
            && (ncEntryIdx <  TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(ipCtrlIdx)))
        {
          entryFound = TRUE;
        }
      }
      else
      {
        /* lookup entry in Neighbor Cache */
        /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        if (   (E_OK == IpV6_Ndp_VNCLookup(ipCtrlIdx, IpAddrPtr, &ncEntryIdx))
            && (ncEntryIdx >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(ipCtrlIdx))
            && (ncEntryIdx <  TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(ipCtrlIdx)))
        {
          entryFound = TRUE;
        }
      }

      if ((entryFound == TRUE) && (TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State != IPV6_REACHABLE_STATE_INCOMPLETE))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      {
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_LL_ADDR_COPY(PhysAddrPtr, &TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LinkLayerAddress[0]);
        retVal = TCPIP_OK;
      }
      else
      {
        retVal = TCPIP_E_PHYS_ADDR_MISS;
      }
    }
  }
  else
  {
    /* no IPv6 instance configured for this EthIf controller */
    retVal = TCPIP_E_NOT_OK;
  }

  return retVal;
} /* End of IpV6_GetRemotePhysAddr() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_IsAddrIdAcceptable()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, IPV6_CODE) IpV6_IsAddrIdAcceptable(
  TcpIp_LocalAddrV6IterType   BindLocalAddrV6Idx,
  TcpIp_LocalAddrV6IterType   RecvLocalAddrV6Idx,
  IPV6_P2V(uint8)             MatchType)
{
  boolean result = FALSE;
  TCPIP_ASSERT((BindLocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6()) || BindLocalAddrV6Idx == TCPIP_LOCAL_ADDR_V6_IDX_ANY);
  TCPIP_ASSERT(RecvLocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  /* #10 Determine if two Ip address indexes match */
  if (BindLocalAddrV6Idx == TCPIP_LOCAL_ADDR_V6_IDX_ANY)
  {
    (*MatchType) = IPV6_ADDR_MATCH_EVER;
    result = TRUE;
  }
  else if (RecvLocalAddrV6Idx == BindLocalAddrV6Idx)
  {
    /* address matches filter address (exact match) */
    (*MatchType) = IPV6_ADDR_MATCH_EXACT;
    result = TRUE;
  }
  /* PRQA S 3415 1 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  else if (TCPIP_IPV6_ADDR_IDX_IS_ASAN(RecvLocalAddrV6Idx) || TCPIP_IPV6_ADDR_IDX_IS_ASAN(BindLocalAddrV6Idx))
  {
    /* bind or received address is an AutoSelect_Multicast address */
    if (TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(RecvLocalAddrV6Idx) == TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(BindLocalAddrV6Idx))
    {
      /* both addresses are on same controller If-match */
      (*MatchType) = IPV6_ADDR_MATCH_IF;
      result = TRUE;
    }
    else
    {
      (*MatchType) = IPV6_ADDR_MATCH_NONE;
    }
  }
  else
  {
    (*MatchType) = IPV6_ADDR_MATCH_NONE;
  }

  return result;
} /* End of IpV6_IsAddrIdAcceptable() */

/**********************************************************************************************************************
 *  IpV6_CreateStaticDefaultRouterEntry()
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_CreateStaticDefaultRouterEntry(
  TcpIp_LocalAddrV6IterType                             LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)                               RouterAddrPtr)
{
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntry; /* needed for out value */
  Std_ReturnType result;
  TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  TCPIP_ASSERT(RouterAddrPtr != NULL_PTR);
  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  /* #10 Check whether a entry already exist */
  result = IpV6_Ndp_VDRLLookup(ipCtrlIdx, RouterAddrPtr, &drlEntry, LocalAddrV6Idx);
  if (result == E_NOT_OK) /* result is E_NOT_OK when no entry exits */
  {
    /* #20 Create a new DRL entry and write values */
    TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx;
    if (E_OK == IpV6_Ndp_VDRLCreateEntry(ipCtrlIdx, RouterAddrPtr, &drlEntryIdx))
    {
      TcpIp_SizeOfIpV6NeighborCacheEntryType ncIdx;
      IpV6_Ndp_VNCGetOrCreateEntry(ipCtrlIdx, RouterAddrPtr, &ncIdx);
      IPV6_TIME_SET_INFINITY(TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->ExpireTime);
      TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->StaticEntry = TRUE;
      TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->NcIdxHint = ncIdx;
      TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->LocalIpV6Idx = (IpV6_AddrIdxType)LocalAddrV6Idx;
    }
  } /* else nothing is to do */
} /* End of IpV6_CreateStaticDefaultRouterEntry() */


/**********************************************************************************************************************
 *  IpV6_SelectDefaultRouterConfigAndCreateEntry()
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
TCPIP_LOCAL FUNC(void, IPV6_CODE) IpV6_SelectDefaultRouterConfigAndCreateEntry(
  TcpIp_LocalAddrV6IterType                             LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)                               DefaultRouterPtr)
{
  /* #10 Use manuel configurated default router as default */
  TCPIP_P2C(IpV6_AddrType) defaultRouterPtr = DefaultRouterPtr;
  /* #20 Else use static default router */
  if ((defaultRouterPtr == NULL_PTR) && (TcpIp_IsStaticDefaultRouterUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    defaultRouterPtr = TcpIp_GetAddrStaticDefaultRouter(TcpIp_GetStaticDefaultRouterIdxOfLocalAddrV6(LocalAddrV6Idx));
  }

  /* #30 Create default router entry for selected address */
  if (defaultRouterPtr != NULL_PTR)
  {
    IpV6_CreateStaticDefaultRouterEntry(LocalAddrV6Idx, defaultRouterPtr);
  }
} /* End of IpV6_SelectDefaultRouterConfigAndCreateEntry() */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

   MD_IPV6_Rule8.9_1533: An object should be defined at block scope if its identifier only appears in a single function
   Reason:     Some objects are defined keeping in mind future modifications and usage
   Risk:       None.
   Prevention: Covered by code review.

   MD_IPV6_Rule15.5_ComplexFunction: A function should have a single point of exit at the end
   Reason:      The API performs complex functionality. Refactoring the code not feasible at present.
   Risk:        None.
   Prevention:  Covered by code review.

   MD_IPV6_Rule8.3_3673: A pointer should point to a const-qualified type whenever possible
   Reason:      The parameter is modified by an internal function. This is a false warning.
   Risk:        None.
   Prevention:  Covered by code review.

   MD_TCPIP_Rule11.3_0310_Uint8ToEth_DataType: Casting to different object pointer type.
     Reason:     Casting from uint8 to Eth_DataType type. The EthIf_ProvideTxBuffer requires buffer pointer of
                 type Eth_DataType which is uint32.
     Risk:       Since the cast is from uint8 to uint32, unaligned memmory access will not happen.
     Prevention: Covered by code review.
*/

#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: IpV6.c
 *********************************************************************************************************************/
