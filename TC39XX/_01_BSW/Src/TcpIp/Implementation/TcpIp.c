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
 *         \file  TcpIp.c
 *        \brief  Implementation of TcpIp Module
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp.h"
#include "TcpIp_Cbk.h"
#include "TcpIp_Priv.h"
#include "TcpIp_Lcfg.h"

#include "IpBase.h"

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# include "TcpIp_IpV4.h"
# include "TcpIp_IpV4_Cbk.h"   /* needed to forward the RxIndication */
# include "TcpIp_Arp.h"
# include "TcpIp_Arp_Cbk.h"    /* needed to forward the RxIndication */
#endif

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
# include "TcpIp_IpSec.h"
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# include "TcpIp_IpV6.h"
# include "TcpIp_IpV6_Cbk.h"   /* needed to forward the RxIndication */
# include "TcpIp_IcmpV6.h"
# include "TcpIp_Ndp.h"
#endif

#include "TcpIp_Udp.h"

#if (TCPIP_SUPPORT_TCP == STD_ON)
# include "TcpIp_Tcp.h"
#endif

#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
# include "TcpIp_DhcpV4.h"
#endif

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# include "TcpIp_DhcpV6.h"
#endif

#if (TCPIP_SUPPORT_DHCPV4SERVER == STD_ON)                                                                              /* COV_MSR_UNSUPPORTED */
# include "TcpIp_DhcpV4Server.h"
#endif

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
# include "Tls.h"
# include "Tls_Cbk.h"         /* needed to forward the RxIndication */
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of TcpIp.h file */
#if (  (TCPIP_SW_MAJOR_VERSION != 14u) \
    || (TCPIP_SW_MINOR_VERSION != 3u) \
    || (TCPIP_SW_PATCH_VERSION != 3u) )
  #error "TcpIp.c: Source and Header file are inconsistent!"
#endif

/* Check configuration variant for building the library */
#if ( (defined V_EXTENDED_BUILD_LIB_CHECK) && (TCPIP_CONFIGURATION_VARIANT_PRECOMPILE == TCPIP_CONFIGURATION_VARIANT) )
  #error "TcpIp.c: Switch configuration variant to link-time or post-build for library build!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
STATIC VAR(uint32, TCPIP_VAR_NOINIT) TcpIp_IpSecSaEntryPairCnt; /* PRQA S 3218 */ /* MD_TCPIP_Rule8.9_3218 */
# endif /* (TCPIP_SUPPORT_IPSEC == STD_ON) */
#endif /* (TCPIP_SUPPORT_MEASUREMEN== STD_ON) */

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(TcpIp_StateType, TCPIP_VAR_ZERO_INIT) TcpIp_State = TCPIP_STATE_UNINIT;

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_VSocketAccessExclusive()
 *********************************************************************************************************************/
/*! \brief          Checks if another TX request is currently processed for a socket.
 *                  If not, the socket will be locked for other TX requests.
 *  \details        -
 *  \param[in]      SocketIdx             Index of a UDP or TCP socket.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \return         TRUE                  Socket has been locked and can be used for transmit.
 *  \return         FALSE                 Socket is already locked and must not be used for transmit.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketIdx
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_VSocketAccessExclusive(TcpIp_SizeOfSocketDynType SocketIdx);

/**********************************************************************************************************************
 *  TcpIp_UdpTransmitInternalVerify()
 *********************************************************************************************************************/
/*! \brief          Verifies the socket state and triggers transmission of the packet if possible.
 *  \details        -
 *  \param[in]      SocketUdpIdx        Index of a UDP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]      RemoteSockAddrPtr   Pointer to remote socket address (IPv4/IPv6 address and port).
 *  \param[in]      DataPtr             Pointer to payload of the UDP packet.
 *                                      May be NULL_PTR if indirect data provision is used. (see TcpIp_UdpTransmit()).
 *  \param[in]      DataLen             Length of the UDP payload. [bytes]
 *  \return         E_OK                Datagram successfully passed to lower layer for transmission.
 *  \return         E_NOT_OK            Socket in invalid state or transmit was rejected by UDP submodule.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketUdpIdx
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_UdpTransmitInternalVerify(
  TcpIp_SizeOfSocketUdpDynType      SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteSockAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            DataLen);

/**********************************************************************************************************************
 *  TcpIp_UdpTransmitInternal()
 *********************************************************************************************************************/
/*! \brief          Copies the data to a UDP tx buffer and triggers trnasmission of the packet.
 *  \details        -
 *  \param[in]      SocketUdpIdx        Index of a UDP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]      RemoteSockAddrPtr   Remote socket address (IPv4/IPv6 address and port).
 *  \param[in]      DataPtr             Payload of the UDP packet.
 *                                      May be NULL_PTR if indirect data provision is used. (see TcpIp_UdpTransmit()).
 *  \param[in]      DataLen             Length of the UDP payload. [bytes]
 *  \return         E_OK                Datagram successfully passed to lower layer for transmission.
 *  \return         E_NOT_OK            Transmit was rejected by UDP submodule.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketUdpIdx
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_UdpTransmitInternal(
  TcpIp_SizeOfSocketUdpDynType      SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteSockAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            DataLen);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TcpConnectInternal()
 *********************************************************************************************************************/
/*! \brief          Initiates active open of a TCP connection to the specified remote address.
 *  \details        -
 *  \param[in]      SocketTcpIdx        Index of a TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]      RemoteAddrPtr       Remote socket address (IPv4/IPv6 address and port).
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted.
 *  \pre            SocketIdx was allocated by <Up>_GetSocket().
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketTcpIdx
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpConnectInternal(
  TcpIp_SizeOfSocketTcpDynType      SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteAddrPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_VBindSocketImplicit()
 *********************************************************************************************************************/
/*! \brief         Tries to bind a socket to the local address if the socket is not bound already.
 *  \details       -
 *  \param[in]     SocketIdx   Index of a UDP or TCP socket.
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \return        E_OK        Socket successfully bound or was already bound.
 *  \return        E_NOT_OK    Socket could not be bound.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different SocketIdx
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VBindSocketImplicit(TcpIp_SizeOfSocketDynType SocketIdx);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VCloseTcpSocket()
 *********************************************************************************************************************/
/*! \brief         Requests to close the given TCP socket connection and releases all related resources.
 *  \details       Performs the following actions for the socket specified by SocketTcpIdx in case it is a TCP socket:
 *                 (a) if the connection is active and
 *                 (a1) Abort = FALSE: the connection is terminated after performing a regular connection termination handshake and releasing all related resources.
 *                 (a2) Abort = TRUE: connection will immediately be terminated by sending a RST segment and releasing all related resources.
 *                 (b) if the socket is in the Listen state, the Listen state is left immediately and related resources are released.
 *  \param[in]     SocketTcpIdx  Index of a TCP socket.
 *                 CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     Abort    TRUE: connection will immediately be terminated by sending a RST-Segment and releasing
 *                          all related resources.
 *                          FALSE: connection will be terminated after performing a regular connection termination
 *                          handshake and releasing all related resources.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different SocketTcpIdx.
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_VCloseTcpSocket(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  boolean                      Abort);
#endif /* TCPIP_SUPPORT_TCP */

/**********************************************************************************************************************
 *  TcpIp_BindInternal()
 *********************************************************************************************************************/
/*! \brief          Binds a UDP or TCP socket to a local resource
 *  \details        Checks whether the socket may be bound, using the given parameters, and does the actual binding.
 *  \param[in]      SocketIdx           Index of a UDP or TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      LocalAddrIdx        Refer to description of this parameter at function TcpIp_Bind().
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCALADDRID_ANY.
 *  \param[in,out]  PortPtr             Refer to description of this parameter at function TcpIp_Bind().
 *  \param[out]     ErrorIdPtr          TCPIP_E_NO_ERROR    In case the binding was conducted.
 *                                      TCPIP_E_ADDRINUSE   In case a socket with the requested protocol, port and
 *                                                          IpAddrId has already been requested, earlier.
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted (e.g. address in use).
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_BindInternal(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TcpIp_SizeOfLocalAddrType LocalAddrIdx,
  TCPIP_P2V(uint16)         PortPtr,
  TCPIP_P2V(uint8)          ErrorIdPtr);

/**********************************************************************************************************************
 *  TcpIp_RequestIpAddrAssignmentInternal()
 *********************************************************************************************************************/
/*! \brief          Initiates the local IP address assignment for the IP address specified by LocalAddrIdx.
 *  \details        -
 *  \param[in]      LocalAddrIdx       IP address index specifying the IP address for which an
 *                                     assignment shall be initiated.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]      Type               Type of IP address assignment which shall be initiated
 *  \param[in]      LocalIpAddrPtr     Pointer to structure containing the IP address which shall be
 *                                     assigned to the EthIf controller indirectly specified via
 *                                     LocalAddrIdx.
 *                                     May be NULL_PTR if ip address shall not be set.
 *  \param[in]      Netmask            Network mask of IPv4 address or address prefix of IPv6 address in CIDR Notation.
 *  \param[in]      DefaultRouterPtr   Pointer to struct where the IP address of the default router
 *                                     (gateway) is stored (struct member 'port' is not used and of
 *                                     arbitrary value) (IPv4 only)
 *                                     May be NULL_PTR if default router shall not be set.
 *  \return         E_OK               The request has been accepted.
 *  \return         E_NOT_OK           The request has not been accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different LocalAddrIdx.
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_RequestIpAddrAssignmentInternal(
  TcpIp_SizeOfLocalAddrType         LocalAddrIdx,
  TcpIp_IpAddrAssignmentType        Type,
  TCPIP_P2C(TcpIp_SockAddrBaseType) LocalIpAddrPtr,
  uint8                             Netmask,
  TCPIP_P2C(TcpIp_SockAddrBaseType) DefaultRouterPtr);

/**********************************************************************************************************************
 *  TcpIp_VGetSocketForOwner()
 *********************************************************************************************************************/
/*! \brief          Allocates a TCP/UDP socket for use in the specified domain (IPv4/IPv6).
 *  \details        -
 *  \param[in]      Domain             Domain / address family that will be used with the socket.
 *                                     [TCPIP_AF_INET (IPv4) or TCPIP_AF_INET6 (IPv6)]
 *  \param[in]      Protocol           Transport layer protocol that will be used with the socket.
 *                                     [TCPIP_IPPROTO_TCP or TCPIP_IPPROTO_UDP]
 *  \param[out]     SocketIdPtr        Socket identifier of the allocated socket.
 *                                     Only valid if E_OK is returned.
 *  \param[in]      SocketOwnerIdx     Index of the socket owner for which the socket shall be allocated.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfSocketOwnerConfig()-1]
 *  \return         E_OK               Socket was allocated (*SocketIdPtr updated).
 *  \return         E_NOT_OK           The socket could not be allocated.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketOwnerIdx.
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VGetSocketForOwner(
  TcpIp_DomainType                Domain,
  TcpIp_ProtocolType              Protocol,
  TCPIP_P2V(TcpIp_SocketIdType)   SocketIdPtr,
  TcpIp_SocketOwnerConfigIterType SocketOwnerIdx);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VTcpListenSockStateListen()
 *********************************************************************************************************************/
/*! \brief          Handles the listen action for a socket that is in state 'listen', already.
 *  \details        -
 *  \param[in]      SocketTcpIdx       Index of a TCP socket.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]      MaxChannels        Maximum number of new parallel connections established on this listen connection.
 *  \return         E_OK               The request has been accepted.
 *  \return         E_NOT_OK           The request has not been accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketTcpIdx.
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VTcpListenSockStateListen(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint16                     MaxChannels);
#endif

#if (TCPIP_SUPPORT_DIAG_ACCESS_EXTENSIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DiagDataReadAccessInternal()
 *********************************************************************************************************************/
/*! \brief          Reads miscellaneous TcpIp related diagnostic data.
 *  \details        The memory fragment DataPtr points to should be aligned properly regarding the expected returned
 *                  type / struct. Data is only written if RetValue is E_OK.
 *                  This is a Vector extension.
 *  \param[in]      SocketIdx      Index of a UDP or TCP socket.
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      DataID         Valid and checked data identifier.
 *  \param[out]     DataPtr        Valid and checked pointer for diagnostic data.
 *  \param[in,out]  DataLenPtr     Valid and checked pointer for maximum / actual length of diagnostic data in bytes
 *  \return         E_OK           Diagnostic data has been written to the DataPtr and DataLenPtr parameter.
 *  \return         E_NOT_OK       Invalid parameter. (data identifier not found, NULL_PTR parameter, invalid length)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DiagDataReadAccessInternal(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TcpIp_DiagParamsType      DataID,
  TCPIP_P2V(uint8)          DataPtr,
  TCPIP_P2V(uint16)         DataLenPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_VHandleGenericSocketParameter()
 *********************************************************************************************************************/
/*! \brief          Handles a parameter that applies for UDP and TCP sockets.
 *  \details        -
 *  \param[in]      SocketIdx             Index of a UDP or TCP socket.
 *                                        CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      ParameterId           Identifier of the parameter.
 *  \param[in]      ParameterValuePtr     Pointer to the parameter value bytes.
 *                                        (The number of bytes depends on ParameterId).
 *                                        CONSTRAINT: May be NULL_PTR if ParameterId is TCPIP_PARAMID_V_PHYS_DEST_ADDR.
 *  \param[in,out]  ParameterRetValuePtr  Return value of the parameter specific handler function.
 *                                        (Only updated if this function returns TRUE).
 *  \return         TRUE                  Parameter Id matched (*ParameterRetValuePtr has been updated).
 *  \return         FALSE                 Unknown parameter Id.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different socket owners
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_VHandleGenericSocketParameter(
  TcpIp_SocketDynIterType   SocketIdx,
  TcpIp_ParamIdType         ParameterId,
  TCPIP_P2C(uint8)          ParameterValuePtr,
  TCPIP_P2V(Std_ReturnType) ParameterRetValuePtr);

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VGetAndResetMeasurementData()
 *********************************************************************************************************************/
/*! \brief          Read the corresponding measurement data counter and optionally reset it.
 *  \details        -
 *  \param[in]      MeasurementIdx         Index of a measurement data.
 *  \param[in]      MeasurementResetNeeded Flag for the measurement data to reset.
 *                                         TRUE  - Reset the measurement data.
 *                                         FALSE - Do not reset.
 *  \param[out]     MeasurementDataPtr     Returns the value of the measurement data count.
 *                                         CONSTRAINT: [May be NULL_PTR in combination with
 *                                                      MeasurementResetNeeded == TRUE.]
 *  \return         E_OK                   Measurement data is read and optionally reset successfully.
 *  \return         E_NOT_OK               Read or Reset is not sucessfull.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VGetAndResetMeasurementData(
  TcpIp_MeasurementIdxType  MeasurementIdx,
  boolean                   MeasurementResetNeeded,
  TCPIP_P2V(uint32)         MeasurementDataPtr);

/**********************************************************************************************************************
 *  TcpIp_VResetMeasurementData()
 **********************************************************************************************************************/
/*! \brief          Reset all measurement data counters for dropped TCP/UDP/IPV4/IPV6 packets.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 **********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_VResetMeasurementData(void);
#endif

#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_MainFunctionRx()
 *********************************************************************************************************************/
/*! \brief          Handles reception of data and forwards it to the socket owners.
 *  \details        -
 *  \pre            -
 *  \context        TASK (Called by TcpIp_MainFunction() which is called cyclically by schedule manager)
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_MainFunctionRx(void);

/**********************************************************************************************************************
 *  TcpIp_MainFunctionState()
 *********************************************************************************************************************/
/*! \brief          Performs pending state changes of the TcpIp module and the TCP/UDP sockets.
 *  \details        -
 *  \pre            -
 *  \context        TASK (Called by TcpIp_MainFunction() which is called cyclically by schedule manager)
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_MainFunctionState(void);

/**********************************************************************************************************************
 *  TcpIp_MainFunctionTx()
 *********************************************************************************************************************/
/*! \brief          Queues data from the socket owners and triggers transmission of data at the lower layer.
 *  \details        -
 *  \pre            -
 *  \context        TASK (Called by TcpIp_MainFunction() which is called cyclically by schedule manager)
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_MainFunctionTx(void);
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_InitMemory()
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
FUNC(void, TCPIP_CODE) TcpIp_InitMemory( void )
{
  /* #10 Set the TcpIp initialization state to 'not initialized'. */
  TcpIp_State = TCPIP_STATE_UNINIT;

#if (TCPIP_SUPPORT_DHCPV4SERVER == STD_ON)                                                                              /* COV_MSR_UNSUPPORTED */
  /* #20 Call the InitMemory function of the submodule DhcpV4Server in case it is configured. */
  TcpIp_DhcpV4Server_InitMemory();
#endif

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  /* #30 Call the InitMemory function of the submodule IpV4 in case it is configured. */
  IpV4_InitMemory();
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  /* #40 Call the InitMemory function of the submodule IpV6 in case it is configured. */
  IpV6_InitMemory();
#endif

  /* #50 Reset configuration pointer. */
  TcpIp_ConfigDataPtr = NULL_PTR;
}

/**********************************************************************************************************************
 *  TcpIp_Init()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 * */
