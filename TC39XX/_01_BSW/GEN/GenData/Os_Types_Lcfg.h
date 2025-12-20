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
 *              File: Os_Types_Lcfg.h
 *   Generation Time: 2025-12-20 10:43:27
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef OS_TYPES_LCFG_H
# define OS_TYPES_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* OS-Application identifiers. */
#define OsApplication_OsCore0 OsApplication_OsCore0
#define OsApplication_OsCore1 OsApplication_OsCore1
#define OsApplication_OsCore2 OsApplication_OsCore2
#define OsApplication_OsCore3 OsApplication_OsCore3
#define OsApplication_OsCore4 OsApplication_OsCore4
#define OsApplication_OsCore5 OsApplication_OsCore5
#define SystemApplication_OsCore0 SystemApplication_OsCore0
#define SystemApplication_OsCore1 SystemApplication_OsCore1
#define SystemApplication_OsCore2 SystemApplication_OsCore2
#define SystemApplication_OsCore3 SystemApplication_OsCore3
#define SystemApplication_OsCore4 SystemApplication_OsCore4
#define SystemApplication_OsCore5 SystemApplication_OsCore5

/* Trusted function identifiers. */

/* Non-trusted function identifiers. */

/* Fast trusted function identifiers. */

/* Task identifiers. */
#define Default_Init_Task Default_Init_Task
#define Default_Init_Task_Core1 Default_Init_Task_Core1
#define Default_Init_Task_Core1_Trusted Default_Init_Task_Core1_Trusted
#define Default_Init_Task_Core2 Default_Init_Task_Core2
#define Default_Init_Task_Core2_Trusted Default_Init_Task_Core2_Trusted
#define Default_Init_Task_Core3 Default_Init_Task_Core3
#define Default_Init_Task_Core3_Trusted Default_Init_Task_Core3_Trusted
#define Default_Init_Task_Core4 Default_Init_Task_Core4
#define Default_Init_Task_Core4_Trusted Default_Init_Task_Core4_Trusted
#define Default_Init_Task_Core6 Default_Init_Task_Core6
#define Default_Init_Task_Core6_Trusted Default_Init_Task_Core6_Trusted
#define Default_Init_Task_Trusted Default_Init_Task_Trusted
#define IdleTask_OsCore0 IdleTask_OsCore0
#define IdleTask_OsCore1 IdleTask_OsCore1
#define IdleTask_OsCore2 IdleTask_OsCore2
#define IdleTask_OsCore3 IdleTask_OsCore3
#define IdleTask_OsCore4 IdleTask_OsCore4
#define IdleTask_OsCore5 IdleTask_OsCore5
#define OsTask_Asw_OsCore0 OsTask_Asw_OsCore0
#define OsTask_Asw_OsCore1 OsTask_Asw_OsCore1
#define OsTask_Asw_OsCore2 OsTask_Asw_OsCore2
#define OsTask_Asw_OsCore3 OsTask_Asw_OsCore3
#define OsTask_Asw_OsCore4 OsTask_Asw_OsCore4
#define OsTask_Asw_OsCore5 OsTask_Asw_OsCore5
#define OsTask_Bsw_10ms_Core0 OsTask_Bsw_10ms_Core0
#define OsTask_Bsw_1ms_Core0 OsTask_Bsw_1ms_Core0
#define OsTask_Bsw_20ms_Core0 OsTask_Bsw_20ms_Core0
#define OsTask_Bsw_5ms_Core0 OsTask_Bsw_5ms_Core0
#define OsTask_Bsw_OsCore1 OsTask_Bsw_OsCore1
#define OsTask_Bsw_OsCore2 OsTask_Bsw_OsCore2
#define OsTask_Bsw_OsCore3 OsTask_Bsw_OsCore3
#define OsTask_Bsw_OsCore4 OsTask_Bsw_OsCore4
#define OsTask_Bsw_OsCore5 OsTask_Bsw_OsCore5
#define OsTask_Init_OsCore0 OsTask_Init_OsCore0
#define OsTask_Init_OsCore1 OsTask_Init_OsCore1
#define OsTask_Init_OsCore2 OsTask_Init_OsCore2
#define OsTask_Init_OsCore3 OsTask_Init_OsCore3
#define OsTask_Init_OsCore4 OsTask_Init_OsCore4
#define OsTask_Init_OsCore5 OsTask_Init_OsCore5
#define OsTask_lock_2ms OsTask_lock_2ms
#define OsTask_window_2ms OsTask_window_2ms

