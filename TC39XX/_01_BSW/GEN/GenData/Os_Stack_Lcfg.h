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
 *              File: Os_Stack_Lcfg.h
 *   Generation Time: 2025-12-20 10:43:27
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef OS_STACK_LCFG_H
# define OS_STACK_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Stack_Cfg.h"
# include "Os_Stack_Types.h"

/* Os kernel module dependencies */
# include "Os_Lcfg.h"

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

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core error stack: OsCore0_Error */
/* User: [ErrorHook_OsCore0, OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Error_Dyn, OS_CFG_SIZE_OSCORE0_ERROR_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core init stack: OsCore0_Init */
/* User: [OsCore0, Os_CoreInitHook_OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Init_Dyn, OS_CFG_SIZE_OSCORE0_INIT_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ISR core global stack: OsCore0_Isr_Core */
/* User: [CounterIsr_SystemTimer_OsCore0, EthIsr_EthCtrlConfig_MAIN_EthInterruptServiceRoutine, XSignalIsr_OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE0_ISR_CORE_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core kernel stack: OsCore0_Kernel */
/* User: [OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Kernel_Dyn, OS_CFG_SIZE_OSCORE0_KERNEL_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core shutdown stack: OsCore0_Shutdown */
/* User: [OsCore0, ShutdownHook_OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Shutdown_Dyn, OS_CFG_SIZE_OSCORE0_SHUTDOWN_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core startup stack: OsCore0_Startup */
/* User: [OsCore0, StartupHook_OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Startup_Dyn, OS_CFG_SIZE_OSCORE0_STARTUP_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_TASK_PRIO20_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore0_Task_Prio20 */
/* User: [OsTask_Bsw_20ms_Core0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio20_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO20_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO20_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_TASK_PRIO40_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore0_Task_Prio40 */
/* User: [OsTask_Bsw_5ms_Core0, OsTask_lock_2ms] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio40_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO40_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO40_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore0_Task_Prio4294967295 */
/* User: [IdleTask_OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO4294967295_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore0_Task_Prio48 */
/* User: [OsTask_Init_OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio48_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO48_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_TASK_PRIO50_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore0_Task_Prio50 */
/* User: [Default_Init_Task_Trusted, OsTask_Bsw_1ms_Core0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio50_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO50_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO50_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE0_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore0_Task_Prio55 */
/* User: [Default_Init_Task] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio55_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO55_STACK);

# define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core error stack: OsCore1_Error */
/* User: [ErrorHook_OsCore1, OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Error_Dyn, OS_CFG_SIZE_OSCORE1_ERROR_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core init stack: OsCore1_Init */
/* User: [OsCore1, Os_CoreInitHook_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Init_Dyn, OS_CFG_SIZE_OSCORE1_INIT_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ISR core global stack: OsCore1_Isr_Core */
/* User: [CounterIsr_SystemTimer_OsCore1, XSignalIsr_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE1_ISR_CORE_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core kernel stack: OsCore1_Kernel */
/* User: [OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Kernel_Dyn, OS_CFG_SIZE_OSCORE1_KERNEL_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core shutdown stack: OsCore1_Shutdown */
/* User: [OsCore1, ShutdownHook_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Shutdown_Dyn, OS_CFG_SIZE_OSCORE1_SHUTDOWN_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core startup stack: OsCore1_Startup */
/* User: [OsCore1, StartupHook_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Startup_Dyn, OS_CFG_SIZE_OSCORE1_STARTUP_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_TASK_PRIO14_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore1_Task_Prio14 */
/* User: [OsTask_Asw_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio14_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO14_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO14_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_TASK_PRIO34_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore1_Task_Prio34 */
/* User: [OsTask_Bsw_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio34_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO34_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO34_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_TASK_PRIO41_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore1_Task_Prio41 */
/* User: [OsTask_window_2ms] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio41_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO41_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO41_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore1_Task_Prio4294967295 */
/* User: [IdleTask_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO4294967295_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore1_Task_Prio48 */
/* User: [OsTask_Init_OsCore1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio48_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO48_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore1_Task_Prio49 */
/* User: [Default_Init_Task_Core1_Trusted] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio49_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO49_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore1_Task_Prio54 */
/* User: [Default_Init_Task_Core1] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio54_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO54_STACK);

# define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core error stack: OsCore2_Error */
/* User: [ErrorHook_OsCore2, OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Error_Dyn, OS_CFG_SIZE_OSCORE2_ERROR_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core init stack: OsCore2_Init */
/* User: [OsCore2, Os_CoreInitHook_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Init_Dyn, OS_CFG_SIZE_OSCORE2_INIT_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ISR core global stack: OsCore2_Isr_Core */
/* User: [CounterIsr_SystemTimer_OsCore2, XSignalIsr_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE2_ISR_CORE_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core kernel stack: OsCore2_Kernel */
/* User: [OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Kernel_Dyn, OS_CFG_SIZE_OSCORE2_KERNEL_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core shutdown stack: OsCore2_Shutdown */
/* User: [OsCore2, ShutdownHook_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Shutdown_Dyn, OS_CFG_SIZE_OSCORE2_SHUTDOWN_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core startup stack: OsCore2_Startup */
/* User: [OsCore2, StartupHook_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Startup_Dyn, OS_CFG_SIZE_OSCORE2_STARTUP_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore2_Task_Prio13 */
/* User: [OsTask_Asw_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio13_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO13_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore2_Task_Prio33 */
/* User: [OsTask_Bsw_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio33_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO33_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore2_Task_Prio4294967295 */
/* User: [IdleTask_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO4294967295_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore2_Task_Prio48 */
/* User: [OsTask_Init_OsCore2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio48_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO48_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore2_Task_Prio49 */
/* User: [Default_Init_Task_Core2_Trusted] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio49_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO49_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore2_Task_Prio53 */
/* User: [Default_Init_Task_Core2] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio53_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO53_STACK);

# define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core error stack: OsCore3_Error */
/* User: [ErrorHook_OsCore3, OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Error_Dyn, OS_CFG_SIZE_OSCORE3_ERROR_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core init stack: OsCore3_Init */
/* User: [OsCore3, Os_CoreInitHook_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Init_Dyn, OS_CFG_SIZE_OSCORE3_INIT_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ISR core global stack: OsCore3_Isr_Core */
/* User: [CounterIsr_SystemTimer_OsCore3, XSignalIsr_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE3_ISR_CORE_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core kernel stack: OsCore3_Kernel */
/* User: [OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Kernel_Dyn, OS_CFG_SIZE_OSCORE3_KERNEL_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core shutdown stack: OsCore3_Shutdown */
/* User: [OsCore3, ShutdownHook_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Shutdown_Dyn, OS_CFG_SIZE_OSCORE3_SHUTDOWN_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core startup stack: OsCore3_Startup */
/* User: [OsCore3, StartupHook_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Startup_Dyn, OS_CFG_SIZE_OSCORE3_STARTUP_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_TASK_PRIO12_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore3_Task_Prio12 */
/* User: [OsTask_Asw_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Task_Prio12_Dyn, OS_CFG_SIZE_OSCORE3_TASK_PRIO12_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_TASK_PRIO12_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_TASK_PRIO32_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore3_Task_Prio32 */
/* User: [OsTask_Bsw_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Task_Prio32_Dyn, OS_CFG_SIZE_OSCORE3_TASK_PRIO32_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_TASK_PRIO32_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore3_Task_Prio4294967295 */
/* User: [IdleTask_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE3_TASK_PRIO4294967295_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore3_Task_Prio48 */
/* User: [OsTask_Init_OsCore3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Task_Prio48_Dyn, OS_CFG_SIZE_OSCORE3_TASK_PRIO48_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore3_Task_Prio49 */
/* User: [Default_Init_Task_Core3_Trusted] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Task_Prio49_Dyn, OS_CFG_SIZE_OSCORE3_TASK_PRIO49_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE3_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore3_Task_Prio52 */
/* User: [Default_Init_Task_Core3] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore3_Task_Prio52_Dyn, OS_CFG_SIZE_OSCORE3_TASK_PRIO52_STACK);

# define OS_STOP_SEC_STACK_OSCORE3_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core error stack: OsCore4_Error */
/* User: [ErrorHook_OsCore4, OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Error_Dyn, OS_CFG_SIZE_OSCORE4_ERROR_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core init stack: OsCore4_Init */
/* User: [OsCore4, Os_CoreInitHook_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Init_Dyn, OS_CFG_SIZE_OSCORE4_INIT_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ISR core global stack: OsCore4_Isr_Core */
/* User: [CounterIsr_SystemTimer_OsCore4, XSignalIsr_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE4_ISR_CORE_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core kernel stack: OsCore4_Kernel */
/* User: [OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Kernel_Dyn, OS_CFG_SIZE_OSCORE4_KERNEL_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core shutdown stack: OsCore4_Shutdown */
/* User: [OsCore4, ShutdownHook_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Shutdown_Dyn, OS_CFG_SIZE_OSCORE4_SHUTDOWN_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core startup stack: OsCore4_Startup */
/* User: [OsCore4, StartupHook_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Startup_Dyn, OS_CFG_SIZE_OSCORE4_STARTUP_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_TASK_PRIO11_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore4_Task_Prio11 */
/* User: [OsTask_Asw_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Task_Prio11_Dyn, OS_CFG_SIZE_OSCORE4_TASK_PRIO11_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_TASK_PRIO11_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_TASK_PRIO31_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore4_Task_Prio31 */
/* User: [OsTask_Bsw_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Task_Prio31_Dyn, OS_CFG_SIZE_OSCORE4_TASK_PRIO31_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_TASK_PRIO31_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore4_Task_Prio4294967295 */
/* User: [IdleTask_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE4_TASK_PRIO4294967295_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore4_Task_Prio48 */
/* User: [OsTask_Init_OsCore4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Task_Prio48_Dyn, OS_CFG_SIZE_OSCORE4_TASK_PRIO48_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore4_Task_Prio49 */
/* User: [Default_Init_Task_Core4_Trusted] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Task_Prio49_Dyn, OS_CFG_SIZE_OSCORE4_TASK_PRIO49_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE4_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore4_Task_Prio51 */
/* User: [Default_Init_Task_Core4] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore4_Task_Prio51_Dyn, OS_CFG_SIZE_OSCORE4_TASK_PRIO51_STACK);

# define OS_STOP_SEC_STACK_OSCORE4_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core error stack: OsCore5_Error */
/* User: [ErrorHook_OsCore5, OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Error_Dyn, OS_CFG_SIZE_OSCORE5_ERROR_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_ERROR_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core init stack: OsCore5_Init */
/* User: [OsCore5, Os_CoreInitHook_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Init_Dyn, OS_CFG_SIZE_OSCORE5_INIT_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_INIT_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ISR core global stack: OsCore5_Isr_Core */
/* User: [CounterIsr_SystemTimer_OsCore5, XSignalIsr_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE5_ISR_CORE_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core kernel stack: OsCore5_Kernel */
/* User: [OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Kernel_Dyn, OS_CFG_SIZE_OSCORE5_KERNEL_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_KERNEL_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core shutdown stack: OsCore5_Shutdown */
/* User: [OsCore5, ShutdownHook_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Shutdown_Dyn, OS_CFG_SIZE_OSCORE5_SHUTDOWN_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_SHUTDOWN_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Core startup stack: OsCore5_Startup */
/* User: [OsCore5, StartupHook_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Startup_Dyn, OS_CFG_SIZE_OSCORE5_STARTUP_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_STARTUP_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_TASK_PRIO10_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore5_Task_Prio10 */
/* User: [OsTask_Asw_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Task_Prio10_Dyn, OS_CFG_SIZE_OSCORE5_TASK_PRIO10_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_TASK_PRIO10_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_TASK_PRIO30_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore5_Task_Prio30 */
/* User: [OsTask_Bsw_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Task_Prio30_Dyn, OS_CFG_SIZE_OSCORE5_TASK_PRIO30_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_TASK_PRIO30_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore5_Task_Prio4294967295 */
/* User: [IdleTask_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE5_TASK_PRIO4294967295_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore5_Task_Prio48 */
/* User: [OsTask_Init_OsCore5] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Task_Prio48_Dyn, OS_CFG_SIZE_OSCORE5_TASK_PRIO48_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_TASK_PRIO48_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore5_Task_Prio49 */
/* User: [Default_Init_Task_Core6_Trusted] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Task_Prio49_Dyn, OS_CFG_SIZE_OSCORE5_TASK_PRIO49_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_TASK_PRIO49_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSCORE5_TASK_PRIO50_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Shared Task stack: OsCore5_Task_Prio50 */
/* User: [Default_Init_Task_Core6] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsCore5_Task_Prio50_Dyn, OS_CFG_SIZE_OSCORE5_TASK_PRIO50_STACK);

# define OS_STOP_SEC_STACK_OSCORE5_TASK_PRIO50_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSTASK_ASW_OSCORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Task stack: OsTask_Asw_OsCore0 */
/* User: [OsTask_Asw_OsCore0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsTask_Asw_OsCore0_Dyn, OS_CFG_SIZE_OSTASK_ASW_OSCORE0_STACK);

# define OS_STOP_SEC_STACK_OSTASK_ASW_OSCORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_STACK_OSTASK_BSW_10MS_CORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Task stack: OsTask_Bsw_10ms_Core0 */
/* User: [OsTask_Bsw_10ms_Core0] */
extern OS_STACK_DECLARE(OsCfg_Stack_OsTask_Bsw_10ms_Core0_Dyn, OS_CFG_SIZE_OSTASK_BSW_10MS_CORE0_STACK);

