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
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SoAd_SoCon.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component SoCon.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main source file.
 *********************************************************************************************************************/

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_SO_CON_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_EventQueue.h"
#include "SoAd_TimeoutList.h"
#include "SoAd_TcpIp.h"
#include "SoAd_Util.h"
#include "SoAd_SoCon.h"
#include "SoAd_Tx.h"
#include "SoAd_Rx.h"
#include "SoAd_Measure.h"

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
#include "IpBase.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL static
#endif

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/*! Counts the number of open TcpIp sockets. */
SOAD_LOCAL VAR(SoAd_SizeOfSocketType, SOAD_VAR_NOINIT) SoAd_SoCon_OpenSocks;

#define SOAD_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
 *  SoAd_SoCon_UdpChangeParameter()
**********************************************************************************************************************/
/*! \brief      Changes parameters on a UDP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change request was accepted.
 *  \return     E_NOT_OK        Parameter change request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-SoAdHandleSockets, DSGN-SoAdUdpRetry
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_UdpChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterNoDelay()
 *********************************************************************************************************************/
/*! \brief      Changes no delay (Nagle algorithm) parameter on a TCP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change request was accepted or not required.
 *  \return     E_NOT_OK        Parameter change request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterNoDelay(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterKeepAlive()
 *********************************************************************************************************************/
/*! \brief      Changes keep alive parameters on a TCP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change requests were accepted or not required.
 *  \return     E_NOT_OK        Parameter change requests were not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterKeepAlive(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterTls()
 *********************************************************************************************************************/
/*! \brief      Changes TLS parameters on a TCP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change requests were accepted or not required.
 *  \return     E_NOT_OK        Parameter change requests were not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *  \trace      DSGN-SoAdNotifyTlsSocketConnection
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterTls(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAcceptedCheckAcceptance()
 *********************************************************************************************************************/
/*! \brief      Checks connection acceptance on a socket connection on connection establishment on listen socket.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SocketIdConnected   Connected socket identifier.
 *  \param[in]  RemoteAddrPtr       Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK                Socket connection accepted connection establishment.
 *  \return     E_NOT_OK            Socket connection rejected connection establishment.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAcceptedCheckAcceptance(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketIdConnected,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpClose()
 *********************************************************************************************************************/
/*! \brief      Handles UDP close event on socket.
 *  \details    -
 *  \param[in]  SockIdx     Module internal socket index.
 *                          [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpClose(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpCloseAllSoCons()
 *********************************************************************************************************************/
/*! \brief      Closes all related socket connections on UDP close event on socket.
 *  \details    -
 *  \param[in]  SockIdx     Module internal socket index.
 *                          [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpCloseAllSoCons(
  SoAd_SizeOfSocketType SockIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpClose()
 *********************************************************************************************************************/
/*! \brief      Handles TCP close and reset event on socket.
 *  \details    -
 *  \param[in]  SockIdx     Module internal socket index.
 *                          [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpClose(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpFinReceived()
 *********************************************************************************************************************/
/*! \brief      Handles TCP FIN received event on socket.
 *  \details    -
 *  \param[in]  SockIdx     Module internal socket index.
 *                          [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpFinReceived(
  SoAd_SizeOfSocketType SockIdx);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckStates()
 *********************************************************************************************************************/
/*! \brief      Checks socket connection state to indicate if remote address is allowed to bet set.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK            States on socket connections allow to set remote address.
 *  \return     E_NOT_OK        States on socket connections does not allow to set remote address.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckStates(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckAndSet()
 *********************************************************************************************************************/
/*! \brief      Checks a remote address and set it on a socket connection if remote address is valid.
 *  \details    Compares remote address to be set with all related local addresses and overwrites current remote
 *              address if remote address to be set is different to the local addresses.
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  RemoteAddrPtr   Pointer to remote address.
 *                              [Points to one of the following structs depending on configured IP address version
 *                              of parameter SoConIdx:
 *                                - SoAd_SockAddrInetType for IPv4
 *                                - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK            Remote address is valid and set.
 *  \return     E_NOT_OK        Remote address is not valid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckAndSet(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrTcp()
 *********************************************************************************************************************/
/*! \brief      Sets the remote address on a TCP socket connection if setting unique remote address is used.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  RemoteAddrPtr       Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK                Request was accepted.
 *  \return     E_NOT_OK            Request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrTcp(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrUdp()
 *********************************************************************************************************************/
/*! \brief      Sets the remote address on a UDP socket connection if setting unique remote address is used.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  RemoteAddrPtr       Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK                Request was accepted.
 *  \return     E_NOT_OK            Request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrUdp(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpen()
 *********************************************************************************************************************/
/*! \brief      Performs open actions to open a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \trace      DSGN-SoAdAutomaticOpenAndClose, DSGN-SoAdOpenOnReception
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpen(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpenSocketForOpenOnReception()
 *********************************************************************************************************************/
/*! \brief      Performs open actions for a UDP socket to support socket connection open on reception.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpenSocketForOpenOnReception(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_Open()
 *********************************************************************************************************************/
/*! \brief      Opens a socket connection and the related socket.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-SoAdHandleSockets
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Open(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketUdp()
 *********************************************************************************************************************/
/*! \brief      Opens a socket for a UDP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK            Socket is opened or already assigned.
 *  \return     E_NOT_OK        Socket is not opened.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketUdp(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_AssignSocketUdp()
 *********************************************************************************************************************/
/*! \brief      Assigns a socket for a UDP socket connection and updates the state.
 *  \details    -
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  LocalPort       Local port.
 *  \return     E_OK            Socket is opened or already assigned.
 *  \return     E_NOT_OK        Socket is not opened.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_AssignSocketUdp(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PortType LocalPort);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConUdp()
 *********************************************************************************************************************/
/*! \brief      Opens UDP socket connection if a socket is already assigned.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConUdp(
  SoAd_SizeOfSoConType SoConIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClient()
 *********************************************************************************************************************/
/*! \brief      Opens a socket for a TCP client socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK            Socket is assigned and connects to remote entity.
 *  \return     E_NOT_OK        Socket is not assigned or is already connecting.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClient(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientGetAndConnect()
 *********************************************************************************************************************/
/*! \brief      Gets a socket for a TCP client socket connection and starts connecting to remote entity.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return     E_OK            Socket is assigned and connects to remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientGetAndConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientConnect()
 *********************************************************************************************************************/
/*! \brief      Starts connecting to remote entity on a socket for a TCP client socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  SocketId        Socket identifier.
 *  \param[in]  LocalPort       Local port.
 *  \return     E_OK            Socket is assigned and connects to remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServer()
 *********************************************************************************************************************/
/*! \brief      Opens a socket for a TCP server socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                              SoAd_IsSocketTcpUsedOfSoConGrp(),
 *                              !SoAd_IsTcpInitiateOfSocketTcp()]
 *  \return     E_OK            Socket is assigned and listens for connection attempts from remote entity.
 *  \return     E_NOT_OK        Socket is not assigned or is already listening.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServer(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerGetAndListen()
 *********************************************************************************************************************/
/*! \brief      Gets a socket for a TCP server socket connection and starts listening for connection attempts.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  ListenSockIdx   Module internal socket index of listen socket.
 *                              [range: ListenSockIdx < SoAd_GetSizeOfSocket()]
 *  \return     E_OK            Socket is assigned and listens for connection attempts from remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerGetAndListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType ListenSockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerListen()
 *********************************************************************************************************************/
/*! \brief      Starts listening for connection attempts on a socket for a TCP server.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  ListenSockIdx   Module internal socket index of listen socket.
 *                              [range: ListenSockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  SocketId        Socket identifier.
 *  \param[in]  LocalPort       Local port.
 *  \return     E_OK            Socket is assigned and listens for connection attempts from remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType ListenSockIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConTcp()
 *********************************************************************************************************************/
/*! \brief      Opens TCP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConTcp(
  SoAd_SizeOfSoConType SoConIdx);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_Close()
 *********************************************************************************************************************/
/*! \brief      Closes a socket connection and the related sockets.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Close(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSoCon()
 *********************************************************************************************************************/
/*! \brief      Closes a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSoCon(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocket()
 *********************************************************************************************************************/
/*! \brief      Closes socket connection related sockets.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  Abort       Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocket(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcp()
 *********************************************************************************************************************/
/*! \brief      Closes TCP socket connection related socket.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  Abort       Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcp(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcpListen()
 *********************************************************************************************************************/
/*! \brief      Closes TCP socket connection related listen socket if no other socket connection requires the socket.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  Abort       Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcpListen(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketUdp()
 *********************************************************************************************************************/
/*! \brief      Closes UDP socket connection related socket if no other socket connection requires the socket.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  Abort       Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketUdp(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetCloseMode()
 *********************************************************************************************************************/
/*! \brief        Resets close mode considering socket connection and socket states.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetCloseMode(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifySoConModeChg()
 *********************************************************************************************************************/
/*! \brief      Notifies users about a socket connection mode change.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  Mode        Socket connection mode.
 *                          [range: SOAD_SOCON_ONLINE, SOAD_SOCON_RECONNECT, SOAD_SOCON_OFFLINE]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-SoAdNotifySocketConnectionStateChange
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifySoConModeChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SoConModeType Mode);

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifyLocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*! \brief      Notifies users about a socket connection local IP address assignment change.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  State       State of IP address assignment.
 *                          [range: SOAD_IPADDR_STATE_ASSIGNED, SOAD_IPADDR_STATE_ONHOLD, SOAD_IPADDR_STATE_UNASSIGNED]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-SoAdNotifyLocalIpAddressAssignmentStateChange
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifyLocalIpAddrAssignmentChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrStateType State);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetLocalPortDyn()
 *********************************************************************************************************************/
/*! \brief        Resets local port of a socket.
 *  \details      Considers that a local port is shared by multiple sockets/socket connections.
 *  \param[in]    SockIdx       Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetSoCon()
 *********************************************************************************************************************/
/*! \brief      Resets socket connection specific properties.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  ResetRemAddr  Indicates if remote address shall be reset.
 *  \param[in]  ResetOpClSeq  Indicates if open/close sequence shall be reset.
 *  \param[in]  NormalClose   Indicates if socket connection is closed by normal close request.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  boolean ResetRemAddr,
  boolean ResetOpClSeq,
  boolean NormalClose);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAndRcvRemAddr()
 *********************************************************************************************************************/
/*! \brief      Resets remote address and received remote address on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAndRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAddr()
 *********************************************************************************************************************/
/*! \brief      Resets remote address on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-SoAdHandleRemoteAddressState
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAddr(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRcvRemAddr()
 *********************************************************************************************************************/
/*! \brief      Resets received remote address on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_IsTxActive()
 *********************************************************************************************************************/
/*! \brief      Indicates if a transmission is active on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     TRUE            Transmission is active.
 *  \return     FALSE           No transmission is active.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_IsTxActive(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_IsTxRouteGrpActive()
 *********************************************************************************************************************/
/*! \brief      Indicates if a routing group transmission is active on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     TRUE            Transmission is active.
 *  \return     FALSE           No transmission is active.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_IsTxRouteGrpActive(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdx()
 *********************************************************************************************************************/
/*! \brief      Returns the best match algorithm priority of a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx              Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SockAddrPtr           Pointer to socket address used to perform best match algorithm.
 *                                    [Points to one of the following structs depending on configured IP address
 *                                    version of parameter SoConIdx:
 *                                      - SoAd_SockAddrInetType for IPv4
 *                                      - SoAd_SockAddrInet6Type for IPv6]
 *  \return     Priority              Best match algorithm priority of socket connection.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdx(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr);

#if ( SOAD_IPV6 == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6()
 *********************************************************************************************************************/
/*! \brief      Returns the best match algorithm priority of a socket connection of type IPv6.
 *  \details    -
 *  \param[in]  SoConIdx              Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                                    SoAd_GetDomainOfLocalAddr() == SOAD_AF_INET6]
 *  \param[in]  SockAddrPtr           Pointer to socket address used to perform best match algorithm.
 *  \return     Priority              Best match algorithm priority of socket connection.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_IPV6
 *********************************************************************************************************************/
/* PRQA S 779 3 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr);
#endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4()
 *********************************************************************************************************************/
/*! \brief      Returns the best match algorithm priority of a socket connection of type IPv4.
 *  \details    -
 *  \param[in]  SoConIdx              Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                                    SoAd_GetDomainOfLocalAddr() == SOAD_AF_INET]
 *  \param[in]  SockAddrPtr           Pointer to socket address used to perform best match algorithm.
 *  \return     Priority              Best match algorithm priority of socket connection.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
/* PRQA S 779 3 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrInetType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUdpAliveTimeout()
 *********************************************************************************************************************/
/*! \brief      Sets the UDP alive supervision timeout on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                              SoAd_IsSocketUdpUsedOfSoConGrp()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_SetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetUdpAliveTimeout()
 *********************************************************************************************************************/
