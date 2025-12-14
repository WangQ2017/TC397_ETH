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
 *             File:  Rte.c
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  RTE implementation file
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0857 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define RTE_CORE
#include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_Dir1.1, MD_Rte_Os */
#include "Rte_Type.h"
#include "Rte_Main.h"

#include "Rte_BswM.h"
#include "Rte_Cdd_Core0.h"
#include "Rte_Cdd_Core1.h"
#include "Rte_Cdd_Core2.h"
#include "Rte_Cdd_Core3.h"
#include "Rte_Cdd_Core4.h"
#include "Rte_Cdd_Core5.h"
#include "Rte_Cdd_Nm.h"
#include "Rte_ComM.h"
#include "Rte_Det.h"
#include "Rte_EcuM.h"
#include "Rte_Os_OsCore0_swc.h"
#include "Rte_Os_OsCore1_swc.h"
#include "Rte_Os_OsCore2_swc.h"
#include "Rte_Os_OsCore3_swc.h"
#include "Rte_Os_OsCore4_swc.h"
#include "Rte_Os_OsCore5_swc.h"
#include "Rte_StbM.h"
#include "Rte_lock_control.h"
#include "Rte_window_core1.h"
#include "SchM_BswM.h"
#include "SchM_Com.h"
#include "SchM_ComM.h"
#include "SchM_Det.h"
#include "SchM_Dio.h"
#include "SchM_EcuM.h"
#include "SchM_EthIf.h"
#include "SchM_EthSM.h"
#include "SchM_EthTSyn.h"
#include "SchM_EthTrcv_30_Tja1100.h"
#include "SchM_Eth_30_Tc3xx.h"
#include "SchM_Irq.h"
#include "SchM_McalLib.h"
#include "SchM_Mcu.h"
#include "SchM_Nm.h"
#include "SchM_PduR.h"
#include "SchM_Port.h"
#include "SchM_SoAd.h"
#include "SchM_StbM.h"
#include "SchM_TcpIp.h"
#include "SchM_Uart.h"
#include "SchM_UdpNm.h"

#include "Rte_Hook.h"

#include "Rte_Cbk.h"

/* AUTOSAR 3.x compatibility */
#if !defined (RTE_LOCAL)
# define RTE_LOCAL static
#endif


/**********************************************************************************************************************
 * API for enable / disable interrupts global
 *********************************************************************************************************************/

#if defined(osDisableGlobalKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_DisableAllInterrupts() osDisableGlobalKM()   /* MICROSAR OS */
#else
# define Rte_DisableAllInterrupts() DisableAllInterrupts()   /* AUTOSAR OS */
#endif

#if defined(osEnableGlobalKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_EnableAllInterrupts() osEnableGlobalKM()   /* MICROSAR OS */
#else
# define Rte_EnableAllInterrupts() EnableAllInterrupts()   /* AUTOSAR OS */
#endif

/**********************************************************************************************************************
 * API for enable / disable interrupts up to the systemLevel
 *********************************************************************************************************************/

#if defined(osDisableLevelKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_DisableOSInterrupts() osDisableLevelKM()   /* MICROSAR OS */
#else
# define Rte_DisableOSInterrupts() SuspendOSInterrupts()   /* AUTOSAR OS */
#endif

#if defined(osEnableLevelKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_EnableOSInterrupts() osEnableLevelKM()   /* MICROSAR OS */
#else
# define Rte_EnableOSInterrupts() ResumeOSInterrupts()   /* AUTOSAR OS */
#endif

/**********************************************************************************************************************
 * Rte Init State Variable
 *********************************************************************************************************************/

#define RTE_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState = RTE_STATE_UNINIT; /* PRQA S 3408 */ /* MD_Rte_3408 */
volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_StartTiming_InitState = RTE_STATE_UNINIT; /* PRQA S 0850, 3408, 1514 */ /* MD_MSR_MacroArgumentEmpty, MD_Rte_3408, MD_Rte_1514 */

#define RTE_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_1 = RTE_STATE_UNINIT; /* PRQA S 3408 */ /* MD_Rte_3408 */

#define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_2 = RTE_STATE_UNINIT; /* PRQA S 3408 */ /* MD_Rte_3408 */

#define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_3 = RTE_STATE_UNINIT; /* PRQA S 3408 */ /* MD_Rte_3408 */

#define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_4 = RTE_STATE_UNINIT; /* PRQA S 3408 */ /* MD_Rte_3408 */

#define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_5 = RTE_STATE_UNINIT; /* PRQA S 3408 */ /* MD_Rte_3408 */

#define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 * Defines for Rte_ComSendSignalProxy
 *********************************************************************************************************************/
