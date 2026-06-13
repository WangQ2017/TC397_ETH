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
 *         \file  TcpIp_Arp_Cbk.h
 *        \brief  Implementation of Address Resolution Protocol (ARP) for IPv4 - Callback Header
 *
 *      \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

#if !defined (IPV4_ARP_CBK_H)
# define IPV4_ARP_CBK_H

#include "TcpIp_Cfg.h"
#include "TcpIp_Lcfg.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "ComStack_Types.h"
#include "Eth_GeneralTypes.h"


#include "TcpIp_IpV4.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *  IpV4_Arp_RxIndication
 *********************************************************************************************************************/
/*! \brief        Indicates a received ARP message.
 *  \details      Called by the lower layer (EthIf) when a message arrives.
 *  \param[in]    EthIfCtrlIdx          EthIf controller index 
 *                                      CONSTRAINT: [0  TcpIp_GetSizeOfEthIfCtrl() - 1]
 *  \param[in]    FrameType             Ethernet Frame type (should be ARP 0x0806)
 *  \param[in]    IsBroadcast           TRUE if received packet was sent as broadcast
 *  \param[in]    PhysAddrPtr           physical address of the sender
 *                                      CONSTRAINT: [Must point to the 6 bytes of memory location.]
 *  \param[in]    DataPtr               pointer to the received data
 *  \param[in]    LenByte               length of received data in bytes
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV4_CODE) IpV4_Arp_RxIndication(
  TcpIp_SizeOfEthIfCtrlType                EthIfCtrlIdx,
  Eth_FrameType                            FrameType,
  boolean                                  IsBroadcast,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) PhysAddrPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   LenByte);

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
#endif  /* IPV4_ARP_CBK_H */
/**********************************************************************************************************************
 *  END OF FILE: IPV4_Arp_Cbk.h
 *********************************************************************************************************************/
