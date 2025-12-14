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
 *              File: Os_Stack_Cfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef OS_STACK_CFG_H
# define OS_STACK_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether stack monitoring is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_STACKMONITORING                  (STD_ON)

/*! Defines whether stack measurement is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_STACKMEASUREMENT                 (STD_OFF)

/* Configured stack sizes (Total: 76800 Byte) */
# define OS_CFG_SIZE_OSCORE0_ERROR_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_INIT_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_ISR_CORE_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_KERNEL_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_SHUTDOWN_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_STARTUP_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO20_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO40_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO4294967295_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO48_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO50_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO55_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_ERROR_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_INIT_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_ISR_CORE_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_KERNEL_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_SHUTDOWN_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_STARTUP_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO14_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO34_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO41_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO4294967295_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO48_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO49_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO54_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_ERROR_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_INIT_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_ISR_CORE_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_KERNEL_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_SHUTDOWN_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_STARTUP_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO13_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO33_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO4294967295_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO48_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO49_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO53_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_ERROR_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_INIT_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_ISR_CORE_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_KERNEL_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_SHUTDOWN_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_STARTUP_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_TASK_PRIO12_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_TASK_PRIO32_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_TASK_PRIO4294967295_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_TASK_PRIO48_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_TASK_PRIO49_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE3_TASK_PRIO52_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_ERROR_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_INIT_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_ISR_CORE_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_KERNEL_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_SHUTDOWN_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_STARTUP_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_TASK_PRIO11_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_TASK_PRIO31_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_TASK_PRIO4294967295_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_TASK_PRIO48_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_TASK_PRIO49_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE4_TASK_PRIO51_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_ERROR_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_INIT_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_ISR_CORE_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_KERNEL_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_SHUTDOWN_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_STARTUP_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_TASK_PRIO10_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_TASK_PRIO30_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_TASK_PRIO4294967295_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_TASK_PRIO48_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_TASK_PRIO49_STACK     (1024uL)
# define OS_CFG_SIZE_OSCORE5_TASK_PRIO50_STACK     (1024uL)
# define OS_CFG_SIZE_OSTASK_ASW_OSCORE0_STACK     (1024uL)
# define OS_CFG_SIZE_OSTASK_BSW_10MS_CORE0_STACK     (1024uL)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_STACK_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Stack_Cfg.h
 *********************************************************************************************************************/
