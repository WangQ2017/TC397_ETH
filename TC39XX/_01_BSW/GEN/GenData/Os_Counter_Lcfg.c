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
 *              File: Os_Counter_Lcfg.c
 *   Generation Time: 2025-08-29 14:51:59
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_COUNTER_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Counter_Cfg.h"
#include "Os_Counter_Lcfg.h"
#include "Os_Counter.h"

/* Os kernel module dependencies */
#include "Os_Application_Lcfg.h"
#include "Os_Cfg.h"
#include "Os_Common.h"
#include "Os_Core_Lcfg.h"
#include "Os_PriorityQueue.h"
#include "Os_Timer.h"

/* Os hal dependencies */
#include "Os_Hal_Cfg.h"
#include "Os_Hal_Timer_Lcfg.h"


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

/*! Dynamic counter data: SystemTimer_OsCore0 */
OS_LOCAL VAR(Os_TimerHrtType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore0_Dyn;
OS_LOCAL VAR(Os_PriorityQueueType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore0_JobQueue_Dyn;
OS_LOCAL VAR(Os_PriorityQueueNodeType, OS_VAR_NOINIT)
  OsCfg_Counter_SystemTimer_OsCore0_JobQueueNodes_Dyn[OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE0_JOBS + 1u];

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic counter data: SystemTimer_OsCore1 */
OS_LOCAL VAR(Os_TimerHrtType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore1_Dyn;
OS_LOCAL VAR(Os_PriorityQueueType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore1_JobQueue_Dyn;
OS_LOCAL VAR(Os_PriorityQueueNodeType, OS_VAR_NOINIT)
  OsCfg_Counter_SystemTimer_OsCore1_JobQueueNodes_Dyn[OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE1_JOBS + 1u];

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic counter data: SystemTimer_OsCore2 */
OS_LOCAL VAR(Os_TimerHrtType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore2_Dyn;
OS_LOCAL VAR(Os_PriorityQueueType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore2_JobQueue_Dyn;
OS_LOCAL VAR(Os_PriorityQueueNodeType, OS_VAR_NOINIT)
  OsCfg_Counter_SystemTimer_OsCore2_JobQueueNodes_Dyn[OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE2_JOBS + 1u];

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic counter data: SystemTimer_OsCore3 */
OS_LOCAL VAR(Os_TimerHrtType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore3_Dyn;
OS_LOCAL VAR(Os_PriorityQueueType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore3_JobQueue_Dyn;
OS_LOCAL VAR(Os_PriorityQueueNodeType, OS_VAR_NOINIT)
  OsCfg_Counter_SystemTimer_OsCore3_JobQueueNodes_Dyn[OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE3_JOBS + 1u];

#define OS_STOP_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic counter data: SystemTimer_OsCore4 */
OS_LOCAL VAR(Os_TimerHrtType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore4_Dyn;
OS_LOCAL VAR(Os_PriorityQueueType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore4_JobQueue_Dyn;
OS_LOCAL VAR(Os_PriorityQueueNodeType, OS_VAR_NOINIT)
  OsCfg_Counter_SystemTimer_OsCore4_JobQueueNodes_Dyn[OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE4_JOBS + 1u];

#define OS_STOP_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic counter data: SystemTimer_OsCore5 */
OS_LOCAL VAR(Os_TimerHrtType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore5_Dyn;
OS_LOCAL VAR(Os_PriorityQueueType, OS_VAR_NOINIT) OsCfg_Counter_SystemTimer_OsCore5_JobQueue_Dyn;
OS_LOCAL VAR(Os_PriorityQueueNodeType, OS_VAR_NOINIT)
  OsCfg_Counter_SystemTimer_OsCore5_JobQueueNodes_Dyn[OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE5_JOBS + 1u];

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


/*! Counter configuration data: SystemTimer_OsCore0 */
CONST(Os_TimerHrtConfigType, OS_CONST) OsCfg_Counter_SystemTimer_OsCore0 =
{
  /* .Counter  = */
  {
    /* .Characteristics       = */
    {
      /* .MaxAllowedValue      = */ OSMAXALLOWEDVALUE_SystemTimer_OsCore0,
      /* .MaxCountingValue     = */ OS_TIMERHRT_GETMAXCOUNTINGVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore0),
      /* .MaxDifferentialValue = */ OS_TIMERHRT_GETMAXDIFFERENTIALVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore0),
      /* .MinCycle             = */ OSMINCYCLE_SystemTimer_OsCore0,
      /* .TicksPerBase         = */ OSTICKSPERBASE_SystemTimer_OsCore0
    },
    /* .JobQueue              = */
    {
      /* .Queue     = */ OsCfg_Counter_SystemTimer_OsCore0_JobQueueNodes_Dyn,
      /* .Dyn       = */ &OsCfg_Counter_SystemTimer_OsCore0_JobQueue_Dyn,
      /* .QueueSize = */ (Os_PriorityQueueNodeIdxType)OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE0_JOBS
    },
    /* .DriverType            = */ OS_TIMERTYPE_HIGH_RESOLUTION,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5))  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  },
  /* .Dyn      = */ &OsCfg_Counter_SystemTimer_OsCore0_Dyn,
  /* .HwConfig = */ &OsCfg_Hal_TimerFrt_SystemTimer_OsCore0
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Counter configuration data: SystemTimer_OsCore1 */
CONST(Os_TimerHrtConfigType, OS_CONST) OsCfg_Counter_SystemTimer_OsCore1 =
{
  /* .Counter  = */
  {
    /* .Characteristics       = */
    {
      /* .MaxAllowedValue      = */ OSMAXALLOWEDVALUE_SystemTimer_OsCore1,
      /* .MaxCountingValue     = */ OS_TIMERHRT_GETMAXCOUNTINGVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore1),
      /* .MaxDifferentialValue = */ OS_TIMERHRT_GETMAXDIFFERENTIALVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore1),
      /* .MinCycle             = */ OSMINCYCLE_SystemTimer_OsCore1,
      /* .TicksPerBase         = */ OSTICKSPERBASE_SystemTimer_OsCore1
    },
    /* .JobQueue              = */
    {
      /* .Queue     = */ OsCfg_Counter_SystemTimer_OsCore1_JobQueueNodes_Dyn,
      /* .Dyn       = */ &OsCfg_Counter_SystemTimer_OsCore1_JobQueue_Dyn,
      /* .QueueSize = */ (Os_PriorityQueueNodeIdxType)OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE1_JOBS
    },
    /* .DriverType            = */ OS_TIMERTYPE_HIGH_RESOLUTION,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore1,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5))  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  },
  /* .Dyn      = */ &OsCfg_Counter_SystemTimer_OsCore1_Dyn,
  /* .HwConfig = */ &OsCfg_Hal_TimerFrt_SystemTimer_OsCore1
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Counter configuration data: SystemTimer_OsCore2 */
CONST(Os_TimerHrtConfigType, OS_CONST) OsCfg_Counter_SystemTimer_OsCore2 =
{
  /* .Counter  = */
  {
    /* .Characteristics       = */
    {
      /* .MaxAllowedValue      = */ OSMAXALLOWEDVALUE_SystemTimer_OsCore2,
      /* .MaxCountingValue     = */ OS_TIMERHRT_GETMAXCOUNTINGVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore2),
      /* .MaxDifferentialValue = */ OS_TIMERHRT_GETMAXDIFFERENTIALVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore2),
      /* .MinCycle             = */ OSMINCYCLE_SystemTimer_OsCore2,
      /* .TicksPerBase         = */ OSTICKSPERBASE_SystemTimer_OsCore2
    },
    /* .JobQueue              = */
    {
      /* .Queue     = */ OsCfg_Counter_SystemTimer_OsCore2_JobQueueNodes_Dyn,
      /* .Dyn       = */ &OsCfg_Counter_SystemTimer_OsCore2_JobQueue_Dyn,
      /* .QueueSize = */ (Os_PriorityQueueNodeIdxType)OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE2_JOBS
    },
    /* .DriverType            = */ OS_TIMERTYPE_HIGH_RESOLUTION,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore2,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5))  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  },
  /* .Dyn      = */ &OsCfg_Counter_SystemTimer_OsCore2_Dyn,
  /* .HwConfig = */ &OsCfg_Hal_TimerFrt_SystemTimer_OsCore2
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Counter configuration data: SystemTimer_OsCore3 */
CONST(Os_TimerHrtConfigType, OS_CONST) OsCfg_Counter_SystemTimer_OsCore3 =
{
  /* .Counter  = */
  {
    /* .Characteristics       = */
    {
      /* .MaxAllowedValue      = */ OSMAXALLOWEDVALUE_SystemTimer_OsCore3,
      /* .MaxCountingValue     = */ OS_TIMERHRT_GETMAXCOUNTINGVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore3),
      /* .MaxDifferentialValue = */ OS_TIMERHRT_GETMAXDIFFERENTIALVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore3),
      /* .MinCycle             = */ OSMINCYCLE_SystemTimer_OsCore3,
      /* .TicksPerBase         = */ OSTICKSPERBASE_SystemTimer_OsCore3
    },
    /* .JobQueue              = */
    {
      /* .Queue     = */ OsCfg_Counter_SystemTimer_OsCore3_JobQueueNodes_Dyn,
      /* .Dyn       = */ &OsCfg_Counter_SystemTimer_OsCore3_JobQueue_Dyn,
      /* .QueueSize = */ (Os_PriorityQueueNodeIdxType)OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE3_JOBS
    },
    /* .DriverType            = */ OS_TIMERTYPE_HIGH_RESOLUTION,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore3,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5))  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  },
  /* .Dyn      = */ &OsCfg_Counter_SystemTimer_OsCore3_Dyn,
  /* .HwConfig = */ &OsCfg_Hal_TimerFrt_SystemTimer_OsCore3
};

