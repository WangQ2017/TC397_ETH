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
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_XSignal_Lcfg.h
 *   Generation Time: 2025-08-29 16:36:38
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef OS_XSIGNAL_LCFG_H
# define OS_XSIGNAL_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_XSignal_Types.h"

/* Os kernel module dependencies */
# include "Os_Error_Types.h"
# include "OsInt.h"

/* Os hal dependencies */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Cross-core function identifiers. */
typedef enum
{
  /* USED */
  XSigFunctionIdx_ActivateTask = 0,
  XSigFunctionIdx_CancelAlarm = 1,
  XSigFunctionIdx_ControlIdle = 2,
  XSigFunctionIdx_GetAlarm = 3,
  XSigFunctionIdx_GetApplicationState = 4,
  XSigFunctionIdx_GetCounterValue = 5,
  XSigFunctionIdx_GetErrorHookStackUsage = 6,
  XSigFunctionIdx_GetEvent = 7,
  XSigFunctionIdx_GetISRStackUsage = 8,
  XSigFunctionIdx_GetKernelStackUsage = 9,
  XSigFunctionIdx_GetNonTrustedFunctionStackUsage = 10,
  XSigFunctionIdx_GetProtectionHookStackUsage = 11,
  XSigFunctionIdx_GetScheduleTableStatus = 12,
  XSigFunctionIdx_GetShutdownHookStackUsage = 13,
  XSigFunctionIdx_GetStartupHookStackUsage = 14,
  XSigFunctionIdx_GetTaskStackUsage = 15,
  XSigFunctionIdx_GetTaskState = 16,
  XSigFunctionIdx_HookCallCallback = 17,
  XSigFunctionIdx_NextScheduleTable = 18,
  XSigFunctionIdx_SetAbsAlarm = 19,
  XSigFunctionIdx_SetEvent = 20,
  XSigFunctionIdx_SetRelAlarm = 21,
  XSigFunctionIdx_ShutdownAllCores = 22,
  XSigFunctionIdx_StartScheduleTableAbs = 23,
  XSigFunctionIdx_StartScheduleTableRel = 24,
  XSigFunctionIdx_StopScheduleTable = 25,
  XSigFunctionIdx_TerminateApplication = 26,
  OS_XSIGFUNCTIONIDX_USEDCOUNT = 27,
  /* UNUSED */
  OS_XSIGFUNCTIONIDX_COUNT = 27
} Os_XSigFunctionIdx;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* X-Signal configuration data: OsCore0 */
extern CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore0_FuncTable;
extern CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore0_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE0_PORTS + 1u];
extern CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore0;

# define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* X-Signal configuration data: OsCore1 */
extern CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore1_FuncTable;
extern CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore1_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE1_PORTS + 1u];
extern CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore1;

# define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* X-Signal configuration data: OsCore2 */
extern CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore2_FuncTable;
extern CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore2_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE2_PORTS + 1u];
extern CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore2;

# define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE3_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* X-Signal configuration data: OsCore3 */
extern CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore3_FuncTable;
extern CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore3_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE3_PORTS + 1u];
extern CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore3;

# define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE4_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* X-Signal configuration data: OsCore4 */
extern CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore4_FuncTable;
extern CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore4_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE4_PORTS + 1u];
extern CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore4;

# define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE5_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* X-Signal configuration data: OsCore5 */
extern CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore5_FuncTable;
extern CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore5_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE5_PORTS + 1u];
extern CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore5;

# define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! X-Signal used services map. */
extern CONST(OSServiceIdType, OS_CONST) OsCfg_XSig_ServiceMap[OS_XSIGFUNCTIONIDX_COUNT + 1u];                           /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */

# define OS_STOP_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_XSIGNAL_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_XSignal_Lcfg.h
 *********************************************************************************************************************/
