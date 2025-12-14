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
 *         \file  TcpIp_Arp.h
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

#if !defined (IPV4_ARP_H)
# define IPV4_ARP_H

#include "TcpIp_Cfg.h"
#include "TcpIp_Lcfg.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */

/*
|0              |8              |16             |24             |
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          HwAddrType           |         ProtAddrType          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   HwAddrSize  |  ProtAddrSize |           Operation           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                          SrcMacAddr                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          SrcMacAddr           |       Source IP Address       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|       Source IP Address       |          DestMacAddr          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                          DestMacAddr                          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                     Destination Address                       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
ARP packet format
*/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_IpV4.h"
#include "TcpIp.h"


#include "ComStack_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ARP ApiIds */
#define IPV4_ARP_API_ID_RX_INDICATION           0x40u
#define IPV4_ARP_API_ID_TX_CONFIRMATION         0x41u

#define IPV4_ARP_API_ID_INIT                    0x50u
#define IPV4_ARP_API_ID_RESET                   0x51u
#define IPV4_ARP_API_ID_MAIN_FUNCTION           0x52u
#define IPV4_ARP_API_ID_GET_PHYS_ADDR           0x53u
#define IPV4_ARP_API_ID_SEND_ARP_REQUEST        0x54u
#define IPV4_ARP_API_ID_MAP_IP_TO_PHYS_MC_ADDR  0x55u
#define IPV4_ARP_API_ID_SEND_ARP_PROBE          0x56u
#define IPV4_ARP_API_ID_SEND_ARP_ANNOUNCEMENT   0x57u

#define IPV4_ARP_API_ID_V_INTERNAL_FUNCTION     0xFFu

/* ARP state */
#define IPV4_ARP_STATE_UNINIT                   0x00u
#define IPV4_ARP_STATE_INITMEMORY               0x01u
#define IPV4_ARP_STATE_INIT                     0x02u

#define IPV4_ARP_HW_ADDR_SIZE_ETHERNET                6u
#define IPV4_ARP_PROT_ADDR_SIZE_IPV4                  4u
#define IPV4_ARP_PACKET_LEN_BYTE                     28u

/* status of ARP table elements */
#define IPV4_ARP_ELSTATUS_INVALID                     0u
#define IPV4_ARP_ELSTATUS_VALID                       1u
#define IPV4_ARP_ELSTATUS_INPROGESS                   2u
#define IPV4_ARP_ELSTATUS_PROBE                       3u

#define IPV4_ARP_MAX_TIME_DIFF              (0x7FFFFFFFu)

#define IPV4_ARP_FRAME_TYPE                      0x0806u


/* BIGENDIAN */
#define IPV4_ARP_HW_ADDR_TYPE_ETHERNET           0x0001u
#define IPV4_ARP_PROT_ADDR_TYPE_IPV4             0x0800u
#define IPV4_ARP_OP_REQUEST                      0x0001u
#define IPV4_ARP_OP_REPLY                        0x0002u


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8 IpV4_Arp_StateType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */
/**********************************************************************************************************************
 *  IpV4_Arp_Init
 *********************************************************************************************************************/
/*! \brief        Initializes the ARP component.
 *  \details      -
 *  \pre          Module is uninitialized
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_Init(void);

/**********************************************************************************************************************
 *  IpV4_Arp_MapIpToPhysMulticastAddr
 *********************************************************************************************************************/
/*! \brief        Maps an IP multicast address to a physical multicast address.
 *  \details      -
 *  \param[in]    NetMcAddr             network layer multicast address (network byte order)
 *                                      CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[out]   PhysMcAddr            physical layer multicast address (network byte order)
 *                                      CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_MapIpToPhysMulticastAddr(
  IpBase_AddrInType NetMcAddr,
  IPV4_P2V(uint8)   PhysMcAddr);

/**********************************************************************************************************************
 *  IpV4_Arp_GetPhysicalAddress
 *********************************************************************************************************************/
