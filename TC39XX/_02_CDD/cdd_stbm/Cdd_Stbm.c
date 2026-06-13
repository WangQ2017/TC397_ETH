/**********************************************************************************************************************
 *  FILE REQUIRES USER MODIFICATIONS
 *  Template Scope: sections marked with Start and End comments
 *  -------------------------------------------------------------------------------------------------------------------
 *  This file includes template code that must be completed and/or adapted during BSW integration.
 *  The template code is incomplete and only intended for providing a signature and an empty implementation.
 *  It is neither intended nor qualified for use in series production without applying suitable quality measures.
 *  The template code must be completed as described in the instructions given within this file and/or in the.
 *  Technical Reference.
 *  The completed implementation must be tested with diligent care and must comply with all quality requirements which.
 *  are necessary according to the state of the art before its use.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Cdd_Stbm.c
 *           Config:  G:/TC397_ETH/BSW_Config/TC397_BSW.dpa
 *        SW-C Type:  Cdd_Stbm
 *  Generation Time:  2026-05-30 11:43:30
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  C-Code implementation template for SW-C <Cdd_Stbm>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Cdd_Stbm.h"
#include "Stbm.h"
#include "Com.h"
#include "EthTSyn.h"
#include "Cdd_Log.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#define Cdd_Stbm_START_SEC_CODE
#include "Cdd_Stbm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Stbm_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Stbm_Init_doc
 *********************************************************************************************************************/
/* Bit 0: Timeout of receiving sync message */
#define STBM_TBS_TIMEOUT                     (1U << 0U)
/* Bit 1: Reserved (must be zero) */
#define STBM_TBS_RESERVED1                   (1U << 1U)   /* Do not use */
/* Bit 2: Local time base synchronized via Time Gateway */
#define STBM_TBS_SYNC_TO_GATEWAY             (1U << 2U)
/* Bit 3: Synchronized to global time master at least once (sticky) */
#define STBM_TBS_GLOBAL_TIME_BASE            (1U << 3U)
/* Bit 4: Time leap to future detected */
#define STBM_TBS_TIMELEAP_FUTURE             (1U << 4U)
/* Bit 5: Time leap to past detected */
#define STBM_TBS_TIMELEAP_PAST               (1U << 5U)
/* Bit 6: Valid rate correction value computed */
#define STBM_TBS_RATE_CORRECTED              (1U << 6U)
/* Bit 7: Rate correction exceeds limit */
#define STBM_TBS_RATE_EXCEEDED               (1U << 7U)

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

static uint8 s_lastMain0UpdateCounter = 0xFFu;
static StbM_TimeBaseStatusType s_lastMain0TimeBaseStatus = 0;
static boolean s_main0SnapshotValid = FALSE;

static boolean Cdd_Stbm_ResetMain0TimeChanged(StbM_TimeBaseStatusType timeBaseStatus, uint8 updateCounter)
{

  boolean timeChanged = FALSE;

  if ((s_main0SnapshotValid == FALSE) || 
      (timeBaseStatus != s_lastMain0TimeBaseStatus) || 
      (updateCounter != s_lastMain0UpdateCounter))
  {
      timeChanged = TRUE;
  }
  return timeChanged;
}

static void Cdd_Stbm_UpdateMain0SnapShot(StbM_TimeBaseStatusType timeBaseStatus, uint8 updateCounter)
{
  s_lastMain0UpdateCounter = updateCounter;
  s_lastMain0TimeBaseStatus = timeBaseStatus;
  s_main0SnapshotValid = TRUE;
}

static void Cdd_Stbm_ResetMain0SnapShot(void)
{
  s_lastMain0UpdateCounter = 0xFFu;
  s_lastMain0TimeBaseStatus = 0;
  s_main0SnapshotValid = FALSE;
}

