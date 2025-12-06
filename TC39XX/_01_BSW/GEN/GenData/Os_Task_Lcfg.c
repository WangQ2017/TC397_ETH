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
 *              File: Os_Task_Lcfg.c
 *   Generation Time: 2025-09-02 11:14:44
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_TASK_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Task_Lcfg.h"
#include "Os_Task.h"

/* Os kernel module dependencies */
#include "Os_AccessCheck_Lcfg.h"
#include "Os_Application_Lcfg.h"
#include "Os_Common.h"
#include "Os_Core_Lcfg.h"
#include "Os_Core.h"
#include "Os_Error.h"
#include "Os_Ioc.h"
#include "Os_Lcfg.h"
#include "Os_MemoryProtection_Lcfg.h"
#include "Os_Scheduler_Types.h"
#include "Os_Stack_Lcfg.h"
#include "Os_TaskInt.h"
#include "Os_Thread.h"
#include "Os_TimingProtection_Lcfg.h"
#include "Os_Trace_Lcfg.h"

/* Os hal dependencies */
#include "Os_Hal_Context_Lcfg.h"


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

/*! Dynamic task data: Default_Init_Task */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Dyn;

/*! Dynamic task data: Default_Init_Task_Trusted */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Trusted_Dyn;

/*! Dynamic task data: IdleTask_OsCore0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore0_Dyn;

/*! Dynamic task data: OsTask_Asw_OsCore0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Asw_OsCore0_Dyn;

/*! Dynamic task data: OsTask_Bsw_OsCore0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Bsw_OsCore0_Dyn;

/*! Dynamic task data: OsTask_Init_OsCore0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Init_OsCore0_Dyn;

/*! Dynamic task data: OsTask_lock_2ms */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_lock_2ms_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic task data: Default_Init_Task_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core1_Dyn;

/*! Dynamic task data: Default_Init_Task_Core1_Trusted */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core1_Trusted_Dyn;

/*! Dynamic task data: IdleTask_OsCore1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore1_Dyn;

/*! Dynamic task data: OsTask_Asw_OsCore1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Asw_OsCore1_Dyn;

/*! Dynamic task data: OsTask_Bsw_OsCore1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Bsw_OsCore1_Dyn;

/*! Dynamic task data: OsTask_Init_OsCore1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Init_OsCore1_Dyn;

/*! Dynamic task data: OsTask_window_2ms */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_window_2ms_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic task data: Default_Init_Task_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core2_Dyn;

/*! Dynamic task data: Default_Init_Task_Core2_Trusted */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core2_Trusted_Dyn;

/*! Dynamic task data: IdleTask_OsCore2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore2_Dyn;

/*! Dynamic task data: OsTask_Asw_OsCore2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Asw_OsCore2_Dyn;

/*! Dynamic task data: OsTask_Bsw_OsCore2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Bsw_OsCore2_Dyn;

/*! Dynamic task data: OsTask_Init_OsCore2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Init_OsCore2_Dyn;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic task data: Default_Init_Task_Core3 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core3_Dyn;

/*! Dynamic task data: Default_Init_Task_Core3_Trusted */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core3_Trusted_Dyn;

/*! Dynamic task data: IdleTask_OsCore3 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore3_Dyn;

/*! Dynamic task data: OsTask_Asw_OsCore3 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Asw_OsCore3_Dyn;

/*! Dynamic task data: OsTask_Bsw_OsCore3 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Bsw_OsCore3_Dyn;

/*! Dynamic task data: OsTask_Init_OsCore3 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Init_OsCore3_Dyn;

#define OS_STOP_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic task data: Default_Init_Task_Core4 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core4_Dyn;

/*! Dynamic task data: Default_Init_Task_Core4_Trusted */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core4_Trusted_Dyn;

/*! Dynamic task data: IdleTask_OsCore4 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore4_Dyn;

/*! Dynamic task data: OsTask_Asw_OsCore4 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Asw_OsCore4_Dyn;

/*! Dynamic task data: OsTask_Bsw_OsCore4 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Bsw_OsCore4_Dyn;

/*! Dynamic task data: OsTask_Init_OsCore4 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Init_OsCore4_Dyn;

#define OS_STOP_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic task data: Default_Init_Task_Core6 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core6_Dyn;

/*! Dynamic task data: Default_Init_Task_Core6_Trusted */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Default_Init_Task_Core6_Trusted_Dyn;

