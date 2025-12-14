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
/**        \file  UdpNm.h
 *        \brief  AUTOSAR Udp Network Management
 *
 *      \details  Header of AUTOSAR Udp Network Management
 *                AUTOSAR Release 4.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  00.00.00  2009-02-13  visalr  -             Created
 *                                -             BRS Time Measurement support added
 *                                -             Config variant check for library build
 *                                -             Bugfix include files adapted
 *                                -             Single module header introduced (single source)
 *  00.00.01  2011-11-15  viswmc  -             Configuration parameters according to AUTOSAR 4.0.3 specification
 *  00.00.02  2011-12-07  viswmc  -             Functionality according to AUTOSAR 4.0.3 specification
 *                                -             Adapted timer handling
 *  00.00.03  2011-12-08  viswmc  -             MISRA adaptations
 *  01.00.00  2012-02-22  viswmc  -             Function signatures of RxIndication and TxConfirmation adapted
 *  01.01.00  2012-03-07  viswmc  -             Changes due to review
 *  01.02.00  2012-03-19  viswmc  -             Multi-channel support added (Cfg5 only)
 *            2012-03-19  viswmc  -             Compiler abstraction bugfixes
 *            2012-03-20  viswmc  -             MISRA and Vector Coding Rule adaption
 *            2012-04-02  viswmc  ESCAN00056362 VAR_INIT / VAR_ZERO_INIT Memory Mapping sections
 *            2012-04-12  viswmc  -             Module ID corrected
 *            2012-04-12  viswmc  -             Unused typedefs removed
 *            2012-04-12  viswmc  -             Formal changes
 *  01.02.01  2012-10-02  visalr  ESCAN00061923 ASR4 Enhancement
 *            2012-10-02  visalr  ESCAN00058888 AR4-125: Remove support for v_cfg.h in Cfg5 systems
 *  02.00.00  2013-09-04  vismha  ESCAN00068231 AR4-496: Implementation according to ASR 4.1.1 (BSWMD Schema 4.0.3)
 *            2013-09-05  vismha  ESCAN00069264 AR4-450: Usage of section PBCFG in PB files
 *            2013-10-08  vismha  ESCAN00070928 R8 AR4-89: Support Optional Confirmation
 *  02.01.00  2014-01-13  vismha  ESCAN00071762 AR4-517: Partial Networking for Ethernet
 *  02.01.01  2014-06-17  vismha  ESCAN00076294 Define STATIC in source files instead of UdpNm_Priv.h
 *                                ESCAN00076293 Compiler error: Redeclaration of UdpNm_Init
 *  02.01.02  2014-10-10  vismha  ESCAN00077708 Compiler warning: Several warnings when the component is compiled with
 *                                              Visual Studio
 *  02.01.03  2015-08-04  vismha  ESCAN00081457 State change issued to Nm during initialization although state hasn't
 *                                              changed
 *  02.01.04  2015-11-02  vismha  ESCAN00086204 AR3-2679: Description BCD-coded return-value of Xyz_GetVersionInfo()
 *                                              in TechRef
 *                                ESCAN00082595 Compiler error: Tx Buffers are used while passive mode is enabled
 *                                ESCAN00082617 UdpNm use the Nm_TxTimeoutException Api in passive mode
 *                                ESCAN00082618 UdpNm uses not available channel configuration parameters
 *  03.00.00  2015-11-26  vismha  ESCAN00084966 Remove PDU length restriction according to AUTOSAR RfC 70333
 *  03.00.01  2016-02-04  visfdn  ESCAN00088184 Nm_TxTimeoutException() called although not in state NM_STATE_NORMAL_OPERATION
 *                                ESCAN00088118 Fixed small review findings
 *  03.01.00  2016-02-12  visfdn  ESCAN00087843 FEAT-1631: Trigger Transmit API with SduLength In/Out according to ASR4.2.2
 *  03.02.00  2016-08-08  vissrk  FEATC-59      UdpNM Transmission of NM Coordinator Sleep Ready Bit
 *                                FEATC-63      Immediate Transmission Feature for UdpNM
 *            2016-09-12          FEATC-324     Support Selective Shutdown (Partial Networking)
 *            2016-10-19          ESCAN00092379 Wrong state change or no state change is notified to upper layer after NetworkRequest in state Ready Sleep or Normal Operation
 *  03.02.01  2016-11-25  vissrk  ESCAN00093017 Immediate Nm Transmissions are not executed in case 'Pn Handle Multiple Network Requests' is ON and an internal PN is requested or released
 *                                ESCAN00093027 Immediate Nm Transmissions are executed even though a value equal to 0 is configured
 *  03.02.02  2017-02-17  vissrk  ESCAN00092989 MISRA deviation: MISRA-C:2004 Rule 19.15, Rule 19.6, Rule 8.8
 *                                ESCAN00092916 For PN Handling only the latest NM message content is processed in between two UdpNm main function calls.
 *                                ESCAN00092452 UdpNm_Init compiler abstraction memclass changed to AUTOMATIC
 *                                ESCAN00092947 Com User Data is not updated in next NM message
 *  03.03.00  2017-10-25  vislsi  STORYC-2169   Added Car Wakeup Handling
 *                                ESCAN00097112 Compiler warning: variable "IsEraRxIndToBeCalled" was set but never used
 *  03.03.01  2018-01-04  vissrk  ESCAN00097753 UdpNm Active Wakeup Bit is always set on every UdpNm channel even if not configured
 *  04.00.00  2016-12-09  vissrk  FEATC-614: FEAT-2204 Support SafeBSW for UdpNm Step 1
 *            2018-06-27  vispkn  STORYC-4551   Support SafeBsw for UdpNm Step 2
 *            2018-06-28  vispkn  STORYC-4553   Finalization for SafeBsw
 *                                ESCAN00097410 Compiler error: 'UdpNm_CancelTransmit' : undeclared identifier
 *                                ESCAN00099125 Compiler error/warning: C4013, C2065, C2109, C4244
 *                                ESCAN00099290 Partial Networking is not available if Passive Mode is selected
 *  05.00.00  2019-04-05  vispkn  STORYC-8040   Extend PNC bits in NM message layout
 *                                ESCAN00099872 Compiler warning: "conditional expression is constant"
 *                                ESCAN00102787 Partial Networks are not detected properly
 *                                ESCAN00102788 UdpNm_GetPduData and UdpNm_GetUserData do not return correct data
 *                                ESCAN00102789 Car Wake Up is not executed
 *                                ESCAN00102790 Corrupted information is transmitted: Node Id / CBV are not transmitted at correct byte position
 *                                ESCAN00102792 The NM messages are transmitted with incorrect user data
 *  06.00.00  2021-09-27  vispkn  ESCAN00109020 Channels in coordinator cluster fall asleep unexpectedly
 *                                NMM-1438      Fixed QAC warnings -> updated to Helix
 **********************************************************************************************************************/