#define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Counter configuration data: SystemTimer_OsCore4 */
CONST(Os_TimerHrtConfigType, OS_CONST) OsCfg_Counter_SystemTimer_OsCore4 =
{
  /* .Counter  = */
  {
    /* .Characteristics       = */
    {
      /* .MaxAllowedValue      = */ OSMAXALLOWEDVALUE_SystemTimer_OsCore4,
      /* .MaxCountingValue     = */ OS_TIMERHRT_GETMAXCOUNTINGVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore4),
      /* .MaxDifferentialValue = */ OS_TIMERHRT_GETMAXDIFFERENTIALVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore4),
      /* .MinCycle             = */ OSMINCYCLE_SystemTimer_OsCore4,
      /* .TicksPerBase         = */ OSTICKSPERBASE_SystemTimer_OsCore4
    },
    /* .JobQueue              = */
    {
      /* .Queue     = */ OsCfg_Counter_SystemTimer_OsCore4_JobQueueNodes_Dyn,
      /* .Dyn       = */ &OsCfg_Counter_SystemTimer_OsCore4_JobQueue_Dyn,
      /* .QueueSize = */ (Os_PriorityQueueNodeIdxType)OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE4_JOBS
    },
    /* .DriverType            = */ OS_TIMERTYPE_HIGH_RESOLUTION,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore4,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5))  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  },
  /* .Dyn      = */ &OsCfg_Counter_SystemTimer_OsCore4_Dyn,
  /* .HwConfig = */ &OsCfg_Hal_TimerFrt_SystemTimer_OsCore4
};

