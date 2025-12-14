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
 *         \file  TcpIp_Ndp.c
 *        \brief  Implementation of Neighbor Discovery Protocol (NDP) for IPv6
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

#define TCPIP_NDP_SOURCE

#include "TcpIp_Cfg.h"
#include "TcpIp.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_IpV6_Priv.h"
#include "TcpIp_IcmpV6.h"
#include "TcpIp_Ndp.h"
#include "TcpIp_Priv.h"

#include "EthIf.h"

#if (TCPIP_SUPPORT_NDP_OPT_RFC6106_RDNSS == STD_ON)
# include "Dns.h"
#endif

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (STATIC)
# define STATIC static
#endif

#define IPV6_NDP_ENABLE_LL_ADDR_GATHERING             STD_ON
#define IPV6_NDP_ENABLE_TIMEOUT_OPTIMIZATION          STD_OFF

#define IPV6_NDP_NA_FLAG_ROUTER    0x80u /* (1<<7) */
#define IPV6_NDP_NA_FLAG_SOLICITED 0x40u /* (1<<6) */
#define IPV6_NDP_NA_FLAG_OVERRIDE  0x20u /* (1<<5) */

typedef struct
{
  boolean Solicited;
  boolean Override;
  boolean Router;
  boolean TgtLLAddrChanged;
  boolean SrcLLAddrChanged;
} IpV6_NdpNaFlagsType;

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */

#define IPV6_NDP_CALC_OPTION_LENGTH(LENGTH) (8u * (LENGTH))

#define IPV6_NDP_OPT_INVALID_OFFSET   0x0U  /* invalid offset value for options */
#define IPV6_NDP_IS_OPT_INVALID(OptList, OptType)   (((OptList)[(OptType)] == IPV6_NDP_OPT_INVALID_OFFSET))
/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
VAR(uint32, IPV6_VAR_NOINIT) IpV6_DbgNeighborCacheLookups;
VAR(uint32, IPV6_VAR_NOINIT) IpV6_DbgNeighborCacheHits;
VAR(uint32, IPV6_VAR_NOINIT) IpV6_DbgNeighborCacheOptimizedHits;
VAR(uint32, IPV6_VAR_NOINIT) IpV6_DbgDestinationCacheLookups;
VAR(uint32, IPV6_VAR_NOINIT) IpV6_DbgDestinationCacheHits;
VAR(uint32, IPV6_VAR_NOINIT) IpV6_DbgDestinationCacheOptimizedHits;
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  IpV6_Ndp_VDCInvalidateSrcAddrs()
 *********************************************************************************************************************/
/*! \brief         Invalidate destination cache address indexes
 *  \details       -
 *  \param[in]     IpCtrlIdx   Index of Ip Controller
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDCInvalidateSrcAddrs(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VDestinationUnreachableCbks()
 *********************************************************************************************************************/
/*! \brief         Invoke callback for unreachable destination
 *  \details       -
 *  \param[in]     DstAddrPtr     Destination address which is not reachable
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDestinationUnreachableCbks(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr);


/**********************************************************************************************************************
 *  IpV6_Ndp_VWriteLLAddrOpt()
 *********************************************************************************************************************/
/*! \brief         Obtain link layer address of controller and write into data buffer
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     OptType      Option type
 *                              IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR  - source link layer address option
 *  \param[in]     DataPtr      IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR  - target link layer address option
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VWriteLLAddrOpt(
  TcpIp_IpV6CtrlIterType                  IpCtrlIdx,
  uint8                                   OptType,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr);

#if ((TCPIP_SUPPORT_NDP_INV_NA == STD_ON) || (TCPIP_SUPPORT_NDP_INV_NS == STD_ON))
/**********************************************************************************************************************
 *  IpV6_Ndp_VWriteAddrListOpt()
 *********************************************************************************************************************/
/*! \brief         Obtain source address table entries and store into data buffer
 *  \details       -
 *  \param[in]     IpCtrlIdx   Index of Ip Controller
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     OptType     Option Type
 *                             IPV6_NDP_OPT_TYPE_SOURCE_ADDR_LIST  source address list
 *  \param[in]     DataPtr     Data buffer
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(uint16, IPV6_CODE) IpV6_Ndp_VWriteAddrListOpt(
  TcpIp_IpV6CtrlIterType                  IpCtrlIdx,
  uint8                                   OptType,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLCheckLifetimes()
 *********************************************************************************************************************/
/*! \brief         Check lifetimes of default router list entries
 *  \details       Remove default routers whose lifetimes have expired
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDRLCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCCheckLifetimes()
 *********************************************************************************************************************/
/*! \brief         Check lifetimes and state of neighbor cache entries
 *  \details       Process the neighbor cache entries based on their reachablity state
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VSetAddrStateExpired()
 *********************************************************************************************************************/
/*! \brief        Set the state of source address table entry to expired
 *  \details      -
 *  \param[in]    IpV6SrcAddrIdx   Index of the source address
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSetAddrStateExpired(TcpIp_SizeOfIpV6SourceAddressType IpV6SrcAddrIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VSATCheckLifetimes()
 *********************************************************************************************************************/
/*! \brief         Check lifetimes of source address table entries and handle expired entries
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSATCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VSlaacRxPrefixInformation()
 *********************************************************************************************************************/
/*! \brief         Process Slaac prefixes in router advertisement option
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     PrefixInfoPtr    Prefix information
 *  \param[in]     IsMulticastRa    Flag indicates if router advertisement was multicast
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSlaacRxPrefixInformation(
  TcpIp_IpV6CtrlIterType                                         IpCtrlIdx,
  P2CONST(IpV6_NdpOptPrefixInfoType, AUTOMATIC, IPV6_APPL_DATA)  PrefixInfoPtr,
  boolean                                                        IsMulticastRa);

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessPrefixInformation()
 *********************************************************************************************************************/
/*! \brief         Process prefix information in router advertisement
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     PrefixInfoPtr    Prefix information
 *  \param[in]     IsMulticastRa    Flag indicates if router advertisement was multicast
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessPrefixInformation(
  TcpIp_IpV6CtrlIterType              IpCtrlIdx,
  IPV6_P2C(IpV6_NdpOptPrefixInfoType) PrefixInfoPtr,
  boolean                             IsMulticastRa);

/**********************************************************************************************************************
 *  IpV6_Ndp_VValidateOptions()
 *********************************************************************************************************************/
/*! \brief        Validate the options recieved in the ndp messages
 *  \details      This function scans through all Type-Length-Value (TLV) options of a received neighbor discovery packet
 *                and validates, that all options have a valid length (>0) and do not exceed the packet payload.
 *  \param[in]    DataPtr      Data buffer which contains ndp packet
 *  \param[in]    DataLen      Length of ndp packet
 *  \return       E_OK         All options of the ndp message have been validated
 *  \return       E_NOT_OK     Invalid option recieved in the ndp message
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VValidateOptions(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr,
  uint16                                    DataLen);

/**********************************************************************************************************************
 *  IpV6_Ndp_VDefaultRouterUpdate()
 *********************************************************************************************************************/
/*! \brief         Update/add entry in the default router list.
 *  \details       -
 *  \param[in]     IpCtrlIdx     Index of Ip Controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     SrcAddrPtr    Router Ip address to be added / updated in the list
 *  \param[in]     Lifetime      Lifetime of the router
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDefaultRouterUpdate(
  TcpIp_IpV6CtrlIterType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)   SrcAddrPtr,
  uint16                    Lifetime);

#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VDCCheckLifetimes()
 *********************************************************************************************************************/
/*! \brief         Check the Mtu lifetimes of destination cache entries
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDCCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateDadState()
 *********************************************************************************************************************/
/*! \brief         Update Dad state in source address table entry
 *  \details       -
 *  \param[in]     IpV6SrcAddrIdx    Index of the source address
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]     DadMode           Mode of duplicate address detection
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VUpdateDadState(
  TcpIp_IpV6SourceAddressTableEntryIterType    IpV6SrcAddrIdx,
  uint8                                        DadMode);

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxProbeStateNUD()
 *********************************************************************************************************************/
/*! \brief         Perform network unreachability detection
 *  \details       Send Nud probes to destinations whose lifetimes have expired
 *  \param[in]     IpCtrlIdx      Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx     Neighbor cache entry index
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VTxProbeStateNUD(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxIncompleteStateNS()
 *********************************************************************************************************************/
/*! \brief         Handle neighbor cache enrties in incomplete state
 *  \details       Send neighbor solicitations if neighbors state is incomplete
 *  \param[in]     IpCtrlIdx         Index of Ip Controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx        Neighbor cache entry index
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VTxIncompleteStateNS(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCGetExistingEntry()
 *********************************************************************************************************************/
/*! \brief            Iterate over all currently stored entries to earch for given Address
 *  \details          -
 *  \param[in]        IpCtrlIdx          Index of Ip Controller
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]        AddrPtr            Address to search for in neighbor cache
 *  \param[in,out]    EntryIdxPtr        Entry index in neighbor cache, in case matching entry is found
 *                                       valid only if E_OK is returned
 *  \param[in,out]    NcNewEntryIdxPtr   Least used entry index in neighbor cache is stored here
 *  \return           E_OK               Existing entry found in neighbor cache
 *  \return           E_NOT_OK           No matching entry found in cache
 *  \pre              -
 *  \context          TASK|ISR
 *  \reentrant        FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNCGetExistingEntry(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                           AddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType)  EntryIdxPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType)  NcNewEntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdatePreferredLifetime()
 *********************************************************************************************************************/
/*! \brief         Process prefix information contained in a received router advertisement
 *  \details       Update source address table entry with updated information from router advertisement
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]    SatEntryPtr      Source address table entry
 *  \param[in]     PrefixInfoPtr    Prefix information
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VUpdatePreferredLifetime(
  TcpIp_IpV6CtrlIterType                                         IpCtrlIdx,
  IPV6_P2V(IpV6_SourceAddressTableEntryType)                     SatEntryPtr,
  P2CONST(IpV6_NdpOptPrefixInfoType, AUTOMATIC, IPV6_APPL_DATA)  PrefixInfoPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCHandleTgtLLAddrChangedFlag()
 *********************************************************************************************************************/
/*! \brief         Handle change of target link layer address in neighbor advertisement
 *  \details       This function updates the neighbor cache when target ll address changed flag is set but
 *                 override Flag is not set in neighbor advertisement
 *  \param[in]     IpCtrlIdx     Index of Ip Controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx    Neighbor cache entry index
 *  \param[in]     Flags         Neighbor advertisement flags
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCHandleTgtLLAddrChangedFlag(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx,
  IpV6_NdpNaFlagsType                    Flags);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCHandleSolicitedFlag()
 *********************************************************************************************************************/
/*! \brief         Handle the flags in neighbor advertisement messages
 *  \details       -
 *  \param[in]     IpCtrlIdx       Index of Ip Controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx      Neighbor cache entry index
 *  \param[in]     TgtAddrPtr      Target address
 *  \param[in]     TgtLLAddrPtr    Target link layer address obtained from neighbor advertisement
 *  \param[in]     Flags           Option flags
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCHandleSolicitedFlag(
  TcpIp_IpV6CtrlIterType                  IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType  NcEntryIdx,
  IPV6_P2C(IpV6_AddrType)                 TgtAddrPtr,
  IPV6_P2C(uint8)                         TgtLLAddrPtr,
  IpV6_NdpNaFlagsType                     Flags);

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessNaNsOptions()
 *********************************************************************************************************************/
/*! \brief         Process the neighbor advertisement /solicitation options
 *  \details       -
 *  \param[out]    ValidOptOffsetList   Array that stores offsets of valid options in the ndp message
 *                                      For Na/Ns , only SLLA and TLLA option offsets are valid
 *  \param[in]     DataPtr              Ndp message buffer
 *  \param[in]     LenByte              Ndp message length
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessNaNsOptions(
  IPV6_P2V(uint16)          ValidOptOffsetList,
  IPV6_P2C(uint8)           DataPtr,
  uint16                    LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxNaValidateTargetAddress()
 *********************************************************************************************************************/
/*! \brief         Verify that the neighbor advertisement target address is not a local controller address
 *  \details       -
 *  \param[in]     IpCtrlIdx       Index of Ip Controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     TgtAddrPtr      Target address of the neighbor advertisement
 *  \param[in]     PhysAddrPtr     Physical address of the sender
 *  \return        E_OK            Neighbor advertisement target address is not used locally
 *  \return        E_NOT_OK        Neighbor advertisement target address is also a controller address
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VRxNaValidateTargetAddress(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)    TgtAddrPtr,
  IPV6_P2C(uint8)            PhysAddrPtr);

# if (TCPIP_ICMPV6INDADDRLISTRECEIVEDCBK == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VInvokeAddrRcvdCbk()
 *********************************************************************************************************************/
/*! \brief        Invoke callback function if source/target address list is recieved during inverse neighbor discovery
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of Ip Controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    SrcLLAddrOptPtr    Source link layer address option
 *  \param[in]    IpAddrListPtr      Source/target Ip address list
 *  \param[in]    IpAddrCount        Number of Ip addresses in address list
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VInvokeAddrRcvdCbk(
  TcpIp_IpV6CtrlIterType           IpCtrlIdx,
  IPV6_P2C(uint8)                  SrcLLAddrOptPtr,
  IPV6_P2C(IpV6_AddrType)          IpAddrListPtr,
  uint8                            IpAddrCount);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VRedirValidate()
 *********************************************************************************************************************/
/*! \brief         Validate recieved redirect message parameters
 *  \details       -
 *  \param[in]     IpCtrlIdx      Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     LocalAddrV6Idx Index of IpV6 Address
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6Addr()-1]
 *  \param[in]     DataPtr        Ndp message buffer
 *  \param[in]     SrcAddrPtr     Source address of the redirect message
 *  \param[in]     LenByte        Length of redirect message packet
 *  \return        E_OK           Redirect message is valid
 *  \return        E_NOT_OK       Redirect message parameter validation failed
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VRedirValidate(
  TcpIp_IpV6CtrlIterType    IpCtrlIdx,
  TcpIp_LocalAddrV6IterType LocalAddrV6Idx,
  IPV6_P2C(uint8)           DataPtr,
  IPV6_P2C(IpV6_AddrType)   SrcAddrPtr,
  uint16                    LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VGetFirstHopRouterAddress()
 *********************************************************************************************************************/
/*! \brief         Get the address of the first-hop router for the destination
 *  \details       -
 *  \param[in]     LocalAddrV6Idx          Ip local address index
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV6Addr()-1]
 *  \param[out]    NextHopAddrPtrPtr       Next hop address for the destination. Only valid if E_OK is returned
 *  \param[in]     DestinationAddressPtr   Destination address
 *  \param[in]     DcLookupResultPtr       Result of destination cache lookup of the destination address
 *  \param[in]     DcEntryIdxPtr           Destination cache entry index
 *  \return        E_OK                    Next hop was determined successfully
 *  \return        E_NOT_OK                Next hop not determined, destination is on-link or no default router set
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VGetFirstHopRouterAddress(
  TcpIp_LocalAddrV6IterType                             LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType*)                              NextHopAddrPtrPtr,
  IPV6_P2C(IpV6_AddrType)                               DestinationAddressPtr,
  IPV6_P2V(Std_ReturnType)                              DcLookupResultPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DestinationCacheEntryType)   DcEntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRedirProcessTLVOptions()
 *********************************************************************************************************************/
/*! \brief         Process TLV Options of Router Advertisement
 *  \details       -
 *  \param[in]     DataPtr            Ndp message buffer
 *  \param[in]     TgtLLAddrPtrPtr    Target link layer address option
 *  \param[in]     LenByte            Ndp message length
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRedirProcessTLVOptions(
  IPV6_P2C(uint8)           DataPtr,
  IPV6_P2C(uint8*)          TgtLLAddrPtrPtr,
  uint16                    LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRedirectUpdateNC()
 *********************************************************************************************************************/
/*! \brief         Update the Neighbor Cache Entry using received redirect message
 *  \details       -
 *  \param[in]     IpCtrlIdx                 Index of Ip Controller
 *                                           CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     TgtLLAddrPtr              Target link layer address
 *  \param[in]     TargetAddressPtr          Target address in redirect message
 *  \param[in]     TargetEqualsDestination   Flag indicate sif target address is same as destination
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRedirectUpdateNC(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  IPV6_P2C(uint8)          TgtLLAddrPtr,
  IPV6_P2C(IpV6_AddrType)  TargetAddressPtr,
  boolean                  TargetEqualsDestination);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdatewithNaFlags()
 *********************************************************************************************************************/
/*! \brief         Update the Neighbor Cache Entry using received neighbor advertisement message
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     IpLLAddrPtr  Link layer address option from neighbor advertisement
 *  \param[in]     NcEntryIdx   Neighbor cache entrz index
 *  \param[in]     Flags        Neighbor advertisement flags
 *  \return        E_OK         Flags updated in neighbor cache successfullly
 *  \return        E_NOT_OK     No link lazer address option found, flags not updated
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNCUpdatewithNaFlags(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  IPV6_P2C(uint8)                        IpLLAddrPtr,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx,
  IpV6_NdpNaFlagsType                    Flags);

/**********************************************************************************************************************
 *  IpV6_Ndp_VScheduleNeighborAdv()
 *********************************************************************************************************************/
/*! \brief         Send neighbor advertisement in response to solicitation
 *  \details       -
 *  \param[in]     IpCtrlIdx            Index of Ip Controller
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     SrcAddrPtr           Sender of neighbor solicitation
 *  \param[in]     SrcLinkLayerAddrPtr  SLLA option
 *  \param[in]     ResponseNaRSOFlags   RSO flags for the neighbor advertisement
 *  \param[in]     TargetAddrPtr        Target Address recieved in the solicitation
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VScheduleNeighborAdv(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)  SrcAddrPtr,
  IPV6_P2C(uint8)          SrcLinkLayerAddrPtr,
  uint8                    ResponseNaRSOFlags,
  IPV6_P2C(IpV6_AddrType)  TargetAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNsValidateTargetAddress()
 *********************************************************************************************************************/
/*! \brief         Validate the target address option in the recieved neighbor solicitation
 *  \details       -
 *  \param[in]     IpCtrlIdx                Index of Ip Controller
 *                                          CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     PhysAddrPtr              Link layer address of sender
 *  \param[out]    ResponseNaRSOFlagsPtr    RSO flag for response neighbor advertisement
 *  \param[in]     SrcAddrType              Type of source address of sender
 *  \param[in]     TargetAddrPtr            Target address option in the advertisement
 *  \return        E_OK                     Target address option is valid
 *  \return        E_NOT_OK                 Target address is not validated (no source address)
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNsValidateTargetAddress(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(uint8)            PhysAddrPtr,
  IPV6_P2V(uint8)            ResponseNaRSOFlagsPtr,
  IpV6_AddrTypeType          SrcAddrType,
  IPV6_P2C(IpV6_AddrType)    TargetAddrPtr);

#if (TCPIP_SUPPORT_IPV6_DYN_RETRANS_TIMER == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateRetransTimer()
 *********************************************************************************************************************/
/*! \brief         Update retransmission timer from router advertisement
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     RetransTimerNbo  Updated retransmission timer value
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateRetransTimer(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint32                     RetransTimerNbo);
#endif

#if (TCPIP_SUPPORT_IPV6_DYN_HOP_LIMIT == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateCurHopLimit()
 *********************************************************************************************************************/
/*! \brief         Update hop limit
 *  \details       If dynamic hop limit reconfiguration is enabled, update with new hop limit
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     CurHopLimit  Updated hop limit
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateCurHopLimit(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint8                      CurHopLimit);
#endif

#if (TCPIP_SUPPORT_NDP_NUD == STD_ON)
# if (TCPIP_SUPPORT_IPV6_DYN_REACHABLE_TIME == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateDynReachableTime()
 *********************************************************************************************************************/
/*! \brief         Update dynamic reachable time of router
 *  \details       If dynamic reconfiguration of reachable time is enabled, update with randomized value generated from
 *                 the ReachableTimeNbo obtained from the router advertisement
 *  \param[in]     IpCtrlIdx         Index of Ip Controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     ReachableTimeNbo  Reachable time for the router
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateDynReachableTime(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint32                     ReachableTimeNbo);
#endif
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VRaProcessTLVOptions()
 *********************************************************************************************************************/
/*! \brief         Process recieved router advertisement options
 *  \details       -
 *  \param[in]     LocalAddrV6Idx         Ip address index specified  by caller
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     DataPtr                Router advertisement data buffer
 *  \param[out]    SourceLLAddrPtr        This pointer points to the source link layer address if SLLA option is
 *                                        present in the advertisement
 *                                        This pointer returns NULL_PTR if no SLLA option present
 *  \param[in]     LenByte                Length of advertisement message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaProcessTLVOptions(
  TcpIp_LocalAddrV6IterType          LocalAddrV6Idx,
  IPV6_P2C(uint8)                    DataPtr,
  IPV6_P2C(uint8*)                   SourceLLAddrPtr,
  uint16                             LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateRouterEntryInNc()
 *********************************************************************************************************************/
/*! \brief         Update link layer address of router in neighbor cache
 *  \details       -
 *  \param[in]     IpCtrlIdx               Index of Ip Controller
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     SrcAddrPtr              Ip address of router
 *  \param[in]     SourceLLAddrPtr         Link layer address obtained from router advertisement SLLA option
 *                                         This pointer should be NULL_PTR if no SLLA option present
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateRouterEntryInNc(
  TcpIp_IpV6CtrlIterType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)   SrcAddrPtr,
  IPV6_P2C(uint8)           SourceLLAddrPtr);

# if (TCPIP_SUPPORT_NDP_INV_NA_NC_UPDATE == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdateTargetAddress()
 *********************************************************************************************************************/
/*! \brief         Lookup each address of the target address list in NeighborCache and record link-layer
 *                 address if there exists an INCOMPLETE entry
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     TgtAddrListPtr   Target address list obtain from inverse advertisement
 *  \param[in]     SrcLLAddrPtr     Link layer address to update
 *  \param[in]     TgtAddrCount     Number of entries in target address list
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCUpdateTargetAddress(
  TcpIp_IpV6CtrlIterType         IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)        TgtAddrListPtr,
  IPV6_P2C(uint8)                SrcLLAddrPtr,
  uint8                          TgtAddrCount);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VCleanInvalidCacheEntry()
 *********************************************************************************************************************/
/*! \brief         Clean destination cache entries which are using invalid address
 *  \details       -
 *  \param[in]     IpCtrlIdx     Index of Ip Controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx    Neighbor cache entry of invalid address
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VCleanInvalidCacheEntry(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateRaOptions()
 *********************************************************************************************************************/
/*! \brief         Process Options in recieved router advertisement
 *  \details       -
 *  \param[in]     IpCtrlIdx      Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NdpRaPtr       Ndp router advertisement data buffer
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VUpdateRaOptions(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(IpV6_NdpRaType)   NdpRaPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessCacheStates()
 *********************************************************************************************************************/
/*! \brief         Check lifetimes of enrties in diffrent caches and update states if necessary
 *  \details       -
 *  \param[in]     IpCtrlIdx      Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessCacheStates(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VCreateSATEntry()
 *********************************************************************************************************************/
/*! \brief         Create new SAT Entry using Information from recieved Prefix
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     PrefixInfoPtr    Prefix information recieved
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VCreateSATEntry(
  TcpIp_IpV6CtrlIterType                                        IpCtrlIdx,
  P2CONST(IpV6_NdpOptPrefixInfoType, AUTOMATIC, IPV6_APPL_DATA) PrefixInfoPtr,
  boolean IsMulticastRa);

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaProcessMOFlag()
 *********************************************************************************************************************/
/*! \brief         Process MO Flags in recieved RA
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     MOReservedFlag   MO flags from the recieved router advertisement
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaProcessMOFlag(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint8                      MOReservedFlag);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateandValidateLLAddr()
 *********************************************************************************************************************/
/*! \brief         Update and validate the Source/Target Link layer Address Option from the Prefix
 *  \details       -
 *  \param[in]     DataPtr              Ndp message data buffer
 *  \param[in]     DataOffset           Ndp message data offset
 *  \return        E_OK                 Valid link layer address recieved
 *  \return        E_NOT_OK             Invalid address option in the message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VUpdateandValidateLLAddr(
  IPV6_P2C(uint8)  DataPtr,
  uint16           DataOffset);

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateandValidateLLAddr()
 *********************************************************************************************************************/
/*! \brief         Validate the address list prefix option in ndp message
 *  \details       -
 *  \param[out]    IpAddrCountPtr       Number of Ip addresses in the address list
 *                                      Value of the pointer is valid only if E_OK is returned
 *  \param[in]     DataPtr              Ndp message data buffer
 *  \param[in]     DataOffset           Ndp message data offset
 *  \return        E_OK                 Address list validated successfully
 *  \return        E_NOT_OK             Invalid address list option recieved
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VUpdateandValidateAddrList(
  IPV6_P2V(uint8)  IpAddrCountPtr,
  IPV6_P2C(uint8)  DataPtr,
  uint16           DataOffset);

#if ((TCPIP_SUPPORT_NDP_INV_NA == STD_ON) || (TCPIP_SUPPORT_NDP_INV_NS == STD_ON))
/**********************************************************************************************************************
 *  IpV6_Ndp_VValidatePrefixOptions()
 *********************************************************************************************************************/