#if !defined (UDPNM_H)
# define UDPNM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "UdpNm_Cfg.h"                                                              /* Include UdpNm NM Configuration */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
# define NM_ASR4NMUDP_VERSION                          (0x0600u)
# define NM_ASR4NMUDP_RELEASE_VERSION                  (0x00u)

/* Vendor and module identification */
# define UDPNM_VENDOR_ID                               (30u)
# define UDPNM_MODULE_ID                               (33u)

/* AUTOSAR Software specification version information */
# define UDPNM_AR_RELEASE_MAJOR_VERSION                (0x04u)
# define UDPNM_AR_RELEASE_MINOR_VERSION                (0x01u)
# define UDPNM_AR_RELEASE_REVISION_VERSION             (0x01u)

/* ----- Component version information (BCD coded version of ALM implementation package) ----- */
# define UDPNM_SW_MAJOR_VERSION                        (NM_ASR4NMUDP_VERSION >> 8)
# define UDPNM_SW_MINOR_VERSION                        (NM_ASR4NMUDP_VERSION & 0x00FFu)
# define UDPNM_SW_PATCH_VERSION                        (NM_ASR4NMUDP_RELEASE_VERSION)

/* ----- API service IDs ----- */
# define UDPNM_SID_INIT                                (0x01u) /*!< Service ID: UdpNm_Init() */
# define UDPNM_SID_NETWORKREQUEST                      (0x02u) /*!< Service ID: UdpNm_NetworkRequest() */
# define UDPNM_SID_NETWORKRELEASE                      (0x03u) /*!< Service ID: UdpNm_NetworkRelease() */
# define UDPNM_SID_SETUSERDATA                         (0x04u) /*!< Service ID: UdpNm_SetUserData() */
# define UDPNM_SID_GETUSERDATA                         (0x05u) /*!< Service ID: UdpNm_GetUserData() */
# define UDPNM_SID_GETNODEIDENTIFIER                   (0x06u) /*!< Service ID: UdpNm_GetNodeIdentifier() */
# define UDPNM_SID_GETLOCALNODEIDENTIFIER              (0x07u) /*!< Service ID: UdpNm_GetLocalNodeIdentifier() */
# define UDPNM_SID_REPEATMESSAGEREQUEST                (0x08u) /*!< Service ID: UdpNm_RepeatMessageRequest() */
# define UDPNM_SID_GETVERSIONINFO                      (0x09u) /*!< Service ID: UdpNm_GetVersionInfo() */
# define UDPNM_SID_GETPDUDATA                          (0x0Au) /*!< Service ID: UdpNm_GetPduData() */
# define UDPNM_SID_GETSTATE                            (0x0Bu) /*!< Service ID: UdpNm_GetState() */
# define UDPNM_SID_DISABLECOMMUNICATION                (0x0Cu) /*!< Service ID: UdpNm_DisableCommunication() */
# define UDPNM_SID_ENABLECOMMUNICATION                 (0x0Du) /*!< Service ID: UdpNm_EnableCommunication() */
# define UDPNM_SID_PASSIVESTARTUP                      (0x0Eu) /*!< Service ID: UdpNm_PassiveStartUp() */
# define UDPNM_SID_CHECKREMOTESLEEPINDICATION          (0x11u) /*!< Service ID: UdpNm_CheckRemoteSleepIndication() */
# define UDPNM_SID_MAINFUNCTION                        (0x13u) /*!< Service ID: UdpNm_MainFunction() */
# define UDPNM_SID_REQUESTBUSSYNCHRONIZATION           (0x14u) /*!< Service ID: UdpNm_RequestBusSynchronization() */
# define UDPNM_SID_TRANSMIT                            (0x15u) /*!< Service ID: UdpNm_Transmit() */
# define UDPNM_SID_SETSLEEPREADYBIT                    (0x16u) /*!< Service ID: UdpNm_SetSleepReadyBit() */
# define UDPNM_SID_CANCELTRANSMIT                      (0xF0u) /*!< Service ID: UdpNm_CancelTransmit() */

