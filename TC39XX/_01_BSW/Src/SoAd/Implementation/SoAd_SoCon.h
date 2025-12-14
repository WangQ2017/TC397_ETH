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
/**        \file  SoAd_SoCon.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component SoCon.
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

#if !defined (SOAD_SO_CON_H)
# define SOAD_SO_CON_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd.h"
# include "SoAd_Priv.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define SOAD_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
  SoAd_SoCon_InitLocalAddr()
**********************************************************************************************************************/
/*! \brief        Initializes local address structs.
 *  \details      -
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_InitLocalAddr(void);

/**********************************************************************************************************************
  SoAd_SoCon_InitSoCon()
**********************************************************************************************************************/
/*! \brief        Initializes socket connection structs.
 *  \details      -
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_InitSoCon(void);

/**********************************************************************************************************************
 *  SoAd_SoCon_InitSocket()
 *********************************************************************************************************************/
/*! \brief        Initializes module internal socket index structs.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_InitSocket(void);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetSockIdxBySocketId()
 *********************************************************************************************************************/
/*! \brief        Returns module internal socket index of a socket identifier if mapping is available.
 *  \details      -
 *  \param[in]    SocketId      Socket identifier.
 *  \param[out]   SockIdxPtr    Pointer to module internal socket index.
 *  \return       E_OK          Mapping found and SockIdxPtr is valid.
 *  \return       E_NOT_OK      No mapping found.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_GetSockIdxBySocketId(
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_SizeOfSocketType, AUTOMATIC, SOAD_APPL_DATA) SockIdxPtr);

# if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAccepted()
 *********************************************************************************************************************/
/*! \brief        Accepts TCP connections on a listen socket.
 *  \details      -
 *  \param[in]    SockIdx             Module internal socket index.
 *                                    [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    SocketIdConnected   Connected socket identifier.
 *  \param[in]    RemoteAddrPtr       Pointer to remote address.
 *                                    [Points to one of the following structs depending on configured IP address version
 *                                    of parameter SoConIdx:
 *                                      - SoAd_SockAddrInetType for IPv4
 *                                      - SoAd_SockAddrInet6Type for IPv6]
 *  \return       E_OK                Connection was accepted.
 *  \return       E_NOT_OK            Connection was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket indexes, FALSE for same socket index.
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAccepted(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketIdConnected,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAcceptedGetSoConIdx()
 *********************************************************************************************************************/
/*! \brief        Returns socket connection of a socket connection group on connection establishment on listen socket.
 *  \details      Uses best match algorithm to get socket connection if required. Parameter "SoConIdx" is used to
 *                identify the socket connection group.
 *  \param[in]    SoConIdx            Socket connection index.
 *                                    [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    RemoteAddrPtr       Pointer to remote address.
 *                                    [Points to one of the following structs depending on configured IP address version
 *                                    of parameter SoConIdx:
 *                                      - SoAd_SockAddrInetType for IPv4
 *                                      - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]   SoConIdxPtr         Pointer to socket connection index.
 *  \return       E_OK                Socket connection was found.
 *  \return       E_NOT_OK            No socket connection was found.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAcceptedGetSoConIdx(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpConnected()
 *********************************************************************************************************************/
/*! \brief        Handles TCP connections which have been initiated locally and are now successfully connected.
 *  \details      -
 *  \param[in]    SockIdx         Module internal socket index.
 *                                [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket indexes, FALSE for same socket index.
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_TcpConnected(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
  SoAd_SoCon_TcpChangeParameter()
**********************************************************************************************************************/
/*! \brief        Changes parameters on a TCP socket via the Socket API.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    SocketId        Socket identifier.
 *  \return       E_OK            Parameter change request was accepted.
 *  \return       E_NOT_OK        Parameter change request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *  \trace        DSGN-SoAdHandleSockets
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_Event()
 *********************************************************************************************************************/
/*! \brief        Handles events on socket.
 *  \details      -
 *  \param[in]    SockIdx     Module internal socket index.
 *                            [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    Event       Event type.
 *                            [range: SOAD_TCP_RESET, SOAD_TCP_CLOSED, SOAD_TCP_FIN_RECEIVED, SOAD_UDP_CLOSED]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket indexes, FALSE for same socket index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_Event(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_EventType Event);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddr()
 *********************************************************************************************************************/
/*! \brief        Sets remote address on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    RemoteAddrPtr   Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \return       E_OK            Remote address is valid and set.
 *  \return       E_NOT_OK        Remote address is not valid.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddr()
 *********************************************************************************************************************/
