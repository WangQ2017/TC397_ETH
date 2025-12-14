/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_LL.c
 *        \brief  Lower Layer of Ethernet Driver
 *
 *      \details  Implementation of lower layer part of Ethernet driver.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/

/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

#define ETH_30_TC3XX_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_LL.h"
#include "Eth_30_Tc3xx.h"

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/**********************************************************************************************************************
 * Eth_30_Tc3xx_ArmPpsEventOnTime
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ArmPpsEventOnTime(
    uint8 CtrlIdx,
    P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) TimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;
  boolean        trgtbusy;

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* Check module state and input parameters */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( CtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl() )
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( TimestampPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    if(Eth_30_Tc3xx_IsArmPpsOnTimeEnabledOfEthCtrlTc3xx(CtrlIdx) == TRUE)
    {
      /* 10 Check target time register busy bit */
      trgtbusy = Eth_30_Tc3xx_Reg_IsBitMaskSet(CtrlIdx,
                  ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_NANOSECONDS,
                      ETH_30_TC3XX_REG_OFFS_MAC_PPS_NANOSECOND_TRGTBUSY0);

      /* #20 Check the range of nanosecond and value of seconds. */
      if ((TimestampPtr->secondsHi == ETH_30_TC3XX_PPS_TIME_SECONDS_HI) &&
          (TimestampPtr->nanoseconds <= ETH_30_TC3XX_PPS_TIME_NANOSECONDS_RANGE) && (!trgtbusy))
      {
        /* #210 Program the start time value in the PPS timer registers. */
        Eth_30_Tc3xx_Reg_Write(CtrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_SECONDS,
            TimestampPtr->seconds);
        Eth_30_Tc3xx_Reg_Write(CtrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_NANOSECONDS,
            TimestampPtr->nanoseconds);

        /* Width and interval of PPS signal output is configured in the initial configuration of MAC */

        /* #220 Set the Pps control register for single pulse generation. */
        Eth_30_Tc3xx_Reg_SetBitMask(CtrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PPS_CONTROL_REG,
            ETH_30_TC3XX_REG_OFFS_MAC_PPS_CONTROL_REG_PPSCMD);

        retVal = E_OK;
      }
    }
    else
    {
      retVal = E_OK;
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx),
        ETH_30_TC3XX_SID_ARM_PPS_EVENT_ON_TIME, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
}/* PRQA S 6080 */ /* MD_MSR_STMIF */
 /**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL.c
 *********************************************************************************************************************/