# define OS_STOP_SEC_STACK_OSTASK_BSW_10MS_CORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stack configuration data: OsCore0_Error */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Error;

/*! Stack configuration data: OsCore0_Init */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Init;

/*! Stack configuration data: OsCore0_Isr_Core */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Isr_Core;

/*! Stack configuration data: OsCore0_Kernel */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Kernel;

/*! Stack configuration data: OsCore0_Shutdown */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Shutdown;

/*! Stack configuration data: OsCore0_Startup */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Startup;

/*! Stack configuration data: OsCore0_Task_Prio20 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio20;

/*! Stack configuration data: OsCore0_Task_Prio40 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio40;

/*! Stack configuration data: OsCore0_Task_Prio4294967295 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio4294967295;

/*! Stack configuration data: OsCore0_Task_Prio48 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio48;

/*! Stack configuration data: OsCore0_Task_Prio50 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio50;

/*! Stack configuration data: OsCore0_Task_Prio55 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio55;

/*! Stack configuration data: OsTask_Asw_OsCore0 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsTask_Asw_OsCore0;

/*! Stack configuration data: OsTask_Bsw_10ms_Core0 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsTask_Bsw_10ms_Core0;

# define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stack configuration data: OsCore1_Error */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Error;

/*! Stack configuration data: OsCore1_Init */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Init;