FUNC(void, TCPIP_CODE) TcpIp_Init(
  TCPIP_P2C(TcpIp_ConfigType) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if(TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                   /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check plausibility of input parameters. */
  if(ConfigPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Initialize configuration pointer. */
    TcpIp_ConfigDataPtr = ConfigPtr;

    /* #30 Initialize the submodules (IPv4, IPv6, TCP, UDP), if configured. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    IpV4_Init();
#endif

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
    TcpIp_IpSec_Init();
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    IpV6_Init();
#endif

#if (TCPIP_SUPPORT_TCP == STD_ON)
    TcpIp_Tcp_Init();
#endif

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
    TcpIp_VResetMeasurementData();
#endif

    TcpIp_Udp_Init();

    /* #40 Initialize socket-related data structures. */
    TcpIp_VInitSockets();

    /* #50 Initialize address-related data structures. */
    {
      TcpIp_LocalAddrIterType localAddrIdx;

      for(localAddrIdx = 0; localAddrIdx < TcpIp_GetSizeOfLocalAddr(); localAddrIdx++)
      {
        TcpIp_SetAssignmentStateOfLocalAddr(localAddrIdx, TCPIP_IPADDR_STATE_UNASSIGNED);                                 /* SBSW_TCPIP_CslIteration */
      }
    }

    /* #60 Initialize the DHCPv4 server submodule, if configured. */
#if (TCPIP_SUPPORT_DHCPV4SERVER == STD_ON)                                                                              /* COV_MSR_UNSUPPORTED */
    TcpIp_DhcpV4Server_Init();
#endif

    /* #70 Set module state to INIT. */
    TcpIp_State = TCPIP_STATE_INIT;
  }

  /* ----- Development Error Report --------------------------------------- */
#if(TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* #80 Report default errors if any occurred. */
  if(errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_INIT, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* TcpIp_Init() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_RxIndication()
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
FUNC(void, TCPIP_CODE) TcpIp_RxIndication(
  uint8            CtrlIdx,
  Eth_FrameType    FrameType,
  boolean          IsBroadcast,
  TCPIP_P2V(uint8) PhysAddrPtr,
  TCPIP_P2V(uint8) DataPtr,
  uint16           LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'PhysAddrPtr' */
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'LenByte' */
  else if (LenByte == 0u)
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check of parameter 'CtrlIdx' is done by the RxIndication functions of the sub-modules! */
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call sub-module-specific RxIndication functions depending on the FrameType. */
    switch(FrameType)
    {
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    /* #30 In case IpV4 is configured, call the IpV4-specific RxIndication function for FrameType IpV4. */
    case TCPIP_ETH_FRAME_TYPE_IPV4:
    {
      IpV4_Ip_RxIndication(CtrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, LenByte);                             /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
      break;
    }

    /* #40 In case IpV4 is configured, call the IpV4/ARP-specific RxIndication function for FrameType IpV4/ARP. */
    case TCPIP_ETH_FRAME_TYPE_ARP:
    {
      IpV4_Arp_RxIndication(CtrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, LenByte);                            /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
      break;
    }
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    /* #50 In case IpV6 is configured, call the IpV6-specific RxIndication function for FrameType IpV6. */
    case TCPIP_ETH_FRAME_TYPE_IPV6:
    {
      IpV6_RxIndication(CtrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, LenByte);                                /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
      break;
    }
#endif
    default:
      /* TcpIp called for unsupported FrameType. -> ignore this message */
      errorId = TCPIP_E_INV_ARG;
      break;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_RXINDICATION, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
} /* TcpIp_RxIndication() */ /* PRQA S 6060, 6080 */ /* MD_TcpIp_AutosarApi, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_GetSocketForUser()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetSocketForUser(
  TcpIp_DomainType                Domain,
  TcpIp_ProtocolType              Protocol,
  TCPIP_P2V(TcpIp_SocketIdType)   SocketIdPtr,
  TcpIp_SocketOwnerConfigIterType SocketOwnerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'Domain' */
  else if (!TCPIP_COND_VALID_DOMAIN(Domain))
  {
    errorId = TCPIP_E_AFNOSUPPORT;
  }
  /* Parameter 'Protocol' is checked below. */
  /* Check parameter 'SocketIdPtr' */
  else if (SocketIdPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'SocketOwnerIdx' */
  else if (SocketOwnerIdx >= TcpIp_GetSizeOfSocketOwnerConfig())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
  /* ----- Implementation ----------------------------------------------- */
#endif
  /* #20 Check the protocol to be supported. */
  if(    (TCPIP_IPPROTO_UDP == Protocol)
# if (TCPIP_SUPPORT_TCP == STD_ON)
      || (TCPIP_IPPROTO_TCP == Protocol)
# endif
    )
  {
    /* #30 Forward the request to the internal helper function. */
    retVal = TcpIp_VGetSocketForOwner(Domain, Protocol, SocketIdPtr, SocketOwnerIdx);                                   /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
  }
  else
  {
    /* MISRA: The protocol is not supported - leave retVal at value E_NOT_OK */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void) Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_SOCKET, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetSocketForUser() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_VGetSocketForOwner()
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VGetSocketForOwner(
  TcpIp_DomainType                Domain,
  TcpIp_ProtocolType              Protocol,
  TCPIP_P2V(TcpIp_SocketIdType)   SocketIdPtr,
  TcpIp_SocketOwnerConfigIterType SocketOwnerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfSocketDynType socketIdx;
  TcpIp_SizeOfSocketDynType socketIdxStart;
  TcpIp_SizeOfSocketDynType socketIdxEnd;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine relevant sockets based on 'Protocol'. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
  if (Protocol == TCPIP_IPPROTO_TCP)
  {
    socketIdxStart = TcpIp_GetSizeOfSocketUdpDyn();
    socketIdxEnd   = TcpIp_GetSizeOfSocketDyn();
  }
  else
#else
  TCPIP_UNUSED_PARAMETER(Protocol);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  {
    socketIdxStart = 0;
    socketIdxEnd   = TcpIp_GetSizeOfSocketUdpDyn();
  }


  /* #20 Enter exclusive area. */
  TCPIP_VENTER_CRITICAL_SECTION();  /* lock interrupts */

  /* #30 Iterate over relevant sockets looking for a 'free' socket which is currently not assigned to a user. */
  for(socketIdx = socketIdxStart; socketIdx < socketIdxEnd; socketIdx++)
  {
    if (TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx) == TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN)
    {
      /* #40 Found a free socket, assign it to the SocketOwner. */
      TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(socketIdx, (TcpIp_SizeOfSocketOwnerConfigType)SocketOwnerIdx);           /* SBSW_TCPIP_SocketIdx_1 */
      break;
    }
  }

  /* #50 Exit exclusive area. */
  TCPIP_VLEAVE_CRITICAL_SECTION();  /* unlock interrupts */

  /* #60 In case a free socket has been found, allocate the socket for this user. */
  if (socketIdx < socketIdxEnd)
  {
    TcpIp_VPreconfigSocket(socketIdx);
    TcpIp_SetListenActiveConnStatOfSocketDyn(socketIdx, TCPIP_SOCK_CONN_ALLOCATED);                                     /* SBSW_TCPIP_SocketIdx_1 */

    TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->sa_family = Domain;                                                     /* SBSW_TCPIP_SocketIdx_1 */

    /* Initialize TCP socket parameters, if socket is a TCP socket. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
    if (Protocol == TCPIP_IPPROTO_TCP)
    {
      TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_TCP(socketIdx));
      TcpIp_Tcp_InitSock(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx));
    }
#endif

    *SocketIdPtr = TCPIP_SOCKET_IDX_TO_ID(socketIdx);                                                                   /* SBSW_TCPIP_NonNullPtrParameter */

    retVal = E_OK;
  }
  /* else: No free socket was found */

  return retVal;
} /* TcpIp_VGetSocketForUser() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TcpListen()
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpListen(
  TcpIp_SocketIdType SocketId,
  uint16             MaxChannels)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!(TCPIP_SOCKET_ID_IS_VALID(SocketId) && TCPIP_SOCKET_IDX_IS_TCP(TCPIP_SOCKET_ID_TO_IDX(SocketId))))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'MaxChannels' */
  else if (MaxChannels >= TcpIp_GetSizeOfSocketTcpDyn())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SocketDynIterType    socketIdx    = TCPIP_SOCKET_ID_TO_IDX(SocketId);
    TcpIp_SocketTcpDynIterType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx);

    /* #20 In case the socket is in listen state, already: Handle the request in that state. */
    if (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx) == TCPIP_SOCK_CONN_LISTEN_ENABLED)
    {
      retVal = TcpIp_VTcpListenSockStateListen(socketTcpIdx, MaxChannels);
    }
    else
    {
      /* #30 In case the socket is not yet in listen state: Bring the socket into that state. */
      if (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx) == TCPIP_SOCK_CONN_ALLOCATED)
      {
        /* TCP: Passive open: (TcpIp_VTcpListenSockStateAllocated) */
        TcpIp_SockAddrBaseType SockAddrRem;  /* PRQA S 0759 */ /* MD_MSR_Union */

        /* #40 Set remote address to 'undefined'. */
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
        (void)IpBase_DelSockAddr(&SockAddrRem.SockAddr, IPBASE_AF_INET6);                                               /* SBSW_TCPIP_PtrToLocalVariable */
#else
        (void)IpBase_DelSockAddr(&SockAddrRem.SockAddr, IPBASE_AF_INET);                                                /* SBSW_TCPIP_PtrToLocalVariable */
#endif
        /* #50 Try to open the TCP socket in passive mode and inform the caller about the result. */
        if (TcpIp_Tcp_Open(socketTcpIdx, &SockAddrRem, TCPIP_TCP_PASSIVE_OPEN) == E_OK)                                 /* SBSW_TCPIP_PtrToLocalVariable */
        {
          TcpIp_SetListenActiveConnStatOfSocketDyn(socketIdx, TCPIP_SOCK_CONN_LISTEN_ENABLED);                          /* SBSW_TCPIP_SocketIdxFromCheckedSocketId */
          TcpIp_SetMaxNumListenSocketsOfSocketTcpDyn(socketTcpIdx, MaxChannels);  /* set limit */                       /* SBSW_TCPIP_TcpIdxFromCheckedSocketIdx */
          retVal = E_OK;
        }
        /* else: Open failed: Leave retVal at value E_NOT_OK */
      }
      /* else: Socket is in an invalid state - leave retVal at E_NOT_OK. */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_TCP_LISTEN, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_Listen() */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_VTcpListenSockStateListen()
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
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VTcpListenSockStateListen(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint16                     MaxChannels)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  /* #10 In case the given MaxChannels value has changed, check if more than MaxChannels sockets have been derived
         from the current socket and set the TcpIp-internal limit to the new MaxChannels value */
  if (MaxChannels != TcpIp_GetMaxNumListenSocketsOfSocketTcpDyn(SocketTcpIdx))
  {
    /* #20 In case MaxChannels is smaller than the TcpIp-internal limit iterate all sockets and count those that are related to the given SocketId */
    if(MaxChannels < TcpIp_GetMaxNumListenSocketsOfSocketTcpDyn(SocketTcpIdx))
    {
      /* Check if more than MaxChannels sockets have been derived from the current socket */
      TcpIp_SocketIdType SockCnt = 0;
      TcpIp_SocketTcpDynIterType iterSocketTcpIdx;
      for (iterSocketTcpIdx = 0; iterSocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); iterSocketTcpIdx++)
      {
        if(TcpIp_GetSocketTcpDynMasterListenSocketIdxOfSocketTcpDyn(iterSocketTcpIdx) == SocketTcpIdx)
        {
          SockCnt++;
        }
      }
      /* #30 In case the number of allocated sockets related to the given SocketId has increased: Set the TcpIp-internal limit to the new value */
      if(MaxChannels >= SockCnt)
      {
        TcpIp_SetMaxNumListenSocketsOfSocketTcpDyn(SocketTcpIdx, MaxChannels);                                          /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
      }
      /* #40 Indicated an error in case the given MaxChannels value is larger than the counted number of related sockets */
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* #50 In case MaxChannels is bigger than the currently configured value, simply set the TcpIp-internal limit to the new value */
      TcpIp_SetMaxNumListenSocketsOfSocketTcpDyn(SocketTcpIdx, MaxChannels);                                            /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
    }
  }
  /* else: Leave retVal at value E_OK */
  return retVal;
} /* TcpIp_VTcpListenSockStateListen() */