/*! Dynamic task data: IdleTask_OsCore5 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore5_Dyn;

/*! Dynamic task data: OsTask_Asw_OsCore5 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Asw_OsCore5_Dyn;

/*! Dynamic task data: OsTask_Bsw_OsCore5 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Bsw_OsCore5_Dyn;

/*! Dynamic task data: OsTask_Init_OsCore5 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_OsTask_Init_OsCore5_Dyn;

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


/*! Task configuration data: Default_Init_Task */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio55,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)0uL,
  /* .TaskId                 = */ Default_Init_Task,
  /* .RunningPriority        = */ (Os_TaskPrioType)0uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: Default_Init_Task_Trusted */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Trusted =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Trusted,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Trusted_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio50,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Trusted_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)5uL,
  /* .TaskId                 = */ Default_Init_Task_Trusted,
  /* .RunningPriority        = */ (Os_TaskPrioType)5uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: IdleTask_OsCore0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore0 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)21uL,
  /* .TaskId                 = */ IdleTask_OsCore0,
  /* .RunningPriority        = */ (Os_TaskPrioType)21uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_ANY,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Asw_OsCore0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Asw_OsCore0 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsTask_Asw_OsCore0,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Asw_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)15uL,
  /* .TaskId                 = */ OsTask_Asw_OsCore0,
  /* .RunningPriority        = */ (Os_TaskPrioType)15uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)TRUE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Bsw_OsCore0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Bsw_OsCore0 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio30,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Bsw_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)14uL,
  /* .TaskId                 = */ OsTask_Bsw_OsCore0,
  /* .RunningPriority        = */ (Os_TaskPrioType)14uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)3uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Init_OsCore0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Init_OsCore0 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Init_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Init_OsCore0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio48,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Init_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)7uL,
  /* .TaskId                 = */ OsTask_Init_OsCore0,
  /* .RunningPriority        = */ (Os_TaskPrioType)7uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_lock_2ms */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_lock_2ms =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_lock_2ms,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_lock_2ms_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio40,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_lock_2ms_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)9uL,
  /* .TaskId                 = */ OsTask_lock_2ms,
  /* .RunningPriority        = */ (Os_TaskPrioType)9uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)3uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Task configuration data: Default_Init_Task_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core1 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio54,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)1uL,
  /* .TaskId                 = */ Default_Init_Task_Core1,
  /* .RunningPriority        = */ (Os_TaskPrioType)1uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: Default_Init_Task_Core1_Trusted */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core1_Trusted =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core1_Trusted,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core1_Trusted_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio49,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core1_Trusted_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)6uL,
  /* .TaskId                 = */ Default_Init_Task_Core1_Trusted,
  /* .RunningPriority        = */ (Os_TaskPrioType)6uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: IdleTask_OsCore1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore1 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)21uL,
  /* .TaskId                 = */ IdleTask_OsCore1,
  /* .RunningPriority        = */ (Os_TaskPrioType)21uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_ANY,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Asw_OsCore1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Asw_OsCore1 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio14,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Asw_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)16uL,
  /* .TaskId                 = */ OsTask_Asw_OsCore1,
  /* .RunningPriority        = */ (Os_TaskPrioType)16uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Bsw_OsCore1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Bsw_OsCore1 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio34,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Bsw_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)10uL,
  /* .TaskId                 = */ OsTask_Bsw_OsCore1,
  /* .RunningPriority        = */ (Os_TaskPrioType)10uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Init_OsCore1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Init_OsCore1 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Init_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Init_OsCore1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio48,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Init_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)7uL,
  /* .TaskId                 = */ OsTask_Init_OsCore1,
  /* .RunningPriority        = */ (Os_TaskPrioType)7uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_window_2ms */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_window_2ms =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_window_2ms,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_window_2ms_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio41,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_window_2ms_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)8uL,
  /* .TaskId                 = */ OsTask_window_2ms,
  /* .RunningPriority        = */ (Os_TaskPrioType)8uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)3uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Task configuration data: Default_Init_Task_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core2 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio53,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)2uL,
  /* .TaskId                 = */ Default_Init_Task_Core2,
  /* .RunningPriority        = */ (Os_TaskPrioType)2uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: Default_Init_Task_Core2_Trusted */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core2_Trusted =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core2_Trusted,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core2_Trusted_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio49,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core2_Trusted_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)6uL,
  /* .TaskId                 = */ Default_Init_Task_Core2_Trusted,
  /* .RunningPriority        = */ (Os_TaskPrioType)6uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: IdleTask_OsCore2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore2 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)21uL,
  /* .TaskId                 = */ IdleTask_OsCore2,
  /* .RunningPriority        = */ (Os_TaskPrioType)21uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_ANY,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Asw_OsCore2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Asw_OsCore2 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio13,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Asw_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)17uL,
  /* .TaskId                 = */ OsTask_Asw_OsCore2,
  /* .RunningPriority        = */ (Os_TaskPrioType)17uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Bsw_OsCore2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Bsw_OsCore2 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio33,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Bsw_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)11uL,
  /* .TaskId                 = */ OsTask_Bsw_OsCore2,
  /* .RunningPriority        = */ (Os_TaskPrioType)11uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Init_OsCore2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Init_OsCore2 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Init_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Init_OsCore2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio48,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Init_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)7uL,
  /* .TaskId                 = */ OsTask_Init_OsCore2,
  /* .RunningPriority        = */ (Os_TaskPrioType)7uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Task configuration data: Default_Init_Task_Core3 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core3 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core3,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core3_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Task_Prio52,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core3_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)3uL,
  /* .TaskId                 = */ Default_Init_Task_Core3,
  /* .RunningPriority        = */ (Os_TaskPrioType)3uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: Default_Init_Task_Core3_Trusted */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core3_Trusted =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core3_Trusted,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core3_Trusted_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Task_Prio49,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core3_Trusted_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)6uL,
  /* .TaskId                 = */ Default_Init_Task_Core3_Trusted,
  /* .RunningPriority        = */ (Os_TaskPrioType)6uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: IdleTask_OsCore3 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore3 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore3,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore3_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore3_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)21uL,
  /* .TaskId                 = */ IdleTask_OsCore3,
  /* .RunningPriority        = */ (Os_TaskPrioType)21uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_ANY,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Asw_OsCore3 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Asw_OsCore3 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore3,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore3_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Task_Prio12,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Asw_OsCore3_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)18uL,
  /* .TaskId                 = */ OsTask_Asw_OsCore3,
  /* .RunningPriority        = */ (Os_TaskPrioType)18uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Bsw_OsCore3 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Bsw_OsCore3 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore3,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore3_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Task_Prio32,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Bsw_OsCore3_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)12uL,
  /* .TaskId                 = */ OsTask_Bsw_OsCore3,
  /* .RunningPriority        = */ (Os_TaskPrioType)12uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Init_OsCore3 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Init_OsCore3 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Init_OsCore3,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Init_OsCore3_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Task_Prio48,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Init_OsCore3_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)7uL,
  /* .TaskId                 = */ OsTask_Init_OsCore3,
  /* .RunningPriority        = */ (Os_TaskPrioType)7uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Task configuration data: Default_Init_Task_Core4 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core4 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core4,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core4_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Task_Prio51,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core4_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)4uL,
  /* .TaskId                 = */ Default_Init_Task_Core4,
  /* .RunningPriority        = */ (Os_TaskPrioType)4uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: Default_Init_Task_Core4_Trusted */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core4_Trusted =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core4_Trusted,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core4_Trusted_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Task_Prio49,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core4_Trusted_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)6uL,
  /* .TaskId                 = */ Default_Init_Task_Core4_Trusted,
  /* .RunningPriority        = */ (Os_TaskPrioType)6uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: IdleTask_OsCore4 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore4 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore4,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore4_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore4_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)21uL,
  /* .TaskId                 = */ IdleTask_OsCore4,
  /* .RunningPriority        = */ (Os_TaskPrioType)21uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_ANY,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Asw_OsCore4 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Asw_OsCore4 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore4,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore4_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Task_Prio11,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Asw_OsCore4_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)19uL,
  /* .TaskId                 = */ OsTask_Asw_OsCore4,
  /* .RunningPriority        = */ (Os_TaskPrioType)19uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Bsw_OsCore4 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Bsw_OsCore4 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore4,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore4_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Task_Prio31,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Bsw_OsCore4_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)13uL,
  /* .TaskId                 = */ OsTask_Bsw_OsCore4,
  /* .RunningPriority        = */ (Os_TaskPrioType)13uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Init_OsCore4 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Init_OsCore4 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Init_OsCore4,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Init_OsCore4_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Task_Prio48,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Init_OsCore4_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)7uL,
  /* .TaskId                 = */ OsTask_Init_OsCore4,
  /* .RunningPriority        = */ (Os_TaskPrioType)7uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Task configuration data: Default_Init_Task_Core6 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core6 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core6,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core6_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Task_Prio50,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core6_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)5uL,
  /* .TaskId                 = */ Default_Init_Task_Core6,
  /* .RunningPriority        = */ (Os_TaskPrioType)5uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: Default_Init_Task_Core6_Trusted */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Default_Init_Task_Core6_Trusted =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Default_Init_Task_Core6_Trusted,
    /* .Context               = */ &OsCfg_Hal_Context_Default_Init_Task_Core6_Trusted_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Task_Prio49,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Default_Init_Task_Core6_Trusted_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)6uL,
  /* .TaskId                 = */ Default_Init_Task_Core6_Trusted,
  /* .RunningPriority        = */ (Os_TaskPrioType)6uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OSDEFAULTAPPMODE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: IdleTask_OsCore5 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore5 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore5,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore5_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore5_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)21uL,
  /* .TaskId                 = */ IdleTask_OsCore5,
  /* .RunningPriority        = */ (Os_TaskPrioType)21uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_ANY,
    /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Asw_OsCore5 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Asw_OsCore5 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore5,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Asw_OsCore5_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Task_Prio10,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Asw_OsCore5_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)20uL,
  /* .TaskId                 = */ OsTask_Asw_OsCore5,
  /* .RunningPriority        = */ (Os_TaskPrioType)20uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Bsw_OsCore5 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Bsw_OsCore5 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore5,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Bsw_OsCore5_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Task_Prio30,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Bsw_OsCore5_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)14uL,
  /* .TaskId                 = */ OsTask_Bsw_OsCore5,
  /* .RunningPriority        = */ (Os_TaskPrioType)14uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)100uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};


