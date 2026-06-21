/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: StbM
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: StbM_Cfg.c
 *   Generation Time: 2026-06-19 21:41:28
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#define STBM_CFG_SOURCE

/**********************************************************************************************************************
 *  LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "StbM.h"
#include "Rte_StbM.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  StbM_EthClockConfig
**********************************************************************************************************************/
/** 
  \var    StbM_EthClockConfig
  \details
  Element         Description
  EthIfCtrlIdx    Index of the ethernet communication controller used as local clock.
*/ 
#define STBM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(StbM_EthClockConfigType, STBM_CONST) StbM_EthClockConfig[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    EthIfCtrlIdx        Referable Keys */
  { /*     0 */           0u },  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain_MAIN0] */
  { /*     1 */           0u }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain_MAIN6] */
};
#define STBM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_LocalClockConfig
**********************************************************************************************************************/
/** 
  \var    StbM_LocalClockConfig
  \details
  Element                                     Description
  HwFrequency                                 Frequency of the hardware reference clock in Hz.
  NumeratorOfFactorClockTicksToLocalTime      Pre calculated numerator of the rational number of the calculation: (StbMClockPrescaler * 10^15) / StbMClockFrequency.
  ClockType                                   The type of local clock, which is used as hardware clock
  DenominatorOfFactorClockTicksToLocalTime    Pre calculated denominator of the rational number of the calculation: (StbMClockPrescaler * 10^15) / StbMClockFrequency.
  EthClockConfigIdx                           the index of the 0:1 relation pointing to StbM_EthClockConfig
  HwPrescaler                                 Prescaler of hardware reference clock.
*/ 
#define STBM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(StbM_LocalClockConfigType, STBM_CONST) StbM_LocalClockConfig[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    HwFrequency  NumeratorOfFactorClockTicksToLocalTime  ClockType                                        DenominatorOfFactorClockTicksToLocalTime  EthClockConfigIdx                                                           HwPrescaler        Referable Keys */
  { /*     0 */  100000000u,                              10000000u, STBM_ETH_LOCALCLOCK_CLOCKTYPEOFLOCALCLOCKCONFIG,                                       1u,                0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain_MAIN0 */,          1u },  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  { /*     1 */  100000000u,                              10000000u, STBM_ETH_LOCALCLOCK_CLOCKTYPEOFLOCALCLOCKCONFIG,                                       1u,                1u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain_MAIN6 */,          1u }   /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */
};
#define STBM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_LocalTimeConfig
**********************************************************************************************************************/
/** 
  \var    StbM_LocalTimeConfig
  \brief  This table contains the local time information of all timebases.
  \details
  Element                Description
  LocalClockConfigIdx    the index of the 0:1 relation pointing to StbM_LocalClockConfig
  TimeBaseConfigIdx      the index of the 1:1 relation pointing to StbM_TimeBaseConfig
*/ 
#define STBM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(StbM_LocalTimeConfigType, STBM_CONST) StbM_LocalTimeConfig[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    LocalClockConfigIdx                                                         TimeBaseConfigIdx                                                               Referable Keys */
  { /*     0 */                  0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,                0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */ },  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  { /*     1 */                  1u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6 */,                1u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6 */ }   /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */
};
#define STBM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeBaseConfig
**********************************************************************************************************************/
/** 
  \var    StbM_TimeBaseConfig
  \brief  Configuration data from timebase. Contains all indirections to other tables.
  \details
  Element                         Description
  GlobalTimeMaster                true if time base has the role of a global time master
  SynchronizedTimeBase            Indicates if the time base is a synchronized time base.
  TimeSlave                       true if timebase has the role of a time slave
  LocalTimeConfigIdx              the index of the 0:1 relation pointing to StbM_LocalTimeConfig
  StatusIdx                       the index of the 1:1 relation pointing to StbM_Status
  TimeBaseId                      Id of the timebase.
  TimeCorrectionSlaveConfigIdx    the index of the 0:1 relation pointing to StbM_TimeCorrectionSlaveConfig
  TimeLeapConfigIdx               the index of the 0:1 relation pointing to StbM_TimeLeapConfig
  TimeoutConfigIdx                the index of the 0:1 relation pointing to StbM_TimeoutConfig
  UserDataStateIdx                the index of the 1:1 relation pointing to StbM_UserDataState
*/ 
#define STBM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(StbM_TimeBaseConfigType, STBM_CONST) StbM_TimeBaseConfig[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    GlobalTimeMaster  SynchronizedTimeBase  TimeSlave  LocalTimeConfigIdx                                                         StatusIdx                                                         TimeBaseId  TimeCorrectionSlaveConfigIdx                                                                                 TimeLeapConfigIdx                                                                                 TimeoutConfigIdx                                                                                 UserDataStateIdx                                                               Referable Keys */
  { /*     0 */            FALSE,                 TRUE,      TRUE,                 0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,        0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,         0u,                                                   0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,                                        0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,                                       0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,               0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */ },  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  { /*     1 */             TRUE,                 TRUE,     FALSE,                 1u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6 */,        1u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6 */,         6u, STBM_NO_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG  /* unusedIndex1 */                                   , STBM_NO_TIMELEAPCONFIGIDXOFTIMEBASECONFIG  /* unusedIndex1 */                                   , STBM_NO_TIMEOUTCONFIGIDXOFTIMEBASECONFIG  /* unusedIndex1 */                                   ,               1u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6 */ }   /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */
};
#define STBM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeCorrectionSlaveConfig
**********************************************************************************************************************/
/** 
  \var    StbM_TimeCorrectionSlaveConfig
  \details
  Element                                               Description
  OffsetCorrectionAdaptionInterval                      Defines the interval during which the adaptive rate correction cancels out the rate- and time deviation.
  OffsetCorrectionJumpThreshold                         Threshold for the correction method. Deviations below this value will be corrected by a linear reduction over a defined timespan. Values equal- and greater than this value will be corrected by immediately setting the correct time- and rate in form of a jump.
  NumberOfSimultaneousRateMeasurements                  Number of simultaneous rate measurements to determine the current rate deviation.
  RateCorrectionMeasurementDurationNanoseconds          Nanoseconds part of definition of the time span which is used to calculate the rate deviation.
  RateCorrectionMeasurementDurationSeconds              Seconds part of definition of the time span which is used to calculate the rate deviation.
  RateMeasurementsEndIdx                                the end index of the 1:n relation pointing to StbM_RateMeasurements
  RateMeasurementsStartIdx                              the start index of the 1:n relation pointing to StbM_RateMeasurements
  SingleRateCorrectionMeasurementDurationNanoseconds    Nanoseconds part of single duration of measurement: RateCorrectionMeasurementDuration / NumberOfSimultaneousRateMeasurements.
  SingleRateCorrectionMeasurementDurationSeconds        Seconds part of single duration of measurement: RateCorrectionMeasurementDuration / NumberOfSimultaneousRateMeasurements.
*/ 
#define STBM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(StbM_TimeCorrectionSlaveConfigType, STBM_CONST) StbM_TimeCorrectionSlaveConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    OffsetCorrectionAdaptionInterval  OffsetCorrectionJumpThreshold  NumberOfSimultaneousRateMeasurements  RateCorrectionMeasurementDurationNanoseconds  RateCorrectionMeasurementDurationSeconds  RateMeasurementsEndIdx                                                         RateMeasurementsStartIdx                                                         SingleRateCorrectionMeasurementDurationNanoseconds  SingleRateCorrectionMeasurementDurationSeconds        Referable Keys */
  { /*     0 */                       500000000u,                       100000u,                                   1u,                                           0u,                                       5u,                     1u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,                       0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */,                                                 0u,                                             5u }   /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
};
#define STBM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeLeapConfig
**********************************************************************************************************************/
/** 
  \var    StbM_TimeLeapConfig
  \details
  Element            Description
  FutureThreshold    Time leap threshold after which a future time leap is detected.
  PastThreshold      Time leap threshold after which a past time leap is detected.
  ClearCount         Counter after which the a time leap is deleted.
*/ 
#define STBM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(StbM_TimeLeapConfigType, STBM_CONST) StbM_TimeLeapConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    FutureThreshold  PastThreshold  ClearCount        Referable Keys */
  { /*     0 */         600000u,       600000u,         3u }   /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
};
#define STBM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeoutConfig
**********************************************************************************************************************/
/** 
  \var    StbM_TimeoutConfig
  \details
  Element                   Description
  SyncLossTimeoutCounter    Represents the amount of main functions until the timeout is expired. Calculated by Timeout(ns)/MainFunction(ns).
  TimeBaseConfigIdx         the index of the 1:1 relation pointing to StbM_TimeBaseConfig
*/ 
#define STBM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(StbM_TimeoutConfigType, STBM_CONST) StbM_TimeoutConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    SyncLossTimeoutCounter  TimeBaseConfigIdx                                                               Referable Keys */
  { /*     0 */                    50u,                0u  /* /ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0 */ }   /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
};
#define STBM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_Initialized
**********************************************************************************************************************/
/** 
  \var    StbM_Initialized
  \brief  Initialization state of the StbM. TRUE, if StbM_Init() has been called, else FALSE.
*/ 
#define STBM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_InitializedType, STBM_VAR_ZERO_INIT) StbM_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define STBM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_LocalClockState
**********************************************************************************************************************/
/** 
  \var    StbM_LocalClockState
  \brief  State table for Local Time unit.
  \details
  Element           Description
  FractionalPart    The fractional part of the VirtualLocalTime * (HWPrescaler / HWFrequency) calculation in order to increase the precision.
  LastReadTime      Last read time of the lock clock. This can be either a counter value or a real time.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_LocalClockStateUType, STBM_VAR_NOINIT) StbM_LocalClockState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  /*     1 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_LocalTimeState
**********************************************************************************************************************/
/** 
  \var    StbM_LocalTimeState
  \brief  Local time state table.
  \details
  Element             Description
  TimeLeap            The last calculated time leap TGrx - TL.
  LocalTimeUpdated    Indicate if LocalTime is updated and therefore valid, hence can be used without recalculating it. (E_OK | E_NOT_OK)
  TimeLeapValid       Flag which indicates if the calculated time leap is valid.
  GlobalTimeRx        TGrx (received global time).
  GlobalTimeSync      TGsync (local time after update).
  LocalTime           TL (current corrected local time).
  LocalTimeSync       TLsync (local time before update).
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_LocalTimeStateUType, STBM_VAR_NOINIT) StbM_LocalTimeState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  /*     1 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_RateMeasurements
**********************************************************************************************************************/
/** 
  \var    StbM_RateMeasurements
  \brief  Table with current rate measurement snapshots
  \details
  Element                  Description
  Valid                    True if the measurement is valid.
  StartGlobalTime          Global time at the start of a measurement.
  StartStatus              Status of the start time snapshot
  StartVirtualLocalTime    Virtual local time at the start of a measurement.
  StopGlobalTime           Global time at the stop of a measurement.
  StopStatus               Status of the stop time snapshot
  StopVirtualLocalTime     Virtual local time at the stop of a measurement.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_RateMeasurementsUType, STBM_VAR_NOINIT) StbM_RateMeasurements;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_Status
**********************************************************************************************************************/
/** 
  \var    StbM_Status
  \brief  Table with timebase status
  \details
  Element             Description
  GlobalTimeStatus    Status of received global time.
  LocalTimeStatus     Status of local time.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_StatusUType, STBM_VAR_NOINIT) StbM_Status;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  /*     1 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeBaseState
**********************************************************************************************************************/
/** 
  \var    StbM_TimeBaseState
  \brief  Internal state of the Time Bases.
  \details
  Element          Description
  UpdateCounter    Actual counter value for immediate time synchronisation.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_TimeBaseStateUType, STBM_VAR_NOINIT) StbM_TimeBaseState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  /*     1 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeCorrectionSlaveState
**********************************************************************************************************************/
/** 
  \var    StbM_TimeCorrectionSlaveState
  \brief  State table of time correction values for slave.
  \details
  Element                        Description
  OffsetRateCorrection           Current rate for time offset elimination via rate adaption denoted as: r_oc.
  RateCorrection                 Current rate for rate correction denoted as: r_rc.
  CurrentRateMeasurementIndex    The index of the current used rate measurement storage.
  OffsetCorrectionRateValid      True, if valid offset correction rate has been calculated and shall be applied.
  RateDeviationValid             True, if at least one valid rate deviation has been calculated.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_TimeCorrectionSlaveStateUType, STBM_VAR_NOINIT) StbM_TimeCorrectionSlaveState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeLeapState
**********************************************************************************************************************/
/** 
  \var    StbM_TimeLeapState
  \details
  Element       Description
  ClearCount    Clear counter to count until a detected timeleap is reset.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_TimeLeapStateUType, STBM_VAR_NOINIT) StbM_TimeLeapState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_TimeoutState
**********************************************************************************************************************/
/** 
  \var    StbM_TimeoutState
  \details
  Element                   Description
  SyncLossTimeoutCounter    Timeout for the synchronisation of the Time Base.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_TimeoutStateUType, STBM_VAR_NOINIT) StbM_TimeoutState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_UserDataState
**********************************************************************************************************************/
/** 
  \var    StbM_UserDataState
  \brief  State table for user data.
  \details
  Element     Description
  UserData    User data.
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_UserDataStateUType, STBM_VAR_NOINIT) StbM_UserDataState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  /*     1 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  StbM_VirtualLocalTimeState
**********************************************************************************************************************/
/** 
  \var    StbM_VirtualLocalTimeState
  \brief  Virtual local time state table.
  \details
  Element                 Description
  VirtualLocalTime        TV (current virtual local time).
  VirtualLocalTimeRx      TVrx (received virtual local time).
  VirtualLocalTimeSync    TVsync (virtual local time at last synchronization event).
*/ 
#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(StbM_VirtualLocalTimeStateUType, STBM_VAR_NOINIT) StbM_VirtualLocalTimeState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN0] */
  /*     1 */  /* [/ActiveEcuC/StbM/StbMSynchronizedTimeBase_MAIN6] */

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: StbM_Cfg.c
 *********************************************************************************************************************/
