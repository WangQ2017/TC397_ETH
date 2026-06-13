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
/**        \file  SoAd_TcpIp.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component TcpIp.
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

#define SOAD_TCPIP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_TcpIp.h"
#include "SoAd_SoCon.h"
#include "SoAd_Util.h"
#include "SoAd_Measure.h"

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# include "TcpIp.h"
#else
# include "SoAd_Cbk.h"
# include "SoAd_EventQueue.h"
# include "SoAd_Tx.h"
# include "IpBase.h"
# include "vstdlib.h"
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Indicates that no flags shall be set in case of transmission over BSD-like Socket API. */
#define SOAD_ZERO_FLAGS                            (0x00)

/*! Offset in IPv6 address where ScopeId is stored on BSD-like Socket API. */
#define SOAD_ADDR_IF_OFFSET                        (2u)

/*! Negative return value in case of BSD-like Socket API. */
#define SOAD_E_BSD_NOT_OK                          (-1)

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_1 */
/*! Invalid network interface index in case of INTEGRITY Socket API. */
# define SOAD_INTEGRITY_INV_INTEGRITY_IF_IDX       (-1)

/*! Invalid Integrity SocketId in case of INTEGRITY Socket API */
# define SOAD_INTEGRITY_INV_INTEGRITY_SOCKET_ID    (-1)

#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

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

#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
# define SOAD_START_SEC_VAR_NOINIT_32BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/*! Indicates the counter for local IP address availability check interval. */
VAR(uint32, SOAD_VAR_NOINIT) SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter;

# define SOAD_STOP_SEC_VAR_NOINIT_32BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityInit()
 *********************************************************************************************************************/
/*! \brief      Initializes all variables specific to INTEGRITY Socket API.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityInit(void);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityHandleLocalAddressCheckInterval()
 *********************************************************************************************************************/
/*! \brief      Handles local IP address check availability interval for INTEGRITY Socket API.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityHandleLocalAddressCheckInterval(void);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable()
 *********************************************************************************************************************/
/*! \brief      Checks if the local IP address of the passed INTEGRITY socket is available.
 *  \details    -
 *  \param[in]  IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                   [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \return     TRUE                 Local address is available.
 *  \return     FALSE                Local address is not available.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityAddrIsEqual()
 *********************************************************************************************************************/
/*! \brief      Checks if the passed IP addresses are equal.
 *  \details    -
 *  \param[in]  OsSockAddrPtr        IP address in INTEGRITY format and Network-Byte-Order.
 *                                   [Points to one of the following structs depending on configured IP address version
 *                                   of parameter SoConIdx:
 *                                     - SoAd_SockAddrInetType for IPv4
 *                                     - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]  SoAdIpAddressPtr     IP address in SoAd internal format and Network-Byte-Order.
 *  \param[in]  SoAdIpAddressDomain  Domain of the passed SoAd IP address.
 *                                   [range: SOAD_AF_INET, SOAD_AF_INET6]
 *  \return     TRUE                 The passed IP addresses are equal.
 *  \return     FALSE                The passed IP addresses are not equal.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegrityAddrIsEqual(
  P2CONST(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) OsSockAddrPtr,
  P2CONST(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) SoAdIpAddressPtr,
  SoAd_DomainType SoAdIpAddressDomain);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetPhysAddr()
 *********************************************************************************************************************/
/*! \brief      Returns the physical address (MAC address) of a local interface.
 *  \details    The implementation uses API calls that are present on a INTEGRITY operating system.
 *  \param[in]  SoConIdx      Socket connection index.
 *  \param[out] PhysAddrPtr   Pointer to physical address.
 *  \return     E_OK          The physical address was stored in the passed buffer.
 *  \return     E_NOT_OK      The physical address could not be resolved.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetIpAddrOfIf()
 *********************************************************************************************************************/
/*! \brief      Gets the IP address of the passed INTEGRITY network interface in Network-Byte-Order.
 *  \details    -
 *  \param[in]  NetworkIfIdx  Index of the INTEGRITY network interface.
 *  \param[in]  Domain        Domain of the requested IP address.
 *                            [range: SOAD_AF_INET, SOAD_AF_INET6]
 *  \param[out] IpAddrPtr     Pointer to the IP address.
 *  \return     E_OK          The IP address was stored in the passed buffer.
 *  \return     E_NOT_OK      The IP address could not be resolved.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetIpAddrOfIf(
  sint32 NetworkIfIdx,
  SoAd_DomainType Domain,
  P2VAR(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf()
 *********************************************************************************************************************/
/*! \brief      Gets the IPv4 address of the passed INTEGRITY network interface in Network-Byte-Order.
 *  \details    -
 *  \param[in]  IfNamePtr      Name of the network interface.
 *  \param[out] IPv4IfAddrPtr  The IPv4 address assigned to the passed interface.
 *  \return     E_OK           Successfully retrieved the IPv4 address of the passed interface.
 *  \return     E_NOT_OK       Failed to retrieve the IPv4 address of the passed interface.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf(
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) IfNamePtr,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR)  IPv4IfAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetIPv6AddrOfIf()
 *********************************************************************************************************************/
/*! \brief      Gets the IPv6 address of the passed network interface in Network-Byte-Order.
 *  \details    -
 *  \param[in]  IfNamePtr      Name of the network interface.
 *  \param[out] IPv6IfAddrPtr  The IPv6 address assigned to the passed interface.
 *  \return     E_OK           Successfully retrieved the IPv6 address of the passed interface.
 *  \return     E_NOT_OK       Failed to retrieve the IPv6 address of the passed interface.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetIPv6AddrOfIf(
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) IfNamePtr,
  P2VAR(SoAd_IpAddrInet6Type, AUTOMATIC, SOAD_APPL_VAR)  IPv6IfAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityCloseAllMappedSockets()
 *********************************************************************************************************************/
/*! \brief      Closes all SoAd Sockets mapped to the passed INTEGRITY socket.
 *  \details    -
 *  \param[in]  IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                   [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityCloseAllMappedSockets(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityClose()
 *********************************************************************************************************************/
/*! \brief        Closes the passed socket.
 *  \details      -
 *  \param[in]    SocketIdx   Module internal socket index.
 *                            [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityClose(
  SoAd_SizeOfSocketType SocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityPrepareSocket()
 *********************************************************************************************************************/
/*! \brief        Prepares an INTEGRITY socket for usage with the passed SoCon.
 *  \details      Either get a new INTEGRITY socket or use the matching existing one and map it to the SoAd socket of
 *                the passed SoCon. Returns the SocketId as SoAd internal handle.
 *  \param[in]    SoConIdx     Socket connection index.
 *                             [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   SocketIdPtr  Pointer to socket identifier.
 *  \return       E_OK         Preparation of INTEGRITY Socket succeeded.
 *                E_NOT_OK     Preparation of INTEGRITY Socket failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityPrepareSocket(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_DATA) SocketIdPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityBind()
 *********************************************************************************************************************/
/*! \brief         Binds the passed socket of the passed SoCon.
 *  \details       -
 *  \param[in]     SoConIdx     Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]     SocketId     Socket identifier.
 *  \param[in,out] PortPtr      In:  Requested Port number of the passed socket or Wildcard (SOAD_PORT_ANY)
 *                              Out: Port number assigned to the passed socket.
 *  \return        E_OK         Bind was successful.
 *                 E_NOT_OK     Bind failed.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *  \note          Port has to be provided and is returned in Network-Byte-Order.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityBind(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetSocketFromOs()
 *********************************************************************************************************************/
/*! \brief        Gets a new Socket resource from the INTEGRITY Os for the passed INTEGRITY Socket.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \return       SOAD_INV_SOCKET_ID   Failed to retrieve a new Socket from INTEGRITY Os.
 *                other values         The Socket identifier assigned from INTEGRITY Os.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(sint32, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetSocketFromOs(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityBindSocket()
 *********************************************************************************************************************/
/*! \brief        Binds the INTEGRITY Os socket mapped to the passed INTEGRITY Socket.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \param[in]    SoConIdx             Socket connection index.
 *                                     [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return       E_OK                 Bind succeeded.
 *                E_NOT_OK             Bind failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityBindSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  SoAd_SizeOfSoConType SoConIdx);

# if ( SOAD_IPV6 == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityIPv6EnableBroadcast()
 *********************************************************************************************************************/
/*! \brief        Enables IPv6 Broadcast reception on the passed INTEGRITY Os Socket.
 *  \details      -
 *  \param[in]    OsSocketId      INTEGRITY Os Socket identifier.
 *  \param[in]    IntegrityIfIdx  Index of the INTEGRITY network interface.
 *  \return       E_OK            Successfully enabled broadcast reception.
 *                E_NOT_OK        Failed to enable broadcast reception.
 *  \pre          OsSocketId has to be a valid INTEGRITY Os Socket handle for a Os Socket bound to the passed If.
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different handles
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY & SOAD_IPV6
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityIPv6EnableBroadcast(
  SoAd_SocketIdType OsSocketId,
  sint32 IntegrityIfIdx);
# endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetPortOfSocket()
 *********************************************************************************************************************/
/*! \brief        Gets the Port number assigned to the passed INTEGRITY Socket.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \param[out]   PortPtr              Pointer to where to store the port number assigned to the passed
 *                                     INTEGRITY Socket.
 *  \return       E_OK                 Successfully retrieved the assigned port number.
 *                E_NOT_OK             Failed to retrieve the assigned port number.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetPortOfSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityUpdateMulticastFilter()
 *********************************************************************************************************************/
/*! \brief        Updates the IP multicast reception filter of the passed INTEGRITY Socket.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \param[in]    LocalAddrIdx         Module internal handle of the local address.
 *  \param[in]    AddToFilter          TRUE:  Add the multicast address to the reception filter.
 *                                     FALSE: Remove the multicast address from the reception filter.
 *  \return       E_OK                 Successfully updated the multicast filter.
 *                E_NOT_OK             Failed to update the multicast filter.
 *  \pre          LocalAddrIdx has to identify a multicast address.
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityUpdateMulticastFilter(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  SoAd_SizeOfLocalAddrType LocalAddrIdx,
  boolean AddToFilter);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetMatchingOrFreeSocket()
 *********************************************************************************************************************/
/*! \brief        Gets an INTEGRITY Socket which matches the passed socket connection and port or a free one.
 *  \details      Checks if an INTEGRITY Socket which matches the settings of the passed socket connection and port
 *                is already in use. If so, this INTEGRITY Socket is returned. Otherwise a free INTEGRITY Socket will
 *                be reserved and returned. In case of Port == SOAD_ANY_PORT, a new INTEGRITY Socket is used.
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \param[in]    Port          Module internal handle of the local address in Network-Byte-Order.
 *  \param[in]    AddToFilter   TRUE:  Add the multicast address to the reception filter.
 *                              FALSE: Remove the multicast address from the reception filter.
 *  \return       E_OK          Successfully updated the multicast filter.
 *                E_NOT_OK      Failed to update the multicast filter.
 *  \pre          LocalAddrIdx has to identify a multicast address.
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfIntegritySocketDynType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetMatchingOrFreeSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PortType Port);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetMappedOrFreeSocket()
 *********************************************************************************************************************/
/*! \brief        Gets the INTEGRITY Socket mapped to the passed SoAd Socket or reserves a free one.
 *  \details      -
 *  \param[in]    SocketIdx    Module internal Socket index.
 *                             [range: SocketIdx < SoAd_GetSizeOfSocket()]
 *  \return       SoAd_GetSizeOfIntegritySocketDyn()  No INTEGRITY Socket mapped and no free socket available.
 *                other values                        Index of the mapped or the reserved INTEGRITY socket.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfIntegritySocketDynType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetMappedOrFreeSocket(
  SoAd_SizeOfSocketType SocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegritySocketIsEqual()
 *********************************************************************************************************************/
/*! \brief        Checks if the passed INTEGRITY Socket matches the passed criteria.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \param[in]    Port                 Requested Port number.
 *  \param[in]    Domain               IP domain (IPv4/6)
 *  \param[in]    NetworkIfIdx         Requested INTEGRITY network interface index.
 *  \param[in]    Protocol             Transport protocol (UDP/TCP)
 *  \return       TRUE                 Passed INTEGRITY Socket matches the passed criteria.
 *  \return       FALSE                Passed INTEGRITY Socket does not match the passed criteria.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegritySocketIsEqual(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  SoAd_PortType Port,
  SoAd_DomainType Domain,
  sint32 NetworkIfIdx,
  SoAd_ProtocolType Protocol);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetFreeSocket()
 *********************************************************************************************************************/
/*! \brief        Gets and reserves a free INTEGRITY Socket.
 *  \details      -
 *  \return       SoAd_GetSizeOfIntegritySocketDyn()   No free INTEGRITY Socket available.
 *  \return       other values                         Index of the free and now reserved INTEGRITY Socket.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfIntegritySocketDynType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetFreeSocket(void);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityRemoveFromFreeSocket()
 *********************************************************************************************************************/
/*! \brief        Removes the passed INTEGRITY Socket from the list of free INTEGRITY Sockets.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityRemoveFromFreeSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityAddToUsedSocket()
 *********************************************************************************************************************/
/*! \brief        Adds the passed INTEGRITY Socket to the list of used INTEGRITY Sockets.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityAddToUsedSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityReleaseSocket()
 *********************************************************************************************************************/
/*! \brief        Releases the passed INTEGRITY Socket.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityReleaseSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityRemoveFromUsedSocket()
 *********************************************************************************************************************/
/*! \brief        Removes the passed INTEGRITY Socket from the list of used INTEGRITY Sockets.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityRemoveFromUsedSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityAddToFreeSocket()
 *********************************************************************************************************************/
/*! \brief        Adds the passed INTEGRITY Socket to the list of free INTEGRITY Sockets.
 *  \details      -
 *  \param[in]    IntegritySocketIdx   Index of the SoAd internal INTEGRITY socket.
 *                                     [range: IntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityAddToFreeSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityReceive()
 *********************************************************************************************************************/
/*! \brief         Tries to receive data from the INTEGRITY Os on the passed Socket.
 *  \details       -
 *  \param[in]     SoConIdx                    Socket connection index.
 *                                             [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]     BufPtr                      Reception buffer. Possible received message will be stored here.
 *  \param[in,out] LenBytePtr                  In:  Length of the passed reception buffer.
 *                                             Out: Length of the received message copied to reception buffer.
 *  \return        SOAD_INTEGRITY_RX_E_OK      Successfully received data.
 *  \return        SOAD_INTEGRITY_RX_E_AGAIN   No data received. Retry again later.
 *  \return        SOAD_INTEGRITY_RX_E_NOT_OK  No data received and an error occurred.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_IntegrityRxReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityReceive(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(sint32, AUTOMATIC, SOAD_APPL_VAR) LenBytePtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityRxIndication()
 *********************************************************************************************************************/
/*! \brief         Provides received data to the SoAd.
 *  \details       Finds the correct SoAd Socket the data where received on with the help of the destination address.
 *                 The received message is then provided to the SoAd_RxIndication().
 *  \param[in]     IntegritySocketIdx  Module internal INTEGRITY Socket index.
 *                                     [range: SocketIdx < SoAd_GetSizeOfIntegritySocketDyn()]
 *  \param[in]     RemAddrPtr          Pointer to remote address.
 *                                     [Points to one of the following structs depending on configured IP address
 *                                     version of parameter IntegritySocketIdx:
 *                                       - SoAd_SockAddrInetType for IPv4
 *                                       - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]     BufPtr              Pointer to buffer of received data.
 *  \param[in]     Length              Length of received data.
 *  \param[in]     DestAddrPtr         Pointer to destination address.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityRxIndication(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2CONST(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) DestAddrPtr);

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityTcpReceive()
 *********************************************************************************************************************/
/*! \brief         Tries to receive data from the INTEGRITY Os on the passed TCP socket connection.
 *  \details       -
 *  \param[in]     SoConIdx   Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return        E_OK       Successfully received data or no data are available yet.
 *  \return        E_NOT_OK   No data received and an error occurred during reception.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different socket connection indices.
 *  \synchronous   TRUE
 *  \config        SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityTcpReceive(
  SoAd_SizeOfSoConType SoConIdx);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityUdpReceive()
 *********************************************************************************************************************/
/*! \brief         Tries to receive data from the INTEGRITY Os on the passed UDP socket connection.
 *  \details       -
 *  \param[in]     SoConIdx   Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return        E_OK       Successfully received data or no data are available yet.
 *  \return        E_NOT_OK   No data received and an error occurred during reception.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityUdpReceive(
  SoAd_SizeOfSoConType SoConIdx);

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityTcpAcceptGetAndMapSocket()
 *********************************************************************************************************************/
/*! \brief         Gets and maps an INTEGRITY Socket to the newly opened TCP data Socket.
 *  \details       -
 *  \param[in]     SoConIdx               Socket connection index.
 *                                        [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]     RemSockAddr            Pointer to remote address of the TCP client.
 *                                        [Points to one of the following structs depending on configured IP address
 *                                        version of parameter SoConIdx:
 *                                          - SoAd_SockAddrInetType for IPv4
 *                                          - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in,out] SocketIdConnectedPtr   Pointer to the connected socket identifier:
 *                                        In:  INTEGRITY Os handle of the new accepted TCP connection socket.
 *                                        Out: Corresponding SoAd internal handle.
 *  \return        E_OK                   Successfully received data or no data are available yet.
 *  \return        E_NOT_OK               No data received and an error occurred during reception.
 *  \pre           SoConIdx has to identify a valid TCP Server socket connection.
 *  \pre           This function must only be called when a new TCP connection is accepted on a TCP Server Socket.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different socket connection indices.
 *  \synchronous   TRUE
 *  \config        SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityTcpAcceptGetAndMapSocket(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemSockAddr,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_VAR) SocketIdConnectedPtr);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityIsBroadcast()
 *********************************************************************************************************************/
/*! \brief         Checks if the passed IP address is a Broadcast address.
 *  \details       -
 *  \param[in]     AddrPtr   Pointer to the IP address in Network-Byte-Order.
 *  \param[in]     Domain    IP domain (IPv4/6).
 *  \param[in]     Netmask   Netmask in CIDR.
 *  \return        TRUE      Passed IP address is a Broadcast address.
 *  \return        FALSE     Passed IP address is no Broadcast address.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegrityIsBroadcast(
  P2CONST(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) AddrPtr,
  SoAd_DomainType Domain,
  SoAd_NetmaskOfLocalAddrDynType Netmask);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxGetPhysAddr()
 *********************************************************************************************************************/
/*! \brief      Returns the physical address (MAC address) of a local interface.
 *  \details    The implementation uses API calls that are present on a QNX operating system.
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out] PhysAddrPtr   Pointer to physical address.
 *  \return     E_OK          The physical address was stored in the passed buffer.
 *  \return     E_NOT_OK      The physical address could not be resolved.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_QNX
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_QnxGetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxJoinMultiCastGroupV4()
 *********************************************************************************************************************/
/*! \brief       Joins the multicast group.
 *  \details     The implementation uses API calls that are present on a QNX operating system.
 *  \param[in]   SoConIdx     Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]   SocketId     Socket identifier.
 *  \return      E_OK         Successfully joined the multicast group.
 *  \return      E_NOT_OK     Failed to join the multicast group.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \config      SOAD_SOCKET_API == SOAD_SOCKET_API_QNX
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_QnxJoinMultiCastGroupV4(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6()
 *********************************************************************************************************************/
/*! \brief      Checks if IPv6 address has a value at the index used to store the interface id (scope id).
 *  \details    Can be used to check if interface id has to be considered on socket bind or comparing IP addresses.
 *              This is the convention in BSD-like operating systems (e.g. QNX).
 *  \param[in]  AddrPtr       Pointer to the IPv6 address that should be updated.
 *  \return     TRUE          Value is set at interface Id index.
 *  \return     FALSE         No value is set at interface Id index (means zero).
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_QNX & SOAD_IPV6
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) AddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6()
 *********************************************************************************************************************/
/*! \brief          Stores the interface id (scope id) in the IPv6 address.
 *  \details        Store the interface id in the 2nd 16bit-word (3rd and 4th byte) of the passed IPv6 address.
 *                  This is the convention in BSD-like operating systems (e.g. QNX).
 *  \param[in]      CtrlIdx       Controller/interface index.
 *  \param[in,out]  AddrPtr       Pointer to the IPv6 address that should be updated.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \config         SOAD_SOCKET_API == SOAD_SOCKET_API_QNX & SOAD_IPV6
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6(
  uint16 CtrlIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) AddrPtr);
# endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxUdpReceiveFromIPv4LimBroadcast()
 *********************************************************************************************************************/
/*! \brief      Receives data from UDP socket that is bound to an IPv4 limited broadcast address.
 *  \details    Checks whether the destination address is the limited broadcast address.
 *  \param[in]  SocketId          Socket identifier.
 *  \param[out] RemAddrPtr        Pointer to remote address.
 *  \param[in]  RemAddrSize       Size of remote address struct.
 *  \param[out] ErrorPtr          Pointer to QNX socket error.
 *  \param[out] IsLimBroadcastPtr Pointer to a boolean that is TRUE if the destination address is the
 *                                limited broadcast address. Otherwise the value is FALSE.
 *  \param[out] RxDataLenPtr      Pointer to the size of received data. On failure the value is SOAD_E_BSD_NOT_OK.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_QNX
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_QnxUdpReceiveFromIPv4LimBroadcast(
  SoAd_SocketIdType SocketId,
  P2VAR(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr,
  socklen_t RemAddrSize,
  P2VAR(sint32, AUTOMATIC, SOAD_APPL_VAR) ErrorPtr,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_VAR) IsLimBroadcastPtr,
  P2VAR(ssize_t, AUTOMATIC, SOAD_APPL_VAR) RxDataLenPtr);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_LinuxGetPhysAddr()
 *********************************************************************************************************************/
/*! \brief      Returns the physical address (MAC address) of a local interface.
 *  \details    The implementation uses API calls that are present on a Linux operating system.
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out] PhysAddrPtr   Pointer to physical address.
 *  \return     E_OK          The physical address was stored in the passed buffer.
 *  \return     E_NOT_OK      The physical address could not be resolved.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_LinuxGetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_LinuxJoinMultiCastGroupV4()
 *********************************************************************************************************************/
/*! \brief       Joins the multicast group.
 *  \details     The implementation uses API calls that are present on a Linux operating system.
 *  \param[in]   SoConIdx     Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]   SocketId     Socket identifier.
 *  \return      E_OK         Successfully joined the multicast group.
 *  \return      E_NOT_OK     Failed to join the multicast group.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \config      SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_LinuxJoinMultiCastGroupV4(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX */

#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
  SoAd_TcpIpBsd_RequestIpAddrAssignment()
**********************************************************************************************************************/
/*! \brief      Requests IP address assignment on a local address identified by a socket connection in case of BSD
 *              Socket API.
 *  \details    -
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  Type              IP address type.
 *                                [range: SOAD_IPADDR_ASSIGNMENT_STATIC .. SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER]
 *  \param[in]  LocalIpAddrPtr    Pointer to IP address which shall be assigned.
 *                                [Points to one of the following structs depending on configured IP address version
 *                                of parameter SoConIdx in case parameter Type has value
 *                                SOAD_IPADDR_ASSIGNMENT_STATIC (unused otherwise):
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]  Netmask           Netmask in CIDR.
 *  \param[in]  DefaultRouterPtr  Pointer to default router (gateway) address.
 *                                [not used]
 *  \return     E_OK              Assignment request was accepted.
 *  \return     E_NOT_OK          Assignment request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different local IP addresses, FALSE for same local IP address.
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_RequestIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_GetSocket()
 *********************************************************************************************************************/
/*! \brief        Creates a socket on BSD-like Socket API and returns the assigned identifier.
 *  \details      For unicast sockets additional sockets are created to receive directed and limted broadcasts.
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    Domain        IP domain (IPv4/6).
 *  \param[in]    Protocol      Transport protocol (UDP/TCP).
 *  \param[out]   SocketIdPtr   Pointer to socket identifier.
 *  \return       E_OK          Socket request was accepted.
 *  \return       E_NOT_OK      Socket request was not accepted.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \config       SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_GetSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_DomainType Domain,
  SoAd_ProtocolType Protocol,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_DATA) SocketIdPtr);

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_Bind()
 *********************************************************************************************************************/
/*! \brief          Binds a BSD-like Socket API socket to a local address and port.
 *  \details        Returns a dynamically assigned port if wildcard (*PortPtr == 0) is used.
 *                  For unicast sockets additional sockets are bound to receive directed and limted broadcasts.
 *  \param[in]      SoConIdx      Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      SocketId      Socket identifier.
 *  \param[in,out]  PortPtr       Pointer to local port.
 *  \return         E_OK          Bind socket was successful.
 *  \return         E_NOT_OK      Bind socket was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \config         SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_Bind(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_BindSingleSocket()
 *********************************************************************************************************************/
/*! \brief          Binds a single BSD-like Socket API socket to a local address and port.
 *  \details        Returns a dynamically assigned port if wildcard (*PortPtr == 0) is used.
 *  \param[in]      SoConIdx      Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      SocketId      Socket identifier.
 *  \param[in]      LocalAddrPtr  Pointer to local address.
 *  \param[in]      LocalAddrSize Size of local address struct.
 *  \param[in,out]  PortPtr       Pointer to local port.
 *  \return         E_OK          Bind socket was successful.
 *  \return         E_NOT_OK      Bind socket was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \config         SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_BindSingleSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2CONST(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  size_t LocalAddrSize,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_BindSingleSocketToInterface()
 *********************************************************************************************************************/
/*! \brief          Binds a single BSD-like Socket API socket to an interface.
 *  \details        -
 *  \param[in]      SoConIdx      Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      SocketId      Socket identifier.
 *  \return         E_OK          Bind socket was successful.
 *  \return         E_NOT_OK      Bind socket was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \config         SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_BindSingleSocketToInterface(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId);
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ChangeParameter()
 *********************************************************************************************************************/
/*! \brief      Changes parameter on a BSD-like Socket API socket.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SocketId        Socket identifier.
 *  \param[in]  ParameterId     Parameter identifier.
 *  \param[in]  ParameterValue  Parameter value.
 *  \return     E_OK            Change parameter request was successful.
 *  \return     E_NOT_OK        Change parameter request was not successful.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_ChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  SoAd_ParamIdType ParameterId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ParameterValue);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleSocketReception()
 *********************************************************************************************************************/
/*! \brief      Handles reception on BSD-like Socket API sockets.
 *  \details    Polls the BSD-like Socket API for pending received data.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleSocketReception(void);

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_UdpReceiveFrom()
 *********************************************************************************************************************/
/*! \brief      Receives data from UDP BSD-like Socket API socket and forwards them to the SoAd_RxIndication.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SocketId        Socket identifier.
 *  \param[out] RemAddrPtr      Pointer to remote address.
 *  \param[in]  RemAddrSize     Size of remote address struct.
 *  \return     E_OK            Socket is still available.
 *  \return     E_NOT_OK        Socket is not available anymore.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_UdpReceiveFrom(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr,
  socklen_t RemAddrSize);
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
#  if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_TcpReceive()
 *********************************************************************************************************************/
/*! \brief      Receives data from TCP BSD-like Socket API socket and forwards them to the SoAd_RxIndication.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK            Socket is still available.
 *  \return     E_NOT_OK        Socket is not available anymore.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_TcpReceive(
  SoAd_SizeOfSoConType SoConIdx);
#  endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */
# endif /* SOAD_TCP == STD_ON */

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleLocalAddressCheckInterval()
 *********************************************************************************************************************/
/*! \brief      Handles local IP address check availability interval for BSD-like Socket API.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleLocalAddressCheckInterval(void);
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleIpAddrStates()
 *********************************************************************************************************************/
/*! \brief      Handles IP address assignment states for BSD-like Socket API.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleIpAddrStates(void);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleIpAddrStateUnassigned()
 *********************************************************************************************************************/
/*! \brief      Handles IP address assignment unassigned state on a local address for BSD-like Socket API.
 *  \details    -
 *  \param[in]  LocalAddrIdx                  Local IP address index.
 *                                            [range: LocalAddrIdx < SoAd_GetSizeOfLocalAddr()]
 *  \return     SOAD_IPADDR_STATE_ASSIGNED    IP address is assigned.
 *  \return     SOAD_IPADDR_STATE_ONHOLD      No change of IP address state.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_IpAddrStateType, SOAD_CODE) SoAd_TcpIpBsd_HandleIpAddrStateUnassigned(
  SoAd_SizeOfLocalAddrType LocalAddrIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleIpAddrStateAssigned()
 *********************************************************************************************************************/
/*! \brief      Handles IP address assignment assigned state on a local address for BSD-like Socket API.
 *  \details    -
 *  \param[in]  LocalAddrIdx                  Local IP address index.
 *                                            [range: LocalAddrIdx < SoAd_GetSizeOfLocalAddr()]
 *  \return     SOAD_IPADDR_STATE_UNASSIGNED  IP address is not assigned anymore.
 *  \return     SOAD_IPADDR_STATE_ONHOLD      No change of IP address state.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_IpAddrStateType, SOAD_CODE) SoAd_TcpIpBsd_HandleIpAddrStateAssigned(
  SoAd_SizeOfLocalAddrType LocalAddrIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_AssignIpAddr()
 *********************************************************************************************************************/
/*! \brief      Assigns a IP address of a local address identified by a socket connection.
 *  \details    -
 *  \param[in]  LocalAddrIdx  Local IP address index.
 *                            [range: LocalAddrIdx < SoAd_GetSizeOfLocalAddr()]
 *  \return     E_OK          IP address assignment was sucessful.
 *  \return     E_NOT_OK      IP address assignment was not sucessful.
 *  \pre        To be called within critical section.
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_AssignIpAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ReleaseIpAddr()
 *********************************************************************************************************************/
/*! \brief      Releases an assigned IP address of a local address identified by a socket connection and closes
 *              the corresponding sockets.
 *  \details    -
 *  \param[in]  LocalAddrIdx  Local IP address index.
 *                            [range: LocalAddrIdx < SoAd_GetSizeOfLocalAddr()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ReleaseIpAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx);

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleTcpSocketStates()
 *********************************************************************************************************************/
/*! \brief      Handles TCP BSD-like Socket API socket states.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleTcpSocketStates(void);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_TcpCheckConnect()
 *********************************************************************************************************************/
/*! \brief      Checks if a TCP client connection is established.
 *  \details    -
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return     TRUE            Retry required since connection is not yet established.
 *  \return     FALSE           Check was not successful.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_TcpCheckConnect(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_TcpCheckAccept()
 *********************************************************************************************************************/
