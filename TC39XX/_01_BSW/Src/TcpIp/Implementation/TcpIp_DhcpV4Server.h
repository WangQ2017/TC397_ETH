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
 *         \file  TcpIp_DhcpV4Server.h
 *        \brief  Implementation of Dynamic Host Configuration Protocol for IPv4 - Server (DHCPv4 Server)
 *
 *      \details  This file contains the implementation of the DHCPv4 Server for the Semi-Static Auto-Configuration
 *                of the AUTOSAR Concept "Ethernet Configuration and System Description for Manageable Switched Systems"
 *                This file is part of the TcpIp DHCPv4 Server submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 *  Until version 7.xx.xx the following table lists the changes affecting the following files:
 *    TcpIp_DhcpV4Server.*
 *
 *  Since version 8.00.00 all changes are documented in TcpIp.h.
 *
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *                                -             All changes of Tp_TcpIp Implementation_DhcpV4Server 2.00.00 are included.
 *  01.00.00  2015-06-18  visfdn  ESCAN00083591 FEAT-1248: Configuration of the TCP/IP stack according to AR 4.2.1
 *  02.00.00  2015-11-26  visal   -             no changes in the implementation
 *  03.00.00  2016-06-16  visfdn  ESCAN00088858 DHCPv4 server does not respond correctly to a client with broadcast flag set to 0
 *  03.01.00  2017-01-17  visfdn  ESCAN00092143 DHCPv4-Server is not fully reset after DHCP STOP and DHCP START
 *            2017-01-17  visfdn  ESCAN00089423 If client's 'giaddr' is non-zero the DHCPv4-Server does not send return message to the 'DHCP server' port
 *            2017-01-17  visfdn  ESCAN00089451 Retain record of client's initialization parameters for later reuse.
 *            2017-01-17  visfdn  ESCAN00089401 NAK request from a client who moved to a new subnet.
 *            2017-01-17  visfdn  ESCAN00089398 DHCPv4-Server does not send DHCP-NAK messages
 *            2017-01-17  visfdn  ESCAN00092149 OFFER IP address that is requested in a DISCOVER message
 *            2017-01-17  visfdn  ESCAN00084715 BETA version - no series production allowed (AR4-500)
 *            2017-01-17  visfdn  FEATC-254     FEAT-1830: Release of DHCPv4 server (AR4-500)
 *  03.02.00  2017-07-06  visfdn  STORYC-1478   P3 Implementation cleanup
 *  07.00.00  2018-03-15  visfdn  STORYC-352    Usage of ComStackLib for generated data.
 *            2018-03-15  visfdn  STORYC-2204   Code Refactoring in order to improve code metrics.
 *  07.00.01  2018-04-11  vismjv  STORYC-4950   Integration of code inspection findings
 *  07.00.02  2018-05-30  visfdn  -             Module-wide editorial changes. / No change of functionality.
 *  -------------------------------------------------------------------------------------------------------------------
 *  08.00.00  2018-06-11  visfdn  -             See TcpIp.h for changes in version 8.00.00 and above.
 *********************************************************************************************************************/

#if !defined (TCPIP_DHCPV4SERVER_H)
#define TCPIP_DHCPV4SERVER_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_DHCPV4SERVER == STD_ON)                                                                              /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "TcpIp_Types.h"

#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
#define TCPIP_DHCPV4SERVER_VENDOR_ID                           (30u)
#define TCPIP_DHCPV4SERVER_MODULE_ID                           TCPIP_MODULE_ID /* TcpIp module id */

/* AUTOSAR Software specification version information */
#define TCPIP_DHCPV4SERVER_AR_RELEASE_MAJOR_VERSION            (0x04u)
#define TCPIP_DHCPV4SERVER_AR_RELEASE_MINOR_VERSION            (0x02u)
#define TCPIP_DHCPV4SERVER_AR_RELEASE_REVISION_VERSION         (0x01u)

#define TCPIP_DHCPV4SERVER_INSTANCE_ID_DET                     (0x04u) /* 0=SoAd, 1=TcpIp, 2=IpV4, 3=IpV6, 4=DhcpV4Server */

