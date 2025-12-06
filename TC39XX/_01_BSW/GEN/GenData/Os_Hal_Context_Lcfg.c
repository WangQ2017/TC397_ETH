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
 *              File: Os_Hal_Context_Lcfg.c
 *   Generation Time: 2025-09-02 11:14:44
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_HAL_CONTEXT_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Context_Lcfg.h"
#include "Os_Hal_Context.h"

/* Os kernel module dependencies */
#include "OsInt.h"
#include "Os_Core.h"
#include "Os_Hook_Lcfg.h"
#include "Os_Hook.h"
#include "Os_Ioc_Lcfg.h"
#include "Os_Isr_Lcfg.h"
#include "Os_Lcfg.h"
#include "Os_Stack_Lcfg.h"
#include "Os_Task_Lcfg.h"
#include "Os_Task.h"

/* Os hal dependencies */
#include "Os_Hal_Core.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore0_Dyn;

/*! HAL dynamic hook context data: StartupHook_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_StartupHook_OsCore0_Dyn;

/*! HAL dynamic hook context data: ShutdownHook_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ShutdownHook_OsCore0_Dyn;

/*! HAL dynamic hook context data: ErrorHook_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ErrorHook_OsCore0_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level2_Dyn;

/*! HAL dynamic task context data: Default_Init_Task */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Trusted */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Trusted_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore0_Dyn;

/*! HAL dynamic task context data: OsTask_Asw_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Asw_OsCore0_Dyn;

/*! HAL dynamic task context data: OsTask_Bsw_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Bsw_OsCore0_Dyn;

/*! HAL dynamic task context data: OsTask_Init_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Init_OsCore0_Dyn;

/*! HAL dynamic task context data: OsTask_lock_2ms */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_lock_2ms_Dyn;

/*! HAL exception context data: OsCore0 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_ExceptionContext;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore1_Dyn;

/*! HAL dynamic hook context data: StartupHook_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_StartupHook_OsCore1_Dyn;

/*! HAL dynamic hook context data: ShutdownHook_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ShutdownHook_OsCore1_Dyn;

/*! HAL dynamic hook context data: ErrorHook_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ErrorHook_OsCore1_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level2_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core1_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core1_Trusted */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core1_Trusted_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore1_Dyn;

/*! HAL dynamic task context data: OsTask_Asw_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Asw_OsCore1_Dyn;

/*! HAL dynamic task context data: OsTask_Bsw_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Bsw_OsCore1_Dyn;

/*! HAL dynamic task context data: OsTask_Init_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Init_OsCore1_Dyn;

/*! HAL dynamic task context data: OsTask_window_2ms */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_window_2ms_Dyn;

/*! HAL exception context data: OsCore1 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_ExceptionContext;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore2_Dyn;

/*! HAL dynamic hook context data: StartupHook_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_StartupHook_OsCore2_Dyn;

/*! HAL dynamic hook context data: ShutdownHook_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ShutdownHook_OsCore2_Dyn;

/*! HAL dynamic hook context data: ErrorHook_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ErrorHook_OsCore2_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_Isr_Level2_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core2_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core2_Trusted */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core2_Trusted_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore2_Dyn;

/*! HAL dynamic task context data: OsTask_Asw_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Asw_OsCore2_Dyn;

/*! HAL dynamic task context data: OsTask_Bsw_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Bsw_OsCore2_Dyn;

/*! HAL dynamic task context data: OsTask_Init_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Init_OsCore2_Dyn;

/*! HAL exception context data: OsCore2 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_ExceptionContext;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore3_Dyn;

/*! HAL dynamic hook context data: StartupHook_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_StartupHook_OsCore3_Dyn;

/*! HAL dynamic hook context data: ShutdownHook_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ShutdownHook_OsCore3_Dyn;

/*! HAL dynamic hook context data: ErrorHook_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ErrorHook_OsCore3_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore3_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore3_Isr_Level2_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core3_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core3_Trusted */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core3_Trusted_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore3_Dyn;

