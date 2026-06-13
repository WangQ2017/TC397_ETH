/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: BswM
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: BswM_Lcfg.c
 *   Generation Time: 2026-06-13 19:00:24
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#define BSWM_LCFG_SOURCE

/* -----------------------------------------------------------------------------
    &&&~ MISRA JUSTIFICATION
 ----------------------------------------------------------------------------- */
/* PRQA S 0785, 0786 EOF */ /* MD_CSL_DistinctIdentifiers */

/* -----------------------------------------------------------------------------
    &&&~ INCLUDE
 ----------------------------------------------------------------------------- */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
#include "BswM.h"
#include "BswM_Private_Cfg.h"
#include "SchM_BswM.h"

#if !defined (BSWM_LOCAL)
# define BSWM_LOCAL static
#endif

#if !defined (BSWM_LOCAL_INLINE) /* COV_BSWM_LOCAL_INLINE */
# define BSWM_LOCAL_INLINE LOCAL_INLINE
#endif



#define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

/* -----------------------------------------------------------------------------
    &&&~ LOCAL FUNCTION DECLARATIONS
 ----------------------------------------------------------------------------- */
/**********************************************************************************************************************
 *  BswM_Action_RuleHandler()
 **********************************************************************************************************************/
/*!
 * \brief       Executes a rule.
 * \details     Arbitrates a rule and executes corresponding action list.
 * \param[in]   handleId       Id of the rule to execute.
 * \param[in]   partitionIdx   Current partition context.
 * \return      E_OK      No action list was executed or corresponding action list was completely executed.
 * \return      E_NOT_OK  Action list was aborted because an action failed.
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_Action_RuleHandler(BswM_HandleType handleId,
                                                                   BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);

/**********************************************************************************************************************
 *  BswM_UpdateRuleStates()
 **********************************************************************************************************************/
/*!
 * \brief       Updates the state of a rule.
 * \details     Set rule state of passed ruleId to passed state.
 * \param[in]   ruleId         Id of the rule to update.
 * \param[in]   state          New state of the rule.
 * \param[in]   partitionIdx   Current partition context.
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_UpdateRuleStates(BswM_SizeOfRuleStatesType ruleId, 
                                                              BswM_RuleStatesType state,
                                                              BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);

/**********************************************************************************************************************
 *  BswM_UpdateTimer()
 **********************************************************************************************************************/
/*!
 * \brief       Updates a timer.
 * \details     Set timer value of passed timerId to passed value and calculates the new state.
 * \param[in]   timerId        Id of the timer to update.
 * \param[in]   value          New value of the timer.
 * \param[in]   partitionIdx   Current partition context. 
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_UpdateTimer(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx,
                                                         BswM_SizeOfTimerValueType timerId,
                                                         BswM_TimerValueType value);

/*! \addtogroup    BswMGeneratedFunctions BswM Generated Functions
 * \{
 */
/* PRQA S 0779 FUNCTIONDECLARATIONS */ /* MD_MSR_Rule5.2_0779 */

/**********************************************************************************************************************
 *  Init
 *********************************************************************************************************************/
/*! \defgroup    Init
 * \{
 */
/**********************************************************************************************************************
 *  BswM_InitGenVarAndInitAL_BSWM_SINGLEPARTITION
 *********************************************************************************************************************/
