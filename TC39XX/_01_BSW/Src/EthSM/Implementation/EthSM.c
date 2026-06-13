/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EthSM.c
 *      Project:  MICROSAR ETH
 *       Module:  Ethernet State Manager
 *    Generator:  Ccl_AsrSmEth.jar
 *
 *  Description:  Source file of MICROSAR Ethernet State Manager.
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

#define ETHSM_SOURCE

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* EthSM Module includes */
#include "EthSM.h"
#include "SchM_EthSM.h"

/* adjacent module includes */
#if ( ETHSM_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif
#include "BswM_EthSM.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthSM header file */
#if (  (ETHSM_SW_MAJOR_VERSION != (4U)) \
    || (ETHSM_SW_MINOR_VERSION != (0U)) \
    || (ETHSM_SW_PATCH_VERSION != (1U)) )
# error "EthSM.c: Source and Header file are inconsistent!"
#endif

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if ( ETHSM_CONFIGURATION_VARIANT != ETHSM_CONFIGURATION_VARIANT_PRECOMPILE )
# error "EthSM.c: Only PreCompile configuration variant supported!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ETHSM_CTRL_CFG_IDX  0
#define ETHSM_TRCV_CFG_IDX  0

/***********************************************************************************************************************
*  LOCAL FUNCTION MACROS
***********************************************************************************************************************/
#if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
/*! Function Macro to check if channel parameter by ComM is valid. */
# define EthSM_IsChannelbyComMInvalid(channel)        ( ( (channel) >= EthSM_GetSizeOfNetIdxByComMNetwHnd() ) ||  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
                               ( EthSM_GetNetIdxByComMNetwHnd(channel) >= EthSM_GetSizeOfChannelConfig() ) ) 

# if ((ETHSM_IS_VECTOR_TCPIP == STD_ON) || (ETHSM_IS_VECTOR_ETHIF == STD_ON))
/*! Function Macro to check if controller parameter by EthIf is valid. */
#  define EthSM_IsChannelbyEthIfInvalid(ctrl)         ( ( (ctrl) >= EthSM_GetSizeOfNetIdxByEthIfCtrlIdx() ) || /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
                               ( EthSM_GetNetIdxByEthIfCtrlIdx(ctrl) >= EthSM_GetSizeOfChannelConfig() ) ) 
#endif
#endif

#if ( ETHSM_IS_VECTOR_TCPIP == STD_ON )
/*! This macro returns the information if at least one IP is used on the given network. */
# define EthSM_IsIpActiveOnNetwork(NetIdx) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
          (boolean)((EthSM_GetActiveIpVxCnt(NetIdx) == 0U) ? FALSE : TRUE)

#endif /* ETHSM_IS_VECTOR_TCPIP */

/***********************************************************************************************************************
*  LOCAL DATA TYPES AND STRUCTURES
***********************************************************************************************************************/

#if !defined (ETHSM_LOCAL) /* COV_ETHSM_REDEFINEABLE */
# define ETHSM_LOCAL static
#endif

#if !defined (ETHSM_LOCAL_INLINE) /* COV_ETHSM_REDEFINEABLE */
# define ETHSM_LOCAL_INLINE LOCAL_INLINE
#endif

/***********************************************************************************************************************
*  LOCAL DATA PROTOTYPES
***********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
 #define ETHSM_START_SEC_CODE

#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthSM_TransOfflineToWaitTrcvLink()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state OFFLINE to WAIT_TRCVLINK.
 *  \details     This function transitions from state OFFLINE to WAIT TRCVLINK, i.e. waits for the EthIf controller to
 *               be initialized and sets the controller mode to ACTIVE, if both are successfully completed it transitions
 *               to WAIT_TRCVLINK.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function must only be called after checking that EthSM_ComMRequestedMode is COMM_FULL_COMMUNICATION!
 *  \trace       DSGN-EthSMCon1334
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOfflineToWaitTrcvLink(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransWaitTrcvLinkToOffline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state WAIT_TRCVLINK to OFFLINE.
 *  \details     This function transitions from state WAIT_TRCVLINK to OFFLINE. The state is WAIT_TRCVLINK,
 *               WAIT_TRCVLINK_TO_OFFLINE or WAIT_CONTROLLER_ACTIVE and controller mode is DOWN, set the state to
 *               OFFLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function must only be called after checking that EthSM_ComMRequestedMode is
 *               COMM_NO_COMMUNICATION!
 *  \trace       DSGN-EthSMCon1333
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitTrcvLinkToOffline(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransWaitTrcvLinkToWaitOnline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state WAIT_TRCVLINK to WAIT_ONLINE.
 *  \details     This function transitions from state WAIT_TRCVLINK to WAIT_ONLINE, i.e. if the TCP IP state online is
 *               requested then transition to WAIT_ONLINE and report the state to BswM.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1335
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitTrcvLinkToWaitOnline(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransWaitOnlineToWaitTrvLink()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state WAIT_ONLINE to WAIT_TRCVLINK.
 *  \details     This function transitions from state WAIT_ONLINE to WAIT_TRCVLINK, i.e. if the requested COM mode is 
 *               OFFLINE then transition to state WAIT_TRCVLINK.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1336
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOnlineToWaitTrvLink(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransWaitOnlineToOffline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state WAIT_ONLINE to OFFLINE.
 *  \details     This function transitions from WAIT_ONLINE to OFFLINE, i.e. NO_COMM is requested, the controller mode
 *               is set to DOWN then transition to state OFFLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1332
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOnlineToOffline(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransWaitOnlineToOnline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state WAIT_ONLINE to ONLINE.
 *  \details     This function transitions from WAIT_ONLINE to ONLINE, i.e. If FULL_COMM is requested and TCP IP mode 
 *               is ONLINE then transition to state ONLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1341
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOnlineToOnline(EthSM_NetworkIdxType NetIdx);

#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  EthSM_TransOnlineToWaitOnline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state ONLINE to WAIT_ONLINE.
 *  \details     This function transitions from ONLINE to WAIT_ONLINE, i.e. If TCP IP state is OFFLINE then transition
 *               to the state WAIT_ONLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      ETHSM_IS_TCPIP_ENABLED == STD_ON
 *  \trace       DSGN-EthSMCon1344
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnlineToWaitOnline(EthSM_NetworkIdxType NetIdx);
#endif /* ETHSM_IS_TCPIP_ENABLED */

/**********************************************************************************************************************
 *  EthSM_TransOnlineToOnhold()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state ONLINE to ONHOLD.
 *  \details     This function transitions from ONLINE to ONHOLD, i.e. If the TrcvLink state is DOWN then transition 
 *               to the EthSM state ONHOLD.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1340
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnlineToOnhold(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransOnlineToWaitOffline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state ONLINE to WAIT_OFFLINE.
 *  \details     This function transitions from ONLINE to WAIT_OFFLINE, i.e. If NO_COMM is requested then transition 
 *               to the EthSM state WAIT_OFFLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1342
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnlineToWaitOffline(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransOnholdToOnline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state ONHOLD to ONLINE.
 *  \details     This function transitions from ONHOLD to ONLINE, i.e. If the TrcvLinkState is ACTIVE then transition
 *               to the EthSM state ONLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1343
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnholdToOnline(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransOnholdToWaitTrcvLink()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state ONHOLD to WAIT_TRCVLINK.
 *  \details     This function transitions from ONHOLD to WAIT_TRCVLINK, i.e. TCP IP state is OFFLINE then transition
 *               to EthSM state WAIT_TRCVLINK.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1338
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnholdToWaitTrcvLink(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransOnholdToOffline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state ONHOLD to OFFLINE.
 *  \details     This function transitions from ONHOLD to OFFLINE, i.e. If NO_COMM is requested then transition to
 *               EthSM state OFFLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1337
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnholdToOffline(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
 *  EthSM_TransWaitOfflineToOffline()
 *********************************************************************************************************************/
/*! \brief       Handle Transition from state WAIT_OFFLINE to OFFLINE.
 *  \details     This function transitions from WAIT_OFFLINE to OFFLINE, i.e.If TCP IP state is OFFLINE then transition
 *               to EthSM state OFFLINE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMCon1331
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOfflineToOffline(EthSM_NetworkIdxType NetIdx);

#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
/**********************************************************************************************************************
 *  EthSM_EthIf_StartTimer()
 *********************************************************************************************************************/
/*! \brief       Starts the EthIf Timer.
 *  \details     This function resets the retries left and restart the timer.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON
 *  \trace       DSGN-EthSM21376
 *********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_EthIf_StartTimer(EthSM_NetworkIdxType NetIdx);

/**********************************************************************************************************************
*  EthSM_EthIf_StopTimer
**********************************************************************************************************************/
/*! \brief       Stops the EthIf Timer.
 *  \details     This function sets the retries left to 0, stops the retry timer. It also sets the Timeout occured to
 *               FALSE.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON
 *  \trace       DSGN-EthSM21376
*********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_EthIf_StopTimer(EthSM_NetworkIdxType NetIdx);
#endif /* ETHSM_ENABLE_ETHIF_API_TIMEOUT */