/*! HAL dynamic task context data: OsTask_Asw_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Asw_OsCore3_Dyn;

/*! HAL dynamic task context data: OsTask_Bsw_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Bsw_OsCore3_Dyn;

/*! HAL dynamic task context data: OsTask_Init_OsCore3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Init_OsCore3_Dyn;

/*! HAL exception context data: OsCore3 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore3_ExceptionContext;

#define OS_STOP_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore4_Dyn;

/*! HAL dynamic hook context data: StartupHook_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_StartupHook_OsCore4_Dyn;

/*! HAL dynamic hook context data: ShutdownHook_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ShutdownHook_OsCore4_Dyn;

/*! HAL dynamic hook context data: ErrorHook_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ErrorHook_OsCore4_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore4_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore4_Isr_Level2_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core4_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core4_Trusted */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core4_Trusted_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore4_Dyn;

/*! HAL dynamic task context data: OsTask_Asw_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Asw_OsCore4_Dyn;

/*! HAL dynamic task context data: OsTask_Bsw_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Bsw_OsCore4_Dyn;

/*! HAL dynamic task context data: OsTask_Init_OsCore4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Init_OsCore4_Dyn;

/*! HAL exception context data: OsCore4 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore4_ExceptionContext;

#define OS_STOP_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore5_Dyn;

/*! HAL dynamic hook context data: StartupHook_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_StartupHook_OsCore5_Dyn;

/*! HAL dynamic hook context data: ShutdownHook_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ShutdownHook_OsCore5_Dyn;

/*! HAL dynamic hook context data: ErrorHook_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_ErrorHook_OsCore5_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore5_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore5_Isr_Level2_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core6 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core6_Dyn;

/*! HAL dynamic task context data: Default_Init_Task_Core6_Trusted */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Default_Init_Task_Core6_Trusted_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore5_Dyn;

/*! HAL dynamic task context data: OsTask_Asw_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Asw_OsCore5_Dyn;

/*! HAL dynamic task context data: OsTask_Bsw_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Bsw_OsCore5_Dyn;

/*! HAL dynamic task context data: OsTask_Init_OsCore5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsTask_Init_OsCore5_Dyn;

/*! HAL exception context data: OsCore5 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore5_ExceptionContext;

#define OS_STOP_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Init_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: StartupHook_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_StartupHook_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Startup_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Startup_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperCallback,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ShutdownHook_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ShutdownHook_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Shutdown_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Shutdown_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ErrorHook_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ErrorHook_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Error_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Error_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio55_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio55_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Trusted */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Trusted =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio50_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio50_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Trusted,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Asw_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Asw_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsTask_Asw_OsCore0_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsTask_Asw_OsCore0_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Asw_OsCore0,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Bsw_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Bsw_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio30_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio30_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Bsw_OsCore0,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Init_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Init_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio48_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio48_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Init_OsCore0,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_lock_2ms */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_lock_2ms =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio40_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio40_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_lock_2ms,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore0_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore0_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Kernel_Dyn)+1)  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Init_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: StartupHook_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_StartupHook_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Startup_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Startup_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperCallback,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ShutdownHook_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ShutdownHook_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Shutdown_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Shutdown_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ErrorHook_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ErrorHook_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Error_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Error_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio54_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio54_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core1,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core1_Trusted */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core1_Trusted =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio49_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio49_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core1_Trusted,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Asw_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Asw_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio14_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio14_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Asw_OsCore1,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Bsw_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Bsw_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio34_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio34_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Bsw_OsCore1,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Init_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Init_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio48_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio48_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Init_OsCore1,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_window_2ms */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_window_2ms =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio41_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio41_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_window_2ms,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore1_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore1_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Kernel_Dyn)+1)  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Init_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: StartupHook_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_StartupHook_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Startup_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Startup_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperCallback,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ShutdownHook_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ShutdownHook_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Shutdown_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Shutdown_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ErrorHook_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ErrorHook_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Error_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Error_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio53_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio53_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core2,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core2_Trusted */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core2_Trusted =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio49_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio49_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core2_Trusted,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Asw_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Asw_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio13_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio13_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Asw_OsCore2,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Bsw_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Bsw_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio33_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio33_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Bsw_OsCore2,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Init_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Init_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio48_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio48_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Init_OsCore2,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore2_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore2_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Kernel_Dyn)+1)  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Init_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: StartupHook_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_StartupHook_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Startup_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Startup_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperCallback,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ShutdownHook_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ShutdownHook_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Shutdown_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Shutdown_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ErrorHook_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ErrorHook_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Error_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Error_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Task_Prio52_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Task_Prio52_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core3,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core3_Trusted */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core3_Trusted =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Task_Prio49_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Task_Prio49_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core3_Trusted,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Asw_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Asw_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Task_Prio12_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Task_Prio12_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Asw_OsCore3,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Bsw_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Bsw_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Task_Prio32_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Task_Prio32_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Bsw_OsCore3,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Init_OsCore3 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Init_OsCore3 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Task_Prio48_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Task_Prio48_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Init_OsCore3,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore3_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore3_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore3_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore3_Kernel_Dyn)+1)  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
};

