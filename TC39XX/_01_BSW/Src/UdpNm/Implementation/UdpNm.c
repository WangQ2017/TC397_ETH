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
 /**        \file  UdpNm.c
 *         \brief  AUTOSAR Udp Network Management
 *
 *       \details  Source of AUTOSAR Udp Network Management
 *                 AUTOSAR Release 4.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define UDPNM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "UdpNm.h"                                                        /* Include UdpNm Network Management header */
#include "UdpNm_Cbk.h"                                                           /* Include UdpNm NM callback header */
#include "Nm_Cbk.h"                                                          /* Include NM Interface callback header */
#include "SoAd.h"                                                                  /* Include UdpNm Interface header */
#if ( UDPNM_DEV_ERROR_REPORT == STD_ON ) || ( UDPNM_RUNTIME_ERROR_REPORT == STD_ON )   /* COV_DEV_ERROR_DETECT TX tf */
# include "Det.h"                                                                /* Include Development Error Tracer */
#endif
#include "SchM_UdpNm.h"                                            /* Include Scheduler Module for Critical Sections */
#if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) || defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
# include "PduR_UdpNm.h"                                                           /* PduR Callback Header for UdpNm */
#endif

#if ( UDPNM_CONFIGURATION_VARIANT == UDPNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE ) || \
    ( UDPNM_POSTBUILD_VARIANT_SUPPORT == STD_ON )
# include "EcuM_Error.h"                                                                /* Include EcuM Error header */
#endif

#if ( UDPNM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
# include "Rtm.h"                                                                    /* Include Run Time Measurement */
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information check */
#if ( (UDPNM_SW_MAJOR_VERSION != 6u) || (UDPNM_SW_MINOR_VERSION != 0u) || (UDPNM_SW_PATCH_VERSION != 0u) )
# error "Vendor specific version numbers of UdpNm.c and UdpNm.h are inconsistent"
#endif

#if ( (UDPNM_CBK_MAJOR_VERSION != 6u) || (UDPNM_CBK_MINOR_VERSION != 0u) || (UDPNM_CBK_PATCH_VERSION != 0u) )
# error "Vendor specific version numbers of UdpNm.c and UdpNm_Cbk.h are inconsistent"
#endif
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
/*! Definition of channel parameter for local functions. */
/* Local functions do not use a channel parameter in single channel configurations. */
#if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
# define UDPNM_CHANNEL_TYPE_ONLY                    void
# define UDPNM_CHANNEL_TYPE_FIRST
# define UDPNM_CHANNEL_PARA_ONLY
# define UDPNM_CHANNEL_PARA_FIRST
#else
# define UDPNM_CHANNEL_TYPE_ONLY                    CONST( NetworkHandleType, AUTOMATIC ) channel
# define UDPNM_CHANNEL_TYPE_FIRST                   CONST( NetworkHandleType, AUTOMATIC ) channel,
# define UDPNM_CHANNEL_PARA_ONLY                    UDPNM_CHANNEL_IDX
# define UDPNM_CHANNEL_PARA_FIRST                   UDPNM_CHANNEL_IDX,
#endif

#if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
# define UDPNM_CHANNEL_IDX                          ((NetworkHandleType)0u)
#else
# define UDPNM_CHANNEL_IDX                          (channel)
#endif
#define UDPNM_NMTOSYSTEM_CHANNEL_IND                (UdpNm_GetChannelIdOfChannelConfig(UDPNM_CHANNEL_IDX))


/* Enumeration type for Communication Control (optimized) */
/*! The application has no communication need and is ready to sleep. */
#define COMM_READY_SLEEP                            ((uint8)0x00u)
/*! The application has communication need. */
#define COMM_NORMAL_OPERATION                       ((uint8)0x01u)

/* Enumeration type for Message Transmission Control (optimized) */
/*! Message Transmission Ability is disabled/enabled */
#define MSG_TX_DISABLED                             ((uint8)0x00u)
#define MSG_TX_ENABLED                              ((uint8)0x01u)

/*! Mask to check if the Repeat Message Bit is set or reset */
#define UDPNM_REPEAT_MSG_BIT_MASK                   ((uint8)0x01u)
#define UDPNM_REPEAT_MSG_BIT_INV_MASK               ((uint8)0xFEu)

/*! Mask to check if the Active Wakeup Bit is set or reset */
#define UDPNM_ACT_WU_BIT_MASK                       ((uint8)0x10u)
#define UDPNM_ACT_WU_BIT_INV_MASK                   ((uint8)0xEFu)

/*! Mask to check if the Cluster Request Bit is set */
#define UDPNM_CRI_BIT_MASK                          ((uint8)0x40u)

/*! UdpNm Instance ID */
#define UDPNM_INSTANCE_ID                           ((uint8)0x00u)

/*! Mask to check if asynchronous transmission is requested */
#define UDPNM_NO_TRANSMIT_REQUEST                   ((uint8)0x00u)
#define UDPNM_TRANSMIT_REQUEST                      ((uint8)0x02u)

/*! Number of system channels */
#define UDPNM_CFG_NUMBER_OF_SYS_CHANNELS            (UdpNm_GetSizeOfSysToNmChInd())

/*! Macros for communication requests */
#define UDPNM_NO_RESTART                            ((uint8)0u)
#define UDPNM_PASSIVE_RESTART                       ((uint8)1u)
#define UDPNM_ACTIVE_RESTART                        ((uint8)2u)

/*! Macro for Coordinator Sleep Handling */
#define UDPNM_COORD_ASLEEP_OR_NOT_READY_TO_SLEEP    ((uint8)0x00u)

/*! Macro for Immediate Restart Failed Message Timer Value */
#define UDPNM_IMMEDIATE_RESTART_FAILED_MSG_TMR_VAL  ((uint8)0x02u)

#if !defined ( UDPNM_LOCAL ) /* COV_UDPNM_REDEFINEABLE */
# define UDPNM_LOCAL static
#endif

#if !defined ( UDPNM_LOCAL_INLINE ) /* COV_UDPNM_REDEFINEABLE */
# define UDPNM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/


/* Macros for Runtime Measurement Support */
#if ( UDPNM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )

/* PRQA S 0342 3 */ /* MD_MSR_Rule20.10_0342 */
# define UdpNm_Rtm_Start(measurement) { \
                                        Rtm_Start(RtmConf_##measurement); \
                                      }
/* PRQA S 0342 3 */ /* MD_MSR_Rule20.10_0342 */
# define UdpNm_Rtm_Stop(measurement)  { \
                                        Rtm_Stop(RtmConf_##measurement); \
                                      }
#else
# define UdpNm_Rtm_Start(measurement) 
# define UdpNm_Rtm_Stop(measurement)
#endif


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/* ----------- Local Data definitions with unspecified size and frequent access ----------- */
#define UDPNM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( UDPNM_USE_INIT_POINTER == STD_ON )
/*! Pointer to the current configuration */
UDPNM_LOCAL P2CONST( UdpNm_ConfigType, UDPNM_VAR_ZERO_INIT, UDPNM_INIT_DATA ) UdpNm_ConfigDataPtr = NULL_PTR;
#endif

#define UDPNM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define UDPNM_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* UdpNm NM version (BCD coded). */
CONST(uint8, UDPNM_CONST) UdpNm_MainVersion     = (uint8)UDPNM_SW_MAJOR_VERSION;
CONST(uint8, UDPNM_CONST) UdpNm_SubVersion      = (uint8)UDPNM_SW_MINOR_VERSION;
CONST(uint8, UDPNM_CONST) UdpNm_ReleaseVersion  = (uint8)UDPNM_SW_PATCH_VERSION;

#define UDPNM_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define UDPNM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_DetermineDynamicPnInfoLength
**********************************************************************************************************************/
/*! \brief       Determine maximum number of PnInfo Bytes depending on received PDU Length.
 *  \details     -
 *  \pre         -
 *  \param[in]   PduInfoPtr       - Pointer to UDP PDU related data containing DLC and pointer to UDP SDU buffer.
 *  \note        Called by UdpNm_RxIndication
 *  \return      Adjusted (shortened) PnInfoLength
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( UdpNm_SizeOfPnInfoByteConfigType, UDPNM_CODE ) UdpNm_DetermineDynamicPnInfoLength( P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR )PduInfoPtr );
#endif

#if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_PnEraCalculation()
**********************************************************************************************************************/
/*! \brief       Process received Partial Networking ERA information
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *  \trace       DSGN-UdpNm22937
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_PnEraCalculation( UDPNM_CHANNEL_TYPE_ONLY );
#endif

#if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_PnEiraCalculation
**********************************************************************************************************************/
/*! \brief       Process received Partial Networking EIRA information
 *  \details     -
 *  \pre         -
 *  \param[in]   nmChannelHandle  - Local channel handle
 *  \context     TASK
 *  \note        Called after last UdpNm_MainFunction_x
 *  \trace       DSGN-UdpNm22938
 *********************************************************************************************************************/
UDPNM_LOCAL FUNC( void, UDPNM_CODE ) UdpNm_PnEiraCalculation( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
#endif

#if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_PnFilterHandling()
**********************************************************************************************************************/
/*! \brief       Process Partial Networking information
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   PduInfoPtr       - Pointer to UdpNm PDU related data containing data length and pointer to UdpNm SDU buffer.
 *  \context     TASK|ISR1|ISR2
 *  \note        Called by UdpNm_SoAdIfRxIndication
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( boolean, UDPNM_CODE ) UdpNm_PnFilterHandling( UDPNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr );
#endif

#if ( ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_USER_DATA_ENABLED == STD_ON ) \
        || ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON ) )
/**********************************************************************************************************************
  UdpNm_CopyRxMessageData()
**********************************************************************************************************************/
/*! \brief       Process Data received in last NM message
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   PduInfoPtr       - Pointer to UdpNm PDU related data containing data length and pointer to UdpNm SDU buffer.
 *  \context     TASK|ISR1|ISR2
 *  \note        Called by UdpNm_SoAdIfRxIndication
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CopyRxMessageData( UDPNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr );
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/**********************************************************************************************************************
  UdpNm_CommunicationControlHandling()
**********************************************************************************************************************/
/*! \brief       Process Communication Control requests
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *  \trace       DSGN-UdpNm22921
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CommunicationControlHandling( UDPNM_CHANNEL_TYPE_ONLY );
#endif

/**********************************************************************************************************************
  UdpNm_MainRxTxConfHandling()
**********************************************************************************************************************/
/*! \brief       Process Tx Confirmations and Rx Indications
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_MainRxTxConfHandling( UDPNM_CHANNEL_TYPE_ONLY );


#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/**********************************************************************************************************************
  UdpNm_RepeatMessageIndHandling()
**********************************************************************************************************************/
/*! \brief       Process Repeat Message Indications from UdpNm_RepeatMessageRequest
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_RepeatMessageIndHandling( UDPNM_CHANNEL_TYPE_ONLY );
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
  UdpNm_BusCommunicationHandling()
**********************************************************************************************************************/
/*! \brief       Process Request / Release of Communication
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   commState        - Current communication request state
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_BusCommunicationHandling( UDPNM_CHANNEL_TYPE_FIRST CONST( uint8, AUTOMATIC ) commState );
#endif

/**********************************************************************************************************************
  UdpNm_TimeoutTimerHandling()
**********************************************************************************************************************/
/*! \brief       Process Timeout Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_TimeoutTimerHandling( UDPNM_CHANNEL_TYPE_ONLY );

/**********************************************************************************************************************
  UdpNm_RepeatMessageTimerHandling()
**********************************************************************************************************************/
/*! \brief       Process Repeat Message Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_RepeatMessageTimerHandling( UDPNM_CHANNEL_TYPE_ONLY );

/**********************************************************************************************************************
  UdpNm_WaitBusSleepTimerHandling()
**********************************************************************************************************************/
/*! \brief       Process Wait Bus Sleep Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_WaitBusSleepTimerHandling( UDPNM_CHANNEL_TYPE_ONLY );

#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_RemoteSleepTimerHandling()
**********************************************************************************************************************/
/*! \brief       Process Remote Sleep Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_RemoteSleepTimerHandling( UDPNM_CHANNEL_TYPE_ONLY );
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
  UdpNm_MessageTimerHandling()
**********************************************************************************************************************/
/*! \brief       Process Message Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_MessageTimerHandling( UDPNM_CHANNEL_TYPE_ONLY );

/**********************************************************************************************************************
  UdpNm_MessageTimeoutTimerHandling()
**********************************************************************************************************************/
/*! \brief       Process Message Timeout Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Mainfunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_MessageTimeoutTimerHandling( UDPNM_CHANNEL_TYPE_ONLY );
#endif

#if ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON )
/**********************************************************************************************************************
  UdpNm_CarWakeupIndication()
**********************************************************************************************************************/
/*! \brief       Process Car Wakeup Indication
 *  \details     Evaluates the Car Wakeup Bit in the last received Nm message.
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   PduInfoPtr       - Pointer to received NM Pdu
 *  \context     TASK
 *  \note        Called by UdpNm_SoAdIfRxIndication
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CarWakeupIndication( UDPNM_CHANNEL_TYPE_FIRST  P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr);
#endif

#if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/**********************************************************************************************************************
  UdpNm_CoordReadyToSleepHandling()
**********************************************************************************************************************/
/*! \brief       Process CoordinatorReadyToSleep Indication
 *  \details     Evaluates the Sleep Ready Bit in the last received Nm message.
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   controlBitVector - The CBV of the previously received NM message
 *  \context     TASK
 *  \note        Called by UdpNm_SoAdIfRxIndication
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CoordReadyToSleepHandling( UDPNM_CHANNEL_TYPE_FIRST  CONST( uint8, AUTOMATIC ) controlBitVector );
#endif

/**********************************************************************************************************************
  UdpNm_TransitionToRepeatMessage()
**********************************************************************************************************************/
/*! \brief       Process transition to Repeat Message state
 *  \details     Process transition from any other state to Repeat Message state
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_StateTransition
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_TransitionToRepeatMessage( UDPNM_CHANNEL_TYPE_ONLY );

/**********************************************************************************************************************
  UdpNm_TransitionToNetworkMode()
**********************************************************************************************************************/
/*! \brief       Process transition to Network mode
 *  \details     Process transition from BusSleep / PrepareBusSleep to Network Mode
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   lastNmState      - last NM state before transitioning to Network Mode
 *  \context     TASK
 *  \note        Called by UdpNm_StateTransition
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_TransitionToNetworkMode( UDPNM_CHANNEL_TYPE_FIRST  CONST(uint8, AUTOMATIC) lastNmState );

#if defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
/**********************************************************************************************************************
  UdpNm_PnLocal_Init
**********************************************************************************************************************/
/*! \brief       Initialization of Partial Networking relevant variables
 *  \details     This function initializes the UdpNm's Partial Networking related variables
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Init
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_PnLocal_Init( void );
#endif

/**********************************************************************************************************************
  UdpNm_LocalInit()
**********************************************************************************************************************/
/*! \brief       Initialization of the Generic Network Management
 *               and its internal state machine for one channel.
 *  \details     By default the UdpNm starts in the Bus-Sleep Mode.
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_Init
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_LocalInit( UDPNM_CHANNEL_TYPE_ONLY );

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
/**********************************************************************************************************************
  UdpNm_TriggerTransmission()
**********************************************************************************************************************/
/*! \brief       Triggers NM message transmission
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by UdpNm_RequestBusSynchronization, UdpNm_MainFunction
 *  \return      E_OK             - Successful transmission of Nm Message
 *               E_NOT_OK         - Transmit request is not accepted by SoAd (i.e. SoAd_IfTransmit returned E_NOT_OK )
 *********************************************************************************************************************/
UDPNM_LOCAL FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_TriggerTransmission( UDPNM_CHANNEL_TYPE_ONLY );
#endif

/**********************************************************************************************************************
  UdpNm_StateTransition()
**********************************************************************************************************************/
/*! \brief       Perform a transition to another state of the state machine
 *  \details     CBV is only accessed on Task level -> no interrupt locks required
 *               Access to RepeatMsgBitIndFlag does not require interrupt locks
 *  \pre         -
 *  \param[in]   nextNmState      - Next state in the state machine
 *  \context     TASK
 *  \note        Called by UdpNm_MainFunction_x
 *********************************************************************************************************************/
UDPNM_LOCAL FUNC( void, UDPNM_CODE ) UdpNm_StateTransition( UDPNM_CHANNEL_TYPE_FIRST  CONST( Nm_StateType, AUTOMATIC ) nextNmState );

/**********************************************************************************************************************
  UdpNm_LocalMainFunction()
**********************************************************************************************************************/
/*! \brief       Local Main function of the UdpNm which processes the NM algorithm. This function is responsible to
 *               handle one UdpNm instance.
 *  \details     -
 *  \pre         NM is initialized
 *  \config      -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by UdpNm_LocalMainFunctionSelector
 *********************************************************************************************************************/
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_LocalMainFunction( CONST( NetworkHandleType, AUTOMATIC ) channel );

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/
#if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_DetermineDynamicPnInfoLength
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
UDPNM_LOCAL_INLINE FUNC( UdpNm_SizeOfPnInfoByteConfigType, UDPNM_CODE ) UdpNm_DetermineDynamicPnInfoLength( P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR )PduInfoPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  UdpNm_SizeOfPnInfoByteConfigType adjustedInfoLength;

  /* #10 If PduInfoPointer DLC is less than the configured PN Info length
   *      Cut off all overlapping PnInfoBytes
   *     otherwise all PN Bytes shall be processed
   *     return the adjusted PnInfoLength value
   */
  if( (PduInfoPtr->SduLength ) < ((PduLengthType)UdpNm_GetPnInfoOffset() + UdpNm_GetSizeOfPnInfoByteConfig()) ) /* COV_UDPNM_PN_INFO_LENGTH */
  {
    adjustedInfoLength = (UdpNm_SizeOfPnInfoByteConfigType)((PduLengthType)(PduInfoPtr->SduLength - UdpNm_GetPnInfoOffset()));
  }
  else
  {
    adjustedInfoLength = UdpNm_GetSizeOfPnInfoByteConfig();
  }

  return adjustedInfoLength;
}
#endif

#if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_PnEiraCalculation()
**********************************************************************************************************************/
/*!
 *
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
/* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
UDPNM_LOCAL FUNC( void, UDPNM_CODE ) UdpNm_PnEiraCalculation( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  NetworkHandleType channel;
# endif
  UdpNm_SizeOfPnInfoByteConfigType pnClusterRequestByte;
  uint8_least pnClusterRequestBits;
  UdpNm_PnClusterResetTimerIterType pnClusterResetTimerIndex;
  UdpNm_PnClusterReqNewType pnClusterRequestNew;
  boolean pnClusterRequestChanged;
  PduInfoType nmPnInfo;

  /*
    * #10 If PnEiraCalcEnabled is enabled and PnEnabled is enabled on at least one channel in variant
    */
  
# if ( UDPNM_ISDEF_PNENABLEDINVARIANT == STD_OFF )
  if (UdpNm_IsPnEnabledInVariant()) /* PRQA S 2741 */ /* MD_UDPNM_Rule14.3 */ /*lint !e506 */ /* COV_UDPNM_PNENABLEDINVARIANT */
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
# if ( UDPNM_ISDEF_PNEIRACALCENABLED == STD_OFF )
    if ( UdpNm_IsPnEiraCalcEnabled() ) /* COV_UDPNM_PN_EIRA_CALC */
