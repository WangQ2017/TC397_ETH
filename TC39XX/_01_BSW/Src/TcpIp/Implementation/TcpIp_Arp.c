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
 *         \file  TcpIp_Arp.c
 *        \brief  Implementation of Address Resolution Protocol (ARP) for IPv4
 *
 *      \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

/* The ARP module is an integral part of the IP module. For this the ARP module may directly access
   the IP configuration. */

#define TCPIP_ARP_SOURCE

#include "TcpIp_Cfg.h"
#include "TcpIp_Lcfg.h"

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "TcpIp_Arp.h"
#include "TcpIp_Arp_Cbk.h"
#include "TcpIp_IpV4_Priv.h"
#include "TcpIp_Priv.h"


#include "EthIf.h"


#include "TcpIp_IpV4.h"  /* needed for dynamic IP LL config */

#if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                    /* COV_TCPIP_ICMPV4_ALWAYS_ON */
#include "TcpIp_IcmpV4_Cbk.h"
#endif

#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if !defined (STATIC)                                                                                                   /* COV_TCPIP_COMPATIBILITY */
# define STATIC static
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define IPV4_ARP_HW_ADDR_TYPE_OFS         0u
#define IPV4_ARP_PR_ADDR_TYPE_OFS         2u
#define IPV4_ARP_HW_ADDR_SIZE_OFS         4u
#define IPV4_ARP_PR_ADDR_SIZE_OFS         5u
#define IPV4_ARP_OP_OFS                   6u
#define IPV4_ARP_SRC_MC_ADDR_OFS          8u
#define IPV4_ARP_SRC_IP_ADDR_OFS          14u
#define IPV4_ARP_DST_MC_ADDR_OFS          18u
#define IPV4_ARP_DST_IP_ADDR_OFS          24u

#define IPV4_ARP_INVALID_RES_IDX          TcpIp_GetSizeOfArpTableEntry()

/* Gratuitous ARP reply on Startup */
#define IPV4_ARP_GRATUITOUS_REPLY_INTERVAL (400u)  /* Time for the next gratuitous ARP reply ( every 2 seconds) */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define IPV4_ARP_TIMESTAMP_IS_OLDER(TS_A, TS_B) IPV4_UINT32_TIMESTAMP_IS_OLDER((TS_A), (TS_B))

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint32 IpV4_Arp_MainFuncCycleType;


/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
/* ----- */

#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

STATIC VAR(IpV4_Arp_MainFuncCycleType, IPV4_VAR_NOINIT) IpV4_Arp_MainFuncCycle;

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */


#define TCPIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

STATIC VAR(uint8, IPV4_VAR_NOINIT)  IpV4_Arp_NumPendEle;  /* number of pending ARP requests */

#define TCPIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */


#define TCPIP_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

STATIC CONST(IpBase_EthPhysAddrType, IPV4_CONST) IpV4_Arp_PhysBroadcastAddr =
{
  0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU
};

#define TCPIP_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */
/**********************************************************************************************************************
 *  IpV4_Arp_VSendMessage
 *********************************************************************************************************************/
/*! \brief        Sends an ARP message.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance.
                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    RemNetAddr            Remote Network address(Destination Ip address).
 *  \param[in]    LocNetAddr            Local Network address(Source Ip address).
 *  \param[in]    RemPhysAddr           Remote Physical address( the destination MAC address).
 *                                      CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]    Operation             Type of operation (Reply or Request).
 *  \return       E_OK                  ARP message sent successfully.
 *  \return       E_NOT_OK              ARP message could not be sent.
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_VSendMessage(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        RemNetAddr,
  IpBase_AddrInType                        LocNetAddr,
  IPV4_P2C(uint8)                          RemPhysAddr,
  uint16                                   Operation);

/**********************************************************************************************************************
 *  IpV4_Arp_VUpdateEntry
 *********************************************************************************************************************/
/*! \brief          Sets the state of an entry in the dynamic ARP table to valid and notifies the upper layer if required.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx              Index of the IP controller/instance.
 *                                           CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      PhysAddr                 Physical address (network byte order).
                                             CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]      ArpTableEntryIdx         Entry Index in the ARP resolution table.
 *                                           CONSTRAINT: [TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx)...
 *                                                        TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx)-1]
 *  \param[in]      EntryInTable             Indicates if an existing entry is updated.
 *  \pre            PRE_TCPIP_ARP_INIT
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
  ********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VUpdateEntry(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IPV4_P2C(uint8)                          PhysAddr,
  TcpIp_SizeOfArpTableEntryType            ArpTableEntryIdx,
  boolean                                  EntryInTable);

/**********************************************************************************************************************
 *  IpV4_Arp_VStoreDynamicEntry
 *********************************************************************************************************************/
/*! \brief        Stores an entry into the dynamic ARP table.
 *  \details      Called only if ARPCONFIG exist for the desired Ip controller.
 *  \param[in]    IpV4CtrlIdx              Index of the IP controller/instance
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                         CONSTRAINT: [ARPCONFIG must exist for this controller index.]
 *  \param[in]    NetAddr                  Network address.
 *  \param[in]    PhysAddr                 Physical address (network byte order).
 *                                         CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]    AddIfNotExisting         TRUE:  Add a new entry if no matching entry is found.
 *                                         FALSE: Leave ARP table unchanged if no matching entry is found.
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
  ********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VStoreDynamicEntry(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        NetAddr,
  IPV4_P2C(uint8)                          PhysAddr,
  boolean                                  AddIfNotExisting);

/**********************************************************************************************************************
 *  IpV4_Arp_VPhysAddrTableChgNotification
 *********************************************************************************************************************/
/*! \brief        Notifies upper layer about a change in the ARP table related to controller, specified by IpV4CtrlIdx.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx        IP controller index of the related ARP table.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    ArpTableEntryIdx   ARP table entryIndex.
 *                                   CONSTRAINT: [TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx)...
 *                                                TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx)-1]
 *  \param[in]    Valid              Specifies if the ARP table entry is added or changed (TRUE) or has been removed (FALSE).
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VPhysAddrTableChgNotification(
  TcpIp_IpV4CtrlIterType        IpV4CtrlIdx,
  TcpIp_SizeOfArpTableEntryType ArpTableEntryIdx,
  boolean                       Valid);

#if (TCPIP_SUPPORT_ARP_DISCARDED_ENTRY_HANDLING == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Arp_VPhysAddrTableChgDiscardedNotification
 *********************************************************************************************************************/
/*! \brief        Notifies ULs about a new ARP-table entry that was discarded because the ARP-table was full, already.
 *  \details      Called only in case the functionality defined by DSGN-TcpIpIpV4AddressResolutionModes is active, i.e.:
 *                TCPIP_ARP_SUPPORT_DISCARD_HANDLING == STD_ON
 *                Does nothing if no callback for this event is configured.
 *  \param[in]    IpV4CtrlIdx              IP controller index of the related ARP table.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    DiscardedNetAddr         Specifies the IP address of the discarded ARP table entry
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        DSGN-TcpIpIpV4AddressResolutionModes
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VPhysAddrTableChgDiscardedNotification(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      DiscardedNetAddr);
#endif

/**********************************************************************************************************************
 *  IpV4_Arp_VStaticTableLookup
 *********************************************************************************************************************/
/*! \brief        Lookup static configured IP address to physical address mapping.
 *  \details      This function returns the physical address for the configured IP address for the given IP controller.
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    NetAddr               Network address
 *  \param[out]   PhysAddrPtr           Pointer to physical address (network byte order).
 *                                      CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *                                      (May be NULL_PTR in case it shall only be checked if an entry exists.)
 *  \return       E_OK                  Static mapping has been found. *PhysAddrPtr has been updated if != NULL_PTR
 *  \return       E_NOT_OK              No static mapping has been found. *PhysAddrPtr unchanged
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_VStaticTableLookup(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        NetAddr,
  P2VAR(uint8, IPV4_APPL_DATA, IPV4_CONST) PhysAddrPtr);

/**********************************************************************************************************************
 *  IpV4_Arp_VDetectLinkLocalAddressConflict
 *********************************************************************************************************************/
/*! \brief        Notifies the link-local address configuration module about IP addresses used in received ARP packets.
 *  \details      The link-local address configuration module uses this information to detect if the IP address of this
 *                node conflicts with the address of other nodes.
 *  \param[in]    IpV4CtrlIdx      Index of the IP controller/instance.
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    ArpOperation     Operation of the ARP packet. (IPV4_ARP_OP_REQUEST or IPV4_ARP_OP_REPLY)
 *  \param[in]    LocIpAddr        Unicast IP address used by the IP controller/instance.
 *  \param[in]    ArpSrcIpAddr     Source IP address contained in the ARP packet.
 *  \param[in]    ArpDstIpAddr     Target IP address contained in the ARP packet.
 *  \param[in]    ArpSrcMacAddrPtr Source MAC address contained in the ARP packet.
 *                                 CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \return                        E_OK:     No conflict was detected.
 *  \return                        E_NOT_OK: Address conflict detected.
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_VDetectLinkLocalAddressConflict(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  uint16                 ArpOperation,
  IpBase_AddrInType      LocIpAddr,
  IpBase_AddrInType      ArpSrcIpAddr,
  IpBase_AddrInType      ArpDstIpAddr,
  IPV4_P2C(uint8)        ArpSrcMacAddrPtr);

/**********************************************************************************************************************
 *  IpV4_Arp_VUpdateTable
 *********************************************************************************************************************/
/*! \brief        Updates an existing or inserts a new entry into the dynamic ARP table.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx             Index of the IP controller/instance.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    ArpSrcIpAddr            Source IP address contained in the ARP packet.
 *  \param[in]    ArpSrcMacAddr           Source MAC address contained in the ARP packet.
 *                                        CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]    AddIfNotExisting TRUE:  Add a new entry if no matching entry is found.
 *                                 FALSE: Leave ARP table unchanged if no matching entry is found.
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VUpdateTable(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        ArpSrcIpAddr,
  IPV4_P2C(uint8)                          ArpSrcMacAddr,
  boolean                                  AddIfNotExisting);

/**********************************************************************************************************************
 *  IpV4_Arp_VRespondToPacket
 *********************************************************************************************************************/
/*! \brief        Responds to a received ARP packet if required.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx        Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    ArpOperation       Operation of the ARP packet. (IPV4_ARP_OP_REQUEST or IPV4_ARP_OP_REPLY)
 *  \param[in]    ArpSrcIpAddr       Source IP address contained in the ARP packet.
 *  \param[in]    ArpDstIpAddr       Target IP address contained in the ARP packet.
 *  \param[in]    ArpSrcMacAddr      Source MAC address contained in the ARP packet.
 *                                   CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VRespondToPacket(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  uint16                                   ArpOperation,
  IpBase_AddrInType                        ArpSrcIpAddr,
  IpBase_AddrInType                        ArpDstIpAddr,
  IPV4_P2C(uint8)                          ArpSrcMacAddr);

/**********************************************************************************************************************
 *  IpV4_Arp_VHandlePacket
 *********************************************************************************************************************/
/*! \brief        Handles a received ARP packet.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx        Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    ArpOperation       Operation of the ARP packet. (IPV4_ARP_OP_REQUEST or IPV4_ARP_OP_REPLY)
 *  \param[in]    ArpSrcIpAddr       Source IP address contained in the ARP packet.
 *  \param[in]    ArpDstIpAddr       Target IP address contained in the ARP packet.
 *  \param[in]    ArpSrcMacAddr      Source MAC address contained in the ARP packet.
 *                                   CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VHandlePacket(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  uint16                                   ArpOperation,
  IpBase_AddrInType                        ArpSrcIpAddr,
  IpBase_AddrInType                        ArpDstIpAddr,
  IPV4_P2C(uint8)                          ArpSrcMacAddr);

/**********************************************************************************************************************
 * IpV4_Arp_VReadStaticTable
 *********************************************************************************************************************/
/*! \brief        Copies the elements of the static ARP table into the given user defined buffer.
 *  \details      The function is used to read the number of total arp entries available in the static table or write
 *                those vailable entries into the buffer provided by the user
 *  \param[in]    IpV4CtrlIdx            Index of the IP controller/instance.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    NumOfElements          Maximum number of entries that can be stored.
 *  \param[out]   EntryListPtr           Pointer to the memory where the list of cache entries are stored.
 *                                       (May be NULL_PTR if only the number of entries shall be returned.)
 *  \param[out]   EntryListIdxPtr        Entry Index Pointer for the User defined buffer.
 *  \return                              EntryListPtr != NULL_PTR: Number of entries written to EntryList.
 *                                       EntryListPtr == NULL_PTR: Total number of entries to be read
 *                                                                 OR Number of all entries in Static Arp Table(cache).
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        CREQ-111995
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint32, IPV4_CODE) IpV4_Arp_VReadStaticTable(
  TcpIp_IpV4CtrlIterType                                        IpV4CtrlIdx,
  uint32                                                        NumOfElements,
  P2VAR(TcpIp_ArpCacheEntryType, IPV4_APPL_DATA, IPV4_APPL_VAR) EntryListPtr,
  IPV4_P2V(uint32)                                              EntryListIdxPtr);

/**********************************************************************************************************************
 * IpV4_Arp_VWriteValidEntries
 *********************************************************************************************************************/
/*! \brief         Copies Dynamic ARP Table elements into the given, user defined buffer.
 *  \details       -
 *  \param[in]     IpV4CtrlIdx                       Index of the IP controller/instance.
 *                                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]     ArpConfigIdx                      Index to access the dynamic arp table and other config parameters.
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfArpConfig() - 1]
 *  \param[in]     EntryListPtr                      Pointer to the memory where the list of cache entries shall be stored.
 *  \param[in,out] EntryListIdxPtr                   Entry Index Pointer for the User defined buffer.
 *                                                   CONSTRAINT: [0...TcpIp_GetTableSizeOfArpConfig(ArpConfigIdx)-1]
 *  \param[in]     DynElementsToReadLimitIdx         End Index of the Arp dynamic table.This parameter is used to
 *                                                   limit the Arp cache entries that are read from the
 *                                                   cache(dynamic table) and written in to user defined buffer.
 *                                                   CONSTRAINT: [0  ( TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx)
 *                                                                   - TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx))]
 *  \pre           PRE_TCPIP_ARP_INIT
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-111995
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VWriteValidEntries(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  TcpIp_SizeOfArpConfigType         ArpConfigIdx,
  IPV4_P2V(TcpIp_ArpCacheEntryType) EntryListPtr,
  IPV4_P2V(uint32)                  EntryListIdxPtr,
  uint32                            DynElementsToReadLimitIdx);

/**********************************************************************************************************************
 * IpV4_Arp_VReadDynTable
 *********************************************************************************************************************/