#define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Counter configuration data: SystemTimer_OsCore5 */
CONST(Os_TimerHrtConfigType, OS_CONST) OsCfg_Counter_SystemTimer_OsCore5 =
{
  /* .Counter  = */
  {
    /* .Characteristics       = */
    {
      /* .MaxAllowedValue      = */ OSMAXALLOWEDVALUE_SystemTimer_OsCore5,
      /* .MaxCountingValue     = */ OS_TIMERHRT_GETMAXCOUNTINGVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore5),
      /* .MaxDifferentialValue = */ OS_TIMERHRT_GETMAXDIFFERENTIALVALUE(OSMAXALLOWEDVALUE_SystemTimer_OsCore5),
      /* .MinCycle             = */ OSMINCYCLE_SystemTimer_OsCore5,
      /* .TicksPerBase         = */ OSTICKSPERBASE_SystemTimer_OsCore5
    },
    /* .JobQueue              = */
    {
      /* .Queue     = */ OsCfg_Counter_SystemTimer_OsCore5_JobQueueNodes_Dyn,
      /* .Dyn       = */ &OsCfg_Counter_SystemTimer_OsCore5_JobQueue_Dyn,
      /* .QueueSize = */ (Os_PriorityQueueNodeIdxType)OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE5_JOBS
    },
    /* .DriverType            = */ OS_TIMERTYPE_HIGH_RESOLUTION,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore5,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5))  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  },
  /* .Dyn      = */ &OsCfg_Counter_SystemTimer_OsCore5_Dyn,
  /* .HwConfig = */ &OsCfg_Hal_TimerFrt_SystemTimer_OsCore5
};

#define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Object reference table for counters. */
CONSTP2CONST(Os_CounterConfigType, OS_CONST, OS_CONST) OsCfg_CounterRefs[OS_COUNTERID_COUNT + 1u] =            /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
{
  OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
  OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore1),
  OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore2),
  OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore3),
  OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore4),
  OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore5),
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
 *  END OF FILE: Os_Counter_Lcfg.c
 *********************************************************************************************************************/