/*! Task configuration data: OsTask_Init_OsCore5 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_OsTask_Init_OsCore5 =
{
  /* .Thread                 = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_OsTask_Init_OsCore5,
    /* .Context               = */ &OsCfg_Hal_Context_OsTask_Init_OsCore5_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Task_Prio48,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_OsTask_Init_OsCore5_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority           = */ (Os_TaskPrioType)7uL,
  /* .TaskId                 = */ OsTask_Init_OsCore5,
  /* .RunningPriority        = */ (Os_TaskPrioType)7uL,
  /* .MaxActivations         = */ (Os_ActivationCntType)1uL,
  /* .AutostartModes         = */ OS_APPMODE_NONE,
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
  /* .NumSchEventsRoundRobin = */ 0uL,
  /* .RoundRobinEnabled      = */ FALSE,
  /* .IsExtended             = */ (boolean)FALSE,
  /* .StackSharing           = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Object reference table for tasks. */
CONSTP2CONST(Os_TaskConfigType, OS_CONST, OS_CONST) OsCfg_TaskRefs[OS_TASKID_COUNT + 1] =   /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
{
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core1_Trusted),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core2_Trusted),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core3),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core3_Trusted),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core4),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core4_Trusted),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core6),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Core6_Trusted),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Default_Init_Task_Trusted),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore3),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore4),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore5),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Asw_OsCore0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Asw_OsCore1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Asw_OsCore2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Asw_OsCore3),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Asw_OsCore4),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Asw_OsCore5),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Bsw_OsCore0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Bsw_OsCore1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Bsw_OsCore2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Bsw_OsCore3),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Bsw_OsCore4),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Bsw_OsCore5),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Init_OsCore0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Init_OsCore1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Init_OsCore2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Init_OsCore3),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Init_OsCore4),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_Init_OsCore5),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_lock_2ms),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_OsTask_window_2ms),
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
 *  END OF FILE: Os_Task_Lcfg.c
 *********************************************************************************************************************/
