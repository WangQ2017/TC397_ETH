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
/*!        \file  EthIf_Stats_Int.h
 *        \brief  EthIf Stats internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module Stats of EthIf only to be used internally,
 *                where functions are intended to be linked by linker.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined (ETHIF_STATS_INT_H)
# define ETHIF_STATS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Stats_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to Eth resolved through EthIf_Lcfg.h -> no include needed */

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Rx_Types_Int.h"
# include "EthIf_Tx_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_STATS_INT_LOCAL)                                                                                   /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_STATS_INT_LOCAL static
# endif

# if !defined (ETHIF_STATS_INT_LOCAL_INLINE)                                                                            /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_STATS_INT_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthIf_UpdateTxStats
 *********************************************************************************************************************/
/*! \brief          Updates the tx statistic counters of the EthIf-controller
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the statistics shall be updated for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_UpdateTxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  uint16                   payloadLen);

/**********************************************************************************************************************
 *  EthIf_ClearTxStats
 *********************************************************************************************************************/
/*! \brief          Clears the tx statistic counters of the EthIf-controller
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the statistics shall be cleared for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            Exclusive area RXTX_STATS must have been entered
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_ClearTxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_UpdateRxStats
 *********************************************************************************************************************/
/*! \brief          Updates the rx statistic counters of the EthIf-controller
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the statistics shall be updated for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_UpdateRxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  uint16                   payloadLen);

/**********************************************************************************************************************
 *  EthIf_ClearRxStats
 *********************************************************************************************************************/
/*! \brief          Clears the rx statistic counters of the EthIf-controller
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the statistics shall be cleared for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            Exclusive area RXTX_STATS must have been entered
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_ClearRxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

# if ( ETHIF_MEASUREMENT_DATA_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_ClearMeasurementData
 *********************************************************************************************************************/
/*! \brief          Clears all measurement data statistic counters of the EthIf-controller
 *  \details        -
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_ClearMeasurementData( void ); /* PRQA S 3219 */ /* MD_EthIf_3219 */

/**********************************************************************************************************************
 *  EthIf_GetAndResetMeasurementDataCounter
 *********************************************************************************************************************/
/*! \brief          Retrieve and optionally reset a specific measurement data statistics counter of the EthIf-controller
 *  \details        -
 *  \param[out]     measurementDataPtr                   Pointer to retrieve a measurement data counter value or
 *                                                       NULL_PTR if no retrieval is intended
 *  \param[in]      measurementDataStatisticsCounterPtr  Pointer to a specific measurement data statistics counter
 *                                                       value from the CSL
 *  \param[in]      measurementResetNeeded               Flag to trigger a reset of the related measurement data
 *                                                       counter value
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_GetAndResetMeasurementDataCounter( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR) measurementDataPtr,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR) measurementDataStatisticsCounterPtr,
        boolean                            measurementResetNeeded);

/**********************************************************************************************************************
 *  EthIf_IncrementMeasurementDataCounter
 *********************************************************************************************************************/