/*! \brief         Update and validate the Source/Target Address List Option from the Prefix
 *  \details       -
 *  \param[in]     ValidOptOffsetList   Array which contains offsets of prefix options in ndp messages
 *                                      The offsets are valid only when used with the corresponding message data buffer
 *                                      Options are valid only if E_OK is returned
 *  \param[out]    IpAddrCountPtr       Number of Ip addresses in the addres list
 *  \param[in]     DataPtr              Ndp message data buffer
 *  \param[in]     LenByte              Ndp message length
 *  \return        E_OK                 Prefix options validated successfully
 *  \return        E_NOT_OK             Invalid prefix options recieved
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VValidatePrefixOptions(
  IPV6_P2V(uint16)  ValidOptOffsetList,
  IPV6_P2V(uint8)   IpAddrCountPtr,
  IPV6_P2C(uint8)   DataPtr,
  uint16            LenByte);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VNaValidateMessage()
 *********************************************************************************************************************/
/*! \brief         Validate the recieved neighbor advertisement message
 *  \details       -
 *  \param[in]     LocalAddrV6Idx Ip address index specified  by caller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     DataPtr        Message buffer
 *  \param[in]     LenByte        Message data length
 *  \return        E_OK           Advertisement was processed successfully
 *  \return        E_NOT_OK       Advertisement was recieved from an invalid source address / with invalid flags
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNaValidateMessage(
  TcpIp_LocalAddrV6IterType  LocalAddrV6Idx,
  IPV6_P2C(uint8)            DataPtr,
  uint16                     LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNaUpdateRSOFlags()
 *********************************************************************************************************************/
/*! \brief         Copy the RSO Flags recieved from the neighbor advertisement
 *  \details       -
 *  \param[in]     RSOReserved    RSo flag obtained from the neighbor advertisement
 *  \param[out]    FlagsPtr       RSO flags is stored here
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNaUpdateRSOFlags(
  uint8                           RSOReserved,
  IPV6_P2V(IpV6_NdpNaFlagsType)   FlagsPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VHandleAddrStateExpired()
 *********************************************************************************************************************/
/*! \brief         Process expired source address
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     SrcAddrIdx       Index of the source address
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VHandleAddrStateExpired(
  TcpIp_IpV6CtrlIterType            IpCtrlIdx,
  TcpIp_SizeOfIpV6SourceAddressType SrcAddrIdx);

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VPerformDad()
 *********************************************************************************************************************/
/*! \brief         Perform duplicate address detection for given source address
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     IpV6SrcAddrIdx   Index of the source address for which Dad is performed
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VPerformDad(
  TcpIp_IpV6CtrlIterType            IpCtrlIdx,
  TcpIp_SizeOfIpV6SourceAddressType IpV6SrcAddrIdx);
#endif

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessNsforSlaac()
 *********************************************************************************************************************/
/*! \brief         This function handles solicitation for tentative address SLAAC (RFC4862 5.4.3)
 *  \details       -
 *  \param[in]     IpCtrlIdx       Index of Ip Controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     PhysAddrPtr     Physical address of the destination
 *  \param[in]     TgtAddrIdx      Ip address index of the source address for which solicitation has been recieved
 *  \param[in]     SrcAddrType     Type of source address from which solicitation was recieved
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessNsforSlaac(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
  IPV6_P2C(uint8)                    PhysAddrPtr,
  TcpIp_SizeOfIpV6SourceAddressType  TgtAddrIdx,
  IpV6_AddrTypeType                  SrcAddrType);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessOnLinkPrefix()
 *********************************************************************************************************************/
/*! \brief         Process onlink prefix information option contained in a received router advertisement
 *  \details       -
 *  \param[in]     IpCtrlIdx           Index of Ip Controller
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     PrefixInfoPtr       Prefix information in the router advertisement
 *  \pre           -
 *  \context       ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessOnLinkPrefix(
  TcpIp_IpV6CtrlIterType              IpCtrlIdx,
  IPV6_P2C(IpV6_NdpOptPrefixInfoType) PrefixInfoPtr);

#if (TCPIP_SUPPORT_NDP_ROUTER_SOLICITATIONS == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VSendRtrSolictations()
 *********************************************************************************************************************/
/*! \brief         Configure and send router solicitation messages
 *  \details       -
 *  \param[in]     IpCtrlIdx         Index of Ip Controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSendRtrSolictations(TcpIp_IpV6CtrlIterType IpCtrlIdx);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VCountCacheEntries
 *********************************************************************************************************************/
/*! \brief         Count number of neighbor cache entires
 *  \details       -
 *  \param[in]     IpCtrlIdx                  Index of Ip Controller
 *                                            CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \return        idxEntryCount              Number of valid neighbor cache entries
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(uint32, IPV6_CODE) IpV6_Ndp_VCountCacheEntries(
  TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VCopyCacheEntries
 *********************************************************************************************************************/
/*! \brief         Copy neighbhor cahce entries into list
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]    EntryListPtr     List to store cache entries
 *  \param[in,out] MaxNumEntriesPtr In: Maximum number of entries that shall be copied.
 *                                  Out: Number of copied entries. (may be less than input value).
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VCopyCacheEntries(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
  TCPIP_P2V(TcpIp_NdpCacheEntryType) EntryListPtr,
  TCPIP_P2V(uint32)                  MaxNumEntriesPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VSendPendingNA()
 *********************************************************************************************************************/
/*! \brief         Send neighbor advertisement for pending neighbors in neighbor cache
 *  \details       -
 *  \param[in]     IpCtrlIdx           Index of Ip Controller
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx          Neighbor cache entry index for which advertisement needs to be sent
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSendPendingNA(
  TcpIp_IpV6CtrlIterType                  IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  IpV6_Ndp_VNCLookup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNCLookup(
  TcpIp_IpV6CtrlIterType                           IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                          NetAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType) EntryIdxPtr)
{
  Std_ReturnType result = E_NOT_OK;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NULL_PTR != NetAddrPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);

# if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
    IpV6_DbgNeighborCacheLookups++;
# endif

  /* #10 Check if the supplied Entry index has the right entry */
  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   (*EntryIdxPtr >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
      && (*EntryIdxPtr <  TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
      && (IPV6_ADDR_EQUALS(TcpIp_GetAddrIpV6NeighborCacheEntry(*EntryIdxPtr)->NeighborAddress, *NetAddrPtr)))
  {
    /* check if supplied EntryIdx is already the right one */
# if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
    IpV6_DbgNeighborCacheOptimizedHits++;
# endif

    IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6NeighborCacheEntry(*EntryIdxPtr)->LastUsedTime);
    result = E_OK;
  }
  else
  {
    TcpIp_SizeOfIpV6NeighborCacheEntryType ncEntryIdx;
    /* #20 Otherwise traverse through the neighbor cache and check if there is an entry */
    for (ncEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
         ncEntryIdx < TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
         ncEntryIdx++)
    {
      /* skip entry with the supplied EntryIdx since it has already been checked */
      if (ncEntryIdx == *EntryIdxPtr)
      {
        continue;
      }

      if (IPV6_ADDR_EQUALS(TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->NeighborAddress, *NetAddrPtr))
      {
        /* valid entry found? */
#if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
        IpV6_DbgNeighborCacheHits++;
#endif

        IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LastUsedTime);
        *EntryIdxPtr = ncEntryIdx;
        result = E_OK;
        break;
      }
    }
  }

  return result;
} /* End of IpV6_Ndp_VNCLookup() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VPLGetOrCreateEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VPLGetOrCreateEntry(
  TcpIp_IpV6CtrlIterType                        IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                       AddrPrefixPtr,
  uint8                                         PrefixLength,
  IPV6_P2V(TcpIp_SizeOfIpV6PrefixListEntryType) EntryIdxPtr)
{
  Std_ReturnType result;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NULL_PTR != AddrPrefixPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);

  if (E_OK == IpV6_Ndp_VPLLookup(IpCtrlIdx, AddrPrefixPtr, PrefixLength, EntryIdxPtr))
  {
    /* #10 Check if entry exists in prefix list */
    result = E_OK;
  }
  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  else if (   (TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6PrefixListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
           && (TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) < TcpIp_GetIpV6PrefixListEntryEndIdxOfIpV6Ctrl(IpCtrlIdx)))
  {
    /* #20 Create new entry if no prefix exists */
    *EntryIdxPtr = TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6PrefixListEntry(*EntryIdxPtr)->Prefix, *AddrPrefixPtr);
    TcpIp_GetAddrIpV6PrefixListEntry(*EntryIdxPtr)->PrefixLenBits = PrefixLength;
    TcpIp_SetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) + 1u);
    result = E_OK;
  }
  else
  {
    /* no matching entry found */
    result = E_NOT_OK;
  }
  return result;
} /* End of IpV6_Ndp_VPLGetOrCreateEntry() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VPLLookup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VPLLookup(
  TcpIp_IpV6CtrlIterType                         IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                        AddrPrefixPtr,
  uint8                                          PrefixLength,
  IPV6_P2V(TcpIp_SizeOfIpV6PrefixListEntryType)  EntryIdxPtr)
{
  Std_ReturnType result = E_NOT_OK; /* no matching entry found yet */
  TcpIp_SizeOfIpV6PrefixListEntryType plEntryIdx;

  TCPIP_ASSERT(NULL_PTR != AddrPrefixPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);

  TCPIP_ASSERT(TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6PrefixListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6PrefixListEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  for (plEntryIdx = TcpIp_GetIpV6PrefixListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       plEntryIdx < TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       plEntryIdx++)
  {
    if (PrefixLength == TcpIp_GetIpV6PrefixListEntry(plEntryIdx).PrefixLenBits)
    {
      if (E_OK == IpV6_VMatchPrefix(AddrPrefixPtr, &TcpIp_GetAddrIpV6PrefixListEntry(plEntryIdx)->Prefix.addr[0],
          TcpIp_GetIpV6PrefixListEntry(plEntryIdx).PrefixLenBits))
      {
        *EntryIdxPtr = plEntryIdx;
        result = E_OK;
        break;
      }
    }
  }

  return result;
} /* End of IpV6_Ndp_VPLLookup() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VPLRemoveEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VPLRemoveEntry(
  TcpIp_IpV6CtrlIterType              IpCtrlIdx,
  TcpIp_SizeOfIpV6PrefixListEntryType PlEntryIdx)
{

  IPV6_BEGIN_CRITICAL_SECTION_PL();

  /* check for valid index */
  if (   (PlEntryIdx >= TcpIp_GetIpV6PrefixListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx)) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (PlEntryIdx < TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)))
  {
    TcpIp_DecIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);

    /* copy last entry at the position of the removed entry to avoid stale entries */
    if (PlEntryIdx != TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
    {
      TcpIp_SetIpV6PrefixListEntry(PlEntryIdx,
        TcpIp_GetIpV6PrefixListEntry(TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)));
    }
  }

  IPV6_END_CRITICAL_SECTION_PL();
} /* End of IpV6_Ndp_VPLRemoveEntry() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLLookup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VDRLLookup(
  TcpIp_IpV6CtrlIterType                                IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                               RouterAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DefaultRouterListEntryType)  EntryIdxPtr,
  TcpIp_LocalAddrV6IterType                             LocalIpV6AddrIdx)
{
  Std_ReturnType result = E_NOT_OK; /* no matching entry found */
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx;

  TCPIP_ASSERT(NULL_PTR != RouterAddrPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);

  TCPIP_ASSERT(TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DefaultRouterListEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  for (drlEntryIdx = TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       drlEntryIdx < TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       drlEntryIdx++)
  {
    /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    if (   (  (TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->LocalIpV6Idx == TCPIP_LOCAL_ADDR_V6_IDX_ANY)
            ||(TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->LocalIpV6Idx == LocalIpV6AddrIdx))
        && IPV6_ADDR_EQUALS(*RouterAddrPtr, TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->NextHopAddress))
    {
      *EntryIdxPtr = drlEntryIdx;
      result = E_OK;
      break;
    }
  }

  return result;
} /* End of IpV6_Ndp_VDRLLookup() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLCreateEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VDRLCreateEntry(
  TcpIp_IpV6CtrlIterType                                IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                               RouterAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DefaultRouterListEntryType)  EntryIdxPtr)
{
  Std_ReturnType result;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NULL_PTR != RouterAddrPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);

  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   (TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
      && (TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) < TcpIp_GetIpV6DefaultRouterListEntryEndIdxOfIpV6Ctrl(IpCtrlIdx)))
  {
    *EntryIdxPtr = TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6DefaultRouterListEntry(*EntryIdxPtr)->NextHopAddress, *RouterAddrPtr);
    TcpIp_SetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx, ((*EntryIdxPtr) + 1u));
    TcpIp_GetAddrIpV6DefaultRouterListEntry(*EntryIdxPtr)->LocalIpV6Idx = TCPIP_LOCAL_ADDR_V6_IDX_ANY;

    result = E_OK;
  }
  else
  {
    /* router list is full, address not added */
    result = E_NOT_OK;
  }

  return result;
} /* End of IpV6_Ndp_VDRLCreateEntry() */



/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLRemoveEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VDRLRemoveEntry(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx)
{
  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  IPV6_BEGIN_CRITICAL_SECTION_DRL();

  /* check for valid index */
  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   (drlEntryIdx >= TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
      && (drlEntryIdx <  TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)))
  {
    TcpIp_DecIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);

    /* copy last entry at the position of the removed entry to avoid stale entries */
    if (drlEntryIdx != TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
    {
      TcpIp_SetIpV6DefaultRouterListEntry(drlEntryIdx,
        TcpIp_GetIpV6DefaultRouterListEntry(TcpIp_GetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)));
    }
  }

  IPV6_END_CRITICAL_SECTION_DRL();
} /* End of IpV6_Ndp_VDRLRemoveEntry() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VNCGetExistingEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNCGetExistingEntry(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                           AddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType)  EntryIdxPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType)  NcNewEntryIdxPtr)
{
  Std_ReturnType Result = E_NOT_OK;
  TcpIp_SizeOfIpV6NeighborCacheEntryType ncEntryIdx;

  /* #10 Traverse through the neighbor cache and look up if matching address is present */
  for (ncEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       ncEntryIdx < TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       ncEntryIdx++)
  {

    /* skip entry with the supplied EntryIdx since it has already been checked */
    if (ncEntryIdx == *EntryIdxPtr)
    {
      continue;
    }

    /* if entry is found, break */
    if (IPV6_ADDR_EQUALS(TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->NeighborAddress, *AddrPtr))
    {
      /* entry found? */
      Result = E_OK;
# if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
      IpV6_DbgNeighborCacheHits++;
# endif

      IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LastUsedTime);
      *EntryIdxPtr = ncEntryIdx;
      break;
    }

    /* #20 Store the least used entry index if no matching address is found and cache is full */
    if (IPV6_TIME_IS_LOWER(TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LastUsedTime,
      TcpIp_GetAddrIpV6NeighborCacheEntry(*NcNewEntryIdxPtr)->LastUsedTime) == TRUE) /* oldest entry so far? */
    {
      (*NcNewEntryIdxPtr) = ncEntryIdx; /* save least recently used entry */
    }
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCGetOrCreateEntry()
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
FUNC(void, IPV6_CODE) IpV6_Ndp_VNCGetOrCreateEntry(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                           AddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType)  EntryIdxPtr)
{
  TcpIp_SizeOfIpV6NeighborCacheEntryType ncNewEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfIpV6NeighborCacheEntryType ncExistingEntryIdx = *EntryIdxPtr;

  TCPIP_ASSERT(NULL_PTR != AddrPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);
  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

# if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
    IpV6_DbgNeighborCacheLookups++;
# endif

  /* #10 Check if provided entry index contains matching address */
  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   ((ncExistingEntryIdx >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
      && (ncExistingEntryIdx <  TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)))
      && (IPV6_ADDR_EQUALS(TcpIp_GetAddrIpV6NeighborCacheEntry(ncExistingEntryIdx)->NeighborAddress, *AddrPtr)))
  {
  /* check if supplied EntryIdx is already the right one */
# if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
    IpV6_DbgNeighborCacheOptimizedHits++;
# endif
    IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6NeighborCacheEntry(ncExistingEntryIdx)->LastUsedTime);
    *EntryIdxPtr = ncExistingEntryIdx;
  }
  /* #20 Look up the entry in neighbor cache */
  else if (E_OK != IpV6_Ndp_VNCGetExistingEntry(IpCtrlIdx, AddrPtr, &ncExistingEntryIdx, &ncNewEntryIdx))
  {
    /* #30 If entry is not present, create new entry for the given address */
    if (TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) < TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx))
    {
      /* #40 If there is space left in cache, use the unused entry index */
      ncNewEntryIdx = TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
      TcpIp_SetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx, ncNewEntryIdx + 1u);
    }
    else
    {
      /* #50 If the cache is full, remove least used existing entry will be removed from cache */
      IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, ncNewEntryIdx, NULL_PTR);
    }

    /* #60 Store new entry in the appropriate index */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->NeighborAddress, *AddrPtr);
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->State      = IPV6_REACHABLE_STATE_INCOMPLETE;
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->IsRouter   = FALSE;
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->RetryCount = 0;
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->NaPending  = FALSE;
#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->InvNaPending = FALSE;
#endif
    IPV6_TIME_SET(TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->LastUsedTime, 0u, 0u);
    IPV6_TIME_SET(TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->NextEventTime, 0u, 0u);

    /* FEAT-5752 The source address to be used for transmitting neighbor solicitations for this packet
     * shall be determined later.
     * - If transmission of a packet has been triggered to this neighbor, the source address shall be
     *   set by the caller
     * - If only address resolution is triggered for this neighbor, the source address shall be
     * - set based on the "best fitting algorithm"
     */
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncNewEntryIdx)->NsSrcAddressIdx = TCPIP_IPV6_SRC_ADDR_IDX_INV;

    *EntryIdxPtr = ncNewEntryIdx;
  }
  else
  {
    /* return existing entry index to caller */
    *EntryIdxPtr = ncExistingEntryIdx;
  }

} /* End of IpV6_Ndp_VNCGetOrCreateEntry() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCLookup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, AUTOMATIC) IpV6_Ndp_VDCLookup(
  TcpIp_IpV6CtrlIterType                              IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                             AddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DestinationCacheEntryType) EntryIdxPtr)
{
  Std_ReturnType result = E_NOT_OK;

  TCPIP_ASSERT(NULL_PTR != AddrPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

# if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
    IpV6_DbgDestinationCacheLookups++;
# endif

  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   ((*EntryIdxPtr >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
      && (*EntryIdxPtr <  TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)))
      && (IPV6_ADDR_EQUALS(TcpIp_GetAddrIpV6DestinationCacheEntry(*EntryIdxPtr)->DestinationAddress, *AddrPtr)))
  {
  /* check if supplied EntryIdx is already the right one */
# if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
    IpV6_DbgDestinationCacheOptimizedHits++;
# endif

    IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6DestinationCacheEntry(*EntryIdxPtr)->LastUsedTime);
    result = E_OK;
  }
  else
  {
    TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;
    for (dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
        dcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
        dcEntryIdx++)
    {
      /* skip entry with the supplied EntryIdx since it has already been checked */
      if (dcEntryIdx == *EntryIdxPtr)
      {
        continue;
      }

      if (IPV6_ADDR_EQUALS(*AddrPtr, TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->DestinationAddress))
      {

  # if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
      IpV6_DbgDestinationCacheHits++;
  # endif

        IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->LastUsedTime);
        *EntryIdxPtr = dcEntryIdx;
        result = E_OK;
        break;
      }
    }
  }
  return result;
} /* End of IpV6_Ndp_VDCLookup() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCGetOrCreateEntry()
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
FUNC(void, AUTOMATIC) IpV6_Ndp_VDCGetOrCreateEntry(
  TcpIp_IpV6CtrlIterType                              IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                             DstAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DestinationCacheEntryType) EntryIdxPtr)
{
  Std_ReturnType result = E_NOT_OK;
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcNewEntryIdx;

  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);
  TCPIP_ASSERT(NULL_PTR != EntryIdxPtr);

  dcNewEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  /* #10 Traverse through the destination cache and check if the address is present */
  for (dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       dcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       dcEntryIdx++)
  {

    if (IPV6_ADDR_EQUALS(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->DestinationAddress, *DstAddrPtr))
    {
      IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->LastUsedTime);
      *EntryIdxPtr = dcEntryIdx;
      result = E_OK;
      break;
    }

    /* #20 Store least recently used entry (to overwrite if cache is full) */
    if (IPV6_TIME_IS_LOWER(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->LastUsedTime, TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->LastUsedTime) == TRUE)
    {
      dcNewEntryIdx = dcEntryIdx;
    }
  }

  /* #30 If no entry found, add new destination to cache */
  if (result == E_NOT_OK)
  {
    if (TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) < TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx))
    {
      /* #40 If cache is not full, add address to the first available index */
      dcNewEntryIdx = TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
      TcpIp_SetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx,
        TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) + 1u);
    }
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->DestinationAddress, *DstAddrPtr);
    IPV6_SET_CURRENT_TIME(TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->LastUsedTime);
    TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->SourceAddressIdx = TCPIP_IPV6_SRC_ADDR_IDX_INV;

  #if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
    /* #50 If Mtu reconfiguration is supported, assign the dynamic Mtu to the entry */
    if (TcpIp_IsEnablePathMtuOfIpV6Ctrl(IpCtrlIdx) == TRUE)
    {
      if (TcpIp_IsAllowLinkMtuReconfigurationOfIpV6Ctrl(IpCtrlIdx) == TRUE)
      {
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->Mtu         = TcpIp_GetDefaultLinkMtuOfIpV6CtrlDyn(IpCtrlIdx);
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->MtuReported = TcpIp_GetDefaultLinkMtuOfIpV6CtrlDyn(IpCtrlIdx);
      }
      else
      {
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->Mtu         = TcpIp_GetDefaultLinkMtuOfIpV6Ctrl(IpCtrlIdx);
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcNewEntryIdx)->MtuReported = TcpIp_GetDefaultLinkMtuOfIpV6Ctrl(IpCtrlIdx);
      }
    }
  #endif

    *EntryIdxPtr = dcNewEntryIdx;
  }
} /* End of IpV6_Ndp_VDCGetOrCreateEntry() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCRemoveEntries()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, AUTOMATIC) IpV6_Ndp_VDCRemoveEntries(
  TcpIp_IpV6CtrlIterType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)   NextHopAddrPtr)
{
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NULL_PTR != NextHopAddrPtr);
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  IPV6_BEGIN_CRITICAL_SECTION_DC();
  for (dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       dcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       dcEntryIdx++)
  {

    /* remove this entry if the next hop address matches address in NextHopAddrPtr */
    if (IPV6_ADDR_EQUALS(*NextHopAddrPtr, TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->NextHopAddress))
    {
      TcpIp_SetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx,
        TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) - 1u);

      /* copy last entry at the position of removed entry to avoid stale entry */
      if (dcEntryIdx != TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
      {
        TcpIp_SetIpV6DestinationCacheEntry(dcEntryIdx,
          TcpIp_GetIpV6DestinationCacheEntry(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)));
      }
    }
  }

  IPV6_END_CRITICAL_SECTION_DC();
} /* End of IpV6_Ndp_VDCRemoveEntries() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCRemoveEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VDCRemoveEntry(
  TcpIp_IpV6CtrlIterType                    IpCtrlIdx,
  TcpIp_SizeOfIpV6DestinationCacheEntryType DcEntryIdx)
{

  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  IPV6_BEGIN_CRITICAL_SECTION_DC();

  /* check for valid index */
  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   (DcEntryIdx >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
      && (DcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)))
  {
    TcpIp_SetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx,
      TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) - 1u);

    /* copy last entry at the position of the removed entry to avoid stale entries */
    if (DcEntryIdx != TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
    {
      TcpIp_SetIpV6DestinationCacheEntry(DcEntryIdx,
        TcpIp_GetIpV6DestinationCacheEntry(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)));
    }
  }

  IPV6_END_CRITICAL_SECTION_DC();
} /* End of IpV6_Ndp_VDCRemoveEntry() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VDCInvalidateSrcAddrs()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDCInvalidateSrcAddrs(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;

  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  IPV6_BEGIN_CRITICAL_SECTION_DC();

  for (dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       dcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       dcEntryIdx++)
  {
    TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->SourceAddressIdx = TCPIP_IPV6_SRC_ADDR_IDX_INV;
  }

  IPV6_END_CRITICAL_SECTION_DC();

} /* End of IpV6_Ndp_VDCInvalidateSrcAddrs() */