/*! \brief      Resets the UDP alive supervision timeout on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                              SoAd_IsSocketUdpUsedOfSoConGrp()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_DecrementOpenSockets()
 *********************************************************************************************************************/
/*! \brief      Decrements the number of open sockets.
 *  \details    -
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_DecrementOpenSockets(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_SoCon_UdpChangeParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_UdpChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set frame priority. */
  if ( SoAd_GetFramePriorityOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) != SOAD_NO_FRAMEPRIORITYOFSOCONGRP )
  {
    uint8 framePriority = SoAd_GetFramePriorityOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));

    retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_FRAMEPRIO, &framePriority);                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #20 Set UDP Tx request list size. */
  if ( SoAd_IsImmedIfTxConfOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))) )
  {
    uint8 udpTxReqListSize = SoAd_GetImmedIfTxConfListSizeOfSocketUdp(
      SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)));

    retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_UDP_TXREQLISTSIZE, &udpTxReqListSize);       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #30 Set UDP Tx retry list size (number of Eth Tx buffers used in case of physical address miss). */
  if ( SoAd_IsRetryEnabledOfTcpIpCtrl(
    SoAd_GetTcpIpCtrlIdxOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSocketUdpIdxOfSoConGrp(
      SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))))) )
  {
    uint8 udpTxRetryListSize = SoAd_GetRetryQueueLimitOfSocketUdp(
      SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)));

    retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_UDP_TXRETRYLISTSIZE, &udpTxRetryListSize);   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #40 Set stack (Socket API) specific parameters. */
  retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_STACK_SPECIFIC, NULL_PTR);                     /* SBSW_SOAD_NULL_POINTER_FORWARD */

  return retVal;
} /* SoAd_SoCon_UdpChangeParameter() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterNoDelay()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterNoDelay(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  switch ( SoAd_GetTcpNoDelayOfSocketTcp(socketTcpIdx) )
  {
    /* #10 Change parameter if no delay (Nagle algorithm) is enabled. */
    case SOAD_TCP_NO_DELAY_ENABLED:
    {
      uint8 value = 0x00u;

      retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_NAGLE, &value);                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
    /* #20 Change parameter if no delay (Nagle algorithm) is disabled. */
    case SOAD_TCP_NO_DELAY_DISABLED:
    {
      uint8 value = 0x01u;

      retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_NAGLE, &value);                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
    /* #30 Do not change parameter if no delay (Nagle algorithm) is not configured. */
    default:
    { /* SOAD_TCP_NO_DELAY_NOT_SPECIFIED */
      /* nothing to do */
      break;
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpChangeParameterNoDelay() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterKeepAlive()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterKeepAlive(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if keep alive is enabled globally. */
  if ( SoAd_IsTcpKeepAliveGloballyEnabled(0u) )
  {
    boolean tcpKeepAlive = (boolean)SoAd_IsTcpKeepAliveOfSocketTcp(socketTcpIdx);

    /* #100 Enable/Disable keep alive. */
    retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_KEEPALIVE,                                /* SBSW_SOAD_CAST_POINTER_FORWARD */
      SOAD_A_P2VAR(uint8)&tcpKeepAlive);

    /* #101 Check if keep alive could be set. */
    if ( (retVal == E_OK) && (tcpKeepAlive == TRUE) )
    {
      uint32 tcpKeepAliveTime = SoAd_GetTcpKeepAliveTimeOfSocketTcp(socketTcpIdx);
      uint32 tcpKeepAliveInterval = SoAd_GetTcpKeepAliveIntervalOfSocketTcp(socketTcpIdx);
      uint16 tcpKeepAliveProbesMax = SoAd_GetTcpKeepAliveProbesMaxOfSocketTcp(socketTcpIdx);

      /* #1010 Set keep alive time. */
      if ( tcpKeepAliveTime != SOAD_NO_TCPKEEPALIVETIMEOFSOCKETTCP )
      {
        retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_KEEPALIVE_TIME,                       /* SBSW_SOAD_CAST_POINTER_FORWARD */
          SOAD_A_P2VAR(uint8)&tcpKeepAliveTime); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */
      }
      /* #1011 Set keep alive maximum probes. */
      if ( tcpKeepAliveProbesMax != SOAD_NO_TCPKEEPALIVEPROBESMAXOFSOCKETTCP )
      {
        retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_KEEPALIVE_PROBES_MAX,                /* SBSW_SOAD_CAST_POINTER_FORWARD */
          SOAD_A_P2VAR(uint8)&tcpKeepAliveProbesMax); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */
      }
      /* #1012 Set keep alive interval. */
      if ( tcpKeepAliveInterval != SOAD_NO_TCPKEEPALIVEINTERVALOFSOCKETTCP )
      {
        retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_KEEPALIVE_INTERVAL,                  /* SBSW_SOAD_CAST_POINTER_FORWARD */
          SOAD_A_P2VAR(uint8)&tcpKeepAliveInterval); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */
      }
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpChangeParameterKeepAlive() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterTls()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterTls(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TLS is enabled. */
  if ( SoAd_IsTlsConfigUsedOfSoCon(SoConIdx) )
  {
    SoAd_SizeOfTlsConfigType  tlsConfigIdx = SoAd_GetTlsConfigIdxOfSoCon(SoConIdx);
    uint8                     tlsEnabled = (uint8)TRUE;

    /* #100 Enable TLS. */
    retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_USE_TLS, &tlsEnabled);                        /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

    /* #101 Check if TLS could be enabled. */
    if ( retVal == E_OK )
    {
      uint32 bufSize;

      /* #1010 Set TLS rx buffer size. */
      bufSize = SoAd_GetRxBufSizeOfTlsConfig(tlsConfigIdx);
      retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TLS_RXBUFSIZE,                              /* SBSW_SOAD_CAST_POINTER_FORWARD */
        SOAD_A_P2VAR(uint8)&bufSize); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */

      /* #1011 Set TLS tx buffer size. */
      bufSize = SoAd_GetTxBufSizeOfTlsConfig(tlsConfigIdx);
      retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TLS_TXBUFSIZE,                             /* SBSW_SOAD_CAST_POINTER_FORWARD */
        SOAD_A_P2VAR(uint8)&bufSize); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */

      /* #1012 Notify about TLS socket creation. */
      if ( SoAd_IsTcpTlsSocketCreatedNotificationCbkUsedOfTlsConfig(tlsConfigIdx) )
      {
        if ( SoAd_GetTcpTlsSocketCreatedNotificationCbk(
          SoAd_GetTcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig(tlsConfigIdx)) != NULL_PTR )
        {
          SoAd_GetTcpTlsSocketCreatedNotificationCbk(                                                                  /* SBSW_SOAD_FUNCTION_PTR */
            SoAd_GetTcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig(tlsConfigIdx))(
              SoAd_GetSoConIdOfSoCon(SoConIdx), SocketId);
        }
      }
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpChangeParameterTls() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAcceptedCheckAcceptance()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAcceptedCheckAcceptance(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketIdConnected,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check socket connection related socket state. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    retVal = E_OK;

    /* #200 Assign socket identifier to module internal socket index. */
    SoAd_SetSocketIdOfSocketDyn(sockIdx, SocketIdConnected);                                                           /* SBSW_SOAD_CSL03_CSL02 */

    /* #201 Update remote address on socket connection. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx),                  /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */
      RemoteAddrPtr);
    SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx, SOAD_SOCON_IP_SET_PORT_SET);                                           /* SBSW_SOAD_PARAMETER_IDX */

    /* #202 Set socket and socket connection state. */
    SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_ESTABLISHED);                                                    /* SBSW_SOAD_CSL03_CSL02 */
    SoAd_SoCon_OpenSocks++;
    SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_ONLINE);                                                               /* SBSW_SOAD_PARAMETER_IDX */

    /* #203 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #204 Notify user about state change. */
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, SoAd_GetModeOfSoConDyn(SoConIdx));

    /* #205 Check if socket connection has a SocketRoute. */
    if ( SoAd_GetSocketRouteStartIdxOfSoCon(SoConIdx) != SoAd_GetSocketRouteEndIdxOfSoCon(SoConIdx) )
    {
      /* #2050 Try to start TP reception is required. */
      if ( SoAd_Rx_TpStartOfReception(SoConIdx) == E_NOT_OK )
      {
        retVal = E_NOT_OK;
      }
    }
  }
  /* #21 Otherwise leave critical section. */
  else
  {
    SOAD_END_CRITICAL_SECTION();
  }

  return retVal;
} /* SoAd_SoCon_TcpAcceptedCheckAcceptance() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpClose()
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
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpClose(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent inconsistencies in socket and socket connection states. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Reset map of module internal socket index to socket identifier. */
  SoAd_SetSocketIdOfSocketDyn(SockIdx, SOAD_INV_SOCKET_ID);                                                            /* SBSW_SOAD_PARAMETER_IDX */

  /* #30 Check if socket is not yet in closed state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #40 Decrement number of open sockets. */
    SoAd_SoCon_DecrementOpenSockets();

    /* #50 Set socket state. */
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CLOSED);                                                         /* SBSW_SOAD_PARAMETER_IDX */

    /* #60 Reset map of module internal socket index to active transmitting socket connection. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSoCon());                                               /* SBSW_SOAD_PARAMETER_IDX */

    /* #70 Reset local port to the configured value. */
    SoAd_SoCon_ResetLocalPortDyn(SockIdx);

    /* #80 Close all related socket connections. */
    SoAd_SoCon_EventUdpCloseAllSoCons(SockIdx);
  }

  /* #90 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_SoCon_EventUdpClose() */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpCloseAllSoCons()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpCloseAllSoCons(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType soConIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all related socket connection to close them. */
  for ( soConIter = SoAd_GetSoConStartIdxOfSocket(SockIdx);
    soConIter < SoAd_GetSoConEndIdxOfSocket(SockIdx);
    soConIter++ )
  {
    /* #20 Check if socket connection is not closed. */
    if ( SoAd_GetModeOfSoConDyn(soConIter) != SOAD_SOCON_OFFLINE )
    {
      /* #30 Set close mode to indicate that socket is closed. */
      SoAd_SoCon_SetCloseMode((SoAd_SizeOfSoConType)soConIter, SOAD_CLOSE_SOCKET);

      /* #40 Set event to handle socket connection state in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, (SoAd_SizeOfSoConType)soConIter);
    }
  }
} /* SoAd_SoCon_EventUdpCloseAllSoCons() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpClose()
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
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpClose(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent inconsistencies in socket and socket connection states. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Reset map of module internal socket index to socket identifier. */
  SoAd_SetSocketIdOfSocketDyn(SockIdx, SOAD_INV_SOCKET_ID);                                                            /* SBSW_SOAD_PARAMETER_IDX */

  /* #30 Check if socket is not yet in closed state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #40 Decrement number of open sockets. */
    SoAd_SoCon_DecrementOpenSockets();

    /* #50 Set socket state. */
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CLOSED);                                                         /* SBSW_SOAD_PARAMETER_IDX */

    /* #60 Reset map of module internal socket index to active transmitting socket connection. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSoCon());                                               /* SBSW_SOAD_PARAMETER_IDX */

    /* #70 Reset local port to the configured value. */
    SoAd_SoCon_ResetLocalPortDyn(SockIdx);

    /* #80 Check if socket is no listen socket. */
    if ( SockIdx != SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx) )
    {
      /* #800 Set close mode to indicate that socket is closing and shall be reconnected in case of client socket. */
      if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
      {
        SoAd_SoCon_SetCloseMode(soConIdx, SOAD_CLOSE_SOCKET_RECONNECT);
      }
      /* #801 Set close mode to indicate that socket is closing otherwise. */
      else
      {
        SoAd_SoCon_SetCloseMode(soConIdx, SOAD_CLOSE_SOCKET);
      }

      /* #802 Set event to handle socket connection state in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx);
    }
    /* #81 Set event to handle state in main function for all socket connections related to listen socket otherwise. */
    else
    {
      SoAd_SoConIterType soConIter;

      for ( soConIter = SoAd_GetSoConStartIdxOfSocket(SockIdx);
        soConIter < SoAd_GetSoConEndIdxOfSocket(SockIdx);
        soConIter++ )
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, (uint32)soConIter);
      }
    }
  }

  /* #90 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_SoCon_EventTcpClose() */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpFinReceived()
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
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpFinReceived(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  SoAd_SocketIdType       socketId = SoAd_GetSocketIdOfSocketDyn(SockIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to check socket identifier validity and the socket state. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if socket is not yet in closed state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #30 Set close mode to indicate that socket is closing and shall be reconnected in case of client socket. */
    if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
    {
      SoAd_SoCon_SetCloseMode(soConIdx, SOAD_CLOSE_SOCKET_RECONNECT);
    }
    /* #31 Set close mode to indicate that socket is closing otherwise. */
    else
    {
      SoAd_SoCon_SetCloseMode(soConIdx, SOAD_CLOSE_SOCKET);
    }

    /* #40 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx);

    /* #50 Set socket to closing. */
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CLOSING);                                                        /* SBSW_SOAD_PARAMETER_IDX */

    /* #60 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #70 Close socket.*/
    SoAd_TcpIp_Close(socketId, FALSE, SockIdx);
  }
  /* #21 Leave critical section otherwise. */
  else
  {
    SOAD_END_CRITICAL_SECTION();
  }
} /* SoAd_SoCon_EventTcpFinReceived() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckStates(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket connection is not offline in case of TCP (if enabled). */
  if ( (SoAd_GetModeOfSoConDyn(SoConIdx) != SOAD_SOCON_OFFLINE) &&
    SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
  {
    retVal = E_NOT_OK;
  }
#endif /* SOAD_TCP == STD_ON */

  /* #20 Check if TP transmission is active. */
  if ( SoAd_IsTxMgtUsedOfSoCon(SoConIdx) )
  {
    if ( SoAd_GetPduRouteDestIdxOfTxMgt(SoAd_GetTxMgtIdxOfSoCon(SoConIdx)) != SoAd_GetSizeOfPduRouteDest() )
    {
      retVal = E_NOT_OK;
    }
  }

  /* #30 Check if TP reception is active. */
  if ( SoAd_IsRxMgtUsedOfSoCon(SoConIdx) )
  {
    if ( SoAd_GetSocketRouteDestIdxOfRxMgt(SoAd_GetRxMgtIdxOfSoCon(SoConIdx)) != SoAd_GetSizeOfSocketRouteDest() )
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* SoAd_SoCon_SetRemoteAddrCheckStates() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckAndSet()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckAndSet(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare remote address to corresponding local IP addresses to prevent setting local IP address as remote. */
  /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
  if ( SoAd_TcpIp_CompareToIpAddr(SoConIdx, (SOAD_A_P2CONST(SoAd_SockAddrInetXType)RemoteAddrPtr)->addr) ==            /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_FORWARD */
    E_NOT_OK)
  {
    boolean addrIsAny = FALSE;
    boolean portIsAny = FALSE;

    /* #20 Enter critical section to prevent that remote address is set in other context. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Copy remote address to local struct. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx), RemoteAddrPtr);  /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */

    /* #40 Set remote address state considering wildcards in remote address to be set. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CheckForWildcards(RemoteAddrPtr, &addrIsAny, &portIsAny);                                                /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    if ( addrIsAny == TRUE )
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SOAD_SOCON_IP_ANY_PORT_ANY & SOAD_SOCON_MASK_IPADDR));
    }
    else
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SOAD_SOCON_IP_SET_PORT_ANY & SOAD_SOCON_MASK_IPADDR));
    }
    if ( portIsAny == TRUE )
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) |
          (SOAD_SOCON_IP_ANY_PORT_ANY & SOAD_SOCON_MASK_PORT)));
    }
    else
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) |
          (SOAD_SOCON_IP_SET_PORT_SET & SOAD_SOCON_MASK_PORT)));
    }

    /* #50 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_SetRemoteAddrCheckAndSet() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrTcp(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set remote address if valid. */
  if ( SoAd_SoCon_SetRemoteAddrCheckAndSet(SoConIdx, RemoteAddrPtr) == E_OK )                                          /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #20 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_SetUniqueRemoteAddrTcp() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrUdp(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set remote address if valid. */
  if ( SoAd_SoCon_SetRemoteAddrCheckAndSet(SoConIdx, RemoteAddrPtr) == E_OK )                                          /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #20 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_SetUniqueRemoteAddrUdp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpen()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpen(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if module is initialized and not in shutdown state. */
  if ( SoAd_State == SOAD_STATE_INIT )
  {
    /* #20 Check if socket connection has automatic setup, is in reconnect state or is requested to be opened. */
    if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(soConGrpIdx) ||
      (SoAd_GetModeOfSoConDyn(SoConIdx) == SOAD_SOCON_RECONNECT) ||
      (SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx) > 0u) )
    {
      /* #200 Check if socket connection is not online yet and IP address is assigned. */
      if ( (SoAd_GetModeOfSoConDyn(SoConIdx) != SOAD_SOCON_ONLINE) &&
        (SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) == SOAD_IPADDR_STATE_ASSIGNED) )
      {
        /* #201 Try to open socket connection. */
        SoAd_SoCon_Open(SoConIdx);
      }
    }
    /* #21 Check if socket shall be opened to enable socket connection open on reception otherwise. */
    else
    {
      SoAd_SoCon_CheckAndOpenSocketForOpenOnReception(SoConIdx);
    }
  }
} /* SoAd_SoCon_CheckAndOpen() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpenSocketForOpenOnReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpenSocketForOpenOnReception(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP is assigned, socket is not yet opened and protocol type is UDP. */
  if ( (SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) == SOAD_IPADDR_STATE_ASSIGNED) &&
    (SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CLOSED) &&
    SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
  {
    /* #20 Check if message acceptance filter is enabled and UDP listen only is disabled. */
    if ( SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(soConGrpIdx) &&
      !SoAd_IsUdpListenOnlyOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
    {
      /* #30 Check if configured remote address contains wildcards. */
      if ( (SoAd_GetRemAddrStateOfSoCon(SoConIdx) <= SOAD_SOCON_IP_ANY_PORT_ANY) &&
        ((SoAd_GetRemAddrStateOfSoCon(SoConIdx) & SOAD_SOCON_MASK_ANY) != 0u) )
      {
        /* #40 Try to open socket and indicate to retry in next main function if no socket can be assigned. */
        if ( SoAd_SoCon_OpenSocketUdp(SoConIdx) == E_NOT_OK )
        {
          SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
        }
      }
    }
  }
} /* SoAd_SoCon_CheckAndOpenSocketForOpenOnReception() */