# endif
    {
      /* #20 Iterate over all Partial Networking Cluster Bytes
        *      If received Nm message contains new or repeated requests
        *       Copy PNC requests to local buffer to avoid long interrupt locks
        *       Clear request buffer to detect changes in next received NM message
        *       If received PNC Byte contains new EIRA requests.
        *        Update local EIRA requests
        *       Iterate over all PNC Bits in the current PNC Byte (and corresponding PnResetTimer)
        *        If PNC Bit is set in received message
        *         Restart PnClusterResetTimer of the requested PNC with PnResetTime
        *          If PnClusterResetTimer of PNC Bit in PNC Byte has not elapsed
        *           Decrement PnClusterResetTimer by one
        *           If PnClusterResetTimer has elapsed
        *            Reset the local PNC request
        */

      pnClusterRequestChanged = FALSE;

# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
      channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# else
      UDPNM_DUMMY_STATEMENT_CONST( nmChannelHandle ); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

      for( pnClusterRequestByte = 0u; pnClusterRequestByte < UdpNm_GetSizeOfPnInfoByteConfig(); pnClusterRequestByte++ )
      {
        pnClusterRequestNew = 0u;
        if( UdpNm_GetPnClusterReqNew(pnClusterRequestByte) != 0u )
        {
          SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_0();
          pnClusterRequestNew = UdpNm_GetPnClusterReqNew(pnClusterRequestByte);
          UdpNm_SetPnClusterReqNew(pnClusterRequestByte, 0u); /* SBSW_UDPNM_CSL02 */
          SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_0();

          pnClusterRequestBits = (uint8)(UdpNm_GetPnClusterReq(pnClusterRequestByte) | pnClusterRequestNew);

          if( pnClusterRequestBits != UdpNm_GetPnClusterReq(pnClusterRequestByte) )
          {
            pnClusterRequestChanged = TRUE;
            UdpNm_SetPnClusterReq(pnClusterRequestByte, (UdpNm_PnClusterReqType)pnClusterRequestBits); /* SBSW_UDPNM_CSL02 */
          }
        }

        pnClusterRequestBits = 0u;
        for( pnClusterResetTimerIndex = UdpNm_GetPnClusterResetTimerStartIdxOfPnInfoByteConfig(pnClusterRequestByte);
              pnClusterResetTimerIndex < UdpNm_GetPnClusterResetTimerEndIdxOfPnInfoByteConfig(pnClusterRequestByte);
              pnClusterResetTimerIndex++ )
        {
          if( (pnClusterRequestNew & (UdpNm_PnClusterReqNewType)(1u << pnClusterRequestBits)) != 0u )
          {
            UdpNm_SetPnClusterResetTimer(pnClusterResetTimerIndex, UdpNm_GetPnResetTimeOfPbChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_CSL03 */
          }
          if( UdpNm_GetPnClusterResetTimer(pnClusterResetTimerIndex) != 0u )
          {
            UdpNm_DecPnClusterResetTimer(pnClusterResetTimerIndex); /* SBSW_UDPNM_CSL03 */
            if( UdpNm_GetPnClusterResetTimer(pnClusterResetTimerIndex) == 0u )
            {
              pnClusterRequestChanged = TRUE;
              UdpNm_SetPnClusterReq(pnClusterRequestByte, (UdpNm_PnClusterReqType)  /* SBSW_UDPNM_CSL02 */
                                    (UdpNm_GetPnClusterReq(pnClusterRequestByte) & (UdpNm_PnClusterReqType)(~(1u << pnClusterRequestBits))));
            }
          }
          pnClusterRequestBits++;
        }
      }
      /* #30 If an PNC EIRA request has changed, indicate this to the ComM (via PduR -> Com <- ComM)
        *      Pass the changed PnClusterRequest buffer to the Com by calling PduR_UdpNmRxIndication
        */
      if( pnClusterRequestChanged == TRUE )
      {
        nmPnInfo.SduDataPtr = UdpNm_GetAddrPnClusterReq(0u);
        nmPnInfo.SduLength = UdpNm_GetPnInfoLength();
        PduR_UdpNmRxIndication( UdpNm_GetPnEiraRxPduId(), &nmPnInfo ); /* SBSW_UDPNM_POINTER_PARAM */
      }
    }
  }
}
#endif /* UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON */


#if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_PnEraCalculation()
**********************************************************************************************************************/
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
/* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_PnEraCalculation( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  UdpNm_PbPncClusterConfigExtIterType pnClusterRequestByte;
  uint8_least pnClusterRequestBits;
  UdpNm_PnClusterResetTimerExtIterType pnClusterResetTimerExtIndex;
  UdpNm_PnClusterReqExtNewType pnClusterRequestExtNew;
  boolean pnClusterRequestChanged;
  PduInfoType nmPnInfo;

  /* ----- Implementation ----------------------------------------------- */
  if ( UdpNm_IsPnEnabledOfPbChannelConfig(UDPNM_CHANNEL_IDX) && UdpNm_IsPnEraCalcEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_PN_ERA_CALC */
  {
    /* #10 Iterate over all Partial Networking Cluster Bytes related to the current channel
     *      If received Nm message contains new or repeated requests
     *       Copy PNC requests to local buffer to avoid long interrupt locks
     *       Clear request buffer to detect changes in next received NM message
     *       If received PNC Byte contains new ERA requests.
     *        Update local ERA requests
     *       Iterate over all PNC Bits in the current PNC Byte (and corresponding PnResetTimer)
     *        If PNC Bit is set in last received message
     *         Restart PnClusterResetTimerExt of the requested PNC with PnResetTime
     *          If PnClusterResetTimerExt of PNC Bit in PNC Byte has not elapsed
     *           Decrement PnClusterResetTimerExt by one
     *           If PnClusterResetTimerExt has elapsed
     *            Reset the local PNC request
     */

    pnClusterRequestChanged = FALSE;
    for( pnClusterRequestByte = UdpNm_GetPbPncClusterConfigExtStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
          pnClusterRequestByte < UdpNm_GetPbPncClusterConfigExtEndIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
          pnClusterRequestByte++ )
    {
      pnClusterRequestExtNew = 0u;
      /* Check for new / repeated cluster requests */
      if( UdpNm_GetPnClusterReqExtNew(pnClusterRequestByte) != 0u )
      {
        SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_0();
        pnClusterRequestExtNew = UdpNm_GetPnClusterReqExtNew(pnClusterRequestByte);
        UdpNm_SetPnClusterReqExtNew(pnClusterRequestByte, 0u); /* SBSW_UDPNM_CSL02 */
        SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_0();

        pnClusterRequestBits = (uint8)(UdpNm_GetPnClusterReqExt(pnClusterRequestByte) | pnClusterRequestExtNew);
        if( pnClusterRequestBits != UdpNm_GetPnClusterReqExt(pnClusterRequestByte))
        {
          pnClusterRequestChanged = TRUE;
          UdpNm_SetPnClusterReqExt(pnClusterRequestByte, (UdpNm_PnClusterReqExtType)pnClusterRequestBits); /* SBSW_UDPNM_CSL02 */
        }
      }

      pnClusterRequestBits = 0u;
      for( pnClusterResetTimerExtIndex = UdpNm_GetPnClusterResetTimerExtStartIdxOfPbPncClusterConfigExt(pnClusterRequestByte);
            pnClusterResetTimerExtIndex < UdpNm_GetPnClusterResetTimerExtEndIdxOfPbPncClusterConfigExt(pnClusterRequestByte);
            pnClusterResetTimerExtIndex++ )
      {
        if( (pnClusterRequestExtNew & (UdpNm_PnClusterReqExtNewType)(1u << pnClusterRequestBits)) != 0u )
        {
          UdpNm_SetPnClusterResetTimerExt(pnClusterResetTimerExtIndex, UdpNm_GetPnResetTimeOfPbChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_CSL03 */
        }
        if( UdpNm_GetPnClusterResetTimerExt(pnClusterResetTimerExtIndex) != 0u )
        {
          UdpNm_DecPnClusterResetTimerExt(pnClusterResetTimerExtIndex); /* SBSW_UDPNM_CSL03 */
          if( UdpNm_GetPnClusterResetTimerExt(pnClusterResetTimerExtIndex) == 0u )
          {
            pnClusterRequestChanged = TRUE;
            /* Clear bit by masking with inverted bit */
            UdpNm_SetPnClusterReqExt(pnClusterRequestByte, (UdpNm_PnClusterReqExtType) /* SBSW_UDPNM_CSL02 */
                                  (UdpNm_GetPnClusterReqExt(pnClusterRequestByte) & (UdpNm_PnClusterReqExtType)(~(1u << pnClusterRequestBits))));
          }
        }
        pnClusterRequestBits++;
      }
    }
    /* #20 If an PNC ERA request has changed, indicate this to the ComM (via PduR -> Com <- ComM)
      *      Pass the changed PnClusterRequestExt buffer to the Com by calling PduR_UdpNmRxIndication
      */
    if( pnClusterRequestChanged == TRUE )
    {
      nmPnInfo.SduDataPtr = UdpNm_GetAddrPnClusterReqExt(UdpNm_GetPbPncClusterConfigExtStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX));
      nmPnInfo.SduLength = UdpNm_GetPnInfoLength();
      PduR_UdpNmRxIndication( UdpNm_GetPnEraRxPduIdOfChannelConfig(UDPNM_CHANNEL_IDX), &nmPnInfo ); /* SBSW_UDPNM_POINTER_PARAM */
    }
    UDPNM_DUMMY_STATEMENT_CONST(UDPNM_CHANNEL_IDX); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
}
#endif /* UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON */


#if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_PnFilterHandling()
**********************************************************************************************************************/
/*!
 *
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
UDPNM_LOCAL_INLINE FUNC( boolean, UDPNM_CODE ) UdpNm_PnFilterHandling( UDPNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr )
{
  boolean                            msgRelevant = FALSE;
  UdpNm_SizeOfPnInfoByteConfigType   rxMsgBytePos;
  uint8                              reqCluster;
#  if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  UdpNm_SizeOfPnClusterReqExtNewType pnClusterRequestIndex;
#  endif

  /* #10 If Partial Networking is enabled */
  /* #20 If configuration parameter <Pdu Cbv Position> is set to Byte 0 or Byte 1 */
  if( UdpNm_IsPnEnabledOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_PN_ENABLED */
  {
    if ( ( UdpNm_GetPduCbvPositionOfChannelConfig(UDPNM_CHANNEL_IDX) != UDPNM_PDU_OFF )
      && ( PduInfoPtr->SduLength > UdpNm_GetPduCbvPositionOfChannelConfig(UDPNM_CHANNEL_IDX) ) ) /* COV_UDPNM_CHECK_CBVPOSITION */
    {
      /* #200 If CRI bit is set in received CBV and at least one PNC byte is included in the received message
       *       Iterate over all received Pn Info Bytes
       *        Store the received Pn Requests filtered by the configured Pn Filter Mask
       *        If at least one request matches the filter
       *         If <Pn Eira Calc Enabled> is configured
       *          Store the filtered EIRA request for further processing in UdpNm_MainFunction
       *         If <Pn Era Calc Enabled> is configured
       *          Store the filtered ERA request for further processing in UdpNm_MainFunction
       */
      if( (PduInfoPtr->SduLength > UdpNm_GetPnInfoOffset()) && (((uint8)(PduInfoPtr->SduDataPtr[UdpNm_GetPduCbvPositionOfChannelConfig(UDPNM_CHANNEL_IDX)]) & UDPNM_CRI_BIT_MASK) != 0u ) )
      {
        /* PN is enabled, PN bit is true => apply filter algorithm: */
        /* copy the requests and apply the PN filter mask: */
        SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_0();

        for (rxMsgBytePos = 0u; rxMsgBytePos < UdpNm_DetermineDynamicPnInfoLength( PduInfoPtr ); rxMsgBytePos++) /* SBSW_UDPNM_LOCALFUNCTION_CALL */
        {
          reqCluster = (uint8)(PduInfoPtr->SduDataPtr[rxMsgBytePos + UdpNm_GetPnInfoOffset()] & UdpNm_GetPnFilterMaskOfPnInfoByteConfig(rxMsgBytePos));
          if( reqCluster != 0u )
          {
            msgRelevant = TRUE;
# if defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
#  if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )

#   if ( UDPNM_ISDEF_PNEIRACALCENABLED == STD_OFF )
            if( UdpNm_IsPnEiraCalcEnabled() ) /* COV_UDPNM_PN_EIRA_CALC */
#   endif
            {
#   if( UDPNM_DEV_ERROR_DETECT == STD_ON )
              /* Runtime Check that UdpNm_SetPnClusterReqNew array is always written within its defined bounds. */
              if( rxMsgBytePos < UdpNm_GetSizeOfPnClusterReqNew() ) /* COV_UDPNM_RUNTIME_CHECK */
#   endif
              {
                UdpNm_SetPnClusterReqNew(rxMsgBytePos, (UdpNm_PnClusterReqNewType)(UdpNm_GetPnClusterReqNew(rxMsgBytePos) | reqCluster)); /* SBSW_UDPNM_DYN_PNINFOLENGTH */
              }
            }
#  endif
#  if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )

            if( UdpNm_IsPnEraCalcEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_PN_ERA_CALC */
            {
              pnClusterRequestIndex = (UdpNm_PnClusterReqExtNewType)(UdpNm_GetPbPncClusterConfigExtStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX) + rxMsgBytePos);
#   if( UDPNM_DEV_ERROR_DETECT == STD_ON )
              /* Runtime Check that UdpNm_SetPnClusterReqExtNew array is always written within its defined bounds. */
              if( pnClusterRequestIndex < UdpNm_GetSizeOfPnClusterReqExtNew() ) /* COV_UDPNM_RUNTIME_CHECK */
#   endif
              {
                UdpNm_SetPnClusterReqExtNew(pnClusterRequestIndex, (UdpNm_PnClusterReqExtNewType)((UdpNm_GetPnClusterReqExtNew(pnClusterRequestIndex)) | reqCluster)); /* SBSW_UDPNM_PNCLUSTERREQEXTNEW */
              }
            }
#  endif
# else
            break;
# endif
          }
        }
        SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_0();
      }
    } /* if ( (UdpNm_GetPduCbvPositionOfChannelConfig(UDPNM_CHANNEL_IDX) != UDPNM_PDU_OFF) && ... ) */
  } /* if ( UdpNm_IsPnEnabledOfPbChannelConfig ) */
  else
  {
    msgRelevant = TRUE;
  }

  return msgRelevant;
}
#endif

#if ( ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_USER_DATA_ENABLED == STD_ON ) \
        || ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON ) )
/**********************************************************************************************************************
  UdpNm_CopyRxMessageData()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CopyRxMessageData( UDPNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr )
{
  UdpNm_RxMessageDataIterType  rxMessageDataByte;
  UdpNm_RxMessageDataIterType  rxMessageDataBytePos;


  /* #10 Copy received NM message data to the Rx Message Data buffer */
  SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_4();

  rxMessageDataByte = 0u;
  for( rxMessageDataBytePos = UdpNm_GetRxMessageDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
       rxMessageDataBytePos < UdpNm_GetRxMessageDataEndIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
       rxMessageDataBytePos++ )
  {
    if ( rxMessageDataByte >= PduInfoPtr->SduLength )
    {
      UdpNm_SetRxMessageData(rxMessageDataBytePos, 0u); /* SBSW_UDPNM_CSL03 */
    }
    else
    {
      UdpNm_SetRxMessageData(rxMessageDataBytePos, (UdpNm_RxMessageDataType)(PduInfoPtr->SduDataPtr[rxMessageDataByte]) ); /* SBSW_UDPNM_CSL03 */
    }
    rxMessageDataByte++;
  }

  SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_4();
}
#endif


