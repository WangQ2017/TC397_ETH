/**********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  --------------------------------------------------------------------------------------------------------------------
 *         \file  TcpIp_Tcp.h
 *        \brief  Implementation of Transmission Control Protocol (TCP)
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_TCP_H)
# define TCPIP_TCP_H

/*
--- LIMITAIONS OF THIS IMPLEMENTATION ------------------------------------------
- (Backlog > 1) is not supported
- no precedence and security compartment support
- no OutOfBand data support
*/


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_TCP == STD_ON)
#include "TcpIp_Priv_Types.h"
#include "TcpIp_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define TCPIP_TCP_ACTIVE_OPEN                        TRUE
#define TCPIP_TCP_PASSIVE_OPEN                       FALSE

#define TCPIP_TCP_SOCK_STATE_INVALID                    0u /* must be '0' */ /* is only used for TcpIp_SetSockStateNextOfSocketTcpDyn */
#define TCPIP_TCP_SOCK_STATE_LISTEN                     1u
#define TCPIP_TCP_SOCK_STATE_SYNSENT                    2u
#define TCPIP_TCP_SOCK_STATE_SYNRCVD                    3u
#define TCPIP_TCP_SOCK_STATE_ESTABLISHED                4u
#define TCPIP_TCP_SOCK_STATE_CLOSEWAIT                  5u
#define TCPIP_TCP_SOCK_STATE_LASTACK                    6u
#define TCPIP_TCP_SOCK_STATE_FINWAIT1                   7u
#define TCPIP_TCP_SOCK_STATE_FINWAIT2                   8u
#define TCPIP_TCP_SOCK_STATE_CLOSING                    9u
#define TCPIP_TCP_SOCK_STATE_TIMEWAIT                  10u
#define TCPIP_TCP_SOCK_STATE_CLOSED                    11u

#define TCPIP_TCP_INV_IDX                            TcpIp_GetSizeOfSocketTcpDyn()

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
  /* all values in this struct are in HostByteOrder */
  /* most of the elements can directly be read from the TCP segment header */
  /* TCP Header Format
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Source Port          |       Destination Port        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                        Sequence Number                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Acknowledgment Number                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Data |           |U|A|P|R|S|F|                               |
   | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
   |       |           |G|K|H|T|N|N|                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           Checksum            |         Urgent Pointer        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             data                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   (figure copied from RFC 793)
  */
  IpBase_PortType SrcPort;
  IpBase_PortType TgtPort;
  uint32          SegSeq;      /* SEG.SEQ - segment sequence number - first sequence number of the segment */
  uint32          SegAck;      /* SEG.ACK - segment acknowledgment number - sequence number acknowledged by the peer (next sequence number expected by the receiving TCP) */
  uint16          SegLen;      /* SEG.LEN - payload length - the number of octets occupied by the data in the segment  (_without_ counting SYN and FIN, different than specified in RFC) */
  uint16          SegWnd;      /* SEG.WND - segment window - window size offered by the peer */
  /* Checksum - TCP checksum for the whole segment (header and payload). This parameter is not needed in the struct for analyzing received segments. */
  uint16          UrgentPtr;   /* offset of the urgent data inside the TCP payload of this segment */
  uint8           HdrLen;      /* header length in byte inlcuding TCP options (range [20..60]) */
  uint8           CodeBits;    /* |___|___|URG|ACK|PSH|RST|SYN|FIN| */
  uint8*          HdrPtr;      /* pointer to the TCP header */
  uint8*          PayloadPtr;  /* pointer to the segment payload */
} TcpIp_Tcp_SegmentDescriptorType;


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_Tcp_Init()
 *********************************************************************************************************************/
/*! \brief         Initializes variables and data structures of the TCP submodule.
 *  \details       Function is called during the initialization of the ECU.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Init(void);


/**********************************************************************************************************************
 *  TcpIp_Tcp_CbkPathMtuChg()
 *********************************************************************************************************************/
/*! \brief         Notifies the TCP that the MTU on the path to a certain destination has changed.
 *  \details       -
 *  \param[in]     SockAddrPtr         Network address of the destination.
 *  \param[in]     PathMtuSize         New size of the Path-MTU (transport layer part / maximum IP payload length)
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_CbkPathMtuChg(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr,
  uint16                            PathMtuSize);

/**********************************************************************************************************************
 *  TcpIp_Tcp_Received()
 *********************************************************************************************************************/
/*! \brief         Releases the given number of bytes in the TCP socket RX buffer.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DataLenByte         length of received data in bytes.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different SocketTcpIdx.
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Received(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint16                     DataLenByte);

/**********************************************************************************************************************
 *  TcpIp_Tcp_InitSock()
 *********************************************************************************************************************/
/*! \brief         Initializes a TCP socket.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_InitSock(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_TcpTransmitInternal()
 *********************************************************************************************************************/
