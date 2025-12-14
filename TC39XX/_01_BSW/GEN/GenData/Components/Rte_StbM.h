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
 *             File:  Rte_StbM.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application header file for SW-C <StbM>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_STBM_H
# define RTE_STBM_H

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

# include "Rte_StbM_Type.h"
# include "Rte_DataHandleType.h"


# define StbM_START_SEC_CODE
# include "StbM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_GetCurrentTime StbM_GetCurrentTime
#  define RTE_RUNNABLE_GetRateDeviation StbM_GetRateDeviation
#  define RTE_RUNNABLE_GetTimeBaseStatus StbM_GetTimeBaseStatus
#  define RTE_RUNNABLE_GetTimeLeap StbM_GetTimeLeap
#  define RTE_RUNNABLE_StbM_MainFunction StbM_MainFunction
# endif

FUNC(Std_ReturnType, StbM_CODE) StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType parg0, P2VAR(StbM_TimeStampType, AUTOMATIC, RTE_STBM_APPL_VAR) timeStampPtr, P2VAR(StbM_UserDataType, AUTOMATIC, RTE_STBM_APPL_VAR) userDataPtr); /* PRQA S 1330, 3451, 0786, 3449, 0624 */ /* MD_Rte_1330, MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, StbM_CODE) StbM_GetRateDeviation(StbM_SynchronizedTimeBaseType parg0, P2VAR(StbM_RateDeviationType, AUTOMATIC, RTE_STBM_APPL_VAR) rateDeviation); /* PRQA S 1330, 3451, 0786, 3449, 0624 */ /* MD_Rte_1330, MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, StbM_CODE) StbM_GetTimeBaseStatus(StbM_SynchronizedTimeBaseType parg0, P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, RTE_STBM_APPL_VAR) syncTimeBaseStatus, P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, RTE_STBM_APPL_VAR) offsetTimeBaseStatus); /* PRQA S 1330, 3451, 0786, 3449, 0624 */ /* MD_Rte_1330, MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, StbM_CODE) StbM_GetTimeLeap(StbM_SynchronizedTimeBaseType parg0, P2VAR(StbM_TimeDiffType, AUTOMATIC, RTE_STBM_APPL_VAR) timeJump); /* PRQA S 1330, 3451, 0786, 3449, 0624 */ /* MD_Rte_1330, MD_Rte_3451, MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(void, StbM_CODE) StbM_MainFunction(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */

# define StbM_STOP_SEC_CODE
# include "StbM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_GlobalTime_Slave_StbMSynchronizedTimeBase_E_NOT_OK (1U)

#  define RTE_E_GlobalTime_Slave_StbMSynchronizedTimeBase_E_OK (0U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_STBM_H */

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

   MD_Rte_1330:  MISRA rule: Rule8.3
     Reason:     The RTE Generator uses default names for parameter identifiers of port defined arguments of service modules.
                 Therefore the parameter identifiers in the function declaration differs from those of the implementation of the BSW module.
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