/*!
 * \brief       Initializes BswM.
 * \details     Part of the BswM_Init. Initializes all generated variables and executes action lists for initialization.
 * \pre         -
 * \reentrant   FALSE
 * \synchronous TRUE
 * \note        May only be called by BswM_Init.
 */
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_InitGenVarAndInitAL_BSWM_SINGLEPARTITION(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
/*! \} */ /* End of group Init */

/**********************************************************************************************************************
 *  Common
 *********************************************************************************************************************/
/*! \defgroup    Common
 * \{
 */
/**********************************************************************************************************************
 *  BswM_ModeNotificationFct_BSWM_SINGLEPARTITION
 *********************************************************************************************************************/
/*!
 * \brief       Switch Modes of RTE and writes RTE values.
 * \details     Forwards a BswM Switch Action to the RTE and writes value of RteRequestPorts to RTE.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \note        May only be called by BswM_MainFunction.
 */
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_ModeNotificationFct_BSWM_SINGLEPARTITION(void);
/*! \} */ /* End of group Common */

/**********************************************************************************************************************
 *  SwcModeRequestUpdate
 *********************************************************************************************************************/
/*! \defgroup    SwcModeRequestUpdate
 * \{
 */
/**********************************************************************************************************************
 *  BswM_SwcModeRequestUpdateFct_BSWM_SINGLEPARTITION
 *********************************************************************************************************************/
/*!
 * \brief       Reads port values from RTE.
 * \details     Gets the current value of SwcModeRequest Ports and SwcNotification Ports from RTE.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \note        May only be called by BswM_MainFunction.
 */
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_SwcModeRequestUpdateFct_BSWM_SINGLEPARTITION(void);
/*! \} */ /* End of group SwcModeRequestUpdate */

/**********************************************************************************************************************
 *  BswMActionListFunctions
 *********************************************************************************************************************/
/*! \defgroup    BswMActionListFunctions
 * \{
 */

/*!
 * \{
 * \brief       Execute actions of action list.
 * \details     Generated function which depends on the configuration. Executes the actions of the action list in the
 *              configured order.
 * \return      E_OK      Action list was completely executed.
 * \return      E_NOT_OK  Action list was aborted because an action failed.
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_RunToPostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvMToShutdown(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WakeupToPrep(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvMWakeup(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WakeupToRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PostRunToPrepShutdown(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_ESH_PostRunToPrepCheck(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PostRunToRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_ExitPostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PrepShutdownToWaitForNvM(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_INIT_AL_Initialize(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_DemInit(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
/*! \} */ /* End of sharing description for BswMActionListFunctions */
#define BswM_ActionList_ESH_AL_InitToWakeup BswM_ActionList_ESH_AL_WaitForNvMWakeup
/*! \} */ /* End of group BswMActionListFunctions */

/**********************************************************************************************************************
 *  BswMRuleFunctions
 *********************************************************************************************************************/
/*! \defgroup    BswMRuleFunctions
 * \{
 */

/*!
 * \{
 * \brief       Arbitrates the configured rule.
 * \details     Generated function which depends on the configuration. Arbitrates the rule and returns the action list
 *              which shall be executed.
 * \return      ID of action list to execute (BSWM_NO_ACTIONLIST if no ActionList shall be executed)
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_RunToPostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WaitToShutdown(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WakeupToPrep(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WaitToWakeup(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WakeupToRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_InitToWakeup(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PostRunToPrepNested(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PostRunNested(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PrepToWait(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_DemInit(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
/*! \} */ /* End of sharing description for BswMRuleFunctions */
/*! \} */ /* End of group BswMRuleFunctions */
/* PRQA L:FUNCTIONDECLARATIONS */
/*! \} */ /* End of group BswMGeneratedFunctions */

#define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"


/* -----------------------------------------------------------------------------
    &&&~ LOCAL VARIABLE DECLARATIONS
 ----------------------------------------------------------------------------- */

/* PRQA S 0779 VARIABLEDECLARATIONS */ /* MD_MSR_Rule5.2_0779 */ 


#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"


#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

/* PRQA L:VARIABLEDECLARATIONS */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/



/**********************************************************************************************************************
 *  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA
**********************************************************************************************************************/


/* PRQA S 0310 GLOBALDATADECLARATIONS */ /* MD_BSWM_0310 */ 
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  BswM_ActionLists
**********************************************************************************************************************/
/** 
  \var    BswM_ActionLists
  \details
  Element    Description
  FctPtr     Pointer to the array list function.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_ActionListsType, BSWM_CONST) BswM_ActionLists[47] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    FctPtr                                                                                                                                     Comment                   Referable Keys */
  { /*     0 */ BswM_ActionList_ESH_AL_RunToPostRun                                                                                                 },  /* [Priority: 0] */  /* [AL_ESH_AL_RunToPostRun] */
  { /*     1 */ BswM_ActionList_ESH_AL_WaitForNvMToShutdown                                                                                         },  /* [Priority: 0] */  /* [AL_ESH_AL_WaitForNvMToShutdown] */
  { /*     2 */ BswM_ActionList_ESH_AL_WakeupToPrep                                                                                                 },  /* [Priority: 0] */  /* [AL_ESH_AL_WakeupToPrep] */
  { /*     3 */ BswM_ActionList_ESH_AL_WaitForNvMWakeup                                                                                             },  /* [Priority: 0] */  /* [AL_ESH_AL_WaitForNvMWakeup] */
  { /*     4 */ BswM_ActionList_ESH_AL_WakeupToRun                                                                                                  },  /* [Priority: 0] */  /* [AL_ESH_AL_WakeupToRun] */
  { /*     5 */ BswM_ActionList_ESH_AL_InitToWakeup                                                                                                 },  /* [Priority: 0] */  /* [AL_ESH_AL_InitToWakeup] */
  { /*     6 */ BswM_ActionList_ESH_AL_PostRunToPrepShutdown                                                                                        },  /* [Priority: 0] */  /* [AL_ESH_AL_PostRunToPrepShutdown] */
  { /*     7 */ BswM_ActionList_ESH_AL_ESH_PostRunToPrepCheck                                                                                       },  /* [Priority: 0] */  /* [AL_ESH_AL_ESH_PostRunToPrepCheck] */
  { /*     8 */ BswM_ActionList_ESH_AL_PostRunToRun                                                                                                 },  /* [Priority: 0] */  /* [AL_ESH_AL_PostRunToRun] */
  { /*     9 */ BswM_ActionList_ESH_AL_ExitPostRun                                                                                                  },  /* [Priority: 0] */  /* [AL_ESH_AL_ExitPostRun] */
  { /*    10 */ BswM_ActionList_ESH_AL_PrepShutdownToWaitForNvM                                                                                     },  /* [Priority: 0] */  /* [AL_ESH_AL_PrepShutdownToWaitForNvM] */
  { /*    11 */ BswM_ActionList_INIT_AL_Initialize                                                                                                  },  /* [Priority: 0] */  /* [AL_INIT_AL_Initialize] */
  { /*    12 */ BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo               },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  { /*    13 */ BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo               },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  { /*    14 */ BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN                                                           },  /* [Priority: 0] */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN] */
  { /*    15 */ BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE                                                 },  /* [Priority: 0] */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE] */
  { /*    16 */ BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState                                },  /* [Priority: 0] */  /* [AL_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
  { /*    17 */ BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState                                },  /* [Priority: 0] */  /* [AL_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
  { /*    18 */ BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN             },  /* [Priority: 0] */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN] */
  { /*    19 */ BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE   },  /* [Priority: 0] */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE] */
  { /*    20 */ BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed                                                           },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed] */
  { /*    21 */ BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed                                                           },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed] */
  { /*    22 */ BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN                                                            },  /* [Priority: 0] */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN] */
  { /*    23 */ BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE                                                  },  /* [Priority: 0] */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE] */
  { /*    24 */ BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN           },  /* [Priority: 0] */  /* [AL_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN] */
  { /*    25 */ BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE },  /* [Priority: 0] */  /* [AL_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE] */
  { /*    26 */ BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo                              },  /* [Priority: 0] */  /* [AL_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  { /*    27 */ BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo                              },  /* [Priority: 0] */  /* [AL_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  { /*    28 */ BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus                                                          },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus] */
  { /*    29 */ BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus                                                          },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus] */
  { /*    30 */ BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo                                                               },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo] */
  { /*    31 */ BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo                                                               },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo] */
  { /*    32 */ BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState                                                                },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState] */
  { /*    33 */ BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState                                                                },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState] */
  { /*    34 */ BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN                                                          },  /* [Priority: 0] */  /* [AL_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN] */
  { /*    35 */ BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE                                                },  /* [Priority: 0] */  /* [AL_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE] */
  { /*    36 */ BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus           },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  { /*    37 */ BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus           },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  { /*    38 */ BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN               },  /* [Priority: 0] */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN] */
  { /*    39 */ BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE     },  /* [Priority: 0] */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE] */
  { /*    40 */ BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState                                                                },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState] */
  { /*    41 */ BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState                                                                },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState] */
  { /*    42 */ BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed             },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  { /*    43 */ BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed             },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  { /*    44 */ BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo                                                            },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo] */
  { /*    45 */ BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo                                                            },  /* [Priority: 0] */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo] */
  { /*    46 */ BswM_ActionList_ESH_AL_DemInit                                                                                                      }   /* [Priority: 0] */  /* [AL_ESH_AL_DemInit] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_DeferredRules
**********************************************************************************************************************/
/** 
  \var    BswM_DeferredRules
  \details
  Element     Description
  RulesIdx    the index of the 1:1 relation pointing to BswM_Rules
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_DeferredRulesType, BSWM_CONST) BswM_DeferredRules[24] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RulesIdx        Referable Keys */
  { /*     0 */       0u },  /* [R_ESH_RunToPostRun] */
  { /*     1 */       1u },  /* [R_ESH_WaitToShutdown] */
  { /*     2 */       2u },  /* [R_ESH_WakeupToPrep] */
  { /*     3 */       3u },  /* [R_ESH_WaitToWakeup] */
  { /*     4 */       4u },  /* [R_ESH_WakeupToRun] */
  { /*     5 */       8u },  /* [R_ESH_PostRun] */
  { /*     6 */       9u },  /* [R_ESH_PrepToWait] */
  { /*     7 */      10u },  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  { /*     8 */      11u },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed] */
  { /*     9 */      12u },  /* [R_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
  { /*    10 */      13u },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  { /*    11 */      14u },  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed] */
  { /*    12 */      15u },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo] */
  { /*    13 */      16u },  /* [R_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  { /*    14 */      17u },  /* [R_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  { /*    15 */      18u },  /* [R_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus] */
  { /*    16 */      19u },  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo] */
  { /*    17 */      20u },  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState] */
  { /*    18 */      21u },  /* [R_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus] */
  { /*    19 */      22u },  /* [R_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  { /*    20 */      23u },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  { /*    21 */      24u },  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState] */
  { /*    22 */      25u },  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  { /*    23 */      26u }   /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_GenericMapping