/**********************************************************************************************************************
 *  TcpIp_TcpConnect()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpConnect(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2C(TcpIp_SockAddrType) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'RemoteAddrPtr' */
  else if (RemoteAddrPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else if (TcpIp_VNetAddrIsUnicast((TCPIP_P2C(TcpIp_SockAddrBaseType))RemoteAddrPtr) == FALSE)  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */  /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);

    if (TCPIP_SOCKET_IDX_IS_TCP(socketIdx))
    {
      /* #20 Forward call to internal function. */
      retVal = TcpIp_TcpConnectInternal(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx), (TCPIP_P2C(TcpIp_SockAddrBaseType))RemoteAddrPtr);  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */  /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
    }
    else
    {
      errorId = TCPIP_E_INV_ARG;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_TCP_CONNECT, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_TcpConnectInternal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpConnectInternal(
  TcpIp_SizeOfSocketTcpDynType      SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType            retVal    = E_NOT_OK;
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Connect the socket, in case the socket is properly bound. */
  if (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx) == TCPIP_SOCK_CONN_ALLOCATED)
  {
    /* #20 Assign a random port number in case the socket (identified by SocketId) has not yet been assigned a valid port number. */
    if (TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->DomainAndPort.port == TCPIP_PORT_NOT_SET)
    {
      TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->DomainAndPort.port = TcpIp_VGetNextDynamicPort(TCPIP_PROTOCOL_TCP);   /* SBSW_TCPIP_SocketIdxFromValidTcpIdx */
    }

    /* #30 Actually open the TCP connection using the given TCP socket index. */
    if (TcpIp_Tcp_Open(SocketTcpIdx, RemoteAddrPtr, TCPIP_TCP_ACTIVE_OPEN) == E_OK)                                     /* SBSW_TCPIP_NonNullPtrParameter */
    {
      TcpIp_SetListenActiveConnStatOfSocketDyn(socketIdx, TCPIP_SOCK_CONN_ACTIVE);                                      /* SBSW_TCPIP_SocketIdxFromValidTcpIdx */
      retVal = E_OK;
    }
    /* else: Leave retVal at value E_NOT_OK. */
  }
  else
  {
    /* Leave retVal at value E_NOT_OK. */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TcpTransmit()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpTransmit(
  TcpIp_SocketIdType SocketId,
  TCPIP_P2V(uint8)   DataPtr,  /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  uint32             AvailableLength,
  boolean            ForceRetrieve)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'AvailableLength' */
  else if (AvailableLength > 0xFFFFu)
  {
    /* This implementation is limited to 64k per transmit. */
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check if there is any data to transmit. */
    if (AvailableLength > 0u)
    {
      TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);

      if (TCPIP_SOCKET_IDX_IS_TCP(socketIdx))
      {
        /* #30 Forward call to Tls, if Tls is used for the socket. */
# if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
        TcpIp_SizeOfSocketDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx);
        if (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
        {
          retVal = TcpIp_TcpTransmitTls(socketIdx, DataPtr, AvailableLength);
        }
        else
# endif
        /* #40 Otherwise: Forward call to internal function. */
        {
          retVal = TcpIp_TcpTransmitInternal(socketIdx, DataPtr, AvailableLength, ForceRetrieve);                       /* SBSW_TCPIP_MaybeNullPtrParameter */
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_TCP_TRANSMIT, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif  /* (TCPIP_SUPPORT_TCP == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_VBindSocketImplicit()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VBindSocketImplicit(TcpIp_SizeOfSocketDynType SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket is already bound. (local port is set to 0 for unbound sockets) */
  if (TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->DomainAndPort.port != TCPIP_PORT_NOT_SET)
  {
    retVal = E_OK;
  }
  /* #20 In case the socket is unbound: Try to bind it implicitly to a dynamic port. */
  /* \trace SPEC-50982 */
  else
  {
    uint8 errorId;

    retVal = TcpIp_BindInternal(SocketIdx, TcpIp_GetLocalAddrBindIdxOfSocketDyn(SocketIdx),
      &TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->DomainAndPort.port, &errorId);                                       /* SBSW_TCPIP_BindInternal */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_UdpTransmit()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_UdpTransmit(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(uint8)              DataPtr,        /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  TCPIP_P2V(TcpIp_SockAddrType) RemoteAddrPtr,  /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  uint16                        TotalLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (TCPIP_SOCKET_ID_TO_IDX(SocketId) >= TcpIp_GetSizeOfSocketUdpDyn())
  {
    /* Passed socket ID does not represent a UDP socket. */
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'RemoteAddrPtr' */
  else if (RemoteAddrPtr == NULL_PTR)
  {
    /* RemoteAddrPtr not set. */
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else if (TCPIP_IS_ADDR_FAMILY_SUPPORTED(RemoteAddrPtr->domain) == FALSE)  /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
  {
    /* RemoteAddrPtr has invalid address family. */
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType    socketIdx    = TCPIP_SOCKET_ID_TO_IDX(SocketId);
    TcpIp_SizeOfSocketUdpDynType socketUdpIdx = TCPIP_SOCKET_IDX_TO_UDP_IDX(socketIdx);

    retVal = TcpIp_UdpTransmitInternalVerify(socketUdpIdx, (TCPIP_P2C(TcpIp_SockAddrBaseType))RemoteAddrPtr, DataPtr, TotalLength); /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */ /* SBSW_TCPIP_UdpTransmitInternalVerify */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_UDP_TRANSMIT, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_UdpTransmit() */

/**********************************************************************************************************************
*  TcpIp_UdpTransmitInternalVerify()
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_UdpTransmitInternalVerify(
  TcpIp_SizeOfSocketUdpDynType      SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteSockAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_UDP_IDX_TO_SOCKET_IDX(SocketUdpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check that socket is allocated. */
  if (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx) != TCPIP_SOCK_CONN_NONE)
  {
    /* #20 Try to bind to socket implicitly, if socket is unbound. */
    if (TcpIp_VBindSocketImplicit(socketIdx) == E_OK)
    {
      /* #30 Acquire semaphore for the socket in order to avoid simultaneous transmits over the same socket. */
      if (TcpIp_VSocketAccessExclusive(socketIdx) == TRUE)
      {
        /* #40 Try to send requested UDP datagram. */
        retVal = TcpIp_UdpTransmitInternal(SocketUdpIdx, RemoteSockAddrPtr, DataPtr, DataLen);                          /* SBSW_TCPIP_UdpTransmitInternal */

        /* #50 Release semaphore for the socket. */
        TcpIp_SetTxBufRequestedOfSocketDyn(socketIdx, FALSE);                                                           /* SBSW_TCPIP_SocketIdxFromValidUdpIdx */
      }
    }
  }

  return retVal;
} /* TcpIp_UdpTransmitInternalVerify() */

/**********************************************************************************************************************
 *  TcpIp_UdpTransmitInternal()
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
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_UdpTransmitInternal(
  TcpIp_SizeOfSocketUdpDynType      SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteSockAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType    retVal = E_NOT_OK;
  uint16            dataLenRemain = DataLen;
  uint16            dataLenLocal  = DataLen;
  uint16            udpPayloadBufferLen = dataLenRemain;
  BufReq_ReturnType udpBufReqRetVal;
  TCPIP_P2V(uint8)  udpPayloadPtr;

  TCPIP_ASSERT(SocketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn());

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Request TX buffer for UDP packet from lower layer.
    *     Multiple buffer segments may be provided by the IP if fragmentation is required. */
    /* If DataLen exceeds the payload that fits into one IP packet TcpIp_Udp_RequestTxBuffer() may only provide a buffer for the first payload fragment.
    * Additional buffers for the other payload fragments are obtained by TcpIp_Udp_FragmentRequestTxBuffer() later.
    */
  udpBufReqRetVal = TcpIp_Udp_RequestTxBuffer(SocketUdpIdx, RemoteSockAddrPtr, &udpPayloadPtr, &udpPayloadBufferLen);   /* SBSW_TCPIP_Udp_RequestTxBuffer */

  if (udpBufReqRetVal == BUFREQ_OK)
  {
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_UDP_IDX_TO_SOCKET_IDX(SocketUdpIdx);
    boolean copyDataSuccessful = TRUE;
    uint16  dataPos = 0;

    /* a buffer could be provided successfully */
    /* #20 Iterate over all provided UDP payload buffer fragments and copy upper layer data. */
    while (dataLenRemain > 0u)
    {
      /* Provided buffer may be larger than required. */
      if (dataLenRemain < udpPayloadBufferLen)
      {
        udpPayloadBufferLen = dataLenRemain;
      }

      /* #30 Copy data from upper layer into TX buffer, if data was provided. */
      if (DataPtr != NULL_PTR)
      {
        TCPIP_ASSERT(dataPos < dataLenLocal);

        /* directly copy provided data from user into provided UDP buffer */
        IpBase_Copy(udpPayloadPtr, &DataPtr[dataPos], udpPayloadBufferLen);  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_TCPIP_UdpTransmitInternal_Copy_1 */
        dataPos       += udpPayloadBufferLen;
        dataLenRemain -= udpPayloadBufferLen;
      }
      /* #40 Otherwise: Trigger upper layer to copy TX data into buffer by calling CopyTxData. */
      else
      {
        uint16 udpTxDataLen = udpPayloadBufferLen;

        /* call CopyTxData function of user */

        if (TcpIp_CopyTxDataFunctions(  /* udpPayloadPtr, &udpTxDataLen */                                              /* SBSW_TCPIP_UdpTransmitInternal_Copy_2 */
          socketIdx, udpPayloadPtr, &udpTxDataLen) == BUFREQ_OK)
        {
          if (udpTxDataLen < udpPayloadBufferLen)
          {
            /* Upper layer provided less data than requested. Adapt requested length and do not copy more data. */
            uint16 trucnLen = dataLenRemain - udpTxDataLen;
            dataLenLocal -= trucnLen;
            dataLenRemain = 0;
          }
          else
          {
            dataLenRemain -= udpPayloadBufferLen;
          }
        }
        else
        {
          /* ERROR: CopyTxData of upper layer failed. Transmit will be aborted. */
          copyDataSuccessful = FALSE;
          dataLenRemain = 0;
        }
      }

      /* #50 Request next TX buffer segment from lower layer if required. */
      if (dataLenRemain > 0u)
      {
        /* Request next UDP payload buffer fragment */
        if (E_OK != TcpIp_Udp_FragmentRequestTxBuffer(SocketUdpIdx, RemoteSockAddrPtr->sa_family, &udpPayloadPtr, &udpPayloadBufferLen))  /* SBSW_TCPIP_Udp_FragmentRequestTxBuffer */
        {
          /* ERROR: This should not happen. If TcpIp_Udp_RequestTxBuffer() returns BUFREQ_OK there should be sufficient buffer space */
          copyDataSuccessful = FALSE;
          dataLenRemain = 0;
        }
      }
    }

    /* #60 Transmit UDP datagram if payload was successfully copied into TX buffer.
     *     Otherwise: Abort transmission. */
    if (copyDataSuccessful == TRUE)
    {
      if (TcpIp_Udp_Transmit(SocketUdpIdx, dataLenLocal, RemoteSockAddrPtr) == E_OK)  /* SBSW_TCPIP_NonNullPtrParameter */
      {
        retVal = E_OK;
      }
    }
    else
    {
      TcpIp_Udp_TransmitCancel(SocketUdpIdx);
    }
  }
  else
  {
    /* No Ethernet buffer available or link-layer address resolution pending and no free element in UDP retry queue. */
    /* retVal remains E_NOT_OK */
  }

  return retVal;
} /* TcpIp_UdpTransmitInternal() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_IcmpV6Transmit()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IcmpV6Transmit(
  TcpIp_LocalAddrIdType          LocalIpAddrId,
  TCPIP_P2C(TcpIp_SockAddrType)  RemoteAddrPtr,
  uint8                          HopLimit,
  uint8                          Type,
  uint8                          Code,
  uint16                         DataLength,
  TCPIP_P2C(uint8)               DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal  = E_NOT_OK;
  uint8           errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  else if (!(TCPIP_LOCAL_ADDR_IDX_IS_IPV6(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId))))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* LocalIpAddrId invalid. */
    errorId = TCPIP_E_INV_ARG;
  }
  else if (RemoteAddrPtr == NULL_PTR)
  {
    /* RemoteAddrPtr not set. */
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else if (RemoteAddrPtr->domain != TCPIP_AF_INET6)
  {
    /* RemoteAddr address family invalid. */
    errorId = TCPIP_E_INV_ARG;
  }
  else if (DataPtr == NULL_PTR)
  {
    /* DataPtr not set. */
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_LocalAddrIterType   localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId);
    TcpIp_LocalAddrV6IterType ipV6AddrIdx  = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx);

    TCPIP_P2C(TcpIp_SockAddrBaseType) remoteAddrPtr = (TCPIP_P2C(TcpIp_SockAddrBaseType))RemoteAddrPtr;  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */

    /* #20 Forward call to ICMPv6 submodule. */
    if (IpV6_Icmp_TxRawMessage(&ipV6AddrIdx, &remoteAddrPtr->SockAddrIn6.sin6_addr, HopLimit, Type, Code, DataLength, DataPtr) == BUFREQ_OK)  /* SBSW_TCPIP_IpV6_Icmp_TxRawMessage */
    {
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_ICMPV6_TRANSMIT, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_IcmpV6Transmit() */  /* PRQA S 6060, 6080 */ /* MD_TcpIp_AutosarApi, MD_MSR_STMIF */
#endif

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TcpReceived()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpReceived(
  TcpIp_SocketIdType SocketId,
  uint32             Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'Length' */
  else if (!TCPIP_COND_LEN_MAX_UINT16(Length))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);

    /* #20 Check this TCP socket to be properly requested by a socket user. */
    if(TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx) != TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN)
    {
      /* #30 Dispatch the reception to TCP or TLS according to the sockets configuration. */
      if (TCPIP_SOCKET_IDX_IS_TCP(socketIdx))
      {
        TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx);

# if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
        if(TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
        {
          /* TLS received */
          (void)Tls_Received(SocketId, Length);
          /* Return value of Tls_Received() is ignored because this function will only return an error if called with
             an invalid socket id or if TLS is not initialized. -> A Det will be reported by TLS in that case. */
        }
        else
# endif
        {
          /* TCP received */
          TcpIp_Tcp_Received(socketTcpIdx, (uint16)Length);
        }
        retVal = E_OK;
      }
      /* else: Invalid socket id: Leave retVal at value E_NOT_OK. */
    }
    /* else: socket is not requested by a user: Leave retVal at value E_NOT_OK. */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_TCP_RECEIVED, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* TcpIp_TcpReceived() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif

/**********************************************************************************************************************
 *  TcpIp_Close()
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Close(
  TcpIp_SocketIdType SocketId,
  boolean            Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);

    /* #20 Check if the socket state is valid. */
    if (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx) != TCPIP_SOCK_CONN_NONE)
    {
      /* #30 Check if socket is a UDP or TCP socket. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
      if (TCPIP_SOCKET_IDX_IS_UDP(socketIdx))
#endif
      {
        /* #40 UDP: Close the socket and inform socket owner. */
        /* Temporarily store the index of the socket owner because the socket variables will be reset below before the
           socket owner is notified. */
        uint8 tmpSocketOwnerIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

        TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(socketIdx, TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN);                  /* SBSW_TCPIP_SocketIdxFromCheckedSocketId */
        TcpIp_SetListenActiveConnStatOfSocketDyn(socketIdx, TCPIP_SOCK_CONN_NONE);                                      /* SBSW_TCPIP_SocketIdxFromCheckedSocketId */

        TcpIp_VDelSockAddrMapping(socketIdx);
        TcpIp_Udp_CloseSocket(TCPIP_SOCKET_IDX_TO_UDP_IDX(socketIdx));

        TcpIp_TcpIpEventFunctions(tmpSocketOwnerIdx, socketIdx, TCPIP_UDP_CLOSED);  /* trigger 'CLOSED' event */

      }
#if (TCPIP_SUPPORT_TCP == STD_ON)
      else
      {
        /* #50 TCP: Forward call to internal function that closes the TCP socket depending on parameter 'Abort'. */
        TcpIp_VCloseTcpSocket(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx), Abort);

      }
#else
      TCPIP_UNUSED_PARAMETER(Abort);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
      retVal = E_OK;
    }
    /* else: Socket (already) closed. Leave retVal = E_NOT_OK. */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_CLOSE, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_Close() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VCloseTcpSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_VCloseTcpSocket(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  boolean                      Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketDynType         socketIdx;

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  boolean useTls;
#endif

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);


#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  useTls = TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx);
#endif

  /* #10 Trigger the closing of the socket (via FIN) at the TCP, if 'Abort' is not requested. */
  if (Abort == FALSE)
  {
    TcpIp_Tcp_Close(SocketTcpIdx);
  }
  /* #20 Otherwise: Trigger the fast closing (abort) of the socket at the TCP and update the admin data to actually delete the socket. */
  else
  {
    TcpIp_Tcp_Abort(SocketTcpIdx);

    /* delete socket */
    TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(socketIdx, TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN);                      /* SBSW_TCPIP_SocketIdxFromValidTcpIdx */
    TcpIp_SetListenActiveConnStatOfSocketDyn(socketIdx, TCPIP_SOCK_CONN_NONE);                                          /* SBSW_TCPIP_SocketIdxFromValidTcpIdx */
  }

  /* #30 Check, whether to inform the upper layers about the closing of the socket in case of slow closing but non-connected socket. */
  if ((Abort == FALSE) && (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx) != TCPIP_SOCK_CONN_ACTIVE) )  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* delete socket */
    TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(socketIdx, TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN);                      /* SBSW_TCPIP_SocketIdxFromValidTcpIdx */
    TcpIp_SetListenActiveConnStatOfSocketDyn(socketIdx, TCPIP_SOCK_CONN_NONE);                                          /* SBSW_TCPIP_SocketIdxFromValidTcpIdx */
  }

  /* #40 Actually inform upper layers about the closing of the socket, if required. */
  if (Abort == TRUE)
  {
#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
    if(useTls == TRUE)
    {
      Tls_TcpIpEvent(socketIdx, TCPIP_TCP_CLOSED);  /* trigger 'CLOSED' event */
    }

#endif
  }
} /* TcpIp_VCloseTcpSocket() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif /* TCPIP_SUPPORT_TCP */

/**********************************************************************************************************************
 *  TcpIp_Bind()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Bind(
  TcpIp_SocketIdType    SocketId,
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2V(uint16)     PortPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* Check component initialization state. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID_OR_ANY(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'PortPtr' */
  else if (PortPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check state of the address that is affected by the bind-request: */
  else if ((LocalAddrId != TCPIP_LOCALADDRID_ANY) && (TcpIp_GetAssignmentStateOfLocalAddr(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId)) != TCPIP_IPADDR_STATE_ASSIGNED))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* reject the bind request if no valid address is available for the LocalAddrId */
    errorId = TCPIP_E_ADDRNOTAVAIL;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = (LocalAddrId != TCPIP_LOCALADDRID_ANY) ? TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId) : TCPIP_LOCALADDRID_ANY;

    retVal = TcpIp_BindInternal(TCPIP_SOCKET_ID_TO_IDX(SocketId), localAddrIdx, PortPtr, &errorId);                     /* SBSW_TCPIP_BindInternal */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_BIND, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_Bind() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_BindInternal()
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
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_BindInternal(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TcpIp_SizeOfLocalAddrType LocalAddrIdx,
  TCPIP_P2V(uint16)         PortPtr,
  TCPIP_P2V(uint8)          ErrorIdPtr)
{
  /* [SWS_TCPIP_00146]:  TcpIp_Bind() shall check if there is another socket already bound to the same port, protocol
      and local address and if that is the case refuse the request and return E_NOT_OK. If development error detection
      is enabled, the service TcpIp_Bind() shall also raise the development error code TCPIP_E_ADDRINUSE. () \trace SPEC-66326 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_OK;
  TcpIp_SocketDynIterType socketStartIdx;
  TcpIp_SocketDynIterType socketEndIdx;
  uint8                   protocol;

  /* ----- Implementation ----------------------------------------------- */
  *ErrorIdPtr = TCPIP_E_NO_ERROR;                                                                                      /* SBSW_TCPIP_NonNullPtrParameter */
  /* #10 Select range of all TCP or all UDP sockets that need to be checked below. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
  if (TCPIP_SOCKET_IDX_IS_UDP(SocketIdx))
#endif
  {
    protocol = TCPIP_PROTOCOL_UDP;

    socketStartIdx = 0;
    socketEndIdx   = TcpIp_GetSizeOfSocketUdpDyn();
  }
#if (TCPIP_SUPPORT_TCP == STD_ON)
  else
  {
    protocol = TCPIP_PROTOCOL_TCP;

    socketStartIdx = TcpIp_GetSizeOfSocketUdpDyn();
    socketEndIdx   = TcpIp_GetSizeOfSocketDyn();
  }
#endif

  /* #20 Check if the socketOwnerConfig is invalid. */
  if (TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(SocketIdx) == TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN)
  {
    /* ERROR: Invalid socketOwnerIndex, TcpIp_Bind is called without TcpIp_GetSocketForUser() */
    *ErrorIdPtr = TCPIP_E_INV_ARG;                                                                                     /* SBSW_TCPIP_NonNullPtrParameter */
    retVal      = E_NOT_OK;
  }
  else
  {
    /* #30 Otherwise: Select an unused port from the dynamic port range if caller did not specify a port. */
    if (*PortPtr == TCPIP_PORT_NOT_SET)
    {
      *PortPtr = TcpIp_VFindUnusedDynamicPort(protocol, LocalAddrIdx, socketStartIdx, socketEndIdx, SocketIdx);        /* SBSW_TCPIP_NonNullPtrParameter */

      if (*PortPtr == TCPIP_PORT_NOT_SET)
      {
        /* ERROR: Did not find a dynamic port that is not in use by another socket. */
        *ErrorIdPtr = TCPIP_E_ADDRINUSE;                                                                               /* SBSW_TCPIP_NonNullPtrParameter */
        retVal = E_NOT_OK;
      }
    }
    /* #40 Otherwise: Check if specified port is not already in use by another socket. */
    else
    {
      if (TcpIp_VIsPortAndAddrUsedBySocket(*PortPtr, LocalAddrIdx, socketStartIdx, socketEndIdx, SocketIdx) == TRUE)
      {
        /* ERROR: A socket with the requested protocol, port and LocalAddrId is already bound. */
        *ErrorIdPtr = TCPIP_E_ADDRINUSE;                                                                               /* SBSW_TCPIP_NonNullPtrParameter */
        retVal = E_NOT_OK;
      }
    }

    /* #50 Bind the socket to the IP address and port, if no other socket uses the same port and address. */
    if (retVal == E_OK)
    {
      TcpIp_SizeOfLocalAddrType ipVxAddrIdx;

      if (LocalAddrIdx < TcpIp_GetSizeOfLocalAddr())
      {
        ipVxAddrIdx = TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx);
      }
      else
      {
        ipVxAddrIdx = TCPIP_IP_ADDR_ID_ANY;
      }

      TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->DomainAndPort.port = TCPIP_HTONS(*PortPtr);                          /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
      TcpIp_SetTxIpAddrIdxOfSocketDyn(SocketIdx, ipVxAddrIdx);                                                         /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
      TcpIp_SetLocalAddrBindIdxOfSocketDyn(SocketIdx, LocalAddrIdx);                                                   /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */

#if (TCPIP_SUPPORT_TCP == STD_ON)
      if (TCPIP_SOCKET_IDX_IS_UDP(SocketIdx))
#endif
      {
        /* Bound UDP socket is always handled as listening socket. */
        TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_LISTEN_ENABLED);                           /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
      }
    }
  }

  return retVal;
} /* TcpIp_BindInternal() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_RequestIpAddrAssignment()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_RequestIpAddrAssignment(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TcpIp_IpAddrAssignmentType    Type,
  TCPIP_P2V(TcpIp_SockAddrType) LocalIpAddrPtr,    /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  uint8                         Netmask,
  TCPIP_P2V(TcpIp_SockAddrType) DefaultRouterPtr)  /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* Check component initialization state. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check input parameters. */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else if ((Type > TCPIP_IPADDR_ASSIGNMENT_MAX_VALUE) && (Type != TCPIP_IPADDR_ASSIGNMENT_ANY))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else if ((Type == TCPIP_IPADDR_ASSIGNMENT_STATIC) && (LocalIpAddrPtr == NULL_PTR))
  {
    /* ERROR: LocalIpAddrPtr must not be NULL_PTR if assignment type is STATIC. */
    errorId = TCPIP_E_INV_ARG;
  }
  /* Values of 'LocalIpAddrPtr', 'Netmask' and 'DefaultRouterPtr' are checked below. */
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = TcpIp_RequestIpAddrAssignmentInternal(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId),                             /* SBSW_TCPIP_RequestIpAddrAssignmentInternal */
      Type,
      (TCPIP_P2C(TcpIp_SockAddrBaseType))LocalIpAddrPtr,     /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */
      Netmask,
      (TCPIP_P2C(TcpIp_SockAddrBaseType))DefaultRouterPtr);  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_REQ_IP_ADDR_ASSIGN, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
}  /* TcpIp_RequestIpAddrAssignment() */

