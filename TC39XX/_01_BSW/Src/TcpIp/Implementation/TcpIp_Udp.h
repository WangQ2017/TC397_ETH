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
 *         \file  TcpIp_Udp.h
 *        \brief  Implementation of User Datagram Protocol (UDP)
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_UDP_H)
# define TCPIP_UDP_H

/*
--- LIMITAIONS OF THIS IMPLEMENTATION ------------------------------------------
- no data handling (rx ant tx) bigger than 64kB possible
- TcpIp_Udp_RecvFrom() ignores "flags"
*/

/*
|0              |8              |16             |24             |
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          Source Port          |       Destination Port        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|            Length             |           Checksum            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
UDP header format
*/
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TcpIp_Priv_Types.h"
#include "IpBase_Types.h"
#include "TcpIp_Cfg.h"
#include "TcpIp_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define TCPIP_UDP_HDR_LEN_BYTE        8u

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_Udp_Init()
 *********************************************************************************************************************/
/*! \brief          Initializes all UDP related parameters and socket structures.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_Init(void);

/**********************************************************************************************************************
 *  TcpIp_Udp_CloseSocket()
 *********************************************************************************************************************/
/*! \brief          Closes a UDP socket and resets the socket related data structures.
 *  \details        -
 *  \param[in]      SocketUdpIdx             Index of a UDP socket.
 *                                           CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \pre            SocketUdpIdx was allocated by <Up>_GetSocket().
 *  \context        TASK
 *  \reentrant      TRUE for different SocketUdpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_CloseSocket(
  TcpIp_SocketUdpDynIterType SocketUdpIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_RequestTxBuffer()
 *********************************************************************************************************************/
/*! \brief          Provides a UDP TX buffer.
 *  \details        This function calls the ProvideTxBuffer service of the IP layer (IPv4 or IPv6) based on the destination
 *                  address and returns a buffer for the UDP payload.
 *  \param[in]      SocketUdpIdx          Index of a UDP socket.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]      DestinationPtr        Pointer to the destination socket address.
 *  \param[out]     BufPtr                Pointer to the (first) UDP payload buffer.
 *  \param[in,out]  BufLenPtr             In:  Required buffer size. [bytes]
 *                                        Out: Actual size of the provided buffer fragment. [bytes] (see notes).
 *  \return         BUFREQ_OK             Buffer provided.
 *  \return         BUFREQ_E_NOT_OK       Buffer could not be provided.
 *  \return         BUFREQ_E_BUSY         IP layer is currently not able to provide buffer. Try again later.
 *  \note                                 If IPv4 is used this function may provide more than one buffer if the requested
 *                                        payload size is too large to fit into one IP packet. In that case only the first
 *                                        buffer fragment is returned by this function. The additional buffer fragments
 *                                        can be obtained via TcpIp_Udp_FragmentRequestTxBuffer().
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketUdpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_Udp_RequestTxBuffer(
  TcpIp_SocketUdpDynIterType         SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)  DestinationPtr,
  TCPIP_P2V(uint8)                  *BufPtr,
  TCPIP_P2V(uint16)                  BufLenPtr);

/**********************************************************************************************************************
 *  TcpIp_Udp_FragmentRequestTxBuffer()
 *********************************************************************************************************************/
/*! \brief          Provides an additional UDP TX buffer fragment.
 *  \details        TcpIp_Udp_RequestTxBuffer() may return a buffer that is smaller than the requested length.
 *                  In that case additional buffer fragments can be obtained via this function.
 *  \param[in]      SocketUdpIdx           Index of a UDP socket.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]      AddrFamily             Address Family of destination used at previous TcpIp_Udp_RequestTxBuffer() call.
 *  \param[out]     BufPtrPtr              Pointer to the next UDP buffer fragment.
 *  \param[out]     BufLenPtr              Length of the next UDP buffer fragment in bytes.
 *  \return         E_OK                   Next fragment buffer provided.
 *  \return         E_NOT_OK               No buffer for next fragment available.
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketUdpIdx.
 *  \pre            TcpIp_Udp_RequestTxBuffer() must be called first.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_FragmentRequestTxBuffer(
  TcpIp_SocketUdpDynIterType  SocketUdpIdx,
  IpBase_FamilyType           AddrFamily,
  TCPIP_P2V(uint8)           *BufPtrPtr,
  TCPIP_P2V(uint16)           BufLenPtr);

/**********************************************************************************************************************
 *  TcpIp_Udp_Transmit()
 *********************************************************************************************************************/