**********************************************************************************************************************/
/** 
  \var    BswM_GenericMapping
  \brief  Maps the external id of BswMGenericRequest to an internal id and references immediate request ports.
  \details
  Element                  Description
  ExternalId               External id of BswMGenericRequest.
  ImmediateUserEndIdx      the end index of the 0:n relation pointing to BswM_ImmediateUser
  ImmediateUserStartIdx    the start index of the 0:n relation pointing to BswM_ImmediateUser
  InitValue                Initialization value of port.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_GenericMappingType, BSWM_CONST) BswM_GenericMapping[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ExternalId                            ImmediateUserEndIdx                          ImmediateUserStartIdx                          InitValue                                                  Referable Keys */
  { /*     0 */ BSWM_GENERIC_ESH_DemInitStatus      ,                                          1u,                                            0u, BSWM_GENERICVALUE_ESH_DemInitStatus_DEM_INITIALIZED },  /* [GENERIC_0, MRP_ESH_DemInitStatus] */
  { /*     1 */ BSWM_GENERIC_ESH_DemPostRunRequested, BSWM_NO_IMMEDIATEUSERENDIDXOFGENERICMAPPING, BSWM_NO_IMMEDIATEUSERSTARTIDXOFGENERICMAPPING, BSWM_GENERICVALUE_ESH_DemPostRunRequested_TRUE      },  /* [GENERIC_1, MRP_ESH_DemPostRunRequested] */
  { /*     2 */ BSWM_GENERIC_ESH_State              ,                                          2u,                                            1u, BSWM_GENERICVALUE_ESH_State_ESH_INIT                }   /* [GENERIC_2, MRP_ESH_State] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ImmediateUser
**********************************************************************************************************************/
/** 
  \var    BswM_ImmediateUser
  \brief  Contains all immediate request ports.
  \details
  Element             Description
  MaskedBits          contains bitcoded the boolean data of BswM_OnInitOfImmediateUser, BswM_RulesIndUsedOfImmediateUser
  RulesIndEndIdx      the end index of the 0:n relation pointing to BswM_RulesInd
  RulesIndStartIdx    the start index of the 0:n relation pointing to BswM_RulesInd
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_ImmediateUserType, BSWM_CONST) BswM_ImmediateUser[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaskedBits  RulesIndEndIdx                         RulesIndStartIdx                               Comment                               Referable Keys */
  { /*     0 */      0x00u, BSWM_NO_RULESINDENDIDXOFIMMEDIATEUSER, BSWM_NO_RULESINDSTARTIDXOFIMMEDIATEUSER },  /* [Name: ESH_DemInitStatus] */  /* [MRP_ESH_DemInitStatus, GENERIC_0] */
  { /*     1 */      0x03u,                                    8u,                                      0u }   /* [Name: ESH_State]         */  /* [MRP_ESH_State, GENERIC_2] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_InitGenVarAndInitAL
**********************************************************************************************************************/
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_InitGenVarAndInitALType, BSWM_CONST) BswM_InitGenVarAndInitAL[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitGenVarAndInitAL                            */
  /*     0 */ BswM_InitGenVarAndInitAL_BSWM_SINGLEPARTITION 
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ModeNotificationFct
**********************************************************************************************************************/
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_PartitionFunctionType, BSWM_CONST) BswM_ModeNotificationFct[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     ModeNotificationFct                            */
  /*     0 */ BswM_ModeNotificationFct_BSWM_SINGLEPARTITION 
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_PartitionIdentifiers
**********************************************************************************************************************/
/** 
  \var    BswM_PartitionIdentifiers
  \brief  the partition contex in Config
  \details
  Element                 Description
  PartitionSNV        
  PCPartitionConfigIdx    the index of the 1:1 relation pointing to BswM_PCPartitionConfig
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_PartitionIdentifiersType, BSWM_CONST) BswM_PartitionIdentifiers[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionSNV          PCPartitionConfigIdx */
  { /*     0 */ BSWM_SINGLEPARTITION,                   0u }
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_Rules
**********************************************************************************************************************/
/** 
  \var    BswM_Rules
  \details
  Element          Description
  Id               External id of rule.
  Init             Initialization value of rule state (TRUE, FALSE, UNDEFINED or DEACTIVATED).
  RuleStatesIdx    the index of the 1:1 relation pointing to BswM_RuleStates
  FctPtr           Pointer to the rule function which does the arbitration.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_RulesType, BSWM_CONST) BswM_Rules[28] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Id   Init        RuleStatesIdx  FctPtr                                                                                                                    Referable Keys */
  { /*     0 */  6u, BSWM_FALSE,            0u, BswM_Rule_ESH_RunToPostRun                                                                                         },  /* [R_ESH_RunToPostRun, MRP_ESH_State, MRP_ESH_ModeNotification, MRP_ESH_RunRequest_0, MRP_ESH_RunRequest_1, MRP_ESH_SelfRunRequestTimer] */
  { /*     1 */  7u, BSWM_FALSE,            1u, BswM_Rule_ESH_WaitToShutdown                                                                                       },  /* [R_ESH_WaitToShutdown, MRP_ESH_State, MRP_ESH_EcuM_GetValidatedWakeupEvents] */
  { /*     2 */  9u, BSWM_FALSE,            2u, BswM_Rule_ESH_WakeupToPrep                                                                                         },  /* [R_ESH_WakeupToPrep, MRP_ESH_State, MRP_ESH_EcuM_GetPendingWakeupEvents, MRP_ESH_EcuM_GetValidatedWakeupEvents, MRP_ESH_ModeNotification] */
  { /*     3 */  8u, BSWM_FALSE,            3u, BswM_Rule_ESH_WaitToWakeup                                                                                         },  /* [R_ESH_WaitToWakeup, MRP_ESH_State, MRP_ESH_EcuM_GetValidatedWakeupEvents] */
  { /*     4 */ 10u, BSWM_FALSE,            4u, BswM_Rule_ESH_WakeupToRun                                                                                          },  /* [R_ESH_WakeupToRun, MRP_ESH_State, MRP_ESH_EcuM_GetValidatedWakeupEvents, MRP_ESH_ModeNotification] */
  { /*     5 */  1u, BSWM_FALSE,            5u, BswM_Rule_ESH_InitToWakeup                                                                                         },  /* [R_ESH_InitToWakeup, MRP_ESH_State] */
  { /*     6 */  4u, BSWM_FALSE,            6u, BswM_Rule_ESH_PostRunToPrepNested                                                                                  },  /* [R_ESH_PostRunToPrepNested] */
  { /*     7 */  3u, BSWM_FALSE,            7u, BswM_Rule_ESH_PostRunNested                                                                                        },  /* [R_ESH_PostRunNested] */
  { /*     8 */  2u, BSWM_FALSE,            8u, BswM_Rule_ESH_PostRun                                                                                              },  /* [R_ESH_PostRun, MRP_ESH_State, MRP_ESH_ModeNotification] */
  { /*     9 */  5u, BSWM_FALSE,            9u, BswM_Rule_ESH_PrepToWait                                                                                           },  /* [R_ESH_PrepToWait, MRP_ESH_State, MRP_ESH_ModeNotification] */
  { /*    10 */ 14u, BSWM_TRUE ,           10u, BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo       },  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, MRP_SDC_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  { /*    11 */ 20u, BSWM_FALSE,           11u, BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed                                                 },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed, MRP_SDC_SdClientState_C_SdCLientService_0xC3CB_VechicleSpeed] */
  { /*    12 */ 27u, BSWM_FALSE,           12u, BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState                    },  /* [R_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState, MRP_SDC_SdEHState_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
  { /*    13 */ 21u, BSWM_FALSE,           13u, BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed   },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, MRP_SDC_SdCEGState_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  { /*    14 */ 11u, BSWM_TRUE ,           14u, BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed                                                   },  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed, MRP_SDC_C_SdCLientService_0xC3CB_VechicleSpeed] */
  { /*    15 */ 22u, BSWM_FALSE,           15u, BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo                                                  },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo, MRP_SDC_SdClientState_C_SdCLientService_0xC3CD_VechicleInfo] */
  { /*    16 */ 25u, BSWM_FALSE,           16u, BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus },  /* [R_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, MRP_SDC_SdCEGState_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  { /*    17 */ 26u, BSWM_FALSE,           17u, BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo                  },  /* [R_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo, MRP_SDC_SdEHState_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  { /*    18 */ 15u, BSWM_TRUE ,           18u, BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus                                                  },  /* [R_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus, MRP_SDC_C_SdClientService_0xC3CC_VechicleStatus] */
  { /*    19 */ 17u, BSWM_TRUE ,           19u, BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo                                                       },  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo, MRP_SDC_S_SdServerService_0xC3C0_FaultInfo] */
  { /*    20 */ 18u, BSWM_TRUE ,           20u, BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState                                                        },  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState, MRP_SDC_S_SdServerService_0xC3C1_SenState] */
  { /*    21 */ 24u, BSWM_FALSE,           21u, BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus                                                },  /* [R_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus, MRP_SDC_SdClientState_C_SdClientService_0xC3CC_VechicleStatus] */
  { /*    22 */ 16u, BSWM_TRUE ,           22u, BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus   },  /* [R_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, MRP_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  { /*    23 */ 23u, BSWM_FALSE,           23u, BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo     },  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, MRP_SDC_SdCEGState_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  { /*    24 */ 19u, BSWM_TRUE ,           24u, BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState                                                        },  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState, MRP_SDC_S_SdServerService_0xC3C2_EcuState] */
  { /*    25 */ 12u, BSWM_TRUE ,           25u, BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed     },  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, MRP_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  { /*    26 */ 13u, BSWM_TRUE ,           26u, BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo                                                    },  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo, MRP_SDC_C_SdCLientService_0xC3CD_VechicleInfo] */
  { /*    27 */  0u, BSWM_FALSE,           27u, BswM_Rule_ESH_DemInit                                                                                              }   /* [R_ESH_DemInit] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_RulesInd
**********************************************************************************************************************/
/** 
  \var    BswM_RulesInd
  \brief  the indexes of the 1:1 sorted relation pointing to BswM_Rules
*/ 
#define BSWM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_RulesIndType, BSWM_CONST) BswM_RulesInd[8] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RulesInd      Referable Keys */
  /*     0 */        0u,  /* [MRP_ESH_State] */
  /*     1 */        1u,  /* [MRP_ESH_State] */
  /*     2 */        2u,  /* [MRP_ESH_State] */
  /*     3 */        3u,  /* [MRP_ESH_State] */
  /*     4 */        4u,  /* [MRP_ESH_State] */
  /*     5 */        5u,  /* [MRP_ESH_State] */
  /*     6 */        8u,  /* [MRP_ESH_State] */
  /*     7 */        9u   /* [MRP_ESH_State] */
};
#define BSWM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SdClientServiceMapping
**********************************************************************************************************************/
/** 
  \var    BswM_SdClientServiceMapping
  \brief  Maps the external id of BswMSdClientServiceCurrentState to an internal id and references immediate request ports.
  \details
  Element       Description
  ExternalId    External id of BswMSdClientServiceCurrentState.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_SdClientServiceMappingType, BSWM_CONST) BswM_SdClientServiceMapping[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ExternalId                                                          Referable Keys */
  { /*     0 */ SdConf_SdClientService_SdCLientService_0xC3CB_VechicleSpeed  },  /* [SD_CLIENT_0, MRP_SDC_SdClientState_C_SdCLientService_0xC3CB_VechicleSpeed] */
  { /*     1 */ SdConf_SdClientService_SdCLientService_0xC3CD_VechicleInfo   },  /* [SD_CLIENT_1, MRP_SDC_SdClientState_C_SdCLientService_0xC3CD_VechicleInfo] */
  { /*     2 */ SdConf_SdClientService_SdClientService_0xC3CC_VechicleStatus }   /* [SD_CLIENT_2, MRP_SDC_SdClientState_C_SdClientService_0xC3CC_VechicleStatus] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SdConsumedEventMapping
**********************************************************************************************************************/
/** 
  \var    BswM_SdConsumedEventMapping
  \brief  Maps the external id of BswMSdConsumedEventGroupCurrentState to an internal id and references immediate request ports.
  \details
  Element       Description
  ExternalId    External id of BswMSdConsumedEventGroupCurrentState.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_SdConsumedEventMappingType, BSWM_CONST) BswM_SdConsumedEventMapping[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ExternalId                                                                    Referable Keys */
  { /*     0 */ SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CB_VechicleSpeed  },  /* [SD_CONSUMED_0, MRP_SDC_SdCEGState_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  { /*     1 */ SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CC_VechicleStatus },  /* [SD_CONSUMED_1, MRP_SDC_SdCEGState_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  { /*     2 */ SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CD_VechicleInfo   }   /* [SD_CONSUMED_2, MRP_SDC_SdCEGState_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SdEventHandlerMapping
**********************************************************************************************************************/
/** 
  \var    BswM_SdEventHandlerMapping
  \brief  Maps the external id of BswMSdEventHandlerCurrentState to an internal id and references immediate request ports.
  \details
  Element       Description
  ExternalId    External id of BswMSdEventHandlerCurrentState.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_SdEventHandlerMappingType, BSWM_CONST) BswM_SdEventHandlerMapping[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ExternalId                                                   Referable Keys */
  { /*     0 */ SdConf_SdEventHandler_SdEventHandler_0xC3C0_FaultInfo },  /* [SD_EVENT_0, MRP_SDC_SdEHState_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  { /*     1 */ SdConf_SdEventHandler_SdEventHandler_0xC3C1_SenState  }   /* [SD_EVENT_1, MRP_SDC_SdEHState_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SwcModeRequestUpdateFct
**********************************************************************************************************************/
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(BswM_PartitionFunctionType, BSWM_CONST) BswM_SwcModeRequestUpdateFct[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     SwcModeRequestUpdateFct                            */
  /*     0 */ BswM_SwcModeRequestUpdateFct_BSWM_SINGLEPARTITION 
};
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ActionListQueue
**********************************************************************************************************************/
/** 
  \var    BswM_ActionListQueue
  \brief  Variable to store action lists which shall be executed.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_ActionListQueueUType, BSWM_VAR_NOINIT) BswM_ActionListQueue;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [AL_ESH_AL_RunToPostRun] */
  /*     1 */  /* [AL_ESH_AL_WaitForNvMToShutdown] */
  /*     2 */  /* [AL_ESH_AL_WakeupToPrep] */
  /*     3 */  /* [AL_ESH_AL_WaitForNvMWakeup] */
  /*     4 */  /* [AL_ESH_AL_WakeupToRun] */
  /*     5 */  /* [AL_ESH_AL_InitToWakeup] */
  /*     6 */  /* [AL_ESH_AL_PostRunToPrepShutdown] */
  /*     7 */  /* [AL_ESH_AL_ESH_PostRunToPrepCheck] */
  /*     8 */  /* [AL_ESH_AL_PostRunToRun] */
  /*     9 */  /* [AL_ESH_AL_ExitPostRun] */
  /*    10 */  /* [AL_ESH_AL_PrepShutdownToWaitForNvM] */
  /*    11 */  /* [AL_INIT_AL_Initialize] */
  /*    12 */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  /*    13 */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  /*    14 */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN] */
  /*    15 */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE] */
  /*    16 */  /* [AL_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
  /*    17 */  /* [AL_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
  /*    18 */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN] */
  /*    19 */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE] */
  /*    20 */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed] */
  /*    21 */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed] */
  /*    22 */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN] */
  /*    23 */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE] */
  /*    24 */  /* [AL_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN] */
  /*    25 */  /* [AL_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE] */
  /*    26 */  /* [AL_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  /*    27 */  /* [AL_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  /*    28 */  /* [AL_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus] */
  /*    29 */  /* [AL_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus] */
  /*    30 */  /* [AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo] */
  /*    31 */  /* [AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo] */
  /*    32 */  /* [AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState] */
  /*    33 */  /* [AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState] */
  /*    34 */  /* [AL_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN] */
  /*    35 */  /* [AL_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE] */
  /*    36 */  /* [AL_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  /*    37 */  /* [AL_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  /*    38 */  /* [AL_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN] */
  /*    39 */  /* [AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE] */
  /*    40 */  /* [AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState] */
  /*    41 */  /* [AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState] */
  /*    42 */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  /*    43 */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  /*    44 */  /* [AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo] */
  /*    45 */  /* [AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo] */
  /*    46 */  /* [AL_ESH_AL_DemInit] */