/*! \brief        Get physical address for a given network address.
 *  \details      The cache table access is optimized for requesting the same address many times for the same socket.
 *
 *  \param[in]    IpV4CtrlIdx             Index of the IP controller/instance.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    SocketIdx               Socket index
 *  \param[in]    NetAddr                 Network address (network byte order)
 *  \param[out]   PhysAddrPtr             Pointer for physical address (network byte order)
                                          CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]    InitRes                 Specifies if the address resolution shall be initiated (TRUE) or not (FALSE) in
 *                                        case the physical address related to the specified IP address is currently
 *                                        unknown.
 *  \return       TCP_OK                  Address could be resolved
 *                TCP_E_NOT_OK            Address could not be resolved, resolution has NOT been triggered, even in case
 *                                        the parameter InitRes has indicated the callers wish to do so,
 *                TCPIP_E_PHYS_ADDR_MISS  Address could not be resolved, resolution has been triggered successfully,
 *                                        depending on the value of the parameter InitRes.
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        CREQ-115906
 *********************************************************************************************************************/
FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Arp_GetPhysicalAddress(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  TcpIp_SizeOfIpV4SocketDynType           SocketIdx,
  IpBase_AddrInType                       NetAddr,
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) PhysAddrPtr,
  boolean                                 InitRes);

/**********************************************************************************************************************
 *  IpV4_Arp_SendArpRequest
 *********************************************************************************************************************/
/*! \brief        Send ARP request message
 *  \details      -
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance.
                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    NetAddr               Destination network address.
 *  \return       E_OK                  success (Request sent successfully.)
 *  \return       E_NOT_OK              error
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendArpRequest(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      NetAddr );

/**********************************************************************************************************************
 *  IpV4_Arp_SendArpProbe
 *********************************************************************************************************************/
/*! \brief        Sends an ARP Probe packet as specified in [RFC3927 1.2. Terminology]
 *  \details      -
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    IpAddrToProbe         network address to be probed
 *  \return       E_OK                  success (Arp Prob message sent successfully.)
 *  \return       E_NOT_OK              error
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendArpProbe(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      IpAddrToProbe);

/**********************************************************************************************************************
 *  IpV4_Arp_SendArpAnnouncement
 *********************************************************************************************************************/
/*! \brief        Sends an ARP Announcement packet as specified in [RFC3927 1.2. Terminology]
 *  \details      -
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance.
                                        CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    IpAddrToAnnounce      Network address to be announced.
 *  \return       E_OK                  success
 *  \return       E_NOT_OK              error
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendArpAnnouncement(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      IpAddrToAnnounce);

/**********************************************************************************************************************
 *  IpV4_Arp_SendGratuitousArpReq
 *********************************************************************************************************************/
/*! \brief        Sends an gratuitous ARP request packet as specified in [RFC2002 4.6. second indentation]
 *  \details      This function sends an ARP REQUEST packet with these properties:
 *                1. THE NODES [NEW, I.E. CURRENT] IP ADDRESS
 *                2. THE NODES [NEW, I.E. CURRENT] MAC ADDRESS
 *                3. The packets field TARGET HW ADDRESS is handled like at any other ARP request implemented by the ARP subcomponent:
 *                4. The request packet is finally sent using IpV4_Arp_VSendMessage() with parameter IPV4_ARP_OP_REQUEST
 *                5. The packet is sent only in case the affected interface has an assigned IP address
 *                The function returns E_NOT_OK in case one of the conditions 4. or 5. are not fulfilled or a step to check them can not be conducted.
 *  \param[in]    LocalAddrV4Idx  Index of an IPv4 address.
 *                                Constraint: [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \return       E_OK            in case all parameters were valid, conditions were 'OK' and
 *                                the gratuitous ARP message was successfully handed to the lower layer.
 *  \return       E_NOT_OK        Otherwise.
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendGratuitousArpReq(TcpIp_LocalAddrV4IterType LocalAddrV4Idx);

/**********************************************************************************************************************
*  IpV4_Arp_SendGratuitousArpReply
**********************************************************************************************************************/
/*! \brief       Sends gratuitous ARP reply packet as specified in [RFC2002 4.6. second indentation]
*  \details      This function sends an ARP REPLY packet with these properties:
*                1. THE NODES [NEW, I.E. CURRENT] IP ADDRESS
*                2. THE NODES [NEW, I.E. CURRENT] MAC ADDRESS
*                3. The packets field TARGET HW ADDRESS is handled like at any other ARP reply implemented by the ARP subcomponent:
*                4. The reply packet is finally sent using IpV4_Arp_VSendMessage() with parameter IPV4_ARP_OP_REPLY
*                5. The packet is sent only in case the affected interface has an assigned IP address
*                The function returns E_NOT_OK in case one of the conditions 4. or 5. are not fulfilled or a step to check them can not be conducted.
*  \param[in]    IpV4CtrlIdx     Index of an IPv4 instance.
*                                Constraint: [0..TcpIp_GetSizeOfLocalAddrV4()-1]
*  \return       E_OK            in case all parameters were valid, conditions were 'OK' and
*                                the gratuitous ARP message was successfully handed to the lower layer.
*  \return       E_NOT_OK        Otherwise.
*  \pre          PRE_TCPIP_ARP_INIT
*  \context      TASK
*  \reentrant    FALSE
*  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_SendGratuitousArpReply(TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
*  IpV4_Arp_SendGratuitousArpOnStartup
**********************************************************************************************************************/
/*! \brief       Sends gratuitous ARP reply packet as specified in [RFC2002 4.6. second indentation].
*  \details      This function sends an ARP REPLY packet only,
*                if configuration parameter [TcpIpArpNumGratuitousARPonStartup is set to > 0]. This is an Autosar feature.
*  \param[in]    IpV4CtrlIdx     Index of an IPv4 instance.
*                                Constraint: [0..TcpIp_GetSizeOfLocalAddrV4()-1]
*                                Constraint: [Controller is Online Active]
*                                Constraint: [Controller has dynamic Arp enabled]
*  \pre          PRE_TCPIP_ARP_INIT
*  \context      TASK
*  \reentrant    FALSE
*  \synchronous  TRUE
*  \note         This function is called every IPV4_MAIN_FCT_PERIOD_MSEC ms
**********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_SendGratuitousArpOnStartup(TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Arp_MainFunction
 *********************************************************************************************************************/