#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_CommunicationControlHandling
 **********************************************************************************************************************/
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CommunicationControlHandling( UDPNM_CHANNEL_TYPE_ONLY )
{

  uint8 txControlStateReq;
  /* #10 If communication allowed request has changed
   *      Update TxControlState
   */
  txControlStateReq = UdpNm_GetTxControlStateRequest(UDPNM_CHANNEL_IDX);
  if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) != txControlStateReq )
  {
    UdpNm_SetTxControlState(UDPNM_CHANNEL_IDX, (UdpNm_TxControlStateType)txControlStateReq); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    /* #100 If communication is not allowed
     *       Stop Nm Timeout Timer.
     *       Reset Remote Sleep Timer and state.
     *       Call Nm_RemoteSleepCancellation if it was indicated before.
     *       Stop Nm Message Timer
     */
    if( txControlStateReq == MSG_TX_DISABLED )
    {
      UdpNm_SetTimeoutTimer(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      /* ESCAN00109020: If RemoteSleep was already indicated, it has to be cancelled. */
      if ( UdpNm_IsRemoteSleepIndState(UDPNM_CHANNEL_IDX) )
      {
        UdpNm_SetRemoteSleepIndState(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        Nm_RemoteSleepCancellation( UDPNM_NMTOSYSTEM_CHANNEL_IND );
      }
      UdpNm_SetRemoteSleepTimer(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# endif
      UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    }
    /* #110 otherwise start Nm Timeout Timer
     *       In state NormalOperation: Start RemoteSleepIndicationTimer.
     *       In state NormalOperation or RepeatMessage: Start MessageTimer
     */
    else
    {
      UdpNm_SetTimeoutTimer(UDPNM_CHANNEL_IDX, (UdpNm_TimeoutTimerType)((UdpNm_TimeoutTimerType)UdpNm_GetTimeoutTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION )
      {
        UdpNm_SetRemoteSleepTimer(UDPNM_CHANNEL_IDX, (UdpNm_RemoteSleepTimerType)((UdpNm_RemoteSleepTimerType)UdpNm_GetRemoteSleepIndTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }
# endif
      if( ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION ) ||
          ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_REPEAT_MESSAGE ) )
      {
        UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimerType)((UdpNm_MsgTimerType)UdpNm_GetMsgCycleOffsetOfPbChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }
  }
}
#endif /* #if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON ) */

/***********************************************************************************************************************
 *  UdpNm_MainRxTxConfHandling
 **********************************************************************************************************************/
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
 */
/* PRQA S 6030 1 */ /* MD_MSR_STCYC */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_MainRxTxConfHandling( UDPNM_CHANNEL_TYPE_ONLY )
{

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* #10 Processing of event: Tx Confirmation (#1)
   *     If message transmission has been confirmed by SoAdIf
   *      If message transmission is allowed
   *       Restart Timeout Timer
   *      Stop Message Timeout Timer
   */
  /*
   * No interrupt locks required due to an update of the flag in the receive interrupt
   * does not influence the algorithm, even if it occurs somewhere near the check.
   */

  if( UdpNm_IsMsgConfirmationFlag(UDPNM_CHANNEL_IDX) )
  {
    UdpNm_SetMsgConfirmationFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
    if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
    {
      UdpNm_SetTimeoutTimer(UDPNM_CHANNEL_IDX, (UdpNm_TimeoutTimerType)((UdpNm_TimeoutTimerType)UdpNm_GetTimeoutTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    }
    UdpNm_SetMsgTimeoutTimer(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  }
#endif

  /* #20 Processing of event: Rx Indication. (#2)
   *     If NM message has been received
   */
  if( UdpNm_IsMsgIndicationFlag(UDPNM_CHANNEL_IDX) )
  {
    UdpNm_SetMsgIndicationFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    switch (UdpNm_GetNmState(UDPNM_CHANNEL_IDX))
    {
      /* -------------------- Bus Sleep -------------------- */
      case NM_STATE_BUS_SLEEP:
        /* #200 in BusSleep
         *       Request to restart the network if an NM message has been received in Bus-Sleep Mode.
         */
        Nm_NetworkStartIndication ( UDPNM_NMTOSYSTEM_CHANNEL_IND );
        break;

        /* -------------------- Prepare Bus Sleep -------------------- */
      case NM_STATE_PREPARE_BUS_SLEEP:
        /* #210 in PrepareBusSleep
         *       Perform state transition to RepeatMessage state (refer to UdpNm_StateTransition)
         */
        UdpNm_StateTransition ( UDPNM_CHANNEL_PARA_FIRST NM_STATE_REPEAT_MESSAGE );
        break;

#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
        /* -------------------- Normal Operation -------------------- */
        case NM_STATE_NORMAL_OPERATION:
          /* #220 in NormalOperation
           *       If message transmission is allowed
           *        Restart Remote Sleep Indication Timer
           */
# if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
          if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
          {
            UdpNm_SetRemoteSleepTimer(UDPNM_CHANNEL_IDX, (UdpNm_RemoteSleepTimerType)((UdpNm_RemoteSleepTimerType)UdpNm_GetRemoteSleepIndTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
          }

        /* -------------------- Ready Sleep -------------------- */
        /* FALLTHROUGH */
        case NM_STATE_READY_SLEEP: /* PRQA S 2003 */ /* MD_UDPNM_Rule16.3 */
          /* #230 in ReadySleep or NormalOperation
           *       If RemoteSleepIndication was stated
           *        Reset RemoteSleepIndication state
           *        Indicate RemoteSleepCancellation to the NmIf
           */
           /* ESCAN00109020: This will never be hit in Normal Operation, because the IndicationState is already set to FALSE. The Cancellation is triggered in the transition context. */
          if( UdpNm_IsRemoteSleepIndState(UDPNM_CHANNEL_IDX) )
          {
            UdpNm_SetRemoteSleepIndState(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
            Nm_RemoteSleepCancellation( UDPNM_NMTOSYSTEM_CHANNEL_IND );
          }
#endif /* ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */

        /* -------------------- Repeat Message -------------------- */
        /* FALLTHROUGH */
      default: /* PRQA S 2003 */ /* MD_UDPNM_Rule16.3 */
        /* #240 in RepeatMessage, ReadySleep or NormalOperation
         *       If message transmission is allowed
         *        Restart TimeoutTimer in order to stay awake
         */
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
        if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED )
#endif
        {
          UdpNm_SetTimeoutTimer(UDPNM_CHANNEL_IDX, (UdpNm_TimeoutTimerType)((UdpNm_TimeoutTimerType)UdpNm_GetTimeoutTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        }
        break;
    }
  }
}

#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_RepeatMessageIndHandling
 **********************************************************************************************************************/
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_RepeatMessageIndHandling( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If RepeatMessage state was requested internally (Discovery of Network Nodes)
   *      Request RepeatMessage Indication to NmIf
   *      Set Repeat Message Bit in CBV
   */
  if (UdpNm_IsRepeatMsgReqFlag(UDPNM_CHANNEL_IDX))
  {
    UdpNm_SetRepeatMsgBitIndFlag(UDPNM_CHANNEL_IDX, TRUE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    /* Check for valid PDU Position */
    if ( UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_UDPNM_CHECK_CBVPOSITION */
    {
      /* Control Bit Vector is only accessed on task level. Therefore no interrupt locks are necessary. */
      /* Set Repeat Message Bit. */
      UdpNm_SetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX), /* SBSW_UDPNM_CSL03 */
        (UdpNm_TxMessageDataType)(UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) | (UdpNm_TxMessageDataType)UDPNM_REPEAT_MSG_BIT_MASK));
    }
  }
  /* #20 If RepeatMessageIndication is requested by Network or internally
   *      Execute state transition to RepeatMessage state
   *      Reset RepeatMessage request
   */
  if( UdpNm_IsRepeatMsgBitIndFlag(UDPNM_CHANNEL_IDX) )
  {
    /* Perform a State Transition to Repeat Message State. */
    UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST NM_STATE_REPEAT_MESSAGE );
    UdpNm_SetRepeatMsgReqFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  }
}
#endif /* ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) */

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  UdpNm_BusCommunicationHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_BusCommunicationHandling( UDPNM_CHANNEL_TYPE_FIRST CONST( uint8, AUTOMATIC ) commState )
{
  /* #10 If Network is requested AND NmState is ReadySleep
   *      Do state transition to NormalOperation state
   *     If Network is released AND NmState is NormalOperation
   *      Do state transition to ReadySleep state
   */
  if( commState == COMM_NORMAL_OPERATION )
  {
    if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP ) /* COV_UDPNM_TRANS_RS_TO_NO */
    {
      /* Perform a state transition because bus-communication has been requested. */
      UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST  NM_STATE_NORMAL_OPERATION);
    }
  }
  else
  {
    if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION )
    {
      /* Perform a state transition because bus-communication has been released. */
      UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST  NM_STATE_READY_SLEEP );
    }
  }
}
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

/***********************************************************************************************************************
 *  UdpNm_TimeoutTimerHandling
 **********************************************************************************************************************/
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_TimeoutTimerHandling( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Timeout Timer is running
   *      Decrement Timeout Timer
   *      If Timeout Timer has elapsed
   *       If NmState is not ReadySleep
   *        Report Development Error
   *        Restart Timeout Timer
   *       otherwise do state transition to PrepareBusSleep state
   */
  if( UdpNm_GetTimeoutTimer(UDPNM_CHANNEL_IDX) != 0u )
  {
    UdpNm_DecTimeoutTimer(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    if( UdpNm_GetTimeoutTimer(UDPNM_CHANNEL_IDX) == 0u )
    {
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
      if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) != NM_STATE_READY_SLEEP )
      {
        /* Handling of the Timeout Timer (Repeat Message State and Normal Operation State) */
# if ( UDPNM_RUNTIME_ERROR_REPORT == STD_ON )
        /* Report error if the timeout timer times out in Repeat Message State
         * or Normal Operation State.
         */
        (void)Det_ReportRuntimeError( UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_MAINFUNCTION, UDPNM_E_NETWORK_TIMEOUT );
# endif

        /* Restart the NM Timeout Timer. */
        UdpNm_SetTimeoutTimer(UDPNM_CHANNEL_IDX, (UdpNm_TimeoutTimerType)UdpNm_GetTimeoutTimeOfChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }
      else
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF) */
      {
        /* Leave Ready Sleep State, when the Timeout Timer has expired. */
        UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST  NM_STATE_PREPARE_BUS_SLEEP );
      }
    }
  } /* Timeout Timer Handling */
}

/***********************************************************************************************************************
 *  UdpNm_RepeatMessageTimerHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_RepeatMessageTimerHandling( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Repeat Message Timer is running
   *      Decrement Repeat Message Timer
   *      If Repeat Message Timer has elapsed
   *       Do state transition to either NormalOperation (non-passive) or ReadySleep state, depending on internal request state.
   */
  if( UdpNm_GetRepeatMsgTimer(UDPNM_CHANNEL_IDX) != 0u )
  {
    UdpNm_DecRepeatMsgTimer(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    if( UdpNm_GetRepeatMsgTimer(UDPNM_CHANNEL_IDX) == 0u ) /* COV_UDPNM_CHECK_REPEATMSGTIMER */
    {
      /* Repeat Message State is left upon Repeat Message Timer timeout. */
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
      UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST
                             (Nm_StateType)((UdpNm_GetCommState(UDPNM_CHANNEL_IDX) == COMM_NORMAL_OPERATION) ?
                                             NM_STATE_NORMAL_OPERATION : NM_STATE_READY_SLEEP) );
#else
      UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST  NM_STATE_READY_SLEEP );
#endif
    }
  } /* Repeat Message Timer Handling */
}


/**********************************************************************************************************************
  UdpNm_WaitBusSleepTimerHandling()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_WaitBusSleepTimerHandling( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Wait Bus Sleep Timer is running
   *      Decrement Wait Bus Sleep Timer
   *      If Wait Bus Sleep Timer has elapsed
   *       Do state transition to BusSleep state
   */
  if( UdpNm_GetWaitBusSleepTimer(UDPNM_CHANNEL_IDX) != 0u )
  {
    UdpNm_DecWaitBusSleepTimer(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    if( UdpNm_GetWaitBusSleepTimer(UDPNM_CHANNEL_IDX) == 0u )
    {
      /* Prepare Bus-Sleep Mode is left upon Wait Bus-Sleep Timer timeout. */
      UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST  NM_STATE_BUS_SLEEP );
    }
  } /* Wait Bus Sleep Timer Handling */
}

#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
  UdpNm_RemoteSleepTimerHandling()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_RemoteSleepTimerHandling( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Remote Sleep Indication Timer is running
   *      Decrement Remote Sleep Indication Timer
   *      If Remote Sleep Indication Timer has elapsed
   *       Indicate that channel is ready to go to sleep
   */
  if( UdpNm_GetRemoteSleepTimer(UDPNM_CHANNEL_IDX) != 0u )
  {
    UdpNm_DecRemoteSleepTimer(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    if( UdpNm_GetRemoteSleepTimer(UDPNM_CHANNEL_IDX) == 0u )
    {
      /* Remote Sleep Indication (Normal Operation State only). */
      UdpNm_SetRemoteSleepIndState(UDPNM_CHANNEL_IDX, TRUE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

      /* Notification that all other nodes are ready to sleep. */
      Nm_RemoteSleepIndication( UDPNM_NMTOSYSTEM_CHANNEL_IND );
    }
  }
}
#endif /* ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
  UdpNm_MessageTimerHandling()
**********************************************************************************************************************/
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
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_MessageTimerHandling( UDPNM_CHANNEL_TYPE_ONLY ) 
{
  /* #10 If Tx Message Timer is running
   *      Decrement Tx Message Timer
   *      If Tx Message Timer has elapsed OR message shall be sent asynchronously
   *       Transmit one NM message
   *       If Immediate NM message shall be sent
   *        Clear the RetryFirstMessageRequestFlag
   *        If transmit request was successful
   *         Reduce number of Immediate NM transmissions by one
   *         Restart Tx Message Timer with ImmediateNmCycleTime
   *        If transmit request failed
   *         Restart Tx Message Timer with MainFunctionCycleTime
   */
  if( UdpNm_GetMsgTimer(UDPNM_CHANNEL_IDX) != 0u )
  {
    UdpNm_DecMsgTimer(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    if( (UdpNm_GetMsgTimer(UDPNM_CHANNEL_IDX) == 0u )
# if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) || ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
        || (UdpNm_GetMsgRequest(UDPNM_CHANNEL_IDX) != 0u)
# endif
      )
    {
      /* Transmit a NM message. */
      Std_ReturnType success = UdpNm_TriggerTransmission( UDPNM_CHANNEL_PARA_ONLY );

# if ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
      /* Reset timer with immediate cycle time when immediate NM transmissions greater zero  */
      if( UdpNm_GetImmediateNmMsgCount(UDPNM_CHANNEL_IDX) != 0u )
      {
#  if ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
        UdpNm_SetRetryFirstMessageRequestFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#  endif
        if( success == E_OK )
        {
          UdpNm_DecImmediateNmMsgCount(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
          
          if ( UdpNm_GetImmediateNmMsgCount(UDPNM_CHANNEL_IDX) == 0u )
          {
            /* Reset Timer to MsgCycle Time */
            UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimerType)(UdpNm_GetMsgCycleTimeOfChannelConfig(UDPNM_CHANNEL_IDX))); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
          }
          else
          {
            UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimerType)UdpNm_GetImmediateNmCycleTimeOfChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
          }
        }
        else
        {
          /* Try transmission in next main function cycle */
          UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, 1u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        }
      }
      else
# endif
       /*  #20  If no immediate Nm message shall be sent 
        *        If the RetryFirstMessageRequestFlag is set
        *         If transmit request was successful
        *          Clear the RetryFirstMessageRequestFlag
        *          If ImmediateRestart is enabled and failed
        *           Clear ImmediateRestartFailedFlag
        *           Set MsgTimer to MsgCycleOffset
        *          If ImmediateRestart is not enabled or didn't fail
        *           Restart Tx Message Timer with MsgCycleTime
        *         If transmit request failed
        *          Restart Tx Message Timer with MainFunctionCycleTime
        *        If the RetryFirstMessgeRequestFlag is cleared
        *         Restart Tx Message Timer with MsgCycleTime
        */
      {
#if ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
        if ( UdpNm_IsRetryFirstMessageRequestFlag(UDPNM_CHANNEL_IDX) )
        {
          if( success == E_OK )
          {
            /* If one message was successfully transmitted, the RetryFirstMessageRequest feature is turned off */
            UdpNm_SetRetryFirstMessageRequestFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
            
# if ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
            /* If the ImmediateRestart message failed, the MsgTimer will be reloaded with the offset that would have been transmitted if the ImmediateRestart didn't fail */
            if ( UdpNm_IsImmediateRestartFailedFlag(UDPNM_CHANNEL_IDX) )
            {
              UdpNm_SetImmediateRestartFailedFlag( UDPNM_CHANNEL_IDX, FALSE ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
              /* Reset Timer to MsgCycleOffset */
              UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimerType)(UdpNm_GetMsgCycleOffsetOfPbChannelConfig(UDPNM_CHANNEL_IDX))); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
            }
            else
# endif
            {
              /* Reset Timer to MsgCycle Time */
              UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimerType)(UdpNm_GetMsgCycleTimeOfChannelConfig(UDPNM_CHANNEL_IDX))); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
            }
          }
          else
          {
            /* Try transmission in next main function cycle */
            UdpNm_SetMsgTimer( UDPNM_CHANNEL_IDX, 1u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
          }
        }
        else
#endif
        {
          /* Reset Timer to MsgCycle Time */
          UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimerType)(UdpNm_GetMsgCycleTimeOfChannelConfig(UDPNM_CHANNEL_IDX))); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        }

        UDPNM_DUMMY_STATEMENT( success ); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
      }
    }
  }
}


/**********************************************************************************************************************
  UdpNm_MessageTimeoutTimerHandling()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_MessageTimeoutTimerHandling( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Tx Message Timeout Timer is running
   *      Decrement Tx Message Timeout Timer
   *      If Tx Message Timer Timeout has elapsed
   *       Inform NmIf of the timeout
   */
  if( UdpNm_GetMsgTimeoutTimer(UDPNM_CHANNEL_IDX) != 0u )
  {
    SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_6();
    UdpNm_DecMsgTimeoutTimer(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

    if( UdpNm_GetMsgTimeoutTimer(UDPNM_CHANNEL_IDX) == 0u )
    {
      /* The ExArea must be closed in any case. The else path is created to keep the Nm_TxTimeoutException call out of the ExArea. */
      SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_6();
      /* Call timeout exception only once  */
      Nm_TxTimeoutException( UDPNM_NMTOSYSTEM_CHANNEL_IND );
    }
    else
    {
      SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_6();
    }
    
  }
}
#endif


#if ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON )
/**********************************************************************************************************************
  UdpNm_CarWakeupIndication()
**********************************************************************************************************************/
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CarWakeupIndication( UDPNM_CHANNEL_TYPE_FIRST  P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr)
{
  /* #10 If all of the following conditions are met:
   *     1. "Car Wake Up Rx Enabled" is configured
   *     2. "Car Wake Up Byte Position" is within received PDU length
   *     3. ( "Car Wake Up Filter Enabled" is not configured OR Node Identifier Byte is within received PDU length )
   *     4. Car Wake Up Bit is set in Car WakeUp Byte
   *     5. ( "Car Wake Up Filter Enabled" is not configured OR the received Node ID is equal to "Car Wake Up Filter Node Id" )
   *        Notify Car Wakeup to the Nm Interface
   */

  if( ( UdpNm_IsCarWakeUpRxEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) && ( PduInfoPtr->SduLength > UdpNm_GetCarWakeUpBytePositionOfChannelConfig(UDPNM_CHANNEL_IDX) ) ) /* COV_UDPNM_CAR_WAKEUP_RX */
  {
    if( (UdpNm_GetRxMessageData(UdpNm_GetRxMessageData_CarWakeUpByteIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) & (UdpNm_GetCarWakeUpBitMaskOfChannelConfig(UDPNM_CHANNEL_IDX))) != 0u )
    {
# if ( UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG == STD_ON )
      if( (!UdpNm_IsCarWakeUpFilterEnabledOfChannelConfig(UDPNM_CHANNEL_IDX)) ||
          ((UdpNm_GetPduNidPositionOfChannelConfig(UDPNM_CHANNEL_IDX) != UDPNM_PDU_OFF) &&
          (UdpNm_GetRxMessageData(UdpNm_GetRxMessageData_NIDIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX))
          == UdpNm_GetCarWakeUpFilterNodeIdOfChannelConfig(UDPNM_CHANNEL_IDX)))) /* COV_UDPNM_CAR_WAKEUP_FILTER */
# endif
      {
        /* UdpNm_GetPduData shall return PDU Data for this call is
            fulfilled because message is already copied to local buffer  */
        Nm_CarWakeUpIndication( UDPNM_NMTOSYSTEM_CHANNEL_IND );
      }
    }
  }
}
#endif

#if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/**********************************************************************************************************************
  UdpNm_CoordReadyToSleepHandling()
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_CoordReadyToSleepHandling( UDPNM_CHANNEL_TYPE_FIRST  CONST( uint8, AUTOMATIC ) controlBitVector )
{
  /* #10 If Sleep Ready Bit has changed and NmIf has not been notified yet
   *      If Sleep Ready Bit is set
   *       Call Nm_CoordReadyToSleepIndication()
   *      otherwise Call Nm_CoordReadyToSleepCancellation()
   *       Update the changed Sleep Ready Bit
   */
  uint8 sleepReadyBit;

  sleepReadyBit = (uint8)(controlBitVector & NM_COORD_BIT_SLEEP);
  if( UdpNm_GetCoordReadyToSleepState(UDPNM_CHANNEL_IDX) != sleepReadyBit )
  {
    if( sleepReadyBit != 0u )
    {
      Nm_CoordReadyToSleepIndication( UDPNM_NMTOSYSTEM_CHANNEL_IND );
    }
    else
    {
      Nm_CoordReadyToSleepCancellation( UDPNM_NMTOSYSTEM_CHANNEL_IND );
    }
    UdpNm_SetCoordReadyToSleepState(UDPNM_CHANNEL_IDX, (UdpNm_CoordReadyToSleepStateType)sleepReadyBit); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  }
}
#endif