#define RTE_COM_SENDSIGNALPROXY_NOCHANGE       (0U)
#define RTE_COM_SENDSIGNALPROXY_SEND           (1U)
#define RTE_COM_SENDSIGNALPROXY_INVALIDATE     (2U)



#define RTE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Helper functions for mode management
 *********************************************************************************************************************/
FUNC(uint8, RTE_CODE) Rte_GetInternalModeIndex_BswM_ESH_Mode(BswM_ESH_Mode mode) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 ret;

  if (mode == 0U)
  {
    ret = 3U;
  }
  else if (mode == 1U)
  {
    ret = 1U;
  }
  else if (mode == 2U)
  {
    ret = 0U;
  }
  else if (mode == 3U)
  {
    ret = 4U;
  }
  else if (mode == 4U)
  {
    ret = 2U;
  }
  else
  {
    ret = 5U;
  }

  return ret;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * Timer handling
 *********************************************************************************************************************/

#if defined OS_US2TICKS_SystemTimer_OsCore0
# define RTE_USEC_SystemTimer_OsCore0 OS_US2TICKS_SystemTimer_OsCore0
#else
# define RTE_USEC_SystemTimer_OsCore0(val) ((TickType)RTE_CONST_USEC_SystemTimer_OsCore0_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_MS2TICKS_SystemTimer_OsCore0
# define RTE_MSEC_SystemTimer_OsCore0 OS_MS2TICKS_SystemTimer_OsCore0
#else
# define RTE_MSEC_SystemTimer_OsCore0(val) ((TickType)RTE_CONST_MSEC_SystemTimer_OsCore0_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_SEC2TICKS_SystemTimer_OsCore0
# define RTE_SEC_SystemTimer_OsCore0 OS_SEC2TICKS_SystemTimer_OsCore0
#else
# define RTE_SEC_SystemTimer_OsCore0(val)  ((TickType)RTE_CONST_SEC_SystemTimer_OsCore0_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_US2TICKS_SystemTimer_OsCore1
# define RTE_USEC_SystemTimer_OsCore1 OS_US2TICKS_SystemTimer_OsCore1
#else
# define RTE_USEC_SystemTimer_OsCore1(val) ((TickType)RTE_CONST_USEC_SystemTimer_OsCore1_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_MS2TICKS_SystemTimer_OsCore1
# define RTE_MSEC_SystemTimer_OsCore1 OS_MS2TICKS_SystemTimer_OsCore1
#else
# define RTE_MSEC_SystemTimer_OsCore1(val) ((TickType)RTE_CONST_MSEC_SystemTimer_OsCore1_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_SEC2TICKS_SystemTimer_OsCore1
# define RTE_SEC_SystemTimer_OsCore1 OS_SEC2TICKS_SystemTimer_OsCore1
#else
# define RTE_SEC_SystemTimer_OsCore1(val)  ((TickType)RTE_CONST_SEC_SystemTimer_OsCore1_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_US2TICKS_SystemTimer_OsCore2
# define RTE_USEC_SystemTimer_OsCore2 OS_US2TICKS_SystemTimer_OsCore2
#else
# define RTE_USEC_SystemTimer_OsCore2(val) ((TickType)RTE_CONST_USEC_SystemTimer_OsCore2_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_MS2TICKS_SystemTimer_OsCore2
# define RTE_MSEC_SystemTimer_OsCore2 OS_MS2TICKS_SystemTimer_OsCore2
#else
# define RTE_MSEC_SystemTimer_OsCore2(val) ((TickType)RTE_CONST_MSEC_SystemTimer_OsCore2_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_SEC2TICKS_SystemTimer_OsCore2
# define RTE_SEC_SystemTimer_OsCore2 OS_SEC2TICKS_SystemTimer_OsCore2
#else
# define RTE_SEC_SystemTimer_OsCore2(val)  ((TickType)RTE_CONST_SEC_SystemTimer_OsCore2_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_US2TICKS_SystemTimer_OsCore3
# define RTE_USEC_SystemTimer_OsCore3 OS_US2TICKS_SystemTimer_OsCore3
#else
# define RTE_USEC_SystemTimer_OsCore3(val) ((TickType)RTE_CONST_USEC_SystemTimer_OsCore3_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_MS2TICKS_SystemTimer_OsCore3
# define RTE_MSEC_SystemTimer_OsCore3 OS_MS2TICKS_SystemTimer_OsCore3
#else
# define RTE_MSEC_SystemTimer_OsCore3(val) ((TickType)RTE_CONST_MSEC_SystemTimer_OsCore3_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_SEC2TICKS_SystemTimer_OsCore3
# define RTE_SEC_SystemTimer_OsCore3 OS_SEC2TICKS_SystemTimer_OsCore3
#else
# define RTE_SEC_SystemTimer_OsCore3(val)  ((TickType)RTE_CONST_SEC_SystemTimer_OsCore3_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_US2TICKS_SystemTimer_OsCore4
# define RTE_USEC_SystemTimer_OsCore4 OS_US2TICKS_SystemTimer_OsCore4
#else
# define RTE_USEC_SystemTimer_OsCore4(val) ((TickType)RTE_CONST_USEC_SystemTimer_OsCore4_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_MS2TICKS_SystemTimer_OsCore4
# define RTE_MSEC_SystemTimer_OsCore4 OS_MS2TICKS_SystemTimer_OsCore4
#else
# define RTE_MSEC_SystemTimer_OsCore4(val) ((TickType)RTE_CONST_MSEC_SystemTimer_OsCore4_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_SEC2TICKS_SystemTimer_OsCore4
# define RTE_SEC_SystemTimer_OsCore4 OS_SEC2TICKS_SystemTimer_OsCore4
#else
# define RTE_SEC_SystemTimer_OsCore4(val)  ((TickType)RTE_CONST_SEC_SystemTimer_OsCore4_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_US2TICKS_SystemTimer_OsCore5
# define RTE_USEC_SystemTimer_OsCore5 OS_US2TICKS_SystemTimer_OsCore5
#else
# define RTE_USEC_SystemTimer_OsCore5(val) ((TickType)RTE_CONST_USEC_SystemTimer_OsCore5_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_MS2TICKS_SystemTimer_OsCore5
# define RTE_MSEC_SystemTimer_OsCore5 OS_MS2TICKS_SystemTimer_OsCore5
#else
# define RTE_MSEC_SystemTimer_OsCore5(val) ((TickType)RTE_CONST_MSEC_SystemTimer_OsCore5_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#if defined OS_SEC2TICKS_SystemTimer_OsCore5
# define RTE_SEC_SystemTimer_OsCore5 OS_SEC2TICKS_SystemTimer_OsCore5
#else
# define RTE_SEC_SystemTimer_OsCore5(val)  ((TickType)RTE_CONST_SEC_SystemTimer_OsCore5_##val) /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#endif