/*! \brief        Main function
 *  \details      This function executes the main function every second.
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \note         This function is called every IPV4_MAIN_FCT_PERIOD_MSEC ms
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_MainFunction(void);

/**********************************************************************************************************************
 *  IpV4_Arp_GetCacheEntries
 *********************************************************************************************************************/
/*! \brief          Copies physical address cache entries of the IPV4 instance into the User defined buffer.
 *  \details        This function first copies the static entries and then dynamic entries.
 *                  The given IPv4 instance has to be active on the defined EthIf controller.
 *  \param[in]      EthIfCtrlIdx            EthIf controller Index to identify the related ARP table.
 *                                          CONSTRAINT: [0    TcpIp_GetSizeOfEthIfCtrl() - 1]
 *  \param[in,out]  NumberOfElementsPtr     Maximum number of entries that can be stored.
 *  \param[out]     EntryListPtr            Pointer to the memory where the list of cache entries shall be stored.
 *                                          CONSTRAINT: May by NULL_PTR if *NumberOfElementsPtr == 0.
 *  \return         E_OK                    Physical address cache reading was successful.
 *                  E_NOT_OK                Unsuccessful (No IPV4 instance is active on this controller).
 *  \pre            PRE_TCPIP_ARP_INIT
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          CREQ-111995
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Arp_GetCacheEntries(
  TcpIp_SizeOfEthIfCtrlType         EthIfCtrlIdx,
  IPV4_P2V(uint32)                  NumberOfElementsPtr,
  IPV4_P2V(TcpIp_ArpCacheEntryType) EntryListPtr);

/**********************************************************************************************************************
 *  IpV4_Arp_Reset
 *********************************************************************************************************************/
/*! \brief        Reset elements in Arp_ResTable for given controller index
 *  \details      -
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_Reset(TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Arp_ClearCache
 *********************************************************************************************************************/
/*! \brief        IpV4_Arp_ClearCache clears the address resolution cache
 *  \details      -
 *  \param[in]    LocalAddrV4Idx      Index of an IPv4 address implicitly specifying the IPv4 controller that shall
 *                                    be cleared
 *  \pre          PRE_TCPIP_ARP_INIT
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        CREQ-126879
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Arp_ClearCache(TcpIp_LocalAddrV4IterType LocalAddrV4Idx);

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
#endif  /* IPV4_ARP_H */

/* \PRE PRE_TCPIP_ARP_INIT
        IpV4_Arp must have been initialized by a call to IpV4_Arp_Init(<valid configuration pointer>). */

/**********************************************************************************************************************
 *  END OF FILE: IpV4_Arp.h
 *********************************************************************************************************************/