/**********************************************************************************************************************
  UdpNm_TransitionToRepeatMessage()
**********************************************************************************************************************/
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_TransitionToRepeatMessage( UDPNM_CHANNEL_TYPE_ONLY )
{
/* #10 If new state is Repeat Message
 *      Start the Repeat Message Timer
 *      Stop Remote Sleep Timer and clear Remote Sleep Indication flag
 *      Call Nm_RemoteSleepCancellation if it was indicated before.
 *      If Repeat Message Indication flag is set
 *       Clear Repeat Message Indication flag (No interrupt locks required)
 *       Notify NM Interface about Repeat Message Indication.
 */
  UdpNm_SetRepeatMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_RepeatMsgTimerType)((UdpNm_RepeatMsgTimerType)UdpNm_GetRepeatMessageTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
  if ( UdpNm_IsRemoteSleepIndState(UDPNM_CHANNEL_IDX) )
  {
    /* ESCAN00109020 The Nm was already notified that RemoteSleep was indicated. It has to be cancelled. */
    UdpNm_SetRemoteSleepIndState(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    Nm_RemoteSleepCancellation( UDPNM_NMTOSYSTEM_CHANNEL_IND );
  }
  UdpNm_SetRemoteSleepTimer(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
  if( UdpNm_IsRepeatMsgBitIndFlag(UDPNM_CHANNEL_IDX) )
  {
    UdpNm_SetRepeatMsgBitIndFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( UDPNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_ON ) /* depends on UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON */
    if( UdpNm_IsRepeatMsgIndEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_REPEAT_MSG_IND_ENABLED */
    {
      Nm_RepeatMessageIndication( UDPNM_NMTOSYSTEM_CHANNEL_IND );
    }
# endif
  }
#endif

  /* #20 If message transmission is allowed
   *      If Immediate Nm transmission feature is enabled
   *      AND Network is actively requested by this node
   *       Trigger an asynchronous transmission of the NM message
   *       Ensure that (ImmediateNmTransmissions - 1) NM messages are sent with faster cycle time
   *      otherwise start message transmission with regular cycle time
   */
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
# if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
  if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED ) /* COV_UDPNM_TRANS_TO_REPEAT_MSG */
# endif
  {
# if ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
    if( (UdpNm_GetImmediateNmTransmissionsOfChannelConfig(UDPNM_CHANNEL_IDX) > 0u)
      && (UdpNm_GetNetworkRestartFlag(UDPNM_CHANNEL_IDX) == UDPNM_ACTIVE_RESTART) ) /* COV_UDPNM_IMMEDIATE_TRANSMISSIONS */
    {
      UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, 1u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      UdpNm_SetImmediateNmMsgCount(UDPNM_CHANNEL_IDX, (UdpNm_ImmediateNmMsgCountType)UdpNm_GetImmediateNmTransmissionsOfChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    }
    else
# endif
    {
      UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimerType)((UdpNm_MsgTimerType)UdpNm_GetMsgCycleOffsetOfPbChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    }
  }
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) */
}

/**********************************************************************************************************************
  UdpNm_TransitionToNetworkMode()
**********************************************************************************************************************/
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_TransitionToNetworkMode( UDPNM_CHANNEL_TYPE_FIRST  CONST(uint8, AUTOMATIC) lastNmState )
{
  /* #10 If RepeatMessage state was entered from BusSleep or PrepareBusSleep state
   *      Reset the RetryFirstMessageRequestFlag to the configured value
   *      Clear Wait Bus Sleep Timer
   *      Restart the Timeout Timer whenever Network Mode is entered.
   *      Notify Nm Interface that the network mode is entered.
   *      If "Active Wakeup Bit Enabled" is configured AND network is actively requested by this node
   *      AND CBV is available
   *       Set Active Wake-up Bit in CBV of Tx Nm message.
   */
  if ( lastNmState < NM_STATE_READY_SLEEP ) /* COV_UDPNM_CHECK_TRANSITION_TO_NETWORKMODE */
  {
#if ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
    UdpNm_SetRetryFirstMessageRequestFlag(UDPNM_CHANNEL_IDX, UdpNm_IsRetryFirstMessageRequestOfChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */ /* PRQA S 4404 */ /* MD_MSR_AutosarBoolean */
#endif
    UdpNm_SetWaitBusSleepTimer(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    UdpNm_SetTimeoutTimer(UDPNM_CHANNEL_IDX, (UdpNm_TimeoutTimerType)((UdpNm_TimeoutTimerType)UdpNm_GetTimeoutTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    Nm_NetworkMode( UDPNM_NMTOSYSTEM_CHANNEL_IND );

#if ( UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
    if( (UdpNm_IsActiveWakeUpBitEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) )
      && (UdpNm_GetNetworkRestartFlag(UDPNM_CHANNEL_IDX) == UDPNM_ACTIVE_RESTART) ) /* COV_UDPNM_ACTIVE_WAKEUP_BIT */
    {
      if( UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_UDPNM_CHECK_CBVPOSITION */
      {
        UdpNm_SetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX), /* SBSW_UDPNM_CSL03 */
          (UdpNm_TxMessageDataType)(UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) | UDPNM_ACT_WU_BIT_MASK));
      }
    }
#endif
  }
}

#if defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
/**********************************************************************************************************************
  UdpNm_PnLocal_Init
**********************************************************************************************************************/
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_PnLocal_Init( void )
{
# if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  uint8_least channel;
  UdpNm_PnClusterResetTimerExtIterType pnClusterResetTimerExtIndex;
  UdpNm_PbPncClusterConfigExtIterType  pnClusterRequestByteExt;
# endif

# if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  UdpNm_PnClusterResetTimerIterType pnClusterResetTimerIndex;
  UdpNm_SizeOfPnInfoByteConfigType  pnClusterRequestByte;
# endif

  /* ----- Implementation ----------------------------------------------- */
# if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  /* #10 Iterate over all channels
   *      If PnEraCalcEnabled is enabled
   *       Initialize ERA request buffer
   *       Stop all ERA PnClusterResetTimer
   */
  for( channel = 0u; channel < UdpNm_GetSizeOfChannelConfig(); channel++ )
  {
    if( UdpNm_IsPnEraCalcEnabledOfChannelConfig(channel) ) /* COV_UDPNM_PN_ERA_CALC */
    {
      for( pnClusterRequestByteExt = UdpNm_GetPbPncClusterConfigExtStartIdxOfPbChannelConfig(channel);
           pnClusterRequestByteExt < UdpNm_GetPbPncClusterConfigExtEndIdxOfPbChannelConfig(channel);
           pnClusterRequestByteExt++ )
      {
        UdpNm_SetPnClusterReqExt(pnClusterRequestByteExt, 0u); /* SBSW_UDPNM_CSL02 */
        UdpNm_SetPnClusterReqExtNew(pnClusterRequestByteExt, 0u); /* SBSW_UDPNM_CSL02 */

        for( pnClusterResetTimerExtIndex = UdpNm_GetPnClusterResetTimerExtStartIdxOfPbPncClusterConfigExt(pnClusterRequestByteExt);
             pnClusterResetTimerExtIndex < UdpNm_GetPnClusterResetTimerExtEndIdxOfPbPncClusterConfigExt(pnClusterRequestByteExt);
             pnClusterResetTimerExtIndex++ )
        {
          UdpNm_SetPnClusterResetTimerExt(pnClusterResetTimerExtIndex, 0u); /* SBSW_UDPNM_CSL03 */
        }
      }
    }
  }
# endif
# if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  /* #20 If PnEiraCalcEnabled is enabled
   *      Initialize EIRA related variables
   *      Stop all EIRA PnClusterResetTimer
   */
  for( pnClusterRequestByte = 0u; pnClusterRequestByte < UdpNm_GetSizeOfPnInfoByteConfig(); pnClusterRequestByte++ )
  {
    UdpNm_SetPnClusterReq(pnClusterRequestByte, 0u); /* SBSW_UDPNM_CSL02 */
    UdpNm_SetPnClusterReqNew(pnClusterRequestByte, 0u); /* SBSW_UDPNM_CSL02 */

    for( pnClusterResetTimerIndex = UdpNm_GetPnClusterResetTimerStartIdxOfPnInfoByteConfig(pnClusterRequestByte);
         pnClusterResetTimerIndex < UdpNm_GetPnClusterResetTimerEndIdxOfPnInfoByteConfig(pnClusterRequestByte);
         pnClusterResetTimerIndex++)
    {
      UdpNm_SetPnClusterResetTimer(pnClusterResetTimerIndex, 0u); /* SBSW_UDPNM_CSL03 */
    }
  }
# endif
}
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
/**********************************************************************************************************************
  UdpNm_TriggerTransmission()
**********************************************************************************************************************/
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
UDPNM_LOCAL FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_TriggerTransmission( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                      nmPduInfo;
  Std_ReturnType                   retVal;
# if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  UdpNm_SizeOfPnClusterReqNewType  pnClusterRequestByte;
# endif

  /* #10 Set Pointer variable nmPduInfo to the correct UdpNm Tx Message buffer address
   *     Call PduR_UdpNmTriggerTransmit to read User Data from the Com IPDU and store it in Tx Message buffer
   *     If PDU Length written by PduR does not match the UdpNm's UserData Length
   *      Report Development Error
   */
# if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON )

  nmPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, UDPNM_VAR_NOINIT))
    (UdpNm_GetAddrTxMessageData(UdpNm_GetTxMessageData_UserDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)));
  /* Set SduLength to expected Pdu Length. */
  nmPduInfo.SduLength = (PduLengthType)UdpNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX);
  /* SDU Length is set by the upper layer to the number of copied bytes */
  (void)PduR_UdpNmTriggerTransmit( UdpNm_GetTxUserDataPduIdOfPbChannelConfig(UDPNM_CHANNEL_IDX), &nmPduInfo ); /* SBSW_UDPNM_POINTER_PARAM */
#  if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  if( nmPduInfo.SduLength != (PduLengthType)UdpNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX) )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_CHANNEL_IDX, UDPNM_SID_MAINFUNCTION , UDPNM_E_PDUR_TRIGGERTX_ERROR);
  }
#  endif
# endif

  /* #20 If Partial Networking is enabled on this channel and PnEiraCalcEnabled is enabled in this variant
   *      Iterate over all Pn Cluster Request Bytes
   *       Copy EIRA requests and apply the PN filter mask
   */
# if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  if( (UdpNm_IsPnEnabledOfPbChannelConfig(UDPNM_CHANNEL_IDX))
#  if ( UDPNM_ISDEF_PNEIRACALCENABLED == STD_OFF )
     && ( UdpNm_IsPnEiraCalcEnabled() )
#  endif
    ) /* COV_UDPNM_PN_EIRA_CALC */
  {
    SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_0();
    for( pnClusterRequestByte = 0u; pnClusterRequestByte < UdpNm_GetSizeOfPnClusterReqNew(); pnClusterRequestByte++ )
    {
      UdpNm_SetPnClusterReqNew(pnClusterRequestByte, /* SBSW_UDPNM_CSL01 */
        (UdpNm_PnClusterReqNewType)(UdpNm_GetPnClusterReqNew(pnClusterRequestByte) | (UdpNm_PnClusterReqNewType)
            (UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_PnFilterMaskStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX) + pnClusterRequestByte) & UdpNm_GetPnFilterMaskOfPnInfoByteConfig(pnClusterRequestByte))));
    }
    SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_0();
  }
# endif

  /* #30 Prepare user data for transmission */
  /* #40 Clear local transmission request shortly before actual transmission */
  SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_1();
  nmPduInfo.SduDataPtr = (UdpNm_GetAddrTxMessageData(UdpNm_GetTxMessageDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)));
  nmPduInfo.SduLength = (PduLengthType)UdpNm_GetTxMessageDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX);

# if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) || ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
  UdpNm_SetMsgRequest(UDPNM_CHANNEL_IDX, UDPNM_NO_TRANSMIT_REQUEST); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# endif

  /* #80 Transmit the NM message. */
  /* #90 If SoAd_IfTransmit returns E_OK
   *      Start Message Timeout Timer (UdpNm_SoAdIfTxConfirmation has to be called within this time by the SoAd)
   */
  retVal = SoAd_IfTransmit( UdpNm_GetTxPduIdOfPbChannelConfig(UDPNM_CHANNEL_IDX), &nmPduInfo ); /* SBSW_UDPNM_POINTER_PARAM */
  SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_1();

  if( retVal == E_OK )
  {
    UdpNm_SetMsgTimeoutTimer(UDPNM_CHANNEL_IDX, (UdpNm_MsgTimeoutTimerType)((UdpNm_MsgTimeoutTimerType)UdpNm_GetMsgTimeoutTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u )); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  }

  return retVal;
}
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