/*! Stack configuration data: OsCore1_Isr_Core */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Isr_Core;

/*! Stack configuration data: OsCore1_Kernel */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Kernel;

/*! Stack configuration data: OsCore1_Shutdown */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Shutdown;

/*! Stack configuration data: OsCore1_Startup */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Startup;

/*! Stack configuration data: OsCore1_Task_Prio14 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio14;

/*! Stack configuration data: OsCore1_Task_Prio34 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio34;

/*! Stack configuration data: OsCore1_Task_Prio41 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio41;

/*! Stack configuration data: OsCore1_Task_Prio4294967295 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio4294967295;

/*! Stack configuration data: OsCore1_Task_Prio48 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio48;

/*! Stack configuration data: OsCore1_Task_Prio49 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio49;

/*! Stack configuration data: OsCore1_Task_Prio54 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio54;

# define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stack configuration data: OsCore2_Error */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Error;

/*! Stack configuration data: OsCore2_Init */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Init;

/*! Stack configuration data: OsCore2_Isr_Core */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Isr_Core;

/*! Stack configuration data: OsCore2_Kernel */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Kernel;

/*! Stack configuration data: OsCore2_Shutdown */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Shutdown;

/*! Stack configuration data: OsCore2_Startup */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Startup;

/*! Stack configuration data: OsCore2_Task_Prio13 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio13;

/*! Stack configuration data: OsCore2_Task_Prio33 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio33;

/*! Stack configuration data: OsCore2_Task_Prio4294967295 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio4294967295;

/*! Stack configuration data: OsCore2_Task_Prio48 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio48;

/*! Stack configuration data: OsCore2_Task_Prio49 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio49;

/*! Stack configuration data: OsCore2_Task_Prio53 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio53;

# define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE3_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stack configuration data: OsCore3_Error */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Error;

