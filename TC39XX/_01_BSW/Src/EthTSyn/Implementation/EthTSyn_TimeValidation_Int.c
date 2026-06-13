/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTSyn_TimeValidation_Int.c
 *        \brief  EthTSyn TimeValidation source file - Internal Functions
 *      \details  EthTSyn TimeValidation source file containing the implementation of TimeValidation unit
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

#define ETHTSYN_TIME_VALIDATION_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_TimeValidation_Int.h"
#include "EthTSyn.h"
#include "EthTSyn_Util_Int.h"
#include "SchM_EthTSyn.h"
#include "StbM.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (2u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn_TimeValidation_Int.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (2u)) )
# error "Version numbers of EthTSyn_TimeValidation_Int.c and EthTSyn_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ETHTSYN_TIME_VALID_MASTER_S_INVALID                           (0x00u)
#define ETHTSYN_TIME_VALID_MASTER_S_CYCLE_STARTED_FLAG                (0x01u)
#define ETHTSYN_TIME_VALID_MASTER_S_SYNC_EGR_TS_PROVIDED_FLAG         (0x02u)
#define ETHTSYN_TIME_VALID_MASTER_S_DATA_PROVIDED_FLAG                (0x04u)
#define ETHTSYN_TIME_VALID_MASTER_S_FUP_SENT_FLAG                     (0x08u)
#define ETHTSYN_TIME_VALID_MASTER_S_READY                             (0x0Fu)

#define ETHTSYN_TIME_VALID_SLAVE_S_INVALID                            (0x00u)
#define ETHTSYN_TIME_VALID_SLAVE_S_CYCLE_STARTED_FLAG                 (0x01u)
#define ETHTSYN_TIME_VALID_SLAVE_S_SYNC_IN_DATA_PROVIDED_FLAG         (0x02u)
#define ETHTSYN_TIME_VALID_SLAVE_S_FUP_DATA_PROVIDED_FLAG             (0x04u)
#define ETHTSYN_TIME_VALID_SLAVE_S_CURR_PDELAY_PROVIDED_FLAG          (0x08u)
#define ETHTSYN_TIME_VALID_SLAVE_S_BUS_SET_GLOBAL_TIME_CALLED_FLAG    (0x10u)
#define ETHTSYN_TIME_VALID_SLAVE_S_READY                              (0x1Fu)

#define ETHTSYN_TIME_VALID_PD_REQ_S_INVALID                           (0x00u)
#define ETHTSYN_TIME_VALID_PD_REQ_S_CYCLE_STARTED_FLAG                (0x01u)
#define ETHTSYN_TIME_VALID_PD_REQ_S_REF_TIME_TAKEN_FLAG               (0x02u)
#define ETHTSYN_TIME_VALID_PD_REQ_S_PD_CALC_DATA_PROVIDED_FLAG        (0x04u)
#define ETHTSYN_TIME_VALID_PD_REQ_S_READY                             (0x07u)

#define ETHTSYN_TIME_VALID_PD_RESP_S_INVALID                          (0x00u)
#define ETHTSYN_TIME_VALID_PD_RESP_S_CYCLE_STARTED_FLAG               (0x01u)
#define ETHTSYN_TIME_VALID_PD_RESP_S_REF_TIME_TAKEN_FLAG              (0x02u)
#define ETHTSYN_TIME_VALID_PD_RESP_S_PD_REQ_DATA_PROVIDED_FLAG        (0x04u)
#define ETHTSYN_TIME_VALID_PD_RESP_S_PD_RESP_EGR_TS_PROVIDED_FLAG     (0x08u)
#define ETHTSYN_TIME_VALID_PD_RESP_S_PD_RESP_FUP_SENT_FLAG            (0x10u)
#define ETHTSYN_TIME_VALID_PD_RESP_S_READY                            (0x1Fu)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHTSYN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * MASTER DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterInit
 *********************************************************************************************************************/
/*! \brief          Initializes all time validation variables directly related to the master data reporting
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterInit(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterReportAllPendingData
 *********************************************************************************************************************/
/*! \brief          Reports all pending and complete time validation master data set to the StbM
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterReportAllPendingData(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterSetStateFlag
 *********************************************************************************************************************/
/*! \brief          Sets the passed flag(s) within the master data state bit-field
 *  \details        -
 *  \param[in]      MasterDataIdx  Index of the master data
 *                                 [range: MasterDataIdx < EthTSyn_GetSizeOfTimeValidMasterCfg()]
 *  \param[in]      Flag           The flag(s) to be set
 *  \pre            Has to be called with disabled interrupts to ensure data consistency
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterSetStateFlag(
  EthTSyn_SizeOfTimeValidMasterDataType MasterDataIdx,
  uint8                                 Flag);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterReportData
 *********************************************************************************************************************/
/*! \brief          Reports the master data to the StbM in case all information are available.
 *  \details        -
 *  \param[in]      MasterDataIdx  Index of the master data
 *                                 [range: MasterDataIdx < EthTSyn_GetSizeOfTimeValidMasterCfg()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterReportData(
  EthTSyn_TimeValidMasterDataIterType MasterDataIdx);
#endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * SLAVE DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveInit
 *********************************************************************************************************************/
/*! \brief          Initializes all time validation variables directly related to the slave data reporting
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveInit(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveReportAllPendingData
 *********************************************************************************************************************/
/*! \brief          Reports all pending and complete time validation slave data set to the StbM
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveReportAllPendingData(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveSetStateFlag
 *********************************************************************************************************************/
/*! \brief          Sets the passed flag(s) within the master data state bit-field
 *  \details        -
 *  \param[in]      SlaveDataIdx  Index of the master data
 *                                [range: SlaveDataIdx < EthTSyn_GetSizeOfTimeValidSlaveCfg()]
 *  \param[in]      Flag          The flag(s) to be set
 *  \pre            Has to be called with disabled interrupts to ensure data consistency
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveSetStateFlag(
  EthTSyn_SizeOfTimeValidSlaveDataType SlaveDataIdx,
  uint8                                Flag);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveReportData
 *********************************************************************************************************************/