/*! \brief         Copies Dynamic ARP Table elements into the given, user defined buffer.
 *  \details       -
 *  \param[in]     IpV4CtrlIdx            Index of the IP controller/instance.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]     NumOfElements          Number of entries that can be read from the dynamic Arp table.
 *  \param[out]    EntryListPtr           Pointer to the memory where the list of cache entries shall be stored.
 *                                        (May be NULL_PTR if only the number of entries shall be returned.)
 *  \param[in]     EntryListIdxPtr        Index Pointer for the User defined  Entry List buffer.
 *  \return                               EntryListPtr != NULL_PTR: Number of entries written to EntryList.
 *                                        EntryListPtr == NULL_PTR: Total number of entries in cache.
 *                                        CONSTRAINT: [0...TcpIp_GetTableSizeOfArpConfig(ArpConfigIdx)-1]
 *  \pre           PRE_TCPIP_ARP_INIT
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-111995
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint32, IPV4_CODE) IpV4_Arp_VReadDynTable(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  uint32                            NumOfElements,
  IPV4_P2V(TcpIp_ArpCacheEntryType) EntryListPtr,
  IPV4_P2V(uint32)                  EntryListIdxPtr);

/**********************************************************************************************************************
 * IpV4_Arp_VCreateEntry
 *********************************************************************************************************************/
/*! \brief          Create new entry and trigger ARP request in case the caller desires that.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx            Index of the IP controller/instance.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      IpV4SocketIdx          Socket index
 *                                         CONSTRAINT: [SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn() or IPV4_INV_SOCK_IDX]
 *  \param[in]      NetAddr                Network address (network byte order).
 *  \param[in]      TableFull              Flag to indicate that TableIdxLru contains an entry that will be overwritten
 *  \param[in]      ArpTableEntryIdx       Index of ARP entry that shall be created.
 *                                         CONSTRAINT: [TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx)...
 *                                                      TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx)-1]
 *  \return         TCPIP_E_PHYS_ADDR_MISS  Address could not be resolved, resolution has been triggered successfully.
 *                  TCP_E_NOT_OK            Address could not be resolved, resolution has NOT been triggered
 *
 *  \pre            PRE_TCPIP_ARP_INIT
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_VCreateEntry(
  TcpIp_IpV4CtrlIterType        IpV4CtrlIdx,
  TcpIp_IpV4SocketDynIterType   IpV4SocketIdx,
  IpBase_AddrInType             NetAddr,
  boolean                       TableFull,
  TcpIp_SizeOfArpTableEntryType ArpTableEntryIdx);

/**********************************************************************************************************************
 * IpV4_Arp_VCheckValidityOfEntry
 *********************************************************************************************************************/
/*! \brief          Check if the Entry is Valid or out of date.
 *  \details        This function verifies whether an ARP entry is too old, if so then it resets the entry timer,
 *                  changes status of that entry to INPROGRESS and tries to send the ARP request again.
 *  \param[in]      IpV4CtrlIdx             Index of the IP controller/instance.
 *                                          CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[out]     PhysAddrPtr             Pointer to the Physical address.
 *                                          CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]      NetAddr                 Network address (network byte order).
 *  \param[in]      ArpTableEntryIdx        ARP resolution table Index.
 *                                          CONSTRAINT: [TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx)...
 *                                                       TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx)-1]
 *  \return         TCPIP_E_PHYS_ADDR_MISS  ARP request already is in progress.
 *                  TCP_E_NOT_OK            Not resolved
 *                  TCP_E_OK                there is a valid entry for the given network address

 *  \pre            PRE_TCPIP_ARP_INIT
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_VCheckValidityOfEntry(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) PhysAddrPtr,
  IpBase_AddrInType                       NetAddr,
  TcpIp_SizeOfArpTableEntryType           ArpTableEntryIdx);

/**********************************************************************************************************************
 * IpV4_Arp_VCheckArpEntry
 *********************************************************************************************************************/
/*! \brief          Check if the entry is already in the ARP table or not.
 *  \details        This function checks whether a valid entry exists in ARP resolution table.
 *  \param[in]      IpV4CtrlIdx            Index of the IP controller/instance.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      IpV4SocketIdx          Socket index
 *                                         CONSTRAINT: [SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn() or IPV4_INV_SOCK_IDX]
 *                                         (If a valid socket index is specified, the index of the matching ARP entry, if there is one,
 *                                         is stored related to the socket in order to allow an optimized lookup next time.)
 *  \param[in]      NetAddr                Network address (network byte order).
 *  \param[out]     TableFullPtr           Indicates whether the ARP cache is completely filled.
 *                                         CONSTRAINT: [Parameter is updated only when no matching entry is found.]
 *  \param[out]     LruArpTableEntryIdxPtr Index of the least recently used entry.
 *                                         This parameter is used only if the dynamic arp table is full and we need space to add new arp entry.
 *  \return         Index of the matching entry                      if any valid maching entry found.
 *                  TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN         if no matching entry is found.
 *  \pre            PRE_TCPIP_ARP_INIT
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_SizeOfArpTableEntryType, IPV4_CODE) IpV4_Arp_VCheckArpEntry(
  TcpIp_IpV4CtrlIterType                                         IpV4CtrlIdx,
  TcpIp_IpV4SocketDynIterType                                    IpV4SocketIdx,
  IpBase_AddrInType                                              NetAddr,
  P2VAR(boolean, AUTOMATIC, IPV4_APPL_VAR)                       TableFullPtr,
  P2VAR(TcpIp_SizeOfArpTableEntryType, AUTOMATIC, IPV4_APPL_VAR) LruArpTableEntryIdxPtr);

/**********************************************************************************************************************
 * IpV4_Arp_VProcessPendingEntries
 *********************************************************************************************************************/
/*! \brief          Retransmits ARP requests of pending entries if required and handles address resolution timeout.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx              Index of the IP controller/instance.
 *                                           CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre            PRE_TCPIP_ARP_INIT
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VProcessPendingEntries(TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Arp_GetPhysicalAddressFromDynamicTables
 *********************************************************************************************************************/
/*! \brief        Get physical address from a dynamic ARP table for a given network address.
 *  \details      The cache table access is optimized for requesting the same address many times for the same socket.
 *  \param[in]    IpV4CtrlIdx             Index of the IP controller/instance.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    IpV4SocketIdx           Socket index
 *                                        CONSTRAINT: [SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn() or IPV4_INV_SOCK_IDX]
 *  \param[in]    NetAddr                 Network address (network byte order)
 *  \param[out]   PhysAddrPtr             Pointer for physical address (network byte order)
 *                                        CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]    InitRes                 Specifies if the address resolution shall be initiated (TRUE) or not (FALSE) in
 *                                        case the physical address related to the specified IP address is currently
 *                                        unknown.
 *  \return       TCP_OK                  Address could be resolved
 *                TCP_E_NOT_OK            Address could not be resolved, resolution has NOT been triggered, even in case
 *                                        the parameter InitRes has indicated the callers wish to do so,
 *                TCPIP_E_PHYS_ADDR_MISS  Address could not be resolved, resolution has been triggered successfully,
 *                                        depending on the value of the parameter InitRes.
 *  \pre           PRE_TCPIP_ARP_INIT
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_GetPhysicalAddressFromDynamicTables(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  TcpIp_SizeOfIpV4SocketDynType           IpV4SocketIdx,
  IpBase_AddrInType                       NetAddr,
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) PhysAddrPtr,
  boolean                                 InitRes);

/**********************************************************************************************************************
 *  IpV4_Arp_VReadMsgData
 *********************************************************************************************************************/
/*! \brief        Reads data from a received ARP message.
 *  \details      Called by the Arp_RxIndication when a message arrives.
 *  \param[in]    EthIfCtrlIdx          EthIf controller index
 *                                      CONSTRAINT: [0  TcpIp_GetSizeOfEthIfCtrl() - 1]
 *  \param[in]    DataPtr               Pointer to the received data
 *  \param[in]    LenByte               Length of received data in bytes
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VReadMsgData(
  TcpIp_SizeOfEthIfCtrlType                  EthIfCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     LenByte);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  IpV4_Arp_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Arp_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType ipV4SocketIdx;
  TcpIp_ArpTableEntryIterType arpTableEntryIdx;
  TcpIp_GratuitousArpIterType gratuitousArpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize dynamic ARP table entries */
  for (arpTableEntryIdx = 0; arpTableEntryIdx < TcpIp_GetSizeOfArpTableEntry(); arpTableEntryIdx++)
  {
    /* #20 Invalidate all entries in the ARP table. */
    /* Set all elements of the arp table as Invalid. */
    TcpIp_SetStatusOfArpTableEntry(arpTableEntryIdx, IPV4_ARP_ELSTATUS_INVALID);                                        /* SBSW_TCPIP_CSL01_IDX_CALLEE */
  }

  /* Set Ip controller to invalid for all sockets. */
  /* Optimization to get the last stored arp entry for this socket index. */
  /* #30 Iterate over all socket index and reset the arp entry and Ipv4 controller index refernced by it. */
  for (ipV4SocketIdx = 0; ipV4SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn(); ipV4SocketIdx++)
  {
    TcpIp_SetIpV4CtrlIdxOfIpV4SocketDyn(ipV4SocketIdx, TCPIP_NO_IPV4CTRLIDXOFIPV4SOCKETDYN);                                /* SBSW_TCPIP_CSL01_IDX_CALLEE */
    /* Reset the arp enty which was saved for this socket index. */
    TcpIp_SetArpTableEntryIdxOfIpV4SocketDyn(ipV4SocketIdx, TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN);                      /* SBSW_TCPIP_CSL01_IDX_CALLEE */
  }

  if (TcpIp_GetSizeOfGratuitousArp() != 0u)
  {
    /* If gratuitous Arps are configured, clear counters */
    for (gratuitousArpIdx = 0; gratuitousArpIdx < TcpIp_GetSizeOfGratuitousArp(); gratuitousArpIdx++)
    {
      TcpIp_SetTransmissionCntOfGratuitousArp(gratuitousArpIdx, 0u);                                                    /* SBSW_TCPIP_CSL01_IDX_CALLEE */
      TcpIp_SetNextTransmissionMsOfGratuitousArp(gratuitousArpIdx, 0u);                                                 /* SBSW_TCPIP_CSL01_IDX_CALLEE */
    }
  }

  /* #40 Reset the global variables.*/
  IpV4_Arp_NumPendEle    = 0;
  IpV4_Arp_MainFuncCycle = 0;

} /* IpV4_Arp_Init() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Arp_MapIpToPhysMulticastAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Arp_MapIpToPhysMulticastAddr(
  IpBase_AddrInType NetMcAddr,
  IPV4_P2V(uint8)   PhysMcAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_AddrInType netMcAddrHbo;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(PhysMcAddr != NULL_PTR);
  TCPIP_ASSERT(IPV4_ADDR_IS_MULTICAST(NetMcAddr));
  /* #10 Calculate corresponding MAC group address from specified multicast IP address. */
  /* "An IP host group address is mapped to an Ethernet multicast address
    *  by placing the low-order 23-bits of the IP address into the low-order
    *  23 bits of the Ethernet multicast address 01-00-5E-00-00-00 (hex)."
    * [RFC1112 6.4. Extensions to an Ethernet Local Network Module]
    */
  /* #20 Convert IP address from network byte order into host byte order. */
  netMcAddrHbo = TCPIP_NTOHL(NetMcAddr);

  /* #30 Set first three bytes 01:00:5e:XX:XX:XX */
  PhysMcAddr[0] = 0x01U;                                                                                                /* SBSW_TCPIP_FUNC_PARAM_PTR_PHYSADDR_WRITE_CALLER */
  PhysMcAddr[1] = 0x00U;                                                                                                /* SBSW_TCPIP_FUNC_PARAM_PTR_PHYSADDR_WRITE_CALLER */
  PhysMcAddr[2] = 0x5EU;                                                                                                /* SBSW_TCPIP_FUNC_PARAM_PTR_PHYSADDR_WRITE_CALLER */

  /* #40 Set last 23 bits of IP address */
  PhysMcAddr[3] = (uint8)((netMcAddrHbo >> 16u) & 0x0000007FU); /* 7 bit */                                             /* SBSW_TCPIP_FUNC_PARAM_PTR_PHYSADDR_WRITE_CALLER */
  PhysMcAddr[4] = (uint8) (netMcAddrHbo >> 8u);                 /* 8 bit */                                             /* SBSW_TCPIP_FUNC_PARAM_PTR_PHYSADDR_WRITE_CALLER */
  PhysMcAddr[5] = (uint8) (netMcAddrHbo);                      /* 9 bit */                                              /* SBSW_TCPIP_FUNC_PARAM_PTR_PHYSADDR_WRITE_CALLER */
} /* IpV4_Arp_MapIpToPhysMulticastAddr() */

/**********************************************************************************************************************
 *  IpV4_Arp_VCreateEntry
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
TCPIP_LOCAL FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_VCreateEntry(
  TcpIp_IpV4CtrlIterType        IpV4CtrlIdx,
  TcpIp_IpV4SocketDynIterType   IpV4SocketIdx,
  IpBase_AddrInType             NetAddr,
  boolean                       TableFull,
  TcpIp_SizeOfArpTableEntryType ArpTableEntryIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType retValue = TCPIP_E_PHYS_ADDR_MISS;
  uint8_least physAddrByteIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case DiscardedEntryHandling is active: Only modify an entry in case the ARP-table-entry is NOT full. */
#if (TCPIP_SUPPORT_ARP_DISCARDED_ENTRY_HANDLING == STD_ON)
  /* Runtime check TcpIp_IsArpDiscardedEntryHandlingOfIpV4General(TCPIP_IPV4GENERAL_IDX) is converted into Preprocessor check.*/
  if (TableFull == FALSE)