/* Category 2 ISR identifiers. */
#define CounterIsr_SystemTimer_OsCore0 CounterIsr_SystemTimer_OsCore0
#define CounterIsr_SystemTimer_OsCore1 CounterIsr_SystemTimer_OsCore1
#define CounterIsr_SystemTimer_OsCore2 CounterIsr_SystemTimer_OsCore2
#define CounterIsr_SystemTimer_OsCore3 CounterIsr_SystemTimer_OsCore3
#define CounterIsr_SystemTimer_OsCore4 CounterIsr_SystemTimer_OsCore4
#define CounterIsr_SystemTimer_OsCore5 CounterIsr_SystemTimer_OsCore5
#define EthIsr_EthCtrlConfig_MAIN_EthInterruptServiceRoutine EthIsr_EthCtrlConfig_MAIN_EthInterruptServiceRoutine
#define XSignalIsr_OsCore0 XSignalIsr_OsCore0
#define XSignalIsr_OsCore1 XSignalIsr_OsCore1
#define XSignalIsr_OsCore2 XSignalIsr_OsCore2
#define XSignalIsr_OsCore3 XSignalIsr_OsCore3
#define XSignalIsr_OsCore4 XSignalIsr_OsCore4
#define XSignalIsr_OsCore5 XSignalIsr_OsCore5

/* Alarm identifiers. */
#define Rte_Al_TE2_EcuM_EcuM_MainFunction Rte_Al_TE2_EcuM_EcuM_MainFunction
#define Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms
#define Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms
#define Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms
#define Rte_Al_TE3_EcuM_EcuM_MainFunction Rte_Al_TE3_EcuM_EcuM_MainFunction
#define Rte_Al_TE4_EcuM_EcuM_MainFunction Rte_Al_TE4_EcuM_EcuM_MainFunction
#define Rte_Al_TE5_EcuM_EcuM_MainFunction Rte_Al_TE5_EcuM_EcuM_MainFunction
#define Rte_Al_TE6_EcuM_EcuM_MainFunction Rte_Al_TE6_EcuM_EcuM_MainFunction
#define Rte_Al_TE_Cdd_Core0_Runnable_20 Rte_Al_TE_Cdd_Core0_Runnable_20
#define Rte_Al_TE_Cdd_Core0_Runnable_5ms Rte_Al_TE_Cdd_Core0_Runnable_5ms
#define Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms
#define Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms
#define Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms
#define Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms
#define Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms
#define Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms
#define Rte_Al_TE_EthIf_EthIf_MainFunctionState Rte_Al_TE_EthIf_EthIf_MainFunctionState
#define Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction
#define Rte_Al_TE_swc_lock_Runnable_2ms Rte_Al_TE_swc_lock_Runnable_2ms
#define Rte_Al_TE_window_core1_Runnable_windows_2ms Rte_Al_TE_window_core1_Runnable_windows_2ms

/* Counter identifiers. */
#define SystemTimer_OsCore0 SystemTimer_OsCore0
#define SystemTimer_OsCore1 SystemTimer_OsCore1
#define SystemTimer_OsCore2 SystemTimer_OsCore2
#define SystemTimer_OsCore3 SystemTimer_OsCore3
#define SystemTimer_OsCore4 SystemTimer_OsCore4
#define SystemTimer_OsCore5 SystemTimer_OsCore5

/* ScheduleTable identifiers. */

/* Resource identifiers. */
#define OsResource OsResource

/* Spinlock identifiers. */

/* Peripheral identifiers. */

/* Barrier identifiers. */

/* Trace thread identifiers (Tasks and ISRs inclusive system objects). */

/* Trace spinlock identifiers (All spinlocks inclusive system objects). */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint32  Os_AppAccessMaskType;

/*! OS-Application identifiers. */
typedef enum
{
  OsApplication_OsCore0 = 0, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsApplication_OsCore1 = 1, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsApplication_OsCore2 = 2, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsApplication_OsCore3 = 3, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsApplication_OsCore4 = 4, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsApplication_OsCore5 = 5, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore0 = 6, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore1 = 7, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore2 = 8, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore3 = 9, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore4 = 10, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore5 = 11, /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_APPID_COUNT = 12,
  INVALID_OSAPPLICATION = OS_APPID_COUNT
} ApplicationType;

/*! Trusted function identifiers. */
typedef enum
{
  OS_TRUSTEDFUNCTIONID_COUNT = 0
} TrustedFunctionIndexType;

/*! Non-trusted function identifiers. */
typedef enum
{
  OS_NONTRUSTEDFUNCTIONID_COUNT = 0
} Os_NonTrustedFunctionIndexType;

/*! Fast trusted function identifiers. */
typedef enum
{
  OS_FASTTRUSTEDFUNCTIONID_COUNT = 0
} Os_FastTrustedFunctionIndexType;