/**********************************************************************************************************************
*  TcpIp_RequestIpAddrAssignmentInternal()
**********************************************************************************************************************/
/*! Internal comment removed.
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
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_RequestIpAddrAssignmentInternal(
  TcpIp_SizeOfLocalAddrType         LocalAddrIdx,
  TcpIp_IpAddrAssignmentType        Type,
  TCPIP_P2C(TcpIp_SockAddrBaseType) LocalIpAddrPtr,
  uint8                             Netmask,
  TCPIP_P2C(TcpIp_SockAddrBaseType) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  /* #10 Dispatch the request to the affected IP subcomponent depending on the address type being IpV4 or IpV6. */
  if (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(LocalAddrIdx))
# endif
  {
    /* #20 IPv4: Check if parameter 'Netmask' is valid IPv4 netmask. */
    if (Netmask <= 32u)
    {
      TcpIp_SizeOfLocalAddrV4Type ipV4AddrIdx       = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(LocalAddrIdx);
      IpBase_AddrInType           localIpAddr       = IPV4_ADDR_ANY;
      IpBase_AddrInType           defaultRouterAddr = IPV4_ADDR_ANY;

      retVal = E_OK;

      /* #30 Check if optional parameter 'LocalIpAddrPtr' is valid. */
      if (LocalIpAddrPtr != NULL_PTR)
      {
        if (LocalIpAddrPtr->sa_family == TCPIP_AF_INET)
        {
          localIpAddr = LocalIpAddrPtr->SockAddrIn.sin_addr;
        }
        else
        {
          retVal = E_NOT_OK;
          TcpIp_CallDetReportError(TCPIP_API_ID_REQ_IP_ADDR_ASSIGN, TCPIP_E_INV_ARG);
        }
      }
      /* else: Use IPV4_ADDR_ANY to indicate that localIpAddr was not specified. */

      /* #40 Check if optional parameter 'DefaultRouterPtr' is valid. */
      if (DefaultRouterPtr != NULL_PTR)
      {
        if (DefaultRouterPtr->sa_family == TCPIP_AF_INET)
        {
          defaultRouterAddr = DefaultRouterPtr->SockAddrIn.sin_addr;
        }
        else
        {
          retVal = E_NOT_OK;
          TcpIp_CallDetReportError(TCPIP_API_ID_REQ_IP_ADDR_ASSIGN, TCPIP_E_INV_ARG);
        }
      }
      /* else: Use IPV4_ADDR_ANY to indicate that defaultRouterAddr was not specified. */

      /* #50 Forward call to IpV4 submodule, if not error occurred. */
      if (retVal == E_OK)
      {
        retVal = IpV4_Ip_RequestIpAddrAssignment(ipV4AddrIdx, Type, localIpAddr, Netmask, defaultRouterAddr);
      }
    }
    else
    {
      /* Netmask is invalid. */
      TcpIp_CallDetReportError(TCPIP_API_ID_REQ_IP_ADDR_ASSIGN, TCPIP_E_INV_ARG);
    }
  }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)
  else
# endif
  {
    /* #60 IPv6: Check if parameter 'Netmask' is valid IPv6 netmask. */
    if (Netmask <= 128u)
    {
      TcpIp_SizeOfLocalAddrV6Type   ipV6AddrIdx          = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(LocalAddrIdx);
      TCPIP_P2C(IpBase_AddrIn6Type) localIpAddrPtr       = NULL_PTR;
      TCPIP_P2C(IpBase_AddrIn6Type) defaultRouterAddrPtr = NULL_PTR;

      retVal = E_OK;

      /* #70 Check if optional parameter 'LocalIpAddrPtr' is valid. */
      if (LocalIpAddrPtr != NULL_PTR)
      {
        if (LocalIpAddrPtr->sa_family == TCPIP_AF_INET6)
        {
          localIpAddrPtr = &LocalIpAddrPtr->SockAddrIn6.sin6_addr;
        }
        else
        {
          retVal = E_NOT_OK;
          TcpIp_CallDetReportError(TCPIP_API_ID_REQ_IP_ADDR_ASSIGN, TCPIP_E_INV_ARG);
        }
      }
      /* else: Use NULL_PTR to indicate that localIpAddr was not specified. */

      /* #80 Check if optional parameter 'DefaultRouterPtr' is valid. */
      if (DefaultRouterPtr != NULL_PTR)
      {
        if (DefaultRouterPtr->sa_family == TCPIP_AF_INET6)
        {
          defaultRouterAddrPtr = &DefaultRouterPtr->SockAddrIn6.sin6_addr;
        }
        else
        {
          retVal = E_NOT_OK;
          TcpIp_CallDetReportError(TCPIP_API_ID_REQ_IP_ADDR_ASSIGN, TCPIP_E_INV_ARG);
        }
      }
      /* else: Use NULL_PTR to indicate that defaultRouterAddr was not specified. */

      /* #90 Forward call to IpV6 submodule, if not error occurred. */
      if (retVal == E_OK)
      {
        retVal = IpV6_Ip_RequestIpAddrAssignment(ipV6AddrIdx, Type, localIpAddrPtr, Netmask, defaultRouterAddrPtr);     /* SBSW_TCPIP_IpV6_Ip_RequestIpAddrAssignment */
      }
    }
    else
    {
      /* Netmask is invalid. */
      TcpIp_CallDetReportError(TCPIP_API_ID_REQ_IP_ADDR_ASSIGN, TCPIP_E_INV_ARG);
    }
  }
#endif

  return retVal;
} /* TcpIp_RequestIpAddrAssignmentInternal() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  TcpIp_ReleaseIpAddrAssignment()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ReleaseIpAddrAssignment(
  TcpIp_LocalAddrIdType LocalAddrId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call TcpIp_ReleaseSpecificIpAddrAssignment with all assignment methods. */
    retVal = TcpIp_ReleaseSpecificIpAddrAssignment(LocalAddrId, TCPIP_IPADDR_ASSIGNMENT_ANY);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_REL_IP_ADDR_ASSIGN, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
}  /* TcpIp_ReleaseIpAddrAssignment() */

/**********************************************************************************************************************
 *  TcpIp_ReleaseSpecificIpAddrAssignment()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ReleaseSpecificIpAddrAssignment (
  TcpIp_LocalAddrIdType      LocalAddrId,
  TcpIp_IpAddrAssignmentType AssignmentType)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'AssignmentType' */
  else if ((AssignmentType > TCPIP_IPADDR_ASSIGNMENT_MAX_VALUE) && (AssignmentType != TCPIP_IPADDR_ASSIGNMENT_ANY))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Forward the request to the related subcomponent, depending on the protocol of the given local address id. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    if (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx))
# endif
    {
      /* LocalAddrId is an IpV4 address id */
      retVal = IpV4_Ip_ReleaseIpAddrAssignment(TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx), AssignmentType);
    }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)
    else
# endif
    {
      /* LocalAddrId is an IpV6 address id */
      uint32  preferredLifetime = 0;
      uint32  validLifetime     = 0;
      boolean noDad             = FALSE;

      retVal = IpV6_SetAddress(TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx), NULL_PTR, preferredLifetime, validLifetime, noDad);  /* SBSW_TCPIP_MaybeNullPtrParameter */
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_REL_IP_ADDR_ASSIGN, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_ReleaseSpecificIpAddrAssignment() */

/**********************************************************************************************************************
 *  TcpIp_GetPhysAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetPhysAddr(
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2V(uint8)      PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'PhysAddrPtr' */
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Depending on the address-type of the given LocalAddrId, forward the request to the IpV4 or IpV6 subcomponent. */
    /* Forward request to IP */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    if (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx))
# endif
    {
      /* IpV4 */
      TcpIp_LocalAddrV4IterType localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx);
      IpV4_Ip_GetPhysAddr(localAddrV4Idx, PhysAddrPtr);                                                                 /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
    }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)
    else
# endif
    {
      /* IpV6 */
      TcpIp_LocalAddrV6IterType localAddrV6Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx);
      IpV6_GetPhysAddrByIpAddrId(localAddrV6Idx, PhysAddrPtr);                                                          /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
    }
#endif
    retVal = E_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_PHYS_ADDR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetPhysAddr() */

/**********************************************************************************************************************
 *  TcpIp_GetRemotePhysAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(TcpIp_ReturnType, TCPIP_CODE) TcpIp_GetRemotePhysAddr(
  uint8                         CtrlIdx,
  TCPIP_P2V(TcpIp_SockAddrType) IpAddrPtr,  /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  TCPIP_P2V(uint8)              PhysAddrPtr,
  boolean                       initRes)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType retVal = TCPIP_E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'IpAddrPtr' */
  else if (IpAddrPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'PhysAddrPtr' */
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else if (CtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TCPIP_P2C(TcpIp_SockAddrBaseType) sockAddrBaseTypePtr = (TCPIP_P2C(TcpIp_SockAddrBaseType))IpAddrPtr;  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */

    /* #20 Forward the request to the IP subcomponent related to the domain of the given IpAddrPtr. */
    switch(IpAddrPtr->domain)
    {
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    case TCPIP_AF_INET:
      {
        /* IpV4 */
        retVal = IpV4_Ip_GetRemotePhysAddr(CtrlIdx, sockAddrBaseTypePtr->SockAddrIn.sin_addr, PhysAddrPtr, initRes);    /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
        break;
      }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    case TCPIP_AF_INET6:
      {
        /* IpV6 */
        retVal = IpV6_GetRemotePhysAddr(CtrlIdx, &(sockAddrBaseTypePtr->SockAddrIn6.sin6_addr), PhysAddrPtr, initRes);  /* SBSW_TCPIP_CheckedPtrPassedToSubroutine */
        break;
      }
#endif
    default:
      {
        /* error, invalid domain type */
        retVal = TCPIP_E_NOT_OK;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_REMOTE_PHYS_ADDR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetRemotePhysAddr() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_GetArpCacheEntries()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetArpCacheEntries(
  uint8                              CtrlIdx,
  TCPIP_P2V(uint32)                  NumberOfElementsPtr,
  TCPIP_P2V(TcpIp_ArpCacheEntryType) EntryListPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'NumberOfElementsPtr' */
  else if (NumberOfElementsPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'EntryListPtr' dependent on parameter 'NumberOfElementsPtr' */
  else if ((*NumberOfElementsPtr > 0u) && (EntryListPtr == NULL_PTR))
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else if (CtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward call to IpV4 submodule. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    retVal = IpV4_Arp_GetCacheEntries(CtrlIdx, NumberOfElementsPtr, EntryListPtr);                                      /* SBSW_TCPIP_GetCacheEntries */
#else
    TCPIP_UNUSED_PARAMETER(CtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_ARP_CACHE_ENTRIES, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  return retVal;
} /* TcpIp_GetArpCacheEntries() */

/**********************************************************************************************************************
 *  TcpIp_SendGratuitousArpReq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_SendGratuitousArpReq(
  TcpIp_LocalAddrIdType LocalAddrId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalAddrId' */
  else if (LocalAddrId >= TcpIp_GetSizeOfLocalAddrV4())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward call to IpV4 submodule. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    retVal = IpV4_Arp_SendGratuitousArpReq(LocalAddrId);
#else
    TCPIP_UNUSED_PARAMETER(LocalAddrId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  }
  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_SEND_GRATUITOUS_ARP_REQ, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_SendGratuitousArpReq() */

/**********************************************************************************************************************
 *  TcpIp_GetCtrlIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetCtrlIdx(
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2V(uint8)      CtrlIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'CtrlIdxPtr' */
  else if (CtrlIdxPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Depending on the protocol of the local address id pass the request to the affected submodule IpV4 or IpV6. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    if(TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx))
# endif
    {
      /* IpV4 */
      TcpIp_LocalAddrV4IterType localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx);
      TcpIp_IpV4CtrlIdxOfLocalAddrV4Type ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(localAddrV4Idx);
      (*CtrlIdxPtr) = TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(ipV4CtrlIdx);                                                     /* SBSW_TCPIP_CheckedPtrParameter */
      retVal = E_OK;
    }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)
    else
# endif
    {
      /* IpV6 */
      TcpIp_LocalAddrV6IterType localAddrV6Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx);
      TcpIp_IpV6CtrlIdxOfLocalAddrV6Type ipV6CtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);
      (*CtrlIdxPtr) = TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(ipV6CtrlIdx);                                                     /* SBSW_TCPIP_CheckedPtrParameter */
      retVal = E_OK;
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_CTRL_IDX, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetCtrlIdx() */

/**********************************************************************************************************************
 *  TcpIp_MainFunctionRx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_ON)
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_MainFunctionRx(void)
#else
FUNC(void, TCPIP_CODE) TcpIp_MainFunctionRx(void)
#endif
{
#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_OFF)
  /* #10 Check initialization of the component. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    /* module is not initialized, so do nothing here but just return */
  }
  else
#endif
  {
    /* IpV4 submodule does not have RX MainFunction. */

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    /* #20 Call RX MainFunction of IpV6 submodule. */
    IpV6_MainFunctionRx();
#endif

    /* #30 Call RX MainFunction of UDP submodule. */
    TcpIp_Udp_MainFunctionRx();

#if (TCPIP_SUPPORT_TCP == STD_ON)
    /* #40 Call RX MainFunction of TCP submodule. */
    TcpIp_Tcp_MainFunctionRx();
#endif
  }
} /* TcpIp_MainFunctionRx() */

/**********************************************************************************************************************
 *  TcpIp_MainFunctionState()
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
#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_ON)
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_MainFunctionState(void)
#else
FUNC(void, TCPIP_CODE) TcpIp_MainFunctionState(void)
#endif
{
#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_OFF)
  /* #10 Check initialization of the component. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    /* module is not initialized, so do nothing here but just return */
  }
  else
#endif
  {
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    /* #20 Call MainFunction of IpV4 submodule. */
    IpV4_MainFunction();
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    /* #30 Call State MainFunction of IpV6 submodule. */
    IpV6_MainFunctionState();
#endif

#if (TCPIP_SUPPORT_DHCPV4SERVER == STD_ON)                                                                              /* COV_MSR_UNSUPPORTED */
    /* #40 Call MainFunction of DHCPv4 Server submodule. */
    TcpIp_DhcpV4Server_MainFunction();
#endif

    /* UDP submodule only has RX and TX MainFunctions. */

#if (TCPIP_SUPPORT_TCP == STD_ON)
    /* #50 Call State MainFunction of TCP submodule. */
    TcpIp_Tcp_MainFunctionState();
#endif
  }
} /* TcpIp_MainFunctionState() */

