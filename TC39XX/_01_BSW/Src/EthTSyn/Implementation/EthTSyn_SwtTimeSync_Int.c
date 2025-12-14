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
/*!        \file  EthTSyn_SwtTimeSync_Int.c
 *        \brief  EthTSyn Switch Time Sync source file - Internal functions
 *      \details  EthTSyn Switch Time Sync source file containing the EthTSyn Switch Time Sync implementation of the
 *                EthTSyn module.
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

#define ETHTSYN_SWT_TIME_SYNC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_SwtTimeSync_Int.h"

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#  include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
#  include "EthTSyn_Pdelay_Int.h"
#  include "EthTSyn_Master_Int.h"
#  include "EthTSyn_SwtMgmt_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
#  if (  (ETHTSYN_SW_MAJOR_VERSION != (13u)) \
      || (ETHTSYN_SW_MINOR_VERSION != (2u)) \
      || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#   error "Vendor specific version numbers of EthTSyn_SwtTimeSync_Int.c and EthTSyn.h are inconsistent"
#  endif

/* Check the version of the configuration header file */
#  if (  (ETHTSYN_CFG_MAJOR_VERSION != (13u)) \
      || (ETHTSYN_CFG_MINOR_VERSION != (2u)) )
#   error "Version numbers of EthTSyn_SwtTimeSync_Int.c and EthTSyn_Cfg.h are inconsistent!"
#  endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#  define ETHTSYN_SWT_TIME_SYNC_OUT_OF_SYNC_COUNT_MAX_ALLOWED_VALUE   (255u)

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

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define ETHTSYN_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_InitTimeStampInfo
 *********************************************************************************************************************/
/*! \brief      Initializes the timestamp information of the passed switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                 [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_InitTimeStampInfo(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtSyncFrame
 *********************************************************************************************************************/
/*! \brief      Handles the switch sync frame.
 *  \details    -
 *  \param[in]  SwtSyncFrameCfgIdx   Index of the switch sync frame configuration
 *                                   [range: 0 <= SwtSyncFrameCfgIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtSyncFrame(
  EthTSyn_SizeOfSwitchSyncFrameCfgType SwtSyncFrameCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSyncEventTimeout
 *********************************************************************************************************************/
/*! \brief      Handles the optional sync event timeout of the passed switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                 [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSyncEventTimeout(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtTimeSync
 *********************************************************************************************************************/
/*! \brief      Handles the time synchronization of the passed switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                 [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtTimeSync(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeSwtOffset
 *********************************************************************************************************************/
/*! \brief      Computes the offset of the passed switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[out] SwtOffsetPtr        The computed offset of the switch cascade.
 *                                  Note: Valid for return value of E_OK.
 *  \return     E_OK - Offset calculation succeeded
 *  \return     E_NOT_OK - Offset calculation failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeSwtOffset(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtOffsetPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_GetSyncStateAndCorrActions
 *********************************************************************************************************************/
/*! \brief      Determines the synchronization state and the required correction actions.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx    Index of the switch cascade in context of the EthTSyn
 *                                   [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  SwtOffset            The computed offset of the switch cascade.
 *  \param[out] OfsJumpCorrRequired  Indication if offset jump correction is required.
 *                                    TRUE: offset jump correction is required
 *                                    False: offset jump correction is not required
 *  \param[out] NewSyncState         The new sync state of the switch cascade.
 *  \param[out] RequiredCorrActions  The correction actions which are required for the current sync event.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_GetSyncStateAndCorrActions(
                EthTSyn_SwitchTimeSyncCfgIterType    SwtTimeSyncCfgIdx,
                EthTSyn_TimediffType                 SwtOffset,
  ETHTSYN_P2VAR(boolean)                             OfsJumpCorrRequired,
  ETHTSYN_P2VAR(EthTSyn_SyncStateType)               NewSyncState,
  ETHTSYN_P2VAR(EthTSyn_SwtTimeSync_CorrActionType)  RequiredCorrActions);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CheckOffsetJumpCorrThreshold
 *********************************************************************************************************************/
/*! \brief      Checks if offset jump correction threshold is reached.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  SwtOffset           Current offset of the switch cascade.
 *  \return     TRUE                Offset jump correction is required
 *  \return     FALSE               Offset jump correction is not required
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CheckOffsetJumpCorrThreshold(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CalculateSyncState
 *********************************************************************************************************************/
/*! \brief      Gets the sync state of the passed switch cascade depending on the passed offset.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx    Index of the switch cascade in context of the EthTSyn.
 *                                   [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  SwtOffset            Current offset of the switch cascade.
 *  \param[in]  OfsJumpCorrRequired  Indication if offset jump correction is required.
 *                                    TRUE: offset jump correction is required
 *                                    False: offset jump correction is not required
 *  \return     ETHTSYN_SYNC - The new sync state of the switch cascade is SYNC.
 *  \return     ETHTSYN_UNSYNC - The new sync state of the switch cascade is UNSYNC.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncStateType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CalculateSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset,
  boolean                             OfsJumpCorrRequired);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_GetRequiredCorrActions
 *********************************************************************************************************************/
/*! \brief      Gets the required correction actions.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx    Index of the switch cascade in context of the EthTSyn
 *                                   [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  NewSyncState         The new sync state of the switch cascade.
 *  \param[in]  OfsJumpCorrRequired  Indication if offset jump correction is required
 *                                    TRUE: offset jump correction is required
 *                                    False: offset jump correction is not required
 *  \return     The required correction actions.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_CorrActionType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_GetRequiredCorrActions(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState,
  boolean                             OfsJumpCorrRequired);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleOutOfSyncCounter
 *********************************************************************************************************************/
/*! \brief      Handles the out of sync counter depending on the passed sync state.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  NewSyncState        The new sync state of the switch cascade.
                                    [range: ETHTSYN_SYNC, ETHTSYN_UNSYNC]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleOutOfSyncCounter(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ApplyNewSyncState
 *********************************************************************************************************************/
/*! \brief      Sets the new switch sync state and optionally informs the user about a change of the sync state.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx    Index of the switch cascade in context of the EthTSyn
 *                                   [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  NewSyncState         The new sync state of the switch cascade.
 *  \param[in]  OfsJumpCorrApplied   Indication if offset jump correction was applied
 *                                    TRUE: offset jump correction was applied
 *                                    False: offset jump correction was not applied
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ApplyNewSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState,
  boolean                             OfsJumpCorrApplied);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleRateRatio
 *********************************************************************************************************************/
/*! \brief      Checks if rate ratio is required and optionally computes it.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  NewSyncState        The new sync state of the switch cascade
 *  \param[in]  RequiredCorrActions The correction actions which are required for the current sync event
 *  \param[in]  SwtOffset           Current offset of the switch cascade
 *  \param[out] SwtRateRatioPtr     The computed RateRatio (valid for return value E_OK)
 *  \return     E_OK - RateRatio required and computation succeeded
 *  \return     E_NOT_OK - RateRatio not required or computation failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleRateRatio(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                EthTSyn_SyncStateType               NewSyncState,
                EthTSyn_SwtTimeSync_CorrActionType  RequiredCorrActions,
                EthTSyn_TimediffType                SwtOffset,
  ETHTSYN_P2VAR(float64)                            SwtRateRatioPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff
 *********************************************************************************************************************/
/*! \brief      Computes the master and switch time diffs of two consecutive sync events if possible.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[out] MasterTimeDiffPtr   The computed master time diff (valid for return value E_OK)
 *  \param[out] SwtTimeDiffPtr      The computed switch time diff (valid for return value E_OK)
 *  \return     E_OK - Computation of time differences succeeded
 *  \return     E_NOT_OK - Computation of time differences not possible or failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               MasterTimeDiffPtr,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtTimeDiffPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_UpdateAllRateMeasurements
 *********************************************************************************************************************/
/*! \brief      Updates accumulated master time diff and accumulated switch time diff of each rate measurement and
 *              returns the index of the longest running rate measurement.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx    Index of the switch cascade in context of the EthTSyn
 *                                   [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  MasterTimeDiff       The time passed between two consecutive sync events in the time master
 *                                   [range: MasterTimeDiff > 0]
 *  \param[in]  SwtTimeDiff          The time passed between two consecutive sync events in the switch
 *                                   [range: SwtTimeDiff > 0]
 *  \return     EthTSyn_GetSizeOfRateMeasurement() - no valid rate measurement was found
 *  \return     other values - Index of the longest running rate measurement
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementIterType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_UpdateAllRateMeasurements(
  EthTSyn_SizeOfSwitchTimeSyncCfgType                                SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                                               MasterTimeDiff,
  EthTSyn_TimediffType                                               SwtTimeDiff);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeGmRateRatio
 *********************************************************************************************************************/