#else
  TCPIP_UNUSED_PARAMETER(TableFull);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  {
    /* #20 Enter exclusive area. */
    IPV4_VENTER_CRITICAL_SECTION();
    /* Set entry parameters. */
    for (physAddrByteIdx = 0; physAddrByteIdx < IPBASE_ETH_PHYS_ADDR_LEN_BYTE; physAddrByteIdx++)
    {
      TcpIp_GetAddrPhysAddrOfArpTableEntry(ArpTableEntryIdx)->data[physAddrByteIdx] = 0x00;                             /* SBSW_TCPIP_FUNC_PARAM_CALLER_WRITE_ACCESS_ARRAY_PHYSADDR */
    }
    /* Overwrite the details of "ArpTableEntryIdx" with new information. */
    TcpIp_SetNetAddrOfArpTableEntry(ArpTableEntryIdx, NetAddr);                                                         /* SBSW_TCPIP_FUNC_PARAM_CALLER */
    /* #30 Set status of entry as "In Progress". */
    TcpIp_SetStatusOfArpTableEntry(ArpTableEntryIdx, IPV4_ARP_ELSTATUS_INPROGESS);                                      /* SBSW_TCPIP_FUNC_PARAM_CALLER */
    TcpIp_SetTimeStampOfArpTableEntry(ArpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                        /* SBSW_TCPIP_FUNC_PARAM_CALLER */
    TcpIp_SetCreationTimeStampOfArpTableEntry(ArpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                /* SBSW_TCPIP_FUNC_PARAM_CALLER */
    IPV4_VLEAVE_CRITICAL_SECTION();

    /* #40 Try to send the ARP request. */
    if (IpV4_Arp_SendArpRequest(IpV4CtrlIdx, NetAddr) == E_OK)
    {
      /* #50 Enter exclusive area. */
      IPV4_VENTER_CRITICAL_SECTION();

      /* #60 Verify that the Socket Index is valid. */
      if (IpV4SocketIdx != IPV4_INV_SOCK_IDX)
      {
        TcpIp_SetIpV4CtrlIdxOfIpV4SocketDyn(IpV4SocketIdx, (TcpIp_SizeOfIpV4CtrlType)IpV4CtrlIdx);                      /* SBSW_TCPIP_FUNC_PARAM_SOCK */
       /* #70 Optimization: Arp Entry index is saved for the socket.So next time if the same socket is used to send the
                            arp request, saved arp entry is checked first instead to iterate over whole arp tabel. */
        TcpIp_SetArpTableEntryIdxOfIpV4SocketDyn(IpV4SocketIdx, ArpTableEntryIdx);                                      /* SBSW_TCPIP_FUNC_PARAM_SOCK */
      }
      /* #80 Increment the global variable of pending entry, which is checked in IpV4_Arp_MainFunction. */
      IpV4_Arp_NumPendEle++;
      IPV4_VLEAVE_CRITICAL_SECTION();
    }
    /* #90 Otherwise invalidate the above created entry( which was "IPV4_ARP_ELSTATUS_INPROGESS"). */
    else
    {
      IPV4_VENTER_CRITICAL_SECTION();

      TcpIp_SetStatusOfArpTableEntry(ArpTableEntryIdx, IPV4_ARP_ELSTATUS_INVALID);                                      /* SBSW_TCPIP_FUNC_PARAM_CALLER */

      IPV4_VLEAVE_CRITICAL_SECTION();
      /* currently no buffer available, try again later (main function)
      "TCPIP_E_PHYS_ADDR_MISS" will be returned */
    }
  }
#if (TCPIP_SUPPORT_ARP_DISCARDED_ENTRY_HANDLING == STD_ON)
  else
  {
    /* Due to the if-statement of this if-else-block it is sure that DiscardedEntryHandling is active, when we get here. */
    /* In case the new entry would overwrite an existing entry because the table is "full":
       Conduct the optional callout to indicate, which entry was discarded.
       IpV4_Arp_VPhysAddrTableChgNotification() is NOT used to do the discard callback, because in case of a new entry being discarded the ARP table is not changed. */
    /* #100 Otherwise Inform the upper layer about discarded entry, in case the new entry overwrite an existing entry when table is full.*/
    IpV4_Arp_VPhysAddrTableChgDiscardedNotification(IpV4CtrlIdx, /* Discarded */ NetAddr);
    retValue = TCPIP_E_NOT_OK;
  }
#endif
  return retValue;
} /* IpV4_Arp_VCreatNewEntry() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Arp_VCheckValidityOfEntry
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
TCPIP_LOCAL FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_VCheckValidityOfEntry(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) PhysAddrPtr,
  IpBase_AddrInType                       NetAddr,
  TcpIp_SizeOfArpTableEntryType           ArpTableEntryIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType retValue = TCPIP_E_PHYS_ADDR_MISS;
  TcpIp_SizeOfArpConfigType arpConfigIdx = TcpIp_GetArpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the entry is too old or not. */
  /* timestamp contains the value in terms of mainfunction cycles */
  IpV4_Arp_MainFuncCycleType timestamp = TcpIp_GetCreationTimeStampOfArpTableEntry(ArpTableEntryIdx);

  TCPIP_ASSERT(arpConfigIdx     < TcpIp_GetSizeOfArpConfig());
  TCPIP_ASSERT(ArpTableEntryIdx < TcpIp_GetSizeOfArpTableEntry());

  /* we know that IpV4_Arp_MainFuncCycle will always be bigger than timestamp, so the values can be subtracted without considering the integer overflow */
  if (   (TcpIp_GetEntryTimeoutOfArpConfig(arpConfigIdx) == 0u)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || ((IpV4_Arp_MainFuncCycle - timestamp) < TcpIp_GetEntryTimeoutOfArpConfig(arpConfigIdx)))
  {
    /* table entry is not out of date */
    if (   (TcpIp_GetStatusOfArpTableEntry(ArpTableEntryIdx) == IPV4_ARP_ELSTATUS_VALID)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetStatusOfArpTableEntry(ArpTableEntryIdx) == IPV4_ARP_ELSTATUS_PROBE))
    {
      /* #20 If Valid  entry is found for this network address, then return physical address. */
      TcpIp_VCopyPhysAddr(PhysAddrPtr, &TcpIp_GetAddrPhysAddrOfArpTableEntry(ArpTableEntryIdx)->data[0]);               /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
      retValue = TCPIP_OK;
    }
    /* #30 Otherwise: Send Arp request, If Retry time is not expired. */
    else if ( (IpV4_Arp_MainFuncCycle - TcpIp_GetCreationTimeStampOfArpTableEntry(ArpTableEntryIdx))
             < TcpIp_GetRetryTimeOfArpConfig(arpConfigIdx))
    {
      /* #40 Send Arp Request if Upper layer has triggered transmission after ArpRequestTimeout. */
      if (  (IpV4_Arp_MainFuncCycle - TcpIp_GetTimeStampOfArpTableEntry(ArpTableEntryIdx))
          >= TcpIp_GetRequestTimeoutOfArpConfig(arpConfigIdx))
      {
        if (IpV4_Arp_SendArpRequest(IpV4CtrlIdx, NetAddr) == E_OK)
        {
          TcpIp_SetTimeStampOfArpTableEntry(ArpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                 /* SBSW_TCPIP_FUNC_PARAM_CALLER */
        }
      }
    }
    else
    {
      /* else: ARP request already is in progress, RetValue remains TCPIP_E_PHYS_ADDR_MISS */
    }
  }
  else
  {
    /* #50 If Entry is too old, Change its state to PROBE continue and reset timestamp. */
    TcpIp_SetStatusOfArpTableEntry(ArpTableEntryIdx, IPV4_ARP_ELSTATUS_PROBE);                                          /* SBSW_TCPIP_FUNC_PARAM_CALLER */
    TcpIp_SetTimeStampOfArpTableEntry(ArpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                        /* SBSW_TCPIP_FUNC_PARAM_CALLER */
    TcpIp_SetCreationTimeStampOfArpTableEntry(ArpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                /* SBSW_TCPIP_FUNC_PARAM_CALLER */

    IpV4_Arp_NumPendEle++;

    retValue = TCPIP_OK;
    /*#60 Send Arp Request for the above too old  arp entry but still existed in the arp Resolution table(in state PROBE).*/
    if(IpV4_Arp_SendArpRequest(IpV4CtrlIdx, NetAddr) != E_OK)
    {
      retValue = TCPIP_E_NOT_OK;
    }
    /* else RetValue remains TCPIP_OK */
  }
  return retValue;
} /* IpV4_Arp_VCheckValidityOfEntry() */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Arp_VCheckArpEntry
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
TCPIP_LOCAL FUNC(TcpIp_SizeOfArpTableEntryType, IPV4_CODE) IpV4_Arp_VCheckArpEntry(
  TcpIp_IpV4CtrlIterType                                         IpV4CtrlIdx,
  TcpIp_IpV4SocketDynIterType                                    IpV4SocketIdx,
  IpBase_AddrInType                                              NetAddr,
  P2VAR(boolean, AUTOMATIC, IPV4_APPL_VAR)                       TableFullPtr,
  P2VAR(TcpIp_SizeOfArpTableEntryType, AUTOMATIC, IPV4_APPL_VAR) LruArpTableEntryIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ArpTableEntryIterType arpTableEntryIdx;

  /* Assume that first entry is the least recently used entry, this value is updated below if an older entry is found. */
  *LruArpTableEntryIdxPtr = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);                                      /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */

  /* ----- Implementation ----------------------------------------------- */
  /* there is no valid entry in mapping table */
  /* #10 Iterate over ARP entry table. */
  for (arpTableEntryIdx = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx < TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx++)
  {
    /* #20 Check if ARP entry already exists (without entry in mapping table). */
    if (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) != IPV4_ARP_ELSTATUS_INVALID)
    {
      /* #30 Compare network addresses. */
      if (TcpIp_GetNetAddrOfArpTableEntry(arpTableEntryIdx) == NetAddr)
      {
        /* #40 If the entry is found("valid" or "in progress"), update socket mapping table. So entry is found faster next time. */
        if (IpV4SocketIdx != IPV4_INV_SOCK_IDX)
        {
          TcpIp_SetIpV4CtrlIdxOfIpV4SocketDyn(IpV4SocketIdx, (TcpIp_SizeOfIpV4CtrlType)IpV4CtrlIdx);                    /* SBSW_TCPIP_FUNC_PARAM_SOCK */
          TcpIp_SetArpTableEntryIdxOfIpV4SocketDyn(IpV4SocketIdx, (TcpIp_SizeOfArpTableEntryType)arpTableEntryIdx);     /* SBSW_TCPIP_FUNC_PARAM_SOCK */
        }
        break;
      }
      /* #50 If the entry is found as valid and too old, store it as a last recently used entry. */
      if (  (IPV4_ARP_ELSTATUS_INVALID != TcpIp_GetStatusOfArpTableEntry(*LruArpTableEntryIdxPtr))  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && IPV4_ARP_TIMESTAMP_IS_OLDER(TcpIp_GetTimeStampOfArpTableEntry(arpTableEntryIdx),
                                         TcpIp_GetTimeStampOfArpTableEntry(*LruArpTableEntryIdxPtr)))
      {
        /* Store index of least recently used entry, if we need space for a new element later */
        *LruArpTableEntryIdxPtr = (TcpIp_SizeOfArpTableEntryType)arpTableEntryIdx;                                      /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
        /* Flag to denote if the table is full or not.*/
        /* If discarded handling is on, table will be kept unmodified and new entry will be discarded */
#if (TCPIP_SUPPORT_ARP_DISCARDED_ENTRY_HANDLING == STD_ON)
        *TableFullPtr = TRUE;                                                                                           /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
#else
        *TableFullPtr = FALSE;                                                                                          /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
#endif
      }
    }
    else
    {
      /* #60 ARP entry does not exist. Store invalid (unused) entry as least recently used entry. */
      *LruArpTableEntryIdxPtr = (TcpIp_SizeOfArpTableEntryType)arpTableEntryIdx;                                        /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
      *TableFullPtr = FALSE;                                                                                            /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
    }
  }

  /* Return TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN if no matching entry was found. */
  if (arpTableEntryIdx >= TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx))
  {
    arpTableEntryIdx = TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN;
  }

  return (TcpIp_SizeOfArpTableEntryType)arpTableEntryIdx;
} /* IpV4_Arp_VCheckArpEntry() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Arp_VProcessPendingEntries
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
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VProcessPendingEntries(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  TcpIp_ArpTableEntryIterType arpTableEntryIdx;
  TcpIp_SizeOfArpConfigType   arpConfigIdx = TcpIp_GetArpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* #10 Iterate over the ARP table. */
  for (arpTableEntryIdx = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx < TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx++)
  {
    TCPIP_ASSERT(arpConfigIdx < TcpIp_GetSizeOfArpConfig());

    /* #20 Check the status of each entry. */
    if (   (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_INPROGESS)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_PROBE) )
    {
      /* #30 Remove entry from ARP table if retry time has exceeded. */
      if (  (IpV4_Arp_MainFuncCycle - TcpIp_GetCreationTimeStampOfArpTableEntry(arpTableEntryIdx))
          >= TcpIp_GetRetryTimeOfArpConfig(arpConfigIdx))
      {
        TCPIP_VENTER_CRITICAL_SECTION();
        /* #40 Invalidate the ARP entry and decrement the globle variable for the pending entry. */
        /* timeout expired, invalidate the table entry */
        IpV4_Arp_VPhysAddrTableChgNotification(IpV4CtrlIdx, (TcpIp_SizeOfArpTableEntryType)arpTableEntryIdx, FALSE);
        TcpIp_SetStatusOfArpTableEntry(arpTableEntryIdx, IPV4_ARP_ELSTATUS_INVALID);                                    /* SBSW_TCPIP_ARP_CSL03_IDX_BASED_ON_CALLER */
        IpV4_Arp_NumPendEle--;
        {
          TcpIp_SockAddrBaseType DestSockAddrIn; /* PRQA S 0759 */ /* MD_MSR_Union */
          DestSockAddrIn.SockAddrIn.sin_family = IPBASE_AF_INET;
          DestSockAddrIn.SockAddrIn.sin_addr   = TcpIp_GetNetAddrOfArpTableEntry(arpTableEntryIdx);
          /* #50 Notifies the TcpIp that the link layer address resolution for the specified destination timed out. */
          /* call timeout function */
          TcpIp_Cbk_VAddrResTimeout(&DestSockAddrIn);                                                                   /* SBSW_TCPIP_UPDATE_VARIABLE */
#if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                    /* COV_TCPIP_ICMPV4_ALWAYS_ON */
          /* #60 Call the upper layer to cancel ICMP echo reply by reseting the Echo reply pending flag incase the time out occured. */
          IpV4_Icmp_Cbk_VAddrResTimeout(IpV4CtrlIdx, DestSockAddrIn.SockAddrIn.sin_addr);
#endif
        }
        TCPIP_VLEAVE_CRITICAL_SECTION();
        /* #70 if no pending entry exists, break the for loop. Don't do anything. */
        if (IpV4_Arp_NumPendEle == 0u)
        {
          break;
        }

      }
      /* #80 Send ARP Request if time interval between ARP requests has been reached, otherwise wait for Arp esponse or timeout. */
      else if (   (TcpIp_GetRetryIntervalOfArpConfig(arpConfigIdx) !=0u) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
               && (( (IpV4_Arp_MainFuncCycle - TcpIp_GetTimeStampOfArpTableEntry(arpTableEntryIdx))
                    % TcpIp_GetRetryIntervalOfArpConfig(arpConfigIdx)) == 0u))
      {
        /* trigger retry */
        (void)IpV4_Arp_SendArpRequest(IpV4CtrlIdx, TcpIp_GetNetAddrOfArpTableEntry(arpTableEntryIdx));
        TcpIp_SetTimeStampOfArpTableEntry(arpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                    /* SBSW_TCPIP_FUNC_PARAM_CALLER */
      }
      else
      {
         /* Wait for ARP response or next retry timeout. */
      }
    }
  }
} /* IpV4_Arp_VProcessPendingEntries() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Arp_GetPhysicalAddressFromDynamicTables
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
TCPIP_LOCAL FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_GetPhysicalAddressFromDynamicTables(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  TcpIp_SizeOfIpV4SocketDynType           IpV4SocketIdx,
  IpBase_AddrInType                       NetAddr,
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) PhysAddrPtr,
  boolean                                 InitRes)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType retValue = TCPIP_E_PHYS_ADDR_MISS;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the Dynamic table is configured for the given controller. */
  if (TcpIp_IsArpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
# if defined(TCPIP_ASSERT_HANDLER)                                                                                      /* COV_TCPIP_CANOE_DEBUG */
    TcpIp_SizeOfArpConfigType arpConfigIdx;
# endif
    boolean                          elemInTable;
    TcpIp_SizeOfArpTableEntryType    arpTableEntryIdx;
    TcpIp_SizeOfArpTableEntryType lruArpTableEntryIdx = 0;  /* least recently used entry index */
    boolean        tableFull   = FALSE; /* flag to indicate that tableIdxLru contains an entry that will be overwritten (i.e. not an entry that's still unused) */
# if defined(TCPIP_ASSERT_HANDLER)                                                                                      /* COV_TCPIP_CANOE_DEBUG */
    arpConfigIdx = TcpIp_GetArpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
# endif
    TCPIP_ASSERT(arpConfigIdx < TcpIp_GetSizeOfArpConfig());
    TCPIP_ASSERT(TcpIp_GetTableSizeOfArpConfig(arpConfigIdx) > 0u);
     /* Do not check the whole table but only the element for this socket
      - check if IP address is still the same
      - read physical address */
    /* #20 Check if there is an entry in socket mapping table mapped to this socket. */
    if (IpV4SocketIdx != IPV4_INV_SOCK_IDX)
    {
      if (TcpIp_GetIpV4CtrlIdxOfIpV4SocketDyn(IpV4SocketIdx) != IpV4CtrlIdx)
      {
        arpTableEntryIdx = TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN;
      }
      else
      {
        arpTableEntryIdx = TcpIp_GetArpTableEntryIdxOfIpV4SocketDyn(IpV4SocketIdx);
      }
    }
    else
    {
      arpTableEntryIdx = TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN;
    }

    if (   (arpTableEntryIdx != TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN )  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) != IPV4_ARP_ELSTATUS_INVALID)
        && (TcpIp_GetNetAddrOfArpTableEntry(arpTableEntryIdx) == NetAddr))
    {
      /* there is an entry for this network address ("valid" or "in progress") */
      elemInTable = TRUE;
    }
    else
    {
      TCPIP_VENTER_CRITICAL_SECTION();  /* lock interrupts */
      /* there is no valid entry in mapping table */
      /* #30 Otherwise check if ARP entry already exists (without entry in mapping table). */
      arpTableEntryIdx = IpV4_Arp_VCheckArpEntry(IpV4CtrlIdx, IpV4SocketIdx, NetAddr, &tableFull, &lruArpTableEntryIdx);/* SBSW_TCPIP_UPDATE_VARIABLE */

      elemInTable = (boolean)(arpTableEntryIdx != TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN);                             /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
      /* Below check makes sure that arpTableEntryIdx would not get overwritten deu to RxIndication Interrupt. */
      /* Set the LRU to In_Progress, if the entry is not present in table */
      if ((elemInTable == FALSE) && (InitRes == TRUE) && (tableFull  == FALSE))
      {
#if (TCPIP_SUPPORT_ARP_DISCARDED_ENTRY_HANDLING == STD_OFF)
        /* Inform the upper layer about the creation of the new entry, but set the valid flag to FALSE because the address has not yet been resolved
          (callout will be called again with valid = TRUE in the Rx - indication, later on)
           Calling the callout immediately after creation of the new entry(and any change in ARP table) is an AUTOSAR requirement */
        /* If no entry is present, LRU shall be deleted (overwritten) and new arp entry will be created later. */
        /* #40 Inform upper layer about deletion of LRU entry if the LRU is previously valid. */
        if (TcpIp_GetStatusOfArpTableEntry(lruArpTableEntryIdx) != IPV4_ARP_ELSTATUS_INVALID)
        {
          IpV4_Arp_VPhysAddrTableChgNotification(IpV4CtrlIdx, lruArpTableEntryIdx, FALSE);
        }
#endif
        /* Set the LRU state to INPROGRESS to ensure that it is not overwritten in a different context */
        TcpIp_SetStatusOfArpTableEntry(lruArpTableEntryIdx, IPV4_ARP_ELSTATUS_INPROGESS);                                       /* SBSW_TCPIP_LRUINDEX_CALLER */

      }
      TCPIP_VLEAVE_CRITICAL_SECTION();  /* unlock interrupts */
    }

    if (elemInTable == TRUE)
    {
      /* #50 Check if Entry is too old. */
      TCPIP_ASSERT(arpTableEntryIdx >= TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx));
      TCPIP_ASSERT(arpTableEntryIdx <  TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx));
      retValue = IpV4_Arp_VCheckValidityOfEntry(IpV4CtrlIdx, PhysAddrPtr, NetAddr, arpTableEntryIdx);                   /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
    }
    else
    {
      /* #60 No matching element in table. Create a new entry and trigger ARP request in case the caller desires that. */
      if (InitRes == TRUE)
      {
        TCPIP_ASSERT(lruArpTableEntryIdx >= TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx));
        TCPIP_ASSERT(lruArpTableEntryIdx <  TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx));
        retValue = IpV4_Arp_VCreateEntry(IpV4CtrlIdx, IpV4SocketIdx, NetAddr, tableFull, lruArpTableEntryIdx);
      }
    }
  }

  return retValue;
}  /* IpV4_Arp_GetPhysicalAddressFromDynamicTables() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Arp_GetPhysicalAddress
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
FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_GetPhysicalAddress(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  TcpIp_SizeOfIpV4SocketDynType           SocketIdx,
  IpBase_AddrInType                       NetAddr,
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) PhysAddrPtr,
  boolean                                 InitRes )
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType retVal;
  IpBase_AddrInType invertedNetMask;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl());
  TCPIP_ASSERT(PhysAddrPtr != NULL_PTR);

  /* #10 Return calculated group MAC address, if IP address is multicast address. */
  if (IPV4_ADDR_IS_MULTICAST(NetAddr))
  {
    IpV4_Arp_MapIpToPhysMulticastAddr(NetAddr, PhysAddrPtr);                                                            /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
    retVal = TCPIP_OK;
  }
  else
  {
    invertedNetMask = ~TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(IpV4CtrlIdx);
    /* #20 Return broadcast MAC address, if IP address is global or local broadcast. */
    if ((NetAddr & invertedNetMask) == invertedNetMask)
    {
      TcpIp_VCopyPhysAddr(PhysAddrPtr, IpV4_Arp_PhysBroadcastAddr);                                                     /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */ /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
      retVal = TCPIP_OK;
    }
    /* #30 Verify if the IP address is valid. */
    else if ((invertedNetMask & NetAddr) == 0u)
    {
      retVal = TCPIP_E_NOT_OK;
    }
    /* #40 Check if static mapping is configured, if static ARP table is configured. */
    else if (IpV4_Arp_VStaticTableLookup(IpV4CtrlIdx, NetAddr, PhysAddrPtr) == E_OK)                                    /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
    {
      retVal = TCPIP_OK;
    }
    /* #50 Search for cached mapping in dynamic ARP table or trigger address resolution if required. */
    else
    {
      retVal = IpV4_Arp_GetPhysicalAddressFromDynamicTables(IpV4CtrlIdx, SocketIdx, NetAddr, PhysAddrPtr, InitRes);     /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
    }
  }
  return retVal;
} /* IpV4_Arp_GetPhysicalAddress() */