/**********************************************************************************************************************
  UdpNm_LocalInit()
**********************************************************************************************************************/
/*!
 *
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
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_LocalInit( UDPNM_CHANNEL_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( UDPNM_TXMESSAGEDATA == STD_ON  ) || \
    ( UDPNM_RXMESSAGEDATA == STD_ON  )
  uint16                         userDataByte;
# if ( UDPNM_TXMESSAGEDATA == STD_ON )
#  if ( UDPNM_PDUNIDPOSITIONOFCHANNELCONFIG == STD_ON )
  UdpNm_SizeOfTxMessageDataType  nidPosition;
#  endif
#  if ( UDPNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON )
  UdpNm_SizeOfTxMessageDataType  cbvPosition;
#  endif
# endif
#endif

  /* #10 Initialize all global and local variables */
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
  /* The bus-communication is initially released. */
  UdpNm_SetCommState(UDPNM_CHANNEL_IDX, COMM_READY_SLEEP); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) || ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
  UdpNm_SetMsgRequest(UDPNM_CHANNEL_IDX, UDPNM_NO_TRANSMIT_REQUEST); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
  /* Per default the transmission control status is enabled. */
  UdpNm_SetTxControlState(UDPNM_CHANNEL_IDX, MSG_TX_ENABLED); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  UdpNm_SetTxControlStateRequest(UDPNM_CHANNEL_IDX, MSG_TX_ENABLED); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
  UdpNm_SetCoordReadyToSleepState(UDPNM_CHANNEL_IDX, UDPNM_COORD_ASLEEP_OR_NOT_READY_TO_SLEEP); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
  UdpNm_SetImmediateNmMsgCount(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

  /* #20 Reset flags */
  UdpNm_SetNetworkRestartFlag(UDPNM_CHANNEL_IDX, UDPNM_NO_RESTART); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  UdpNm_SetMsgIndicationFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

#if ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
  UdpNm_SetRetryFirstMessageRequestFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
  UdpNm_SetImmediateRestartFailedFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# endif
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
  UdpNm_SetMsgConfirmationFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
  UdpNm_SetRepeatMsgBitIndFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  UdpNm_SetRepeatMsgReqFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

  /* #30 Reset Timers */
  /* All timers have to be initialized since they are processed in every state. */
  UdpNm_SetTimeoutTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  UdpNm_SetWaitBusSleepTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  UdpNm_SetRepeatMsgTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
  /* Reset Remote Sleep Timer and state. */
  UdpNm_SetRemoteSleepTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
  UdpNm_SetRemoteSleepIndState(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* The transmission of NM messages is initially stopped. */
  UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

  /* Timeout Timer is initially stopped */
  UdpNm_SetMsgTimeoutTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

  /* Initialize NM message data. */
  /* #50 Initialize User Data with 0xFF */
#if ( UDPNM_TXMESSAGEDATA == STD_ON )
  for( userDataByte = UdpNm_GetTxMessageDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
       userDataByte < UdpNm_GetTxMessageDataEndIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
       userDataByte++ )
  {
    UdpNm_SetTxMessageData(userDataByte, 0xFFu); /* SBSW_UDPNM_CSL03 */
  }
#endif

#if ( UDPNM_RXMESSAGEDATA == STD_ON )
  for( userDataByte = UdpNm_GetRxMessageDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
       userDataByte < UdpNm_GetRxMessageDataEndIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
       userDataByte++ )
  {
    UdpNm_SetRxMessageData(userDataByte, 0xFFu); /* SBSW_UDPNM_CSL03 */
  }
#endif

#if ( UDPNM_TXMESSAGEDATA == STD_ON ) || ( UDPNM_RXMESSAGEDATA == STD_ON )
  /* The reserved bits are set to 0 */
  /* #60 If Node Id Enabled is configured and 'Pdu Nid Position' is configured to Byte0 or Byte1
   *      Initialize Source Node Identifier Byte to the configured Node Id
   *     otherwise initialize the reserved Byte to zero
   */
# if ( UDPNM_TXMESSAGEDATA == STD_ON )
#  if ( UDPNM_PDUNIDPOSITIONOFCHANNELCONFIG == STD_ON )
  if ( UdpNm_GetPduNidPositionOfChannelConfig(UDPNM_CHANNEL_IDX) != UDPNM_PDU_OFF ) /* COV_UDPNM_CHECK_NIDPOSITION */
  {
    nidPosition = (UdpNm_SizeOfTxMessageDataType)(UdpNm_GetTxMessageData_NIDIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX));
      /* Source Node Identifier */
#   if ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON )
    if ( UdpNm_IsNodeIdEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_NODE_ID_ENABLED */
    {
      UdpNm_SetTxMessageData(nidPosition, (UdpNm_TxMessageDataType)UdpNm_GetNodeIdOfPbChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_CSL03 */
    }
    else
#   endif
    {
      UdpNm_SetTxMessageData(nidPosition, 0x00u); /* SBSW_UDPNM_CSL03 */
    }
  }
#  endif

  /* #70 If 'Pdu Cbv Position' is configured to Byte0 or Byte1
   *      Set the Cri bit in the Cbv Byte to cleared
   *      If Pn is enabled or CriBitAlwaysEnabled
   *       Initialize Cbv Byte with Cri bit set
   */
#  if ( UDPNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON )
  if( UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_UDPNM_CHECK_CBVPOSITION */
  {
    cbvPosition = (UdpNm_SizeOfTxMessageDataType)(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX));
    /* ControlBitVector = 0x00, RepeatMessageBit = FALSE */
      UdpNm_SetTxMessageData(cbvPosition, 0x00u); /* SBSW_UDPNM_CSL03 */

#   if ( UDPNM_PNENABLEDOFPBCHANNELCONFIG == STD_ON )
    if( UdpNm_IsPnEnabledOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_PN_ENABLED */
    {
      UdpNm_SetTxMessageData(cbvPosition, UDPNM_CRI_BIT_MASK); /* SBSW_UDPNM_CSL03 */
    }
#   endif
#   if ( UDPNM_CRIBITALWAYSENABLEDOFCHANNELCONFIG == STD_ON )
    if( UdpNm_IsCriBitAlwaysEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_CRI_BIT_ALWAYS_ENABLED */
    {
      UdpNm_SetTxMessageData(cbvPosition, UDPNM_CRI_BIT_MASK); /* SBSW_UDPNM_CSL03 */
    }
#   endif
  }
#  endif
# endif
#endif

  /* #90 Set NmState to default state Bus Sleep without notification of upper layer */
  /* State machine initialization without notification. */
  UdpNm_SetNmState(UDPNM_CHANNEL_IDX, NM_STATE_BUS_SLEEP); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

}

/**********************************************************************************************************************
  UdpNm_StateTransition()
**********************************************************************************************************************/
/*!
 *
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
/* PRQA S 6030 1 */ /* MD_MSR_STCYC */
UDPNM_LOCAL FUNC( void, UDPNM_CODE ) UdpNm_StateTransition( UDPNM_CHANNEL_TYPE_FIRST
                                                            CONST( Nm_StateType, AUTOMATIC ) nextNmState )
{
  /* ----- Local Variables ---------------------------------------------- */
  Nm_StateType  lastNmState;   /* Last state of the state machine. */
#if ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
  boolean additionalTransmissionRequired = FALSE;
#endif

  /* #10 Update Nm state */
  lastNmState = UdpNm_GetNmState(UDPNM_CHANNEL_IDX);
  UdpNm_SetNmState(UDPNM_CHANNEL_IDX, nextNmState);  /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

  switch (nextNmState)
  {
    /* -------------------- transition to Bus Sleep -------------------- */
    /* #100 If new state is Bus Sleep
     *       Notify Nm Interface that BusSleep mode has been entered.
     */
  case NM_STATE_BUS_SLEEP:
    Nm_BusSleepMode( UDPNM_NMTOSYSTEM_CHANNEL_IND );
    break;

    /* -------------------- transition to Prepare Bus Sleep -------------------- */
    /* #200 If new state is Prepare Bus Sleep
     *       Notify Nm Interface that PrepareBusSleep mode has been entered.
     *       Start the WaitBusSleepTimer with WaitBusSleep time
     *       If ActiveWakeupBitEnabled is set and CBV is available
     *        Clear Active Wake-up Bit in CBV.
     *       Clear CoordReadyToSleepState. Notification handling is done in UdpNm_SoAdIfRxIndication
     *       Clear RemoteSleepIndState. When entering NetworkMode, the RemoteSleepStates are reset in the NmIf.
     */
  case NM_STATE_PREPARE_BUS_SLEEP:
    Nm_PrepareBusSleepMode( UDPNM_NMTOSYSTEM_CHANNEL_IND );

    UdpNm_SetWaitBusSleepTimer(UDPNM_CHANNEL_IDX, (UdpNm_WaitBusSleepTimerType)UdpNm_GetWaitBusSleepTimeOfChannelConfig(UDPNM_CHANNEL_IDX) ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

#if ( UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
    if( UdpNm_IsActiveWakeUpBitEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_ACTIVE_WAKEUP_BIT */
    {
      if( UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_UDPNM_CHECK_CBVPOSITION */
      {
        UdpNm_SetTxMessageData((UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)), /* SBSW_UDPNM_CSL03 */
          (UdpNm_TxMessageDataType)(UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) & (UdpNm_TxMessageDataType)UDPNM_ACT_WU_BIT_INV_MASK));
      }
    }
#endif

#if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
    /* No need to notify Nm about Ready To Sleep Cancellation, would be done by Nm_NetworkMode */
    UdpNm_SetCoordReadyToSleepState(UDPNM_CHANNEL_IDX, UDPNM_COORD_ASLEEP_OR_NOT_READY_TO_SLEEP); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
    /* ESCAN00109020: Reset the RemoteSleepIndState. The cancellation is not required anymore when entering RepeatMessage, because the RemoteSleepStates in the NmIf are
     *                reset in the Nm_NetworkMode. So the states are consistent.
     */
    UdpNm_SetRemoteSleepIndState(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
    break;

    /* -------------------- transition to Ready Sleep -------------------- */
    /* #300 If new state is Ready Sleep
     *       Stop NM message timer.
     *       Stop Remote Sleep Timer (Normal to Ready Only)
     *       If CBV is available and NodeDetection is enabled on this channel
     *        Clear the repeat message bit in CBV (no interrupt locks required, access on Task level only)
     *       Stop transmission of Nm Messages with faster cycle time (Immediate Nm transmission)
     *       Clear RetryFirstMessageRequest flag
     */
  case NM_STATE_READY_SLEEP:
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
    UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
    UdpNm_SetRemoteSleepTimer(UDPNM_CHANNEL_IDX, 0u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
    if (UdpNm_IsNodeDetectionEnabledOfChannelConfig(UDPNM_CHANNEL_IDX)) /* COV_UDPNM_NODE_DETECTION_ENABLED */
    {
      if( UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_UDPNM_CHECK_CBVPOSITION */
      {
        UdpNm_SetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX), /* SBSW_UDPNM_CSL03 */
          (UdpNm_TxMessageDataType)(UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) & (UdpNm_TxMessageDataType)UDPNM_REPEAT_MSG_BIT_INV_MASK));
      }
    }
#endif
#if ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
    UdpNm_SetImmediateNmMsgCount(UDPNM_CHANNEL_IDX, 0u); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
    UdpNm_SetRetryFirstMessageRequestFlag(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
    break;

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
    /* -------------------- transition to Normal Operation -------------------- */
    /* #400 If new state is Normal Operation
     *       If message transmission is allowed
     *        Restart Remote Sleep Timer and clear Remote Sleep Indication flag
     *        Call Nm_RemoteSleepCancellation if it was indicated before.
     *       If lastState was ReadySleep AND message transmission is allowed
     *        Trigger asynchronous transmission of the NM message.
     *       In any other state AND if NodeDetection is enabled for this channel AND if CBV is available
     *        Clear the repeat message bit in TxMessageData buffer
     */
  case NM_STATE_NORMAL_OPERATION:
# if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
    if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED )
#  endif
    {
      /* ESCAN00109020 If there is a state transition to Normal Operation and RemoteSleep was already indicated, it must be cancelled. */
      if ( UdpNm_IsRemoteSleepIndState(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_REMOTE_SLEEP_IND_STATE_NO_RS_TO_NO XF */
      {
        UdpNm_SetRemoteSleepIndState(UDPNM_CHANNEL_IDX, FALSE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        Nm_RemoteSleepCancellation( UDPNM_NMTOSYSTEM_CHANNEL_IND );
      }
      UdpNm_SetRemoteSleepTimer(UDPNM_CHANNEL_IDX, (UdpNm_RemoteSleepTimerType)((UdpNm_RemoteSleepTimerType)UdpNm_GetRemoteSleepIndTimeOfChannelConfig(UDPNM_CHANNEL_IDX) + 1u )); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    }
# endif
    if( lastNmState == NM_STATE_READY_SLEEP ) /* COV_UDPNM_TRANS_RS_TO_NO */
    {
# if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
      if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED ) /* COV_UDPNM_TRANS_RS_TO_NO_COMCONTROL */
# endif
      {
        UdpNm_SetMsgTimer(UDPNM_CHANNEL_IDX, 1u ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }
    else
    {
# if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( UDPNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON )
      if ( UdpNm_IsNodeDetectionEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_NODE_DETECTION_ENABLED */
      {
        if( UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_UDPNM_CHECK_CBVPOSITION */
        {
          UdpNm_SetTxMessageData((UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)), /* SBSW_UDPNM_CSL03 */
            (UdpNm_TxMessageDataType)(UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) & (UdpNm_TxMessageDataType)UDPNM_REPEAT_MSG_BIT_INV_MASK));
        }
      }
# endif
    }
    break;
#endif
    /* -------------------- transition to Repeat Message -------------------- */
  default:
    /* #500 Transition to Repeat Message */
    UdpNm_TransitionToRepeatMessage( UDPNM_CHANNEL_PARA_ONLY );

    /* #510 Additional actions when entering Network Mode */
    UdpNm_TransitionToNetworkMode( UDPNM_CHANNEL_PARA_FIRST  lastNmState );

    /* #520 If ImmediateRestartEnabled feature is active on this channel
     *      AND Repeat Message state is entered from PrepareBusSleep state due to an internal communication request a
     *      transmission of an asynchronous NM message is done right after the notification of new state.
     *      Clear NetworkRestartFlag
     */
#if ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
    /* If Network Mode has been entered from Prepare Bus-Sleep Mode due to a network request,
       an asynchronous NM message transmission is requested as soon as Network Mode has been entered */
    if (UdpNm_IsImmediateRestartEnabledOfChannelConfig(UDPNM_CHANNEL_IDX)) /* COV_UDPNM_IMMEDIATE_RESTART_ENABLED */
    {
      if( (lastNmState == NM_STATE_PREPARE_BUS_SLEEP) &&
          (UdpNm_GetMsgTimer(UDPNM_CHANNEL_IDX) > 1u) &&
          (UdpNm_GetNetworkRestartFlag(UDPNM_CHANNEL_IDX) == UDPNM_ACTIVE_RESTART) ) /* COV_UDPNM_MSG_TIMER_GREATER_ZERO */
      {
        additionalTransmissionRequired = TRUE;
      }
    }
#endif /* ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON ) */

    UdpNm_SetNetworkRestartFlag(UDPNM_CHANNEL_IDX, UDPNM_NO_RESTART); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

    break;
  }

#if ( UDPNM_STATE_CHANGE_IND_ENABLED == STD_ON )
  /* #20 Notify Nm Interface that state has changed. */
  if ( lastNmState != nextNmState )
  {
    Nm_StateChangeNotification( UDPNM_NMTOSYSTEM_CHANNEL_IND, lastNmState, nextNmState );
  }
#endif

#if ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
  /* #30 If transmission of asynchronous Nm message is required
   *      Call local function UdpNm_TriggerTransmission in order to transmit an NM message immediately
   *      If message transmission failed AND Retry First Message Request is enabled on this channel
   *       Reset the Message Timer in order to transmit an NM message in the next main function cycle
   *       Set flag that ImmediateRestart failed
   *      If message transmission succeeded
   *       Clear RetryFirstMessageRequest Flag
   */
  if( additionalTransmissionRequired == TRUE ) /* COV_UDPNM_MSG_TIMER_GREATER_ZERO */
  {
    Std_ReturnType retVal;
    /* Request the transmission of the asynchronous NM message in Network Mode. */
    /* Call UdpNm_TriggerTransmission after Nm_StateChangeNotification because the user data might have been
     * changed inside the Nm_StateChangeNotification call */
    retVal = UdpNm_TriggerTransmission( UDPNM_CHANNEL_PARA_ONLY );

# if ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
    if (UdpNm_IsRetryFirstMessageRequestFlag(UDPNM_CHANNEL_IDX)) /* COV_UDPNM_RETRY_FIRST_MESSAGE_REQUEST_ENABLED */
    {
      if ( retVal == E_NOT_OK )
      {
        /* MsgTimer = 2 since the MsgTimer Handling is done later in the main function and a transmit request was already
         * processed during the current main function cycle.
         */
        UdpNm_SetMsgTimer( UDPNM_CHANNEL_IDX, UDPNM_IMMEDIATE_RESTART_FAILED_MSG_TMR_VAL ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        UdpNm_SetImmediateRestartFailedFlag( UDPNM_CHANNEL_IDX, TRUE ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }
      else
      {
        UdpNm_SetRetryFirstMessageRequestFlag( UDPNM_CHANNEL_IDX, FALSE ); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }
# endif

    UDPNM_DUMMY_STATEMENT( retVal ); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }

#endif /* ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON ) */
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * UdpNm_Init
 **********************************************************************************************************************/
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
/* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
FUNC( void, UDPNM_CODE ) UdpNm_Init( CONSTP2CONST( UdpNm_ConfigType, AUTOMATIC, UDPNM_INIT_DATA ) UdpNmConfigPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = UDPNM_E_NO_ERROR;
  uint8             ecumErrorId = UDPNM_E_ECUM_NO_ERROR;
  NetworkHandleType channel;
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON ) && ( UDPNM_PBCHANNELCONFIG == STD_ON ) /* COV_UDPNM_GEN_DATA_CHECK */
  uint8             sizeOfChannelConfig;
#endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_INIT )

#if ( UDPNM_USE_INIT_POINTER == STD_ON )
  /* Use selected configuration */
  /* #10 Store selected configuration from 'UdpNmConfigPtr' */
  UdpNm_ConfigDataPtr = UdpNmConfigPtr;
#else
  UDPNM_DUMMY_STATEMENT_CONST(UdpNmConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #20 Check that module is not initialized */
  if( UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_ALREADY_INITIALIZED;
  }
  else
#endif /* ( UDPNM_DEV_ERROR_DETECT == STD_ON ) */
#if ( UDPNM_USE_INIT_POINTER == STD_ON )
  /* #30 Check that configuration parameter 'UdpNmConfigPtr' is not NULL */
  if( UdpNmConfigPtr == NULL_PTR )
  {
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
    errorId = UDPNM_E_INIT_FAILED;
# endif
# if ( UDPNM_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
    ecumErrorId = ECUM_BSWERROR_NULLPTR;
# endif
  }
  else
#endif
#if ( UDPNM_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
  /* #40 Check Generator Compatibility Version */
  if( UdpNm_GetGeneratorCompatibilityVersion() != (uint16)UDPNM_EXPECTED_GENERATOR_COMPATIBILITY_VERSION )
  {
    ecumErrorId = ECUM_BSWERROR_COMPATIBILITYVERSION;
  }
  else
#endif
#if ( UDPNM_FINALMAGICNUMBER == STD_ON )
  /* #50 Check Magic Number */
  if( UdpNm_GetFinalMagicNumber() != UDPNM_FINAL_MAGIC_NUMBER )
  {
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
    errorId = UDPNM_E_INIT_FAILED;
# endif
  }
  else
#endif
  {
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON ) && ( UDPNM_PBCHANNELCONFIG == STD_ON ) /* COV_UDPNM_GEN_DATA_CHECK */
    /* #60 Check GenData */
    /* Initialization down here, because Init Pointer is not set yet, during declaration */
    sizeOfChannelConfig = UdpNm_GetSizeOfChannelConfig();
    if (sizeOfChannelConfig != UdpNm_GetSizeOfPbChannelConfig()) /* PRQA S 2992, 2996 */ /* MD_UDPNM_Rule14.3, MD_UDPNM_Rule2.2 */ /* COV_UDPNM_INVALID_GENDATA */
    {
      errorId = UDPNM_E_INVALID_GENDATA; /* PRQA S 2880 */ /* MD_UDPNM_Rule2.1 */
    }
    else
# endif
    {
      /* #70 Initialize PN relevant variables */
#if defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
      UdpNm_PnLocal_Init();
#endif

      /* #80 Call UdpNm_LocalInit to initialize all global and local variables for each channel */
      for( channel = 0u; channel < UdpNm_GetSizeOfChannelConfig(); channel++ )
      {
        UdpNm_LocalInit( UDPNM_CHANNEL_PARA_ONLY );
      }
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
      /* #90 Set global state to initialized */
      UdpNm_SetModuleInitialized(TRUE); /* SBSW_UDPNM_CSL_VAR_ACCESS */
#endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #A0 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_INIT , errorId);
  }
#else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if ( UDPNM_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
  if( ecumErrorId != UDPNM_E_ECUM_NO_ERROR )
  {
    (void)EcuM_BswErrorHook(UDPNM_MODULE_ID, ecumErrorId);
  }
#else
  UDPNM_DUMMY_STATEMENT(ecumErrorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_INIT )
}

/***********************************************************************************************************************
 *  UdpNm_PassiveStartUp
 **********************************************************************************************************************/
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

#if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  NetworkHandleType channel;
#endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_PASSIVESTARTUP )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
# else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
# endif
  else
#endif
  /* #20 If module is initialized and parameter checks are passed */
  {
#if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
#endif
    /* #200 If NmState is BusSleep or PrepareBusSleep
     *       If network was not actively requested
     *        Set NetworkRestartFlag to passive restart for further handling in main function
     */
    if( (UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_BUS_SLEEP) ||
        (UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_PREPARE_BUS_SLEEP) )
    {
      if( UdpNm_GetNetworkRestartFlag(UDPNM_CHANNEL_IDX) == UDPNM_NO_RESTART )
      {
        UdpNm_SetNetworkRestartFlag(UDPNM_CHANNEL_IDX, UDPNM_PASSIVE_RESTART); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_PASSIVESTARTUP , errorId);
  }
#else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_PASSIVESTARTUP )
  return retVal;
}

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  UdpNm_NetworkRequest
 **********************************************************************************************************************/
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_NETWORKREQUEST )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* Request network */
    /* #200 Set internal communication flag to NormalOperation
     *      If no internal request is set AND ( UdpNm is in state BusSleep or PrepareBusSleep OR ( <Pn Enabled> AND <Pn Handle Multiple Network Requests> is configured ) )
     *       Set NetworkRestartFlag to active restart for further handling in main function
     */
    UdpNm_SetCommState(UDPNM_CHANNEL_IDX, COMM_NORMAL_OPERATION); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

    /* Ensure Start-Up */
    if( (UdpNm_GetNetworkRestartFlag(UDPNM_CHANNEL_IDX) == UDPNM_NO_RESTART) &&
        ( (UdpNm_GetNmState(UDPNM_CHANNEL_IDX) < NM_STATE_READY_SLEEP)
    /* Check is not done if PnHandleMultipleRequests = 0 on all channels ( A && 0 = 0 ) */
# if ( UDPNM_PN_FEATURE_ENABLED == STD_ON ) && ( UDPNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG == STD_ON )
      /* Change to Network Mode if Multiple Network Request is set to true */
      || ( (UdpNm_IsPnEnabledOfPbChannelConfig(UDPNM_CHANNEL_IDX)) &&
           (UdpNm_IsPnHandleMultipleNetworkRequestOfChannelConfig(UDPNM_CHANNEL_IDX))
         )
# endif
         ) ) /* COV_UDPNM_PN_ENABLED */
    {
      UdpNm_SetNetworkRestartFlag(UDPNM_CHANNEL_IDX, UDPNM_ACTIVE_RESTART); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_NETWORKREQUEST , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_NETWORKREQUEST )
  return retVal;
}


/***********************************************************************************************************************
 *  UdpNm_NetworkRelease
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8           errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_NETWORKRELEASE )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* #200 Set internal communication flag to ReadySleep */
    UdpNm_SetCommState(UDPNM_CHANNEL_IDX, COMM_READY_SLEEP); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_NETWORKRELEASE , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_NETWORKRELEASE )
  return retVal;
}
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

/***********************************************************************************************************************
 *  UdpNm_GetState
 **********************************************************************************************************************/
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                   CONSTP2VAR( Nm_StateType, AUTOMATIC, UDPNM_APPL_VAR ) nmStatePtr,
                                                   CONSTP2VAR( Nm_ModeType, AUTOMATIC, UDPNM_APPL_VAR ) nmModePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8          errorId = UDPNM_E_NO_ERROR;

#if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  NetworkHandleType channel;
#endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_GETSTATE )

  /* ----- Development Error Checks ------------------------------------- */
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmStatePtr' */
  else if( nmStatePtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  /* Check parameter 'nmModePtr' */
  else if( nmModePtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
#endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* #200 Return current UdpNm state in passed <nmStatePtr> parameter */
    *nmStatePtr = UdpNm_GetNmState(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_GETSTATE */
    /* Set mode according to the current state */
    /* #210 If UdpNm state is BusSleep
     *       Return 'Bus Sleep Mode' in passed <nmModePtr> parameter
     */
    if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_BUS_SLEEP )                     /* Bus Sleep */
    {
      *nmModePtr = NM_MODE_BUS_SLEEP; /* SBSW_UDPNM_GETSTATE */
    }
    /* #220 If UdpNm state is PrepareBusSleep
     *       Return 'Prepare Bus Sleep Mode' in passed <nmModePtr> parameter
     */
    else if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_PREPARE_BUS_SLEEP )    /* Prepare Sleep */
    {
      *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP; /* SBSW_UDPNM_GETSTATE */
    }
    /* #230 in all other cases
     *       Return 'Network Mode' to passed <nmModePtr> parameter
     */
    else                                            /* Ready Sleep, Normal Operation, Repeat Message */
    {
      *nmModePtr = NM_MODE_NETWORK; /* SBSW_UDPNM_GETSTATE */
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_GETSTATE , errorId);
  }
#else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_GETSTATE )
  return retVal;
}

#if ( UDPNM_USER_DATA_ENABLED == STD_ON )
# if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_COM_USER_DATA_SUPPORT == STD_OFF )
/***********************************************************************************************************************
 *  UdpNm_SetUserData
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                      CONSTP2CONST( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmUserDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8                         errorId = UDPNM_E_NO_ERROR;
  UdpNm_TxMessageDataIterType   txMesssageDataByte;
  UdpNm_TxMessageDataIterType   userDataByte;

#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  else
  NetworkHandleType channel;
#  endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_SETUSERDATA )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
#  if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#   if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#   else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#   endif
  /* Check parameter 'nmUserDataPtr' */
  else if( nmUserDataPtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
#  endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_3();
    /* #200 Iterate all user data bytes
     *       Write user data into Tx Message Data buffer. Content is transmitted in the next NM message.
     */
    /*
     * nmUserDataPtr is a zero based list. Iteration is done from 0u
     * TxMessageData is an indirected list.
     */

    userDataByte = 0u;
    for( txMesssageDataByte = UdpNm_GetTxMessageData_UserDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
         txMesssageDataByte < UdpNm_GetTxMessageData_UserDataEndIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
         txMesssageDataByte++ )
    {
      UdpNm_SetTxMessageData(txMesssageDataByte, (UdpNm_TxMessageDataType)nmUserDataPtr[userDataByte]); /* SBSW_UDPNM_CSL03 */
      userDataByte++;
    }
    SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_3();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#  if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_SETUSERDATA , errorId);
  }
#  else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_SETUSERDATA )
  return retVal;
}
# endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_COM_USER_DATA_SUPPORT == STD_OFF ) */

/***********************************************************************************************************************
 *  UdpNm_GetUserData
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                      CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmUserDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8                         errorId = UDPNM_E_NO_ERROR;
  UdpNm_RxMessageDataIterType   userDataByte;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_GETUSERDATA )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmUserDataPtr' */
  else if( nmUserDataPtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_5();
    /* #200 Iterate over all user data bytes
     *       Return user data from last received Nm message.
     */
    for( userDataByte = 0u; userDataByte < UdpNm_GetRxMessageData_UserDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX); userDataByte++ )
    {
      nmUserDataPtr[userDataByte] = UdpNm_GetRxMessageData(UdpNm_GetRxMessageData_UserDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX) + userDataByte); /* SBSW_UDPNM_GETUSERDATA */
    }
    SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_5();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_GETUSERDATA , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_GETUSERDATA )
  return retVal;
}
#endif  /* ( UDPNM_USER_DATA_ENABLED == STD_ON ) */


#if ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_GetNodeIdentifier
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                            CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmNodeIdPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_GETNODEIDENTIFIER )

# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmNodeIdPtr' */
  else if( (nmNodeIdPtr) == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* #200 If NodeIdentifier position is configured to Byte0 or Byte1
     *       Return the current Node Identifier from the last received NM message
     */
    if( UdpNm_GetPduNidPositionOfChannelConfig(UDPNM_CHANNEL_IDX) != UDPNM_PDU_OFF ) /* COV_UDPNM_CHECK_NIDPOSITION */
    {
      if (UdpNm_IsNodeIdEnabledOfChannelConfig(UDPNM_CHANNEL_IDX)) /* COV_UDPNM_NODE_ID_ENABLED */
      {
        *nmNodeIdPtr = UdpNm_GetRxMessageData(UdpNm_GetRxMessageData_NIDIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)); /* SBSW_UDPNM_GETNODEIDENTIFIER */
        retVal = E_OK;
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_GETNODEIDENTIFIER , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_GETNODEIDENTIFIER )

  return retVal;
}


/***********************************************************************************************************************
 *  UdpNm_GetLocalNodeIdentifier
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                 CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR )
                                                                 nmNodeIdPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_GETLOCALNODEIDENTIFIER )

  /* ----- Development Error Checks ------------------------------------- */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmNodeIdPtr' */
  else if( nmNodeIdPtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* #200 Return Node ID from configuration. */
    if ( UdpNm_IsNodeIdEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_NODE_ID_ENABLED */
    {
      *nmNodeIdPtr = UdpNm_GetNodeIdOfPbChannelConfig(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_GETNODEIDENTIFIER */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_GETLOCALNODEIDENTIFIER , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_GETLOCALNODEIDENTIFIER )

  return retVal;
}
#endif /* ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) */

#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_RepeatMessageRequest
 **********************************************************************************************************************/
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_REPEATMESSAGEREQUEST )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if ((nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS)
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* #200 If Node Detection is enabled on this channel
     *       If current state is ReadySleep or NormalOperation.
     *        Request Transition to Repeat Message State.
     */
    if ( UdpNm_IsNodeDetectionEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_NODE_DETECTION_ENABLED */
    {
      if( ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP ) ||
        ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION ) )
      {
        UdpNm_SetRepeatMsgReqFlag(UDPNM_CHANNEL_IDX, TRUE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        retVal =  E_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_REPEATMESSAGEREQUEST , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_REPEATMESSAGEREQUEST )

  return retVal;
}
#endif /* ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) */

#if ( ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_USER_DATA_ENABLED == STD_ON ) || \
      ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ))
/***********************************************************************************************************************
 *  UdpNm_GetPduData
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                     CONSTP2VAR( uint8, AUTOMATIC, UDPNM_APPL_VAR ) nmPduDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                  retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8                           errorId = UDPNM_E_NO_ERROR;
  UdpNm_RxMessageDataIterType     msgDataByte;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_GETPDUDATA )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmPduDataPtr' */
  else if( (nmPduDataPtr) == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
# if ( UDPNM_USER_DATA_ENABLED == STD_OFF )
    if ( UdpNm_IsNodeIdEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_NODE_ID_ENABLED */
# endif
    {
      SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_5();
      /* #200 Iterate over all data bytes of last received Nm message
       *       Return current PDU data
       */
      for( msgDataByte = 0u; msgDataByte < UdpNm_GetRxMessageDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX); msgDataByte++ )
      {
        nmPduDataPtr[msgDataByte] = UdpNm_GetRxMessageData((UdpNm_GetRxMessageDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) + (msgDataByte)); /* SBSW_UDPNM_GETPDUDATA */
      }
      SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_5();
      retVal = E_OK;
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_GETPDUDATA , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_GETPDUDATA )

  return retVal;
}
#endif /* ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) ||
          ( UDPNM_USER_DATA_ENABLED == STD_ON ) */

#if ( UDPNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_RequestBusSynchronization
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_RequestBusSynchronization( CONST( NetworkHandleType, AUTOMATIC )
                                                                    nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_REQUESTBUSSYNCHRONIZATION )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* Trigger Transmission */
    /* #200 If NmState is not BusSleep AND not PrepareBusSleep AND if message transmission is allowed.
     *       Call UdpNm_TriggerTransmission to request an asynchronous NM message transmission
     */
    if( ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) != NM_STATE_BUS_SLEEP ) &&
        ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) != NM_STATE_PREPARE_BUS_SLEEP )
