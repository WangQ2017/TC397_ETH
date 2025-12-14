/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_LL_TimeSync.h
 *        \brief  Timer sub-module header of the Ethernet controller driver
 *
 *      \details  Provides access to the hardware timer related API of the Ethernet controller driver.
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

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_TC3XX_LL_TIME_SYNC_H)
# define ETH_30_TC3XX_LL_TIME_SYNC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Int.h"

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#  if !defined (ETH_30_TC3XX_LL_TIME_SYNC_LOCAL) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TIME_SYNC_LOCAL                            LOCAL
#  endif /* ETH_30_TC3XX_LL_TIME_SYNC_LOCAL */

#  if !defined (ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE                     LOCAL_INLINE
#  endif /* ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock()
 *********************************************************************************************************************/
/*! \brief       Function for starting the timesync clock of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timesync clock shall be started
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime
 **********************************************************************************************************************/
/*! \brief       Captures the hardware timer of the Ethernet controller and returns the time stamp
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  timeStampPtr Time stamp captured
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different Ethernet controllers
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime(
        uint8                                    ctrlIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_SetHwTime
 **********************************************************************************************************************/
/*! \brief       Sets the hardware and software part of the timer to the given time
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   timeStampPtr Time to set
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different Ethernet controllers
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         Exclusive area for hardware timer (EXCLUSIVE_AREA_TIME) entered
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_SetHwTime(
          uint8                                    ctrlIdx,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the TX time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   ringIdx    Identifier of the TX descriptor ring
 *               [range: 0 <= ringIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx   Identifier of the TX descriptor within the ring
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[out]  timeStampPtr Transmission time stamp
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different TX descriptor
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp(
        uint8                                                  ctrlIdx,
        Eth_30_Tc3xx_RingIdxOfTxTsContextType                  ringIdx,
        Eth_30_Tc3xx_DescrIdxOfTxTsContextType                 descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the RX time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   ringIdx    Identifier of the RX descriptor ring
 *               [range: 0 <= ringIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx   Identifier of the RX descriptor within the ring
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \param[out]  timeStampPtr  Reception time stamp
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different RX descriptor
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp(
        uint8                                                           ctrlIdx,
        Eth_30_Tc3xx_RingIdxOfRxTsContextStackType                      ringIdx,
        Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType                     descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT)          timeStampPtr);

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITONS
 *********************************************************************************************************************/