/*! \brief      Checks if a TCP server connection is established.
 *  \details    -
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return     TRUE            Retry required since listen socket is still active.
 *  \return     FALSE           Check was not successful.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_TcpCheckAccept(
  SoAd_SizeOfSocketType SockIdx);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ResetLocalIpAddr()
 *********************************************************************************************************************/
/*! \brief      Resets local IP address struct.
 *  \details    -
 *  \param[in]  LocalAddrIdx  Local IP address index.
 *                            [range: LocalAddrIdx < SoAd_GetSizeOfLocalAddr()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ResetLocalIpAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr()
 *********************************************************************************************************************/
/*! \brief      Checks existence of local address and overwrites local address.
 *  \details    -
 *  \param[in]  LocalAddrIdx    Local IP address index.
 *                              [range: LocalAddrIdx < SoAd_GetSizeOfLocalAddr()]
 *  \param[in]  OverwriteLocal  Overwrite configured local address or not.
 *  \return     E_OK            Local address exists.
 *  \return     E_NOT_OK        Local address does not exist.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx,
  boolean OverwriteLocal);

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleTcpTxConfirmation()
 *********************************************************************************************************************/
/*! \brief      Handles TxConfirmation for TCP socket connection on BSD-like Socket API.
 *  \details    -
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleTcpTxConfirmation(
  SoAd_SizeOfSocketType SockIdx);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ConvertAsrSockAddr2BsdSockAddr()
 *********************************************************************************************************************/
/*! \brief        Converts a socket address in AUTOSAR format to a socket address in BSD-like Socket API format.
 *  \details      -
 *  \param[out]   BsdSockAddrPtr  Pointer to socket address in BSD-like Socket API format.
 *                                [Points to one of the following structs depending on value of struct element domain
 *                                of parameter AsrSockAddrPtr:
 *                                  - sockaddr_in for IPv4
 *                                  - sockaddr_in6 for IPv6]
 *  \param[in]    AsrSockAddrPtr  Pointer to socket address in AUTOSAR format.
 *                                [Points to one of the following structs depending on value of struct element domain:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \config       SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ConvertAsrSockAddr2BsdSockAddr(
  P2VAR(struct sockaddr, SOAD_APPL_DATA, SOAD_APPL_DATA) BsdSockAddrPtr,
  P2CONST(SoAd_SockAddrType, SOAD_APPL_DATA, SOAD_APPL_DATA) AsrSockAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr()
 *********************************************************************************************************************/
/*! \brief        Converts a socket address in BSD-like Socket API format to a socket address in AUTOSAR format.
 *  \details      -
 *  \param[out]   AsrSockAddrPtr  Pointer to socket address in AUTOSAR format.
 *                                [Points to one of the following structs depending on struct element sa_family of
 *                                parameter BsdSockAddrPtr:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]    BsdSockAddrPtr  Pointer to socket address in BSD-like Socket API format.
 *                                [Points to one of the following structs depending on value of struct element
 *                                sa_family:
 *                                  - sockaddr_in for IPv4
 *                                  - sockaddr_in6 for IPv6]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \config       SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr(
  P2VAR(SoAd_SockAddrType, SOAD_APPL_DATA, SOAD_APPL_DATA) AsrSockAddrPtr,
  P2CONST(struct sockaddr, SOAD_APPL_DATA, SOAD_APPL_DATA) BsdSockAddrPtr);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Init()
 *********************************************************************************************************************/
/*! \brief        Initializes the socket transmission buffers.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Init(void);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Request()
 *********************************************************************************************************************/
/*! \brief        Requests a socket transmission buffer.
 *  \details      -
 *  \param[in]    SockIdx               Module internal socket index.
 *                                      [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    Length                Length of data to be stored.
 *  \param[out]   SocketTxBufferPtrPtr  Pointer to pointer to socket transmission buffer.
 *  \return       E_OK                  Transmission buffer was requested successfully.
 *  \return       E_NOT_OK              Transmission buffer was not requested successfully.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \config       SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Request(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length,
  P2VAR(uint8*, SOAD_APPL_DATA, SOAD_APPL_DATA) SocketTxBufferPtrPtr);

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Set()
 *********************************************************************************************************************/
/*! \brief      Sets the last requested socket transmission buffer on a socket to "ready for transmission".
 *  \details    -
 *  \param[in]  SockIdx       Module internal socket index.
 *                            [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  Length        Length of data stored in socket transmission buffer.
 *  \return     E_OK          Transmission buffer set successfully.
 *  \return     E_NOT_OK      Transmission buffer has not been requested or updated length exceeds the buffer size.
 *  \pre        SoAd_TcpIpBsdSocketTxBuffer_Request() has to be called first.
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Set(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_ReleaseLast()
 *********************************************************************************************************************/
/*! \brief      Releases the last requested socket transmission buffer of a socket.
 *  \details    -
 *  \param[in]  SockIdx       Module internal socket index.
 *                            [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_ReleaseLast(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_ReleaseAll()
 *********************************************************************************************************************/
/*! \brief      Releases all socket transmission buffer related to a specific socket.
 *  \details    -
 *  \param[in]  SockIdx     Module internal socket index.
 *                          [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_ReleaseAll(
  SoAd_SizeOfSocketType SockIdx);

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Transmit()
 *********************************************************************************************************************/
/*! \brief      Transmits socket transmission buffers on a socket.
 *  \details    Performs transmissions until first transmission fails and releases buffers if transmitted successfully.
 *  \param[in]  SockIdx       Module internal socket index.
 *                            [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return     E_OK          Transmissions succeeded.
 *  \return     E_NOT_OK      Transmission aborted since one of the buffers could not be transmitted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Transmit(
  SoAd_SizeOfSocketType SockIdx);
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_ReleaseFirst()
 *********************************************************************************************************************/
/*! \brief      Releases the first requested socket transmission buffer of a socket.
 *  \details    -
 *  \param[in]  SockIdx       Module internal socket index.
 *                            [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR
 *  \note       Sub-component TcpIp->Bsd->SocketTxBuffer internal function.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_ReleaseFirst(
  SoAd_SizeOfSocketType SockIdx);
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/**********************************************************************************************************************
  SoAd_TcpIpAsr_RequestIpAddrAssignment()
**********************************************************************************************************************/
/*! \brief      Requests IP address assignment on a local address identified by a socket connection in case of AUTOSAR
 *              Socket API.
 *  \details    -
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  Type              IP address type.
 *                                [range: SOAD_IPADDR_ASSIGNMENT_STATIC .. SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER]
 *  \param[in]  LocalIpAddrPtr    Pointer to IP address which shall be assigned.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]  Netmask           Netmask in CIDR.
 *  \param[in]  DefaultRouterPtr  Pointer to default router (gateway) address.
 *                                [Type == SOAD_IPADDR_ASSIGNMENT_STATIC:
 *                                  ->  DefaultRouterPtr != NULL_PTR
 *                                      Points to one of the following structs depending on configured IP address
 *                                      version of parameter SoConIdx:
 *                                        - SoAd_SockAddrInetType for IPv4
 *                                        - SoAd_SockAddrInet6Type for IPv6
 *                                Type != SOAD_IPADDR_ASSIGNMENT_STATIC:
 *                                  ->  DefaultRouterPtr == NULL_PTR]
 *  \return     E_OK              Assignment request was accepted.
 *  \return     E_NOT_OK          Assignment request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different local IP addresses, FALSE for same local IP address.
 *  \config     SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpAsr_RequestIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketToIntegritySocketMapIterType  socketToIntSocketMapIter;
  SoAd_IntegritySocketDynIterType          integritySocketIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize SocketToIntegritySocket map. */
  for ( socketToIntSocketMapIter = 0;
        socketToIntSocketMapIter < SoAd_GetSizeOfSocketToIntegritySocketMap();
        socketToIntSocketMapIter++ )
  {
    SoAd_SetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketToIntSocketMapIter,
      SoAd_GetSizeOfIntegritySocketDyn());
    SoAd_SetLocalAddrIdxOfSocketToIntegritySocketMap(socketToIntSocketMapIter, SoAd_GetSizeOfLocalAddr());
  }

  /* #20 Initialize integrity sockets. */
  for ( integritySocketIter = 0; integritySocketIter < SoAd_GetSizeOfIntegritySocketDyn(); integritySocketIter++ )
  {
    SoAd_SetStateOfIntegritySocketDyn(integritySocketIter, SOAD_INTEGRITY_SOCKET_S_UNUSED);
    SoAd_SetIntegrityIfIdxOfIntegritySocketDyn(integritySocketIter, SOAD_INTEGRITY_INV_INTEGRITY_IF_IDX);
    SoAd_SetSocketIdOfIntegritySocketDyn(integritySocketIter, SOAD_INTEGRITY_INV_INTEGRITY_SOCKET_ID);
    SoAd_SetUsedCountOfIntegritySocketDyn(integritySocketIter, 0);

    /* For the first and last integrity socket, invalid indices are written. This is fine because they are
     * overridden with valid values right after this iteration. */
    SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(integritySocketIter,
      (SoAd_PrevIntegritySocketIdxOfIntegritySocketDynType)(integritySocketIter - 1));
    SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(integritySocketIter,
      (SoAd_NextIntegritySocketIdxOfIntegritySocketDynType)(integritySocketIter + 1));

  }
  SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(0, SoAd_GetSizeOfIntegritySocketDyn());
  SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(SoAd_GetSizeOfIntegritySocketDyn() - 1,
    SoAd_GetSizeOfIntegritySocketDyn());

  /* #30 Initialize Free and Used integrity socket indices. */
  SoAd_SetFirstFreeIntegritySocketIdx(0);
  SoAd_SetLastFreeIntegritySocketIdx(SoAd_GetSizeOfIntegritySocketDyn() - 1);
  SoAd_SetFirstUsedIntegritySocketIdx(SoAd_GetSizeOfIntegritySocketDyn());

} /* SoAd_TcpIpBsd_IntegrityInit() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityHandleLocalAddressCheckInterval()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityHandleLocalAddressCheckInterval(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfIntegritySocketDynType  curUsedIntegritySocketIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Decrement local address check interval counter. */
  SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter--;

  /* #20 Check if timeout exceeded. */
  if ( SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter == 0u )
  {
    /* #200 Iterate over all used integrity sockets. */
    for ( curUsedIntegritySocketIdx = SoAd_GetFirstUsedIntegritySocketIdx();
          curUsedIntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn();
          curUsedIntegritySocketIdx = SoAd_GetNextIntegritySocketIdxOfIntegritySocketDyn(curUsedIntegritySocketIdx))
    {
      /* #2000 Check if local address of the integrity socket is still available. */
      if ( SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable(curUsedIntegritySocketIdx) == FALSE )
      {
        /* #20000 Trigger release of Ip address for all mapped sockets, if address is not available anymore. */
        SoAd_SocketIterType socketIter;
        SoAd_SizeOfSocketType mappedSocketsFoundCount = 0;
        for ( socketIter = 0; socketIter < SoAd_GetSizeOfSocket(); socketIter++ )
        {
          if ( SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIter) == curUsedIntegritySocketIdx )
          {
            mappedSocketsFoundCount++;
            SoAd_SetIpAddrReqStateOfLocalAddrDyn(SoAd_GetLocalAddrIdxOfSocketToIntegritySocketMap(socketIter),
              SOAD_LOCAL_IP_ADDR_REQ_STATE_RELEASE);

            if ( mappedSocketsFoundCount == SoAd_GetUsedCountOfIntegritySocketDyn(curUsedIntegritySocketIdx) )
            {
              break;
            }
          }
        }
      }
    }

    /* #201 Reset local address check interval counter. */
    SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter = SoAd_GetLocalAddrCheckInterval();
  }
} /* SoAd_TcpIpBsd_IntegrityHandleLocalAddressCheckInterval() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable()
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
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean                     addrIsAvailable = FALSE;
  SOAD_P2VAR(struct ifaddrs)  addrPtr;
  SOAD_P2VAR(struct ifaddrs)  curAddrPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a list of all interfaces on the system can be retrieved. */
  if ( getifaddrs(&addrPtr) != SOAD_E_BSD_NOT_OK )
  {
    /* #20 Iterate over all interfaces. */
    for ( curAddrPtr = addrPtr; curAddrPtr != NULL; curAddrPtr = curAddrPtr->ifa_next )
    {
      /* #30 Check if the current interface is the requested one. */
      if ( if_nametoindex(curAddrPtr->ifa_name) == SoAd_GetIntegrityIfIdxOfIntegritySocketDyn(IntegritySocketIdx) )
      {
        /* #40 Check if the interface address is valid and equals the requested one. */
        if ( curAddrPtr->ifa_addr != NULL )
        {
          if ( SoAd_TcpIpBsd_IntegrityAddrIsEqual(curAddrPtr->ifa_addr,
               SoAd_GetAddrIpAddressOfIntegritySocketDyn(IntegritySocketIdx),
               SoAd_GetDomainOfIntegritySocketDyn(IntegritySocketIdx)) == TRUE )
          {
            addrIsAvailable = TRUE;
            break;
          }
        }
      }
    }
    /* #50 Release the list of all interfaces on the system. */
    freeifaddrs(addrPtr);
  }
  /* #11 Report error on socket otherwise. */
  else
  {
    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_IS_LOC_ADDR_AVAIL, SOAD_SOCK_BSD_API_GET_IF_ADDR, errno);
  }

  return addrIsAvailable;
} /* SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityAddrIsEqual()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegrityAddrIsEqual(
  P2CONST(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) OsSockAddrPtr,
  P2CONST(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) SoAdIpAddressPtr,
  SoAd_DomainType SoAdIpAddressDomain)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean addrIsEqual = FALSE;
  sint32  domain;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get domain of the SoAd Ip address. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAdIpAddressDomain == SOAD_AF_INET6 )
  {
    domain = AF_INET6;
  }
  else
# endif /* SOAD_IPV6 == STD_ON */
  {
    domain = AF_INET;
  }

  /* #20 Check for equality of address. */
  if ( OsSockAddrPtr->sa_family == domain )
  {
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( domain == AF_INET6 )
    {
      SOAD_P2CONST(struct sockaddr_in6) sockAddrIn6Ptr = SOAD_A_P2CONST(struct sockaddr_in6)OsSockAddrPtr;
      uint8_least ipV6AddrByteIter;
      addrIsEqual = TRUE;

      for ( ipV6AddrByteIter = 0; ipV6AddrByteIter < SOAD_IPV6_ADDR_LEN_BYTE; ipV6AddrByteIter++ )
      {
        if ( SoAdIpAddressPtr->addr[ipV6AddrByteIter] != sockAddrIn6Ptr->sin6_addr.s6_addr[ipV6AddrByteIter] )
        {
          addrIsEqual = FALSE;
          break;
        }
      }
    }
    else
# endif /* SOAD_IPV6 == STD_ON */
    {
      SOAD_P2CONST(struct sockaddr_in) sockAddrInPtr = SOAD_A_P2CONST(struct sockaddr_in)OsSockAddrPtr;
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
      addrIsEqual = (boolean)(SoAdIpAddressPtr->addr32[0] == sockAddrInPtr->sin_addr.s_addr);
# else
      addrIsEqual = (boolean)((*SoAdIpAddressPtr) == sockAddrInPtr->sin_addr.s_addr);
# endif /* SOAD_IPV6 == STD_ON */
    }
  }

  return addrIsEqual;
} /* SoAd_TcpIpBsd_IntegrityAddrIsEqual() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetPhysAddr()
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
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(struct ifaddrs)  addrPtr;
  SOAD_P2VAR(struct ifaddrs)  curAddrPtr;
  SOAD_P2CONST(uint8)         phyAddrPtr;
  SoAd_SizeOfSoConGrpType     soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType    localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfTcpIpCtrlType    tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a list of all interfaces on the system can be get. */
  if ( getifaddrs(&addrPtr) != SOAD_E_BSD_NOT_OK )
  {
    /* #20 Iterate over all interfaces. */
    for ( curAddrPtr = addrPtr; curAddrPtr != NULL; curAddrPtr = curAddrPtr->ifa_next )
    {
      /* #30 Check if the current interface is the requested one. */
      if ( if_nametoindex(curAddrPtr->ifa_name) == SoAd_GetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx) )
      {
        /* #40 Check if the interface address is valid and a link layer address (MAC address). */
        if ( (curAddrPtr->ifa_addr != SOAD_INV_PHYS_ADDR) && (curAddrPtr->ifa_addr->sa_family == AF_LINK) )
        {
          /* #50 Store the address in the provided buffer, stop iteration and assume that the request is successful. */
          phyAddrPtr = SOAD_A_P2CONST(uint8)LLADDR(SOAD_A_P2VAR(struct sockaddr_dl)(curAddrPtr)->ifa_addr);
          PhysAddrPtr[0u] = phyAddrPtr[0u];
          PhysAddrPtr[1u] = phyAddrPtr[1u];
          PhysAddrPtr[2u] = phyAddrPtr[2u];
          PhysAddrPtr[3u] = phyAddrPtr[3u];
          PhysAddrPtr[4u] = phyAddrPtr[4u];
          PhysAddrPtr[5u] = phyAddrPtr[5u];

          retVal = E_OK;

          break;
        }
      }
    }
    /* #60 Release the list of all interfaces on the system. */
    freeifaddrs(addrPtr);
  }
  /* #11 Report error on socket otherwise. */
  else
  {
    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_PHYS_ADDR, SOAD_SOCK_BSD_API_GET_IF_ADDR, errno);
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityGetPhysAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetIpAddrOfIf(
  sint32 NetworkIfIdx,
  SoAd_DomainType Domain,
  P2VAR(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8           ifName[IFNAMSIZ];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the interface name. */
  if ( if_indextoname(NetworkIfIdx, SOAD_A_P2VAR(char)ifName) != NULL ) /* PRQA S 5209 */ /* MD_SoAd_BasicType */
  {
    /* #20 Check the IP address domain and get the IPv4/IPv6 address of the interface accordingly. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( Domain == SOAD_AF_INET6 )
    {
      retVal = SoAd_TcpIpBsd_IntegrityGetIPv6AddrOfIf(ifName, IpAddrPtr);
    }
    else
    {
      retVal = SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf(ifName, &IpAddrPtr->addr32[0]);
      IpAddrPtr->addr32[1] = SOAD_IPADDR_ANY;
      IpAddrPtr->addr32[2] = SOAD_IPADDR_ANY;
      IpAddrPtr->addr32[3] = SOAD_IPADDR_ANY;
    }
# else
    retVal = SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf(ifName, IpAddrPtr);
# endif /* SOAD_IPV6 == STD_ON */
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityGetIpAddrOfIf() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf(
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) IfNamePtr,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR)  IPv4IfAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  sint32          dummySocketId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get a dummy socket for the request. */
  dummySocketId = socket(AF_INET, SOCK_DGRAM, 0);

  if ( dummySocketId != SOAD_E_BSD_NOT_OK )
  {
    /* #20 Set up ifreq struct for request. */
    struct ifreq ifr;

    IpBase_StrCpy(SOAD_A_P2VAR(uint8)ifr.ifr_name, IfNamePtr);
    ifr.ifr_ifru.ifru_addr.sa_family = AF_INET;
    ifr.ifr_ifru.ifru_addr.sa_len = sizeof(ifr.ifr_ifru.ifru_addr);

    /* #30 Request IPv4 address of interface using ioctl. */
    if ( ioctl(dummySocketId, SIOCGIFADDR, &ifr) == SOAD_E_BSD_NOT_OK )
    {
      /* #300 Report error if the interface address couldn't be retrieved. */
      SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_IF_ADDR, SOAD_SOCK_BSD_API_IOCTL, errno);
    }
    else
    {
      /* #301 Return the IP address of the interface otherwise. */
      (*IPv4IfAddrPtr) = (uint32)(SOAD_A_P2VAR(struct sockaddr_in)&ifr.ifr_ifru.ifru_addr)->sin_addr.s_addr;

      retVal = E_OK;
    }

    /* #40 Close the dummy socket. */
    close(dummySocketId);
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityGetIPv4AddrOfIf() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetIPv6AddrOfIf()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetIPv6AddrOfIf(
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) IfNamePtr,
  P2VAR(SoAd_IpAddrInet6Type, AUTOMATIC, SOAD_APPL_VAR)  IPv6IfAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType              retVal = E_NOT_OK;
  SOAD_P2VAR(struct ifaddrs)  ifAddrPtr;
  SOAD_P2VAR(struct ifaddrs)  curIfAddrPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a list of all interfaces on the system can be get. */
  if ( getifaddrs(&ifAddrPtr) != SOAD_E_BSD_NOT_OK )
  {
    /* #20 Iterate over all interfaces. */
    for ( curIfAddrPtr = ifAddrPtr; curIfAddrPtr != NULL; curIfAddrPtr = curIfAddrPtr->ifa_next )
    {
      /* #30 Check if the interface name is equal to the requested one. */
      if ( IpBase_StrCmp(SOAD_A_P2CONST(uint8)curIfAddrPtr->ifa_name, IfNamePtr) == IPBASE_CMP_EQUAL )
      {
        /* #40 Check if the interface address is an IPv6 address. */
        if ( curIfAddrPtr->ifa_addr->sa_family == AF_INET6 )
        {
          /* #50 Store the address, stop iteration and assume that the request is successful. */
          /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
          VStdMemCpy(
              SOAD_A_P2VAR(void)IPv6IfAddrPtr->addr,
              SOAD_A_P2CONST(void)(SOAD_A_P2CONST(struct sockaddr_in6)curIfAddrPtr->ifa_addr)->sin6_addr.s6_addr,
              sizeof(IPv6IfAddrPtr->addr));

          retVal = E_OK;
          break;
        }
      }
    }

    freeifaddrs(ifAddrPtr);
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityGetIPv6AddrOfIf() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityCloseAllMappedSockets()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityCloseAllMappedSockets(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType socketIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all sockets. */
  for ( socketIter = 0; socketIter < SoAd_GetSizeOfSocket(); socketIter++ )
  {
    /* #20 Check if socket mapped to the passed INTEGRITY socket... */
    if ( SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIter) == IntegritySocketIdx )
    {
      /* #30 ... close the socket. */
      SoAd_TcpIp_Close(socketIter, TRUE, socketIter); /* In INTEGRITY SocketId and SocketIdx are the same. */
    }
  }

} /* SoAd_TcpIpBsd_IntegrityCloseAllMappedSockets() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityClose()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityClose(
  SoAd_SizeOfSocketType SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_LocalAddrIdxOfSocketToIntegritySocketMapType           localAddrIdx;
  SoAd_IntegritySocketDynIdxOfSocketToIntegritySocketMapType  integritySocketIdx;

  /* ----- Implementation ----------------------------------------------- */
  localAddrIdx = SoAd_GetLocalAddrIdxOfSocketToIntegritySocketMap(SocketIdx);
  integritySocketIdx = SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SocketIdx);

  /* #10 Verify that socket is mapped to a valid INTEGRITY socket. */
  if ( integritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #20 Remove multicast address if local address is a multicast address. */
    if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_MULTICAST )
    {
      (void) SoAd_TcpIpBsd_IntegrityUpdateMulticastFilter(integritySocketIdx, localAddrIdx, FALSE);
    }
    /* #30 Unmap socket from INTEGRITY socket. */
    SoAd_SetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SocketIdx, SoAd_GetSizeOfIntegritySocketDyn());
    SoAd_SetLocalAddrIdxOfSocketToIntegritySocketMap(SocketIdx, SoAd_GetSizeOfLocalAddr());

    /* #40 Decrement used counter of INTEGRITY socket. */
    SoAd_DecUsedCountOfIntegritySocketDyn(integritySocketIdx);
    /* #50 Close socket if used counter reached 0. */
    if ( SoAd_GetUsedCountOfIntegritySocketDyn(integritySocketIdx) == 0 )
    {
      /* #500 Close INTEGRITY Os socket if one was assigned. */
      if ( SoAd_GetStateOfIntegritySocketDyn(integritySocketIdx) >= SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_AVAILABLE )
      {
        (void) close(SoAd_GetSocketIdOfIntegritySocketDyn(integritySocketIdx));
        SoAd_SetStateOfIntegritySocketDyn(integritySocketIdx, SOAD_INTEGRITY_SOCKET_S_USED);
      }
      /* #501 Release INTEGRITY socket resource. */
      SoAd_TcpIpBsd_IntegrityReleaseSocket(integritySocketIdx);
    }
  }
} /* SoAd_TcpIpBsd_IntegrityClose() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityPrepareSocket()
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
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityPrepareSocket(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_DATA) SocketIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                     retVal = E_NOT_OK;
  SoAd_SizeOfSocketType              socketIdx;
  SoAd_SoConGrpIdxOfSoConType        soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_PortType                      port;
  SoAd_SizeOfIntegritySocketDynType  integritySocketIdx;
  sint32                             socketId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the matching socket index. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  socketIdx = SoAd_GetSizeOfSocket();
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) )
  {
    if ( !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
    {
      /* #100 Use the listener socket in case of TCP Server socket. */
      socketIdx = SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx);
    }
  }
  if ( socketIdx == SoAd_GetSizeOfSocket() )
# endif /* SOAD_TCP == STD_ON */
  {
    /* #101 Use socket index of the socket connection in case of UDP or TCP-Client socket. */
    socketIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  }

  /* #20 Get the local port of the socket. */
  port = SoAd_SoCon_GetLocalPortDyn(socketIdx);

  /* #30 Get the matching or a free INTEGRITY socket. */
  integritySocketIdx = SoAd_TcpIpBsd_IntegrityGetMatchingOrFreeSocket(SoConIdx, port);

  if ( integritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #40 Map socket to INTEGRITY socket. */
    SoAd_SetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIdx, integritySocketIdx);
    SoAd_SetLocalAddrIdxOfSocketToIntegritySocketMap(socketIdx, SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx));

    /* #50 Check if INTEGRITY Os socket is not yet assigned. */
    if ( SoAd_GetStateOfIntegritySocketDyn(integritySocketIdx) < SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_AVAILABLE )
    {
      /* #60 Get a new socket from INTEGRITY Os in case of first use of the socket. */
      socketId = SoAd_TcpIpBsd_IntegrityGetSocketFromOs(integritySocketIdx);

      /* #70 If the socket is valid, store it for later use and set INTEGRITY socket state to OS_SOCKET_AVAILABLE. */
      if ( socketId != SOAD_INTEGRITY_INV_INTEGRITY_SOCKET_ID )
      {
        SoAd_SetSocketIdOfIntegritySocketDyn(integritySocketIdx, socketId);
        SoAd_SetStateOfIntegritySocketDyn(integritySocketIdx, SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_AVAILABLE);

        /* #80 Store the external socket handle for the SoAd. For INTEGRITY it is the same as the internal socket
         *     handle. */
        *SocketIdPtr = socketIdx;

        retVal = E_OK;
      }
    }
    /* #51 Assume INTEGRITY Os socket is already assigned otherwise. */
    else
    {
      /* #90 Store the external socket handle for the SoAd. For INTEGRITY it is the same as the internal socket
       *     handle. */
      *SocketIdPtr = socketIdx;

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityPrepareSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityBind()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityBind(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                     retVal = E_NOT_OK;
  SoAd_SoConGrpIdxOfSoConType        soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketType              socketIdx = (SoAd_SizeOfSocketType)SocketId;
  SoAd_LocalAddrIdxOfSoConGrpType    localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfIntegritySocketDynType  integritySocketIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the mapped INTEGRITY socket. */
  integritySocketIdx = SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIdx);
  if ( integritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #20 Check if INTEGRITY socket is already bound. */
    if ( SoAd_GetStateOfIntegritySocketDyn(integritySocketIdx) < SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_BOUND )
    {
      /* #30 Bind the socket. */
      if ( SoAd_TcpIpBsd_IntegrityBindSocket(integritySocketIdx, SoConIdx) == E_OK )
      {
        /* #40 Set state of INTEGRITY socket to OS_SOCKET_BOUND. */
        SoAd_SetStateOfIntegritySocketDyn(integritySocketIdx, SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_BOUND);

        /* #50 Get the used port in case of port wildcard. */
        if ( (*PortPtr) == SOAD_PORT_ANY )
        {
          if ( SoAd_TcpIpBsd_IntegrityGetPortOfSocket(integritySocketIdx, PortPtr) == E_OK )
          {
            /* #500 Store the port information if it was successfully retrieved. */
            SoAd_SetPortOfIntegritySocketDyn(integritySocketIdx, IPBASE_SWAP16((*PortPtr)));
            retVal = E_OK;
          }
        }
        else
        {
          retVal = E_OK;
        }
      }
    }
    else
    {
      retVal = E_OK;
    }

    /* #60 Enable the multicast in case of multicast address. */
    if ( (retVal == E_OK) && (SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_MULTICAST) )
    {
      retVal = SoAd_TcpIpBsd_IntegrityUpdateMulticastFilter(integritySocketIdx, localAddrIdx, TRUE);
    }
    /* #70 Add event to queue to handle UDP socket in main function if all calls to INTEGRITY socket API succeeded. */
    if ( retVal == E_OK )
    {
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
      if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
# endif /* SOAD_TCP == STD_ON */
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SOCK_IDX, socketIdx);
      }
    }
    else
    {
      /* #80 Release resources for the socket in case of any error. */
      SoAd_TcpIpBsd_IntegrityClose(socketIdx);
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityBind() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetSocketFromOs()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(sint32, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetSocketFromOs(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  sint32 socketId;
  sint32 protocol;
  sint32 domain;
  sint32 type;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get address family for INTEGRITY API call. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_GetDomainOfIntegritySocketDyn(IntegritySocketIdx) == SOAD_AF_INET6 )
  {
    domain = AF_INET6;
  }
  else
# endif /* SOAD_IPV6 == STD_ON */
  {
    domain = AF_INET;
  }

  /* #20 Get protocol for INTEGRITY API call. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_GetProtocolOfIntegritySocketDyn(IntegritySocketIdx) == SOAD_IPPROTO_TCP )
  {
    type = SOCK_STREAM;
    protocol = IPPROTO_TCP;
  }
  else
# endif /* SOAD_TCP == STD_ON */
  {
    type = SOCK_DGRAM;
    protocol = IPPROTO_UDP;
  }

  /* #30 Get a new socket from INTEGRITY Os. */
  socketId = socket(domain, type, protocol);

  /* #40 Report socket error in case 'socket' call failed. */
  if ( socketId == SOAD_INV_SOCKET_ID )
  {
    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_SOCKET_FROM_OS, SOAD_SOCK_BSD_API_SOCKET, errno);
  }

  return socketId;
} /* SoAd_TcpIpBsd_IntegrityGetSocketFromOs() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityBindSocket()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityBindSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                   retVal = E_NOT_OK;
  SOAD_P2VAR(struct sockaddr)      sockAddrPtr;
  sint32                           sockAddrLen;
  struct sockaddr_in               sockAddrV4;
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  struct sockaddr_in6              sockAddrV6;
# endif /* SOAD_IPV6 == STD_ON */
  SoAd_SoConGrpIdxOfSoConType      soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_LocalAddrIdxOfSoConGrpType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  sint32                           osSocketId = SoAd_GetSocketIdOfIntegritySocketDyn(IntegritySocketIdx);
  SoAd_PortType                    portNbo =
    SoAd_GetPortOfIntegritySocketDyn(IntegritySocketIdx); /* Port is already stored in NBO */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set up the socket address structure according to the address family. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_GetDomainOfIntegritySocketDyn(IntegritySocketIdx) == SOAD_AF_INET6 )
  {
    sockAddrV6.sin6_family = AF_INET6;
    sockAddrV6.sin6_port = portNbo;
    sockAddrV6.sin6_flowinfo = 0;
    sockAddrV6.sin6_scope_id = SoAd_GetIntegrityIfIdxOfIntegritySocketDyn(IntegritySocketIdx);

    /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(
      SOAD_A_P2VAR(void)sockAddrV6.sin6_addr.s6_addr,
      SOAD_A_P2CONST(void)SoAd_GetIpAddressOfIntegritySocketDyn(IntegritySocketIdx).addr,
      sizeof(sockAddrV6.sin6_addr.s6_addr));

    sockAddrLen = sizeof(sockAddrV6);
    sockAddrV6.sin6_len = sockAddrLen;

    sockAddrPtr = SOAD_A_P2VAR(struct sockaddr)&sockAddrV6;
  }
  else
