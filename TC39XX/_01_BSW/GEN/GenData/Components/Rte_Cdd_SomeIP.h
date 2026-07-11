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
 *             File:  Rte_Cdd_SomeIP.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application header file for SW-C <Cdd_SomeIP>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_CDD_SOMEIP_H
# define RTE_CDD_SOMEIP_H

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

# include "Rte_Cdd_SomeIP_Type.h"
# include "Rte_DataHandleType.h"


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdClientServiceState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdClientServiceState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdClientServiceState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdEventHandlerState_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdEventHandlerState_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState(void);
FUNC(uint8, RTE_CODE) Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdEventHandlerState_0xC3C2_EcuState_BswM_MDGP_SDC_SdEventHandlerState(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_BswM_MSI_SDC_SdClientServiceState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdClientServiceState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState
#  define Rte_Mode_BswM_MSI_SDC_SdClientServiceState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdClientServiceState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState
#  define Rte_Mode_BswM_MSI_SDC_SdClientServiceState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdClientServiceState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState
#  define Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState
#  define Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState
#  define Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState
#  define Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdEventHandlerState_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState
#  define Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdEventHandlerState_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState
#  define Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C2_EcuState_BswM_MDGP_SDC_SdEventHandlerState Rte_Mode_Cdd_SomeIP_BswM_MSI_SDC_SdEventHandlerState_0xC3C2_EcuState_BswM_MDGP_SDC_SdEventHandlerState


# endif /* !defined(RTE_CORE) */


# define Cdd_SomeIP_START_SEC_CODE
# include "Cdd_SomeIP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_Cdd_SomeIP_Init Cdd_SomeIP_Init
#  define RTE_RUNNABLE_Cdd_SomeIP_Runnable_100ms Cdd_SomeIP_Runnable_100ms
# endif

FUNC(void, Cdd_SomeIP_CODE) Cdd_SomeIP_Init(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */
FUNC(void, Cdd_SomeIP_CODE) Cdd_SomeIP_Runnable_100ms(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */

# define Cdd_SomeIP_STOP_SEC_CODE
# include "Cdd_SomeIP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_CDD_SOMEIP_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
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