/**********************************************************************************************************************
 *  SoAd_SoCon_Open()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Open(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Handle socket connection open sequence for TCP (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) )
  {
    /* #20 Handle socket connection open sequence for TCP client. */
    if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
    {
      /* #200 Open TCP client socket. */
      if ( SoAd_SoCon_OpenSocketTcpClient(SoConIdx) == E_OK )
      {
        /* #2000 Handle TCP socket connection state for TCP client. */
        SoAd_SoCon_OpenSoConTcp(SoConIdx);
      }
    }
    /* #30 Handle socket connection open sequence for TCP server. */
    else
    {
      /* #300 Open TCP server (i.e. listen) socket. */
      if ( SoAd_SoCon_OpenSocketTcpServer(SoConIdx) == E_OK )
      {
        /* #3000 Handle TCP socket connection state for TCP server. */
        SoAd_SoCon_OpenSoConTcp(SoConIdx);
      }
    }
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #40 Handle socket connection open sequence for UDP (if enabled). */
  {
    /* #400 Open UDP socket. */
    if ( SoAd_SoCon_OpenSocketUdp(SoConIdx) == E_OK )
    {
      /* #4000 Open UDP socket connection. */
      SoAd_SoCon_OpenSoConUdp(SoConIdx);
    }
  }
} /* SoAd_SoCon_Open() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketUdp()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketUdp(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SocketIdType         socketId = SOAD_INV_SOCKET_ID;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if no socket is assigned. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    /* #20 Get socket. */
    if ( SoAd_TcpIp_GetSocket(SoConIdx, SoAd_GetDomainOfLocalAddr(localAddrIdx), SOAD_IPPROTO_UDP, &socketId) == E_OK )/* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Change parameter on socket. */
      if ( SoAd_SoCon_UdpChangeParameter(SoConIdx, socketId) == E_OK )
      {
        SoAd_PortType localPort = (SoAd_PortType)IPBASE_HTON16(SoAd_SoCon_GetLocalPortDyn(sockIdx));

        /* #40 Set socket identifier before it may be reset due to interrupts. */
        SoAd_SetSocketIdOfSocketDyn(sockIdx, socketId);                                                                /* SBSW_SOAD_PARAMETER_IDX */

        /* #50 Bind socket. */
        if ( SoAd_TcpIp_Bind(SoConIdx, socketId, &localPort) == E_OK )                                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        {
          /* #60 Assign socket and update state. */
          retVal = SoAd_SoCon_AssignSocketUdp(sockIdx, localPort);
        }
      }

      /* #70 Close socket if any error occurred. */
      if ( retVal == E_NOT_OK )
      {
        SoAd_TcpIp_Close(socketId, FALSE, sockIdx);
      }
    }
  }
  else
  {
    retVal = E_OK;
  }

  /* #80 If no socket is assigned set event to handle socket connection state in main function again. */
  if ( retVal == E_NOT_OK )
  {
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketUdp() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  SoAd_SoCon_AssignSocketUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_AssignSocketUdp(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket state is overwritten by any function call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Assign socket and update local port and state in case of a valid socket identifier. */
  if ( SoAd_GetSocketIdOfSocketDyn(SockIdx) != SOAD_INV_SOCKET_ID )
  {
    SoAd_SoCon_SetLocalPortDyn(SockIdx, (SoAd_PortType)IPBASE_HTON16(LocalPort));
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_ESTABLISHED);                                                    /* SBSW_SOAD_CSL03_CSL02 */
    SoAd_SoCon_OpenSocks++;

    retVal = E_OK;
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_AssignSocketUdp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConUdp()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConUdp(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if remote address is set or UDP listen only is configured. */
  if ( (SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) == SOAD_SOCON_IP_SET_PORT_SET) ||
    SoAd_IsUdpListenOnlyOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
  {
    /* #20 Set socket connection to online. */
    SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_ONLINE);                                                               /* SBSW_SOAD_PARAMETER_IDX */

    /* #30 Trigger address resolution if remote address is set. */
    if ( SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) == SOAD_SOCON_IP_SET_PORT_SET )
    {
      SoAd_TcpIp_TriggerAddressResolution(SoConIdx);
    }

    /* #40 Notify user about socket connection state change. */
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, SoAd_GetModeOfSoConDyn(SoConIdx));

    /* #50 Start TP sessions by calling StartOfReception if required. */
    (void)SoAd_Rx_TpStartOfReception(SoConIdx);
  }
  /* #11 Set socket connection state to reconnect and notify user about state change (if not done before) otherwise. */
  else
  {
    if ( SoAd_GetModeOfSoConDyn(SoConIdx) != SOAD_SOCON_RECONNECT )
    {
      SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT);                                                          /* SBSW_SOAD_PARAMETER_IDX */

      SoAd_SoCon_NotifySoConModeChg(SoConIdx, SoAd_GetModeOfSoConDyn(SoConIdx));
    }
  }
} /* SoAd_SoCon_OpenSoConUdp() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClient()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClient(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if no socket is assigned and remote address is set. */
  if ( (SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CLOSED) &&
    (SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) == SOAD_SOCON_IP_SET_PORT_SET) )
  {
    /* #20 Try to get and connect socket. */
    retVal = SoAd_SoCon_OpenSocketTcpClientGetAndConnect(SoConIdx, sockIdx);

    /* #30 If no socket is assigned set event to handle socket connection state in main function again. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpClient() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientGetAndConnect()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientGetAndConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIdType         socketId = SOAD_INV_SOCKET_ID;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get socket. */
  if ( SoAd_TcpIp_GetSocket(SoConIdx, SoAd_GetDomainOfLocalAddr(localAddrIdx), SOAD_IPPROTO_TCP, &socketId) == E_OK )  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* #20 Change parameter on socket. */
    if ( SoAd_SoCon_TcpChangeParameter(SoConIdx, socketId) == E_OK )
    {
      SoAd_PortType localPort = (SoAd_PortType)IPBASE_HTON16(SoAd_SoCon_GetLocalPortDyn(SockIdx));

      /* #30 Set socket identifier before it may be reset due to interrupts. */
      SoAd_SetSocketIdOfSocketDyn(SockIdx, socketId);                                                                  /* SBSW_SOAD_PARAMETER_IDX */

      /* #40 Bind socket. */
      if ( SoAd_TcpIp_Bind(SoConIdx, socketId, &localPort) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      {
        /* #50 Start connect and assign socket. */
        retVal = SoAd_SoCon_OpenSocketTcpClientConnect(SoConIdx, SockIdx, socketId, localPort);
      }
    }

    /* #60 Close socket if any error occurred. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_TcpIp_Close(socketId, FALSE, SockIdx);
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpClientGetAndConnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientConnect()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Start connect. */
  /* PRQA S 310 2 */ /* MD_SoAd_PointerCastOnStruct */
  if ( SoAd_TcpIp_TcpConnect(SoConIdx, SocketId,                                                                       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL02 */
      SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx)) == E_OK )
  {
    /* #20 Enter critical section to prevent that socket state is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Assign socket and update local port and state in case of a valid socket identifier. */
    if ( SoAd_GetSocketIdOfSocketDyn(SockIdx) != SOAD_INV_SOCKET_ID )
    {
      SoAd_SoCon_SetLocalPortDyn(SockIdx, (SoAd_PortType)IPBASE_HTON16(LocalPort));
      SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CONNECT);                                                      /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_SoCon_OpenSocks++;

      retVal = E_OK;
    }

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpClientConnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServer(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to Safe BSW assumption SoConGrp -> Socket. */
  SoAd_SizeOfSocketType listenSockIdx = SoAd_GetSocketIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));
  Std_ReturnType        retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if no listen socket is assigned. */
  if ( SoAd_GetStateOfSocketDyn(listenSockIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    /* #20 Try to get socket and start listening. */
    retVal = SoAd_SoCon_OpenSocketTcpServerGetAndListen(SoConIdx, listenSockIdx);

    /* #30 If no socket is assigned set event to handle socket connection state in main function again. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
    }
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpServer() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerGetAndListen()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerGetAndListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType ListenSockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIdType         socketId = SOAD_INV_SOCKET_ID;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get socket. */
  if ( SoAd_TcpIp_GetSocket(SoConIdx, SoAd_GetDomainOfLocalAddr(localAddrIdx), SOAD_IPPROTO_TCP, &socketId) == E_OK )  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* #20 Change parameter on socket. */
    if ( SoAd_SoCon_TcpChangeParameter(SoConIdx, socketId) == E_OK )
    {
      SoAd_PortType localPort = (SoAd_PortType)IPBASE_HTON16(SoAd_SoCon_GetLocalPortDyn(ListenSockIdx));

      /* #30 Set socket identifier before it may be reset due to interrupts. */
      SoAd_SetSocketIdOfSocketDyn(ListenSockIdx, socketId);                                                            /* SBSW_SOAD_PARAMETER_IDX */

      /* #40 Bind socket. */
      if ( SoAd_TcpIp_Bind(SoConIdx, socketId, &localPort) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      {
        /* #50 Start listen and assign socket. */
        retVal = SoAd_SoCon_OpenSocketTcpServerListen(SoConIdx, ListenSockIdx, socketId, localPort);
      }
    }

    /* #60 Close socket if any error occurred. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_TcpIp_Close(socketId, FALSE, ListenSockIdx);
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpServerGetAndListen() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerListen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketType ListenSockIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Start listen. */
  /* PRQA S 4391 2 */ /* MD_SoAd_GenericWiderTypeCast */
  if ( SoAd_TcpIp_TcpListen(SoConIdx, SocketId,
      (uint16)(SoAd_GetSoConEndIdxOfSocket(ListenSockIdx) - SoAd_GetSoConStartIdxOfSocket(ListenSockIdx))) ==
    E_OK )
  {
    /* #20 Enter critical section to prevent that socket state is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Assign socket and update local port and state in case of a valid socket identifier. */
    if ( SoAd_GetSocketIdOfSocketDyn(ListenSockIdx) != SOAD_INV_SOCKET_ID )
    {
      SoAd_SoCon_SetLocalPortDyn(ListenSockIdx, (SoAd_PortType)IPBASE_HTON16(LocalPort));
      SoAd_SetStateOfSocketDyn(ListenSockIdx, SOAD_SOCK_STATE_LISTEN);                                                 /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_SoCon_OpenSocks++;

      retVal = E_OK;
    }

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpServerListen() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConTcp(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection is already set to reconnect. */
  if ( SoAd_GetModeOfSoConDyn(SoConIdx) != SOAD_SOCON_RECONNECT )
  {
    /* #20 Set socket connection to reconnect. */
    SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT);                                                            /* SBSW_SOAD_PARAMETER_IDX */

    /* #30 Notify user about socket connection state change. */
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, SoAd_GetModeOfSoConDyn(SoConIdx));
  }
} /* SoAd_SoCon_OpenSoConTcp() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_Close()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Close(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConModeType  newSoConState;
  boolean             abortFlag = (boolean)SoAd_IsAbortOfSoConDyn(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get expected socket connection state after closing. */
  switch ( SoAd_GetCloseModeOfSoConDyn(SoConIdx) )
  {
    case SOAD_CLOSE_OFFLINE_RESET:
    case SOAD_CLOSE_OFFLINE:
    case SOAD_CLOSE_SOCKET:
    {
      newSoConState = SOAD_SOCON_OFFLINE;
      break;
    }
    default: /* SOAD_CLOSE_RECONNECT || SOAD_CLOSE_SOCKET_RECONNECT */
    {
      newSoConState = SOAD_SOCON_RECONNECT;
      break;
    }
  }

  /* #20 Check if expected socket connection state after closing is different to the current state. */
  if ( SoAd_GetModeOfSoConDyn(SoConIdx) != newSoConState )
  {
    /* #30 Set new socket connection state. */
    SoAd_SetModeOfSoConDyn(SoConIdx, newSoConState);                                                                   /* SBSW_SOAD_PARAMETER_IDX */

    /* #40 Close socket connection. */
    SoAd_SoCon_CloseSoCon(SoConIdx);

    /* #50 Notify user about socket connection state change. */
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, SoAd_GetModeOfSoConDyn(SoConIdx));
  }

  /* #60 Close related sockets. */
  SoAd_SoCon_CloseSocket(SoConIdx, abortFlag);

  /* #70 Reset socket connection close mode. */
  SoAd_SoCon_ResetCloseMode(SoConIdx);

  /* #80 Set event to handle socket connection state in main function. */
  SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
} /* SoAd_SoCon_Close() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSoCon()
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
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSoCon(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle socket connection close dependent on close mode. */
  switch ( SoAd_GetCloseModeOfSoConDyn(SoConIdx) )
  {
    /* #100 Check if socket connection shall be closed by normal close request. */
    case SOAD_CLOSE_OFFLINE:
    {
      /* #1000 Reset structs, remote address and terminate active TP sessions. */
      SoAd_SoCon_ResetSoCon(SoConIdx, TRUE, FALSE, TRUE);
      break;
    }
    /* #101 Check if socket connection shall be closed by special request (shutdown, API call failed, config issue). */
    case SOAD_CLOSE_OFFLINE_RESET:
    {
      /* #1010 Reset structs, remote address, open/close sequence and terminate active TP sessions negatively. */
      SoAd_SoCon_ResetSoCon(SoConIdx, TRUE, TRUE, FALSE);
      break;
    }
#if ( SOAD_TCP == STD_ON )
    /* #102 Check if socket connection shall be closed by socket close and TcpInitiate is true (if TCP is enabled). */
    case SOAD_CLOSE_SOCKET_RECONNECT:
    {
      /* #1020 Reset structs and terminate active TP sessions negatively. */
      SoAd_SoCon_ResetSoCon(SoConIdx, FALSE, FALSE, FALSE);
      break;
    }
#endif /* SOAD_TCP == STD_ON */
    /* #103 Close socket connection if socket is closed or requested to be reconnected otherwise. */
    default: /* SOAD_CLOSE_SOCKET || SOAD_CLOSE_RECONNECT */
    {
      /* #1030 Reset structs, remote address and terminate active TP sessions negatively. */
      SoAd_SoCon_ResetSoCon(SoConIdx, TRUE, FALSE, FALSE);
      break;
    }
  }
} /* SoAd_SoCon_CloseSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocket()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocket(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket is of type TCP. */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
  {
    /* #100 Close socket. */
    SoAd_SoCon_CloseSocketTcp(SoConIdx, Abort);

    /* #101 Handle listen socket close. */
    SoAd_SoCon_CloseSocketTcpListen(SoConIdx, Abort);
  }
  else