/*! \brief        Sets the remote address of a suitable socket connection in a socket connection group.
 *  \details      -
 *  \param[in]    SoConIdx            Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    RemoteAddrPtr       Pointer to remote address.
 *                                    [Points to one of the following structs depending on configured IP address
 *                                    version of parameter SoConIdx:
 *                                      - SoAd_SockAddrInetType for IPv4
 *                                      - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]   AssignedSoConIdPtr  Pointer to assigned socket connection identifier.
 *  \return       E_OK                Request was accepted.
 *  \return       E_NOT_OK            Request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) AssignedSoConIdPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestOpenSoCon()
 *********************************************************************************************************************/
/*! \brief        Stores a socket connection open request.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return       E_OK            Request succeeded.
 *  \return       E_NOT_OK        Request failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_RequestOpenSoCon(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestCloseSoCon()
 *********************************************************************************************************************/
/*! \brief        Stores a socket connection close request.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    Abort           Flag to close socket connection immediately.
 *  \return       E_OK            Request succeeded.
 *  \return       E_NOT_OK        Request failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_RequestCloseSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetCloseMode()
 *********************************************************************************************************************/
/*! \brief        Sets close mode considering priority of requested and current close mode.
 *  \details      Has to be called in critical section.
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    CloseMode       Requested close mode.
 *                                [range: SOAD_CLOSE_NONE .. SOAD_CLOSE_OFFLINE_RESET]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_SetCloseMode(
  SoAd_SizeOfSoConType SoConIdx,
  uint8 CloseMode);

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleSoConStates()
 *********************************************************************************************************************/
/*! \brief        Handles socket connection open and close actions in main function context.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_HandleSoConStates(void);

/**********************************************************************************************************************
 *  SoAd_SoCon_Reconnect()
 *********************************************************************************************************************/
/*! \brief        Reconnects a socket connection by resetting the corresponding structs and notifying the user.
 *  \details      Checks if automatic setup is enabled and remote address has wildcards configured before reconnecting.
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_Reconnect(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestReconnect()
 *********************************************************************************************************************/
/*! \brief        Requests reconnection of a socket connection in main function.
 *  \details      Used to reconnect socket connection with auto setup and wildcards after transmission.
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_RequestReconnect(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseAllSockets()
 *********************************************************************************************************************/
/*! \brief        Closes all configured sockets and implicitly the corresponding socket connections.
 *  \details      Used to close all socket connections in case of module shutdown.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_CloseAllSockets(void);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseAllSoCons()
 *********************************************************************************************************************/
/*! \brief        Closes all configured socket connections considering if a transmission is pending.
 *  \details      Used to close all socket connections in case of module shutdown.
 *  \return       TRUE            All socket connections are offline.
 *  \return       FALSE           At least one socket connection is not in state offline.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(boolean, SOAD_CODE) SoAd_SoCon_CloseAllSoCons(void);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetSoConIdxListByBestMatchAlg()
 *********************************************************************************************************************/
/*! \brief        Fills a global list of socket connection indexes with highest best match algorithm priority on a
 *                socket connection group and returns the size of valid elements in list.
 *  \details      Uses the parameter "SoConIdx" to identify the socket connection group on which the best match
 *                algorithm is performed.
 *  \param[in]    SoConIdx              Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    SoConModeFilter       Indicates if socket connections with specific states shall be skipped.
 *                                      [range: SOAD_SOCON_FILTER_DISABLED, SOAD_SOCON_FILTER_ON_OFF]
 *  \param[in]    SockAddrPtr           Pointer to socket address used to perform best match algorithm.
 *                                      [Points to one of the following structs depending on configured IP address
 *                                      version of parameter SoConIdx:
 *                                        - SoAd_SockAddrInetType for IPv4
 *                                        - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]   SoConIdxListSizePtr   Pointer to size of list of socket connection indexes.
 *  \return       E_OK                  At least one matching socket connection found.
 *  \return       E_NOT_OK              No matching socket connection found.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_GetSoConIdxListByBestMatchAlg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SoConModeFilterType SoConModeFilter,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxListSizePtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConOnReception()
 *********************************************************************************************************************/
/*! \brief        Tries to open a socket connection on reception.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    RemoteAddrPtr   Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \return       E_OK            Socket connection open succeeded.
 *  \return       E_NOT_OK        Socket connection open failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSoConOnReception(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleUdpAliveTimeout()
 *********************************************************************************************************************/
/*! \brief        Handles UDP alive supervision timeout on a socket connection in main function.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-SoAdCloseByTimeout
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_HandleUdpAliveTimeout(void);

/**********************************************************************************************************************
 *  SoAd_SoCon_UpdateUdpAliveTimeout()
 *********************************************************************************************************************/
