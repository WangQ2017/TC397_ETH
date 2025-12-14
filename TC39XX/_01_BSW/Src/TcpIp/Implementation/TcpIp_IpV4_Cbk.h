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
 *         \file  TcpIp_IpV4_Cbk.h
 *        \brief  Implementation of Internet Protocol version 4 (IPv4) - Callback Header
 *
 *      \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

#if !defined (IPV4_IP_CBK_H)
# define IPV4_IP_CBK_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "TcpIp_Types.h"
#include "EthIf.h"



/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"
/**********************************************************************************************************************
 *  IpV4_Ip_RxIndication
 *********************************************************************************************************************/
/*! \brief          Indication of a received IP message.
 *  \details        Called by the lower layer (EthIf) when a message arrives.
 *  \param[in]      EthIfCtrlIdx  EthIf controller index
 *  \param[in]      FrameType     Eth frame type (currently unused)
 *  \param[in]      IsBroadcast   Eth broadcast flag (currently unused)
 *  \param[in]      PhysAddrPtr   Pointer to the physical (source) address of the received packet.
 *  \param[in]      DataPtr       Pointer to the received data
 *  \param[in]      LenByte       Length of received data in bytes
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV4_CODE) IpV4_Ip_RxIndication(
  uint8                                     EthIfCtrlIdx,
  Eth_FrameType                             FrameType,
  boolean                                   IsBroadcast,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  PhysAddrPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                    LenByte);

/**********************************************************************************************************************
 *  IpV4_Ip_TxConfirmation
 *********************************************************************************************************************/
/*! \brief          Confirms a message transmission.
 *  \details        Called by lower layer (EthIf) if a message has been transmitted by the hardware.
 *  \param[in]      EthIfCtrlIdx EthIf controller index
 *  \param[in]      EthBufIdx    Buffer index
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV4_CODE) IpV4_Ip_TxConfirmation(
  uint8 EthIfCtrlIdx,
  uint8 EthBufIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_Cbk_TrcvLinkStateChg
 *********************************************************************************************************************/
/*! \brief          Called by lower layer on physical link status change
 *  \details        -
 *  \param[in]      EthIfCtrlIdx  Controller index
 *  \param[in]      TrcvLinkState Transceiver link state
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV4_CODE) IpV4_Ip_Cbk_TrcvLinkStateChg(
  uint8                 EthIfCtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState);


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
#endif  /* IPV4_IP_CBK_H */
/**********************************************************************************************************************
 *  END OF FILE: Ip_Cbk.h
 *********************************************************************************************************************/
