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
 *             File:  Rte_Cdd_UDS.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application header file for SW-C <Cdd_UDS>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_CDD_UDS_H
# define RTE_CDD_UDS_H

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

# include "Rte_Cdd_UDS_Type.h"
# include "Rte_DataHandleType.h"


# define Cdd_UDS_START_SEC_CODE
# include "Cdd_UDS_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_Cdd_UDS_Init Cdd_UDS_Init
#  define RTE_RUNNABLE_Cdd_Uds_Runnable10ms Cdd_Uds_Runnable10ms
#  define RTE_RUNNABLE_DID_0x16F_DataServices_DcmDspData_NetPara_ConditionCheckRead DID_0x16F_DataServices_DcmDspData_NetPara_ConditionCheckRead
#  define RTE_RUNNABLE_DID_0x16F_DataServices_DcmDspData_NetPara_ReadData DID_0x16F_DataServices_DcmDspData_NetPara_ReadData
#  define RTE_RUNNABLE_DID_0x16F_DataServices_DcmDspData_NetPara_WriteData DID_0x16F_DataServices_DcmDspData_NetPara_WriteData
#  define RTE_RUNNABLE_RID_0x250_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_RequestResults RID_0x250_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_RequestResults
#  define RTE_RUNNABLE_RID_0x250_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_Start RID_0x250_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_Start
# endif

FUNC(void, Cdd_UDS_CODE) Cdd_UDS_Init(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */
FUNC(void, Cdd_UDS_CODE) Cdd_Uds_Runnable10ms(void); /* PRQA S 3451, 0786, 3449 */ /* MD_Rte_3451, MD_Rte_0786, MD_Rte_3449 */
FUNC(Std_ReturnType, Cdd_UDS_CODE) DID_0x16F_DataServices_DcmDspData_NetPara_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CDD_UDS_APPL_VAR) ErrorCode); /* PRQA S 0786, 3449, 0624 */ /* MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Cdd_UDS_CODE) DID_0x16F_DataServices_DcmDspData_NetPara_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_CDD_UDS_APPL_VAR) Data); /* PRQA S 0786, 3449, 0624 */ /* MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
# else
FUNC(Std_ReturnType, Cdd_UDS_CODE) DID_0x16F_DataServices_DcmDspData_NetPara_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data8ByteType, AUTOMATIC, RTE_CDD_UDS_APPL_VAR) Data); /* PRQA S 0786, 3449, 0624 */ /* MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Cdd_UDS_CODE) DID_0x16F_DataServices_DcmDspData_NetPara_WriteData(P2CONST(uint8, AUTOMATIC, RTE_CDD_UDS_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CDD_UDS_APPL_VAR) ErrorCode); /* PRQA S 0786, 3449, 0624 */ /* MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
# else
FUNC(Std_ReturnType, Cdd_UDS_CODE) DID_0x16F_DataServices_DcmDspData_NetPara_WriteData(P2CONST(Dcm_Data8ByteType, AUTOMATIC, RTE_CDD_UDS_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CDD_UDS_APPL_VAR) ErrorCode); /* PRQA S 0786, 3449, 0624 */ /* MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
# endif
FUNC(Std_ReturnType, Cdd_UDS_CODE) RID_0x250_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_RequestResults(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CDD_UDS_APPL_VAR) ErrorCode); /* PRQA S 0786, 3449, 0624 */ /* MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */
FUNC(Std_ReturnType, Cdd_UDS_CODE) RID_0x250_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_Start(uint8 TxMode, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CDD_UDS_APPL_VAR) ErrorCode); /* PRQA S 0786, 3449, 0624 */ /* MD_Rte_0786, MD_Rte_3449, MD_Rte_0624 */

# define Cdd_UDS_STOP_SEC_CODE
# include "Cdd_UDS_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_DataServices_DcmDspData_NetPara_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_NetPara_E_NOT_OK (1U)

#  define RTE_E_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_DCM_E_FORCE_RCRRP (12U)

#  define RTE_E_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_DCM_E_PENDING (10U)

#  define RTE_E_RoutineServices_DcmDspRoutine_0x250_SetPhyTxMode_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_CDD_UDS_H */

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
