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
 *             File:  Rte_OsApplication_OsCore1.c
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
FUNC(uint8, RTE_CODE) Rte_GetInternalModeIndex_BswM_ESH_Mode(BswM_ESH_Mode mode); /* PRQA S 3408 */ /* MD_Rte_3408 */

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


FUNC(void, RTE_CODE) Rte_InitMemory_OsApplication_OsCore1(void)
{
}


/**********************************************************************************************************************
 * Task bodies for RTE controlled tasks
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Task:     OsTask_Asw_OsCore1
 * Priority: 14
 * Schedule: FULL
 * Alarm:    Cycle Time 0.01 s Alarm Offset 0 s
 *********************************************************************************************************************/
TASK(OsTask_Asw_OsCore1) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_Unreachable */
{

  /* call runnable */
  Cdd_Core1_Runnable10ms(); /* PRQA S 2987 */ /* MD_Rte_2987 */

  (void)TerminateTask(); /* PRQA S 3417 */ /* MD_Rte_Os */
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * Task:     OsTask_Bsw_OsCore1
 * Priority: 34
 * Schedule: FULL
 * Alarm:    Cycle Time 0.01 s Alarm Offset 0 s
 *********************************************************************************************************************/
TASK(OsTask_Bsw_OsCore1) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_Unreachable */
{

  /* call schedulable entity */
  EcuM_MainFunction();

  (void)TerminateTask(); /* PRQA S 3417 */ /* MD_Rte_Os */
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * Task:     OsTask_Init_OsCore1
 * Priority: 48
 * Schedule: FULL
 *********************************************************************************************************************/
TASK(OsTask_Init_OsCore1) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_Unreachable */
{

  /* call runnable */
  Cdd_Core1_Init(); /* PRQA S 2987 */ /* MD_Rte_2987 */

  /* call runnable */
//  window_core1_Init(); /* PRQA S 2987 */ /* MD_Rte_2987 */

  (void)TerminateTask(); /* PRQA S 3417 */ /* MD_Rte_Os */
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * Task:     OsTask_window_2ms
 * Priority: 41
 * Schedule: FULL
 * Alarm:    Cycle Time 0.002 s Alarm Offset 0 s
 *********************************************************************************************************************/
TASK(OsTask_window_2ms) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_Unreachable */
{

  /* call runnable */
//  Runnable_windows_2ms(); /* PRQA S 2987 */ /* MD_Rte_2987 */

  (void)TerminateTask(); /* PRQA S 3417 */ /* MD_Rte_Os */
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_2987:  MISRA rule: Rule2.2
     Reason:     Used to simplify code generation.
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