#endif /* SOAD_TCP == STD_ON */
    /* #20 Handle close if socket is of type UDP. */
  {
    SoAd_SoCon_CloseSocketUdp(SoConIdx, Abort);
  }

  /* #30 Reset number of data to be skipped on reception. */
  SoAd_SetSkipBytesOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), 0u);                                                /* SBSW_SOAD_PARAMETER_IDX */

} /* SoAd_SoCon_CloseSocket() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcp()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcp(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SocketIdType     socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket state is overwritten by any function call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Ignore close if socket is already closed. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    /* #200 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
  /* #21 Wait for socket close if socket is closing. */
  else if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CLOSING )
  {
    /* #210 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
  /* #22 Set socket to closing and call close service otherwise. */
  else
  {
    SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_CLOSING);                                                        /* SBSW_SOAD_CSL03_CSL02 */

    /* #220 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #221 Close socket. */
    SoAd_TcpIp_Close(socketId, Abort, sockIdx);
  }
} /* SoAd_SoCon_CloseSocketTcp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcpListen()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcpListen(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType   sockIdx;
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SocketIdType       socketId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket is a server socket. */
  if ( !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
  {
    /* #20 Get listen socket. */
    sockIdx = SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx);
    socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);

    /* #30 Enter critical section to prevent that socket state is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #40 Check if listen socket is in close or closing state. */
    if ( (SoAd_GetStateOfSocketDyn(sockIdx) != SOAD_SOCK_STATE_CLOSED) &&
      (SoAd_GetStateOfSocketDyn(sockIdx) != SOAD_SOCK_STATE_CLOSING) )
    {
      /* #50 Iterate over all socket connections of socket connection group. */
      SoAd_SoConIterType  soConIter;
      boolean             listenSocketRequired = FALSE;

      for ( soConIter = SoAd_GetSoConStartIdxOfSocket(sockIdx);
        soConIter < SoAd_GetSoConEndIdxOfSocket(sockIdx);
        soConIter++ )
      {
        /* #60 Check if socket connection still requires a listen socket. */
        if ( SoAd_GetModeOfSoConDyn(soConIter) != SOAD_SOCON_OFFLINE )
        {
          listenSocketRequired = TRUE;
          break;
        }
      }

      /* #70 Set socket to closing and call close service if no socket connection requires a listen socket. */
      if ( listenSocketRequired == FALSE )
      {
        SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_CLOSING);                                                    /* SBSW_SOAD_CSL03_CSL02 */

        /* #700 Leave critical section and call close service. */
        SOAD_END_CRITICAL_SECTION();

        /* #701 Close socket. */
        SoAd_TcpIp_Close(socketId, Abort, sockIdx);
      }
      /* #71 Otherwise leave critical section. */
      else
      {
        SOAD_END_CRITICAL_SECTION();
      }
    }
    /* #41 Otherwise leave critical section. */
    else
    {
      SOAD_END_CRITICAL_SECTION();
    }
  }
} /* SoAd_SoCon_CloseSocketTcpListen() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketUdp(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SoConIterType    soConIter;
  SoAd_SocketIdType     socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);
  boolean               socketRequired = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket is not yet closed. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #20 Iterate over all socket connections of socket connection group. */
    for ( soConIter = SoAd_GetSoConStartIdxOfSocket(sockIdx);
      soConIter < SoAd_GetSoConEndIdxOfSocket(sockIdx);
      soConIter++ )
    {
      /* #30 Check if socket connection still requires the shared socket. */
      if ( SoAd_GetModeOfSoConDyn(soConIter) != SOAD_SOCON_OFFLINE )
      {
        socketRequired = TRUE;
        break;
      }
    }

    /* #40 Close socket if shared socket is not required anymore and socket identifier is valid. */
    if ( (socketRequired == FALSE) && (socketId != SOAD_INV_SOCKET_ID) )
    {
      SoAd_TcpIp_Close(socketId, Abort, sockIdx);
    }
  }
} /* SoAd_SoCon_CloseSocketUdp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetCloseMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetCloseMode(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSocketType   sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
#endif /* SOAD_TCP == STD_ON */
  SoAd_SoConModeType      newSoConMode;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that close mode is overwritten by any function call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Get expected socket connection mode after closing. */
  switch ( SoAd_GetCloseModeOfSoConDyn(SoConIdx) )
  {
    case SOAD_CLOSE_OFFLINE_RESET:
    case SOAD_CLOSE_OFFLINE:
    case SOAD_CLOSE_SOCKET:
    {
      newSoConMode = SOAD_SOCON_OFFLINE;
      break;
    }
    default: /* SOAD_CLOSE_RECONNECT || SOAD_CLOSE_SOCKET_RECONNECT */
    {
      newSoConMode = SOAD_SOCON_RECONNECT;
      break;
    }
  }

  /* #30 Reset close mode if socket connection is in expected mode and socket is closed in case of TCP. */
  if ( (SoAd_GetModeOfSoConDyn(SoConIdx) == newSoConMode)
#if ( SOAD_TCP == STD_ON )
    && (SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx)
      || (SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CLOSED))