/**********************************************************************************************************************
*  EthSM_ReportState
**********************************************************************************************************************/
/*! \brief       Reports State to BswM
 *  \details     This function reports the current EthSM state to BswM if its not already reported.
 *  \param[in]   EthSM Network index
 *  \param[in]   EthSM Network mode
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSM21607
*********************************************************************************************************************/
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_ReportState( EthSM_NetworkIdxType NetIdx, EthSM_NetworkModeStateType state );


/**********************************************************************************************************************
*  EthSM_StateMachine
**********************************************************************************************************************/
/*! \brief       State machine for EthSM
 *  \details     This function handles the state transitions.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSMDiag1988
*********************************************************************************************************************/
ETHSM_LOCAL_INLINE FUNC(void, ETHSM_CODE) EthSM_StateMachine(EthSM_NetworkIdxType NetIdx);


/**********************************************************************************************************************
 *  EthSM_EthernetInterfaceTimeout()
 *********************************************************************************************************************/
/*! \brief       Process the EthIf Timeout Handling
 *  \details     This function handles the EthIf timeout if the timer is already running depending upon the value of
 *               the retry timer, i.e. If the value is exceeded or not. Additional checks are performed to see if the
 *               error handling has to be processed if the value is exceeded, otherwise the timer is decremented.
 *  \param[in]   EthSM Network index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       DSGN-EthSM21376
 *********************************************************************************************************************/
ETHSM_LOCAL_INLINE FUNC(void, ETHSM_CODE) EthSM_EthernetInterfaceTimeout(EthSM_NetworkIdxType NetIdx);


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthSM_TransOfflineToWaitTrcvLink
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
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOfflineToWaitTrcvLink(EthSM_NetworkIdxType NetIdx)
{
  /* This function must only be called after checking that EthSM_ComMRequestedMode is COMM_FULL_COMMUNICATION! */
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
  /* #1 Only execute the following function if retry timer has its maximum value */
  if( EthSM_GetRetryTimer(NetIdx) == EthSM_GetConfirmationTimeoutOfChannelConfig(NetIdx) )
#endif
  {
    uint8 ctrlIdx = EthSM_GetEthIfControllerOfChannelConfig(NetIdx);

    /* EthIf Controller Init */
    /* #11 If the current EthSM state is either OFFLINE or WAIT_CONTROLLER_INIT */
    if( (EthSM_GetState(NetIdx) == ETHSM_STATE_OFFLINE) || (EthSM_GetState(NetIdx) == STATE_WAIT_CONTROLLER_INIT) )
    {
      /* #111 If the initialization of controller is successful then set EthSM state to WAIT_CONTROLLER_ACTIVE */
      if( EthIf_ControllerInit(ctrlIdx, ETHSM_CTRL_CFG_IDX) == E_OK )
      {
        EthSM_SetState(NetIdx, STATE_WAIT_CONTROLLER_ACTIVE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      }
      /* #112 Else Set EthSM state to WAIT_CONTROLLER_INIT */
      else
      {
        EthSM_SetState(NetIdx, STATE_WAIT_CONTROLLER_INIT); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      }
    }

    /* EthIf Controller Mode Active */
    /* #12 If the current EthSM state is WAIT_CONTROLLER_ACTIVE or WAIT_TRCVLINK_TO_OFFLINE */
    if( (EthSM_GetState(NetIdx) == STATE_WAIT_CONTROLLER_ACTIVE) ||
        (EthSM_GetState(NetIdx) == STATE_WAIT_TRCVLINK_TO_OFFLINE) )
    {
      /* #121 If the controller mode is successfully set to ACTIVE */
      if( EthIf_SetControllerMode(ctrlIdx, ETH_MODE_ACTIVE) == E_OK )
      {
        /* #1211 Set the EthSM state to STATE_WAIT_TRCVLINK and Inform BswM about the state change */
        EthSM_SetState(NetIdx, ETHSM_STATE_WAIT_TRCVLINK); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
        EthSM_ReportState(NetIdx, ETHSM_BSWM_WAIT_TRCVLINK);
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
        /* #1212 Stop the EthIf timer */
        EthSM_EthIf_StopTimer(NetIdx);
#endif
      }
    }
  }
}

/**********************************************************************************************************************
 *  EthSM_TransWaitTrcvLinkToOffline
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
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitTrcvLinkToOffline(EthSM_NetworkIdxType NetIdx)
{
  /* This function must only be called after checking that EthSM_ComMRequestedMode is COMM_NO_COMMUNICATION and the state is
   * ETHSM_STATE_WAIT_TRCVLINK or STATE_WAIT_TRCVLINK_TO_OFFLINE or STATE_WAIT_CONTROLLER_ACTIVE or STATE_WAIT_CONTROLLER_INIT! */
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT ==  STD_ON )
  /* #1 Only execute the following function if retry timer has its maximum value */
  if( EthSM_GetRetryTimer(NetIdx) == EthSM_GetConfirmationTimeoutOfChannelConfig(NetIdx) )