# endif /* SOAD_IPV6 == STD_ON */
  {
    sockAddrV4.sin_family = AF_INET;
    sockAddrV4.sin_port = portNbo;
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    sockAddrV4.sin_addr.s_addr = SoAd_GetIpAddressOfIntegritySocketDyn(IntegritySocketIdx).addr32[0];
# else
    sockAddrV4.sin_addr.s_addr = SoAd_GetIpAddressOfIntegritySocketDyn(IntegritySocketIdx);
# endif /* SOAD_IPV6 == STD_ON */

    sockAddrLen = sizeof(sockAddrV4);
    sockAddrV4.sin_len = sockAddrLen;

    sockAddrPtr = SOAD_A_P2VAR(struct sockaddr)&sockAddrV4;
  }
  /* #20 Bind the socket using the INTEGRITY Os API 'bind'. */
  if ( bind(osSocketId, sockAddrPtr, sockAddrLen) == SOAD_E_BSD_NOT_OK )
  {
    /* #200 Report socket error in case of 'bind' failed and release (close) the socket. */
    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_BIND_SOCKET, SOAD_SOCK_BSD_API_BIND, errno);
    (void)close(osSocketId);

    /* #201 Check if local address is still available. */
    if ( errno == EADDRNOTAVAIL )
    {
      if ( SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable(IntegritySocketIdx) == FALSE )
      {
        /* #2010 Mark local address as to be released. */
        SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_RELEASE);

        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, localAddrIdx);
      }
    }
  }
  else
  {
    retVal = E_OK;
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    /* #30 Enable Broadcast reception in case of IPv6 and successful bind. */
    if ( SoAd_GetDomainOfIntegritySocketDyn(IntegritySocketIdx) == SOAD_AF_INET6 )
    {
      retVal = SoAd_TcpIpBsd_IntegrityIPv6EnableBroadcast(osSocketId,
        SoAd_GetIntegrityIfIdxOfIntegritySocketDyn(IntegritySocketIdx));
    }
# endif /* SOAD_IPV6 == STD_ON */
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityBindSocket() */

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityIPv6EnableBroadcast()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityIPv6EnableBroadcast(
  SoAd_SocketIdType OsSocketId,
  sint32 IntegrityIfIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  struct ipv6_mreq mreq;

  /* ----- Implementation ----------------------------------------------- */
  /* IPv6 Broadcast is FF01::1 and FF02::1 */
  mreq.ipv6mr_interface = IntegrityIfIdx;

  /* #10 Enable IPv6 FF01::1 Broadcast address by using INTEGRITY Os API 'setsockopt'. */
  IpBase_Fill(mreq.ipv6mr_multiaddr.s6_addr, 0, sizeof(mreq.ipv6mr_multiaddr));
  mreq.ipv6mr_multiaddr.s6_addr[0u]  = 0xFFu;
  mreq.ipv6mr_multiaddr.s6_addr[1u]  = 0x01u;
  mreq.ipv6mr_multiaddr.s6_addr[15u] = 0x01u;

  if ( setsockopt(OsSocketId, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq, sizeof(mreq)) == SOAD_E_BSD_NOT_OK )
  {
    /* #100 Report socket error in case of 'setsockopt' failed. */
    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_EN_V6_BROADCAST, SOAD_SOCK_BSD_API_SET_SOCK_OPT, errno);
    retVal = E_NOT_OK;
  }

  /* #20 Enable IPv6 FF01::2 Broadcast address by using INTEGRITY Os API 'setsockopt'. */
  IpBase_Fill(mreq.ipv6mr_multiaddr.s6_addr, 0, sizeof(mreq.ipv6mr_multiaddr));
  mreq.ipv6mr_multiaddr.s6_addr[0u]  = 0xFFu;
  mreq.ipv6mr_multiaddr.s6_addr[1u]  = 0x02u;
  mreq.ipv6mr_multiaddr.s6_addr[15u] = 0x01u;

  if ( setsockopt(OsSocketId, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq, sizeof(mreq)) == SOAD_E_BSD_NOT_OK )
  {
    /* #200 Report socket error in case of 'setsockopt' failed. */
    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_EN_V6_BROADCAST, SOAD_SOCK_BSD_API_SET_SOCK_OPT, errno);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityIPv6EnableBroadcast() */
# endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetPortOfSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetPortOfSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType       retVal = E_NOT_OK;
  sint32               socketId = SoAd_GetSocketIdOfIntegritySocketDyn(IntegritySocketIdx);
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  struct sockaddr_in6  sockAddr;
# else
  struct sockaddr_in   sockAddr;
# endif /* SOAD_IPV6 == STD_ON */
  socklen_t            sockAddrSize = sizeof(sockAddr);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that a valid socket id is mapped to the INTEGRITY socket. */
  if ( socketId != SOAD_INTEGRITY_INV_INTEGRITY_SOCKET_ID )
  {
    /* #20 Get port via INTEGRITY Os API 'getsockname'. */
    if ( getsockname(socketId, SOAD_A_P2VAR(struct sockaddr)&sockAddr, &sockAddrSize) == SOAD_E_BSD_NOT_OK )
    {
      /* #30 Report socket error if call failed. */
      SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_PORT_OF_SOCKET, SOAD_SOCK_BSD_API_GET_SOCK_NAME, errno);
    }
    else
    {
      /* #40 Set output parameter 'PortPtr' if call succeeded. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
      *PortPtr = IPBASE_SWAP16(sockAddr.sin6_port);
# else
      *PortPtr = IPBASE_SWAP16(sockAddr.sin_port);
# endif /* SOAD_IPV6 == STD_ON */
      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityGetPortOfSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityUpdateMulticastFilter()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityUpdateMulticastFilter(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  SoAd_SizeOfLocalAddrType LocalAddrIdx,
  boolean AddToFilter)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType        retVal = E_NOT_OK;
  SoAd_IpAddrInetXType  ipMulticastAddr = SoAd_GetAddrOfLocalAddrDyn(LocalAddrIdx);
  sint32                socketId = SoAd_GetSocketIdOfIntegritySocketDyn(IntegritySocketIdx);
  sint32                request;
  sint32                requestSrc;

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* #10 Check address family. */
  if ( SoAd_GetDomainOfLocalAddr(LocalAddrIdx) == SOAD_AF_INET6 )
  {
    struct ipv6_mreq mreq;

    mreq.ipv6mr_interface = SoAd_GetIntegrityIfIdxOfIntegritySocketDyn(IntegritySocketIdx);

    /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(
      SOAD_A_P2VAR(void)mreq.ipv6mr_multiaddr.s6_addr,
      SOAD_A_P2CONST(void)ipMulticastAddr.addr,
      sizeof(mreq.ipv6mr_multiaddr.s6_addr));

    /* #20 Join/Leave IPv6 multicast address using the INTEGRITY Os API 'setsockopt'. */
    if ( AddToFilter == TRUE )
    {
      request = IPV6_JOIN_GROUP;
    }
    else
    {
      request = IPV6_LEAVE_GROUP;
    }
    if ( setsockopt(socketId, IPPROTO_IPV6, request, &mreq, sizeof(mreq)) == SOAD_E_BSD_NOT_OK )
    {
      /* #200 Report socket error if API call failed. */
      SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_UPDATE_MULTICAST, SOAD_SOCK_BSD_API_SET_SOCK_OPT, errno);
    }
    else
    {
      retVal = E_OK;
    }
  }
  else
# endif /* SOAD_IPV6 == STD_ON */
  {
    struct ip_mreq mreq;

# if (SOAD_IPV6 == STD_ON) /* COV_SOAD_QM_FEATURE_3 */
    mreq.imr_interface.s_addr = SoAd_GetIpAddressOfIntegritySocketDyn(IntegritySocketIdx).addr32[0];
    mreq.imr_multiaddr.s_addr = ipMulticastAddr.addr32[0];
# else
    mreq.imr_interface.s_addr = SoAd_GetIpAddressOfIntegritySocketDyn(IntegritySocketIdx);
    mreq.imr_multiaddr.s_addr = ipMulticastAddr;
# endif /* SOAD_IPV6 == STD_ON */

    /* #30 Join/Leave IPv4 multicast address using the INTEGRITY Os API 'setsockopt'. */
    if ( AddToFilter == TRUE )
    {
      request = IP_ADD_MEMBERSHIP;
      requestSrc = IP_ADD_SOURCE_MEMBERSHIP;
    }
    else
    {
      request = IP_DROP_MEMBERSHIP;
      requestSrc = IP_DROP_SOURCE_MEMBERSHIP;
    }
      /* #300 Check if 'setsockopt' failed. */
    if ( setsockopt(socketId, IPPROTO_IP, request, SOAD_A_P2VAR(sint8)&mreq, sizeof(mreq)) == SOAD_E_BSD_NOT_OK )
    {
      if ( errno == EINVAL )
      {
        /* #3000 Retry with 'Source' Multicast option in case of 'Invalid Argument' error. */
        if ( setsockopt(socketId, IPPROTO_IP, requestSrc, SOAD_A_P2VAR(sint8)&mreq, sizeof(mreq)) == SOAD_E_BSD_NOT_OK )
        {
          /* #30000 Report socket error if API call failed. */
          SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_UPDATE_MULTICAST, SOAD_SOCK_BSD_API_SET_SOCK_OPT, errno);
        }
      }
      else
      {
        /* #3001 Report socket error otherwise. */
        SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_UPDATE_MULTICAST, SOAD_SOCK_BSD_API_SET_SOCK_OPT, errno);
      }
    }
    else
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityUpdateMulticastFilter() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetMatchingOrFreeSocket()
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
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfIntegritySocketDynType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetMatchingOrFreeSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PortType Port)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfIntegritySocketDynType  integritySocketIdx = SoAd_GetSizeOfIntegritySocketDyn();
  SoAd_SoConGrpIdxOfSoConType        soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_LocalAddrIdxOfSoConGrpType    localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_IpAddrInetXType               localAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdx);
  SoAd_DomainType                    domain = SoAd_GetDomainOfLocalAddr(localAddrIdx);
  SoAd_ProtocolType                  protocol;
  SoAd_TcpIpCtrlIdxOfLocalAddrType   tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  SoAd_CtrlIdxOfTcpIpCtrlDynType     networkIfIdx = SoAd_GetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx);
  SoAd_SizeOfIntegritySocketDynType  integritySocketIter;
  boolean                            getFreeIntegritySocket = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the used Protocol. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) )
  {
    protocol = SOAD_IPPROTO_TCP;
  }
  else
# endif /* SOAD_TCP == STD_ON */
  {
    protocol = SOAD_IPPROTO_UDP;
  }

  /* #20 Check if port is wildcard. */
  if ( Port == SOAD_PORT_ANY )
  {
    /* #30 Mark to get a new INTEGRITY socket in case of wildcard. */
    getFreeIntegritySocket = TRUE;
  }
  else
  {
    /* #40 Check if a matching socket exists in case of set port. */
    for ( integritySocketIter = SoAd_GetFirstUsedIntegritySocketIdx();
          integritySocketIter < SoAd_GetSizeOfIntegritySocketDyn();
          integritySocketIter = SoAd_GetNextIntegritySocketIdxOfIntegritySocketDyn(integritySocketIter) )
    {
      if ( SoAd_TcpIpBsd_IntegritySocketIsEqual(integritySocketIter, Port, domain, networkIfIdx, protocol) == TRUE )
      {
        integritySocketIdx = integritySocketIter;
        break;
      }
    }

    /* #50 Prevent reuse for same address if a matching INTEGRITY socket was found. */
    if ( integritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
    {
      SoAd_SizeOfSocketType mappedSocketCount = SoAd_GetUsedCountOfIntegritySocketDyn(integritySocketIdx);
      SoAd_SocketIterType   socketIter;

      /* #500 Iterate all sockets. */
      for (socketIter = 0; socketIter < SoAd_GetSizeOfSocket(); socketIter++)
      {
        /* #501 Check if socket is mapped to the INTEGRITY socket. */
        if ( SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIter) == integritySocketIdx )
        {
          mappedSocketCount--;

          /* #502 Check if addresses are the same. */
          if ( SoAd_GetLocalAddrIdxOfSocketToIntegritySocketMap(socketIter) == localAddrIdx )
          {
            /* #503 Invalidate INTEGRITY socket and stop iteration in case of already used address. */
            integritySocketIdx = SoAd_GetSizeOfIntegritySocketDyn();
            mappedSocketCount = 0; /* Set to '0' to stop iteration. */
          }

          /* #504 Stop iteration if all sockets mapped to the INTEGRITY socket where checked. */
          if ( mappedSocketCount == 0 )
          {
            break;
          }
        }
      }
    }
    else
    {
      getFreeIntegritySocket = TRUE;
    }
  }

  /* #60 Check if a new INTEGRITY socket is required. */
  if ( getFreeIntegritySocket == TRUE )
  {
    /* #70 Get a free INTEGRITY socket and store required information for later use. */
    integritySocketIdx = SoAd_TcpIpBsd_IntegrityGetFreeSocket();

    if ( integritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
    {
      SoAd_SetDomainOfIntegritySocketDyn(integritySocketIdx, domain);
      SoAd_SetPortOfIntegritySocketDyn(integritySocketIdx, Port); /* Port is provided and stored in NBO. */
      SoAd_SetProtocolOfIntegritySocketDyn(integritySocketIdx, protocol);
      SoAd_SetIntegrityIfIdxOfIntegritySocketDyn(integritySocketIdx, networkIfIdx);

      /* #80 Store address information of the socket. */
      if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST )
      {
        /* #800 Use the unicast address in case of unicast. */
        SoAd_SetIpAddressOfIntegritySocketDyn(integritySocketIdx, localAddr);
      }
      else
      {
        /* #801 Get and use the local address of the network interface in case of multicast. */
        SoAd_IpAddrInetXType ipAddrOfIf;
        if ( SoAd_TcpIpBsd_IntegrityGetIpAddrOfIf(networkIfIdx, domain, &ipAddrOfIf) == E_OK )
        {
          SoAd_SetIpAddressOfIntegritySocketDyn(integritySocketIdx, ipAddrOfIf);
        }
      }
    }
  }

  /* #90 Increment the 'used' count if a valid INTEGRITY socket was found. */
  if ( integritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    SoAd_IncUsedCountOfIntegritySocketDyn(integritySocketIdx);
  }

  return integritySocketIdx;
} /* SoAd_TcpIpBsd_IntegrityGetMatchingOrFreeSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetMappedOrFreeSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfIntegritySocketDynType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetMappedOrFreeSocket(
  SoAd_SizeOfSocketType SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfIntegritySocketDynType mappedIntegritySocketIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket is already mapped to an INTEGRITY socket. */
  mappedIntegritySocketIdx = SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SocketIdx);
  if ( mappedIntegritySocketIdx == SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #20 Get a free INTEGRITY socket if not. */
    mappedIntegritySocketIdx = SoAd_TcpIpBsd_IntegrityGetFreeSocket();
  }

  return mappedIntegritySocketIdx;
} /* SoAd_TcpIpBsd_IntegrityGetMappedOrFreeSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegritySocketIsEqual()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegritySocketIsEqual(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  SoAd_PortType Port,
  SoAd_DomainType Domain,
  sint32 NetworkIfIdx,
  SoAd_ProtocolType Protocol)
{
  /* #10 Check if the passed INTEGRITY socket matches the passed criteria. */
  return ((SoAd_GetPortOfIntegritySocketDyn(IntegritySocketIdx) == Port)
      && (SoAd_GetDomainOfIntegritySocketDyn(IntegritySocketIdx) == Domain)
      && (SoAd_GetProtocolOfIntegritySocketDyn(IntegritySocketIdx) == Protocol)
      && (SoAd_GetIntegrityIfIdxOfIntegritySocketDyn(IntegritySocketIdx) == NetworkIfIdx));
} /* SoAd_TcpIpBsd_IntegritySocketIsEqual() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityGetFreeSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfIntegritySocketDynType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityGetFreeSocket(
  void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfIntegritySocketDynType freeIntegritySocketIdx = SoAd_GetFirstFreeIntegritySocketIdx();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is a free INTEGRITY socket. */
  if ( freeIntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #20 Removed socket from free socket queue. */
    SoAd_TcpIpBsd_IntegrityRemoveFromFreeSocket(freeIntegritySocketIdx);

    /* #30 Add socket to used socket queue. */
    SoAd_TcpIpBsd_IntegrityAddToUsedSocket(freeIntegritySocketIdx);

    /* #40 Set the INTEGRITY socket state to 'USED'. */
    SoAd_SetStateOfIntegritySocketDyn(freeIntegritySocketIdx, SOAD_INTEGRITY_SOCKET_S_USED);
  }
  return freeIntegritySocketIdx;
} /* SoAd_TcpIpBsd_IntegrityGetFreeSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityRemoveFromFreeSocket()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityRemoveFromFreeSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_NextIntegritySocketIdxOfIntegritySocketDynType nextFreeSocketIdx =
    SoAd_GetNextIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx);
  SoAd_PrevIntegritySocketIdxOfIntegritySocketDynType prevFreeSocketIdx =
    SoAd_GetPrevIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is a previous free socket. */
  if ( prevFreeSocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #100 Set next socket of previous socket to next socket of the passed socket. */
    SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(prevFreeSocketIdx, nextFreeSocketIdx);
  }
  else
  {
    /* #101 Set the first free socket to the next socket of the passed socket. */
    SoAd_SetFirstFreeIntegritySocketIdx(nextFreeSocketIdx);
  }

  /* #20 Check if there is a next free socket. */
  if ( nextFreeSocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #200 Set previous socket of next socket to previous socket of passed socket. */
    SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(nextFreeSocketIdx, prevFreeSocketIdx);
  }
  else
  {
    /* #201 Set the last free socket to the previous socket of the passed socket. */
    SoAd_SetLastFreeIntegritySocketIdx(prevFreeSocketIdx);
  }

  /* #30 Decouple INTEGRITY socket. */
  SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx, SoAd_GetSizeOfIntegritySocketDyn());
  SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx, SoAd_GetSizeOfIntegritySocketDyn());

} /* SoAd_TcpIpBsd_IntegrityRemoveFreeSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityAddToUsedSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityAddToUsedSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfIntegritySocketDynType firstUsedIntegritySocketIdx = SoAd_GetFirstUsedIntegritySocketIdx();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there are other used sockets. */
  if ( firstUsedIntegritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #100 Add passed socket to the start of the queue. */
    SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(firstUsedIntegritySocketIdx, IntegritySocketIdx);
    SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx, firstUsedIntegritySocketIdx);
    SoAd_SetFirstUsedIntegritySocketIdx(IntegritySocketIdx);
  }
  else
  {
    /* #101 No other used sockets. Start queue with passed socket. */
    SoAd_SetFirstUsedIntegritySocketIdx(IntegritySocketIdx);
  }
} /* SoAd_TcpIpBsd_IntegrityAddUsedSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityReleaseSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityReleaseSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* #10 Remove passed socket from used socket queue. */
  SoAd_TcpIpBsd_IntegrityRemoveFromUsedSocket(IntegritySocketIdx);

  /* #20 Add passed socket to free socket queue. */
  SoAd_TcpIpBsd_IntegrityAddToFreeSocket(IntegritySocketIdx);

  /* #30 Reset information stored in INTEGRITY socket. */
  SoAd_SetIntegrityIfIdxOfIntegritySocketDyn(IntegritySocketIdx, SOAD_INTEGRITY_INV_INTEGRITY_IF_IDX);
  SoAd_SetSocketIdOfIntegritySocketDyn(IntegritySocketIdx, SOAD_INTEGRITY_INV_INTEGRITY_SOCKET_ID);
  SoAd_SetUsedCountOfIntegritySocketDyn(IntegritySocketIdx, 0);

  /* #40 Set state of passed socket to UNUSED. */
  SoAd_SetStateOfIntegritySocketDyn(IntegritySocketIdx, SOAD_INTEGRITY_SOCKET_S_UNUSED);

} /* SoAd_TcpIpBsd_IntegrityReleaseSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityRemoveFromUsedSocket()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityRemoveFromUsedSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_NextIntegritySocketIdxOfIntegritySocketDynType nextUsedSocketIdx =
    SoAd_GetNextIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx);
  SoAd_PrevIntegritySocketIdxOfIntegritySocketDynType prevUsedSocketIdx =
    SoAd_GetPrevIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is a previous used socket. */
  if ( prevUsedSocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #100 Set next socket of previous socket to next socket of the passed socket. */
    SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(prevUsedSocketIdx, nextUsedSocketIdx);
  }
  else
  {
    /* #101 Set the first used socket to the next socket of the passed socket. */
    SoAd_SetFirstUsedIntegritySocketIdx(nextUsedSocketIdx);
  }

  /* #20 Check if there is a next used socket. */
  if ( nextUsedSocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #200 Set previous socket of next socket to previous socket of the passed socket. */
    SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(nextUsedSocketIdx, prevUsedSocketIdx);
  }

  /* #30 Decouple integrity socket. */
  SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx, SoAd_GetSizeOfIntegritySocketDyn());
  SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx, SoAd_GetSizeOfIntegritySocketDyn());

} /* SoAd_TcpIpBsd_IntegrityRemoveUsedSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityAddToFreeSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityAddToFreeSocket(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is any other free socket. */
  if ( SoAd_GetLastFreeIntegritySocketIdx() < SoAd_GetSizeOfIntegritySocketDyn() )
  {
    /* #100 Add passed socket to the end of the free socket queue. */
    SoAd_SetPrevIntegritySocketIdxOfIntegritySocketDyn(IntegritySocketIdx, SoAd_GetLastFreeIntegritySocketIdx());
    SoAd_SetNextIntegritySocketIdxOfIntegritySocketDyn(SoAd_GetLastFreeIntegritySocketIdx(), IntegritySocketIdx);
    SoAd_SetLastFreeIntegritySocketIdx(IntegritySocketIdx);
  }
  else
  {
    /* #101 No other free socket. Start queue with the passed socket. */
    SoAd_SetFirstFreeIntegritySocketIdx(IntegritySocketIdx);
    SoAd_SetLastFreeIntegritySocketIdx(IntegritySocketIdx);
  }
} /* SoAd_TcpIpBsd_IntegrityAddFreeSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityReceive()
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
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_IntegrityRxReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityReceive(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(sint32, AUTOMATIC, SOAD_APPL_VAR) LenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_IntegrityRxReturnType         retVal = SOAD_INTEGRITY_RX_E_NOT_OK;
  SoAd_SizeOfSocketType              socketIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SizeOfIntegritySocketDynType  integritySocketIdx =
    SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIdx);
  struct msghdr                      msg;
  struct iovec                       iov[1];
  sint8                              control[CMSG_SPACE(sizeof(struct cmsghdr)) +
                                             CMSG_SPACE(sizeof(struct in6_pktinfo))];
  struct sockaddr_inX                remoteAddr;
  sint32                             rxMsgLength;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Setup message structure for message reception. */
  iov[0].iov_base = SOAD_A_P2VAR(void)BufPtr;
  iov[0].iov_len = (*LenBytePtr);
  msg.msg_control = &control;
  msg.msg_controllen = sizeof(control);
  msg.msg_flags = 0;
  msg.msg_name = &remoteAddr;
  msg.msg_namelen = sizeof(remoteAddr);
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;

  /* #20 Try to receive message using the INTEGRITY Os API 'recvmsg'. */
  rxMsgLength = recvmsg(SoAd_GetSocketIdOfIntegritySocketDyn(integritySocketIdx), &msg, MSG_DONTWAIT);

  /* #30 Check if no data is received or any other error occurred. */
  if ( (rxMsgLength == 0u) || (rxMsgLength == SOAD_E_BSD_NOT_OK) )
  {
    /* #300 Mark to repeat if no data is received. */
    if ( ((errno == EAGAIN) || (errno == EWOULDBLOCK)) && (rxMsgLength != 0u) )
    {
      retVal = SOAD_INTEGRITY_RX_E_AGAIN;
    }
    /* #301 Handle all other errors otherwise. */
    else
    {
      /* #3010 Report socket error. */
      SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_INTEGRITY_RECEIVE, SOAD_SOCK_BSD_API_RECV_MSG, errno);

      /* #3011 Mark local address as to be released if it is not available anymore. */
      if ( SoAd_TcpIpBsd_IntegrityIsLocalAddressAvailable(integritySocketIdx) == FALSE )
      {
        SoAd_SizeOfLocalAddrType localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));

        SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_RELEASE);

        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, localAddrIdx);
      }

      /* #3012 Close all sockets mapped to INTEGRITY socket. */
      SoAd_TcpIpBsd_IntegrityCloseAllMappedSockets(integritySocketIdx);
    }
  }
  /* #40 Mark to repeat and forward data if data is received otherwise. */
  else
  {
    SoAd_SockAddrInetXType             remAddr;
    SoAd_IpAddrInetXType               destAddr;
    SOAD_P2CONST(SoAd_IpAddrInetXType) destAddrPtr = NULL_PTR;

    /* #50 Verify that data is not received from own local address in case of UDP. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( SoAd_GetProtocolOfIntegritySocketDyn(integritySocketIdx) == SOAD_IPPROTO_TCP )
    {
      remAddr = SoAd_GetRemAddrDynOfSoConDyn(SoConIdx);
      retVal = SOAD_INTEGRITY_RX_E_OK;
    }
    else
# endif /* SOAD_TCP == STD_ON */
    {
      SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)&remAddr,
        SOAD_A_P2CONST(struct sockaddr)&remoteAddr);

      if ( SoAd_TcpIp_CompareToIpAddr(SoConIdx, (SoAd_IpAddrConstPtrType)remAddr.addr) == E_NOT_OK )
      {
        /* #60 Get the destination address for UDP sockets. */
        SOAD_P2VAR(struct cmsghdr) ctrlMsgHdr = SOAD_A_P2VAR(struct cmsghdr)msg.msg_control;

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_GetDomainOfIntegritySocketDyn(integritySocketIdx) == SOAD_AF_INET6 )
        {
          if ( ctrlMsgHdr->cmsg_type == IPV6_PKTINFO )
          {
            SOAD_P2VAR(struct in6_pktinfo) pktInfoPtr = SOAD_A_P2VAR(struct in6_pktinfo)CMSG_DATA(msg.msg_control);
            /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
            VStdMemCpy(
              SOAD_A_P2VAR(void)destAddr.addr,
              SOAD_A_P2CONST(void)pktInfoPtr->ipi6_addr.s6_addr,
              sizeof(destAddr));
            destAddrPtr = &destAddr;
          }
        }
        else