/* ----- API service IDs ----- */
/* Service ID: TcpIp_DhcpV4Server_Init() */
#define TCPIP_DHCPV4SERVER_SID_INIT                            (0x00u)
/* Service ID: TcpIp_DhcpV4Server_Start() */
#define TCPIP_DHCPV4SERVER_SID_START                           (0x01u)
/* Service ID: TcpIp_DhcpV4Server_Stop() */
#define TCPIP_DHCPV4SERVER_SID_STOP                            (0x02u)
/* Service ID: TcpIp_DhcpV4Server_GetVersionInfo() */
#define TCPIP_DHCPV4SERVER_SID_GET_VERSION_INFO                (0x03u)
/* Service ID: TcpIp_DhcpV4Server_MainFunction() */
#define TCPIP_DHCPV4SERVER_SID_MAIN_FUNCTION                   (0x04u)
/* Service ID: TcpIp_DhcpV4Server_RxIndication() */
#define TCPIP_DHCPV4SERVER_SID_RX_INDICATION                   (0x05u)
/* Service ID: TcpIp_DhcpV4Server_TxMessage() */
#define TCPIP_DHCPV4SERVER_SID_TX_MESSAGE                      (0x06u)
/* Service ID: TcpIp_DhcpV4Server_GetClientRecIdx() */
#define TCPIP_DHCPV4SERVER_SID_GET_CLIENT_REC_IDX              (0x07u)
/* Service ID: TcpIp_DhcpV4Server_CopyTxData() */
#define TCPIP_DHCPV4SERVER_SID_COPY_TX_DATA                    (0x08u)
/* Service ID: TcpIp_DhcpV4Server_LocalIpAddrAssignmentChg() */
#define TCPIP_DHCPV4SERVER_SID_LOCAL_IP_ADDR_ASSIGNMENT_CHG    (0x09u)
/* Service ID: TcpIp_DhcpV4Server_V....() */
#define TCPIP_DHCPV4SERVER_SID_VINTERNAL_FUNCTION              (0xFFu)

/* ----- Error codes ----- */
/* Error code: API service TcpIp_DhcpV4Server_Init() called with wrong parameter  */
#define TCPIP_DHCPV4SERVER_E_PARAM_CONFIG                      (0x0Au)
/* Error Code: API service used with an invalid channel identifier or channel was not configured for the
 * functionality of the calling API */
#define TCPIP_DHCPV4SERVER_E_PARAM_CHANNEL                     (0x0Bu)
/* Error code: API service used with invalid value parameter */
#define TCPIP_DHCPV4SERVER_E_INV_PARAM                         (0x0Cu)
/* Error code: API service used without module initialization */
#define TCPIP_DHCPV4SERVER_E_UNINIT                            (0x10u)
/* Error code: The service TcpIp_DhcpV4Server_Init() is called while the module is already initialized  */
#define TCPIP_DHCPV4SERVER_E_ALREADY_INITIALIZED               (0x11u)
/* Error code: API service called with NULL_PTR as parameter  */
#define TCPIP_DHCPV4SERVER_E_INV_PTR                           (0x12u)
/* Error code: Insufficient buffers or buffer length  */
#define TCPIP_DHCPV4SERVER_E_OUT_OF_MEMORY                     (0x13u)
/* Error code: Number of configured client record is not sufficient */
#define TCPIP_DHCPV4SERVER_E_TOO_MANY_CLIENTS                  (0x14u)
/* Error code: Indicates that the payload length of the assembled message does not match the requested buffer length */
#define TCPIP_DHCPV4SERVER_E_INV_MSG_LEN                       (0x16u)
/* Error code: Indicates that an unexpected error in an internal function has occurred */
#define TCPIP_DHCPV4SERVER_E_INTERNAL_ERROR                    (0x17u)
/* Error code: Indicates that TcpIp_GetSocket() call for the UDP server socket has failed. */
#define TCPIP_DHCPV4SERVER_E_UDP_SOCKET_GET_ERROR              (0x18u)
/* Error code: Indicates that TcpIp_Bind() call for the UDP server socket has failed. */
#define TCPIP_DHCPV4SERVER_E_UDP_SOCKET_BIND_ERROR             (0x19u)
/* Error code: Indicates that TcpIp_Close() call for the UDP server socket has failed. */
#define TCPIP_DHCPV4SERVER_E_UDP_SOCKET_CLOSE_ERROR            (0x20u)