/**********************************************************************************************************************
 *  TcpIp_MainFunctionTx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_ON)
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_MainFunctionTx(void)
#else
FUNC(void, TCPIP_CODE) TcpIp_MainFunctionTx(void)
#endif
{
#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_OFF)
  /* #10 Check initialization of the component. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    /* module is not initialized, so do nothing here but just return */
  }
  else
#endif
  {
    /* IpV4 submodule does not have a TX MainFunction. */

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    /* #20 Call TX MainFunction of IpV6 submodule. */
    IpV6_MainFunctionTx();
#endif

    /* #30 Call TX MainFunction of UDP submodule. */
    TcpIp_Udp_MainFunctionTx();

#if (TCPIP_SUPPORT_TCP == STD_ON)
    /* #40 Call TX MainFunction of TCP submodule. */
    TcpIp_Tcp_MainFunctionTx();
#endif
  }
} /* TcpIp_MainFunctionTx() */

#if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_MainFunction(void)
{
  /* #10 Check initialization of the component. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    /* module is not initialized, so do nothing here but just return */
  }
  else
  {
    /* #20 Call RX MainFunction. */
    TcpIp_MainFunctionRx();

    /* #30 Call State MainFunction. */
    TcpIp_MainFunctionState();

    /* #40 Call TX MainFunction. */
    TcpIp_MainFunctionTx();
  }
} /* TcpIp_MainFunction() */
#endif

/**********************************************************************************************************************
 *  TcpIp_ChangeParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ChangeParameter(
  TcpIp_SocketIdType SocketId,
  TcpIp_ParamIdType  ParameterId,
  TCPIP_P2V(uint8)   ParameterValue)  /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'ParameterValue' */
  else if ((ParameterId != TCPIP_PARAMID_V_PHYS_DEST_ADDR) && (ParameterValue == NULL_PTR))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* ParameterId is no checked for DET because they are verified by the handlers for the specific parameters. */
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);

    /* #20 Forward parameter to the IP submodules, if socket parameter is generic (UDP and TCP). */
    if (TcpIp_VHandleGenericSocketParameter(socketIdx, ParameterId, ParameterValue, &retVal) == TRUE)                   /* SBSW_TCPIP_VHandleGenericSocketParameter */
    {
      /* return updated retVal. */
    }
    else
    /* #30 Forward parameter to TCP or UDP submodule based on the socket type. */
    {
#if (TCPIP_SUPPORT_TCP == STD_ON)
      if (TCPIP_SOCKET_IDX_IS_UDP(socketIdx))
#endif
      {
        TcpIp_SizeOfSocketUdpDynType socketUdpIdx = TCPIP_SOCKET_IDX_TO_UDP_IDX(socketIdx);

        retVal = TcpIp_Udp_SetSockOpt(socketUdpIdx, ParameterId, ParameterValue);                                       /* SBSW_TCPIP_CheckedPtrParameter */
      }
#if (TCPIP_SUPPORT_TCP == STD_ON)
      else  /* The Socket must be TCP as it is already verified above, against UDP and also against valid Socket (TCPIP_SOCKET_ID_IS_VALID(SocketId)) */
      {
        TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx);

        retVal = TcpIp_Tcp_SetSockOpt(socketTcpIdx, ParameterId, ParameterValue);                                       /* SBSW_TCPIP_CheckedPtrParameter */
      }
#endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_CHANGE_PARAM, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_ChangeParameter() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
*  TcpIp_VHandleGenericSocketParameter()
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_VHandleGenericSocketParameter(
  TcpIp_SocketDynIterType   SocketIdx,
  TcpIp_ParamIdType         ParameterId,
  TCPIP_P2C(uint8)          ParameterValuePtr,
  TCPIP_P2V(Std_ReturnType) ParameterRetValuePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType parameterRetValue  = E_OK;
  boolean        parameterIdMatched = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call corresponding function of the IP submodule(s), if parameter is a generic (UDP and TCP) socket parameter. */
  switch (ParameterId)
  {
  case TCPIP_PARAMID_FRAMEPRIO:
    parameterRetValue = TcpIp_VSetSocketSpecificFramePriority(SocketIdx, *ParameterValuePtr);
    break;

  case TCPIP_PARAMID_TTL:
    TcpIp_VSetSocketSpecificTimeToLive(SocketIdx, *ParameterValuePtr);
    break;

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  case TCPIP_PARAMID_V_IPV4_TYPE_OF_SERVICE:
    /* uint8 TypeOfService value, forward to IpV4 */
    IpV4_Ip_SetTypeOfService(SocketIdx, *ParameterValuePtr);
    break;
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  case TCPIP_PARAMID_V_IPV6_FLOW_LABEL:
  {
    /* uint32 FlowLabel value, forward to IpV6 */
    uint32 flowLabelValue = TCPIP_GET_UINT32(ParameterValuePtr, 0u);
    IpV6_SetFlowLabel(SocketIdx, flowLabelValue);
    break;
  }

  case TCPIP_PARAMID_V_IPV6_TRAFFIC_CLASS:
    /* uint8 Traffic Class value, forward to IpV6 */
    IpV6_SetTrafficClass(SocketIdx, *ParameterValuePtr);
    break;
#endif

  case TCPIP_PARAMID_V_PHYS_DEST_ADDR:
    /* This parameter is currently only supported for IpV4. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    IpV4_Ip_SetPhysDestAddr(SocketIdx, ParameterValuePtr);                                                              /* SBSW_TCPIP_MaybeNullPtrParameter */
#endif
    break;

  default:
    parameterIdMatched = FALSE;
    break;
  }

  /* #20 Update *ParameterRetValuePtr, if parameter Id matched. */
  if (parameterIdMatched == TRUE)
  {
    *ParameterRetValuePtr = parameterRetValue;                                                                          /* SBSW_TCPIP_NonNullPtrParameter */
  }

  return parameterIdMatched;
} /* TcpIp_VHandleGenericSocketParameter() */

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_Tls_SetClientCertInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_SetClientCertInfo(
  TcpIp_SocketIdType SocketId,
  TCPIP_P2V(uint8)   CertPtr,
  TCPIP_P2V(uint8)   KeyPtr,
  uint16             CertLen,
  uint16             KeyLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_SOCK_ID;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);
    TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx);
    /* #20 Forward the request to the TLS plugin in case the socket is configured for TLS. */
    if(TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
    {
      retVal = Tls_SetClientCertInfo( SocketId, CertPtr, KeyPtr, CertLen, KeyLen );
    }
    /* else: TLS is not enabled for this socket: Leave retVal at E_NOT_OK */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_SET_CLIENT_CERT_INFO, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_Tls_SetClientCertInfo() */

/**********************************************************************************************************************
 *  TcpIp_Tls_GetNvmBlockIdForUsedRootCert()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetNvmBlockIdForUsedRootCert(
  TcpIp_SocketIdType         SocketId,
  TCPIP_P2V(NvM_BlockIdType) RootCertBlockIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'RootCertBlockIdPtr' */
  else if (RootCertBlockIdPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward the request to the TLS plugin. */
    retVal = Tls_GetNvmBlockIdForUsedRootCert( SocketId, RootCertBlockIdPtr );
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_NVM_BLOCK_FOR_USED_ROOT_CERT, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_Tls_GetNvmBlockIdForUsedRootCert() */

/**********************************************************************************************************************
 *  TcpIp_Tls_RootCertWasModified()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_RootCertWasModified(NvM_BlockIdType NvmBlockId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward the request to the TLS plugin. */
    retVal = Tls_RootCertWasModified( NvmBlockId );
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_ROOT_CERT_WAS_MODIFIED, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
}
#endif  /* (TCPIP_SUPPORT_TLS == STD_ON) */

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/**********************************************************************************************************************
 *  TcpIp_GetLocNetAddr()                                                                                  [DEPRECATED]
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetLocNetAddr(
  TcpIp_LocalAddrIdType        LocalAddrId,
  TCPIP_P2V(TcpIp_NetAddrType) NetAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'NetAddrPtr' */
  else if (NetAddrPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check that parameter 'LocalAddrId' references an IPv4 address. */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  else if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV4(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId)))
  {
    errorId = TCPIP_E_INV_ARG;
  }
# endif
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Forward the request to the related function of the IpV4 submodule. */
    retVal = IpV4_Ip_GetLocNetAddr(TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx), NetAddrPtr);                             /* SBSW_TCPIP_CheckedPtrParameter */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_LOC_NET_ADDR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetLocNetAddr() */

/**********************************************************************************************************************
 *  TcpIp_GetLocNetMask()                                                                                  [DEPRECATED]
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetLocNetMask(
  TcpIp_LocalAddrIdType        LocalAddrId,
  TCPIP_P2V(TcpIp_NetAddrType) NetMaskPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'NetMaskPtr' */
  else if (NetMaskPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check first criterion related to parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  /* Check that parameter 'LocalAddrId' references an IPv4 address. */
  else if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV4(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId)))
  {
    errorId = TCPIP_E_INV_ARG;
  }
# endif
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Forward the request to the related function of the IpV4 submodule. */
    retVal = IpV4_Ip_GetLocNetMask(TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx), NetMaskPtr);                             /* SBSW_TCPIP_CheckedPtrParameter */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_LOC_NET_ADDR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
}  /* TcpIp_GetLocNetMask() */
#endif

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_GetAndResetMeasurementData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetAndResetMeasurementData(
  TcpIp_MeasurementIdxType  MeasurementIdx,
  boolean                   MeasurementResetNeeded,
  TCPIP_P2V(uint32)         MeasurementDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check Measurement Index. */
    if (   (MeasurementIdx != TCPIP_MEAS_DROP_TCP)
        && (MeasurementIdx != TCPIP_MEAS_DROP_UDP)
        && (MeasurementIdx != TCPIP_MEAS_DROP_IPV4)
        && (MeasurementIdx != TCPIP_MEAS_DROP_IPV6)
        && (MeasurementIdx != TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6)
        && (MeasurementIdx != TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4)
        && (MeasurementIdx != TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_TX_BUFFER)
        && (MeasurementIdx != TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER)
        && (MeasurementIdx != TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER)
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
        && (MeasurementIdx != TCPIP_MEAS_VENDOR_SPECIFIC_NR_SA_PAIRS)
        && (MeasurementIdx != TCPIP_MEAS_VENDOR_SPECIFIC_SA_PAIRS)
# endif /* (TCPIP_SUPPORT_IPSEC == STD_ON) */
        && (MeasurementIdx != TCPIP_MEAS_ALL))
    {
      /* Unsupported measurement index. */
      retVal = E_NOT_OK;
    }
    else if (   (MeasurementIdx == TCPIP_MEAS_ALL)
             && (MeasurementDataPtr != NULL_PTR))
    {
      /* Unsupported combination of TCPIP_MEAS_ALL and DataPtr. */
      retVal = E_NOT_OK;
    }
    /* #30 Forward call to Internal function. */
    else
    {
      retVal = TcpIp_VGetAndResetMeasurementData(MeasurementIdx, MeasurementResetNeeded, MeasurementDataPtr);           /* SBSW_TCPIP_MaybeNullPtrParameter */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_AND_RESET_MEAS_DATA, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetAndResetMeasurementData() */

/**********************************************************************************************************************
 *  TcpIp_VGetAndResetMeasurementData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VGetAndResetMeasurementData(
  TcpIp_MeasurementIdxType  MeasurementIdx,
  boolean                   MeasurementResetNeeded,
  TCPIP_P2V(uint32)         MeasurementDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_VENTER_CRITICAL_SECTION();
  /* #10 Copy the counter value of the dropped packets to the given measurement data pointer, if MeasurementDataPtr is not NULL_PTR. */
  if (MeasurementDataPtr != NULL_PTR)
  {
    switch (MeasurementIdx)
    {
# if (TCPIP_SUPPORT_TCP == STD_ON)
    case TCPIP_MEAS_DROP_TCP:
      *MeasurementDataPtr = TcpIp_GetDroppedTcpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                     /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_TX_BUFFER:
      *MeasurementDataPtr = TcpIp_GetDroppedTcpPacketsInsuffTxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);          /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER:
      *MeasurementDataPtr = TcpIp_GetDroppedTcpPacketsInsuffRxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);          /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;
# endif

    case TCPIP_MEAS_DROP_UDP:
      *MeasurementDataPtr = TcpIp_GetDroppedUdpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                     /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4:
      *MeasurementDataPtr = TcpIp_GetDroppedVndrLayer4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);              /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */
    case TCPIP_MEAS_DROP_IPV4:
      *MeasurementDataPtr = TcpIp_GetDroppedIpV4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                    /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER:
      *MeasurementDataPtr = TcpIp_GetDroppedIpV4PacketsInsuffReassemblyBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX); /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;
# endif

# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    case TCPIP_MEAS_DROP_IPV6:
      *MeasurementDataPtr = TcpIp_GetDroppedIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                    /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6:
      *MeasurementDataPtr = TcpIp_GetDroppedVndrIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

# endif

# if (TCPIP_SUPPORT_IPSEC == STD_ON)
    case TCPIP_MEAS_VENDOR_SPECIFIC_NR_SA_PAIRS:
      /* Store the current number of valid Sa entry pairs in current context */
      TcpIp_IpSecSaEntryPairCnt = TcpIp_IpSec_GetNumSaEntryPairs();
      *MeasurementDataPtr = TcpIp_IpSecSaEntryPairCnt;                                                                 /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_SA_PAIRS:
      /* Retrieve the IPsec status */
      /* PRQA S 0310 2 */ /* MD_TCPIP_Rule11.3_0310_Uint32ToStruct */
      retVal = TcpIp_IpSec_GetSaEntryPairsStatus((TcpIp_IpSecSaStatusType *)MeasurementDataPtr, TcpIp_IpSecSaEntryPairCnt);   /* SBSW_TCPIP_ExplicitlyCheckedPtr */
      break;
# endif /* (TCPIP_SUPPORT_IPSEC == STD_ON) */

    default:
      /* Unsupported measurement index. Nothing to do. */
      break;
    }
  }

  /* #20 Reset measurement data counter of dropped packets, if MeasurementResetNeeded is TRUE. */
  if(MeasurementResetNeeded == TRUE)
  {
    switch (MeasurementIdx)
    {
# if (TCPIP_SUPPORT_TCP == STD_ON)
    case TCPIP_MEAS_DROP_TCP:
      TcpIp_SetDroppedTcpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                        /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_TX_BUFFER:
      TcpIp_SetDroppedTcpPacketsInsuffTxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                             /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER:
      TcpIp_SetDroppedTcpPacketsInsuffRxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                             /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;
# endif

    case TCPIP_MEAS_DROP_UDP:
      TcpIp_SetDroppedUdpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                        /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4:
      TcpIp_SetDroppedVndrLayer4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                 /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;

# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */
    case TCPIP_MEAS_DROP_IPV4:
      TcpIp_SetDroppedIpV4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                       /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER:
      TcpIp_SetDroppedIpV4PacketsInsuffReassemblyBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                    /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;
# endif

# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    case TCPIP_MEAS_DROP_IPV6:
      TcpIp_SetDroppedIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                       /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;

    case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6:
      TcpIp_SetDroppedVndrIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                   /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
      retVal = E_OK;
      break;
# endif

    case TCPIP_MEAS_ALL:
      /* #30 Reset all measurement data counter in case of TCPIP_MEAS_ALL. */
      TcpIp_VResetMeasurementData();
      retVal = E_OK;
      break;

    default:
      /* Unsupported measurement index. Nothing to do. */
      break;
    }
  }
  TCPIP_VLEAVE_CRITICAL_SECTION();
  return retVal;
} /* TcpIp_VGetAndResetMeasurementData() */ /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_VResetMeasurementData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_VResetMeasurementData(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset measurement data counter. */

# if (TCPIP_SUPPORT_TCP == STD_ON)
  TcpIp_SetDroppedTcpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                            /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
  TcpIp_SetDroppedTcpPacketsInsuffTxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                 /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
  TcpIp_SetDroppedTcpPacketsInsuffRxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                 /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
# endif

  TcpIp_SetDroppedUdpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                            /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
  TcpIp_SetDroppedVndrLayer4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                     /* SBSW_TCPIP_MEASUREMENTDATA_IDX */

# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */
  TcpIp_SetDroppedIpV4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                           /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
  TcpIp_SetDroppedIpV4PacketsInsuffReassemblyBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                        /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
# endif

# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  TcpIp_SetDroppedIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                           /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
  TcpIp_SetDroppedVndrIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX, 0);                                       /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