/*! \brief      Computes the grand master rate ratio.
 *  \details    -
 *  \param[in]  RateMeasurementIdx  Index of the rate measurement
 *  \return     The computed grand master rate ratio [range: > 0]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeGmRateRatio(
  EthTSyn_RateMeasurementIterType  RateMeasurementIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeOffsetCorrRateRatio
 *********************************************************************************************************************/
/*! \brief      Computes the offset correction rate ratio.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  NewSyncState        The new sync state of the switch cascade
 *  \param[in]  SwtOffset           Current offset of the switch cascade.
 *  \param[in]  RateMeasurementIdx  Index of the rate measurement
 *  \return     The computed offset correction rate ratio
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeOffsetCorrRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType  SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType                NewSyncState,
  EthTSyn_TimediffType                 SwtOffset,
  EthTSyn_RateMeasurementIterType      RateMeasurementIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ApplyRateRatioBoundaries
 *********************************************************************************************************************/
/*! \brief      Checks the computed rate ratios for its boundaries and corrects accordingly.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                 [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[out] SwtRateRatioPtr    New switch rate ratio
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ApplyRateRatioBoundaries(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(float64)              SwtRateRatioPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CorrectAllRateMeasurementsForNewRateRatio
 *********************************************************************************************************************/
/*! \brief      Corrects accumulated switch time diff of each rate measurement for the new switch rate ratio.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                 [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[out] SwtRateRatioPtr    New switch rate ratio
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CorrectAllRateMeasurementsForNewRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  float64                             SwtRateRatio);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StartNewRateMeasurement
 *********************************************************************************************************************/
/*! \brief       Selects which rate measurement to start this sync cycle.
 *  \details     -
 *  \param[in]   SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  RateMeasurementIdx  Index of the rate measurement
 *              [range: RateMeasurementIndex < EthTSyn_GetSizeOfRateMeasurement()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StartNewRateMeasurement(
  EthTSyn_SizeOfSwitchTimeSyncCfgType  SwtTimeSyncCfgIdx,
  EthTSyn_RateMeasurementIterType      RateMeasurementIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StartSingleRateMeasurement
 *********************************************************************************************************************/
/*! \brief      Sets all variables of a rate measurement to default values and IsActive to TRUE.
 *  \details    -
 *  \param[in]  RateMeasurementIndex  Index of the rate measurement
 *              [range: RateMeasurementIndex < EthTSyn_GetSizeOfRateMeasurement()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StartSingleRateMeasurement(
  EthTSyn_RateMeasurementIterType  RateMeasurementIndex);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ResetSingleRateMeasurement
 *********************************************************************************************************************/
/*! \brief      Sets all variables of a rate measurement to default values.
 *  \details    -
 *  \param[in]  RateMeasurementIndex  Index of the rate measurement
 *              [range: RateMeasurementIndex < EthTSyn_GetSizeOfRateMeasurement()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 **********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ResetSingleRateMeasurement(
  EthTSyn_RateMeasurementIterType  RateMeasurementIndex);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ResetAllRateMeasurements
 *********************************************************************************************************************/
/*! \brief         Sets the variables of all rate measurements to default values.
 *  \details       -
 *  \param[in]     SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                    [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 **********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ResetAllRateMeasurements(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_InitRateMeasurements
 *********************************************************************************************************************/
/*! \brief         Initializes all parallel rate measurements.
 *  \details       -
 *  \param[in]     SwtTimeSyncCfgIdx  Index of the switch cascade in context of the EthTSyn
 *                                    [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 **********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_InitRateMeasurements(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SetSwitchCorrectionTime
 *********************************************************************************************************************/
/*! \brief      Applies the time corrections to the switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *                                  [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  SwtOffsetPtr        The offset to be applied or NULL_PTR
 *  \param[in]  RateRatioPtr        The rate ratio to be applied or NULL_PTR
 *  \return     E_OK - Successfully applied corrections to switch cascade
 *  \return     E_NOT_OK - Failed to apply corrections to switch cascade
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SetSwitchCorrectionTime(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)               SwtOffsetPtr,
  ETHTSYN_P2CONST(float64)                            SwtRateRatioPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff
 *********************************************************************************************************************/
/*! \brief      Converts the passed time difference into the AUTOSAR format (TimeIntDiffType).
 *  \details    -
 *  \param[in]  TimeDiff   The TimeDiff to convert
 *  \return     TimeDiff converted to TimeIntDiff
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeIntDiffType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff(
  EthTSyn_TimediffType TimeDiff);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StoreTimestamps
 *********************************************************************************************************************/
/*! \brief      Stores the passed switch timestamps in the passed switch time sync info and updates the state.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx          Index of the switch cascade in context of the EthTSyn
 *                                         [range: 0 <= SwtTimeSyncCfgIdx < EthTSyn_GetSizeOfSwitchTimeSyncCfg()]
 *  \param[in]  SequenceId                 The sequence id of the corresponding sync event
 *  \param[in]  PreciseOriginTimestampPtr  The precise origin timestamp of the sync event
 *  \param[in]  SyncIngressTimestamp       The switch sync ingress timestamp
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StoreTimestamps(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                  uint16                              SequenceId,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        PreciseOriginTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        SyncIngressTimestamp);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameTrigger
 *********************************************************************************************************************/
/*! \brief      Triggers the transmission of a switch sync frame.
 *  \details    -
 *  \param[in]  SwtSyncFrameCfgIdx   Index of the switch sync frame.
 *                                   [range: 0 <= SwtSyncFrameCfgIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch sync frames
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameTrigger(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps
 *********************************************************************************************************************/
/*! \brief      Provides the timestamps of the passed switch sync frame.
 *  \details    Checks for available of the timestamps of the passed switch sync frame. If available, the timestamps
 *              are provided to the corresponding switch cascade for later time synchronization of the switch cascade.
 *  \param[in]  SwtSyncFrameCfgIdx   Index of the switch sync frame.
 *                                   [range: 0 <= SwtSyncFrameCfgIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg()]
 *  \return     E_OK - Timestamps of switch sync frame ready to process and provided in case they where available.
 *  \return     E_NOT_OK - Timestamps of switch sync frame not yet ready to process. Retry again later.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch sync frames
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameCalcPot
 *********************************************************************************************************************/