#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ForcedActionListPriority
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_ForcedActionListPriorityType, BSWM_VAR_NOINIT) BswM_ForcedActionListPriority;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_GenericState
**********************************************************************************************************************/
/** 
  \var    BswM_GenericState
  \brief  Variable to store current mode of BswMGenericRequest mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_ModeType, BSWM_VAR_NOINIT) BswM_GenericState[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [GENERIC_0, MRP_ESH_DemInitStatus] */
  /*     1 */  /* [GENERIC_1, MRP_ESH_DemPostRunRequested] */
  /*     2 */  /* [GENERIC_2, MRP_ESH_State] */

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_Initialized
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_InitializedType, BSWM_VAR_NOINIT) BswM_Initialized;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ModeRequestQueue
**********************************************************************************************************************/
/** 
  \var    BswM_ModeRequestQueue
  \brief  Variable to store an immediate mode request which must be queued because of a current active arbitration.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_ModeRequestQueueType, BSWM_VAR_NOINIT) BswM_ModeRequestQueue[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [MRP_ESH_DemInitStatus, GENERIC_0] */
  /*     1 */  /* [MRP_ESH_State, GENERIC_2] */

#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_QueueSemaphore
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_QueueSemaphoreType, BSWM_VAR_NOINIT) BswM_QueueSemaphore;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_QueueWritten
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_QueueWrittenType, BSWM_VAR_NOINIT) BswM_QueueWritten;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_RuleStates
**********************************************************************************************************************/
/** 
  \var    BswM_RuleStates
  \brief  Stores the last execution state of the rule.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_RuleStatesUType, BSWM_VAR_NOINIT) BswM_RuleStates;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [R_ESH_RunToPostRun] */
  /*     1 */  /* [R_ESH_WaitToShutdown] */
  /*     2 */  /* [R_ESH_WakeupToPrep] */
  /*     3 */  /* [R_ESH_WaitToWakeup] */
  /*     4 */  /* [R_ESH_WakeupToRun] */
  /*     5 */  /* [R_ESH_InitToWakeup] */
  /*     6 */  /* [R_ESH_PostRunToPrepNested] */
  /*     7 */  /* [R_ESH_PostRunNested] */
  /*     8 */  /* [R_ESH_PostRun] */
  /*     9 */  /* [R_ESH_PrepToWait] */
  /*    10 */  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  /*    11 */  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed] */
  /*    12 */  /* [R_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */
  /*    13 */  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  /*    14 */  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed] */
  /*    15 */  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo] */
  /*    16 */  /* [R_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  /*    17 */  /* [R_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  /*    18 */  /* [R_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus] */
  /*    19 */  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo] */
  /*    20 */  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState] */
  /*    21 */  /* [R_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus] */
  /*    22 */  /* [R_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  /*    23 */  /* [R_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */
  /*    24 */  /* [R_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState] */
  /*    25 */  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  /*    26 */  /* [R_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo] */
  /*    27 */  /* [R_ESH_DemInit] */

