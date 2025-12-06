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
 *             File:  Rte_Cdd_Nm.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application header file for SW-C <Cdd_Nm>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_CDD_NM_H
# define RTE_CDD_NM_H

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

# include "Rte_Cdd_Nm_Type.h"
# include "Rte_DataHandleType.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * extern declaration of RTE buffers for optimized macro implementation
 *********************************************************************************************************************/
#  define RTE_START_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(BswM_ESH_RunRequest, RTE_VAR_INIT) Rte_Cdd_nm_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode;

#  define RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_BswM_SRI_BswM_MSI_ESH_Mode_BswM_MDGP_ESH_Mode_requestedMode Rte_Write_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_Mode_BswM_MDGP_ESH_Mode_requestedMode
#  define Rte_Write_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_Mode_BswM_MDGP_ESH_Mode_requestedMode(data) (RTE_E_OK) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Rte_Write_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode Rte_Write_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode
#  define Rte_Write_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode(data) (Rte_Cdd_nm_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


# endif /* !defined(RTE_CORE) */


# define Cdd_Nm_START_SEC_CODE
# include "Cdd_Nm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_Cdd_Nm_Init Cdd_Nm_Init
#  define RTE_RUNNABLE_Cdd_Nm_Runnable10ms Cdd_Nm_Runnable10ms
# endif

FUNC(void, Cdd_Nm_CODE) Cdd_Nm_Init(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */
FUNC(void, Cdd_Nm_CODE) Cdd_Nm_Runnable10ms(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */

# define Cdd_Nm_STOP_SEC_CODE
# include "Cdd_Nm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_CDD_NM_H */

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