/*! \brief          Reports the master data to the StbM in case all information are available.
 *  \details        -
 *  \param[in]      SlaveDataIdx  Index of the master data
 *                                [range: SlaveDataIdx < EthTSyn_GetSizeOfTimeValidSlaveCfg()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveReportData(
  EthTSyn_TimeValidSlaveDataIterType SlaveDataIdx);
#endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY INITIATOR DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqInit
 *********************************************************************************************************************/
/*! \brief          Initializes all time validation variables directly related to the pdelay initiator data reporting
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqInit(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqReportAllPendingData
 *********************************************************************************************************************/
/*! \brief          Reports all pending and complete time validation pdelay initiator data sets to the StbM
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqReportAllPendingData(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqSetStateFlag
 *********************************************************************************************************************/
/*! \brief          Sets the passed flag(s) within the pdelay initiator data state bit-field
 *  \details        -
 *  \param[in]      PdReqDataIdx  Index of the pdelay initiator data
 *                                [range: PdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdReqCfg()]
 *  \param[in]      Flag          The flag(s) to be set
 *  \pre            Has to be called with disabled interrupts to ensure data consistency
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqSetStateFlag(
  EthTSyn_SizeOfTimeValidPdReqDataType PdReqDataIdx,
  uint8                                Flag);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqReportData
 *********************************************************************************************************************/
/*! \brief          Reports the pdelay initiator data to the StbM in case all information are available.
 *  \details        -
 *  \param[in]      PdReqDataIdx  Index of the pdelay responder data
 *                                [range: PdReqDataIdx < EthTSyn_GetSizeOfTimeValidPdReqCfg()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqReportData(
  EthTSyn_TimeValidPdReqCfgIterType PdReqDataIdx);
#endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY RESPONDER DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespInit
 *********************************************************************************************************************/
/*! \brief          Initializes all time validation variables directly related to the pdelay responder data reporting
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespInit(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespReportAllPendingData
 *********************************************************************************************************************/
/*! \brief          Reports all pending and complete time validation pdelay responder data sets to the StbM
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespReportAllPendingData(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespSetStateFlag
 *********************************************************************************************************************/
/*! \brief          Sets the passed flag(s) within the pdelay responder data state bit-field
 *  \details        -
 *  \param[in]      PdRespDataIdx  Index of the pdelay responder data
 *                                 [range: PdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdRespCfg()]
 *  \param[in]      Flag           The flag(s) to be set
 *  \pre            Has to be called with disabled interrupts to ensure data consistency
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespSetStateFlag(
  EthTSyn_SizeOfTimeValidPdRespDataType PdRespDataIdx,
  uint8                                 Flag);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespReportData
 *********************************************************************************************************************/