#endif
  {
    /* #11 State is WAIT_CONTROLLER_INIT then set the EthSM state to OFFLINE */
    if( EthSM_GetState(NetIdx) == STATE_WAIT_CONTROLLER_INIT )
    {
      EthSM_SetState(NetIdx, ETHSM_STATE_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      /* #111 Notify ETHSM_BSWM_OFFLINE state to ComM and BswM */
      EthSM_ReportState(NetIdx, ETHSM_BSWM_OFFLINE);
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      /* #112 Stop the EthIf timer */
      EthSM_EthIf_StopTimer(NetIdx);
#endif
    }
    /* #12 If State is WAIT_TRCVLINK or WAIT_TRCVLINK_TO_OFFLINE or WAIT_CONTROLLER_ACTIVE */
    else
    {
      /* #121 If the controller mode is successfully set to DOWN then set the EthSM state to OFFLINE */
      if( EthIf_SetControllerMode(EthSM_GetEthIfControllerOfChannelConfig(NetIdx), ETH_MODE_DOWN ) == E_OK )
      {
        EthSM_SetState(NetIdx, ETHSM_STATE_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
        /* #1211 Notify ETHSM_BSWM_OFFLINE state to ComM and BswM */
        EthSM_ReportState(NetIdx, ETHSM_BSWM_OFFLINE);
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
        /* #1212 Stop the EthIf timer */
        EthSM_EthIf_StopTimer(NetIdx);
#endif
      }
      /* #122 If the current controller state is WAIT_TRCVLINK or WAIT_TRCVLINK_TO_OFFLINE then set the EthSM state to WAIT_TRCVLINK_TO_OFFLINE */
      else if( ( EthSM_GetState(NetIdx) == ETHSM_STATE_WAIT_TRCVLINK ) || ( EthSM_GetState(NetIdx) == STATE_WAIT_TRCVLINK_TO_OFFLINE ) )
      {
        EthSM_SetState(NetIdx, STATE_WAIT_TRCVLINK_TO_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      }
      else
      {
        /* State stays STATE_WAIT_CONTROLLER_ACTIVE */
        /* nothing to do, only for MISRA compliance */
      }
    }
  }
}

/**********************************************************************************************************************
 *  EthSM_TransWaitTrcvLinkToWaitOnline
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitTrcvLinkToWaitOnline(EthSM_NetworkIdxType NetIdx)
{
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
  Std_ReturnType isModeSetSucceeded = E_OK; /* PRQA S 2981 */ /* MD_EthSM_2981 */
  /* #1 If the stack type of the current network is TCPIP */
  if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
  {
    /* #11 Request the Transition to TcpIP mode ONLINE */
    isModeSetSucceeded = TcpIp_RequestComMode(EthSM_GetEthIfControllerOfChannelConfig(NetIdx), TCPIP_STATE_ONLINE);
  }
  /* #2 If TCPIP state is successfully set to state ONLINE, set ETHSM state to WAIT_ONLINE*/
  if( isModeSetSucceeded == E_OK )
  {
#endif /* ETHSM_IS_TCPIP_ENABLED */
    EthSM_SetState(NetIdx, ETHSM_STATE_WAIT_ONLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    /* #21 Notify ETHSM_BSWM_WAIT_ONLINE state to BswM */
    EthSM_ReportState(NetIdx, ETHSM_BSWM_WAIT_ONLINE);
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
  }
#endif
}

/**********************************************************************************************************************
 *  EthSM_TransWaitOnlineToWaitTrvLink
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOnlineToWaitTrvLink(EthSM_NetworkIdxType NetIdx)
{
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
  Std_ReturnType isModeSetSucceeded = E_OK; /* PRQA S 2981 */ /* MD_EthSM_2981 */
  /* #1 If the stack type of the current network is TCPIP */
  if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
  {
    /* #11 Request the transition to TCPIP mode OFFLINE */
    isModeSetSucceeded = TcpIp_RequestComMode(EthSM_GetEthIfControllerOfChannelConfig(NetIdx), TCPIP_STATE_OFFLINE);
  }
  /* #2 If TCPIP state is successfully set to state OFFLINE, set ETHSM state to WAIT_TRCVLINK*/
  if( isModeSetSucceeded == E_OK )
  {
#endif
    EthSM_SetState(NetIdx, ETHSM_STATE_WAIT_TRCVLINK); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    /* #21 Notify ETHSM_BSWM_WAIT_TRCVLINK state to BswM */
    EthSM_ReportState(NetIdx, ETHSM_BSWM_WAIT_TRCVLINK);
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
  }
#endif
}

/**********************************************************************************************************************
 *  EthSM_TransWaitOnlineToOffline
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
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOnlineToOffline(EthSM_NetworkIdxType NetIdx)
{
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
  /* #1 Only execute the following function if retry timer has its maximum value */
  if( EthSM_GetRetryTimer(NetIdx) == EthSM_GetConfirmationTimeoutOfChannelConfig(NetIdx) )
#endif /* ETHSM_ENABLE_ETHIF_API_TIMEOUT */
  {
    Std_ReturnType isModeSetSucceeded = E_OK; /* PRQA S 2981 */ /* MD_EthSM_2981 */
    uint8 ctrlIdx = EthSM_GetEthIfControllerOfChannelConfig(NetIdx);

#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
    /* #11 If the stack type of the current network is TCPIP */
    if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
    {
      /* #111 Request TCPIP mode OFFLINE */
      isModeSetSucceeded = TcpIp_RequestComMode(ctrlIdx, TCPIP_STATE_OFFLINE);
    }
#endif

    /* #12 Set the EthIf controller mode to DOWN */
    isModeSetSucceeded |= EthIf_SetControllerMode(ctrlIdx, ETH_MODE_DOWN); /* PRQA S 2986 */ /* MD_EthSM_2986 */
    /* #13 If TCPIP state is OFFLINE and Controller mode is set to DOWN */
    if( isModeSetSucceeded == E_OK )
    {
      /* #131 Set ETHSM state to OFFLINE */
      EthSM_SetState(NetIdx, ETHSM_STATE_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      /*#132 Notify ETHSM_BSWM_OFFLINE state to BswM */
      EthSM_ReportState(NetIdx, ETHSM_BSWM_OFFLINE);
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      /* #133 Stop the EthIf timer */
      EthSM_EthIf_StopTimer(NetIdx);
#endif
    }
    else
    {
      EthSM_SetState(NetIdx, STATE_WAIT_ONLINE_TO_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    }
  }
}

/**********************************************************************************************************************
 *  EthSM_TransWaitOnlineToOnline
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOnlineToOnline(EthSM_NetworkIdxType NetIdx)
{
  ComM_ModeType modeToPass = COMM_FULL_COMMUNICATION;
  /* #1 Set the ComM Mode to COMM_FULL_COMMUNICATION */
  EthSM_SetMode(NetIdx, COMM_FULL_COMMUNICATION); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #2 Set the state to ETHSM_STATE_ONLINE */
  EthSM_SetState(NetIdx, ETHSM_STATE_ONLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #3 Notify the COMM_FULL_COMMUNICATION and ETHSM_BSWM_ONLINE state to ComM and BswM respectively */
  ComM_BusSM_ModeIndication(EthSM_GetComMNetworkHandleOfChannelConfig(NetIdx), &modeToPass); /* SBSW_ETHSM_ADDRESS_TOBUSSM */
  EthSM_ReportState(NetIdx, ETHSM_BSWM_ONLINE);
}

#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  EthSM_TransOnlineToWaitOnline
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnlineToWaitOnline(EthSM_NetworkIdxType NetIdx)
{
  ComM_ModeType modeToPass = COMM_NO_COMMUNICATION;
  /* #1 Set the ComM Mode to COMM_NO_COMMUNICATION */
  EthSM_SetMode(NetIdx, COMM_NO_COMMUNICATION); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #2 Set the state to ETHSM_STATE_WAIT_ONLINE */
  EthSM_SetState(NetIdx, ETHSM_STATE_WAIT_ONLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #3 Notify the COMM_NO_COMMUNICATION and ETHSM_BSWM_WAIT_ONLINE state to ComM and BswM respectively */
  ComM_BusSM_ModeIndication(EthSM_GetComMNetworkHandleOfChannelConfig(NetIdx), &modeToPass); /* SBSW_ETHSM_ADDRESS_TOBUSSM */
  EthSM_ReportState(NetIdx, ETHSM_BSWM_WAIT_ONLINE);
}
#endif /* ETHSM_IS_TCPIP_ENABLED */

/**********************************************************************************************************************
 *  EthSM_TransOnlineToOnhold
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
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnlineToOnhold(EthSM_NetworkIdxType NetIdx)
{
#if( ETHSM_IS_TCPIP_ENABLED == STD_ON )
  Std_ReturnType isModeSetSucceeded = E_OK; /* PRQA S 2981 */ /* MD_EthSM_2981 */
  /* #1 If the stack type of the current network is TCPIP request the mode TCPIP_STATE_ONHOLD */
  if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
  {
    isModeSetSucceeded = TcpIp_RequestComMode(EthSM_GetEthIfControllerOfChannelConfig(NetIdx), TCPIP_STATE_ONHOLD);
  }
  /* #2 If the mode is successfully set to TCPIP_STATE_ONHOLD */
  if( isModeSetSucceeded == E_OK )
#endif /* ETHSM_IS_TCPIP_ENABLED */
  {
    /* #21 Set the ETHSM state to ONHOLD */
    EthSM_SetState(NetIdx, ETHSM_STATE_ONHOLD); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    /* #22 Notify BswM about the current ETHSM state */
    EthSM_ReportState(NetIdx, ETHSM_BSWM_ONHOLD);
#if ( ETHSM_IS_LINK_DOWN_DEM_ENABLED == STD_ON )
    /* #23 Only report a DEM event if it is configured (DEM Event ID 0U is invalid) */
    if( EthSM_GetLinkDownDemEnabledOfChannelConfig(NetIdx) != DEM_EVENT_INVALID ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_0 */
    {
      (void)Dem_ReportErrorStatus(EthSM_GetLinkDownDemEnabledOfChannelConfig(NetIdx), DEM_EVENT_STATUS_FAILED);
    }
#endif /* ETHSM_IS_LINK_DOWN_DEM_ENABLED */
  }
}

/**********************************************************************************************************************
 *  EthSM_TransOnlineToWaitOffline
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnlineToWaitOffline(EthSM_NetworkIdxType NetIdx)
{
#if( ETHSM_IS_TCPIP_ENABLED == STD_ON )
  Std_ReturnType isModeSetSucceeded = E_OK; /* PRQA S 2981 */ /* MD_EthSM_2981 */
  /* #1 If the stack type of the current network is TCPIP then request mode TCPIP_STATE_OFFLINE */
  if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
  {
    isModeSetSucceeded = TcpIp_RequestComMode(EthSM_GetEthIfControllerOfChannelConfig(NetIdx), TCPIP_STATE_OFFLINE);
  }
  /* #2 If the mode is successfully set to TCPIP_STATE_OFFLINE */
  if( isModeSetSucceeded == E_OK )
#endif /* ETHSM_IS_TCPIP_ENABLED */
  {
    /* #21 Set the ETHSM state to WAIT_OFFLINE */
    EthSM_SetState(NetIdx, ETHSM_STATE_WAIT_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    /* #22 Notify ETHSM_BSWM_WAIT_OFFLINE state to BswM */
    EthSM_ReportState(NetIdx, ETHSM_BSWM_WAIT_OFFLINE);
  }
}

/**********************************************************************************************************************
 *  EthSM_TransOnholdToOnline
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
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnholdToOnline(EthSM_NetworkIdxType NetIdx)
{
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
  Std_ReturnType isModeSetSucceeded = E_OK; /* PRQA S 2981 */ /* MD_EthSM_2981 */
  /* #1 If the stack type of the current network is TCPIP then request mode TCPIP_STATE_ONLINE */
  if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
  {
    isModeSetSucceeded = TcpIp_RequestComMode(EthSM_GetEthIfControllerOfChannelConfig(NetIdx), TCPIP_STATE_ONLINE);
  }
  /* #2 If the mode is successfully set to TCPIP_STATE_ONLINE */
  if( E_OK == isModeSetSucceeded )
#endif
  {
    /* #21 Set the ETHSM state to ONLINE */
    EthSM_SetState(NetIdx, ETHSM_STATE_ONLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    /* #22 Notify ETHSM_BSWM_ONLINE state to BswM */
    EthSM_ReportState(NetIdx, ETHSM_BSWM_ONLINE);
#if ( ETHSM_IS_LINK_DOWN_DEM_ENABLED == STD_ON )
    /* #23 Only report a DEM event if it is configured (DEM Event ID 0U is invalid) */
    if( EthSM_GetLinkDownDemEnabledOfChannelConfig(NetIdx) != DEM_EVENT_INVALID ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_0 */
    {
      (void)Dem_ReportErrorStatus(EthSM_GetLinkDownDemEnabledOfChannelConfig(NetIdx), DEM_EVENT_STATUS_PASSED);
    }
#endif
  }
}

/**********************************************************************************************************************
 *  EthSM_TransOnholdToWaitTrcvLink
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnholdToWaitTrcvLink(EthSM_NetworkIdxType NetIdx)
{
  ComM_ModeType modeToPass = COMM_NO_COMMUNICATION;
  /* #1 Set the ComM Mode to COMM_NO_COMMUNICATION */
  EthSM_SetMode(NetIdx, COMM_NO_COMMUNICATION); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #2 Set the ETHSM state to WAIT_TRCVLINK */
  EthSM_SetState(NetIdx, ETHSM_STATE_WAIT_TRCVLINK); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #3 Notify the mode and WAIT_TRCVLINK state to ComM and BswM */
  ComM_BusSM_ModeIndication(EthSM_GetComMNetworkHandleOfChannelConfig(NetIdx), &modeToPass); /* SBSW_ETHSM_ADDRESS_TOBUSSM */
  EthSM_ReportState(NetIdx, ETHSM_BSWM_WAIT_TRCVLINK);
}

/**********************************************************************************************************************
 *  EthSM_TransOnholdToOffline
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
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransOnholdToOffline(EthSM_NetworkIdxType NetIdx)
{
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
  /* #1 Only execute the following function if retry timer has its maximum value */
  if( EthSM_GetRetryTimer(NetIdx) == EthSM_GetConfirmationTimeoutOfChannelConfig(NetIdx) )
#endif
  {
    Std_ReturnType isModeSetSucceeded = E_OK; /* PRQA S 2981 */ /* MD_EthSM_2981 */
    uint8 ctrlIdx = EthSM_GetEthIfControllerOfChannelConfig(NetIdx);
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
    /* #11 If the stack type of the current network is TCPIP then request TCPIP mode OFFLINE*/
    if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
    {
      isModeSetSucceeded = TcpIp_RequestComMode(ctrlIdx, TCPIP_STATE_OFFLINE);
    }
#endif
    /* #12 Set the controller mode to DOWN */
    isModeSetSucceeded |= EthIf_SetControllerMode(ctrlIdx, ETH_MODE_DOWN); /* PRQA S 2986 */ /* MD_EthSM_2986 */
    /* #13 If request of TCPIP state OFFLINE and ETHIF mode DOWN was successful */
    if( isModeSetSucceeded == E_OK )
    {
      ComM_ModeType modeToPass = COMM_NO_COMMUNICATION;
      /* #131 Set the ComM mode to NO_COMMUNICATION and set ETHSM state to OFFLINE */
      EthSM_SetMode(NetIdx, COMM_NO_COMMUNICATION); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetState(NetIdx, ETHSM_STATE_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      /* #132 Notify ComM about the mode change to COMM_NO_COMMUNICATION */
      ComM_BusSM_ModeIndication(EthSM_GetComMNetworkHandleOfChannelConfig(NetIdx), &modeToPass); /* SBSW_ETHSM_ADDRESS_TOBUSSM */
      /* #133 Notify BswM about the state change to OFFLINE */
      EthSM_ReportState(NetIdx, ETHSM_BSWM_OFFLINE);
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      /* #134 Stop the EthIf timer */
      EthSM_EthIf_StopTimer(NetIdx);
#endif
    }
    /*#14 If any mode request was not successful, trigger the transition to ONHOLD_TO_OFFLINE */
    else
    {
      EthSM_SetState(NetIdx, STATE_ONHOLD_TO_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    }
  }
}

/**********************************************************************************************************************
 *  EthSM_TransWaitOfflineToOffline
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
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_TransWaitOfflineToOffline(EthSM_NetworkIdxType NetIdx)
{
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
  /* #1 Only execute the following function if retry timer has its maximum value */
  if( EthSM_GetRetryTimer(NetIdx) == EthSM_GetConfirmationTimeoutOfChannelConfig(NetIdx) )
#endif
  {
    Std_ReturnType isModeSetSucceeded;
    uint8 ctrlIdx = EthSM_GetEthIfControllerOfChannelConfig(NetIdx);
    /* #11 Set the controller Mode to DOWN */
    isModeSetSucceeded = EthIf_SetControllerMode(ctrlIdx, ETH_MODE_DOWN);
    /* #12 If ETHIF mode to DOWN was successful */
    if( isModeSetSucceeded == E_OK )
    {
      ComM_ModeType modeToPass = COMM_NO_COMMUNICATION;
      /* #121 SetComMMode to NO_COMMUNICATION */
      EthSM_SetMode(NetIdx, COMM_NO_COMMUNICATION); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      /* #122 Set ETHSM state to OFFLINE */
      EthSM_SetState(NetIdx, ETHSM_STATE_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      /* #123 Notify ComM about the mode change to COMM_NO_COMMUNICATION */
      ComM_BusSM_ModeIndication(EthSM_GetComMNetworkHandleOfChannelConfig(NetIdx), &modeToPass); /* SBSW_ETHSM_ADDRESS_TOBUSSM */
      /* #124 Notify OFFLINE state to BswM */
      EthSM_ReportState(NetIdx, ETHSM_BSWM_OFFLINE);
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      /* #125 Stop the EthIf timer */
      EthSM_EthIf_StopTimer(NetIdx);
#endif
    }
    /* #13 If any mode request was not successful, trigger the transition WAIT_OFFLINE_TO_OFFLINE */
    else
    {
      EthSM_SetState(NetIdx, STATE_WAIT_OFFLINE_TO_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    }
  }
}

#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
/**********************************************************************************************************************
 *  EthSM_EthIf_StartTimer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_EthIf_StartTimer(EthSM_NetworkIdxType NetIdx)
{
  /* #1 Reset the retries left */
  EthSM_SetRetriesLeft(NetIdx, (uint8)(EthSM_GetMaxRetriesOfChannelConfig(NetIdx) + 1U)); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #2 Reset the timer */
  EthSM_SetRetryTimer(NetIdx, EthSM_GetConfirmationTimeoutOfChannelConfig(NetIdx)); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
}

/**********************************************************************************************************************
*  EthSM_EthIf_StopTimer
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_EthIf_StopTimer(EthSM_NetworkIdxType NetIdx)
{
  /* #1 Set the retries left to 0 */
  EthSM_SetRetriesLeft(NetIdx, 0U); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #2 Stop the retry timer */
  EthSM_SetRetryTimer(NetIdx, 0U); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  /* #3 Set the timeout occurred to FALSE */
  EthSM_SetTimeoutOccured(NetIdx, FALSE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
}

/**********************************************************************************************************************
 *  EthSM_EthernetInterfaceTimeout
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
ETHSM_LOCAL_INLINE FUNC(void, ETHSM_CODE) EthSM_EthernetInterfaceTimeout(EthSM_NetworkIdxType NetIdx)
{
  /* EthIf API call timeout handling. */
  /* #1 Check if retry timer is already running */
  if( EthSM_GetRetryTimer(NetIdx) != 0U )
  {
    /* #11 Decrement retry timer */
    EthSM_DecRetryTimer(NetIdx); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */

    /* #12 If last retry was executed in this task cycle (state handling is done before timer handling) */
    if( ( EthSM_GetRetriesLeft(NetIdx) == 1U ) && ( EthSM_GetTimeoutOccured(NetIdx) == FALSE ) )
    {
      /* #121 Remember that timeout error occurred, must be only reported once (unless the error recovers) */
      EthSM_SetTimeoutOccured(NetIdx, TRUE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */

      /* #122 Report Det and Dem errors directly, without waiting for the last retry timeout */
# if ( ETHSM_DEV_ERROR_REPORT == STD_ON )
      (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_MAIN_FUNCTION, ETHSM_E_ETHIF_TIMEOUT);
# endif
# if ( ETHSM_IS_ETHIF_TIMEOUT_DEM_ENABLED == STD_ON )
      if( EthSM_GetTimeoutDemEnabledOfChannelConfig(NetIdx) != DEM_EVENT_INVALID ) /* PRQA S 2741 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_0 */
      {
        (void)Dem_ReportErrorStatus(EthSM_GetTimeoutDemEnabledOfChannelConfig(NetIdx), DEM_EVENT_STATUS_FAILED);
      }
# endif
    }

    /* #13 Check if the retry timer has expired */
    if( EthSM_GetRetryTimer(NetIdx) == 0U )
    {
      /* #131 Decrement retries to initiate next retry cycle */
      EthSM_DecRetriesLeft(NetIdx); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */

      /* #132 If no retries are left */
      if( EthSM_GetRetriesLeft(NetIdx) == 0U )
      {
        /* #1321 Restart the retry timer and reset retries */
        EthSM_EthIf_StartTimer(NetIdx);
      }
      /* #133 If retries are still left, reset timeout. */
      else
      {
        EthSM_SetRetryTimer(NetIdx, EthSM_GetConfirmationTimeoutOfChannelConfig(NetIdx)); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHSM_ENABLE_ETHIF_API_TIMEOUT */

/**********************************************************************************************************************
 *  EthSM_ReportState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSM_LOCAL FUNC(void, ETHSM_CODE) EthSM_ReportState( EthSM_NetworkIdxType NetIdx, EthSM_NetworkModeStateType state )
{
  /* #1 Report current state to BswM if the state has not been reported before. */
  if( state != EthSM_GetLastReportedState(NetIdx) )
  {
    BswM_EthSM_CurrentState(EthSM_GetComMNetworkHandleOfChannelConfig(NetIdx), state);
    EthSM_SetLastReportedState(NetIdx, state); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
  }
}

/**********************************************************************************************************************
 *  EthSM_StateMachine
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
ETHSM_LOCAL_INLINE FUNC(void, ETHSM_CODE) EthSM_StateMachine(EthSM_NetworkIdxType NetIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ComM_ModeType requestedMode = EthSM_GetRequestedMode(NetIdx);
  EthTrcv_LinkStateType trcvLinkState = EthSM_GetTrcvLinkState(NetIdx);
  TcpIp_StateType tcpIpState = EthSM_GetTcpIpState(NetIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_EthSM_2983 */

  /* #0 Handling of state transitions. */
  switch( EthSM_GetState(NetIdx) )
  {
  /*-----------------------ETHSM_STATE_OFFLINE-------------------------------*/
  /* #1 Check if the ETHSM state is OFFLINE */
  case ETHSM_STATE_OFFLINE:
    /* #1.1 Full communication is requested */
    if( requestedMode == COMM_FULL_COMMUNICATION )
    {
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      /* #1.11 If the EthIf API timeout is on then start the timer, trigger a transition from the state OFFLINE to WAIT_TRCVLINK */
      EthSM_EthIf_StartTimer(NetIdx);
#endif
      EthSM_TransOfflineToWaitTrcvLink(NetIdx);
    }
    break;
  /*-----------------------ETHSM_STATE_WAIT_TRCVLINK-------------------------*/
  /* #2 Check if the current EthSM state is WAIT_TRCVLINK */
  case ETHSM_STATE_WAIT_TRCVLINK:
    /* #2.1 If NO_COMM is requested */
    if( requestedMode == COMM_NO_COMMUNICATION )
    {
      /* #2.11 If the EthIf API timeout is on then start the timer, make a transition from the state WAIT_TRCVLINK to OFFLINE */
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      EthSM_EthIf_StartTimer(NetIdx);
#endif
      EthSM_TransWaitTrcvLinkToOffline(NetIdx);
    }
    /* #2.2 Check if the TrcvLinkstate is active then make a transition from WAIT_TRCVLINK to WAIT ONLINE*/
    else if( trcvLinkState == ETHTRCV_LINK_STATE_ACTIVE )
    {
      EthSM_TransWaitTrcvLinkToWaitOnline(NetIdx);
    }
    else
    {
      /* nothing to do, only for MISRA compliance */
    }
    break;
  /*-----------------------ETHSM_STATE_WAIT_ONLINE---------------------------*/
  /* #3 Check if the current EthSM state is WAIT ONLINE */
  case ETHSM_STATE_WAIT_ONLINE:
    /* #3.1 If NO_COMM is requested */
    if( requestedMode == COMM_NO_COMMUNICATION )
    {
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      EthSM_EthIf_StartTimer(NetIdx);
#endif
      /* #3.11 Start the EthIf timeout timer make a transition from WAIT ONLINE to OFFLINE */
      EthSM_TransWaitOnlineToOffline(NetIdx);
    }
    /* #3.2 Check if the TrcvLink state is down then make a transition from WAIT ONLINE to WAIT_TRCVLINK */
    else if( trcvLinkState == ETHTRCV_LINK_STATE_DOWN )
    {
      EthSM_TransWaitOnlineToWaitTrvLink(NetIdx); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    /* #3.3 If the stack type of the current network is AVB or TCPIP and TCP IP state is ONLINE then make a transition from WAIT ONLINE to ONLINE */
    /*lint -save -e506 */
    else if( ( ( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP ) && ( tcpIpState == TCPIP_STATE_ONLINE ) )
    || ( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_AVB ) ) /* PRQA S 2991 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
    /*lint -restore */
    {
      EthSM_TransWaitOnlineToOnline(NetIdx);
    }
    else
    {
      /* nothing to do, only for MISRA compliance */
    }
    break;
  /*-----------------------ETHSM_STATE_ONLINE--------------------------------*/
  /* #4 Check if EthSM state is ONLINE */
  case ETHSM_STATE_ONLINE:
    /* #4.1 If TrcvLinkState is DOWN, trigger transition from ONLINE to ONHOLD */
    if( trcvLinkState == ETHTRCV_LINK_STATE_DOWN )
    {
      EthSM_TransOnlineToOnhold(NetIdx);
    }
    /* #4.2 If TrcvLinkState is ACTIVE */
    else
    {
      /* #4.21 If NO_COM is requested, trigger transition from ONLINE to WAIT OFFLINE */
      if( requestedMode == COMM_NO_COMMUNICATION )
      {
        EthSM_TransOnlineToWaitOffline(NetIdx);
      }
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
      /* #4.22 If the stack type of the current network is TCPIP and requested TcpIp state is OFFLINE, trigger transition from ONLINE to WAIT ONLINE */
      else if( (EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP) && (tcpIpState == TCPIP_STATE_OFFLINE) ) /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
      {
        EthSM_TransOnlineToWaitOnline(NetIdx);
      }
#endif
      else
      {
        /* nothing to do, only for MISRA compliance */
      }
    }
    break;
  /*-----------------------ETHSM_STATE_ONHOLD--------------------------------*/
  /* #5 Check if the the EthSM state is ONHOLD */
  case ETHSM_STATE_ONHOLD:
    /* #5.1 If NO_COMM is requested then start the EthIf timer and make a transition from ONHOLD to OFFLINE*/
    if( requestedMode == COMM_NO_COMMUNICATION )
    {
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      EthSM_EthIf_StartTimer(NetIdx);
#endif
      EthSM_TransOnholdToOffline(NetIdx);
    }
    /* #5.2 Else, if the stack type of the current network is TCPIP and TCP IP state is OFFLINE then make a transition from ONHOLD to WAIT_TRCVLINK */
    else if( (EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP) && (tcpIpState == TCPIP_STATE_OFFLINE) ) /* PRQA S 2741, 2992 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
    {
      EthSM_TransOnholdToWaitTrcvLink(NetIdx); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    /* #5.3 Check if TrcvLinkState is active then make a transition from ONHOLD to ONLINE */
    else if( trcvLinkState == ETHTRCV_LINK_STATE_ACTIVE )
    {
      EthSM_TransOnholdToOnline(NetIdx);
    }
    /* #5.4 Else, if the stack type of the current network is AVB then make a transition from ONHOLD to WAIT_TRCVLINK */
    else if( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_AVB ) /* PRQA S 2741, 2742 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
    {
      EthSM_TransOnholdToWaitTrcvLink(NetIdx); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else
    {
      /* nothing to do, only for MISRA compliance */
    }
    break;
  /*-----------------------ETHSM_STATE_WAIT_OFFLINE--------------------------*/
  /* #6 Check if the current EthSM state is WAIT OFFLINE */
  case ETHSM_STATE_WAIT_OFFLINE:
#if ( ETHSM_IS_VECTOR_TCPIP == STD_OFF )
    /* #6.1 If the stack type of the current network is AVB or TCPIP and state is OFFLINE then make transition from WAIT OFFLINE to OFFLINE */
    /*lint -save -e506 */
    if( ( (EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_TCPIP) && (tcpIpState == TCPIP_STATE_OFFLINE) )
    || ( EthSM_GetStackTypeOfChannelConfig(NetIdx) == ETHSM_STACK_TYPE_AVB ) ) /* PRQA S 2991 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */

    /*lint -restore */
#endif
     {
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
    /* #6.2 If its a Vector TCP IP stack start the timer and trigger the transition from WAIT OFFLINE to OFFLINE */
      EthSM_EthIf_StartTimer(NetIdx);
#endif
      EthSM_TransWaitOfflineToOffline(NetIdx);
     }
#if ( ETHSM_IS_VECTOR_TCPIP == STD_OFF )
    else
     {
       /* nothing to do, only for MISRA compliance */
     }
#endif
   break;
  /*-----------------------STATE_ONHOLD_TO_OFFLINE---------------------------*/
  /* #7 Check if the current EthSM state is ONHOLD_TO_OFFLINE */
  case STATE_ONHOLD_TO_OFFLINE:
    /* #7.1 Trigger a transition from ONHOLD state to OFFLINE */
    EthSM_TransOnholdToOffline(NetIdx);
    break;
  /*-----------------------STATE_WAIT_OFFLINE_TO_OFFLINE---------------------*/
  /* #8 Check if the current EthSM state is WAIT_OFFLINE_TO_OFFLINE */
  case STATE_WAIT_OFFLINE_TO_OFFLINE:
    /* #8.1 Trigger a transition from WAIT OFFLINE state to OFFLINE */
    EthSM_TransWaitOfflineToOffline(NetIdx);
    break;
  /*-----------------------STATE_WAIT_CONTROLLER_INIT------------------------*/
  /* #9 Check if the current EthSM state is WAIT_CONTROLLER_INIT */
  case STATE_WAIT_CONTROLLER_INIT:
    /* #9.1 If FULL_COM is requested then go from OFFLINE to WAIT_TRCVLINK */
    if( requestedMode == COMM_FULL_COMMUNICATION )
    {
      EthSM_TransOfflineToWaitTrcvLink(NetIdx);
    }
    /* #9.2 If full communication is not requested then go from WAIT_TRCVLINK to OFFLINE */
    else
    {
      EthSM_TransWaitTrcvLinkToOffline(NetIdx);
    }
    break;
  /*-----------------------------STATE_WAIT_CONTROLLER_ACTIVE----------------*/
  /* #10 Check if the current EthSM state is WAIT_CONTROLLER_ACTIVE */
  case STATE_WAIT_CONTROLLER_ACTIVE:
    /* #10.1 If full communication is requested then go from OFFLINE to WAIT_TRCVLINK */
    if( requestedMode == COMM_FULL_COMMUNICATION )
    {
      EthSM_TransOfflineToWaitTrcvLink(NetIdx);
    }
    /* #10.2 If full communication is not requested then go from WaitTrcv link to OFFLINE */
    else
    {
      EthSM_TransWaitTrcvLinkToOffline(NetIdx);
    }
    break;
  /*-----------------------STATE_WAIT_TRCVLINK_TO_OFFLINE--------------------*/
  /* #11 Check if the current EthSM state is WAIT_TRCVLINK_TO_OFFLINE */
  case STATE_WAIT_TRCVLINK_TO_OFFLINE:
    /* #11.1 If NO_COMM is requested then go from WAIT_TRCVLINK to OFFLINE */
    if( requestedMode == COMM_NO_COMMUNICATION )
    {
      EthSM_TransWaitTrcvLinkToOffline(NetIdx);
    }
    /* #11.2 FULL_COMM is requested then go from OFFLINE to WAIT_TRCVLINK */
    else
    {
      EthSM_TransOfflineToWaitTrcvLink(NetIdx);
    }
    break;
  /*-----------------------STATE_WAIT_ONLINE_TO_OFFLINE----------------------*/
  /* #12 Check if the current EthSM state is WAIT_ONLINE_TO_OFFLINE */
  case STATE_WAIT_ONLINE_TO_OFFLINE:
    /* #12.1 Go from WAIT ONLINE state to OFFLINE */
    EthSM_TransWaitOnlineToOffline(NetIdx);
    break;
  default: /* COV_ETHSM_RT_NOT_REACHABLE */
    /* nothing to do, only for MISRA compliance */
    break;
  }
} /* EthSM_StateMachine */ /* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */ /*lint !e438 !e550 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  EthSM_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHSM_CODE) EthSM_InitMemory(void)
{
  /* #1 Set global state to not initialized */
  EthSM_SetInitialized(FALSE); /* SBSW_ETHSM_CSL_VAR_ACCESS */
} /* EthSM_InitMemory() */


/**********************************************************************************************************************
 *  EthSM_RequestComMode
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
FUNC(Std_ReturnType, ETHSM_CODE) EthSM_RequestComMode(VAR(NetworkHandleType, AUTOMATIC) NetworkHandle, VAR(ComM_ModeType, AUTOMATIC) Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that module is initialized */
  if( !EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_UNINIT;
  }
  /* #2 Check that network index is not an invalid index */
  else if( EthSM_IsChannelbyComMInvalid(NetworkHandle) ) /* PRQA S 2996 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */
  {
    errorId = ETHSM_E_INVALID_NETWORK_HANDLE;
  }
  /* #3 Check that the ComM mode is not an Invalid network mode */
  else if( Mode > COMM_FULL_COMMUNICATION )
  {
    errorId = ETHSM_E_INVALID_NETWORK_MODE;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    EthSM_NetworkIdxType netIdx = EthSM_GetNetIdxByComMNetwHnd(NetworkHandle);
    /* SILENT_COMMUNICATION according to SWS_EthSM_00087 of EthSM AUTOSAR SWS not supported
     * -> ignore mode request like mentioned in SWS_EthSM_00188
     */
    /* #4 If mode is not SILENT_COMM, set requested mode for state machine. */
    if( Mode != COMM_SILENT_COMMUNICATION )
    {
      EthSM_SetRequestedMode(netIdx, Mode); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( ETHSM_DEV_ERROR_REPORT == STD_ON )
  /* #5 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_REQUEST_COM_MODE, errorId);
  }
#else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  return retVal;
} /* EthSM_RequestComMode() */

/**********************************************************************************************************************
 *  EthSM_GetCurrentComMode
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
FUNC(Std_ReturnType, ETHSM_CODE) EthSM_GetCurrentComMode(VAR(NetworkHandleType, AUTOMATIC) NetworkHandle,
  P2VAR(ComM_ModeType, AUTOMATIC, ETHSM_APPL_DATA) ModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that module is initialized */
  if( !EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_UNINIT;
  }
  /* #2 Check that network index is not an invalid index */
  else if( EthSM_IsChannelbyComMInvalid(NetworkHandle) ) /* PRQA S 2996 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */
  {
    errorId = ETHSM_E_INVALID_NETWORK_HANDLE;
  }
  /* #3 Check that the mode pointer is not a null pointer */
  else if( ModePtr == NULL_PTR )
  {
    errorId = ETHSM_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    EthSM_NetworkIdxType netIdx = EthSM_GetNetIdxByComMNetwHnd(NetworkHandle);
    /* #4 Save current mode to the passed ModePtr */
    *ModePtr = EthSM_GetMode(netIdx); /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHSM_DEV_ERROR_REPORT == STD_ON)
  /* #5 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_GET_CURRENT_COM_MODE, errorId);
  }
#else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  return retVal;
} /* EthSM_GetCurrentComMode() */

/**********************************************************************************************************************
 *  EthSM_GetCurrentInternalMode
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
FUNC(Std_ReturnType, ETHSM_CODE) EthSM_GetCurrentInternalMode(NetworkHandleType NetworkHandle,
  P2VAR(EthSM_NetworkModeStateType, AUTOMATIC, ETHSM_APPL_DATA) ModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that the module is initialized */
  if( !EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_UNINIT;
  }
  /* #2 Check that the network index is not an invalid index */
  else if( EthSM_IsChannelbyComMInvalid(NetworkHandle) ) /* PRQA S 2996 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */
  {
    errorId = ETHSM_E_INVALID_NETWORK_HANDLE;
  }
  /* #3 Check that the mode pointer is not null */
  else if( ModePtr == NULL_PTR )
  {
    errorId = ETHSM_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    EthSM_NetworkIdxType netIdx = EthSM_GetNetIdxByComMNetwHnd(NetworkHandle);
    /* #4 Else store the state in a pointer variable */
    switch( EthSM_GetState(netIdx) )
    {
    case STATE_WAIT_CONTROLLER_INIT:
      *ModePtr = ETHSM_STATE_OFFLINE; /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
      break;
    case STATE_WAIT_CONTROLLER_ACTIVE:
      *ModePtr = ETHSM_STATE_OFFLINE; /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
      break;
    case STATE_WAIT_TRCVLINK_TO_OFFLINE:
      *ModePtr = ETHSM_STATE_WAIT_TRCVLINK; /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
      break;
    case STATE_WAIT_ONLINE_TO_OFFLINE:
      *ModePtr = ETHSM_STATE_WAIT_ONLINE; /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
      break;
    case STATE_ONHOLD_TO_OFFLINE:
      *ModePtr = ETHSM_STATE_ONHOLD; /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
      break;
    case STATE_WAIT_OFFLINE_TO_OFFLINE:
      *ModePtr = ETHSM_STATE_WAIT_OFFLINE; /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
      break;
    default:
      *ModePtr = EthSM_GetState(netIdx); /* SBSW_ETHSM_STATE_MODE_PTRWRITE */
      break;
    }
    retVal = E_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETHSM_DEV_ERROR_REPORT == STD_ON)
  /* #5 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_GET_CURRENT_INTERNAL_MODE, errorId);
  }
#else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  return retVal;
} /* EthSM_GetCurrentInternalMode() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  EthSM_TrcvLinkStateChg
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
FUNC(Std_ReturnType, ETHSM_CODE) EthSM_TrcvLinkStateChg(NetworkHandleType NetworkHandle,
    EthTrcv_LinkStateType TransceiverLinkState) 
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that module is not initialized */
  if( !EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_UNINIT;
  }
  /* #2 Check that network index is not invalid */
  else if( EthSM_IsChannelbyComMInvalid(NetworkHandle) ) /* PRQA S 2996 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */
  {
    errorId = ETHSM_E_INVALID_NETWORK_HANDLE;
  }
  /* #3 Check that the Transceiver Link state is not invalid */
  else if( TransceiverLinkState > ETHTRCV_LINK_STATE_ACTIVE )
  {
    errorId = ETHSM_E_INVALID_TRCV_LINK_STATE;
  }
  else
#endif
  {
    /* --------------------- Implementation ------------------------------- */
    EthSM_NetworkIdxType netIdx = EthSM_GetNetIdxByComMNetwHnd(NetworkHandle);
    /* #4 If none of the above is applicable, store Transceiver Link State */
    EthSM_SetTrcvLinkState(netIdx, TransceiverLinkState); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHSM_DEV_ERROR_REPORT == STD_ON)
  /* #5 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_TRCV_LINK_STATE_CHG, errorId);
  }
#else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  return retVal;
} /* EthSM_TrcvLinkStateChg() */

#if ( ETHSM_IS_VECTOR_ETHIF == STD_ON )
/**********************************************************************************************************************
 *  EthSM_VTrcvLinkStateChg
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
FUNC(void, ETHSM_CODE) EthSM_VTrcvLinkStateChg(uint8 CtrlIdx, EthTrcv_LinkStateType TrcvLinkState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that module is initialized */
  if( !EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_UNINIT;
  }
  /* #2 Check that network index is not invalid */
  else if( EthSM_IsChannelbyEthIfInvalid(CtrlIdx) ) /*lint !e506 */
  {
    errorId = ETHSM_E_PARAM_CONTROLLER;
  }
  /* #3 Check that the Transceiver Link state is not invalid */
  else if( TrcvLinkState > ETHTRCV_LINK_STATE_ACTIVE )
  {
    errorId = ETHSM_E_INVALID_TRCV_LINK_STATE;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #4 If none of the above is applicable, report a Link State change for an Ethernet network */
    (void)EthSM_TrcvLinkStateChg(EthSM_GetComMNetworkHandleOfChannelConfig(EthSM_GetNetIdxByEthIfCtrlIdx(CtrlIdx)), TrcvLinkState);
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( ETHSM_DEV_ERROR_REPORT == STD_ON )
  /* #5 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_TRCV_LINK_STATE_CHG, errorId);
  }
# else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

# if ( ETHSM_DEV_ERROR_DETECT == STD_OFF )
#  if ( ETHSM_ISDEF_NETIDXBYETHIFCTRLIDX == STD_ON )
  ETHSM_DUMMY_STATEMENT_CONST(CtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#  endif
# endif
} /* EthSM_VTrcvLinkStateChg */
#endif /* ETHSM_IS_VECTOR_ETHIF */

#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  EthSM_TcpIpModeIndication
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
FUNC(Std_ReturnType, ETHSM_CODE) EthSM_TcpIpModeIndication(NetworkHandleType NetworkHandle,
  TcpIp_StateType TcpIpState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that module is initialized */
  if( !EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_UNINIT;
  }
  /* #2 Check that network index is not invalid */
  else if( EthSM_IsChannelbyComMInvalid(NetworkHandle) ) /* PRQA S 2996 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */
  {
    errorId = ETHSM_E_INVALID_NETWORK_HANDLE;
  }
  /* #3 Check that the TcpIp state is not invalid */
  else if( TcpIpState > TCPIP_STATE_ONLINE )
  {
    errorId = ETHSM_E_INVALID_TcpIpMode;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    EthSM_NetworkIdxType netIdx = EthSM_GetNetIdxByComMNetwHnd(NetworkHandle);
    /* #4 If none of the above is applicable, store TcpIp state */
    EthSM_SetTcpIpState(netIdx, TcpIpState); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( ETHSM_DEV_ERROR_REPORT == STD_ON )
  /* #5 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_TCPIP_MODE_INDICATION, errorId);
  }
# else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
  return retVal;
} /* EthSM_TcpIpModeIndication */
#endif /* ETHSM_IS_TCPIP_ENABLED */

#if ( ETHSM_IS_VECTOR_TCPIP == STD_ON )
/**********************************************************************************************************************
 *  EthSM_VTcpIpModeIndication
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
FUNC(void, ETHSM_CODE) EthSM_VTcpIpModeIndication(uint8 CtrlIdx, boolean IsAnyAddrOnCtrlActive)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that module is initialized */
  if( !EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_UNINIT;
  }
  /* #2 Check that network index is not invalid */
  else if( EthSM_IsChannelbyEthIfInvalid(CtrlIdx) )
  {
    errorId = ETHSM_E_PARAM_CONTROLLER;
  }
  /* #3 Check if the stack type of the current network is not TCPIP */
  else if( EthSM_GetStackTypeOfChannelConfig(EthSM_GetNetIdxByEthIfCtrlIdx(CtrlIdx)) != ETHSM_STACK_TYPE_TCPIP ) /* PRQA S 2742 */ /* MD_EthSM_2741_2742_2992_2996_2991 */ /*lint !e506 */ /* COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1 */
  {
    errorId = ETHSM_E_STACKTYPE_WRONG; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #4 Else store previous activity state to recognize if a state machine transition must be processed */
    EthSM_NetworkIdxType netIdx = EthSM_GetNetIdxByEthIfCtrlIdx(CtrlIdx);
    boolean isIpActivityBeforeProcessing = EthSM_IsIpActiveOnNetwork(netIdx);

    /* #41 adapt active count depending on passed state */
    if( IsAnyAddrOnCtrlActive == TRUE )
    {
      EthSM_IncActiveIpVxCnt(netIdx); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
    }
    else
    {
      if((EthSM_GetActiveIpVxCnt(netIdx) != 0U))
      {
        EthSM_DecActiveIpVxCnt(netIdx); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      }
    }

    /* #42 only process a transition if a state change is needed */
    if( isIpActivityBeforeProcessing != EthSM_IsIpActiveOnNetwork(netIdx) )
    {
      TcpIp_StateType wrappedTcpIpState
        = (TcpIp_StateType)((IsAnyAddrOnCtrlActive == TRUE) ? TCPIP_STATE_ONLINE : TCPIP_STATE_OFFLINE);
      /*
       * Call AUTOSAR API.
       */ 
      (void)EthSM_TcpIpModeIndication(EthSM_GetComMNetworkHandleOfChannelConfig(netIdx), wrappedTcpIpState);
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETHSM_DEV_ERROR_REPORT == STD_ON)
  /* #5 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_TCPIP_MODE_INDICATION, errorId);
  }
# else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif 
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* EthSM_VTcpIpModeIndication() */ /* ETHSM_IS_VECTOR_TCPIP */

#if defined( ETHSM_ENABLE_CTRL_TRCV_IND_API )
# if ( ETHSM_ENABLE_CTRL_TRCV_IND_API == STD_ON )
/**********************************************************************************************************************
 *  EthSM_CtrlModeIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHSM_CODE) EthSM_CtrlModeIndication(uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
  /*
   * SWS_EthSM_00191 and SWS_EthSM_00192 are not implemented because purpose of API isn't clear and
   * configuration data doesn't fit to API. (Controllers and Transceivers are abstracted by the
   * EthIf Controller -> no knowledge of controllers beyond EthIf)
   */
  /* #1 API is an empty implementation */
  ETHSM_DUMMY_STATEMENT_CONST(CtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  ETHSM_DUMMY_STATEMENT_CONST(CtrlMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* do nothing, AUTOSAR SWS doesn't even specify why this API exists and what its purpose is */
}

/**********************************************************************************************************************
 *  EthSM_TrcvModeIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHSM_CODE) EthSM_TrcvModeIndication(uint8 TrcvIdx, EthTrcv_ModeType TrcvMode)
{
  /*
   * SWS_EthSM_00194 and SWS_EthSM_00195 are not implemented because purpose off API isn't clear and
   * configuration data doesn't fit to API. (Controllers and Transceivers are abstracted by the
   * EthIf Controller -> no knowledge of transceivers beyond EthIf)
   */
  /* #1 API is an empty implementation */
  ETHSM_DUMMY_STATEMENT_CONST(TrcvIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  ETHSM_DUMMY_STATEMENT_CONST(TrcvMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* do nothing, AUTOSAR SWS doesn't even specify why this API exists and what its purpose is */
}
# endif /* ETHSM_ENABLE_CTRL_TRCV_IND_API */
#endif /* ETHSM_ENABLE_CTRL_TRCV_IND_API */

/**********************************************************************************************************************
 *  EthSM_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHSM_CODE) EthSM_MainFunction(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #1 Check initialization state of the component */
  if( EthSM_IsInitialized() )
  {
    EthSM_NetworkIdxType netIdx;
    /* #2 Iterate through all the channels */
    for( netIdx = 0U; netIdx < EthSM_GetSizeOfChannelConfig(); netIdx++ )
    {
      /* #21 Handles the state transitions */
      EthSM_StateMachine(netIdx);

#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      /* #22 Handles the EthIf timeout */
      EthSM_EthernetInterfaceTimeout(netIdx);
#endif
    } /* for each network */
  }
} /* EthSM_MainFunction() */

/**********************************************************************************************************************
* EthSM_Init
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
FUNC(void, ETHSM_CODE) EthSM_Init(P2CONST(EthSM_ConfigType, AUTOMATIC, ETHSM_PBCFG) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;
  EthSM_NetworkIdxType netIdx;
  /* ----- Development Error Checks ------------------------------------- */
#if (ETHSM_DEV_ERROR_DETECT == STD_ON)
  /* #1 Check initialization state of the component */
  if( EthSM_IsInitialized() )
  {
    errorId = ETHSM_E_ALREADY_INITIALIZED;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #2 Iterate through all the channels */
    for( netIdx = 0U; netIdx < EthSM_GetSizeOfChannelConfig(); netIdx++ )
    {
    /* #21 Initialize all global and local variables */
#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      EthSM_SetRetryTimer(netIdx, 0U); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetRetriesLeft(netIdx, 0U); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetTimeoutOccured(netIdx, FALSE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
#endif
      EthSM_SetMode(netIdx, COMM_NO_COMMUNICATION); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetRequestedMode(netIdx, COMM_NO_COMMUNICATION); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetState(netIdx, ETHSM_STATE_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetTcpIpState(netIdx, TCPIP_STATE_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetTrcvLinkState(netIdx, ETHTRCV_MODE_DOWN); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
      EthSM_SetLastReportedState(netIdx, ETHSM_BSWM_OFFLINE); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */

#if ( ETHSM_ENABLE_ETHIF_API_TIMEOUT == STD_ON )
      /* #22 Stop the EthIf timer */
      EthSM_EthIf_StopTimer(netIdx);
#endif
#if ( ETHSM_IS_VECTOR_TCPIP == STD_ON )
      EthSM_SetActiveIpVxCnt(netIdx, 0U); /* SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS */
#endif
    }

    /* #3 Set global state to initialized */
    EthSM_SetInitialized(TRUE); /* SBSW_ETHSM_CSL_VAR_ACCESS */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHSM_DEV_ERROR_REPORT == STD_ON)
  /* #4 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_INIT, errorId);
  }
#else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint !e438 */
#endif

#if ( ETHSM_USE_INIT_POINTER == STD_OFF ) /* COV_ETHSM_POSTBUILDREQUIRED */
  ETHSM_DUMMY_STATEMENT_CONST(ConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
} /* EthSM_Init() */

#if ( ETHSM_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
* EthSM_GetVersionInfo
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHSM_CODE) EthSM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ETHSM_APPL_DATA) versionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHSM_DEV_ERROR_DETECT == STD_ON )
  /* #1 Check that passed versionInfo parameter is not NULL. */
  if( versionInfo == NULL_PTR )
  {
    errorId = ETHSM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ------------------ Implementation ----------------------------------------- */
    /* #2 Read out vendor ID, module ID and version data */
    versionInfo->vendorID = (ETHSM_VENDOR_ID); /* SBSW_ETHSM_VERSIONINFO_PTRWRITE */
    versionInfo->moduleID = (ETHSM_MODULE_ID); /* SBSW_ETHSM_VERSIONINFO_PTRWRITE */
    versionInfo->sw_major_version = (ETHSM_SW_MAJOR_VERSION); /* SBSW_ETHSM_VERSIONINFO_PTRWRITE */ /* PRQA S 4464 */ /* MD_MSR_AutosarBoolean */
    versionInfo->sw_minor_version = (ETHSM_SW_MINOR_VERSION); /* SBSW_ETHSM_VERSIONINFO_PTRWRITE */
    versionInfo->sw_patch_version = (ETHSM_SW_PATCH_VERSION); /* SBSW_ETHSM_VERSIONINFO_PTRWRITE */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHSM_DEV_ERROR_REPORT == STD_ON)
  /* #3 Report error if applicable */
  if( errorId != ETHSM_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, ETHSM_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETHSM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
} /* EthSM_GetVersionInfo() */
#endif /* ETHSM_VERSION_INFO_API */

#define ETHSM_STOP_SEC_CODE

#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Module specific MISRA deviations:

 MD_EthSM_2741_2742_2992_2996_2991:
    Reason:       One operand of the if-statement is optimized to a pre processor define in some configurations.
                  The if-statement is still needed for configurations in which no optimization is applied.
    Risk:         No Risk.
    Prevention:   Covered by code review.

 MD_EthSM_2981:
    Reason:       Initialization is needed if the stack type of a network is not TcpIp.
    Risk:         No Risk.
    Prevention:   Covered by code review.

 MD_EthSM_2983:
    Reason:       The local variable and its assigned value is needed for configurations with stack type TcpIp.
    Risk:         No Risk.
    Prevention:   Covered by code review.

 MD_EthSM_2986:
    Reason:       The operation is needed if the stack type of a network is TcpIp.
    Risk:         No Risk.
    Prevention:   Covered by code review.

 MD_EthSM_3451_3449:
    Reason:       It is ensured by code generator that the declarations remain compatible. The first declaration is in SchM_EthSM.h, which is not included via EthSM.h.
                  The second declaration is in EthSM.h, which is visible to other modules.
    Risk:         There is no risk.
    Prevention:   Covered by code review.
*/
/* SBSW_JUSTIFICATION_BEGIN

\ID                  SBSW_ETHSM_CSL_CHANNEL_IDX_ACCESS
  \DESCRIPTION       Access of
                     EthSM_State, EthSM_Mode, EthSM_TcpIpState, EthSM_RetryTimer, EthSM_RetriesLeft,
                     EthSM_TimeoutOccured, EthSM_RequestedMode, EthSM_TrcvLinkState, EthSM_LastReportedState
                     EthSM_ActiveIpVxCnt via indirection over EthSM_ChannelConfig with same index using ComStackLib.
                     The 'channel' variable which is used as index is always checked.
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID                  SBSW_ETHSM_VERSIONINFO_PTRWRITE
  \DESCRIPTION       The function EthSM_GetVersionInfo writes to the object referenced by parameter versionInfo.
  \COUNTERMEASURE \N The caller must ensure that the pointer passed as parameter versionInfo is valid and references an
                     object of type Std_VersionInfoType.

\ID                  SBSW_ETHSM_STATE_MODE_PTRWRITE
  \DESCRIPTION       The function EthSM_GetCurrentComMode, EthSM_GetCurrentInternalMode writes to the object referenced
                     by parameter ModePtr.
  \COUNTERMEASURE \N The caller must ensure that the pointers passed as parameter ModePtr is valid
                     and reference an object of type ComM_ModeType, EthSM_NetworkModeStateType respectively.

\ID                  SBSW_ETHSM_ADDRESS_TOBUSSM
  \DESCRIPTION       A pointer to the local stack variable 'modeToPass' is passed to an global API.
  \COUNTERMEASURE \N The passed pointer references a local stack variable and is therefore always valid.

\ID                  SBSW_ETHSM_CSL_VAR_ACCESS
  \DESCRIPTION       A ComStackLib generated variable is accessed.
  \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the
                     variables address without pointer arithmetic.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION
  \ID COV_ETHSM_REDEFINEABLE
  \ACCEPT TX
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to
          allow redefinition using an optional user configuration file.

  \ID COV_ETHSM_POSTBUILDREQUIRED
  \ACCEPT TX
  \REASON The component does not support PostBuild and the condition can therefore not be covered with False.

  \ID COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_0
  \ACCEPT TX
  \REASON These conditions checks whether the DEM is configured or not. They cannot be covered in certain
          configurations as DEM is configured for each channel in that configuration.

  \ID COV_ETHSM_RT_SPECIFIC_CFG_REQUIRED_1
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf xx tx
  \ACCEPT XF xf xx
  \ACCEPT TF tx tf xf
  \ACCEPT TF tx tf
  \ACCEPT TX tx tx xx
  \REASON These conditions check whether a particular stack type is configured or not. They cannot be covered in certain
          configurations as only one stack type is configured for all channels in those configurations.

  \ID COV_ETHSM_RT_NOT_REACHABLE
  \ACCEPT X
  \REASON All possible states are covered within the switch-case, there cannot be any other state to reach the default case.
END_COVERAGE_JUSTIFICATION
*/

/**********************************************************************************************************************
 *  END OF FILE: EthSM.c
 *********************************************************************************************************************/
