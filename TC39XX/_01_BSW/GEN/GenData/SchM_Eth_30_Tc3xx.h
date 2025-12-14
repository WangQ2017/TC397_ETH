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
 *             File:  SchM_Eth_30_Tc3xx.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Header of BSW Scheduler for BSW Module <Eth_30_Tc3xx>
 *********************************************************************************************************************/
#ifndef SCHM_ETH_30_TC3XX_H
# define SCHM_ETH_30_TC3XX_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Eth_30_Tc3xx_Type.h"

# include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_Dir1.1, MD_Rte_Os */

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_MainFunction(void); /* PRQA S 3451, 3449 */ /* MD_Rte_3451, MD_Rte_3449 */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define SchM_Enter_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DATA() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DATA() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DISABLE_MAC() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DISABLE_MAC() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_MII() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_MII() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */


# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_ETH_30_TC3XX_H */

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