/**********************************************************************************************************************
 *  IpV4_Arp_RxIndication
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_RxIndication(
  TcpIp_SizeOfEthIfCtrlType                EthIfCtrlIdx,
  Eth_FrameType                            FrameType,
  boolean                                  IsBroadcast,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) PhysAddrPtr,    /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,        /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  uint16                                   LenByte )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = IPV4_E_NO_ERROR;

  IPV4_UNUSED_PARAMETER(FrameType);    /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  IPV4_UNUSED_PARAMETER(IsBroadcast);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  IPV4_UNUSED_PARAMETER(PhysAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (IpV4_State == IPV4_STATE_UNINIT)
  {
    errorId = IPV4_E_NOT_INITIALIZED;
  }
  /* Check parameter 'EthIfCtrlIdx' */
  else if (EthIfCtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = IPV4_E_INV_PARAM;
  }
  /* Check parameter 'FrameType' */
  else if (FrameType != IPV4_ARP_FRAME_TYPE)
  {
    errorId = IPV4_E_INV_PARAM;
  }
   /* Check parameter 'PhysAddrPtr' */
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward call to Subfunction. */
    /* Read the received message data.*/
    IpV4_Arp_VReadMsgData(EthIfCtrlIdx, DataPtr, LenByte);                                                              /* SBSW_TCPIP_FUNC_PARAM_PTR_CALLER */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != IPV4_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, IPV4_VINSTANCE_ID, IPV4_ARP_API_ID_RX_INDICATION, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

} /* IpV4_Arp_RxIndication() */ /* PRQA S 6050, 6060, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Arp_VReadMsgData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VReadMsgData(
  TcpIp_SizeOfEthIfCtrlType                  EthIfCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     LenByte)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP instance is configured for a given Controller. */
  if ((TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE) && (LenByte >= IPV4_ARP_PACKET_LEN_BYTE))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      TcpIp_IpV4CtrlIterType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);

      if ((TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) != IPV4_IP_OFFLINE))
      {
        uint16 hwAddrType   = TCPIP_GET_UINT16(DataPtr, IPV4_ARP_HW_ADDR_TYPE_OFS);
        uint16 protAddrType = TCPIP_GET_UINT16(DataPtr, IPV4_ARP_PR_ADDR_TYPE_OFS);
        uint8  hwAddrSize   = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_HW_ADDR_SIZE_OFS);
        uint8  protAddrSize = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_PR_ADDR_SIZE_OFS);
        uint16 operation    = TCPIP_GET_UINT16(DataPtr, IPV4_ARP_OP_OFS);

        /* #20 Check ARP hardware and protocol address formats. */
        if (   (hwAddrType   == IPV4_ARP_HW_ADDR_TYPE_ETHERNET)
            && (hwAddrSize   == IPV4_ARP_HW_ADDR_SIZE_ETHERNET)
            && (protAddrType == IPV4_ARP_PROT_ADDR_TYPE_IPV4)
            && (protAddrSize == IPV4_ARP_PROT_ADDR_SIZE_IPV4))
        {
          IpBase_AddrInType srcIpAddr;
          IpBase_AddrInType dstIpAddr;
          IpBase_EthPhysAddrType srcPhysAddr;
          srcIpAddr = TCPIP_GET_UINT32(DataPtr, IPV4_ARP_SRC_IP_ADDR_OFS);
          srcIpAddr = TCPIP_NTOHL(srcIpAddr);

          dstIpAddr = TCPIP_GET_UINT32(DataPtr, IPV4_ARP_DST_IP_ADDR_OFS);
          dstIpAddr = TCPIP_NTOHL(dstIpAddr);

          srcPhysAddr[0] = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_SRC_MC_ADDR_OFS);                                          /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */
          srcPhysAddr[1] = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 1u);                                     /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */
          srcPhysAddr[2] = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 2u);                                     /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */
          srcPhysAddr[3] = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 3u);                                     /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */
          srcPhysAddr[4] = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 4u);                                     /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */
          srcPhysAddr[5] = TCPIP_GET_UINT8(DataPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 5u);                                     /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */

          /* #30 Handle received ARP packet. */
          IpV4_Arp_VHandlePacket(ipV4CtrlIdx, operation, srcIpAddr, dstIpAddr, srcPhysAddr);                            /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
        }
      }
    } /* else: Ip instance is not configured and length is invalid */
}

/**********************************************************************************************************************
 *  IpV4_Arp_SendArpRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendArpRequest(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      NetAddr )
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_AddrInType       locNetAddr; /* Source IP address */

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl());

  /* #10 Prepare ARP request. */
  locNetAddr = TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx);

  /* #20 Send an ARP request. */
  return IpV4_Arp_VSendMessage(IpV4CtrlIdx, NetAddr, locNetAddr, &IpV4_Arp_PhysBroadcastAddr[0], IPV4_ARP_OP_REQUEST);  /* SBSW_TCPIP_STATIC_BRODCAST_PHYSADDR */
} /* IpV4_Arp_SendArpRequest() */

/**********************************************************************************************************************
 *  IpV4_Arp_SendArpProbe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendArpProbe(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      IpAddrToProbe)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_AddrInType       remNetAddr;
  IpBase_AddrInType       locNetAddr;
  IpBase_EthPhysAddrType  remPhysAddr;
  uint16                  operation;
  uint8_least             physAddrByteIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl());

  /* #10 Set all bytes of a target hardware address to zero. */
  /* "The 'target hardware address' field is ignored and SHOULD be set to all zeroes. */
  for (physAddrByteIdx = 0; physAddrByteIdx < IPBASE_ETH_PHYS_ADDR_LEN_BYTE; physAddrByteIdx++)
  {
    remPhysAddr[physAddrByteIdx] = 0;                                                                                   /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */
  }

  /* #20 Prepare ARP request. */
  locNetAddr = 0;                   /* "... with an all-zero 'sender IP address'." */
  remNetAddr = IpAddrToProbe;       /* "The 'target IP address' field MUST be set to the address being probed." */
  operation  = IPV4_ARP_OP_REQUEST; /* "ARP Request packet, broadcast on the local link" */

  /* #30 Send ARP request. */
  return IpV4_Arp_VSendMessage(IpV4CtrlIdx, remNetAddr, locNetAddr, &remPhysAddr[0], operation);                        /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
} /* IpV4_Arp_SendArpProbe() */