/* ----- Error codes ----- */
# define UDPNM_E_NO_ERROR                              (0x00u) /*!< used to check if no error occurred - use a value unequal to any error code */
# define UDPNM_E_NO_INIT                               (0x01u) /*!< Error code: API service used without module initialization */
# define UDPNM_E_INVALID_CHANNEL                       (0x02u) /*!< Error code: API service used with an invalid channel identifier or channel was not configured for the functionality of the calling API */
# define UDPNM_E_INVALID_PDUID                         (0x03u) /*!< Error code: API service called with wrong PDU-ID */
# define UDPNM_E_INIT_FAILED                           (0x04u) /*!< Error code: API service UdpNm_Init() called with wrong parameter */
# define UDPNM_E_NETWORK_TIMEOUT                       (0x11u) /*!< Error code: NM-Timeout Timer has abnormally expired outside of the Ready Sleep State */
# define UDPNM_E_PARAM_POINTER                         (0x12u) /*!< Error code: API service used with invalid pointer parameter (NULL) */
# define UDPNM_E_PDUR_TRIGGERTX_ERROR                  (0x21u) /*!< Error code: Call of PduR_TriggerTransmit failed */
# define UDPNM_E_ALREADY_INITIALIZED                   (0x22u) /*!< Error code: The service UdpNm_Init() is called while the module is already initialized */
# define UDPNM_E_INVALID_GENDATA                       (0x33u) /*!< Error code: The value of a variable used for write accesses is out of bounds */

# define UDPNM_E_ECUM_NO_ERROR                         (0xFFu)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define UDPNM_START_SEC_CONST_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* UdpNm NM version (BCD coded). */
extern CONST(uint8, UDPNM_CONST) UdpNm_MainVersion;
extern CONST(uint8, UDPNM_CONST) UdpNm_SubVersion;
extern CONST(uint8, UDPNM_CONST) UdpNm_ReleaseVersion;

# define UDPNM_STOP_SEC_CONST_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define UDPNM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
  UdpNm_Init()
 **********************************************************************************************************************/
/*! \brief       Initializes component
 *  \details     Initializes all component variables and sets the component state to
 *               initialized.
 *               By default the NM starts in the Bus-Sleep Mode.
 *  \param[in]   UdpNmConfigPtr              Component configuration structure
 *  \pre         Interrupts are disabled.
 *               Module is uninitialized.
 *               UdpNm_InitMemory has been called unless UdpNm_ModuleInitialized is initialized
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-UdpNm22920
 **********************************************************************************************************************/