#endif /* SOAD_TCP == STD_ON */
    )
  {
    SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_NONE);                                                            /* SBSW_SOAD_PARAMETER_IDX */
  }

  /* #40 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_SoCon_ResetCloseMode() */

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifySoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifySoConModeChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SoConModeType Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConModeChgCbkIndIterType soConModeChgCbkIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call all socket connection related socket connection mode change notifications. */
  for ( soConModeChgCbkIndIter = SoAd_GetSoConModeChgCbkIndStartIdxOfSoCon(SoConIdx);
    soConModeChgCbkIndIter < SoAd_GetSoConModeChgCbkIndEndIdxOfSoCon(SoConIdx);
    soConModeChgCbkIndIter++ )
  {
    if ( SoAd_GetSoConModeChgCbk(SoAd_GetSoConModeChgCbkInd(soConModeChgCbkIndIter)) != NULL_PTR )
    {
      SoAd_GetSoConModeChgCbk(SoAd_GetSoConModeChgCbkInd(soConModeChgCbkIndIter))(                                     /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetSoConIdOfSoCon(SoConIdx), Mode);
    }
  }
} /* SoAd_SoCon_NotifySoConModeChg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifyLocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifyLocalIpAddrAssignmentChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrStateType State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_LocalIpAddrAssignmentChgCbkIndIterType localIpAddrAssignmentChgCbkIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call all socket connection related socket connection local IP address assignment change notifications. */
  for ( localIpAddrAssignmentChgCbkIndIter = SoAd_GetLocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon(SoConIdx);
    localIpAddrAssignmentChgCbkIndIter < SoAd_GetLocalIpAddrAssignmentChgCbkIndEndIdxOfSoCon(SoConIdx);
    localIpAddrAssignmentChgCbkIndIter++ )
  {
    if ( SoAd_GetLocalIpAddrAssignmentChgCbk(
      SoAd_GetLocalIpAddrAssignmentChgCbkInd(localIpAddrAssignmentChgCbkIndIter)) != NULL_PTR )
    {
      SoAd_GetLocalIpAddrAssignmentChgCbk(SoAd_GetLocalIpAddrAssignmentChgCbkInd(localIpAddrAssignmentChgCbkIndIter))( /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetSoConIdOfSoCon(SoConIdx), State);
    }
  }
} /* SoAd_SoCon_NotifyLocalIpAddrAssignmentChg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetLocalPortDyn()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConStartIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConStartIdx);

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Reset local port on listen socket in case of TCP server socket (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) &&
    !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
  {
    /* Optional indirection: Refer to Safe BSW assumption SoConGrp -> Socket. */
    SoAd_SizeOfSocketType grpSockIdx = SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx);
    SoAd_SoConIterType    soConIter;
    SoAd_ReturnType       retVal = E_OK;

    /* #100 Check if listen socket is closed. */
    if ( SoAd_GetStateOfSocketDyn(grpSockIdx) == SOAD_SOCK_STATE_CLOSED )
    {
      /* #1000 Check if all data sockets are closed and indicate that local port cannot be reset if not. */
      for ( soConIter = SoAd_GetSoConStartIdxOfSocket(grpSockIdx);
        soConIter < SoAd_GetSoConEndIdxOfSocket(grpSockIdx);
        soConIter++ )
      {
        if ( SoAd_GetStateOfSocketDyn(SoAd_GetSocketIdxOfSoCon(soConIter)) != SOAD_SOCK_STATE_CLOSED )
        {
          retVal = E_NOT_OK;
          break;
        }
      }
    }
    /* #101 Indicate that local port cannot be reset otherwise. */
    else
    {
      retVal = E_NOT_OK;
    }

    /* #102 Reset local port on listen socket to configured value if all sockets are closed. */
    if ( retVal == E_OK )
    {
      SoAd_SetLocalPortOfSocketDyn(grpSockIdx, SoAd_GetLocalPortOfSoConGrp(soConGrpIdx));                              /* SBSW_SOAD_OPTIONAL_CSL03 */
    }
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Reset local port on data socket to configured value otherwise. */
  {
    SoAd_SetLocalPortOfSocketDyn(SockIdx, SoAd_GetLocalPortOfSoConGrp(soConGrpIdx));                                   /* SBSW_SOAD_PARAMETER_IDX */
  }
} /* SoAd_SoCon_ResetLocalPortDyn() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetSoCon()
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
/* PRQA S 3206 5 */ /* MD_SoAd_UnusedParameter */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  boolean ResetRemAddr,
  boolean ResetOpClSeq,
  boolean NormalClose)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset remote address if required. */
#if ( SOAD_TCP == STD_ON )
  if ( ResetRemAddr == TRUE )
#else
  SOAD_DUMMY_STATEMENT(ResetRemAddr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_TCP == STD_ON */
  {
    SoAd_SoCon_ResetRemAndRcvRemAddr(SoConIdx);
  }

  /* #20 Reset open/close sequence if required. */
  if ( ResetOpClSeq == TRUE )
  {
    SoAd_SetOpenCloseCounterOfSoConDyn(SoConIdx, 0u);                                                                  /* SBSW_SOAD_PARAMETER_IDX */
  }

  /* #30 Reset abort flag. */
  SoAd_SetAbortOfSoConDyn(SoConIdx, FALSE);                                                                            /* SBSW_SOAD_PARAMETER_IDX */

  /* #40 Terminate active transmissions. */
  if ( SoAd_IsTxMgtUsedOfSoCon(SoConIdx) )
  {
    SoAd_Tx_TerminateTransmit(SoConIdx);
  }

  /* #50 Terminate active receptions. */
  if ( SoAd_IsRxMgtUsedOfSoCon(SoConIdx) )
  {
    SoAd_Rx_TerminateReceive(SoConIdx, NormalClose);
  }

  /* #60 Reset alive supervision timeout. */
#if ( SOAD_TCP == STD_ON )
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
#endif /* SOAD_TCP == STD_ON */
  {
    if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) > 0u )
    {
      SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx);
    }
  }
} /* SoAd_SoCon_ResetSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAndRcvRemAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAndRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset remote address. */
  SoAd_SoCon_ResetRemAddr(SoConIdx);

  /* #20 Reset received remote address (if enabled). */
  SoAd_SoCon_ResetRcvRemAddr(SoConIdx);
} /* SoAd_SoCon_ResetRemAndRcvRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAddr(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType sockAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset remote address to configured remote address. */
#if ( SOAD_IPV6 == STD_ON )
  if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))) ==
    SOAD_AF_INET6 )
  {
    /* PRQA S 759 1 */ /* MD_MSR_Union */
    SoAd_IpAddrInet6Type remAddrIpV6;

    remAddrIpV6 = SoAd_GetAddrOfRemAddrIpV6(SoAd_GetRemAddrIpV6IdxOfSoCon(SoConIdx));

    /* PRQA S 2983 2 */ /* MD_SoAd_UsageNotDetected */
    sockAddr.domain   = SOAD_AF_INET6;
    sockAddr.port     = SoAd_GetPortOfRemAddrIpV6(SoAd_GetRemAddrIpV6IdxOfSoCon(SoConIdx));
    sockAddr.addr[0u] = remAddrIpV6.addr32[0u];                                                                        /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    sockAddr.addr[1u] = remAddrIpV6.addr32[1u];                                                                        /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    sockAddr.addr[2u] = remAddrIpV6.addr32[2u];                                                                        /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    sockAddr.addr[3u] = remAddrIpV6.addr32[3u];                                                                        /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
  }
  else