/**********************************************************************************************************************
 *  IpV4_Arp_SendArpAnnouncement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendArpAnnouncement(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      IpAddrToAnnounce)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_AddrInType       remNetAddr;
  IpBase_AddrInType       locNetAddr;
  IpBase_EthPhysAddrType  remPhysAddr;
  uint16                  operation;
  uint8_least             physAddrByteIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl());

  /* "'ARP Announcement' is [...] an ARP Request packet,
   *  broadcast on the local link, identical to the ARP Probe [...]
   *  except that both the sender and target IP address fields contain the IP address being announced."
   */
  /* #10 Set all bytes of a target hardware address to zero.*/
  /* "The 'target hardware address' field is ignored and SHOULD be set to all zeroes. */
  for (physAddrByteIdx = 0; physAddrByteIdx < IPBASE_ETH_PHYS_ADDR_LEN_BYTE; physAddrByteIdx++)
  {
    remPhysAddr[physAddrByteIdx] = 0;                                                                                   /* SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR */
  }

  /* #20 Prepare ARP request. */
  locNetAddr = IpAddrToAnnounce;
  remNetAddr = IpAddrToAnnounce;    /* "The 'target IP address' field MUST be set to the address being probed." */
  operation  = IPV4_ARP_OP_REQUEST; /* "ARP Request packet, broadcast on the local link" */

  /* #30 Send ARP request. */
  return IpV4_Arp_VSendMessage(IpV4CtrlIdx, remNetAddr, locNetAddr, &remPhysAddr[0], operation);                        /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
} /* IpV4_Arp_SendArpAnnouncement() */

/**********************************************************************************************************************
 *  IpV4_Arp_SendGratuitousArpReq
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendGratuitousArpReq(TcpIp_LocalAddrV4IterType LocalAddrV4Idx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_NOT_OK;

  TcpIp_SizeOfIpV4CtrlType IpV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  IpV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  /* #10 Verify that IP instance is in state ONLINE. */
  if(TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_ACTIVE)
  {
    IpBase_AddrInType       remNetAddr;
    IpBase_AddrInType       locNetAddr;
    uint16                  operation;
    IpBase_AddrInType       locIpAddr = TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx);

    /* #20 Fill the C-struct parameter that is given to IpV4_Arp_VSendMessage() in order to send a broadcast ARP request to publish the LocIpAddr. */
    locNetAddr = locIpAddr;           /* "In either case, the ARP Sender Protocol Address [...] are both set to the IP address of the cache entry to be updated" */
    remNetAddr = locIpAddr;           /* "In either case, the [...] ARP Target Protocol Address are both set to the IP address of the cache entry to be updated" */
    operation  = IPV4_ARP_OP_REQUEST; /* "ARP Request packet, broadcast on the local link" */

    /* #30 Pass the request to send the ARP request to the internal helper function that transmits ARP packages. */
    retVal = IpV4_Arp_VSendMessage(IpV4CtrlIdx, remNetAddr, locNetAddr, &IpV4_Arp_PhysBroadcastAddr[0], operation);     /* SBSW_TCPIP_STATIC_BRODCAST_PHYSADDR */
  }
  return retVal;
} /* IpV4_Arp_SendGratuitousArpReq() */

/**********************************************************************************************************************
*  IpV4_Arp_SendGratuitousArpReply
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendGratuitousArpReply(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal;
  IpBase_AddrInType       remNetAddr;
  IpBase_AddrInType       locNetAddr;
  uint16                  operation;
  IpBase_EthPhysAddrType  srcMacAddr;
  /* ----- Implementation ----------------------------------------------- */

  IpBase_AddrInType       locIpAddr = TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx);
  /* #10 Get source MAC address. */
  TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), srcMacAddr);                                       /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */

  /* #20 Fill the C-struct parameter that is given to IpV4_Arp_VSendMessage() in order to send gratuitous ARP reply to publish the LocIpAddr. */
  locNetAddr = locIpAddr;           /* "In either case, the ARP Sender Protocol Address [...] are both set to the IP address of the cache entry to be updated" */
  remNetAddr = locIpAddr;           /* "In either case, the [...] ARP Target Protocol Address are both set to the IP address of the cache entry to be updated" */
  operation = IPV4_ARP_OP_REPLY; /* "ARP Reply packet, broadcast on the local link" */

    /* #30 Pass the request to send the ARP request to the internal helper function that transmits ARP packages. */
  retVal = IpV4_Arp_VSendMessage(IpV4CtrlIdx, remNetAddr, locNetAddr, srcMacAddr, operation);                           /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */

  return retVal;
} /* IpV4_Arp_SendGratuitousArpReply() */

/**********************************************************************************************************************
*  IpV4_Arp_SendGratuitousArpOnStartup
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
FUNC(void, IPV4_CODE) IpV4_Arp_SendGratuitousArpOnStartup(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal;
  TcpIp_ArpConfigIterType arpConfigIdx = TcpIp_GetArpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_GratuitousArpIterType gratuitousArpIdx = TcpIp_GetGratuitousArpIdxOfIpV4Ctrl(IpV4CtrlIdx);
  uint8 numOfTxGratuitousReply = TcpIp_GetTransmissionCntOfGratuitousArp(gratuitousArpIdx);

  /* #10 Set the time stamp to send the first Arp gratuitous reply. */
  if (numOfTxGratuitousReply == 0u)
  {
    TcpIp_SetNextTransmissionMsOfGratuitousArp(gratuitousArpIdx, IpV4_Arp_MainFuncCycle);                               /* SBSW_TCPIP_ARP_CSL03_IDX_BASED_ON_CALLER */
  }

  /* #20 Check if configured number of Gratuitous arp reply has been sent.*/
  if (numOfTxGratuitousReply < TcpIp_GetNumGratuitousArpOnStartupOfArpConfig(arpConfigIdx))
  {
    /* #30 Verify the time interwal between two gratuitous arp replys. */
    if (IpV4_Arp_MainFuncCycle >= TcpIp_GetNextTransmissionMsOfGratuitousArp(gratuitousArpIdx))
    {
      retVal = IpV4_Arp_SendGratuitousArpReply(IpV4CtrlIdx);
      /* #40 Increament the count of number of transmitted gratuituos ARP replys and set the time for the next
              transmission, if ARP gratuitous reply has been succcessfully sent. */
      if (retVal == E_OK)
      {
        TcpIp_SetNextTransmissionMsOfGratuitousArp(gratuitousArpIdx,                                                    /* SBSW_TCPIP_ARP_CSL03_IDX_BASED_ON_CALLER */
                                                    (IpV4_Arp_MainFuncCycle
                                                    + IPV4_ARP_GRATUITOUS_REPLY_INTERVAL));
        TcpIp_IncTransmissionCntOfGratuitousArp(gratuitousArpIdx);                                                      /* SBSW_TCPIP_ARP_CSL03_IDX_BASED_ON_CALLER */
      }
    }
  }
} /* IpV4_Arp_SendGratuitousArpOnStartup() */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Arp_MainFunction
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
FUNC(void, IPV4_CODE) IpV4_Arp_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlIterType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Increment MainFunction cycle counter. */
  IpV4_Arp_MainFuncCycle++;

  /* #20 Iterate over all configured IPv4 controllers. */
  for(ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl(); ipV4CtrlIdx++)
  {
    /* #30 Send Gratuitous ARP reply if Ip address is assigned through DHCP or STATIC address assignment method. */
    /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    if (   (TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(ipV4CtrlIdx) == TCPIP_IPADDR_ASSIGNMENT_DHCP)
        || (TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(ipV4CtrlIdx) == TCPIP_IPADDR_ASSIGNMENT_STATIC))
    {
      /* #40 If gratuitous ARP is configured for the controller, transmit */
      if (TcpIp_IsGratuitousArpUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)
      {
        /* #50 Send configured number of Arp Gratuitous reply on start up. */
        IpV4_Arp_SendGratuitousArpOnStartup(ipV4CtrlIdx);
      }
    }

    /* #60 Check if there are pending entries in the ARP table and ARP Requests have to be sent. */
    if(IpV4_Arp_NumPendEle != 0u)
    {
      IpV4_Arp_VProcessPendingEntries(ipV4CtrlIdx);
    }
  }
} /* IpV4_Arp_MainFunction() */

/**********************************************************************************************************************
 *  IpV4_Arp_Reset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Arp_Reset(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfArpTableEntryType  arpTableEntryIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl());

  /* #10 Mark each element in the ARP table as invalid. */
  for (arpTableEntryIdx = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx < TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx++)
  {
    /* for all table elements */
    TcpIp_SetStatusOfArpTableEntry(arpTableEntryIdx, IPV4_ARP_ELSTATUS_INVALID);                                        /* SBSW_TCPIP_ARP_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetNetAddrOfArpTableEntry(arpTableEntryIdx, 0);                                                               /* SBSW_TCPIP_ARP_CSL03_IDX_BASED_ON_CALLER */
  }

  /* #20 Reset counter of pending ARP resolutions. */
  IpV4_Arp_NumPendEle = 0;
}

/**********************************************************************************************************************
 *  IpV4_Arp_GetCacheEntries
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_GetCacheEntries(
  TcpIp_SizeOfEthIfCtrlType         EthIfCtrlIdx,
  IPV4_P2V(uint32)                  NumberOfElementsPtr,
  IPV4_P2V(TcpIp_ArpCacheEntryType) EntryListPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Check if IP instance is configured for given EthIfCtrlIdx */
  if (TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE)
  {
    TcpIp_SizeOfIpV4CtrlType  IpV4CtrlIdx;
    IpV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);

    /* #20 Verify that IP instance is in state ONLINE. */
    if (TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_ACTIVE)
    {
      uint32 totalNumOfDynamicElements;
      uint32 totalNumOfStaticElements;
      uint32 globTableIdx = 0; /* Entrylist Index */
      /* Read only the number of valid entries into the ARP table. */
      if (*NumberOfElementsPtr == 0u)
      {
        totalNumOfStaticElements = IpV4_Arp_VReadStaticTable(IpV4CtrlIdx, *NumberOfElementsPtr, NULL_PTR, &globTableIdx); /* SBSW_TCPIP_NULL_PTR_ALLOWED */ /* SBSW_TCPIP_UPDATE_VARIABLE */

        totalNumOfDynamicElements = IpV4_Arp_VReadDynTable(IpV4CtrlIdx, *NumberOfElementsPtr, NULL_PTR, &globTableIdx); /* SBSW_TCPIP_NULL_PTR_ALLOWED */ /* SBSW_TCPIP_UPDATE_VARIABLE */
      }
      else
      {
        /* #30 Copy static table entries, if configured. */
        totalNumOfStaticElements = IpV4_Arp_VReadStaticTable(IpV4CtrlIdx, *NumberOfElementsPtr, EntryListPtr, &globTableIdx); /* SBSW_TCPIP_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_UPDATE_VARIABLE */
        /* IpV4_Arp_VReadStaticTable() does not return a value > *NumberOfElementsPtr. */
        *NumberOfElementsPtr -= totalNumOfStaticElements;                                                               /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
        /* #40 Copy dynamic table entries, if configured. */
        totalNumOfDynamicElements = IpV4_Arp_VReadDynTable(IpV4CtrlIdx, *NumberOfElementsPtr, EntryListPtr, &globTableIdx); /* SBSW_TCPIP_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_UPDATE_VARIABLE */
      }

      *NumberOfElementsPtr = totalNumOfDynamicElements + totalNumOfStaticElements;                                      /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
      retVal = E_OK;
    }
  }

  return retVal;
} /* IpV4_Arp_GetCacheEntries() */