/*! \brief         Requests the transmission of data to a remote node using TCP.
 *  \details       This function is either called by TcpIp_TcpTransmit (parameter checks are done there) or by the Tls module to send data via TCP.
 *  \param[in]     SocketIdx           Index of a UDP or TCP socket.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     DataPtr             Pointer to the data that shall be sent.
 *                                     May be NULL_PTR in case indirect data provision is used. (see TcpIp_TcpTransmit())
 *  \param[in]     Length              Length of the data that shalll be sent. (bytes)
 *                                     CONSTRAINT: If DataPtr != NULL_PTR, DataPtr must point to 'Length' number of bytes.
 *  \param[in]     ForceRetrieve       This parameter is only used if DataPtr is NULL_PTR.
 *                                     TRUE:  This function will reject the transmit if there is currently not enough
 *                                            space in the TCP buffer.
 *                                     FALSE: This function may copy less bytes than specified in 'Length'.
 *  \return        E_OK                The request has been accepted
 *  \return        E_NOT_OK            The request has not been accepted
 *  \pre           SocketIdx references a TCP socket in state ESTABLISHED.
 *  \context       TASK
 *  \reentrant     TRUE for different socket indexs.
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpTransmitInternal(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2C(uint8)          DataPtr,
  uint32                    Length,
  boolean                   ForceRetrieve);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
*  TcpIp_TcpTransmitTls()
**********************************************************************************************************************/
/*! \brief         Requests the transmission of data to a remote node using TLS.
 *  \details       This function is called by TcpIp_TcpTransmit (parameter checks are done there) to forward user data
 *                 to the TLS module. TLS will later forward the (maybe encrypted) data to TCP for sending to the
 *                 communication partner.
 *  \param[in]     SocketIdx           Index of a UDP or TCP socket.
 *                                     CONSTRAINT: Here it has to be a TCP socket
 *  \param[in]     DataPtr             Pointer to the data that shall be sent.
 *                                     May be NULL_PTR in case indirect data provision is used. (see TcpIp_TcpTransmit())
 *  \param[in]     Length              Length of the data that shalll be sent. (bytes)
 *                                     CONSTRAINT: If DataPtr != NULL_PTR, DataPtr must point to 'Length' number ob bytes.
 *  \return        E_OK                The request has been accepted
 *  \return        E_NOT_OK            The request has not been accepted
 *  \pre           SocketIdx references a TCP socket in state ESTABLISHED.
 *  \context       TASK
 *  \reentrant     TRUE for different SocketIdx.
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpTransmitTls(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2C(uint8)          DataPtr,
  uint32                    Length);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_GetSockIsConnected()
 *********************************************************************************************************************/
/*! \brief         Get information if socket is connected and not yet closed.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        TRUE                socket is connected
 *  \return        FALSE               socket is not connected
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_GetSockIsConnected(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_MainFunctionRx()
 *********************************************************************************************************************/
/*! \brief         Main function for handling of all rx dependent jobs.
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_MainFunctionRx(void);

/**********************************************************************************************************************
 *  TcpIp_Tcp_MainFunctionTx()
 *********************************************************************************************************************/
/*! \brief         Main function for handling of all tx dependent jobs.
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_MainFunctionTx(void);

/**********************************************************************************************************************
 *  TcpIp_Tcp_MainFunctionState()
 *********************************************************************************************************************/
/*! \brief         Main function to handle state changes and timeouts.
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_MainFunctionState(void);

/**********************************************************************************************************************
 *  TcpIp_Tcp_Open()
 *********************************************************************************************************************/
/*! \brief         Active or passive open of a TCP connection.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SockAddrPtr         IP address and port of the remote host
 *  \param[in]     ActiveOpen          active or passive open of a connection
 *                                     CONSTRAINT: TCPIP_TCP_ACTIVE_OPEN or TCPIP_TCP_PASSIVE_OPEN.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_Open(
  TcpIp_SocketTcpDynIterType        SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr,
  boolean                           ActiveOpen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_Close()
 *********************************************************************************************************************/
/*! \brief         Closes a TCP connection gracefully.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Close(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_Abort()
 *********************************************************************************************************************/
/*! \brief         Closes a TCP immediately via RST.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Abort(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_ResetSocket()
 *********************************************************************************************************************/
/*! \brief         Resets a TCP socket and informs the socket owner.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_ResetSocket(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_SetSockOpt()
 *********************************************************************************************************************/
/*! \brief         Sets a TCP socket option.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     OptName             Option name
 *  \param[in]     OptValPtr           Option parameter
 *  \return        E_OK                Socket option changed
 *  \return        E_NOT_OK            Socket option change request failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_SetSockOpt(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr);

/**********************************************************************************************************************
 *  Stack internal FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_Tcp_VClearTxBuffer()
 *********************************************************************************************************************/
/*! \brief         Clears the content of the TX buffer which is assigned to the socket.
 *  \details       Called in the context of the initialization of the TcpIp.
 *  \param[in]     SockIdx             socket index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_VClearTxBuffer(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VAddrResTimeout()
 *********************************************************************************************************************/
/*! \brief         Informs the TCP that the link layer address resolution to a destination has timed out and related sockets should be closed.
 *  \details       The address resolution for the given address timed out on the given controller, after the address
 *                 resolution request was accepted earlier.
 *  \param[in]     DestAddrPtr         Pointer to destination address
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tcp_VAddrResTimeout(
  TCPIP_P2C(TcpIp_SockAddrBaseType) DestAddrPtr);

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (TCPIP_SUPPORT_TCP == STD_ON) */
#endif
  /* TCPIP_TCP_H */
/**********************************************************************************************************************
 *  END OF FILE: Tcp.h
 *********************************************************************************************************************/