# if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
          && ( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
       )
    {
      retVal = UdpNm_TriggerTransmission( UDPNM_CHANNEL_PARA_ONLY );
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_REQUESTBUSSYNCHRONIZATION , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_REQUESTBUSSYNCHRONIZATION )

  return retVal;
}
#endif /* ( UDPNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) */

#if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_CheckRemoteSleepIndication
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC )
                                                                     nmChannelHandle,
                                                                     CONSTP2VAR( boolean, AUTOMATIC, UDPNM_APPL_VAR )
                                                                     nmRemoteSleepIndPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_CHECKREMOTESLEEPINDICATION )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmRemoteSleepIndPtr' */
  else if( nmRemoteSleepIndPtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* Check Remote Sleep Indication may only be requested in Ready Sleep State and during Normal Operation. */
    /* #200 If state is Ready Sleep or Normal Operation
     *       Return current Remote Sleep Indication state
     */
    if( (UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP) ||
        (UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION) )
    {
      /* Provide information about current status of remote sleep indication */
      *nmRemoteSleepIndPtr = (boolean)UdpNm_IsRemoteSleepIndState(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CHECKREMOTESLEEPINDICATION */ /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_CHECKREMOTESLEEPINDICATION , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_CHECKREMOTESLEEPINDICATION )

  return retVal;
}
#endif /* ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */


#if ( UDPNM_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_GetVersionInfo
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
FUNC( void, UDPNM_CODE ) UdpNm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, UDPNM_APPL_VAR ) versioninfo)
{

  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = UDPNM_E_NO_ERROR;

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_GETVERSIONINFO )

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that module is initialized */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* Check parameter 'versioninfo' */
  if( versioninfo == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If parameter checks are successful */
  {
    /* Provide version information */
    /* #200 Return vendor ID, module ID and version data */
    versioninfo->vendorID = (uint16)UDPNM_VENDOR_ID; /* SBSW_UDPNM_GETVERSIONINFO */
    versioninfo->moduleID = (uint8)UDPNM_MODULE_ID; /* SBSW_UDPNM_GETVERSIONINFO */

    versioninfo->sw_major_version = (uint8)UDPNM_SW_MAJOR_VERSION; /* SBSW_UDPNM_GETVERSIONINFO */
    versioninfo->sw_minor_version = (uint8)UDPNM_SW_MINOR_VERSION; /* SBSW_UDPNM_GETVERSIONINFO */
    versioninfo->sw_patch_version = (uint8)UDPNM_SW_PATCH_VERSION; /* SBSW_UDPNM_GETVERSIONINFO */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_GETVERSIONINFO , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_GETVERSIONINFO )
}
#endif /* ( UDPNM_VERSION_INFO_API == STD_ON ) */

#if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_EnableCommunication
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED ) || ( UDPNM_PASSIVE_MODE_ENABLED == STD_ON )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_ENABLECOMMUNICATION )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if ( UDPNM_PASSIVE_MODE_ENABLED == STD_ON )
    retVal = E_NOT_OK;
# else
#  if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
#  endif
    /* #200 If message transmission ability is disabled and NM state is not BusSleep or PrepareBusSleep
     *       Request to enable the message transmission ability. Further handling is done in UdpNm_Mainfunction.
     */
    if ( UdpNm_IsComControlEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_COM_CONTROL_ENABLED */
    {
      if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) > NM_STATE_PREPARE_BUS_SLEEP )
      {
        if( UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_DISABLED )
        {
          UdpNm_SetTxControlStateRequest(UDPNM_CHANNEL_IDX, MSG_TX_ENABLED); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
          retVal = E_OK;
        }
      }
    }
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_ENABLECOMMUNICATION , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_ENABLECOMMUNICATION )

  return retVal;
}


/***********************************************************************************************************************
 *  UdpNm_DisableCommunication
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
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
#  if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
  NetworkHandleType channel;
#  endif
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_DISABLECOMMUNICATION )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) ) /* COV_UDPNM_INVALID_CHANNEL_DET */
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
#  endif
    /* Disable NM PDU transmission ability in Network Mode */
    /* #200 If NM state is not BusSleep and not PrepareBusSleep
     *       Request to disable Tx Message transmission ability. Further handling is done in UdpNm_Mainfunction.
     */
    if ( UdpNm_IsComControlEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_COM_CONTROL_ENABLED */
    {
      if( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) > NM_STATE_PREPARE_BUS_SLEEP )
      {
        UdpNm_SetTxControlStateRequest(UDPNM_CHANNEL_IDX, MSG_TX_DISABLED); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        retVal = E_OK;
      }
    }
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_DISABLECOMMUNICATION , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_DISABLECOMMUNICATION )

  return retVal;
}
#endif /* ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON ) */


/***********************************************************************************************************************
 *  UdpNm_InitMemory
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, UDPNM_CODE ) UdpNm_InitMemory( void )
{
  /* Note: Do not perform init check. */
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Set global state to not initialized */
  UdpNm_SetModuleInitialized(FALSE); /* SBSW_UDPNM_CSL_VAR_ACCESS */
#endif
#if ( UDPNM_USE_INIT_POINTER == STD_ON )
  /* #20 Set config pointer to NULL_PTR */
  UdpNm_ConfigDataPtr = NULL_PTR;
#endif
}

#if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/***********************************************************************************************************************
 *  UdpNm_SetSleepReadyBit
 **********************************************************************************************************************/
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_SetSleepReadyBit( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                           CONST( boolean, AUTOMATIC ) nmSleepReadyBit )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = UDPNM_E_NO_ERROR;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_SETSLEEPREADYBIT )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( nmChannelHandle != UdpNm_GetChannelIdOfChannelConfig(0u) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= UDPNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( UdpNm_GetSysToNmChInd(nmChannelHandle) >= UdpNm_GetSizeOfChannelConfig() ) )
  {
    errorId = UDPNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmSleepReadyBit' */
  else if( ( nmSleepReadyBit != TRUE ) && ( nmSleepReadyBit != FALSE ) )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = UdpNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* Set Coordination Bit */
    /* #200 If configuration parameter <Pdu Cbv Position> is set to Byte 0 or Byte 1
     *       If passed parameter <nmSleepReadyBit> is set
     *        Set Nm Coordinator Sleep Ready Bit
     *       otherwise Clear Nm Coordinator Sleep Ready Bit
     */
    if( UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(UDPNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_UDPNM_CHECK_CBVPOSITION */
    {
      SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_3();
      if( nmSleepReadyBit == TRUE )
      {
        UdpNm_SetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX), /* SBSW_UDPNM_CSL03 */
          (UdpNm_TxMessageDataType)(UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) | NM_COORD_BIT_SLEEP));
      }
      else
      {
        UdpNm_SetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX), /* SBSW_UDPNM_CSL03 */
          (UdpNm_TxMessageDataType)(UdpNm_GetTxMessageData(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)) & NM_COORD_BIT_INV_SLEEP));
      }
      SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_3();
    /* #300 If state is Repeat Message OR Normal Operation AND message transmission is allowed.
     *       Trigger an asynchronous transmission of the NM message
     */
      if( ((UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION) ||
           (UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_REPEAT_MESSAGE))
#  if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
          && (UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED)
#  endif
        )
      {
        UdpNm_SetMsgRequest(UDPNM_CHANNEL_IDX, UDPNM_TRANSMIT_REQUEST); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
      }

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_SETSLEEPREADYBIT , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_SETSLEEPREADYBIT )

  return retVal;
}
#endif /* ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON ) */

/***********************************************************************************************************************
 *  UdpNm_SoAdIfRxIndication
 **********************************************************************************************************************/
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
/* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
FUNC( void, UDPNM_CODE ) UdpNm_SoAdIfRxIndication( VAR( PduIdType, AUTOMATIC ) RxPduId,
                                             P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  errorId = UDPNM_E_NO_ERROR;
#if !defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  NetworkHandleType channel;
#endif

#if ( ( UDPNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON ) && ( ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON ) \
        || (( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )) ) )
  /* local variables */
  uint8             controlBitVector;
#endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_RXINDICATION )

  /* ----- Development Error Checks ------------------------------------- */
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'RxPduId' */
  else if
# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
          ( RxPduId != UDPNM_CHANNEL_IDX )
# else
#  if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
          ( RxPduId >= (NetworkHandleType)UdpNm_GetSizeOfPduIdToChIndex() )
#  else
          ( RxPduId >= (NetworkHandleType)UdpNm_GetSizeOfChannelConfig() )
#  endif
# endif
  {
    errorId = UDPNM_E_INVALID_PDUID;
  }
  else
#endif
  {
#if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
#else
# if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
    channel = (NetworkHandleType)UdpNm_GetPduIdToChIndex(RxPduId);
# else
    channel = (NetworkHandleType)RxPduId;
# endif
#endif
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
    /* Check parameter 'PduInfoPtr' */
    if( (PduInfoPtr) == NULL_PTR )
    {
      errorId = UDPNM_E_PARAM_POINTER;
    }
    /* Check parameter 'SduDataPtr' */
    else if( (PduInfoPtr->SduDataPtr) == NULL_PTR )
    {
      errorId = UDPNM_E_PARAM_POINTER;
    }
    else
#endif
    /* #20 If module is initialized and parameter checks are passed */
    {
#if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
      /* #30 If PN Filtering needs to be applied OR <All Messages Keep Awake> is configured
       *      If Node Id is enabled on this channel
       */
      if( (UdpNm_PnFilterHandling( UDPNM_CHANNEL_PARA_FIRST PduInfoPtr ) == TRUE) /* SBSW_UDPNM_LOCALFUNCTION_CALL */
# if ( UDPNM_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG == STD_ON )
       || (UdpNm_IsAllMessagesKeepAwakeOfChannelConfig(UDPNM_CHANNEL_IDX))
# endif
         ) /* COV_UDPNM_PN_FILTER_HANDLING */
#endif /* ( UDPNM_PN_FEATURE_ENABLED == STD_ON ) */
      {

#if ( ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_USER_DATA_ENABLED == STD_ON ) \
        || ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON ) )
# if ( ( UDPNM_USER_DATA_ENABLED == STD_OFF ) && ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_OFF ) )
        if (UdpNm_IsNodeIdEnabledOfChannelConfig(UDPNM_CHANNEL_IDX)) /* COV_UDPNM_NODE_ID_ENABLED */
# endif
        {
          /* #300 Copy received NM message data to the Rx Message Data buffer */
          UdpNm_CopyRxMessageData( UDPNM_CHANNEL_PARA_FIRST PduInfoPtr ); /* SBSW_UDPNM_LOCALFUNCTION_CALL */
        }
#endif

#if ( ( UDPNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON ) && ( ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON ) \
        || (( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )) ) )
        /* #310 If configuration parameter <Pdu Cbv Position> is set to Byte 0 or Byte 1
         *       If Node Detection is enabled on this channel
         *        If Nm state is not RepeatMessage state and Repeat Message Indication flag has not been set yet
         *         Set the Repeat Message Indication flag in order to notify it to the Nm Interface in next main function
         */
        if ( ( UdpNm_GetPduCbvPositionOfChannelConfig(UDPNM_CHANNEL_IDX) != UDPNM_PDU_OFF ) 
          && ( PduInfoPtr->SduLength > UdpNm_GetPduCbvPositionOfChannelConfig(UDPNM_CHANNEL_IDX) ) ) /* COV_UDPNM_CHECK_CBVPOSITION */
        {
          /* Store the CBV Byte */
          controlBitVector = (uint8)(PduInfoPtr->SduDataPtr[UdpNm_GetPduCbvPositionOfChannelConfig(UDPNM_CHANNEL_IDX)]);
# if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
          if ( UdpNm_IsNodeDetectionEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_NODE_DETECTION_ENABLED */
          {
            if( ( ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION ) ||
                  ( UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP ) ) &&
                ( !UdpNm_IsRepeatMsgBitIndFlag(UDPNM_CHANNEL_IDX) ) )
            {
              UdpNm_SetRepeatMsgBitIndFlag(UDPNM_CHANNEL_IDX, (UdpNm_RepeatMsgBitIndFlagType)(controlBitVector & UDPNM_REPEAT_MSG_BIT_MASK)); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
            }
          }
# endif

# if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
          /* #3100 Call CoordReadyToSleepHandling */
          UdpNm_CoordReadyToSleepHandling( UDPNM_CHANNEL_PARA_FIRST  controlBitVector);
# endif
        }
#endif

#if ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON )
        /* #320 Car Wakeup Indication Handing */
        UdpNm_CarWakeupIndication( UDPNM_CHANNEL_PARA_FIRST  PduInfoPtr ); /* SBSW_UDPNM_LOCALFUNCTION_CALL */
#endif

        /* #330 Further Message Reception is processed in UdpNm_MainFunction */
        UdpNm_SetMsgIndicationFlag(UDPNM_CHANNEL_IDX, TRUE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

        /* #340 Notify NM Interface that an NM message has been received. */
# if ( UDPNM_PDU_RX_INDICATION_ENABLED == STD_ON )
        Nm_PduRxIndication( UDPNM_NMTOSYSTEM_CHANNEL_IND );
# endif
      }
    }  /* Error checks */
  }

  /* ----- Development Error Report --------------------------------------- */
  /* Use channel number as InstanceID */
  /* #40 Report errors if applicable */
#if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_RXINDICATION, errorId);
  }
#else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#else
  UDPNM_DUMMY_STATEMENT_CONST(PduInfoPtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT(RxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_RXINDICATION )
}

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  UdpNm_SoAdIfTxConfirmation
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
FUNC( void, UDPNM_CODE ) UdpNm_SoAdIfTxConfirmation( VAR( PduIdType, AUTOMATIC ) TxPduId )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = UDPNM_E_NO_ERROR;
# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_TXCONFIRMATION )

  /* ----- Development Error Checks ------------------------------------- */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'TxPduId' */
  else if
