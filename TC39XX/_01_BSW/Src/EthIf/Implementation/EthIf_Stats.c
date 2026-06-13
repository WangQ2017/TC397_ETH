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
/*!        \file  EthIf_Stats.c
 *        \brief  EthIf Stats public API source file
 *
 *      \details  Implementation of the public API of the sub-module Stats of EthIf.
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

#define ETHIF_STATS_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Stats.h"
#include "EthIf_Stats_Cbk.h"
#include "EthIf_Stats_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_Stats.c and EthIf.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHIF_STATS_LOCAL)                                                                                        /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_STATS_LOCAL static
#endif

#if !defined (ETHIF_STATS_LOCAL_INLINE)                                                                                 /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_STATS_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

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
 * EthIf_GetTxStats
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTxStats(
        uint8                                         CtrlIdx,
  P2VAR(Eth_TxStatsType,   AUTOMATIC, ETHIF_APPL_VAR) EthTxStats,
  P2VAR(EthIf_TxStatsType, AUTOMATIC, ETHIF_APPL_VAR) EthIfTxStats)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHIF_E_NO_ERROR;

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
#endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( EthTxStats == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( EthIfTxStats == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);
    EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

    /* #30 Enter exclusive area (Reason: Retrieval of tx statistic counters in a consistent manner) */
    EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #40 Retrieve the statistic counters of the EthIf-controller and clear them */
    EthIfTxStats->NumTxPkts  = EthIf_GetNumTxPktsOfEthIfCtrlTxStats(CtrlIdx);                                           /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    EthIfTxStats->NumTxBytes = EthIf_GetNumTxBytesOfEthIfCtrlTxStats(CtrlIdx);                                          /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    EthIf_ClearTxStats(CtrlIdx);

    /* #50 Leave exclusive area */
    EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    if( EthIf_GetGetTxStatsOfEthDrvApi(ethDrvApiIdx) != NULL_PTR )
    {
      /* #60 If the driver supports the API, retrieve the statistic counters of the respective
       *     Eth-controller by calling the driver */
      retVal = EthIf_GetGetTxStatsOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx), EthTxStats);      /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
    else
    {
      /* #70 Otherwise invalidate the driver specific counters */
      EthTxStats->TxNumberOfOctets = ETH_RXTX_STATS_INV_COUNTER_VAL;                                                    /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthTxStats->TxNUcastPkts     = ETH_RXTX_STATS_INV_COUNTER_VAL;                                                    /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthTxStats->TxUniCastPkts    = ETH_RXTX_STATS_INV_COUNTER_VAL;                                                    /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #80 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TX_STATS, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetTxStats() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthIf_GetRxStats
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetRxStats(
        uint8                                         CtrlIdx,
  P2VAR(Eth_RxStatsType,   AUTOMATIC, ETHIF_APPL_VAR) EthRxStats,
  P2VAR(EthIf_RxStatsType, AUTOMATIC, ETHIF_APPL_VAR) EthIfRxStats)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHIF_E_NO_ERROR;

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
#endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( EthRxStats == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( EthIfRxStats == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);
    EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

    /* #30 Enter exclusive area (Reason: Retrieval of rx statistic counters in a consistent manner) */
    EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #40 Retrieve the statistic counters of the EthIf-controller */
    EthIfRxStats->NumRxPkts  = EthIf_GetNumRxPktsOfEthIfCtrlRxStats(CtrlIdx);                                           /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    EthIfRxStats->NumRxBytes = EthIf_GetNumRxBytesOfEthIfCtrlRxStats(CtrlIdx);                                          /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    EthIf_ClearRxStats(CtrlIdx);

    /* #50 Leave exclusive area */
    EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    if( EthIf_GetGetRxStatsOfEthDrvApi(ethDrvApiIdx) != NULL_PTR )
    {
      /* #60 If the driver supports the API, retrieve the statistic counters of the respective
       *     Eth-controller by calling the driver */
      retVal = EthIf_GetGetRxStatsOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx), EthRxStats);      /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
    else
    {
      /* #70 Otherwise invalidate the driver specific counters */
      EthRxStats->RxStatsDropEvents           = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsOctets               = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsPkts                 = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsBroadcastPkts        = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsMulticastPkts        = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsCrcAlignErrors       = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsUndersizePkts        = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsOversizePkts         = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsFragments            = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsJabbers              = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsCollisions           = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsPkts64Octets         = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsPkts65to127Octets    = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsPkts128to255Octets   = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsPkts256to511Octets   = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsPkts512to1023Octets  = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxStatsPkts1024to1518Octets = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      EthRxStats->RxUnicastFrames             = ETH_RXTX_STATS_INV_COUNTER_VAL;                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #80 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_RX_STATS, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetRxStats() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if ( ETHIF_MEASUREMENT_DATA_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetAndResetMeasurementData(
        EthIf_MeasurementIdxType           MeasurementIdx,
        boolean                            MeasurementResetNeeded,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR) MeasurementDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHIF_E_NO_ERROR;

# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
# endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = E_OK;

    /* #20 Perform action according to MeasurementIdx */
    if (MeasurementIdx == ETHIF_MEAS_ALL)
    {
      /* #210 Perform actions for ETHIF_MEAS_ALL */
      if (MeasurementResetNeeded == TRUE)
      {
        /* #2010 Reset all measurement data statistics */
        EthIf_ClearMeasurementData();
      }
      else
      {
        /* #2020 MeasrementIdx ETHIF_MEAS_ALL only supported / specified for reset of all statistics */
        retVal = E_NOT_OK;
      }
    }
    else if (MeasurementIdx == ETHIF_MEAS_DROP_CTRLIDX)
    {
      /* #220 Perform actions for ETHIF_MEAS_DROP_CTRLIDX */
      EthIf_GetAndResetMeasurementDataCounter(
          MeasurementDataPtr,
          EthIf_GetAddrDropCtrlIdxOfEthIfMeasurementData(ETHIF_MEASUREMENT_DATA_CSL_IDX),
          MeasurementResetNeeded);                                                                                      /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
    }
    else if (MeasurementIdx == ETHIF_MEAS_VLAN_DOUBLE_TAGGED)
    {
      /* #230 Perform actions for ETHIF_MEAS_VLAN_DOUBLE_TAGGED */
      EthIf_GetAndResetMeasurementDataCounter(
          MeasurementDataPtr,
          EthIf_GetAddrVlanDoubleTaggedOfEthIfMeasurementData(ETHIF_MEASUREMENT_DATA_CSL_IDX),
          MeasurementResetNeeded);                                                                                      /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
    }
    else if (MeasurementIdx == ETHIF_MEAS_UNKNOWN_ETHERTYPE)
    {
      /* #240 Perform actions for ETHIF_MEAS_UNKNOWN_ETHERTYPE */
      EthIf_GetAndResetMeasurementDataCounter(
          MeasurementDataPtr,
          EthIf_GetAddrUnknownEtherTypeOfEthIfMeasurementData(ETHIF_MEASUREMENT_DATA_CSL_IDX),
          MeasurementResetNeeded);                                                                                      /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
    }
    else
    {
      /* #250 Measurement index is not supported / unknown */
      retVal = E_NOT_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_AND_RESET_MEASUREMENT_DATA, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetAndResetMeasurementData() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_MEASUREMENT_DATA_SUPPORT */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Stats.c
 *********************************************************************************************************************/

