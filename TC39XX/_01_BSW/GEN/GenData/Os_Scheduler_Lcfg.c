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
 *              File: Os_Scheduler_Lcfg.c
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_SCHEDULER_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Scheduler_Cfg.h"
#include "Os_Scheduler_Lcfg.h"
#include "Os_Scheduler.h"

/* Os kernel module dependencies */
#include "Os_BitArray.h"
#include "Os_Common.h"
#include "Os_Deque.h"

/* Os hal dependencies */


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

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic scheduler data: OsCore0 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore0_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore0_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore0_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore0 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue12_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes12_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE12_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue13_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes13_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE13_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue14_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes14_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE14_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue15_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes15_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE15_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue16_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes16_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE16_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue17_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes17_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE17_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue18_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes18_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE18_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue19_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes19_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE19_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue20_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes20_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE20_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue21_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes21_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE21_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue22_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes22_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE22_OSCORE0_SLOTS];

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic scheduler data: OsCore1 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore1_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore1_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore1_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore1 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue12_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes12_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE12_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue13_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes13_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE13_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue14_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes14_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE14_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue15_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes15_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE15_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue16_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes16_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE16_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue17_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes17_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE17_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue18_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes18_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE18_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue19_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes19_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE19_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue20_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes20_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE20_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue21_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes21_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE21_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue22_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes22_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE22_OSCORE1_SLOTS];

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic scheduler data: OsCore2 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore2_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore2_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore2_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore2 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue12_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes12_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE12_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue13_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes13_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE13_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue14_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes14_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE14_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue15_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes15_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE15_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue16_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes16_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE16_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue17_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes17_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE17_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue18_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes18_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE18_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue19_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes19_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE19_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue20_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes20_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE20_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue21_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes21_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE21_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue22_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes22_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE22_OSCORE2_SLOTS];

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic scheduler data: OsCore3 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore3_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore3_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore3_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore3 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue12_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes12_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE12_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue13_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes13_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE13_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue14_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes14_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE14_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue15_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes15_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE15_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue16_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes16_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE16_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue17_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes17_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE17_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue18_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes18_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE18_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue19_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes19_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE19_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue20_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes20_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE20_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue21_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes21_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE21_OSCORE3_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue22_OsCore3_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes22_OsCore3_Dyn[OS_CFG_NUM_TASKQUEUE22_OSCORE3_SLOTS];

#define OS_STOP_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic scheduler data: OsCore4 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore4_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore4_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore4_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore4 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue12_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes12_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE12_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue13_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes13_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE13_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue14_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes14_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE14_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue15_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes15_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE15_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue16_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes16_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE16_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue17_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes17_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE17_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue18_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes18_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE18_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue19_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes19_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE19_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue20_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes20_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE20_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue21_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes21_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE21_OSCORE4_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue22_OsCore4_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes22_OsCore4_Dyn[OS_CFG_NUM_TASKQUEUE22_OSCORE4_SLOTS];

#define OS_STOP_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic scheduler data: OsCore5 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore5_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore5_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore5_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore5 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue12_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes12_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE12_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue13_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes13_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE13_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue14_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes14_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE14_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue15_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes15_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE15_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue16_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes16_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE16_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue17_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes17_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE17_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue18_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes18_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE18_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue19_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes19_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE19_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue20_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes20_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE20_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue21_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes21_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE21_OSCORE5_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue22_OsCore5_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes22_OsCore5_Dyn[OS_CFG_NUM_TASKQUEUE22_OSCORE5_SLOTS];