/*! Stack configuration data: OsCore3_Init */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Init;

/*! Stack configuration data: OsCore3_Isr_Core */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Isr_Core;

/*! Stack configuration data: OsCore3_Kernel */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Kernel;

/*! Stack configuration data: OsCore3_Shutdown */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Shutdown;

/*! Stack configuration data: OsCore3_Startup */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Startup;

/*! Stack configuration data: OsCore3_Task_Prio12 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Task_Prio12;

/*! Stack configuration data: OsCore3_Task_Prio32 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Task_Prio32;

/*! Stack configuration data: OsCore3_Task_Prio4294967295 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Task_Prio4294967295;

/*! Stack configuration data: OsCore3_Task_Prio48 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Task_Prio48;

/*! Stack configuration data: OsCore3_Task_Prio49 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Task_Prio49;

/*! Stack configuration data: OsCore3_Task_Prio52 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore3_Task_Prio52;

# define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE4_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stack configuration data: OsCore4_Error */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Error;

/*! Stack configuration data: OsCore4_Init */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Init;

/*! Stack configuration data: OsCore4_Isr_Core */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Isr_Core;

/*! Stack configuration data: OsCore4_Kernel */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Kernel;

/*! Stack configuration data: OsCore4_Shutdown */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Shutdown;

/*! Stack configuration data: OsCore4_Startup */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Startup;