/*! \brief          Increment a specific measurement data statistics counter of the EthIf-controller
 *  \details        -
 *  \param[in]      measurementDataStatisticsCounterPtr  Pointer to a specific measurement data statistics counter
 *                                                       value from the CSL
 *  \param[in]      maxCounterValue                      Maximum value of the related measurement data statistics
 *                                                       counter from the CSL
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_IncrementMeasurementDataCounter( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR) measurementDataStatisticsCounterPtr,
        uint32                             maxCounterValue);
# endif /* ETHIF_MEASUREMENT_DATA_SUPPORT */

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */
/**********************************************************************************************************************
 *  EthIf_UpdateTxStats
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_UpdateTxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  uint16                   payloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint64 updateBytes;
  uint64 curNumTxBytes;
  uint64 curNumTxPkts;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the bytes transmitted with this frame */
  updateBytes = ((uint64)payloadLen + (uint64)ETH_HEADER_LEN_BYTE);
  if( EthIf_GetTypeOfEthIfCtrl(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
  {
    updateBytes += ETHIF_VLAN_TAG_LEN_BYTE;
  }
  if( updateBytes < ETHIF_MIN_ETH_FRAME_LEN_BYTE )
  {
    updateBytes = ETHIF_MIN_ETH_FRAME_LEN_BYTE;
  }

  /* #20 Enter exclusive area (Reason: Update statistic counters in a consistent manner) */
  EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  curNumTxBytes = EthIf_GetNumTxBytesOfEthIfCtrlTxStats(ethIfCtrlIdx);
  curNumTxPkts = EthIf_GetNumTxPktsOfEthIfCtrlTxStats(ethIfCtrlIdx);

  if( (curNumTxBytes + updateBytes) < ETH_RXTX_STATS_MAX_COUNTER_VAL )
  {
    /* #30 If the transmitted bytes counter is able to hold the update value set it */
    EthIf_SetNumTxBytesOfEthIfCtrlTxStats(ethIfCtrlIdx, (EthIf_NumTxBytesOfEthIfCtrlTxStatsType)(curNumTxBytes + updateBytes)); /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }
  else
  {
    /* #40 Otherwise set it to the special overflow value */
    EthIf_SetNumTxBytesOfEthIfCtrlTxStats(ethIfCtrlIdx, ETH_RXTX_STATS_COUNTER_OVERFLOW_VAL);                           /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }

  /* #50 If the transmitted frames counter hasn't overflown since last update, update it */
  if( curNumTxPkts != ETH_RXTX_STATS_COUNTER_OVERFLOW_VAL )
  {
    EthIf_SetNumTxPktsOfEthIfCtrlTxStats(ethIfCtrlIdx, (EthIf_NumTxPktsOfEthIfCtrlTxStatsType)(curNumTxPkts + 1u));     /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }

  /* #60 Leave exclusive area */
  EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

} /* EthIf_UpdateTxStats() */

/**********************************************************************************************************************
 *  EthIf_ClearTxStats
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_ClearTxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Clear tx statistic counters */
  EthIf_SetNumTxBytesOfEthIfCtrlTxStats(ethIfCtrlIdx, 0);                                                               /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_SetNumTxPktsOfEthIfCtrlTxStats(ethIfCtrlIdx, 0);                                                                /* SBSW_ETHIF_INT_FCT_IDX_PASS */
} /* EthIf_ClearTxStats() */