/* ----- Mapping of error reporting macro ----- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
# define TcpIp_DhcpV4Server_CheckDetErrorReturnVoid(  CONDITION, API_ID, ERROR_CODE )           {  \
   if(!(CONDITION)) {  \
   (void) Det_ReportError( (uint16)TCPIP_DHCPV4SERVER_MODULE_ID, (uint8)TCPIP_DHCPV4SERVER_INSTANCE_ID_DET, (uint8)(API_ID), (uint8)(ERROR_CODE)); \
   return; } }
# define TcpIp_DhcpV4Server_CheckDetErrorReturnValue( CONDITION, API_ID, ERROR_CODE, RET_VAL )  {  \
   if(!(CONDITION)) {  \
   (void) Det_ReportError( (uint16)TCPIP_DHCPV4SERVER_MODULE_ID, (uint8)TCPIP_DHCPV4SERVER_INSTANCE_ID_DET, (uint8)(API_ID), (uint8)(ERROR_CODE)); \
   return (RET_VAL); } }
# define TcpIp_DhcpV4Server_ReportDetError( API_ID, ERROR_CODE) { \
   (void) Det_ReportError( (uint16)TCPIP_DHCPV4SERVER_MODULE_ID, (uint8)TCPIP_DHCPV4SERVER_INSTANCE_ID_DET, (uint8)(API_ID), (uint8)(ERROR_CODE)); \
   }
#else
# define TcpIp_DhcpV4Server_CheckDetErrorReturnVoid(  CONDITION, API_ID, ERROR_CODE )
# define TcpIp_DhcpV4Server_CheckDetErrorReturnValue( CONDITION, API_ID, ERROR_CODE, RET_VAL )
# define TcpIp_DhcpV4Server_ReportDetError(API_ID, ERROR_CODE)
#endif

/* ----- Modes ----- */
#define TCPIP_DHCPV4SERVER_STATE_UNINIT                                 (0x00U)
#define TCPIP_DHCPV4SERVER_STATE_INIT                                   (0x01U)

#define TCPIP_DHCPV4SERVER_INV_SERVER_CONF_IDX                          TcpIp_GetSizeOfDhcpV4ServerConfig()
#define TCPIP_DHCPV4SERVER_INV_ADDR_LEASE_REC_IDX                       TcpIp_GetSizeOfDhcpV4ServerAddrLeaseRecs()
#define TCPIP_DHCPV4SERVER_INV_ADDR_ASSIGN_IDX                          TcpIp_GetSizeOfDhcpV4ServerAddressAssignmentConfig()

#define TCPIP_DHCPV4SERVER_LEASE_STATE_INIT                             1U /* The lease record is assigned to a client (client identifier is set) */
#define TCPIP_DHCPV4SERVER_LEASE_STATE_EXPIRED                          2U /* The lease record is expired and may be reused for the same client in future. */
#define TCPIP_DHCPV4SERVER_LEASE_STATE_TX_OFFER                         3U
#define TCPIP_DHCPV4SERVER_LEASE_STATE_RX_REQUEST                       4U
#define TCPIP_DHCPV4SERVER_LEASE_STATE_TX_ACK                           5U
#define TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK                           6U
#define TCPIP_DHCPV4SERVER_LEASE_STATE_TX_NAK_BROADCAST                 7U

#define TCPIP_DHCPV4SERVER_REQUEST_LEASE_TIME_ENABLED STD_ON

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */

#define TCPIP_DHCPV4SERVER_P2C(TYPE) P2CONST(TYPE, AUTOMATIC, TCPIP_APPL_DATA)
#define TCPIP_DHCPV4SERVER_P2V(TYPE) P2VAR(  TYPE, AUTOMATIC, TCPIP_APPL_VAR)

#define TCPIP_DHCPV4SERVER_COPY(DST_PTR, SRC_PTR, LEN_BYTE) IpBase_Copy((IpBase_CopyDataType*)(DST_PTR), (const IpBase_CopyDataType*)(SRC_PTR), (LEN_BYTE))

#define TCPIP_DHCPV4SERVER_UNUSED_PARAMETER(Parameter) TCPIP_DUMMY_STATEMENT(Parameter)