# endif /* SOAD_IPV6 == STD_ON */
        {
          if ( ctrlMsgHdr->cmsg_type == IP_RECVDSTADDR )
          {
            SOAD_P2VAR(struct in_addr) inAddrPtr = SOAD_A_P2VAR(struct in_addr)CMSG_DATA(msg.msg_control);
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
            destAddr.addr32[0] = inAddrPtr->s_addr;
# else
            destAddr = inAddrPtr->s_addr;
# endif /* SOAD_IPV6 == STD_ON */
            destAddrPtr = &destAddr;
          }
        }

        /* #70 Check if message was sent to Broadcast address. */
        if ( SoAd_TcpIpBsd_IntegrityIsBroadcast(&destAddr,
            SoAd_GetDomainOfIntegritySocketDyn(integritySocketIdx),
            SoAd_GetNetmaskOfLocalAddrDyn(SoAd_GetLocalAddrIdxOfSocketToIntegritySocketMap(socketIdx))) == TRUE )
        {
          /* #700 Message has to be forwarded to the Unicast socket in case of Broadcast destination ->
           *      change destination address to the local address. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
           /* PRQA S 314 4 */ /* MD_MSR_VStdLibCopy */
          VStdMemCpy(
            SOAD_A_P2VAR(void)destAddr.addr,
            SOAD_A_P2CONST(void)SoAd_GetIpAddressOfIntegritySocketDyn(integritySocketIdx).addr,
            sizeof(destAddr));
# else
           /* PRQA S 314 4 */ /* MD_MSR_VStdLibCopy */
          VStdMemCpy(
            SOAD_A_P2VAR(void)&destAddr,
            SOAD_A_P2CONST(void)SoAd_GetAddrIpAddressOfIntegritySocketDyn(integritySocketIdx),
            sizeof(destAddr));
# endif /* SOAD_IPV6 == STD_ON */
        }

        retVal = SOAD_INTEGRITY_RX_E_OK;
      }
      else
      {
        retVal = SOAD_INTEGRITY_RX_E_AGAIN;
      }
    }

    if ( retVal == SOAD_INTEGRITY_RX_E_OK )
    {
      /* #80 Forward received data. */
      *LenBytePtr = rxMsgLength;

      SoAd_TcpIpBsd_IntegrityRxIndication(integritySocketIdx, SOAD_A_P2VAR(SoAd_SockAddrType)&remAddr, BufPtr,
        (uint16)rxMsgLength, destAddrPtr);
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityReceive() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityRxIndication()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_IntegrityRxIndication(
  SoAd_SizeOfIntegritySocketDynType IntegritySocketIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2CONST(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) DestAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType socketIdx = SoAd_GetSizeOfSocket();
  SoAd_SocketIterType   socketIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all SoAd sockets to get the matching SoAd socket. */
  for ( socketIter = 0; socketIter < SoAd_GetSizeOfSocket(); socketIter++ )
  {
    /* #20 Check if current SoAd socket is mapped to the passed INTEGRITY socket. */
    if ( SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIter) == IntegritySocketIdx )
    {
      /* #30 Use the first mapped SoAd socket if no destination address was passed. */
      if ( DestAddrPtr == NULL_PTR )
      {
        socketIdx = (SoAd_SizeOfSocketType)socketIter;
      }
      /* #31 Find a SoAd socket which local address is equal to passed destination address otherwise. */
      else
      {
        SoAd_LocalAddrIdxOfSocketToIntegritySocketMapType localAddrIdx =
          SoAd_GetLocalAddrIdxOfSocketToIntegritySocketMap(socketIter);

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_GetDomainOfIntegritySocketDyn(IntegritySocketIdx) == SOAD_AF_INET6 )
        {
          uint8_least ipV6AddrByteIter;
          socketIdx = (SoAd_SizeOfSocketType)socketIter;
          for ( ipV6AddrByteIter = 0; ipV6AddrByteIter < SOAD_IPV6_ADDR_LEN_BYTE; ipV6AddrByteIter++ )
          {
            if ( SoAd_GetAddrOfLocalAddrDyn(localAddrIdx).addr[ipV6AddrByteIter] !=
                DestAddrPtr->addr[ipV6AddrByteIter] )
            {
              socketIdx = SoAd_GetSizeOfSocket();
              break;
            }
          }
        }
        else
# endif /* SOAD_IPV6 == STD_ON */
        {
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
          if ( SoAd_GetAddrOfLocalAddrDyn(localAddrIdx).addr32[0] == DestAddrPtr->addr32[0] )
          {
            socketIdx = (SoAd_SizeOfSocketType)socketIter;
          }
# else
          if ( SoAd_GetAddrOfLocalAddrDyn(localAddrIdx) == (*DestAddrPtr) )
          {
            socketIdx = (SoAd_SizeOfSocketType)socketIter;
          }
# endif /* SOAD_IPV6 == STD_ON */
        }
      }

      if ( socketIdx < SoAd_GetSizeOfSocket() )
      {
        break;
      }
    }
  }

  /* #40 Forward the received message to the SoAd_RxIndication. */
  SoAd_RxIndication(socketIdx, RemAddrPtr, BufPtr, Length); /* SocketId and SocketIdx are equal for INTEGRITY. */

} /* SoAd_TcpIpBsd_IntegrityRxIndication() */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityTcpReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityTcpReceive(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType               retVal = E_NOT_OK;
  SoAd_IntegrityRxReturnType   receiveRetVal;
  sint32                       bufLen;
  SoAd_SizeOfTcpRxBufferType   bufIdx;
  SoAd_SizeOfSocketType        socketIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTcpRxMgtType      tcpRxMgtIdx = SoAd_GetTcpRxMgtIdxOfSocket(socketIdx);
  SoAd_SizeOfTcpRxBufferType   tcpRxBufferMaxLen =
    SoAd_GetTcpRxBufferEndIdxOfSocket(socketIdx) - SoAd_GetTcpRxBufferStartIdxOfSocket(socketIdx);
  SoAd_SizeOfTcpRxBufferType   tcpRxBufferRelIdx =
    SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) - SoAd_GetTcpRxBufferStartIdxOfSocket(socketIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if reception buffer is sufficient to receive data and mark to repeat if not. */
  if ( SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx) != tcpRxBufferMaxLen )
  {
    /* #20 Get next buffer segment from local ring buffer. */
    if ( tcpRxBufferMaxLen <= (tcpRxBufferRelIdx + SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx)) )
    {
      /* wrap around. */
      bufLen = tcpRxBufferMaxLen - SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx);
      bufIdx = (SoAd_SizeOfTcpRxBufferType)(SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) - bufLen);
    }
    else
    {
      /* no wrap around. */
      bufLen = tcpRxBufferMaxLen - (tcpRxBufferRelIdx + SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx));
      bufIdx = SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) + SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx);
    }

    /* #30 Receive data. */
    receiveRetVal = SoAd_TcpIpBsd_IntegrityReceive(SoConIdx, SoAd_GetAddrTcpRxBuffer(bufIdx), &bufLen);

    if ( (receiveRetVal == SOAD_INTEGRITY_RX_E_OK) || (receiveRetVal == SOAD_INTEGRITY_RX_E_AGAIN) )
    {
      if ( receiveRetVal == SOAD_INTEGRITY_RX_E_OK )
      {
        SoAd_SetLenOfTcpRxMgt(tcpRxMgtIdx, (SoAd_LenOfTcpRxMgtType)(SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx) + bufLen));
      }

      retVal = E_OK;
    }

  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityTcpReceive() */
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityUdpReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityUdpReceive(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType         retVal = E_NOT_OK;
  sint32                 dataLen = SoAd_GetSizeOfUdpRxBuffer();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to receive data. */
  if ( SoAd_TcpIpBsd_IntegrityReceive(SoConIdx, SoAd_GetAddrUdpRxBuffer(0u), &dataLen) != SOAD_INTEGRITY_RX_E_NOT_OK )
  {
    retVal = E_OK;
  }
  return retVal;

} /* SoAd_TcpIpBsd_IntegrityUdpReceive() */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityTcpAcceptGetAndMapSocket()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_IntegrityTcpAcceptGetAndMapSocket(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemSockAddr,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_VAR) SocketIdConnectedPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                     retVal = E_NOT_OK;
  SoAd_SizeOfSoConType               bestMatchSoConIdx;
  SoAd_SizeOfSocketType              socketIdx;
  SoAd_SizeOfIntegritySocketDynType  integritySocketIdx;
  SoAd_SizeOfLocalAddrType           localAddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get best match socket connection. */
  if ( SoAd_SoCon_TcpAcceptedGetSoConIdx(SoConIdx, RemSockAddr, &bestMatchSoConIdx) == E_OK )
  {
    socketIdx = SoAd_GetSocketIdxOfSoCon(bestMatchSoConIdx);
    /* #20 Get the mapped INTEGRITY Os socket or a free one. */
    integritySocketIdx = SoAd_TcpIpBsd_IntegrityGetMappedOrFreeSocket(socketIdx);

    /* #30 Verify that a valid INTEGRITY socket was found. */
    if ( integritySocketIdx < SoAd_GetSizeOfIntegritySocketDyn() )
    {
      localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(bestMatchSoConIdx));

      /* #40 Map the SoAd socket to the INTEGRITY socket. */
      SoAd_SetIntegritySocketDynIdxOfSocketToIntegritySocketMap(socketIdx, integritySocketIdx);
      SoAd_SetLocalAddrIdxOfSocketToIntegritySocketMap(socketIdx, localAddrIdx);

      /* #50 Store all required information in INTEGRITY socket and set its state to OS_SOCKET_AVAILABLE. */
      SoAd_SetSocketIdOfIntegritySocketDyn(integritySocketIdx, (*SocketIdConnectedPtr));
      SoAd_SetIntegrityIfIdxOfIntegritySocketDyn(integritySocketIdx,
        SoAd_GetCtrlIdxOfTcpIpCtrlDyn(SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx)));
      SoAd_SetIpAddressOfIntegritySocketDyn(integritySocketIdx, SoAd_GetAddrOfLocalAddrDyn(localAddrIdx));
      SoAd_SetDomainOfIntegritySocketDyn(integritySocketIdx, SoAd_GetDomainOfLocalAddr(localAddrIdx));
      SoAd_SetStateOfIntegritySocketDyn(integritySocketIdx, SOAD_INTEGRITY_SOCKET_S_OS_SOCKET_AVAILABLE);
      SoAd_SetProtocolOfIntegritySocketDyn(integritySocketIdx, SOAD_IPPROTO_TCP);
      SoAd_SetPortOfIntegritySocketDyn(integritySocketIdx, SoAd_SoCon_GetLocalPortDyn(socketIdx));

      SoAd_IncUsedCountOfIntegritySocketDyn(integritySocketIdx);

      /* #60 Set SocketIdConnected to the SoAd socket index (SoAd internal handle). */
      (*SocketIdConnectedPtr) = (SoAd_SocketIdType)socketIdx; /* Socket index is used as socket handle in INTEGRITY. */

      retVal = E_OK;
    }
  }
#  if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  /* #11 Increment dropped TCP connection counter otherwise. */
  else
  {
    SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP_CONNECTION, 1);
  }
#  endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

  return retVal;
} /* SoAd_TcpIpBsd_IntegrityTcpAcceptGetAndMapSocket() */
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_IntegrityIsBroadcast()
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
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_IntegrityIsBroadcast(
  P2CONST(SoAd_IpAddrInetXType, AUTOMATIC, SOAD_APPL_VAR) AddrPtr,
  SoAd_DomainType Domain,
  SoAd_NetmaskOfLocalAddrDynType Netmask)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isBroadcast = FALSE;

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* #10 Check the domain of the passed IP address. */
  if ( Domain == SOAD_AF_INET6 )
  {
    /* IPv6 Broadcast is FF01::1 and FF02::1 */
    /* #200 Check if IPv6 address starts with 0xFF01 or 0xFF02 and ends with 0x01. */
    if ( (AddrPtr->addr[0u] == 0xFFu) &&
         ((AddrPtr->addr[1u] == 0x01u) || (AddrPtr->addr[1u] == 0x02u)) &&
         (AddrPtr->addr[15u] == 0x01u) )
    {
      /* #201 Verify that remaining bytes are '0'. */
      uint8 idx;

      isBroadcast = TRUE;
      for ( idx = 2u; idx < 15u; idx++ )
      {
        if ( AddrPtr->addr[idx] != 0x00u )
        {
          isBroadcast = FALSE;
          break;
        }
      }
    }
  }
  else
# endif /* SOAD_IPV6 == STD_ON */
  {
    /* #300 Derive the broadcast mask from the passed Netmask in case of IPv4. */
    SoAd_IpAddrInetType v4Addr;
    uint32 broadcastMask = ((1 << (32 - Netmask)) - 1);
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    v4Addr = IPBASE_SWAP32(AddrPtr->addr32[0]);
# else
    v4Addr = IPBASE_SWAP32((*AddrPtr));
# endif /* SOAD_IPV6 == STD_ON */

    /* #301 Mark passed IP address as broadcast if all bits of the broadcast mask are set. */
    isBroadcast = (boolean)((v4Addr & broadcastMask) == broadcastMask);
  }

# if ( SOAD_IPV6 == STD_OFF ) /* COV_SOAD_QM_FEATURE_3 */
  SOAD_DUMMY_STATEMENT(Domain);
# endif /* SOAD_IPV6 == STD_OFF */

  return isBroadcast;
} /* SoAd_TcpIpBsd_IntegrityIsBroadcast() */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxGetPhysAddr()
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
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_QnxGetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(struct ifaddrs)  addrPtr;
  SOAD_P2VAR(struct ifaddrs)  addrPtrIdx;
  SOAD_P2CONST(uint8)         phyAddrPtr;
  SoAd_SizeOfSoConGrpType     soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType    localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfTcpIpCtrlType    tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a list of all interfaces on the system can be get. */
  if ( getifaddrs(&addrPtr) != SOAD_E_BSD_NOT_OK )
  {
    /* #20 Iterate over all interfaces. */
    for ( addrPtrIdx = addrPtr; addrPtrIdx != NULL; addrPtrIdx = addrPtrIdx->ifa_next )
    {
      /* #30 Check if the interface name is equal to the requested one. */
      if ( IpBase_StrCmp(
        SOAD_A_P2CONST(uint8)addrPtrIdx->ifa_name,
        SOAD_A_P2CONST(uint8)SoAd_GetAddrCtrlName(SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx))) ==
          IPBASE_CMP_EQUAL )
      {
        /* #40 Check if the interface address is valid and a link layer address (MAC address). */
        if ( (addrPtrIdx->ifa_addr != SOAD_INV_PHYS_ADDR) && (addrPtrIdx->ifa_addr->sa_family == AF_LINK) )
        {
          /* #50 Store the address in the provided buffer, stop iteration and assume that the request is successful. */
          phyAddrPtr = SOAD_A_P2CONST(uint8)LLADDR(SOAD_A_P2VAR(struct sockaddr_dl)(addrPtrIdx)->ifa_addr);
          PhysAddrPtr[0u] = phyAddrPtr[0u];
          PhysAddrPtr[1u] = phyAddrPtr[1u];
          PhysAddrPtr[2u] = phyAddrPtr[2u];
          PhysAddrPtr[3u] = phyAddrPtr[3u];
          PhysAddrPtr[4u] = phyAddrPtr[4u];
          PhysAddrPtr[5u] = phyAddrPtr[5u];

          retVal = E_OK;

          break;
        }
      }
    }
    /* #60 Release the list of all interfaces on the system. */
    freeifaddrs(addrPtr);
  }
  /* #11 Report error on socket otherwise. */
  else
  {
    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_QNX_GET_PHYS_ADDR, SOAD_SOCK_BSD_API_GET_IF_ADDR, errno);
  }

  return retVal;
} /* SoAd_TcpIpBsd_QnxGetPhysAddr() */

 /**********************************************************************************************************************
  *  SoAd_TcpIpBsd_QnxJoinMultiCastGroupV4()
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
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_QnxJoinMultiCastGroupV4(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  struct ip_mreq              mreq;
  struct ifreq                ifr;
  SOAD_P2VAR(struct ifaddrs)  addrPtr;
  SOAD_P2VAR(struct ifaddrs)  addrPtrIdx;
  SoAd_SizeOfSoConGrpType     soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType    localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfTcpIpCtrlType    tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  mreq.imr_interface.s_addr = INADDR_NONE;

  /* #10 Check if a list of all interfaces on the system can be get. */
  if ( getifaddrs(&addrPtr) != SOAD_E_BSD_NOT_OK )
  {
    /* #100 Iterate over all interfaces. */
    for ( addrPtrIdx = addrPtr; addrPtrIdx != NULL; addrPtrIdx = addrPtrIdx->ifa_next )
    {
      /* #1000 Check if the interface name is equal to the requested one. */
      if ( IpBase_StrCmp(
        SOAD_A_P2CONST(uint8)(addrPtrIdx->ifa_name),
        SOAD_A_P2CONST(uint8)SoAd_GetAddrCtrlName(SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx))) ==
          IPBASE_CMP_EQUAL )
      {
        /* #10000 Check if the address is valid and a IPv4 address. */
        if ( ( addrPtrIdx->ifa_addr != INADDR_ANY ) && ( addrPtrIdx->ifa_addr->sa_family == AF_INET ) )
        {
          /* #100000 Store the IP address to use it later to join multicast address on it. */
          mreq.imr_interface.s_addr = (SOAD_A_P2VAR(struct sockaddr_in)(addrPtrIdx->ifa_addr))->sin_addr.s_addr;
          /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
          VStdMemCpy(
            SOAD_A_P2VAR(void)ifr.ifr_name,
            SOAD_A_P2CONST(void)addrPtrIdx->ifa_name,
            sizeof(ifr.ifr_name));
          break;
        }
      }
    }
    /* #101 Release the list of all interfaces on the system. */
    freeifaddrs(addrPtr);
  }
  /* #11 Report error on socket otherwise. */
  else
  {
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_QNX_JOIN_MCAST_GRP_V4, SOAD_SOCK_BSD_API_GET_IF_ADDR,
      SOAD_SOCK_BSD_PARAM_NONE, SOAD_SOCK_BSD_VALUE_NONE, SocketId, errno);
  }

  /* #20 Check if the corresponding IP address has been found. */
  if ( mreq.imr_interface.s_addr != INADDR_NONE )
  {
    SoAd_IpAddrInetXType localIpAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdx);

    /* #200 Check if multicast group can be joined. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    mreq.imr_multiaddr.s_addr = localIpAddr.addr32[0u];
# else
    mreq.imr_multiaddr.s_addr = localIpAddr;
# endif /* SOAD_IPV6 == STD_ON */
    if ( setsockopt(SocketId, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != SOAD_E_BSD_NOT_OK )
    {
      /* #2000 Rebind the socket to the interface of the passed connection. */
      retVal = SoAd_TcpIpBsd_BindSingleSocketToInterface(SoConIdx, SocketId);
    }
    /* #201 Report error on socket otherwise. */
    else
    {
      SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_QNX_JOIN_MCAST_GRP_V4, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
        SOAD_SOCK_BSD_PARAM_IP_ADD_MEMBERSHIP, SOAD_SOCK_BSD_VALUE_NONE, SocketId, errno);
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_QnxJoinMultiCastGroupV4() */

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) AddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean ScopeIdSet = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if second 16 bit of the IPv6 address is set to zero. */
  if ( (AddrPtr[SOAD_ADDR_IF_OFFSET] == 0u) && (AddrPtr[SOAD_ADDR_IF_OFFSET + 1u] == 0u) )
  {
    ScopeIdSet = FALSE;
  }

  return ScopeIdSet;
} /* SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6(
  uint16 CtrlIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) AddrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store the interface id in the second 16 bit of the IPv6 address. */
  /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
  VStdMemCpy(
    SOAD_A_P2VAR(void)(&AddrPtr[SOAD_ADDR_IF_OFFSET]),
    SOAD_A_P2VAR(void)(&CtrlIdx),
    sizeof(CtrlIdx));
} /* SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6() */
# endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_QnxUdpReceiveFromIPv4LimBroadcast()
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
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_QnxUdpReceiveFromIPv4LimBroadcast(
  SoAd_SocketIdType SocketId,
  P2VAR(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr,
  socklen_t RemAddrSize,
  P2VAR(sint32, AUTOMATIC, SOAD_APPL_VAR) ErrorPtr,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_VAR) IsLimBroadcastPtr,
  P2VAR(ssize_t, AUTOMATIC, SOAD_APPL_VAR) RxDataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  struct msghdr               msg;
  struct iovec                iov[1];
  sint8                       control[CMSG_SPACE(sizeof(struct cmsghdr)) + CMSG_SPACE(sizeof(struct in_addr))];
  SOAD_P2VAR(struct in_addr)  destAddr;
  SOAD_P2VAR(struct cmsghdr)  ctlMsgHdr;

  /* ----- Implementation ----------------------------------------------- */
  *IsLimBroadcastPtr = FALSE;

  /* #10 Prepare structure to receive a message. */
  iov[0u].iov_base = SoAd_GetAddrUdpRxBuffer(0u);
  iov[0u].iov_len = SoAd_GetSizeOfUdpRxBuffer();
  msg.msg_control = &control;
  msg.msg_controllen = sizeof(control);
  msg.msg_flags = 0;
  msg.msg_name = RemAddrPtr;
  msg.msg_namelen = RemAddrSize;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;

  /* #20 Call socket API to receive a message. */
  *RxDataLenPtr = recvmsg(SocketId, &msg, 0u);
  *ErrorPtr = errno;

  /* #30 Check if an unexpected error occurred on socket. */
  if ( (*RxDataLenPtr == SOAD_E_BSD_NOT_OK) && ((*ErrorPtr != EAGAIN) && (*ErrorPtr != EWOULDBLOCK)) )
  {
    /* nothing to do */
  }
  /* #31 Check if data is received otherwise. */
  else if ( *RxDataLenPtr > 0u )
  {
    /* #310 Check if data is received over limited broadcast address. */
    ctlMsgHdr = SOAD_A_P2VAR(struct cmsghdr)msg.msg_control;
    destAddr = SOAD_A_P2VAR(struct in_addr)CMSG_DATA(msg.msg_control);
    if ( (ctlMsgHdr->cmsg_type == IP_RECVDSTADDR) && (ctlMsgHdr->cmsg_level == IPPROTO_IP) )
    {
      if ( destAddr->s_addr == INADDR_BROADCAST )
      {
        *IsLimBroadcastPtr = TRUE;
      }
    }
  }
  /* #32 Indicate that no data is received otherwise. */
  else
  {
    /* nothing to do */
  }
} /* SoAd_TcpIpBsd_QnxUdpReceiveFromIPv4LimBroadcast() */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_LinuxGetPhysAddr()
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
 SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_LinuxGetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  struct ifreq              ifr;
  SoAd_SocketIdType         socketId;
  SoAd_SizeOfSocketType     sockIdx;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfTcpIpCtrlType  tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get socket handle dependent of the socket type. */
  sockIdx = SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx);
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) )
  {
    if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
    {
      sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
    }
  }
# endif /* SOAD_TCP == STD_ON */
  socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);

  /* #20 Check if a socket handle is currently active. */
  if ( socketId != SOAD_INV_SOCKET_ID )
  {
    /* #30 Prepare to retrieve the physical address on the socket handle. */
    /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(
      SOAD_A_P2VAR(void)ifr.ifr_name,
      SOAD_A_P2CONST(void)SoAd_GetAddrCtrlName(SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx)),
      SoAd_GetCtrlNameEndIdxOfTcpIpCtrl(tcpIpCtrlIdx) - SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx));

    /* #40 Check if physical address can be retrieved. */
    if ( ioctl(socketId, SIOCGIFHWADDR, &ifr) != SOAD_E_BSD_NOT_OK )
    {
      /* #50 Store the address in the provided buffer and assume that the request is successful. */
      PhysAddrPtr[0] = (uint8)ifr.ifr_hwaddr.sa_data[0];
      PhysAddrPtr[1] = (uint8)ifr.ifr_hwaddr.sa_data[1];
      PhysAddrPtr[2] = (uint8)ifr.ifr_hwaddr.sa_data[2];
      PhysAddrPtr[3] = (uint8)ifr.ifr_hwaddr.sa_data[3];
      PhysAddrPtr[4] = (uint8)ifr.ifr_hwaddr.sa_data[4];
      PhysAddrPtr[5] = (uint8)ifr.ifr_hwaddr.sa_data[5];

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_LinuxGetPhysAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_LinuxJoinMultiCastGroupV4()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_LinuxJoinMultiCastGroupV4(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfTcpIpCtrlType  tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  SoAd_IpAddrInetXType      localIpAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdx);
  struct ip_mreqn           mreq;
  Std_ReturnType            retVal;

  /* ----- Implementation ----------------------------------------------- */
  mreq.imr_ifindex = SoAd_GetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx);
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  mreq.imr_address.s_addr = localIpAddr.addr32[0u];
  mreq.imr_multiaddr.s_addr = localIpAddr.addr32[0u];
# else
  mreq.imr_address.s_addr = localIpAddr;
  mreq.imr_multiaddr.s_addr = localIpAddr;
# endif /* SOAD_IPV6 == STD_ON */

  /* #10 Check if multicast group can be joined. */
  if ( setsockopt(SocketId, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != SOAD_E_BSD_NOT_OK )
  {
    retVal = E_OK;
  }
  /* #11 Report error on socket otherwise. */
  else
  {
    retVal = E_NOT_OK;
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
      SOAD_SOCK_BSD_PARAM_IP_ADD_MEMBERSHIP, SOAD_SOCK_BSD_VALUE_NONE, SocketId, errno);
  }

  return retVal;
} /* SoAd_TcpIpBsd_LinuxJoinMultiCastGroupV4() */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX */

#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_RequestIpAddrAssignment()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_RequestIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_IpAddrInetXType      localIpAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if local IP address is already assigned. */
  if ( SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) == SOAD_IPADDR_STATE_ASSIGNED )
  {
    /* #100 If local IP address is assigned check if local IP address is of assignment type static. */
    if ( Type == SOAD_IPADDR_ASSIGNMENT_STATIC )
    {
      /* #1000 Accept request for same IP address. */
      if ( E_OK == SoAd_Util_CompareIpAddr(SoAd_GetDomainOfLocalAddr(localAddrIdx),
          (SOAD_A_P2VAR(SoAd_SockAddrInetXType)LocalIpAddrPtr)->addr,
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
          &localIpAddr.addr32[0],
# else
          &localIpAddr,
# endif /* SOAD_IPV6 == STD_ON */
          FALSE) )
      {
        retVal = E_OK;
      }
    }
  }
  else
  {
    /* #101 If local IP address is not assigned check if assignment trigger is manual. */
    if ( SoAd_GetAssignTriggerOfLocalAddr(localAddrIdx) == SOAD_ASSIGN_TRIGGER_MANUAL )
    {
      /* #1010 Set static IP address. */
      if ( Type == SOAD_IPADDR_ASSIGNMENT_STATIC )
      {
        /* #10100 Set IPv6 address if valid. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
        {
          if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_MULTICAST )
          { /* multicast address */
            /* check if address is a valid multicast address */
            if ( ((SOAD_A_P2VAR(SoAd_SockAddrInet6Type)LocalIpAddrPtr)->addr[0] & SOAD_IPV6_MULTICAST_PREFIX_MASK) ==
              SOAD_IPV6_MULTICAST_PREFIX )
            { /* valid multicast address */
              retVal = E_OK;
            }
          }
          else
          { /* unicast address */
            if ( ((SOAD_A_P2VAR(SoAd_SockAddrInet6Type)LocalIpAddrPtr)->addr[0] & SOAD_IPV6_MULTICAST_PREFIX_MASK) !=
              SOAD_IPV6_MULTICAST_PREFIX )
            { /* no multicast address */
              retVal = E_OK;
            }
          }

          if ( retVal == E_OK )
          { /* valid address */
            /* overwrite current local address */
            localIpAddr.addr32[0u] = (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)LocalIpAddrPtr)->addr[0u];
            localIpAddr.addr32[1u] = (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)LocalIpAddrPtr)->addr[1u];
            localIpAddr.addr32[2u] = (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)LocalIpAddrPtr)->addr[2u];
            localIpAddr.addr32[3u] = (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)LocalIpAddrPtr)->addr[3u];

            SoAd_SetAddrOfLocalAddrDyn(localAddrIdx, localIpAddr);

            /* set local address to "requested" */
            SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_REQUEST);

            /* set event to handle local address in main function */
            SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, localAddrIdx);
          }
        }
        else
# endif /* SOAD_IPV6 == STD_ON */
        /* #10101 Set IPv4 address if valid. */
        {
          if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_MULTICAST )
          { /* multicast address */
            /* check if address is a valid multicast address */
            if ( ((SOAD_A_P2VAR(SoAd_SockAddrInetType)LocalIpAddrPtr)->addr[0] & SOAD_IPV4_MULTICAST_PREFIX_MASK) ==
              SOAD_IPV4_MULTICAST_PREFIX )
            { /* valid multicast address */
              retVal = E_OK;
            }
          }
          else
          { /* unicast address */
            if ( DefaultRouterPtr != NULL_PTR )
            {
              if ( Netmask <= 32u )
              { /* valid netmask */
                if ( ((SOAD_A_P2VAR(SoAd_SockAddrInetType)LocalIpAddrPtr)->addr[0] &
                  SOAD_IPV4_MULTICAST_PREFIX_MASK) != SOAD_IPV4_MULTICAST_PREFIX )
                { /* no multicast address */
                  retVal = E_OK;
                }
              }
            }
          }

          if ( retVal == E_OK )
          { /* valid address */
            /* overwrite current netmask */
            SoAd_SetNetmaskOfLocalAddrDyn(localAddrIdx, Netmask);

            /* overwrite current local address */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
            localIpAddr.addr32[0u] = (SOAD_A_P2VAR(SoAd_SockAddrInetType)LocalIpAddrPtr)->addr[0u];
            localIpAddr.addr32[1u] = SOAD_IPADDR_ANY;
            localIpAddr.addr32[2u] = SOAD_IPADDR_ANY;
            localIpAddr.addr32[3u] = SOAD_IPADDR_ANY;
# else
            localIpAddr = (SOAD_A_P2VAR(SoAd_SockAddrInetType)LocalIpAddrPtr)->addr[0u];
# endif /* SOAD_IPV6 == STD_ON */

            SoAd_SetAddrOfLocalAddrDyn(localAddrIdx, localIpAddr);

            /* set local address to "requested" */
            SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_REQUEST);

            /* set event to handle local address in main function */
            SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, localAddrIdx);
          }
        }
      }
      /* #1011 Accept request for link-local or DHCP IP address since it is automatically started at startup. */
      else
      {
        retVal = E_OK;

        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, localAddrIdx);
      }
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_RequestIpAddrAssignment() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_GetSocket()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_GetSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_DomainType Domain,
  SoAd_ProtocolType Protocol,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_DATA) SocketIdPtr)
{
# if (SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY) /* COV_SOAD_QM_FEATURE_3 */
  SOAD_DUMMY_STATEMENT(Domain); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(Protocol); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return SoAd_TcpIpBsd_IntegrityPrepareSocket(SoConIdx, SocketIdPtr);
# else
  /* ----- Local Variables ---------------------------------------------- */
  sint32                    domain;
  sint32                    type;
  sint32                    protocol = 0;
  SoAd_SocketIdType         socketId;
  SoAd_SocketIdType         dirLinkSocketId;
  SoAd_SocketIdType         limNodeSocketId;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert domain for BSD-like Socket API. */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( Domain == SOAD_AF_INET6 )
  {
    domain = AF_INET6;
  }
  else
#  endif /* SOAD_IPV6 == STD_ON */
  {
    domain = AF_INET;
  }

  /* #20 Convert protocol for BSD-like Socket API. */
#  if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( Protocol == SOAD_IPPROTO_TCP )
  {
    type = SOCK_STREAM;
  }
  else
#  endif /* SOAD_TCP == STD_ON */
  {
    type = SOCK_DGRAM;
  }

  /* #30 Get socket from BSD-like Socket API. */
  socketId = socket(domain, type, protocol);

  /* #40 Check if socket is UDP and of type unicast and if broadcasts are enabled for this socket. */
  if ( (Protocol == SOAD_IPPROTO_UDP) && (SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST) &&
    SoAd_IsBroadcastRxEnabledOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
  {
    /* #400 Get separate socket to receive from directed broadcast/link-local address. */
    dirLinkSocketId = socket(domain, type, protocol);

    /* #401 Get separate socket to receive from limited broadcast/node-local address. */
    limNodeSocketId = socket(domain, type, protocol);
  }
  else
  {
    dirLinkSocketId = socketId;
    limNodeSocketId = socketId;
  }

  /* #50 Handle errors. */
  if ( (socketId == SOAD_INV_SOCKET_ID) || (dirLinkSocketId == SOAD_INV_SOCKET_ID) ||
    (limNodeSocketId == SOAD_INV_SOCKET_ID) )
  {
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_GET_SOCKET, SOAD_SOCK_BSD_API_SOCKET,
      SOAD_SOCK_BSD_PARAM_NONE, domain, type, errno);

    if ( socketId != SOAD_INV_SOCKET_ID )
    {
      (void)close(socketId);
    }
    if ( dirLinkSocketId != SOAD_INV_SOCKET_ID )
    {
      (void)close(dirLinkSocketId);
    }
    if ( limNodeSocketId != SOAD_INV_SOCKET_ID )
    {
      (void)close(limNodeSocketId);
    }
  }
  /* #60 Return socket in case no error occurred. */
  else
  {
    *SocketIdPtr = socketId;
    SoAd_SetDirLinkSocketIdOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), dirLinkSocketId);
    SoAd_SetLimNodeSocketIdOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), limNodeSocketId);

    retVal = E_OK;
  }

  return retVal;