#  ifndef ETH_30_TC3XX_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock(
  uint8 ctrlIdx)
{
  /* #10 Start time synchronization clock */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_TIMESTAMP_CONTROL,
                                       ETH_30_TC3XX_REG_MAC_TIMESTAMP_CONTROL_TSADDREG);
} /* Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime(
        uint8                                    ctrlIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr)
{
  uint32 sec;
  uint32_least hwLoopCycles;
  uint16 secHi;
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Loop if cycle count limit is not reached yet */
  for (hwLoopCycles = 0u; hwLoopCycles < Eth_30_Tc3xx_GetLoopCyclesOfEthCtrl(ctrlIdx); hwLoopCycles++)
  {
    /* #110 Get hardware time stamp from hardware timer register parts */
    timeStampPtr->secondsHi   =  (uint16) /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */ /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS,
                                           ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK);
    timeStampPtr->seconds     = /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */ /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS,
                                           ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_SECONDS_TSS_MASK);
    timeStampPtr->nanoseconds = /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */ /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_NANOSECONDS,
                                           ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK);

    /* #120 Check if there was any time stamp part overflow during retrieval of separate time stamp parts */
    secHi = (uint16) /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
        Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS,
                                           ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK);
    sec   = /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
        Eth_30_Tc3xx_Reg_Read    (ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS);

    if ((timeStampPtr->secondsHi == secHi) && (timeStampPtr->seconds == sec))
    {
      /* #1210 If consistent and valid time stamp retrieved break the loop and set E_OK as return value */
      retVal = E_OK;
      break;
    }

    /* #130 In case there was an overflow do another loop execution to try again to read consistent time stamp parts
     * (no further overflow for the duration of approximately one second expected) */
  }

  /* #20 If no valid time stamp is available reset time stamp values to zero and report DEM error */
  if (retVal != E_OK)
  {
    ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
    timeStampPtr->secondsHi   = 0u;                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
    timeStampPtr->seconds     = 0ul;                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
    timeStampPtr->nanoseconds = 0ul;                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
} /* Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_SetHwTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_SetHwTime(
         uint8                                                   ctrlIdx,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr)
{
  /* #10 Set time in hardware timer registers */
  /* PRQA S 0306 5 */ /* MD_Eth_30_Tc3xx_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE,  timeStampPtr->nanoseconds);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS_UPDATE,      timeStampPtr->seconds);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS, timeStampPtr->secondsHi);

  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_TIMESTAMP_CONTROL,
                                       ETH_30_TC3XX_REG_MAC_TIMESTAMP_CONTROL_TSINIT_MASK);

  return E_OK;
} /* Eth_30_Tc3xx_TimeSync_LL_SetHwTime() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp(
        uint8                                                       ctrlIdx,
        Eth_30_Tc3xx_RingIdxOfTxTsContextType                       ringIdx,
        Eth_30_Tc3xx_DescrIdxOfTxTsContextType                      descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT)      timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* #10 For a valid descriptor index */
  if (Eth_30_Tc3xx_GetDescrNumOfTxBufferHandling(Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx)) > descrIdx)
  {
     Eth_30_Tc3xx_TxDescrPtrType txDescPtr = Eth_30_Tc3xx_GetAddrTxDescr(descrIdx);

    /* #110 Check if last descriptor bit and TX timestamp status flags are available */
    if (((txDescPtr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_TX3_DESC_STATUS_LD)   != 0ul) &&
        ((txDescPtr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_TX3_DESC_STATUS_TTSS) != 0ul))
    {
      /* #1010 Retrieve TX time stamp */
      timeStampPtr->nanoseconds = txDescPtr->TxDescrWord[ETH_30_TC3XX_DES0_IDX];                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      timeStampPtr->seconds     = txDescPtr->TxDescrWord[ETH_30_TC3XX_DES1_IDX];                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      /* The seconds portion, stored in the descriptor only contains the lower 32 bits. The upper bits must be read
       * from Higher Word Seconds Register.
       * There is a potential risk that the Higher Word Seconds Register was increased between the actual reception of
       * the frame and the time the descriptor is processed here. However this risk is extremely unlikely and cannot be
       * avoided
       */
      /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
      timeStampPtr->secondsHi = (uint16)                                                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
          Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS,
                                             ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK);

      /* #1020 Set E_OK as return value if time stamp is valid, i.e. different from all ones pattern */
      if ((timeStampPtr->seconds     != ETH_30_TC3XX_TX1_DESC_TIMESTAMP_HIGH_INVALID_MASK) &&
          (timeStampPtr->nanoseconds != ETH_30_TC3XX_TX0_DESC_TIMESTAMP_LOW_INVALID_MASK))
      {
        retVal = E_OK;
      }
    }
  }
  ETH_30_TC3XX_DUMMY_STATEMENT(ringIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return retVal;
} /* Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp(
        uint8                                                            ctrlIdx,
        Eth_30_Tc3xx_RingIdxOfRxTsContextStackType                       ringIdx,
        Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType                      descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT)           timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check descriptor index */
  Eth_30_Tc3xx_RxBufferHandlingIterType rxBuffIter;
  uint16 rxDescCount = 0;
  for (rxBuffIter = Eth_30_Tc3xx_GetRxBufferHandlingStartIdxOfEthCtrl(ctrlIdx); rxBuffIter < Eth_30_Tc3xx_GetRxBufferHandlingEndIdxOfEthCtrl(ctrlIdx); rxBuffIter++)
      {
        rxDescCount += Eth_30_Tc3xx_GetDescrNumOfRxBufferHandling(rxBuffIter);
      }
  if (rxDescCount > descrIdx)
  {
    Eth_30_Tc3xx_RxDescrPtrType rxDescPtr = Eth_30_Tc3xx_GetAddrRxDescr(descrIdx);

    /* #110 Check for last descriptor, timestamp valid and timestamp not dropped flags */
    if (((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_LD)  != 0ul) &&
        ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES1_IDX] & ETH_30_TC3XX_RX1_DESC_TSA) != 0ul) &&
        ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES1_IDX] & ETH_30_TC3XX_RX1_DESC_TD)  == 0ul))
    {
      /* #1010 Retrieve RX time stamp */
      timeStampPtr->nanoseconds = rxDescPtr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES0_IDX];                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      timeStampPtr->seconds     = rxDescPtr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES1_IDX];                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      /* The seconds portion, stored in the descriptor only contains the lower 32 bits. The upper bits must be read
       * from Higher Word Seconds Register.
       * There is a potential risk that the Higher Word Seconds Register was increased between the actual reception of
       * the frame and the time the descriptor is processed here. However this risk is extremely unlikely and cannot be
       * avoided
       */
      /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
      timeStampPtr->secondsHi = (uint16)                                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
          Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS,
                                             ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK);

      /* #1020 Check if time stamp is valid and set return value accordingly. 
               If an all ones pattern is set, the timestamp is not valid */
      if ((timeStampPtr->seconds     != ETH_30_TC3XX_TX1_DESC_TIMESTAMP_HIGH_INVALID_MASK) &&
          (timeStampPtr->nanoseconds != ETH_30_TC3XX_TX0_DESC_TIMESTAMP_LOW_INVALID_MASK))
      {
        retVal = E_OK;
      }
    }
  }
  ETH_30_TC3XX_DUMMY_STATEMENT(ringIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return retVal;
} /* Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp() */

#  endif /* ETH_30_TC3XX_UNIT_TEST */

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

#endif /* ETH_30_TC3XX_LL_TIME_SYNC_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_TimeSync.h
 *********************************************************************************************************************/