#  if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
          ( TxPduId >= (NetworkHandleType)UdpNm_GetSizeOfPduIdToChIndex() )
#  else
          ( TxPduId >= (NetworkHandleType)UdpNm_GetSizeOfChannelConfig() )
#  endif
  {
    errorId = UDPNM_E_INVALID_PDUID;
  }
  else
# endif
  {
# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
# else
#  if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
    channel = (NetworkHandleType)UdpNm_GetPduIdToChIndex(TxPduId);
#  else
    channel = (NetworkHandleType)TxPduId;
#  endif
# endif
    /* #20 If module is initialized and parameter checks are passed */

    /* A flag is used in order to ensure data consistency of the timeout timer. */
    /* #200 Set Message Confirmation Flag for further handling in UdpNm_Mainfunction
     *      Confirm User Data Transmission.
     */
    UdpNm_SetMsgConfirmationFlag(UDPNM_CHANNEL_IDX, TRUE); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) && ( UDPNM_PDUR_UDPNM_TXCONFIRMATION == STD_ON )
    PduR_UdpNmTxConfirmation( UdpNm_GetTxUserDataPduIdOfPbChannelConfig(UDPNM_CHANNEL_IDX) );
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    /* Development error detection */
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_TXCONFIRMATION , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_TXCONFIRMATION )
}
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

#if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) || defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
/***********************************************************************************************************************
 *  UdpNm_Transmit
 **********************************************************************************************************************/
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_Transmit( VAR( PduIdType, AUTOMATIC ) UdpNmTxPduId,
                                                   P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType    retVal;
  uint8             errorId = UDPNM_E_NO_ERROR;

# if ( UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON )
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT(UdpNmTxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  else
  /* Create Channel Handle */
  NetworkHandleType channel;
#  endif
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_TRANSMIT )

# if ( UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON )
  retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that module is initialized */
#  if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'PduInfoPtr' */
  else if( PduInfoPtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  /* Check parameter 'SduDataPtr' */
  else if( (PduInfoPtr->SduDataPtr) == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  /* Check parameter 'UdpNmTxPduId' */
  else if
#   if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
          ( UdpNmTxPduId >= (NetworkHandleType)UdpNm_GetSizeOfPduIdToChIndex() )
#   else
          ( UdpNmTxPduId >= (NetworkHandleType)UdpNm_GetSizeOfChannelConfig() )
#   endif
  {
    errorId = UDPNM_E_INVALID_PDUID;
  }
  else
#  endif
  {
#  if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
#   if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
    channel = (NetworkHandleType)UdpNm_GetPduIdToChIndex(UdpNmTxPduId);
#   else
    channel = (NetworkHandleType)UdpNmTxPduId;
#   endif
#  endif
    /* #20 If module is initialized and parameter checks are passed */
    UDPNM_DUMMY_STATEMENT_CONST(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    /* Spontaneous transmission is required if
     * - The PN Feature is enabled and the handling of multiple calls of UdpNm_NetworkRequest() is disabled
     * - The Car Wake-Up Rx feature is enabled
     * - The Allow Triggered Msg Transmission is enabled
     */
    /* #200 If Partial Networking is enabled AND Pn Handle Multiple Network Requests is disabled
     *      OR Car Wake Up Rx Enabled is enabled
     *      OR Allow Triggered Msg Transmission is enabled
     *       If Nm is in state NormalOperation OR RepeatMessage AND message transmission is allowed.
     *        Trigger transmission in next main function call
     */
    if(
#  if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
         ((UdpNm_IsPnEnabledOfPbChannelConfig(UDPNM_CHANNEL_IDX))
#   if ( UDPNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG == STD_ON )
          && (!UdpNm_IsPnHandleMultipleNetworkRequestOfChannelConfig(UDPNM_CHANNEL_IDX))
#   endif
         )
#   if ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG == STD_ON )
         ||
#   endif
#  endif
#  if ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON )
         (UdpNm_IsCarWakeUpRxEnabledOfChannelConfig(UDPNM_CHANNEL_IDX))
#   if( UDPNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG == STD_ON )
         ||
#   endif
#  endif
#  if( UDPNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG == STD_ON )
         (UdpNm_IsAllowTriggeredMsgTransmissionOfPbChannelConfig(UDPNM_CHANNEL_IDX))
#  endif
      ) /* COV_UDPNM_PN_ENABLED_UDPNM_TRANSMIT */
    {
      if( ((UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION) ||
           (UdpNm_GetNmState(UDPNM_CHANNEL_IDX) == NM_STATE_REPEAT_MESSAGE))
#  if ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
          && (UdpNm_GetTxControlState(UDPNM_CHANNEL_IDX) == MSG_TX_ENABLED)
#  endif
        )
      {
        UdpNm_SetMsgRequest(UDPNM_CHANNEL_IDX, UDPNM_TRANSMIT_REQUEST); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */
        retVal = E_OK;
      }
    }
    else
    {
      retVal = E_OK;
    }
  }
# else /* if ( UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON ) */
  /* Passive Mode Enabled is ON or PN Feature and Car Wake-Up Rx Enabled are disabled:
   * no spontaneous NM message transmission required
   */
  UDPNM_DUMMY_STATEMENT(UdpNmTxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  UDPNM_DUMMY_STATEMENT(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = E_OK;
# endif

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON ) && ( UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON )
  if( errorId != UDPNM_E_NO_ERROR )
  {
  /* #90 Report errors if applicable */
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_TRANSMIT , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_TRANSMIT )

  return retVal;
}


/***********************************************************************************************************************
 *  UdpNm_CancelTransmit
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, UDPNM_CODE ) UdpNm_CancelTransmit( VAR( PduIdType, AUTOMATIC ) UdpNmTxSduId )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = UDPNM_E_NO_ERROR;
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
    /* #200 Function is only provided for compatibility reasons and has no functionality. */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_CANCELTRANSMIT , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  UDPNM_DUMMY_STATEMENT( UdpNmTxSduId ); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return retVal;
}

#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  UdpNm_SoAdIfTriggerTransmit
 **********************************************************************************************************************/
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
/* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
FUNC(Std_ReturnType, UDPNM_CODE) UdpNm_SoAdIfTriggerTransmit( VAR( PduIdType, AUTOMATIC ) TxPduId, 
                                                        P2VAR( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType               retVal = E_NOT_OK;
  uint8                        errorId = UDPNM_E_NO_ERROR;
  UdpNm_TxMessageDataIterType  txMsgByte;
  UdpNm_TxMessageDataIterType  txMsgPosition;

# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  /* Create Channel Handle */
  NetworkHandleType channel;
# endif

  UdpNm_Rtm_Start( RtmMeasurementPoint_UDPNM_SID_TRIGGERTRANSMIT )

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that module is initialized */
# if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  /* Check parameter 'PduInfoPtr' */
  else if( PduInfoPtr == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  /* Check parameter 'SduDataPtr' */
  else if( (PduInfoPtr->SduDataPtr) == NULL_PTR )
  {
    errorId = UDPNM_E_PARAM_POINTER;
  }
  /* Check parameter 'UdpNmTxPduId' */
  else if
#  if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
          ( TxPduId >= (NetworkHandleType)UdpNm_GetSizeOfPduIdToChIndex() )
#  else
          ( TxPduId >= (NetworkHandleType)UdpNm_GetSizeOfChannelConfig() )
#  endif
  {
    errorId = UDPNM_E_INVALID_PDUID;
  }
  else
# endif
  {
# if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
# else
#  if ( UDPNM_PDUIDTOCHINDEX == STD_ON )
    channel = (NetworkHandleType)UdpNm_GetPduIdToChIndex(TxPduId);
#  else
    channel = (NetworkHandleType)TxPduId;
#  endif
# endif
    /* #20 If module is initialized and parameter checks are passed
     *      If the length of the provided pointer is big enough
     *       Request the current user data
     *       If wrong length was returned by the user data request, report to DET
     *       Update the data to transmit in the provided pointer 
     */
    if ( PduInfoPtr->SduLength >= UdpNm_GetTxMessageDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX) )
    {
# if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON )
      VAR( PduInfoType, AUTOMATIC ) PduInfo;

      PduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, UDPNM_VAR_NOINIT))
         (UdpNm_GetAddrTxMessageData(UdpNm_GetTxMessageData_UserDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX)));
      /* Set SduLength to expected Pdu Length. */
      PduInfo.SduLength = (PduLengthType)UdpNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX);
      /* SDU Length is set by the upper layer to the number of copied bytes */
      (void)PduR_UdpNmTriggerTransmit( UdpNm_GetTxUserDataPduIdOfPbChannelConfig(UDPNM_CHANNEL_IDX), &PduInfo ); /* SBSW_UDPNM_POINTER_PARAM */
#  if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
      if( PduInfo.SduLength != (PduLengthType)UdpNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX) )
      {
        errorId = UDPNM_E_PDUR_TRIGGERTX_ERROR;
      }
      else
#  endif
# endif
      {
        SchM_Enter_UdpNm_UDPNM_EXCLUSIVE_AREA_2();
        
        txMsgByte = 0u;
        for( txMsgPosition = UdpNm_GetTxMessageDataStartIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
             txMsgPosition < UdpNm_GetTxMessageDataEndIdxOfPbChannelConfig(UDPNM_CHANNEL_IDX);
             txMsgPosition++ )
        {
          PduInfoPtr->SduDataPtr[txMsgByte] = UdpNm_GetTxMessageData(txMsgPosition); /* SBSW_UDPNM_TRIGGER_TRANSMIT */
          txMsgByte++;
        }
        SchM_Exit_UdpNm_UDPNM_EXCLUSIVE_AREA_2();

        PduInfoPtr->SduLength = (PduLengthType)UdpNm_GetTxMessageDataLengthOfPbChannelConfig(UDPNM_CHANNEL_IDX); /* SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS */

        retVal = E_OK;
      }
    }
  }

    /* ----- Development Error Report --------------------------------------- */
# if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  if( errorId != UDPNM_E_NO_ERROR )
  {
  /* #30 Report errors if applicable */
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_TRIGGERTRANSMIT , errorId);
  }
# else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  UdpNm_Rtm_Stop( RtmMeasurementPoint_UDPNM_SID_TRIGGERTRANSMIT )

  return retVal;
}
#endif

/***********************************************************************************************************************
 *  UdpNm_LocalMainFunctionChannelSelector
 **********************************************************************************************************************/
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
FUNC( void, UDPNM_CODE ) UdpNm_LocalMainFunctionChannelSelector( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = UDPNM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( UDPNM_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check that module is initialized */
  if( !UdpNm_IsModuleInitialized() )
  {
    errorId = UDPNM_E_NO_INIT;
  }
  else
#endif
  {
    /* #20 If module is initialized */
    /* #200 If ComM channel is valid in variant
     *          Call UpdNm_LocalMainFunction
     *          If ComM channel is last one in current variant
     *           Call UdpNm_PnEiraCalculation
     */
    if ((nmChannelHandle < UdpNm_GetSizeOfSysToNmChInd()) && (UdpNm_GetSysToNmChInd(nmChannelHandle) != UDPNM_NO_SYSTONMCHIND)) /* COV_UDPNM_PRECOMPILE */
    {
      UdpNm_LocalMainFunction(UdpNm_GetSysToNmChInd(nmChannelHandle));
#if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
      /* Current channel is last one variant */
      if ( UdpNm_GetSysToNmChInd(nmChannelHandle) == (UdpNm_GetSizeOfChannelConfig() - 1u) ) /* COV_UDPNM_PRECOMPILE */
      {
        UdpNm_PnEiraCalculation( nmChannelHandle );
      }
#endif
    }
  } /* Error Checks */

  /* ----- Development Error Report --------------------------------------- */
#if ( UDPNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != UDPNM_E_NO_ERROR )
  {
    (void)Det_ReportError(UDPNM_MODULE_ID, UDPNM_INSTANCE_ID, UDPNM_SID_MAINFUNCTION , errorId);
  }
#else
  UDPNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

}

/***********************************************************************************************************************
 *  UdpNm_LocalMainFunction
 **********************************************************************************************************************/
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
/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
UDPNM_LOCAL_INLINE FUNC( void, UDPNM_CODE ) UdpNm_LocalMainFunction( CONST( NetworkHandleType, AUTOMATIC ) channel )
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
  uint8             commState;                /* local copy of the global communication state. */
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
    /* #10 Process Communication Control (if ComControlEnabled enabled) */
  if ( UdpNm_IsComControlEnabledOfChannelConfig( UDPNM_CHANNEL_IDX ) ) /* COV_UDPNM_COM_CONTROL_ENABLED */
  {
    UdpNm_CommunicationControlHandling( UDPNM_CHANNEL_PARA_ONLY );
  }
      
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* #20 Copy the global communication state. (no interrupt locks required) */
  commState = UdpNm_GetCommState(UDPNM_CHANNEL_IDX);
#endif

  /* #30 Process Rx Indication and Tx Confirmation events */
  UdpNm_MainRxTxConfHandling( UDPNM_CHANNEL_PARA_ONLY );

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
  /* #40 Process Repeat Message Indication (if Node Detection is enabled) */
  if ( UdpNm_IsNodeDetectionEnabledOfChannelConfig(UDPNM_CHANNEL_IDX) ) /* COV_UDPNM_NODE_DETECTION_ENABLED */
  {
    UdpNm_RepeatMessageIndHandling( UDPNM_CHANNEL_PARA_ONLY );
  }
#endif
  /* #50 Process Network Restart */
  /* #500 If passive or active start-up is requested
    *        Perform a state transition to RepeatMessage (Network Mode).
    */
  if( UdpNm_GetNetworkRestartFlag(UDPNM_CHANNEL_IDX) != UDPNM_NO_RESTART )
  {
    UdpNm_StateTransition( UDPNM_CHANNEL_PARA_FIRST  NM_STATE_REPEAT_MESSAGE );
  }

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF)
  /* #60 Process Request or Release bus communication (if PassiveModeEnabled disabled) */
  UdpNm_BusCommunicationHandling( UDPNM_CHANNEL_PARA_FIRST  commState );
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF) */

  /* #70 Process NM Timeout Timer */
  UdpNm_TimeoutTimerHandling( UDPNM_CHANNEL_PARA_ONLY );

  /* #80 Process Repeat Message Timer */
  UdpNm_RepeatMessageTimerHandling( UDPNM_CHANNEL_PARA_ONLY );

  /* #90 Process Wait Bus Sleep Timer */
  UdpNm_WaitBusSleepTimerHandling( UDPNM_CHANNEL_PARA_ONLY );

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
  /* #A0 Process Remote Sleep Indication Timer (if RemoteSleepIndication is enabled) */
  UdpNm_RemoteSleepTimerHandling( UDPNM_CHANNEL_PARA_ONLY );
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* #B0 Process Tx Message Timer */
  UdpNm_MessageTimerHandling( UDPNM_CHANNEL_PARA_ONLY );

  /* #C0 Process Tx Message Timeout Timer */
  UdpNm_MessageTimeoutTimerHandling( UDPNM_CHANNEL_PARA_ONLY );
#endif /* ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

#if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
# if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  /* #D0 Calculate Pn Era (if PnEraCalcEnabled enabled) */
  UdpNm_PnEraCalculation( UDPNM_CHANNEL_PARA_ONLY );
# endif
#endif /* UDPNM_PN_FEATURE_ENABLED == STD_ON */

#if defined ( UDPNM_OPTIMIZE_CHANNEL_ENABLED )
  UDPNM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}

#define UDPNM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*******************************************************************************
  Verify the configuration of the UdpNm Network Management
*******************************************************************************/

/* Check Error Detection / Diagnostic switches */
#if !( defined ( UDPNM_DEV_ERROR_DETECT ) && ( ( UDPNM_DEV_ERROR_DETECT == STD_OFF ) || ( UDPNM_DEV_ERROR_DETECT == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Development Error Detection Enabled has to be defined STD_OFF or STD_ON"
#endif

#if !( defined ( UDPNM_DEV_ERROR_REPORT ) && \
      ( ( UDPNM_DEV_ERROR_REPORT == STD_OFF ) || ( UDPNM_DEV_ERROR_REPORT == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Development Error Reporting Enabled has to be defined STD_OFF or STD_ON"
#endif

/* Check UdpNm Configuration switches */
#if !( defined UDPNM_CONFIGURATION_VARIANT_PRECOMPILE )
# error: "UdpNm NM configuration issue: Config Variant Pre-Compile has to be defined"
#endif
#if !( defined UDPNM_CONFIGURATION_VARIANT_LINKTIME )
# error: "UdpNm NM configuration issue: Config Variant Link-Time has to be defined"
#endif
#if !( defined UDPNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error: "UdpNm NM configuration issue: Config Variant Post-Build-Loadable has to be defined"
#endif

#if ( UDPNM_CONFIGURATION_VARIANT_PRECOMPILE == UDPNM_CONFIGURATION_VARIANT_LINKTIME )
# error: "UdpNm NM configuration issue: Config Variant Defines of Pre-Compile and Link-Time must have different values"
#endif
#if ( UDPNM_CONFIGURATION_VARIANT_PRECOMPILE == UDPNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error: "UdpNm NM configuration issue: Config Variant Defines of Pre-Compile and Post-Build-Loadable must have different values"
#endif
#if ( UDPNM_CONFIGURATION_VARIANT_LINKTIME == UDPNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error: "UdpNm NM configuration issue: Config Variant Defines of Link-Time and Post-Build-Loadable must have different values"
#endif

#if !( defined ( UDPNM_CONFIGURATION_VARIANT ) && \
      ( ( UDPNM_CONFIGURATION_VARIANT == UDPNM_CONFIGURATION_VARIANT_PRECOMPILE ) || \
        ( UDPNM_CONFIGURATION_VARIANT == UDPNM_CONFIGURATION_VARIANT_LINKTIME ) || \
        ( UDPNM_CONFIGURATION_VARIANT == UDPNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE ) ) )
# error: "UdpNm NM configuration issue: Configuration Variant has to be defined to Pre-Compile, Link-Time or Post-Build-Loadable"
#endif
#if !( defined ( UDPNM_POSTBUILD_VARIANT_SUPPORT ) && \
      ( ( UDPNM_POSTBUILD_VARIANT_SUPPORT == STD_OFF ) || ( UDPNM_POSTBUILD_VARIANT_SUPPORT == STD_ON ) ) )