# endif /* (SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY) */
} /* SoAd_TcpIpBsd_GetSocket() */

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_Bind()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_Bind(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_IpAddrInetXType      localIpAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* #10 Check if local IP address is of type IPv6. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
  {
    struct sockaddr_in6 localAddrV6;

    /* #100 Bind socket to local address. */
    localAddrV6.sin6_family = AF_INET6;
    localAddrV6.sin6_port = IPBASE_HTON16(*PortPtr);
    localAddrV6.sin6_flowinfo = 0u;
    localAddrV6.sin6_scope_id = SoAd_GetCtrlIdxOfTcpIpCtrlDyn(SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx));

    /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(
      SOAD_A_P2VAR(void)localAddrV6.sin6_addr.s6_addr,
      SOAD_A_P2CONST(void)&localIpAddr.addr32[0u],
      SOAD_IPV6_ADDR_LEN_BYTE);

#   if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
    if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST )
    {
      if ( SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6(localAddrV6.sin6_addr.s6_addr) == FALSE )
      {
        SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6(
          IPBASE_SWAP16(SoAd_GetCtrlIdxOfTcpIpCtrlDyn(SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx))),
          localAddrV6.sin6_addr.s6_addr);
      }
      localAddrV6.sin6_scope_id = 0;
    }
#   endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */

    retVal = SoAd_TcpIpBsd_BindSingleSocket(SoConIdx, SocketId, SOAD_A_P2CONST(struct sockaddr)&localAddrV6,
      sizeof(localAddrV6), PortPtr);

    localAddrV6.sin6_port = IPBASE_HTON16(*PortPtr);

    /* #101 Check if socket is UDP and of type unicast and if broadcasts are enabled for this socket. */
#   if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
#   endif /* SOAD_TCP == STD_ON */
    {
      if ( (SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST) &&
        SoAd_IsBroadcastRxEnabledOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
      {
        /* #1010 Bind separate socket to receive from directed broadcast/link-local address. */
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[0])  = IPBASE_HTON32(0xFF020000ul);
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[4])  = IPBASE_HTON32(0x00000000ul);
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[8])  = IPBASE_HTON32(0x00000000ul);
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[12]) = IPBASE_HTON32(0x00000001ul);
#   if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6(localAddrV6.sin6_addr.s6_addr) == FALSE )
        {
          SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6(
            IPBASE_SWAP16(SoAd_GetCtrlIdxOfTcpIpCtrlDyn(SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx))),
            localAddrV6.sin6_addr.s6_addr);
        }
#   endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */

        retVal |= SoAd_TcpIpBsd_BindSingleSocket(SoConIdx, SoAd_GetDirLinkSocketIdOfSocketDyn(sockIdx),
          SOAD_A_P2CONST(struct sockaddr)&localAddrV6, sizeof(localAddrV6), PortPtr);

        /* #1011 Bind separate socket to receive from limited broadcast/node-local address. */
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[0])  = IPBASE_HTON32(0xFF010000ul);
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[4])  = IPBASE_HTON32(0x00000000ul);
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[8])  = IPBASE_HTON32(0x00000000ul);
        *((uint32*)&localAddrV6.sin6_addr.s6_addr[12]) = IPBASE_HTON32(0x00000001ul);
#   if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6(localAddrV6.sin6_addr.s6_addr) == FALSE )
        {
          SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6(
            IPBASE_SWAP16(SoAd_GetCtrlIdxOfTcpIpCtrlDyn(SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx))),
            localAddrV6.sin6_addr.s6_addr);
        }
#   endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */

        retVal |= SoAd_TcpIpBsd_BindSingleSocket(SoConIdx, SoAd_GetLimNodeSocketIdOfSocketDyn(sockIdx),
          SOAD_A_P2CONST(struct sockaddr)&localAddrV6, sizeof(localAddrV6), PortPtr);
      }
    }
  }
  /* #20 Check if local IP address is of type IPv4. */
  else
#  endif /* SOAD_IPV6 == STD_ON */
  {
    struct sockaddr_in localAddrV4;

    /* #200 Bind socket to local address. */
    localAddrV4.sin_family = AF_INET;
    localAddrV4.sin_port = IPBASE_HTON16(*PortPtr);
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    localAddrV4.sin_addr.s_addr = localIpAddr.addr32[0u];
#  else
    localAddrV4.sin_addr.s_addr = localIpAddr;
#  endif /* SOAD_IPV6 == STD_ON */

    retVal = SoAd_TcpIpBsd_BindSingleSocket(SoConIdx, SocketId, SOAD_A_P2CONST(struct sockaddr)&localAddrV4,
      sizeof(localAddrV4), PortPtr);

    localAddrV4.sin_port = IPBASE_HTON16(*PortPtr);

    /* #201 Check if socket is UDP and of type unicast and if broadcasts are enabled for this socket. */
#  if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
#  endif /* SOAD_TCP == STD_ON */
    {
      if ( (SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST) &&
        SoAd_IsBroadcastRxEnabledOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
      {
        /* #2010 Bind separate socket to receive from directed broadcast/link-local address. */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        localAddrV4.sin_addr.s_addr = localIpAddr.addr32[0u] |
#  else
        localAddrV4.sin_addr.s_addr = localIpAddr |
#  endif /* SOAD_IPV6 == STD_ON */
          IPBASE_HTON32((INADDR_BROADCAST >> SoAd_GetNetmaskOfLocalAddrDyn(localAddrIdx)));

        retVal |= SoAd_TcpIpBsd_BindSingleSocket(SoConIdx, SoAd_GetDirLinkSocketIdOfSocketDyn(sockIdx),
          SOAD_A_P2CONST(struct sockaddr)&localAddrV4, sizeof(localAddrV4), PortPtr);

        /* #2011 Bind separate socket to receive from limited broadcast/node-local address. */
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
        localAddrV4.sin_addr.s_addr = INADDR_ANY;
#  else
        localAddrV4.sin_addr.s_addr = INADDR_BROADCAST;
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */

        retVal |= SoAd_TcpIpBsd_BindSingleSocket(SoConIdx, SoAd_GetLimNodeSocketIdOfSocketDyn(sockIdx),
          SOAD_A_P2CONST(struct sockaddr)&localAddrV4, sizeof(localAddrV4), PortPtr);
      }
    }
  }

  /* #30 Add event to queue to handle UDP socket in main function if all calls to BSD-like Socket API succeeded. */
  if ( (retVal == E_OK)
#  if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    && SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx)
#  endif /* SOAD_TCP == STD_ON */
    )
  {
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SOCK_IDX, sockIdx);
  }

  return retVal;
} /* SoAd_TcpIpBsd_Bind() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_BindSingleSocket()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_BindSingleSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2CONST(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  size_t LocalAddrSize,
  P2VAR(SoAd_PortType, AUTOMATIC, SOAD_APPL_VAR) PortPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfLocalAddrType  localAddrIdx =  SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Bind socket via Socket API. */
  if ( bind(SocketId, LocalAddrPtr, LocalAddrSize) == SOAD_E_BSD_NOT_OK )
  {
    /* #100 Report error on socket if bind failed. */
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_BIND_SINGLE_SOCKET, SOAD_SOCK_BSD_API_BIND,
      SOAD_SOCK_BSD_PARAM_NONE, SoAd_GetSocketIdOfSocketDyn(SoConIdx), SocketId, errno);

    /* #101 Check if local address is still available. */
    if ( errno == EADDRNOTAVAIL )
    {
      if ( SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr(localAddrIdx, FALSE) == E_NOT_OK )
      {
        /* #1010 Mark local address as to be released. */
        SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_RELEASE);

        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, localAddrIdx);
      }
    }

    retVal = E_NOT_OK;
  }
  /* #20 Bind socket to interface if bind succeeded. */
  else if ( SoAd_TcpIpBsd_BindSingleSocketToInterface(SoConIdx, SocketId) == E_NOT_OK )
  {
    retVal = E_NOT_OK;
  }
  /* #30 Check if port has been chosen randomly if bind and bind to interface succeeded. */
  else
  {
    if ( *PortPtr == 0u )
    {
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
      struct sockaddr_in6 sockAddr;
      socklen_t sockAddrSize = sizeof(sockAddr);
#  else
      struct sockaddr_in sockAddr;
      socklen_t sockAddrSize = sizeof(sockAddr);
#  endif /* SOAD_IPV6 == STD_ON */

      /* #300 Get port via BSD-like Socket API. */
      if ( getsockname(SocketId, SOAD_A_P2VAR(struct sockaddr)&sockAddr, &sockAddrSize) == SOAD_E_BSD_NOT_OK )
      {
        /* #3000 Report BSD-like Socket API error if call failed. */
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_BIND_SINGLE_SOCKET, SOAD_SOCK_BSD_API_GET_SOCK_NAME,
          SOAD_SOCK_BSD_PARAM_NONE, SoAd_GetSocketIdOfSocketDyn(SoConIdx), SocketId, errno);

        retVal = E_NOT_OK;
      }
      else
      {
        /* #3001 Update local port if call succeeded. */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
        {
          *PortPtr = IPBASE_SWAP16((SOAD_A_P2VAR(struct sockaddr_in6)&sockAddr)->sin6_port);
        }
        else
#  endif /* SOAD_IPV6 == STD_ON */
        {
          *PortPtr = IPBASE_SWAP16((SOAD_A_P2VAR(struct sockaddr_in)&sockAddr)->sin_port);
        }
      }
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_BindSingleSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_BindSingleSocketToInterface()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_BindSingleSocketToInterface(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  struct ifreq              ifr;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfTcpIpCtrlType  tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  Std_ReturnType            retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the interface request. */
  IpBase_StrCpy(
    SOAD_A_P2VAR(uint8)ifr.ifr_name,
    SOAD_A_P2CONST(uint8)SoAd_GetAddrCtrlName(SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx)));

  /* #20 Bind socket to interface. */
  if ( setsockopt(SocketId, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof(ifr)) == SOAD_E_BSD_NOT_OK )
  {
    retVal = E_NOT_OK;
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_BIND_SINGLE_SOCK_TO_IFC, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
      SOAD_SOCK_BSD_PARAM_SO_BIND_TO_DEVICE, SOAD_SOCK_BSD_VALUE_NONE, SocketId, errno);
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TcpIpBsd_BindSingleSocketToInterface() */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ChangeParameter()
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
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_ChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  SoAd_ParamIdType ParameterId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ParameterValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                     retVal = E_OK;
  sint32                             osSocketId;
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_SizeOfIntegritySocketDynType  integritySocketIdx =
    SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SocketId);
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  osSocketId = SoAd_GetSocketIdOfIntegritySocketDyn(integritySocketIdx);
# else
  osSocketId = SocketId;
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_3 */
#  if ( SOAD_TCP == STD_OFF ) /* COV_SOAD_QM_FEATURE_3 */
  SOAD_DUMMY_STATEMENT(ParameterValue); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif /* SOAD_TCP == STD_OFF */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_LINUX */

  switch ( ParameterId )
  {
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_3 */
    /* #10 Set frame priority. */
  case SOAD_PARAMID_FRAMEPRIO:
    {
      sint32                    var = *ParameterValue;
      SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
      SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
      SoAd_SizeOfTcpIpCtrlType  tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);

      /* Set frame priority on socket. */
      if ( setsockopt(osSocketId, SOL_SOCKET, SO_PRIORITY, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
          SOAD_SOCK_BSD_PARAM_PRIORITY, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      /* Set egress map to use the same VLAN priority in frame like on socket if enabled. */
      else if ( SoAd_IsSetEgressEnabledOfTcpIpCtrl(tcpIpCtrlIdx) )
      {
        struct vlan_ioctl_args vlanIoctlArgs;

        vlanIoctlArgs.cmd = SET_VLAN_EGRESS_PRIORITY_CMD;
        vlanIoctlArgs.u.skb_priority = var;
        vlanIoctlArgs.vlan_qos = var;

        /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
        VStdMemCpy(
          SOAD_A_P2VAR(void)vlanIoctlArgs.device1,
          SOAD_A_P2CONST(void)SoAd_GetAddrCtrlName(SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx)),
          SoAd_GetCtrlNameEndIdxOfTcpIpCtrl(tcpIpCtrlIdx) - SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx));

        if ( ioctl(osSocketId, SIOCSIFVLAN, &vlanIoctlArgs) == SOAD_E_BSD_NOT_OK )
        {
          retVal = E_NOT_OK;
          SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_IOCTL,
            SOAD_SOCK_BSD_PARAM_SIOCSIFVLAN, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
        }
      }
      else
      {
        /* Nothing to do. */
      }
      break;
    }
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    /* #20 Set TCP rx buffer size. */
  case SOAD_PARAMID_TCP_RXWND_MAX:
    {
      sint32 sockTpRxBufMin = *((uint32*)ParameterValue);

      if ( setsockopt(osSocketId, SOL_SOCKET, SO_RCVBUF, &sockTpRxBufMin, sizeof(sockTpRxBufMin)) ==
          SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
          SOAD_SOCK_BSD_PARAM_RCVBUF, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      break;
    }
    /* #30 Set TCP tx buffer size. */
  case SOAD_PARAMID_TCP_TXWND_MAX:
    {
      sint32 sockTcpTxBufMin = *((uint32*)ParameterValue);

      if ( setsockopt(osSocketId, SOL_SOCKET, SO_SNDBUF, &sockTcpTxBufMin, sizeof(sockTcpTxBufMin)) ==
        SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
          SOAD_SOCK_BSD_PARAM_SNDBUF, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      break;
    }
    /* #40 Set TCP no delay (Nagle algorithm). */
  case SOAD_PARAMID_TCP_NAGLE:
    {
      sint32 var = *((uint8*)ParameterValue);
      if ( setsockopt(osSocketId, IPPROTO_TCP, TCP_NODELAY, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
            SOAD_SOCK_BSD_PARAM_NODELAY, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      break;
    }
    /* #50 Set TCP keep alive. */
  case SOAD_PARAMID_TCP_KEEPALIVE:
    {
      sint32 var = *((uint8*)ParameterValue);
      if ( setsockopt(osSocketId, SOL_SOCKET, SO_KEEPALIVE, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
            SOAD_SOCK_BSD_PARAM_SO_KEEPALIVE, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      break;
    }
    /* #60 Set TCP keep alive time. */
  case SOAD_PARAMID_TCP_KEEPALIVE_TIME:
    {
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_3 */
      sint32 var = *((uint32*)ParameterValue);

      if ( setsockopt(osSocketId, IPPROTO_TCP, TCP_KEEPIDLE, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
#  else /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */
      struct timeval tval;

      tval.tv_usec = 0;
      tval.tv_sec = *ParameterValue;
      if ( setsockopt(osSocketId, IPPROTO_TCP, TCP_KEEPALIVE, &tval, sizeof(tval)) == SOAD_E_BSD_NOT_OK )
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX */
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
          SOAD_SOCK_BSD_PARAM_TCP_KEEPALIVE, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      break;
    }
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_3 */
    /* #70 Set TCP keep alive maximum probes. */
  case SOAD_PARAMID_TCP_KEEPALIVE_PROBES_MAX:
    {
      sint32 var = *((uint16*)ParameterValue);
      if ( setsockopt(osSocketId, IPPROTO_TCP, TCP_KEEPCNT, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
          SOAD_SOCK_BSD_PARAM_TCP_KEEPALIVE_CNT, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      break;
    }
    /* #80 Set TCP keep alive interval. */
  case SOAD_PARAMID_TCP_KEEPALIVE_INTERVAL:
    {
      sint32 var = *((uint32*)ParameterValue);
      if ( setsockopt(osSocketId, IPPROTO_TCP, TCP_KEEPINTVL, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
          SOAD_SOCK_BSD_PARAM_TCP_KEEPALIVE_INTV, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      break;
    }
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX */
# endif /* SOAD_TCP == STD_ON */
    /* #90 Set BSD-like Socket API specific parameters. */
  case SOAD_PARAMID_STACK_SPECIFIC:
    {
      sint32                  var;
# if ( (SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY) || (SOAD_TCP == STD_ON) ) /* COV_SOAD_QM_FEATURE_3 */
      SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
      SoAd_SizeOfLocalAddrType localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
# endif /* (SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY) || (SOAD_TCP == STD_ON) */

      /* #900 Set socket to non-blocking mode. */
      var = fcntl(osSocketId, F_GETFL, 0);
      if ( var == SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_FCNTL,
          SOAD_SOCK_BSD_PARAM_F_GETFL, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
      else
      {
        if ( fcntl(osSocketId, F_SETFL, var|O_NONBLOCK) == SOAD_E_BSD_NOT_OK )
        {
          retVal = E_NOT_OK;
          SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
            SOAD_SOCK_BSD_PARAM_REUSEADDR, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
        }
      }

      /* #901 Set reuse option for IP address to have the possibility to bind same address to another local address. */
      var = (sint32)TRUE;
      if ( setsockopt(osSocketId, SOL_SOCKET, SO_REUSEADDR, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
      {
        retVal = E_NOT_OK;
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
          SOAD_SOCK_BSD_PARAM_REUSEADDR, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }

      /* #902 Set restriction of socket to IPv6 for UDP sockets, TCP client sockets or TCP listen sockets. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
#  if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
      if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx)) == SOAD_AF_INET6 )
      {
#   if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) ||
          !SoAd_IsSocketUsedOfSoConGrp(soConGrpIdx) ||
          (SoAd_GetSocketIdOfSocketDyn(SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx)) == SOAD_INV_SOCKET_ID) )
#   endif /* SOAD_TCP == STD_ON */
        {
          if ( setsockopt(osSocketId, IPPROTO_IPV6, IPV6_V6ONLY, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
          {
            retVal = E_NOT_OK;
            SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
              SOAD_SOCK_BSD_PARAM_IP6ONLY, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
          }
        }
      }
#  else
      SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */
# else
      SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* SOAD_IPV6 == STD_ON */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
      if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) )
      {
        /* #903 Enable linger time and set it to 0 for TCP sockets to allow faster socket connection reestablishment. */
        if ( SoAd_IsSetLingerTimeoutEnabled(0u) )
        { /* linger time enabled */
          struct linger lingerConfig;
          lingerConfig.l_onoff = 1;
          lingerConfig.l_linger = 0;
          if ( setsockopt(osSocketId, SOL_SOCKET, SO_LINGER, &lingerConfig, sizeof(lingerConfig)) == SOAD_E_BSD_NOT_OK )
          {
            retVal = E_NOT_OK;
            SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
              SOAD_SOCK_BSD_PARAM_LINGER, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
          }
        }
      }
      else
# endif /* SOAD_TCP == STD_ON */
      {
        /* #904 Set broadcast flag to have the possibility to send to broadcast addresses on UDP socket connections. */
# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST )
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */
        {
          if ( setsockopt(osSocketId, SOL_SOCKET, SO_BROADCAST, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
          {
            retVal = E_NOT_OK;
            SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
              SOAD_SOCK_BSD_PARAM_BROADCAST, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
          }
        }

        /* #905 Set the IP_RECVDSTADDR/IPV6_RECVPKTINFO option so that recvmsg() returns the destination IP address
         *      for UDP datagram. */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_IsBroadcastRxEnabledOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
        {
          if ((SoAd_GetLimNodeSocketIdOfSocketDyn(SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx)) == SocketId) &&
            (SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx)) ==
              SOAD_AF_INET) &&
              (SoAd_GetAddressTypeOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx)) ==
                SOAD_ADDRESS_TYPE_UNICAST))
          {
            if (setsockopt(SoAd_GetLimNodeSocketIdOfSocketDyn(SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx)),
              IPPROTO_IP, IP_RECVDSTADDR, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK)
            {
              SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
                SOAD_SOCK_BSD_PARAM_IP_RECVDSTADDR, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
            }
          }
        }
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_GetProtocolOfIntegritySocketDyn(integritySocketIdx) == SOAD_IPPROTO_UDP )
        {
          var = (sint32)TRUE;
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
          if ( SoAd_GetDomainOfIntegritySocketDyn(integritySocketIdx) == SOAD_AF_INET6 )
          {
            if ( setsockopt(osSocketId, IPPROTO_IPV6, IPV6_RECVPKTINFO, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
            {
              SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
                SOAD_SOCK_BSD_PARAM_IPV6_RECVPKTINFO, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
            }
          }
          else
#  endif /* SOAD_IPV6 == STD_ON */
          {
            if ( setsockopt(osSocketId, IPPROTO_IP, IP_RECVDSTADDR, &var, sizeof(var)) == SOAD_E_BSD_NOT_OK )
            {
              SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
                SOAD_SOCK_BSD_PARAM_IP_RECVDSTADDR, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
            }
          }
        }
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
      }
      break;
    }
    /* #100 Ignore not relevant parameters. */
  default:
    {
      /* Nothing to do. */
    }
  }

  return retVal;
} /* SoAd_TcpIpBsd_ChangeParameter() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleSocketReception()
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
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleSocketReception(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueSocketIdxIterType  eventQueueSockIdxIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_SOCK_IDX);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueSockIdxIter = 0u;
        eventQueueSockIdxIter < elementNumToHandle;
        eventQueueSockIdxIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_SOCK_IDX, &handleIdx) == E_OK )
    {
      SoAd_SizeOfSocketType sockIdx = (SoAd_SizeOfSocketType)handleIdx;
      boolean               addEventAgain = FALSE;

      /* #30 Check if socket is ready to receive data. */
      if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_ESTABLISHED )
      {
        SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(sockIdx);
        SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);

        /* #40 Handle reception on UDP socket. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) )
# endif /* SOAD_TCP == STD_ON */
        {
# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
          struct sockaddr_inX       sockAddr;
          socklen_t                 addrLen = sizeof(sockAddr);
          SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
          SoAd_SocketIdType         socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */

          /* #400 Receive from unicast socket. */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
          if ( SoAd_TcpIpBsd_IntegrityUdpReceive(soConIdx) == E_OK )
# else
          if ( E_OK == SoAd_TcpIpBsd_UdpReceiveFrom(soConIdx, socketId, SOAD_A_P2VAR(struct sockaddr)&sockAddr,
              addrLen) )
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
          {
            /* #4000 Add event to queue again if no socket error occurred. */
            addEventAgain = TRUE;
          }

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
          if ( (SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST) &&
            SoAd_IsBroadcastRxEnabledOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
          {
            /* #401 Receive from directed broadcast/link-local address socket. */
            if ( SoAd_GetDirLinkSocketIdOfSocketDyn(sockIdx) != SOAD_INV_SOCKET_ID )
            {
              if ( E_OK == SoAd_TcpIpBsd_UdpReceiveFrom(soConIdx, SoAd_GetDirLinkSocketIdOfSocketDyn(sockIdx),
                  SOAD_A_P2VAR(struct sockaddr)&sockAddr, addrLen) )
              {
                /* #4010 Add event to queue again if no socket error occurred */
                addEventAgain = TRUE;
              }
            }

            /* #402 Receive from limited broadcast/node-local address socket. */
            if ( SoAd_GetLimNodeSocketIdOfSocketDyn(sockIdx) != SOAD_INV_SOCKET_ID )
            {
              if ( E_OK == SoAd_TcpIpBsd_UdpReceiveFrom(soConIdx, SoAd_GetLimNodeSocketIdOfSocketDyn(sockIdx),
                  SOAD_A_P2VAR(struct sockaddr)&sockAddr, addrLen) )
              {
                /* #5020 Add event to queue again if no socket error occurred. */
                addEventAgain = TRUE;
              }
            }
          }
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */
        }
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        /* #50 Handle reception on TCP socket. */
        else
        {
          /* #500 Receive from client or server data socket. */
          if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) ||
            (SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx) != sockIdx) )
          {
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
            if ( E_OK == SoAd_TcpIpBsd_IntegrityTcpReceive(soConIdx) )
#  else
            if ( E_OK == SoAd_TcpIpBsd_TcpReceive(soConIdx) )
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
            {
              /* #5000 Add event to queue again if no socket error occurred. */
              addEventAgain = TRUE;
            }
          }
          /* #501 Add event to queue again if socket is listen socket. */
          else
          {
            addEventAgain = TRUE;
          }
        }
# endif /* SOAD_TCP == STD_ON */
      }
      /* #31 Add event to queue again if socket is not ready to receive data. */
      else
      {
        addEventAgain = TRUE;
      }
      if ( addEventAgain == TRUE )
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SOCK_IDX, sockIdx);
      }
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_TcpIpBsd_HandleSocketReception() */

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_UdpReceiveFrom()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_UdpReceiveFrom(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(struct sockaddr, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr,
  socklen_t RemAddrSize)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SocketIdType         unicastSocketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);
  ssize_t                   dataLen;
  sint32                    error;
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketUdpType  socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  boolean                   ignoreMsg = FALSE;
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
  /* #10 Check if this socket is used for reception of limited broadcasts in case of QNX. */
  if ( SoAd_IsBroadcastRxEnabledOfSocketUdp(socketUdpIdx) &&
    (SoAd_GetLimNodeSocketIdOfSocketDyn(sockIdx) == SocketId) &&
    (SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET) &&
    (SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST) )
  {
    boolean isLimBroadcast = TRUE;
    error = EOK;

    /* #100 Try to receive data sent to limited broadcasts only. */
    SoAd_TcpIpBsd_QnxUdpReceiveFromIPv4LimBroadcast(SocketId, RemAddrPtr, RemAddrSize, &error, &isLimBroadcast,
      &dataLen);

    if ( isLimBroadcast == FALSE )
    {
      ignoreMsg = TRUE;
    }
  }
  else
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */
  /* #11 Receive from socket otherwise. */
  {
    dataLen = recvfrom(SocketId, SoAd_GetAddrUdpRxBuffer(0u), SoAd_GetSizeOfUdpRxBuffer(), 0u, RemAddrPtr,
      &RemAddrSize);

    error = errno;
  }
  /* #20 Check if an unexpected error occurred. */
  if ( (dataLen == 0u) || (dataLen == SOAD_E_BSD_NOT_OK) )
  {
    /* #200 Mark to repeat if no data is received. */
    if ( ((error == EAGAIN) || (error == EWOULDBLOCK)) && (dataLen != 0) )
    {
      retVal = E_OK;
    }
    /* #201 Close unicast socket (broadcast/multicast sockets closed in same context) if unknown error occurred. */
    else
    {
      SoAd_TcpIp_Close(unicastSocketId, TRUE, sockIdx);
    }
  }
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
  /* #21 Mark to repeat if message should be ignored otherwise. */
  else if ( ignoreMsg == TRUE )
  {
    retVal = E_OK;
  }
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */
  /* #22 Handle received data otherwise. */
  else
  {
    SoAd_SockAddrInetXType remAddr;

    /* #220 Check if data is not received from own local address if data is received. */
    SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)&remAddr, RemAddrPtr);

    if ( SoAd_TcpIp_CompareToIpAddr(SoConIdx, (SoAd_IpAddrConstPtrType)remAddr.addr) == E_NOT_OK )
    {
      /* #2200 Forward received data via unicast socket since its socket identifier is known by SoAd. */
      SoAd_RxIndication(unicastSocketId, SOAD_A_P2VAR(SoAd_SockAddrType)&remAddr, SoAd_GetAddrUdpRxBuffer(0u),
        dataLen);
    }

    /* #221 Mark to repeat reception. */
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TcpIpBsd_UdpReceiveFrom() */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
#  if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_TcpReceive()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_TcpReceive(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ssize_t                     dataLen;
  SoAd_SizeOfTcpRxBufferType  bufLen;
  SoAd_SizeOfTcpRxBufferType  bufIdx;
  SoAd_SizeOfSocketType       sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SocketIdType           socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);
  SoAd_SizeOfTcpRxMgtType     tcpRxMgtIdx = SoAd_GetTcpRxMgtIdxOfSocket(sockIdx);
  SoAd_SizeOfTcpRxBufferType  tcpRxBufferMaxLen = SoAd_GetTcpRxBufferEndIdxOfSocket(sockIdx) -
    SoAd_GetTcpRxBufferStartIdxOfSocket(sockIdx);
  SoAd_SizeOfTcpRxBufferType  tcpRxBufferRelIdx = SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) -
    SoAd_GetTcpRxBufferStartIdxOfSocket(sockIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if reception buffer is sufficient to receive data and mark to repeat if not. */
  if ( SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx) != tcpRxBufferMaxLen )
  {
    /* #20 Get next buffer segment from local ring buffer.*/
    if ( tcpRxBufferMaxLen <= (tcpRxBufferRelIdx + SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx)) )
    { /* wrap around */
      bufLen = tcpRxBufferMaxLen - SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx);
      bufIdx = SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) - bufLen;
    }
    else
    { /* no wrap around */
      bufLen = tcpRxBufferMaxLen - (tcpRxBufferRelIdx + SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx));
      bufIdx = SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) + SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx);
    }

    /* #30 Receive data via BSD-like Socket API. */
    dataLen = recv(socketId, SoAd_GetAddrTcpRxBuffer(bufIdx), (ssize_t)bufLen, 0);

    /* #40 Check if no data is received or any other error occurred. */
    if ( (dataLen == 0u) || (dataLen == SOAD_E_BSD_NOT_OK) )
    {
      /* #400 Mark to repeat if no data is received. */
      if ( ((errno == EAGAIN) || (errno == EWOULDBLOCK)) && (dataLen != 0) )
      {
        retVal = E_OK;
      }
      /* #401 Close socket if unknown error occurred otherwise. */
      else
      {
        SoAd_TcpIp_Close(socketId, TRUE, sockIdx);
      }
    }
    /* #41 Mark to repeat and forward data if data is received otherwise. */
    else
    {
      SoAd_SetLenOfTcpRxMgt(tcpRxMgtIdx, SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx) + dataLen);

      SoAd_RxIndication(socketId, SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx),
        SoAd_GetAddrTcpRxBuffer(bufIdx), dataLen);

      retVal = E_OK;
    }
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TcpIpBsd_TcpReceive() */
#  endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */
# endif /* SOAD_TCP == STD_ON */

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleLocalAddressCheckInterval()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleLocalAddressCheckInterval(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_LocalAddrIterType localAddrIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Decrement local address check interval counter. */
  SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter--;

  /* #20 Check if timeout exceeded. */
  if ( SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter == 0u )
  {
    /* #200 Iterate over all local addresses. */
    for ( localAddrIter = 0u; localAddrIter < SoAd_GetSizeOfLocalAddr(); localAddrIter++ )
    {
      /* #2000 Set flag to check availability of local address for assigned unicast addresses. */
      if ( (SoAd_GetAddressTypeOfLocalAddr(localAddrIter) == SOAD_ADDRESS_TYPE_UNICAST) &&
        (SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIter) == SOAD_IPADDR_STATE_ASSIGNED) )
      {
        SoAd_SetCheckAvailabilityOfLocalAddrDyn(localAddrIter, TRUE);
      }
    }

    /* #201 Reset local address check interval counter. */
    SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter = SoAd_GetLocalAddrCheckInterval();
  }
} /* SoAd_TcpIpBsd_HandleLocalAddressCheckInterval() */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleIpAddrStates()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleIpAddrStates(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueLocalAddrIterType  eventQueueLocalAddrIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_LOCAL_ADDR);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueLocalAddrIter = 0u;
    eventQueueLocalAddrIter < elementNumToHandle;
    eventQueueLocalAddrIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, &handleIdx) == E_OK )
    {
      SoAd_SizeOfLocalAddrType  localAddrIdx = (SoAd_LocalAddrIdType)handleIdx;
      SoAd_IpAddrStateType      ipAddrState;

      /* #30 Enter critical section to prevent that local IP address is changed via any API call. */
      SOAD_BEGIN_CRITICAL_SECTION();

      /* #40 Check if local IP address is assigned. */
      if ( SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) != SOAD_IPADDR_STATE_ASSIGNED )
      {
        ipAddrState = SoAd_TcpIpBsd_HandleIpAddrStateUnassigned(localAddrIdx);
      }
      /* #41 Handle local IP address if it is assigned. */
      else
      {
        ipAddrState = SoAd_TcpIpBsd_HandleIpAddrStateAssigned(localAddrIdx);
      }

      /* #50 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      /* #60 Check if local address assignment has changed. */
      if ( ipAddrState != SOAD_IPADDR_STATE_ONHOLD )
      {
        /* #600 Notify about local IP address assignment state change. */
        SoAd_LocalIpAddrAssignmentChg(SoAd_GetAddrIdOfLocalAddr(localAddrIdx), ipAddrState);
      }
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_TcpIpBsd_HandleIpAddrStates() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleIpAddrStateUnassigned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_IpAddrStateType, SOAD_CODE) SoAd_TcpIpBsd_HandleIpAddrStateUnassigned(
  SoAd_SizeOfLocalAddrType LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_IpAddrStateType ipAddrState = SOAD_IPADDR_STATE_ONHOLD;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if local IP address is explicitly requested or assignment trigger is automatic. */
  if ( (SoAd_GetAssignTriggerOfLocalAddr(LocalAddrIdx) == SOAD_ASSIGN_TRIGGER_AUTOMATIC) ||
    (SoAd_GetIpAddrReqStateOfLocalAddrDyn(LocalAddrIdx) == SOAD_LOCAL_IP_ADDR_REQ_STATE_REQUEST) )
  {
    /* #100 Try to assign the local IP address. */
    if ( E_OK == SoAd_TcpIpBsd_AssignIpAddr(LocalAddrIdx) )
    {
      /* #1000 Mark IP address as assigned and reset request state if local IP address could be assigned. */
      ipAddrState = SOAD_IPADDR_STATE_ASSIGNED;
      SoAd_SetIpAddrReqStateOfLocalAddrDyn(LocalAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_NONE);
    }

    /* #101 Add element to queue again to check for availability later. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, LocalAddrIdx);
  }

  return ipAddrState;
} /* SoAd_TcpIpBsd_HandleIpAddrStateUnassigned() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleIpAddrStateAssigned()
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
 */
SOAD_LOCAL_INLINE FUNC(SoAd_IpAddrStateType, SOAD_CODE) SoAd_TcpIpBsd_HandleIpAddrStateAssigned(
  SoAd_SizeOfLocalAddrType LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_IpAddrStateType ipAddrState = SOAD_IPADDR_STATE_ONHOLD;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if local IP address shall be released. */
  if ( SoAd_GetIpAddrReqStateOfLocalAddrDyn(LocalAddrIdx) == SOAD_LOCAL_IP_ADDR_REQ_STATE_RELEASE )
  {
    /* #100 Release local IP address and close corresponding sockets. */
    SoAd_TcpIpBsd_ReleaseIpAddr(LocalAddrIdx);

    /* #101 Mark IP address as unassigned and reset request state. */
    ipAddrState = SOAD_IPADDR_STATE_UNASSIGNED;
    SoAd_SetIpAddrReqStateOfLocalAddrDyn(LocalAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_NONE);

    /* #102 Add element to queue again if local IP address is triggered automatically to reassign it later. */
    if ( SoAd_GetAssignTriggerOfLocalAddr(LocalAddrIdx) == SOAD_ASSIGN_TRIGGER_AUTOMATIC )
    {
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, LocalAddrIdx);
    }

    /* #103 Reset check availability flag. */
    SoAd_SetCheckAvailabilityOfLocalAddrDyn(LocalAddrIdx, FALSE);
  }
  /* #11 Check if local IP address shall be checked for availability otherwise. */
  else if ( SoAd_IsCheckAvailabilityOfLocalAddrDyn(LocalAddrIdx) )
  {
    /* #110 Check if local IP address is not available anymore. */
    if ( SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr(LocalAddrIdx, FALSE) == E_NOT_OK )
    {
      /* #1100 Release local IP address and close corresponding sockets. */
      SoAd_TcpIpBsd_ReleaseIpAddr(LocalAddrIdx);

      /* #1101 Mark IP address as unassigned and reset request state. */
      ipAddrState = SOAD_IPADDR_STATE_UNASSIGNED;
      SoAd_SetIpAddrReqStateOfLocalAddrDyn(LocalAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_REQUEST);
    }

    /* #111 Add element to queue again. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, LocalAddrIdx);

    /* #112 Reset check availability flag. */
    SoAd_SetCheckAvailabilityOfLocalAddrDyn(LocalAddrIdx, FALSE);
  }
  /* #12 Add element to queue again to check for availability later otherwise. */
  else
  {
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, LocalAddrIdx);
  }

  return ipAddrState;
} /* SoAd_TcpIpBsd_HandleIpAddrStateAssigned() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_AssignIpAddr()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_AssignIpAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to assign local IP address. */
  /* #100 Check if local IP address is unicast. */
  if ( SoAd_GetAddressTypeOfLocalAddr(LocalAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST )
  {
    /* #1000 Handle static IP addresses. */
    if ( SoAd_GetAssignTypeOfLocalAddr(LocalAddrIdx) == SOAD_IPADDR_ASSIGNMENT_STATIC )
    {
      /* #10000 Check if local address is available. */
      retVal = SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr(LocalAddrIdx, FALSE);
    }
    /* #1001 Handle other IP addresses. */
    else
    {
      /* #10010 Overwrite local address with first matching local address on the configured interface. */
      retVal = SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr(LocalAddrIdx, TRUE);
    }
  }
  /* #101 Assume that multicast local IP address is always assigned. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TcpIpBsd_AssignIpAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ReleaseIpAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ReleaseIpAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIterType sockIter;
  SoAd_SocketIdType   socketId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all sockets. */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(); sockIter++ )
  {
    /* #100 Check if socket is configured for the local address. */
    if ( SoAd_GetLocalAddrIdxOfSoConGrp(
      SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIter))) == LocalAddrIdx )
    {
      socketId = SoAd_GetSocketIdOfSocketDyn(sockIter);

      /* #1000 Close socket if assigned. */
      if ( socketId != SOAD_INV_SOCKET_ID )
      {
        SoAd_TcpIp_Close(socketId, TRUE, (SoAd_SizeOfSocketType)sockIter);
      }
    }
  }

  /* #20 Reset local IP address struct. */
  SoAd_TcpIpBsd_ResetLocalIpAddr(LocalAddrIdx);
} /* SoAd_TcpIpBsd_ReleaseIpAddr() */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleTcpSocketStates()
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
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleTcpSocketStates(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueSocketIdxIterType  eventQueueSockIdxIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_SOCK_IDX);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueSockIdxIter = 0u;
    eventQueueSockIdxIter < elementNumToHandle;
    eventQueueSockIdxIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_SOCK_IDX, &handleIdx) == E_OK )
    {
      SoAd_SizeOfSocketType sockIdx = (SoAd_SizeOfSocketType)handleIdx;
      SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(sockIdx);
      SoAd_SizeOfSoConType  soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
      boolean               addEventAgain = FALSE;

      /* #30 Check if socket is a TCP socket. */
      if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx) )
      {
        /* #40 Check if socket is a TCP client socket. */
        if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx)) )
        {
          /* #50 Check if socket is connecting to a remote entity. */
          if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_CONNECT )
          {
            /* #60 Check if connection is established. */
            if ( SoAd_TcpIpBsd_TcpCheckConnect(sockIdx) == TRUE )
            {
              /* #70 Mark to add element to queue again if connection is not yet established or to start reception. */
              addEventAgain = TRUE;
            }
          }
          /* #51 Mark to add element to queue again if socket is not connecting to remote entity. */
          else
          {
            addEventAgain = TRUE;
          }
        }
        /* #41 Handle TCP server sockets. */
        else
        {
          /* #80 Check if socket is a listen socket. */
          if ( sockIdx == SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx) )
          {
            /* #90 Check if socket is in listen state. */
            if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_LISTEN )
            {
              /* #91 Check if any new connection has been established. */
              if ( SoAd_TcpIpBsd_TcpCheckAccept(sockIdx) == TRUE )
              {
                /* #100 Mark to add element to queue again if no socket error occurred. */
                addEventAgain = TRUE;
              }
            }
          }
          /* #71 Mark to add element to queue again in case TCP socket is a "data" socket. */
          else
          {
            addEventAgain = TRUE;
          }
        }
      }
      /* #31 Mark to add element to queue again in case of UDP socket. */
      else
      {
        addEventAgain = TRUE;
      }

      /* #110 Add element to queue again if required. */
      if ( addEventAgain == TRUE )
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SOCK_IDX, sockIdx);
      }
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_TcpIpBsd_HandleTcpSocketStates() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_TcpCheckConnect()
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
 *
 */
