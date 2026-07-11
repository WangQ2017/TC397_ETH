/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_BswM.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application header file for SW-C <BswM>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_BSWM_H
# define RTE_BSWM_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
#  ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#   define RTE_PTR2ARRAYBASETYPE_PASSING
#  endif
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_BswM_Type.h"
# include "Rte_DataHandleType.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_Request_ESH_PostRunRequest_0_requestedMode (0U)
#  define Rte_InitValue_Request_ESH_PostRunRequest_1_requestedMode (0U)
#  define Rte_InitValue_Request_ESH_RunRequest_0_requestedMode (0U)
#  define Rte_InitValue_Request_ESH_RunRequest_1_requestedMode (0U)
#  define Rte_InitValue_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_requestedMode (1U)
#  define Rte_InitValue_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode (1U)
#  define Rte_InitValue_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode (1U)
#  define Rte_InitValue_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode (1U)
#  define Rte_InitValue_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_requestedMode (0U)
#  define Rte_InitValue_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode (1U)
#  define Rte_InitValue_Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode (1U)
#  define Rte_InitValue_Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode (1U)
#  define Rte_InitValue_Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode (1U)
# endif


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_PostRunRequest_0_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_PostRunRequest_1_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_RunRequest_0_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_RunRequest_1_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_requestedMode(P2VAR(BswM_SDC_SdClientServiceRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode(P2VAR(BswM_SDC_SdConsumedEventGroupRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode(P2VAR(BswM_SDC_SdClientServiceRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode(P2VAR(BswM_SDC_SdConsumedEventGroupRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_requestedMode(P2VAR(BswM_SDC_SdClientServiceRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode(P2VAR(BswM_SDC_SdConsumedEventGroupRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode(P2VAR(BswM_SDC_SdServerServiceRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode(P2VAR(BswM_SDC_SdServerServiceRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode(P2VAR(BswM_SDC_SdServerServiceRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data); /* PRQA S 3451, 0786, 3449, 0624 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(BswM_ESH_Mode, RTE_CODE) Rte_Mode_BswM_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode(BswM_ESH_Mode nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState(BswM_SDC_SdClientServiceState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState(BswM_SDC_SdConsumedEventGroupState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState(BswM_SDC_SdClientServiceState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState(BswM_SDC_SdConsumedEventGroupState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState(BswM_SDC_SdClientServiceState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState(BswM_SDC_SdConsumedEventGroupState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState(BswM_SDC_SdEventHandlerState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState(BswM_SDC_SdEventHandlerState nextMode);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_SDC_Mode_S_SdServerService_0xC3C2_EcuState_EH_SdEventHandler_0xC3C2_EcuState_BswM_MDGP_SDC_SdEventHandlerState(BswM_SDC_SdEventHandlerState nextMode);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_Request_ESH_PostRunRequest_0_requestedMode Rte_Read_BswM_Request_ESH_PostRunRequest_0_requestedMode
#  define Rte_Read_Request_ESH_PostRunRequest_1_requestedMode Rte_Read_BswM_Request_ESH_PostRunRequest_1_requestedMode
#  define Rte_Read_Request_ESH_RunRequest_0_requestedMode Rte_Read_BswM_Request_ESH_RunRequest_0_requestedMode
#  define Rte_Read_Request_ESH_RunRequest_1_requestedMode Rte_Read_BswM_Request_ESH_RunRequest_1_requestedMode
#  define Rte_Read_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_requestedMode Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_requestedMode
#  define Rte_Read_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_requestedMode
#  define Rte_Read_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_requestedMode
#  define Rte_Read_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_requestedMode
#  define Rte_Read_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_requestedMode Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_requestedMode
#  define Rte_Read_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode Rte_Read_BswM_Request_SDC_C_SdClientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_requestedMode
#  define Rte_Read_Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode Rte_Read_BswM_Request_SDC_S_SdServerService_0xC3C0_FaultInfo_requestedMode
#  define Rte_Read_Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode Rte_Read_BswM_Request_SDC_S_SdServerService_0xC3C1_SenState_requestedMode
#  define Rte_Read_Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode Rte_Read_BswM_Request_SDC_S_SdServerService_0xC3C2_EcuState_requestedMode


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode Rte_Mode_BswM_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode


/**********************************************************************************************************************
 * Rte_Switch_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Switch_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode Rte_Switch_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode
#  define Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState
#  define Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CB_VechicleSpeed_CEG_SdConsumedEventGroup_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState
#  define Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState
#  define Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CC_VechicleStatus_CEG_SdConsumedEventGroup_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState
#  define Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState
#  define Rte_Switch_Switch_SDC_Mode_C_SdClientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState Rte_Switch_BswM_Switch_SDC_Mode_C_SdClientService_0xC3CD_VechicleInfo_CEG_SdConsumedEventGroup_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState
#  define Rte_Switch_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState Rte_Switch_BswM_Switch_SDC_Mode_S_SdServerService_0xC3C0_FaultInfo_EH_SdEventHandler_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState
#  define Rte_Switch_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState Rte_Switch_BswM_Switch_SDC_Mode_S_SdServerService_0xC3C1_SenState_EH_SdEventHandler_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState
#  define Rte_Switch_Switch_SDC_Mode_S_SdServerService_0xC3C2_EcuState_EH_SdEventHandler_0xC3C2_EcuState_BswM_MDGP_SDC_SdEventHandlerState Rte_Switch_BswM_Switch_SDC_Mode_S_SdServerService_0xC3C2_EcuState_EH_SdEventHandler_0xC3C2_EcuState_BswM_MDGP_SDC_SdEventHandlerState


# endif /* !defined(RTE_CORE) */


# define BswM_START_SEC_CODE
# include "BswM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_BswM_MainFunction BswM_MainFunction
# endif

FUNC(void, BswM_CODE) BswM_MainFunction(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */

# define BswM_STOP_SEC_CODE
# include "BswM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_BSWM_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0624:  MISRA rule: Rule8.3
     Reason:     This MISRA violation is a consequence from the RTE requirements [SWS_Rte_01007] [SWS_Rte_01150].
                 The typedefs are never used in the same context.
     Risk:       No functional risk. Only a cast to uint8* is performed.
     Prevention: Not required.

   MD_Rte_0786:  MISRA rule: Rule5.5
     Reason:     Same macro and idintifier names in first 63 characters are required to meet AUTOSAR spec.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3449:  MISRA rule: Rule8.5
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3451:  MISRA rule: Rule8.5
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