#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VDCCheckLifetimes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDCCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  /* #10 Iterate over all entries in the Destination Cache and reset MTU value to default if MTU timeout has expired. */
  IPV6_BEGIN_CRITICAL_SECTION_DC();

  for (dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       dcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       dcEntryIdx++)
  {

    if (IPV6_TIME_EXPIRED(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuTimeout) == TRUE)
    {
      if (TcpIp_IsAllowLinkMtuReconfigurationOfIpV6Ctrl(IpCtrlIdx) == TRUE)
      {
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->Mtu = TcpIp_GetDefaultLinkMtuOfIpV6CtrlDyn(IpCtrlIdx);
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuReported = TcpIp_GetDefaultLinkMtuOfIpV6CtrlDyn(IpCtrlIdx);
      }
      else
      {
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->Mtu = TcpIp_GetDefaultLinkMtuOfIpV6Ctrl(IpCtrlIdx);
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuReported = TcpIp_GetDefaultLinkMtuOfIpV6Ctrl(IpCtrlIdx);
      }
    }
  }

  IPV6_END_CRITICAL_SECTION_DC();

} /* End of IpV6_Ndp_VDCCheckLifetimes() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


/**********************************************************************************************************************
 *  IpV6_Ndp_VDestinationUnreachableCbks()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDestinationUnreachableCbks(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr)
{
  TcpIp_SockAddrBaseType sockAddrIn6; /* PRQA S 0759 */ /* MD_MSR_Union */

  sockAddrIn6.SockAddrIn6.sin6_family = IPBASE_AF_INET6;
  sockAddrIn6.SockAddrIn6.sin6_port = 0;
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(sockAddrIn6.SockAddrIn6.sin6_addr, *DstAddrPtr);

#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
  IpV6_Icmp_Cbk_DestinationUnreachable(DstAddrPtr);
#endif

  TcpIp_Cbk_VAddrResTimeout(&sockAddrIn6);
}


/**********************************************************************************************************************
 *  IpV6_Ndp_VWriteLLAddrOpt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VWriteLLAddrOpt(
  TcpIp_IpV6CtrlIterType                  IpCtrlIdx,
  uint8                                   OptType,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr)
{

  TCPIP_ASSERT(NULL_PTR != DataPtr);
  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  DataPtr[0] = OptType;
  DataPtr[1] = 1; /* 1*8 byte */
  TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), &DataPtr[2]);

} /* End of IpV6_Ndp_VWriteLLAddrOpt() */

#if ((TCPIP_SUPPORT_NDP_INV_NA == STD_ON) || (TCPIP_SUPPORT_NDP_INV_NS == STD_ON))
/**********************************************************************************************************************
 *  IpV6_Ndp_VWriteAddrListOpt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(uint16, IPV6_CODE) IpV6_Ndp_VWriteAddrListOpt(
  TcpIp_IpV6CtrlIterType                  IpCtrlIdx,
  uint8                                   OptType,
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr)
{
  TcpIp_SizeOfIpV6SourceAddressTableEntryType srcAddrIdx;
  IpV6_ListIdxType     SaCount = 0;
  uint16               DataOffset;

  TCPIP_ASSERT(NULL_PTR != DataPtr);
  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  DataPtr[0] = OptType;
  /* DataPtr[1] (option length is written at end of this function */
  DataPtr[2] = 0;
  DataPtr[3] = 0;
  DataPtr[4] = 0;
  DataPtr[5] = 0;
  DataPtr[6] = 0;
  DataPtr[7] = 0;

  DataOffset = 8;

  for (srcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx++)
  {
    if (IPV6_LADDR_STATE_INVALID != TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State)
    {
# if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      if (IPV6_LADDR_STATE_TENTATIVE != TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State)
# endif
      {
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(DataPtr[DataOffset], TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->Address);
        DataOffset += IPV6_ADDRESS_LEN_BYTE;
        SaCount++;
      }
    }
  }

  /* write option length in units of 8 octets */
  DataPtr[1] = (uint8)(1u + (SaCount * 2u)); /* (1 + (SaCount*2))*8 byte */

  return DataOffset;
} /* End of IpV6_Ndp_VWriteAddrListOpt() */
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VValidateOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VValidateOptions(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr,
  uint16                                    DataLen)
{
  Std_ReturnType result = E_OK;
  uint16 DataOffset = 0;
  uint16 OptLenByte, optLenDWord;

  TCPIP_ASSERT(NULL_PTR != DataPtr);

  while (DataOffset < DataLen)
  {
    if ((DataOffset + IPV6_TLV_OPT_DATA_OFFS) > DataLen)
    {
      /* incomplete option header */
      result = E_NOT_OK;
    }

    /* OptType = DataPtr[DataOffset]; */
    optLenDWord = DataPtr[(uint16) DataOffset + 1u];
    OptLenByte = IPV6_NDP_CALC_OPTION_LENGTH(optLenDWord);

    /* RFC4861 6.1.2: All options must have a length that is greater than zero */
    if (0u == OptLenByte)
    {
      result = E_NOT_OK;
    }

    if ((DataOffset + OptLenByte) > DataLen)
    {
      /* option length exceeds data length */
      result = E_NOT_OK;
    }

    if (result == E_NOT_OK)
    {
      break;
    }
    DataOffset += OptLenByte; /* skip to next option */
  }

  return result;
} /* End of IpV6_Ndp_VValidateOptions() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateDadState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VUpdateDadState(
  TcpIp_IpV6SourceAddressTableEntryIterType  IpV6SrcAddrIdx,
  uint8                                       DadMode)
{
  IpV6_SourceAddressTableEntryType *SatEntryPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx);

  /* #10 Update the source address table entry states based on the Dad mode */
  switch (DadMode)
  {
    /* Configure OPTIMISTIC address? */
  case IPV6_SRC_ADDR_DAD_MODE_OPTIMISTIC: /* PRQA S 2003 */ /* MD_TCPIP_Rule16.3_2003 */
    {
#   if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
      TcpIp_LocalAddrV6IdxOfIpV6SourceAddressType localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
      TcpIp_IpV6CtrlIterType ipCtrlIdx   = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);
      TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx);
      /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
      if (TcpIp_IsEnableOptimisticDadOfNdpConfig(ndpConfigIdx) == TRUE)
      {
        SatEntryPtr->State = IPV6_LADDR_STATE_OPTIMISTIC;
        SatEntryPtr->DadNsTxRemain = TcpIp_GetDadTransmitsOfNdpConfig(ndpConfigIdx);
        break;
      }
      else
#   endif
      {
        /* fall through */
      }
    }
    /* Configure TENTATIVE address? */
  case IPV6_SRC_ADDR_DAD_MODE_NORMAL: /* PRQA S 2003 */ /* MD_TCPIP_Rule16.3_2003 */
    {
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      TcpIp_LocalAddrV6IdxOfIpV6SourceAddressType localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
      TcpIp_IpV6CtrlIterType ipCtrlIdx   = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);
      TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx);

      if (0u < TcpIp_GetDadTransmitsOfNdpConfig(ndpConfigIdx)) /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
      {
        SatEntryPtr->State = IPV6_LADDR_STATE_TENTATIVE;
        SatEntryPtr->DadNsTxRemain = TcpIp_GetDadTransmitsOfNdpConfig(ndpConfigIdx);
        break;
      }
      else
#endif
      {
        /* fall through */
      }
    }
    /* fall through */
  case IPV6_SRC_ADDR_DAD_MODE_NONE: /* PRQA S 2003 */ /* MD_TCPIP_Rule16.3_2003 */
    {
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      TcpIp_LocalAddrV6IdxOfIpV6SourceAddressType localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
      TcpIp_IpV6CtrlIterType ipCtrlIdx   = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);
      TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx);
#endif
      /* Configure address without performing DAD */
      if (IPV6_TIME_EXPIRED(SatEntryPtr->PreferredTime) == FALSE)
      {
        SatEntryPtr->State = IPV6_LADDR_STATE_PREFERRED;
      }
      else
      {
        SatEntryPtr->State = IPV6_LADDR_STATE_DEPRECATED;
      }
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
      if (0u < TcpIp_GetDadTransmitsOfNdpConfig(ndpConfigIdx))
      {
        SatEntryPtr->DadNsTxRemain = 0;
      }
#endif
    }
    break;
  default: /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    break;
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VAddSourceAddress()
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
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VAddSourceAddress(
  TcpIp_IpV6SourceAddressIterType                   IpV6SrcAddrIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) AddressPtr,
  uint32                                            PreferredLifetime,
  uint32                                            ValidLifetime,
  uint32                                            DelayMs,
  uint8                                             DadMode)
{
  Std_ReturnType    Result;

  TCPIP_ASSERT(NULL_PTR != AddressPtr);
  TCPIP_ASSERT(IpV6SrcAddrIdx < TcpIp_GetSizeOfIpV6SourceAddress());

#if (TCPIP_SUPPORT_NDP_DAD == STD_OFF)
  TCPIP_UNUSED_PARAMETER(DelayMs);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  /* #10 Validate the address */
  if ((IPV6_ADDR_IS_MULTICAST(*AddressPtr)) || /* multicast addresses must not be assigned to a node */
      (!IPV6_ADDR_IS_EUI64(*AddressPtr)))
  {
    /* We do not support IPv6 addresses that are not required to have 64Bit interface identifiers.
     * This check filters out all addresses starting with the binary value 000.
     * E.g. the Loopback and Unspecified addresses
     */

    Result = E_NOT_OK;
  }
  else if (0u < ValidLifetime)
  {
     /* #20 Obtain the SAT entry to which the new address will be added */
    TcpIp_LocalAddrV6IdxOfIpV6SourceAddressType localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
    TcpIp_IpV6CtrlIterType ipCtrlIdx   = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);
    IpV6_SourceAddressTableEntryType *SatEntryPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx);

    /* #30 Initialize the SAT entry */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(SatEntryPtr->Address, *AddressPtr);
    IPV6_TIME_SET(SatEntryPtr->NextEventTime, 0u, 0u);

    IPV6_SET_LIFETIME_S(SatEntryPtr->PreferredTime, PreferredLifetime, (IpV6_TimeType*)NULL_PTR);
    IPV6_SET_LIFETIME_S(SatEntryPtr->ValidTime,     ValidLifetime,     (IpV6_TimeType*)NULL_PTR);

     /* #40 Join solicited-node multicast group of the address */
     /* This has to be done here before the address is configured (DAD is complete) because
     * we will only detect address configuration issues if we are able to receive NDP messages
     * that are sent to the solicited-node multicast address.
     */
    IPV6_VJOIN_SOLICITED_NODE_MULTICAST_GROUP(ipCtrlIdx, AddressPtr, TRUE);

    IpV6_Ndp_VUpdateDadState(IpV6SrcAddrIdx, DadMode);

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    /* #50 If Dad is enabled, update timer to send out Ndp Dad messages */
    /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
    if (0u < TcpIp_GetDadTransmitsOfNdpConfig(TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx)))
    {
      if (0u < SatEntryPtr->DadNsTxRemain)
      {
        /* Set next event time for this address entry so that it will expire after DelayMs milliseconds.
           The delay will defer transmit of the first Neighbor Solicitation and should be randomly chosen by the caller.
           See [RFC4861 5.4.2. Sending Neighbor Solicitation Messages] */
        IPV6_SET_EVENT_TIME_MS(SatEntryPtr->NextEventTime, DelayMs);
      }
      else
      {
        SatEntryPtr->NextEventTime = SatEntryPtr->PreferredTime;
      }

      /* If DAD is active and the address is in TENTATIVE state, it is not ready for use right now.
       * IpV6_VHandleSourceAddrAssignmentChange() will be called from IpV6_Ndp_VSATCheckLifetimes()
       * after DAD has been completed.
       */
      if (IPV6_LADDR_STATE_TENTATIVE != SatEntryPtr->State)
      {
        /* #60 If address is not tentative, notify upper layers that new address is available for use */
        IpV6_VHandleSourceAddrAssignmentChange(IpV6SrcAddrIdx, TRUE);
      }
    }
    else
#endif
    {
      /* #70 Notify upper layers that new address is available for use */
      SatEntryPtr->NextEventTime = SatEntryPtr->PreferredTime;
      IpV6_VHandleSourceAddrAssignmentChange(IpV6SrcAddrIdx, TRUE);
    }

    Result = E_OK;
  }
  else
  {
    /* ignore unconfigured address with zero lifetime */
    Result = E_NOT_OK;
  }

  return Result;
} /* End of IpV6_Ndp_VAddSourceAddress() */ /* PRQA S 6050, 6060 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */

#if (TCPIP_SUPPORT_NDP_ROUTER_SOLICITATIONS == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VSendRtrSolictations()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSendRtrSolictations(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  /* router solicitations sending active */
  IpV6_TimeType nextTxTime;
  IPV6_TIME_SET(nextTxTime, TcpIp_GetNdp_RouterSolicitationNextTxTimeOfIpV6CtrlDyn(IpCtrlIdx).S,
    TcpIp_GetNdp_RouterSolicitationNextTxTimeOfIpV6CtrlDyn(IpCtrlIdx).Ms);
  /* #10 Check if timeout for next Router Solicitation has expired. */
  if (IPV6_TIME_EXPIRED(nextTxTime) == TRUE)
  {
    boolean IncludeSllaOpt;

    /* #20 Check if Source Link-Layer Option must be included in Router Solicitation. */
    if (IPV6_CTRL_STATE_LLADDR_READY <= TcpIp_GetCtrlStateOfIpV6CtrlDyn(IpCtrlIdx))
    {
      /* IPV6_STATE_LLADDR_READY indicates that a valid link-local address has been stored in entry 0 of
        * the SourceAddressTable.
        */

#if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
      /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
      if (TcpIp_IsEnableOptimisticDadOfNdpConfig(ndpConfigIdx) == TRUE)
      {
        /* "A node MUST NOT send a Router Solicitation with a SLLAO from an Optimistic Address.
          *  Router Solicitations SHOULD be sent from a non-Optimistic or the Unspecified Address; however,
          *  they MAY be sent from an Optimistic Address as long as the SLLAO is not included."
          *  [RFC4429 3.2. Modifications to RFC 2461 Neighbor Discovery]
          */
        /* PRQA S 4304 2 */ /* MD_MSR_AutosarBoolean */
        IncludeSllaOpt = (boolean)(IPV6_LADDR_STATE_OPTIMISTIC !=
          TcpIp_GetIpV6SourceAddressTableEntry(TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx)).State);
      }
      else
#endif
      {
        IncludeSllaOpt = TRUE;
      }
    }
    else
    {
      /* use the unspecified address as source address for RS, since we do not have a valid address */
      IncludeSllaOpt = FALSE;
    }

    {
      TcpIp_SizeOfIpV6SourceAddressTableEntryType ipV6SrcAddrIdx = TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx);
      TcpIp_SizeOfLocalAddrV6Type ipAddrIdx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);

      /* #30 Send one Router Solicitation and update timeout for next Router Solicitation. */
      if (E_OK == IpV6_Ndp_VTxRouterSolicitation(ipAddrIdx, IncludeSllaOpt))
      {
        IpV6_TimeType rtrSolicitNxtTime;
        IPV6_SET_EVENT_TIME_MS(rtrSolicitNxtTime, TcpIp_GetRtrSolicitationIntervalOfNdpConfig(ndpConfigIdx));
        TcpIp_SetNdp_RouterSolicitationNextTxTimeOfIpV6CtrlDyn(IpCtrlIdx, rtrSolicitNxtTime);
      }
      TcpIp_IncNdp_RouterSolicitationTxCountOfIpV6CtrlDyn(IpCtrlIdx);
    }
  }
} /* IpV6_Ndp_VSendRtrSolictations() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLCheckLifetimes()
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
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDRLCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx;

#if (TCPIP_SUPPORT_NDP_ROUTER_SOLICITATIONS == STD_ON)
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif

  IPV6_BEGIN_CRITICAL_SECTION_DRL();

  /* #10 Send configured number of Router Solicitations while no default router is known. */
#if (TCPIP_SUPPORT_NDP_ROUTER_SOLICITATIONS == STD_ON)
  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (0u < TcpIp_GetMaxRtrSolicitationDelayOfNdpConfig(ndpConfigIdx))
  {
    /* We start sending Router Solicitations until at least one default router has been
     * discovered (rx of Router Advertisement) or the maximum number of Router Solicitations has been sent.
     */

    if (TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) ==
        TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx))
    {
      /* no default routers known */

      if (TcpIp_GetNdp_RouterSolicitationTxCountOfIpV6CtrlDyn(IpCtrlIdx) <
          TcpIp_GetMaxRtrSolicitationsOfNdpConfig(ndpConfigIdx))
      {
        IpV6_Ndp_VSendRtrSolictations(IpCtrlIdx);
      }
    }
  }
#endif

  /* #50 Remove default routers from list if their lifetime has expired. */

  /* check expiration times of all entries */
  TCPIP_ASSERT(TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DefaultRouterListEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  for (drlEntryIdx = TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       drlEntryIdx < TcpIp_GetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       drlEntryIdx++)
  {

    /* remove default router entry if lifetime has expired */
    if (   (IPV6_TIME_EXPIRED(TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->ExpireTime) == TRUE)/* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->StaticEntry == FALSE))
    {
      IpV6_Ndp_VDCRemoveEntries(IpCtrlIdx, &(TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->NextHopAddress));
      IpV6_Ndp_VDRLRemoveEntry(IpCtrlIdx, drlEntryIdx);
    }
  }

  IPV6_END_CRITICAL_SECTION_DRL();

} /* End of IpV6_Ndp_VDRLCheckLifetimes() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_Ndp_VNCRemoveEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VNCRemoveEntry(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx)
{
  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  IPV6_BEGIN_CRITICAL_SECTION_NC();

  /* #10 Iterate over all currently stored neighbor cache entries */
  if (NcEntryIdx < TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
  {
    TcpIp_SetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx,
      TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) - 1u);

    /* #20 Copy last entry at the position of the removed entry to avoid stale entries */
    if (NcEntryIdx != TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx))
    {
      TcpIp_SetIpV6NeighborCacheEntry(NcEntryIdx,
        TcpIp_GetIpV6NeighborCacheEntry(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx)));
    }
  }
  IPV6_END_CRITICAL_SECTION_NC();

} /* End of IpV6_Ndp_VNCRemoveEntry() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VCleanInvalidCacheEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VCleanInvalidCacheEntry(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx)
{
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;
  TCPIP_P2C(IpV6_NeighborCacheEntryType) EntryPtr = TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx);

  /* address resolution failed! */
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6DestinationCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  /* #10 Remove all entries from Destination Cache that are using the
   * unreachable neighbor as next hop and inform upper layers.
   */
  IPV6_BEGIN_CRITICAL_SECTION_DC();

  for (dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       dcEntryIdx < TcpIp_GetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       dcEntryIdx++)
  {

    /* remove this entry if the next hop address matches address in NextHopAddrPtr */
    if (IPV6_ADDR_EQUALS(EntryPtr->NeighborAddress, TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->NextHopAddress))
    {
      IpV6_Ndp_VDestinationUnreachableCbks(&(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->DestinationAddress));
      IpV6_Ndp_VDCRemoveEntry(IpCtrlIdx, dcEntryIdx);
    }
  }

  IPV6_END_CRITICAL_SECTION_DC();

  /* #20 Remove entry from neighbor Cache */
  IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, NcEntryIdx, NULL_PTR);
  IpV6_Ndp_VNCRemoveEntry(IpCtrlIdx, NcEntryIdx);
} /* IpV6_Ndp_VCleanInvalidCacheEntry() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxIncompleteStateNS()
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

STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VTxIncompleteStateNS(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx)
{
  IpV6_NeighborCacheEntryType *EntryPtr = TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx);
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  /* #10 Check if timeout for next Neighbor Solicitation has expired. */
  if (IPV6_TIME_EXPIRED(EntryPtr->NextEventTime) == TRUE) /* timeout expired? */
  {
    /* #20 Check if number of retries has not exceeded */
    if (EntryPtr->RetryCount < TcpIp_GetMulticastSolicitsOfNdpConfig(ndpConfigIdx))
    {
      /* Send NS */
      TcpIp_SizeOfLocalAddrV6Type ipAddrIdx;

      /* #30 Determine the best fitting source address to send the NS, if not source address index has been set */
      if (TCPIP_IPV6_SRC_ADDR_IDX_INV == EntryPtr->NsSrcAddressIdx)
      {
        TcpIp_SizeOfIpV6SourceAddressType srcAddrIdx;
        if (IpV6_VSelectSourceAddress(IpCtrlIdx, &EntryPtr->NeighborAddress, &srcAddrIdx) == E_OK)
        {
          /* FEAT-5752 Update the source address using the best fitting source address
           * since there is no triggering interface
           */
          EntryPtr->NsSrcAddressIdx = srcAddrIdx;
        }
      }

      /* #40 Use the best fitting source address index if available, or use default address index */
      if (TCPIP_IPV6_SRC_ADDR_IDX_INV != EntryPtr->NsSrcAddressIdx)
      {
        TcpIp_SizeOfIpV6SourceAddressType nsIpV6SourceAddressIdx = EntryPtr->NsSrcAddressIdx;
        ipAddrIdx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(nsIpV6SourceAddressIdx);
      }
      else
      {
        ipAddrIdx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);
      }

      IPV6_BEGIN_CRITICAL_SECTION();

      /* #50 Trigger the transmission of the NS */
      if (E_OK == IpV6_Ndp_VTxNeighborSolicitation(ipAddrIdx, &EntryPtr->NeighborAddress, FALSE, FALSE))
      {
        IPV6_SET_EVENT_TIME_MS(EntryPtr->NextEventTime, TcpIp_GetRetransTimerMsOfIpV6CtrlDyn(IpCtrlIdx));
        EntryPtr->RetryCount++;
      }

      IPV6_END_CRITICAL_SECTION();
    }
    /* #60 Otherwise, handle failed link layer address resolution. */
    else
    {
      /* address resolution failed! */
      IpV6_Ndp_VCleanInvalidCacheEntry(IpCtrlIdx, NcEntryIdx);
    }
  }
  else
  {
    /* do nothing */
  }

  return;
} /* IpV6_Ndp_VTxIncompleteStateNS() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxProbeStateNUD()
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

STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VTxProbeStateNUD(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx)
{
  IpV6_NeighborCacheEntryType *EntryPtr = TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx);
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  if (IPV6_TIME_EXPIRED(EntryPtr->NextEventTime) == TRUE) /* retrans delay expired? */
  {
    /* #10 Send one NUD Probe if configured number of probes has not been sent yet. */
    if (EntryPtr->RetryCount < TcpIp_GetUnicastSolicitsOfNdpConfig(ndpConfigIdx))
    {
      /* Send NUD probe NS */
      TcpIp_SizeOfLocalAddrV6Type ipAddrIdx;
      IpV6_AddrIdxType nsIpV6SrcAddrIdx = EntryPtr->NsSrcAddressIdx;

      if (TCPIP_IPV6_SRC_ADDR_IDX_INV != nsIpV6SrcAddrIdx)
      {
        /* #110 Use the best fitting source address to send the NUD probe */
        ipAddrIdx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(nsIpV6SrcAddrIdx);
      }
      else
      {
        /* #120 If best fit address not determined, configure default address
         * and best fitting source address shall be determined later
         */
        ipAddrIdx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);
      }

      IPV6_BEGIN_CRITICAL_SECTION();

      if (E_OK == IpV6_Ndp_VTxNeighborSolicitation(ipAddrIdx, &EntryPtr->NeighborAddress, TRUE, FALSE))
      {
        IPV6_SET_EVENT_TIME_MS(EntryPtr->NextEventTime, TcpIp_GetRetransTimerMsOfIpV6CtrlDyn(IpCtrlIdx));
        EntryPtr->RetryCount++;
      }

      IPV6_END_CRITICAL_SECTION();
    }
    /* #20 ELSE: Handle unreachable Neighbor. */
    else
    {
      /* #30 Remove all entries from Destination Cache that are using the unreachable neighbor as next hop. */
      IpV6_Ndp_VDCRemoveEntries(IpCtrlIdx, &EntryPtr->NeighborAddress);

      /* #40 Remove entry from Neighbor Cache. */
      IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, NcEntryIdx, NULL_PTR);
      IpV6_Ndp_VNCRemoveEntry(IpCtrlIdx, NcEntryIdx);

      /* Remove all entries from destination cache that are using this neighbor as next hop */
      IpV6_Ndp_VDCRemoveEntries(IpCtrlIdx, &EntryPtr->NeighborAddress);
    }
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VSendPendingNA()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSendPendingNA(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx)
{

#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif

  if (IPV6_REACHABLE_STATE_INCOMPLETE != TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->State)
  {
    if (TRUE == TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->NaPending)
    {
      TcpIp_LocalAddrV6IterType ipAddrIdx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);

      /* #10 Send pending neighbor advertisement */
      if (E_OK == IpV6_Ndp_VTxNeighborAdvertisement(&ipAddrIdx,
        &(TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->NeighborAddress),
        &(TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->NaTgtAddress),
        TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->NaRSOFlags))
      {
        TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->NaPending = FALSE;
      }
    }

#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
    /* #20 Send pending Inverse Neighbor Advertisement */
    /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
    if (   (TcpIp_IsEnableNdpInvNsOfNdpConfig(ndpConfigIdx) == TRUE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TRUE == TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->InvNaPending))
    {
      /* try to transmit pending inverse advertisement */
      TcpIp_LocalAddrV6IterType ipAddrIdx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);

      if (E_OK == IpV6_Ndp_VTxInverseAdvertisement(&ipAddrIdx, &(TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->InvNsSrcAddress), &(TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->LinkLayerAddress[0])))
      {
        TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->InvNaPending = FALSE;
      }
    }
#endif
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCCheckLifetimes()
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

STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfIpV6NeighborCacheEntryType ncEntryIdx;
  IPV6_P2C(IpV6_NeighborCacheEntryType) EntryPtr;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  IPV6_BEGIN_CRITICAL_SECTION_NC();

  /* #10 Iterate over all entries in the Neighbor Cache. */
  /* iterate over all currently stored entries */
  for (ncEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       ncEntryIdx < TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       ncEntryIdx++)
  {

    EntryPtr = TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx);
    /* #20 Send pending advertisements if cache entry is valid */
    IpV6_Ndp_VSendPendingNA(IpCtrlIdx, ncEntryIdx);

    switch (TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State)
    {
    case IPV6_REACHABLE_STATE_INCOMPLETE:
      /* #30 Send pending Neighbor Solicitations if entry is in state INCOMPLETE. */
      IpV6_Ndp_VTxIncompleteStateNS(IpCtrlIdx, ncEntryIdx);
      break;

#if (TCPIP_SUPPORT_NDP_NUD == STD_ON)

    case IPV6_REACHABLE_STATE_DELAY:
      /* #40 Set entry state from DELAY to PROBE if probe delay has expired. */

      if (IPV6_TIME_EXPIRED(EntryPtr->NextEventTime) == TRUE) /* probe delay expired? */
      {
        /* setting the entry state to PROBE will trigger probing this neighbor next time this function is called */
        IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, ncEntryIdx, IPV6_REACHABLE_STATE_PROBE);
      }

      break;

    case IPV6_REACHABLE_STATE_PROBE:
      /* #50 Perform Neighbor Unreachability Detection (NUD) if entry is in state PROBE.  */
      IpV6_Ndp_VTxProbeStateNUD(IpCtrlIdx, ncEntryIdx);

      break;

    case IPV6_REACHABLE_STATE_REACHABLE:
      /* #60 Set entry state from REACHABLE to STALE if reachable time has expired. */
      /* expiration check may be omitted here, it is sufficent when an expired entry is
       * set to stale when a packet is transmitted
       */

      if (IPV6_TIME_EXPIRED(EntryPtr->NextEventTime) == TRUE) /* entry expired? */
      {
        /* change entry state to stale because no recent reachable confirmation has been received */
        IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, ncEntryIdx, IPV6_REACHABLE_STATE_STALE);
      }

      break;

#endif

    default: /* last possible case is IPV6_REACHABLE_STATE_STALE: */
      /* stale entries are not modified until a packet should be sent */
      break;
    }
  }

  IPV6_END_CRITICAL_SECTION_NC();
} /* End of IpV6_Ndp_VNCCheckLifetimes() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_Ndp_VChangeLocalAddrState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VChangeLocalAddrState(
  TcpIp_SizeOfIpV6SourceAddressTableEntryType IpV6SrcAddrIdx,
  IpV6_LocAddrStateType                       NewState)
{
  TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
  TcpIp_IpV6CtrlIterType ipCtrlIdx           = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

  TCPIP_ASSERT(IpV6SrcAddrIdx >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(ipCtrlIdx));
  TCPIP_ASSERT(IpV6SrcAddrIdx <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(ipCtrlIdx));

  {
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
    if (0u < TcpIp_GetDadTransmitsOfNdpConfig(TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx)))
    {
      if (   (IPV6_LADDR_STATE_TENTATIVE == TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->State)
          && (IPV6_LADDR_STATE_TENTATIVE != NewState))
      {
        /* If a TENTATIVE address has become valid. Notify upper layers. */
        IpV6_VHandleSourceAddrAssignmentChange(IpV6SrcAddrIdx, TRUE);
      }
    }
#endif

    TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->State = NewState;

    switch (NewState)
    {
      case IPV6_LADDR_STATE_PREFERRED:
        TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->NextEventTime =
          TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->PreferredTime;
        break;

      default: /* case IPV6_LADDR_STATE_DEPRECATED: */
        TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->NextEventTime =
          TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx)->ValidTime;
        break;
    }

    /* Invalidate all source addresses in Destination Cache. */
    IpV6_Ndp_VDCInvalidateSrcAddrs(ipCtrlIdx);
  }

} /* End of IpV6_Ndp_VChangeLocalAddrState() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VSetAddrStateExpired()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSetAddrStateExpired(TcpIp_SizeOfIpV6SourceAddressType IpV6SrcAddrIdx)
{
  TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx;
  TcpIp_IpV6CtrlIterType      ipCtrlIdx;

  localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(IpV6SrcAddrIdx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

  TCPIP_ASSERT(IpV6SrcAddrIdx >= TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(ipCtrlIdx));
  TCPIP_ASSERT(IpV6SrcAddrIdx <  TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(ipCtrlIdx));

  IpV6_Ndp_VDCInvalidateSrcAddrs(ipCtrlIdx);

  IpV6_VHandleSourceAddrAssignmentChange(IpV6SrcAddrIdx, FALSE);

  IpV6_VSATRemoveEntry(IpV6SrcAddrIdx);
} /* End of IpV6_Ndp_VSetAddrStateExpired() */

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VPerformDad()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VPerformDad(
  TcpIp_IpV6CtrlIterType            IpCtrlIdx,
  TcpIp_SizeOfIpV6SourceAddressType IpV6SrcAddrIdx)
{
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  IpV6_SourceAddressTableEntryType *SatEntryPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(IpV6SrcAddrIdx);

  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (0u < TcpIp_GetDadTransmitsOfNdpConfig(ndpConfigIdx))
  {
    /* IPV6_LADDR_STATE_TENTATIVE or IPV6_LADDR_STATE_OPTIMISTIC */

    if (0u < SatEntryPtr->DadNsTxRemain)
    {
      /* #10 Send one DAD Neighbor Solicitation message and update next event time for this address. */
      TcpIp_SizeOfIpV6SourceAddressTableEntryType ipV6SrcAddrIdx = TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx);

      TcpIp_LocalAddrV6IterType ipAddrIdx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);

      IPV6_BEGIN_CRITICAL_SECTION();

      if (E_OK == IpV6_Ndp_VTxNeighborSolicitation(ipAddrIdx, &SatEntryPtr->Address, FALSE, TRUE))
      {
        SatEntryPtr->DadNsTxRemain--;
        IPV6_SET_EVENT_TIME_MS(SatEntryPtr->NextEventTime, TcpIp_GetRetransTimerMsOfIpV6CtrlDyn(IpCtrlIdx));
      }

      IPV6_END_CRITICAL_SECTION();
    }
    /* #20 Change address state to PREFERRED if configured number of DAD NS messages have been sent. */
    else
    {
      /* DAD for TENTATIVE or OPTIMISTIC address complete */
      /* this tentative address has not become invalid after performing duplicate address detection */
      IpV6_Ndp_VChangeLocalAddrState(IpV6SrcAddrIdx, IPV6_LADDR_STATE_PREFERRED);
    }
  }
} /* IpV6_Ndp_VPerformDad() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VHandleAddrStateExpired()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VHandleAddrStateExpired(
  TcpIp_IpV6CtrlIterType            IpCtrlIdx,
  TcpIp_SizeOfIpV6SourceAddressType SrcAddrIdx)
{
  IPV6_P2C(IpV6_SourceAddressTableEntryType) SatEntryPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(SrcAddrIdx);

#if (TCPIP_SUPPORT_NDP_DAD == STD_OFF)
  TCPIP_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  if (IPV6_TIME_EXPIRED(SatEntryPtr->NextEventTime) == TRUE)
  {
    /* #10 Change address state from PREFERRED to DEPRECATED. */
    if (IPV6_LADDR_STATE_PREFERRED == SatEntryPtr->State)
    {
      /* the preferred lifetime for this address has been expired.
        * This address is still valid but now deprecated for usage with new connections.
        * Source address selection will not select this address if preferred addresses exist.
        */
      IpV6_Ndp_VChangeLocalAddrState(SrcAddrIdx, IPV6_LADDR_STATE_DEPRECATED);
    }
    /* #20 Remove address from Source Address Table if lifetime has expired. */
    else if (IPV6_LADDR_STATE_DEPRECATED == SatEntryPtr->State)
    {
      /* Valid lifetime of this deprecated address has been expired.
        * Remove this source address and notify upper layers.
        */
      IpV6_Ndp_VSetAddrStateExpired(SrcAddrIdx);
    }
    /* #30 Perform Duplicate Address Detection (DAD) for addresses in state TENTATIVE or OPTIMISTIC. */
    else
    {
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
      IpV6_Ndp_VPerformDad(IpCtrlIdx, SrcAddrIdx);
#endif
    }
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VSATCheckLifetimes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSATCheckLifetimes(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{

  TcpIp_SizeOfIpV6SourceAddressType srcAddrIdx;

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  IPV6_BEGIN_CRITICAL_SECTION_SAT();

  /* #10 Iterate over all entries in the Source Address Table. */
  for (srcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
       srcAddrIdx++)
  {

    /* #20 Skip invalid/unused entries. */
    if (IPV6_LADDR_STATE_INVALID != TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx)->State)
    {
      /* #30 Check if timeout for the entry has expired and action is required. */
      IpV6_Ndp_VHandleAddrStateExpired(IpCtrlIdx, srcAddrIdx);
    }
  }

  IPV6_END_CRITICAL_SECTION_SAT();

} /* End of IpV6_Ndp_VSATCheckLifetimes() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VDefaultRouterUpdate()
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
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VDefaultRouterUpdate(
  TcpIp_IpV6CtrlIterType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)   SrcAddrPtr,
  uint16                    Lifetime)
{
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx = 
        TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NULL_PTR != SrcAddrPtr);

  /* #10 Check if router address already exists in the default router list */
  if (E_OK == IpV6_Ndp_VDRLLookup(IpCtrlIdx, SrcAddrPtr, &drlEntryIdx, TCPIP_LOCAL_ADDR_V6_IDX_ANY))
  {
    /* #20 If router is already present, update the lifetime of the entry */
    if (0u < Lifetime)
    {
      IPV6_SET_LIFETIME_S(TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->ExpireTime, Lifetime, NULL_PTR);
    }
    else /* lifetime expired */
    {
      IpV6_Ndp_VDRLRemoveEntry(IpCtrlIdx, drlEntryIdx);

      /* #30 If lifetime of the router has expired, remove all entries from the
       * destination cache using the default router
       */

      IpV6_Ndp_VDCRemoveEntries(IpCtrlIdx, SrcAddrPtr);
    }
  }
  else /* router not in default router list */
  {
    if (0u < Lifetime)
    {
      /* #40 If address is not present in the list, create entry if list is not full */
      if (E_OK == IpV6_Ndp_VDRLCreateEntry(IpCtrlIdx, SrcAddrPtr, &drlEntryIdx))
      {
        IPV6_SET_LIFETIME_S(TcpIp_GetAddrIpV6DefaultRouterListEntry(drlEntryIdx)->ExpireTime, Lifetime, NULL_PTR);
      }
      else /* no space left in default router list */
      {
        /* we have reached the maximum number of enries in the default router list, this router will be ignored */
      }
    }
    else /* lifetime expired */
    {
      /* ignore router information */
    }
  }
} /* End of IpV6_Ndp_VDefaultRouterUpdate() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdatePreferredLifetime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VUpdatePreferredLifetime(
  TcpIp_IpV6CtrlIterType                                        IpCtrlIdx,
  IPV6_P2V(IpV6_SourceAddressTableEntryType)                    SatEntryPtr,
  P2CONST(IpV6_NdpOptPrefixInfoType, AUTOMATIC, IPV6_APPL_DATA) PrefixInfoPtr)
{

  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  uint32                    validLifetime;
  uint32                    preferredLifetime;
  uint32                    RemainingLifetime;

  validLifetime     = TCPIP_NTOHL(PrefixInfoPtr->ValidLifetimeNbo);
  preferredLifetime = TCPIP_NTOHL(PrefixInfoPtr->PreferredLifetimeNbo);

  /* Update preferred lifetime of the SAT entry */
  IPV6_SET_LIFETIME_S(SatEntryPtr->PreferredTime, preferredLifetime, &SatEntryPtr->NextEventTime);

  if (IpV6_Time.S < SatEntryPtr->ValidTime.S)
  {
    RemainingLifetime = (SatEntryPtr->ValidTime.S - IpV6_Time.S);
  }
  else
  {
    RemainingLifetime = 0;
  }

  /* prevent quick invalidation of addresses by prefix information options
   * with very small lifetimes (see RFC4862 5.5.3. e)
   */
  /* PRQA S 3415 1 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if ((validLifetime > RemainingLifetime) || (validLifetime > TcpIp_GetSlaacMinLifetimeOfNdpConfig(ndpConfigIdx)))
  {
    IPV6_SET_LIFETIME_S(SatEntryPtr->ValidTime, validLifetime, &SatEntryPtr->NextEventTime);
  }
  else if (RemainingLifetime > TcpIp_GetSlaacMinLifetimeOfNdpConfig(ndpConfigIdx))
  {
    /* New lifetime is smaller than current remaining lifetime and smaller than IPV6_NDP_SLAAC_MIN_VALID_LIFETIME
      * Truncate current lifetime to minimum valid lifetime.
      */
    IPV6_SET_LIFETIME_S(SatEntryPtr->ValidTime,
      TcpIp_GetSlaacMinLifetimeOfNdpConfig(ndpConfigIdx), &SatEntryPtr->NextEventTime);
  }
  else
  {
    /* Do not update valid lifetime.
      * The remaining lifetime for this address is already less that IPV6_NDP_SLAAC_MIN_VALID_LIFETIME seconds.
      * Setting a shorter lifetime value here would make denail-of-service attacks easier.
      */
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VCreateSATEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VCreateSATEntry(
  TcpIp_IpV6CtrlIterType                                        IpCtrlIdx,
  P2CONST(IpV6_NdpOptPrefixInfoType, AUTOMATIC, IPV6_APPL_DATA) PrefixInfoPtr,
  boolean                                                       IsMulticastRa)
{

  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  uint32                    validLifetime;
  uint32                    preferredLifetime;
  TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx;

  TcpIp_LinkLocalDadDelayMsOfIpV6CtrlDynType minDelayMs;

  validLifetime     = TCPIP_NTOHL(PrefixInfoPtr->ValidLifetimeNbo);
  preferredLifetime = TCPIP_NTOHL(PrefixInfoPtr->PreferredLifetimeNbo);

  if ((0u < preferredLifetime) && (0u < validLifetime))
  {
    /* create new source address entry for this prefix */
    IpV6_AddrType        SrcAddrCandidate; /* PRQA S 0759 */ /* MD_MSR_Union */
    TcpIp_IpV6SourceAddressStartIdxOfIpV6CtrlType linkLocalAddrIdx;
    boolean              FreeCtrlAddrIdxFound = FALSE;

    /* #10 Locate free source address entry for configuration source RA */
    for (ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6SrcAddrIdx < TcpIp_GetIpV6SourceAddressEndIdxOfIpV6Ctrl(IpCtrlIdx);
         ipV6SrcAddrIdx++)
    {
      if (TCPIP_IPADDR_ASSIGNMENT_IPV6_ROUTER == TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(ipV6SrcAddrIdx))
      {
        if (IPV6_LADDR_STATE_INVALID == TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx)->State)
        {
          /* free address container for configuration source RA found */
          FreeCtrlAddrIdxFound = TRUE;
          break;
        }
      }
    }

    /* Get the index of the link local address. */
    linkLocalAddrIdx = TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx);

    /* If the link local address is in state tentative we should care about the minimum delay for the router address. */
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    if (IPV6_LADDR_STATE_TENTATIVE == TcpIp_GetAddrIpV6SourceAddressTableEntry(linkLocalAddrIdx)->State)
    {
      minDelayMs = TcpIp_GetLinkLocalDadDelayMsOfIpV6CtrlDyn(IpCtrlIdx);
    }
    else
#endif
    {
      /* If the link local address is not anymore in state tentative the minDelayMs could be zero. */
      minDelayMs = 0;
    }

    /* #20 If free source address index found, build and add source address with prefix into SAT */
    if (TRUE == FreeCtrlAddrIdxFound)
    {
      /* a prefix must have a specific length so that in combination with the
       * interface identifier the address is 128 bytes long
       */
      /* combine prefix and interface identifier to an address */
      TcpIp_InterfaceIdentifierStartIdxOfIpV6CtrlType interfaceIdentifierStartIdx = TcpIp_GetInterfaceIdentifierStartIdxOfIpV6Ctrl(IpCtrlIdx);
      uint32 DelayMs;
      IpV6_VBuildSourceAddress(TcpIp_GetAddrInterfaceIdentifier(interfaceIdentifierStartIdx), &PrefixInfoPtr->Prefix, &SrcAddrCandidate);

      /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
      if ((TcpIp_IsEnableSlaacDelayOfNdpConfig(ndpConfigIdx) == TRUE) && (TRUE == IsMulticastRa))
      {
        /* The RA was sent to a multicast destination, so we SHOULD wait a random delay before
          * starting address configuration.
          * "The delay will avoid similar congestion when multiple nodes are going to configure
          *  addresses by receiving the same single multicast router advertisement."
          *  [RFC4862 5.4.2. Sending Neighbor Solicitation Messages]
          */
        DelayMs = IpV6_VGetRandomValue(minDelayMs, TcpIp_GetMaxSlaacDelayOfNdpConfig(ndpConfigIdx));
      }
      else
      {
        DelayMs = 0;
      }

      (void)IpV6_Ndp_VAddSourceAddress(ipV6SrcAddrIdx, &SrcAddrCandidate, preferredLifetime, validLifetime, DelayMs, IPV6_SRC_ADDR_DAD_MODE_OPTIMISTIC);
    }
    else
    {
      /* no free source address table entry for configuration source RA found */
    }
  }
  else /* prefix information expired */
  {
    /* we have no address configured for this expired prefix. ignore information */
  }
} /* IpV6_Ndp_VCreateSATEntry() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VSlaacRxPrefixInformation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VSlaacRxPrefixInformation(
  TcpIp_IpV6CtrlIterType                                        IpCtrlIdx,
  P2CONST(IpV6_NdpOptPrefixInfoType, AUTOMATIC, IPV6_APPL_DATA) PrefixInfoPtr,
  boolean                                                       IsMulticastRa)
{
  Std_ReturnType result = E_OK;
  TcpIp_SizeOfIpV6SourceAddressType srcAddrIdx;
  uint32                            validLifetime;
  uint32                            preferredLifetime;

  TCPIP_ASSERT(NULL_PTR != PrefixInfoPtr);

  if ((IPV6_PREFIX_LEN_BYTE * IPV6_BITS_IN_BYTE) != PrefixInfoPtr->PrefixLength)
  {
    /* unsupported prefix length */
    result = E_NOT_OK;
  }
  else if (!IPV6_ADDR_IS_EUI64(PrefixInfoPtr->Prefix))
  {
    /* ignore prefix */
    result = E_NOT_OK;
  }
  else
  {
    validLifetime     = TCPIP_NTOHL(PrefixInfoPtr->ValidLifetimeNbo);
    preferredLifetime = TCPIP_NTOHL(PrefixInfoPtr->PreferredLifetimeNbo);

    /* ignore this prefix if preferred lifetime is bigger that valid lifetime */
    if (preferredLifetime > validLifetime)
    {
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
    IPV6_BEGIN_CRITICAL_SECTION_SAT();

    /* IpV6_VSATLookupPrefix() needs initialized index */
    srcAddrIdx = TcpIp_GetIpV6SourceAddressStartIdxOfIpV6Ctrl(IpCtrlIdx);

    /* lookup all addresses with advertised prefix that are already in source address list */
    if (E_OK == IpV6_VSATLookupPrefix(IpCtrlIdx, &PrefixInfoPtr->Prefix.addr[0],
        &srcAddrIdx, TCPIP_IPADDR_ASSIGNMENT_IPV6_ROUTER))
    {
      IpV6_SourceAddressTableEntryType *SatEntryPtr = TcpIp_GetAddrIpV6SourceAddressTableEntry(srcAddrIdx);

      IpV6_Ndp_VUpdatePreferredLifetime(IpCtrlIdx, SatEntryPtr, PrefixInfoPtr);
    }
    else
    {
      /* no address configured for this prefix so far */
      IpV6_Ndp_VCreateSATEntry(IpCtrlIdx, PrefixInfoPtr, IsMulticastRa);
    }

    IPV6_END_CRITICAL_SECTION_SAT();
  }
} /* End of IpV6_Ndp_VSlaacRxPrefixInformation() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessOnLinkPrefix()
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
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessOnLinkPrefix(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
 IPV6_P2C(IpV6_NdpOptPrefixInfoType) PrefixInfoPtr)
{

  TcpIp_SizeOfIpV6PrefixListEntryType  plEntryIdx;
#if (TCPIP_IPV6STATICONLINKPREFIX == STD_ON)
  /* #10 If prefix is statically configured, ignore the prefix */
  if (IpV6_VIsStaticOnLinkPrefix(IpCtrlIdx, &PrefixInfoPtr->Prefix, PrefixInfoPtr->PrefixLength) == TRUE)
  {
    /* This prefix or a prefix that covers this prefix is statically configured. Ignore prefix information. */
  }
  else
#endif
  {
    uint32 validLifetime = TCPIP_NTOHL(PrefixInfoPtr->ValidLifetimeNbo);

    /* #20 Check if the prefix is already known. */
    if (E_OK == IpV6_Ndp_VPLLookup(IpCtrlIdx, &PrefixInfoPtr->Prefix, PrefixInfoPtr->PrefixLength, &plEntryIdx))
    {
      if (0u < validLifetime)
      {
        /* #30 Extend lifetime if valid lifetime received */
        IPV6_SET_LIFETIME_S(TcpIp_GetAddrIpV6PrefixListEntry(plEntryIdx)->ExpireTime, validLifetime,
          (P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_VAR))NULL_PTR);
      }
      else
      {
        /* #40 Otherwise, lifetime is expired and remove prefix entry */
        IpV6_Ndp_VPLRemoveEntry(IpCtrlIdx, plEntryIdx);
      }
    }
    else /* prefix unknown */
    {
      /* #50 Otherwise, create prefix entry if lifetime not expired */
      if (0u < validLifetime)
      {
        if (E_OK == IpV6_Ndp_VPLGetOrCreateEntry(IpCtrlIdx, &PrefixInfoPtr->Prefix,
            PrefixInfoPtr->PrefixLength, &plEntryIdx))
        {
          IPV6_SET_LIFETIME_S(TcpIp_GetAddrIpV6PrefixListEntry(plEntryIdx)->ExpireTime,
            validLifetime, (P2VAR(IpV6_TimeType, AUTOMATIC, IPV6_APPL_VAR))NULL_PTR);
        }
      }
      else /* prefix lifetime expired */
      {
        /* ignore prefix information */
      }
    }
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessPrefixInformation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessPrefixInformation(
  TcpIp_IpV6CtrlIterType              IpCtrlIdx,
  IPV6_P2C(IpV6_NdpOptPrefixInfoType) PrefixInfoPtr,
  boolean                             IsMulticastRa)
{

  TCPIP_ASSERT(NULL_PTR != PrefixInfoPtr);

  if (IPV6_ADDR_IS_LINK_LOCAL(PrefixInfoPtr->Prefix) || IPV6_ADDR_IS_MULTICAST(PrefixInfoPtr->Prefix))
  {
    /* ignore link-local and multicast prefixes */
  }
  else
  {
    if (0u != (PrefixInfoPtr->LAReserved & IPV6_NDP_OPT_PREFIX_INFO_FLAG_ON_LINK)) /* on-link prefix? */
    {
      /* PROCESS ON-LINK FLAG */
      IpV6_Ndp_VProcessOnLinkPrefix(IpCtrlIdx, PrefixInfoPtr);
    }
    else /* no on-link information */
    {
      /* nothing to to here */
    }

    /* PROCESS SLAAC FLAG */
    if (0u != (PrefixInfoPtr->LAReserved & IPV6_NDP_OPT_PREFIX_INFO_FLAG_SLAAC)) /* autoconfiguration */
    {
      IpV6_Ndp_VSlaacRxPrefixInformation(IpCtrlIdx, PrefixInfoPtr, IsMulticastRa);
    }
  }
} /* IpV6_Ndp_VProcessPrefixInformation() */


#if (TCPIP_SUPPORT_NDP_OPT_RFC6106_RDNSS == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessRdnssOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessRdnssOption(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr)
{
  P2CONST(IpV6_NdpOptRdnssType, AUTOMATIC, IPV6_APPL_DATA) RdnssOptPtr;

#if (IPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  IpV6_CheckDetErrorReturnVoid(NULL_PTR != DataPtr, IPV6_API_ID_V_INTERNAL_FUNCTION, IPV6_E_INV_POINTER);
#endif

  RdnssOptPtr = (P2CONST(IpV6_NdpOptRdnssType, AUTOMATIC, IPV6_APPL_DATA))DataPtr;

  if (3 <= RdnssOptPtr->Length)
  {
    /* "The number of addresses is determined by the Length field.
     *  That is, the number of addresses is equal to (Length - 1u) / 2."
     */
    uint8 AddrCount = (RdnssOptPtr->Length - 1u) >> IPV6_RSHIFT_DIV_2;

    Dns_UpdateIpV6Servers((IpBase_AddrIn6Type*)&DataPtr[sizeof(IpV6_NdpOptRdnssType)],
      AddrCount, TCPIP_NTOHL(RdnssOptPtr->LifetimeNbo), 0u);
  }
  else
  {
    /* minimum value of length field is 3 */
  }


} /* IpV6_Ndp_VProcessRdnssOption() */
#endif