#define RTE_CONST_MSEC_SystemTimer_OsCore0_0 (0UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore1_0 (0UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore2_0 (0UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore3_0 (0UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore4_0 (0UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore5_0 (0UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore0_1 (100000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore0_10 (1000000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore1_10 (1000000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore2_10 (1000000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore3_10 (1000000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore4_10 (1000000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore5_10 (1000000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore0_2 (200000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore1_2 (200000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore0_20 (2000000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore0_25 (2500000UL)
#define RTE_CONST_MSEC_SystemTimer_OsCore0_5 (500000UL)


/**********************************************************************************************************************
 * Internal definitions
 *********************************************************************************************************************/

#define RTE_TASK_TIMEOUT_EVENT_MASK   ((EventMaskType)0x01)
#define RTE_TASK_WAITPOINT_EVENT_MASK ((EventMaskType)0x02)

/**********************************************************************************************************************
 * RTE life cycle API
 *********************************************************************************************************************/

#define RTE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, RTE_CODE) SchM_Init(void)
{
  uint32 id = GetCoreID();
  if (id == OS_CORE_ID_0) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the tasks */
    (void)ActivateTask(OsTask_Bsw_10ms_Core0); /* PRQA S 3417 */ /* MD_Rte_Os */

    /* activate the alarms used for TimingEvents */
    (void)SetRelAlarm(Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(1)); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(5)); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(10)); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_EthIf_EthIf_MainFunctionState, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(25)); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(20)); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState = RTE_STATE_SCHM_INIT;
  }
  if (id == OS_CORE_ID_1) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the alarms used for TimingEvents */
    (void)SetRelAlarm(Rte_Al_TE2_EcuM_EcuM_MainFunction, RTE_MSEC_SystemTimer_OsCore1(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore1(10)); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_1 = RTE_STATE_SCHM_INIT;
  }
  if (id == OS_CORE_ID_2) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the alarms used for TimingEvents */
    (void)SetRelAlarm(Rte_Al_TE3_EcuM_EcuM_MainFunction, RTE_MSEC_SystemTimer_OsCore2(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore2(10)); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_2 = RTE_STATE_SCHM_INIT;
  }
  if (id == OS_CORE_ID_3) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the alarms used for TimingEvents */
    (void)SetRelAlarm(Rte_Al_TE4_EcuM_EcuM_MainFunction, RTE_MSEC_SystemTimer_OsCore3(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore3(10)); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_3 = RTE_STATE_SCHM_INIT;
  }
  if (id == OS_CORE_ID_4) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the alarms used for TimingEvents */
    (void)SetRelAlarm(Rte_Al_TE5_EcuM_EcuM_MainFunction, RTE_MSEC_SystemTimer_OsCore4(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore4(10)); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_4 = RTE_STATE_SCHM_INIT;
  }
  if (id == OS_CORE_ID_5) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the alarms used for TimingEvents */
    (void)SetRelAlarm(Rte_Al_TE6_EcuM_EcuM_MainFunction, RTE_MSEC_SystemTimer_OsCore5(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore5(10)); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_5 = RTE_STATE_SCHM_INIT;
  }
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void)
{
  uint32 id = GetCoreID();
  if (id == OS_CORE_ID_0) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the tasks */
    (void)ActivateTask(OsTask_Asw_OsCore0); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)ActivateTask(OsTask_Init_OsCore0); /* PRQA S 3417 */ /* MD_Rte_Os */

    /* activate the alarms used for TimingEvents */
    (void)SetRelAlarm(Rte_Al_TE_window_core1_Runnable_windows_2ms, RTE_MSEC_SystemTimer_OsCore1(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore1(2)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_swc_lock_Runnable_2ms, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(2)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_Core0_Runnable_20, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(20)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_Core0_Runnable_5ms, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(5)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms, RTE_MSEC_SystemTimer_OsCore0(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore0(10)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms, RTE_MSEC_SystemTimer_OsCore1(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore1(10)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms, RTE_MSEC_SystemTimer_OsCore2(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore2(10)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms, RTE_MSEC_SystemTimer_OsCore3(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore3(10)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms, RTE_MSEC_SystemTimer_OsCore4(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore4(10)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */
    (void)SetRelAlarm(Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms, RTE_MSEC_SystemTimer_OsCore5(0) + (TickType)1, RTE_MSEC_SystemTimer_OsCore5(10)); /* PRQA S 3417, 1840 */ /* MD_Rte_Os, MD_Rte_Os */

    Rte_StartTiming_InitState = RTE_STATE_INIT;
    Rte_InitState = RTE_STATE_INIT;

  }
  if (id == OS_CORE_ID_1) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the tasks */
    (void)ActivateTask(OsTask_Init_OsCore1); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_1 = RTE_STATE_INIT;

  }
  if (id == OS_CORE_ID_2) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the tasks */
    (void)ActivateTask(OsTask_Init_OsCore2); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_2 = RTE_STATE_INIT;

  }
  if (id == OS_CORE_ID_3) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the tasks */
    (void)ActivateTask(OsTask_Init_OsCore3); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_3 = RTE_STATE_INIT;

  }
  if (id == OS_CORE_ID_4) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the tasks */
    (void)ActivateTask(OsTask_Init_OsCore4); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_4 = RTE_STATE_INIT;

  }
  if (id == OS_CORE_ID_5) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* activate the tasks */
    (void)ActivateTask(OsTask_Init_OsCore5); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_5 = RTE_STATE_INIT;

  }
  return RTE_E_OK;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void)
{
  uint32 id = GetCoreID();
  if (id == OS_CORE_ID_0) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    Rte_StartTiming_InitState = RTE_STATE_UNINIT;
    /* deactivate alarms */
    (void)CancelAlarm(Rte_Al_TE_Cdd_Core0_Runnable_20); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Cdd_Core0_Runnable_5ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_swc_lock_Runnable_2ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_window_core1_Runnable_windows_2ms); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState = RTE_STATE_SCHM_INIT;

  }
  if (id == OS_CORE_ID_1) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    Rte_InitState_1 = RTE_STATE_SCHM_INIT;

  }
  if (id == OS_CORE_ID_2) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    Rte_InitState_2 = RTE_STATE_SCHM_INIT;

  }
  if (id == OS_CORE_ID_3) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    Rte_InitState_3 = RTE_STATE_SCHM_INIT;

  }
  if (id == OS_CORE_ID_4) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    Rte_InitState_4 = RTE_STATE_SCHM_INIT;

  }
  if (id == OS_CORE_ID_5) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    Rte_InitState_5 = RTE_STATE_SCHM_INIT;

  }
  return RTE_E_OK;
}