#endif /* SOAD_IPV6 == STD_ON */
  {
    /* PRQA S 2983 2 */ /* MD_SoAd_UsageNotDetected */
    sockAddr.domain   = SOAD_AF_INET;
    sockAddr.port     = SoAd_GetPortOfRemAddrIpV4(SoAd_GetRemAddrIpV4IdxOfSoCon(SoConIdx));
    sockAddr.addr[0u] = SoAd_GetAddrOfRemAddrIpV4(SoAd_GetRemAddrIpV4IdxOfSoCon(SoConIdx));                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
  }

  /* PRQA S 310 2 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx),                    /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */
    SOAD_A_P2CONST(SoAd_SockAddrType)&sockAddr);

  /* #20 Reset remote address state to configured remote address state. */
  SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx, SoAd_GetRemAddrStateOfSoCon(SoConIdx));                                  /* SBSW_SOAD_PARAMETER_IDX */
} /* SoAd_SoCon_ResetRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRcvRemAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType  rcvRemAddr;
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_DomainType         domainLocalAddr = SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if received remote address is configured. */
  if ( SoAd_IsRcvRemAddrUsedOfSoCon(SoConIdx) )
  {
    /* #20 Reset received remote address. */
    /* PRQA S 2983 2 */ /* MD_SoAd_UsageNotDetected */
    rcvRemAddr.domain = domainLocalAddr;
    rcvRemAddr.port = SOAD_PORT_ANY;
#if ( SOAD_IPV6 == STD_ON )
    if ( domainLocalAddr == SOAD_AF_INET6 )
    {
      rcvRemAddr.addr[0u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[1u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[2u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[3u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    }
    else
#endif /* SOAD_IPV6 == STD_ON */
    {
      rcvRemAddr.addr[0u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
#if ( SOAD_IPV6 == STD_ON )
      rcvRemAddr.addr[1u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[2u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[3u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
#endif /* SOAD_IPV6 == STD_ON */
    }

    SoAd_SetRcvRemAddr(SoAd_GetRcvRemAddrIdxOfSoCon(SoConIdx), rcvRemAddr);                                            /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
  }
} /* SoAd_SoCon_ResetRcvRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_IsTxActive()
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
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_IsTxActive(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isTxActive;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for pending IF/TP transmission. */
  if ( SoAd_IsTxMgtUsedOfSoCon(SoConIdx) &&
    (SoAd_GetPduRouteDestIdxOfTxMgt(SoAd_GetTxMgtIdxOfSoCon(SoConIdx)) != SoAd_GetSizeOfPduRouteDest()) )
  {
    isTxActive = TRUE;
  }
  /* #20 Check for pending nPdu transmission. */
  else if ( SoAd_IsNPduUdpTxUsedOfSoCon(SoConIdx) &&
    (SoAd_GetTotalLenOfNPduUdpTxDyn(SoAd_GetNPduUdpTxIdxOfSoCon(SoConIdx)) > 0u) )
  {
    /* #200 Update timeout to send nPdu immediately in next main function. */
    (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU,
      SoAd_GetNPduUdpTxIdxOfSoCon(SoConIdx), 1u, SoAd_GlobalCounter);

    isTxActive = TRUE;
  }
  /* #30 Check for pending routing group transmission. */
  else if ( SoAd_SoCon_IsTxRouteGrpActive(SoConIdx) == TRUE )
  {
    isTxActive = TRUE;
  }
  /* #40 Indicate that no transmission is active otherwise. */
  else
  {
    isTxActive = FALSE;
  }

  return isTxActive;
} /* SoAd_SoCon_IsTxActive() */

/**********************************************************************************************************************
 *  SoAd_SoCon_IsTxRouteGrpActive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_IsTxRouteGrpActive(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestBySoConIndIterType         pduRouteDestBySoConIndIter;
  SoAd_RouteGrpSoConByPduRouteDestIndIterType routeGrpSoConByPduRouteDestIndIter;
  SoAd_SizeOfPduRouteDestType                 pduRouteDestIdx;
  SoAd_SizeOfRouteGrpSoConType                routeGrpSoConIdx;
  boolean                                     isTxActive = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all PduRouteDests. */
  for ( pduRouteDestBySoConIndIter = SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(SoConIdx);
    pduRouteDestBySoConIndIter < SoAd_GetPduRouteDestBySoConIndEndIdxOfSoCon(SoConIdx);
    pduRouteDestBySoConIndIter++ )
  {
    pduRouteDestIdx = SoAd_GetPduRouteDestBySoConInd(pduRouteDestBySoConIndIter);

    /* #20 Iterate over all PduRouteDest related routing group states. */
    for ( routeGrpSoConByPduRouteDestIndIter =
        SoAd_GetRouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest(pduRouteDestIdx);
      routeGrpSoConByPduRouteDestIndIter <
        SoAd_GetRouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDest(pduRouteDestIdx);
      routeGrpSoConByPduRouteDestIndIter++ )
    {
      routeGrpSoConIdx = SoAd_GetRouteGrpSoConByPduRouteDestInd(routeGrpSoConByPduRouteDestIndIter);

      /* #30 Check if routing group transmission is active. */
      if ( SoAd_IsTriggerOfRouteGrpSoConDyn(routeGrpSoConIdx) )
      {
        /* #40 Return that transmission is active. */
        isTxActive = TRUE;
        break;
      }
    }
    if ( isTxActive == TRUE )
    {
      break;
    }
  }

  return isTxActive;
} /* SoAd_SoCon_IsTxRouteGrpActive() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdx(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_BestMatchPrioType bestMachPrio = SOAD_BEST_MATCH_NONE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if remote address has no "not set" values. */
  if ( (SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) & SOAD_SOCON_MASK_NOT) == 0u )
  {
#if ( SOAD_IPV6 == STD_ON )
    /* #20 Check remote address in case of IPv6 (if enabled). */
    if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))) ==
      SOAD_AF_INET6 )
    {
      /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
      bestMachPrio = SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6(SoConIdx,
        SOAD_A_P2CONST(SoAd_SockAddrInet6Type)SockAddrPtr);                                                            /* SBSW_SOAD_POINTER_FORWARD */
    }
    else
#endif /* SOAD_IPV6 == STD_ON */
    /* #30 Check remote address in case of IPv4. */
    {
      /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
      bestMachPrio = SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4(SoConIdx,
        SOAD_A_P2CONST(SoAd_SockAddrInetType)SockAddrPtr);                                                             /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  return bestMachPrio;
} /* SoAd_SoCon_GetBestMatchPrioOfSoConIdx() */

#if ( SOAD_IPV6 == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 310, 3305 4 */ /* MD_SoAd_PointerCastOnStruct */
  uint8_least             addrIdx;
  uint16                  dynPort = SockAddrPtr->port;
  SoAd_BestMatchPrioType  bestMachPrio = SOAD_BEST_MATCH_NONE;
  boolean                 ipIsEqual = TRUE;
  boolean                 ipIsWildcard = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP address is equal. */
  for ( addrIdx = 0u; addrIdx < SOAD_IPV6_ADDR_LEN_32; addrIdx++ )
  {
    /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
    if ( SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).addr[addrIdx] != SockAddrPtr->addr[addrIdx] )
    {
      ipIsEqual = FALSE;
      break;
    }
  }

  /* #20 Check if IP address is wildcard. */
  for ( addrIdx = 0u; addrIdx < SOAD_IPV6_ADDR_LEN_32; addrIdx++ )
  {
    if ( SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).addr[addrIdx] != SOAD_IP6ADDR_ANY )
    {
      ipIsWildcard = FALSE;
      break;
    }
  }

  /* #30 Calculate best match priority. */
  if ( (ipIsEqual == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_MATCH;
  }
  else if ( (ipIsEqual == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == SOAD_PORT_ANY) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_ANY;
  }
  else if ( (ipIsWildcard == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_MATCH;
  }
  else if ( (ipIsWildcard == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == SOAD_PORT_ANY) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_ANY;
  }
  else
  {
    /* Nothing to do. */
  }

  return bestMachPrio;
} /* SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6() */
#endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrInetType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_IpAddrInetType     dynAddr = SockAddrPtr->addr[0];
  SoAd_PortType           dynPort = SockAddrPtr->port;
  SoAd_BestMatchPrioType  bestMachPrio = SOAD_BEST_MATCH_NONE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate best match priority. */
  if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).addr[0] == dynAddr) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_MATCH;
  }
  else if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).addr[0] == dynAddr) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == SOAD_PORT_ANY) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_ANY;
  }
  else if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).addr[0] == SOAD_IPADDR_ANY) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_MATCH;
  }
  else if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).addr[0] == SOAD_IPADDR_ANY) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx).port == SOAD_PORT_ANY))
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_ANY;
  }
  else
  {
    /* Nothing to do. */
  }

  return bestMachPrio;
} /* SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUdpAliveTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_SetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketUdpType socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if alive supervision timeout is configured. */
  if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(socketUdpIdx) != 0u )
  {
    /* #20 Set alive supervision timeout. */
    (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_UDP_ALIVE,
      SoConIdx, SoAd_GetAliveTimeoutMaxCntOfSocketUdp(socketUdpIdx), SoAd_GlobalCounter);
  }
} /* SoAd_SoCon_SetUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetUdpAliveTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketUdpType socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if alive supervision timeout is configured. */
  if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(socketUdpIdx) != 0u )
  {
    /* #20 Remove alive supervision timeout from timeout list. */
    SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx);
  }
} /* SoAd_SoCon_ResetUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_DecrementOpenSockets()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_DecrementOpenSockets(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if at least one socket is opened. */
  if ( SoAd_SoCon_OpenSocks > 0u )
  {
    /* #20 Decrement number of open sockets. */
    SoAd_SoCon_OpenSocks--;
  }
} /* SoAd_SoCon_DecrementOpenSockets() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_SoCon_InitLocalAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_InitLocalAddr(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_LocalAddrIterType localAddrIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all local addresses. */
  for ( localAddrIter = 0u; localAddrIter < SoAd_GetSizeOfLocalAddr(); localAddrIter++ )
  {
    /* #20 Initialize IP address assignment state. */
    SoAd_SetIpAddrStateOfLocalAddrDyn(localAddrIter, SOAD_IPADDR_STATE_UNASSIGNED);                                    /* SBSW_SOAD_CSL02 */
  }
} /* SoAd_SoCon_InitLocalAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_InitSoCon()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_InitSoCon(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType soConIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket connection indexes. */
  for ( soConIter = 0u; soConIter < SoAd_GetSizeOfSoCon(); soConIter++ )
  {
    /* #20 Initialize general struct elements. */
    SoAd_SetModeOfSoConDyn(soConIter, SOAD_SOCON_OFFLINE);                                                             /* SBSW_SOAD_CSL02 */
    SoAd_SetAbortOfSoConDyn(soConIter, FALSE);                                                                         /* SBSW_SOAD_CSL02 */
    SoAd_SetCloseModeOfSoConDyn(soConIter, SOAD_CLOSE_NONE);                                                           /* SBSW_SOAD_CSL02 */
    SoAd_SetOpenCloseCounterOfSoConDyn(soConIter, 0u);                                                                 /* SBSW_SOAD_CSL02 */

    SoAd_SoCon_ResetRemAndRcvRemAddr((SoAd_SizeOfSoConType)soConIter);

    /* #30 Initialize tx struct elements. */
    SoAd_Tx_InitSoCon((SoAd_SizeOfSoConType)soConIter);

    /* #40 Initialize rx struct elements. */
    SoAd_Rx_InitSoCon((SoAd_SizeOfSoConType)soConIter);
  }
} /* SoAd_SoCon_InitSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_InitSocket()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_InitSocket(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIterType sockIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all module internal socket indexes. */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(); sockIter++ )
  {
    /* #20 Initialize general struct elements. */
    SoAd_SetStateOfSocketDyn(sockIter, SOAD_SOCK_STATE_CLOSED);                                                        /* SBSW_SOAD_CSL02 */
    SoAd_SetSocketIdOfSocketDyn(sockIter, SOAD_INV_SOCKET_ID);                                                         /* SBSW_SOAD_CSL02 */
    SoAd_SoCon_ResetLocalPortDyn((SoAd_SizeOfSocketType)sockIter);

    /* #30 Initialize tx struct elements. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIter, SoAd_GetSizeOfSoCon());                                              /* SBSW_SOAD_CSL02 */

    /* #40 Initialize rx struct elements. */
    SoAd_SetSkipBytesOfSocketDyn(sockIter, 0u);                                                                        /* SBSW_SOAD_CSL02 */
  }

  /* #50 Initialize the number of open sockets. */
  SoAd_SoCon_OpenSocks = 0u;
} /* SoAd_SoCon_InitSocket() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetSockIdxBySocketId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_GetSockIdxBySocketId(
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_SizeOfSocketType, AUTOMATIC, SOAD_APPL_DATA) SockIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIterType sockIter;
  Std_ReturnType      retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket indexes. */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(); sockIter++ )
  {
    /* #20 Check if specified socket identifier is related to the socket index. */
    if ( SocketId == SoAd_GetSocketIdOfSocketDyn(sockIter) )
    {
      /* #30 Return socket index and stop iteration. */
      *SockIdxPtr = (SoAd_SizeOfSocketType)sockIter;                                                                   /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* SoAd_SoCon_GetSockIdxBySocketId() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAccepted()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAccepted(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketIdConnected,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConType  soConIdxAccepted = SoAd_GetSizeOfSoCon();
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check listen socket state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx) == SOAD_SOCK_STATE_LISTEN )
  {
    /* #20 Check if a suitable socket connection can be found. */
    if ( SoAd_SoCon_TcpAcceptedGetSoConIdx(soConIdx, RemoteAddrPtr, &soConIdxAccepted) == E_OK )                       /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Check if socket connection accepts connection. */
      retVal = SoAd_SoCon_TcpAcceptedCheckAcceptance(soConIdxAccepted, SocketIdConnected, RemoteAddrPtr);              /* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #21 Increment dropped TCP connection counter otherwise. */
    else
    {
# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
      SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP_CONNECTION, 1);
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpAccepted() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAcceptedGetSoConIdx()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAcceptedGetSoConIdx(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdxListSize = 0u;
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check is message acceptance filter is enabled. */
  if ( SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
  {
    /* #100 Enter critical section to prevent that socket connections of group changes states or remote address. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #101 Check if best match algortihm can find a suitable socket connection. */
    if ( SoAd_SoCon_GetSoConIdxListByBestMatchAlg(SoConIdx, SOAD_SOCON_FILTER_ON_OFF, RemoteAddrPtr,                   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      &soConIdxListSize) == E_OK )
    {
      /* #102 Return first matching socket connection. */
      *SoConIdxPtr = SoAd_GetSoConIdxOfBestMatchSoConIdxList(0u);                                                      /* SBSW_SOAD_POINTER_WRITE */

      retVal = E_OK;
    }

    /* #104 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
  /* #11 Check acceptance on single socket connection otherwise. */
  else
  {
    /* #110 Check socket connection state. */
    if ( SoAd_GetModeOfSoConDyn(SoConIdx) == SOAD_SOCON_RECONNECT )
    {
      *SoConIdxPtr = SoConIdx;                                                                                         /* SBSW_SOAD_POINTER_WRITE */

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpAcceptedGetSoConIdx() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpConnected()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_TcpConnected(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSocketType sockIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if socket is in connected state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx) == SOAD_SOCK_STATE_CONNECT )
  {
    /* #200 Check if socket connection is still requested to be opened. */
    if ( (SoAd_GetOpenCloseCounterOfSoConDyn(soConIdx) > 0u) ||
      SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) )
    {
      /* #2000 Check if socket connection mode is not online. */
      if ( SoAd_GetModeOfSoConDyn(soConIdx) != SOAD_SOCON_ONLINE )
      {
        /* #20000 Change socket state and socket connection mode. */
        sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx);
        SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_ESTABLISHED);                                                /* SBSW_SOAD_CSL03_CSL02 */
        SoAd_SetModeOfSoConDyn(soConIdx, SOAD_SOCON_ONLINE);                                                           /* SBSW_SOAD_PARAMETER_IDX */

        /* #20001 Leave critical section. */
        SOAD_END_CRITICAL_SECTION();

        /* #20002 Notify user about state change. */
        SoAd_SoCon_NotifySoConModeChg(soConIdx, SoAd_GetModeOfSoConDyn(soConIdx));

        /* #20003 Try to start TP reception if required. */
        (void)SoAd_Rx_TpStartOfReception(soConIdx);
      }
      /* #2001 Otherwise leave critical section. */
      else
      {
        SOAD_END_CRITICAL_SECTION();
      }
    }
    /* #210 Otherwise leave critical section. */
    else
    {
      SOAD_END_CRITICAL_SECTION();
    }
  }
  /* #21 Otherwise leave critical section. */
  else
  {
    SOAD_END_CRITICAL_SECTION();
  }
} /* SoAd_SoCon_TcpConnected() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameter()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx);
  uint32                    tcpTxBufMin = SoAd_GetTcpTxBufMinOfSocketTcp(socketTcpIdx);
  uint32                    tcpRxBufMin = SoAd_GetTcpRxBufMinOfSocketTcp(socketTcpIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set frame priority. */
  if ( SoAd_GetFramePriorityOfSoConGrp(soConGrpIdx) != SOAD_NO_FRAMEPRIORITYOFSOCONGRP )
  {
    uint8 framePriority = SoAd_GetFramePriorityOfSoConGrp(soConGrpIdx);

    retVal = SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_FRAMEPRIO, &framePriority);                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #20 Set rx buffer size. */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnParam */
  retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_RXWND_MAX, (uint8*)&tcpRxBufMin);          /* SBSW_SOAD_CAST_POINTER_FORWARD */

  /* #30 Set tx buffer size. */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnParam */
  retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_TCP_TXWND_MAX, (uint8*)&tcpTxBufMin);          /* SBSW_SOAD_CAST_POINTER_FORWARD */

  /* #40 Set no delay (Nagle algorithm). */
  retVal |= SoAd_SoCon_TcpChangeParameterNoDelay(SoConIdx, SocketId);

  /* #50 Set keep alive. */
  retVal |= SoAd_SoCon_TcpChangeParameterKeepAlive(SoConIdx, SocketId);

  /* #60 Set TLS. */
  retVal |= SoAd_SoCon_TcpChangeParameterTls(SoConIdx, SocketId);

  /* #70 Set stack (Socket API) specific parameters. */
  retVal |= SoAd_TcpIp_ChangeParameter(SoConIdx, SocketId, SOAD_PARAMID_STACK_SPECIFIC, NULL_PTR);                     /* SBSW_SOAD_NULL_POINTER_FORWARD */

  return retVal;
} /* SoAd_SoCon_TcpChangeParameter() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_Event()
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
/* PRQA S 3206 3 */ /* MD_SoAd_UnusedParameter */
FUNC(void, SOAD_CODE) SoAd_SoCon_Event(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_EventType Event)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Handle socket dependent of Event type (if TCP is enabled). */
  switch ( Event )
  {
    /* #100 Handle event of UDP close. */
    case SOAD_UDP_CLOSED:
    {
      SoAd_SoCon_EventUdpClose(SockIdx);
      break;
    }
    /* #101 Handle event of TCP close or reset. */
    case SOAD_TCP_RESET:
    case SOAD_TCP_CLOSED:
    {
      SoAd_SoCon_EventTcpClose(SockIdx);
      break;
    }
    /* #102 Handle event of TCP FIN received. */
    default:
    { /* SOAD_TCP_FIN_RECEIVED */
      SoAd_SoCon_EventTcpFinReceived(SockIdx);
      break;
    }
  }