FUNC(void, Cdd_Stbm_CODE) Cdd_Stbm_Init(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Stbm_Init
 *********************************************************************************************************************/
    Com_IpduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_All, TRUE);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Stbm_Runnable5ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 5ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Stbm_Runnable5ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
// #define StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN0 0u 
// #define StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN6 1u 

FUNC(void, Cdd_Stbm_CODE) Cdd_Stbm_Runnable5ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE   COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Stbm_Runnable5ms
 *********************************************************************************************************************/

  Std_ReturnType ret = E_NOT_OK;
  StbM_UserDataType userData = {0U};
  StbM_TimeStampType localTime;
  /* 1. 调用StbM_BusGetCurrentTime获取源时基的时间、状态和用户数据 */
  if (StbM_GetCurrentTime(StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN0, &localTime, &userData) == E_OK)
  {
    /* 2. 检查源时基是否有效（至少已同步过一次全局时间） */
    if (((localTime.timeBaseStatus) & STBM_TBS_GLOBAL_TIME_BASE) != 0U)
    {
      const uint8 main0UpdateCounter = StbM_GetTimeBaseUpdateCounter(StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN0);
      if (Cdd_Stbm_ResetMain0TimeChanged(localTime.timeBaseStatus, main0UpdateCounter) == TRUE)
      {
        ret = StbM_SetGlobalTime(StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN6, &localTime, &userData);
        if (ret != E_OK)
        {
          CDD_LOG_ERROR("Failed to set Global Time for TimeBase %d\n", StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN6);
        }
        else
        {
          Cdd_Stbm_UpdateMain0SnapShot(localTime.timeBaseStatus, main0UpdateCounter);
        }
      }
    }
    else
    {
      Cdd_Stbm_ResetMain0SnapShot();
    }
    // else
    // {
    //   CDD_LOG_ERROR("Source TimeBase %d is not synchronized.\n", StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN0);
    // }
    /* 3. 使能底层发送开关 */
    // if (((localTime.timeBaseStatus) & STBM_TBS_GLOBAL_TIME_BASE) != 0U)
    // {
    //   EthTSyn_SetTransmissionMode(EthIfConf_EthIfController_EthIfController_untagged, ETHTSYN_TX_ON);
    // }
    // else
    // {
    //   EthTSyn_SetTransmissionMode(EthIfConf_EthIfController_EthIfController_untagged, ETHTSYN_TX_OFF);
    // }

  }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Stbm_Runnable5ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 5ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Stbm_Runnable5ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_Stbm_CODE) Cdd_Stbm_Runnable100ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE   COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Stbm_Runnable5ms
 *********************************************************************************************************************/
  static StbM_TimeBaseStatusType s_timeBaseStatus = 0;

  StbM_TimeBaseStatusType syncTimeBaseStatus = 0;
  StbM_TimeBaseStatusType offsetTimeBaseStatus;
  if(StbM_GetTimeBaseStatus(StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN0,&syncTimeBaseStatus, &offsetTimeBaseStatus) == E_OK)
  {
    uint8 ret = Com_SendSignal(ComConf_ComSignal_ComSignal_TimeSyncStatus_Tx, &syncTimeBaseStatus);
    if (ret != COM_E_NO_ERROR)
    {
      CDD_LOG_ERROR("TimeSync Status Send fail, ret = %d!\n", ret);
    }
    s_timeBaseStatus = syncTimeBaseStatus;
  }


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

#define Cdd_Stbm_STOP_SEC_CODE
#include "Cdd_Stbm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0624:  MISRA rule: Rule8.3
     Reason:     This MISRA violation is a consequence from the RTE requirements [SWS_Rte_01007] [SWS_Rte_01150].
                 The typedefs are never used in the same context.
     Risk:       No functional risk. Only a cast to uint8* is performed.
     Prevention: Not required.

   MD_Rte_3206:  MISRA rule: Rule2.7
     Reason:     The parameter are not used by the code in all possible code variants.
     Risk:       No functional risk.
     Prevention: Not required.

*/