FUNC(void, RTE_CODE) SchM_Deinit(void)
{
  uint32 id = GetCoreID();
  if (id == OS_CORE_ID_0) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* deactivate alarms */
    (void)CancelAlarm(Rte_Al_TE2_OsTask_Bsw_10ms_Core0_0_10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_EthIf_EthIf_MainFunctionState); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE2_OsTask_Bsw_1ms_Core0_0_1ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)CancelAlarm(Rte_Al_TE2_OsTask_Bsw_5ms_Core0_0_5ms); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState = RTE_STATE_UNINIT;
  }
  if (id == OS_CORE_ID_1) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* deactivate alarms */
    (void)CancelAlarm(Rte_Al_TE2_EcuM_EcuM_MainFunction); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_1 = RTE_STATE_UNINIT;
  }
  if (id == OS_CORE_ID_2) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* deactivate alarms */
    (void)CancelAlarm(Rte_Al_TE3_EcuM_EcuM_MainFunction); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_2 = RTE_STATE_UNINIT;
  }
  if (id == OS_CORE_ID_3) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* deactivate alarms */
    (void)CancelAlarm(Rte_Al_TE4_EcuM_EcuM_MainFunction); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_3 = RTE_STATE_UNINIT;
  }
  if (id == OS_CORE_ID_4) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* deactivate alarms */
    (void)CancelAlarm(Rte_Al_TE5_EcuM_EcuM_MainFunction); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_4 = RTE_STATE_UNINIT;
  }
  if (id == OS_CORE_ID_5) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    /* deactivate alarms */
    (void)CancelAlarm(Rte_Al_TE6_EcuM_EcuM_MainFunction); /* PRQA S 3417 */ /* MD_Rte_Os */

    Rte_InitState_5 = RTE_STATE_UNINIT;
  }
}