extern FUNC( void, UDPNM_CODE ) UdpNm_Init( CONSTP2CONST( UdpNm_ConfigType, AUTOMATIC, UDPNM_INIT_DATA ) UdpNmConfigPtr );

/***********************************************************************************************************************
  UdpNm_PassiveStartUp()
 **********************************************************************************************************************/
/*! \brief       Requests the given network passively
 *  \details     Starts the UdpNm from the Bus Sleep or Prepare Bus Sleep Mode and triggers
 *               a transition to the Network Mode (Repeat Message State)
 *               This service has no effect if the current state is not equal to
 *               Bus Sleep Mode or Prepare Bus Sleep Mode. In that case E_NOT_OK is returned
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Start of network management failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \note        Called from NM Interface
 *  \trace       CREQ-150125
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

# if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
  UdpNm_NetworkRequest()
 **********************************************************************************************************************/
/*! \brief       Requests the given network actively
 *  \details     A call of UdpNm_NetworkRequest overrides a previous call of UdpNm_PassiveStartUp
 *               ECU has a need to communicate on the bus
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Requesting bus-communication was not accepted
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \note        Called from NM Interface
 *  \config      UDPNM_PASSIVE_MODE_ENABLED == STD_OFF
 *  \trace       CREQ-150126
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

/***********************************************************************************************************************
  UdpNm_NetworkRelease()
 **********************************************************************************************************************/
/*! \brief       Releases the given network
 *  \details     ECU has no need to communicate on the bus
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Releasing bus-communication was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_PASSIVE_MODE_ENABLED == STD_OFF
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       CREQ-150127
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

/***********************************************************************************************************************
  UdpNm_GetState()
 **********************************************************************************************************************/
/*! \brief       Returns current state and mode of the network management
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmStatePtr                  Pointer where the state of the Network Management shall be copied to
 *  \param[out]  nmModePtr                   Pointer where the mode of the Network Management shall be copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting the NM state was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150124
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                          CONSTP2VAR( Nm_StateType, AUTOMATIC, UDPNM_APPL_VAR ) nmStatePtr,
                                                          CONSTP2VAR( Nm_ModeType, AUTOMATIC, UDPNM_APPL_VAR ) nmModePtr );

# if ( UDPNM_USER_DATA_ENABLED == STD_ON )
#  if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_COM_USER_DATA_SUPPORT == STD_OFF )
/***********************************************************************************************************************
  UdpNm_SetUserData()
 **********************************************************************************************************************/
/*! \brief       Sets user data for NM messages transmitted next on the bus
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[in]   nmUserDataPtr               Pointer to User data for the next transmitted NM message that shall be copied
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Setting of user data was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_USER_DATA_ENABLED == STD_ON && UDPNM_PASSIVE_MODE_ENABLED == STD_OFF && UDPNM_COM_USER_DATA_SUPPORT == STD_OFF
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-UdpNm22975
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                             CONSTP2CONST( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmUserDataPtr );
#  endif

/***********************************************************************************************************************
  UdpNm_GetUserData()
 **********************************************************************************************************************/
/*! \brief       Gets user data from last received NM message
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[in]   nmUserDataPtr               Pointer where user data out of the last received NM message shall be copied
 *                                           to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting of user data was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_USER_DATA_ENABLED == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       DSGN-UdpNm22975
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                             CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmUserDataPtr );
# endif

# if ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
  UdpNm_GetNodeIdentifier()
 **********************************************************************************************************************/
/*! \brief       Gets node identifier of the last received NM message
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmNodeIdPtr                 Pointer where node identifier from the last received NM message shall be
 *                                           copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting of node identifier was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150140
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                   CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmNodeIdPtr );

/***********************************************************************************************************************
  UdpNm_GetLocalNodeIdentifier()
 **********************************************************************************************************************/
/*! \brief       Gets node identifier configured for the local node
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmNodeIdPtr                 Pointer where node identifier of the local node shall be copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting of local node identifier was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150139
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                        CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmNodeIdPtr );
# endif

# if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
  UdpNm_RepeatMessageRequest()
 **********************************************************************************************************************/
/*! \brief       Requests state change to Repeat Message State
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Repeat Message Request was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       CREQ-150138
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_USER_DATA_ENABLED == STD_ON ) || \
      ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ))
/***********************************************************************************************************************
  UdpNm_GetPduData()
 **********************************************************************************************************************/
