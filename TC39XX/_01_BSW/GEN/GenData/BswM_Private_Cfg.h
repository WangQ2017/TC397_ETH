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
 *              File: BswM_Private_Cfg.h
 *   Generation Time: 2025-12-20 15:18:05
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined(BSWM_PRIVATE_CFG_H)
#define BSWM_PRIVATE_CFG_H


/* -----------------------------------------------------------------------------
    &&&~ INCLUDE
 ----------------------------------------------------------------------------- */
#include "BswM_Cfg.h"
#include "Rte_BswM.h" 
#include "EcuM.h" 
#include "Rte_Main.h" 
#include "EthTrcv_30_Tja1100.h" 
#include "Eth_30_Tc3xx.h" 
#include "SoAd.h" 
#include "EthIf.h" 
#include "Com.h" 
#include "PduR.h" 
#include "EthSM.h" 
#include "Nm.h" 
#include "UdpNm.h" 
#include "TcpIp.h" 
#include "EthTSyn.h" 
#include "StbM.h" 
#include "ComM.h" 
#include "Det.h" 
#include "EthTrcv_30_Tja1100_Hw_Int.h" 



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/


# define BSWM_FUNCTION_BASED STD_ON

#if (defined (BSWM_ACTIONLISTSTRUEIDXOFRULES))
# if ((BSWM_ACTIONLISTSTRUEIDXOFRULES == STD_ON) && defined (BSWM_NO_ACTIONLISTSTRUEIDXOFRULES))
#  define BSWM_NO_ACTIONLIST(partition) BSWM_NO_ACTIONLISTSTRUEIDXOFRULES
# endif
#endif
#if (defined(BSWM_NO_ACTIONLIST))
#else
# if(defined(BSWM_ACTIONLISTSFALSEIDXOFRULES))
#  if ((BSWM_ACTIONLISTSFALSEIDXOFRULES == STD_ON) && defined (BSWM_NO_ACTIONLISTSFALSEIDXOFRULES))
#   define BSWM_NO_ACTIONLIST(partition) BSWM_NO_ACTIONLISTSFALSEIDXOFRULES
#  endif
# endif
#endif
#if (defined(BSWM_NO_ACTIONLIST))
#else
# if(defined(BSWM_SIZEOFACTIONLISTS))
#  if (BSWM_SIZEOFACTIONLISTS == STD_ON)
#   define BSWM_NO_ACTIONLIST(partition) BswM_GetSizeOfActionLists(partition) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
# endif
#endif
#if (defined(BSWM_NO_ACTIONLIST))
#else
# define BSWM_NO_ACTIONLIST(partition) 255
#endif


#if BSWM_NVMJOBSTATE == STD_ON
#define NVM_SERVICE_ID_READALL   (uint8)0x0Cu
#define NVM_SERVICE_ID_WRITEALL  (uint8)0x0Du
#endif



#define BSWM_ID_RULE_ESH_RunToPostRun        0u 
#define BSWM_ID_RULE_ESH_WaitToShutdown      1u 
#define BSWM_ID_RULE_ESH_WakeupToPrep        2u 
#define BSWM_ID_RULE_ESH_WaitToWakeup        3u 
#define BSWM_ID_RULE_ESH_WakeupToRun         4u 
#define BSWM_ID_RULE_ESH_InitToWakeup        5u 
#define BSWM_ID_RULE_ESH_PostRunToPrepNested 6u 
#define BSWM_ID_RULE_ESH_PostRunNested       7u 
#define BSWM_ID_RULE_ESH_PostRun             8u 
#define BSWM_ID_RULE_ESH_PrepToWait          9u 

