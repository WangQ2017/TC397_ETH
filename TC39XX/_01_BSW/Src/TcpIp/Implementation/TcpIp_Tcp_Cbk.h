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
 *         \file  TcpIp_Tcp_Cbk.h
 *        \brief  Implementation of Transmission Control Protocol (TCP) - Callback Header
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_TCP_CBK_H)
# define TCPIP_TCP_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TcpIp_Priv_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_Tcp_RxIndication
 *********************************************************************************************************************/
/*! \brief         Receive Indication Callback
 *  \details       -
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      IP address and port of remote socket
 *  \param[in]     DataPtr               pointer to the received data
 *  \param[in]     LenByte               length of received data
 *  \param[in]     ChecksumCalculated    indicates if the TCP checksum is already checked by lower layer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_RxIndication(
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2V(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2V(uint8)                  DataPtr,
  uint16                            LenByte,
  boolean                           ChecksumCalculated);

/**********************************************************************************************************************
 *  TcpIp_Tcp_StoreChecksumInHeader
 *********************************************************************************************************************/
/*! \brief         Stores a calculated TCP checksum value at the correct position into the TCP header
 *  \details       -
 *  \param[in]     Checksum              Finalized checksum value. Value is in network byte order.
 *  \param[in]     TcpHdrPtr             Pointer to the TCP header that shall be written partly. So 20 bytes have to be
 *                                       available starting at TcpHdrPtr.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_StoreChecksumInHeader(
  uint16           Checksum,
  TCPIP_P2V(uint8) TcpHdrPtr);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsRxIndication
 *********************************************************************************************************************/
/*! \brief         Forwards the received (and decoded) data from TLS to the socket owner.
 *  \details       -
 *  \param[in]     SocketIdx           Index of a UDP or TCP socket
 *  \param[in]     DataPtr             Pointer to the received data
 *  \param[in]     DataLen             Length of received data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsRxIndication(
  TcpIp_SocketIdType                       SocketIdx,
  TCPIP_P2V(uint8) DataPtr,
  uint16                                   DataLen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsTxConfirmation
 *********************************************************************************************************************/
/*! \brief         Forwards the TxConfirmation from TLS to the socket owner
 *  \details       -
 *  \param[in]     SocketIdx           Index of a UDP or TCP socket
 *  \param[in]     DataLen             Length of transmitted/confirmed data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsTxConfirmation(
  TcpIp_SocketIdType SocketIdx,
  uint16             DataLen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsConnected
 *********************************************************************************************************************/
/*! \brief         Forwards the 'connected' event from TLS to the socket owner
 *  \details       -
 *  \param[in]     SocketIdx           Index of a UDP or TCP socket
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsConnected(
  TcpIp_SocketIdType SocketIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsEvent
 *********************************************************************************************************************/
/*! \brief         Forwards the event from TLS to the socket owner
 *  \details       -
 *  \param[in]     SocketIdx           Index of a UDP or TCP socket
 *  \param[in]     Event               Event identifier
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsEvent(
  TcpIp_SocketIdType SocketIdx,
  TcpIp_EventType Event);

/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsValidationResult
 *********************************************************************************************************************/
/*! \brief         Forwards the event from TLS to the socket owner
 *  \details       -
 *  \param[in]     SocketIdx             Index of a UDP or TCP socket
 *  \param[in,out] ValidationResultPtr   Result of the chain validation, can be overruled by the socket owner
 *  \param[in]     CertChainPtr          Pointer to the certificate chain
 *  \param[in]     CertChainLen          Length of the certificate chain
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsValidationResult(
  TcpIp_SocketIdType  SocketIdx,
  TCPIP_P2V(uint8)    ValidationResultPtr,
  TCPIP_P2C(uint8)    CertChainPtr,
  uint32              CertChainLen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsReceived
 *********************************************************************************************************************/
/*! \brief         Marks part of buffer as read.
 *  \details       -
 *  \param[in]     SocketIdx           Index of a UDP or TCP socket
 *  \param[in]     DataLenByte         Length of received data in bytes
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsReceived(
  TcpIp_SocketIdType SocketIdx,
  uint32 DataLenByte);

#endif

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
  /* TCPIP_TCP_CBK_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Tcp_Cbk.h
 *********************************************************************************************************************/