/*! Task identifiers. */
typedef enum
{
  Default_Init_Task = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core1 = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core1_Trusted = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core2 = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core2_Trusted = 4,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core3 = 5,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core3_Trusted = 6,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core4 = 7,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core4_Trusted = 8,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core6 = 9,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Core6_Trusted = 10,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Default_Init_Task_Trusted = 11,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore0 = 12,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore1 = 13,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore2 = 14,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore3 = 15,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore4 = 16,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore5 = 17,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Asw_OsCore0 = 18,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Asw_OsCore1 = 19,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Asw_OsCore2 = 20,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Asw_OsCore3 = 21,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Asw_OsCore4 = 22,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Asw_OsCore5 = 23,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_10ms_Core0 = 24,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_1ms_Core0 = 25,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_20ms_Core0 = 26,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_5ms_Core0 = 27,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_OsCore1 = 28,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_OsCore2 = 29,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_OsCore3 = 30,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_OsCore4 = 31,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Bsw_OsCore5 = 32,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_OsCore0 = 33,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_OsCore1 = 34,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_OsCore2 = 35,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_OsCore3 = 36,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_OsCore4 = 37,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_OsCore5 = 38,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_lock_2ms = 39,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_window_2ms = 40,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_TASKID_COUNT = 41,
  INVALID_TASK = OS_TASKID_COUNT
} TaskType;

/*! Category 2 ISR identifiers. */
typedef enum
{
  CounterIsr_SystemTimer_OsCore0 = 0,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_OsCore1 = 1,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_OsCore2 = 2,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_OsCore3 = 3,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_OsCore4 = 4,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_OsCore5 = 5,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  EthIsr_EthCtrlConfig_MAIN_EthInterruptServiceRoutine = 6,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore0 = 7,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore1 = 8,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore2 = 9,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore3 = 10,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore4 = 11,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore5 = 12,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_ISRID_COUNT = 13,
  INVALID_ISR = OS_ISRID_COUNT
} ISRType;

/*! Alarm identifiers. */
typedef enum
{
  Rte_Al_TE2_EcuM_EcuM_MainFunction = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE3_EcuM_EcuM_MainFunction = 4,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE4_EcuM_EcuM_MainFunction = 5,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE5_EcuM_EcuM_MainFunction = 6,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE6_EcuM_EcuM_MainFunction = 7,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_Core0_Runnable_20 = 8,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_Core0_Runnable_5ms = 9,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms = 10,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms = 11,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms = 12,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms = 13,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms = 14,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms = 15,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_EthIf_EthIf_MainFunctionState = 16,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction = 17,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_swc_lock_Runnable_2ms = 18,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_window_core1_Runnable_windows_2ms = 19,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_ALARMID_COUNT = 20
} AlarmType;

/*! Counter identifiers. */
typedef enum
{
  SystemTimer_OsCore0 = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_OsCore1 = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_OsCore2 = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_OsCore3 = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_OsCore4 = 4,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_OsCore5 = 5,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_COUNTERID_COUNT = 6
} CounterType;

/*! ScheduleTable identifiers. */
typedef enum
{
  OS_SCHTID_COUNT = 0
} ScheduleTableType;

/*! Resource identifiers. */
typedef enum
{
  OsResource = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_RESOURCEID_COUNT = 1
} ResourceType;

/*! Spinlock identifiers. */
typedef enum
{
  OS_SPINLOCKID_COUNT = 0,
  INVALID_SPINLOCK = OS_SPINLOCKID_COUNT
} SpinlockIdType;

/*! Peripheral identifiers. */
typedef enum
{
  OS_PERIPHERALID_COUNT = 0
} Os_PeripheralIdType;

/*! Barrier identifiers. */
typedef enum
{
  OS_BARRIERID_COUNT = 0
} Os_BarrierIdType;

/*! Trace thread identifiers (Tasks and ISRs inclusive system objects). */
typedef enum
{
  OS_TRACE_THREADID_COUNT = 0,
  OS_TRACE_INVALID_THREAD = OS_TRACE_THREADID_COUNT + 1
} Os_TraceThreadIdType;

/*! Trace spinlock identifiers (All spinlocks inclusive system objects). */
typedef enum
{
  OS_TRACE_NUMBER_OF_CONFIGURED_SPINLOCKS = OS_SPINLOCKID_COUNT,
  OS_TRACE_NUMBER_OF_ALL_SPINLOCKS = OS_SPINLOCKID_COUNT + 0u,  /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
  OS_TRACE_INVALID_SPINLOCK = OS_TRACE_NUMBER_OF_ALL_SPINLOCKS + 1
} Os_TraceSpinlockIdType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_TYPES_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Types_Lcfg.h
 *********************************************************************************************************************/