/*! \brief          Reports the pdelay responder data to the StbM in case all information are available.
 *  \details        -
 *  \param[in]      PdRespDataIdx  Index of the pdelay responder data
 *                                 [range: PdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdRespCfg()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespReportData(
  EthTSyn_TimeValidPdRespCfgIterType PdRespDataIdx);
#endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * MASTER DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidMasterDataIterType masterDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation master data. */
  for(masterDataIter = 0u;
      masterDataIter < EthTSyn_GetSizeOfTimeValidMasterData();
      masterDataIter++)
  {
    /* #20 Reset the state flag. */
    EthTSyn_SetStateFlagsOfTimeValidMasterData(masterDataIter, ETHTSYN_TIME_VALID_MASTER_S_INVALID);                   /* SBSW_ETHTSYN_CSL01 */
  }
} /* EthTSyn_TimeValid_MasterInit() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterReportAllPendingData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterReportAllPendingData(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidMasterDataIterType masterDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation master data. */
  for(masterDataIter = 0u;
      masterDataIter < EthTSyn_GetSizeOfTimeValidMasterData();
      masterDataIter++)
  {
    /* #20 Report the master data to the StbM in case the data set is complete. */
    EthTSyn_TimeValid_MasterReportData(masterDataIter);
  }
} /* EthTSyn_TimeValid_MasterReportAllPendingData() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterSetStateFlag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterSetStateFlag(
  EthTSyn_SizeOfTimeValidMasterDataType MasterDataIdx,
  uint8                                 Flag)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 stateFlagVal = EthTSyn_GetStateFlagsOfTimeValidMasterData(MasterDataIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the passed Flag within the state flags of the time validation master data. */
  stateFlagVal |= Flag;
  EthTSyn_SetStateFlagsOfTimeValidMasterData(MasterDataIdx, stateFlagVal);                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_TimeValid_MasterSetStateFlag() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterReportData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterReportData(
  EthTSyn_TimeValidMasterDataIterType MasterDataIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean reportData = FALSE;
  StbM_EthTimeMasterMeasurementType masterData = { 0 };

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();
  /* #10 Check if a complete master data set is available. */
  if(EthTSyn_GetStateFlagsOfTimeValidMasterData(MasterDataIdx) == ETHTSYN_TIME_VALID_MASTER_S_READY)
  {
    /* #20 Get all required master data for later reporting and invalidate the master data set. */
    masterData.sequenceId = EthTSyn_GetSequenceIdOfTimeValidMasterData(MasterDataIdx);
    masterData.sourcePortId.clockIdentity = EthTSyn_GetSrcClockIdOfTimeValidMasterData(MasterDataIdx);
    masterData.sourcePortId.portNumber = EthTSyn_GetSrcPortNumOfTimeValidMasterData(MasterDataIdx);
    masterData.preciseOriginTimestamp = EthTSyn_GetPreciseOriginTimestampOfTimeValidMasterData(MasterDataIdx);
    masterData.syncEgressTimestamp =
      EthTSyn_UtilVlt_IntVltToVlt(EthTSyn_GetSyncEgressTsVltOfTimeValidMasterData(MasterDataIdx));
    masterData.correctionField = EthTSyn_GetCorrectionFieldOfTimeValidMasterData(MasterDataIdx);

    EthTSyn_SetStateFlagsOfTimeValidMasterData(MasterDataIdx, ETHTSYN_TIME_VALID_MASTER_S_INVALID);                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    reportData = TRUE;
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();

  /* #30 Report master data to the StbM via StbM_EthSetMasterTimingData() if applicable. */
  if(reportData == TRUE)
  {
    (void)StbM_EthSetMasterTimingData(
      EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidMasterCfg(MasterDataIdx), &masterData);                              /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  }
} /* EthTSyn_TimeValid_MasterReportData() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * SLAVE DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidSlaveDataIterType slaveDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation master data. */
  for(slaveDataIter = 0u;
      slaveDataIter < EthTSyn_GetSizeOfTimeValidSlaveData();
      slaveDataIter++)
  {
    /* #20 Reset the state flag. */
    EthTSyn_SetStateFlagsOfTimeValidSlaveData(slaveDataIter, ETHTSYN_TIME_VALID_SLAVE_S_INVALID);                      /* SBSW_ETHTSYN_CSL01 */
  }
} /* EthTSyn_TimeValid_SlaveInit() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveReportAllPendingData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveReportAllPendingData(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidSlaveDataIterType slaveDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation master data. */
  for(slaveDataIter = 0u;
      slaveDataIter < EthTSyn_GetSizeOfTimeValidSlaveData();
      slaveDataIter++)
  {
    /* #20 Report the slave data to the StbM in case the data set is complete. */
    EthTSyn_TimeValid_SlaveReportData(slaveDataIter);
  }
} /* EthTSyn_TimeValid_SlaveReportAllPendingData() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveSetStateFlag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveSetStateFlag(
  EthTSyn_SizeOfTimeValidSlaveDataType SlaveDataIdx,
  uint8                                Flag)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 stateFlagVal = EthTSyn_GetStateFlagsOfTimeValidSlaveData(SlaveDataIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the passed Flag within the state flags of the time validation slave data. */
  stateFlagVal |= Flag;
  EthTSyn_SetStateFlagsOfTimeValidSlaveData(SlaveDataIdx, stateFlagVal);                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_TimeValid_SlaveSetStateFlag() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveReportData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveReportData(
  EthTSyn_TimeValidSlaveDataIterType SlaveDataIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean reportData = FALSE;
  StbM_EthTimeSlaveMeasurementType slaveData = { 0 };

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();
  /* #10 Check if a complete master data set is available. */
  if(EthTSyn_GetStateFlagsOfTimeValidSlaveData(SlaveDataIdx) == ETHTSYN_TIME_VALID_SLAVE_S_READY)
  {
    /* #20 Get all required slave data for later reporting and invalidate the master data set. */
    slaveData.sequenceId = EthTSyn_GetSequenceIdOfTimeValidSlaveData(SlaveDataIdx);
    slaveData.sourcePortId.portNumber = EthTSyn_GetMasterPortNumOfTimeValidSlaveData(SlaveDataIdx);
    slaveData.sourcePortId.clockIdentity = EthTSyn_GetMasterClockIdOfTimeValidSlaveData(SlaveDataIdx);
    slaveData.syncIngressTimestamp =
      EthTSyn_UtilVlt_IntVltToVlt(EthTSyn_GetSyncIngressTsVltOfTimeValidSlaveData(SlaveDataIdx));
    slaveData.preciseOriginTimestamp = EthTSyn_GetPreciseOriginTimestampOfTimeValidSlaveData(SlaveDataIdx);
    slaveData.correctionField = EthTSyn_GetCorrectionFieldOfTimeValidSlaveData(SlaveDataIdx);
    slaveData.pDelay = EthTSyn_GetCurrPdelayOfTimeValidSlaveData(SlaveDataIdx);

    slaveData.referenceGlobalTimestamp.seconds = 0u;
    slaveData.referenceGlobalTimestamp.nanoseconds = 0u;
    slaveData.referenceLocalTimestamp.nanosecondsHi = 0u;
    slaveData.referenceLocalTimestamp.nanosecondsLo = 0u;

    EthTSyn_SetStateFlagsOfTimeValidSlaveData(SlaveDataIdx, ETHTSYN_TIME_VALID_SLAVE_S_INVALID);                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    reportData = TRUE;
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();

  /* #30 Report slave data to the StbM via StbM_EthSetSlaveTimingData() if applicable. */
  if(reportData == TRUE)
  {
    (void)StbM_EthSetSlaveTimingData(
      EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidSlaveCfg(SlaveDataIdx), &slaveData);                                 /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  }
} /* EthTSyn_TimeValid_SlaveReportData() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY INITIATOR DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidPdReqDataIterType pdReqDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation pdelay initiator data. */
  for(pdReqDataIter = 0u;
      pdReqDataIter < EthTSyn_GetSizeOfTimeValidPdReqData();
      pdReqDataIter++)
  {
    /* #20 Reset the state flag. */
    EthTSyn_SetStateFlagsOfTimeValidPdReqData(pdReqDataIter, ETHTSYN_TIME_VALID_PD_REQ_S_INVALID);                     /* SBSW_ETHTSYN_CSL01 */
  }
} /* EthTSyn_TimeValid_PdReqInit() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqReportAllPendingData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqReportAllPendingData(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidPdReqDataIterType pdReqDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation pdelay initiator data. */
  for(pdReqDataIter = 0u;
      pdReqDataIter < EthTSyn_GetSizeOfTimeValidPdReqData();
      pdReqDataIter++)
  {
    /* #20 Report the pdelay initiator data to the StbM in case the data set is complete. */
    EthTSyn_TimeValid_PdReqReportData(pdReqDataIter);
  }
} /* EthTSyn_TimeValid_PdReqReportAllPendingData() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqSetStateFlag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqSetStateFlag(
  EthTSyn_SizeOfTimeValidPdReqDataType PdReqDataIdx,
  uint8                                Flag)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 stateFlagVal = EthTSyn_GetStateFlagsOfTimeValidPdReqData(PdReqDataIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the passed Flag within the state flags of the time validation pdelay initiator data. */
  stateFlagVal |= Flag;
  EthTSyn_SetStateFlagsOfTimeValidPdReqData(PdReqDataIdx, stateFlagVal);                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_TimeValid_PdReqSetStateFlag() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqReportData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqReportData(
  EthTSyn_TimeValidPdReqCfgIterType PdReqDataIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean reportData = FALSE;
  StbM_PdelayInitiatorMeasurementType pdReqData = { 0 };

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();
  /* #10 Check if a complete master data set is available. */
  if(EthTSyn_GetStateFlagsOfTimeValidPdReqData(PdReqDataIdx) == ETHTSYN_TIME_VALID_PD_REQ_S_READY)
  {
    /* #20 Get all required pdelay initiator data for later reporting and invalidate the pdelay initiator data set. */
    pdReqData.sequenceId = EthTSyn_GetSequenceIdOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.requestPortId.portNumber = EthTSyn_GetSrcPortNumOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.requestPortId.clockIdentity = EthTSyn_GetSrcClockIdOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.responsePortId.portNumber = EthTSyn_GetPdRespPortNumOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.responsePortId.clockIdentity = EthTSyn_GetPdRespClockIdOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.requestOriginTimestamp =
      EthTSyn_UtilVlt_IntVltToVlt(EthTSyn_GetPdReqEgressTsVltOfTimeValidPdReqData(PdReqDataIdx));
    pdReqData.requestReceiptTimestamp = EthTSyn_GetPdReqRcvdTsOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.responseReceiptTimestamp =
      EthTSyn_UtilVlt_IntVltToVlt(EthTSyn_GetPdRespIngressTsVltOfTimeValidPdReqData(PdReqDataIdx));
    pdReqData.responseOriginTimestamp = EthTSyn_GetPdRespSentTsOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.pdelay = EthTSyn_GetCurrPdelayOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.referenceGlobalTimestamp = EthTSyn_GetRefTimeGlobalOfTimeValidPdReqData(PdReqDataIdx);
    pdReqData.referenceLocalTimestamp = EthTSyn_GetRefTimeVltOfTimeValidPdReqData(PdReqDataIdx);


    EthTSyn_SetStateFlagsOfTimeValidPdReqData(PdReqDataIdx, ETHTSYN_TIME_VALID_PD_REQ_S_INVALID);                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    reportData = TRUE;
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();

  /* #30 Report pdelay initiator data to the StbM via StbM_EthSetPdelayInitiatorData() if applicable. */
  if(reportData == TRUE)
  {
    (void)StbM_EthSetPdelayInitiatorData(
      EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdReqCfg(PdReqDataIdx), &pdReqData);                                 /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  }
} /* EthTSyn_TimeValid_PdReqReportData() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY RESPONDER DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidPdRespDataIterType pdRespDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation pdelay responder data. */
  for(pdRespDataIter = 0u;
      pdRespDataIter < EthTSyn_GetSizeOfTimeValidPdRespData();
      pdRespDataIter++)
  {
    /* #20 Reset the state flag. */
    EthTSyn_SetStateFlagsOfTimeValidPdRespData(pdRespDataIter, ETHTSYN_TIME_VALID_PD_RESP_S_INVALID);                  /* SBSW_ETHTSYN_CSL01 */
  }
} /* EthTSyn_TimeValid_PdRespInit() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespReportAllPendingData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespReportAllPendingData(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeValidPdRespDataIterType pdRespDataIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all time validation pdelay responder data. */
  for(pdRespDataIter = 0u;
      pdRespDataIter < EthTSyn_GetSizeOfTimeValidPdRespData();
      pdRespDataIter++)
  {
    /* #20 Report the pdelay responder data to the StbM in case the data set is complete. */
    EthTSyn_TimeValid_PdRespReportData(pdRespDataIter);
  }
} /* EthTSyn_TimeValid_PdRespReportAllPendingData() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespSetStateFlag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespSetStateFlag(
  EthTSyn_SizeOfTimeValidPdRespDataType PdRespDataIdx,
  uint8                                 Flag)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 stateFlagVal = EthTSyn_GetStateFlagsOfTimeValidPdRespData(PdRespDataIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the passed Flag within the state flags of the time validation pdelay responder data. */
  stateFlagVal |= Flag;
  EthTSyn_SetStateFlagsOfTimeValidPdRespData(PdRespDataIdx, stateFlagVal);                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_TimeValid_PdRespSetStateFlag() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespReportData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespReportData(
  EthTSyn_TimeValidPdRespCfgIterType PdRespDataIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean reportData = FALSE;
  StbM_PdelayResponderMeasurementType pdRespData = { 0 };

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();
  /* #10 Check if a complete master data set is available. */
  if(EthTSyn_GetStateFlagsOfTimeValidPdRespData(PdRespDataIdx) == ETHTSYN_TIME_VALID_PD_RESP_S_READY)
  {
    /* #20 Get all required pdelay responder data for later reporting and invalidate the pdelay responder data set. */
    pdRespData.sequenceId = EthTSyn_GetSequenceIdOfTimeValidPdRespData(PdRespDataIdx);
    pdRespData.responsePortId.portNumber = EthTSyn_GetSrcPortNumOfTimeValidPdRespData(PdRespDataIdx);
    pdRespData.responsePortId.clockIdentity = EthTSyn_GetSrcClockIdOfTimeValidPdRespData(PdRespDataIdx);
    pdRespData.requestPortId.portNumber = EthTSyn_GetPdReqPortNumOfTimeValidPdRespData(PdRespDataIdx);
    pdRespData.requestPortId.clockIdentity = EthTSyn_GetPdReqClockIdOfTimeValidPdRespData(PdRespDataIdx);
    pdRespData.requestReceiptTimestamp =
      EthTSyn_UtilVlt_IntVltToVlt(EthTSyn_GetPdReqIngressTsVltOfTimeValidPdRespData(PdRespDataIdx));
    pdRespData.responseOriginTimestamp =
      EthTSyn_UtilVlt_IntVltToVlt(EthTSyn_GetPdRespEgressTsVltOfTimeValidPdRespData(PdRespDataIdx));
    pdRespData.referenceLocalTimestamp = EthTSyn_GetRefTimeVltOfTimeValidPdRespData(PdRespDataIdx);
    pdRespData.referenceGlobalTimestamp = EthTSyn_GetRefTimeGlobalOfTimeValidPdRespData(PdRespDataIdx);

    EthTSyn_SetStateFlagsOfTimeValidPdRespData(PdRespDataIdx, ETHTSYN_TIME_VALID_PD_RESP_S_INVALID);                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    reportData = TRUE;
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();

  /* #30 Report pdelay responder data to the StbM via StbM_EthSetPdelayResponderData() if applicable. */
  if(reportData == TRUE)
  {
    (void)StbM_EthSetPdelayResponderData(                                                                              /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdRespCfg(PdRespDataIdx), &pdRespData);
  }
} /* EthTSyn_TimeValid_PdRespReportData() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_Init
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
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_Init(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If master time validation is enabled. */
# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
  {
    /* #100 Initialize time validation master data. */
    EthTSyn_TimeValid_MasterInit();                                                                                     /* PRQA S 2987 */ /* MD_EthTSyn_2987_GlobalDataInit */

    /* #101 Initialize time validation pdelay responder data. */
    EthTSyn_TimeValid_PdRespInit();                                                                                     /* PRQA S 2987 */ /* MD_EthTSyn_2987_GlobalDataInit */
  }
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

  /* #20 If slave time validation is enabled. */
# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
  {
    /* #200 Initialize time validation slave data. */
    EthTSyn_TimeValid_SlaveInit();                                                                                      /* PRQA S 2987 */ /* MD_EthTSyn_2987_GlobalDataInit */

    /* #201 Initialize time validation pdelay initiator data. */
    EthTSyn_TimeValid_PdReqInit();                                                                                      /* PRQA S 2987 */ /* MD_EthTSyn_2987_GlobalDataInit */
  }
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */
} /* EthTSyn_TimeValid_Init() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MainFunction
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
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MainFunction(void)
{
  /* #10 If master time validation is enabled. */
# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
  {
    /* #100 Report all pending master data to the StbM. */
    EthTSyn_TimeValid_MasterReportAllPendingData();

    /* #101 Report all pending pdelay responder data to the StbM. */
    EthTSyn_TimeValid_PdRespReportAllPendingData();
  }
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

  /* #20 If slave time validation is enabled. */
# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
  {
    /* #200 Report all pending slave data to the StbM. */
    EthTSyn_TimeValid_SlaveReportAllPendingData();

    /* #201 Report all pending pdelay initiator data to the StbM. */
    EthTSyn_TimeValid_PdReqReportAllPendingData();
  }
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */
} /* EthTSyn_TimeValid_MainFunction() */
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

/**********************************************************************************************************************
 * MASTER DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterStartCycle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidMasterCfgIdxOfPortType masterDataIdx = EthTSyn_GetTimeValidMasterCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if master data reporting is required. */
  if(masterDataIdx < EthTSyn_GetSizeOfTimeValidMasterCfg())
  {
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);

    /* #20 Trigger reporting of potential pending old master data. */
    EthTSyn_TimeValid_MasterReportData(masterDataIdx);

    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #30 Store the sequence id and source port identity of the master for later processing. */
    EthTSyn_SetSequenceIdOfTimeValidMasterData(masterDataIdx, SequenceId);                                             /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSrcPortNumOfTimeValidMasterData(masterDataIdx, EthTSyn_GetNumberOfPort(PortIdx));                       /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSrcClockIdOfTimeValidMasterData(masterDataIdx, EthTSyn_GetCtrlState(ctrlIdx).ClockIdentity);            /* SBSW_ETHTSYN_CSL02 */

    /* #40 Set state of master data to cycle started. */
    EthTSyn_SetStateFlagsOfTimeValidMasterData(masterDataIdx, ETHTSYN_TIME_VALID_MASTER_S_CYCLE_STARTED_FLAG);         /* SBSW_ETHTSYN_CSL02 */

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_MasterStartCycle() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterProvideData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterProvideSyncEgressTs(
  EthTSyn_IntPortIdxType PortIdx,
  EthTSyn_IntVltType     SyncEgressVlt)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidMasterCfgIdxOfPortType masterDataIdx = EthTSyn_GetTimeValidMasterCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if master data reporting is required. */
  if(masterDataIdx < EthTSyn_GetSizeOfTimeValidMasterCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Store the provided sync egress timestamp for later processing. */
    EthTSyn_SetSyncEgressTsVltOfTimeValidMasterData(masterDataIdx, SyncEgressVlt);                                     /* SBSW_ETHTSYN_CSL02 */

    /* #30 Set sync egress timestamp provided flag in the master data state field. */
    EthTSyn_TimeValid_MasterSetStateFlag(masterDataIdx, ETHTSYN_TIME_VALID_MASTER_S_SYNC_EGR_TS_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_MasterProvideSyncEgressTs() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterProvideFupData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterProvideFupData(
                  EthTSyn_IntPortIdxType       PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PotPtr,
                  sint64                       CorrField)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidMasterCfgIdxOfPortType masterDataIdx = EthTSyn_GetTimeValidMasterCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if master data reporting is required. */
  if(masterDataIdx < EthTSyn_GetSizeOfTimeValidMasterCfg())
  {
    StbM_TimeStampShortType pot;

    pot.seconds = PotPtr->seconds;
    pot.nanoseconds = PotPtr->nanoseconds;
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Store the provided master data for later processing. */
    EthTSyn_SetPreciseOriginTimestampOfTimeValidMasterData(masterDataIdx, pot);                                        /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetCorrectionFieldOfTimeValidMasterData(masterDataIdx, CorrField);                                         /* SBSW_ETHTSYN_CSL02 */

    /* #30 Set master data provided flag in the master data state field. */
    EthTSyn_TimeValid_MasterSetStateFlag(masterDataIdx, ETHTSYN_TIME_VALID_MASTER_S_DATA_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_MasterProvideFupData() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterFollowUpSent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterFollowUpSent(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidMasterCfgIdxOfPortType masterDataIdx = EthTSyn_GetTimeValidMasterCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if master data reporting is required. */
  if(masterDataIdx < EthTSyn_GetSizeOfTimeValidMasterCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Set FollowUp sent flag in the master data state field. */
    EthTSyn_TimeValid_MasterSetStateFlag(masterDataIdx, ETHTSYN_TIME_VALID_MASTER_S_FUP_SENT_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_MasterFollowUpSent() */
#endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * SLAVE DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveStartCycle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidSlaveCfgIdxOfPortType slaveDataIdx = EthTSyn_GetTimeValidSlaveCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if slave data reporting is required. */
  if(slaveDataIdx < EthTSyn_GetSizeOfTimeValidSlaveCfg())
  {
    /* #20 Trigger reporting of potential pending old slave data. */
    EthTSyn_TimeValid_SlaveReportData(slaveDataIdx);

    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #30 Store the sequence id for later processing. */
    EthTSyn_SetSequenceIdOfTimeValidSlaveData(slaveDataIdx, SequenceId);                                               /* SBSW_ETHTSYN_CSL02 */

    /* #40 Set state of slave data to cycle started. */
    EthTSyn_SetStateFlagsOfTimeValidSlaveData(slaveDataIdx, ETHTSYN_TIME_VALID_SLAVE_S_CYCLE_STARTED_FLAG);            /* SBSW_ETHTSYN_CSL02 */

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_SlaveStartCycle() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveProvideSyncIngressData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveProvideSyncIngressData(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) SrcPortIdPtr,
                  EthTSyn_IntVltType        SyncIngressVlt)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidSlaveCfgIdxOfPortType slaveDataIdx = EthTSyn_GetTimeValidSlaveCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if slave data reporting is required. */
  if(slaveDataIdx < EthTSyn_GetSizeOfTimeValidSlaveCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Store the master port identity and the sync ingress timestamp for later processing. */
    EthTSyn_SetMasterPortNumOfTimeValidSlaveData(slaveDataIdx, SrcPortIdPtr->PortNumber);                              /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetMasterClockIdOfTimeValidSlaveData(slaveDataIdx, SrcPortIdPtr->ClockIdentity);                           /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSyncIngressTsVltOfTimeValidSlaveData(slaveDataIdx, SyncIngressVlt);                                     /* SBSW_ETHTSYN_CSL02 */

    /* #30 Set Sync ingress data provided flag in the slave data state field. */
    EthTSyn_TimeValid_SlaveSetStateFlag(slaveDataIdx, ETHTSYN_TIME_VALID_SLAVE_S_SYNC_IN_DATA_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_SlaveProvideSyncIngressData() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveProvideFollowUpData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveProvideFollowUpData(
                  EthTSyn_IntPortIdxType       PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PotPtr,
                  sint64                       CorrField)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidSlaveCfgIdxOfPortType slaveDataIdx = EthTSyn_GetTimeValidSlaveCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if slave data reporting is required. */
  if(slaveDataIdx < EthTSyn_GetSizeOfTimeValidSlaveCfg())
  {
    StbM_TimeStampShortType pot;

    pot.seconds = PotPtr->seconds;
    pot.nanoseconds = PotPtr->nanoseconds;
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Store the precise origin timestamp and the correction field value for later processing. */
    EthTSyn_SetPreciseOriginTimestampOfTimeValidSlaveData(slaveDataIdx, pot);                                          /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetCorrectionFieldOfTimeValidSlaveData(slaveDataIdx, CorrField);                                           /* SBSW_ETHTSYN_CSL02 */

    /* #30 Set the FollowUp data provided flag in the slave data state field. */
    EthTSyn_TimeValid_SlaveSetStateFlag(slaveDataIdx, ETHTSYN_TIME_VALID_SLAVE_S_FUP_DATA_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_SlaveProvideFollowUpData() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveProvideCurrPdelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveProvideCurrPdelay(
  EthTSyn_IntPortIdxType PortIdx,
  EthTSyn_PdelayType     CurrPdelay)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidSlaveCfgIdxOfPortType slaveDataIdx = EthTSyn_GetTimeValidSlaveCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if slave data reporting is required. */
  if(slaveDataIdx < EthTSyn_GetSizeOfTimeValidSlaveCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Store the current Pdelay for later processing. */
    EthTSyn_SetCurrPdelayOfTimeValidSlaveData(slaveDataIdx, CurrPdelay);                                               /* SBSW_ETHTSYN_CSL02 */

    /* #30 Set the current Pdelay provided flag in the slave data state field. */
    EthTSyn_TimeValid_SlaveSetStateFlag(slaveDataIdx, ETHTSYN_TIME_VALID_SLAVE_S_CURR_PDELAY_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_SlaveProvideCurrPdelay() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveBusSetGlobalTimeCalled
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveBusSetGlobalTimeCalled(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidSlaveCfgIdxOfPortType slaveDataIdx = EthTSyn_GetTimeValidSlaveCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if slave data reporting is required. */
  if(slaveDataIdx < EthTSyn_GetSizeOfTimeValidSlaveCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #30 Set the StbM_BusSetGlobalTimeCalled flag in the slave data state field. */
    EthTSyn_TimeValid_SlaveSetStateFlag(slaveDataIdx, ETHTSYN_TIME_VALID_SLAVE_S_BUS_SET_GLOBAL_TIME_CALLED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_SlaveBusSetGlobalTimeCalled() */
#endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY INITIATOR DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqStartCycle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdReqCfgIdxOfPortType pdReqDataIdx = EthTSyn_GetTimeValidPdReqCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdReqDataIdx < EthTSyn_GetSizeOfTimeValidPdReqCfg())
  {
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);

    /* #20 Trigger reporting of potential pending old pdelay initiator data. */
    EthTSyn_TimeValid_PdReqReportData(pdReqDataIdx);

    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #30 Store the sequence id and source port identity of the pdelay initiator for later processing. */
    EthTSyn_SetSequenceIdOfTimeValidPdReqData(pdReqDataIdx, SequenceId);                                               /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSrcPortNumOfTimeValidPdReqData(pdReqDataIdx, EthTSyn_GetNumberOfPort(PortIdx));                         /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSrcClockIdOfTimeValidPdReqData(pdReqDataIdx, EthTSyn_GetCtrlState(ctrlIdx).ClockIdentity);              /* SBSW_ETHTSYN_CSL02 */

    /* #40 Set state of pdelay initiator data to cycle started. */
    EthTSyn_SetStateFlagsOfTimeValidPdReqData(pdReqDataIdx, ETHTSYN_TIME_VALID_PD_REQ_S_CYCLE_STARTED_FLAG);           /* SBSW_ETHTSYN_CSL02 */

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_PdReqStartCycle() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqTakeRefTimes
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqTakeRefTimes(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdReqCfgIdxOfPortType pdReqDataIdx = EthTSyn_GetTimeValidPdReqCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdReqDataIdx < EthTSyn_GetSizeOfTimeValidPdReqCfg())
  {
    StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdReqCfg(pdReqDataIdx);
    StbM_TimeStampType globalTime = { 0u, 0u, 0u, 0u };
    StbM_VirtualLocalTimeType vlt = { 0u, 0u };
    StbM_UserDataType userData = { 0u, 0u, 0u, 0u };

    /* #20 Get the reference time tuple via StbM_BusGetCurrentTime().
     *     In case reference time tuple was successfully retrieved. */
    if(StbM_BusGetCurrentTime(timeBaseId, &globalTime, &vlt, &userData) == E_OK)                                       /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      StbM_TimeStampShortType refTimeGlobal;

      ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

      /* #30 Store the reference time tuple for later reporting. */
      refTimeGlobal.seconds = globalTime.seconds;
      refTimeGlobal.nanoseconds = globalTime.nanoseconds;

      EthTSyn_SetRefTimeGlobalOfTimeValidPdReqData(pdReqDataIdx, refTimeGlobal);                                       /* SBSW_ETHTSYN_CSL02 */
      EthTSyn_SetRefTimeVltOfTimeValidPdReqData(pdReqDataIdx, vlt);                                                    /* SBSW_ETHTSYN_CSL02 */

      /* #40 Set the reference time taken flag in the pdelay initiator state field. */
      EthTSyn_TimeValid_PdReqSetStateFlag(pdReqDataIdx, ETHTSYN_TIME_VALID_PD_REQ_S_REF_TIME_TAKEN_FLAG);

      ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
    }
  }
} /* EthTSyn_TimeValid_PdReqTakeRefTimes() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqCopyDataFromSm
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
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqCopyDataFromSm(
                  EthTSyn_IntPortIdxType   PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PdelayReqSmType) PdReqSmPtr,
                  uint32                   CurrPdelay)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdReqCfgIdxOfPortType pdReqDataIdx = EthTSyn_GetTimeValidPdReqCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdReqDataIdx < EthTSyn_GetSizeOfTimeValidPdReqCfg())
  {
    StbM_TimeStampShortType pdReqRcvdTs;
    StbM_TimeStampShortType pdRespSentTs;

    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    pdReqRcvdTs.seconds = PdReqSmPtr->PdelayResp.RequestReceiptTimestamp.seconds;
    pdReqRcvdTs.nanoseconds = PdReqSmPtr->PdelayResp.RequestReceiptTimestamp.nanoseconds;
    pdRespSentTs.seconds = PdReqSmPtr->PdelayRespFollowUp.RespOrgTs.seconds;
    pdRespSentTs.nanoseconds = PdReqSmPtr->PdelayRespFollowUp.RespOrgTs.nanoseconds;

    /* #20 Store the egress timestamp of the transmitted Pdelay_Req for later reporting. */
    EthTSyn_SetPdReqEgressTsVltOfTimeValidPdReqData(pdReqDataIdx,                                                      /* SBSW_ETHTSYN_CSL02 */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      EthTSyn_UtilVlt_TsToIntVlt(&PdReqSmPtr->PdelayReq.EgressTsMgmt.Ts));

    /* #30 Store the information of the received Pdelay_Resp for later reporting. */
    EthTSyn_SetPdReqRcvdTsOfTimeValidPdReqData(pdReqDataIdx, pdReqRcvdTs);                                             /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetPdRespPortNumOfTimeValidPdReqData(pdReqDataIdx, PdReqSmPtr->PdelayResp.SourcePortIdentity.PortNumber);  /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetPdRespClockIdOfTimeValidPdReqData(pdReqDataIdx,                                                         /* SBSW_ETHTSYN_CSL02 */
      PdReqSmPtr->PdelayResp.SourcePortIdentity.ClockIdentity);
    EthTSyn_SetPdRespIngressTsVltOfTimeValidPdReqData(pdReqDataIdx,                                                    /* SBSW_ETHTSYN_CSL02 */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      EthTSyn_UtilVlt_TsToIntVlt(&PdReqSmPtr->PdelayResp.IngressTsMgmt.Ts));

    /* #40 Store the information of the received Pdelay_Resp_Fup for later reporting. */
    EthTSyn_SetPdRespSentTsOfTimeValidPdReqData(pdReqDataIdx, pdRespSentTs);                                           /* SBSW_ETHTSYN_CSL02 */

    /* #50 Store the current pdelay for later reporting. */
    EthTSyn_SetCurrPdelayOfTimeValidPdReqData(pdReqDataIdx, CurrPdelay);                                               /* SBSW_ETHTSYN_CSL02 */

    /* #60 Set the pDelay data provided flag in the pdelay initiator state field. */
    EthTSyn_TimeValid_PdReqSetStateFlag(pdReqDataIdx, ETHTSYN_TIME_VALID_PD_REQ_S_PD_CALC_DATA_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_PdReqCopyDataFromSm() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY RESPONDER DATA REPORTING
 *********************************************************************************************************************/
#if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespStartCycle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdRespCfgIdxOfPortType pdRespDataIdx = EthTSyn_GetTimeValidPdRespCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdRespCfg())
  {
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);

    /* #20 Trigger reporting of potential pending old pdelay responder data. */
    EthTSyn_TimeValid_PdRespReportData(pdRespDataIdx);

    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #30 Store the sequence id and source port identity of the pdelay responder for later processing. */
    EthTSyn_SetSequenceIdOfTimeValidPdRespData(pdRespDataIdx, SequenceId);                                             /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSrcPortNumOfTimeValidPdRespData(pdRespDataIdx, EthTSyn_GetNumberOfPort(PortIdx));                       /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSrcClockIdOfTimeValidPdRespData(pdRespDataIdx, EthTSyn_GetCtrlState(ctrlIdx).ClockIdentity);            /* SBSW_ETHTSYN_CSL02 */

    /* #40 Set state of pdelay responder data to cycle started. */
    EthTSyn_SetStateFlagsOfTimeValidPdRespData(pdRespDataIdx, ETHTSYN_TIME_VALID_PD_RESP_S_CYCLE_STARTED_FLAG);        /* SBSW_ETHTSYN_CSL02 */

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_PdRespStartCycle() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespTakeRefTimes
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespTakeRefTimes(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdRespCfgIdxOfPortType pdRespDataIdx = EthTSyn_GetTimeValidPdRespCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdRespCfg())
  {
    StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdRespCfg(pdRespDataIdx);
    StbM_TimeStampType globalTime = { 0u, 0u, 0u, 0u };
    StbM_VirtualLocalTimeType vlt = { 0u, 0u };
    StbM_UserDataType userData = { 0u, 0u, 0u, 0u };

    /* #20 Get the reference time tuple via StbM_BusGetCurrentTime().
     *     In case reference time tuple was successfully retrieved. */
    if(StbM_BusGetCurrentTime(timeBaseId, &globalTime, &vlt, &userData) == E_OK)                                       /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      StbM_TimeStampShortType refTimeGlobal;

      ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

      /* #30 Store the reference time tuple for later reporting. */
      refTimeGlobal.seconds = globalTime.seconds;
      refTimeGlobal.nanoseconds = globalTime.nanoseconds;

      EthTSyn_SetRefTimeGlobalOfTimeValidPdRespData(pdRespDataIdx, refTimeGlobal);                                     /* SBSW_ETHTSYN_CSL02 */
      EthTSyn_SetRefTimeVltOfTimeValidPdRespData(pdRespDataIdx, vlt);                                                  /* SBSW_ETHTSYN_CSL02 */

      /* #40 Set the reference time taken flag in the pdelay responder state field. */
      EthTSyn_TimeValid_PdRespSetStateFlag(pdRespDataIdx, ETHTSYN_TIME_VALID_PD_RESP_S_REF_TIME_TAKEN_FLAG);

      ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
    }
  }
} /* EthTSyn_TimeValid_PdRespTakeRefTimes() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespProvidePdReqData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespProvidePdReqData(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PdReqPortIdPtr,
                  EthTSyn_IntVltType        PdReqIngressVlt)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdRespCfgIdxOfPortType pdRespDataIdx = EthTSyn_GetTimeValidPdRespCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdRespCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Store the provided data of the received Pdelay_Req for later reporting. */
    EthTSyn_SetPdReqPortNumOfTimeValidPdRespData(pdRespDataIdx, PdReqPortIdPtr->PortNumber);                           /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetPdReqClockIdOfTimeValidPdRespData(pdRespDataIdx, PdReqPortIdPtr->ClockIdentity);                        /* SBSW_ETHTSYN_CSL02 */

    EthTSyn_SetPdReqIngressTsVltOfTimeValidPdRespData(pdRespDataIdx, PdReqIngressVlt);                                 /* SBSW_ETHTSYN_CSL02 */

    /* #30 Set the Pdelay_Req data provided flag in the pdelay responder state field. */
    EthTSyn_TimeValid_PdRespSetStateFlag(pdRespDataIdx, ETHTSYN_TIME_VALID_PD_RESP_S_PD_REQ_DATA_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_PdRespProvidePdReqData() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespProvidePdRespEgressTs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespProvidePdRespEgressTs(
                  EthTSyn_IntPortIdxType       PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PdRespEgressTsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdRespCfgIdxOfPortType pdRespDataIdx = EthTSyn_GetTimeValidPdRespCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdRespCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Store the Pdelay_Resp egress timestamp for later reporting.*/
    EthTSyn_SetPdRespEgressTsVltOfTimeValidPdRespData(pdRespDataIdx, EthTSyn_UtilVlt_TsToIntVlt(PdRespEgressTsPtr));   /* SBSW_ETHTSYN_CSL02 */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

    /* #30 Set the Pdelay_Resp egress timestamp provided flag in the pdelay responder state field. */
    EthTSyn_TimeValid_PdRespSetStateFlag(pdRespDataIdx, ETHTSYN_TIME_VALID_PD_RESP_S_PD_RESP_EGR_TS_PROVIDED_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_PdRespProvidePdRespEgressTs() */

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespPdRespFupSent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespPdRespFupSent(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeValidPdRespCfgIdxOfPortType pdRespDataIdx = EthTSyn_GetTimeValidPdRespCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if pdelay responder data reporting is required. */
  if(pdRespDataIdx < EthTSyn_GetSizeOfTimeValidPdRespCfg())
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID();

    /* #20 Set the Pdelay_Resp_Fup sent flag in the pdelay responder state field. */
    EthTSyn_TimeValid_PdRespSetStateFlag(pdRespDataIdx, ETHTSYN_TIME_VALID_PD_RESP_S_PD_RESP_FUP_SENT_FLAG);

    ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID();
  }
} /* EthTSyn_TimeValid_PdRespPdRespFupSent() */
#endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

#define ETHTSYN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_TimeValidation_Int.c
 *********************************************************************************************************************/
