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
 *             File:  Cdd_PPS.c
 *           Config:  G:/TC397_ETH/BSW_Config/TC397_BSW.dpa
 *        SW-C Type:  Cdd_PPS
 *  Generation Time:  2026-05-30 11:17:59
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  C-Code implementation template for SW-C <Cdd_PPS>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Cdd_PPS.h"
#include "Os.h"
#include "IfxGeth_reg.h"
#include "Cdd_Log.h"
#include "Eth_30_Tc3xx_TimeSync.h"
#include "StbM.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
typedef enum
{
    PPS_UNSYNC = 1,
    PPS_WAIT_RISE = 2,
    PPS_HIGH = 3,
    PPS_LOW = 4,
    PPS_INVALID = 5,
} Cdd_PPS_Status;

 typedef struct
{
    uint32 ntSec;
    uint32 ntNSec;
    uint32 nsPerSec;
    uint64 ntGlbTimeSec;
} Cdd_PPS_NextTime;
 /* 全局标志，由PPS中断设置，由周期函数清除 */
volatile boolean g_ppsEvent = FALSE;
volatile Cdd_PPS_Status g_ppsCurStatus = PPS_INVALID;
volatile uint64 g_ppsCurTime = 0;
static Cdd_PPS_NextTime s_nexTime = {0};

#define PPS_NANO_PER_SECOND (1000000000ULL)
#define PPS_MILLION (1000000) 
#define PPS_ADJUST_GAP (10000000)   /* 10ms */
#define PPS_ADJUST_TIMEOUT (1000)   /* 1000ms */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#define Cdd_PPS_START_SEC_CODE
#include "Cdd_PPS_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_PPS_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_PPS_Init_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_PPS_CODE) Cdd_PPS_Init(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_PPS_Init
 *********************************************************************************************************************/
  GETH_MAC_INTERRUPT_ENABLE.B.TSIE = 1U;
  g_ppsCurStatus = PPS_UNSYNC;
  CDD_LOG_DEBUG("pps init!");
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_PPS_Runnable5ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 5ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_PPS_Runnable5ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

static Std_ReturnType Cdd_PPS_GetNextTime(Cdd_PPS_NextTime *nextime)
{

    StbM_TimeStampType currGlobalTime = { 0u, 0u, 0u, 0u };
    StbM_VirtualLocalTimeType currVlt = { 0u, 0u };
    StbM_UserDataType userData = { 0u, 0u, 0u, 0u };
    Std_ReturnType retValTemp = E_NOT_OK;
    uint64 glbTime = 0;
    uint64 virLocalTime = 0;
    uint32 ntGap = 0;

    /* #30 Get the current global and virtual local time tuple from StbM via StbM_BusGetCurrentTime() for later
     *     calculation of the precise origin timestamp. */
    if(StbM_BusGetCurrentTime(0, &currGlobalTime, &currVlt, &userData) == E_OK) /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      glbTime = ((uint64)(currGlobalTime.secondsHi << 32) + currGlobalTime.seconds) * PPS_NANO_PER_SECOND + currGlobalTime.nanoseconds;
      virLocalTime = ((uint64)currVlt.nanosecondsHi << 32) + currVlt.nanosecondsLo;
      retValTemp = E_OK;
    }
    else
    {
      retValTemp = E_NOT_OK;
    }

    StbM_RateDeviationType rateDeviation = 0;
    if ((retValTemp == E_OK) && (StbM_GetRateDeviation(0, &rateDeviation) == E_OK))   
    {
      ntGap = (uint32)((PPS_NANO_PER_SECOND - (glbTime % PPS_NANO_PER_SECOND)) * PPS_MILLION / (PPS_MILLION + rateDeviation));
      nextime->ntNSec = (uint32)((virLocalTime + ntGap) % PPS_NANO_PER_SECOND);
      nextime->ntSec = (uint32)((virLocalTime + ntGap) / PPS_NANO_PER_SECOND);
      nextime->nsPerSec = (uint32)(PPS_NANO_PER_SECOND * PPS_MILLION / (PPS_MILLION + rateDeviation));
      nextime->ntGlbTimeSec = (glbTime / PPS_NANO_PER_SECOND) + 1;
      retValTemp = E_OK;
    }
    else
    {
      retValTemp = E_NOT_OK;
    }

    return retValTemp;
}