SOAD_LOCAL FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_TcpCheckConnect(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIdType   socketId = SoAd_GetSocketIdOfSocketDyn(SockIdx);
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_SocketIdType   osSocketId =
    SoAd_GetSocketIdOfIntegritySocketDyn(SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SockIdx));
#  else
  SoAd_SocketIdType   osSocketId = socketId;
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
  fd_set              socketFd;
  struct timeval      timeout;
  int                 errorSelect; /* PRQA S 5209 */ /* MD_SoAd_BasicType */
  int                 errorGetSockOpt = SOAD_E_BSD_NOT_OK; /* PRQA S 5209 */ /* MD_SoAd_BasicType */
  socklen_t           errorGetSockOptLength = sizeof(errorGetSockOpt);
  boolean             retry = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare BSD Socket API select call. */
  FD_ZERO(&socketFd);
  FD_SET(osSocketId, &socketFd);
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  if ( osSocketId >= FD_SETSIZE )
  {
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_TCP_CHECK_CONNECT, SOAD_SOCK_BSD_API_SELECT,
      SOAD_SOCK_BSD_PARAM_FD_SET, SoAd_GetSoConIdOfSoCon(SoAd_GetSoConStartIdxOfSocket(SockIdx)), osSocketId, EINVAL);

    SoAd_TcpIp_Close(socketId, TRUE, SockIdx);
  }
  else
  {
    /* #20 Call BSD Socket API select to check if the connection state changed. */
    errorSelect = select(osSocketId + 1, 0, &socketFd, 0, &timeout);

    /* #30 Check if an error occurred. */
    if ( errorSelect == SOAD_E_BSD_NOT_OK )
    {
      /* #300 Report Socket API error. */
      SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_TCP_CHECK_CONNECT, SOAD_SOCK_BSD_API_SELECT,
        SOAD_SOCK_BSD_PARAM_NONE, SoAd_GetSoConIdOfSoCon(SoAd_GetSoConStartIdxOfSocket(SockIdx)), osSocketId, errno);

      /* #301 Mark to retry to start reception in main function. */
      retry = TRUE;

      /* #302 Close socket. */
      SoAd_TcpIp_Close(socketId, TRUE, SockIdx);
    }
    /* #31 Check if connection state has not been changed otherwise. */
    else if ( errorSelect == SOAD_BSD_FD_NO_CHANGE )
    {
      /* #310 Mark to retry. */
      retry = TRUE;
    }
    /* #32 Try to check the state via BSD Socket API getsockopt otherwise. */
    else if ( getsockopt(osSocketId, SOL_SOCKET, SO_ERROR, &errorGetSockOpt, &errorGetSockOptLength) !=
      SOAD_E_BSD_NOT_OK )
    {
      /* #320 Check if TCP connection is established. */
      if ( errorGetSockOpt == SOAD_BSD_TCP_CONNECTED )
      {
        /* #3200 Notify that TCP connection is established. */
        SoAd_TcpConnected(socketId);

        /* #3201 Mark to retry to start reception in main function. */
        retry = TRUE;
      }
      /* #321 Report BSD Socket API error and close socket otherwise. */
      else
      {
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_TCP_CHECK_CONNECT, SOAD_SOCK_BSD_API_CONNECT,
          SOAD_SOCK_BSD_PARAM_NONE, SoAd_GetSoConIdOfSoCon(SoAd_GetSoConStartIdxOfSocket(SockIdx)), osSocketId,
          errorGetSockOpt);

        SoAd_TcpIp_Close(socketId, TRUE, SockIdx);
      }
    }
    /* #33 Report BSD Socket API error and close socket otherwise. */
    else
    {
      SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_TCP_CHECK_CONNECT, SOAD_SOCK_BSD_API_GET_SOCK_OPT,
        SOAD_SOCK_BSD_PARAM_SO_ERROR, SoAd_GetSoConIdOfSoCon(SoAd_GetSoConStartIdxOfSocket(SockIdx)), osSocketId,
        errno);

      SoAd_TcpIp_Close(socketId, TRUE, SockIdx);
    }
  }

  return retry;
} /* SoAd_TcpIpBsd_TcpCheckConnect() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_TcpCheckAccept()
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
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_TcpIpBsd_TcpCheckAccept(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  struct sockaddr_in6   sockAddr;
#  else
  struct sockaddr_in  sockAddr;
#  endif /* SOAD_IPV6 == STD_ON */
  socklen_t             sockAddrLen = sizeof(sockAddr);
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SocketIdType     socketId = SoAd_GetSocketIdOfSocketDyn(SockIdx);
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_SocketIdType     osSocketId =
    SoAd_GetSocketIdOfIntegritySocketDyn(SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SockIdx));
#  else
  SoAd_SocketIdType     osSocketId = socketId;
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
  SoAd_SocketIdType     socketIdConnected;
  boolean               retry = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set remote address for BSD-like Socket API. */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_GetDomainOfLocalAddr(
      SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx))) == SOAD_AF_INET6 )
  {
    (SOAD_A_P2VAR(struct sockaddr_in6)&sockAddr)->sin6_family = AF_INET6;
  }
  else
#  endif /* SOAD_IPV6 == STD_ON */
  {
    (SOAD_A_P2VAR(struct sockaddr_in)&sockAddr)->sin_family = AF_INET;
  }

  /* #20 Call BSD-like Socket API. */
  socketIdConnected = accept(osSocketId, SOAD_A_P2VAR(struct sockaddr)&sockAddr, &sockAddrLen);

  /* #30 Handle result if function call was successful. */
  if ( socketIdConnected != SOAD_INV_SOCKET_ID )
  {
    Std_ReturnType          retVal = E_NOT_OK;
    SoAd_SockAddrInetXType  remSockAddr;

    /* #300 Convert remote address for AUTOSAR Socket API. */
    remSockAddr.domain = SoAd_GetRemAddrDynOfSoConDyn(soConIdx).domain;
    SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)&remSockAddr,
        SOAD_A_P2CONST(struct sockaddr)&sockAddr);

#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
    /* #301 Get and map an INTEGRITY socket. */
    if ( SoAd_TcpIpBsd_IntegrityTcpAcceptGetAndMapSocket(soConIdx, SOAD_A_P2VAR(SoAd_SockAddrType)&remSockAddr,
        &socketIdConnected) == E_OK )
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
    {
      /* #302 Change parameters on newly connected socket. */
      if ( SoAd_SoCon_TcpChangeParameter(soConIdx, socketIdConnected) == E_OK )
      {
        /* #303 Notify about newly connected socket if parameters could be changed. */
        if ( SoAd_TcpAccepted(socketId, socketIdConnected, SOAD_A_P2VAR(SoAd_SockAddrType)&remSockAddr) == E_OK )
        {
          SoAd_SoConIterType soConIter;

          /* #304 Set event to handle socket reception in main function. */
          for ( soConIter = SoAd_GetSoConStartIdxOfSocket(SockIdx);
              soConIter < SoAd_GetSoConEndIdxOfSocket(SockIdx);
              soConIter++ )
          {
            if ( SoAd_GetSocketIdOfSocketDyn(SoAd_GetSocketIdxOfSoCon(soConIter)) == socketIdConnected )
            {
              SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SOCK_IDX, SoAd_GetSocketIdxOfSoCon(soConIter));
              break;
            }
          }

          retVal = E_OK;
        }
      }

      /* #305 Close socket if parameters could not be changed or newly connected socket is not accepted. */
      if ( retVal == E_NOT_OK )
      {
        SoAd_TcpIp_Close(socketIdConnected, TRUE, SockIdx);
      }
    }
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
    else
    {
      (void) close(socketIdConnected);
    }
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

    /* #306 Mark to retry since listen socket is still active. */
    retry = TRUE;
  }
  /* #31 Handle result if function call was not successful. */
  else
  {
    /* #310 Mark to retry if no new socket is available since listen socket is still active. */
    if ( (errno == EAGAIN) || (errno == EWOULDBLOCK) )
    {
      retry = TRUE;
    }
    /* #311 Report BSD-like Socket API error and close listen socket if any unexpected error occurred. */
    else
    {
      SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_BSD_TCP_CHECK_ACCEPT, SOAD_SOCK_BSD_API_ACCEPT,
        SOAD_SOCK_BSD_PARAM_NONE, SoAd_GetSoConIdOfSoCon(soConIdx), osSocketId, errno);

      SoAd_TcpIp_Close(socketId, TRUE, SockIdx);
    }
  }

  return retry;
} /* SoAd_TcpIpBsd_TcpCheckAccept() */
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ResetLocalIpAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ResetLocalIpAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_IpAddrInetXType      localIpAddr;
  SoAd_SizeOfTcpIpCtrlType  tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(LocalAddrIdx);

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* #10 Reset local IP address struct to configured static IPv6 address (if enabled). */
  if ( SoAd_IsAddrIpV6UsedOfLocalAddr(LocalAddrIdx) )
  {
    SoAd_IpAddrInet6Type localIpAddrV6 = SoAd_GetAddrIpV6(SoAd_GetAddrIpV6IdxOfLocalAddr(LocalAddrIdx));

    localIpAddr.addr32[0u] = localIpAddrV6.addr32[0u];
    localIpAddr.addr32[1u] = localIpAddrV6.addr32[1u];
    localIpAddr.addr32[2u] = localIpAddrV6.addr32[2u];
    localIpAddr.addr32[3u] = localIpAddrV6.addr32[3u];

    SoAd_SetNetmaskOfLocalAddrDyn(LocalAddrIdx, SoAd_GetNetmaskOfLocalAddr(LocalAddrIdx));
    SoAd_SetAddrOfLocalAddrDyn(LocalAddrIdx, localIpAddr);
  }
  else
# endif /* SOAD_IPV6 == STD_ON */
  /* #11 Reset local IP address struct to configured static IPv4 address otherwise (if enabled). */
  if ( SoAd_IsAddrIpV4UsedOfLocalAddr(LocalAddrIdx) )
  {
    SoAd_IpAddrInetType localIpAddrV4 = SoAd_GetAddrIpV4(SoAd_GetAddrIpV4IdxOfLocalAddr(LocalAddrIdx));

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    localIpAddr.addr32[0u] = localIpAddrV4;
    localIpAddr.addr32[1u] = SOAD_IPADDR_ANY;
    localIpAddr.addr32[2u] = SOAD_IPADDR_ANY;
    localIpAddr.addr32[3u] = SOAD_IPADDR_ANY;
# else
    localIpAddr = localIpAddrV4;
# endif /* SOAD_IPV6 == STD_ON */

    SoAd_SetNetmaskOfLocalAddrDyn(LocalAddrIdx, SoAd_GetNetmaskOfLocalAddr(LocalAddrIdx));
    SoAd_SetAddrOfLocalAddrDyn(LocalAddrIdx, localIpAddr);
  }
  /* #12 Reset local IP address struct to wildcard if no static IP address is configured otherwise. */
  else
  {
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    localIpAddr.addr32[0u] = SOAD_IPADDR_ANY;
    localIpAddr.addr32[1u] = SOAD_IPADDR_ANY;
    localIpAddr.addr32[2u] = SOAD_IPADDR_ANY;
    localIpAddr.addr32[3u] = SOAD_IPADDR_ANY;
# else
    localIpAddr = SOAD_IPADDR_ANY;
# endif /* SOAD_IPV6 == STD_ON */

    SoAd_SetNetmaskOfLocalAddrDyn(LocalAddrIdx, 0u);
    SoAd_SetAddrOfLocalAddrDyn(LocalAddrIdx, localIpAddr);
  }

  /* #20 Reset controller/interface index. */
  SoAd_SetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx,
    (uint8)if_nametoindex(SoAd_GetAddrCtrlName(SoAd_GetCtrlNameStartIdxOfTcpIpCtrl(tcpIpCtrlIdx))));
} /* SoAd_TcpIpBsd_ResetLocalIpAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr()
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
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr(
  SoAd_SizeOfLocalAddrType LocalAddrIdx,
  boolean OverwriteLocal)
{
  /* ----- Local Variables ---------------------------------------------- */
  P2VAR(struct ifaddrs, AUTOMATIC, SOAD_APPL_VAR) addrPtr;
  SoAd_SizeOfTcpIpCtrlType                        tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(LocalAddrIdx);
  Std_ReturnType                                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get all local addresses via BSD-like Socket API. */
  if ( getifaddrs(&addrPtr) == SOAD_BSD_NO_ERROR )
  {
    struct ifaddrs *  addrPtrIdx;
    uint8             family;

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( SoAd_GetDomainOfLocalAddr(LocalAddrIdx) == SOAD_AF_INET6 )
    {
      family = AF_INET6;
    }
    else
# endif /* SOAD_IPV6 == STD_ON */
    {
      family = AF_INET;
    }

    /* #20 Iterate over all local addresses. */
    for ( addrPtrIdx = addrPtr; addrPtrIdx != NULL; addrPtrIdx = addrPtrIdx->ifa_next )
    {
      /* #30 Check if local address interface and address family matches the configured local IP address. */
      uint32 ifIndex = if_nametoindex(addrPtrIdx->ifa_name);
      if ( ifIndex == SoAd_GetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx) )
      {
        if ( addrPtrIdx->ifa_addr != NULL )
        {
          if ( family == addrPtrIdx->ifa_addr->sa_family )
          {
            /* #40 Overwrite local IP address with first suitable local address on interface if required. */
            if ( TRUE == OverwriteLocal )
            {
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
              /* #400 Overwrite local IPv6 address (if enabled). */
              if ( SoAd_GetDomainOfLocalAddr(LocalAddrIdx) == SOAD_AF_INET6 )
              {
                SoAd_IpAddrInetXType  localIpAddr = SoAd_GetAddrOfLocalAddrDyn(LocalAddrIdx);
                uint8_least           idxByte;

                /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
                VStdMemCpy(
                  SOAD_A_P2VAR(void)localIpAddr.addr,
                  SOAD_A_P2CONST(void)((struct sockaddr_in6*)addrPtrIdx->ifa_addr)->sin6_addr.s6_addr,
                  SOAD_IPV6_ADDR_LEN_BYTE);
                SoAd_SetAddrOfLocalAddrDyn(LocalAddrIdx, localIpAddr);

                SoAd_SetNetmaskOfLocalAddrDyn(LocalAddrIdx, 0u);
                for ( idxByte = 0u; idxByte < SOAD_IPV6_ADDR_LEN_BYTE; idxByte++ )
                {
                  uint8 addrByte = ((struct sockaddr_in6*)addrPtrIdx->ifa_netmask)->sin6_addr.s6_addr[idxByte];

                  if ( addrByte != 0xFFu )
                  {
                    uint8_least idxBit;

                    for ( idxBit = 0u; idxBit < 8u; idxBit++ )
                    {
                      if ( ((uint8)(addrByte << idxBit)) == 0u )
                      {
                        SoAd_SetNetmaskOfLocalAddrDyn(LocalAddrIdx, (uint8)((idxByte * 8u) + idxBit));
                        break;
                      }
                    }
                    break;
                  }
                }

                retVal = E_OK;
                break;
              }
              else
# endif /* SOAD_IPV6 == STD_ON */
              /* #401 Overwrite local IPv4 address otherwise. */
              {
                SoAd_IpAddrInetXType  localIpAddr;
                uint8_least           idxBit;
                uint32                netmaskAddr;

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
                /* #4010 For INTEGRITY if Netmask is not available in address request... */
                if ( addrPtrIdx->ifa_netmask == NULL )
                {
                  struct ifreq ifReq;
                  int socketIdHelp; /* PRQA S 5209 */ /* MD_SoAd_BasicType */

                  /* #4011 ... get a helper socket for requesting the Netmask. */
                  socketIdHelp = socket(AF_INET, SOCK_DGRAM, 0);

                  /* #4012 Request an IPv4 Netmask from the current network interface with INTEGRITY Os API 'ioctl'. */
                  ifReq.ifr_addr.sa_family = AF_INET;
                  strncpy(ifReq.ifr_name, addrPtrIdx->ifa_name, IFNAMSIZ - 1);

                  if ( ioctl(socketIdHelp, SIOCGIFNETMASK, &ifReq) == SOAD_BSD_NO_ERROR )
                  {
                    /* #40120 Successfully retrieved the Netmask. Store it. */
                    netmaskAddr = IPBASE_SWAP32(((struct sockaddr_in*)&ifReq.ifr_addr)->sin_addr.s_addr);
                  }
                  else
                  {
                    /* #40121 Report socket error in case of 'ioctl' call failed. */
                    SOAD_REPORT_SOCK_ERROR(SOAD_SOCK_SID_TCPIP_CHECK_AND_OVERWRITE_LOC_ADDR, SOAD_SOCK_BSD_API_IOCTL,
                      errno);
                    continue;
                  }

                  /* Close the helper socket. */
                  close(socketIdHelp);
                }
                else
# endif /* (SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY) */
                {
                  netmaskAddr = IPBASE_SWAP32(((struct sockaddr_in*)addrPtrIdx->ifa_netmask)->sin_addr.s_addr);
                }

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
                localIpAddr.addr32[0u] = (uint32)((struct sockaddr_in*)addrPtrIdx->ifa_addr)->sin_addr.s_addr;
                localIpAddr.addr32[1u] = SOAD_IPADDR_ANY;
                localIpAddr.addr32[2u] = SOAD_IPADDR_ANY;
                localIpAddr.addr32[3u] = SOAD_IPADDR_ANY;
# else
                localIpAddr = (uint32)((struct sockaddr_in*)addrPtrIdx->ifa_addr)->sin_addr.s_addr;
# endif /* SOAD_IPV6 == STD_ON */

                SoAd_SetAddrOfLocalAddrDyn(LocalAddrIdx, localIpAddr);

                SoAd_SetNetmaskOfLocalAddrDyn(LocalAddrIdx, 0u);
                for ( idxBit = 0u; idxBit < 32u; idxBit++ )
                {
                  if ( ((uint32)(netmaskAddr << idxBit)) == 0u )
                  {
                    SoAd_SetNetmaskOfLocalAddrDyn(LocalAddrIdx, (uint8)idxBit);
                    break;
                  }
                }

                retVal = E_OK;
                break;
              }
            }
            /* #41 Check if local address matches the configured local IP address otherwise. */
            else
            {
              SoAd_IpAddrInetXType localIpAddr = SoAd_GetAddrOfLocalAddrDyn(LocalAddrIdx);

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
              /* #410 Check local IPv6 address (if enabled). */
              if ( SoAd_GetDomainOfLocalAddr(LocalAddrIdx) == SOAD_AF_INET6 )
              {
                uint32 *bsdAddrPtr = (uint32*)&((struct sockaddr_in6*)addrPtrIdx->ifa_addr)->sin6_addr.s6_addr;

#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
                /* #4100 Consider that ScopeId may be set internally in case of QNX (if enabled). */
                if ( SoAd_TcpIpBsd_QnxCheckScopeIdInSockAddrV6(localIpAddr.addr) == FALSE )
                {
                  SoAd_TcpIpBsd_QnxSetScopeIdInSockAddrV6(IPBASE_SWAP16(SoAd_GetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx)),
                    localIpAddr.addr);
                }
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */

                if ( (localIpAddr.addr32[0u] == bsdAddrPtr[0u]) && (localIpAddr.addr32[1u] == bsdAddrPtr[1u]) &&
                    (localIpAddr.addr32[2u] == bsdAddrPtr[2u]) && (localIpAddr.addr32[3u] == bsdAddrPtr[3u]) )
                {
                  retVal = E_OK;
                  break;
                }
              }
              else
# endif /* SOAD_IPV6 == STD_ON */
              /* #411 Check local IPv4 address otherwise. */
              {
                uint32 bsdAddr = *((uint32*)&((struct sockaddr_in*)addrPtrIdx->ifa_addr)->sin_addr.s_addr);

# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
                if ( localIpAddr.addr32[0u] == bsdAddr )
# else
                if ( localIpAddr == bsdAddr )
# endif /* SOAD_IPV6 == STD_ON */
                {
                  retVal = E_OK;
                  break;
                }
              }
            }
          }
        }
      }
    }
    /* #50 Free occupied buffer of BSD-like Socket API used to get all local addresses. */
    freeifaddrs(addrPtr);
  }
  return retVal;
} /* SoAd_TcpIpBsd_CheckAndOverwriteLocalAddr() */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_HandleTcpTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_HandleTcpTxConfirmation(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 totLen = SoAd_Tx_TcpGetUnconfirmedDataLength(SockIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Tx TCP queue has elements left. */
  if ( totLen > 0u )
  {
    /* #20 Confirm all data in Tx TCP queue. */
    SoAd_Tx_TxConfirmation(SockIdx, (uint16)totLen);
  }
} /* SoAd_TcpIpBsd_HandleTcpTxConfirmation() */
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ConvertAsrSockAddr2BsdSockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ConvertAsrSockAddr2BsdSockAddr(
  P2VAR(struct sockaddr, SOAD_APPL_DATA, SOAD_APPL_DATA) BsdSockAddrPtr,
  P2CONST(SoAd_SockAddrType, SOAD_APPL_DATA, SOAD_APPL_DATA) AsrSockAddrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* #10 Convert IPv6 address. */
  if ( AsrSockAddrPtr->domain == SOAD_AF_INET6 )
  {
    ((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_family = AF_INET6;
    ((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_port = ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->port;
    ((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_flowinfo = 0u;

    *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[0]) =
      ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[0];
    *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[4]) =
      ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[1];
    *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[8]) =
      ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[2];
    *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[12]) =
      ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[3];
  }
  else
# endif /* SOAD_IPV6 == STD_ON */
  /* #20 Convert IPv4 address. */
  {
    ((struct sockaddr_in*)BsdSockAddrPtr)->sin_family = AF_INET;
    ((struct sockaddr_in*)BsdSockAddrPtr)->sin_port = ((SoAd_SockAddrInetType*)AsrSockAddrPtr)->port;
    ((struct sockaddr_in*)BsdSockAddrPtr)->sin_addr.s_addr = *((SoAd_SockAddrInetType*)AsrSockAddrPtr)->addr;
  }
} /* SoAd_TcpIpBsd_ConvertAsrSockAddr2BsdSockAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr(
  P2VAR(SoAd_SockAddrType, SOAD_APPL_DATA, SOAD_APPL_DATA) AsrSockAddrPtr,
  P2CONST(struct sockaddr, SOAD_APPL_DATA, SOAD_APPL_DATA) BsdSockAddrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert IPv6 address. */
  if ( BsdSockAddrPtr->sa_family == AF_INET6 )
  {
    ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->domain = SOAD_AF_INET6;
    ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->port = ((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_port;
    ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[0] =
      *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[0]);
    ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[1] =
      *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[4]);
    ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[2] =
      *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[8]);
    ((SoAd_SockAddrInet6Type*)AsrSockAddrPtr)->addr[3] =
      *((uint32*)&((struct sockaddr_in6*)BsdSockAddrPtr)->sin6_addr.s6_addr[12]);
  }
  /* #20 Convert IPv4 address. */
  else
  {
    ((SoAd_SockAddrInetType*)AsrSockAddrPtr)->domain = SOAD_AF_INET;
    ((SoAd_SockAddrInetType*)AsrSockAddrPtr)->port = ((struct sockaddr_in*)BsdSockAddrPtr)->sin_port;
    ((SoAd_SockAddrInetType*)AsrSockAddrPtr)->addr[0] = ((struct sockaddr_in*)BsdSockAddrPtr)->sin_addr.s_addr;
  }
} /* SoAd_TcpIpBsd_ConvertBsdSockAddr2AsrSockAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIterType               sockIter;
  SoAd_SocketTxBufferQueueIterType  socketTxBufferQueueIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset all queue elements and move them to the linked list for unused queue elements. */
  for ( socketTxBufferQueueIter = 0u; socketTxBufferQueueIter < SoAd_GetSizeOfSocketTxBufferQueue();
    socketTxBufferQueueIter++ )
  {
    SoAd_SetSocketIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIter, SoAd_GetSizeOfSocket());
    SoAd_SetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIter, 0u);
    SoAd_SetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIter, 0u);
    SoAd_SetReadyOfSocketTxBufferQueueDyn(socketTxBufferQueueIter, FALSE);

    SoAd_SetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIter,
      (SoAd_SizeOfSocketTxBufferQueueType)(socketTxBufferQueueIter + 1u));

    if (socketTxBufferQueueIter > 0u)
    {
      SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIter,
        (SoAd_SizeOfSocketTxBufferQueueType)(socketTxBufferQueueIter - 1u));
    }
    else
    {
      SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIter,
        SoAd_GetSizeOfSocketTxBufferQueue());
    }
  }
  SoAd_SetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u, 0u);
  SoAd_SetSocketTxBufferQueueLastUnusedIdxOfSocketTxBufferMgt(0u, SoAd_GetSizeOfSocketTxBufferQueue() - 1u);

  /* #20 Reset the socket transmission buffer queue information on all sockets. */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(); sockIter++ )
  {
    SoAd_SetSocketTxBufferQueueFirstIdxOfSocketDyn(sockIter, SoAd_GetSizeOfSocketTxBufferQueue());
    SoAd_SetSocketTxBufferQueueLastIdxOfSocketDyn(sockIter, SoAd_GetSizeOfSocketTxBufferQueue());
    SoAd_SetSocketTxBufferQueueNumOfSocketDyn(sockIter, 0u);
  }
} /* SoAd_TcpIpBsdSocketTxBuffer_Init() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Request()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Request(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length,
  P2VAR(uint8*, SOAD_APPL_DATA, SOAD_APPL_DATA) SocketTxBufferPtrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueIdx = SoAd_GetSizeOfSocketTxBufferQueue();
  Std_ReturnType                     retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket transmission buffer struct is changed via any API call. */
  SOAD_BEGIN_CRITICAL_SECTION();

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* #20 Check if requesting socket is TCP. */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(SockIdx))) )
  {
    SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueLastIdx =
      SoAd_GetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx);

    /* #200 Get the last used queue element if the remaining buffer size can store the newly requested data. */
    if ( socketTxBufferQueueLastIdx != SoAd_GetSizeOfSocketTxBufferQueue() )
    {
      if ( ((SoAd_GetSocketTxBufferEndIdxOfSocketTxBufferQueue(socketTxBufferQueueLastIdx) -
        SoAd_GetSocketTxBufferStartIdxOfSocketTxBufferQueue(socketTxBufferQueueLastIdx)) -
          SoAd_GetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueLastIdx)) >= Length )
      {
        socketTxBufferQueueIdx = socketTxBufferQueueLastIdx;
      }
    }
  }