# endif
} /* TcpIp_VResetMeasurementData() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif

/**********************************************************************************************************************
 *  TcpIp_GetIpAddr()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetIpAddr(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TCPIP_P2V(TcpIp_SockAddrType) IpAddrPtr,
  TCPIP_P2V(uint8)              NetmaskPtr,
  TCPIP_P2V(TcpIp_SockAddrType) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  else
#endif
  /* Check parameter 'LocalAddrId' */
  if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    /* invalid or any address id: Leave retVal at value E_NOT_OK */
    errorId = TCPIP_E_INV_ARG;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* PRQA S 0310, 3305 2 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */
    TCPIP_P2V(TcpIp_SockAddrBaseType) ipAddrPtr            = (TCPIP_P2V(TcpIp_SockAddrBaseType))IpAddrPtr;
    TCPIP_P2V(TcpIp_SockAddrBaseType) defaultRouterAddrPtr = (TCPIP_P2V(TcpIp_SockAddrBaseType))DefaultRouterPtr;

    /* #20 Check if address family is AF_INET (IPv4). */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    if(TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx))
#endif
    {
      TcpIp_SizeOfLocalAddrV4Type ipV4AddrIdx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx);

      /* #30 Write IpV4 address if requested. */
      if (ipAddrPtr != NULL_PTR)
      {
        ipAddrPtr->sa_family = IPBASE_AF_INET;                                                                          /* SBSW_TCPIP_GetIpAddr_IpAddrPtr */
        retVal = IpV4_Ip_GetLocNetAddr(ipV4AddrIdx, &ipAddrPtr->SockAddrIn.sin_addr);                                   /* SBSW_TCPIP_GetIpAddr_IpAddrPtr */
      }
      else
      {
        retVal = E_OK;
      }

      if (retVal == E_OK)
      {
        /* #40 Write IpV4 netmask if requested. */
        if (NetmaskPtr != NULL_PTR)
        {
          IpBase_AddrInType netmask;

          if (IpV4_Ip_GetLocNetMask(ipV4AddrIdx, &netmask) == E_OK)                                                     /* SBSW_TCPIP_PtrToLocalVariable */
          {
            *NetmaskPtr = TcpIp_VIpV4NetmaskToCidr(netmask);                                                            /* SBSW_TCPIP_ExplicitlyCheckedPtr */
          }
          else
          {
            *NetmaskPtr = 0;                                                                                            /* SBSW_TCPIP_ExplicitlyCheckedPtr */
          }
        }

        /* #50 Write IpV4 default router address if requested. */
        if (defaultRouterAddrPtr != NULL_PTR)
        {
          defaultRouterAddrPtr->sa_family = IPBASE_AF_INET;                                                             /* SBSW_TCPIP_GetIpAddr_DefaultRouterPtr */
          /* Ignore return value of IpV4_Ip_GetDefaultRouterNetAddr() because TcpIp_GetIpAddr() should not return an error if there is no default router. */
          IpV4_Ip_GetDefaultRouterNetAddr(ipV4AddrIdx, &defaultRouterAddrPtr->SockAddrIn.sin_addr);                     /* SBSW_TCPIP_GetIpAddr_DefaultRouterPtr */
        }
      }
    }
#endif
     /* #60 Check if address family is AF_INET6 (IPv6). */
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)
    else
#endif
    {
      TcpIp_SizeOfLocalAddrV6Type ipV6AddrIdx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx);

      /* #70 Write IpV6 address and netmask if requested. */
      if (ipAddrPtr != NULL_PTR)
      {
        ipAddrPtr->sa_family = IPBASE_AF_INET6;                                                                         /* SBSW_TCPIP_GetIpAddr_IpAddrPtr */
        retVal = IpV6_GetLocalAddress(ipV6AddrIdx, &ipAddrPtr->SockAddrIn6.sin6_addr, NetmaskPtr);                      /* SBSW_TCPIP_IpV6_GetLocalAddress */
      }
      else
      {
        retVal = E_OK;
      }

      /* #80 Write IpV6 default router address if requested. */
      if ((retVal == E_OK) && (defaultRouterAddrPtr != NULL_PTR))
      {
        boolean routerIsReachable;
        defaultRouterAddrPtr->sa_family = IPBASE_AF_INET6;                                                              /* SBSW_TCPIP_GetIpAddr_DefaultRouterPtr */
        /* Ignore return value of IpV6_GetDefaultRouterAddress() because TcpIp_GetIpAddr() should not return an error if there is no default router. */
        (void)IpV6_GetDefaultRouterAddress(ipV6AddrIdx, &defaultRouterAddrPtr->SockAddrIn6.sin6_addr, &routerIsReachable);  /* SBSW_TCPIP_IpV6_GetDefaultRouterAddress */
      }
      /* else: No further action requested: Leave retVal on its current value */
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_IP_ADDR, errorId);
  }
#else
  TCPIP_UNUSED_PARAMETER(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return retVal;
} /* TcpIp_GetIpAddr() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_GetRemNetAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetRemNetAddr(
  TcpIp_SocketIdType             SocketId,
  TCPIP_P2V(TcpIp_SockAddrType) *SockAddrPtr)  /* PRQA S 3673 */ /* MD_TCPIP_Rule8.13_CfgSpecific */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check Parameter 'SocketId'. */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_SOCK_ID;
  }
  /* Check parameter 'SockAddrPtr' */
  else if (SockAddrPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (TCPIP_SUPPORT_TCP == STD_ON)
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);

    /* #20 In case it is a TCP socket AND the socket is connected: Store the remote address. */
    if (TCPIP_SOCKET_IDX_IS_TCP(socketIdx))
    {
      if (TcpIp_Tcp_GetSockIsConnected(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx)) == TRUE)
      {
        *SockAddrPtr = &TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->TcpIpSockAddr;                                      /* SBSW_TCPIP_CheckedPtrParameter */
        retVal = E_OK;
      }
      /* else: TCP socket is not connected: Leave retVal at value E_NOT_OK. */
    }
    /* else: No remote socket address is stored for UDP sockets: Leave retVal at value E_NOT_OK. */
#else
    TCPIP_UNUSED_PARAMETER(SocketId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    TCPIP_UNUSED_PARAMETER(SockAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

    /* #30 Reject the request in case only UDP is enabled because in this case no remote addresses are stored. */
    retVal = E_NOT_OK;
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_REM_NET_ADDR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetRemNetAddr() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if (TCPIP_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_GetVersionInfo(
  TCPIP_P2V(Std_VersionInfoType) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'versioninfo' */
  else if (versioninfo == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Write the version info into the struct pointed to by the given pointer. */
    versioninfo->vendorID         = TCPIP_VENDOR_ID;                                                                    /* SBSW_TCPIP_CheckedPtrParameter */
    versioninfo->moduleID         = TCPIP_MODULE_ID;                                                                    /* SBSW_TCPIP_CheckedPtrParameter */
    versioninfo->sw_major_version = TCPIP_SW_MAJOR_VERSION;                                                             /* SBSW_TCPIP_CheckedPtrParameter */
    versioninfo->sw_minor_version = TCPIP_SW_MINOR_VERSION;                                                             /* SBSW_TCPIP_CheckedPtrParameter */
    versioninfo->sw_patch_version = TCPIP_SW_PATCH_VERSION;                                                             /* SBSW_TCPIP_CheckedPtrParameter */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_VERSION_INFO, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
} /* TcpIp_GetVersionInfo() */
#endif
  /* TCPIP_VERSION_INFO_API */

#if TCPIP_SUPPORT_DHCPV4 == STD_ON
/**********************************************************************************************************************
 *  TcpIp_DhcpReadOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpReadOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint8                 Option,
  TCPIP_P2V(uint8)      DataLength,
  TCPIP_P2V(uint8)      DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalIpAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalIpAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
#   if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
  else if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV4(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId)))
  {
    errorId = TCPIP_E_INV_ARG;
  }
#   endif
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_LocalAddrIterType   localAddrIdx   = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId);
    TcpIp_LocalAddrV4IterType localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx);

    /* #20 Forward the request to the DHCPv4 subcomponent. */
    retVal = TcpIp_DhcpV4_VGetTxOption(localAddrV4Idx, Option, DataLength, DataPtr);                                    /* SBSW_TCPIP_CheckedPtrParameter_WithLength */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_SET_DHCP_READ_OPT, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif

  return retVal;
} /* TcpIp_DhcpReadOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpWriteOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpWriteOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint8                 Option,
  uint8                 DataLength,
  TCPIP_P2C(uint8)      DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalIpAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalIpAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
#   if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
  else if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV4(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId)))
  {
    errorId = TCPIP_E_INV_ARG;
  }
#   endif
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_LocalAddrIterType   localAddrIdx   = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId);
    TcpIp_LocalAddrV4IterType localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx);

    /* #20 Forward the request to the DHCPv4 subcomponent. */
    retVal = TcpIp_DhcpV4_VSetTxOption(localAddrV4Idx, Option, DataLength, DataPtr, TCPIP_DHCPV4_MSG_FLAG_ALWAYS);      /* SBSW_TCPIP_CheckedPtrParameter_WithLength */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_SET_DHCP_WRITE_OPT, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif

  return retVal;
} /* TcpIp_DhcpWriteOption() */
#endif /* TCPIP_SUPPORT_DHCPV4 == STD_ON */

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6ReadOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6ReadOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint16                Option,
  TCPIP_P2V(uint16)     DataLength,
  TCPIP_P2V(uint8)      DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalIpAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalIpAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV6(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId)))  /* PRQA S 3415, 2995 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly, MD_TCPIP_Rule14.3_2991_2995 */
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType   localAddrIdx   = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId);
    TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx);

    /* Socket has Unicast or AutoSelect binding. This means use concrete or any IP on concrete controller for transmission */
    /* #20 Forward the request to the DHCPv6 subcomponent. */
    retVal = TcpIp_DhcpV6_VGetTxOption(localAddrV6Idx, Option, DataLength, DataPtr);                                    /* SBSW_TCPIP_CheckedPtrParameter_WithLength */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_SET_DHCP_V6_READ_OPT, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif

  return retVal;
} /* TcpIp_DhcpV6ReadOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6WriteOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6WriteOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint16                Option,
  uint16                DataLength,
  TCPIP_P2C(uint8)      DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalIpAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalIpAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV6(TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId)))  /* PRQA S 3415, 2995 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly, MD_TCPIP_Rule14.3_2991_2995 */
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType   localAddrIdx   = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalIpAddrId);
    TcpIp_SizeOfLocalAddrV6Type localAddrV6Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx);

    /* #20 Forward the request to the DHCPv6 subcomponent. */
    retVal = TcpIp_DhcpV6_VSetTxOption(localAddrV6Idx, Option, DataLength, DataPtr, TCPIP_DHCPV6_MSG_FLAG_ALLWAYS);     /* SBSW_TCPIP_CheckedPtrParameter_WithLength */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_SET_DHCP_V6_WRITE_OPT, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif

  return retVal;
} /* TcpIp_DhcpV6WriteOption() */
# endif
#endif /* TCPIP_SUPPORT_DHCPV6 == STD_ON */

/**********************************************************************************************************************
 *  TcpIp_GetDhcpTimeoutInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_GetDhcpTimeoutInfo(
  uint8 EthIfCtrlIdx,
  uint8 IpVer)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal  = FALSE;
  uint8   errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'CtrlIdx' */
  else if (EthIfCtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
    /* #20 Check the given IP version to be IpV4. */
    if ((IpVer == TCPIP_IP_PROT_VER_4) && (TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      /* #30 Call the internal service function of the DHCPv4 submodule in order to retrieve the timeout status. */
      TcpIp_IpV4CtrlIterType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);

      /* The following function returns the timeout status, directly, i.e.: FALSE: No DHCP timeout occurred, TRUE: A DHCP timeout occurred. */
      retVal = TcpIp_DhcpV4_GetDhcpTimeoutInfo(ipV4CtrlIdx);
    }
    /* else: This case is currently not supported: Leave retVal at value FALSE */
#else
    /* DHCP is not activated, so no timeout can occur: Leave retVal at value FALSE. */
    TCPIP_UNUSED_PARAMETER(IpVer);    /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    TCPIP_UNUSED_PARAMETER(EthIfCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_DHCP_TIMEOUT_INFO, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetDhcpTimeoutInfo() */

/**********************************************************************************************************************
 *  TcpIp_GetIpAddrCfgSrc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetIpAddrCfgSrc(
  TcpIp_LocalAddrIdType  LocalAddrId,
  TCPIP_P2V(uint8)       CfgSrcPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'CfgSrcPtr' */
  else if (CfgSrcPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Check address family. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    if (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx))
#endif
    {
      (*CfgSrcPtr) = IpV4_Ip_GetActiveAddrAssignmentMethod(TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx));                 /* SBSW_TCPIP_CheckedPtrParameter */
      retVal = E_OK;
    }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)
    else
#endif
    {
      (*CfgSrcPtr) = IpV6_GetLocalAddressCfgSrc(TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx));                            /* SBSW_TCPIP_CheckedPtrParameter */
      retVal = E_OK;
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_IP_ADDR_CFG_SRC, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetIpAddrCfgSrc() */

/**********************************************************************************************************************
 *  TcpIp_RequestComMode()
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_RequestComMode(
  uint8            CtrlIdx,
  TcpIp_StateType  State)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'CtrlIdx' */
  else if (CtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'State' */
  else if (State > TCPIP_ACTIVE_STATE_ONLINE)
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check if the requested ComMode is TCPIP_ACTIVE_STATE_ONLINE. */
    if (State == TCPIP_ACTIVE_STATE_ONLINE)
    {
      /* #21 if so, forward the request LINK_STATE_ACTIVE to internal. */
      TcpIp_VRequestComModeInternal(CtrlIdx, ETHTRCV_LINK_STATE_ACTIVE);
    }
    /* #30 Otherwise the requested ComMode is TCPIP_ACTIVE_STATE_OFFLINE || TCPIP_ACTIVE_STATE_ONHOLDE. */
    else
    {
      /* #31 Forward the request LINK_STATE_DOWN to internal. */
      TcpIp_VRequestComModeInternal(CtrlIdx, ETHTRCV_LINK_STATE_DOWN);
    }
    /* Set return value for API compatibility */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_TCP_REQUEST_COM_MODE, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_RequestComMode() */

/**********************************************************************************************************************
 *  TcpIp_GetLocSockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetLocSockAddr(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(TcpIp_SockAddrType) SockPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_SOCK_ID;
  }
  /* Check parameter 'SockPtr' */
  else if (SockPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);
    TCPIP_P2V(TcpIp_SockAddrBaseType) sockAddrPtr = (TCPIP_P2V(TcpIp_SockAddrBaseType))SockPtr;  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */

    /* #20 In case all parameters are valid, copy the desired ones. */
    retVal = IpBase_CopySockAddr(&sockAddrPtr->SockAddr, &TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->SockAddr);        /* SBSW_TCPIP_IpBase_CopySockAddr */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_LOCAL_SOCK_ADDR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetLocSockAddr() */

#if (TCPIP_SUPPORT_DIAG_ACCESS_EXTENSIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DiagDataReadAccess()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DiagDataReadAccess(
  TcpIp_SocketIdType   SocketId,
  TcpIp_DiagParamsType DataID,
  TCPIP_P2V(uint8)     DataPtr,
  TCPIP_P2V(uint16)    DataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SocketId' */
  else if (!TCPIP_SOCKET_ID_IS_VALID(SocketId))
  {
    errorId = TCPIP_E_INV_SOCK_ID;
  }
  /* Check parameter 'DataID' */
  else if (DataID >= TCPIP_DP_INVALID)
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'DataLenPtr' */
  else if (DataLenPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);

    /* #20 In case all parameters are valid, call the internal service function that conducts the desired action. */
    retVal = TcpIp_DiagDataReadAccessInternal(socketIdx, DataID, DataPtr, DataLenPtr);                                  /* SBSW_TCPIP_CheckedPtrParameter_WithLength */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_DIAG_DATA_READ_ACCESS, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* TcpIp_DiagDataReadAccess() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_DiagDataReadAccessInternal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DiagDataReadAccessInternal(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TcpIp_DiagParamsType      DataID,
  TCPIP_P2V(uint8)          DataPtr,
  TCPIP_P2V(uint16)         DataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx < TcpIp_GetSizeOfSocketDyn());

  /* #10 Evaluate the DataID the caller desires to read. */
  switch(DataID)
  {
  case TCPIP_DP_SOCKET_LOCAL_PORT:
    /* ----------------------------------------------------------------------------------------- */
    /* #20 Read the current local port number for a given socket. */
    if(*DataLenPtr >= 2u)
    {
      TCPIP_PUT_UINT16(DataPtr, 0, TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->DomainAndPort.port);                     /* SBSW_TCPIP_NonNullPtrParameter */
      *DataLenPtr = 2;                                                                                                  /* SBSW_TCPIP_NonNullPtrParameter */
      retVal = E_OK;
    }
    break;
# if ((TCPIP_SUPPORT_TCP == STD_ON) && (TCPIP_TCP_DIAG_READ_ACK_SEQ_NUM_ENABLED == STD_ON))
  case TCPIP_DP_SOCKET_TCP_CURRENT_ACK_NUM:
    /* ----------------------------------------------------------------------------------------- */
    /* #30 Read the TCP acknowledgment number that would be used for the next segment for sending. */
    if (TCPIP_SOCKET_IDX_IS_TCP(SocketIdx) && (*DataLenPtr >= 4u))
    {
      TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
      TCPIP_PUT_UINT32_RAW(DataPtr, 0, TcpIp_GetRcvNxtOfSocketTcpDyn(socketTcpIdx));  /* direct access to a TCP variable */  /* SBSW_TCPIP_NonNullPtrParameter */
      *DataLenPtr = 4;                                                                                                  /* SBSW_TCPIP_NonNullPtrParameter */
      retVal = E_OK;
    }
    break;

  case TCPIP_DP_SOCKET_TCP_NEXT_SEQ_NUM:
    /* ----------------------------------------------------------------------------------------- */
    /* #40 Read the TCP sequence number that would be used for the next data segment for sending. */
    if (TCPIP_SOCKET_IDX_IS_TCP(SocketIdx) && (*DataLenPtr >= 4u))
    {
      TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
      TCPIP_PUT_UINT32_RAW(DataPtr, 0, TcpIp_GetTxNextSendSeqNoOfSocketTcpDyn(socketTcpIdx));  /* direct access to a TCP variable */  /* SBSW_TCPIP_NonNullPtrParameter */
      *DataLenPtr = 4;                                                                                                  /* SBSW_TCPIP_NonNullPtrParameter */
      retVal = E_OK;
    }
    break;
# endif
  default:
    /* do nothing */
    break;
  }
  return retVal;
}
#endif  /* (TCPIP_SUPPORT_DIAG_ACCESS_EXTENSIONS == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_ClearARCache()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ClearARCache(
  TcpIp_LocalAddrIdType LocalAddrId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_LocalAddrIterType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Forward call to IPv4 or IPv6 sub module depending on the address type. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    if (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx))
