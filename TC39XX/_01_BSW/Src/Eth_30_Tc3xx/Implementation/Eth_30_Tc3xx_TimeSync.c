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
/*!        \file  Eth_30_Tc3xx_TimeSync.c
 *        \brief  Timer sub-module source file of the Ethernet controller driver
 *
 *      \details  Containes the implementation of the hardware timer related API of the Ethernet controller driver.
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

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#define ETH_30_TC3XX_TIME_SYNC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_TimeSync_Int.h"
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

#if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (ETH_30_TC3XX_TIME_SYNC_LOCAL) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_TIME_SYNC_LOCAL                                 LOCAL
# endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL */

# if !defined (ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE                          LOCAL_INLINE
# endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE */

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
 *  LOCAL FUNCTIONS PROTOTYPES
 **********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetGlobalTime
 **********************************************************************************************************************/
/*! \brief       Retrieves the current time of the Eth controllers timer
 *  \details     -
 *  \param[in]   ctrlIdx              Identifier of the Eth controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  timestampPtr         Retrieve time stamp
 *  \param[out]  timestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetGlobalTime(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! \brief       Enables time stamping for the given frame on transmission
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Eth controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx   Identifier of the buffer holding the frame to be transmitted
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \return      E_OK - Time stamping of frame successfully enabled
 *  \return      E_NOT_OK - Time stamping of the frame wasn't enabled
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_EnableEgressTimestamp(
  uint8 ctrlIdx,
  uint8 bufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetEgressTimestamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the time stamp for a frame transmitted
 *  \details     -
 *  \param[in]   ctrlIdx              Identifier of the Eth controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx               Identifier of the buffer holding the frame to be transmitted
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[out]  timestampPtr         Time stamp taken on transmission
 *  \param[out]  timestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetEgressTimestamp(
        uint8                                           ctrlIdx,
        uint8                                           bufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetIngressTimestamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the time stamp for a frame received
 *  \details     -
 *  \param[in]   ctrlIdx              Identifier of the Eth controller
 *               [range: 0 <= CtrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  timestampPtr         Time stamp taken on reception
 *  \param[out]  timestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetIngressTimestamp(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetGlobalTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetGlobalTime(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call the hardware dependent interface to trigger a timer capture operation */
  retVal = Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime(ctrlIdx, timestampPtr);                                                /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */

   /* #20 If the time stamp could be retrieved successfully from the hardware */
  if (retVal == E_OK)
  {
    /* #210 Mark time stamp as valid */
    (*timestampQualityPtr) = ETH_TIMESTAMP_VALID;                                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #30 If the time stamp could not be retrieved successfully from the hardware */
  else
  {
    /* #320 Mark time stamp as invalid */
    (*timestampQualityPtr) = ETH_TIMESTAMP_INVALID;                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetGlobalTime() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_EnableEgressTimestamp(
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the  buffer holding the frame that shall be timestamped is locked */
  if (Eth_30_Tc3xx_IsBusyOfTxBufferState(bufIdx) == TRUE)
  {
    /* #110 Set the global state variable to indicate that a timestamp is requested for the requested buffer */
    Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(bufIdx, ETH_30_TC3XX_TIMESYNC_TS_REQUESTED);                               /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
    retVal = E_OK;
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_EnableEgressTimestamp() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetEgressTimestamp
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
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetEgressTimestamp(
        uint8                                           ctrlIdx,
        uint8                                           bufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  Eth_30_Tc3xx_BusyOfTxBufferStateType isBufferBusy;
  Eth_30_Tc3xx_RingIdxOfTxTsContextType ringIdx;
  Eth_30_Tc3xx_DescrIdxOfTxTsContextType descrIdx;
  Eth_30_Tc3xx_TsRequestedOfTxBufferStateType isTsRequested;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the buffer the egress timestamp shall be retrieved for is locked and its state indicates that the
   *     timestamping was was enabled before transmission */
  ringIdx       = Eth_30_Tc3xx_GetRingIdxOfTxTsContext(bufIdx);
  descrIdx      = Eth_30_Tc3xx_GetDescrIdxOfTxTsContext(bufIdx);
  isBufferBusy  = Eth_30_Tc3xx_IsBusyOfTxBufferState(bufIdx);
  isTsRequested = Eth_30_Tc3xx_IsTsRequestedOfTxBufferState(bufIdx);

  if ((isBufferBusy == TRUE) && (isTsRequested == ETH_30_TC3XX_TIMESYNC_TS_REQUESTED))
  {
    /* #110 Call the hardware dependent interface to retrieve the egress timestamp if the requested buffer */
    retVal = Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp(ctrlIdx, ringIdx, descrIdx, timestampPtr);                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
    /* #120 If the context was valid and the retrieval of the timestamp was allowed */
    if (retVal == E_OK)
    {
      /* #1210 Report that the retrieved timestamp is valid */
      (*timestampQualityPtr) = ETH_TIMESTAMP_VALID;                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
    }
    /* #130 If the context was invalid or the retrieval of the timestamp was allowed or failed */
    else
    {
      /* #1310 Mark the retrieved timestamp as invalid */
      (*timestampQualityPtr) = ETH_TIMESTAMP_INVALID;                                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetEgressTimestamp() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetIngressTimestamp
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
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetIngressTimestamp(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Retrieve the context (ring and descriptor) the time stamp shall be retrieved for */
  Std_ReturnType retVal = E_NOT_OK;
  Eth_30_Tc3xx_RxTsContextStackPosType rxTsContextStackPos;
  Eth_30_Tc3xx_RxTsContextStackIterType rxTsContextStackIdx;
  Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType rxTsContextStackStartIdx;

  /* ----- Implementation ----------------------------------------------- */
  rxTsContextStackStartIdx = Eth_30_Tc3xx_GetRxTsContextStackStartIdxOfTsHandling(ctrlIdx);
  rxTsContextStackPos      = Eth_30_Tc3xx_GetRxTsContextStackPos(ctrlIdx);

  rxTsContextStackIdx      = rxTsContextStackStartIdx + rxTsContextStackPos;
  /* #20 If the retrieved context is valid */
  if (rxTsContextStackIdx < Eth_30_Tc3xx_GetRxTsContextStackEndIdxOfTsHandling(ctrlIdx))
  {
    Eth_30_Tc3xx_RingIdxOfRxTsContextStackType ringIdx;
    Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType descrIdx;

    ringIdx  = Eth_30_Tc3xx_GetRingIdxOfRxTsContextStack(rxTsContextStackIdx);
    descrIdx = Eth_30_Tc3xx_GetDescrIdxOfRxTsContextStack(rxTsContextStackIdx);
    /* #210 Call the hardware dependent interface to retrieve the ingress timestamp */
    retVal = Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp(ctrlIdx, ringIdx, descrIdx, timestampPtr);                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  }

  /* #30 If the ingress timestamp could be retrieved successfully and the context was valid */
  if (retVal == E_OK)
  {
    /* #310 Mark the retrieved timestamp as valid */
    (*timestampQualityPtr) = ETH_TIMESTAMP_VALID;                                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #40 If the ingress timestamp could not be retrieved successfully or the context was invalid */
  else
  {
    /* #410 Mark the retrieved timestamp as invalid */
    (*timestampQualityPtr) = ETH_TIMESTAMP_INVALID;                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetIngressTimestamp() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_Init
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_Init(
  uint8 CtrlIdx)
{
  Std_ReturnType    retVal;
  Eth_TimeStampType timestamp;

  /* #10 Set hardware time to zero */
  timestamp.seconds = 0u;
  timestamp.secondsHi = 0u;
  timestamp.nanoseconds = 0u;

  retVal = Eth_30_Tc3xx_LL_TimeSync_SetHwTime(CtrlIdx, &timestamp);                                                      /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
  return retVal;
} /* Eth_30_Tc3xx_TimeSync_Init() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetGlobalTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetGlobalTime(
        uint8                                           CtrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) TimestampQualityPtr)
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
  else if (TimestampPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (TimestampQualityPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal interface to retrieve the global time */
    retVal = Eth_30_Tc3xx_Internal_GetGlobalTime(CtrlIdx, TimestampPtr, TimestampQualityPtr);                            /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx),
        ETH_30_TC3XX_TIME_SYNC_SID_GET_GLOBAL_TIME, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetGlobalTime() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_EnableEgressTimestamp(
  uint8 CtrlIdx,
  uint8 BufIdx)
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
  else if (BufIdx >= Eth_30_Tc3xx_GetBufferNumOfTxBufferHandling(CtrlIdx))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal interface to enable egress timestamping */
    retVal = Eth_30_Tc3xx_Internal_EnableEgressTimestamp(CtrlIdx, BufIdx);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx),
        ETH_30_TC3XX_TIME_SYNC_SID_ENABLE_EGRESS_TIMESTAMP, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_EnableEgressTimestamp() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetEgressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEgressTimestamp(
        uint8                                           CtrlIdx,
        uint8                                           BufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) TimestampQualityPtr)
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
  else if (BufIdx >= Eth_30_Tc3xx_GetBufferNumOfTxBufferHandling(CtrlIdx))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if (TimestampPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (TimestampQualityPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal interface to retrieve an egress timestamp */
    retVal = Eth_30_Tc3xx_Internal_GetEgressTimestamp(CtrlIdx, BufIdx, TimestampPtr, TimestampQualityPtr);               /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx),
        ETH_30_TC3XX_TIME_SYNC_SID_GET_EGRESS_TIMESTAMP, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetEgressTimestamp() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetIngressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIngressTimestamp(
        uint8                                           CtrlIdx,
  P2VAR(Eth_DataType,             AUTOMATIC, AUTOMATIC) DataPtr, /* PRQA S 3673 */ /* MD_Eth_30_Tc3xx_3673 */
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) TimestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  ETH_30_TC3XX_DUMMY_STATEMENT(DataPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

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
  else if (DataPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (TimestampPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (TimestampQualityPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal interface to retrieve an ingress timestamp */
    retVal = Eth_30_Tc3xx_Internal_GetIngressTimestamp(CtrlIdx, TimestampPtr, TimestampQualityPtr);                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx),
        ETH_30_TC3XX_TIME_SYNC_SID_GET_INGRESS_TIMESTAMP, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetIngressTimestamp() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

/* module specific MISRA deviations:
 * see file Eth.c
*/

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TimeSync.c
 *********************************************************************************************************************/