#if (TCPIP_SUPPORT_NDP_OPT_RFC6106_DNSSL == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessDnsslOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessDnsslOption(
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) DataPtr)
{
  P2CONST(IpV6_NdpOptDnsslType, AUTOMATIC, IPV6_APPL_DATA) DnsslOptPtr;

#if (IPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  IpV6_CheckDetErrorReturnVoid(NULL_PTR != DataPtr, IPV6_API_ID_V_INTERNAL_FUNCTION, IPV6_E_INV_POINTER);
#endif
  DnsslOptPtr = (P2CONST(IpV6_NdpOptDnsslType, AUTOMATIC, IPV6_APPL_DATA))DataPtr;

  if (2u <= DnsslOptPtr->Length)
  {
    /* message length in bytes: 8 * (1 + AddrCount * 2) | AddrCount: Number of IPv6 addresses */
    uint16 DomainNameListLength = (uint16)(DnsslOptPtr->Length - 1u) << IPV6_LSHIFT_MUL_8;
    uint16 DomainNameListEndPos = (DnsslOptPtr->Length << IPV6_LSHIFT_MUL_8) - 1u;
    uint16 ZeroByteCount = 0;

    /* remove padding */
    while ((DomainNameListEndPos > sizeof(IpV6_NdpOptDnsslType)) && (0u == DataPtr[DomainNameListEndPos]))
    {
      ZeroByteCount++;
      DomainNameListEndPos--;
    }

    if (0u < ZeroByteCount)
    {
      DomainNameListLength -= (ZeroByteCount - 1u);
    }
  }
  else
  {
    /* minumum value of length field is 2 */
  }


} /* IpV6_Ndp_VProcessDnsslOption() */
#endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateRouterEntryInNc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateRouterEntryInNc(
  TcpIp_IpV6CtrlIterType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)   SrcAddrPtr,
  IPV6_P2C(uint8)           SourceLLAddrPtr)
{
  TcpIp_SizeOfIpV6NeighborCacheEntryType  ncEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);

  IPV6_BEGIN_CRITICAL_SECTION_NC();

  if (E_OK == IpV6_Ndp_VNCLookup(IpCtrlIdx, SrcAddrPtr, &ncEntryIdx))
  {
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->IsRouter = TRUE;

    if (NULL_PTR != SourceLLAddrPtr) /* source link-layer address included? */
    {
      /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      if (   (IPV6_REACHABLE_STATE_INCOMPLETE == TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State)
          || (FALSE == TcpIp_CmpLLAddr(&SourceLLAddrPtr[0], &TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LinkLayerAddress[0]))) /* different link-layer address? */
      {
        IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, ncEntryIdx, &SourceLLAddrPtr[0]);
        TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State = IPV6_REACHABLE_STATE_STALE;
      }
    }
  }
#if (IPV6_NDP_ENABLE_LL_ADDR_GATHERING == STD_ON)
  else /* no neighbor cache entry exists */
  {
    if (NULL_PTR != SourceLLAddrPtr) /* source link-layer address included? */
    {
      IpV6_Ndp_VNCGetOrCreateEntry(IpCtrlIdx, SrcAddrPtr, &ncEntryIdx);

      IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, ncEntryIdx, &SourceLLAddrPtr[0]);
      TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State = IPV6_REACHABLE_STATE_STALE;
      TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->IsRouter = TRUE;
    }
  }
#endif
  IPV6_END_CRITICAL_SECTION_NC();
} /* IpV6_Ndp_VRaUpdateRouterEntryInNc() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VRaProcessTLVOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaProcessTLVOptions(
  TcpIp_LocalAddrV6IterType          LocalAddrV6Idx,
  IPV6_P2C(uint8)                    DataPtr,
  IPV6_P2C(uint8*)                   SourceLLAddrPtr,
  uint16                             LenByte)
{
  uint16 DataOffset = sizeof(IpV6_NdpRaType);
  uint8  OptType;
  uint16 OptLenByte;
  TcpIp_IpV6CtrlIterType           ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
  boolean IsMulticastRa = (boolean)(TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* process TLV encoded options */

  while (DataOffset < LenByte)
  {
    OptType = DataPtr[DataOffset];
    OptLenByte = (8u * (uint16) DataPtr[DataOffset + 1u]);

    switch (OptType)
    {
    /* OPTION: Source Link-Layer Address */
    case IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR:
      /* Obtain the source link layer address from the SLLA option in the advertisement */
      *SourceLLAddrPtr = &DataPtr[DataOffset + 2u];

      if (IPV6_LL_ADDR_IS_INVALID(*SourceLLAddrPtr))
      {
        /* ignore invalid source link-layer address option */
        *SourceLLAddrPtr = (const uint8*) NULL_PTR;
      }

      break;

    /* OPTION: Prefix Information */
    case IPV6_NDP_OPT_TYPE_PREFIX_INFO: /* network prefix */

      if (sizeof(IpV6_NdpOptPrefixInfoType) == OptLenByte)
      {
        IpV6_NdpOptPrefixInfoType ndpPrefixInfo;
        ndpPrefixInfo.Type = TCPIP_GET_UINT8(DataPtr, DataOffset /* + IPV6_NDP_PREFIX_INFO_OPT_OFF_TYPE */);
        ndpPrefixInfo.Length =  TCPIP_GET_UINT8(DataPtr, DataOffset + IPV6_NDP_PREFIX_INFO_OPT_OFF_LENGTH);
        ndpPrefixInfo.PrefixLength = TCPIP_GET_UINT8(DataPtr, DataOffset + IPV6_NDP_PREFIX_INFO_OPT_OFF_PREFIXLENGTH);
        ndpPrefixInfo.LAReserved = TCPIP_GET_UINT8(DataPtr, DataOffset + IPV6_NDP_PREFIX_INFO_OPT_OFF_LARESERVED);
        ndpPrefixInfo.ValidLifetimeNbo = TCPIP_GET_UINT32_RAW(DataPtr, DataOffset + IPV6_NDP_PREFIX_INFO_OPT_OFF_VALIDLIFETIMENBO);
        ndpPrefixInfo.PreferredLifetimeNbo = TCPIP_GET_UINT32_RAW(DataPtr, DataOffset + IPV6_NDP_PREFIX_INFO_OPT_OFF_PREFERREDLIFETIMENBO);
        ndpPrefixInfo.Reserved32Nbo = TCPIP_GET_UINT32_RAW(DataPtr, DataOffset + IPV6_NDP_PREFIX_INFO_OPT_OFF_RESERVED32NBO);
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(ndpPrefixInfo.Prefix, DataPtr[DataOffset + IPV6_NDP_PREFIX_INFO_OPT_OFF_PREFIX]);

        IpV6_Ndp_VProcessPrefixInformation(ipCtrlIdx, &ndpPrefixInfo, IsMulticastRa);
      }
      else
      {
        /* invalid Prefix Information option length */
      }
      break;

    /* OPTION: MTU */
    case IPV6_NDP_OPT_TYPE_MTU:

      if (sizeof(IpV6_NdpOptMtuType) == OptLenByte)
      {
        if (TcpIp_IsAllowLinkMtuReconfigurationOfIpV6Ctrl(ipCtrlIdx) == TRUE)
        {
          uint32 MtuValue;

          MtuValue = TCPIP_GET_UINT32(DataPtr, (DataOffset + IPV6_NDP_MTU_OPT_OFF_MTUNBO));

          if (0xFFFFU >= MtuValue)
          {
            IpV6_VUpdateDefaultLinkMtu(ipCtrlIdx, (uint16)MtuValue);
          }
        }
      }
      else
      {
        /* invalid MTU option length */
      }

      break;

#if (TCPIP_SUPPORT_NDP_OPT_RFC6106_RDNSS == STD_ON)

    /* OPTION: RDNSS */
    case IPV6_NDP_OPT_TYPE_RDNSS:

      /* [RFC6106 5.1. Recursive DNS Server Option] */

      IpV6_Ndp_VProcessRdnssOption(&DataPtr[DataOffset]);
      break;
#endif

#if (TCPIP_SUPPORT_NDP_OPT_RFC6106_DNSSL == STD_ON)

    /* OPTION: DNSSL */
    case IPV6_NDP_OPT_TYPE_DNSSL:

      /* [RFC6106 5.2. DNS Search List Option] */

      IpV6_Ndp_VProcessDnsslOption(&DataPtr[DataOffset]);
      break;
#endif

    /* OPTION: UNKNOWN */
    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      /* Default case left blank intentionally */
      /* ignore this option */
      break;
    }

    DataOffset += OptLenByte; /* skip to next option */
  }
} /* IpV6_Ndp_VRaProcessTLVOptions() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaProcessMOFlag()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaProcessMOFlag(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint8                      MOReservedFlag)
{
  if (   (IPV6_DHCPV6_MODE_AUTOMATIC == TcpIp_GetDhcpModeOfIpV6Ctrl(IpCtrlIdx)) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (FALSE == TcpIp_DhcpV6_IsActive(IpCtrlIdx)))
  {
    if (0u != (MOReservedFlag & IPV6_NDP_RA_FLAG_MANAGED))
    {
      /* Managed address configuration flag set.
       * Addresses are availabe via DHCPv6.
       */

      if (FALSE == TcpIp_DhcpV6_IsActive(IpCtrlIdx))
      {
        TcpIp_SizeOfIpV6SourceAddressType srcAddrIdxDhcp;
        TCPIP_ASSERT(TcpIp_IsIpV6SourceAddressDhcpUsedOfIpV6Ctrl(IpCtrlIdx));
        srcAddrIdxDhcp = TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx);
        if (IPV6_LADDR_STATE_INVALID == TcpIp_GetIpV6SourceAddressTableEntry(srcAddrIdxDhcp).State)
        {
          TcpIp_DhcpV6_StartAddressAssignment(IpCtrlIdx);
        }
      }
    }
    else if (0u != (MOReservedFlag & IPV6_NDP_RA_FLAG_OTHER))
    {
      /* Other configuration flag set.
       * Other configuration information is available via DHCPv6.
       */

      if (FALSE == TcpIp_DhcpV6_IsActive(IpCtrlIdx))
      {
        (void)TcpIp_DhcpV6_RequestInformation(IpCtrlIdx);
      }
    }
    else
    {
      /* "Managed address configuration" and "Other configuration" flags not set */
    }
  }
}
#endif

#if (TCPIP_SUPPORT_NDP_NUD == STD_ON)
# if (TCPIP_SUPPORT_IPV6_DYN_REACHABLE_TIME == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateDynReachableTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateDynReachableTime(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint32                     ReachableTimeNbo)
{
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  if (TcpIp_IsDynamicReachableTimeOfNdpConfig(ndpConfigIdx) == TRUE) /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  {
    /* "If the received Reachable Time value is non-zero, the host SHOULD set
        its BaseReachableTime variable to the received value."
        [RFC4861 6.3.4.] */

    uint32 RaReachableTime = TCPIP_HTONL(ReachableTimeNbo);

    if (0u < RaReachableTime)
    {
#  if (TCPIP_SUPPORT_IPV6_RND_REACHABLE_TIME == STD_ON)
      /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
      if (TcpIp_IsRandomReachableTimeOfNdpConfig(ndpConfigIdx) == TRUE)
      {
        /* Behaviour according to [RFC4861 6.3.4.]:
         * "ReachableTime is computed as a uniformly distributed random value between
         *  MIN_RANDOM_FACTOR and MAX_RANDOM_FACTOR times the BaseReachableTime.
         *  Using a random component eliminates the possibility that Neighbor Unreachability
         *  Detection messages will synchronize with each other."
         */
        if (RaReachableTime != TcpIp_GetBaseReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx))
        {
          /* reachable time changed */
          TcpIp_SetBaseReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx, RaReachableTime);
          TcpIp_SetReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx, IpV6_VRandomizeValue(IpCtrlIdx, TcpIp_GetBaseReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx)));
        }
      }
      else
#  endif
      {
        /* do not randomize reachable time */

        if (RaReachableTime != TcpIp_GetReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx))
        {
          /* reachable time changed */
          TcpIp_SetReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx, RaReachableTime);
        }
      }
    }
  }
} /* IpV6_Ndp_VRaUpdateDynReachableTime() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
# endif
#endif

#if (TCPIP_SUPPORT_IPV6_DYN_HOP_LIMIT == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateCurHopLimit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateCurHopLimit(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint8                      CurHopLimit)
{
  if (TcpIp_IsEnableDynHopLimitOfIpV6Ctrl(IpCtrlIdx) == TRUE)
  {
    /* "If the received Cur Hop Limit value is non-zero, the host SHOULD set
        its CurHopLimit variable to the received value."
        [RFC4861 6.3.4.] */

    if (0u < CurHopLimit)
    {
      TcpIp_SetCurHopLimitOfIpV6CtrlDyn(IpCtrlIdx, CurHopLimit);
    }
  }
}
#endif

#if (TCPIP_SUPPORT_IPV6_DYN_RETRANS_TIMER == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRaUpdateRetransTimer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRaUpdateRetransTimer(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  uint32                     RetransTimerNbo)
{
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (TcpIp_IsDynamicRetransTimerOfNdpConfig(ndpConfigIdx) == TRUE)
  {
    /* "The RetransTimer variable SHOULD be copied from the Retrans Timer
        field, if the received value is non-zero."
        [RFC4861 6.3.4.] */

    if (0u < TCPIP_NTOHL(RetransTimerNbo))
    {
      TcpIp_SetRetransTimerMsOfIpV6CtrlDyn(IpCtrlIdx, TCPIP_NTOHL(RetransTimerNbo));
    }
  }
}
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateRaOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VUpdateRaOptions(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(IpV6_NdpRaType)   NdpRaPtr)
{

#if ((TCPIP_SUPPORT_DHCPV6 == STD_OFF) && (TCPIP_SUPPORT_IPV6_DYN_HOP_LIMIT == STD_OFF) && (TCPIP_SUPPORT_IPV6_DYN_REACHABLE_TIME == STD_OFF) && (TCPIP_SUPPORT_IPV6_DYN_RETRANS_TIMER == STD_OFF))
  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  IPV6_UNUSED_PARAMETER(NdpRaPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
  IpV6_Ndp_VRaProcessMOFlag(IpCtrlIdx, NdpRaPtr->MOReserved);
#endif

#if (TCPIP_SUPPORT_IPV6_DYN_HOP_LIMIT == STD_ON)
  IpV6_Ndp_VRaUpdateCurHopLimit(IpCtrlIdx, NdpRaPtr->CurHopLimit);
#endif

#if (TCPIP_SUPPORT_NDP_NUD == STD_ON)
# if (TCPIP_SUPPORT_IPV6_DYN_REACHABLE_TIME == STD_ON)
  IpV6_Ndp_VRaUpdateDynReachableTime(IpCtrlIdx, NdpRaPtr->ReachableTimeNbo);
# endif
#endif

#if (TCPIP_SUPPORT_IPV6_DYN_RETRANS_TIMER == STD_ON)
  IpV6_Ndp_VRaUpdateRetransTimer(IpCtrlIdx, NdpRaPtr->RetransTimerNbo);
#endif

} /* IpV6_Ndp_VUpdateRaOptions() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxRouterAdvertisement()
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
FUNC(void, IPV6_CODE) IpV6_Ndp_VRxRouterAdvertisement(
  TcpIp_LocalAddrV6IterType     LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)       SrcAddrPtr,
  IPV6_P2C(uint8)               DataPtr,
  uint16                        LenByte)
{
  Std_ReturnType result;
  TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA) SourceLinkLayerAddressPtr =
                        (P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA))NULL_PTR;

  TCPIP_ASSERT(NULL_PTR != SrcAddrPtr);
  TCPIP_ASSERT(NULL_PTR != DataPtr);

  /* #10 Validate the router advertisement options */
  /* source address of router advertisement must always be the link-local address of the router */
  if (IPV6_ADDR_TYPE_LL_UNICAST != IpV6_VGetAddrType(SrcAddrPtr))
  {
    result = E_NOT_OK; /* silently ignore invalid router advertisement */
  }
  else if (E_OK != IpV6_Ndp_VValidateOptions(&DataPtr[sizeof(IpV6_NdpRaType)], (uint16)(LenByte - sizeof(IpV6_NdpRaType))))
  {
    result = E_NOT_OK; /* silently ignore invalid router advertisement */
  }
  else
  {
    /* router advertisement is valid */
    result = E_OK;
  }

  if (result == E_OK)
  {
    /* #20 Update the Ra data structure with received valid router advertisement */

    IpV6_NdpRaType NdpRaData; /* RA data is not modified in the block, so no need to wrote back */
    NdpRaData.CurHopLimit        = TCPIP_GET_UINT8(DataPtr, IPV6_NDP_RA_MSG_OFF_CURHOPLIMIT);
    NdpRaData.MOReserved         = TCPIP_GET_UINT8(DataPtr, IPV6_NDP_RA_MSG_OFF_MORESERVED);
    NdpRaData.RouterLifetimeNbo  = TCPIP_GET_UINT16_RAW(DataPtr, IPV6_NDP_RA_MSG_OFF_ROUTERLIFETIMENBO);
    NdpRaData.ReachableTimeNbo   = TCPIP_GET_UINT32_RAW(DataPtr, IPV6_NDP_RA_MSG_OFF_REACHABLETIMENBO);
    NdpRaData.RetransTimerNbo    = TCPIP_GET_UINT32_RAW(DataPtr, IPV6_NDP_RA_MSG_OFF_RETRANSTIMERNBO);

    IpV6_Ndp_VUpdateRaOptions(ipCtrlIdx, &NdpRaData);

    /* #30 Update content of default router list */
    IpV6_Ndp_VDefaultRouterUpdate(ipCtrlIdx, SrcAddrPtr, TCPIP_NTOHS(NdpRaData.RouterLifetimeNbo));

    /* #40 Process router advertisement options */
    IpV6_Ndp_VRaProcessTLVOptions(LocalAddrV6Idx, DataPtr, &SourceLinkLayerAddressPtr, LenByte);

    /* #50 update router entry in neighbor cache if link-layer address has changed */
    IpV6_Ndp_VRaUpdateRouterEntryInNc(ipCtrlIdx, SrcAddrPtr, SourceLinkLayerAddressPtr);
  }
} /* End of IpV6_Ndp_VRxRouterAdvertisement() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessNsforSlaac()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessNsforSlaac(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
  IPV6_P2C(uint8)                    PhysAddrPtr,
  TcpIp_SizeOfIpV6SourceAddressType  TgtAddrIdx,
  IpV6_AddrTypeType                  SrcAddrType)
{
  /* solicitation for tentative address SLAAC (RFC4862 5.4.3) */

  if (IPV6_ADDR_TYPE_UNICAST == SrcAddrType)
  {
    /* the sender of this solicitation is performing address resolution for tentative address,
     * we MUST NOT send a response
     */
  }
  else if (IPV6_ADDR_TYPE_UNSPECIFIED == SrcAddrType)
  {
    /* someone else is performig DAD for this tentative address.
     * If link-layer loops back packets it colud be ourself otherwise someone else also wants to use this address.
     */
    TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

# if (TCPIP_SUPPORT_IPV6_MULTICAST_LOOPBACK == STD_ON)
    if (TcpIp_GetAddrIpV6SourceAddressTableEntry(TgtAddrIdx)->DadNsRxCount < (TcpIp_GetDadTransmitsOfNdpConfig(ndpConfigIdx) - TcpIp_GetAddrIpV6SourceAddressTableEntry(TgtAddrIdx)->DadNsTxRemain))
    {
      TcpIp_GetAddrIpV6SourceAddressTableEntry(TgtAddrIdx)->DadNsRxCount += 1u;
    }
    else
# endif
    {
      {
        /* DAD for non-temporary address failed */
        IpV6_VHandleDADFailure(PhysAddrPtr, TgtAddrIdx, IPV6_DAD_FAIL_NS);
        IpV6_VSATRemoveEntry(TgtAddrIdx);
      }
    }
  }
  else
  {
    /* nothing to do here */
  }
} /* IpV6_Ndp_VProcessNsforSlaac() */
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VNsValidateTargetAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNsValidateTargetAddress(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
  IPV6_P2C(uint8)                    PhysAddrPtr,
  IPV6_P2V(uint8)                    ResponseNaRSOFlagsPtr,
  IpV6_AddrTypeType                  SrcAddrType,
  IPV6_P2C(IpV6_AddrType)            TargetAddrPtr)
{
  Std_ReturnType result = E_OK;
  IpV6_LocAddrStateType    MatchingSrcAddrState;
  /* controller address index of target address in neighbor solicitation */
  TcpIp_SizeOfIpV6SourceAddressType  tgtAddrIdx;

#if (TCPIP_SUPPORT_NDP_DAD == STD_OFF)
    TCPIP_UNUSED_PARAMETER(PhysAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  if (E_OK == IpV6_VSATLookup(IpCtrlIdx, TargetAddrPtr, &tgtAddrIdx))
  {
    MatchingSrcAddrState = TcpIp_GetAddrIpV6SourceAddressTableEntry(tgtAddrIdx)->State;

    if (   (IPV6_LADDR_STATE_PREFERRED  == MatchingSrcAddrState)
        || (IPV6_LADDR_STATE_DEPRECATED == MatchingSrcAddrState))
    {
      /* solicitation for valid local address */
      if (IPV6_ADDR_TYPE_UNSPECIFIED == SrcAddrType)
      {
        /* Sender of the solicitation is performing DAD for one of our source addresses. Send answer... */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->TargetAddr, *TargetAddrPtr);
        TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->RSOFlags = IPV6_NDP_NA_FLAG_OVERRIDE;
        TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->Pending  = TRUE;
      }
      else
      {
        *ResponseNaRSOFlagsPtr = IPV6_NDP_NA_FLAG_SOLICITED | IPV6_NDP_NA_FLAG_OVERRIDE;
      }
    }
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
# if (TCPIP_SUPPORT_NDP_DAD_OPTIMISTIC == STD_ON)
    else if (IPV6_LADDR_STATE_OPTIMISTIC == MatchingSrcAddrState)
    {
      /* solicitation for optimistic address (Optimistic DAD) */
      /* [RFC4429 3.3 Modifications to RFC 2462 Stateless Address Autoconfiguration]
        * modifies [RFC4862 5.4.3. Receiving Neighbor Solicitation Messages]
        */
      if (IPV6_ADDR_TYPE_UNSPECIFIED == SrcAddrType)
      {
        /* "The node MUST NOT reply to a Neighbor Solicitation for an Optimistic Address
          *  from the unspecified address. Receipt of such an NS indicates that the address
          *  is a duplicate, and it MUST be deconfigured as per the behaviour specified in
          *  RFC 2462 for Tentative addresses."
          */
        IpV6_VHandleDADFailure(PhysAddrPtr, tgtAddrIdx, IPV6_DAD_FAIL_NS);
        IpV6_VSATRemoveEntry(tgtAddrIdx);
      }
      else
      {
        /* "The node MUST reply to a Neighbor Solicitation for an Optimistic Address from
          *  a unicast address, but the reply MUST have the Override flag cleared (O=0)."
          */
        *ResponseNaRSOFlagsPtr = IPV6_NDP_NA_FLAG_SOLICITED;
      }
    }
# endif
    else /* if (IPV6_LADDR_STATE_TENTATIVE == MatchingSrcAddrState) */
    {
      IpV6_Ndp_VProcessNsforSlaac(IpCtrlIdx, PhysAddrPtr, tgtAddrIdx, SrcAddrType);
    }
#endif
  }
  else
  {
      /* neighbor solicitation for other node */
    result = E_NOT_OK;
  }
  return result;
} /* IpV6_Ndp_VNsValidateTargetAddress */

