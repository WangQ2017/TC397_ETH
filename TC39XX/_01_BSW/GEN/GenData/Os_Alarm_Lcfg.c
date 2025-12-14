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
 *              File: Os_Alarm_Lcfg.c
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_ALARM_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Alarm_Lcfg.h"
#include "Os_Alarm.h"

/* Os kernel module dependencies */
#include "Os_Application_Lcfg.h"
#include "Os_Cfg.h"
#include "Os_Common.h"
#include "Os_Counter_Lcfg.h"
#include "Os_Counter.h"
#include "Os_Task_Lcfg.h"
#include "Os_Timer.h"

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

/*! Dynamic alarm data: Rte_Al_TE2_OsTask_Asw_OsCore0_0_5ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_OsTask_Asw_OsCore0_0_5ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_Core0_Runnable_20 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_20_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_Core0_Runnable_5ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_5ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_EthIf_EthIf_MainFunctionState */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_EthIf_EthIf_MainFunctionState_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_swc_lock_Runnable_2ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_swc_lock_Runnable_2ms_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic alarm data: Rte_Al_TE2_EcuM_EcuM_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_window_core1_Runnable_windows_2ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_window_core1_Runnable_windows_2ms_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic alarm data: Rte_Al_TE3_EcuM_EcuM_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms_Dyn;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic alarm data: Rte_Al_TE4_EcuM_EcuM_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE4_EcuM_EcuM_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms_Dyn;

#define OS_STOP_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic alarm data: Rte_Al_TE5_EcuM_EcuM_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE5_EcuM_EcuM_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms_Dyn;

#define OS_STOP_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic alarm data: Rte_Al_TE6_EcuM_EcuM_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE6_EcuM_EcuM_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms_Dyn;

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


/*! Alarm configuration data: Rte_Al_TE2_OsTask_Asw_OsCore0_0_5ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_OsTask_Asw_OsCore0_0_5ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_OsTask_Asw_OsCore0_0_5ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore0,
  /* .Mask  = */ Rte_Ev_Cyclic2_OsTask_Asw_OsCore0_0_5ms
};


/*! Alarm configuration data: Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_10ms_Core0,
  /* .Mask  = */ Rte_Ev_Cyclic2_OsTask_Bsw_10ms_Core0_0_10ms
};


/*! Alarm configuration data: Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_1ms_Core0
};


/*! Alarm configuration data: Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_5ms_Core0
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_Core0_Runnable_20 */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_20 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_20_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore0,
  /* .Mask  = */ Rte_Ev_Run_Cdd_Core0_Runnable_20
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_Core0_Runnable_5ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_5ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_5ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore0,
  /* .Mask  = */ Rte_Ev_Run_Cdd_Core0_Runnable_5ms
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore0,
  /* .Mask  = */ Rte_Ev_Run_Cdd_nm_Cdd_Nm_Runnable10ms
};


/*! Alarm configuration data: Rte_Al_TE_EthIf_EthIf_MainFunctionState */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_EthIf_EthIf_MainFunctionState =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_EthIf_EthIf_MainFunctionState_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_10ms_Core0,
  /* .Mask  = */ Rte_Ev_Run_EthIf_EthIf_MainFunctionState
};


/*! Alarm configuration data: Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_20ms_Core0
};


/*! Alarm configuration data: Rte_Al_TE_swc_lock_Runnable_2ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_swc_lock_Runnable_2ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_swc_lock_Runnable_2ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_lock_2ms
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Alarm configuration data: Rte_Al_TE2_EcuM_EcuM_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_OsCore1
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore1
};


/*! Alarm configuration data: Rte_Al_TE_window_core1_Runnable_windows_2ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_window_core1_Runnable_windows_2ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_window_core1_Runnable_windows_2ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore1
  },
  /* .Task  = */ &OsCfg_Task_OsTask_window_2ms
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Alarm configuration data: Rte_Al_TE3_EcuM_EcuM_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore2
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_OsCore2
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore2
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore2
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Alarm configuration data: Rte_Al_TE4_EcuM_EcuM_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE4_EcuM_EcuM_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE4_EcuM_EcuM_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore3),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore3
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_OsCore3
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore3),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore3
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore3
};

#define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Alarm configuration data: Rte_Al_TE5_EcuM_EcuM_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE5_EcuM_EcuM_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE5_EcuM_EcuM_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore4),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore4
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_OsCore4
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore4),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore4
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore4
};

#define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*! Alarm configuration data: Rte_Al_TE6_EcuM_EcuM_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE6_EcuM_EcuM_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE6_EcuM_EcuM_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore5),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore5
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Bsw_OsCore5
};


/*! Alarm configuration data: Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore5),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_OsCore0) | OS_APPID2MASK(OsApplication_OsCore1) | OS_APPID2MASK(OsApplication_OsCore2) | OS_APPID2MASK(OsApplication_OsCore3) | OS_APPID2MASK(OsApplication_OsCore4) | OS_APPID2MASK(OsApplication_OsCore5) | OS_APPID2MASK(SystemApplication_OsCore0) | OS_APPID2MASK(SystemApplication_OsCore1) | OS_APPID2MASK(SystemApplication_OsCore2) | OS_APPID2MASK(SystemApplication_OsCore3) | OS_APPID2MASK(SystemApplication_OsCore4) | OS_APPID2MASK(SystemApplication_OsCore5)),  /* PRQA S 0410 */ /* MD_MSR_Dir1.1 */
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_OsCore5
  },
  /* .Task  = */ &OsCfg_Task_OsTask_Asw_OsCore5
};

#define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Object reference table for alarms. */
CONSTP2CONST(Os_AlarmConfigType, OS_CONST, OS_CONST) OsCfg_AlarmRefs[OS_ALARMID_COUNT + 1] =  /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
{
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_OsTask_Asw_OsCore0_0_5ms),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE4_EcuM_EcuM_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE5_EcuM_EcuM_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE6_EcuM_EcuM_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_20),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_Core0_Runnable_5ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE_EthIf_EthIf_MainFunctionState),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_swc_lock_Runnable_2ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_window_core1_Runnable_windows_2ms),
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
 *  END OF FILE: Os_Alarm_Lcfg.c
 *********************************************************************************************************************/