#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SdClientServiceState
**********************************************************************************************************************/
/** 
  \var    BswM_SdClientServiceState
  \brief  Variable to store current mode of BswMSdClientServiceCurrentState mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_ClientServiceCurrentStateType, BSWM_VAR_NOINIT) BswM_SdClientServiceState[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [SD_CLIENT_0, MRP_SDC_SdClientState_C_SdCLientService_0xC3CB_VechicleSpeed] */
  /*     1 */  /* [SD_CLIENT_1, MRP_SDC_SdClientState_C_SdCLientService_0xC3CD_VechicleInfo] */
  /*     2 */  /* [SD_CLIENT_2, MRP_SDC_SdClientState_C_SdClientService_0xC3CC_VechicleStatus] */

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SdConsumedEventState
**********************************************************************************************************************/
/** 
  \var    BswM_SdConsumedEventState
  \brief  Variable to store current mode of BswMSdConsumedEventGroupCurrentState mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_ConsumedEventGroupCurrentStateType, BSWM_VAR_NOINIT) BswM_SdConsumedEventState[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [SD_CONSUMED_0, MRP_SDC_SdCEGState_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  /*     1 */  /* [SD_CONSUMED_1, MRP_SDC_SdCEGState_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus] */
  /*     2 */  /* [SD_CONSUMED_2, MRP_SDC_SdCEGState_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo] */

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SdEventHandlerState
**********************************************************************************************************************/
/** 
  \var    BswM_SdEventHandlerState
  \brief  Variable to store current mode of BswMSdEventHandlerCurrentState mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_EventHandlerCurrentStateType, BSWM_VAR_NOINIT) BswM_SdEventHandlerState[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [SD_EVENT_0, MRP_SDC_SdEHState_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo] */
  /*     1 */  /* [SD_EVENT_1, MRP_SDC_SdEHState_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState] */

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_TimerState
**********************************************************************************************************************/
/** 
  \var    BswM_TimerState
  \brief  Variable to store current state of BswMTimer (STARTED, STOPPER OR EXPIRED).
*/ 
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_TimerStateUType, BSWM_VAR_NOINIT) BswM_TimerState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [MRP_ESH_SelfRunRequestTimer] */

#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_TimerValue
**********************************************************************************************************************/
/** 
  \var    BswM_TimerValue
  \brief  Variable to store current timer values.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(BswM_TimerValueUType, BSWM_VAR_NOINIT) BswM_TimerValue;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [MRP_ESH_SelfRunRequestTimer] */

#define BSWM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/* PRQA L:GLOBALDATADECLARATIONS */

#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