#define BSWM_ID_AL_ESH_AL_RunToPostRun             0u 
#define BSWM_ID_AL_ESH_AL_WaitForNvMToShutdown     1u 
#define BSWM_ID_AL_ESH_AL_WakeupToPrep             2u 
#define BSWM_ID_AL_ESH_AL_WaitForNvMWakeup         3u 
#define BSWM_ID_AL_ESH_AL_WakeupToRun              4u 
#define BSWM_ID_AL_ESH_AL_InitToWakeup             5u 
#define BSWM_ID_AL_ESH_AL_PostRunToPrepShutdown    6u 
#define BSWM_ID_AL_ESH_AL_ESH_PostRunToPrepCheck   7u 
#define BSWM_ID_AL_ESH_AL_PostRunToRun             8u 
#define BSWM_ID_AL_ESH_AL_ExitPostRun              9u 
#define BSWM_ID_AL_ESH_AL_PrepShutdownToWaitForNvM 10u 
#define BSWM_ID_AL_INIT_AL_Initialize              11u 


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  BswMPCGetConstantDuplicatedRootDataMacros  BswM Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define BswM_GetPartitionIdentifiersOfPCConfig()                                                    BswM_PartitionIdentifiers  /**< the pointer to BswM_PartitionIdentifiers */
#define BswM_GetSizeOfPartitionIdentifiersOfPCConfig()                                              1u  /**< the number of accomplishable value elements in BswM_PartitionIdentifiers */
#define BswM_GetActionListQueueOfPCPartitionConfig(partitionIndex)                                  BswM_ActionListQueue.raw  /**< the pointer to BswM_ActionListQueue */
#define BswM_GetActionListsOfPCPartitionConfig(partitionIndex)                                      BswM_ActionLists  /**< the pointer to BswM_ActionLists */
#define BswM_GetDeferredRulesOfPCPartitionConfig(partitionIndex)                                    BswM_DeferredRules  /**< the pointer to BswM_DeferredRules */
#define BswM_GetForcedActionListPriorityOfPCPartitionConfig(partitionIndex)                         (&(BswM_ForcedActionListPriority))  /**< the pointer to BswM_ForcedActionListPriority */
#define BswM_GetGenericMappingOfPCPartitionConfig(partitionIndex)                                   BswM_GenericMapping  /**< the pointer to BswM_GenericMapping */
#define BswM_GetGenericStateOfPCPartitionConfig(partitionIndex)                                     BswM_GenericState  /**< the pointer to BswM_GenericState */
#define BswM_GetImmediateUserOfPCPartitionConfig(partitionIndex)                                    BswM_ImmediateUser  /**< the pointer to BswM_ImmediateUser */
#define BswM_GetInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                              BswM_InitGenVarAndInitAL  /**< the pointer to BswM_InitGenVarAndInitAL */
#define BswM_GetInitializedOfPCPartitionConfig(partitionIndex)                                      (&(BswM_Initialized))  /**< the pointer to BswM_Initialized */
#define BswM_GetModeNotificationFctOfPCPartitionConfig(partitionIndex)                              BswM_ModeNotificationFct  /**< the pointer to BswM_ModeNotificationFct */
#define BswM_GetModeRequestQueueOfPCPartitionConfig(partitionIndex)                                 BswM_ModeRequestQueue  /**< the pointer to BswM_ModeRequestQueue */
#define BswM_GetQueueSemaphoreOfPCPartitionConfig(partitionIndex)                                   (&(BswM_QueueSemaphore))  /**< the pointer to BswM_QueueSemaphore */
#define BswM_GetQueueWrittenOfPCPartitionConfig(partitionIndex)                                     (&(BswM_QueueWritten))  /**< the pointer to BswM_QueueWritten */
#define BswM_GetRuleStatesOfPCPartitionConfig(partitionIndex)                                       BswM_RuleStates.raw  /**< the pointer to BswM_RuleStates */
#define BswM_GetRulesIndOfPCPartitionConfig(partitionIndex)                                         BswM_RulesInd  /**< the pointer to BswM_RulesInd */
#define BswM_GetRulesOfPCPartitionConfig(partitionIndex)                                            BswM_Rules  /**< the pointer to BswM_Rules */
#define BswM_GetSizeOfActionListsOfPCPartitionConfig(partitionIndex)                                12u  /**< the number of accomplishable value elements in BswM_ActionLists */
#define BswM_GetSizeOfDeferredRulesOfPCPartitionConfig(partitionIndex)                              7u  /**< the number of accomplishable value elements in BswM_DeferredRules */
#define BswM_GetSizeOfGenericMappingOfPCPartitionConfig(partitionIndex)                             1u  /**< the number of accomplishable value elements in BswM_GenericMapping */
#define BswM_GetSizeOfGenericStateOfPCPartitionConfig(partitionIndex)                               1u  /**< the number of accomplishable value elements in BswM_GenericState */
#define BswM_GetSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)                              1u  /**< the number of accomplishable value elements in BswM_ImmediateUser */
#define BswM_GetSizeOfInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                        1u  /**< the number of accomplishable value elements in BswM_InitGenVarAndInitAL */
#define BswM_GetSizeOfModeNotificationFctOfPCPartitionConfig(partitionIndex)                        1u  /**< the number of accomplishable value elements in BswM_ModeNotificationFct */
#define BswM_GetSizeOfRuleStatesOfPCPartitionConfig(partitionIndex)                                 10u  /**< the number of accomplishable value elements in BswM_RuleStates */
#define BswM_GetSizeOfRulesIndOfPCPartitionConfig(partitionIndex)                                   8u  /**< the number of accomplishable value elements in BswM_RulesInd */
#define BswM_GetSizeOfRulesOfPCPartitionConfig(partitionIndex)                                      10u  /**< the number of accomplishable value elements in BswM_Rules */
#define BswM_GetSizeOfSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                    1u  /**< the number of accomplishable value elements in BswM_SwcModeRequestUpdateFct */
#define BswM_GetSizeOfTimerStateOfPCPartitionConfig(partitionIndex)                                 1u  /**< the number of accomplishable value elements in BswM_TimerState */
#define BswM_GetSizeOfTimerValueOfPCPartitionConfig(partitionIndex)                                 1u  /**< the number of accomplishable value elements in BswM_TimerValue */
#define BswM_GetSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                          BswM_SwcModeRequestUpdateFct  /**< the pointer to BswM_SwcModeRequestUpdateFct */
#define BswM_GetTimerStateOfPCPartitionConfig(partitionIndex)                                       BswM_TimerState.raw  /**< the pointer to BswM_TimerState */
#define BswM_GetTimerValueOfPCPartitionConfig(partitionIndex)                                       BswM_TimerValue.raw  /**< the pointer to BswM_TimerValue */
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCGetDuplicatedRootDataMacros  BswM Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define BswM_GetSizeOfActionListQueueOfPCPartitionConfig(partitionIndex)                            BswM_GetSizeOfActionListsOfPCPartitionConfig(partitionIndex)  /**< the number of accomplishable value elements in BswM_ActionListQueue */
#define BswM_GetSizeOfModeRequestQueueOfPCPartitionConfig(partitionIndex)                           BswM_GetSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)  /**< the number of accomplishable value elements in BswM_ModeRequestQueue */
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCGetDataMacros  BswM Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define BswM_GetActionListQueue(Index, partitionIndex)                                              (BswM_GetActionListQueueOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetFctPtrOfActionLists(Index, partitionIndex)                                          (BswM_GetActionListsOfPCPartitionConfig(partitionIndex)[(Index)].FctPtrOfActionLists)
#define BswM_GetRulesIdxOfDeferredRules(Index, partitionIndex)                                      (BswM_GetDeferredRulesOfPCPartitionConfig(partitionIndex)[(Index)].RulesIdxOfDeferredRules)
#define BswM_GetForcedActionListPriority(partitionIndex)                                            ((*(BswM_GetForcedActionListPriorityOfPCPartitionConfig(partitionIndex))))
#define BswM_GetGenericState(Index, partitionIndex)                                                 (BswM_GetGenericStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetInitGenVarAndInitAL(Index, partitionIndex)                                          (BswM_GetInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_IsInitialized(partitionIndex)                                                          (((*(BswM_GetInitializedOfPCPartitionConfig(partitionIndex)))) != FALSE)
#define BswM_GetModeNotificationFct(Index, partitionIndex)                                          (BswM_GetModeNotificationFctOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetModeRequestQueue(Index, partitionIndex)                                             (BswM_GetModeRequestQueueOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetPCPartitionConfigIdxOfPartitionIdentifiers(Index)                                   (BswM_GetPartitionIdentifiersOfPCConfig()[(Index)].PCPartitionConfigIdxOfPartitionIdentifiers)
#define BswM_GetPartitionSNVOfPartitionIdentifiers(Index)                                           (BswM_GetPartitionIdentifiersOfPCConfig()[(Index)].PartitionSNVOfPartitionIdentifiers)
#define BswM_GetQueueSemaphore(partitionIndex)                                                      ((*(BswM_GetQueueSemaphoreOfPCPartitionConfig(partitionIndex))))
#define BswM_IsQueueWritten(partitionIndex)                                                         (((*(BswM_GetQueueWrittenOfPCPartitionConfig(partitionIndex)))) != FALSE)
#define BswM_GetRuleStates(Index, partitionIndex)                                                   (BswM_GetRuleStatesOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetFctPtrOfRules(Index, partitionIndex)                                                (BswM_GetRulesOfPCPartitionConfig(partitionIndex)[(Index)].FctPtrOfRules)
#define BswM_GetIdOfRules(Index, partitionIndex)                                                    (BswM_GetRulesOfPCPartitionConfig(partitionIndex)[(Index)].IdOfRules)
#define BswM_GetRuleStatesIdxOfRules(Index, partitionIndex)                                         (BswM_GetRulesOfPCPartitionConfig(partitionIndex)[(Index)].RuleStatesIdxOfRules)
#define BswM_GetRulesInd(Index, partitionIndex)                                                     (BswM_GetRulesIndOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetSwcModeRequestUpdateFct(Index, partitionIndex)                                      (BswM_GetSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetTimerState(Index, partitionIndex)                                                   (BswM_GetTimerStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetTimerValue(Index, partitionIndex)                                                   (BswM_GetTimerValueOfPCPartitionConfig(partitionIndex)[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCGetDeduplicatedDataMacros  BswM Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define BswM_GetExternalIdOfGenericMapping(Index, partitionIndex)                                   BSWM_GENERIC_ESH_State  /**< External id of BswMGenericRequest. */
#define BswM_GetImmediateUserEndIdxOfGenericMapping(Index, partitionIndex)                          1u  /**< the end index of the 0:n relation pointing to BswM_ImmediateUser */
#define BswM_GetImmediateUserStartIdxOfGenericMapping(Index, partitionIndex)                        0u  /**< the start index of the 0:n relation pointing to BswM_ImmediateUser */
#define BswM_IsImmediateUserUsedOfGenericMapping(Index, partitionIndex)                             (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to BswM_ImmediateUser */
#define BswM_GetInitValueOfGenericMapping(Index, partitionIndex)                                    BSWM_GENERICVALUE_ESH_State_ESH_INIT  /**< Initialization value of port. */
#define BswM_GetMaskedBitsOfImmediateUser(Index, partitionIndex)                                    0x03u  /**< contains bitcoded the boolean data of BswM_OnInitOfImmediateUser, BswM_RulesIndUsedOfImmediateUser */
#define BswM_IsOnInitOfImmediateUser(Index, partitionIndex)                                         (((TRUE)) != FALSE)  /**< Arbitrate depending rules on initialization. */
#define BswM_GetRulesIndEndIdxOfImmediateUser(Index, partitionIndex)                                8u  /**< the end index of the 0:n relation pointing to BswM_RulesInd */
#define BswM_GetRulesIndStartIdxOfImmediateUser(Index, partitionIndex)                              0u  /**< the start index of the 0:n relation pointing to BswM_RulesInd */
#define BswM_IsRulesIndUsedOfImmediateUser(Index, partitionIndex)                                   (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to BswM_RulesInd */
#define BswM_GetInitOfRules(Index, partitionIndex)                                                  BSWM_FALSE  /**< Initialization value of rule state (TRUE, FALSE, UNDEFINED or DEACTIVATED). */
#define BswM_GetSizeOfActionListQueue(partitionIndex)                                               BswM_GetSizeOfActionListQueueOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfActionLists(partitionIndex)                                                   BswM_GetSizeOfActionListsOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfDeferredRules(partitionIndex)                                                 BswM_GetSizeOfDeferredRulesOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfGenericMapping(partitionIndex)                                                BswM_GetSizeOfGenericMappingOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfGenericState(partitionIndex)                                                  BswM_GetSizeOfGenericStateOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfImmediateUser(partitionIndex)                                                 BswM_GetSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfInitGenVarAndInitAL(partitionIndex)                                           BswM_GetSizeOfInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfModeNotificationFct(partitionIndex)                                           BswM_GetSizeOfModeNotificationFctOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfModeRequestQueue(partitionIndex)                                              BswM_GetSizeOfModeRequestQueueOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfPartitionIdentifiers()                                                        BswM_GetSizeOfPartitionIdentifiersOfPCConfig()
#define BswM_GetSizeOfRuleStates(partitionIndex)                                                    BswM_GetSizeOfRuleStatesOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfRules(partitionIndex)                                                         BswM_GetSizeOfRulesOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfRulesInd(partitionIndex)                                                      BswM_GetSizeOfRulesIndOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfSwcModeRequestUpdateFct(partitionIndex)                                       BswM_GetSizeOfSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfTimerState(partitionIndex)                                                    BswM_GetSizeOfTimerStateOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfTimerValue(partitionIndex)                                                    BswM_GetSizeOfTimerValueOfPCPartitionConfig(partitionIndex)
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCSetDataMacros  BswM Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define BswM_SetActionListQueue(Index, Value, partitionIndex)                                       BswM_GetActionListQueueOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetForcedActionListPriority(Value, partitionIndex)                                     (*(BswM_GetForcedActionListPriorityOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetGenericState(Index, Value, partitionIndex)                                          BswM_GetGenericStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetInitialized(Value, partitionIndex)                                                  (*(BswM_GetInitializedOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetModeRequestQueue(Index, Value, partitionIndex)                                      BswM_GetModeRequestQueueOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetQueueSemaphore(Value, partitionIndex)                                               (*(BswM_GetQueueSemaphoreOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetQueueWritten(Value, partitionIndex)                                                 (*(BswM_GetQueueWrittenOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetRuleStates(Index, Value, partitionIndex)                                            BswM_GetRuleStatesOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetTimerState(Index, Value, partitionIndex)                                            BswM_GetTimerStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetTimerValue(Index, Value, partitionIndex)                                            BswM_GetTimerValueOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCHasMacros  BswM Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define BswM_HasActionListQueue(partitionIndex)                                                     (TRUE != FALSE)
#define BswM_HasActionLists(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasFctPtrOfActionLists(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasDeferredRules(partitionIndex)                                                       (TRUE != FALSE)
#define BswM_HasRulesIdxOfDeferredRules(partitionIndex)                                             (TRUE != FALSE)
#define BswM_HasForcedActionListPriority(partitionIndex)                                            (TRUE != FALSE)
#define BswM_HasGenericMapping(partitionIndex)                                                      (TRUE != FALSE)
#define BswM_HasExternalIdOfGenericMapping(partitionIndex)                                          (TRUE != FALSE)
#define BswM_HasImmediateUserEndIdxOfGenericMapping(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasImmediateUserStartIdxOfGenericMapping(partitionIndex)                               (TRUE != FALSE)
#define BswM_HasImmediateUserUsedOfGenericMapping(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasInitValueOfGenericMapping(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasGenericState(partitionIndex)                                                        (TRUE != FALSE)
#define BswM_HasImmediateUser(partitionIndex)                                                       (TRUE != FALSE)
#define BswM_HasMaskedBitsOfImmediateUser(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasOnInitOfImmediateUser(partitionIndex)                                               (TRUE != FALSE)
#define BswM_HasRulesIndEndIdxOfImmediateUser(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasRulesIndStartIdxOfImmediateUser(partitionIndex)                                     (TRUE != FALSE)
#define BswM_HasRulesIndUsedOfImmediateUser(partitionIndex)                                         (TRUE != FALSE)
#define BswM_HasInitGenVarAndInitAL(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasInitialized(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasModeNotificationFct(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasModeRequestQueue(partitionIndex)                                                    (TRUE != FALSE)
#define BswM_HasPartitionIdentifiers()                                                              (TRUE != FALSE)
#define BswM_HasPCPartitionConfigIdxOfPartitionIdentifiers()                                        (TRUE != FALSE)
#define BswM_HasPartitionSNVOfPartitionIdentifiers()                                                (TRUE != FALSE)
#define BswM_HasQueueSemaphore(partitionIndex)                                                      (TRUE != FALSE)
#define BswM_HasQueueWritten(partitionIndex)                                                        (TRUE != FALSE)
#define BswM_HasRuleStates(partitionIndex)                                                          (TRUE != FALSE)
#define BswM_HasRules(partitionIndex)                                                               (TRUE != FALSE)
#define BswM_HasFctPtrOfRules(partitionIndex)                                                       (TRUE != FALSE)
#define BswM_HasIdOfRules(partitionIndex)                                                           (TRUE != FALSE)
#define BswM_HasInitOfRules(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasRuleStatesIdxOfRules(partitionIndex)                                                (TRUE != FALSE)
#define BswM_HasRulesInd(partitionIndex)                                                            (TRUE != FALSE)
#define BswM_HasSizeOfActionListQueue(partitionIndex)                                               (TRUE != FALSE)
#define BswM_HasSizeOfActionLists(partitionIndex)                                                   (TRUE != FALSE)
#define BswM_HasSizeOfDeferredRules(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasSizeOfGenericMapping(partitionIndex)                                                (TRUE != FALSE)
#define BswM_HasSizeOfGenericState(partitionIndex)                                                  (TRUE != FALSE)
#define BswM_HasSizeOfImmediateUser(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasSizeOfInitGenVarAndInitAL(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasSizeOfModeNotificationFct(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasSizeOfModeRequestQueue(partitionIndex)                                              (TRUE != FALSE)
#define BswM_HasSizeOfPartitionIdentifiers()                                                        (TRUE != FALSE)
#define BswM_HasSizeOfRuleStates(partitionIndex)                                                    (TRUE != FALSE)
#define BswM_HasSizeOfRules(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasSizeOfRulesInd(partitionIndex)                                                      (TRUE != FALSE)
#define BswM_HasSizeOfSwcModeRequestUpdateFct(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasSizeOfTimerState(partitionIndex)                                                    (TRUE != FALSE)
#define BswM_HasSizeOfTimerValue(partitionIndex)                                                    (TRUE != FALSE)
#define BswM_HasSwcModeRequestUpdateFct(partitionIndex)                                             (TRUE != FALSE)
#define BswM_HasTimerState(partitionIndex)                                                          (TRUE != FALSE)
#define BswM_HasTimerValue(partitionIndex)                                                          (TRUE != FALSE)
#define BswM_HasPCConfig()                                                                          (TRUE != FALSE)
#define BswM_HasPCPartitionConfigOfPCConfig()                                                       (TRUE != FALSE)
#define BswM_HasPartitionIdentifiersOfPCConfig()                                                    (TRUE != FALSE)
#define BswM_HasSizeOfPartitionIdentifiersOfPCConfig()                                              (TRUE != FALSE)
#define BswM_HasPCPartitionConfig()                                                                 (TRUE != FALSE)
#define BswM_HasActionListQueueOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define BswM_HasActionListsOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasDeferredRulesOfPCPartitionConfig(partitionIndex)                                    (TRUE != FALSE)
#define BswM_HasForcedActionListPriorityOfPCPartitionConfig(partitionIndex)                         (TRUE != FALSE)
#define BswM_HasGenericMappingOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasGenericStateOfPCPartitionConfig(partitionIndex)                                     (TRUE != FALSE)
#define BswM_HasImmediateUserOfPCPartitionConfig(partitionIndex)                                    (TRUE != FALSE)
#define BswM_HasInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasInitializedOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasModeNotificationFctOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasModeRequestQueueOfPCPartitionConfig(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasQueueSemaphoreOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasQueueWrittenOfPCPartitionConfig(partitionIndex)                                     (TRUE != FALSE)
#define BswM_HasRuleStatesOfPCPartitionConfig(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasRulesIndOfPCPartitionConfig(partitionIndex)                                         (TRUE != FALSE)
#define BswM_HasRulesOfPCPartitionConfig(partitionIndex)                                            (TRUE != FALSE)
#define BswM_HasSizeOfActionListQueueOfPCPartitionConfig(partitionIndex)                            (TRUE != FALSE)
#define BswM_HasSizeOfActionListsOfPCPartitionConfig(partitionIndex)                                (TRUE != FALSE)
#define BswM_HasSizeOfDeferredRulesOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasSizeOfGenericMappingOfPCPartitionConfig(partitionIndex)                             (TRUE != FALSE)
#define BswM_HasSizeOfGenericStateOfPCPartitionConfig(partitionIndex)                               (TRUE != FALSE)
#define BswM_HasSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasSizeOfInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                        (TRUE != FALSE)
#define BswM_HasSizeOfModeNotificationFctOfPCPartitionConfig(partitionIndex)                        (TRUE != FALSE)
#define BswM_HasSizeOfModeRequestQueueOfPCPartitionConfig(partitionIndex)                           (TRUE != FALSE)
#define BswM_HasSizeOfRuleStatesOfPCPartitionConfig(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasSizeOfRulesIndOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasSizeOfRulesOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasSizeOfSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                    (TRUE != FALSE)
#define BswM_HasSizeOfTimerStateOfPCPartitionConfig(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasSizeOfTimerValueOfPCPartitionConfig(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                          (TRUE != FALSE)
#define BswM_HasTimerStateOfPCPartitionConfig(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasTimerValueOfPCPartitionConfig(partitionIndex)                                       (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCIncrementDataMacros  BswM Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define BswM_IncActionListQueue(Index, partitionIndex)                                              BswM_GetActionListQueue(((Index)), (partitionIndex))++
#define BswM_IncForcedActionListPriority(partitionIndex)                                            BswM_GetForcedActionListPriority(partitionIndex)++
#define BswM_IncGenericState(Index, partitionIndex)                                                 BswM_GetGenericState(((Index)), (partitionIndex))++
#define BswM_IncModeRequestQueue(Index, partitionIndex)                                             BswM_GetModeRequestQueue(((Index)), (partitionIndex))++
#define BswM_IncQueueSemaphore(partitionIndex)                                                      BswM_GetQueueSemaphore(partitionIndex)++
#define BswM_IncRuleStates(Index, partitionIndex)                                                   BswM_GetRuleStates(((Index)), (partitionIndex))++
#define BswM_IncTimerState(Index, partitionIndex)                                                   BswM_GetTimerState(((Index)), (partitionIndex))++
#define BswM_IncTimerValue(Index, partitionIndex)                                                   BswM_GetTimerValue(((Index)), (partitionIndex))++
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCDecrementDataMacros  BswM Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define BswM_DecActionListQueue(Index, partitionIndex)                                              BswM_GetActionListQueue(((Index)), (partitionIndex))--
#define BswM_DecForcedActionListPriority(partitionIndex)                                            BswM_GetForcedActionListPriority(partitionIndex)--
#define BswM_DecGenericState(Index, partitionIndex)                                                 BswM_GetGenericState(((Index)), (partitionIndex))--
#define BswM_DecModeRequestQueue(Index, partitionIndex)                                             BswM_GetModeRequestQueue(((Index)), (partitionIndex))--
#define BswM_DecQueueSemaphore(partitionIndex)                                                      BswM_GetQueueSemaphore(partitionIndex)--
#define BswM_DecRuleStates(Index, partitionIndex)                                                   BswM_GetRuleStates(((Index)), (partitionIndex))--
#define BswM_DecTimerState(Index, partitionIndex)                                                   BswM_GetTimerState(((Index)), (partitionIndex))--
#define BswM_DecTimerValue(Index, partitionIndex)                                                   BswM_GetTimerValue(((Index)), (partitionIndex))--
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


#define BswM_GetPartitionContext() 0u


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/* PRQA S 3449, 3451 EXTERNDECLARATIONS */ /* MD_BSWM_3449, MD_BSWM_3451 */ 
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
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
extern CONST(BswM_ActionListsType, BSWM_CONST) BswM_ActionLists[12];
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
extern CONST(BswM_DeferredRulesType, BSWM_CONST) BswM_DeferredRules[7];
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
extern CONST(BswM_InitGenVarAndInitALType, BSWM_CONST) BswM_InitGenVarAndInitAL[1];
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
extern CONST(BswM_PartitionFunctionType, BSWM_CONST) BswM_ModeNotificationFct[1];
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
extern CONST(BswM_PartitionIdentifiersType, BSWM_CONST) BswM_PartitionIdentifiers[1];
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
  RuleStatesIdx    the index of the 1:1 relation pointing to BswM_RuleStates
  FctPtr           Pointer to the rule function which does the arbitration.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_RulesType, BSWM_CONST) BswM_Rules[10];
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
extern CONST(BswM_RulesIndType, BSWM_CONST) BswM_RulesInd[8];
#define BSWM_STOP_SEC_CONST_8BIT
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
extern CONST(BswM_PartitionFunctionType, BSWM_CONST) BswM_SwcModeRequestUpdateFct[1];
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
extern VAR(BswM_ActionListQueueUType, BSWM_VAR_NOINIT) BswM_ActionListQueue;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(BswM_ForcedActionListPriorityType, BSWM_VAR_NOINIT) BswM_ForcedActionListPriority;
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
extern VAR(BswM_ModeType, BSWM_VAR_NOINIT) BswM_GenericState[1];
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
extern VAR(BswM_InitializedType, BSWM_VAR_NOINIT) BswM_Initialized;
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
extern VAR(BswM_ModeRequestQueueType, BSWM_VAR_NOINIT) BswM_ModeRequestQueue[1];
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
extern VAR(BswM_QueueSemaphoreType, BSWM_VAR_NOINIT) BswM_QueueSemaphore;
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
extern VAR(BswM_QueueWrittenType, BSWM_VAR_NOINIT) BswM_QueueWritten;
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
extern VAR(BswM_RuleStatesUType, BSWM_VAR_NOINIT) BswM_RuleStates;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
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
extern VAR(BswM_TimerStateUType, BSWM_VAR_NOINIT) BswM_TimerState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(BswM_TimerValueUType, BSWM_VAR_NOINIT) BswM_TimerValue;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define BSWM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/* PRQA L:EXTERNDECLARATIONS */


#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (BSWM_USE_INIT_POINTER == STD_ON)
extern  P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_PBCFG) BswM_ConfigPtr;
#endif

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define BswM_IsPreInitialized()                     (BswM_PreInitialized) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define BswM_SetPreInitialized(Value)               (BswM_IsPreInitialized()) = (Value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/* -----------------------------------------------------------------------------
    &&&~ EXTERNAL DECLARATIONS
 ----------------------------------------------------------------------------- */

#define BSWM_START_SEC_CODE
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */






#if (BSWM_FUNCTION_BASED == STD_OFF)
/**********************************************************************************************************************
 *  BswM_Action_ActionListHandler()
 **********************************************************************************************************************/
/*!
 * \brief       Executes an action list.
 * \details     Executes all actions of an action list.
 * \param[in]   handleId  Id of the action list to execute.
 * \param[in]   partitionIdx Index of current partition Context
 * \return      E_OK      Action list was completely executed.
 * \return      E_NOT_OK  Action list was aborted because an action failed.
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
extern FUNC(Std_ReturnType, BSWM_CODE) BswM_Action_ActionListHandler(BswM_HandleType handleId, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if ((BSWM_RULES == STD_ON)  && (BSWM_FUNCTION_BASED == STD_OFF))
/**********************************************************************************************************************
 *  BswM_ArbitrateRule()
 **********************************************************************************************************************/
/*!
 * \brief       Arbitrates a rule.
 * \details     Evaluates the logical expression of the rule and determines the action list to execute.
 * \param[in]   ruleId  Id of the rule to arbitrate
 * \param[in]   partitionIdx  Index of current partition Context
 * \return      ID of action list to execute (BSWM_NO_ACTIONLIST if no action list shall be executed)
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
extern FUNC(BswM_SizeOfActionListsType, BSWM_CODE) BswM_ArbitrateRule(BswM_HandleType ruleId, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if(BSWM_IMMEDIATEUSER == STD_ON)
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
/**********************************************************************************************************************
 *  BswM_ImmediateModeRequest()
 **********************************************************************************************************************/
/*!
 * \brief       Processes an immediate mode request.
 * \details     Queues mode request and starts arbitration of depending rules if no other request is currently active.
 * \param[in]   start   Handle of first mode request.
 * \param[in]   end     Handle of last mode request.
 * \param[in]   sid     Service Id of calling API. Only available if BSWM_DEV_ERROR_REPORT is STD_ON.
 * \param[in]   partitionIdx Index of current partition Context
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
extern FUNC(void, BSWM_CODE) BswM_ImmediateModeRequest(BswM_SizeOfImmediateUserType start, BswM_SizeOfImmediateUserType end, uint8 sid, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
# else
extern FUNC(void, BSWM_CODE) BswM_ImmediateModeRequest(BswM_SizeOfImmediateUserType start, BswM_SizeOfImmediateUserType end, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
# endif
#endif

#define BSWM_STOP_SEC_CODE
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* BSWM_PRIVATE_CFG_H */