/**********************************************************************************************************************
 *  IpV4_Arp_ClearCache
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_ClearCache(TcpIp_LocalAddrV4IterType LocalAddrV4Idx)
{
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  /* #10 Clear dynamic ARP cache. */
  IpV4_Arp_Reset(TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx));
}

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  IpV4_Arp_VReadStaticTable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(uint32, IPV4_CODE) IpV4_Arp_VReadStaticTable(
  TcpIp_IpV4CtrlIterType                                        IpV4CtrlIdx,
  uint32                                                        NumOfElements,
  P2VAR(TcpIp_ArpCacheEntryType, IPV4_APPL_DATA, IPV4_APPL_VAR) EntryListPtr,
  IPV4_P2V(uint32)                                              EntryListIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 totalNumOfStaticElementsToRead = 0;  /* Number of static entries that are read from the static arp table.*/
  /* Index to iterate over arp cache entries stored in the related controller cache */
  uint32 staticArpEntryLimitIdx;
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfStaticArpTableType staticArpTableIdx = TcpIp_GetStaticArpTableIdxOfIpV4Ctrl(IpV4CtrlIdx);
  /* #10 Check if the StaticArptable is configured. */
  if (staticArpTableIdx != TCPIP_NO_STATICARPTABLEIDXOFIPV4CTRL)
  {
    TcpIp_SizeOfStaticArpEntryType numElementsInStaticArpTable = (  TcpIp_GetStaticArpEntryEndIdxOfStaticArpTable(staticArpTableIdx)
                                                                  - TcpIp_GetStaticArpEntryStartIdxOfStaticArpTable(staticArpTableIdx));

    if ((EntryListPtr == NULL_PTR) || (NumOfElements > numElementsInStaticArpTable))
    {
      totalNumOfStaticElementsToRead = numElementsInStaticArpTable;
    }
    else
    {
      totalNumOfStaticElementsToRead = NumOfElements;
    }

    staticArpEntryLimitIdx = TcpIp_GetStaticArpEntryStartIdxOfStaticArpTable(staticArpTableIdx) + totalNumOfStaticElementsToRead;
    /* Check if the buffer is valid */
    if (EntryListPtr != NULL_PTR)
    { /* Index to read cache entries */
      TcpIp_StaticArpEntryIterType staticArpEntryIdx;
      /* Index to write into the Entrylist buffer pointer */
      uint32 entryListIdx = 0;

      /* #20 Copy valid entries from  Static table. */
      for (staticArpEntryIdx = TcpIp_GetStaticArpEntryStartIdxOfStaticArpTable(staticArpTableIdx);
           staticArpEntryIdx < staticArpEntryLimitIdx;
           staticArpEntryIdx++)
      { /* #30 Read Ip address, Physical address and state of each entry. */
        TcpIp_PhysAddrOfStaticArpEntryPtrType physAddrPtr = TcpIp_GetAddrPhysAddrOfStaticArpEntry(staticArpEntryIdx);

        TCPIP_ASSERT(staticArpEntryIdx < TcpIp_GetStaticArpEntryEndIdxOfStaticArpTable(staticArpTableIdx));

        EntryListPtr[entryListIdx].InetAddr[0] = TcpIp_GetIpAddrOfStaticArpEntry(staticArpEntryIdx);                    /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */
        EntryListPtr[entryListIdx].PhysAddr[0] = physAddrPtr->data[0];                                                  /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */
        EntryListPtr[entryListIdx].PhysAddr[1] = physAddrPtr->data[1];                                                  /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */
        EntryListPtr[entryListIdx].PhysAddr[2] = physAddrPtr->data[2];                                                  /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */
        EntryListPtr[entryListIdx].PhysAddr[3] = physAddrPtr->data[3];                                                  /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */
        EntryListPtr[entryListIdx].PhysAddr[4] = physAddrPtr->data[4];                                                  /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */
        EntryListPtr[entryListIdx].PhysAddr[5] = physAddrPtr->data[5];                                                  /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */
        EntryListPtr[entryListIdx].State = TCPIP_ARP_ENTRY_STATIC;                                                      /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr */

        entryListIdx++;
      }

      *EntryListIdxPtr = entryListIdx;                                                                                  /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
    }
  }
  return totalNumOfStaticElementsToRead;
} /* IpV4_Arp_VReadStaticTable() */
/**********************************************************************************************************************
 * IpV4_Arp_VWriteValidEntries
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VWriteValidEntries(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  TcpIp_SizeOfArpConfigType         ArpConfigIdx,
  IPV4_P2V(TcpIp_ArpCacheEntryType) EntryListPtr,
  IPV4_P2V(uint32)                  EntryListIdxPtr,
  uint32                            DynElementsToReadLimitIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ArpTableEntryIterType     arpTableEntryIdx; /* ArpConfig Entry index */
  /* Limit index to read the entries from the cache */
  uint32 limitIdxToReadEntries = DynElementsToReadLimitIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* Get  configured ArpConfig(Arp Resolution Table) Index for the Ip controller Index */

   /* #10 Iterate over dynamic ARP table. */
  for (arpTableEntryIdx = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx < limitIdxToReadEntries;
       arpTableEntryIdx++)
  {
    TCPIP_ASSERT(ArpConfigIdx < TcpIp_GetSizeOfArpConfig());
    /* #20 Skip entry if state is INVALID or address resolution is still in progress. */
    if (   (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_INVALID)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_INPROGESS))
    {
      /* Skip entries that are invalid or not resolved yet and update the Limit index to read the entries. */
      if (limitIdxToReadEntries < TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx))
      {
        /* Update the Limit index to read the entries if an invalid entry is found.*/
        (limitIdxToReadEntries)++;
      }
    }
    /* #30 Otherwise: Write valid or stale entry to output entry list. */
    else
    {
      IPV4_P2C(TcpIp_PhysAddrType) physAddrPtr = TcpIp_GetAddrPhysAddrOfArpTableEntry(arpTableEntryIdx);
      /* return valid or stale entry. */
      EntryListPtr[*EntryListIdxPtr].InetAddr[0] = TcpIp_GetNetAddrOfArpTableEntry(arpTableEntryIdx);                   /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr_CALLER */
      TcpIp_VCopyPhysAddr(EntryListPtr[*EntryListIdxPtr].PhysAddr, physAddrPtr->data);                                  /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_EntryListPtr_PHYSADDR_COPY */

      if (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_VALID)
      {
        if(   (IpV4_Arp_MainFuncCycle - TcpIp_GetCreationTimeStampOfArpTableEntry(arpTableEntryIdx))
           >= TcpIp_GetEntryTimeoutOfArpConfig(ArpConfigIdx))
        {
          EntryListPtr[*EntryListIdxPtr].State = TCPIP_ARP_ENTRY_STALE;                                                 /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr_CALLER */
        }
        else
        {
          EntryListPtr[*EntryListIdxPtr].State = TCPIP_ARP_ENTRY_VALID;                                                 /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr_CALLER */
        }
      }
      else
      {
        EntryListPtr[*EntryListIdxPtr].State = TCPIP_ARP_ENTRY_STALE;                                                   /* SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr_CALLER */
      }

      (*EntryListIdxPtr)++;                                                                                             /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
    }
  }
} /* IpV4_Arp_VWriteValidEntries */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
/**********************************************************************************************************************
 * IpV4_Arp_VReadDynTable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(uint32, IPV4_CODE) IpV4_Arp_VReadDynTable(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  uint32                            NumOfElements,
  IPV4_P2V(TcpIp_ArpCacheEntryType) EntryListPtr,
  IPV4_P2V(uint32)                  EntryListIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 numOfDynamicElementsToRead;
  TcpIp_ArpTableEntryIterType arpTableEntryIdx;

  uint32 invalidEntryCount = 0;
  TcpIp_SizeOfArpConfigType arpConfigIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if dynamic ARP table is configured on specified IP controller. */
  if (TcpIp_IsArpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    /* Get configured Arpconfig Index for given Ip controller */
    arpConfigIdx = TcpIp_GetArpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
    /* Get the total number of Arp entries for a particular arpconfig */
    numOfDynamicElementsToRead = TcpIp_GetTableSizeOfArpConfig(arpConfigIdx);

    TCPIP_ASSERT(numOfDynamicElementsToRead == (uint32)(  TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx)
                                                        - TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx)));
    /* #20 Return number of valid entries in the ARP table, if no output buffer was supplied. */
    if (EntryListPtr == NULL_PTR)
    {
      for (arpTableEntryIdx = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
           arpTableEntryIdx < TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx);
           arpTableEntryIdx++)
      {
        if (   (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_INVALID)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            || (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_INPROGESS))
        {
          /* Ignore the entry */
          invalidEntryCount++;
        }
      }
      numOfDynamicElementsToRead -= invalidEntryCount;
    }
    else
    /* #30 Otherwise copy valid entries from the ARP table into the output buffer.
          (Number of entries may be limited by the size of output buffer) */
    {
      uint32 previousTableIdx = *EntryListIdxPtr;
      /* End index to limit the reading of the arp entries from the dynamic table. */
      uint32 readEntryDyntableLimitIdx = numOfDynamicElementsToRead + TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
      /* limit maximum number of returned entries if provided output buffer cannot hold all entries. */
      if (NumOfElements < TcpIp_GetTableSizeOfArpConfig(arpConfigIdx))
      {
        readEntryDyntableLimitIdx = NumOfElements + TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
      }
      IpV4_Arp_VWriteValidEntries(IpV4CtrlIdx, arpConfigIdx, EntryListPtr, EntryListIdxPtr, readEntryDyntableLimitIdx); /* SBSW_TCPIP_FUNC_PARAM_PTR_PASSING */
      numOfDynamicElementsToRead = *EntryListIdxPtr - previousTableIdx;
    }
  }
  else
  {
    numOfDynamicElementsToRead = 0;
  }

  return numOfDynamicElementsToRead;
} /* IpV4_Arp_VReadDynTable() */

/**********************************************************************************************************************
 *  IpV4_Arp_VSendMessage
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_VSendMessage(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        RemNetAddr,
  IpBase_AddrInType                        LocNetAddr,
  IPV4_P2C(uint8)                          RemPhysAddr, /* PRQA S 3673 */ /* MD_IPV4_Rule8.3 */
  uint16                                   Operation)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType         retValue   = E_NOT_OK;
  uint8                  bufIdx;
  uint16                 bufLenByte = IPV4_ARP_PACKET_LEN_BYTE;
  IPV4_P2V(Eth_DataType) ethIfTxBufferPtr;


  /* ----- Implementation ----------------------------------------------- */

  /* #10 Obtain ethernet TX buffer. */
  if (TCPIP_LL_ProvideTxBuffer(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx),
      IPV4_ARP_FRAME_TYPE,
      TcpIp_GetFramePrioDefaultOfIpV4Ctrl(IpV4CtrlIdx), &bufIdx, &ethIfTxBufferPtr, &bufLenByte) == BUFREQ_OK)          /* SBSW_TCPIP_FUNC_PARAM_PTR_VARIABLES */
  {
    uint8* ethIfBufferPtr;

    IpBase_EthPhysAddrType         ethDstAddr;
    IpBase_EthPhysAddrType         srcMacAddr;
    IpBase_EthPhysAddrType         dstMacAddr;

    ethIfBufferPtr = (uint8*)&ethIfTxBufferPtr[0]; /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_CastToUInt8 */

    TCPIP_ASSERT(bufLenByte >= IPV4_ARP_PACKET_LEN_BYTE);
    if (bufLenByte >= IPV4_ARP_PACKET_LEN_BYTE)
    {
      /* #20 Build the ARP packet. */
      TCPIP_PUT_UINT16(ethIfBufferPtr, IPV4_ARP_HW_ADDR_TYPE_OFS, IPV4_ARP_HW_ADDR_TYPE_ETHERNET);                      /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT16(ethIfBufferPtr, IPV4_ARP_PR_ADDR_TYPE_OFS, IPV4_ARP_PROT_ADDR_TYPE_IPV4);                        /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr,  IPV4_ARP_HW_ADDR_SIZE_OFS, IPV4_ARP_HW_ADDR_SIZE_ETHERNET);                      /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr,  IPV4_ARP_PR_ADDR_SIZE_OFS, IPV4_ARP_PROT_ADDR_SIZE_IPV4);                        /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT16(ethIfBufferPtr, IPV4_ARP_OP_OFS, Operation);                                                     /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */

        /* store local MAC address. */
      TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), srcMacAddr);                                   /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */

      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_SRC_MC_ADDR_OFS,   srcMacAddr[0]);                                       /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 1u, srcMacAddr[1]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 2u, srcMacAddr[2]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 3u, srcMacAddr[3]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 4u, srcMacAddr[4]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_SRC_MC_ADDR_OFS + 5u, srcMacAddr[5]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */

      TCPIP_PUT_UINT32_RAW(ethIfBufferPtr, IPV4_ARP_SRC_IP_ADDR_OFS, LocNetAddr);                                       /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */

        /* store remote MAC address. */
      TcpIp_VCopyPhysAddr(dstMacAddr, RemPhysAddr);                                                                     /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */ /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */

      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_DST_MC_ADDR_OFS, dstMacAddr[0]);                                         /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_DST_MC_ADDR_OFS + 1u, dstMacAddr[1]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_DST_MC_ADDR_OFS + 2u, dstMacAddr[2]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_DST_MC_ADDR_OFS + 3u, dstMacAddr[3]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_DST_MC_ADDR_OFS + 4u, dstMacAddr[4]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT8(ethIfBufferPtr, IPV4_ARP_DST_MC_ADDR_OFS + 5u, dstMacAddr[5]);                                    /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */
      TCPIP_PUT_UINT32(ethIfBufferPtr, IPV4_ARP_DST_IP_ADDR_OFS, TCPIP_HTONL(RemNetAddr));                              /* SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer */

      /* #30 Set destination MAC address of the ethernet frame to broadcast if sender IP address is a link-local address. */
      if ((LocNetAddr == 0u) || ((LocNetAddr & IPV4_IP_LL_NET_ADDR_MASK) == IPV4_IP_LL_NET_ADDR_NET))
      {
        /* "All ARP packets (*replies* as well as requests) that contain a Link-
        * Local 'sender IP address' MUST be sent using link-layer broadcast
        * instead of link-layer unicast."
        * [RFC3927 2.5. Conflict Detection and Defense]
        */
        TcpIp_VCopyPhysAddr(ethDstAddr, IpV4_Arp_PhysBroadcastAddr);                                                    /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
      }
      else
      {
        TcpIp_VCopyPhysAddr(ethDstAddr, RemPhysAddr);                                                                   /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */ /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
      }

      /* #40 Transmit the message. */
      retValue = TCPIP_LL_Transmit( TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), bufIdx, IPV4_ARP_FRAME_TYPE, FALSE, IPV4_ARP_PACKET_LEN_BYTE, &ethDstAddr[0]); /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
    }
  }
  /* else: EthIf could not provide a buffer, function will return with "E_NOT_OK". */

  return retValue;
} /* IpV4_Arp_VSendMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Arp_VUpdateEntry
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VUpdateEntry(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IPV4_P2C(uint8)                          PhysAddr,  /* PRQA S 3673 */ /* MD_IPV4_Rule8.3 */
  TcpIp_SizeOfArpTableEntryType            ArpTableEntryIdx,
  boolean                                  EntryInTable)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_P2V(uint8) physAddrOfArpTableEntryPtr = &TcpIp_GetAddrPhysAddrOfArpTableEntry(ArpTableEntryIdx)->data[0];

 /* #10 Inform the upper layer if the entry is new or the physical address of an existing entry has changed. */
  if (   (EntryInTable == FALSE)
      || (!(IPV4_LL_ADDR_IS_EQUAL(physAddrOfArpTableEntryPtr, PhysAddr))))
  {
    /* new entry in table or existing entry is updated */
    TcpIp_VCopyPhysAddr(physAddrOfArpTableEntryPtr, PhysAddr);                                                          /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_COPY_LOCAL */
    /* Update state before notifying the upper layer. */
    TcpIp_SetStatusOfArpTableEntry(ArpTableEntryIdx, IPV4_ARP_ELSTATUS_VALID);                                          /* SBSW_TCPIP_FUNC_PARAM_CALLER */
    IpV4_Arp_VPhysAddrTableChgNotification(IpV4CtrlIdx, ArpTableEntryIdx, TRUE);
  }
  /* #20 Set status of ARP entry to VALID. */
  else
  {
    TcpIp_SetStatusOfArpTableEntry(ArpTableEntryIdx, IPV4_ARP_ELSTATUS_VALID);                                          /* SBSW_TCPIP_FUNC_PARAM_CALLER */
  }
} /* IpV4_Arp_VUpdateEntry() */

