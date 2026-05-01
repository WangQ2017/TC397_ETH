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
 *             File:  SchM_Fls_17_Dmu.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Header of BSW Scheduler for BSW Module <Fls_17_Dmu>
 *********************************************************************************************************************/
#ifndef SCHM_FLS_17_DMU_H
# define SCHM_FLS_17_DMU_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Fls_17_Dmu_Type.h"

# define FLS_17_DMU_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, FLS_17_DMU_CODE) Fls_17_Dmu_MainFunction(void); /* PRQA S 3451, 3449 */ /* MD_Rte_3451, MD_Rte_3449 */

# define FLS_17_DMU_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, RTE_CODE) SchM_Enter_Fls_17_Dmu_Erase(void);
FUNC(void, RTE_CODE) SchM_Exit_Fls_17_Dmu_Erase(void);
FUNC(void, RTE_CODE) SchM_Enter_Fls_17_Dmu_Init(void);
FUNC(void, RTE_CODE) SchM_Exit_Fls_17_Dmu_Init(void);
FUNC(void, RTE_CODE) SchM_Enter_Fls_17_Dmu_Main(void);
FUNC(void, RTE_CODE) SchM_Exit_Fls_17_Dmu_Main(void);
FUNC(void, RTE_CODE) SchM_Enter_Fls_17_Dmu_ResumeErase(void);
FUNC(void, RTE_CODE) SchM_Exit_Fls_17_Dmu_ResumeErase(void);
FUNC(void, RTE_CODE) SchM_Enter_Fls_17_Dmu_UserContentCount(void);
FUNC(void, RTE_CODE) SchM_Exit_Fls_17_Dmu_UserContentCount(void);
FUNC(void, RTE_CODE) SchM_Enter_Fls_17_Dmu_Write(void);
FUNC(void, RTE_CODE) SchM_Exit_Fls_17_Dmu_Write(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_FLS_17_DMU_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3449:  MISRA rule: Rule8.5
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3451:  MISRA rule: Rule8.5
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