/**********************************************************************************************************************
 *  IpV6_Ndp_VScheduleNeighborAdv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VScheduleNeighborAdv(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)  SrcAddrPtr,
  IPV6_P2C(uint8)          SrcLinkLayerAddrPtr,
  uint8                    ResponseNaRSOFlags,
  IPV6_P2C(IpV6_AddrType)  TargetAddrPtr)
{
  TcpIp_SizeOfIpV6NeighborCacheEntryType  ncEntryIdx;

  if ((ResponseNaRSOFlags & IPV6_NDP_NA_FLAG_SOLICITED) != 0u)
  {
    /* schedule sending of solicited Neighbor Advertisement */

    /* NS for valid local address (RFC4861 7.2.3) */
    /* create or update neighbor entry and store link-layer address of sender */
    IpV6_Ndp_VNCGetOrCreateEntry(IpCtrlIdx, SrcAddrPtr, &ncEntryIdx);

    if (NULL_PTR != SrcLinkLayerAddrPtr)
    {
      /* record link layer address, if contained in NS */
      /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      if (   (IPV6_REACHABLE_STATE_INCOMPLETE == TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State)
          || (FALSE == TcpIp_CmpLLAddr(&TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LinkLayerAddress[0], SrcLinkLayerAddrPtr)))
      {
        IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, ncEntryIdx, IPV6_REACHABLE_STATE_STALE);
        IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, ncEntryIdx, SrcLinkLayerAddrPtr);
      }
    }
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->NaTgtAddress, *TargetAddrPtr);
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->NaRSOFlags = ResponseNaRSOFlags;
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->NaPending  = TRUE;
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxNeighborSolicitation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VRxNeighborSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              PhysAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte)
{
  Std_ReturnType           result;
  uint8                    ipCtrlIdx;
  IpV6_NdpNsType           ndpNsData;
  IpV6_AddrTypeType        SrcAddrType;
  /* Neighbor solicitation supports only one option */
  uint16                   ValidOptOffsetList[IPV6_NDP_NANS_MAX_IDX] = {IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET};
  uint8                    ResponseNaRSOFlags = 0;

  TCPIP_ASSERT(NULL_PTR != SrcAddrPtr);
  TCPIP_ASSERT(NULL_PTR != DataPtr);
  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(ndpNsData.TargetAddress, DataPtr[IPV6_NDP_NS_MSG_OFF_TARGETADDRESS]);
  SrcAddrType = IpV6_VGetAddrType(SrcAddrPtr);

  /* validation checks (RFC4861 7.1.1) */

  /* #10 Validate the received neighbor solicitation message */
  /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly, MD_TCPIP_Rule13.5_3415_ReadOnly */
  if (   (IPV6_ADDR_TYPE_UNSPECIFIED == SrcAddrType)
      && (   (LocalAddrV6Idx != TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(ipCtrlIdx))
          || (E_OK != IpV6_VMatchPrefix(TcpIp_GetLastBcAddrPtrOfIpV6CtrlDyn(ipCtrlIdx), &IpV6_PrefixSolicitedNode.Prefix.addr[0], IpV6_PrefixSolicitedNode.PrefixLenBits))))
  {
    /* ip destination address must be a solicited node address */
    result = E_NOT_OK; /* silently ignore invalid message */
  }
  else if (E_OK != IpV6_Ndp_VValidateOptions(&DataPtr[sizeof(IpV6_NdpNsType)],
           (uint16)(LenByte - sizeof(IpV6_NdpNsType))))
  {
    result = E_NOT_OK; /* silently discard invalid solicitation */
  }
  else
  {
    /* valid solicitation recieved */
    result = E_OK;
  }

  if (result == E_OK)
  {
    /* #20 Process the options in the message */
    IpV6_Ndp_VProcessNaNsOptions(ValidOptOffsetList, DataPtr, LenByte);

    if (   (IPV6_ADDR_TYPE_UNSPECIFIED == SrcAddrType)
        && (!IPV6_NDP_IS_OPT_INVALID(ValidOptOffsetList, IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX)))
    {
      /* The Source Link-Layer Address option MUST NOT be included if the source address is
       * the unspecified address.
       */
      result = E_NOT_OK; /* discard the packet */
    }
    /* #30 Validate the target address field in the solictation message to determine if message was
     * meant for this node
     */
    else if (E_NOT_OK == IpV6_Ndp_VNsValidateTargetAddress(ipCtrlIdx, PhysAddrPtr, &ResponseNaRSOFlags, SrcAddrType, &(ndpNsData.TargetAddress)))
    {
      /* neighbor solicitation for other node */
      /* silently ignore this message */
      result = E_NOT_OK;
    }
    else
    {
      if (!IPV6_NDP_IS_OPT_INVALID(ValidOptOffsetList, IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX))
      {
        /* If SLLA option is available, update the neighbor cache entry and schedule neighbor advertisement */
        Eth_PhysAddrType SrcLLAddr;
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_LL_ADDR_COPY(SrcLLAddr, &DataPtr[ValidOptOffsetList[IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX]]);
        IpV6_Ndp_VScheduleNeighborAdv(ipCtrlIdx, SrcAddrPtr, SrcLLAddr, ResponseNaRSOFlags, &(ndpNsData.TargetAddress));
      }
      else
      {
        IpV6_Ndp_VScheduleNeighborAdv(ipCtrlIdx, SrcAddrPtr, NULL_PTR, ResponseNaRSOFlags, &(ndpNsData.TargetAddress));
      }
    }
  }
  return result;
} /* End of IpV6_Ndp_VRxNeighborSolicitation() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxNaValidateTargetAddress()
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
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VRxNaValidateTargetAddress(
  TcpIp_IpV6CtrlIterType       IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)      TgtAddrPtr,
  IPV6_P2C(uint8)              PhysAddrPtr)
{
  TcpIp_SizeOfIpV6SourceAddressType ipV6SrcAddrIdx;
  Std_ReturnType Result = E_OK;

  /* #10 Check if the provided target address is used as a source address of the Ecu */
  /* Neighbor advertisements should not have a target address, we use */
  if (E_OK == IpV6_VSATLookup(IpCtrlIdx, TgtAddrPtr, &ipV6SrcAddrIdx))
  {
#if (TCPIP_SUPPORT_NDP_DAD == STD_ON)
    IpV6_LocAddrStateType MatchingSrcAddrState;

    MatchingSrcAddrState = TcpIp_GetAddrIpV6SourceAddressTableEntry(ipV6SrcAddrIdx)->State;

    /* #20 If address is present in SAT, but state is not preferred/deprecated,
     * then remove the address from SAT and handle duplicate address failure
     */
    if (   (IPV6_LADDR_STATE_PREFERRED  != MatchingSrcAddrState)
        && (IPV6_LADDR_STATE_DEPRECATED != MatchingSrcAddrState))
    {
      /* DAD fail. tentative address is not unique! we must not use it! */
      /* DAD for non-temporary address failed */
      IpV6_VHandleDADFailure(PhysAddrPtr, ipV6SrcAddrIdx, IPV6_DAD_FAIL_NA);
      IpV6_VSATRemoveEntry(ipV6SrcAddrIdx);
    }
    else
#endif
    {
      /* #30 If address is present in SAT and is in preferred/deprecated state,
       * handle duplicate address detection
       */
      /* Someone has sent a neighbor advertisement with an address which is used by us */
      /* #-- Handle duplicate address. This handling includes PhysAddr comparison! */
      TcpIp_LocalAddrV6IterType localAddrV6Idx = TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx);
      TcpIp_VDuplicateAddrDetected((TcpIp_LocalAddrIdType) TCPIP_IPV6_TO_LOCAL_ADDR_IDX(localAddrV6Idx), &TgtAddrPtr->addr[0], PhysAddrPtr);

    }

    Result = E_NOT_OK; /* Neighbor advertisement for own ip address received */
  }

  return Result;
}


/**********************************************************************************************************************
 *  IpV6_Ndp_VNCHandleTgtLLAddrChangedFlag()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCHandleTgtLLAddrChangedFlag(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx,
  IpV6_NdpNaFlagsType                    Flags)
{
  if (Flags.Override == FALSE) /* Check if override is set or not */
  {
    if (TRUE == Flags.TgtLLAddrChanged) /* Check if link-layer address has changed from previous value */
    {
      /* If the override flag has not been set, do not update the neighbor cache with the
       * new address.
       */
      if (IPV6_REACHABLE_STATE_REACHABLE == TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->State)
      {
        /* If entry was previously reachable, update entry to stale */
        IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, NcEntryIdx, IPV6_REACHABLE_STATE_STALE);
      }
      else
      {
        /* Nothing to be done if entry is not reachable */
      }
    }
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCHandleSolicitedFlag()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCHandleSolicitedFlag(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx,
  IPV6_P2C(IpV6_AddrType)                TgtAddrPtr,
  IPV6_P2C(uint8)                        TgtLLAddrPtr,
  IpV6_NdpNaFlagsType                    Flags)
{
  if ((TRUE == Flags.Override) || (FALSE == Flags.TgtLLAddrChanged)) /* II. */
  {
    if ((TRUE == Flags.TgtLLAddrChanged) && (NULL_PTR != TgtLLAddrPtr))
    {
      /* record link-layer address (if changed) */
      IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, NcEntryIdx, TgtLLAddrPtr);
    }

    if (TRUE == Flags.Solicited) /* solicited? */
    {
      IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, NcEntryIdx, IPV6_REACHABLE_STATE_REACHABLE);
    }
    else if (TRUE == Flags.TgtLLAddrChanged) /* not solicited, but different link-layer address */
    {
      IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, NcEntryIdx, IPV6_REACHABLE_STATE_STALE);
    }
    else /* not solicited, no changed target link-layer address */
    {
      /* entry state remains uncahnged */
    }

    if (TRUE == Flags.Router) /* IsRouter? */
    {
      if (FALSE == TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->IsRouter)
      {
        /* host has become a router. just update the flag in the cache */
        TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->IsRouter = TRUE;
      }
    }
    else /* not IsRouter? */
    {
      if (TRUE == TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->IsRouter)
      {
        TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx = 
          TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);

        /* host is no router anymore. */
        TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->IsRouter = FALSE;

        /*  remove the host from the router list */
        if (E_OK == IpV6_Ndp_VDRLLookup(IpCtrlIdx, TgtAddrPtr, &drlEntryIdx, TCPIP_LOCAL_ADDR_V6_IDX_ANY))
        {
          IpV6_Ndp_VDRLRemoveEntry(IpCtrlIdx, drlEntryIdx);
        }

        /* update all destination cache entries using this neighbor as a router */
        IpV6_Ndp_VDCRemoveEntries(IpCtrlIdx, TgtAddrPtr);
      }
    }
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessNaNsOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessNaNsOptions(
  IPV6_P2V(uint16)          ValidOptOffsetList,
  IPV6_P2C(uint8)           DataPtr,
  uint16                    LenByte)
{
  Eth_PhysAddrType ipLLAddr;
  uint16 DataOffset = sizeof(IpV6_NdpNsType);
  uint16 OptLenByte, optLenDWord;

  while (DataOffset < LenByte)
  {
    optLenDWord = DataPtr[(uint16) DataOffset + 1u];
    OptLenByte = (optLenDWord * 8u);

    switch (DataPtr[DataOffset])
    {
      /* OPTION: Source Link-Layer Address */
      case IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR:
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_LL_ADDR_COPY(&ipLLAddr[0], &DataPtr[DataOffset + 2u]);
        if (!IPV6_LL_ADDR_IS_INVALID(ipLLAddr))
        {
          /* update only if address is valid */
          ValidOptOffsetList[IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX] = DataOffset + 2u;
        }
      break;

      /* OPTION: Target Link-Layer Address */
      case IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR:
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_LL_ADDR_COPY(&ipLLAddr[0], &DataPtr[DataOffset + 2u]);
        if (!IPV6_LL_ADDR_IS_INVALID(ipLLAddr))
        {
          /* update only if address is valid */
          ValidOptOffsetList[IPV6_NDP_OPT_TARGET_LL_ADDR_IDX] = DataOffset + 2u;
        }
      break;

      /* OPTION: UNKNOWN */
      default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
        /* Default case left blank intentionally */
        break;
    }

    DataOffset += OptLenByte; /* skip to next option */
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdatewithNaFlags()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNCUpdatewithNaFlags(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  IPV6_P2C(uint8)                        IpLLAddrPtr,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx,
  IpV6_NdpNaFlagsType                    Flags)
{
  Std_ReturnType Result = E_OK;
  if (NULL_PTR == IpLLAddrPtr) /* no target link-layer address? */
  {
    /* we don't have any link-layer address of the node so far,
        since this advertisement does not contain one, it is useless */
    /* silently discard the advertisement */
    Result = E_NOT_OK;
  }
  else
  {
    /* record link-layer address */
    IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, NcEntryIdx, IpLLAddrPtr);

    if (TRUE == Flags.Solicited) /* solicited? */
    {
      IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, NcEntryIdx, IPV6_REACHABLE_STATE_REACHABLE);
    }
    else /* not solicited */
    {
      IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, NcEntryIdx, IPV6_REACHABLE_STATE_STALE);
    }

    if (TRUE == Flags.Router) /* IsRouter flag set? */
    {
      TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->IsRouter = TRUE;
    }

    /* NOTE: the override flag is ignored if the entry is in incomplete state */

    /* If there are any queued packets for this neighbor, trigger sending.
      * Since we do not use packets queues currently nothig has do be done here.
      */
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VNaUpdateRSOFlags()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNaUpdateRSOFlags(
  uint8                           RSOReserved,
  IPV6_P2V(IpV6_NdpNaFlagsType)   FlagsPtr)
{

  FlagsPtr->Router    = (((RSOReserved & IPV6_NDP_NA_FLAG_ROUTER)    != 0u) ? TRUE : FALSE);
  FlagsPtr->Solicited = (((RSOReserved & IPV6_NDP_NA_FLAG_SOLICITED) != 0u) ? TRUE : FALSE);
  FlagsPtr->Override  = (((RSOReserved & IPV6_NDP_NA_FLAG_OVERRIDE)  != 0u) ? TRUE : FALSE);
  FlagsPtr->SrcLLAddrChanged = FALSE;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VNaValidateMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNaValidateMessage(
  TcpIp_LocalAddrV6IterType                         LocalAddrV6Idx,
  IPV6_P2C(uint8)                                   DataPtr,
  uint16                                            LenByte)
{
  Std_ReturnType Result;
  IpV6_NdpNaType ndpNaData;
  boolean solicitedFlag;

  ndpNaData.RSOReserved = TCPIP_GET_UINT8(DataPtr, IPV6_NDP_NA_MSG_OFF_RSORESERVED);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(ndpNaData.TargetAddress, DataPtr[IPV6_NDP_NA_MSG_OFF_TARGETADDRESS]);

  /* Get Solicited Flag */
  solicitedFlag = (boolean)((0u != (ndpNaData.RSOReserved & IPV6_NDP_NA_FLAG_SOLICITED)) ? TRUE : FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* ignore message if target address is multicast (RFC4861 7.1.2) */
  if (IPV6_ADDR_TYPE_MULTICAST == IpV6_VGetAddrType(&ndpNaData.TargetAddress))
  {
    Result = E_NOT_OK; /* ignore invalid message */
  }
  else if ((TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == FALSE) && (TRUE == solicitedFlag))  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* ignore message if destination address is multicast and the solicited flag is set (RFC4861 7.1.2) */
    Result = E_NOT_OK; /* ignore invalid message */
  }
  else
  {
    Result = IpV6_Ndp_VValidateOptions(&DataPtr[sizeof(IpV6_NdpNsType)], (uint16)(LenByte - sizeof(IpV6_NdpNsType)));
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxNeighborAdvertisement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VRxNeighborAdvertisement(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              PhysAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte)
{
  Std_ReturnType                                       result;
  uint8                                                ipCtrlIdx;
  IpV6_NdpNaType                                       ndpNaData;
  uint16                                               ValidOptOffsetList[IPV6_NDP_NANS_MAX_IDX]= {IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET};
  Eth_PhysAddrType                                     TgtLLAddr;
  TcpIp_SizeOfIpV6NeighborCacheEntryType               ncEntryIdx;

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* copy NA data into local struct object */
  ndpNaData.RSOReserved = TCPIP_GET_UINT8(DataPtr, IPV6_NDP_NA_MSG_OFF_RSORESERVED);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(ndpNaData.TargetAddress, DataPtr[IPV6_NDP_NA_MSG_OFF_TARGETADDRESS]);

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(NULL_PTR != DataPtr);

  IPV6_UNUSED_PARAMETER(SrcAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  ncEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(ipCtrlIdx);

  /* perform message validation */
  if (E_NOT_OK == IpV6_Ndp_VNaValidateMessage(LocalAddrV6Idx, DataPtr, LenByte))
  {
    /* invalid Neighbor Advertisement received */
    result = E_NOT_OK;
  }
  else if (E_NOT_OK == IpV6_Ndp_VRxNaValidateTargetAddress(ipCtrlIdx, &ndpNaData.TargetAddress, PhysAddrPtr))
  {
    /* Neighbor advertisements should not have a target address, we use */
    result = E_NOT_OK; /* Neighbor advertisement for own ip address received */
  }
  /* no neighbor cache entry exists? */
  else if (E_OK != IpV6_Ndp_VNCLookup(ipCtrlIdx, &ndpNaData.TargetAddress, &ncEntryIdx))
  {
    /* no entry found in neighbor cache, ignore the advertisement (RFC4861 7.2.5)*/
    result = E_NOT_OK;
  }
  else
  {
    /* valid advertisement received */
    result = E_OK;
  }

  /* process TLV options if validation sucessful */
  if (result == E_OK)
  {
    IpV6_NdpNaFlagsType flags = { FALSE, FALSE, FALSE, FALSE, FALSE };

    /* Copy Flags into local struct */
    IpV6_Ndp_VNaUpdateRSOFlags(ndpNaData.RSOReserved, &flags);

    IpV6_Ndp_VProcessNaNsOptions(ValidOptOffsetList, DataPtr, LenByte);
    if (!IPV6_NDP_IS_OPT_INVALID(ValidOptOffsetList, IPV6_NDP_OPT_TARGET_LL_ADDR_IDX))
    {
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_LL_ADDR_COPY(TgtLLAddr, &DataPtr[ValidOptOffsetList[IPV6_NDP_OPT_TARGET_LL_ADDR_IDX]]);
      if (FALSE == TcpIp_CmpLLAddr(TgtLLAddr, &TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LinkLayerAddress[0]))
      {
        flags.TgtLLAddrChanged = TRUE;
      }
      else
      {
        flags.TgtLLAddrChanged = FALSE;
      }

      if (IPV6_REACHABLE_STATE_INCOMPLETE == TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State)
      {
        (void)IpV6_Ndp_VNCUpdatewithNaFlags(ipCtrlIdx, TgtLLAddr, ncEntryIdx, flags);
      }
      else /* other state than INCOMPLETE */
      {
        IpV6_Ndp_VNCHandleTgtLLAddrChangedFlag(ipCtrlIdx, ncEntryIdx, flags); /* I.*/

        IpV6_Ndp_VNCHandleSolicitedFlag(ipCtrlIdx, ncEntryIdx, &ndpNaData.TargetAddress, TgtLLAddr, flags); /* II. */

      }
    }
  }
} /* End of IpV6_Ndp_VRxNeighborAdvertisement() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  IpV6_Ndp_VRedirectUpdateNC()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRedirectUpdateNC(
  TcpIp_IpV6CtrlIterType  IpCtrlIdx,
  IPV6_P2C(uint8)         TgtLLAddrPtr,
  IPV6_P2C(IpV6_AddrType) TargetAddressPtr,
  boolean                 TargetEqualsDestination)
{
  TcpIp_SizeOfIpV6NeighborCacheEntryType  ncEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
  /* if a link-layer address for the target (the next hop) was provied, update or create a neighbor cache
   * entry, if the link-layer address is not known already
   */
  if (NULL_PTR  != TgtLLAddrPtr)
  {

    if (E_OK == IpV6_Ndp_VNCLookup(IpCtrlIdx, TargetAddressPtr, &ncEntryIdx))
    {
      /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      if (   (IPV6_REACHABLE_STATE_INCOMPLETE == TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State)
          || (FALSE == TcpIp_CmpLLAddr(&TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LinkLayerAddress[0], TgtLLAddrPtr)))
      {
        IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, ncEntryIdx, TgtLLAddrPtr);
        TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State = IPV6_REACHABLE_STATE_STALE;
      }
      else
      {
        /* link-layer already cached */
      }
    }
    else
    {
      IpV6_Ndp_VNCGetOrCreateEntry(IpCtrlIdx, TargetAddressPtr, &ncEntryIdx);

      IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, ncEntryIdx, TgtLLAddrPtr);
      TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State = IPV6_REACHABLE_STATE_STALE;
    }

    if (TargetEqualsDestination == FALSE)
    {
      /* different target and destination addresses indicate, that the target is a router */
      TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->IsRouter = TRUE;
    }
  }
  else
  {
    /* Do nothing */
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VRedirProcessTLVOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VRedirProcessTLVOptions(
  IPV6_P2C(uint8)           DataPtr,
  IPV6_P2C(uint8*)          TgtLLAddrPtrPtr,
  uint16                    LenByte)
{

  uint16 DataOffset = sizeof(IpV6_NdpRedirType);
  uint16 OptLenByte;
  while (DataOffset < LenByte)
  {
    uint16 optLenDWord = DataPtr[(uint16) DataOffset + 1u];
    OptLenByte = (optLenDWord * 8u);

    switch (DataPtr[DataOffset])
    {
      /* OPTION: Target Link-Layer Address */
      case IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR:

        *TgtLLAddrPtrPtr = &DataPtr[DataOffset + 2u];

        if (IPV6_LL_ADDR_IS_INVALID(*TgtLLAddrPtrPtr))
        {
          /* ignore invalid source link-layer address */
          *TgtLLAddrPtrPtr = NULL_PTR;
        }
      break;

      /* OPTION: Redirected Header */
      case IPV6_NDP_OPT_TYPE_REDIR_HEADER:

        /* TCPIP-IMPROVE: Process this option? */

      break;

      /* OPTION: UNKNOWN */
      default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
        /* Default case left blank intentionally */
        break;
        /* skip unkown options */
    }

    DataOffset += OptLenByte; /* skip to next option */
  }
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VGetFirstHopRouterAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VGetFirstHopRouterAddress(
  TcpIp_LocalAddrV6IterType                             LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType*)                              NextHopAddrPtrPtr,
  IPV6_P2C(IpV6_AddrType)                               DestinationAddressPtr,
  IPV6_P2V(Std_ReturnType)                              DcLookupResultPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DestinationCacheEntryType)   DcEntryIdxPtr)
{
  Std_ReturnType Result = E_OK;
  TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  *DcLookupResultPtr = IpV6_Ndp_VDCLookup(ipCtrlIdx, DestinationAddressPtr, DcEntryIdxPtr);

  if (E_OK == (*DcLookupResultPtr))
  {
    /* we have a destination cache entry with the first-hop router address */
    *NextHopAddrPtrPtr = &(TcpIp_GetAddrIpV6DestinationCacheEntry(*DcEntryIdxPtr)->NextHopAddress);
  }
  else
  {
    boolean DefaultRouterReachable;
    /* we do not have an entry in the destination cache. */

    /* determine first-hop router address. */
    if (TRUE == IpV6_VIsDestinationOnLink(ipCtrlIdx, DestinationAddressPtr))
    {
      /* ignore this redirect since the destination address is on-link */
      Result = E_NOT_OK;
    }
    else
    {

      if (E_NOT_OK == IpV6_VGetDefaultRouterAddr(ipCtrlIdx, LocalAddrV6Idx, DestinationAddressPtr, &DefaultRouterReachable, DcEntryIdxPtr))
      {
        /* no default router is known, we have to ignore this redirect */
        Result = E_NOT_OK;
      }
      else
      {
        *NextHopAddrPtrPtr = &(TcpIp_GetAddrIpV6DefaultRouterListEntry(*DcEntryIdxPtr)->NextHopAddress);
      }
    }
  }

  return Result;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VRedirValidate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VRedirValidate(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_LocalAddrV6IterType  LocalAddrV6Idx,
  IPV6_P2C(uint8)            DataPtr,
  IPV6_P2C(IpV6_AddrType)    SrcAddrPtr,
  uint16                     LenByte)
{
  Std_ReturnType                            Result;
  Std_ReturnType                            DcLookupResult;
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx = TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
  IPV6_P2C(IpV6_AddrType)                   NextHopAddrPtr;
  IpV6_NdpRedirType                         RedirMsg;
  /* "The IP source address of the Redirect [must be] the same as the current
      first-hop router for the specified ICMP Destination Address." */

  /* copy message into local object */
  /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(RedirMsg.DestinationAddress, DataPtr[IPV6_NDP_REDIR_MSG_OFF_DESTADDRESS]);
  IPV6_ADDR_COPY(RedirMsg.TargetAddress, DataPtr[IPV6_NDP_REDIR_MSG_OFF_TARGETADDRESS]);

  /* get the address of the first-hop router for the destination */
  if (E_NOT_OK == IpV6_Ndp_VGetFirstHopRouterAddress(LocalAddrV6Idx, &NextHopAddrPtr,
     &RedirMsg.DestinationAddress, &DcLookupResult, &dcEntryIdx))
  {
    /* Either no default router found or Destination is on link */
    Result = E_NOT_OK;
  }
  else if (!IPV6_ADDR_EQUALS(*SrcAddrPtr, *NextHopAddrPtr))
  {
    /* the redirect doesn't came from the router we use as next hop for the destination address */
    /* silently ignore invalid redirect */
    Result = E_NOT_OK;
  }
  /* the destination address must not be a multicast address */
  else if (IPV6_ADDR_IS_MULTICAST(RedirMsg.DestinationAddress))
  {
    /* silently ignore redirect with multicast destination address */
    Result = E_NOT_OK;
  }
  /* the target address (our new next hop for the destination) must be the link-local address
    * of a router, or the same as the destination address which indicats redirect to on-link destination (neighbor) */
  else if (   (!IPV6_ADDR_IS_LINK_LOCAL(RedirMsg.TargetAddress)) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           && (IpV6_CmpNetAddr(&RedirMsg.TargetAddress, &RedirMsg.DestinationAddress) == FALSE))
  {
    /* silently ignore invalid redirect */
    Result = E_NOT_OK;
  }
  else if (E_OK != IpV6_Ndp_VValidateOptions(&DataPtr[sizeof(IpV6_NdpRedirType)],
                                  (uint16)(LenByte - sizeof(IpV6_NdpRedirType))))
  {
    /* silently ignore redirect with invalid options */
    Result = E_NOT_OK;
  }
  else
  {
    /* redirect is valid */
    Result = E_OK;
  }

  /* update next hop address of destination cache entry */
  if (Result == E_OK)
  {
    if (E_OK != DcLookupResult)
    {
      IpV6_Ndp_VDCGetOrCreateEntry(IpCtrlIdx, &RedirMsg.DestinationAddress, &dcEntryIdx);
    }
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->NextHopAddress, RedirMsg.TargetAddress);
  }

  return Result;
}/* IpV6_Ndp_VRedirValidate() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxRedirect()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VRxRedirect(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte)
{
  Std_ReturnType              result;
  TcpIp_IpV6CtrlIterType      ipCtrlIdx;
  boolean                     TargetEqualsDestination;
  IPV6_P2C(uint8)             TgtLLAddrPtr = (IPV6_P2C(uint8))NULL_PTR;

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* perform message validation (see RFC4861 8.1) */

  /* routers must always send redirects from their link-local address */
  if (!IPV6_ADDR_IS_LINK_LOCAL(*SrcAddrPtr))
  {
    result = E_NOT_OK; /* silently ignore invalid redirect */
  }
  else if (E_NOT_OK == IpV6_Ndp_VRedirValidate(ipCtrlIdx, LocalAddrV6Idx, DataPtr, SrcAddrPtr, LenByte))
  {
   /* invalid redirect received */
    result = E_NOT_OK;
  }
  else
  {
    /* valid redirect received */
    result = E_OK;
  }

  /* process if valid redirect recieved */
  if (result == E_OK)
  {
    IpV6_NdpRedirType RedirMsg;
    /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(RedirMsg.DestinationAddress, DataPtr[IPV6_NDP_REDIR_MSG_OFF_DESTADDRESS]);
    IPV6_ADDR_COPY(RedirMsg.TargetAddress, DataPtr[IPV6_NDP_REDIR_MSG_OFF_TARGETADDRESS]);

    TargetEqualsDestination = IpV6_CmpNetAddr(&RedirMsg.TargetAddress, &RedirMsg.DestinationAddress);

    IpV6_Ndp_VRedirProcessTLVOptions(DataPtr, &TgtLLAddrPtr, LenByte);

    /* if a link-layer address for the target (the next hop) was provied, update or create a neighbor cache
     * entry, if the link-layer address is not known already */
    IpV6_Ndp_VRedirectUpdateNC(ipCtrlIdx, TgtLLAddrPtr, &RedirMsg.TargetAddress, TargetEqualsDestination);
  }
} /* End of IpV6_Ndp_VRxRedirect() */

/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateandValidateLLAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VUpdateandValidateLLAddr(
  IPV6_P2C(uint8)  DataPtr,
  uint16           DataOffset)
{
  Std_ReturnType result;
  Eth_PhysAddrType ipLLAddr;
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_LL_ADDR_COPY(&ipLLAddr[0], &DataPtr[DataOffset + IPV6_NDP_LL_ADDR_OPT_OFF_ADDR]);

  if (IPV6_LL_ADDR_IS_INVALID(ipLLAddr))
  {
    /* ignore invalid source link layer address option */
    result = E_NOT_OK;
  }
  else
  {
    /* valid address option */
    result = E_OK;
  }
  return result;
}

#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VUpdateandValidateAddrList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VUpdateandValidateAddrList(
  IPV6_P2V(uint8)            IpAddrCountPtr,
  IPV6_P2C(uint8)            DataPtr,
  uint16                     DataOffset)
{
  Std_ReturnType result;
  uint16 optLenDWord = DataPtr[(uint16) DataOffset + 1u];
  uint16 OptLenByte = IPV6_NDP_CALC_OPTION_LENGTH(optLenDWord);
  uint16 AddrListLenByte = (uint16)(OptLenByte - sizeof(IpV6_NdpOptAddrListType));

  if ((0u < AddrListLenByte) && (0u == (AddrListLenByte % IPV6_ADDRESS_LEN_BYTE)))
  {
    *IpAddrCountPtr   = (uint8)(AddrListLenByte / IPV6_ADDRESS_LEN_BYTE);
    result = E_OK;
  }
  else
  {
    /* do nothing */
    result = E_NOT_OK;
  }
  return result;
}
#endif

#if ((TCPIP_SUPPORT_NDP_INV_NA == STD_ON) || (TCPIP_SUPPORT_NDP_INV_NS == STD_ON))
/**********************************************************************************************************************
 *  IpV6_Ndp_VValidatePrefixOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VValidatePrefixOptions(
  IPV6_P2V(uint16)    ValidOptOffsetList,
  IPV6_P2V(uint8)     IpAddrCountPtr,
  IPV6_P2C(uint8)     DataPtr,
  uint16              LenByte)
{
  Std_ReturnType result = E_OK;
  boolean tgtAddrListFlag = FALSE;
  uint16 DataOffset = 4; /* ignore and skip 32bit reserved filed */
  while (DataOffset < LenByte)
  {
    uint8  OptType = DataPtr[DataOffset];
    uint16 OptLenByte = IPV6_NDP_CALC_OPTION_LENGTH((uint16) DataPtr[DataOffset + 1u]);

    switch (OptType)
    {
      case IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR:
        {
          /* mandatory */
          if (E_OK == IpV6_Ndp_VUpdateandValidateLLAddr(DataPtr, DataOffset))
          {
            ValidOptOffsetList[IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX] = DataOffset;
          }
        }
      break;

      case IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR:
        {
          /* mandatory */
          if (E_OK == IpV6_Ndp_VUpdateandValidateLLAddr(DataPtr, DataOffset))
          {
            ValidOptOffsetList[IPV6_NDP_OPT_TARGET_LL_ADDR_IDX] = DataOffset;
          }
        }
      break;

      case IPV6_NDP_OPT_TYPE_SOURCE_ADDR_LIST:
        {
          /* optional */
          if (E_OK == IpV6_Ndp_VUpdateandValidateAddrList(IpAddrCountPtr, DataPtr, DataOffset))
          {
            ValidOptOffsetList[IPV6_NDP_OPT_SOURCE_ADDR_LIST_IDX] = DataOffset + (uint16) sizeof(IpV6_NdpOptAddrListType);
          }
        }
      break;

      case IPV6_NDP_OPT_TYPE_TARGET_ADDR_LIST:
        {
          tgtAddrListFlag = TRUE;
          /* mandatory for Inverse Advertisement */
          if (E_OK == IpV6_Ndp_VUpdateandValidateAddrList(IpAddrCountPtr, DataPtr, DataOffset))
          {
            ValidOptOffsetList[IPV6_NDP_OPT_TARGET_ADDR_LIST_IDX] = DataOffset + (uint16) sizeof(IpV6_NdpOptAddrListType);
          }
        }
      break;

      case IPV6_NDP_OPT_TYPE_MTU:
        /* optional */
        ValidOptOffsetList[IPV6_NDP_OPT_MTU_IDX] = DataOffset;
      break;

      default:
        /* silently ignore unknown option */
      break;
    }
    DataOffset += OptLenByte;
  }

  if (   (IPV6_NDP_IS_OPT_INVALID(ValidOptOffsetList, IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX))
      || (IPV6_NDP_IS_OPT_INVALID(ValidOptOffsetList, IPV6_NDP_OPT_TARGET_LL_ADDR_IDX))
      || ((tgtAddrListFlag == TRUE) && (IPV6_NDP_IS_OPT_INVALID(ValidOptOffsetList, IPV6_NDP_OPT_TARGET_ADDR_LIST_IDX))))
  {
    /* Source/target link layer address is invalid
     * Mandatory target link layer address option missing. silently ignore invalid message */
    result = E_NOT_OK;
  }

  return result;
} /* IpV6_Ndp_VValidatePrefixOptions() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

# if (TCPIP_ICMPV6INDADDRLISTRECEIVEDCBK == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VInvokeAddrRcvdCbk()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VInvokeAddrRcvdCbk(
  TcpIp_IpV6CtrlIterType           IpCtrlIdx,
  IPV6_P2C(uint8)                  SrcLLAddrOptPtr,
  IPV6_P2C(IpV6_AddrType)          IpAddrListPtr,
  uint8                            IpAddrCount)
{
  TcpIp_SizeOfIcmpV6IndAddrListReceivedCbkType cbkIdx;
  for (cbkIdx = 0; cbkIdx < TcpIp_GetSizeOfIcmpV6IndAddrListReceivedCbk(); cbkIdx++)
  {
    TcpIp_IcmpV6IndAddrListReceivedCbkType icmpAddrListRcvdCbkPtr = TcpIp_GetIcmpV6IndAddrListReceivedCbk(cbkIdx);
    /* notify upper layers */
    icmpAddrListRcvdCbkPtr(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), SrcLLAddrOptPtr, IpAddrListPtr, IpAddrCount);
  }
}
#endif

