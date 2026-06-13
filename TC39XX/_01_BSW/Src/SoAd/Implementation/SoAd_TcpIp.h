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
/**        \file  SoAd_TcpIp.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component TcpIp.
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

#if !defined (SOAD_TCPIP_H)
# define SOAD_TCPIP_H

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
 *  SoAd_TcpIp_Init()
**********************************************************************************************************************/
/*! \brief        Initializes Socket API specific structs.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_Init(void);

/**********************************************************************************************************************
 *  SoAd_TcpIp_RequestIpAddrAssignment()
**********************************************************************************************************************/
/*! \brief        Requests IP address assignment on a local address identified by a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    Type              IP address type.
 *                                  [range: SOAD_IPADDR_ASSIGNMENT_STATIC .. SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER]
 *  \param[in]    LocalIpAddrPtr    Pointer to IP address which shall be assigned.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx in case parameter Type has value
 *                                  SOAD_IPADDR_ASSIGNMENT_STATIC (unused otherwise):
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]    Netmask           Netmask in CIDR.
 *  \param[in]    DefaultRouterPtr  Pointer to default router (gateway) address.
 *                                  [Type == SOAD_IPADDR_ASSIGNMENT_STATIC:
 *                                    ->  DefaultRouterPtr != NULL_PTR
 *                                        Points to one of the following structs depending on configured IP address
 *                                        version of parameter SoConIdx:
 *                                          - SoAd_SockAddrInetType for IPv4
 *                                          - SoAd_SockAddrInet6Type for IPv6
 *                                  Type != SOAD_IPADDR_ASSIGNMENT_STATIC:
 *                                    ->  DefaultRouterPtr == NULL_PTR]
 *  \return       E_OK              Assignment request was accepted.
 *  \return       E_NOT_OK          Assignment request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different local IP addresses, FALSE for same local IP address.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_RequestIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_ReleaseIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief        Releases IP address assignment on a local address identified by a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return       E_OK            Release request was accepted.
 *  \return       E_NOT_OK        Release request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different local IP addresses, FALSE for same local IP address.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ReleaseIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIp_GetIpAddr()
 *********************************************************************************************************************/
/*! \brief        Returns the local IP address on a local address identified by a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   LocalAddrPtr      Pointer to local address (IP and Port).
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]   NetmaskPtr        Pointer to network mask (CIDR Notation).
 *  \param[out]   DefaultRouterPtr  Pointer to default router (gateway).
 *                                  [Points to one of the following structs depending on configured IP address
 *                                  version of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different local IP addresses, FALSE for same local IP address.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_GetIpAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) NetmaskPtr,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_CompareToIpAddr()
 *********************************************************************************************************************/
/*! \brief        Compares an IP address to all local IP addresses on an IP controller/interface.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    IpAddrPtr       Pointer to IP address.
 *  \return       E_OK            IP address matches one of the local IP addresses.
 *  \return       E_NOT_OK        IP address does not match one of the local IP addresses.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different local IP addresses, FALSE for same local IP address.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_CompareToIpAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrConstPtrType IpAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_GetPhysAddr()
 *********************************************************************************************************************/
/*! \brief        Returns the physical address (MAC address) of a local interface identified by a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   PhysAddrPtr     Pointer to physical address.
 *  \return       E_OK            Request was accepted.
 *  \return       E_NOT_OK        Request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_GetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_ReadDhcpHostNameOption()
 *********************************************************************************************************************/
/*! \brief          Returns the DHCP hostname option currently configured on a local interface identified by a
 *                  socket connection.
 *  \details        -
 *  \param[in]      SoConIdx  Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in,out]  LengthPtr Pointer to length of buffer for hostname (updated to length of hostname).
 *  \param[out]     DataPtr   Pointer to buffer for hostname.
 *  \return         E_OK      Request was accepted.
 *  \return         E_NOT_OK  Request was not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ReadDhcpHostNameOption(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) LengthPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_WriteDhcpHostNameOption()
 *********************************************************************************************************************/
/*! \brief        Sets the DHCP hostname option on a local interface identified by a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx  Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    Length    Length of buffer for hostname.
 *  \param[in]    DataPtr   Pointer to buffer for hostname.
 *  \return       E_OK      Request was accepted.
 *  \return       E_NOT_OK  Request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_WriteDhcpHostNameOption(
  SoAd_SizeOfSoConType SoConIdx,
  uint8 Length,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_ReadDhcpOption()
 *********************************************************************************************************************/
/*! \brief          Returns a DHCP option on a local address.
 *  \details        -
 *  \param[in]      IpAddrId      IP address identifier.
 *  \param[in]      Option        DHCP option code.
 *  \param[in,out]  DataLengthPtr Pointer to length of option buffer (updated to length of option on return).
 *  \param[out]     DataPtr       Pointer to option buffer.
 *  \return         E_OK          Request was accepted.
 *  \return         E_NOT_OK      Request was not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ReadDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) DataLengthPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_WriteDhcpOption()
 *********************************************************************************************************************/
/*! \brief       Sets a DHCP option on a local address.
 *  \details     -
 *  \param[in]   IpAddrId    IP address identifier.
 *  \param[in]   Option      DHCP option code.
 *  \param[in]   DataLength  Length of option buffer.
 *  \param[in]   DataPtr     Pointer to option buffer.
 *  \return      E_OK        Request was accepted.
 *  \return      E_NOT_OK    Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_WriteDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  uint16 DataLength,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_GetSocket()
 *********************************************************************************************************************/