/*! \brief         Corrects the precise origin timestamp of a transmitted switch sync frame if HW timestamping is used.
 *  \details       -
 *  \param[in]     SwtSyncFrameCfgIdx         Index of the switch sync frame
 *                                            [range: SwtSyncFrameCfgIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg()]
 *  \param[in]     EgressIntVltMgmtPtr        The egress timestamp of the switch sync frame as internal virtual local
 *                                            time and its validity information
 *  \param[out]    PreciseOriginTimestampPtr  The precise origin timestamp
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 ********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameCalcPot(
                  EthTSyn_SwitchSyncFrameCfgIterType SwtSyncFrameCfgIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType)            EgressIntVltMgmtPtr,
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType)       PotPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_InitTimeStampInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_InitTimeStampInfo(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtTimeSync_TimestampInfoStructType timeStampInfo;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all values of the current and previous TimeStampInfo to zero. */
  timeStampInfo.SequenceId = 0u;

  timeStampInfo.PreciseOriginTimestamp.secondsHi = 0u;
  timeStampInfo.PreciseOriginTimestamp.seconds = 0u;
  timeStampInfo.PreciseOriginTimestamp.nanoseconds = 0u;

  timeStampInfo.SyncIngressTimestamp.secondsHi = 0u;
  timeStampInfo.SyncIngressTimestamp.seconds = 0u;
  timeStampInfo.SyncIngressTimestamp.nanoseconds = 0u;

  EthTSyn_SetTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, timeStampInfo);                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetPrevTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, timeStampInfo);                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_SwtTimeSync_InitTimeStampInfo() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtSyncFrame
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtSyncFrame(
  EthTSyn_SizeOfSwitchSyncFrameCfgType SwtSyncFrameCfgIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if state is not IDLE. */
  if (EthTSyn_GetStateOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx) != ETHTSYN_IDLE_STATEOFSWITCHSYNCFRAMEINFO)
  {
    if (EthTSyn_GetSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx) > 0u)
    {
      /* #101 Decrement sync Tx counter if it is higher than zero. */
      EthTSyn_DecSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
    }

    if (EthTSyn_GetStateOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx) == ETHTSYN_WAIT_TS_STATEOFSWITCHSYNCFRAMEINFO)
    {
      /* #102 If state is WAIT_TS, try to provide timestamps. */
      if (EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps(SwtSyncFrameCfgIdx) == E_OK)
      {
        /* #1020 If successful, change state to WAIT_TX. */
        EthTSyn_SetStateOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx, ETHTSYN_WAIT_TX_STATEOFSWITCHSYNCFRAMEINFO);         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
      }
    }

    if (EthTSyn_GetSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx) == 0u)
    {
      /* #103 Trigger switch sync frame transmission if sync Tx counter is expired. */
      EthTSyn_SwtTimeSync_SwtSyncFrameTrigger(SwtSyncFrameCfgIdx);
    }
  }
} /* EthTSyn_SwtTimeSync_HandleSwtSyncFrame() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSyncEventTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSyncEventTimeout(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle sync event timeout. */
  if(EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx) > 0u)
  {
    if(EthTSyn_GetSyncEventTimeoutCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) > 0u)
    {
      EthTSyn_DecSyncEventTimeoutCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    }
    else
    {
      EthTSyn_SwtTimeSync_ApplyNewSyncState(SwtTimeSyncCfgIdx, ETHTSYN_UNCERTAIN, FALSE);
      EthTSyn_SwtTimeSync_ResetAllRateMeasurements(SwtTimeSyncCfgIdx);
    }
  }
} /* EthTSyn_SwtTimeSync_HandleSyncEventTimeout */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtTimeSync
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
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtTimeSync(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_TimediffType) swtOffsetPtr = NULL_PTR;
  ETHTSYN_P2CONST(float64) swtRateRatioPtr = NULL_PTR;
  EthTSyn_TimediffType swtOffset = 0;
  float64 swtRateRatio = 1.0;
  boolean ofsJumpCorrRequired = FALSE;
  EthTSyn_SyncStateType newSwtSyncState;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if synchronization event occurred. */
  if((EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_WAIT_SECOND_STATEOFSWITCHTIMESYNCINFO) ||
    (EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_READY_STATEOFSWITCHTIMESYNCINFO)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
  {
    /* #20 Try to compute current switch offset. */
    if(EthTSyn_SwtTimeSync_ComputeSwtOffset(SwtTimeSyncCfgIdx, &swtOffset) == E_OK)                                    /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      EthTSyn_SwtTimeSync_CorrActionType requiredCorrActions;

      /* #30 Determine the synchronization state and the required correction actions. */
      EthTSyn_SwtTimeSync_GetSyncStateAndCorrActions(SwtTimeSyncCfgIdx, swtOffset, &ofsJumpCorrRequired,               /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        &newSwtSyncState, &requiredCorrActions);

      /* #40 Check if offset correction is required. */
      if(EthTSyn_Util_AreBitsSet(requiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET_MASK) == TRUE)
      {
        /* #400 Offset correction required -> set offset pointer. */
        swtOffsetPtr = &swtOffset;
      }
      /* #50 Compute and use rate ratio if required. */
      if(EthTSyn_SwtTimeSync_HandleRateRatio(SwtTimeSyncCfgIdx, newSwtSyncState, requiredCorrActions,                  /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        swtOffset, &swtRateRatio) == E_OK)
      {
        /* #501 In case rate correction is required and was computed successfully, set rate ratio pointer. */
        swtRateRatioPtr = &swtRateRatio;
      }
      else
      {
        /* #502 In case rate ratio is not required or computation failed, reset all rate measurements. */
        EthTSyn_SwtTimeSync_ResetAllRateMeasurements(SwtTimeSyncCfgIdx);
      }
    }
    else
    {
      /* #200 Set switch sync state to ETHTSYN_UNCERTAIN in case offset calculation failed. */
      newSwtSyncState = ETHTSYN_UNCERTAIN;
    }

    /* #60 Set state of switch time sync info to ETHTSYN_WAIT_STATEOFSWITCHTIMESYNCINFO to wait for next sync event. */
    EthTSyn_SetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, ETHTSYN_WAIT_STATEOFSWITCHTIMESYNCINFO);                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();

    /* #70 Provide correction information to switch if any correction is required. */
    if((swtRateRatioPtr != NULL_PTR) || (swtOffsetPtr != NULL_PTR))
    {
      if(EthTSyn_SwtTimeSync_SetSwitchCorrectionTime(SwtTimeSyncCfgIdx, swtOffsetPtr, swtRateRatioPtr) == E_NOT_OK)    /* SBSW_ETHTSYN_LOCAL_PTR_VAR */
      {
        /* #700 Correction failed -> set sync state to ETHTSYN_UNCERTAIN. */
        newSwtSyncState = ETHTSYN_UNCERTAIN;
      }
    }

    /* #80 Set new sync state of the switch cascade. */
    EthTSyn_SwtTimeSync_ApplyNewSyncState(SwtTimeSyncCfgIdx, newSwtSyncState, ofsJumpCorrRequired);
  }
  else
  {
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();
  }
} /* EthTSyn_SwtTimeSync_HandleSwtTimeSync() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeSwtOffset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeSwtOffset(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtOffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtTimeSync_TimestampInfoStructType tsInfo;

  /* ----- Implementation ----------------------------------------------- */
  tsInfo = EthTSyn_GetTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);

  /* #10 Compute switch offset. */
  return EthTSyn_Util_TimestampMinusTimestamp(                                                                         /* SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF */
    &tsInfo.PreciseOriginTimestamp,
    &tsInfo.SyncIngressTimestamp,
    SwtOffsetPtr);
} /* EthTSyn_SwtTimeSync_ComputeSwtOffset() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_GetSyncStateAndCorrActions
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_GetSyncStateAndCorrActions(
  EthTSyn_SwitchTimeSyncCfgIterType                  SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                               SwtOffset,
  ETHTSYN_P2VAR(boolean)                             OfsJumpCorrRequired,
  ETHTSYN_P2VAR(EthTSyn_SyncStateType)               NewSyncState,
  ETHTSYN_P2VAR(EthTSyn_SwtTimeSync_CorrActionType)  RequiredCorrActions)
{
  /* #10 Check if offset jump correction is required. */
  (*OfsJumpCorrRequired) = EthTSyn_SwtTimeSync_CheckOffsetJumpCorrThreshold(SwtTimeSyncCfgIdx, SwtOffset);             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
  /* #20 Determine the new sync state. */
  (*NewSyncState) = EthTSyn_SwtTimeSync_CalculateSyncState(SwtTimeSyncCfgIdx, SwtOffset, *OfsJumpCorrRequired);        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
  /* #30 Get required correction actions. */
  (*RequiredCorrActions) = EthTSyn_SwtTimeSync_GetRequiredCorrActions(                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    SwtTimeSyncCfgIdx, *NewSyncState, *OfsJumpCorrRequired);
  /* #40 Handle the out of sync counter. */
  EthTSyn_SwtTimeSync_HandleOutOfSyncCounter(SwtTimeSyncCfgIdx, *NewSyncState);
  /* #50 Store the current offset. */
  EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, SwtOffset);                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_SwtTimeSync_GetSyncStateAndCorrActions() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CheckOffsetJumpCorrThreshold
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CheckOffsetJumpCorrThreshold(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean offsetJumpCorrRequired;
  EthTSyn_UTimediffType unsignedSwtOffset =
    ((SwtOffset < 0) ? ((EthTSyn_UTimediffType)(-SwtOffset)) : ((EthTSyn_UTimediffType)SwtOffset));
  EthTSyn_UTimediffType offsetJumpCorrThreshold =
    ((EthTSyn_UTimediffType)EthTSyn_GetOfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case offset jump correction threshold is used and was reached, offset jump correction is required. */
  if ((unsignedSwtOffset >= offsetJumpCorrThreshold) && (offsetJumpCorrThreshold != 0u))
  {
    offsetJumpCorrRequired = TRUE;
  }
  else
  {
    offsetJumpCorrRequired = FALSE;
  }
  return offsetJumpCorrRequired;
} /* EthTSyn_SwtTimeSync_CheckOffsetJumpCorrThreshold */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CalculateSyncState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncStateType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CalculateSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset,
  boolean                             OfsJumpCorrRequired)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_UTimediffType unsignedSwtOffset =
    ((SwtOffset < 0) ? ((EthTSyn_UTimediffType)(-SwtOffset)) : ((EthTSyn_UTimediffType)SwtOffset));
  EthTSyn_SyncStateType newSyncState;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case SwtOffset reached SyncPrecisionLimit or jump correction is used, return UNSYNC and
   *     otherwise return SYNC. */
  if (OfsJumpCorrRequired == TRUE)
  {
    newSyncState = ETHTSYN_UNSYNC;
  }
  else if (unsignedSwtOffset >= EthTSyn_GetSyncPrecisionLimitNsOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx))
  {
    newSyncState = ETHTSYN_UNSYNC;
  }
  else
  {
    newSyncState = ETHTSYN_SYNC;
  }
  return newSyncState;
} /* EthTSyn_SwtTimeSync_CalculateSyncState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_GetRequiredCorrActions
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
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_CorrActionType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_GetRequiredCorrActions(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState,
  boolean                             OfsJumpCorrRequired)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtTimeSync_CorrActionType requiredCorrActions;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case sync state is ETHTSYN_UNSYNC. */
  if(NewSyncState == ETHTSYN_UNSYNC)
  {
    /* #101 In case sync state was never reached yet, rate ratio and offset correction is required. */
    if((EthTSyn_IsUseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx) == TRUE) &&
      (EthTSyn_IsWasSyncReachedOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == FALSE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
    {
      requiredCorrActions = ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET_AND_GM_RATE;
    }
    /* #102 In case of offset jump correction, only offset correction is required. */
    else if (OfsJumpCorrRequired == TRUE)
    {
      requiredCorrActions = ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET;
      /* If a large time leap occurs in the GM clock, the master time diff changes drastically in this sync cycle and
         the computed GM rate ratio is therefore very high or low. The offset will now be corrected by a time leap of
         the switch clock. If GM RateRatio correction would be used in addition, it would induce a new offset in the
         next sync cycle. */
    }
    /* #103 Otherwise rate regulator is required. */
    else
    {
      requiredCorrActions = ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RATE_REGULATOR;
    }
  }
  /* #20 In case of any other sync state. */
  else
  {
    /* #200 Rate regulator is required. */
    requiredCorrActions = ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RATE_REGULATOR;
  }

  return requiredCorrActions;
} /* EthTSyn_SwtTimeSync_GetRequiredCorrActions() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleOutOfSyncCounter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleOutOfSyncCounter(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset out of sync counter in case of ETHTSYN_SYNC.*/
  if(NewSyncState == ETHTSYN_SYNC)
  {
    EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, 0u);                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  }
  /* #20 Increment out of sync counter in case of ETHTSYN_UNSYNC. */
  else
  {
    if(EthTSyn_GetOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) <
      ETHTSYN_SWT_TIME_SYNC_OUT_OF_SYNC_COUNT_MAX_ALLOWED_VALUE)
    {
      EthTSyn_IncOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    }
  }
} /* EthTSyn_SwtTimeSync_HandleOutOfSyncCounter() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ApplyNewSyncState
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ApplyNewSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState,
  boolean                             OfsJumpCorrApplied)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SyncStateType syncStateToSet = EthTSyn_GetSwtSyncStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case of NewSyncState is ETHTSYN_UNSYNC, only set the new state if max out of sync count exceeded
   *     or if offset jump correction is required. */
  if(NewSyncState == ETHTSYN_UNSYNC)
  {
    if((EthTSyn_GetOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) >=
      EthTSyn_GetMaxOutOfSyncCntOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx)) || (OfsJumpCorrApplied == TRUE))
    {
      syncStateToSet = ETHTSYN_UNSYNC;
    }
  }
  /* #20 Otherwise apply the new sync state. */
  else
  {
    syncStateToSet = NewSyncState;
    /* #200 Mark as sync was reached in case of ETHTSYN_SYNC. */
    if(NewSyncState == ETHTSYN_SYNC)
    {
      EthTSyn_SetWasSyncReachedOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, TRUE);                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    }
  }

  /* #30 Trigger sync state change user notification in case it is enabled and the sync state has changed. */
  if(EthTSyn_GetSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx) != NULL_PTR)
  {
    if(EthTSyn_GetSwtSyncStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) != syncStateToSet)
    {
      EthTSyn_GetSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx)(SwtTimeSyncCfgIdx, NewSyncState);         /* SBSW_ETHTSYN_SWT_SYNC_STATE_CHG_CBK */
    }
  }

  /* #40 Set the new sync state in the switch time sync info. */
  EthTSyn_SetSwtSyncStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, syncStateToSet);                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

} /* EthTSyn_SwtTimeSync_ApplyNewSyncState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleRateRatio
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
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleRateRatio(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                EthTSyn_SyncStateType               NewSyncState,
                EthTSyn_SwtTimeSync_CorrActionType  RequiredCorrActions,
                EthTSyn_TimediffType                SwtOffset,
  ETHTSYN_P2VAR(float64)                            SwtRateRatioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if rate ratio is required according to required correction actions. */
  if((EthTSyn_Util_AreBitsSet(RequiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_GM_RATE_MASK) == TRUE) ||
    (EthTSyn_Util_AreBitsSet(RequiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RR_RATE_MASK) == TRUE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
  {
    EthTSyn_TimediffType masterTimeDiff = 0;
    EthTSyn_TimediffType swtTimeDiff = 0;

    /* #20 Compute master and switch time differences of two consecutive sync events. */
    if(EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff(SwtTimeSyncCfgIdx, &masterTimeDiff, &swtTimeDiff) == E_OK)   /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      /* #30 Update accumulatedMasterTimeDiff and accumulatedSwtTimeDiff of all active rate measurements. */
      EthTSyn_RateMeasurementIterType longestMeasurementIdx = EthTSyn_SwtTimeSync_UpdateAllRateMeasurements(
        SwtTimeSyncCfgIdx, masterTimeDiff, swtTimeDiff);
      if (longestMeasurementIdx < EthTSyn_GetSizeOfRateMeasurement())
      {
        /* #40 Compute grand master rate ratio. */
        (*SwtRateRatioPtr) = EthTSyn_SwtTimeSync_ComputeGmRateRatio(longestMeasurementIdx);                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

        /* #50 Compute additional offset correction rate ratio if required. */
        if (EthTSyn_Util_AreBitsSet(RequiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RR_RATE_MASK) == TRUE)
        {
          (*SwtRateRatioPtr) += EthTSyn_SwtTimeSync_ComputeOffsetCorrRateRatio(                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
            SwtTimeSyncCfgIdx, NewSyncState, SwtOffset, longestMeasurementIdx);
        }
        /* #60 Verify that computed rate ratio is within boundaries. */
        EthTSyn_SwtTimeSync_ApplyRateRatioBoundaries(SwtTimeSyncCfgIdx, SwtRateRatioPtr);                              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

        /* #70 Correct accumulatedSwtTimeDiff of all active rate measurements for new rate ratio.*/
        EthTSyn_SwtTimeSync_CorrectAllRateMeasurementsForNewRateRatio(SwtTimeSyncCfgIdx, *SwtRateRatioPtr);

        /* #80 Start new rate measurement.*/
        EthTSyn_SwtTimeSync_StartNewRateMeasurement(SwtTimeSyncCfgIdx, longestMeasurementIdx);

        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* EthTSyn_SwtTimeSync_HandleRateRatio() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               MasterTimeDiffPtr,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtTimeDiffPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if calculation of time difference is possible according to switch time sync info state. */
  if(EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_READY_STATEOFSWITCHTIMESYNCINFO)
  {
    ETHTSYN_P2CONST(EthTSyn_SwtTimeSync_TimestampInfoStructType) timeStampInfoPtr =
      EthTSyn_GetAddrTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);
    ETHTSYN_P2CONST(EthTSyn_SwtTimeSync_TimestampInfoStructType) prevTimeStampInfoPtr =
      EthTSyn_GetAddrPrevTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);

    /* #20 Ensure that two consecutive sync events occurred. */
    if(timeStampInfoPtr->SequenceId == (prevTimeStampInfoPtr->SequenceId + 1u))
    {
      EthTSyn_TimediffType masterTimeDiff = 0;
      EthTSyn_TimediffType swtTimeDiff = 0;

      /* #30 Compute master and switch time diff between two consecutive sync event. */
      retVal = EthTSyn_Util_TimestampMinusTimestamp(&timeStampInfoPtr->PreciseOriginTimestamp,                         /* SBSW_ETHTSYN_CSL_STRUCT_MEMBER_ARRAY_AS_POINTER_CSL_02_AND_LOC_VAR_REF */
        &prevTimeStampInfoPtr->PreciseOriginTimestamp, &masterTimeDiff);
      retVal |= EthTSyn_Util_TimestampMinusTimestamp(&timeStampInfoPtr->SyncIngressTimestamp,                          /* SBSW_ETHTSYN_CSL_STRUCT_MEMBER_ARRAY_AS_POINTER_CSL_02_AND_LOC_VAR_REF */
        &prevTimeStampInfoPtr->SyncIngressTimestamp, &swtTimeDiff);

      /* #40 If calculation of both time differences succeeded, adapt switch time diff by last corrected offset. */
      if(retVal == E_OK)
      {
        swtTimeDiff -= EthTSyn_GetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);
        EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, 0);                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

        /* #50 Ensure causality of the time diffs. */
        if((masterTimeDiff > 0) && (swtTimeDiff > 0))
        {
          (*MasterTimeDiffPtr) = masterTimeDiff;                                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
          (*SwtTimeDiffPtr) = swtTimeDiff;                                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();

  return retVal;
} /* EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_UpdateAllRateMeasurements
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementIterType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_UpdateAllRateMeasurements(
  EthTSyn_SizeOfSwitchTimeSyncCfgType                                SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                                               MasterTimeDiff,
  EthTSyn_TimediffType                                               SwtTimeDiff)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_RateMeasurementIterType longestMeasurementIdx = EthTSyn_GetSizeOfRateMeasurement();
  uint64 numberOfSyncCyclesOfLongestMeasurement = 0;
  EthTSyn_RateMeasurementIterType rateMeasurementIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all rate measurements. */
  for (rateMeasurementIter = EthTSyn_GetRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
    rateMeasurementIter < EthTSyn_GetRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
    rateMeasurementIter++)
  {
    /* #20 Update variables of all active rate measurements. */
    if (EthTSyn_IsActiveOfRateMeasurement(rateMeasurementIter) == TRUE)
    {
      EthTSyn_RateCorrectedTimediffType accumulatedMasterTimeDiff =
        EthTSyn_GetAccumulatedMasterTimeDiffOfRateMeasurement(rateMeasurementIter);
      EthTSyn_RateCorrectedTimediffType accumulatedSwtTimeDiff =
        EthTSyn_GetAccumulatedSwtTimeDiffOfRateMeasurement(rateMeasurementIter);
      uint8 activeNumberOfSyncCycles = EthTSyn_GetActiveNrOfSyncCyclesOfRateMeasurement(rateMeasurementIter);

      EthTSyn_SetAccumulatedMasterTimeDiffOfRateMeasurement(                                                           /* SBSW_ETHTSYN_CSL03 */
        rateMeasurementIter, accumulatedMasterTimeDiff + (EthTSyn_RateCorrectedTimediffType)MasterTimeDiff);
      EthTSyn_SetAccumulatedSwtTimeDiffOfRateMeasurement(                                                              /* SBSW_ETHTSYN_CSL03 */
        rateMeasurementIter, accumulatedSwtTimeDiff + (EthTSyn_RateCorrectedTimediffType)SwtTimeDiff);
      activeNumberOfSyncCycles++;
      EthTSyn_SetActiveNrOfSyncCyclesOfRateMeasurement(rateMeasurementIter, activeNumberOfSyncCycles);                 /* SBSW_ETHTSYN_CSL03 */

      /* #30 Store index of longest running rate measurement. */
      if (activeNumberOfSyncCycles > numberOfSyncCyclesOfLongestMeasurement)
      {
        numberOfSyncCyclesOfLongestMeasurement = activeNumberOfSyncCycles;
        longestMeasurementIdx = rateMeasurementIter;
      }
    }
  }
  return longestMeasurementIdx;
} /* EthTSyn_SwtTimeSync_UpdateAllRateMeasurements() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeGmRateRatio
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeGmRateRatio(
  EthTSyn_RateMeasurementIterType  RateMeasurementIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  float64 swtRateRatio;
  EthTSyn_RateCorrectedTimediffType accumulatedMasterTimeDiff =
    EthTSyn_GetAccumulatedMasterTimeDiffOfRateMeasurement(RateMeasurementIdx);
  EthTSyn_RateCorrectedTimediffType accumulatedSwtTimeDiff =
    EthTSyn_GetAccumulatedSwtTimeDiffOfRateMeasurement(RateMeasurementIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute grand master rate ratio. */
  swtRateRatio = accumulatedMasterTimeDiff / accumulatedSwtTimeDiff;
  return swtRateRatio;
} /* EthTSyn_SwtTimeSync_ComputeGmRateRatio() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeOffsetCorrRateRatio
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
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeOffsetCorrRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType  SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType                NewSyncState,
  EthTSyn_TimediffType                 SwtOffset,
  EthTSyn_RateMeasurementIterType      RateMeasurementIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  float64 offsetCorrRateRatio;
  EthTSyn_RateCorrectedTimediffType swtTimeDiff =
    EthTSyn_GetAccumulatedSwtTimeDiffOfRateMeasurement(RateMeasurementIdx);
  uint8 syncCycleCounterForOfsCorr = EthTSyn_GetCounterOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #11 Restart sync cycle counter if state is UNSYNC and it was not restarted yet. */
  if ((EthTSyn_IsRestartedOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx) == FALSE) &&
    (NewSyncState == ETHTSYN_UNSYNC))
  {
    syncCycleCounterForOfsCorr = 0;
    EthTSyn_SetRestartedOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx, TRUE);                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  }
  /* #12 Reset "WasRestarted"-flag if state is SYNC and it was not reset yet. */
  else if ((EthTSyn_IsRestartedOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx) == TRUE) &&
    (NewSyncState == ETHTSYN_SYNC))
  {
    EthTSyn_SetRestartedOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx, FALSE);                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  }
  else
  {
    /* no action required in this case */
  }

  /* #20 Compute offset correction rate ratio. */
  offsetCorrRateRatio = (float64)SwtOffset / (float64)swtTimeDiff;
  offsetCorrRateRatio *=
    (float64)EthTSyn_GetActiveNrOfSyncCyclesOfRateMeasurement(RateMeasurementIdx);
  offsetCorrRateRatio /=
    ((float64)EthTSyn_GetNrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx) -
    (float64)syncCycleCounterForOfsCorr);

  /* #30 Increment sync cycle counter. */
  syncCycleCounterForOfsCorr++;

  /* 40 Restart sync cycle counter when number of sync cycles for offset correction is reached */
  if (syncCycleCounterForOfsCorr >= EthTSyn_GetNrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx))
  {
    EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx, 0);                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  }
  else
  {
    EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx, syncCycleCounterForOfsCorr);                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  }
  return offsetCorrRateRatio;
} /* EthTSyn_SwtTimeSync_ComputeOffsetCorrRateRatio() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ApplyRateRatioBoundaries
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ApplyRateRatioBoundaries(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(float64)              SwtRateRatioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType rateRegulatorIdx =
    EthTSyn_GetSwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Apply rate boundaries. */
  if ((*SwtRateRatioPtr) > EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(rateRegulatorIdx))
  {
    (*SwtRateRatioPtr) = EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(rateRegulatorIdx);                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
  }
  else if ((*SwtRateRatioPtr) < EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(rateRegulatorIdx))
  {
    (*SwtRateRatioPtr) = EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(rateRegulatorIdx);                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
  }
  else
  {
    /* RateRatio is within limits. Nothing to do. */
  }
} /* EthTSyn_SwtTimeSync_ApplyRateRatioBoundaries() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CorrectAllRateMeasurementsForNewRateRatio
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CorrectAllRateMeasurementsForNewRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  float64                             SwtRateRatio)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_RateMeasurementIterType rateMeasurementIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all rate measurements. */
  for (rateMeasurementIter = EthTSyn_GetRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
    rateMeasurementIter < EthTSyn_GetRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
    rateMeasurementIter++)
  {
    /* #20 Correct SwtTimeDiff of every active rate measurement for new rate ratio. */
    if (EthTSyn_IsActiveOfRateMeasurement(rateMeasurementIter) == TRUE)
    {
      EthTSyn_RateCorrectedTimediffType accumulatedSwtTimeDiff =
        EthTSyn_GetAccumulatedSwtTimeDiffOfRateMeasurement(rateMeasurementIter);
      EthTSyn_SetAccumulatedSwtTimeDiffOfRateMeasurement(                                                              /* SBSW_ETHTSYN_CSL03 */
        rateMeasurementIter, accumulatedSwtTimeDiff * SwtRateRatio);
    }
  }
}/* EthTSyn_SwtTimeSync_CorrectAllRateMeasurementsForNewRateRatio() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StartNewRateMeasurement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StartNewRateMeasurement(
  EthTSyn_SizeOfSwitchTimeSyncCfgType  SwtTimeSyncCfgIdx,
  EthTSyn_RateMeasurementIterType      RateMeasurementIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case longest running rate measurement is finished, restart it. */
  if (EthTSyn_GetActiveNrOfSyncCyclesOfRateMeasurement(RateMeasurementIdx) >=
    EthTSyn_GetNrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx))
  {
    EthTSyn_SwtTimeSync_StartSingleRateMeasurement(RateMeasurementIdx);
  }
  /* #20 Otherwise start the next inactive rate measurement. */
  else
  {
    EthTSyn_RateMeasurementIterType rateMeasurementIter;
    for (rateMeasurementIter = EthTSyn_GetRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
      rateMeasurementIter < EthTSyn_GetRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
      rateMeasurementIter++)
    {
      if (EthTSyn_IsActiveOfRateMeasurement(rateMeasurementIter) == FALSE)
      {
        EthTSyn_SwtTimeSync_StartSingleRateMeasurement(rateMeasurementIter);
        break;
      }
    }
  }
}/* EthTSyn_SwtTimeSync_StartNewRateMeasurement() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StartSingleRateMeasurement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StartSingleRateMeasurement(
  EthTSyn_RateMeasurementIterType  RateMeasurementIndex)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset rate measurement. */
  EthTSyn_SwtTimeSync_ResetSingleRateMeasurement(RateMeasurementIndex);

  /* #20 Set rate measurement to active. */
  EthTSyn_SetActiveOfRateMeasurement(RateMeasurementIndex, TRUE);                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
}/* EthTSyn_SwtTimeSync_StartSingleRateMeasurement() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ResetSingleRateMeasurement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ResetSingleRateMeasurement(
  EthTSyn_RateMeasurementIterType  RateMeasurementIndex)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all variables of the rate measurement to default values. */
  EthTSyn_SetAccumulatedSwtTimeDiffOfRateMeasurement(RateMeasurementIndex, 0.0);                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
  EthTSyn_SetAccumulatedMasterTimeDiffOfRateMeasurement(RateMeasurementIndex, 0.0);                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
  EthTSyn_SetActiveNrOfSyncCyclesOfRateMeasurement(RateMeasurementIndex, 0);                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
  EthTSyn_SetActiveOfRateMeasurement(RateMeasurementIndex, FALSE);                                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */

} /* EthTSyn_SwtTimeSync_ResetSingleRateMeasurement */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ResetAllRateMeasurements
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ResetAllRateMeasurements(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_RateMeasurementIterType rateMeasurementIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all rate measurements. */
  for (rateMeasurementIter = EthTSyn_GetRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
    rateMeasurementIter < EthTSyn_GetRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx);
    rateMeasurementIter++)
  {
    /* #20 Set all variables of each rate measurement to default values. */
    EthTSyn_SwtTimeSync_ResetSingleRateMeasurement(rateMeasurementIter);
  }
  /* #30 Set first rate measurement as active. */
  EthTSyn_SetActiveOfRateMeasurement(                                                                                  /* SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_CSL_02_MANDATORY_IND */
    EthTSyn_GetRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx), TRUE);

  /* #40 Reset rate regulator sync cycle counter. */
  EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx, 0);                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetRestartedOfOfsCorrDurationInSyncCycles(SwtTimeSyncCfgIdx, FALSE);                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_SwtTimeSync_ResetAllRateMeasurements */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_InitRateMeasurements
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_InitRateMeasurements(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset all rate measurements. */
  EthTSyn_SwtTimeSync_ResetAllRateMeasurements(SwtTimeSyncCfgIdx);
} /* EthTSyn_SwtTimeSync_InitRateMeasurements */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SetSwitchCorrectionTime
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
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SetSwitchCorrectionTime(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)               SwtOffsetPtr,
  ETHTSYN_P2CONST(float64)                            SwtRateRatioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorCount = 0;
  ETHTSYN_P2CONST(float64) slaveSwtRateRatioPtr = NULL_PTR;
  EthTSyn_TimeIntDiffType swtOffsetAsTimeIntDiff = { 0 };
  ETHTSYN_P2VAR(EthTSyn_TimeIntDiffType) swtOffsetAsTimeIntDiffPtr = &swtOffsetAsTimeIntDiff;
  const uint8 masterSwitchIdx = EthTSyn_GetEthIfSwitchIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If offset is used, transform it to TimeIntDiffType representation. */
  if(SwtOffsetPtr == NULL_PTR)
  {
    swtOffsetAsTimeIntDiffPtr = NULL_PTR;
  }
  else
  {
    (*swtOffsetAsTimeIntDiffPtr) = EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff((*SwtOffsetPtr));                         /* SBSW_ETHTSYN_LOC_PTR_VAR_WRITE */
  }

  /* #20 Apply correction values to Master-Switch. */
  if(EthIf_SwitchSetCorrectionTime(masterSwitchIdx, swtOffsetAsTimeIntDiffPtr, SwtRateRatioPtr) == E_OK)               /* SBSW_ETHTSYN_INT_FUNC_FWD_PTR_PARAM_AND_LOC_PTR_VAR */
  {
    /* #200 Store corrected offset for later calculation of rate ratio in case of success. */
    if(SwtOffsetPtr != NULL_PTR)
    {
      EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, (*SwtOffsetPtr));                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    }
  }
  else
  {
    /* #201 Increment errorCount in case any error occurred. */
    errorCount++;
  }

  /* #30 Check if rate ratio has to be applied to slave switches separately. */
  if(EthTSyn_IsApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx) == TRUE)
  {
    slaveSwtRateRatioPtr = SwtRateRatioPtr;
  }

  /* #40 Check if any correction has to be applied to slave switches. */
  if((slaveSwtRateRatioPtr != NULL_PTR) || (SwtOffsetPtr != NULL_PTR))
  {
    EthTSyn_SlaveSwitchIdxListIterType slaveSwitchIter;
    /* #400 Apply correction to every slave switch. */
    for(slaveSwitchIter = EthTSyn_GetSlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);
      slaveSwitchIter < EthTSyn_GetSlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);
      slaveSwitchIter++)
    {
      const uint8 slaveSwitchIdx = EthTSyn_GetSlaveSwitchIdxList(slaveSwitchIter);
      if(EthIf_SwitchSetCorrectionTime(slaveSwitchIdx, swtOffsetAsTimeIntDiffPtr, slaveSwtRateRatioPtr) == E_NOT_OK)   /* SBSW_ETHTSYN_INT_FUNC_FWD_PTR_PARAM_AND_LOC_PTR_VAR */
      {
        /* #401 Increment error counter in case of any error. */
        errorCount++;
      }
    }
  }

  return ((errorCount == 0u) ? E_OK : E_NOT_OK);
} /* EthTSyn_SwtTimeSync_SetSwitchCorrectionTime() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeIntDiffType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff(
  EthTSyn_TimediffType TimeDiff)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeIntDiffType timeIntDiff;
  EthTSyn_UTimediffType uTimeDiff;
  uint64 timeDiffSeconds;
  uint32 timeDiffNanoseconds;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get sign and absolute value of time diff. */
  if(TimeDiff < 0)
  {
    timeIntDiff.sign = FALSE;
    uTimeDiff = (EthTSyn_UTimediffType)(-TimeDiff);
  }
  else
  {
    timeIntDiff.sign = TRUE;
    uTimeDiff = (EthTSyn_UTimediffType)TimeDiff;
  }

  /* #20 Split absolute value of time diff into seconds and nanoseconds. */
  timeDiffSeconds = uTimeDiff / ETHTSYN_NANOSECONDS_PER_SECOND;
  timeDiffNanoseconds = (uint32)(uTimeDiff % ETHTSYN_NANOSECONDS_PER_SECOND);

  /* #30 Transform seconds and nanoseconds part into timestamp format. */
  timeIntDiff.diff.secondsHi = (uint16)(timeDiffSeconds >> 32u);
  timeIntDiff.diff.seconds = (uint32)timeDiffSeconds;
  timeIntDiff.diff.nanoseconds = timeDiffNanoseconds;

  return timeIntDiff;
} /* EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StoreTimestamps
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StoreTimestamps(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                  uint16                              SequenceId,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        PreciseOriginTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        SyncIngressTimestamp)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtTimeSync_TimestampInfoStructType timeStampInfo;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle the state of the switch time sync info structure. */
  if(EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_WAIT_FIRST_STATEOFSWITCHTIMESYNCINFO)
  {
    EthTSyn_SetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, ETHTSYN_WAIT_SECOND_STATEOFSWITCHTIMESYNCINFO);            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
  }
  else
  {
    EthTSyn_SetPrevTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx,                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
      EthTSyn_GetTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx));
    EthTSyn_SetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, ETHTSYN_READY_STATEOFSWITCHTIMESYNCINFO);                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
  }

  /* #20 Reset sync event timeout. */
  EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx,                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
    EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx));

  /* #30 Store the switch time stamp information. */
  timeStampInfo.SequenceId = SequenceId;
  timeStampInfo.PreciseOriginTimestamp = (*PreciseOriginTimestampPtr);
  timeStampInfo.SyncIngressTimestamp = (*SyncIngressTimestamp);
  EthTSyn_SetTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, timeStampInfo);                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */
} /* EthTSyn_SwtTimeSync_StoreTimestamps() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameTrigger
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
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameTrigger(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType transmitRetVal = E_NOT_OK;
  const EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType swtTimeSyncCfgIdx =
    EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);
  const EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType timeDomainIdx =
    EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIdx);
  StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
  StbM_TimeStampType globalTime = { 0u };
  StbM_VirtualLocalTimeType vlt = { 0u };
  StbM_UserDataType userData = { 0u };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the current global and virtual local time tuple form the StbM via StbM_BusGetCurrentTime(). */
  if(StbM_BusGetCurrentTime(timeBaseId, &globalTime, &vlt, &userData) == E_OK)                                         /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    EthTSyn_EthTxBufferStructType ethTxBuffer;
    const EthTSyn_PortIdxOfSwitchSyncFrameCfgType portIdx = EthTSyn_GetPortIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);
    const EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfgType ethIfCtrlIdx =
      EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);

    /* #20 Get an Ethernet transmission buffer for the switch sync frame. */
    ethTxBuffer.Length = ETHTSYN_MSG_SYNC_LENGTH;
    if(EthTSyn_UtilTx_ProvideTxBuffer(portIdx, &ethTxBuffer) == E_OK)                                                  /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      EthTSyn_SwtMgmtInfoType swtMgmtInfo;

      /* #30 Assemble the switch sync message. */
      /* EthTSyn_UtilTx_PrepareCommonMsgHdr() can't be used here due to different handling for switch sync frame. */
      IpBase_PutUint8(ethTxBuffer.BufferPtr, ETHTSYN_MSG_HDR_MSG_TYPE_OFS,                                             /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
        (uint8)(ETHTSYN_HDR_COM_TRANSPORT_SPECIFIC | ETHTSYN_MSG_TYPE_SYNC));
      IpBase_PutUint8(ethTxBuffer.BufferPtr, ETHTSYN_MSG_HDR_VERSION_PTP_OFS, ETHTSYN_SUPPORTED_PROTOCOL_VERSION);     /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

      IpBase_PutUint16(ethTxBuffer.BufferPtr, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS, ETHTSYN_MSG_SYNC_LENGTH);                /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
      IpBase_PutUint8(ethTxBuffer.BufferPtr, ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS, EthTSyn_GetIdOfTimeDomain(timeDomainIdx)); /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

      IpBase_PutUint8(ethTxBuffer.BufferPtr, ETHTSYN_MSG_HDR_FLAGS_0_OFS, ETHTSYN_FLAGS_OCTET_0_TWO_STEP);             /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

      IpBase_PutUint16(ethTxBuffer.BufferPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS,                                         /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
        EthTSyn_GetSequenceIdOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx));

      IpBase_PutUint8(ethTxBuffer.BufferPtr, ETHTSYN_MSG_HDR_CONTROL_OFS, ETHTSYN_HDR_COM_CONTROL_SYNC);               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

      /* #40 Set switch management info and enable timestamping. */
      swtMgmtInfo.SwitchIdx = EthTSyn_GetMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);
      swtMgmtInfo.PortIdx = EthTSyn_GetMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);

      if(EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, ethTxBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_AND_SWT_TS,      /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        &swtMgmtInfo) == E_OK)
      {
        EthTSyn_GlobalTimestampType intGlobalTime;
        EthTSyn_IntVltType intVlt = EthTSyn_UtilVlt_VltToIntVlt(&vlt);                                                 /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */

        intGlobalTime.secondsHi = globalTime.secondsHi;
        intGlobalTime.seconds = globalTime.seconds;
        intGlobalTime.nanoseconds = globalTime.nanoseconds;
        /* #50 Store Tx frame information for later identification. */
        EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, ethTxBuffer.BufferIdx);                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
        EthTSyn_SetBufAddrOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, ethTxBuffer.BufferPtr);                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
        EthTSyn_SetGlobalTimeOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, intGlobalTime);                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
        EthTSyn_SetIntVltOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, intVlt);                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
        EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx)->State = ETHTSYN_TS_S_PENDING;     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
        EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx)->State = ETHTSYN_TS_S_PENDING;        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */

        /* #60 Trigger transmission. */
        transmitRetVal = EthTSyn_UtilTx_Transmit(portIdx, ethTxBuffer.BufferIdx, ETHTSYN_MSG_SYNC_LENGTH);
      }

      /* #70 Increment switch sync frame sequence id in case of successful transmission and release Tx buffer and
             invalidate tx frame info otherwise. */
      if(transmitRetVal == E_OK)
      {
        EthTSyn_IncSequenceIdOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
        EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx,                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
          EthTSyn_GetSyncTxIntervalOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx));
        EthTSyn_SetStateOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx, ETHTSYN_WAIT_TS_STATEOFSWITCHSYNCFRAMEINFO);         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
      }
      else
      {
        EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, ETHTSYN_INV_BUF_IDX);                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
        EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, ethTxBuffer.BufferIdx);
        EthTSyn_SetStateOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx, ETHTSYN_WAIT_TX_STATEOFSWITCHSYNCFRAMEINFO);         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
      }
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameTrigger() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  ETHTSYN_CONSTP2CONST(EthTSyn_TsMgmtStructType) potMgmtPtr =
    EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_TsMgmtStructType) swtSyncIngTsMgmtPtr =
    EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that precise origin timestamp and switch ingress timestamp of switch sync frame are ready for
         processing. */
  if((EthTSyn_Util_IsTsReadyToProc(potMgmtPtr->State) == TRUE) &&
    (EthTSyn_Util_IsTsReadyToProc(swtSyncIngTsMgmtPtr->State) == TRUE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
  {
    retVal = E_OK;
    /* #20 Verify that precise origin timestamp and switch ingress timestamp of switch sync frame are available. */
    if((potMgmtPtr->State == ETHTSYN_TS_S_AVAILABLE) &&
      (swtSyncIngTsMgmtPtr->State == ETHTSYN_TS_S_AVAILABLE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
    {
      /* #30 Store the timestamps and update switch time sync info state. */
      EthTSyn_SwtTimeSync_StoreTimestamps(                                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02_PTR */
        EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx),
        EthTSyn_GetSequenceIdOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx),
        &potMgmtPtr->Ts,
        &swtSyncIngTsMgmtPtr->Ts);
    }
  }

  return retVal;
} /* EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameCalcPot
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameCalcPot(
                  EthTSyn_SwitchSyncFrameCfgIterType SwtSyncFrameCfgIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType)            EgressIntVltMgmtPtr,
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType)       PotPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the passed egress timestamp is valid, calculate the precise origin timestamp. */
  if(EgressIntVltMgmtPtr->IntVltValid == TRUE)
  {
    EthTSyn_IntVltType intVltTxSwtSync;
    const EthTSyn_PortIdxOfSwitchSyncFrameCfgType portIdx =
      EthTSyn_GetPortIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);
    intVltTxSwtSync = EthTSyn_GetIntVltOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx);
    (*PotPtr) = EthTSyn_GetGlobalTimeOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx);                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    retVal = EthTSyn_Master_CalcPot(portIdx, EgressIntVltMgmtPtr->IntVlt, intVltTxSwtSync, PotPtr);                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
  }

  return retVal;
} /* EthTSyn_SwtTimeSync_SwtSyncFrameCalcPot() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_Init
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configs. */
  for(swtTimeSyncCfgIter = 0u; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 Initialize dynamic data of each switch time sync config. */
    EthTSyn_SwtTimeSync_InitTimeStampInfo(swtTimeSyncCfgIter);
    EthTSyn_SwtTimeSync_InitRateMeasurements(swtTimeSyncCfgIter);

    EthTSyn_SetStateOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, ETHTSYN_WAIT_FIRST_STATEOFSWITCHTIMESYNCINFO);            /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, 0);                                       /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, 0);                                             /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, 0u);                                               /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetWasSyncReachedOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, FALSE);                                          /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSwtSyncStateOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, ETHTSYN_NEVERSYNC);                                /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(swtTimeSyncCfgIter, 0);                                            /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetRestartedOfOfsCorrDurationInSyncCycles(swtTimeSyncCfgIter, FALSE);                                      /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(swtTimeSyncCfgIter,                                             /* SBSW_ETHTSYN_CSL02 */
      EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(swtTimeSyncCfgIter));
  }

  /* #30 Iterate all switch sync frame configs. */
  for(swtSyncFrameCfgIter = 0u; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    /* #40 Initialize dynamic data of each switch sync frame config. */
    EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(swtSyncFrameCfgIter)->State = ETHTSYN_TS_S_UNDEFINED;      /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(swtSyncFrameCfgIter)->State = ETHTSYN_TS_S_UNDEFINED;         /* SBSW_ETHTSYN_CSL02 */

    EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, 0u);                                                /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSequenceIdOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, 0u);                                               /* SBSW_ETHTSYN_CSL02 */

    EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter, ETHTSYN_INV_BUF_IDX);                           /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetBufAddrOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter, NULL_PTR);                                     /* SBSW_ETHTSYN_CSL02 */

    /* #50 Only initialize 'Running' flag if EthTSyn was not initialized yet. */
    if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
    {
      EthTSyn_SetStateOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, ETHTSYN_IDLE_STATEOFSWITCHSYNCFRAMEINFO);             /* SBSW_ETHTSYN_CSL02 */
    }
  }
} /* EthTSyn_SwtTimeSync_Init() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleCyclicTasks
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleCyclicTasks(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configs. */
  for(swtTimeSyncCfgIter = 0u; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 Handle optional switch sync frame. */
    if(EthTSyn_IsSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == TRUE)
    {
      EthTSyn_SwtTimeSync_HandleSwtSyncFrame(EthTSyn_GetSwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIter));
    }

    /* #30 Handle sync event timeout. */
    EthTSyn_SwtTimeSync_HandleSyncEventTimeout(swtTimeSyncCfgIter);

    /* #40 Handle time synchronization of the switch cascade. */
    EthTSyn_SwtTimeSync_HandleSwtTimeSync(swtTimeSyncCfgIter);
  }
} /* EthTSyn_SwtTimeSync_HandleCyclicTasks() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ProvideTimestamps
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ProvideTimestamps(
                  uint8                        EthIfSwitchIdx,
                  uint16                       SequenceId,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PreciseOriginTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) SwtIngressTimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configurations. */
  for(swtTimeSyncCfgIter = 0; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 Check for matching EthIfSwitch. */
    if(EthTSyn_GetEthIfSwitchIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == EthIfSwitchIdx)
    {
      /* #200 Verify time domain and ensure no separate switch sync frame is used. */
      if(EthTSyn_IsSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == FALSE) /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
      {
        /* #2000 Store timestamps for later synchronization of the switch. */
        EthTSyn_SwtTimeSync_StoreTimestamps(                                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
          (EthTSyn_SizeOfSwitchTimeSyncCfgType)swtTimeSyncCfgIter,
          SequenceId,
          PreciseOriginTimestampPtr,
          SwtIngressTimestampPtr);
      }
      /* #201 Stop iteration because only one switch time sync config can exist per switch. */
      break;
    }
  }
} /* EthTSyn_SwtTimeSync_ProvideTimestamps() */

