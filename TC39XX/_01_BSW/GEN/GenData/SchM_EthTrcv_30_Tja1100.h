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
 *             File:  SchM_EthTrcv_30_Tja1100.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Header of BSW Scheduler for BSW Module <EthTrcv_30_Tja1100>
 *********************************************************************************************************************/
#ifndef SCHM_ETHTRCV_30_TJA1100_H
# define SCHM_ETHTRCV_30_TJA1100_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_EthTrcv_30_Tja1100_Type.h"

# include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_Dir1.1, MD_Rte_Os */

# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_MainFunction(void); /* PRQA S 3451, 3449 */ /* MD_Rte_3451, MD_Rte_3449 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_MainFunctionLinkHandling(void); /* PRQA S 3451, 3449 */ /* MD_Rte_3451, MD_Rte_3449 */

# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define SchM_Enter_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */


# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_ETHTRCV_30_TJA1100_H */

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

   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