/**********************************************************************************************************************
 *  EthIf_UpdateRxStats
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_UpdateRxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  uint16                   payloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint64 updateBytes;
  uint64 curNumRxBytes;
  uint64 curNumRxPkts;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the bytes received with this frame */
  updateBytes = ((uint64)payloadLen + (uint64)ETH_HEADER_LEN_BYTE);
  if( EthIf_GetTypeOfEthIfCtrl(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
  {
    updateBytes += ETHIF_VLAN_TAG_LEN_BYTE;
  }

  /* #20 Enter exclusive area (Reason: Update statistic counters in a consistent manner) */
  EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  curNumRxBytes = EthIf_GetNumRxBytesOfEthIfCtrlRxStats(ethIfCtrlIdx);
  curNumRxPkts = EthIf_GetNumRxPktsOfEthIfCtrlRxStats(ethIfCtrlIdx);

  if( (curNumRxBytes + updateBytes) < ETH_RXTX_STATS_MAX_COUNTER_VAL )
  {
    /* #30 If the received bytes counter is able to hold the update value set it */
    EthIf_SetNumRxBytesOfEthIfCtrlRxStats(ethIfCtrlIdx, (EthIf_NumRxBytesOfEthIfCtrlRxStatsType)(curNumRxBytes + updateBytes)); /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }
  else
  {
    /* #40 Otherwise set it to the special overflow value */
    EthIf_SetNumRxBytesOfEthIfCtrlRxStats(ethIfCtrlIdx, ETH_RXTX_STATS_COUNTER_OVERFLOW_VAL);                           /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }

  /* #50 If the received frames counter hasn't overflown since last update, update it */
  if( curNumRxPkts != ETH_RXTX_STATS_COUNTER_OVERFLOW_VAL )
  {
    EthIf_SetNumRxPktsOfEthIfCtrlRxStats(ethIfCtrlIdx, (EthIf_NumRxPktsOfEthIfCtrlRxStatsType)(curNumRxPkts + 1u));     /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }

  /* #60 Leave exclusive area */
  EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_UpdateRxStats() */

/**********************************************************************************************************************
 *  EthIf_ClearRxStats
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_ClearRxStats( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType ethIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Clear rx statistic counters */
  EthIf_SetNumRxBytesOfEthIfCtrlRxStats(ethIfCtrlIdx, 0);                                                               /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_SetNumRxPktsOfEthIfCtrlRxStats(ethIfCtrlIdx, 0);                                                                /* SBSW_ETHIF_INT_FCT_IDX_PASS */
} /* EthIf_ClearRxStats() */

#  if ( ETHIF_MEASUREMENT_DATA_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_ClearMeasurementData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_ClearMeasurementData( void ) /* PRQA S 3219 */ /* MD_EthIf_3219 */
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Update statistic counters in a consistent manner) */
  EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Clear all measurement data statistic counters */
  EthIf_SetDropCtrlIdxOfEthIfMeasurementData(ETHIF_MEASUREMENT_DATA_CSL_IDX, 0u);                                       /* SBSW_ETHIF_CSL_STRUCT_MEM_PARAM_IDX_MEASUREMENT_DATA */
  EthIf_SetVlanDoubleTaggedOfEthIfMeasurementData(ETHIF_MEASUREMENT_DATA_CSL_IDX,0u);                                   /* SBSW_ETHIF_CSL_STRUCT_MEM_PARAM_IDX_MEASUREMENT_DATA */
  EthIf_SetUnknownEtherTypeOfEthIfMeasurementData(ETHIF_MEASUREMENT_DATA_CSL_IDX,0u);                                   /* SBSW_ETHIF_CSL_STRUCT_MEM_PARAM_IDX_MEASUREMENT_DATA */

  /* #30 Leave exclusive area */
  EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_ClearMeasurementData() */

/**********************************************************************************************************************
 *  EthIf_GetAndResetMeasurementDataCounter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_GetAndResetMeasurementDataCounter( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR) measurementDataPtr,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR) measurementDataStatisticsCounterPtr,
        boolean                            measurementResetNeeded)
{
  /* #10 Enter exclusive area (Reason: Update statistic counters in a consistent manner) */
  EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Only provide measurement data statistics value if pointer is no NULL_PTR */
  if (measurementDataPtr != NULL_PTR)
  {
    (*measurementDataPtr) = (*measurementDataStatisticsCounterPtr);                                                     /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  }

  /* #30 Only reset measurement data statistics value if reset is requested */
  if (measurementResetNeeded == TRUE)
  {
    (*measurementDataStatisticsCounterPtr) = 0u;                                                                        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  }

  /* #40 Leave exclusive area */
  EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_GetAndResetMeasurementDataCounter() */

/**********************************************************************************************************************
 *  EthIf_IncrementMeasurementDataCounter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_STATS_INT_LOCAL_INLINE FUNC(void, ETHIF_STATS_INLINE_CODE) EthIf_IncrementMeasurementDataCounter( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR) measurementDataStatisticsCounterPtr,
        uint32                             maxCounterValue)
{
  /* #10 Enter exclusive area (Reason: Update statistic counters in a consistent manner) */
  EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Increment statistics counter only if no overflow occurs */
  if ((*measurementDataStatisticsCounterPtr) < maxCounterValue)
  {
    (*measurementDataStatisticsCounterPtr)++;                                                                           /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  }

  /* #30 Leave exclusive area */
  EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_IncrementMeasurementDataCounter() */
#  endif /* ETHIF_MEASUREMENT_DATA_SUPPORT */

# endif /* ETHIF_UNIT_TEST */

/**********************************************************************************************************************
 *  EthIf_Stats_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf Mode sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Stats_Init( void );

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_STATS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Stats_Int.h
 *********************************************************************************************************************/