#else
  /* #11 Handle event of UDP close (otherwise). */
  SoAd_SoCon_EventUdpClose(SockIdx);

  SOAD_DUMMY_STATEMENT(Event); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_TCP == STD_ON */
} /* SoAd_SoCon_Event() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  boolean         hasSoConModeChanged = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection states allow to set remote address. */
  if ( SoAd_SoCon_SetRemoteAddrCheckStates(SoConIdx) == E_OK )
  {
    /* #20 Check and set remote address if valid. */
    if ( SoAd_SoCon_SetRemoteAddrCheckAndSet(SoConIdx, RemoteAddrPtr) == E_OK )                                        /* SBSW_SOAD_POINTER_FORWARD */
    {
      /* #30 Enter critical section to prevent that socket connection state is set in other context. */
      SOAD_BEGIN_CRITICAL_SECTION();

      /* #40 Check if socket connection is online and shall be set to reconnect since remote address has wildcards. */
      if ( (SoAd_GetModeOfSoConDyn(SoConIdx) == SOAD_SOCON_ONLINE) &&
        ((SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) & SOAD_SOCON_MASK_ANY) != 0u) )
      {
        SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT);                                                        /* SBSW_SOAD_PARAMETER_IDX */
        hasSoConModeChanged = TRUE;
      }

      /* #50 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      /* #60 Notify about changed socket conenction mode if required. */
      if ( hasSoConModeChanged == TRUE )
      {
        SoAd_SoCon_NotifySoConModeChg(SoConIdx, SOAD_SOCON_RECONNECT);
      }
      /* #61 Check if remote address is set otherwise to set event to handle socket connection in main function. */
      else if ( SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) == SOAD_SOCON_IP_SET_PORT_SET )
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
      }
      else
      {
        /* Nothing to do. */
      }

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_SoCon_SetRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddr()
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
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) AssignedSoConIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  assignedSoConIdx;
  SoAd_SizeOfSoConType  bestMatchListSize = 0u;
  boolean               ipAddrIsAny = FALSE;
  boolean               portIsAny = FALSE;
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that remote address is set in other context. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if remote address contains wildcards. */
  SoAd_Util_CheckForWildcards(RemoteAddrPtr, &ipAddrIsAny, &portIsAny);                                                /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  if ( (ipAddrIsAny == FALSE) && (portIsAny == FALSE) )
  {
    /* #30 Get socket connection using best match algorithm. */
    if ( SoAd_SoCon_GetSoConIdxListByBestMatchAlg(SoConIdx, SOAD_SOCON_FILTER_DISABLED, RemoteAddrPtr,                 /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      &bestMatchListSize) == E_OK )
    {
      assignedSoConIdx = SoAd_GetSoConIdxOfBestMatchSoConIdxList(0u);

      /* #40 Check if requested remote address is already set on the socket connection. */
      if ( SoAd_GetRemAddrStateDynOfSoConDyn(assignedSoConIdx) == SOAD_SOCON_IP_SET_PORT_SET )
      {
        /* #400 Remove alive supervision timeout from timeout list if configured and running. */
#if ( SOAD_TCP == STD_ON )
        if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(assignedSoConIdx)) )
#endif /* SOAD_TCP == STD_ON */
        {
          SoAd_SoCon_ResetUdpAliveTimeout(assignedSoConIdx);
        }

        retVal = E_OK;
      }
      else
#if ( SOAD_TCP == STD_ON )
      /* #41 Handle setting remote address on TCP socket otherwise (if enabled). */
      if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(assignedSoConIdx)) )
      {
        retVal = SoAd_SoCon_SetUniqueRemoteAddrTcp(assignedSoConIdx, RemoteAddrPtr);                                   /* SBSW_SOAD_POINTER_FORWARD */
      }
      else
#endif /* SOAD_TCP == STD_ON */
      /* #42 Handle setting remote address on UDP socket otherwise. */
      {
        retVal = SoAd_SoCon_SetUniqueRemoteAddrUdp(assignedSoConIdx, RemoteAddrPtr);                                   /* SBSW_SOAD_POINTER_FORWARD */
      }

      /* #50 Return socket connection if found by best match algorithm and it is valid to set. */
      if ( retVal == E_OK )
      {
        *AssignedSoConIdPtr = SoAd_GetSoConIdOfSoCon(assignedSoConIdx);                                                /* SBSW_SOAD_POINTER_WRITE */
      }
    }
  }

  /* #60 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_SetUniqueRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestOpenSoCon()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_RequestOpenSoCon(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and open close counter wraps around. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if open close counter can handle new request. */
  if ( SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx) < SOAD_INV_BUF_IDX_32 )
  {
    /* #30 Increment counter. */
    SoAd_IncOpenCloseCounterOfSoConDyn(SoConIdx);                                                                      /* SBSW_SOAD_PARAMETER_IDX */

    /* #40 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

    retVal = E_OK;
  }

  /* #50 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_RequestOpenSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestCloseSoCon()
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
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_RequestCloseSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and open close counter wraps around. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if open close counter can handle new request. */
  if ( SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx) > 0u )
  {
    /* #200 Decrement counter. */
    SoAd_DecOpenCloseCounterOfSoConDyn(SoConIdx);                                                                      /* SBSW_SOAD_PARAMETER_IDX */

    retVal = E_OK;
  }

  /* #30 Check if open close counter is 0 or 'Abort' flag is set. */
  if ( (SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx) == 0u) || (Abort == TRUE) )
  {
    /* #40 Check if socket connection is not yet offline. */
    if ( SoAd_GetModeOfSoConDyn(SoConIdx) != SOAD_SOCON_OFFLINE )
    {
      /* #50 Set flags to close socket connection in main function. */
      if ( Abort == TRUE )
      {
        SoAd_SetAbortOfSoConDyn(SoConIdx, TRUE);                                                                       /* SBSW_SOAD_PARAMETER_IDX */
      }
      SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE);                                                       /* SBSW_SOAD_PARAMETER_IDX */

      /* #60 Set event to handle socket connection state in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
    }

    /* #70 Reset open close counter to 0. */
    SoAd_SetOpenCloseCounterOfSoConDyn(SoConIdx, 0u);                                                                  /* SBSW_SOAD_PARAMETER_IDX */

    retVal = E_OK;
  }

  /* #80 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_RequestCloseSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetCloseMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_SetCloseMode(
  SoAd_SizeOfSoConType SoConIdx,
  uint8 CloseMode)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if new close mode has higher priority than current close mode. */
  if ( CloseMode > SoAd_GetCloseModeOfSoConDyn(SoConIdx) )
  {
    /* #20 Set close mode to requested close mode. */
    SoAd_SetCloseModeOfSoConDyn(SoConIdx, CloseMode);                                                                  /* SBSW_SOAD_PARAMETER_IDX */
  }
} /* SoAd_SoCon_SetCloseMode() */

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleSoConStates()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_HandleSoConStates(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueStateSoConIterType eventQueueStateSoConIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_SO_CON_STATE);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueStateSoConIter = 0u;
    eventQueueStateSoConIter < elementNumToHandle;
    eventQueueStateSoConIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_SO_CON_STATE, &handleIdx) == E_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      SoAd_SizeOfSoConType soConIdx = (SoAd_SizeOfSoConType)handleIdx;

      /* #30 Check and try to open socket connection if no socket connection close is requested. */
      if ( SoAd_GetCloseModeOfSoConDyn(soConIdx) == SOAD_CLOSE_NONE )
      {
        SoAd_SoCon_CheckAndOpen(soConIdx);
      }
      /* #31 Close socket connection otherwise. */
      else
      {
        SoAd_SoCon_Close(soConIdx);
      }
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_SoCon_HandleSoConStates() */