/* PRQA L:FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint8 TcpIp_DhcpV4Server_ConfigType;

typedef struct
{
  uint16 OptOfs;
  uint8  OptLen;
} TcpIp_DhcpV4Server_KnownDynamicOptionInfoType;

typedef struct
{
  IpBase_AddrInType ReqIpAddr;
  IpBase_AddrInType ServerId;
#if (TCPIP_DHCPV4SERVER_REQUEST_LEASE_TIME_ENABLED == STD_ON)
  uint32            LeaseTime;
#endif
  TcpIp_DhcpV4Server_KnownDynamicOptionInfoType ClientId;
  uint8 ParamReqSet;
  uint8 MessageType;
  uint8 OptionOverload;
} TcpIp_DhcpV4Server_KnownOptionsInfoType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Service functions */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Power-up memory initialization.
 *  \details     Initializes component variables(Flag) in *ZERO_INIT_* sections at power up.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note         Use this function in case these variables are not initialized by the startup code.
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_InitMemory(void);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_Init()
 *********************************************************************************************************************/
/*! \brief       Initializes component
 *  \details     Initializes all component variables and sets the component state to initialized.
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *               Msn_InitMemory has been called unless Msn_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
***********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_Init(void);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns version information of the DhcpV4Server
 *  \details     TcpIp_DhcpV4Server_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  VersionInfoPtr     Pointer to where to store the version information
 *  \pre         Input parameter must not be NULL_PTR.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, TCPIP_APPL_DATA) VersionInfoPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*! \brief        Notifies the DHCP server that a TcpIp local address was assigned/unassigned.
 *  \details      -
 *  \param[in]    LocalAddrId  Identifier of the local IP address that has changed.
 *  \param[in]    State        State of the local IP address (ASSIGNED, UNASSIGNED, ONHOLD).
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_LocalIpAddrAssignmentChg(
  TcpIp_LocalAddrIdType LocalAddrId,
  TcpIp_IpAddrStateType State);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_MainFunction()
 *********************************************************************************************************************/
/*! \brief        Cyclically called MainFunction of the DHCP server.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) TcpIp_DhcpV4Server_MainFunction(void);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_Start
 *********************************************************************************************************************/
/*! \brief        Starts all configured DHCP server instances.
 *  \details      -
 *  \return       E_OK      DHCP server started.
 *  \return       E_NOT_OK  Start of at least one DHCP server instance has failed. (Call again to retry)
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_Start(void);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_Stop
 *********************************************************************************************************************/
/*! \brief        Stops all configured DHCP server instances.
 *  \details      -
 *  \return       E_OK      All DHCP server instances stopped.
 *  \return       E_NOT_OK  Stop of at least one DHCP server instance has failed. (Call again to retry)
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_Stop(void);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_CopyTxData()
 *********************************************************************************************************************/
/*! \brief        Triggers copy of data into the provided Tx buffer.
 *  \details      -
 *  \param[in]    SocketId         UDP socket handle.
 *  \param[out]   BufPtr           Pointer to the buffer where the data shall be copied to.
 *  \param[in]    BufLength        Length of the provided buffer in bytes.
 *  \return       BUFREQ_OK        Data are sucessfully filled into the tx buffer.
 *  \return       BUFREQ_E_NOT_OK  Otherwise.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_DhcpV4Server_CopyTxData(
  TcpIp_SocketIdType             SocketId,
  TCPIP_DHCPV4SERVER_P2V(uint8)  BufPtr,
  uint16                         BufLength);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_RxIndication()
 *********************************************************************************************************************/
/*! \brief        Notifies the DHCP server about received UDP packets.
 *  \details      -
 *  \param[in]    SocketId      UDP socket handle.
 *  \param[in]    RemoteAddrPtr Poniter to remote socket address.
 *  \param[in]    BufPtr        Poniter to received data.
 *  \param[in]    Length        Length of the received data in bytes.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_RxIndication(
  TcpIp_SocketIdType                          SocketId,
  TCPIP_DHCPV4SERVER_P2V(TcpIp_SockAddrType)  RemoteAddrPtr,
  TCPIP_DHCPV4SERVER_P2V(uint8)               BufPtr,
  uint16                                      Length);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4Server_TcpIpEvent()
 *********************************************************************************************************************/
/*! \brief        Notifies the DHCP server about a UDP socket state change.
 *  \details      -
 *  \param[in]    SocketId    UDP socket handle.
 *  \param[in]    Event       Tcp/Ip State event.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4Server_TcpIpEvent(
  TcpIp_SocketIdType     SocketId,
  IpBase_TcpIpEventType  Event);

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_DHCPV4SERVER_ENABLED == STD_ON) */
#endif  /* TCPIP_DHCPV4SERVER_H */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_DhcpV4Server.h
 *********************************************************************************************************************/