FUNC(void, Cdd_PPS_CODE) Cdd_PPS_Runnable5ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_PPS_Runnable5ms
 *********************************************************************************************************************/
  Std_ReturnType ret = E_NOT_OK;
  uint64 timeNow = (uint64)TimerGetMs();
  if (((timeNow - g_ppsCurTime) > PPS_ADJUST_TIMEOUT) && (g_ppsCurStatus != PPS_UNSYNC))
  {
    GETH_MAC_PPS_CONTROL.B.PPSCTRL_PPSCMD = 5;
    g_ppsCurStatus = PPS_UNSYNC;
    uint64 deltaTime = timeNow - g_ppsCurTime;
    g_ppsCurTime = timeNow;
    CDD_LOG_ERROR("pps lost sync %llu!", deltaTime);
  }
  else
  {
    switch(g_ppsCurStatus)
    {
      case PPS_UNSYNC:
      {
        ret = Cdd_PPS_GetNextTime(&s_nexTime);
        if (ret == E_OK)
        {
          boolean isValid = FALSE;
          uint64 curTime = 0;
          StbM_VirtualLocalTimeType currVlt = { 0u,0u };

          Std_ReturnType stbmGetCurrVltRetVal = StbM_GetCurrentVirtualLocalTime(0, &currVlt); 
          if (stbmGetCurrVltRetVal == E_OK)
          {
            curTime = ((uint64)currVlt.nanosecondsHi << 32) + currVlt.nanosecondsLo;
            if (curTime != 0)
            {
              uint64 nxTime = (uint64)s_nexTime.ntSec * PPS_NANO_PER_SECOND + s_nexTime.ntNSec;
              if ((nxTime > curTime) && (nxTime - curTime > PPS_ADJUST_GAP))
              {
                isValid = TRUE;
              }
            }
          }
          if (isValid)
          {
            uint32 ppsInterval = s_nexTime.nsPerSec / GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC;
            uint32 ppsWidth = ppsInterval / 2;
            GETH_MAC_PPS_CONTROL.B.PPSCTRL_PPSCMD = 0;
            GETH_MAC_PPS_CONTROL.B.TRGTMODSEL0 = 2U;
            GETH_MAC_PPS0_TARGET_TIME_NANOSECONDS.U = ((1 << 31U) | s_nexTime.ntNSec);
            GETH_MAC_PPS0_TARGET_TIME_SECONDS.U = s_nexTime.ntSec;
            GETH_MAC_PPS0_INTERVAL.U = ppsInterval - 1;
            GETH_MAC_PPS0_WIDTH.U = ppsWidth - 1;
            GETH_MAC_PPS_CONTROL.B.PPSEN0 = 1;
            GETH_MAC_PPS_CONTROL.B.PPSCTRL_PPSCMD = 2;
            g_ppsCurStatus = PPS_WAIT_RISE;
            g_ppsCurTime = (uint64)TimerGetMs();
          }
          else
          {
            CDD_LOG_ERROR("pps set fail in pps unsync!");
          }
        }
      }
      break;
      case PPS_WAIT_RISE:
      {
        if (g_ppsEvent == TRUE)
        {
          g_ppsCurStatus = PPS_HIGH;
          g_ppsEvent = FALSE;
        }
      }
      break;
      case PPS_HIGH:
      {
        GETH_MAC_PPS_CONTROL.B.PPSCTRL_PPSCMD = 5;
        g_ppsCurStatus = PPS_LOW;
      }
      break;
      case PPS_LOW:
      {
        ret = Cdd_PPS_GetNextTime(&s_nexTime);
        if (ret == E_OK)
        {
          boolean isValid = FALSE;
          uint64 curTime = 0;
          StbM_VirtualLocalTimeType currVlt = { 0u,0u };

          Std_ReturnType stbmGetCurrVltRetVal = StbM_GetCurrentVirtualLocalTime(0, &currVlt); 
          if (stbmGetCurrVltRetVal == E_OK)
          {
            curTime = ((uint64)currVlt.nanosecondsHi << 32) + currVlt.nanosecondsLo;
            if (curTime != 0)
            {
              uint64 nxTime = (uint64)s_nexTime.ntSec * PPS_NANO_PER_SECOND + s_nexTime.ntNSec;
              if ((nxTime > curTime) && (nxTime - curTime > PPS_ADJUST_GAP))
              {
                isValid = TRUE;
              }
            }
          }
          if (isValid)
          {
            if (GETH_MAC_PPS0_TARGET_TIME_NANOSECONDS.B.TRGTBUSY0 != 0)
            {
              CDD_LOG_ERROR("pps GETH_MAC_PPS0_TARGET_TIME_NANOSECONDS busy!");
            }
            else
            {
              GETH_MAC_PPS0_TARGET_TIME_NANOSECONDS.U = ((1 << 31U) | s_nexTime.ntNSec);
              GETH_MAC_PPS0_TARGET_TIME_SECONDS.U = s_nexTime.ntSec;
              GETH_MAC_PPS_CONTROL.B.PPSCTRL_PPSCMD = 2;

              g_ppsCurTime = (uint64)TimerGetMs();
              g_ppsCurStatus = PPS_WAIT_RISE;
            }
          }
          else
          {
            CDD_LOG_ERROR("pps too close to set!");
            GETH_MAC_PPS_CONTROL.B.PPSCTRL_PPSCMD = 5;
            g_ppsCurStatus = PPS_UNSYNC;
            return;
          }
        }
      }
      break;
      default: break;
    }
  }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define Cdd_PPS_STOP_SEC_CODE
#include "Cdd_PPS_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

ISR(EthIsr_PPS)
{
    if (GETH_MAC_INTERRUPT_STATUS.B.TSIS == TRUE)
    {
      if (GETH_MAC_TIMESTAMP_STATUS.B.TSTARGT0 != 0)
      {
        g_ppsEvent = TRUE;
        CDD_LOG_DEBUG("pps interrupt!");
      }
      // else if (GETH_MAC_TIMESTAMP_STATUS.B.TSTRGTERR0 != 0)
      // {
      //   Std_ReturnType ret;
      //   Eth_TimeStampType Timestamp;
      //   Eth_TimestampQualityType TimestampQuality;
      //   ret = Eth_30_Tc3xx_GetGlobalTime(0, &Timestamp, &TimestampQuality);
      //   if ((ret != E_OK) || (TimestampQuality != ETH_TIMESTAMP_VALID))
      //   {
      //     CDD_LOG_ERROR("Eth_30_Tc3xx_GetGlobalTime Failed!");
      //   }
      //   CDD_LOG_ERROR("TSTRGTERR0 Interrupt!");
      // }
      else
      {
        CDD_LOG_ERROR("Unknow Interrupt!");
      }
    }
}

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