# endif /* SOAD_TCP == STD_ON */

  /* #30 Try to reserve a new queue element if last queue element cannot be used or has not been reserved yet. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( socketTxBufferQueueIdx == SoAd_GetSizeOfSocketTxBufferQueue() )
# endif /* SOAD_TCP == STD_ON */
  {
    SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueFirstUnusedIdx =
      SoAd_GetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u);

    /* #300 Check if socket did not request the maximum number of buffer and an unused queue element is available. */
    if ( (SoAd_GetSocketTxBufferQueueNumOfSocketDyn(SockIdx) < SoAd_GetSocketTxBufferMaxNumPerSocket()) &&
      socketTxBufferQueueFirstUnusedIdx != SoAd_GetSizeOfSocketTxBufferQueue() )
    {
      /* #3000 Get the next unused queue element if it can store the new request. */
      if ( (SoAd_GetSocketTxBufferEndIdxOfSocketTxBufferQueue(socketTxBufferQueueFirstUnusedIdx) -
        SoAd_GetSocketTxBufferStartIdxOfSocketTxBufferQueue(socketTxBufferQueueFirstUnusedIdx)) >= Length )
      {
        socketTxBufferQueueIdx = socketTxBufferQueueFirstUnusedIdx;
      }
    }
  }

  /* #40 Reserve or update the queue element if a queue element could be found. */
  if ( socketTxBufferQueueIdx != SoAd_GetSizeOfSocketTxBufferQueue() )
  {
    uint16 currentLength = SoAd_GetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx);

    /* #400 Set the transmission request information on the queue element. */
    SoAd_SetSocketIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, SockIdx);
    SoAd_SetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, currentLength + Length);
    SoAd_SetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, currentLength);
    SoAd_SetReadyOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, FALSE);

    /* #401 Check if a new queue element has been reserved. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( socketTxBufferQueueIdx == SoAd_GetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u) )
# endif /* SOAD_TCP == STD_ON */
    {
      /* #4010 Remove the queue element from the linked list of unused queue elements. */
      if ( SoAd_GetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u) ==
        SoAd_GetSocketTxBufferQueueLastUnusedIdxOfSocketTxBufferMgt(0u) )
      {
        SoAd_SetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u, SoAd_GetSizeOfSocketTxBufferQueue());
        SoAd_SetSocketTxBufferQueueLastUnusedIdxOfSocketTxBufferMgt(0u, SoAd_GetSizeOfSocketTxBufferQueue());
      }
      else
      {
        SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueNextIdx =
          SoAd_GetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx);

        SoAd_SetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u, socketTxBufferQueueNextIdx);

        SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueNextIdx,
          SoAd_GetSizeOfSocketTxBufferQueue());
      }

      /* #4011 Add the queue element to the linked list of the socket. */
      if ( SoAd_GetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx) == SoAd_GetSizeOfSocketTxBufferQueue() )
      {
        SoAd_SetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx, socketTxBufferQueueIdx);
      }
      else
      {
        SoAd_SetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(
          SoAd_GetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx), socketTxBufferQueueIdx);

        SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
          SoAd_GetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx));
      }

      SoAd_SetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
        SoAd_GetSizeOfSocketTxBufferQueue());

      SoAd_SetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx, socketTxBufferQueueIdx);

      SoAd_IncSocketTxBufferQueueNumOfSocketDyn(SockIdx);
    }

    /* #402 Set the pointer to the transmission socket buffer. */
    *SocketTxBufferPtrPtr = SoAd_GetAddrSocketTxBuffer(
      SoAd_GetSocketTxBufferStartIdxOfSocketTxBufferQueue(socketTxBufferQueueIdx) + currentLength);

    retVal = E_OK;
  }

  /* #50 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_TcpIpBsdSocketTxBuffer_Request() */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Set()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Set(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketTxBufferQueueType  socketTxBufferQueueIdx;
  Std_ReturnType                      retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket transmission buffer struct is changed via any API call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  socketTxBufferQueueIdx = SoAd_GetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx);

  /* #20 Check if a buffer has been requested previously. */
  if ( socketTxBufferQueueIdx != SoAd_GetSizeOfSocketTxBufferQueue() )
  {
    /* #200 Check if updated length is valid. */
    if ( ((SoAd_GetSocketTxBufferEndIdxOfSocketTxBufferQueue(socketTxBufferQueueIdx) -
      SoAd_GetSocketTxBufferStartIdxOfSocketTxBufferQueue(socketTxBufferQueueIdx)) -
        SoAd_GetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx)) >= Length )
    {
      /* #2000 Update the length of the previous buffer request. */
      SoAd_SetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
        SoAd_GetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx) + Length);

      /* #2001 Mark the buffer request as set. */
      SoAd_SetReadyOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, TRUE);

      retVal = E_OK;
    }
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_TcpIpBsdSocketTxBuffer_Set() */
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_ReleaseLast()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_ReleaseLast(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket transmission buffer struct is changed via any API call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  socketTxBufferQueueIdx = SoAd_GetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx);

  /* #20 Check if a queue element is reserved for the requested socket. */
  if ( socketTxBufferQueueIdx != SoAd_GetSizeOfSocketTxBufferQueue() )
  {
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    /* #30 Release queue element partly if buffer is used at least twice. */
    if ( (SoAd_GetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx) > 0u) &&
      (SoAd_GetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx) >
        SoAd_GetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx)) )
    {
      SoAd_SetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
        SoAd_GetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx));
    }
    /* #31 Release queue element completely otherwise. */
    else
# endif /* SOAD_TCP == STD_ON */
    {
      /* #310 Reset the transmission request information on the queue element. */
      SoAd_SetSocketIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, SoAd_GetSizeOfSocket());
      SoAd_SetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, 0u);
      SoAd_SetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, 0u);
      SoAd_SetReadyOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, FALSE);

      /* #311 Remove the queue element from the linked list of the socket. */
      if ( SoAd_GetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx) == socketTxBufferQueueIdx )
      {
        SoAd_SetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSocketTxBufferQueue());
        SoAd_SetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSocketTxBufferQueue());
      }
      else
      {
        SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueuePrevIdx =
          SoAd_GetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx);

        SoAd_SetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx, socketTxBufferQueuePrevIdx);

        SoAd_SetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueuePrevIdx,
          SoAd_GetSizeOfSocketTxBufferQueue());
      }

      SoAd_DecSocketTxBufferQueueNumOfSocketDyn(SockIdx);

      /* #312 Add the queue element to the linked list of unused queue elements. */
      if ( SoAd_GetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u) == SoAd_GetSizeOfSocketTxBufferQueue() )
      {
        SoAd_SetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u, socketTxBufferQueueIdx);

        SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
          SoAd_GetSizeOfSocketTxBufferQueue());
      }
      else
      {
        SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueLastIdx =
          SoAd_GetSocketTxBufferQueueLastUnusedIdxOfSocketTxBufferMgt(0u);

        SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
          socketTxBufferQueueLastIdx);

        SoAd_SetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueLastIdx,
          socketTxBufferQueueIdx);
      }

      SoAd_SetSocketTxBufferQueueLastUnusedIdxOfSocketTxBufferMgt(0u, socketTxBufferQueueIdx);
    }
  }

  /* #40 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_TcpIpBsdSocketTxBuffer_ReleaseLast() */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_ReleaseAll()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_ReleaseAll(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16_least queueIter;
  uint16_least queueLvl;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket transmission buffer struct is changed via any API call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  queueLvl = SoAd_GetSocketTxBufferQueueNumOfSocketDyn(SockIdx);

  /* #20 Iterate over all queue elements reserved for the socket. */
  for ( queueIter = 0u; queueIter < queueLvl; queueIter++ )
  {
    /* #200 Release first queue element. */
    SoAd_TcpIpBsdSocketTxBuffer_ReleaseFirst(SockIdx);
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_TcpIpBsdSocketTxBuffer_ReleaseAll() */

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_Transmit()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_Transmit(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16_least      queueIter;
  uint16_least      queueLvl;
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_SocketIdType socketId =
    SoAd_GetSocketIdOfIntegritySocketDyn(SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SockIdx));
#  else
  SoAd_SocketIdType socketId = SoAd_GetSocketIdOfSocketDyn(SockIdx);
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
  boolean           stopIteration = FALSE;
  Std_ReturnType    retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket transmission buffer struct is changed via any API call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  queueLvl = SoAd_GetSocketTxBufferQueueNumOfSocketDyn(SockIdx);

  /* #20 Iterate over all reserved buffer of the socket. */
  for ( queueIter = 0u; queueIter < queueLvl; queueIter++ )
  {
    SoAd_SizeOfSocketTxBufferQueueType  socketTxBufferQueueIdx =
      SoAd_GetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx);
    uint16                              len = SoAd_GetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx);

    /* #30 Check if buffer is still reserved. */
    if ( socketTxBufferQueueIdx != SoAd_GetSizeOfSocketTxBufferQueue() )
    {
      /* #40 Check if buffer is ready for transmission. */
      if ( SoAd_IsReadyOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx) )
      {
        /* #50 Leave critical section. */
        SOAD_END_CRITICAL_SECTION();

        /* #60 Call BSD-like Socket API for transmission and check if call succeeds. */
        if ( send(socketId, SOAD_A_P2CONST(void)SoAd_GetAddrSocketTxBuffer(
            SoAd_GetSocketTxBufferStartIdxOfSocketTxBufferQueue(socketTxBufferQueueIdx)), len, SOAD_ZERO_FLAGS) !=
          SOAD_E_BSD_NOT_OK )
        {
          /* #600 Enter critical section again to continue with other transmission buffers. */
          SOAD_BEGIN_CRITICAL_SECTION();

          /* #601 Release socket transmission buffer. */
          SoAd_TcpIpBsdSocketTxBuffer_ReleaseFirst(SockIdx);
        }
        /* #61 Stop iteration otherwise. */
        else
        {
          /* #610 Enter critical section again. */
          SOAD_BEGIN_CRITICAL_SECTION();

          retVal = E_NOT_OK;

          stopIteration = TRUE;
        }
      }
      /* #41 Stop iteration otherwise. */
      else
      {
        stopIteration = TRUE;
      }
    }
    /* #31 Stop iteration otherwise. */
    else
    {
      stopIteration = TRUE;
    }

    if ( stopIteration == TRUE )
    {
      break;
    }
  }

  /* #70 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_TcpIpBsdSocketTxBuffer_Transmit() */
# endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIpBsdSocketTxBuffer_ReleaseFirst()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TcpIpBsdSocketTxBuffer_ReleaseFirst(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueIdx = SoAd_GetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if queue element is still in use. */
  if ( socketTxBufferQueueIdx != SoAd_GetSizeOfSocketTxBufferQueue() )
  {
    /* #20 Reset the transmission request information on the queue element. */
    SoAd_SetSocketIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, SoAd_GetSizeOfSocket());
    SoAd_SetLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, 0u);
    SoAd_SetLastLenOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, 0u);
    SoAd_SetReadyOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx, FALSE);

    /* #30 Remove the queue element from the linked list of the socket. */
    if ( socketTxBufferQueueIdx == SoAd_GetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx) )
    {
      SoAd_SetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSocketTxBufferQueue());
      SoAd_SetSocketTxBufferQueueLastIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSocketTxBufferQueue());
    }
    else
    {
      SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueNextIdx =
        SoAd_GetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx);

      SoAd_SetSocketTxBufferQueueFirstIdxOfSocketDyn(SockIdx, socketTxBufferQueueNextIdx);

      SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueNextIdx,
        SoAd_GetSizeOfSocketTxBufferQueue());
    }

    SoAd_DecSocketTxBufferQueueNumOfSocketDyn(SockIdx);

    /* #40 Add the queue element to the linked list of unused queue elements. */
    if ( SoAd_GetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u) == SoAd_GetSizeOfSocketTxBufferQueue() )
    {
      SoAd_SetSocketTxBufferQueueFirstUnusedIdxOfSocketTxBufferMgt(0u, socketTxBufferQueueIdx);

      SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
        SoAd_GetSizeOfSocketTxBufferQueue());
    }
    else
    {
      SoAd_SizeOfSocketTxBufferQueueType socketTxBufferQueueLastIdx =
        SoAd_GetSocketTxBufferQueueLastUnusedIdxOfSocketTxBufferMgt(0u);

      SoAd_SetSocketTxBufferQueuePrevIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
        socketTxBufferQueueLastIdx);

      SoAd_SetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueLastIdx,
        socketTxBufferQueueIdx);
    }

    SoAd_SetSocketTxBufferQueueLastUnusedIdxOfSocketTxBufferMgt(0u, socketTxBufferQueueIdx);

    SoAd_SetSocketTxBufferQueueNextIdxOfSocketTxBufferQueueDyn(socketTxBufferQueueIdx,
      SoAd_GetSizeOfSocketTxBufferQueue());
  }
} /* SoAd_TcpIpBsdSocketTxBuffer_ReleaseFirst() */
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
/**********************************************************************************************************************
 *  SoAd_TcpIpAsr_RequestIpAddrAssignment()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIpAsr_RequestIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType    localIpAddr;
  SoAd_SockAddrInetXType    defaultRouter;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  uint8                     dummyNetmask;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Do not forward request to TcpIp module if same static IP address is requested. */
  if ( Type == SOAD_IPADDR_ASSIGNMENT_STATIC )
  {
    /* #100 Check if IP address is unassigned. */
    if ( SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) != SOAD_IPADDR_STATE_UNASSIGNED )
    {
      /* #1000 Retrieve local IP address. */
      /* PRQA S 310 4 */ /* MD_SoAd_PointerCastOnStruct */
      if ( TcpIp_GetIpAddr(SoAd_GetAddrIdOfLocalAddr(localAddrIdx),                                                    /* SBSW_SOAD_SOCK_ADDR_VARIABLE_POINTER_AND_VARIABLE_POINTER_FORWARD */
          SOAD_A_P2VAR(SoAd_SockAddrType)&localIpAddr,
          &dummyNetmask,
          SOAD_A_P2VAR(SoAd_SockAddrType)&defaultRouter) == E_OK )
      {
        /* #10000 Compare new IP address to local IP address. */
        /* PRQA S 310, 3305 3 */ /* MD_SoAd_PointerCastOnStruct */
        if ( SoAd_Util_CompareIpAddr(SoAd_GetDomainOfLocalAddr(localAddrIdx),                                          /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_AND_CONST_POINTER_FORWARD */
          localIpAddr.addr,
          (SOAD_A_P2VAR(SoAd_SockAddrInetXType)LocalIpAddrPtr)->addr,
          FALSE) == E_OK)
        {
          retVal = E_OK;
        }
      }
    }
  }

  /* #20 Forward request to TcpIp module otherwise. */
  if ( retVal == E_NOT_OK )
  {
    retVal = TcpIp_RequestIpAddrAssignment(SoAd_GetAddrIdOfLocalAddr(localAddrIdx), Type,                              /* SBSW_SOAD_POINTER_FORWARD */
      LocalIpAddrPtr, Netmask, DefaultRouterPtr);
  }

  return retVal;
} /* SoAd_TcpIpAsr_RequestIpAddrAssignment() */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_TcpIp_Init()
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
FUNC(void, SOAD_CODE) SoAd_TcpIp_Init(void)
{
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
  /* ----- Local Variables ---------------------------------------------- */
# if ( SOAD_TCP == STD_ON )
  SoAd_SocketIterType     sockIter;
# endif /* SOAD_TCP == STD_ON */
  SoAd_LocalAddrIterType  localAddrIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all local addresses. */
  for ( localAddrIter = 0u; localAddrIter < SoAd_GetSizeOfLocalAddr(); localAddrIter++ )
  {
    /* #100 Add element initially to local address event queue if assignment trigger is automatic. */
    if ( SoAd_GetAssignTriggerOfLocalAddr(localAddrIter) == SOAD_ASSIGN_TRIGGER_AUTOMATIC )
    {
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, (SoAd_SizeOfLocalAddrType)localAddrIter);
    }
    /* #101 Initialize local address structs. */
    SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIter, SOAD_LOCAL_IP_ADDR_REQ_STATE_NONE);
    SoAd_TcpIpBsd_ResetLocalIpAddr((SoAd_SizeOfLocalAddrType)localAddrIter);
  }

# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* #20 Initialize socket TCP reception buffers (if enabled). */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(); sockIter++ )
  {
    if ( SoAd_IsTcpRxMgtUsedOfSocket(sockIter) )
    {
      SoAd_SizeOfTcpRxMgtType tcpRxMgtIdx = SoAd_GetTcpRxMgtIdxOfSocket(sockIter);

      SoAd_SetLenOfTcpRxMgt(tcpRxMgtIdx, 0u);
      SoAd_SetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx, SoAd_GetTcpRxBufferStartIdxOfSocket(sockIter));
    }
  }
# endif /* SOAD_TCP == STD_ON */

  /* #30 Initialize socket transmission buffers (if enabled). */
  SoAd_TcpIpBsdSocketTxBuffer_Init();

  /* #40 Initialize local address check interval counter to handle local IP in next main function cycle. */
  SoAd_TcpIpBsd_LocalAddrCheckIntervalCounter = SoAd_GetLocalAddrCheckInterval();

# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  /* #50 Initialize INTEGRITY specific variables (if enabled). */
  SoAd_TcpIpBsd_IntegrityInit();
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_Init() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_RequestIpAddrAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_RequestIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  Std_ReturnType            retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Request IP address in case of AUTOSAR Socket API. */
  retVal = SoAd_TcpIpAsr_RequestIpAddrAssignment(                                                                      /* SBSW_SOAD_POINTER_FORWARD */
    SoConIdx,
    Type,
    LocalIpAddrPtr,
    Netmask,
    DefaultRouterPtr);
#else
  /* #20 Request IP address for BSD-like Socket API otherwise. */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);

  if ( Type == SoAd_GetAssignTypeOfLocalAddr(localAddrIdx) )
  {
    retVal = SoAd_TcpIpBsd_RequestIpAddrAssignment(
      SoConIdx,
      Type,
      LocalIpAddrPtr,
      Netmask,
      DefaultRouterPtr);
  }
  else
  {
    retVal = E_NOT_OK;
  }
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  /* #30 Update local port of local static IP address if request was successful. */
  if ( retVal == E_OK )
  {
    if ( Type == SOAD_IPADDR_ASSIGNMENT_STATIC )
    {
      if ( SoAd_SoCon_GetLocalPortDyn(sockIdx) == SOAD_PORT_ANY )
      {
        /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
        SoAd_SoCon_SetLocalPortDyn(sockIdx, ((SoAd_SockAddrInetXType*)LocalIpAddrPtr)->port);
      }
    }
  }

  return retVal;
} /* SoAd_TcpIp_RequestIpAddrAssignment() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_ReleaseIpAddrAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ReleaseIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));
  Std_ReturnType            retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module in case of AUTOSAR Socket API. */
  retVal = TcpIp_ReleaseIpAddrAssignment(SoAd_GetAddrIdOfLocalAddr(localAddrIdx));
#else
  /* #20 Handle request locally otherwise. */
  retVal = E_NOT_OK;

  if ( SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) == SOAD_IPADDR_STATE_ASSIGNED )
  {
    /* #200 Allow release on multicast addresses and mark local address to be released in main function. */
    if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_MULTICAST )
    {
      SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_RELEASE);

      retVal = E_OK;

      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_LOCAL_ADDR, localAddrIdx);
    }
  }
  else
  {
    /* #201 Allow reverting assignment request of a not yet assigned local addresss. */
    if ( SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) == SOAD_IPADDR_STATE_UNASSIGNED )
    { /* IP address is unassigned */
      /* reset previous request */
      SoAd_SetIpAddrReqStateOfLocalAddrDyn(localAddrIdx, SOAD_LOCAL_IP_ADDR_REQ_STATE_NONE);

      retVal = E_OK;
    }
  }
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_ReleaseIpAddrAssignment() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_GetIpAddr()
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
FUNC(void, SOAD_CODE) SoAd_TcpIp_GetIpAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) NetmaskPtr,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Handle request for AUTOSAR Socket API. */

  /* #100 Get local IP address from TcpIp module. */
  if ( TcpIp_GetIpAddr(SoAd_GetAddrIdOfLocalAddr(localAddrIdx),                                                        /* SBSW_SOAD_POINTER_FORWARD */
      LocalAddrPtr,
      NetmaskPtr,
      DefaultRouterPtr) == E_NOT_OK )
  {
    /* #1000 Use wildcard IP address if call to TcpIp module fail. */
    /* PRQA S 310, 3305 12 */ /* MD_SoAd_PointerCastOnStruct */
# if ( SOAD_IPV6 == STD_ON )
    if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
    {
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[0u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[1u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[2u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[3u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    }
    else
# endif /* SOAD_IPV6 == STD_ON */
    {
      ((SoAd_SockAddrInetType*)LocalAddrPtr)->addr[0u] = SOAD_IPADDR_ANY;                                              /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    }
  }

  /* #101 Get port from local data structure. */
  /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
  ((SoAd_SockAddrInetXType*)LocalAddrPtr)->port = SoAd_SoCon_GetLocalPortDyn(sockIdx);                                 /* SBSW_SOAD_POINTER_WRITE */
#else
  /* #20 Handle request for BSD-like Socket API otherwise. */
  SoAd_IpAddrInetXType localIpAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdx);

  SOAD_DUMMY_STATEMENT(DefaultRouterPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #200 Copy socket address from local data structure. */
  *NetmaskPtr = SoAd_GetNetmaskOfLocalAddrDyn(localAddrIdx);
  LocalAddrPtr->domain = SoAd_GetDomainOfLocalAddr(localAddrIdx);
  ((SoAd_SockAddrInetXType*)LocalAddrPtr)->port = SoAd_SoCon_GetLocalPortDyn(sockIdx);
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  ((SoAd_SockAddrInetXType*)LocalAddrPtr)->addr[0u] = localIpAddr.addr32[0u];
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
  {
    ((SoAd_SockAddrInetXType*)LocalAddrPtr)->addr[1u] = localIpAddr.addr32[1u];
    ((SoAd_SockAddrInetXType*)LocalAddrPtr)->addr[2u] = localIpAddr.addr32[2u];
    ((SoAd_SockAddrInetXType*)LocalAddrPtr)->addr[3u] = localIpAddr.addr32[3u];
  }
# else
  ((SoAd_SockAddrInetXType*)LocalAddrPtr)->addr[0u] = localIpAddr;
# endif /* SOAD_IPV6 == STD_ON */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_GetIpAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_CompareToIpAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_CompareToIpAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_IpAddrConstPtrType IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType               soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType              localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_LocalAddrByTcpIpCtrlIndIterType  tcpIpCtrlInd;
  SoAd_SizeOfTcpIpCtrlType              tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
  Std_ReturnType                        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all local addresses of the TcpIp controller. */
  for ( tcpIpCtrlInd = SoAd_GetLocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl(tcpIpCtrlIdx);
    tcpIpCtrlInd < SoAd_GetLocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrl(tcpIpCtrlIdx);
    tcpIpCtrlInd++ )
  {
    SoAd_SizeOfLocalAddrType  localAddrIdxTmp = SoAd_GetLocalAddrByTcpIpCtrlInd(tcpIpCtrlInd);
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
    /* #100 Handle request for AUTOSAR Socket API. */
    SoAd_SockAddrInetXType    localIpAddr;
    SoAd_SockAddrInetXType    defaultRouter;
    uint8                     netmask;

    /* #1000 Get local IP address from TcpIp. */
    /* PRQA S 310 5 */ /* MD_SoAd_PointerCastOnStruct */
    if ( E_OK == TcpIp_GetIpAddr(                                                                                      /* SBSW_SOAD_SOCK_ADDR_VARIABLE_POINTER_AND_VARIABLE_POINTER_FORWARD */
        SoAd_GetAddrIdOfLocalAddr(localAddrIdxTmp),
        (P2VAR(SoAd_SockAddrType, AUTOMATIC, AUTOMATIC))&localIpAddr,
        &netmask,
        (P2VAR(SoAd_SockAddrType, AUTOMATIC, AUTOMATIC))&defaultRouter) )
    {
      /* #10000 Compare IP address to local IP address. */
      if ( E_OK == SoAd_Util_CompareIpAddr(                                                                            /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
          SoAd_GetDomainOfLocalAddr(localAddrIdxTmp),
          localIpAddr.addr,
          IpAddrPtr,
          FALSE) )
      {
        /* #100000 Stop iteration if a local IP address matches. */
        retVal = E_OK;
        break;
      }
    }
    /* #1001 Ignore local IP address if call to TcpIp failed. */
    else
    {
      /* nothing to do */
    }
#else
    /* #200 Handle request for BSD-like Socket API. */
    SoAd_IpAddrInetXType localIpAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdxTmp);

    /* #2000 Compare IP address to local IP address. */
    if ( E_OK == SoAd_Util_CompareIpAddr(
        SoAd_GetDomainOfLocalAddr(localAddrIdxTmp),
        IpAddrPtr,
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        &localIpAddr.addr32[0u],
# else
        &localIpAddr,
# endif /* SOAD_IPV6 == STD_ON */
        FALSE) )
    {
      /* #20000 Stop iteration if a local IP address matches. */
      retVal = E_OK;
      break;
    }
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
  }

  return retVal;
} /* SoAd_TcpIp_CompareToIpAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_GetPhysAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_GetPhysAddr(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType            retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module in case of AUTOSAR Socket API. */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);

  retVal = TcpIp_GetPhysAddr(SoAd_GetAddrIdOfLocalAddr(localAddrIdx), PhysAddrPtr);                                    /* SBSW_SOAD_POINTER_FORWARD */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_1 */
  /* #11 Retrieve the physical address for QNX Socket API. */
  retVal = SoAd_TcpIpBsd_QnxGetPhysAddr(SoConIdx, PhysAddrPtr);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_1 */
  /* #12 Retrieve the physical address for INTEGRITY Socket API. */
  retVal = SoAd_TcpIpBsd_IntegrityGetPhysAddr(SoConIdx, PhysAddrPtr);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_1 */
  /* #13 Retrieve the physical address for Linux Socket API otherwise. */
  retVal = SoAd_TcpIpBsd_LinuxGetPhysAddr(SoConIdx, PhysAddrPtr);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX */

  return retVal;
} /* SoAd_TcpIp_GetPhysAddr() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_ReadDhcpHostNameOption()
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
/* PRQA S 3206, 3673 4 */ /* MD_SoAd_UnusedParameter, MD_SoAd_ConstCausedByUnused */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ReadDhcpHostNameOption(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) LengthPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Handle request for AUTOSAR Socket API. */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
#  if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
  /* #100 Forward request to TcpIp module for DHCPv6. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
  {
    uint16 tmpLength = *LengthPtr;

    if ( TcpIp_DhcpV6ReadOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx), SOAD_DHCP_OPT_V6_HOSTNAME,                    /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
        &tmpLength, DataPtr) == E_OK )
    {
      *LengthPtr = (uint8)tmpLength;                                                                                   /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
    }
  }
#  endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
#  if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
  /* #101 Forward request to TcpIp module for DHCPv4. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET )
  {
    retVal = TcpIp_DhcpReadOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx), SOAD_DHCP_OPT_V4_HOSTNAME,                  /* SBSW_SOAD_POINTER_FORWARD */
      LengthPtr, DataPtr);
  }