#define OS_STOP_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Task queues configuration data: OsCore0 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore0_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE0_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE0_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE0_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE0_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE0_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE0_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE0_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE0_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE0_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE0_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE0_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE0_SLOTS
  },
  /* [12] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue12_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes12_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE12_OSCORE0_SLOTS
  },
  /* [13] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue13_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes13_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE13_OSCORE0_SLOTS
  },
  /* [14] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue14_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes14_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE14_OSCORE0_SLOTS
  },
  /* [15] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue15_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes15_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE15_OSCORE0_SLOTS
  },
  /* [16] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue16_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes16_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE16_OSCORE0_SLOTS
  },
  /* [17] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue17_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes17_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE17_OSCORE0_SLOTS
  },
  /* [18] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue18_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes18_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE18_OSCORE0_SLOTS
  },
  /* [19] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue19_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes19_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE19_OSCORE0_SLOTS
  },
  /* [20] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue20_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes20_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE20_OSCORE0_SLOTS
  },
  /* [21] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue21_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes21_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE21_OSCORE0_SLOTS
  },
  /* [22] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue22_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes22_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE22_OSCORE0_SLOTS
  }
};

/*! Scheduler configuration data: OsCore0 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore0 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore0_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore0_BitField_Dyn,
    /* .Size      = */ (uint16)OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ (uint16)OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore0_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore0_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Task queues configuration data: OsCore1 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore1_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE1_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE1_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE1_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE1_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE1_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE1_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE1_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE1_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE1_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE1_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE1_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE1_SLOTS
  },
  /* [12] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue12_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes12_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE12_OSCORE1_SLOTS
  },
  /* [13] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue13_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes13_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE13_OSCORE1_SLOTS
  },
  /* [14] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue14_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes14_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE14_OSCORE1_SLOTS
  },
  /* [15] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue15_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes15_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE15_OSCORE1_SLOTS
  },
  /* [16] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue16_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes16_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE16_OSCORE1_SLOTS
  },
  /* [17] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue17_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes17_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE17_OSCORE1_SLOTS
  },
  /* [18] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue18_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes18_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE18_OSCORE1_SLOTS
  },
  /* [19] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue19_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes19_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE19_OSCORE1_SLOTS
  },
  /* [20] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue20_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes20_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE20_OSCORE1_SLOTS
  },
  /* [21] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue21_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes21_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE21_OSCORE1_SLOTS
  },
  /* [22] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue22_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes22_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE22_OSCORE1_SLOTS
  }
};

/*! Scheduler configuration data: OsCore1 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore1 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore1_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore1_BitField_Dyn,
    /* .Size      = */ (uint16)OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ (uint16)OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore1_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore1_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Task queues configuration data: OsCore2 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore2_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE2_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE2_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE2_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE2_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE2_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE2_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE2_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE2_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE2_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE2_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE2_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE2_SLOTS
  },
  /* [12] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue12_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes12_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE12_OSCORE2_SLOTS
  },
  /* [13] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue13_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes13_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE13_OSCORE2_SLOTS
  },
  /* [14] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue14_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes14_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE14_OSCORE2_SLOTS
  },
  /* [15] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue15_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes15_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE15_OSCORE2_SLOTS
  },
  /* [16] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue16_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes16_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE16_OSCORE2_SLOTS
  },
  /* [17] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue17_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes17_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE17_OSCORE2_SLOTS
  },
  /* [18] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue18_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes18_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE18_OSCORE2_SLOTS
  },
  /* [19] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue19_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes19_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE19_OSCORE2_SLOTS
  },
  /* [20] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue20_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes20_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE20_OSCORE2_SLOTS
  },
  /* [21] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue21_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes21_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE21_OSCORE2_SLOTS
  },
  /* [22] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue22_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes22_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE22_OSCORE2_SLOTS
  }
};

/*! Scheduler configuration data: OsCore2 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore2 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore2_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore2_BitField_Dyn,
    /* .Size      = */ (uint16)OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ (uint16)OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore2_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore2_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Task queues configuration data: OsCore3 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore3_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE3_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE3_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE3_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE3_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE3_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE3_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE3_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE3_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE3_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE3_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE3_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE3_SLOTS
  },
  /* [12] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue12_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes12_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE12_OSCORE3_SLOTS
  },
  /* [13] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue13_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes13_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE13_OSCORE3_SLOTS
  },
  /* [14] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue14_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes14_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE14_OSCORE3_SLOTS
  },
  /* [15] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue15_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes15_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE15_OSCORE3_SLOTS
  },
  /* [16] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue16_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes16_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE16_OSCORE3_SLOTS
  },
  /* [17] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue17_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes17_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE17_OSCORE3_SLOTS
  },
  /* [18] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue18_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes18_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE18_OSCORE3_SLOTS
  },
  /* [19] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue19_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes19_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE19_OSCORE3_SLOTS
  },
  /* [20] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue20_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes20_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE20_OSCORE3_SLOTS
  },
  /* [21] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue21_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes21_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE21_OSCORE3_SLOTS
  },
  /* [22] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue22_OsCore3_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes22_OsCore3_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE22_OSCORE3_SLOTS
  }
};

/*! Scheduler configuration data: OsCore3 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore3 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore3_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore3_BitField_Dyn,
    /* .Size      = */ (uint16)OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ (uint16)OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore3_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore3_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Task queues configuration data: OsCore4 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore4_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE4_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE4_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE4_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE4_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE4_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE4_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE4_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE4_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE4_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE4_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE4_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE4_SLOTS
  },
  /* [12] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue12_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes12_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE12_OSCORE4_SLOTS
  },
  /* [13] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue13_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes13_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE13_OSCORE4_SLOTS
  },
  /* [14] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue14_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes14_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE14_OSCORE4_SLOTS
  },
  /* [15] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue15_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes15_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE15_OSCORE4_SLOTS
  },
  /* [16] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue16_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes16_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE16_OSCORE4_SLOTS
  },
  /* [17] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue17_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes17_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE17_OSCORE4_SLOTS
  },
  /* [18] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue18_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes18_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE18_OSCORE4_SLOTS
  },
  /* [19] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue19_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes19_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE19_OSCORE4_SLOTS
  },
  /* [20] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue20_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes20_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE20_OSCORE4_SLOTS
  },
  /* [21] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue21_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes21_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE21_OSCORE4_SLOTS
  },
  /* [22] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue22_OsCore4_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes22_OsCore4_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE22_OSCORE4_SLOTS
  }
};

/*! Scheduler configuration data: OsCore4 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore4 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore4_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore4_BitField_Dyn,
    /* .Size      = */ (uint16)OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ (uint16)OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore4_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore4_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Task queues configuration data: OsCore5 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore5_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE5_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE5_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE5_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE5_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE5_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE5_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE5_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE5_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE5_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE5_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE5_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE5_SLOTS
  },
  /* [12] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue12_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes12_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE12_OSCORE5_SLOTS
  },
  /* [13] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue13_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes13_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE13_OSCORE5_SLOTS
  },
  /* [14] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue14_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes14_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE14_OSCORE5_SLOTS
  },
  /* [15] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue15_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes15_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE15_OSCORE5_SLOTS
  },
  /* [16] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue16_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes16_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE16_OSCORE5_SLOTS
  },
  /* [17] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue17_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes17_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE17_OSCORE5_SLOTS
  },
  /* [18] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue18_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes18_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE18_OSCORE5_SLOTS
  },
  /* [19] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue19_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes19_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE19_OSCORE5_SLOTS
  },
  /* [20] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue20_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes20_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE20_OSCORE5_SLOTS
  },
  /* [21] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue21_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes21_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE21_OSCORE5_SLOTS
  },
  /* [22] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue22_OsCore5_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes22_OsCore5_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE22_OSCORE5_SLOTS
  }
};

/*! Scheduler configuration data: OsCore5 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore5 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore5_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore5_BitField_Dyn,
    /* .Size      = */ (uint16)OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ (uint16)OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore5_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore5_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
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
 *  END OF FILE: Os_Scheduler_Lcfg.c
 *********************************************************************************************************************/
