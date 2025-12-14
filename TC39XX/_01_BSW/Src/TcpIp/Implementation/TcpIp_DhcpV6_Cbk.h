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
 *         \file  TcpIp_DhcpV6_Cbk.h
 *        \brief  Implementation of Dynamic Host Configuration Protocol for IPv6 - Client (DHCPv6 Client) - Callback Header
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv6 submodule. >> TcpIp_IpV6.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

#if !defined (TCPIP_DHCPV6_CBK_H)
# define TCPIP_DHCPV6_CBK_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TcpIp.h"

#include "IpBase_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_RxIndication
 *********************************************************************************************************************/
/*! \brief         Receive Indication Callback
 *  \details       -
 *  \param[in]     IpCtrlIdx             IP controller index
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     DataPtr               Pointer to the received data
 *  \param[in]     DataLen               Length of the received data in bytes
 *  \param[in]     SourcePtr             Source address pointer
 *  \param[in]     DestinationPtr        Destination address pointer
 *  \param[in]     ChecksumCalculated    Indicates if the UDP checksum is already checked by lower layer
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_RxIndication(
    TcpIp_IpV6CtrlIterType        IpCtrlIdx,
    TCPIP_P2C(uint8)              DataPtr,
    uint16                        DataLen,
    boolean ChecksumCalculated,
    TCPIP_P2C(IpBase_AddrIn6Type) SourcePtr,
    TCPIP_P2C(IpBase_AddrIn6Type) DestinationPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_TxConfirmation
 *********************************************************************************************************************/
/*! \brief         Transmission Confirmation Callback
 *  \details       -
 *  \param[in]     SockHnd            Socket handle
 *  \param[in]     Length             Length in bytes
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_TxConfirmation(
    TcpIp_SockHndType SockHnd,
    uint32            Length);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Cbk_LocalIpAssignmentChg
 *********************************************************************************************************************/
/*! \brief         Callback for change of network address assignment notification
 *  \details       -
 *  \param[in]     IpAddrId           Ip address identifier
 *  \param[in]     State              Assignment state
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_Cbk_LocalIpAssignmentChg(
    IpV6_AddrIdType       IpAddrId,
    TcpIp_IpAddrStateType State);

/**********************************************************************************************************************
 *  Dummy callback functions. Functions not implemented because DHCP does not use TCP
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_TcpAccepted
 *********************************************************************************************************************/
/*! \brief         Dummy callback function for Tcp implementation of dhcpv6
 *  \details       -
 *  \param[in]     -
 *  \param[in]     -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_TcpAccepted(TcpIp_SockHndType SockHnd);
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_TcpConnected
 *********************************************************************************************************************/
/*! \brief         Dummy callback function for Tcp implementation of dhcpv6
 *  \details       -
 *  \param[in]     -
 *  \param[in]     -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_TcpConnected(TcpIp_SockHndType SockHnd);
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_TcpIpEvent
 *********************************************************************************************************************/
/*! \brief         Dummy callback function for Tcp implementation of dhcpv6
 *  \details       -
 *  \param[in]     -
 *  \param[in]     -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_TcpIpEvent(TcpIp_SockHndType SockHnd, IpBase_TcpIpEventType Event);


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */
#endif  /* TCPIP_DHCPV4_CBK_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_DhcpV6_Cbk.h
 *********************************************************************************************************************/