# endif
    {
      /* IpV4 */
      TcpIp_LocalAddrV4IterType localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(localAddrIdx);
      IpV4_Arp_ClearCache(localAddrV4Idx);
      retVal = E_OK;
    }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)
    else
# endif
    {
      /* IpV6 */
      TcpIp_LocalAddrV6IterType localAddrV6Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(localAddrIdx);
      retVal = IpV6_Ndp_ClearCache(localAddrV6Idx);
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_CLEAR_AR_CACHE, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_ClearARCache() */

/**********************************************************************************************************************
 *  TcpIp_GetNdpCacheEntries()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetNdpCacheEntries(
  uint8                              CtrlIdx,
  TCPIP_P2V(uint32)                  NumberOfElementsPtr,  /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
  TCPIP_P2V(TcpIp_NdpCacheEntryType) EntryListPtr)         /* PRQA S 3673 */ /* MD_TcpIp_AutosarApi */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_EthIfCtrlIterType ethIfCtrlIdx = CtrlIdx;

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  /* Check parameter 'TcpIp_State' */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'ethIfCtrlIdx' */
  else if (ethIfCtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else if (TcpIp_IsIpV6CtrlUsedOfEthIfCtrl(ethIfCtrlIdx) == FALSE)
  {
    errorId = TCPIP_E_INV_ARG;
  }
  /* Check parameter 'NumberOfElementsPtr' */
  else if (NumberOfElementsPtr == NULL_PTR)
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'EntryListPtr' dependent on parameter 'NumberOfElementsPtr' */
  else if ((*NumberOfElementsPtr > 0u) && (EntryListPtr == NULL_PTR))
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Return cache entries if IpV6 is supported. */
    TcpIp_IpV6CtrlIterType ipV6CtrlIdx = TcpIp_GetIpV6CtrlIdxOfEthIfCtrl(ethIfCtrlIdx);

    IpV6_Ndp_GetCacheEntries(ipV6CtrlIdx, NumberOfElementsPtr, EntryListPtr);                                           /* SBSW_TCPIP_GetCacheEntries */
    retVal = E_OK;
  }
#else
  uint8 errorId = TCPIP_E_NOT_SUPPORTED;
  TCPIP_UNUSED_PARAMETER(ethIfCtrlIdx);              /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  TCPIP_UNUSED_PARAMETER(NumberOfElementsPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  TCPIP_UNUSED_PARAMETER(EntryListPtr);         /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (TCPIP_SUPPORT_IPV6 == STD_ON) */

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  if (errorId != TCPIP_E_NO_ERROR)
# endif
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_GET_NDP_CACHE_ENTRIES, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* TcpIp_GetNdpCacheEntries() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_IpSecSaEntryPairAdd()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSecSaEntryPairAdd(
  TcpIp_LocalAddrIdType             LocalAddrId,
  TCPIP_P2C(TcpIp_IpSecSaInfoType)  SaInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  /* Check parameter 'TcpIp_State' */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  /* Check parameter 'SaSelPtr' */
  else if (   (SaInfoPtr == NULL_PTR)
           || (SaInfoPtr->KeyMaterial.InboundKeyMatPtr == NULL_PTR)
           || (SaInfoPtr->KeyMaterial.OutboundKeyMatPtr == NULL_PTR)
           || (SaInfoPtr->TrafficSelectors == NULL_PTR))
  {
    errorId = TCPIP_E_PARAM_POINTER;
  }
  /* Check parameter 'LocalAddrId' */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TcpIp_LocalAddrIterType   localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

    /* #20 Add a pair of SA entries using the parameters passed */
    retVal = TcpIp_IpSec_AddSaEntryPair(localAddrIdx, SaInfoPtr);                                                      /* SBSW_TCPIP_ExplicitlyCheckedPtr */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_IPSEC_ADD_SAENTRY_PAIR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_IpSecSaEntryPairDelete()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSecSaEntryPairDelete(
  uint32                       InboundSpi)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  /* Check parameter 'TcpIp_State' */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    errorId = TCPIP_E_NOTINIT;
  }
  else if (InboundSpi == 0u)
  {
    errorId = TCPIP_E_INV_ARG;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Delete a pair of SA entries referenced by the Spi */
    retVal = TcpIp_IpSec_DelSaEntryPair(InboundSpi);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if(errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_IPSEC_DEL_SAENTRY_PAIR, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
}
#endif

/**********************************************************************************************************************
 *  INTERNAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_VPreconfigSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VPreconfigSocket(TcpIp_SocketDynIterType SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 addrFamily;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx < TcpIp_GetSizeOfSocketDyn());

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  TCPIP_ASSERT(sizeof(TcpIp_SockAddrBaseType) == sizeof(TcpIp_SockAddrInet6Type));
  addrFamily = IPBASE_AF_INET6;
#else
  TCPIP_ASSERT(sizeof(TcpIp_SockAddrBaseType) >= sizeof(TcpIp_SockAddrInetType));
  addrFamily = IPBASE_AF_INET;
#endif

  /* #10 Initialize the given socket's admin data for both IP protocols. */
  (void)IpBase_DelSockAddr(&TcpIp_GetAddrRemSockOfSocketDyn(SocketIdx)->SockAddr, addrFamily);                          /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  (void)IpBase_DelSockAddr(&TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->SockAddr, addrFamily);                          /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */


  /* #20 Initialize the given socket connection status. */
  TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_NONE);                                            /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
} /* TcpIp_VPreconfigSocket() */

/**********************************************************************************************************************
 *  TcpIp_VSocketAccessExclusive()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_VSocketAccessExclusive(TcpIp_SizeOfSocketDynType SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx < TcpIp_GetSizeOfSocketDyn());

  /* #10 Enter exclusive area. */
  TCPIP_VENTER_CRITICAL_SECTION();  /* lock interrupts */

  /* #20 Try to obtain semaphore (lock variable) and return result via retVal. */
  if (TcpIp_IsTxBufRequestedOfSocketDyn(SocketIdx) == TRUE)
  {
    retVal = FALSE;
  }
  else
  {
    TcpIp_SetTxBufRequestedOfSocketDyn(SocketIdx, TRUE);                                                                /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
    retVal = TRUE;
  }

  /* #30 Exit exclusive area. */
  TCPIP_VLEAVE_CRITICAL_SECTION();  /* unlock interrupts */

  return retVal;
} /* TcpIp_VSocketAccessExclusive() */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRA_Compliance_MSR.pdf'

   module specific MISRA deviations:

   MD_TCPIP_Rule13.5_3415_CslReadOnly: The right hand operand of a logical && or || operator shall not contain side effects.
     Reason:     No side effects possible because the (inline) function only wraps a read-only access to a variable/constant.
                 Used to justify read-only access to constants/variables via inline function generated by the ComStackLib (CSL). (e.g.: TcpIp_Get*()
                 TcpIp_Is*(),TcpIp_Has*())
     Risk:       None.
     Prevention: Covered by code review.

   MD_TCPIP_Rule13.5_3415_ReadOnly: The right hand operand of a logical && or || operator shall not contain side effects.
     Reason:     Moving function call to extra statement would increase complexity of the code.
                 It is intended that this function is only called if the first check failed (||) / was true (&&).
                 The funtion does not modify any global variables and therefore has no side effects.
     Risk:       Behaviour of the function may be changed in future and the above condition could be not valid anymore.
     Prevention: Covered by code review.

   MD_TcpIp_STCAL_CslAccess: Number of distinct function calls too high (HIS: STCAL = 0..7)
     Reason:     Number of distinct function calls is only too high due to trivial inline functions for accessing the ComStackLib data.
                 Complexity of the function does not increase compared to ComStackLib access via macros.
     Risk:       None. Using inline functions instead of macros for accessing the configuration data does not affect complexity of the code.
     Prevention: n/a

   MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType: Casting to different object pointer type. / Pointer cast to stricter alignment.
     Reason:     TcpIp_SockAddrType is casted to union type TcpIp_SockAddrBaseType in order to avoid further casts to TcpIp_SockAddrInetType and TcpIp_SockAddrInet6Type.
     Risk:       Unaligned memory access may occur if the source buffer is not aligned correctly.
     Prevention: Covered by code review.

   MD_TcpIp_AutosarApi:
     Reason:     This API signature is specified by AUTOSAR and therefore not changed.
     Risk:       None
     Prevention: n/a

   MD_TcpIp_0612_BufferSize: [L] Size of object '-identifier-' exceeds 32767 bytes - program is non-conforming.
     Reason:     Large buffers of this size are only used for testing purposes.
     Risk:       None.
     Prevention: n/a

   MD_TCPIP_Rule11.3_0310_3305_AddrList: Casting to different object pointer type.
     Reason:     Casting from uint8 to IpV6_AddrType type refering to an array of IpV6 addresses of variable size.
     Risk:       Unaligned memory access may occur if the source buffer is not aligned correctly.
     Prevention: Covered by code review.

   MD_TCPIP_Rule11.3_0310_Uint8ToStruct: Casting to different object pointer type.
     Reason:     Casting from uint8 to Struct type.
     Risk:       Unaligned memory access may occur if the data is not aligned correctly.
     Prevention: Covered by code review.

   MD_TCPIP_Rule11.3_0310_CastToUInt8: Casting pointer type of higher alignment to uint8 pointer
     Reason:     The data shall be processed byte wise.
                 1) The EthIf_ProvideTxBuffer provides the buffer as type Eth_DataType which may be uint16 or uint32.
                 2) Pointer is passed as IpV4_Ip_HdrType but following payload is accessed byte wise.
     Risk:       None. The Data is stored in network byte order regardless of the types Eth_DataType and IpV4_Ip_HdrType.
     Prevention: Covered by code review.

   MD_TCPIP_Rule8.13_CfgSpecific: The object addressed by the pointer parameter '...' is not modified and so the pointer could be of type 'pointer to const'.
     Reason:     The parameter is only modified in some preprocessor variants.
     Risk:       The parameter could also be modified in variants where a modification is not intended.
     Prevention: Covered by code review.

   MD_TCPIP_Rule16.3_2003: An unconditional break statement shall terminate every switch-clause
     Reason:     The fall-through is utilized to execute statements which are common to all the switch cases
     Risk:       Cases in the begining might execute unnecessary statements.
     Prevention: Covered by code review.

   MD_TCPIP_Rule1.2_1039: Treating array of length one as potentially flexible member.
     Reason:     The struct is defined so to allow inter-operability between IPv4 and IPv6
     Risk:       None.
     Prevention: Covered by code review.

   MD_TCPIP_Rule11.3_0310_Uint32ToStruct: Casting to different object pointer type.
     Reason:     Casting from uint32 to Struct type to reuse existing public Api
                 for special case
     Risk:       Unaligned memory access may occur if the data is not aligned correctly.
     Prevention: Covered by code review.

   MD_TCPIP_Rule8.9_3218: File scope static, '%s', only accessed in one function.
     Reason:      Vector style guide prevents usage of static variables in function scope
     Risk:        None.
     Prevention:  None.

   MD_TCPIP_Rule2.2_2986: This operation is redundant. The value of the result is always that of the right-hand operand.
     Reason:      The redundant operation is a side effect of a better readability of the code.
     Risk:        None.
     Prevention:  n/a

   MD_TCPIP_Rule14.3_2991_2995: The value of the controlling expression in 'if' statement and logical operation is not always true.
     Reason:      The controlling expression depends on a configuration parameter.
     Risk:        None, because in other configuration it may be false.
     Prevention:  None.

   MD_TCPIP_2843:
     Reason:      A Local parameter prevEleIdx is used to access an array element. This variable is always assigned a valid index by the
                  preceding while loop. It is ensured that this code is only reached if there is atleast one element in the retry queue.
     Risk:        There is no risk.
     Prevention:  Covered by code review.

   MD_TCPIP_2897:
     Reason:      The function parameter LocalAddrIdx is used for TCPIP_LOCAL_ADDR_IDX_TO_IPV6().
                  This macro is used only if the check((TcpIp_GetAddrLocSockOfSocketDyn(newSocketIdx)->sa_family == IPBASE_AF_INET6))around it is true.
                  Caller of this function make sure sa_family is set to IPBASE_AF_INET6. That means the index is IpV6 Index.
                  That's why this macro will never return negative value.
     Risk:        There is no risk.
     Prevention:  Covered by code review.

   MD_TCPIP_2896: Negative value is not cast to unsigned type socketIdx
     Reason:      The Local parameter socketIdx is passed into macro TCPIP_SOCKET_IDX_TO_TCP_IDX to convert socket index to TCP socket index.
                  This line of code is only executed if socket is in state TCPIP_SOCK_CONN_ACTIVE, which is only true for TCP but not for UDP sockets.
                  Hence, there is no chance that the calculated TCP socket index gets negative.
     Risk:        There is no risk.
     Prevention:  Covered by code review.

*/