/*! \brief         Transmits a UDP packet.
 *  \details       -
 *  \param[in]     SocketUdpIdx     Index of a UDP socket.
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]     UdpPayloadLen    Length of the UDP payload. [bytes]
 *  \param[in]     DestSockAddrPtr  Destination IP address and port of the UDP packet.
 *  \return        E_OK             Transmit request accepted.
 *  \return        E_NOT_OK         Transmit failed.
 *  \note          The payload of the UDP packet must be written in the provided IP buffer before.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different SocketUdpIdx.
 *  \pre           -
*  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_Transmit(
  TcpIp_SocketUdpDynIterType        SocketUdpIdx,
  uint16                            UdpPayloadLen,
  TCPIP_P2C(TcpIp_SockAddrBaseType) DestSockAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_Udp_TransmitCancel()
 *********************************************************************************************************************/
/*! \brief          Cancels transmit of a UDP datagram.
 *  \details        -
 *  \param[in]      SocketUdpIdx     Index of a UDP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \context        TASK
 *  \reentrant      TRUE for different SocketUdpIdx.
 *  \pre            TcpIp_Udp_ProvideTxBuffer() must have been called before.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_TransmitCancel(
  TcpIp_SocketUdpDynIterType SocketUdpIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_MainFunctionRx()
 *********************************************************************************************************************/
/*! \brief          Main function for RX path. Also handles Tx confirmations.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_MainFunctionRx(void);

/**********************************************************************************************************************
 *  TcpIp_Udp_MainFunctionTx()
 *********************************************************************************************************************/
/*! \brief          Main function for TX path. Transmits queued packets.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_MainFunctionTx(void);

/**********************************************************************************************************************
 *  TcpIp_Udp_ResetSocket()
 *********************************************************************************************************************/
/*! \brief          Reset UDP socket and notify upper layer.
 *  \details        -
 *  \param[in]      SocketUdpIdx    Index of a UDP socket.
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \pre            SocketUdpIdx was allocated by <Up>_GetSocket().
 *  \context        TASK
 *  \reentrant      TRUE for different SocketUdpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_ResetSocket(TcpIp_SocketUdpDynIterType SocketUdpIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_SetSockOpt()
 *********************************************************************************************************************/
/*! \brief          Sets a UDP socket option.
 *  \details        -
 *  \param[in]      SocketUdpIdx           Index of a UDP socket.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]      ParameterId            Parameter identifier
 *  \param[in]      ParameterValuePtr      Parameter value
 *  \return         E_OK                   Socket option changed.
 *  \return         E_NOT_OK               Socket option change request failed
 *  \pre            SocketUdpIdx was allocated by <Up>_GetSocket().
 *  \context        TASK
 *  \reentrant      TRUE for different SocketUdpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_SetSockOpt(
  TcpIp_SocketUdpDynIterType                 SocketUdpIdx,
  TcpIp_ParamIdType                          ParameterId,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) ParameterValuePtr);


/**********************************************************************************************************************
 *  TcpIp_Udp_SendRetryQueueIfPossible()
 *********************************************************************************************************************/
/*! \brief          Retries to send the pending datagrams in the UDP retry queue.
 *  \details        The retry can be limited to datagrams for a specific destination address.
 *  \param[in]      SocketUdpIdx        Index of a UDP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \pre            SocketUdpIdx was allocated by <Up>_GetSocket().
 *  \context        TASK
 *  \reentrant      TRUE for different SocketUdpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_SendRetryQueueIfPossible(
  TcpIp_SocketUdpDynIterType        SocketUdpIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_CancelRetriesForDestination()
 *********************************************************************************************************************/
/*! \brief          Aborts the transmit of all pending datagrams for a specific destination.
 *  \details        -
 *  \param[in]      CtrlIdx             Index of an EthIf controller.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfEthIfCtrl()-1]
 *  \param[in]      RemoteAddrPtr       Remote socket address.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Udp_CancelRetriesForDestination(
  uint8                             CtrlIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteAddrPtr);

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
  /* TCPIP_UDP_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Udp.h
 *********************************************************************************************************************/