#  endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
# else
  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(LengthPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#else
  /* #20 Handle request for BSD-like Socket API. */

  /* #200 Retrieve hostname via Socket API. */
  if ( gethostname((char*)DataPtr, *LengthPtr) == SOAD_BSD_NO_ERROR ) /* PRQA S 5209 */ /* MD_SoAd_BasicType */
  {
    uint8_least idx;

    /* #2000 Determine hostname length. */
    for ( idx = 0u; idx < *LengthPtr; idx++ )
    {
      if ( DataPtr[idx] == 0u )
      {
        *LengthPtr = (uint8)idx;
      }
    }

    retVal = E_OK;
  }
  /* #201 Report Socket API error if call to Socket API failed. */
  else
  {
    SOAD_REPORT_SOCK_ERROR_PARAM_1(SOAD_SOCK_SID_TCPIP_READ_DHCP_HOST_NAME_OPTION, SOAD_SOCK_BSD_API_GET_HOST_NAME,
      SOAD_SOCK_BSD_PARAM_NONE, SoAd_GetSoConIdOfSoCon(SoConIdx), errno);
  }

  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_ReadDhcpHostNameOption() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_WriteDhcpHostNameOption()
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
/* PRQA S 3206 4 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_WriteDhcpHostNameOption(
  SoAd_SizeOfSoConType SoConIdx,
  uint8 Length,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Handle request for AUTOSAR Socket API. */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
#  if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
  /* #100 Forward request to TcpIp module for DHCPv6. */
  if (  SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
  {
    retVal = TcpIp_DhcpV6WriteOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx), SOAD_DHCP_OPT_V6_HOSTNAME,               /* SBSW_SOAD_POINTER_FORWARD */
      Length, DataPtr);
  }
#  endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
#  if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
  /* #101 Forward request to TcpIp module for DHCPv4. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET )
  {
    retVal = TcpIp_DhcpWriteOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx), SOAD_DHCP_OPT_V4_HOSTNAME,                 /* SBSW_SOAD_POINTER_FORWARD */
      Length, DataPtr);
  }
#  endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
# else
  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(Length); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT_CONST(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON)) */
#else
  /* #20 Handle request for BSD-like Socket API otherwise. */

  /* #200 Set hostname via Socket API. */
  if ( sethostname((SOAD_P2CONST(char))DataPtr, Length) == 0u ) /* PRQA S 5209 */ /* MD_SoAd_BasicType */
  {
    retVal = E_OK;
  }
  /* #201 Report Socket API error if call to Socket API failed. */
  else
  {
    SOAD_REPORT_SOCK_ERROR_PARAM_1(SOAD_SOCK_SID_TCPIP_WRITE_DHCP_HOST_NAME_OPTION,
      SOAD_SOCK_BSD_API_SET_HOST_NAME, SOAD_SOCK_BSD_PARAM_NONE, SoAd_GetSoConIdOfSoCon(SoConIdx), errno);
  }

  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_WriteDhcpHostNameOption() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_ReadDhcpOption()
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
/* PRQA S 3206, 3673 5 */ /* MD_SoAd_UnusedParameter, MD_SoAd_ConstCausedByUnused */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ReadDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) DataLengthPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfLocalAddrIdMap(IpAddrId);
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle request for AUTOSAR Socket API. */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
#  if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
  /* #100 Forward request to TcpIp module for DHCPv6. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
  {
    retVal = TcpIp_DhcpV6ReadOption(IpAddrId, Option, DataLengthPtr, DataPtr);                                         /* SBSW_SOAD_POINTER_FORWARD */
  }
#  endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
#  if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
  /* #101 Forward request to TcpIp module for DHCPv4. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET )
  {
    uint8 tmpDataLength = (uint8)*DataLengthPtr;

    retVal = TcpIp_DhcpReadOption(IpAddrId, (uint8)Option, &tmpDataLength, DataPtr);                                   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

    *DataLengthPtr = tmpDataLength;                                                                                    /* SBSW_SOAD_POINTER_WRITE */
  }
#  endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
# else
  SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(Option); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataLengthPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#else
  /* #20 Handle request for BSD-like Socket API otherwise. */
  /* #200 Nothing to do since feature is not supported. */
  SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(Option); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataLengthPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_ReadDhcpOption() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_WriteDhcpOption()
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
/* PRQA S 3206 5 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_WriteDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  uint16 DataLength,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfLocalAddrIdMap(IpAddrId);
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle request for AUTOSAR Socket API. */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
#  if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
  /* #100 Forward request to TcpIp module for DHCPv6. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
  {
    retVal = TcpIp_DhcpV6WriteOption(IpAddrId, Option, DataLength, DataPtr);                                           /* SBSW_SOAD_CONST_POINTER_FORWARD */
  }
#  endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
#  if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
  /* #101 Forward request to TcpIp module for DHCPv4. */
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET )
  {
    retVal = TcpIp_DhcpWriteOption(IpAddrId, (uint8)Option, (uint8)DataLength, DataPtr);                               /* SBSW_SOAD_CONST_POINTER_FORWARD */
  }
#  endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
# else
  SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(Option); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#else
  /* #20 Handle request for BSD-like Socket API otherwise. */
  /* #200 Nothing to do since feature is not supported. */
  SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(Option); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  SOAD_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_WriteDhcpOption() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_GetSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3206 2 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_GetSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_DomainType Domain,
  SoAd_ProtocolType Protocol,
  P2VAR(SoAd_SocketIdType, AUTOMATIC, SOAD_APPL_DATA) SocketIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */
  retVal = TcpIp_SoAdGetSocket(Domain, Protocol, SocketIdPtr);                                                         /* SBSW_SOAD_POINTER_FORWARD */

  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  /* #20 Forward request to BSD-like Socket API otherwise. */
  retVal = SoAd_TcpIpBsd_GetSocket(SoConIdx, Domain, Protocol, SocketIdPtr);
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_GetSocket() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_Bind()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_Bind(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) PortPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */
  retVal = TcpIp_Bind(SocketId,
    SoAd_GetAddrIdOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))), PortPtr);         /* SBSW_SOAD_POINTER_FORWARD */
#else
  /* #20 Forward request to BSD-like Socket API otherwise. */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  retVal = SoAd_TcpIpBsd_IntegrityBind(SoConIdx, SocketId, PortPtr);
# else
  retVal = SoAd_TcpIpBsd_Bind(SoConIdx, SocketId, PortPtr);
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_Bind() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpListen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3206 2 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_TcpListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  uint16 MaxChannels)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType     retVal;
# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  sint32             osSocketId =
    SoAd_GetSocketIdOfIntegritySocketDyn(SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SocketId));
#  else
  SoAd_SocketIdType  osSocketId = SocketId;
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */
  retVal = TcpIp_TcpListen(SocketId, MaxChannels);

  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  /* #20 Forward request to BSD-like Socket API otherwise. */
  if ( listen(osSocketId, MaxChannels) != SOAD_E_BSD_NOT_OK )
  {
    /* #200 Add event to corresponding queue to handle socket in main function if call to Socket API succeeded. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SOCK_IDX,
      SoAd_GetSocketIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)));

    retVal = E_OK;
  }
  else
  {
    /* #201 Report Socket API error if call to Socket API failed. */
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_TCP_LISTEN, SOAD_SOCK_BSD_API_LISTEN,
      SOAD_SOCK_BSD_PARAM_NONE, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);

    retVal = E_NOT_OK;
  }
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_TcpListen() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpConnect()
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
/* PRQA S 3206 2 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_TcpConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  struct sockaddr_in6 sockAddr;
#  else
  struct sockaddr_in  sockAddr;
#  endif /* SOAD_IPV6 == STD_ON */
  size_t              sockAddrLen;
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  sint32              osSocketId =
    SoAd_GetSocketIdOfIntegritySocketDyn(SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SocketId));
#  else
  SoAd_SocketIdType   osSocketId = SocketId;
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
  Std_ReturnType      retVal;

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */
  retVal = TcpIp_TcpConnect(SocketId, RemAddrPtr);                                                                     /* SBSW_SOAD_POINTER_FORWARD */

  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  /* #20 Forward request to BSD-like Socket API otherwise. */
  /* #200 Convert remote address for BSD-like Socket API. */
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( RemAddrPtr->domain == SOAD_AF_INET6 )
  {
    (SOAD_A_P2VAR(struct sockaddr_in6)&sockAddr)->sin6_family = AF_INET6;
    (SOAD_A_P2VAR(struct sockaddr_in6)&sockAddr)->sin6_scope_id = SoAd_GetCtrlIdxOfTcpIpCtrlDyn(
      SoAd_GetTcpIpCtrlIdxOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))));
    sockAddrLen = sizeof(struct sockaddr_in6);
  }
  else
#  endif /* SOAD_IPV6 == STD_ON */
  {
    (SOAD_A_P2VAR(struct sockaddr_in)&sockAddr)->sin_family = AF_INET;
    sockAddrLen = sizeof(struct sockaddr_in);
  }
  SoAd_TcpIpBsd_ConvertAsrSockAddr2BsdSockAddr(SOAD_A_P2VAR(struct sockaddr)&sockAddr, RemAddrPtr);

  /* #201 Call Socket API. */
  (void)connect(osSocketId, SOAD_A_P2VAR(struct sockaddr)&sockAddr, sockAddrLen);

  if ( EINPROGRESS == errno )
  {
    /* #2010 Add event to corresponding queue to handle socket in main function if call to Socket API succeeded. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SOCK_IDX, SoAd_GetSocketIdxOfSoCon(SoConIdx));

    retVal = E_OK;
  }
  else
  {
    /* #2011 Report Socket API error if call to Socket API failed. */
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_TCP_CONNECT, SOAD_SOCK_BSD_API_CONNECT,
      SOAD_SOCK_BSD_PARAM_NONE, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);

    retVal = E_NOT_OK;
  }
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_TcpConnect() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIp_ChangeParameter()
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
/* PRQA S 3206 2 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_ChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SocketIdType SocketId,
  SoAd_ParamIdType ParameterId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ParameterValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */
  if ( ParameterId < SOAD_PARAMID_STACK_SPECIFIC )
  {
    /* #100 Forward only if parameter identifier is valid for TcpIp module. */
    retVal = TcpIp_ChangeParameter(SocketId, ParameterId, ParameterValue);                                             /* SBSW_SOAD_POINTER_FORWARD */
  }
  else
  {
    retVal = E_OK;
  }

  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  /* #20 Forward request to BSD-like Socket API otherwise. */
  /* #200 Forward request to Socket API for main socket. */
  retVal = SoAd_TcpIpBsd_ChangeParameter(SoConIdx, SocketId, ParameterId, ParameterValue);

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  if ( ParameterId == SOAD_PARAMID_STACK_SPECIFIC )
  {
    SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx);
    SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
    SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);

    if ( (retVal == E_OK)
#  if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
      && SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx)
#  endif /* SOAD_TCP == STD_ON */
      )
    {
      /* #201 Forward request to Socket API for separate broadcast sockets in case of unicast local address with
       *      enabled broadcasts. */
      if ( SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST )
      {
        if ( SoAd_IsBroadcastRxEnabledOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
        {
          retVal = SoAd_TcpIpBsd_ChangeParameter(SoConIdx,
            SoAd_GetDirLinkSocketIdOfSocketDyn(sockIdx), ParameterId, ParameterValue);
          retVal |= SoAd_TcpIpBsd_ChangeParameter(SoConIdx,
            SoAd_GetLimNodeSocketIdOfSocketDyn(sockIdx), ParameterId, ParameterValue);
        }
      }
      /* #202 Join multicast addresses in case of multicast local address. */
      else
      {
#  if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
        SoAd_IpAddrInetXType      localIpAddr = SoAd_GetAddrOfLocalAddrDyn(localAddrIdx);
        SoAd_SizeOfTcpIpCtrlType  tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);

        /* #2020 Join IPv6 multicast address (if configured). */
        if ( SoAd_GetDomainOfLocalAddr(localAddrIdx) == SOAD_AF_INET6 )
        {
          struct ipv6_mreq mreq;

          mreq.ipv6mr_interface = SoAd_GetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx);

          /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
          VStdMemCpy(
            SOAD_A_P2VAR(void)mreq.ipv6mr_multiaddr.s6_addr,
            SOAD_A_P2CONST(void)localIpAddr.addr,
            SOAD_IPV6_ADDR_LEN_BYTE);

          if ( setsockopt(SocketId, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq, sizeof(mreq)) == SOAD_E_BSD_NOT_OK )
          {
            retVal = E_NOT_OK;
            SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_CHANGE_PARAMETER, SOAD_SOCK_BSD_API_SET_SOCK_OPT,
              SOAD_SOCK_BSD_PARAM_IPV6_JOIN_GROUP, SOAD_SOCK_BSD_VALUE_NONE, SocketId, errno);
          }
        }
        else
#  endif /* SOAD_IPV6 == STD_ON */
        /* #2021 Join IPv4 multicast address otherwise. */
        {
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_QNX ) /* COV_SOAD_QM_FEATURE_3 */
          retVal = SoAd_TcpIpBsd_QnxJoinMultiCastGroupV4(SoConIdx, SocketId);
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_QNX */
#  if ( SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX ) /* COV_SOAD_QM_FEATURE_3 */
          retVal = SoAd_TcpIpBsd_LinuxJoinMultiCastGroupV4(SoConIdx, SocketId);
#  endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_LINUX */
        }
      }
    }
  }
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_INTEGRITY */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_ChangeParameter() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_Close()
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
/* PRQA S 3206 4 */ /* MD_SoAd_UnusedParameter */
FUNC(void, SOAD_CODE) SoAd_TcpIp_Close(
  SoAd_SocketIdType SocketId,
  boolean Abort,
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
  SoAd_SizeOfSoConType firstSoConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(firstSoConIdx);
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */
  (void)TcpIp_Close(SocketId, Abort);

  SOAD_DUMMY_STATEMENT(SockIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  /* #20 Forward request to BSD-like Socket API otherwise. */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_TcpIpBsd_IntegrityClose((SoAd_SizeOfSocketType)SocketId);

  SOAD_DUMMY_STATEMENT(SockIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  /* #200 Close separate sockets to receive from broadcast addresses. */
#  if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(firstSoConIdx)) )
#  endif /* SOAD_TCP == STD_ON */
  {
    SoAd_SizeOfLocalAddrType localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(firstSoConIdx));

    if ( (SoAd_GetAddressTypeOfLocalAddr(localAddrIdx) == SOAD_ADDRESS_TYPE_UNICAST) &&
      SoAd_IsBroadcastRxEnabledOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
    {
      /* #2000 Close separate socket for directed broadcast/link-local address. */
      if ( close(SoAd_GetDirLinkSocketIdOfSocketDyn(SockIdx)) == SOAD_E_BSD_NOT_OK )
      {
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_CLOSE, SOAD_SOCK_BSD_API_CLOSE, SOAD_SOCK_BSD_PARAM_NONE,
          SoAd_GetSoConIdOfSoCon(firstSoConIdx), SoAd_GetDirLinkSocketIdOfSocketDyn(SockIdx), errno);
      }
      SoAd_SetDirLinkSocketIdOfSocketDyn(SockIdx, SOAD_INV_SOCKET_ID);

      /* #2001 Close separate socket for limited broadcast/node-local address. */
      if ( close(SoAd_GetLimNodeSocketIdOfSocketDyn(SockIdx)) == SOAD_E_BSD_NOT_OK )
      {
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_CLOSE, SOAD_SOCK_BSD_API_CLOSE, SOAD_SOCK_BSD_PARAM_NONE,
          SoAd_GetSoConIdOfSoCon(firstSoConIdx), SoAd_GetLimNodeSocketIdOfSocketDyn(SockIdx), errno);
      }
      SoAd_SetLimNodeSocketIdOfSocketDyn(SockIdx, SOAD_INV_SOCKET_ID);
    }
  }

  /* #201 Close main socket. */
  if ( close(SocketId) == SOAD_E_BSD_NOT_OK )
  {
    SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_CLOSE, SOAD_SOCK_BSD_API_CLOSE, SOAD_SOCK_BSD_PARAM_NONE,
      SoAd_GetSoConIdOfSoCon(firstSoConIdx), SocketId, errno);
  }
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

  /* #202 Release socket buffer. */
  SoAd_TcpIpBsdSocketTxBuffer_ReleaseAll(SockIdx);

  /* #203 Call event function to indicate that socket is closed. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(firstSoConIdx)) )
# endif /* SOAD_TCP == STD_ON */
  {
    SoAd_TcpIpEvent(SocketId, SOAD_UDP_CLOSED);
  }
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  else
  {
    if ( SoAd_IsTcpRxMgtUsedOfSocket(SockIdx) )
    {
      SoAd_SizeOfTcpRxMgtType tcpRxMgtIdx = SoAd_GetTcpRxMgtIdxOfSocket(SockIdx);

      SoAd_SetLenOfTcpRxMgt(tcpRxMgtIdx, 0u);
      SoAd_SetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx, SoAd_GetTcpRxBufferStartIdxOfSocket(SockIdx));
    }
    SoAd_TcpIpEvent(SocketId, SOAD_TCP_CLOSED);
  }
# endif /* SOAD_TCP == STD_ON */

  SOAD_DUMMY_STATEMENT(Abort); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_Close() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_TriggerAddressResolution()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TcpIp_TriggerAddressResolution(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Check if any Tx PDU is configured for the socket connection in case of AUTOSAR Socket API. */
  if ( SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(SoConIdx) !=
    SoAd_GetPduRouteDestBySoConIndEndIdxOfSoCon(SoConIdx) )
  {
    uint8 ctrlIdx = 0u;
    uint8 physAddr[6u] = { 0u, 0u, 0u, 0u, 0u, 0u };

    /* #100 Get the corresponding Ethernet interface controller index. */
    if ( TcpIp_GetCtrlIdx(SoAd_GetAddrIdOfLocalAddr(                                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))), &ctrlIdx) ==
      E_OK)
    {
      /* #1000 Trigger address resolution by getting remote physical address for the Ethernet interface controller. */
      /* PRQA S 310 2 */ /* MD_SoAd_PointerCastOnStruct */
      (void)TcpIp_GetRemotePhysAddr(ctrlIdx,                                                                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx), &physAddr[0], TRUE);
    }
  }
#else
  /* #20 Ignore call in case of BSD-like Socket API. */

  SOAD_DUMMY_STATEMENT(SoConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_TriggerAddressResolution() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_UdpTransmit()
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
/* PRQA S 3206 2 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_UdpTransmit(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, AUTOMATIC) RemAddrPtr,
  uint16 AvailableLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */
  retVal = TcpIp_UdpTransmit(SocketId, NULL_PTR, RemAddrPtr, AvailableLength);                                         /* SBSW_SOAD_POINTER_AND_NULL_POINTER_FORWARD */

  SOAD_DUMMY_STATEMENT(SockIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  /* #11 Forward request to BSD-like Socket API otherwise. */
  SOAD_P2VAR(uint8)                   bufferPtr = NULL_PTR;
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  struct sockaddr_in6                 remAddr;
# else
  struct sockaddr_in                  remAddr;
# endif /* SOAD_IPV6 == STD_ON */
  size_t                              remAddrLength = sizeof(struct sockaddr_in);
  uint16                              msgFlags = SOAD_ZERO_FLAGS;
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_SizeOfSoConGrpType             soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(SockIdx));
  SoAd_SizeOfLocalAddrType            localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  SoAd_SizeOfTcpIpCtrlType            tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx);
# endif /* SOAD_IPV6 == STD_ON */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_SocketIdType                   osSocketId =
    SoAd_GetSocketIdOfIntegritySocketDyn(SoAd_GetIntegritySocketDynIdxOfSocketToIntegritySocketMap(SockIdx));
# else
  SoAd_SocketIdType                   osSocketId = SocketId;
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

  retVal = E_NOT_OK;

  /* #20 Convert remote address for BSD-like Socket API. */
  SoAd_TcpIpBsd_ConvertAsrSockAddr2BsdSockAddr(SOAD_A_P2VAR(struct sockaddr)&remAddr, RemAddrPtr);

  /* #30 Request socket transmission buffer. */
  if ( SoAd_TcpIpBsdSocketTxBuffer_Request(SockIdx, AvailableLength, &bufferPtr) == E_OK )
  {
    /* #40 Let SoAd copy data to transmission buffer by calling SoAd_CopyTxData. */
# if ( SOAD_TX_DYN_LEN == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( SoAd_CopyTxData(SocketId, bufferPtr, SOAD_A_P2VAR(uint16)&AvailableLength) == BUFREQ_OK )
# else
    if ( SoAd_CopyTxData(SocketId, bufferPtr, AvailableLength) == BUFREQ_OK )
# endif /* SOAD_TX_DYN_LEN == STD_ON */
    {
      /* #50 Prepare to call Socket API for transmission. */
# if ( SOAD_IPV6 == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
      if ( RemAddrPtr->domain == SOAD_AF_INET6 )
      {
        remAddr.sin6_scope_id = SoAd_GetCtrlIdxOfTcpIpCtrlDyn(tcpIpCtrlIdx);
        remAddrLength = sizeof(struct sockaddr_in6);
      }
      else
# endif /* SOAD_IPV6 == STD_ON */
      {
        /* #500 Disable routing for IPv4 limited broadcast messages. */
        P2CONST(struct sockaddr_in,  AUTOMATIC, SOAD_APPL_VAR) addrPtr = SOAD_A_P2CONST(struct sockaddr_in)&remAddr;
        if ( addrPtr->sin_addr.s_addr == INADDR_BROADCAST )
        {
          msgFlags = MSG_DONTROUTE;
        }
      }

      /* #60 Check if call to Socket API for transmission succeeds. */
      if ( sendto(osSocketId, SOAD_A_P2CONST(void)bufferPtr, AvailableLength, msgFlags,
        SOAD_A_P2VAR(struct sockaddr)&remAddr, remAddrLength) != SOAD_E_BSD_NOT_OK )
      {
        retVal = E_OK;
      }
      /* #61 Report error on socket otherwise. */
      else
      {
        SOAD_REPORT_SOCK_ERROR_PARAM_2(SOAD_SOCK_SID_TCPIP_UDP_TRANSMIT, SOAD_SOCK_BSD_API_SEND_TO,
          SOAD_SOCK_BSD_PARAM_NONE, SOAD_SOCK_BSD_VALUE_NONE, osSocketId, errno);
      }
    }

    /* #70 Release socket transmission buffer. */
    SoAd_TcpIpBsdSocketTxBuffer_ReleaseLast(SockIdx);
  }
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_UdpTransmit() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpTransmit()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpIp_TcpTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 AvailableLength,
  boolean ForceRetrieve)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType               sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SocketIdType                   socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx);
  Std_ReturnType                      retVal = E_NOT_OK;
# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
  SOAD_P2VAR(uint8)                   bufferPtr = NULL_PTR;
  uint16                              localAvailableLength = (uint16)AvailableLength;
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */

  /* #20 Forward request to TcpIp module if socket identifier is valid. */
  if ( socketId != SOAD_INV_SOCKET_ID )
  {
    retVal = TcpIp_TcpTransmit(socketId, NULL_PTR, AvailableLength, ForceRetrieve);                                    /* SBSW_SOAD_NULL_POINTER_FORWARD */
  }
# else
  /* #11 Forward request to BSD-like Socket API otherwise. */

  /* #30 Request socket transmission buffer. */
  if ( SoAd_TcpIpBsdSocketTxBuffer_Request(sockIdx, localAvailableLength, &bufferPtr) == E_OK )
  {
    /* #40 Let SoAd copy data to socket transmission buffer. */
#  if ( SOAD_TX_DYN_LEN == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
    if ( SoAd_CopyTxData(socketId, bufferPtr, &localAvailableLength) == BUFREQ_OK )
#  else
    if ( SoAd_CopyTxData(socketId, bufferPtr, localAvailableLength) == BUFREQ_OK )
#  endif /* SOAD_TX_DYN_LEN == STD_ON */
    {
      /* #50 Set the socket transmission buffer for transmission and update used buffer if required. */
      if ( SoAd_TcpIpBsdSocketTxBuffer_Set(sockIdx, localAvailableLength) == E_OK )
      {
        /* #60 Set event to handle TCP transmission in main function. */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TCP_TX_SO_CON, SoConIdx);

        retVal = E_OK;
      }
    }

    /* #70 Release buffer in case of any error. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_TcpIpBsdSocketTxBuffer_ReleaseLast(sockIdx);
    }
  }

  SOAD_DUMMY_STATEMENT(ForceRetrieve); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */

  return retVal;
} /* SoAd_TcpIp_TcpTransmit() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_TcpReceived()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TcpIp_TcpReceived(
  SoAd_SizeOfSocketType SockIdx,
  uint32 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
  SoAd_SizeOfTcpRxMgtType     tcpRxMgtIdx = SoAd_GetTcpRxMgtIdxOfSocket(SockIdx);
  SoAd_SizeOfTcpRxBufferType  tcpRxBufferMaxLen = SoAd_GetTcpRxBufferEndIdxOfSocket(SockIdx) -
    SoAd_GetTcpRxBufferStartIdxOfSocket(SockIdx);
  SoAd_SizeOfTcpRxBufferType  tcpRxBufferRelIdx = SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) -
    SoAd_GetTcpRxBufferStartIdxOfSocket(SockIdx);
# else
  SoAd_SocketIdType           socketId = SoAd_GetSocketIdOfSocketDyn(SockIdx);
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
  /* #10 Forward request to TcpIp module. */

  /* #20 Forward request to TcpIp module if socket identifier is valid. */
  if ( socketId != SOAD_INV_SOCKET_ID )
  {
    (void)TcpIp_TcpReceived(socketId, Length);
  }
# else
  /* #11 Release local reception ring buffer considering wrap around in case of BSD-like Socket API otherwise. */
  if ( (tcpRxBufferRelIdx + Length) > tcpRxBufferMaxLen )
  {
    SoAd_SetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx,
      (SoAd_SizeOfTcpRxBufferType)(SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) - (tcpRxBufferMaxLen - Length)));
  }
  else
  {
    SoAd_SetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx,
      (SoAd_SizeOfTcpRxBufferType)(SoAd_GetTcpRxBufferIdxOfTcpRxMgt(tcpRxMgtIdx) + Length));
  }
  SoAd_SetLenOfTcpRxMgt(tcpRxMgtIdx, (SoAd_LenOfTcpRxMgtType)(SoAd_GetLenOfTcpRxMgt(tcpRxMgtIdx) - Length));
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_TcpReceived() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TcpIp_MainFunctionRx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TcpIp_MainFunctionRx(void)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
  /* #10 Handle socket reception in case of BSD-like Socket API. */
  SoAd_TcpIpBsd_HandleSocketReception();
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_MainFunctionRx() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_MainFunctionState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TcpIp_MainFunctionState(void)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
  /* #10 Handle local IP address availability check interval counter in case of BSD-like Socket API. */
# if ( SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_TcpIpBsd_IntegrityHandleLocalAddressCheckInterval();
# else
  SoAd_TcpIpBsd_HandleLocalAddressCheckInterval();
# endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_INTEGRITY */

  /* #20 Handle IP addres states in case of BSD-like Socket API. */
  SoAd_TcpIpBsd_HandleIpAddrStates();

  /* #30 Handle TCP socket states in case of BSD-like Socket API. */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  SoAd_TcpIpBsd_HandleTcpSocketStates();
# endif /* SOAD_TCP == STD_ON */
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_MainFunctionState() */

/**********************************************************************************************************************
 *  SoAd_TcpIp_MainFunctionTx()
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
FUNC(void, SOAD_CODE) SoAd_TcpIp_MainFunctionTx(void)
{
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
# if ( SOAD_TCP == STD_ON ) /* COV_SOAD_QM_FEATURE_3 */
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueTcpTxSoConIterType eventQueueTcpTxSoConIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_TCP_TX_SO_CON);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueTcpTxSoConIter = 0u;
    eventQueueTcpTxSoConIter < elementNumToHandle;
    eventQueueTcpTxSoConIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_TCP_TX_SO_CON, &handleIdx) == E_OK )
    {
      SoAd_SizeOfSoConType  soConIdx = (SoAd_SizeOfSoConType)handleIdx;
      SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx);

      /* #30 Transmit socket transmission buffers. */
      if ( SoAd_TcpIpBsdSocketTxBuffer_Transmit(sockIdx) == E_NOT_OK )
      {
        /* #300 Set event to handle transmission in main function again if transmission failed. */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TCP_TX_SO_CON, soConIdx);
      }

      /* #40 Handle pending TCP Tx Confirmation on socket connection. */
      SoAd_TcpIpBsd_HandleTcpTxConfirmation(sockIdx);
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }

# endif /* SOAD_TCP == STD_ON */
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
} /* SoAd_TcpIp_MainFunctionTx() */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_TcpIp.c
 *********************************************************************************************************************/