#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VRxInverseSolicitation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VRxInverseSolicitation(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte)
{
  Std_ReturnType                              result;
  uint8                                       ipCtrlIdx;
  uint16                                      DataOffset;
  uint16                                      validOptOffsetList[IPV6_NDP_IND_MAX_IDX] = {IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET};
  Eth_PhysAddrType                            srcLLAddr;
  Eth_PhysAddrType                            tgtLLAddr;
  uint8                                       SrcAddrCount = 0;
  TcpIp_SizeOfIpV6NeighborCacheEntryType      ncEntryIdx;
  Eth_PhysAddrType                            ThisTgtLLAddr;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(NULL_PTR != SrcAddrPtr);
  TCPIP_ASSERT(NULL_PTR != DataPtr);

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(ipCtrlIdx), &ThisTgtLLAddr[0]);

  DataOffset = 4; /* ignore and skip 32bit reserved filed */

  /* NDP option valiadtion roules also apply to [RFC3122] */
  if (E_OK != IpV6_Ndp_VValidateOptions(&DataPtr[DataOffset], LenByte - DataOffset))
  {
    result = E_NOT_OK; /* silently discard inverse solicitation with invalid options */
  }
  else if (E_NOT_OK == IpV6_Ndp_VValidatePrefixOptions(validOptOffsetList, &SrcAddrCount, DataPtr, LenByte))
  {
    /* mandatory option missing. silently ignore invalid message */
    result = E_NOT_OK;
  }
  else
  {
    /* Target link layer address option is present */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(&tgtLLAddr[0],
      &DataPtr[validOptOffsetList[IPV6_NDP_OPT_TARGET_LL_ADDR_IDX] + IPV6_NDP_LL_ADDR_OPT_OFF_ADDR]);

    if (FALSE == TcpIp_CmpLLAddr(&tgtLLAddr[0], &ThisTgtLLAddr[0]))
    {
      /* ignore solicitation sent to different target */
      result = E_NOT_OK;
    }
    else
    {
      /* message with valid option received */
       result = E_OK;
    }
  }

  /* message validated, now process options */
  if (result == E_OK)
  {
    /* update the mandatory opt pointers */ /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(&srcLLAddr[0], &DataPtr[validOptOffsetList[IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX] + IPV6_NDP_LL_ADDR_OPT_OFF_ADDR]);

#if (TCPIP_ICMPV6INDADDRLISTRECEIVEDCBK == STD_ON)
    if (!IPV6_NDP_IS_OPT_INVALID(validOptOffsetList, IPV6_NDP_OPT_SOURCE_ADDR_LIST_IDX))
    {
      /* PRQA S 0310, 3305 2 */ /* MD_TCPIP_Rule11.3_0310_3305_AddrList */
      IPV6_P2C(IpV6_AddrType) SrcAddrListPtr =
        (IPV6_P2C(IpV6_AddrType))&DataPtr[validOptOffsetList[IPV6_NDP_OPT_SOURCE_ADDR_LIST_IDX]];

      IpV6_Ndp_VInvokeAddrRcvdCbk(ipCtrlIdx, &srcLLAddr[0], SrcAddrListPtr, SrcAddrCount);
    }
#endif

    if (!IPV6_NDP_IS_OPT_INVALID(validOptOffsetList, IPV6_NDP_OPT_MTU_IDX))
    {
      /* optional MTU Option present */
    }

    IpV6_Ndp_VNCGetOrCreateEntry(ipCtrlIdx, SrcAddrPtr, &ncEntryIdx);

    /* record link layer address, contained in IS */
    /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    if (   (IPV6_REACHABLE_STATE_INCOMPLETE == TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State)
        || (FALSE == TcpIp_CmpLLAddr(&TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->LinkLayerAddress[0], &srcLLAddr[0])))
    {
      IpV6_Ndp_VNCUpdateEntry(ipCtrlIdx, ncEntryIdx, IPV6_REACHABLE_STATE_STALE);
      IpV6_Ndp_VNCUpdateLinkLayerAddress(ipCtrlIdx, ncEntryIdx, &srcLLAddr[0]);
    }
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->InvNsSrcAddress, *SrcAddrPtr);
    TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->InvNaPending  = TRUE;
  }
} /* End of IpV6_Ndp_VRxInverseSolicitation() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_Ndp_VTxInverseAdvertisement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxInverseAdvertisement(
  IPV6_P2C(TcpIp_LocalAddrV6IterType)  LocalAddrV6IdxPtr,
  IPV6_P2C(IpV6_AddrType)              DstAddrPtr,
  IPV6_P2C(uint8)                      TgtLLAddrPtr)
{
  TcpIp_IpV6CtrlIterType          ipCtrlIdx;
  TcpIp_IpTxRequestDescriptorType IpTxReqDesc;
  IPV6_P2V(uint8)                 IcmpBufPtr;
  uint16                          IcmpBufLen;
  Std_ReturnType                  Result;
  uint16                          IcmpBufOffset;
  TcpIp_LocalAddrV6IterType       localAddrV6Idx;

  TCPIP_ASSERT(NULL_PTR != LocalAddrV6IdxPtr);
  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);
  TCPIP_ASSERT((*LocalAddrV6IdxPtr) < TcpIp_GetSizeOfLocalAddrV6());

  localAddrV6Idx = *LocalAddrV6IdxPtr;
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);

  IPV6_BEGIN_CRITICAL_SECTION_SAT();

  IcmpBufLen = ((uint16) sizeof(IpV6_NdpIaType) + (uint16) sizeof(IpV6_NdpOptLLAddrType) + (uint16) sizeof(IpV6_NdpOptAddrListType) +
               ((uint16) TcpIp_GetSizeOfIpV6SourceAddressTableEntry() * IPV6_ADDRESS_LEN_BYTE));

  if (BUFREQ_OK == IpV6_Icmp_ProvideTxBuffer(&localAddrV6Idx,
    TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),
    &IpTxReqDesc, DstAddrPtr, &IcmpBufPtr, &IcmpBufLen))
  {
    IcmpBufPtr[IPV6_NDP_INA_MSG_OFF_RESERVED32] = 0u;
    IcmpBufOffset = sizeof(IpV6_NdpIaType);

    /* add mandatory Source Link-Layer Address Option */
    IpV6_Ndp_VWriteLLAddrOpt(ipCtrlIdx, IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR, &IcmpBufPtr[IcmpBufOffset]);
    IcmpBufOffset += (uint16) sizeof(IpV6_NdpOptLLAddrType);

    /* add mandatory Target Link-Layer Address Option */
    IcmpBufPtr[IcmpBufOffset] = IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR;
    IcmpBufPtr[IcmpBufOffset + 1u] = 1u; /* 1*8 byte */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(&IcmpBufPtr[IcmpBufOffset + 2u], TgtLLAddrPtr);
    IcmpBufOffset += (uint16) sizeof(IpV6_NdpOptLLAddrType);

    /* add mandatory Target Address List Option */
    IcmpBufOffset += IpV6_Ndp_VWriteAddrListOpt(ipCtrlIdx,
      IPV6_NDP_OPT_TYPE_TARGET_ADDR_LIST, &IcmpBufPtr[IcmpBufOffset]);
    /* BufOffset invalid from this point */

    if (E_OK == IpV6_Icmp_Transmit(TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), &IpTxReqDesc, IPV6_ICMP_MSG_TYPE_NDP_INV_NA, 0, IcmpBufOffset))
    {
      Result = E_OK;
    }
    else
    {
      Result = E_NOT_OK;
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  IPV6_END_CRITICAL_SECTION_SAT();

  return Result;
} /* End of IpV6_Ndp_VTxInverseAdvertisement() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif

#if (TCPIP_SUPPORT_NDP_INV_NA == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VTxInverseSolicitation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxInverseSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(uint8)              TgtLLAddrPtr,
  boolean                      IncludeSrcAddrList)
{
  TcpIp_LocalAddrV6IterType       localV6IpAddrIdx = LocalAddrV6Idx;
  TcpIp_IpV6CtrlIterType          ipCtrlIdx;
  TcpIp_IpTxRequestDescriptorType IpTxReqDesc;
  IPV6_P2V(uint8)                 IcmpBufPtr;
  uint16                          IcmpBufLen;
  Std_ReturnType                  Result;
  uint16                          IcmpBufOffset;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(NULL_PTR != TgtLLAddrPtr);

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  IPV6_BEGIN_CRITICAL_SECTION_SAT();

  IcmpBufLen = (sizeof(IpV6_NdpIsType) + (2u * sizeof(IpV6_NdpOptLLAddrType)));

  if (TRUE == IncludeSrcAddrList)
  {
    IcmpBufLen += ((uint16)sizeof(IpV6_NdpOptAddrListType) +
      ((uint16)TcpIp_GetSizeOfIpV6SourceAddressTableEntry() * IPV6_ADDRESS_LEN_BYTE));
  }

  if (BUFREQ_OK == IpV6_Icmp_ProvideTxBuffer(&localV6IpAddrIdx, TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), &IpTxReqDesc, &IpV6_AddrAllNodesLL, &IcmpBufPtr, &IcmpBufLen))
  {
    IcmpBufPtr[IPV6_NDP_INS_MSG_OFF_RESERVED32] = 0u;
    IcmpBufOffset = sizeof(IpV6_NdpIsType);

    /* add mandatory Source Link-Layer Address Option */
    IpV6_Ndp_VWriteLLAddrOpt(ipCtrlIdx, IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR, &IcmpBufPtr[IcmpBufOffset]);
    IcmpBufOffset += (uint16) sizeof(IpV6_NdpOptLLAddrType);

    /* add mandatory Target Link-Layer Address Option */
    IcmpBufPtr[IcmpBufOffset] = IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR;
    IcmpBufPtr[IcmpBufOffset + 1u] = 1u; /* 1*8 byte */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(&IcmpBufPtr[IcmpBufOffset + 2u], TgtLLAddrPtr);
    IcmpBufOffset += (uint16) sizeof(IpV6_NdpOptLLAddrType);

    if (TRUE == IncludeSrcAddrList)
    {
      /* add optional Source Address List Option */
      IcmpBufOffset +=
        IpV6_Ndp_VWriteAddrListOpt(ipCtrlIdx, IPV6_NDP_OPT_TYPE_SOURCE_ADDR_LIST, &IcmpBufPtr[IcmpBufOffset]);
    }

    TcpIp_SetIcmpNextHopLLAddrOverrideOfIpV6CtrlDyn(ipCtrlIdx,TRUE);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(TcpIp_GetAddrIcmpNextHopLLAddrOverrideValueOfIpV6CtrlDyn(ipCtrlIdx), TgtLLAddrPtr);

    if (E_OK == IpV6_Icmp_Transmit(TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), &IpTxReqDesc, IPV6_ICMP_MSG_TYPE_NDP_INV_NS, 0, IcmpBufOffset))
    {
      Result = E_OK;
    }
    else
    {
      Result = E_NOT_OK;
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  IPV6_END_CRITICAL_SECTION_SAT();

  return Result;
} /* End of IpV6_Ndp_VTxInverseSolicitation() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

# if (TCPIP_SUPPORT_NDP_INV_NA_NC_UPDATE == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdateTargetAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VNCUpdateTargetAddress(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)    TgtAddrListPtr,
  IPV6_P2C(uint8)            SrcLLAddrPtr,
  uint8                      TgtAddrCount)
{
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
  uint8  TgtAddrListIdx;
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (TcpIp_IsEnableNdpInvNaNcUpdateOfNdpConfig(ndpConfigIdx) == TRUE)
  {
    TgtAddrListIdx = TgtAddrCount;

    /* Lookup each address of the target address list in Neighbor Cache and record link-layer
     * address if there exists an INCOMPLETE entry
     */
    while (TgtAddrListIdx > 0u)
    {
      TgtAddrListIdx--;

      if (E_OK == IpV6_Ndp_VNCLookup(IpCtrlIdx, &TgtAddrListPtr[TgtAddrListIdx], &NcEntryIdx))
      {
        if (IPV6_REACHABLE_STATE_INCOMPLETE == TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->State)
        {
          /* record link-layer address and set entry state to STALE.
           * This will allow communication with the neighbor but cause NUD to verify the entry.
           */
          IpV6_Ndp_VNCUpdateLinkLayerAddress(IpCtrlIdx, NcEntryIdx, SrcLLAddrPtr);
          IpV6_Ndp_VNCUpdateEntry(IpCtrlIdx, NcEntryIdx, IPV6_REACHABLE_STATE_STALE);
        }
      }
    }
  }
}
# endif


/**********************************************************************************************************************
 *  IpV6_Ndp_VRxInverseAdvertisement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VRxInverseAdvertisement(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte)
{
  Std_ReturnType                              result;
  uint16                                      validOptOffsetList[IPV6_NDP_IND_MAX_IDX] = {IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET, IPV6_NDP_OPT_INVALID_OFFSET};
  uint8                                       ipCtrlIdx;
  uint16                                      DataOffset;
  Eth_PhysAddrType                            srcLLAddr;
  Eth_PhysAddrType                            tgtLLAddr;
  IPV6_P2C(IpV6_AddrType)                     TgtAddrListPtr;

  uint8                                       TgtAddrCount      = 0;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(NULL_PTR != DataPtr);

  IPV6_UNUSED_PARAMETER(SrcAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  DataOffset = 4; /* ignore and skip 32bit reserved filed */

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* NDP option valiadtion roules also apply to [RFC3122] */
  if (E_OK != IpV6_Ndp_VValidateOptions(&DataPtr[DataOffset], LenByte - DataOffset))
  {
    result = E_NOT_OK; /* silently discard inverse advertisement with invalid options */
  }
  else if (E_NOT_OK == IpV6_Ndp_VValidatePrefixOptions(validOptOffsetList, &TgtAddrCount, DataPtr, LenByte))
  {
    /* mandatory option missing */
    result = E_NOT_OK;
  }
  else
  {
    /* valid advertisement recieved */
    result = E_OK;
  }

  /* message validated, now process options */
  if (result == E_OK)
  {
    /* update the mandatory opt pointers */
    /* Source link layer address is valid, copy to local variable */ /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(&srcLLAddr[0],
      &DataPtr[validOptOffsetList[IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX] + IPV6_NDP_LL_ADDR_OPT_OFF_ADDR]);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(&tgtLLAddr[0],
      &DataPtr[validOptOffsetList[IPV6_NDP_OPT_TARGET_LL_ADDR_IDX] + IPV6_NDP_LL_ADDR_OPT_OFF_ADDR]);

    /* PRQA S 0310, 3305 2 */ /* MD_TCPIP_Rule11.3_0310_3305_AddrList */
    TgtAddrListPtr =
      (IPV6_P2C(IpV6_AddrType))&DataPtr[validOptOffsetList[IPV6_NDP_OPT_TARGET_ADDR_LIST_IDX]];

    if (!IPV6_NDP_IS_OPT_INVALID(validOptOffsetList, IPV6_NDP_OPT_MTU_IDX))
    {
      /* optional MTU Option present */
    }

    if (0u < TcpIp_GetNdp_PendingInvNsOfIpV6CtrlDyn(ipCtrlIdx).TxCount)
    {
      if (TRUE == TcpIp_CmpLLAddr(&tgtLLAddr[0], (TCPIP_P2C(uint8))&(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(ipCtrlIdx)->TargetPhysAddr[0])))
      {
        /* answer to pending inverse solicitation received. stop sending retransmissions */
        TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(ipCtrlIdx)->TxCount = 0;
      }
    }

# if (TCPIP_SUPPORT_NDP_INV_NA_NC_UPDATE == STD_ON)
    IpV6_Ndp_VNCUpdateTargetAddress(ipCtrlIdx, TgtAddrListPtr, &srcLLAddr[0], TgtAddrCount);
# endif

# if (TCPIP_ICMPV6INDADDRLISTRECEIVEDCBK == STD_ON)
    IpV6_Ndp_VInvokeAddrRcvdCbk(ipCtrlIdx, &srcLLAddr[0], TgtAddrListPtr, TgtAddrCount);
# endif
  }
} /* End of IpV6_Ndp_VRxInverseAdvertisement() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif



/**********************************************************************************************************************
 *  IpV6_Ndp_VTxNeighborAdvertisement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxNeighborAdvertisement(
  IPV6_P2V(TcpIp_LocalAddrV6IterType) LocalAddrV6IdxPtr,
  IPV6_P2C(IpV6_AddrType)             DstAddrPtr,
  IPV6_P2C(IpV6_AddrType)             TargetAddrPtr,
  uint8                               RSOFlags)
{
  Std_ReturnType                           result;
  TcpIp_IpV6CtrlIterType                   ipCtrlIdx;
  TcpIp_IpTxRequestDescriptorType          IpTxReqDesc;
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)   IcmpBufPtr;
  uint16                                   IcmpBufLen;
  uint16                                   IcmpPayloadLen = 0;

  TCPIP_ASSERT(NULL_PTR != LocalAddrV6IdxPtr);
  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);
  TCPIP_ASSERT(NULL_PTR != TargetAddrPtr);
  TCPIP_ASSERT((*LocalAddrV6IdxPtr) < TcpIp_GetSizeOfLocalAddrV6());

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(*LocalAddrV6IdxPtr);

  IcmpBufLen = sizeof(IpV6_NdpNaType) + 8u; /* 8 = LL option length */

  if (BUFREQ_OK != IpV6_Icmp_ProvideTxBuffer(LocalAddrV6IdxPtr,
    TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),
    &IpTxReqDesc, DstAddrPtr, &IcmpBufPtr, &IcmpBufLen))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* update message fields */
    IcmpBufPtr[IPV6_NDP_NA_MSG_OFF_RSORESERVED] = (uint8)(RSOFlags & 0xE0u); /* Mask: 11100000 */
    IcmpBufPtr[IPV6_NDP_NA_MSG_OFF_RESERVED8] = 0u;
    IcmpBufPtr[IPV6_NDP_NA_MSG_OFF_RESERVED8 + 1u] = 0u;
    IcmpBufPtr[IPV6_NDP_NA_MSG_OFF_RESERVED8 + 2u] = 0u;
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(IcmpBufPtr[IPV6_NDP_NA_MSG_OFF_TARGETADDRESS], *TargetAddrPtr);
    IcmpPayloadLen += (uint16) sizeof(IpV6_NdpNsType);

    IpV6_Ndp_VWriteLLAddrOpt(ipCtrlIdx, IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR, &IcmpBufPtr[IcmpPayloadLen]);
    IcmpPayloadLen += 8u;

    result = IpV6_Icmp_Transmit(TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),
      &IpTxReqDesc, IPV6_ICMP_MSG_TYPE_NDP_NA, 0, IcmpPayloadLen);
  }

  return result;
} /* End of IpV6_Ndp_VTxNeighborAdvertisement() */