/**********************************************************************************************************************
 *  SoAd_SoCon_Reconnect()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_Reconnect(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if automatic setup is enabled. */
  if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
  {
    /* #20 Check if keep online is not enabled. */
    if ( !SoAd_IsSockAutoSoConSetupKeepOnlineOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
    {
      /* #30 Check if remote address contains wildcards. */
      if ( (SoAd_GetRemAddrStateOfSoCon(SoConIdx) & SOAD_SOCON_MASK_ANY) != 0u )
      {
        /* #40 Reset remote address and received remote address. */
        SoAd_SoCon_ResetRemAndRcvRemAddr(SoConIdx);
   
        /* #50 Set socket connection to reconnect. */
        SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT);                                                        /* SBSW_SOAD_PARAMETER_IDX */
   
        /* #60 Set event to handle socket connection state in main function. */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
   
        /* #70 Notify user about socket connection state change. */
        SoAd_SoCon_NotifySoConModeChg(SoConIdx, SoAd_GetModeOfSoConDyn(SoConIdx));
      }
    }
  }
} /* SoAd_SoCon_Reconnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestReconnect()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_RequestReconnect(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection has automatic setup enabled. */
  if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
  {
    /* #20 Check if keep online is not enabled. */
    if ( !SoAd_IsSockAutoSoConSetupKeepOnlineOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
    {
      /* #30 Check if no not set values and wildcards are configured for remote address. */
      if ( (SoAd_GetRemAddrStateOfSoCon(SoConIdx) <= SOAD_SOCON_IP_ANY_PORT_ANY) &&
        ((SoAd_GetRemAddrStateOfSoCon(SoConIdx) & SOAD_SOCON_MASK_ANY) != 0u) )
      {
        /* #40 Set socket connection to reconnect in next main function. */
        SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_RECONNECT);                                                   /* SBSW_SOAD_PARAMETER_IDX */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
      }
    }
  }
} /* SoAd_SoCon_RequestReconnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseAllSockets()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_CloseAllSockets(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIterType sockIter;
  SoAd_SocketIdType   socketId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all sockets. */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(); sockIter++ )
  {
    socketId = SoAd_GetSocketIdOfSocketDyn(sockIter);

    /* #20 Check if socket is not closed. */
    if ( SoAd_GetStateOfSocketDyn(sockIter) != SOAD_SOCK_STATE_CLOSED )
    {
      /* #30 Close socket. */
      SoAd_TcpIp_Close(socketId, TRUE, (SoAd_SizeOfSocketType)sockIter);
    }
  }
} /* SoAd_SoCon_CloseAllSockets() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseAllSoCons()
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
FUNC(boolean, SOAD_CODE) SoAd_SoCon_CloseAllSoCons(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType    soConIter;
  SoAd_SizeOfSoConType  soConIdx;
  boolean               allSoConsClosed = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket connections. */
  for ( soConIter = 0u; soConIter < SoAd_GetSizeOfSoCon(); soConIter++ )
  {
    /* #20 Check if socket connection is not offline or data socket is not closed (i.e. close mode is not reset). */
    if ( (SoAd_GetModeOfSoConDyn(soConIter) != SOAD_SOCON_OFFLINE) ||
      (SoAd_GetCloseModeOfSoConDyn(soConIter) != SOAD_CLOSE_NONE) )
    {
      /* #30 Indicate that not all socket connections are closed. */
      allSoConsClosed = FALSE;

      /* #40 Check if socket connection is not requested to be closed. */
      if ( SoAd_GetCloseModeOfSoConDyn(soConIter) == SOAD_CLOSE_NONE )
      {
        /* #50 Check if no transmission nor reception is active on socket connection (if enabled). */
        if ( SoAd_SoCon_IsTxActive((SoAd_SizeOfSoConType)soConIter) == FALSE )
        {
          soConIdx = (SoAd_SizeOfSoConType)soConIter;

          /* #60 Close socket connection in main function. */
          SoAd_SetCloseModeOfSoConDyn(soConIdx, SOAD_CLOSE_OFFLINE_RESET);                                             /* SBSW_SOAD_CSL02 */
          SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx);
        }
      }
    }
  }

  return allSoConsClosed;
} /* SoAd_SoCon_CloseAllSoCons() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetSoConIdxListByBestMatchAlg()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_GetSoConIdxListByBestMatchAlg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SoConModeFilterType SoConModeFilter,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxListSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType      soConIter;
  SoAd_SizeOfSoConType    soConIdxTmp;
  SoAd_SizeOfSoConType    soConIdxListSize = 0u;
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_BestMatchPrioType  bestMatchPrio = SOAD_BEST_MATCH_NONE;
  SoAd_BestMatchPrioType  bestMatchPrioTmp;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket connection of the socket connection group identified by parameter SoConIdx. */
  for ( soConIter = SoAd_GetSoConStartIdxOfSoConGrp(soConGrpIdx);
    soConIter < SoAd_GetSoConEndIdxOfSoConGrp(soConGrpIdx);
    soConIter++ )
  {
    /* #20 Check if socket connection filter is disabled or socket connection state is according to the filter rule. */
#if ( SOAD_TCP == STD_ON )
    if ( (SoConModeFilter == SOAD_SOCON_FILTER_DISABLED) ||
      (SoAd_GetModeOfSoConDyn(soConIter) == SOAD_SOCON_RECONNECT) )
#else
    SOAD_DUMMY_STATEMENT(SoConModeFilter); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_TCP == STD_ON */
    {
      soConIdxTmp = (SoAd_SizeOfSoConType)soConIter;

      /* #30 Get best match priority of current socket connection. */
      bestMatchPrioTmp = SoAd_SoCon_GetBestMatchPrioOfSoConIdx(soConIdxTmp, SockAddrPtr);                              /* SBSW_SOAD_POINTER_FORWARD */

      /* #40 Store current socket connection if best match priority is higher than the highest priority up to now. */
      if ( bestMatchPrioTmp > bestMatchPrio )
      {
        bestMatchPrio = bestMatchPrioTmp;
        SoAd_SetSoConIdxOfBestMatchSoConIdxList(0u, soConIdxTmp);                                                      /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
        soConIdxListSize = 1u;

        retVal = E_OK;

        /* #400 Stop iteration if best match with highest priority has been found (i.e. IP and port match). */
        if ( bestMatchPrio == SOAD_BEST_MATCH_IP_MATCH_PORT_MATCH )
        {
          break;
        }
      }
      /* #41 Store current socket connection additionally if best match priority is equal to the highest. */
      else if ( bestMatchPrioTmp == bestMatchPrio )
      {
        SoAd_SetSoConIdxOfBestMatchSoConIdxList(soConIdxListSize, soConIdxTmp);                                        /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
        soConIdxListSize++;
      }
      /* #42 Continue without any action if best match priority is lower than the highest priority up to now. */
      else
      {
        /* Nothing to do. */
      }
    }
  }

  /* #50 Return the length of the socket connection index list with the highest priorities. */
  *SoConIdxListSizePtr = soConIdxListSize;                                                                             /* SBSW_SOAD_POINTER_WRITE */

  return retVal;
} /* SoAd_SoCon_GetSoConIdxListByBestMatchAlg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConOnReception()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSoConOnReception(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket connection is of type UDP (if TCP is enabled). */
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
#endif /* SOAD_TCP == STD_ON */
  {
    /* #20 Check if message acceptance filter is enabled. */
    if ( SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(soConGrpIdx) )
    {
      /* #30 Check if UDP listen only is disabled. */
      if ( !SoAd_IsUdpListenOnlyOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
      {
        /* #40 Check if remote is set but contains wildcards. */
        if ( ((SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) & SOAD_SOCON_MASK_ANY) > 0u) &&
          ((SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) & SOAD_SOCON_MASK_NOT) == 0u) )
        {
          /* #50 Enter critical section to prevent that remote address or alive timeout is set in other context. */
          SOAD_BEGIN_CRITICAL_SECTION();

          /* #60 Update remote address. */
          /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
          SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx),            /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */
            RemoteAddrPtr);
          SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx, SOAD_SOCON_IP_SET_PORT_SET);                                     /* SBSW_SOAD_PARAMETER_IDX */

          /* #70 Set socket connection to online. */
          SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_ONLINE);                                                         /* SBSW_SOAD_PARAMETER_IDX */

          /* #80 Set alive supervision timeout. */
          SoAd_SoCon_SetUdpAliveTimeout(SoConIdx);

          /* #90 Leave critical section. */
          SOAD_END_CRITICAL_SECTION();

          /* #100 Notify user about state change. */
          SoAd_SoCon_NotifySoConModeChg(SoConIdx, SOAD_SOCON_ONLINE);

          /* #110 Start TP reception if required and succeeds. */
          retVal = SoAd_Rx_TpStartOfReception(SoConIdx);
        }
      }
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSoConOnReception() */

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleUdpAliveTimeout()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_HandleUdpAliveTimeout(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                elementIdx = 0u;
  uint32                handleIdx = SOAD_INV_BUF_IDX_16;
  SoAd_SizeOfSoConType  soConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all timeouts in this main function cycle. */
  while ( SoAd_TimeoutList_CheckElements(SOAD_TIMEOUT_LIST_UDP_ALIVE, &elementIdx, &handleIdx, SoAd_GlobalCounter) ==  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    E_OK )
  {
     soConIdx = (SoAd_SizeOfSoConType)handleIdx;

    /* #20 Enter critical section to prevent that close mode is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Check if socket connection is online and socket connection is not requested to be closed. */
    if ( (SoAd_GetModeOfSoConDyn(soConIdx) == SOAD_SOCON_ONLINE) &&
      (SoAd_GetCloseModeOfSoConDyn(soConIdx) == SOAD_CLOSE_NONE) )
    {
      /* #300 Request socket connection to be reconnected. */
      SoAd_SetCloseModeOfSoConDyn(soConIdx, SOAD_CLOSE_RECONNECT);                                                     /* SBSW_SOAD_INDEX_BY_FUNCTION */

      /* #301 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      /* #302 Set an event to handle socket connection reconnect in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx);
    }
    /* #31 Leave critical section otherwise. */
    else
    {
      SOAD_END_CRITICAL_SECTION();
    }

    /* #40 Remove timeout from list. */
    SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, handleIdx);
  }
} /* SoAd_SoCon_HandleUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_UpdateUdpAliveTimeout()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_UpdateUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                  tmpCnt = 0u;
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket connection is of type UDP (if TCP is enabled). */
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
#endif /* SOAD_TCP == STD_ON */
  {
    /* #20 Check if timeout is configured. */
    if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) != 0u )
    {
      /* #30 Enter critical section to prevent that timeout update process is interrupted. */
      SOAD_BEGIN_CRITICAL_SECTION();

      /* #40 Check if timeout is already running. */
      if ( SoAd_TimeoutList_GetCurrentTimeout(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx, &tmpCnt, SoAd_GlobalCounter) ==   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        E_OK )
      {
        /* #50 Update timeout. */
        (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx,
          SoAd_GetAliveTimeoutMaxCntOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)), SoAd_GlobalCounter);
      }

      /* #60 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();
    }
  }
} /* SoAd_SoCon_UpdateUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_UpdateRcvRemoteAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_UpdateRcvRemoteAddress(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRcvRemAddrType rcvRemAddrIdx = SoAd_GetRcvRemAddrIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if to get received remote address is configured. */
  if ( SoAd_IsRcvRemAddrUsedOfSoCon(SoConIdx) )
  {
    /* #20 Enter critical section to prevent that received remote address buffer is read while modification. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Copy remote address to received remote address buffer. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRcvRemAddr(rcvRemAddrIdx), RemoteAddrPtr);       /* SBSW_SOAD_VARIABLE_POINTER_CSL03_AND_CONST_POINTER_FORWARD */

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
} /* SoAd_SoCon_UpdateRcvRemoteAddress() */

#if ( (SOAD_TCP == STD_ON) && (SOAD_VERIFYRXPDUCBK == STD_ON) )
/**********************************************************************************************************************
 *  SoAd_SoCon_GetLocalSockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_GetLocalSockAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) LocalSockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType  dummyDefaultRouter = { 0 };
  uint8                   dummyNetmask = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward request to TcpIp. */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_TcpIp_GetIpAddr(SoConIdx, LocalSockAddrPtr, &dummyNetmask, SOAD_A_P2VAR(SoAd_SockAddrType)&dummyDefaultRouter); /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
} /* SoAd_SoCon_GetLocalSockAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetRemoteSockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_GetRemoteSockAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemSockAddrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy current remote address. */
  /* PRQA S 310 3 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CopySockAddr(RemSockAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx)); /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02 */
} /* SoAd_SoCon_GetRemoteSockAddr() */
#endif /* (SOAD_TCP == STD_ON) && (SOAD_VERIFYRXPDUCBK == STD_ON) */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndGetRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CheckAndGetRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if remote address is set and contains at least wildcards. */
  if ( SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx) <= SOAD_SOCON_IP_ANY_PORT_ANY )
  {
    /* #20 Copy remote address to provided struct. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(IpAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx));    /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02 */

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_CheckAndGetRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetRemoteAddrState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_GetRemoteAddrState(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr,
  P2VAR(SoAd_RemAddrStateType, AUTOMATIC, SOAD_APPL_VAR) RemAddrStatePtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return remote address state. */
  *RemAddrStatePtr = SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx);                                                      /* SBSW_SOAD_POINTER_WRITE */

  /* #20 Copy remote address to provided struct. */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CopySockAddr(IpAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx));      /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02 */
} /* SoAd_SoCon_GetRemoteAddrState() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndGetRcvRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CheckAndGetRcvRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRcvRemAddrType rcvRemAddrIdx = SoAd_GetRcvRemAddrIdxOfSoCon(SoConIdx);
  boolean                   ipAddrIsAny = FALSE;
  boolean                   portIsAny = FALSE;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that a reception interrupts and address becomes inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if address is set and has no wildcards (i.e. received something from a remote entity). */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CheckForWildcards(SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRcvRemAddr(rcvRemAddrIdx),                  /* SBSW_SOAD_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD */
    &ipAddrIsAny, &portIsAny);
  if ( (ipAddrIsAny != TRUE) && (portIsAny != TRUE) )
  {
    /* #30 Return received remote address. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(IpAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRcvRemAddr(rcvRemAddrIdx));         /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD */

    retVal = E_OK;
  }

  /* #40 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_CheckAndGetRcvRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_LocalIpAddrAssignmentChg()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_LocalIpAddrAssignmentChg(
  SoAd_SizeOfLocalAddrType LocalAddrIdx,
  SoAd_IpAddrStateType State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType    soConIter;
  SoAd_SizeOfSoConType  soConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set local address state. */
  SoAd_SetIpAddrStateOfLocalAddrDyn(LocalAddrIdx, State);                                                              /* SBSW_SOAD_PARAMETER_IDX */

  /* #20 Iterate over all socket connection. */
  for ( soConIter = 0u; soConIter < SoAd_GetSizeOfSoCon(); soConIter++ )
  {
    /* #30 Check if socket connection is related to the local address. */
    if ( LocalAddrIdx == SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIter)) )
    {
      soConIdx = (SoAd_SizeOfSoConType)soConIter;

      /* #40 Notify user about IP address state change on socket connection. */
      SoAd_SoCon_NotifyLocalIpAddrAssignmentChg(soConIdx, State);

      /* #50 Set event to handle socket connection state in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx);

#if ( SOAD_TCP == STD_ON )
      /* #60 Overwrite close mode to prevent that socket connection is opened automatically on IP reassignment. */
      if ( SoAd_GetCloseModeOfSoConDyn(soConIdx) == SOAD_CLOSE_SOCKET_RECONNECT )
      {
        SOAD_BEGIN_CRITICAL_SECTION();

        SoAd_SoCon_SetCloseMode(soConIdx, SOAD_CLOSE_SOCKET);

        SOAD_END_CRITICAL_SECTION();
      }
#endif /* SOAD_TCP == STD_ON */
    }
  }
} /* SoAd_SoCon_LocalIpAddrAssignmentChg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetNumberOfOpenSocks()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(SoAd_SizeOfSocketType, SOAD_CODE) SoAd_SoCon_GetNumberOfOpenSocks(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return number of open sockets. */
  return SoAd_SoCon_OpenSocks;
} /* SoAd_SoCon_GetNumberOfOpenSocks() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetLocalPortDyn()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(SoAd_PortType, SOAD_CODE) SoAd_SoCon_GetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PortType           localPort;
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSoConType    soConStartIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConStartIdx);
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Return local port of listen socket in case of TCP server socket (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) &&
    !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
  {
    localPort = SoAd_GetLocalPortOfSocketDyn(SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx));
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Return local port of data socket otherwise. */
  {
    localPort = SoAd_GetLocalPortOfSocketDyn(SockIdx);
  }

  return localPort;
} /* SoAd_SoCon_GetLocalPortDyn() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetLocalPortDyn()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_SetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSoConType    soConStartIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConStartIdx);
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Set local port on listen socket in case of TCP server socket (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) &&
    !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
  {
    /* Optional indirection: Refer to Safe BSW assumption SoConGrp -> Socket. */
    SoAd_SetLocalPortOfSocketDyn(SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx), LocalPort);                                 /* SBSW_SOAD_OPTIONAL_CSL03 */
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Set local port on data socket otherwise. */
  {
    SoAd_SetLocalPortOfSocketDyn(SockIdx, LocalPort);                                                                  /* SBSW_SOAD_CSL02 */
  }
} /* SoAd_SoCon_SetLocalPortDyn() */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_SoCon.c
 *********************************************************************************************************************/