/*! \brief       Gets the whole PDU data out of the last NM message received from the bus
 *  \details     This includes also the CBV and NID Byte, if configured
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmPduDataPtr                Pointer where PDU Data out of the most recently received NM message shall be
 *                                           copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting the PDU data was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON || UDPNM_USER_DATA_ENABLED == STD_ON || UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       DSGN-UdpNm22975
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                            CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmPduDataPtr );
# endif


# if ( UDPNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
/***********************************************************************************************************************
  UdpNm_RequestBusSynchronization()
 **********************************************************************************************************************/
/*! \brief       Requests bus synchronization
 *  \details     Transmission of an asynchronous NM message to support coordination of coupled networks
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Requesting bus synchronization was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-150133
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_RequestBusSynchronization( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/***********************************************************************************************************************
  UdpNm_CheckRemoteSleepIndication()
 **********************************************************************************************************************/
/*! \brief       Checks if remote sleep was indicated or not
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmRemoteSleepIndPtr         Pointer where PDU Data out of the most recently received NM message
 *                                           shall be copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Checking remote sleep indication was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       DSGN-UdpNm22933
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                            CONSTP2VAR( boolean, AUTOMATIC, UDPNM_APPL_VAR ) nmRemoteSleepIndPtr );
# endif

# if ( UDPNM_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
  UdpNm_GetVersionInfo()
 **********************************************************************************************************************/
/*! \brief       Returns version information of this module
 *  \details     -
 *  \param[out]  versioninfo                Pointer to where to store the version information of this module
 *  \pre         -
 *  \note        Called from Application
 *  \config      UDPNM_VERSION_INFO_API == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150123
 **********************************************************************************************************************/
extern FUNC( void, UDPNM_CODE ) UdpNm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, UDPNM_APPL_VAR ) versioninfo);
# endif

# if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
  UdpNm_EnableCommunication()
 **********************************************************************************************************************/
/*! \brief       Enables NM message transmission control status
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Enabling of NM PDU transmission ability was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       CREQ-150129
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

/***********************************************************************************************************************
  UdpNm_DisableCommunication()
 **********************************************************************************************************************/
/*! \brief       Disables NM message transmission control status
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Disabling NM PDU transmission ability was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       CREQ-150128
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

/***********************************************************************************************************************
  UdpNm_InitMemory()
 **********************************************************************************************************************/
/*! \brief       Power-up memory initialization
 *  \details     Initializes component variables in *_INIT_* sections at power up.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Use this function in case these variables are not initialized by the startup code.
 *  \trace       DSGN-UdpNm22920
 **********************************************************************************************************************/
extern FUNC( void, UDPNM_CODE ) UdpNm_InitMemory( void );

# if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/***********************************************************************************************************************
  UdpNm_SetSleepReadyBit()
 **********************************************************************************************************************/
/*! \brief       Sets the NM Coordinator Sleep Ready Bit in the Control Bit Vector
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[in]   nmSleepReadyBit             Value written to ReadySleep Bit in CBV (Range: 0,1)
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Writing of Sleep Ready Bit was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-150136
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_SetSleepReadyBit( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                  CONST( boolean, AUTOMATIC ) nmSleepReadyBit );
# endif

# if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) || defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
/***********************************************************************************************************************
  UdpNm_Transmit()
 **********************************************************************************************************************/
/*! \brief       Triggers a spontaneous transmission of an NM message
 *  \details     -
 *  \param[in]   UdpNmTxPduId  Identifier of the PDU to be transmitted.
 *  \param[in]   PduInfoPtr    Parameter is ignored.
 *  \pre         -
 *  \return      E_OK                        Transmit request was accepted
 *               E_NOT_OK                    Transmit request was not accepted
 *  \note        Called from PduR
 *  \config      UDPNM_COM_USER_DATA_SUPPORT == STD_ON || UDPNM_PN_CALC_FEATURE_ENABLED == STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150130
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_Transmit( VAR( PduIdType, AUTOMATIC ) UdpNmTxPduId,
                                                          P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr);

/***********************************************************************************************************************
 *  UdpNm_CancelTransmit()
 **********************************************************************************************************************/
/*! \brief         No functionality provided
 *  \details       This function is only provided to avoid linker errors.
 *  \param[in]     UdpNmTxSduId           Parameter not used
 *  \return        E_OK                   Function call was successful
 *  \return        E_NOT_OK               Module was not initialized
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 *  \trace         DSGN-UdpNm22924
 **********************************************************************************************************************/