FUNC(void, RTE_CODE) Rte_InitMemory(void)
{
  uint32 id;
  id = GetCoreID();
  if (id == OS_CORE_ID_0) /* PRQA S 1843 */ /* MD_Rte_Os */
  {
    Rte_InitState = RTE_STATE_UNINIT;
    Rte_StartTiming_InitState = RTE_STATE_UNINIT;
    Rte_InitMemory_OsApplication_OsCore0();
  }
  else if (id == OS_CORE_ID_1) /* PRQA S 2004, 1843 */ /* MD_MSR_EmptyClause, MD_Rte_Os */
  {
    Rte_InitState_1 = RTE_STATE_UNINIT;
    Rte_InitMemory_OsApplication_OsCore1();
  }
  else if (id == OS_CORE_ID_2) /* PRQA S 2004, 1843 */ /* MD_MSR_EmptyClause, MD_Rte_Os */
  {
    Rte_InitState_2 = RTE_STATE_UNINIT;
    Rte_InitMemory_OsApplication_OsCore2();
  }
  else if (id == OS_CORE_ID_3) /* PRQA S 2004, 1843 */ /* MD_MSR_EmptyClause, MD_Rte_Os */
  {
    Rte_InitState_3 = RTE_STATE_UNINIT;
    Rte_InitMemory_OsApplication_OsCore3();
  }
  else if (id == OS_CORE_ID_4) /* PRQA S 2004, 1843 */ /* MD_MSR_EmptyClause, MD_Rte_Os */
  {
    Rte_InitState_4 = RTE_STATE_UNINIT;
    Rte_InitMemory_OsApplication_OsCore4();
  }
  else if (id == OS_CORE_ID_5) /* PRQA S 2004, 1843 */ /* MD_MSR_EmptyClause, MD_Rte_Os */
  {
    Rte_InitState_5 = RTE_STATE_UNINIT;
    Rte_InitMemory_OsApplication_OsCore5();
  }
}


/**********************************************************************************************************************
 * Exclusive area access
 *********************************************************************************************************************/

FUNC(void, RTE_CODE) SchM_Enter_Mcu_AtomAgcReg(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  SuspendAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Exit_Mcu_AtomAgcReg(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  ResumeAllInterrupts();
}


FUNC(void, RTE_CODE) SchM_Enter_Mcu_TomTgcReg(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  SuspendAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Exit_Mcu_TomTgcReg(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  ResumeAllInterrupts();
}



/**********************************************************************************************************************
 * RTE Schedulable entity for COM-Access from different partitions
 *********************************************************************************************************************/
FUNC(void, RTE_CODE) Rte_ComSendSignalProxyPeriodic(void)
{
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_1514:  MISRA rule: Rule8.9
     Reason:     Because of external definition, misra does not see the call.
     Risk:       No functional risk. There is no side effect.
     Prevention: Not required.

   MD_Rte_3408:  MISRA rule: Rule8.4
     Reason:     For the purpose of monitoring during calibration or debugging it is necessary to use non-static declarations.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