/*! \brief        Creates a socket and returns the assigned identifier.
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    Domain        IP domain (IPv4/6).
 *  \param[in]    Protocol      Transport protocol (UDP/TCP).
 *  \param[out]   SocketIdPtr   Pointer to socket identifier.
 *  \return       E_OK          Socket request was accepted.
 *  \return       E_NOT_OK      Socket request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_GetSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_DomainType Domain,
  SoAd_ProtocolType Protocol,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_DATA) SocketIdPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIp_Bind()
 *********************************************************************************************************************/
/*! \brief          Binds a socket to a local address and port.
 *  \details        Returns a dynamically assigned port if wildcard (*PortPtr == 0) is used.
 *  \param[in]      SoConIdx      Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      SocketId      Socket identifier.
 *  \param[in,out]  PortPtr       Pointer to local port.
 *  \return         E_OK          Bind socket was successful.
 *  \return         E_NOT_OK      Bind socket was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_Bind(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) PortPtr);

# if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpListen()
 *********************************************************************************************************************/
/*! \brief        Sets a TCP socket to listen.
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    SocketId      Socket identifier.
 *  \param[in]    MaxChannels   Maximum number of parallel channels (TCP connections) allowed on this socket.
 *  \return       E_OK          Socket is set to listen.
 *  \return       E_NOT_OK      Socket is not set to listen.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_TcpListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  uint16 MaxChannels);

/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpConnect()
 *********************************************************************************************************************/
/*! \brief        Requests connecting a TCP socket to remote entity.
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    SocketId      Socket identifier.
 *  \param[in]    RemAddrPtr    Pointer to remote address.
 *                              [Points to one of the following structs depending on configured IP address version of
 *                              parameter SoConIdx:
 *                                - SoAd_SockAddrInetType for IPv4
 *                                - SoAd_SockAddrInet6Type for IPv6]
 *  \return       E_OK          Connect request accepted.
 *  \return       E_NOT_OK      Connect request not accepted.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_TcpConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr);
# endif /* SOAD_TCP */

/**********************************************************************************************************************
 *  SoAd_TcpIp_ChangeParameter()
 *********************************************************************************************************************/
/*! \brief        Changes parameter on a socket.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    SocketId        Socket identifier.
 *  \param[in]    ParameterId     Parameter identifier.
 *  \param[in]    ParameterValue  Parameter value.
 *                                [range: value or NULL_PTR in case of ParameterId == SOAD_PARAMID_STACK_SPECIFIC]
 *  \return       E_OK            Change parameter request was successful.
 *  \return       E_NOT_OK        Change parameter request was not successful.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  SoAd_ParamIdType ParameterId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ParameterValue);

/**********************************************************************************************************************
 *  SoAd_TcpIp_Close()
 *********************************************************************************************************************/
/*! \brief        Closes a socket.
 *  \details      -
 *  \param[in]    SocketId            Socket identifier.
 *  \param[in]    Abort               Indicates if TCP connection shall be closed by reset or teardown sequence (not
 *                                    used in case of BSD-like Socket API).
 *  \param[in]    SockIdx             Module internal socket index.
 *                                    [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_Close(
  SoAd_SocketIdType SocketId,
  boolean Abort,
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIp_TriggerAddressResolution()
 *********************************************************************************************************************/
/*! \brief        Triggers address resolution for a remote address on a socket connection (ARP/NDP).
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_TriggerAddressResolution(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIp_UdpTransmit()
 *********************************************************************************************************************/
/*! \brief        Transmits data over UDP socket.
 *  \details      Triggers transmission but data is copied in context of SoAd_CopyTxData.
 *  \param[in]    SockIdx           Module internal socket index.
 *                                  [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    SocketId          Socket identifier.
 *  \param[in]    RemAddrPtr        Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SockIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]    AvailableLength   Length of available data.
 *  \return       E_OK              Transmission request accepted.
 *  \return       E_NOT_OK          Transmission request not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different module internal socket indexes, FALSE for same module internal socket index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_UdpTransmit(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, AUTOMATIC) RemAddrPtr,
  uint16 AvailableLength);

# if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpTransmit()
 *********************************************************************************************************************/
/*! \brief        Transmits data over TCP socket.
 *  \details      Triggers transmission but data is copied in context of SoAd_CopyTxData.
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    AvailableLength   Length of available data.
 *  \param[in]    ForceRetrieve     Indicates if all available data has to be retrieved.
 *  \return       E_OK              Transmission request accepted.
 *  \return       E_NOT_OK          Transmission request not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket identifiers, FALSE for same socket identifier.
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_TcpTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 AvailableLength,
  boolean ForceRetrieve);

/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpReceived()
 *********************************************************************************************************************/
/*! \brief        Releases TCP reception buffer.
 *  \details      -
 *  \param[in]    SockIdx       Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    Length        Length of data to be released.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE for different socket identifiers, FALSE for same socket identifier.
 *  \config       SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_TcpReceived(
  SoAd_SizeOfSocketType SockIdx,
  uint32 Length);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIp_MainFunctionRx()
 *********************************************************************************************************************/
/*! \brief        Handles reception on socket layer.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_MainFunctionRx(void);

/**********************************************************************************************************************
 *  SoAd_TcpIp_MainFunctionState()
 *********************************************************************************************************************/
/*! \brief        Handles states on socket layer.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_MainFunctionState(void);

/**********************************************************************************************************************
 *  SoAd_TcpIp_MainFunctionTx()
 *********************************************************************************************************************/
/*! \brief        Handles transmission on socket layer.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TcpIp_MainFunctionTx(void);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_Rule20.10_0342 */

#endif /* SOAD_TCPIP_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_TcpIp.h
 *********************************************************************************************************************/