extern FUNC(Std_ReturnType, UDPNM_CODE) UdpNm_CancelTransmit( VAR( PduIdType, AUTOMATIC ) UdpNmTxSduId );

# endif

# define UDPNM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* UDPNM_H */

/*
 * \exclusivearea UDPNM_EXCLUSIVE_AREA_0
 * Protects the global Pn Cluster requests from being modified from RxIndication while copying to temporary buffer.
 * \length SHORT At max 7 bytes are copied within this exclusive area.
 * \usedin UdpNm_PnEiraCalculation, UdpNm_LocalMainFunction, UdpNm_SoAdIfRxIndication, UdpNm_RequestBusSynchronization
 * \exclude UdpNm_PnEiraCalculation, UdpNm_LocalMainFunction, UdpNm_SoAdIfRxIndication, UdpNm_RequestBusSynchronization
 * \protects UdpNm_PnClusterReqExtNew, UdpNm_PnClusterReqNew (read, modify, write)
 * \endexclusivearea
 *
 * \exclusivearea UDPNM_EXCLUSIVE_AREA_1
 * Protects the global TX message data from being modified while copying to the Sdu.
 * \length SHORT It is expected that only a few (8 - 64) bytes are copied within this exclusive area. But the worst case configuration length
 *               could reach up to 65535 bytes.
 * \usedin UdpNm_MainFunction_x, UdpNm_RequestBusSynchronization
 * \exclude UdpNm_SetUserData, UdpNm_SetSleepReadyBit, UdpNm_SoAdIfTriggerTransmit
 * \protects UdpNm_TxMessageData (read)
 * \endexclusivearea
 *
 * \exclusivearea UDPNM_EXCLUSIVE_AREA_2
 * Ensures that the global TX message buffer is not read while data is written to it.
 * \length SHORT It is expected that only a few (8 - 64) bytes are copied within this exclusive area. But the worst case configuration length
 *               could reach up to 65535 bytes.
 * \usedin UdpNm_SoAdIfTriggerTransmit
 * \exclude UdpNm_MainFunction_x, UdpNm_RequestBusSynchronization, UdpNm_SetSleepReadyBit, UdpNm_SetUserData
 * \protects UdpNm_TxMessageData (read)
 * \endexclusivearea
 *
 * \exclusivearea UDPNM_EXCLUSIVE_AREA_3
 * Ensures that the global TX message buffer is not read while data is written to it.
 * \length SHORT It is expected that only a few (8 - 64) bytes are copied within this exclusive area. But the worst case configuration length
 *               could reach up to 65535 bytes.
 * \usedin UdpNm_SetSleepReadyBit and UdpNm_SetUserData
 * \exclude UdpNm_MainFunction_x, UdpNm_RequestBusSynchronization, UdpNm_SoAdIfTriggerTransmit
 * \protects UdpNm_TxMessageData (write)
 * \endexclusivearea
 *
 * \exclusivearea UDPNM_EXCLUSIVE_AREA_4
 * Ensures that the global RX message buffer is not read while data is written to it.
 * \length SHORT It is expected that only a few (8 - 64) bytes are copied within this exclusive area. But the worst case configuration length
 *               could reach up to 65535 bytes.
 * \usedin UdpNm_SoAdIfRxIndication
 * \exclude UdpNm_GetUserData, UdpNm_GetPduData
 * \protects UdpNm_RxMessageData (write)
 * \endexclusivearea
 *
 * \exclusivearea UDPNM_EXCLUSIVE_AREA_5
 * Ensures that the global RX message buffer is not written while user data is read from it.
 * \length SHORT It is expected that only a few (8 - 64) bytes are copied within this exclusive area. But the worst case configuration length
 *               could reach up to 65535 bytes.
 * \usedin UdpNm_GetUserData, UdpNm_GetPduData
 * \exclude UdpNm_SoAdIfRxIndication
 * \protects UdpNm_RxMessageData (read)
 * \endexclusivearea
 *
 * \exclusivearea UDPNM_EXCLUSIVE_AREA_6
 * Ensures that the MsgTimeoutTimer is not written while data is modified
 * \length SHORT One rmw of the variable UdpNm_MsgTimeoutTimer is done.
 * \usedin UdpNm_MainFunction_x
 * \exclude UdpNm_RequestBusSynchronization
 * \protects UdpNm_MsgTimeoutTimer
 * \endexclusivearea

 */
/**********************************************************************************************************************
 *  END OF FILE: UdpNm.h
 *********************************************************************************************************************/