#define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Init_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: StartupHook_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_StartupHook_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Startup_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Startup_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperCallback,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ShutdownHook_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ShutdownHook_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Shutdown_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Shutdown_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ErrorHook_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ErrorHook_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Error_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Error_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Task_Prio51_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Task_Prio51_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core4,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core4_Trusted */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core4_Trusted =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Task_Prio49_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Task_Prio49_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core4_Trusted,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Asw_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Asw_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Task_Prio11_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Task_Prio11_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Asw_OsCore4,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Bsw_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Bsw_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Task_Prio31_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Task_Prio31_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Bsw_OsCore4,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Init_OsCore4 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Init_OsCore4 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Task_Prio48_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Task_Prio48_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Init_OsCore4,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore4_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore4_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore4_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore4_Kernel_Dyn)+1)  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
};

#define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Init_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: StartupHook_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_StartupHook_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Startup_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Startup_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperCallback,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ShutdownHook_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ShutdownHook_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Shutdown_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Shutdown_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL hook context configuration data: ErrorHook_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_ErrorHook_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Error_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Error_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperStatusHook,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Isr_Core_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)255<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core6 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core6 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Task_Prio50_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Task_Prio50_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core6,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Default_Init_Task_Core6_Trusted */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Default_Init_Task_Core6_Trusted =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Task_Prio49_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Task_Prio49_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Default_Init_Task_Core6_Trusted,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Asw_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Asw_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Task_Prio10_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Task_Prio10_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Asw_OsCore5,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Bsw_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Bsw_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Task_Prio30_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Task_Prio30_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Bsw_OsCore5,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: OsTask_Init_OsCore5 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_OsTask_Init_OsCore5 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Task_Prio48_Dyn)+1),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Task_Prio48_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK,
  /* .ProtectionSet    = */ (uint32)OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_OsTask_Init_OsCore5,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305 */ /* MD_Os_Hal_Rule11.1_0305 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore5_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore5_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore5_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore5_Kernel_Dyn)+1)  /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
};

#define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Object reference table for HAL exception context. */
CONSTP2VAR(Os_ExceptionContextType, AUTOMATIC, OS_CONST)
  OsCfg_Hal_Context_ExceptionContextRef[OS_CFG_COREPHYSICALID_COUNT + 1u] =
{
  &OsCfg_Hal_Context_OsCore0_ExceptionContext,
  &OsCfg_Hal_Context_OsCore1_ExceptionContext,
  &OsCfg_Hal_Context_OsCore2_ExceptionContext,
  &OsCfg_Hal_Context_OsCore3_ExceptionContext,
  &OsCfg_Hal_Context_OsCore4_ExceptionContext,
  NULL_PTR,
  &OsCfg_Hal_Context_OsCore5_ExceptionContext,
  NULL_PTR
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Context_Lcfg.c
 *********************************************************************************************************************/