# error: "UdpNm NM configuration issue: PostBuild Variant Support has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_VERSION_INFO_API ) && \
      ( ( UDPNM_VERSION_INFO_API == STD_OFF ) || ( UDPNM_VERSION_INFO_API == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Version Info Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG ) && \
      ( ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Node Detection Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_REMOTE_SLEEP_IND_ENABLED ) && \
      ( ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_OFF ) || ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Remote Sleep Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_USER_DATA_ENABLED ) && \
      ( ( UDPNM_USER_DATA_ENABLED == STD_OFF ) || ( UDPNM_USER_DATA_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: User Data Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_BUS_SYNCHRONIZATION_ENABLED ) && \
      ( ( UDPNM_BUS_SYNCHRONIZATION_ENABLED == STD_OFF ) || ( UDPNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Bus Synchronization Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_PASSIVE_MODE_ENABLED ) && \
      ( ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF ) || ( UDPNM_PASSIVE_MODE_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Passive Mode Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG ) && \
      ( ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Node Identifier Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_PDU_RX_INDICATION_ENABLED ) && \
      ( ( UDPNM_PDU_RX_INDICATION_ENABLED == STD_OFF ) || ( UDPNM_PDU_RX_INDICATION_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Pdu Rx Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_STATE_CHANGE_IND_ENABLED ) && \
      ( ( UDPNM_STATE_CHANGE_IND_ENABLED == STD_OFF ) || ( UDPNM_STATE_CHANGE_IND_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: State Change Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG ) && \
      ( ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Communication Control Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG ) && \
      ( ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Immediate Restart Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_REPEATMSGINDENABLEDOFCHANNELCONFIG ) && \
      ( ( UDPNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Repeat Message Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_COORDINATOR_SYNC_SUPPORT ) && \
      ( ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_OFF ) || ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Coordinator Sync Support has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_COM_USER_DATA_SUPPORT ) && \
      ( ( UDPNM_COM_USER_DATA_SUPPORT == STD_OFF ) || ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) ) )
# error: "UdpNm NM configuration issue: User Data Support via Com has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_RUNTIME_MEASUREMENT_SUPPORT ) && \
      ( ( UDPNM_RUNTIME_MEASUREMENT_SUPPORT == STD_OFF ) || ( UDPNM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Runtime Measurement Support has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_PDUR_UDPNM_TXCONFIRMATION ) && \
      ( ( UDPNM_PDUR_UDPNM_TXCONFIRMATION == STD_OFF ) || ( UDPNM_PDUR_UDPNM_TXCONFIRMATION == STD_ON ) ) )
# error: "UdpNm NM configuration issue: PduR UdpNm TxConfirmation has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED ) && \
      ( ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_OFF ) || ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Immediate Nm Transmission Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED ) && \
      ( ( UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_OFF ) || ( UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Active Wup Bit Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG ) && \
      ( ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Car Wup Rx Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG ) && \
      ( ( UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Car Wup Filter Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG ) && \
      ( ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Retry First Message Requests has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_PN_FEATURE_ENABLED ) && \
      ( ( UDPNM_PN_FEATURE_ENABLED == STD_OFF ) || ( UDPNM_PN_FEATURE_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: PN Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED ) && \
      ( ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_OFF ) || ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: PN ERA Calc Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED ) && \
      ( ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_OFF ) || ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) ) )
# error: "UdpNm NM configuration issue: PN EIRA Calc Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION ) && \
      ( ( UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_OFF ) || ( UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Allow Triggered Msg Transmission has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG ) && \
      ( ( UDPNM_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: All Messages Keep Awake has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( UDPNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG ) && \
      ( ( UDPNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG == STD_OFF ) || ( UDPNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG == STD_ON ) ) )
# error: "UdpNm NM configuration issue: Pn Handle Multiple Network Requests has to be defined STD_OFF or STD_ON"
#endif

/* Check configuration of Passive Mode */
#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_ON )
# if ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_COORDINATOR_SYNC_SUPPORT cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( UDPNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_BUS_SYNCHRONIZATION_ENABLED cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( UDPNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_REMOTE_SLEEP_IND_ENABLED cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG cannot be activated if UDPNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
#endif

/* Check Car Wakeup */
#if ( UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG == STD_OFF ) && ( UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG == STD_ON )
# error "UdpNm NM configuration issue: UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG cannot be activated if UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG is STD_OFF."
#endif

/* Check PN Feature */
#if ( UDPNM_PN_FEATURE_ENABLED == STD_ON )
# if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) && ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( UDPNM_COM_USER_DATA_SUPPORT == STD_OFF )
#   error "UdpNm NM configuration issue: UDPNM_PN_EIRA_CALC_FEATURE_ENABLED activated requires UDPNM_COM_USER_DATA_SUPPORT to be enabled."
#  endif
# endif
#else
# if ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_PN_ERA_CALC_FEATURE_ENABLED cannot be activated if UDPNM_PN_FEATURE_ENABLED is STD_OFF."
# endif
# if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
#  error "UdpNm NM configuration issue: UDPNM_PN_EIRA_CALC_FEATURE_ENABLED cannot be activated if UDPNM_PN_FEATURE_ENABLED is STD_OFF."
# endif
#endif

/* Check configuration of Node Detection */
#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_OFF )
# error: "UdpNm NM configuration issue: UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG cannot be activated if UDPNM_NODEIDENABLEDOFCHANNELCONFIG is STD_OFF."
#endif

#if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_OFF ) && ( UDPNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_ON )
# error "UdpNm NM configuration issue: UDPNM_REPEATMSGINDENABLEDOFCHANNELCONFIG cannot be activated if UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG is STD_OFF."
#endif

/* Check configuration of CBV */
#if( UDPNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_OFF )
# if ( UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON ) || ( UDPNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#  error "UdpNm NM configuration issue: 'Pdu Cbv Position' has to be configured to UDPNM_PDU_BYTE0 or UDPNM_PDU_BYTE1."
# endif
#endif

#if ( UDPNM_PDUNIDPOSITIONOFCHANNELCONFIG == STD_OFF )
# if ( UDPNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG == STD_ON )
#  error "UdpNm NM configuration issue: 'Pdu Node Id Position' has to be configured to UDPNM_PDU_BYTE0 or UDPNM_PDU_BYTE1."
# endif
#endif

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
  MD_UDPNM_Rule2.1
    Reason:     Previous if statement checks the generated configuration. In a valid configuration the error message will never be reached.
    Risk:       No Risk.
    Prevention: Covered by code review.
  
  MD_UDPNM_Rule2.2
    Reason:     If statement checks the generated configuration. It ensures no Out-Of-Bounds access can occur.
    Risk:       No Risk.
    Prevention: Covered by code review.
 
  MD_UDPNM_Rule14.3:
    Reason:     In certain configurations the if statement will always result in a TRUE/FALSE expression due to the generated code.
    Risk:       No Risk.
    Prevention: Covered by code review.
 
  MD_UDPNM_Rule16.3:
    Reason:     Fall through used for code optimizations.
    Risk:       There is a risk that a fall through is overseen by a code review and lead to unexpected results.
    Prevention: Fall through is marked with explicit comments to draw attention to it when code review is performed.
 */

/* SBSW_JUSTIFICATION_BEGIN
\ID                SBSW_UDPNM_POINTER_PARAM
\DESCRIPTION       The pointer 'nmPnInfo' is passed to the PduR
                   The pointer 'nmPduInfo' is passed to the PduR or SoAd
\COUNTERMEASURE \N The parameters are not used in address calculations for memory manipulating
                   operations. Such calculations include but are not limited to: Array indexing,
                   pointer offset calculation and related forms of pointer arithmetic. Furthermore
                   these parameters are not forwarded to other software modules which could use
                   them for such operations unless they implement appropriate countermeasures.
                   And the addresses in the pointer variables are not saved in global variables
                   so that they could be used outside the function call. In that case, they are no
                   longer valid.

\ID                SBSW_UDPNM_CHECKREMOTESLEEPINDICATION
\DESCRIPTION       The function UdpNm_CheckRemoteSleepIndication writes to the object referenced by parameter 'nmRemoteSleepIndPtr'
\COUNTERMEASURE \N The caller of this function ensures that the pointer passed to the parameter 'nmRemoteSleepIndPtr' is valid.

\ID                SBSW_UDPNM_DYN_PNINFOLENGTH
\DESCRIPTION       The write access index of array UdpNm_PnClusterReqNew is calculated at runtime by local function UdpNm_DetermineDynamicPnInfoLength().
                   The function UdpNm_DetermineDynamicPnInfoLength() shall always return an index value smaller or equal to the size of UdpNm_PnInfoByteConfig.
                   UdpNm_PnClusterReqNew has a size relation to UdpNm_PnInfoByteConfig.
\COUNTERMEASURE \N A runtime check is performed that ensures the access index is within its defined boundaries.

\ID                SBSW_UDPNM_GETNODEIDENTIFIER
\DESCRIPTION       The functions UdpNm_GetNodeIdentifier and UdpNm_GetLocalNodeIdentifier write to the object referenced by the parameter 'nmNodeIdPtr'.
\COUNTERMEASURE \N The caller of these functions ensures that the pointer passed to the parameter 'nmNodeIdPtr' is valid.

\ID                SBSW_UDPNM_GETPDUDATA
\DESCRIPTION       The function UdpNm_GetPduData writes to the object referenced by parameter 'nmPduDataPtr'.
\COUNTERMEASURE \S The caller of this function must ensure that the pointer passed to the parameter 'nmPduDataPtr'
                   references a valid memory location and that the size of the array referenced by parameter 'nmPduDataPtr'
                   is greater or equal to UdpNm_GetRxMessageDataLengthOfPbChannelConfig(channel). [SMI-146473]

\ID                SBSW_UDPNM_GETSTATE
\DESCRIPTION       The function UdpNm_GetState writes to the object referenced by parameters 'nmStatePtr' and 'nmModePtr'.
\COUNTERMEASURE \N The caller of this function must ensure that the pointers passed to the parameters 'nmStatePtr' and 'nmModePtr' are valid.

\ID                SBSW_UDPNM_GETUSERDATA
\DESCRIPTION       The function UdpNm_GetUserData writes to the object referenced by parameter 'nmUserDataPtr'.
\COUNTERMEASURE \S The caller of this function must ensure that the pointer passed to the parameter 'nmUserDataPtr'
                   references a valid memory location and that the size of the array referenced by parameter 'nmUserDataPtr'
                   is greater or equal to UdpNm_GetRxMessageData_UserDataLengthOfPbChannelConfig(channel). [SMI-146472]

\ID                SBSW_UDPNM_GETVERSIONINFO
\DESCRIPTION       The function UdpNm_GetVersionInfo writes to the object referenced by parameter 'versioninfo'
\COUNTERMEASURE \N The caller of this function ensures that the pointer passed to the parameter 'versioninfo' is valid.

\ID                SBSW_UDPNM_LOCALFUNCTION_CALL
\DESCRIPTION       The pointer 'PduInfoPtr' is passed to the local functions UdpNm_CopyRxMessageData, UdpNm_DetermineDynamicPnInfoLength, UdpNm_PnFilterHandling, UdpNm_CarWakeupIndication.
\COUNTERMEASURE \N Pointer parameter is directly passed through.

\ID                SBSW_UDPNM_PNCLUSTERREQEXTNEW
\DESCRIPTION       The write access index of UdpNm_PnClusterReqExtNew is calculated at runtime. The calculation result shall never exceed the size of UdpNm_PnClusterReqExtNew.
\COUNTERMEASURE \N A runtime check is performed that ensures the access index is within its defined boundaries.

\ID                SBSW_UDPNM_TRIGGER_TRANSMIT
\DESCRIPTION       The function UdpNm_SoAdIfTriggerTransmit writes to the object referenced by parameter 'PduInfoPtr'.
\COUNTERMEASURE \N The caller of this function must ensure that the pointer passed to the parameter 'PduInfoPtr'
                   references a valid memory location. The size is checked during runtime prior to writing the data.

\ID                SBSW_UDPNM_CSL01
\DESCRIPTION       Access of UdpNm_PnClusterReqNew using ComStackLib
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID                SBSW_UDPNM_CSL02
\DESCRIPTION       Access of UdpNm_PnClusterReq, UdpNm_PnClusterReqNew via size relation to UdpNm_PnInfoByteConfig structure and
                   access of UdpNm_PnClusterReqExt, UdpNm_PnClusterReqExtNew via size relation to UdpNm_PbPncClusterConfigExt structure
                   with same index using ComStackLib.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID                SBSW_UDPNM_CSL03
\DESCRIPTION       Access of UdpNm_PnClusterResetTimer, UdpNm_PnClusterResetTimerExt, UdpNm_RxMessageData, UdpNm_TxMessageData using ComStackLib.
\COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID                SBSW_UDPNM_CSL_CHANNEL_INDEX_ACCESS
\DESCRIPTION       Access of UdpNm_TxControlState, UdpNm_TxControlStateReq, UdpNm_TimeoutTimer, UdpNm_RemoteSleepTimer, UdpNm_MsgTimer, UdpNm_MsgConfirmationFlag,
                             UdpNm_MsgIndicationFlag, UdpNm_RepeatMsgBitIndFlag, UdpNm_RepeatMsgTimer, UdpNm_RemoteSleepIndState, UdpNm_ImmediateNmMsgCount,
                             UdpNm_CoordReadyToSleepState, UdpNm_WaitBusSleepTimer, UdpNm_MsgRequest, UdpNm_NmState, UdpNm_NetworkRestartFlag,
                             UdpNm_CommState, UdpNm_RepeatMsgReqFlag, UdpNm_MsgTimeoutTimer
                   via indirection over UdpNm_ChannelConfig structure with same index using ComStackLib.
                   The 'channel' variable which is used as index is always checked.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID                SBSW_UDPNM_CSL_VAR_ACCESS
\DESCRIPTION       A ComStackLib generated variable is accessed.
\COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables
                   address without pointer arithmetic.

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

\ID COV_UDPNM_ACTIVE_WAKEUP_BIT
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_CAR_WAKEUP_FILTER
  \ACCEPT TF tf tx tf
  \ACCEPT TF xf tx tf
  \REASON NodeId cannot be disabled when CarWakeUpFilter is enabled.
          Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_CAR_WAKEUP_RX
  \ACCEPT TF tx tf
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_CHECK_CBVPOSITION
  \ACCEPT TF tx tf
  \ACCEPT TX tx tx
  \ACCEPT TX
  \REASON Decision coverage is not fulfilled in case parameter is not configured to UDPNM_PDU_OFF on all channels or in single channel configurations.
          For code robustness this check is always executed before retrieving the CBV index (even though it is mandatory for PN).

\ID COV_UDPNM_CHECK_NIDPOSITION
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Decision coverage is not fulfilled in case parameter is not configured to UDPNM_PDU_OFF on all channels or in single channel configurations.

\ID COV_UDPNM_COM_CONTROL_ENABLED
  \ACCEPT TX
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_CRI_BIT_ALWAYS_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_DEV_ERROR_DETECT
  \REASON In Safe Configurations the Dev Error Detect switch is always STD_ON. This is globally justified for the regular use case. Special use cases must be justified manually.

\ID COV_UDPNM_IMMEDIATE_TRANSMISSIONS
  \ACCEPT TF tx tf
  \REASON In Configurations with 'Immediate Nm Transmission' > 0 on all channels, the condition can only evaluate to true.

\ID COV_UDPNM_IMMEDIATE_RESTART_ENABLED
  \ACCEPT TX
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_INVALID_CHANNEL_DET
  \ACCEPT TF tf xf
  \REASON If the channel indirections has no invalid elements the decision coverage is not fulfilled.

\ID COV_UDPNM_INVALID_GENDATA
  \ACCEPT XF
  \REASON This statements checks if the static configuration is correctly generated so that all accesses to UdpNm_PbChannelConfig are within its bounds.

\ID COV_UDPNM_MSG_TIMER_GREATER_ZERO
  \ACCEPT TF tf tx tf
  \ACCEPT XF tf xf xx
  \REASON In configurations where Immediate Restart is enabled and an offset is configured, the MsgTimer will always be greater than one.
          In configurations where Immediate Restart is enabled and no offset is configured, the MsgTimer will never be greater than one.
          Resulting from this, no additional transmission is ever sent.

\ID COV_UDPNM_NODE_DETECTION_ENABLED
  \ACCEPT TX
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_NODE_ID_ENABLED
  \ACCEPT TX
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_PN_ENABLED
  \ACCEPT TX
  \ACCEPT TF tf tf tx tx
  \ACCEPT TF tf tf tf tx
  \ACCEPT TF tf tf tx tf
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_PNENABLEDINVARIANT
  \ACCEPT TX
  \REASON Configuration switch PnEiraCalcEnabled and the constant value of "UdpNm_PnEnabledInVariant" is not channel dependent, but may vary in Postbuild-Selectable configurations.
          Therefore it evaluates to TX in pre-compile configurations.

\ID COV_UDPNM_PN_EIRA_CALC
  \ACCEPT TX
  \ACCEPT TF tf tx
  \REASON If PnEnabled differs in variants and Eira Calculation is always configured to the same value in variant/channel where Pn is enabled, decision coverage is not fulfilled.

\ID COV_UDPNM_PN_ERA_CALC
  \ACCEPT TX
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \ACCEPT TF tx tf
  \REASON If PnEraCalc is always enabled if Pn is enabled, the decision coverage is not fulfilled.

\ID COV_UDPNM_PN_ENABLED_UDPNM_TRANSMIT
  \ACCEPT TX tx xf tx xx
  \ACCEPT TF tf xf tx xf
  \ACCEPT TF tf xf tf tf
  \ACCEPT TF tf xf tf xf
  \ACCEPT TF tf xf tf
  \ACCEPT TF tx tf xf
  \ACCEPT TX tx xx
  \ACCEPT TF tx tf
  \ACCEPT TF tf xf
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_PN_FILTER_HANDLING
  \ACCEPT TX tf tx
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_PN_INFO_LENGTH
  \ACCEPT XF
  \REASON Decision coverage is not fulfilled in case PnInfoLength is configured to 1.

\ID COV_UDPNM_PRECOMPILE
  \ACCEPT TX
  \ACCEPT TX tx tx
  \ACCEPT TF tx tf
  \REASON In PreCompile configurations the function is only called with valid channels. Last channel will always be Eira channel.

\ID COV_UDPNM_CHECK_REPEATMSGTIMER
  \ACCEPT TX
  \REASON In Configurations with 'Repeat Message Time' = 0, the condition can only evaluate to true.

\ID COV_UDPNM_REMOTE_SLEEP_IND_STATE_NO_RS_TO_NO
   \REASON There are some configurations where the transition from ReadySleep to NormalOperation is not possible (only channels with PnHandleMultipleNetworkRequest). Therefore
           this if statement will always result in XF, since NormalOperation can never be reached with UpdNm_RemoteSleepIndState true.

\ID COV_UDPNM_REPEAT_MSG_IND_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_RETRY_FIRST_MESSAGE_REQUEST_ENABLED
  \ACCEPT TX
  \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_UDPNM_RUNTIME_CHECK
  \ALWAYS TX
  \REASON To ensure that no out of bounds write access is performed a runtime check is introduced. It shall always evaluate to TX.

\ID COV_UDPNM_REDEFINEABLE
  \ACCEPT TX
  \ACCEPT XF
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to
          allow redefinition using an optional user configuration file.

\ID COV_UDPNM_TRANS_RS_TO_NO
  \ACCEPT XF
  \REASON The transition from ReadySleep to NormalOperation cannot occur, if PnHandleMultipleNetworkRequests is enabled.

\ID COV_UDPNM_TRANS_RS_TO_NO_COMCONTROL
  \ACCEPT XX
  \ACCEPT TX
  \REASON The transition from ReadySleep to NormalOperation cannot occur, if PnHandleMultipleNetworkRequests is enabled. Thus the statement will never be reached.

\ID COV_UDPNM_TRANS_TO_REPEAT_MSG
  \ACCEPT TX
  \REASON The transition to RepeatMessage is not possible from state ReadySleep or NormalOperation without NodeDetection/PnHandleMultipleNetworkRequests enabled.
          Therefore the state cannot be entered with communication disabled.

\ID COV_UDPNM_CHECK_TRANSITION_TO_NETWORKMODE
  \ACCEPT TX
  \REASON In Configurations with 'Node Detection Enabled' = OFF, no transition to NetworkMode from states > NM_STATE_READY_SLEEP is possible.

\ID COV_UDPNM_GEN_DATA_CHECK
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \REASON There is no configuration without PbChannelConfig. For Safe Configurations the Dev Error Detect switch can not be STD_OFF.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: UdpNm.c
 *********************************************************************************************************************/