/**********************************************************************************************************************
 *  IpV4_Arp_VStoreDynamicEntry
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VStoreDynamicEntry(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        NetAddr,
  IPV4_P2C(uint8)                          PhysAddr,
  boolean                                  AddIfNotExisting)
{
   /* ----- Local Variables ---------------------------------------------- */
  boolean entryInTable            = FALSE;
  TcpIp_ArpTableEntryIterType arpTableEntryIdx;
  uint8_least oldestArpTableEntryIdx   = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
  uint8_least freeArpResTabEleIdx = IPV4_ARP_INVALID_RES_IDX;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over ARP table and locate position of existing entry, unused entry or least recently used entry. */
  for (arpTableEntryIdx = TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx < TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx);
       arpTableEntryIdx++)
  {
    if (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) != IPV4_ARP_ELSTATUS_INVALID)
    {
      /* entry is "valid" or "in progress" */
      if (TcpIp_GetNetAddrOfArpTableEntry(arpTableEntryIdx) == NetAddr)
      {
        /* matching entry found */
        entryInTable = TRUE;
        break;
      }

      if (IPV4_ARP_TIMESTAMP_IS_OLDER(TcpIp_GetTimeStampOfArpTableEntry(arpTableEntryIdx),
                                      TcpIp_GetTimeStampOfArpTableEntry(oldestArpTableEntryIdx)))
      {
        /* remember oldest entry */
        oldestArpTableEntryIdx = arpTableEntryIdx;
      }
    }
    else if (freeArpResTabEleIdx == IPV4_ARP_INVALID_RES_IDX)
    {
      /* store free entry index */
      freeArpResTabEleIdx = arpTableEntryIdx;
    }
    else
    {
      /* ignore further free entries */
    }
  }

  /* #20 Update existing entry or create new entry, if requested. */
  if ((entryInTable == TRUE) || (AddIfNotExisting == TRUE))
  {
    if (entryInTable == TRUE)
    {
      /* if entry has been found NetAddr already has the correct value */
      if (   (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_INPROGESS)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetStatusOfArpTableEntry(arpTableEntryIdx) == IPV4_ARP_ELSTATUS_PROBE) )
      {
        /* This is an answer for a pending request. */
        IpV4_Arp_NumPendEle--;
      }
    }
    else
    {
      /* #30 Check if an existing entry needs to be replaced by the new entry. */
      if (freeArpResTabEleIdx != IPV4_ARP_INVALID_RES_IDX)
      {
        /* use free entry */
        arpTableEntryIdx = freeArpResTabEleIdx;
      }
      else
      {
        /* #40 Notify upper layer about removal of entry. */
        arpTableEntryIdx = oldestArpTableEntryIdx;
        IpV4_Arp_VPhysAddrTableChgNotification(IpV4CtrlIdx, (TcpIp_SizeOfArpTableEntryType)arpTableEntryIdx, FALSE);
      }

      TcpIp_SetNetAddrOfArpTableEntry(arpTableEntryIdx, NetAddr);                                                       /* SBSW_TCPIP_STOREDYNAMIC_FUNC_CSL03_IDX */
    }

    TcpIp_SetTimeStampOfArpTableEntry(arpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                        /* SBSW_TCPIP_STOREDYNAMIC_FUNC_ENTRYINTABLE_CSL03_IDX */
    TcpIp_SetCreationTimeStampOfArpTableEntry(arpTableEntryIdx, IpV4_Arp_MainFuncCycle);                                /* SBSW_TCPIP_STOREDYNAMIC_FUNC_ENTRYINTABLE_CSL03_IDX */
    /* #50 Notify upper layer about new or changed entry, if necessary. */
    IpV4_Arp_VUpdateEntry(IpV4CtrlIdx, PhysAddr, (TcpIp_SizeOfArpTableEntryType)arpTableEntryIdx, entryInTable);        /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
  }
} /* IpV4_Arp_VStorePhysicalAddress() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Arp_VPhysAddrTableChgNotification
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VPhysAddrTableChgNotification(
  TcpIp_IpV4CtrlIterType        IpV4CtrlIdx,
  TcpIp_SizeOfArpTableEntryType ArpTableEntryIdx,
  boolean                       Valid)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SockAddrBaseType sockAddrInet; /* PRQA S 0759 */ /* MD_MSR_Union */

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl());
  TCPIP_ASSERT(ArpTableEntryIdx >= TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4CtrlIdx));
  TCPIP_ASSERT(ArpTableEntryIdx <  TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(IpV4CtrlIdx));

  sockAddrInet.SockAddrIn.sin_family = TCPIP_AF_INET;
  sockAddrInet.SockAddrIn.sin_addr   = TcpIp_GetNetAddrOfArpTableEntry(ArpTableEntryIdx);
  sockAddrInet.SockAddrIn.sin_port   = TCPIP_PORT_ANY;
  /* #10 Forward notification to TcpIp Core module.*/
  TcpIp_VPhysAddrTableChg(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), &sockAddrInet, &TcpIp_GetAddrPhysAddrOfArpTableEntry(ArpTableEntryIdx)->data[0], Valid); /* SBSW_TCPIP_TcpIp_FUNC_VPhysAddrTableChg_PARAM_PASSING */

} /* IpV4_Arp_VPhysAddrTableChgNotification() */

#if (TCPIP_SUPPORT_ARP_DISCARDED_ENTRY_HANDLING == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Arp_VPhysAddrTableChgDiscardedNotification
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VPhysAddrTableChgDiscardedNotification(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      DiscardedNetAddr)
{
   /* ----- Local Variables ---------------------------------------------- */
  TcpIp_PhysAddrConfigIterType physAddrConfigIdx;
  TcpIp_SockAddrBaseType   sockAddrInet;  /* PRQA S 0759 */ /* MD_MSR_Union */

  /* ----- Implementation ----------------------------------------------- */
  sockAddrInet.SockAddrIn.sin_family = TCPIP_AF_INET; /* IPv4 protocol */
  sockAddrInet.SockAddrIn.sin_addr   = DiscardedNetAddr;
  sockAddrInet.SockAddrIn.sin_port   = TCPIP_PORT_ANY;
  /* Iterate over the ....*/
  for (physAddrConfigIdx = 0; physAddrConfigIdx < TcpIp_GetSizeOfPhysAddrConfig(); physAddrConfigIdx++)
  {
    /* #10 Forward notification to TcpIp Core module. */
    TcpIp_PhysAddrTableChgDiscardedCbkType funcPtr = TcpIp_GetChgDiscardedFuncPtrOfPhysAddrConfig(physAddrConfigIdx);

    if (funcPtr != NULL_PTR)
    {
      funcPtr(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), (TCPIP_P2C(TcpIp_SockAddrType)) &sockAddrInet.TcpIpSockAddr); /* SBSW_TCPIP_ARP_FUNC_PTR_CALL */
      TCPIP_DUMMY_STATEMENT(sockAddrInet.SockAddrIn); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    }
  }

} /* IpV4_Arp_VPhysAddrTableChgDiscardedNotification() */
#endif

/**********************************************************************************************************************
 *  IpV4_Arp_VStaticTableLookup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_VStaticTableLookup(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        NetAddr,
  P2VAR(uint8, IPV4_APPL_DATA, IPV4_CONST) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over static ARP table and search for entry with matching IP address. */
  if (TcpIp_IsStaticArpTableUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    TcpIp_SizeOfArpTableEntryType staticArpTableIdx = TcpIp_GetStaticArpTableIdxOfIpV4Ctrl(IpV4CtrlIdx);
    TcpIp_StaticArpTableIterType staticArpEntryIdx;

    for (staticArpEntryIdx = TcpIp_GetStaticArpEntryStartIdxOfStaticArpTable(staticArpTableIdx);
         staticArpEntryIdx < TcpIp_GetStaticArpEntryEndIdxOfStaticArpTable(staticArpTableIdx);
         staticArpEntryIdx++)
    {
      if (NetAddr == TcpIp_GetIpAddrOfStaticArpEntry(staticArpEntryIdx))
      {
        if (PhysAddrPtr != NULL_PTR)
        {
          /* #20 Return configured physical/MAC address of matching entry. */
          TcpIp_VCopyPhysAddr(PhysAddrPtr, &TcpIp_GetAddrPhysAddrOfStaticArpEntry(staticArpEntryIdx)->data[0]);         /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_COPY */
        }
        retVal = E_OK;
        break;
      }
    }
  }
  /* No static ARP table entry exists for the supplied NetAddr. */
  return retVal;

} /* IpV4_Arp_VStaticTableLookup() */

/**********************************************************************************************************************
 *  IpV4_Arp_VDetectLinkLocalAddressConflict
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_VDetectLinkLocalAddressConflict(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  uint16                 ArpOperation,
  IpBase_AddrInType      LocIpAddr,
  IpBase_AddrInType      ArpSrcIpAddr,
  IpBase_AddrInType      ArpDstIpAddr,
  IPV4_P2C(uint8)        ArpSrcMacAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if link-local address assignment is configured on controller. */
  if (IpV4_Ip_VCfgGetAddrAssignmentPrio(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL) != 0u)
  {
    boolean                sentByOtherHost;
    IpBase_EthPhysAddrType ownPhysAddr;
    /* Get Controller's Physical(MAC) address. */
    TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), (ownPhysAddr));                                  /* SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
    /* Compare Source MAC address and Controller's MAC address. */
    sentByOtherHost = (boolean)(!(IPV4_LL_ADDR_IS_EQUAL(ownPhysAddr, ArpSrcMacAddrPtr)));  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

    /* #20 Notify link-local address configuration that sender IP address is used by other node, if required. */
    if (ArpSrcIpAddr != 0u)
    {
      /* "If during this period, from the beginning of the probing process
        *  until ANNOUNCE_WAIT seconds after the last probe packet is sent,
        *  the host receives any ARP packet (Request *or* Reply) where the packet's
        *  'sender IP address' is the address being probed for, then the
        *  host MUST treat this address as being in use by some other host,
        *  and MUST select a new pseudo-random address and repeat the process."
        *  [RFC3927 2.2.1. Probe details]
        */

      IpV4_Ip_LlAddrInUse(IpV4CtrlIdx, ArpSrcIpAddr);
    }
    /* #30 Notify link-local address configuration that target IP address is used by other node, if required. */
    else if ((ArpOperation == IPV4_ARP_OP_REQUEST) && (sentByOtherHost == TRUE))
    {
      /* "In addition, if during this period the host receives any ARP Probe
        *  where the packet's 'target IP address' is the address being probed for,
        *  and the packet's 'sender hardware address' is not the hardware address
        *  of the interface the host is attempting to configure, then the host MUST
        *  similarly treat this as an address conflict and select a new address as above."
        */

      IpV4_Ip_LlAddrInUse(IpV4CtrlIdx, ArpDstIpAddr);
    }
    else
    {
      /* nothing to do */
    }

    /* #40 Notify link-local address configuration if a conflict was detected. */
    if((LocIpAddr != 0u) && (ArpSrcIpAddr == LocIpAddr) && (sentByOtherHost == TRUE))
    {
      /* "At any time, if a host receives an ARP packet (request *or* reply) on
        *  an interface where the 'sender IP address' is the IP address the host
        *  has configured for that interface, but the 'sender hardware address'
        *  does not match the hardware address of that interface, then this is a
        *  conflicting ARP packet, indicating an address conflict."
        *  [RFC3927 2.5. Conflict Detection and Defense]
        */

      /* -> defend local address or restart address configuration */
      IpV4_Ip_AddrConflictInd(TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(IpV4CtrlIdx));

      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* IpV4_Arp_VDetectLinkLocalAddressConflict() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV4_Arp_VUpdateTable
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Arp_VUpdateTable(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  IpBase_AddrInType                        ArpSrcIpAddr,
  IPV4_P2C(uint8)                          ArpSrcMacAddr,
  boolean                                  AddIfNotExisting)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if dynamic ARP table is configured for this controller. */
  if (TcpIp_IsArpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
# if defined(TCPIP_ASSERT_HANDLER)                                                                                      /* COV_TCPIP_CANOE_DEBUG */
    TcpIp_SizeOfArpConfigType arpConfigIdx = TcpIp_GetArpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
    TCPIP_ASSERT(TcpIp_GetTableSizeOfArpConfig(arpConfigIdx) > 0u);
# endif
    /* #20 Verify that entry does not exist in static ARP table, if configured. */
    if (IpV4_Arp_VStaticTableLookup(IpV4CtrlIdx, ArpSrcIpAddr, NULL_PTR) != E_OK)                                       /* SBSW_TCPIP_NULL_PTR_ALLOWED */
    {
      /* #30 Store entry in the dynamic ARP table. */
      IpV4_Arp_VStoreDynamicEntry(IpV4CtrlIdx, ArpSrcIpAddr, ArpSrcMacAddr, AddIfNotExisting);                          /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
    }
  }
}  /* IpV4_Arp_VUpdateTable() */