#  if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort(
                  EthTSyn_IntSlavePortIdxType SwtSlavePortIdx,
  ETHTSYN_P2CONST(uint8)                      RcvdFupMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(SwtSlavePortIdx);

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if sync ingress timestamp is available. */
  if(syncReceiveSmPtr->Sync.SwtIngressTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
  {
    const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SwtSlavePortIdx);
    const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(portIdx);
    EthTSyn_GlobalTimestampType preciseOriginTimestamp;
    uint64 unsignedFollowUpCorrectionField;
    EthTSyn_TimediffType timeDiffToCorrect;

    /* #20 Get the precise origin timestamp from the corresponding FollowUp message stored in the site sync sync state
           machine. */
    preciseOriginTimestamp.secondsHi = IpBase_GetUint16(RcvdFupMsgPtr, ETHTSYN_MSG_FUP_POT_SEC_HI_OFS);                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
    preciseOriginTimestamp.seconds = IpBase_GetUint32(RcvdFupMsgPtr, ETHTSYN_MSG_FUP_POT_SEC_LOW_OFS);                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
    preciseOriginTimestamp.nanoseconds = IpBase_GetUint32(RcvdFupMsgPtr, ETHTSYN_MSG_FUP_POT_NSEC_OFS);                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

    /* #30 Correct precise origin timestamp by correction field and path delay. */
    unsignedFollowUpCorrectionField = IpBase_GetUint48(RcvdFupMsgPtr, ETHTSYN_MSG_HDR_CORR_FIELD_OFS);                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
    /* No overflow possible. FollowUp correction field holds a max value of (2^48 - 1)ns and Pdelay (2^32 - 1) -->
     * max value of the sum fits uint64 and sint64 as well. */
    unsignedFollowUpCorrectionField += EthTSyn_Pdelay_GetCurrentPdelay(portIdx);
    timeDiffToCorrect = (EthTSyn_TimediffType)unsignedFollowUpCorrectionField;

    if(EthTSyn_Util_TimestampPlusTimediff(&preciseOriginTimestamp, &timeDiffToCorrect) == E_OK)                        /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      /* #40 Provide the corrected precise origin timestamp and sync ingress timestamp for later time synchronization
             of the switch. */
      EthTSyn_SwtTimeSync_ProvideTimestamps(                                                                           /* SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_SUB_MEMBER_AS_PTR_AND_REF_OF_LOC_VAR */
        EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx),
        syncReceiveSmPtr->Sync.SequenceId,
        &preciseOriginTimestamp,
        &syncReceiveSmPtr->Sync.SwtIngressTsMgmt.Ts);
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();

} /* EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#  endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

#  if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;
  boolean isUsed = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configs. */
  for(swtTimeSyncCfgIter = 0u; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 If parsed time domain matches time domain of the current switch time sync config, mark result as 'TRUE' and
           stop iteration. */
    if(EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == TimeDomainIdx)
    {
      isUsed = TRUE;
      break;
    }
  }

  return isUsed;
} /* EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync() */
#  endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameStart
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameStart(
  uint8 EthIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set state of all switch sync frames to 'WAIT_TX' and reset the sync frame cycle counter. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    if(EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == EthIfCtrlIdx)
    {
      EthTSyn_SetStateOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, ETHTSYN_WAIT_TX_STATEOFSWITCHSYNCFRAMEINFO);          /* SBSW_ETHTSYN_CSL02 */
      EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, 0u);                                              /* SBSW_ETHTSYN_CSL02 */
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameStart() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameStop
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameStop(
  uint8 EthIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set state of all switch sync frames to 'IDLE'. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    if(EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == EthIfCtrlIdx)
    {
      EthTSyn_SetStateOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, ETHTSYN_IDLE_STATEOFSWITCHSYNCFRAMEINFO);             /* SBSW_ETHTSYN_CSL02 */
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameStop() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_TxConfGetSwtSyncFrameIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(EthTSyn_SwitchSyncFrameCfgIterType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_TxConfGetSwtSyncFrameIdx(
  uint8 EthIfCtrlIdx,
  uint8 BufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameIdx = EthTSyn_GetSizeOfSwitchSyncFrameCfg();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch sync frame configs. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    /* #20 Check if EthIf controller matches the passed one. */
    if(EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == EthIfCtrlIdx)
    {
      /* #30 Check if a switch sync frame was transmitted and if the transmission buffer matches. */
      if(EthTSyn_GetBufIdxOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter) == BufIdx)
      {
        /* #40 Store the index of the switch sync frame and stop iteration. */
        swtSyncFrameIdx = swtSyncFrameCfgIter;
        break;
      }
    }
  }

  return swtSyncFrameIdx;
} /* EthTSyn_SwtTimeSync_TxConfGetSwtSyncFrameIdx() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation(
                  EthTSyn_SwitchSyncFrameCfgIterType SwtSyncFrameIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType)            EgressIntVltMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint8 ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(SwtSyncFrameIdx);
  const uint8 txBufIdx = EthTSyn_GetBufIdxOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameIdx);
  EthTSyn_GlobalTimestampType pot = { 0u };
  ETHTSYN_P2VAR(EthTSyn_TsMgmtStructType) potMgmtPtr =
    EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to calculate the actuall precise origin timestamp. */
  if(EthTSyn_SwtTimeSync_SwtSyncFrameCalcPot(SwtSyncFrameIdx, EgressIntVltMgmtPtr, &pot) == E_OK)                      /* SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF */
  {
    /* #100 Store timestamp and mark it as available. */
    potMgmtPtr->Ts = pot;                                                                                              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    potMgmtPtr->State = ETHTSYN_TS_S_AVAILABLE;                                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  }
  /* #20 Otherwise, mark the precise origin timestamp as invalid. */
  else
  {
    potMgmtPtr->State = ETHTSYN_TS_S_INVALID;                                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  }

  /* #30 Invalidate switch sync frame info. */
  EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameIdx, ETHTSYN_INV_BUF_IDX);                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

  /* #40 Get the TxMgmtObject for unified handling and stop iteration. */
  EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(ethIfCtrlIdx, txBufIdx, NULL_PTR, NULL_PTR);                                       /* SBSW_ETHTSYN_NULL_PTR */

} /* EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx(
  uint8 RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_CtrlIdxOfSwtMgmtRxBufType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfSwtMgmtRxBuf(RxBufIdx);
  const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfgType mgmtObjHndlIdx =
    EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx);
  EthTSyn_SwtMgmt_MgmtInfoMgmtStructType swtMgmtInfoMgmt;
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  swtMgmtInfoMgmt = EthTSyn_GetSwtMgmtInfoOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
  /* #10 Iterate all switch sync frame configs. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    /* #20 Check for matching EthIf controller and (management) switch port info. */
    /* PRQA S 3415 5 */ /* MD_EthTSyn_3415_CslReadOnly */
    if((EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) ==
      EthTSyn_GetEthIfCtrlIdxOfCtrl(ethTSynCtrlIdx)) &&
      (EthTSyn_GetMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) ==
        swtMgmtInfoMgmt.MgmtInfo.SwitchIdx) &&
      (EthTSyn_GetMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) ==
        swtMgmtInfoMgmt.MgmtInfo.PortIdx))
    {
      /* #30 Matching switch sync frame found. Store sync ingress timestamp infos and stop iteration. */
      EthTSyn_SetSwtIngressTsMgmtOfSwitchSyncFrameInfo(swtSyncFrameCfgIter,                                            /* SBSW_ETHTSYN_CSL02 */
        EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx));
      break;
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_SwtTimeSync_Int.c
 *********************************************************************************************************************/