/*! Stack configuration data: OsCore4_Task_Prio11 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Task_Prio11;

/*! Stack configuration data: OsCore4_Task_Prio31 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Task_Prio31;

/*! Stack configuration data: OsCore4_Task_Prio4294967295 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Task_Prio4294967295;

/*! Stack configuration data: OsCore4_Task_Prio48 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Task_Prio48;

/*! Stack configuration data: OsCore4_Task_Prio49 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Task_Prio49;

/*! Stack configuration data: OsCore4_Task_Prio51 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore4_Task_Prio51;

# define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE5_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stack configuration data: OsCore5_Error */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Error;

/*! Stack configuration data: OsCore5_Init */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Init;

/*! Stack configuration data: OsCore5_Isr_Core */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Isr_Core;

/*! Stack configuration data: OsCore5_Kernel */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Kernel;

/*! Stack configuration data: OsCore5_Shutdown */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Shutdown;

/*! Stack configuration data: OsCore5_Startup */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Startup;

/*! Stack configuration data: OsCore5_Task_Prio10 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Task_Prio10;

/*! Stack configuration data: OsCore5_Task_Prio30 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Task_Prio30;

/*! Stack configuration data: OsCore5_Task_Prio4294967295 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Task_Prio4294967295;

/*! Stack configuration data: OsCore5_Task_Prio48 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Task_Prio48;

/*! Stack configuration data: OsCore5_Task_Prio49 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Task_Prio49;

/*! Stack configuration data: OsCore5_Task_Prio50 */
extern CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore5_Task_Prio50;

# define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_STACK_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Stack_Lcfg.h
 *********************************************************************************************************************/