/*! \brief        Updates an already running UDP Alive Supervision Timeout on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \synchronous  TRUE
 *  \trace        DSGN-SoAdCloseByTimeout
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_UpdateUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_UpdateRcvRemoteAddress()
 *********************************************************************************************************************/
/*! \brief        Updates received remote address on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    RemoteAddrPtr   Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_UpdateRcvRemoteAddress(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

# if ( (SOAD_TCP == STD_ON) && (SOAD_VERIFYRXPDUCBK == STD_ON) )
/**********************************************************************************************************************
 *  SoAd_SoCon_GetLocalSockAddr()
 *********************************************************************************************************************/
/*! \brief        Returns local socket address (local IP address and port) of a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx            Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   LocalSockAddrPtr    Pointer to local socket address.
 *                                    [Points to one of the following structs depending on configured IP address
 *                                    version of parameter SoConIdx:
 *                                      - SoAd_SockAddrInetType for IPv4
 *                                      - SoAd_SockAddrInet6Type for IPv6]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP & SOAD_VERIFYRXPDUCBK
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_GetLocalSockAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) LocalSockAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetRemoteSockAddr()
 *********************************************************************************************************************/
/*! \brief        Returns remote socket address (remote IP address and port) of a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx            Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   RemSockAddrPtr      Pointer to remote socket address.
 *                                    [Points to one of the following structs depending on configured IP address
 *                                    version of parameter SoConIdx:
 *                                      - SoAd_SockAddrInetType for IPv4
 *                                      - SoAd_SockAddrInet6Type for IPv6]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \config       SOAD_TCP & SOAD_VERIFYRXPDUCBK
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_GetRemoteSockAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemSockAddrPtr);
# endif /* (SOAD_TCP == STD_ON) && (SOAD_VERIFYRXPDUCBK == STD_ON) */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndGetRemoteAddr()
 *********************************************************************************************************************/
/*! \brief        Checks if remote address contains at least wildcards and returns remote adress.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   IpAddrPtr       Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \return       E_OK            Remote address contains at least wildcards and copied successfully.
 *  \return       E_NOT_OK        Remote address is not set and is not copied.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CheckAndGetRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetRemoteAddrState()
 *********************************************************************************************************************/
/*! \brief        Returns the remote address and remote address state of a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   IpAddrPtr       Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]   RemAddrStatePtr Pointer to remote address state.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_GetRemoteAddrState(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr,
  P2VAR(SoAd_RemAddrStateType, AUTOMATIC, SOAD_APPL_VAR) RemAddrStatePtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndGetRcvRemoteAddr()
 *********************************************************************************************************************/
/*! \brief        Checks if received remote address is set on a socket connection and returns it.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRcvRemAddrUsedOfSoCon()]
 *  \param[out]   IpAddrPtr       Pointer to received remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \return       E_OK            Remote address contains at least wildcards and copied successfully.
 *  \return       E_NOT_OK        Remote address is not set and is not copied.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CheckAndGetRcvRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*! \brief        Receives local IP address assignment state changes.
 *  \details      -
 *  \param[in]    LocalAddrIdx  Local IP address index.
 *                              [range: LocalAddrIdx < SoAd_GetSizeOfLocalAddr()]
 *  \param[in]    State         State of IP address assignment.
 *                              [range: SOAD_IPADDR_STATE_ASSIGNED, SOAD_IPADDR_STATE_ONHOLD,
 *                              SOAD_IPADDR_STATE_UNASSIGNED]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different IP address identifier, FALSE for same IP address identifier.
 *  \synchronous  TRUE
  *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_LocalIpAddrAssignmentChg(
  SoAd_SizeOfLocalAddrType LocalAddrIdx,
  SoAd_IpAddrStateType State);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetNumberOfOpenSocks()
 *********************************************************************************************************************/
/*! \brief        Returns the number of open sockets.
 *  \details      -
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
  *********************************************************************************************************************/
FUNC(SoAd_SizeOfSocketType, SOAD_CODE) SoAd_SoCon_GetNumberOfOpenSocks(void);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetLocalPortDyn()
 *********************************************************************************************************************/
/*! \brief        Returns local port of a socket.
 *  \details      Considers that a local port is shared by multiple sockets/socket connections.
 *  \param[in]    SockIdx       Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return       LocalPort     Local port.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(SoAd_PortType, SOAD_CODE) SoAd_SoCon_GetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetLocalPortDyn()
 *********************************************************************************************************************/
/*! \brief        Sets local port of a socket.
 *  \details      Considers that a local port is shared by multiple sockets/socket connections.
 *  \param[in]    SockIdx       Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    LocalPort     Local port.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_SoCon_SetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PortType LocalPort);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_Rule20.10_0342 */

#endif /* SOAD_SO_CON_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_SoCon.h
 *********************************************************************************************************************/
