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
/*!        \file  Eth_30_Tc3xx_TrafficHandling.c
 *        \brief  Traffic handling sub-module source file of the Ethernet controller driver
 *
 *      \details  Contains the implementation of the traffic handling related API of the Ethernet controller driver.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx.h
 *********************************************************************************************************************/

/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#define ETH_30_TC3XX_TRAFFIC_HANDLING_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_TrafficHandling_Int.h"
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#if (ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL                          LOCAL
# endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL */

# if !defined (ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE                   LOCAL_INLINE
# endif /* ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetBandwidthLimit
 **********************************************************************************************************************/
/*! \brief        Reconfigures the bandwidth limit set for a transmission queue.
 *  \details      -
 *  \param[in]    ctrlIdx          Controller Index
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    queuePrio        Queue Priority
 *                [range: 0 <= queuePrio < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]    bandwidthLimit   Bandwidth limit which shall be assigned for the TX queue (in [bits/s])
 *  \return       E_NOT_OK - New bandwidth limit couldn't be set.
 *  \return       E_OK - New bandwidth limit set.
 *  \context      ANY
 *  \reentrant    TRUE for different queue priorities
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetBandwidthLimit(
  uint8  ctrlIdx,
  uint8  queuePrio,
  uint32 bandwidthLimit);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetBandwidthLimit
 **********************************************************************************************************************/
/*! \brief        Retrieves the currently configured bandwidth limit of a transmission queue.
 *  \details      -
 *  \param[in]    ctrlIdx            Controller Index
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    queuePrio          Queue Priority
 *                [range: 0 <= queuePrio < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[out]   bandwidthLimitPtr  Pointer to where to store the currently configured bandwidth limit (in [bit/s])
 *  \return       E_NOT_OK - Current bandwidth limit couldn't be retrieved.
 *  \return       E_OK - Current bandwidth limit retrieved.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetBandwidthLimit(
        uint8                         ctrlIdx,
        uint8                         queuePrio,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) bandwidthLimitPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetBandwidthLimit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetBandwidthLimit(
  uint8  ctrlIdx,
  uint8  queuePrio,
  uint32 bandwidthLimit)
{
  Std_ReturnType retVal  = E_NOT_OK;
  uint32 trcvSpeed = Eth_30_Tc3xx_GetTrcvSpeedOfEthCtrl(ctrlIdx);

  /* #10 If the new bandwidth limit to be set does not exceed the available bandwidth */
  if (bandwidthLimit <= trcvSpeed)
  {
    uint32 curBandwidth = 0;
    Eth_30_Tc3xx_TxDescrHandlingIterType txDescrHandlingIdx;
    Eth_30_Tc3xx_TxDescrHandlingIterType txDescrHandlingStartIdx =
        Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);

    /* #110 Calculate overall bandwidth consumption */
    for (txDescrHandlingIdx = txDescrHandlingStartIdx;
         txDescrHandlingIdx < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);
         txDescrHandlingIdx++)
    {
      if ((Eth_30_Tc3xx_IsShaperAvailable(txDescrHandlingIdx) == TRUE) &&
          (txDescrHandlingIdx != (txDescrHandlingStartIdx + queuePrio)))
      {
        curBandwidth += Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth(ctrlIdx,
            (uint8)(txDescrHandlingIdx - txDescrHandlingStartIdx));
      }
    }

    /* #120 If the new bandwidth limit for the requested queue in combination with the overall bandwidth consumption
     *      does not exceed the available bandwidth */
    if ((bandwidthLimit + curBandwidth) <= trcvSpeed)
    {
      /* #1210 Update the new bandwidth limit on the hardware */
      Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth(ctrlIdx, queuePrio, bandwidthLimit);
      retVal = E_OK;
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_SetBandwidthLimit() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetBandwidthLimit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetBandwidthLimit(
        uint8                         ctrlIdx,
        uint8                         queuePrio,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) bandwidthLimitPtr)
{
  Std_ReturnType retVal  = E_NOT_OK;

  Eth_30_Tc3xx_TxDescrHandlingIterType txDescrHandlingStartIdx =
      Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
  /* #10 If a traffic shaper is available on hardware for the requested queue */
  if (Eth_30_Tc3xx_IsShaperAvailable(txDescrHandlingStartIdx + queuePrio) == TRUE)
  {
    /* #110 Report the currently set shaper bandwidth limit and return that the request was successful */
    (*bandwidthLimitPtr) = Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth(ctrlIdx, queuePrio);                /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
    retVal = E_OK;
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetBandwidthLimit() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetBandwidthLimit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetBandwidthLimit(
  uint8  CtrlIdx,
  uint8  QueuePrio,
  uint32 BandwidthLimit)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(CtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if (QueuePrio >= (Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(CtrlIdx) -
                         Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(CtrlIdx)))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal interface to set a shaper bandwidth limit */
    retVal = Eth_30_Tc3xx_Internal_SetBandwidthLimit(CtrlIdx, QueuePrio, BandwidthLimit);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_SET_BANDWIDTH_LIMIT, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_SetBandwidthLimit() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetBandwidthLimit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetBandwidthLimit(
        uint8                         CtrlIdx,
        uint8                         QueuePrio,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) BandwidthLimitPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(CtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if (QueuePrio >= (Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(CtrlIdx) -
                         Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(CtrlIdx)))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if (BandwidthLimitPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal interface to retrieve a shaper bandwidth limit */
    retVal = Eth_30_Tc3xx_Internal_GetBandwidthLimit(CtrlIdx, QueuePrio, BandwidthLimitPtr);                             /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_GET_BANDWIDTH_LIMIT, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetBandwidthLimit() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif /* ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT */

/* module specific MISRA deviations:
 * see file Eth.c
*/

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TrafficHandling.c
 *********************************************************************************************************************/