#if (TCPIP_SUPPORT_NDP_ROUTER_SOLICITATIONS == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VTxRouterSolicitation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxRouterSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  boolean                      IncludeSllaOpt)
{
  TcpIp_LocalAddrV6IterType              localIpAddrIdx = LocalAddrV6Idx;
  Std_ReturnType                         result;
  TcpIp_IpV6CtrlIterType                 ipCtrlIdx;
  TcpIp_IpTxRequestDescriptorType        IpTxReqDesc;
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR) IcmpBufPtr;
  uint16                                 IcmpBufLen;
  uint16                                 IcmpPayloadLen = 0;

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());

  ipCtrlIdx    = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
  IcmpBufLen = sizeof(IpV6_NdpRsType);

  if (BUFREQ_OK != IpV6_Icmp_ProvideTxBuffer(&localIpAddrIdx,
    TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),
    &IpTxReqDesc, &IpV6_AddrAllRoutersLL, &IcmpBufPtr, &IcmpBufLen))
  {
    result = E_NOT_OK;
  }
  else
  {
    IcmpBufPtr[IPV6_NDP_RS_MSG_OFF_RESERVED32] = 0u;
    IcmpPayloadLen += (uint16) sizeof(IpV6_NdpRsType);

    if (TRUE == IncludeSllaOpt)
    {
      /* if the source address is not the unspecified address, the source link-layer address option SHOULD be
         included in the solicitation */

      IpV6_Ndp_VWriteLLAddrOpt(ipCtrlIdx, IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR, &IcmpBufPtr[IcmpPayloadLen]);
      IcmpPayloadLen += 8u; /* size of source link-layer address option */
    }

    result = IpV6_Icmp_Transmit(TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),
      &IpTxReqDesc, IPV6_ICMP_MSG_TYPE_NDP_RS, 0, IcmpPayloadLen);
  }

  return result;
} /* End of IpV6_Ndp_VTxRouterSolicitation() */
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxNeigborSolicitation()
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
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxNeighborSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      TargetAddrPtr,
  boolean                      Unicast,
  boolean                      ForceUnspecSrcAddr)
{
  TcpIp_LocalAddrV6IterType                       localIpAddrIdx = LocalAddrV6Idx;
  Std_ReturnType                                  result;
  TcpIp_IpV6CtrlIterType                          ipCtrlIdx;
  TcpIp_IpTxRequestDescriptorType                 IpTxReqDesc;
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR)          IcmpBufPtr;
  uint16                                          IcmpBufLen;
  uint16                                          IcmpPayloadLen = 0;
  IpV6_AddrType                                   destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  IpV6_AddrType                                   srcAddr;  /* PRQA S 0759 */ /* MD_MSR_Union */

  TCPIP_ASSERT(LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(NULL_PTR != TargetAddrPtr);

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  /* #10 Determine whether the NS should be sent to unicast or solicited node multicast address */
  if (FALSE == Unicast)
  {
    /* generate solicited node multicast address */
    IpV6_VGetSolicitedNodeAddr(&destAddr, TargetAddrPtr, IPV6_MULTICAST_SCOPE_LINK_LOCAL);
  }
  else
  {
    /* send NS to target address */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(destAddr, *TargetAddrPtr);
  }

  IcmpBufLen = sizeof(IpV6_NdpNsType);

  /* #20 Request for Tx buffer */
  if (BUFREQ_OK != IpV6_Icmp_ProvideTxBuffer(&localIpAddrIdx, TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), &IpTxReqDesc, &destAddr, &IcmpBufPtr, &IcmpBufLen))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #30 If Tx buffer acquired, update the Target address field */
    IPBASE_PUT_UINT32(IcmpBufPtr, IPV6_NDP_NS_MSG_OFF_RESERVED32, 0u);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(IcmpBufPtr[IPV6_NDP_NS_MSG_OFF_TARGETADDRESS], *TargetAddrPtr);
    IcmpPayloadLen += (uint16) sizeof(IpV6_NdpNsType);

    srcAddr = IpV6_GetSrcAddress(&IpTxReqDesc);

    /* #40 Update the source address */
    if (TRUE == ForceUnspecSrcAddr)
    {
      /* #50 If caller requested to send to unspecified address, set to unspecified address */
      (void)IpV6_SetSrcAddress(&IpTxReqDesc, IpV6_AddrUnspecified);
    }
    else if (!IPV6_ADDR_IS_UNSPECIFIED(srcAddr))
    {
      /* #60 If source address is not unspecified, insert SLLA so target can directly respond to it with NA (RFC4861 4.3.) */
      IpV6_Ndp_VWriteLLAddrOpt(ipCtrlIdx, IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR, &IcmpBufPtr[IcmpPayloadLen]);
      IcmpPayloadLen += IPV6_NDP_OPT_LL_ADDR_LEN_BYTE;
    }
    else
    {
      /* nothing to do in this case */
    }

    /* #70 Transmit the packet */
    result = IpV6_Icmp_Transmit(TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),
              &IpTxReqDesc, IPV6_ICMP_MSG_TYPE_NDP_NS, 0, IcmpPayloadLen);
  }

  return result;
} /* End of IpV6_Ndp_VTxNeighborSolicitation() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdateEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VNCUpdateEntry(
  TcpIp_IpV6CtrlIterType                   IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType   NcEntryIdx,
  IpV6_ReachableStateType                  NewState)
{
#if (TCPIP_SUPPORT_NDP_NUD == STD_ON)
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NcEntryIdx < TcpIp_GetSizeOfIpV6NeighborCacheEntry());

#if (TCPIP_SUPPORT_NDP_NUD == STD_ON)
  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if ((TcpIp_IsEnableNudOfNdpConfig(ndpConfigIdx) == TRUE) && (IPV6_REACHABLE_STATE_REACHABLE == NewState))
  {
    IPV6_SET_EVENT_TIME_MS(TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->NextEventTime,
      TcpIp_GetReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx));
  }
#endif

  TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->State = NewState;
} /* End Of IpV6_Ndp_VNCUpdateEntry() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdateLinkLayerAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VNCUpdateLinkLayerAddress(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType NcEntryIdx,
  IPV6_P2C(uint8)                        NewLinkLayerAddressPtr)
{
  TcpIp_SockAddrBaseType SockAddrInet6; /* PRQA S 0759 */ /* MD_MSR_Union */

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());
  TCPIP_ASSERT(NcEntryIdx < TcpIp_GetSizeOfIpV6NeighborCacheEntry());

  SockAddrInet6.SockAddrIn6.sin6_family  = TCPIP_AF_INET6;
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(SockAddrInet6.SockAddrIn6.sin6_addr.addr[0],
    TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->NeighborAddress);
  SockAddrInet6.SockAddrIn6.sin6_port = TCPIP_PORT_ANY;

  if (NULL_PTR != NewLinkLayerAddressPtr)
  {
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(&(TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->LinkLayerAddress[0]),
      NewLinkLayerAddressPtr);
  }
  else
  {
    uint8_least AddrByteIdx = IPBASE_ETH_PHYS_ADDR_LEN_BYTE;

    while (0u < AddrByteIdx)
    {
      AddrByteIdx--;
      TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->LinkLayerAddress[AddrByteIdx] = 0x00U;
    }
  }

  TcpIp_VPhysAddrTableChg(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx),
    &SockAddrInet6, &(TcpIp_GetAddrIpV6NeighborCacheEntry(NcEntryIdx)->LinkLayerAddress[0]),
    (boolean)(NULL_PTR != NewLinkLayerAddressPtr));  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
} /* End Of IpV6_Ndp_VNCUpdateLinkLayerAddress() */


/**********************************************************************************************************************
 *  IpV6_Ndp_VStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_VStart(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  uint32           DelayMs;
  IpV6_AddrType    SrcAddrCandidate;    /* PRQA S 0759 */ /* MD_MSR_Union */
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_InterfaceIdentifierStartIdxOfIpV6CtrlType interfaceIdentifierStartIdx =
    TcpIp_GetInterfaceIdentifierStartIdxOfIpV6Ctrl(IpCtrlIdx);

  /* Reset CurHopLimit, ReachableTime and RestransTimer to configured default values.
     These values may be updated by received Router Advertisements. */
  TcpIp_SetCurHopLimitOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetDefaultHopLimitOfIpV6Ctrl(IpCtrlIdx));
  TcpIp_SetRetransTimerMsOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetRetransTimerOfNdpConfig(ndpConfigIdx));

#if (TCPIP_SUPPORT_NDP_NUD == STD_ON)
  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (TcpIp_IsEnableNudOfNdpConfig(ndpConfigIdx) == TRUE)
  {
    /* configure ReachableTime for Neighbor Unreachability Detection.
       This value may be changed by received router advertisements. */

# if (TCPIP_SUPPORT_IPV6_DYN_REACHABLE_TIME == STD_ON)
    /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
    if (TcpIp_IsRandomReachableTimeOfNdpConfig(ndpConfigIdx) == TRUE)
    {
      /* Set randomized default ReachableTime. */
      TcpIp_SetBaseReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetReachableTimeOfNdpConfig(ndpConfigIdx));
      TcpIp_SetReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetBaseReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx));
    }
    else
# endif
    {
      /* Set configured ReachableTime. */
      TcpIp_SetReachableTimeMsOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetReachableTimeOfNdpConfig(ndpConfigIdx));
    }
  }
#endif

#if (TCPIP_SUPPORT_NDP_ROUTER_SOLICITATIONS == STD_ON)
  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (0u < TcpIp_GetMaxRtrSolicitationsOfNdpConfig(ndpConfigIdx))
  {
    /* Schedule transmission of first Router Advertisement. */

    TcpIp_SetNdp_RouterSolicitationTxCountOfIpV6CtrlDyn(IpCtrlIdx, 0);

    /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
    if (TcpIp_IsRndRtrSolicitationDelayOfNdpConfig(ndpConfigIdx) == TRUE)
    {
      DelayMs = IpV6_VGetRandomValue(0, TcpIp_GetMaxRtrSolicitationDelayOfNdpConfig(ndpConfigIdx));
    }
    else
    {
      DelayMs = TcpIp_GetMaxRtrSolicitationDelayOfNdpConfig(ndpConfigIdx);
    }
    {
      IpV6_TimeType rtrSolicitNxtTime;
      IPV6_SET_EVENT_TIME_MS(rtrSolicitNxtTime, DelayMs);
      TcpIp_SetNdp_RouterSolicitationNextTxTimeOfIpV6CtrlDyn(IpCtrlIdx, rtrSolicitNxtTime);
    }
  }
#endif

  /* build link-local address */
  /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
  IpV6_MemCpy(&SrcAddrCandidate.addr[0], &IpV6_PrefixLinkLocal.Prefix.addr[0], 16u - IPV6_INTERFACE_IDENTIFIER_LEN_BYTE);
  IpV6_MemCpy(&SrcAddrCandidate.addr[16u - IPV6_INTERFACE_IDENTIFIER_LEN_BYTE], TcpIp_GetAddrInterfaceIdentifier(interfaceIdentifierStartIdx), IPV6_INTERFACE_IDENTIFIER_LEN_BYTE);

  /* join all-nodes multicast group */
  IPV6_VJOIN_MULTICAST_GROUP(IpCtrlIdx, &IpV6_AddrAllNodesLL, TRUE);
  /* The solicited-node multicast groups for source addresses will be joines in IpV6_Ndp_VAddSourceAddress() */

  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (TcpIp_IsEnableSlaacDelayOfNdpConfig(ndpConfigIdx) == TRUE)
  {
    DelayMs = IpV6_VGetRandomValue(0, TcpIp_GetMaxSlaacDelayOfNdpConfig(ndpConfigIdx));
  }
  else
  {
    DelayMs = 0;
  }

  TcpIp_SetLinkLocalDadDelayMsOfIpV6CtrlDyn(IpCtrlIdx, DelayMs);

  IPV6_BEGIN_CRITICAL_SECTION_SAT();

  /* trigger configuration of link-local source adress */
  (void)IpV6_Ndp_VAddSourceAddress(TcpIp_IpV6_GetLinkLocalSourceAddrIdxOfIpV6Ctrl(IpCtrlIdx), &SrcAddrCandidate, IPV6_LIFETIME_UNLIMITED, IPV6_LIFETIME_UNLIMITED, DelayMs, 2u);

  IPV6_END_CRITICAL_SECTION_SAT();

} /* End of IpV6_Ndp_VStart() */  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


#if (TCPIP_SUPPORT_NDP_INV_NA == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_SendInverseSolicitation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_SendInverseSolicitation(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(uint8)            TgtLLAddrPtr,
  boolean                    IncludeSrcAddrList)
{
  Std_ReturnType result = E_OK;

  if (0u < TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TxCount)
  {
    result = E_NOT_OK;
  }
  else
  {
    TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
    TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->IncludeSrcAddrList = IncludeSrcAddrList;
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_LL_ADDR_COPY(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TargetPhysAddr, TgtLLAddrPtr);
    TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TxCount =
      TcpIp_GetMulticastSolicitsOfNdpConfig(ndpConfigIdx);
    IPV6_SET_CURRENT_TIME(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->Timeout);
  }
  return result;
} /* End of IpV6_Ndp_SendInverseSolicitation() */
#endif


/**********************************************************************************************************************
 *  IpV6_Ndp_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Ndp_Init(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
#if (IPV6_NDP_ENABLE_TIMEOUT_OPTIMIZATION == STD_ON)
  IpV6_NextSourceAddressEventTimeMs = 0;
  IpV6_NextNeighborCacheEventTimeMs = 0;
  IpV6_NextDefaultRouterEventTimeMs = 0;
  IpV6_NextPrefixListEventTimeMs = 0;
#endif

#if defined(IPV6_VENABLE_CACHE_LOOKUP_OPTIMIZATION_DBG)
  IpV6_DbgNeighborCacheLookups          = 0;
  IpV6_DbgNeighborCacheHits             = 0;
  IpV6_DbgNeighborCacheOptimizedHits    = 0;
  IpV6_DbgDestinationCacheLookups       = 0;
  IpV6_DbgDestinationCacheHits          = 0;
  IpV6_DbgDestinationCacheOptimizedHits = 0;
#endif

  IpV6_VSATRemoveAllEntries(IpCtrlIdx);
  TcpIp_SetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));

  TcpIp_SetIpV6DefaultRouterListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetIpV6DefaultRouterListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));

  TcpIp_SetIpV6DestinationCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetIpV6DestinationCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));

  TcpIp_SetIpV6PrefixListEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetIpV6PrefixListEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));

  TcpIp_SetDefaultLinkMtuOfIpV6CtrlDyn(IpCtrlIdx, TcpIp_GetDefaultLinkMtuOfIpV6Ctrl(IpCtrlIdx));

  TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->Pending = FALSE;

  TcpIp_SetLinkLocalDadDelayMsOfIpV6CtrlDyn(IpCtrlIdx, TCPIP_MIN_LINKLOCALDADDELAYMSOFIPV6CTRLDYN);

#if (TCPIP_SUPPORT_NDP_INV_NA == STD_ON)
  TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TxCount = 0;
  IPV6_TIME_SET_INFINITY(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->Timeout);
#endif

  IpV6_SetHopLimit(TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), IPV6_NDP_MSG_HOP_LIMIT);
} /* End of IpV6_Ndp_Init() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_VProcessCacheStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VProcessCacheStates(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{

  /* #10 Process state of entries in Source Address Table. */
  IpV6_Ndp_VSATCheckLifetimes(IpCtrlIdx);

  /* #20 Process state of entries in Default Router List. */
  IpV6_Ndp_VDRLCheckLifetimes(IpCtrlIdx);

  /* #30 Process state of entries in Neighbor Cache. */
  IpV6_Ndp_VNCCheckLifetimes(IpCtrlIdx);

#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
  /* #40 Process state of entries in Destination Cache. */
  if (0u < TcpIp_GetPathMtuTimeoutOfIpV6Ctrl(IpCtrlIdx))
  {
    IpV6_Ndp_VDCCheckLifetimes(IpCtrlIdx);
  }
#endif
}

/**********************************************************************************************************************
 *  IpV6_Ndp_MainFunction()
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
FUNC(void, IPV6_CODE) IpV6_Ndp_MainFunction(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
#if (TCPIP_SUPPORT_NDP_INV_NA == STD_ON)
  TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif

  TCPIP_ASSERT(IpCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl());

  /* #10 Send pending Duplicate Address Detection response. */
  if (TRUE == TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->Pending)
  {
    TcpIp_LocalAddrV6IterType ipAddrIdx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);

    /* Defend our addresses by sending neighbor advertisements if we received a DAD
     * neighbor solicitation for one of our addresses by another node.
     */
    if (E_OK == IpV6_Ndp_VTxNeighborAdvertisement(&ipAddrIdx, &IpV6_AddrAllNodesLL,
      &(TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->TargetAddr),
        TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->RSOFlags))
    {
      TcpIp_GetAddrNdp_PendingDadNaOfIpV6CtrlDyn(IpCtrlIdx)->Pending = FALSE;
    }
  }

  /* #20 Process pending Inverse Neighbor Solicitation messages. */
#if (TCPIP_SUPPORT_NDP_INV_NA == STD_ON)
  /*lint !e506 */ /* "Constant value Boolean" (only in some configuration variants) */
  if (   (TcpIp_IsEnableNdpInvNaOfNdpConfig(ndpConfigIdx) == TRUE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (IPV6_TIME_EXPIRED(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->Timeout) == TRUE))
  {
    if (0u < TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TxCount)
    {
      /* #30 Try to send Inv NS message. */
      if (E_OK == IpV6_Ndp_VTxInverseSolicitation(TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx),
        &(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TargetPhysAddr[0]),
        TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->IncludeSrcAddrList))
      {
        /* schedule retransmission */
        IPV6_SET_EVENT_TIME_MS(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->Timeout,
          TcpIp_GetRetransTimerMsOfIpV6CtrlDyn(IpCtrlIdx));

        TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TxCount -= 1u;
      }
    }
    else
    {
# if (TCPIP_ICMPV6INDADDRLISTRECEIVEDCBK == STD_ON)
      /* #40 Notify upper layer about expired timeout. */
      IpV6_Ndp_VInvokeAddrRcvdCbk(IpCtrlIdx, &(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->TargetPhysAddr[0]), (IPV6_P2C(IpV6_AddrType))NULL_PTR, 0u);
# endif
      IPV6_TIME_SET_INFINITY(TcpIp_GetAddrNdp_PendingInvNsOfIpV6CtrlDyn(IpCtrlIdx)->Timeout);
    }
  }
#endif
  /* #50 Handle the states of different cache entries */
  IpV6_Ndp_VProcessCacheStates(IpCtrlIdx);

} /* End of IpV6_Ndp_MainFunction() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Ndp_ClearCache
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_ClearCache(
  TcpIp_LocalAddrV6IterType LocalAddrV6Idx)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check input parameter */
  if (LocalAddrV6Idx < TcpIp_GetSizeOfLocalAddrV6())
  {
    /* #20 Clear cache */
    TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
    TcpIp_SetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(ipCtrlIdx, TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(ipCtrlIdx));
    retVal = E_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VCountCacheEntries
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(uint32, IPV6_CODE) IpV6_Ndp_VCountCacheEntries(
  TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  uint32 idxEntryCount = 0;

  TcpIp_SizeOfIpV6NeighborCacheEntryType ncEntryIdx;
  for (ncEntryIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       ncEntryIdx < TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx);
       ncEntryIdx++)
  {
    if (TcpIp_GetAddrIpV6NeighborCacheEntry(ncEntryIdx)->State != IPV6_REACHABLE_STATE_INCOMPLETE)
    {
      idxEntryCount++;
    }
  }
  return idxEntryCount;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_VCopyCacheEntries
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Ndp_VCopyCacheEntries(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
  TCPIP_P2V(TcpIp_NdpCacheEntryType) EntryListPtr,
  TCPIP_P2V(uint32)                  MaxNumEntriesPtr)
{
  TcpIp_IpV6NeighborCacheEntryIterType maxNumEntriesToCopy = (TcpIp_IpV6NeighborCacheEntryIterType)TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) - (TcpIp_IpV6NeighborCacheEntryIterType)TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_IpV6NeighborCacheEntryIterType entryEndIdx;
  TcpIp_IpV6NeighborCacheEntryIterType idxCacheEntry;
  uint32 idxEntryCount = 0;

  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) >= TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx));
  TCPIP_ASSERT(TcpIp_GetIpV6NeighborCacheEntryValidEndIdxOfIpV6CtrlDyn(IpCtrlIdx) <= TcpIp_GetIpV6NeighborCacheEntryEndIdxOfIpV6Ctrl(IpCtrlIdx));

  if (maxNumEntriesToCopy > *MaxNumEntriesPtr)
  {
    maxNumEntriesToCopy = (TcpIp_IpV6NeighborCacheEntryIterType)*MaxNumEntriesPtr;
  }

  entryEndIdx = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx) + maxNumEntriesToCopy;

  /* #10 Traverse through neighbhor cache and copy valid cache entries to list */
  for (idxCacheEntry = TcpIp_GetIpV6NeighborCacheEntryStartIdxOfIpV6Ctrl(IpCtrlIdx);
       idxCacheEntry < entryEndIdx;
       idxCacheEntry++)
  {
    if (TcpIp_GetAddrIpV6NeighborCacheEntry(idxCacheEntry)->State != IPV6_REACHABLE_STATE_INCOMPLETE)
    {
      if (TcpIp_GetAddrIpV6NeighborCacheEntry(idxCacheEntry)->State == IPV6_REACHABLE_STATE_REACHABLE)
      {
        EntryListPtr[idxEntryCount].State = TCPIP_NDP_ENTRY_VALID;
      }
      else
      {
        EntryListPtr[idxEntryCount].State = TCPIP_NDP_ENTRY_STALE;
      }

      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_LL_ADDR_COPY(EntryListPtr[idxEntryCount].PhysAddr,  TcpIp_GetAddrIpV6NeighborCacheEntry(idxCacheEntry)->LinkLayerAddress);
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(EntryListPtr[idxEntryCount].Inet6Addr[0], TcpIp_GetAddrIpV6NeighborCacheEntry(idxCacheEntry)->NeighborAddress);
      idxEntryCount++;
    }
  }

  *MaxNumEntriesPtr = idxEntryCount;
}

/**********************************************************************************************************************
 *  IpV6_Ndp_GetCacheEntries
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) IpV6_Ndp_GetCacheEntries(
    TcpIp_IpV6CtrlIterType             IpCtrlIdx,
    TCPIP_P2V(uint32)                  NumberOfElementsPtr,
    TCPIP_P2V(TcpIp_NdpCacheEntryType) EntryListPtr)
{
  /* #10 Check if cache entries have to be copied or counted. */
  if (*NumberOfElementsPtr == 0u)
  {
    /* #20 Count cache entries. */
    *NumberOfElementsPtr = IpV6_Ndp_VCountCacheEntries(IpCtrlIdx);
  }
  else
  {
    IpV6_Ndp_VCopyCacheEntries(IpCtrlIdx, EntryListPtr, NumberOfElementsPtr);
  }
}  /* IpV6_Ndp_GetCacheEntries() */


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */


/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRA_Compliance_MSR.pdf'

   Justification for module-specific MISRA deviations:

   module global deviations -> see file TcpIp.c

   NDP-specific deviations:

*/


/**********************************************************************************************************************
 *  END OF FILE: IpV6_Ndp.c
 *********************************************************************************************************************/