/**********************************************************************************************************************
 *  IpV4_Arp_VRespondToPacket
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/

TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VRespondToPacket(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  uint16                                   ArpOperation,
  IpBase_AddrInType                        ArpSrcIpAddr,
  IpBase_AddrInType                        ArpDstIpAddr,
  IPV4_P2C(uint8)                          ArpSrcMacAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_AddrInType locIpAddr = TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if ARP packet is an ARP Request. */
  if (ArpOperation == IPV4_ARP_OP_REQUEST)
  {
    /* #20 Check if ARP Request is addressed to this node. */
    if ((locIpAddr != 0u) && (ArpDstIpAddr == locIpAddr))
    {
      /* #30 Send ARP Reply. */
      (void)IpV4_Arp_VSendMessage(IpV4CtrlIdx, ArpSrcIpAddr, locIpAddr, ArpSrcMacAddr, IPV4_ARP_OP_REPLY);              /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
    }
  }
  /* else: No action necessary. */
} /* IpV4_Arp_VProccessArpRequest() */
/**********************************************************************************************************************
 *  IpV4_Arp_VHandlePacket
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Arp_VHandlePacket(
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  uint16                                   ArpOperation,
  IpBase_AddrInType                        ArpSrcIpAddr,
  IpBase_AddrInType                        ArpDstIpAddr,
  IPV4_P2C(uint8)                          ArpSrcMacAddr)
{
   /* ----- Local Variables ---------------------------------------------- */
  /* get IP address of the controller */
  IpBase_AddrInType locIpAddr = TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Forward relevant information from ARP packet to link-local address configuration, if configured. (in order to detect IP address conflict) */
  if (IpV4_Arp_VDetectLinkLocalAddressConflict(IpV4CtrlIdx, ArpOperation, locIpAddr, ArpSrcIpAddr, ArpDstIpAddr, ArpSrcMacAddr) == E_OK)  /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
  {
    /* #20 Check if source IP address of ARP packet is valid. */
    if (IPV4_ADDR_IS_MULTICAST(ArpSrcIpAddr) || IPV4_ADDR_IS_BROADCAST(IpV4CtrlIdx, ArpSrcIpAddr))
    {
      /* Ignore invalid source IP address. */
    }
    /* #30 Check if source MAC address of ARP packet is valid. */
    else if (!IPV4_LL_ADDR_IS_VALID(ArpSrcMacAddr))
    {
      /* Ignore invalid source MAC address. */
    }
    else
    {
      /* #40 Update dynamic ARP table, if required. */
      if (ArpSrcIpAddr != 0u)
      {
        IpV4_Arp_VUpdateTable(IpV4CtrlIdx, ArpSrcIpAddr, ArpSrcMacAddr, (boolean)(ArpDstIpAddr == locIpAddr));  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */          /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
      }
      else
      {
        /* this is an ARP probe (from an IP link local address configuration) or a packet with an invalid source IP address.
         -> do not store the physical address */
      }
      /* #50 Send Arp Reply.*/
      IpV4_Arp_VRespondToPacket(IpV4CtrlIdx, ArpOperation, ArpSrcIpAddr, ArpDstIpAddr, ArpSrcMacAddr);                  /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
    }
  }
} /* IpV4_Arp_VHandlePacket() */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/*
   module specific MISRA deviations:

*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_STATIC_BRODCAST_PHYSADDR
    \DESCRIPTION        The 6 bytes of static const array is passed to the function as argument (a physical address).
    \COUNTERMEASURE \N  This array is defined as a static and also initialized to ensure that it points to a valid  memory location.

  \ID SBSW_TCPIP_NULL_PTR_ALLOWED
    \DESCRIPTION        A pointer that may be NULL_PTR is passed to a subroutine.
    \COUNTERMEASURE \N  The callee explicitly allows the value NULL_PTR and handles this case correctly.

  \ID SBSW_TCPIP_FUNC_PARAM_PTR_PASSING
    \DESCRIPTION        Pointer is passed as function argument.
                        Pointer is passed as a function argument and is updated considering a valid pointer.
                        The validity of the EntryListPtr is checked against NULL_PTR by the caller function and handled properly
    \COUNTERMEASURE \N  The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_PARAM_PTR_VARIABLES
    \DESCRIPTION        Pointer and variables are passed to this function as a function argument.
                        Local variables and pointer are created inside the local function to make sure that they are valid.
    \COUNTERMEASURE \N  The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_PARAM_PTR_CALLER
    \DESCRIPTION        Pointer is passed as function argument without validity check.
                        Pointer is passed as a function argument and is updated considering a valid pointer.
    \COUNTERMEASURE \N  The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE
    \DESCRIPTION        Pointer is Updated inside the local function.
                        A function argument Pointer is updated considering a valid pointer.
    \COUNTERMEASURE \N  The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_UPDATE_VARIABLE
    \DESCRIPTION        Variable is passed by reference as a function argument in order to update it.
    \COUNTERMEASURE \N  The local Variable is created inside the local function and passed as a function argument to the callee function.

  \ID SBSW_TCPIP_WRITE_UINT_TCPIP_LL_ProvideTxBuffer
    \DESCRIPTION        The function writes 1/2/4 bytes beginning at the position in the buffer provided by the caller.
                        TcpIp_WriteUInt8(): 1
                        TcpIp_WriteUInt16(): 2
                        TcpIp_WriteUInt32(): 4
                        A pointer ethIfTxBufferPtr is created inside the caller function.This pointer is passed to TCPIP_LL_ProvideTxBuffer function.
                        If TCPIP_LL_ProvideTxBuffer function returns BUFREQ_OK then only ethIfTxBufferPtr is updated.
                        Buffer should be at least IPV4_ARP_PACKET_LEN_BYTE bytes long. The offsets(ethIfTxBufferPos) which are used to write into this buffere musn't exceed this length.
                        bufLenByte and ethIfTxBufferPtr are related to each other.
    \COUNTERMEASURE \N  The caller ensures that there are 1/2/4 bytes available at &ethIfTxBufferPtr[ethIfTxBufferPos].

  \ID SBSW_TCPIP_CSL01_IDX_CALLEE
    \DESCRIPTION        The function writes to the CSL array referenced by the index parameter.
    \COUNTERMEASURE \N  The Callee function itself ensures that the index is within the valid range by using the TcpIp_GetSizeOf...() function.
                        Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_FUNC_PARAM_PTR_PHYSADDR_WRITE_CALLER
    \DESCRIPTION        Pointer is passed to this local function as a function argument and is updated considering a valid pointer.
                        Exactly 6 bytes are written into the memory location referenced by pointer parameter
                        The validity of the pointer is ensured by the caller.
    \COUNTERMEASURE \N  Caller must make sure that there are at least 6 bytes available at the memory location referenced by this pointer parameter.

  \ID SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER
    \DESCRIPTION        Pointer is passed to this function as a function argument for further usage.
                        CONSTRAINT : [Must contains 6 bytes of memory]
                        The validity of the pointer is ensured by the caller.
    \COUNTERMEASURE \N  Caller must make sure that there are at least 6 bytes available at the memory location referenced by this pointer parameter.

  \ID SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_COPY_LOCAL
    \DESCRIPTION        Pointer is passed to this function as a function argument for further usage.
                        The first parameter physAddrOfArpTableEntryPtr is referenced to an array accessed through an Index using CSL macro.
                        This parameter must point to the 6 bytes of memory location. CONSTRAINT: [Must contains 6 bytes of memory]
                        This index is a function argument of a local function and validity of this index is ensured by the caller.
                        The second parameter PhysAddr is valid as stated in SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER.
    \COUNTERMEASURE \N  Validity of the pointer parameters are ensured by caller.

  \ID SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_COPY
    \DESCRIPTION        Pointer is passed to this function as a function argument for further usage.
                        The first parameter PhysAddrPtr is valid as stated in SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER.
                        This parameter must point to the 6 bytes of memory location. CONSTRAINT : [Must contains 6 bytes of memory]
                        The pointer is checked against the NULL_PTR before passing it to as a function argument.
                        The second parameter is a array accessed through an Index using CSL macro.
                        This index is calculated as stated in SBSW_TCPIP_CSL03_IDX_BASED_ON_CALLER.
    \COUNTERMEASURE \R  Pointer parameter is checked against NULL_PTR within local function and handled properly.

  \ID SBSW_TCPIP_TcpIp_FUNC_VPhysAddrTableChg_PARAM_PASSING
    \DESCRIPTION        Pointer is passed to this function as a function argument for further usage.
                        The first parameter is a sockAddrIne which is a local variable created inside the local function.
                        The second parameter is a array accessed through an Index using CSL macro.
                        This index is calculated as stated in SBSW_TCPIP_CSL03_IDX_BASED_ON_CALLER.
    \COUNTERMEASURE \N  Validity of the pointer parameters are ensured by caller.

  \ID SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR
    \DESCRIPTION        Exactly 6 bytes are written into the array or memory location which is referenced by a pointer.
                        Either Array index is checked inside the function, against the length of 6 bytes (IPBASE_ETH_PHYS_ADDR_LEN_BYTE)
                        or Array is of type IpBase_EthPhysAddrType, which exactly contains 6 bytes.
                        and witten only at the position of [0-5].Thus all write accesses to variables of type
                        IpBase_EthPhysAddrType are valid as soon as they do not exceed the index
                        IPBASE_ETH_PHYS_ADDR_LEN_BYTE - 1.
    \COUNTERMEASURE \N  It is ensured that there are at least 6 bytes available at the referenced memory location
                        or Array is of 6 byte size.

  \ID SBSW_TCPIP_FUNC_PARAM_CALLER_WRITE_ACCESS_ARRAY_PHYSADDR
    \DESCRIPTION        Index parameter is passed as function argument and is used to write into the memory location using CSL macros.
                        The validity of the Index parameter is ensured by the caller.
    \COUNTERMEASURE \N  A valid memory location, accessed through index, is ensured as stated in
                        SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR.

  \ID SBSW_TCPIP_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR
    \DESCRIPTION        Array is passed as a parameter to the function.
                        Local Variable of type IpBase_EthPhysAddrType is created inside the caller function.
                        The validity of the parameter is ensured by the caller.
    \COUNTERMEASURE \N  Validity is ensured, as stated in SBSW_TCPIP_WRITE_ACCESS_ARRAY_PHYSADDR.

  \ID SBSW_TCPIP_FUNC_PARAM_CALLER
    \DESCRIPTION        Index parameter is passed as function argument.
                        Index is passed as a function argument and is used to write into the memory location using CSL macros.
    \COUNTERMEASURE \N  The validity of the Index parameter is ensured by the caller.

  \ID SBSW_TCPIP_LRUINDEX_CALLER
    \DESCRIPTION        Index parameter is passed as function argument.
                        Index is passed as a function argument and is used to write into the memory location using CSL macros.
                        LruIndex is checked inside the function IpV4_Arp_VCheckArpEntry(), which is called before using it.
                        So the function always return the valid Last recently used Arp Entry Index
    \COUNTERMEASURE \N  The validity of the Index parameter is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_PARAM_SOCK
    \DESCRIPTION        Socket Index parameter is passed as function argument.
                        Socket Index is passed as a function argument and is used to write into the memory location using CSL macros.
                        Index is used only if it is not a IPV4_INV_SOCK_IDX and must be less than TcpIp_GetSizeOfIpV4SocketDyn().
    \COUNTERMEASURE \N  The validity of the Index parameter is ensured by the caller.

  \ID SBSW_TCPIP_ARP_CSL03_IDX_BASED_ON_CALLER
    \DESCRIPTION        A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                        The first index for the lookup(s) is provided and checked by the caller of the function to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                        Validity of the index value(s) of the modelled indirection(s) [is|are] checked as using the following functions:
                        1.TcpIp_Is...() function(s) - if 0:1 Indirection is used.
                        2.Iteration over TcpIp_Get..StartIdxOf..(..) and  TcpIp_Get..EndIdxOf..(..) - if 0:N Indirection is used.
                        The associated TcpIp_Is...() function(s) [is|are] used as applicable to check the validity of the index value(s) of the modelled indirection(s).
                        Thus this is a qualified use-case CSL03 of ComStackLib.
                        This scenario is also applicable in case the determined index value is used as parameter of a function-call, because the index has a valid value.
    \COUNTERMEASURE \N  Qualified use-case CSL03 of ComStackLib.

  \ID SBSW_TCPIP_ARP_FUNC_PTR_CALL
    \DESCRIPTION        Local Function Pointer is created inside the local function.
                        Index used to read the function pointer is based on CSL01.
                        Pointer parameter is checked against NULL_PTR within local function and handled properly.
    \COUNTERMEASURE \R  Validy of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr
    \DESCRIPTION        Pointer is passed to this function as a function argument.
                        Pointer is of type TcpIp_ArpCacheEntryType(Structure) and checked against the NULL_PTR within the local function.
                        Memory location, accessed through this pointer is controlled by the index.This index is incremented inside for loop and the stop condition/conroll condition of the loop is staticArpEntryLimitIdx.
                        staticArpEntryLimitIdx indirectly comes from the caller.
                        staticArpEntryLimitIdx is NumOfElements incase caller wants to read less entries than existed in table.If caller wants to read more entries than actually existed entries than staticArpEntryLimitIdx will be set as the maximum available entries to be read.
                        maximum available entries are calculated using  TcpIp_Get..StartIdxOf..(..) and  TcpIp_Get..EndIdxOf..(..) CSL macros.
                        In all cases the index is properly controlled and checked before using it to access the memory location pointed by the pointer EntryListPtr.Thats why it is valid.
                        One element of the struct TcpIp_ArpCacheEntryType is Phyaddr.The local function takes care that exactly 6 bytes [0..5] are written into this element of struct.
    \COUNTERMEASURE \R  Pointer parameter is checked against NULL_PTR within this local function and handled properly.

  \ID SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr_CALLER
    \DESCRIPTION        Pointer is passed to this function as a function argument.
                        Pointer is of type TcpIp_ArpCacheEntryType(Structure) and checked against the NULL_PTR within the caller function and handled properly.
                        Memory location, accesses through this pointer is controlled by the index, which is also a
                        function argument.Validity of this parameter index is verified by the caller.
                        The index is incremented inside the for loop. The stop condition of this loop is limitIdxToReadEntries, which is indirectly the function argument and verified by the caller.
                        That's why the index to access the memory location referenced by EntryListPtr is valid.
                        One element of the struct TcpIp_ArpCacheEntryType is Phyaddr.The local function takes care that exactly 6 bytes [0..5] are written into this element of struct.
    \COUNTERMEASURE \N  Validity of the pointer parameter is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_CALL_PARAM_PTR_EntryListPtr_PHYSADDR_COPY
    \DESCRIPTION        Pointer is passed to this function as a function argument for further usage.
                        The first parameter PhysAddr  and its validity is ensured by the caller.
                        This parameter must point to the 6 bytes of memory location. CONSTRAINT : [Must contains 6 bytes of memory]
                        The second parameter is local pionter which is valid as stated in SBSW_TCPIP_FUNC_PARAM_PTR_EntryListPtr_CALLER.
    \COUNTERMEASURE \N  Validity of the pointer parameters are ensured by caller.

  \ID SBSW_TCPIP_STOREDYNAMIC_FUNC_CSL03_IDX
    \DESCRIPTION        A CSL modelled RAM array is written using an index (arpTableEntryIdx) that is determind as described below:
                        freeArpResTabEleIdx is set to IPV4_ARP_INVALID_RES_IDX.
                        oldestArpTableEntryIdx is set to the start index of ARP table using TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(IpV4Ctrl) macro.
                        1.If the entry of the dynamic table is invalid (IPV4_ARP_ELSTATUS_INVALID)
                          a. freeArpResTabEleIdx will be set to that invalid arpTableEntryIdx that is determined according to Use case CSL03.
                        2.If the entry is Valid but not found maching NetAddr that means entryInTable is FALSE then
                          b. oldestArpTableEntryIdx is set to that arpTableEntryIdx that is determined according to Use case CSL03.
                        If entryInTable is FALSE arpTableEntryIdx can only be set to freeArpResTabEleIdx or to oldestArpTableEntryIdx, before using that index to writting into the RAM array.
                        As explained in 1. and 2. in both cases assigned index was derived according to CSL03. It is always a valid index.
    \COUNTERMEASURE \N  Qualified use-case CSL03 of ComStackLib. Caller must make sure that this function is called only when ARP config exist for desired controller.

  \ID SBSW_TCPIP_STOREDYNAMIC_FUNC_ENTRYINTABLE_CSL03_IDX
    \DESCRIPTION        A CSL modelled RAM array is written using an index (arpTableEntryIdx) that is determind using one (or more) modelled indirections according to CSL03
                        1.If the entry is Valid and matching NetAddr is found that means entryInTable is TRUE then
                          arpTableEntryIdx will be used to write into the RAM array.This index is valid because it is derived using valid use case CSL03.
                        2 In other cases as explained in SBSW_TCPIP_STOREDYNAMIC_FUNC_CSL03_IDX, arpTableEntryIdx will be valid before using it to write into the RAM array.
    \COUNTERMEASURE \N  Qualified use-case CSL03 of ComStackLib. Caller must make sure that this function is called only when ARP config exist for desired controller.

   SBSW_JUSTIFICATION_END */


#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: IpV4_Arp.c
 *********************************************************************************************************************/