VAR(Rte_ModeType_ESH_Mode, BSWM_VAR_NOINIT) BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode;
VAR(Rte_ModeType_SDC_SdClientServiceState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState;
VAR(Rte_ModeType_SDC_SdEventHandlerState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState;
VAR(Rte_ModeType_SDC_SdConsumedEventGroupState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState;
VAR(Rte_ModeType_SDC_SdClientServiceState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState;
VAR(Rte_ModeType_SDC_SdConsumedEventGroupState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState;
VAR(Rte_ModeType_SDC_SdEventHandlerState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState;
VAR(Rte_ModeType_SDC_SdClientServiceState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState;
VAR(Rte_ModeType_SDC_SdConsumedEventGroupState, BSWM_VAR_NOINIT) BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState;

VAR(BswM_ESH_RunRequest, BSWM_VAR_NOINIT) Request_ESH_RunRequest_0_requestedMode;
VAR(BswM_ESH_RunRequest, BSWM_VAR_NOINIT) Request_ESH_RunRequest_1_requestedMode;
VAR(BswM_ESH_RunRequest, BSWM_VAR_NOINIT) Request_ESH_PostRunRequest_0_requestedMode;
VAR(BswM_ESH_RunRequest, BSWM_VAR_NOINIT) Request_ESH_PostRunRequest_1_requestedMode;
VAR(BswM_SDC_SdConsumedEventGroupRequest, BSWM_VAR_NOINIT) Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode;
VAR(BswM_SDC_SdClientServiceRequest, BSWM_VAR_NOINIT) Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_requestedMode;
VAR(BswM_SDC_SdClientServiceRequest, BSWM_VAR_NOINIT) Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode;
VAR(BswM_SDC_SdServerServiceRequest, BSWM_VAR_NOINIT) Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode;
VAR(BswM_SDC_SdServerServiceRequest, BSWM_VAR_NOINIT) Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode;
VAR(BswM_SDC_SdConsumedEventGroupRequest, BSWM_VAR_NOINIT) Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode;
VAR(BswM_SDC_SdServerServiceRequest, BSWM_VAR_NOINIT) Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode;
VAR(BswM_SDC_SdConsumedEventGroupRequest, BSWM_VAR_NOINIT) Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode;
VAR(BswM_SDC_SdClientServiceRequest, BSWM_VAR_NOINIT) Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_requestedMode;
VAR(Rte_ModeType_ESH_Mode, BSWM_VAR_NOINIT) BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode;


VAR(boolean, BSWM_VAR_NOINIT) BswM_PreInitialized;
#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"


#define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

/* -----------------------------------------------------------------------------
    &&&~ FUNCTIONS
 ----------------------------------------------------------------------------- */
 

/**********************************************************************************************************************
 *  BswM_Action_RuleHandler()
 **********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_Action_RuleHandler(BswM_HandleType handleId, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType actionListIndex;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if ( BSWM_DEV_ERROR_DETECT == STD_ON )
  if (handleId < BswM_GetSizeOfRules(partitionIdx))
#endif
  {
    SchM_Enter_BswM_BSWM_EXCLUSIVE_AREA_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    actionListIndex = BswM_GetFctPtrOfRules(handleId, partitionIdx)(partitionIdx); /* SBSW_BSWM_RULEFCTPTR */
    SchM_Exit_BswM_BSWM_EXCLUSIVE_AREA_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    if(actionListIndex < BswM_GetSizeOfActionLists(partitionIdx))
    {
      retVal = BswM_GetFctPtrOfActionLists(actionListIndex, partitionIdx)(partitionIdx); /* SBSW_BSWM_ACTIONLISTFCTPTR */
    }
    else
    {
      retVal = E_OK;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  
  return retVal;
} 

/**********************************************************************************************************************
 *  BswM_UpdateRuleStates()
 **********************************************************************************************************************/
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_UpdateRuleStates(BswM_SizeOfRuleStatesType ruleId, 
                                                                   BswM_RuleStatesType state,
                                                                   BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  if (ruleId < BswM_GetSizeOfRuleStates(partitionIdx))
  {
    BswM_SetRuleStates(ruleId, state, partitionIdx); /* SBSW_BSWM_SETRULESTATE */
  }
  
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

/**********************************************************************************************************************
 *  BswM_UpdateTimer()
 **********************************************************************************************************************/
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_UpdateTimer(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx,
                                                              BswM_SizeOfTimerValueType timerId,
                                                              BswM_TimerValueType value)
{
  if (timerId < BswM_GetSizeOfTimerValue(partitionIdx))
  {
      SchM_Enter_BswM_BSWM_EXCLUSIVE_AREA_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      BswM_SetTimerValue(timerId, value, partitionIdx); /* SBSW_BSWM_SETTIMER */
      BswM_SetTimerState(timerId, (BswM_TimerStateType)((value != 0u) ? BSWM_TIMER_STARTED : BSWM_TIMER_STOPPED), partitionIdx); /* SBSW_BSWM_SETTIMER */
      SchM_Exit_BswM_BSWM_EXCLUSIVE_AREA_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

/**********************************************************************************************************************
 *  BswM_InitGenVarAndInitAL_BSWM_SINGLEPARTITION
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_InitGenVarAndInitAL_BSWM_SINGLEPARTITION(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{

  BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = 0xFFu;
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState = 0xFFu;
  BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState = 0xFFu;
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState = 0xFFu;
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState = 0xFFu;
  BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState = 0xFFu;
  BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState = 0xFFu;
  BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState = 0xFFu;
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState = 0xFFu;
  Request_ESH_RunRequest_0_requestedMode = RELEASED;
  Request_ESH_RunRequest_1_requestedMode = RELEASED;
  Request_ESH_PostRunRequest_0_requestedMode = RELEASED;
  Request_ESH_PostRunRequest_1_requestedMode = RELEASED;
  Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode = SDC_CEG_REQUESTED;
  Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_requestedMode = SDC_CLIENT_REQUESTED;
  Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode = SDC_CLIENT_REQUESTED;
  Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode = SDC_SERVER_AVAILABE;
  Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode = SDC_SERVER_AVAILABE;
  Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode = SDC_CEG_REQUESTED;
  Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode = SDC_SERVER_AVAILABE;
  Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode = SDC_CEG_REQUESTED;
  Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_requestedMode = SDC_CLIENT_REQUESTED;
  BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode = RTE_MODE_ESH_Mode_STARTUP;
  (void)BswM_ActionList_INIT_AL_Initialize(partitionIdx);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

/**********************************************************************************************************************
 *  BswM_ModeNotificationFct_BSWM_SINGLEPARTITION
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_ModeNotificationFct_BSWM_SINGLEPARTITION(void)
{
  if(BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode != 0xFFu)
  {
    if(Rte_Switch_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode(BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode) == RTE_E_OK)
    {
      BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState(BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState(BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState(BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState(BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState = 0xFFu;
    }
  }
  if(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState != 0xFFu)
  {
    if(Rte_Switch_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState(BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState) == RTE_E_OK)
    {
      BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState = 0xFFu;
    }
  }
}

/**********************************************************************************************************************
 *  BswM_SwcModeRequestUpdateFct_BSWM_SINGLEPARTITION
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_SwcModeRequestUpdateFct_BSWM_SINGLEPARTITION(void)
{
  uint32 mode;
  mode = Rte_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode();
  if (mode != RTE_TRANSITION_ESH_Mode)
  {
    BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode = (Rte_ModeType_ESH_Mode)mode;
  }
  (void)Rte_Read_Request_ESH_RunRequest_0_requestedMode(&Request_ESH_RunRequest_0_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_ESH_RunRequest_1_requestedMode(&Request_ESH_RunRequest_1_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_ESH_PostRunRequest_0_requestedMode(&Request_ESH_PostRunRequest_0_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_ESH_PostRunRequest_1_requestedMode(&Request_ESH_PostRunRequest_1_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode(&Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_requestedMode(&Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode(&Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode(&Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode(&Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode(&Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode(&Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode(&Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode); /* SBSW_BSWM_RTE_READ */
  (void)Rte_Read_Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_requestedMode(&Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_requestedMode); /* SBSW_BSWM_RTE_READ */
}

/**********************************************************************************************************************
 *  BswMActionListFunctions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_RunToPostRun
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_RunToPostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_Vlan10, FALSE);
  ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_Vlan23, FALSE);
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  EcuM_ClearValidatedWakeupEvent(ECUM_WKSOURCE_ALL_SOURCES);
  /*lint -restore */
  ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_Vlan1, FALSE);
  BswM_ESH_OnEnterPostRun();
  BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = RTE_MODE_ESH_Mode_POSTRUN;
  BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ESH_POST_RUN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_WaitForNvMToShutdown
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvMToShutdown(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_ESH_OnEnterShutdown();
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  (void)EcuM_GoToSelectedShutdownTarget();
  /*lint -restore */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_WakeupToPrep
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WakeupToPrep(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_ESH_OnEnterPrepShutdown();
  BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = RTE_MODE_ESH_Mode_SHUTDOWN;
  BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ESH_PREP_SHUTDOWN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_WaitForNvMWakeup
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvMWakeup(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_ESH_OnEnterWakeup();
  BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = RTE_MODE_ESH_Mode_WAKEUP;
  BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ESH_WAKEUP);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_WakeupToRun
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WakeupToRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_Vlan10, TRUE);
  (void)BswM_Action_RuleHandler(BSWM_ID_RULE_ESH_DemInit, partitionIdx);
  ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_Vlan23, TRUE);
  ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_Vlan1, TRUE);
  BswM_UpdateTimer(partitionIdx, BSWM_TMR_ESH_SelfRunRequestTimer, 10uL);
  BswM_ESH_OnEnterRun();
  BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = RTE_MODE_ESH_Mode_RUN;
  BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ESH_RUN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_PostRunToPrepShutdown
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PostRunToPrepShutdown(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Dem_Shutdown();
  /*lint -restore */
  BswM_RequestMode(BSWM_GENERIC_ESH_DemInitStatus, BSWM_GENERICVALUE_ESH_DemInitStatus_DEM_NOT_INITIALIZED);
  BswM_ESH_OnEnterPrepShutdown();
  BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = RTE_MODE_ESH_Mode_SHUTDOWN;
  BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ESH_PREP_SHUTDOWN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_ESH_PostRunToPrepCheck
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_ESH_PostRunToPrepCheck(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)BswM_Action_RuleHandler(BSWM_ID_RULE_ESH_PostRunToPrepNested, partitionIdx);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_PostRunToRun
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PostRunToRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_Vlan10, TRUE);
  BswM_UpdateTimer(partitionIdx, BSWM_TMR_ESH_SelfRunRequestTimer, 10uL);
  BswM_ESH_OnEnterRun();
  BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = RTE_MODE_ESH_Mode_RUN;
  BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ESH_RUN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_ExitPostRun
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_ExitPostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  ESH_Dem_PostRunRequested();
  (void)BswM_Action_RuleHandler(BSWM_ID_RULE_ESH_PostRunNested, partitionIdx);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_PrepShutdownToWaitForNvM
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PrepShutdownToWaitForNvM(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_ESH_OnEnterWaitForNvm();
  BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ESH_WAIT_FOR_NVM);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_INIT_AL_Initialize
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_INIT_AL_Initialize(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Det_Start();
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  EthTrcv_30_Tja1100_Init(EthTrcv_30_Tja1100_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Eth_30_Tc3xx_Init(Eth_30_Tc3xx_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  EthIf_Init(EthIf_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  SoAd_Init(SoAd_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Com_Init(Com_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  LdCom_Init(LdCom_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  PduR_Init(PduR_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  EthSM_Init(EthSM_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Nm_Init(Nm_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  UdpNm_Init(UdpNm_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  DoIP_Init(DoIP_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  TcpIp_Init(TcpIp_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  EthTSyn_Init(EthTSyn_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  NvM_Init();
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Sd_Init(Sd_Config_Ptr);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  StbM_Init(StbM_Config_Ptr);
  /*lint -restore */
  BswM_INIT_NvMReadAll();
  BswM_AL_SetProgrammableInterrupts();
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Rte_Start();
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  ComM_Init();
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Dcm_Init(NULL_PTR);
  /*lint -restore */
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Dem_Init(Dem_Config_Ptr);
  /*lint -restore */
  BswM_Action_EthTrcvDebug();
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ConsumedEventGroupSetState(SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CD_VechicleInfo, BSWM_SD_CONSUMED_EVENTGROUP_RELEASED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ConsumedEventGroupSetState(SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CD_VechicleInfo, BSWM_SD_CONSUMED_EVENTGROUP_REQUESTED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState = RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState = RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState = RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState = RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState = RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState = RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ClientServiceSetState(SdConf_SdClientService_SdCLientService_0xC3CB_VechicleSpeed, BSWM_SD_CLIENT_SERVICE_RELEASED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ClientServiceSetState(SdConf_SdClientService_SdCLientService_0xC3CB_VechicleSpeed, BSWM_SD_CLIENT_SERVICE_REQUESTED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState = RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState = RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState = RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState = RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState = RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState = RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ClientServiceSetState(SdConf_SdClientService_SdClientService_0xC3CC_VechicleStatus, BSWM_SD_CLIENT_SERVICE_RELEASED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ClientServiceSetState(SdConf_SdClientService_SdClientService_0xC3CC_VechicleStatus, BSWM_SD_CLIENT_SERVICE_REQUESTED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ServerServiceSetState(SdConf_SdServerService_SdServerService_0xC3C0_FaultInfo, BSWM_SD_SERVER_SERVICE_DOWN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ServerServiceSetState(SdConf_SdServerService_SdServerService_0xC3C0_FaultInfo, BSWM_SD_SERVER_SERVICE_AVAILABLE);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ServerServiceSetState(SdConf_SdServerService_SdServerService_0xC3C1_SenState, BSWM_SD_SERVER_SERVICE_DOWN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ServerServiceSetState(SdConf_SdServerService_SdServerService_0xC3C1_SenState, BSWM_SD_SERVER_SERVICE_AVAILABLE);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState = RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState = RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ConsumedEventGroupSetState(SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CC_VechicleStatus, BSWM_SD_CONSUMED_EVENTGROUP_RELEASED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ConsumedEventGroupSetState(SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CC_VechicleStatus, BSWM_SD_CONSUMED_EVENTGROUP_REQUESTED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState = RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_Switch_SDC_Mode_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState = RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE;
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ServerServiceSetState(SdConf_SdServerService_SdServerService_0xC3C2_EcuState, BSWM_SD_SERVER_SERVICE_DOWN);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ServerServiceSetState(SdConf_SdServerService_SdServerService_0xC3C2_EcuState, BSWM_SD_SERVER_SERVICE_AVAILABLE);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ConsumedEventGroupSetState(SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CB_VechicleSpeed, BSWM_SD_CONSUMED_EVENTGROUP_RELEASED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ConsumedEventGroupSetState(SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CB_VechicleSpeed, BSWM_SD_CONSUMED_EVENTGROUP_REQUESTED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ClientServiceSetState(SdConf_SdClientService_SdCLientService_0xC3CD_VechicleInfo, BSWM_SD_CLIENT_SERVICE_RELEASED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  (void)Sd_ClientServiceSetState(SdConf_SdClientService_SdCLientService_0xC3CD_VechicleInfo, BSWM_SD_CLIENT_SERVICE_REQUESTED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswM_ActionList_ESH_AL_DemInit
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_DemInit(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
  Dem_Init(Dem_Config_Ptr);
  /*lint -restore */
  BswM_RequestMode(BSWM_GENERIC_ESH_DemInitStatus, BSWM_GENERICVALUE_ESH_DemInitStatus_DEM_INITIALIZED);
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return E_OK;
}/* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  BswMRuleFunctions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  BswM_Rule_ESH_RunToPostRun
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_RunToPostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_RunToPostRunTransition. */ /* PRQA S 3415 1 */ /* MD_BSWM_3415 */
  if(((BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_RUN) && (BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode == RTE_MODE_ESH_Mode_RUN)) && (((Request_ESH_RunRequest_0_requestedMode == RELEASED) && (Request_ESH_RunRequest_1_requestedMode == RELEASED)) && (BswM_GetTimerState(0, 0u) == BSWM_TIMER_EXPIRED)))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_RunToPostRun. */
    retVal = BSWM_ID_AL_ESH_AL_RunToPostRun;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_WaitToShutdown
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WaitToShutdown(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_WaitForNvMToShutdown. */ /* PRQA S 3415 1 */ /* MD_BSWM_3415 */
  if((BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_WAIT_FOR_NVM) && (EcuM_GetValidatedWakeupEvents() == 0u))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_WaitForNvMToShutdown. */
    retVal = BSWM_ID_AL_ESH_AL_WaitForNvMToShutdown;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_WakeupToPrep
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WakeupToPrep(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_WakeupToPrepShutdown. */ /* PRQA S 3415 1 */ /* MD_BSWM_3415 */
  if((BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_WAKEUP) && (EcuM_GetPendingWakeupEvents() == 0u) && (EcuM_GetValidatedWakeupEvents() == 0u) && (BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode == RTE_MODE_ESH_Mode_WAKEUP))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_WakeupToPrep. */
    retVal = BSWM_ID_AL_ESH_AL_WakeupToPrep;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_WaitToWakeup
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WaitToWakeup(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_WaitForNvMToWakeup. */ /* PRQA S 3415 1 */ /* MD_BSWM_3415 */
  if((BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_WAIT_FOR_NVM) && (EcuM_GetValidatedWakeupEvents() != 0u))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_WaitForNvMWakeup. */
    retVal = BSWM_ID_AL_ESH_AL_WaitForNvMWakeup;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_WakeupToRun
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_WakeupToRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_WakeupToRun. */ /* PRQA S 3415 1 */ /* MD_BSWM_3415 */
  if((BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_WAKEUP) && (EcuM_GetValidatedWakeupEvents() != 0u) && (BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode == RTE_MODE_ESH_Mode_WAKEUP))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_WakeupToRun. */
    retVal = BSWM_ID_AL_ESH_AL_WakeupToRun;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_InitToWakeup
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_InitToWakeup(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_InitToWakeup. */
  if(BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_INIT)
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_InitToWakeup. */
    retVal = BSWM_ID_AL_ESH_AL_InitToWakeup;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_PostRunToPrepNested
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PostRunToPrepNested(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_Dem_PostRunRequested. */
  if(((Request_ESH_PostRunRequest_0_requestedMode == RELEASED) && (Request_ESH_PostRunRequest_1_requestedMode == RELEASED)) && (BswM_GetGenericState(1, 0u) == BSWM_GENERICVALUE_ESH_DemPostRunRequested_FALSE))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_PostRunToPrepShutdown. */
    retVal = BSWM_ID_AL_ESH_AL_PostRunToPrepShutdown;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_PostRunNested
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PostRunNested(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal;
  /* Evaluate logical expression ESH_LE_PostRunToRun. */
  if(((Request_ESH_RunRequest_0_requestedMode == REQUESTED) || (Request_ESH_RunRequest_1_requestedMode == REQUESTED)) || (EcuM_GetValidatedWakeupEvents() != 0u))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_PostRunToRun. */
    retVal = BSWM_ID_AL_ESH_AL_PostRunToRun;
  }
  else
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_ESH_PostRunToPrepCheck. */
    retVal = BSWM_ID_AL_ESH_AL_ESH_PostRunToPrepCheck;
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_PostRun
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PostRun(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_PostRun. */
  if((BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_POST_RUN) && (BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode == RTE_MODE_ESH_Mode_POSTRUN))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_ExitPostRun. */
    retVal = BSWM_ID_AL_ESH_AL_ExitPostRun;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_PrepToWait
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_PrepToWait(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_PrepShutdownToWaitForNvM. */
  if((BswM_GetGenericState(2, 0u) == BSWM_GENERICVALUE_ESH_State_ESH_PREP_SHUTDOWN) && (BswM_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode == RTE_MODE_ESH_Mode_SHUTDOWN))
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_PrepShutdownToWaitForNvM. */
    retVal = BSWM_ID_AL_ESH_AL_PrepShutdownToWaitForNvM;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo. */
  if(Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode == SDC_CEG_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_C_SdCLientService_0xC3CB_VechicleSpeedIsAvailable. */
  if(BswM_GetSdClientServiceState(0, 0u) == SD_CLIENT_SERVICE_AVAILABLE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE. */
      retVal = BSWM_ID_AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_AVAILABLE;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN. */
      retVal = BSWM_ID_AL_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_DOWN;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenStateIsRequested. */
  if(BswM_GetSdEventHandlerState(1, 0u) == SD_EVENT_HANDLER_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState. */
      retVal = BSWM_ID_AL_SDC_AL_SdRequest_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState. */
      retVal = BSWM_ID_AL_SDC_AL_SdRelease_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeedIsAvailable. */
  if(BswM_GetSdConsumedEventState(0, 0u) == SD_CONSUMED_EVENTGROUP_AVAILABLE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE. */
      retVal = BSWM_ID_AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_AVAILABLE;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN. */
      retVal = BSWM_ID_AL_SDC_AL_SdDown_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_DOWN;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed. */
  if(Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_requestedMode == SDC_CLIENT_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_C_SdCLientService_0xC3CD_VechicleInfoIsAvailable. */
  if(BswM_GetSdClientServiceState(1, 0u) == SD_CLIENT_SERVICE_AVAILABLE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE. */
      retVal = BSWM_ID_AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_AVAILABLE;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN. */
      retVal = BSWM_ID_AL_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_DOWN;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatusIsAvailable. */
  if(BswM_GetSdConsumedEventState(1, 0u) == SD_CONSUMED_EVENTGROUP_AVAILABLE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE. */
      retVal = BSWM_ID_AL_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_AVAILABLE;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN. */
      retVal = BSWM_ID_AL_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_DOWN;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfoIsRequested. */
  if(BswM_GetSdEventHandlerState(0, 0u) == SD_EVENT_HANDLER_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo. */
      retVal = BSWM_ID_AL_SDC_AL_SdRequest_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo. */
      retVal = BSWM_ID_AL_SDC_AL_SdRelease_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus. */
  if(Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode == SDC_CLIENT_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_S_SdServerService_0xC3C0_FaultInfo. */
  if(Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode == SDC_SERVER_AVAILABE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C0_FaultInfo;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C0_FaultInfo, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C0_FaultInfo;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_S_SdServerService_0xC3C1_SenState. */
  if(Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode == SDC_SERVER_AVAILABE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C1_SenState;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C1_SenState, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C1_SenState;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_C_SdClientService_0xC3CC_VechicleStatusIsAvailable. */
  if(BswM_GetSdClientServiceState(2, 0u) == SD_CLIENT_SERVICE_AVAILABLE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE. */
      retVal = BSWM_ID_AL_SDC_AL_SdAvailable_C_SdClientService_0xC3CC_VechicleStatus_AVAILABLE;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdClientService_0xC3CC_VechicleStatus, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN. */
      retVal = BSWM_ID_AL_SDC_AL_SdDown_C_SdClientService_0xC3CC_VechicleStatus_DOWN;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus. */
  if(Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode == SDC_CEG_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfoIsAvailable. */
  if(BswM_GetSdConsumedEventState(2, 0u) == SD_CONSUMED_EVENTGROUP_AVAILABLE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE. */
      retVal = BSWM_ID_AL_SDC_AL_SdAvailable_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_AVAILABLE;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_SdStateChange_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN. */
      retVal = BSWM_ID_AL_SDC_AL_SdDown_C_SdCLientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_DOWN;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_S_SdServerService_0xC3C2_EcuState. */
  if(Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode == SDC_SERVER_AVAILABE)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_S_SdServerService_0xC3C2_EcuState;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_S_SdServerService_0xC3C2_EcuState, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_S_SdServerService_0xC3C2_EcuState;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed. */
  if(Request_SDC_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode == SDC_CEG_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression SDC_LE_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo. */
  if(Request_SDC_C_SdCLientService_0xC3CD_VechicleInfo_requestedMode == SDC_CLIENT_REQUESTED)
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo, partitionIdx) != BSWM_TRUE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo, BSWM_TRUE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo;
    }
  }
  else
  {
    if( BswM_GetRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo, partitionIdx) != BSWM_FALSE ) /* COV_BSWM_TRIGGEREDRULEEXECUTION */
    {
      BswM_UpdateRuleStates(BSWM_ID_RULE_SDC_ApplRequest_C_SdCLientService_0xC3CD_VechicleInfo, BSWM_FALSE, partitionIdx);
      /* Return triggered action list BswM_ActionList_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo. */
      retVal = BSWM_ID_AL_SDC_AL_ApplRelease_C_SdCLientService_0xC3CD_VechicleInfo;
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}

/**********************************************************************************************************************
 *  BswM_Rule_ESH_DemInit
 *********************************************************************************************************************/
BSWM_LOCAL FUNC(BswM_HandleType, BSWM_CODE) BswM_Rule_ESH_DemInit(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  BswM_HandleType retVal = BSWM_NO_ACTIONLIST(partitionIdx);
  /* Evaluate logical expression ESH_LE_DemNotInitialized. */
  if(BswM_GetGenericState(0, 0u) == BSWM_GENERICVALUE_ESH_DemInitStatus_DEM_NOT_INITIALIZED)
  {
    /* Return conditional action list BswM_ActionList_ESH_AL_DemInit. */
    retVal = BSWM_ID_AL_ESH_AL_DemInit;
  }
  /* No false action list configured. */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}


#define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