/* COV_JUSTIFICATION_BEGIN
  \ID COV_TCPIP_IPV4_ALWAYS_ON
  \ACCEPT TX
  \REASON IPv4 is always active in SafeBSW configurations.

  \ID COV_TCPIP_ICMPV4_ALWAYS_ON
  \ACCEPT TX
  \REASON ICMPv4 is always active in SafeBSW configurations.

  \ID COV_TCPIP_DEV_ERROR_DETECT
  \ACCEPT TX
  \REASON TCPIP_DEV_ERROR_DETECT must always be enabled in SafeBSW.

  \ID COV_TCPIP_CANOE_DEBUG
  \ACCEPT XF
  \ACCEPT XF xf xf
  \REASON This code is only active in debug environments.

  \ID COV_TCPIP_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \REASON [COV_MSR_COMPATIBILITY]

  \ID COV_TCPIP_C_COMMENT_VECTOR
  \ACCEPT XF
  \REASON Commented section.

  \ID COV_TCPIP_BYTE_ORDER
  \ACCEPT XF
  \REASON Only little endian byte-order is tested.

  \ID COV_TCPIP_UNIT_TEST
  \ACCEPT TX
  \REASON Code is only inactive in unit test environment.

  \ID COV_TCPIP_RUNTIME_TEST
  \ACCEPT XF xf xx
  \REASON Code in only active in runtime test environment.

COV_JUSTIFICATION_END */

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_CSL_IDX_FROM_CALLER
    \DESCRIPTION       The function writes into the CSL array at a position that is given by the index parameter.
    \COUNTERMEASURE \N The caller ensures that the index is within the valid range by using the TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_CSL_IDX_CHECKED
    \DESCRIPTION       The function writes into the CSL array at a position that is given by the index parameter.
    \COUNTERMEASURE \R The function ensures that the index is within the valid range by using the TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_WriteUInt
    \DESCRIPTION       The function writes 2/4 bytes beginning at the position in the buffer provided by the caller (&BufferPtr[BufferPos]).
                       TcpIp_WriteUInt16(): 2
                       TcpIp_WriteUInt32(): 4
    \COUNTERMEASURE \N The caller ensures that there are 2/4 bytes available at &BufferPtr[BufferPos].

  \ID SBSW_TCPIP_WritePhysAddr
    \DESCRIPTION       The function writes exactly 6 bytes (a physical address).
    \COUNTERMEASURE \N The caller ensures that there are at least 6 bytes available at the referenced memory location.

  \ID SBSW_TCPIP_CslIteration
    \DESCRIPTION       Access of ComStackLib generated array with bounds check using TcpIp_GetSizeOf...() function.
                       Arrays that differ only in the suffix 'Dyn' are modeled by
                       VarIndirectableSizeByConstIndirecableRelation and always have the same size.
                       TcpIp_GetSizeOf<Array>() == TcpIp_GetSizeOf<Array>Dyn().
                       Therefore access of array ...Of<Array>Dyn(idx) is valid if idx was checked against TcpIp_GetSizeOf<Array>().
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib. (boundary check)
                       Qualified use-case CSL02 of ComStackLib. (same size relation)

  \ID SBSW_TCPIP_CheckedPtrPassedToSubroutine
    \DESCRIPTION       Pointer parameter is passed unmodified to a subfunction.
    \COUNTERMEASURE \R Pointer parameter is checked by SafeBSW check within this function.

  \ID SBSW_TCPIP_SocketIdx_1
    \DESCRIPTION       Access of array SocketDyn[] with range [0..TcpIp_GetSizeOfSocketUdpDyn()-1] or [TcpIp_GetSizeOfSocketUdpDyn()..TcpIp_GetSizeOfSocketDyn()-1].
                       The access may also be done by retrieving the address of the element using the ComStackLib TcpIp_GetAddr...() and writing to that address.
    \COUNTERMEASURE \N The array SocketDyn[] contains all UDP sockets followed by all TCP sockets: TcpIp_GetSizeOfSocketDyn() = TcpIp_GetSizeOfSocketUdpDyn() + TcpIp_GetSizeOfSocketTcpDyn().
                       Therefore TcpIp_GetSizeOfSocketUdpDyn() is never bigger than TcpIp_GetSizeOfSocketDyn().
                       TcpIp_GetSizeOfSocketDyn() is generated by the CSL: Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_NonNullPtrParameter
    \DESCRIPTION       Unmodified pointer parameter is used.
    \COUNTERMEASURE \N The caller ensures that the pointer parameter is not NULL_PTR and points to a valid memory location.

  \ID SBSW_TCPIP_CheckedPtrParameter
    \DESCRIPTION       Unmodified pointer parameter is used.
    \COUNTERMEASURE \N The caller ensures that the pointer parameter points to a valid memory location.
                       An additional runtime check ensures that the pointer is not a NULL_PTR.

  \ID SBSW_TCPIP_CheckedPtrParameter_WithLength
    \DESCRIPTION       Unmodified pointer parameter and corresponding length parameter is used.
    \COUNTERMEASURE \N The caller ensures that the pointer parameter points to a valid memory location and the length
                       parameter specifies the number of bytes at the pointer destination.
                       An additional runtime check ensures that the pointer is not a NULL_PTR.

  \ID SBSW_TCPIP_ExplicitlyCheckedPtr
    \DESCRIPTION       A pointer is written or passed to a function that may write at the pointer location.
    \COUNTERMEASURE \R A runtime check verifies that the pointer is not NULL_PTR.

  \ID SBSW_TCPIP_PtrToLocalVariable
    \DESCRIPTION       A pointer to a local (stack) variable is passed to a subfunction.
    \COUNTERMEASURE \N The pointer points to valid memory on the stack.

  \ID SBSW_TCPIP_SocketIdxFromCheckedSocketId
    \DESCRIPTION       Access of array using index socketIdx which is resolved via TCPIP_SOCKET_ID_TO_IDX(SocketId).
                       TCPIP_SOCKET_ID_TO_IDX() is a direct mapping: socketIdx == SocketId.
                       The parameter SocketId is checked by a SafeBSW check via the macro TCPIP_SOCKET_ID_IS_VALID(SocketId) = (SOCKET_ID) < TcpIp_GetSizeOfSocketDyn().
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_TcpIdxFromCheckedSocketIdx
    \DESCRIPTION       Access of SocketTcp(Dyn)[] array using TCP socket index which is derived from generic (UDP/TCP) socket index using the
                       macro TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx). -> SocketTcpIdx == SocketIdx - TcpIp_GetSizeOfSocketUdpDyn().
                       1: SocketIdx is checked for validity: SocketIdx < TcpIp_GetSizeOfSocketDyn()
                       2: TcpIp_GetSizeOfSocketDyn() = TcpIp_GetSizeOfSocketUdpDyn() + TcpIp_GetSizeOfSocketTcpDyn()
                       3: SocketIdx is checked to be a TCP socket: TCPIP_SOCKET_IDX_IS_TCP(SocketIdx) -> SocketIdx >= TcpIp_GetSizeOfSocketUdpDyn()
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_SocketIdxFromValidTcpIdx
    \DESCRIPTION       Access of Socket(Dyn)[] array using socket index which is derived from a TCP socket index using the
                       macro TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx). -> SocketIdx = SocketTcpIdx + TcpIp_GetSizeOfSocketUdpDyn().
                       The access may also be done by retrieving the address of the element using the ComStackLib TcpIp_GetAddr...() and writing to that address.
                       1: SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn() (Checked by caller)
                       2: TcpIp_GetSizeOfSocketDyn() = TcpIp_GetSizeOfSocketUdpDyn() + TcpIp_GetSizeOfSocketTcpDyn()
                       3: SocketIdx < TcpIp_GetSizeOfSocketDyn()
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_SocketIdxFromValidUdpIdx
    \DESCRIPTION       Access of Socket(Dyn)[] array using socket index which is derived from a UDP socket index using the
                       macro TCPIP_UDP_IDX_TO_SOCKET_IDX(SocketUdpIdx). -> SocketIdx == SocketUdpIdx
                       1: SocketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn()
                       2: TcpIp_GetSizeOfSocketDyn() = TcpIp_GetSizeOfSocketUdpDyn() + TcpIp_GetSizeOfSocketTcpDyn()
                       3: SocketIdx < TcpIp_GetSizeOfSocketDyn()
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_MaybeNullPtrParameter
    \DESCRIPTION       A pointer that may be NULL_PTR is passed unmodified to a subroutine.
    \COUNTERMEASURE \N The callee explicitely allows the value NULL_PTR and handles this case correctly.

  \ID SBSW_TCPIP_SockAddrBaseType
    \DESCRIPTION       CONCEPT: AUTOSAR uses the structures TcpIp_SockAddrInetType and TcpIp_SockAddrInet6Type for
                       storage of a socket address. A socket address consists of an IP(v4/v6) address and a port.
                       For a generic representation of IPv4 addresses (32bit) and IPv6 addresses (128bit) a pointer to
                       the specific structures is casted to the generic type TcpIp_SockAddrType*. This pointer is
                       passed to the TcpIp APIs. The member 'domain' (uint16) overlaps with a member of the same name in
                       the structures TcpIp_SockAddrInetType and TcpIp_SockAddrInet6Type.
                       The TcpIp evaluates the 'domain' member of the TcpIp_SockAddrType structure and then casts the
                       pointer to the specific structure again.
                       In order to avoid massive casting of the structures inside the TcpIp a TcpIp_SockAddrBaseType is
                       used which combines the other structures in a union.
                       The memory referenced by a TcpIp_SockAddrType* is at least sizeof(TcpIp_SockAddrInetType) and
                       may be sizeof(TcpIp_SockAddrInet6Type) if the 'domain' member indicates an IPv6 address.
    \COUNTERMEASURE \R The members 'sin_addr' and 'sin6_addr' are only accessed after evaluating the
                       sin_family/sin6_family member.

  \ID SBSW_TCPIP_UdpTransmitInternalVerify
    \DESCRIPTION       1: Argument RemoteAddrPtr is casted to TcpIp_SockAddrBaseType and passed to subroutine.
                          See SBSW_TCPIP_SockAddrBaseType for explanation of the cast.
                       2: Parameters DataPtr (which may be NULL_PTR) and TotalLength are passed unmodified to subroutine.
    \COUNTERMEASURE \N 1: The caller ensures that RemoteAddrPtr points to valid memory.
                          The member 'domain' of the type TcpIp_SockAddrType indicates the size of the underlying datatype.
                          The caller ensures that the underlying datatype is at least as big as IpBase_SockAddrInType.
                          If domain is AF_INET6 the caller ensures that the underlying datatype is IpBase_SockAddrIn6Type.
                          TcpIp_SockAddrBaseType is a union of all valid datatypes that can be referenced by a TcpIp_SockAddrType.
                       2: The caller ensures that DataPtr is NULL_PTR or points to at least TotalLength bytes of valid memory.

  \ID SBSW_TCPIP_UdpTransmitInternal
    \DESCRIPTION       1: Argument RemoteSockAddrPtr is passed unmodified to subroutine.
                       2: Arguments DataPtr (which may be NULL_PTR) and DataLen are passed unmodified to subroutine.
    \COUNTERMEASURE \N 1: The caller ensures that RemoteSockAddrPtr points to valid memory.
                       2: The caller ensures that DataPtr is NULL_PTR or points to at least DataLen bytes of valid memory.

  \ID SBSW_TCPIP_UdpTransmitInternal_Copy_1
    \DESCRIPTION       The buffer udpPayloadPtr is obtained from the IpV4 or IpV6 submodule.
                       Since currently only IpV4 is qualified for SafeBSW only the buffer provision for IpV4 is documented here:
                       During the first iteration the parameters udpPayloadPtr and udpPayloadBufferLen are valid if TcpIp_Udp_RequestTxBuffer() returned BUFREQ_OK.
                       In subsequent iterations the buffers are valid if TcpIp_Udp_FragmentRequestTxBuffer returned E_OK.
                       IpV4_Ip_ProvideTxBuffer provides a valid pointer to an EthIf TX buffer and it's length if the return value is BUFREQ_OK.
                       The buffer is internally obtained from IpV4_Ip_VFragmentProvideTxBuffers which obtains one (or more in case of IP fragmentation) TX buffers from the EthIf.
                       The index, data pointer and length of the separate buffer segments are stored in the Buf2TxReqMap structure.
                       If multiple buffers are provided the buffers are linked inside the Buf2TxReqMap structure.

                       The index, pointer and length to the first buffer is stored in IpTxReqDescrPtr.
                       The buffers are valid if EthIf_ProvideTxBuffer returned BUFREQ_OK and only in this case IpV4_Ip_ProvideTxBuffer will return BUFREQ_OK.
                       TcpIp_Udp_FragmentRequestTxBuffer() only returns E_OK if the linked list inside the Buf2TxReqMap contains one more valid buffer.
                       Argument DataPtr is const and cannot be changed by the called function.
    \COUNTERMEASURE \R The pointer is only used if TcpIp_Udp_RequestTxBuffer()/TcpIp_Udp_FragmentRequestTxBuffer() returned a positive result.

  \ID SBSW_TCPIP_UdpTransmitInternal_Copy_2
    \DESCRIPTION       Usage of argument udpPayloadPtr and *udpTxDataLen (equals udpPayloadBufferLen) is similar to SBSW_TCPIP_UdpTransmitInternal_Copy_1.
                       Pointer &udpTxDataLen references a local variable on the stack.
    \COUNTERMEASURE \N Argument &udpTxDataLen points to valid memory on the stack.

  \ID SBSW_TCPIP_Udp_RequestTxBuffer
    \DESCRIPTION       1: Argument RemoteSockAddrPtr is passed unmodified to subroutine.
                       2: Pointer to local variables udpPayloadPtr and udpPayloadBufferLen are passed to subroutine.
    \COUNTERMEASURE \N 1: The caller ensures that RemoteSockAddrPtr points to valid memory.
                       2: The pointer points to valid memory on the stack.

  \ID SBSW_TCPIP_Udp_FragmentRequestTxBuffer
    \DESCRIPTION       Pointer to local variables udpPayloadPtr and udpPayloadBufferLen are passed to subroutine.
    \COUNTERMEASURE \N The pointer points to valid memory on the stack.

  \ID SBSW_TCPIP_IpV6_Icmp_TxRawMessage
    \DESCRIPTION       1: Argument &ipV6AddrIdx references local (stack) variable.
                       2: Argument &remoteAddrPtr->SockAddrIn6.sin6_addr is derived from unmodified pointer parameter.
                       3: Argument DataPtr and DataLength passed unmodified to subroutine.
    \COUNTERMEASURE \N 1: The pointer points to valid memory on the stack.
                       2 and 3: The caller ensures that pointer and length are valid.

  \ID SBSW_TCPIP_BindInternal
    \DESCRIPTION       1: Argument PortPtr is passed unmodified to subroutine.
                       2: Argument &errorId references local (stack) variable.
    \COUNTERMEASURE \N 1: The caller ensures that PortPtr is valid.
                       2: The pointer points to valid memory on the stack.

  \ID SBSW_TCPIP_RequestIpAddrAssignmentInternal
    \DESCRIPTION       Arguments LocalIpAddrPtr and DefaultRouterPtr are casted to TcpIp_SockAddrBaseType.
                       See SBSW_TCPIP_SockAddrBaseType for explanation of the cast.
                       Both pointers may be NULL_PTR.
    \COUNTERMEASURE \N The caller ensures that LocalIpAddrPtr and DefaultRouterPtr are valid or NULL_PTR.

  \ID SBSW_TCPIP_IpV6_Ip_RequestIpAddrAssignment
    \DESCRIPTION       Arguments localIpAddrPtr and defaultRouterAddrPtr will be NULL_PTR or derived from parameters LocalIpAddrPtr, DefaultRouterPtr.
    \COUNTERMEASURE \N The caller ensures that LocalIpAddrPtr and DefaultRouterPtr are valid or NULL_PTR.

  \ID SBSW_TCPIP_GetCacheEntries
    \DESCRIPTION       Arguments NumberOfElementsPtr and EntryListPtr that may be NULL_PTR are passed unmodified to subroutine.
    \COUNTERMEASURE \R The caller ensures that NumberOfElementsPtr and EntryListPtr are valid or NULL_PTR.
                       There is a runtime check that verifies if NULL_PTR value is allowed.

  \ID SBSW_TCPIP_VHandleGenericSocketParameter
    \DESCRIPTION       1: Argument ParameterValue is passed unmodified to subroutine.
                       2: Argument &retVal references a local (stack) variable.
    \COUNTERMEASURE \N 1: The caller ensures that ParameterValue is valid.
                       2: The pointer points to valid memory on the stack.

  \ID SBSW_TCPIP_GetIpAddr_IpAddrPtr
    \DESCRIPTION       Variable ipAddrPtr is derived from parameter IpAddrPtr which may be NULL_PTR.
    \COUNTERMEASURE \R The caller ensures that parameter IpAddrPtr is NULL_PTR or points to valid memory.
                       A runtime check verifies that ipAddrPtr is != NULL_PTR.

  \ID SBSW_TCPIP_GetIpAddr_DefaultRouterPtr
    \DESCRIPTION       Variable defaultRouterAddrPtr is derived from parameter DefaultRouterPtr which may be NULL_PTR.
    \COUNTERMEASURE \R The caller ensures that parameter DefaultRouterPtr is NULL_PTR or points to valid memory.
                       A runtime check verifies that defaultRouterAddrPtr is != NULL_PTR.

  \ID SBSW_TCPIP_IpV6_GetLocalAddress
    \DESCRIPTION       1: Argument ipAddrPtr is derived from parameter IpAddrPtr which may be NULL_PTR.
                       2: Argument NetmaskPtr is passed unchanged to subroutine.
    \COUNTERMEASURE \R 1: The caller ensures that parameter IpAddrPtr is NULL_PTR or points to valid memory.
                          A runtime check verifies that ipAddrPtr is != NULL_PTR.
                       2: The caller ensures that parameter NetmaskPtr is NULL_PTR or points to valid memory.
                          The called subroutine allows NetmaskPtr to be NULL_PTR.

  \ID SBSW_TCPIP_IpV6_GetDefaultRouterAddress
    \DESCRIPTION       1: Argument defaultRouterAddrPtr is derived from parameter DefaultRouterPtr which may be NULL_PTR.
                       2: Argument routerIsReachable references a local (stack) variable.
    \COUNTERMEASURE \R 1: The caller ensures that parameter DefaultRouterPtr is NULL_PTR or points to valid memory.
                          A runtime check verifies that defaultRouterAddrPtr is != NULL_PTR.
                       2: The pointer points to valid memory on the stack.

  \ID SBSW_TCPIP_IpBase_CopySockAddr
    \DESCRIPTION       1: Argument &sockAddrPtr->SockAddr is derived from parameter SockPtr which is casted to TcpIp_SockAddrBaseType.
                          See SBSW_TCPIP_SockAddrBaseType for explanation of the cast.
                       2: Argument &TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->SockAddr is a const pointer.
    \COUNTERMEASURE \N 1: The caller ensures that parameter SockPtr points to valid memory.
                       2: The const pointer cannot be written in the called function.

  \ID SBSW_TCPIP_ConstPtr
    \DESCRIPTION       A constant pointer is passed to a subroutine.
    \COUNTERMEASURE \N The subroutine cannot write to a const pointer.

  \ID SBSW_TCPIP_RANDOM_NUMBER_FUNC
    \DESCRIPTION        Function pointer is accessed in order to calculate random number by user callout function.
    \COUNTERMEASURE \M  Function pointer is based on mandatory configuration of function name parameter and checked by MSSV plugin:
                        CM_TCPIP_RANDOM_NUMBER_FUNC

  \ID SBSW_TCPIP_FUNC_PTR_CALL
    \DESCRIPTION        Optional function pointer is used in order to notify customer function.
    \COUNTERMEASURE \R  The optional function pointer is checked against NULL_PTR within local function and handled properly.

  \ID SBSW_TCPIP_MEASUREMENTDATA_IDX
    \DESCRIPTION        Array write access with fixed index: TCPIP_MEASUREMENTDATA_IDX (0u).
    \COUNTERMEASURE \N  The MeasurementData structure is generated as array with fixed size '1'. If the access functions
                        are available, they can be accessed by the fixed index: TCPIP_MEASUREMENTDATA_IDX

   SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp.c
 *********************************************************************************************************************/
