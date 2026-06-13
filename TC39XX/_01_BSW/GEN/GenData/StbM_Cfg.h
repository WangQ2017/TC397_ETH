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
 *              File: StbM_Cfg.h
 *   Generation Time: 2026-05-23 23:37:07
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (STBM_CFG_H)
# define STBM_CFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "StbM_Types.h"
# include "EthIf.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* General defines */
#ifndef STBM_USE_DUMMY_STATEMENT
#define STBM_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef STBM_DUMMY_STATEMENT
#define STBM_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef STBM_DUMMY_STATEMENT_CONST
#define STBM_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef STBM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define STBM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef STBM_ATOMIC_VARIABLE_ACCESS
#define STBM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef STBM_PROCESSOR_TC397X_STEPB
#define STBM_PROCESSOR_TC397X_STEPB
#endif
#ifndef STBM_COMP_TASKING
#define STBM_COMP_TASKING
#endif
#ifndef STBM_GEN_GENERATOR_MSR
#define STBM_GEN_GENERATOR_MSR
#endif
#ifndef STBM_CPUTYPE_BITORDER_LSB2MSB
#define STBM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef STBM_CONFIGURATION_VARIANT_PRECOMPILE
#define STBM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef STBM_CONFIGURATION_VARIANT_LINKTIME
#define STBM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef STBM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define STBM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef STBM_CONFIGURATION_VARIANT
#define STBM_CONFIGURATION_VARIANT STBM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef STBM_POSTBUILD_VARIANT_SUPPORT
#define STBM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/* Version identification */
# define STBM_CFG_MAJOR_VERSION                              (8u)
# define STBM_CFG_MINOR_VERSION                              (1u)

/* AUTOSAR version */
# define STBM_AR_MAJOR_VERSION                               (4u)
# define STBM_AR_MINOR_VERSION                               (3u)
# define STBM_AR_PATCH_VERSION                               (1u)

# define STBM_DEV_ERROR_DETECT                               (STD_ON)    /**< /ActiveEcuC/StbM/StbMGeneral[0:StbMSafeBswChecks] || /ActiveEcuC/StbM/StbMGeneral[0:StbMDevErrorDetect] */
# define STBM_DEV_ERROR_REPORT                               (STD_ON) 
# define STBM_VERSION_INFO_API                               (STD_OFF)    /**< /ActiveEcuC/StbM/StbMGeneral[0:StbMVersionInfoApi] */
# define STBM_MAIN_FUNCTION_CYCLE                            (10uL /*  ms  */ )    /**< /ActiveEcuC/StbM/StbMGeneral[0:StbMMainFunctionPeriod] */
# define STBM_GET_CURRENT_TIME_EXTENDED_API                  (STD_OFF) /**< Deactivateable: 'StbMGetCurrentTimeExtendedAvailable' Reason: the module configuration does not support extended timestamp */

/* Symbolic Name Values of TimeBases */
#define StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN0 0u 
#define StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase_MAIN6 1u 

# define STBM_UNUSED_INDEX                                   (0xFFFFu)

# define STBM_HAS_MULTIPLE_TIMEBASE_CONFIGS                   (STD_ON)
# define STBM_HAS_RUNTIME_CHECKING                            (STD_OFF)
# define STBM_HAS_ALLOW_SYSTEM_WIDE_GLOBAL_TIME_MASTER        (STD_OFF)


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  StbMPCDataSwitches  StbM Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define STBM_ETHCLOCKCONFIG                                                                         STD_ON
#define STBM_ETHIFCTRLIDXOFETHCLOCKCONFIG                                                           STD_ON
#define STBM_FINALMAGICNUMBER                                                                       STD_OFF  /**< Deactivateable: 'StbM_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define STBM_GPTCLOCKCONFIG                                                                         STD_OFF  /**< Deactivateable: 'StbM_GptClockConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_GPTCHANNELSYMBOLICNAMEOFGPTCLOCKCONFIG                                                 STD_OFF  /**< Deactivateable: 'StbM_GptClockConfig.GptChannelSymbolicName' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_MAXTICKVALUEOFGPTCLOCKCONFIG                                                           STD_OFF  /**< Deactivateable: 'StbM_GptClockConfig.MaxTickValue' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_GPTCLOCKSTATE                                                                          STD_OFF  /**< Deactivateable: 'StbM_GptClockState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_GPTCHANNELACTIVEOFGPTCLOCKSTATE                                                        STD_OFF  /**< Deactivateable: 'StbM_GptClockState.GptChannelActive' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_INITDATAHASHCODE                                                                       STD_OFF  /**< Deactivateable: 'StbM_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define STBM_INITIALIZED                                                                            STD_ON
#define STBM_LOCALCLOCKCONFIG                                                                       STD_ON
#define STBM_CLOCKTYPEOFLOCALCLOCKCONFIG                                                            STD_ON
#define STBM_DENOMINATOROFFACTORCLOCKTICKSTOLOCALTIMEOFLOCALCLOCKCONFIG                             STD_ON
#define STBM_ETHCLOCKCONFIGIDXOFLOCALCLOCKCONFIG                                                    STD_ON
#define STBM_ETHCLOCKCONFIGUSEDOFLOCALCLOCKCONFIG                                                   STD_ON
#define STBM_GPTCLOCKCONFIGIDXOFLOCALCLOCKCONFIG                                                    STD_OFF  /**< Deactivateable: 'StbM_LocalClockConfig.GptClockConfigIdx' Reason: 'the optional indirection is deactivated because GptClockConfigUsedOfLocalClockConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_GPTCLOCKCONFIGUSEDOFLOCALCLOCKCONFIG                                                   STD_OFF  /**< Deactivateable: 'StbM_LocalClockConfig.GptClockConfigUsed' Reason: 'the optional indirection is deactivated because GptClockConfigUsedOfLocalClockConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_HWFREQUENCYOFLOCALCLOCKCONFIG                                                          STD_ON
#define STBM_HWPRESCALEROFLOCALCLOCKCONFIG                                                          STD_ON
#define STBM_NUMERATOROFFACTORCLOCKTICKSTOLOCALTIMEOFLOCALCLOCKCONFIG                               STD_ON
#define STBM_OSCLOCKCONFIGIDXOFLOCALCLOCKCONFIG                                                     STD_OFF  /**< Deactivateable: 'StbM_LocalClockConfig.OsClockConfigIdx' Reason: 'the optional indirection is deactivated because OsClockConfigUsedOfLocalClockConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_OSCLOCKCONFIGUSEDOFLOCALCLOCKCONFIG                                                    STD_OFF  /**< Deactivateable: 'StbM_LocalClockConfig.OsClockConfigUsed' Reason: 'the optional indirection is deactivated because OsClockConfigUsedOfLocalClockConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_LOCALCLOCKSTATE                                                                        STD_ON
#define STBM_FRACTIONALPARTOFLOCALCLOCKSTATE                                                        STD_ON
#define STBM_LASTREADTIMEOFLOCALCLOCKSTATE                                                          STD_ON
#define STBM_LOCALTIMECONFIG                                                                        STD_ON
#define STBM_LOCALCLOCKCONFIGIDXOFLOCALTIMECONFIG                                                   STD_ON
#define STBM_LOCALCLOCKCONFIGUSEDOFLOCALTIMECONFIG                                                  STD_ON
#define STBM_TIMEBASECONFIGIDXOFLOCALTIMECONFIG                                                     STD_ON
#define STBM_LOCALTIMESTATE                                                                         STD_ON
#define STBM_GLOBALTIMERXOFLOCALTIMESTATE                                                           STD_ON
#define STBM_GLOBALTIMESYNCOFLOCALTIMESTATE                                                         STD_ON
#define STBM_LOCALTIMEOFLOCALTIMESTATE                                                              STD_ON
#define STBM_LOCALTIMESYNCOFLOCALTIMESTATE                                                          STD_ON
#define STBM_LOCALTIMEUPDATEDOFLOCALTIMESTATE                                                       STD_ON
#define STBM_TIMELEAPOFLOCALTIMESTATE                                                               STD_ON
#define STBM_TIMELEAPVALIDOFLOCALTIMESTATE                                                          STD_ON
#define STBM_OFFSETTIMERECORDINGBLOCK                                                               STD_OFF  /**< Deactivateable: 'StbM_OffsetTimeRecordingBlock' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_GLBNANOSECONDSOFOFFSETTIMERECORDINGBLOCK                                               STD_OFF  /**< Deactivateable: 'StbM_OffsetTimeRecordingBlock.GlbNanoSeconds' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_GLBSECONDSOFOFFSETTIMERECORDINGBLOCK                                                   STD_OFF  /**< Deactivateable: 'StbM_OffsetTimeRecordingBlock.GlbSeconds' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEBASESTATUSOFOFFSETTIMERECORDINGBLOCK                                               STD_OFF  /**< Deactivateable: 'StbM_OffsetTimeRecordingBlock.TimeBaseStatus' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_OFFSETTIMERECORDINGHEADER                                                              STD_OFF  /**< Deactivateable: 'StbM_OffsetTimeRecordingHeader' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_OFFSETTIMEDOMAINOFOFFSETTIMERECORDINGHEADER                                            STD_OFF  /**< Deactivateable: 'StbM_OffsetTimeRecordingHeader.OffsetTimeDomain' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_OSCLOCKCONFIG                                                                          STD_OFF  /**< Deactivateable: 'StbM_OsClockConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_OSCOUNTERSYMBOLICNAMEOFOSCLOCKCONFIG                                                   STD_OFF  /**< Deactivateable: 'StbM_OsClockConfig.OsCounterSymbolicName' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_RATEMEASUREMENTS                                                                       STD_ON
#define STBM_STARTGLOBALTIMEOFRATEMEASUREMENTS                                                      STD_ON
#define STBM_STARTSTATUSOFRATEMEASUREMENTS                                                          STD_ON
#define STBM_STARTVIRTUALLOCALTIMEOFRATEMEASUREMENTS                                                STD_ON
#define STBM_STOPGLOBALTIMEOFRATEMEASUREMENTS                                                       STD_ON
#define STBM_STOPSTATUSOFRATEMEASUREMENTS                                                           STD_ON
#define STBM_STOPVIRTUALLOCALTIMEOFRATEMEASUREMENTS                                                 STD_ON
#define STBM_VALIDOFRATEMEASUREMENTS                                                                STD_ON
#define STBM_SIZEOFETHCLOCKCONFIG                                                                   STD_ON
#define STBM_SIZEOFLOCALCLOCKCONFIG                                                                 STD_ON
#define STBM_SIZEOFLOCALCLOCKSTATE                                                                  STD_ON
#define STBM_SIZEOFLOCALTIMECONFIG                                                                  STD_ON
#define STBM_SIZEOFLOCALTIMESTATE                                                                   STD_ON
#define STBM_SIZEOFRATEMEASUREMENTS                                                                 STD_ON
#define STBM_SIZEOFSTATUS                                                                           STD_ON
#define STBM_SIZEOFTIMEBASECONFIG                                                                   STD_ON
#define STBM_SIZEOFTIMEBASESTATE                                                                    STD_ON
#define STBM_SIZEOFTIMECORRECTIONSLAVECONFIG                                                        STD_ON
#define STBM_SIZEOFTIMECORRECTIONSLAVESTATE                                                         STD_ON
#define STBM_SIZEOFTIMELEAPCONFIG                                                                   STD_ON
#define STBM_SIZEOFTIMELEAPSTATE                                                                    STD_ON
#define STBM_SIZEOFTIMEOUTCONFIG                                                                    STD_ON
#define STBM_SIZEOFTIMEOUTSTATE                                                                     STD_ON
#define STBM_SIZEOFUSERDATASTATE                                                                    STD_ON
#define STBM_SIZEOFVIRTUALLOCALTIMESTATE                                                            STD_ON
#define STBM_STATUS                                                                                 STD_ON
#define STBM_GLOBALTIMESTATUSOFSTATUS                                                               STD_ON
#define STBM_LOCALTIMESTATUSOFSTATUS                                                                STD_ON
#define STBM_STATUSNOTIFICATIONCUSTOMERCALLBACK                                                     STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationCustomerCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFSTATUSNOTIFICATIONCUSTOMERCALLBACK                                           STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationCustomerCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_STATUSNOTIFICATIONCUSTOMERCONFIG                                                       STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationCustomerConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_STATUSNOTIFICATIONCUSTOMERCALLBACKIDXOFSTATUSNOTIFICATIONCUSTOMERCONFIG                STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationCustomerConfig.StatusNotificationCustomerCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_STATUSNOTIFICATIONEVENTMASKOFSTATUSNOTIFICATIONCUSTOMERCONFIG                          STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationCustomerConfig.StatusNotificationEventMask' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_STATUSNOTIFICATIONSTATE                                                                STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_EVENTSOFSTATUSNOTIFICATIONSTATE                                                        STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationState.Events' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_LASTSTATUSOFSTATUSNOTIFICATIONSTATE                                                    STD_OFF  /**< Deactivateable: 'StbM_StatusNotificationState.LastStatus' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_SYNCTIMERECORDINGBLOCK                                                                 STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_GLBNANOSECONDSOFSYNCTIMERECORDINGBLOCK                                                 STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.GlbNanoSeconds' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_GLBSECONDSOFSYNCTIMERECORDINGBLOCK                                                     STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.GlbSeconds' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_LOCNANOSECONDSOFSYNCTIMERECORDINGBLOCK                                                 STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.LocNanoSeconds' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_LOCSECONDSOFSYNCTIMERECORDINGBLOCK                                                     STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.LocSeconds' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_PATHDELAYOFSYNCTIMERECORDINGBLOCK                                                      STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.PathDelay' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RATEDEVIATIONOFSYNCTIMERECORDINGBLOCK                                                  STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.RateDeviation' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEBASESTATUSOFSYNCTIMERECORDINGBLOCK                                                 STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.TimeBaseStatus' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_VIRTUALLOCALTIMELOWOFSYNCTIMERECORDINGBLOCK                                            STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingBlock.VirtualLocalTimeLow' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_SYNCTIMERECORDINGHEADER                                                                STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingHeader' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_HWFREQUENCYOFSYNCTIMERECORDINGHEADER                                                   STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingHeader.HwFrequency' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_HWPRESCALEROFSYNCTIMERECORDINGHEADER                                                   STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingHeader.HwPrescaler' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEDOMAINOFSYNCTIMERECORDINGHEADER                                                    STD_OFF  /**< Deactivateable: 'StbM_SyncTimeRecordingHeader.TimeDomain' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEBASECONFIG                                                                         STD_ON
#define STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG                                                       STD_ON
#define STBM_LOCALTIMECONFIGIDXOFTIMEBASECONFIG                                                     STD_ON
#define STBM_LOCALTIMECONFIGUSEDOFTIMEBASECONFIG                                                    STD_ON
#define STBM_PURELOCALTIMEBASEOFTIMEBASECONFIG                                                      STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.PureLocalTimeBase' Reason: 'the value of StbM_PureLocalTimeBaseOfTimeBaseConfig is always 'false' due to this, the array is deactivated.' */
#define STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG                                                       STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.ReservedTimeBase' Reason: 'the value of StbM_ReservedTimeBaseOfTimeBaseConfig is always 'false' due to this, the array is deactivated.' */
#define STBM_STATUSIDXOFTIMEBASECONFIG                                                              STD_ON
#define STBM_STATUSNOTIFICATIONCUSTOMERCONFIGIDXOFTIMEBASECONFIG                                    STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.StatusNotificationCustomerConfigIdx' Reason: 'the optional indirection is deactivated because StatusNotificationCustomerConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_STATUSNOTIFICATIONCUSTOMERCONFIGUSEDOFTIMEBASECONFIG                                   STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.StatusNotificationCustomerConfigUsed' Reason: 'the optional indirection is deactivated because StatusNotificationCustomerConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_SYNCHRONIZEDTIMEBASEOFTIMEBASECONFIG                                                   STD_ON
#define STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG                                                      STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeBaseConfigIdx' Reason: 'the optional indirection is deactivated because TimeBaseConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMEBASECONFIGUSEDOFTIMEBASECONFIG                                                     STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeBaseConfigUsed' Reason: 'the optional indirection is deactivated because TimeBaseConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMEBASEIDOFTIMEBASECONFIG                                                             STD_ON
#define STBM_TIMECORRECTIONMASTERCONFIGIDXOFTIMEBASECONFIG                                          STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeCorrectionMasterConfigIdx' Reason: 'the optional indirection is deactivated because TimeCorrectionMasterConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMECORRECTIONMASTERCONFIGUSEDOFTIMEBASECONFIG                                         STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeCorrectionMasterConfigUsed' Reason: 'the optional indirection is deactivated because TimeCorrectionMasterConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG                                           STD_ON
#define STBM_TIMECORRECTIONSLAVECONFIGUSEDOFTIMEBASECONFIG                                          STD_ON
#define STBM_TIMEGATEWAYOFTIMEBASECONFIG                                                            STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeGateway' Reason: 'the value of StbM_TimeGatewayOfTimeBaseConfig is always 'false' due to this, the array is deactivated.' */
#define STBM_TIMELEAPCONFIGIDXOFTIMEBASECONFIG                                                      STD_ON
#define STBM_TIMELEAPCONFIGUSEDOFTIMEBASECONFIG                                                     STD_ON
#define STBM_TIMENOTIFICATIONCONFIGENDIDXOFTIMEBASECONFIG                                           STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeNotificationConfigEndIdx' Reason: 'the optional indirection is deactivated because TimeNotificationConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMENOTIFICATIONCONFIGSTARTIDXOFTIMEBASECONFIG                                         STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeNotificationConfigStartIdx' Reason: 'the optional indirection is deactivated because TimeNotificationConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMENOTIFICATIONCONFIGUSEDOFTIMEBASECONFIG                                             STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeNotificationConfigUsed' Reason: 'the optional indirection is deactivated because TimeNotificationConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMERECORDINGCONFIGIDXOFTIMEBASECONFIG                                                 STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeRecordingConfigIdx' Reason: 'the optional indirection is deactivated because TimeRecordingConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMERECORDINGCONFIGUSEDOFTIMEBASECONFIG                                                STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeRecordingConfigUsed' Reason: 'the optional indirection is deactivated because TimeRecordingConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMESLAVEOFTIMEBASECONFIG                                                              STD_ON
#define STBM_TIMEVALIDATIONCONFIGIDXOFTIMEBASECONFIG                                                STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeValidationConfigIdx' Reason: 'the optional indirection is deactivated because TimeValidationConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMEVALIDATIONCONFIGUSEDOFTIMEBASECONFIG                                               STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TimeValidationConfigUsed' Reason: 'the optional indirection is deactivated because TimeValidationConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TIMEOUTCONFIGIDXOFTIMEBASECONFIG                                                       STD_ON
#define STBM_TIMEOUTCONFIGUSEDOFTIMEBASECONFIG                                                      STD_ON
#define STBM_TRIGGEREDCUSTOMERCONFIGIDXOFTIMEBASECONFIG                                             STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TriggeredCustomerConfigIdx' Reason: 'the optional indirection is deactivated because TriggeredCustomerConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_TRIGGEREDCUSTOMERCONFIGUSEDOFTIMEBASECONFIG                                            STD_OFF  /**< Deactivateable: 'StbM_TimeBaseConfig.TriggeredCustomerConfigUsed' Reason: 'the optional indirection is deactivated because TriggeredCustomerConfigUsedOfTimeBaseConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define STBM_USERDATASTATEIDXOFTIMEBASECONFIG                                                       STD_ON
#define STBM_TIMEBASESTATE                                                                          STD_ON
#define STBM_UPDATECOUNTEROFTIMEBASESTATE                                                           STD_ON
#define STBM_TIMECORRECTIONMASTERCONFIG                                                             STD_OFF  /**< Deactivateable: 'StbM_TimeCorrectionMasterConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_MAXRATEDEVIATIONOFTIMECORRECTIONMASTERCONFIG                                           STD_OFF  /**< Deactivateable: 'StbM_TimeCorrectionMasterConfig.MaxRateDeviation' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMECORRECTIONMASTERSTATE                                                              STD_OFF  /**< Deactivateable: 'StbM_TimeCorrectionMasterState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RATECORRECTIONRATEOFTIMECORRECTIONMASTERSTATE                                          STD_OFF  /**< Deactivateable: 'StbM_TimeCorrectionMasterState.RateCorrectionRate' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RATEDEVIATIONVALIDOFTIMECORRECTIONMASTERSTATE                                          STD_OFF  /**< Deactivateable: 'StbM_TimeCorrectionMasterState.RateDeviationValid' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMECORRECTIONSLAVECONFIG                                                              STD_ON
#define STBM_NUMBEROFSIMULTANEOUSRATEMEASUREMENTSOFTIMECORRECTIONSLAVECONFIG                        STD_ON
#define STBM_OFFSETCORRECTIONADAPTIONINTERVALOFTIMECORRECTIONSLAVECONFIG                            STD_ON
#define STBM_OFFSETCORRECTIONJUMPTHRESHOLDOFTIMECORRECTIONSLAVECONFIG                               STD_ON
#define STBM_RATECORRECTIONMEASUREMENTDURATIONNANOSECONDSOFTIMECORRECTIONSLAVECONFIG                STD_ON
#define STBM_RATECORRECTIONMEASUREMENTDURATIONSECONDSOFTIMECORRECTIONSLAVECONFIG                    STD_ON
#define STBM_RATEMEASUREMENTSENDIDXOFTIMECORRECTIONSLAVECONFIG                                      STD_ON
#define STBM_RATEMEASUREMENTSSTARTIDXOFTIMECORRECTIONSLAVECONFIG                                    STD_ON
#define STBM_SINGLERATECORRECTIONMEASUREMENTDURATIONNANOSECONDSOFTIMECORRECTIONSLAVECONFIG          STD_ON
#define STBM_SINGLERATECORRECTIONMEASUREMENTDURATIONSECONDSOFTIMECORRECTIONSLAVECONFIG              STD_ON
#define STBM_TIMECORRECTIONSLAVESTATE                                                               STD_ON
#define STBM_CURRENTRATEMEASUREMENTINDEXOFTIMECORRECTIONSLAVESTATE                                  STD_ON
#define STBM_OFFSETCORRECTIONRATEVALIDOFTIMECORRECTIONSLAVESTATE                                    STD_ON
#define STBM_OFFSETRATECORRECTIONOFTIMECORRECTIONSLAVESTATE                                         STD_ON
#define STBM_RATECORRECTIONOFTIMECORRECTIONSLAVESTATE                                               STD_ON
#define STBM_RATEDEVIATIONVALIDOFTIMECORRECTIONSLAVESTATE                                           STD_ON
#define STBM_TIMELEAPCONFIG                                                                         STD_ON
#define STBM_CLEARCOUNTOFTIMELEAPCONFIG                                                             STD_ON
#define STBM_FUTURETHRESHOLDOFTIMELEAPCONFIG                                                        STD_ON
#define STBM_PASTTHRESHOLDOFTIMELEAPCONFIG                                                          STD_ON
#define STBM_TIMELEAPSTATE                                                                          STD_ON
#define STBM_CLEARCOUNTOFTIMELEAPSTATE                                                              STD_ON
#define STBM_TIMENOTIFICATIONCALLBACK                                                               STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFTIMENOTIFICATIONCALLBACK                                                     STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMENOTIFICATIONCONFIG                                                                 STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_TIMEBASECONFIGIDXOFTIMENOTIFICATIONCONFIG                                              STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationConfig.TimeBaseConfigIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMENOTIFICATIONCALLBACKIDXOFTIMENOTIFICATIONCONFIG                                    STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationConfig.TimeNotificationCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERSTARTTHRESHOLDNANOSECONDSOFTIMENOTIFICATIONCONFIG                                 STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationConfig.TimerStartThresholdNanoseconds' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERSTARTTHRESHOLDSECONDSOFTIMENOTIFICATIONCONFIG                                     STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationConfig.TimerStartThresholdSeconds' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMENOTIFICATIONSTATE                                                                  STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_EXPIRETIMEOFTIMENOTIFICATIONSTATE                                                      STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationState.ExpireTime' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_STARTTIMEOFTIMENOTIFICATIONSTATE                                                       STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationState.StartTime' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMERSTATEOFTIMENOTIFICATIONSTATE                                                      STD_OFF  /**< Deactivateable: 'StbM_TimeNotificationState.TimerState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMERECORDINGCONFIG                                                                    STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_BLOCKCOUNTOFTIMERECORDINGCONFIG                                                        STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.BlockCount' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_OFFSETTIMERECORDINGBLOCKENDIDXOFTIMERECORDINGCONFIG                                    STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.OffsetTimeRecordingBlockEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_OFFSETTIMERECORDINGBLOCKSTARTIDXOFTIMERECORDINGCONFIG                                  STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.OffsetTimeRecordingBlockStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_OFFSETTIMERECORDINGBLOCKUSEDOFTIMERECORDINGCONFIG                                      STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.OffsetTimeRecordingBlockUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_OFFSETTIMERECORDINGHEADERIDXOFTIMERECORDINGCONFIG                                      STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.OffsetTimeRecordingHeaderIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_OFFSETTIMERECORDINGHEADERUSEDOFTIMERECORDINGCONFIG                                     STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.OffsetTimeRecordingHeaderUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_SYNCTIMERECORDINGBLOCKENDIDXOFTIMERECORDINGCONFIG                                      STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.SyncTimeRecordingBlockEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_SYNCTIMERECORDINGBLOCKSTARTIDXOFTIMERECORDINGCONFIG                                    STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.SyncTimeRecordingBlockStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_SYNCTIMERECORDINGBLOCKUSEDOFTIMERECORDINGCONFIG                                        STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.SyncTimeRecordingBlockUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_SYNCTIMERECORDINGHEADERIDXOFTIMERECORDINGCONFIG                                        STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.SyncTimeRecordingHeaderIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_SYNCTIMERECORDINGHEADERUSEDOFTIMERECORDINGCONFIG                                       STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.SyncTimeRecordingHeaderUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEBASECONFIGIDXOFTIMERECORDINGCONFIG                                                 STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.TimeBaseConfigIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEBASECONFIGUSEDOFTIMERECORDINGCONFIG                                                STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.TimeBaseConfigUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERECORDINGOFFSETCALLBACKIDXOFTIMERECORDINGCONFIG                                    STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.TimeRecordingOffsetCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERECORDINGOFFSETCALLBACKUSEDOFTIMERECORDINGCONFIG                                   STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.TimeRecordingOffsetCallbackUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERECORDINGSYNCCALLBACKIDXOFTIMERECORDINGCONFIG                                      STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.TimeRecordingSyncCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERECORDINGSYNCCALLBACKUSEDOFTIMERECORDINGCONFIG                                     STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingConfig.TimeRecordingSyncCallbackUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERECORDINGOFFSETCALLBACK                                                            STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingOffsetCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFTIMERECORDINGOFFSETCALLBACK                                                  STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingOffsetCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMERECORDINGSTATE                                                                     STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_CURRENTBLOCKIDXOFTIMERECORDINGSTATE                                                    STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingState.CurrentBlockIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_PATHDELAYOFTIMERECORDINGSTATE                                                          STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingState.PathDelay' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RECORDEDBLOCKSCOUNTOFTIMERECORDINGSTATE                                                STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingState.RecordedBlocksCount' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMERECORDINGSYNCCALLBACK                                                              STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingSyncCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFTIMERECORDINGSYNCCALLBACK                                                    STD_OFF  /**< Deactivateable: 'StbM_TimeRecordingSyncCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONCONFIG                                                                   STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_BLOCKCOUNTOFTIMEVALIDATIONCONFIG                                                       STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig.BlockCount' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERCONFIGENDIDXOFTIMEVALIDATIONCONFIG                              STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig.TimeValidationEthMasterConfigEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERCONFIGLENGTHOFTIMEVALIDATIONCONFIG                              STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig.TimeValidationEthMasterConfigLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERCONFIGSTARTIDXOFTIMEVALIDATIONCONFIG                            STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig.TimeValidationEthMasterConfigStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERCONFIGUSEDOFTIMEVALIDATIONCONFIG                                STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig.TimeValidationEthMasterConfigUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHSLAVECONFIGIDXOFTIMEVALIDATIONCONFIG                                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig.TimeValidationEthSlaveConfigIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHSLAVECONFIGUSEDOFTIMEVALIDATIONCONFIG                                 STD_OFF  /**< Deactivateable: 'StbM_TimeValidationConfig.TimeValidationEthSlaveConfigUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERBLOCKDATA                                                       STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterBlockData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_ETHMASTERTIMINGDATAOFTIMEVALIDATIONETHMASTERBLOCKDATA                                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterBlockData.EthMasterTimingData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHMASTERCALLBACK                                                        STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFTIMEVALIDATIONETHMASTERCALLBACK                                              STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERCONFIG                                                          STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_TIMEVALIDATIONCONFIGIDXOFTIMEVALIDATIONETHMASTERCONFIG                                 STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig.TimeValidationConfigIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERBLOCKDATAENDIDXOFTIMEVALIDATIONETHMASTERCONFIG                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig.TimeValidationEthMasterBlockDataEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERBLOCKDATASTARTIDXOFTIMEVALIDATIONETHMASTERCONFIG                STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig.TimeValidationEthMasterBlockDataStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERCALLBACKIDXOFTIMEVALIDATIONETHMASTERCONFIG                      STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig.TimeValidationEthMasterCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYRESPONDERBLOCKDATAENDIDXOFTIMEVALIDATIONETHMASTERCONFIG         STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig.TimeValidationEthPdelayResponderBlockDataEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYRESPONDERBLOCKDATASTARTIDXOFTIMEVALIDATIONETHMASTERCONFIG       STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig.TimeValidationEthPdelayResponderBlockDataStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYRESPONDERCALLBACKIDXOFTIMEVALIDATIONETHMASTERCONFIG             STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterConfig.TimeValidationEthPdelayResponderCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHMASTERIDENTIFICATION                                                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterIdentification' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_PORTIDOFTIMEVALIDATIONETHMASTERIDENTIFICATION                                          STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterIdentification.PortId' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHMASTERSTATE                                                           STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_CURRENTBLOCKIDXOFTIMEVALIDATIONETHMASTERSTATE                                          STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterState.CurrentBlockIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RECORDEDBLOCKSCOUNTOFTIMEVALIDATIONETHMASTERSTATE                                      STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthMasterState.RecordedBlocksCount' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHPDELAYINITIATORBLOCKDATA                                              STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayInitiatorBlockData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_ETHPDELAYINITIATORTIMINGDATAOFTIMEVALIDATIONETHPDELAYINITIATORBLOCKDATA                STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayInitiatorBlockData.EthPdelayInitiatorTimingData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHPDELAYINITIATORCALLBACK                                               STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayInitiatorCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFTIMEVALIDATIONETHPDELAYINITIATORCALLBACK                                     STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayInitiatorCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYINITIATORSTATE                                                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayInitiatorState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_CURRENTBLOCKIDXOFTIMEVALIDATIONETHPDELAYINITIATORSTATE                                 STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayInitiatorState.CurrentBlockIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RECORDEDBLOCKSCOUNTOFTIMEVALIDATIONETHPDELAYINITIATORSTATE                             STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayInitiatorState.RecordedBlocksCount' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHPDELAYRESPONDERBLOCKDATA                                              STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayResponderBlockData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_ETHPDELAYRESPONDERTIMINGDATAOFTIMEVALIDATIONETHPDELAYRESPONDERBLOCKDATA                STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayResponderBlockData.EthPdelayResponderTimingData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHPDELAYRESPONDERCALLBACK                                               STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayResponderCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFTIMEVALIDATIONETHPDELAYRESPONDERCALLBACK                                     STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayResponderCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYRESPONDERSTATE                                                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayResponderState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_CURRENTBLOCKIDXOFTIMEVALIDATIONETHPDELAYRESPONDERSTATE                                 STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayResponderState.CurrentBlockIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RECORDEDBLOCKSCOUNTOFTIMEVALIDATIONETHPDELAYRESPONDERSTATE                             STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthPdelayResponderState.RecordedBlocksCount' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHSLAVEBLOCKDATA                                                        STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveBlockData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_ETHSLAVETIMINGDATAOFTIMEVALIDATIONETHSLAVEBLOCKDATA                                    STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveBlockData.EthSlaveTimingData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEVALIDATIONETHSLAVECALLBACK                                                         STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveCallback' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_CALLBACKOFTIMEVALIDATIONETHSLAVECALLBACK                                               STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveCallback.Callback' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHSLAVECONFIG                                                           STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_TIMEVALIDATIONCONFIGIDXOFTIMEVALIDATIONETHSLAVECONFIG                                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig.TimeValidationConfigIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYINITIATORBLOCKDATAENDIDXOFTIMEVALIDATIONETHSLAVECONFIG          STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig.TimeValidationEthPdelayInitiatorBlockDataEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYINITIATORBLOCKDATASTARTIDXOFTIMEVALIDATIONETHSLAVECONFIG        STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig.TimeValidationEthPdelayInitiatorBlockDataStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHPDELAYINITIATORCALLBACKIDXOFTIMEVALIDATIONETHSLAVECONFIG              STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig.TimeValidationEthPdelayInitiatorCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHSLAVEBLOCKDATAENDIDXOFTIMEVALIDATIONETHSLAVECONFIG                    STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig.TimeValidationEthSlaveBlockDataEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHSLAVEBLOCKDATASTARTIDXOFTIMEVALIDATIONETHSLAVECONFIG                  STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig.TimeValidationEthSlaveBlockDataStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHSLAVECALLBACKIDXOFTIMEVALIDATIONETHSLAVECONFIG                        STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveConfig.TimeValidationEthSlaveCallbackIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEVALIDATIONETHSLAVESTATE                                                            STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_CURRENTBLOCKIDXOFTIMEVALIDATIONETHSLAVESTATE                                           STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveState.CurrentBlockIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_RECORDEDBLOCKSCOUNTOFTIMEVALIDATIONETHSLAVESTATE                                       STD_OFF  /**< Deactivateable: 'StbM_TimeValidationEthSlaveState.RecordedBlocksCount' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_TIMEOUTCONFIG                                                                          STD_ON
#define STBM_SYNCLOSSTIMEOUTCOUNTEROFTIMEOUTCONFIG                                                  STD_ON
#define STBM_TIMEBASECONFIGIDXOFTIMEOUTCONFIG                                                       STD_ON
#define STBM_TIMEOUTSTATE                                                                           STD_ON
#define STBM_SYNCLOSSTIMEOUTCOUNTEROFTIMEOUTSTATE                                                   STD_ON
#define STBM_TRIGGEREDCUSTOMERCONFIG                                                                STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define STBM_SCHEDULETABLECOUNTERTICKSPERUSOFTRIGGEREDCUSTOMERCONFIG                                STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerConfig.ScheduleTableCounterTicksPerUs' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_SCHEDULETABLEDURATIONOFTRIGGEREDCUSTOMERCONFIG                                         STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerConfig.ScheduleTableDuration' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_SCHEDULETABLEIDOFTRIGGEREDCUSTOMERCONFIG                                               STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerConfig.ScheduleTableID' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEBASECONFIGIDXOFTRIGGEREDCUSTOMERCONFIG                                             STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerConfig.TimeBaseConfigIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TIMEBASEIDOFTRIGGEREDCUSTOMERCONFIG                                                    STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerConfig.TimeBaseID' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TRIGGEREDCUSTOMERPERIODOFTRIGGEREDCUSTOMERCONFIG                                       STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerConfig.TriggeredCustomerPeriod' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define STBM_TRIGGEREDCUSTOMERSTATE                                                                 STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_PERIODCOUNTEROFTRIGGEREDCUSTOMERSTATE                                                  STD_OFF  /**< Deactivateable: 'StbM_TriggeredCustomerState.PeriodCounter' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define STBM_USERDATASTATE                                                                          STD_ON
#define STBM_USERDATAOFUSERDATASTATE                                                                STD_ON
#define STBM_VIRTUALLOCALTIMESTATE                                                                  STD_ON
#define STBM_VIRTUALLOCALTIMEOFVIRTUALLOCALTIMESTATE                                                STD_ON
#define STBM_VIRTUALLOCALTIMERXOFVIRTUALLOCALTIMESTATE                                              STD_ON
#define STBM_VIRTUALLOCALTIMESYNCOFVIRTUALLOCALTIMESTATE                                            STD_ON
#define STBM_PCCONFIG                                                                               STD_ON
#define STBM_ETHCLOCKCONFIGOFPCCONFIG                                                               STD_ON
#define STBM_FINALMAGICNUMBEROFPCCONFIG                                                             STD_OFF  /**< Deactivateable: 'StbM_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define STBM_INITDATAHASHCODEOFPCCONFIG                                                             STD_OFF  /**< Deactivateable: 'StbM_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define STBM_INITIALIZEDOFPCCONFIG                                                                  STD_ON
#define STBM_LOCALCLOCKCONFIGOFPCCONFIG                                                             STD_ON
#define STBM_LOCALCLOCKSTATEOFPCCONFIG                                                              STD_ON
#define STBM_LOCALTIMECONFIGOFPCCONFIG                                                              STD_ON
#define STBM_LOCALTIMESTATEOFPCCONFIG                                                               STD_ON
#define STBM_RATEMEASUREMENTSOFPCCONFIG                                                             STD_ON
#define STBM_SIZEOFETHCLOCKCONFIGOFPCCONFIG                                                         STD_ON
#define STBM_SIZEOFLOCALCLOCKCONFIGOFPCCONFIG                                                       STD_ON
#define STBM_SIZEOFLOCALCLOCKSTATEOFPCCONFIG                                                        STD_ON
#define STBM_SIZEOFLOCALTIMECONFIGOFPCCONFIG                                                        STD_ON
#define STBM_SIZEOFLOCALTIMESTATEOFPCCONFIG                                                         STD_ON
#define STBM_SIZEOFRATEMEASUREMENTSOFPCCONFIG                                                       STD_ON
#define STBM_SIZEOFSTATUSOFPCCONFIG                                                                 STD_ON
#define STBM_SIZEOFTIMEBASECONFIGOFPCCONFIG                                                         STD_ON
#define STBM_SIZEOFTIMEBASESTATEOFPCCONFIG                                                          STD_ON
#define STBM_SIZEOFTIMECORRECTIONSLAVECONFIGOFPCCONFIG                                              STD_ON
#define STBM_SIZEOFTIMECORRECTIONSLAVESTATEOFPCCONFIG                                               STD_ON
#define STBM_SIZEOFTIMELEAPCONFIGOFPCCONFIG                                                         STD_ON
#define STBM_SIZEOFTIMELEAPSTATEOFPCCONFIG                                                          STD_ON
#define STBM_SIZEOFTIMEOUTCONFIGOFPCCONFIG                                                          STD_ON
#define STBM_SIZEOFTIMEOUTSTATEOFPCCONFIG                                                           STD_ON
#define STBM_SIZEOFUSERDATASTATEOFPCCONFIG                                                          STD_ON
#define STBM_SIZEOFVIRTUALLOCALTIMESTATEOFPCCONFIG                                                  STD_ON
#define STBM_STATUSOFPCCONFIG                                                                       STD_ON
#define STBM_TIMEBASECONFIGOFPCCONFIG                                                               STD_ON
#define STBM_TIMEBASESTATEOFPCCONFIG                                                                STD_ON
#define STBM_TIMECORRECTIONSLAVECONFIGOFPCCONFIG                                                    STD_ON
#define STBM_TIMECORRECTIONSLAVESTATEOFPCCONFIG                                                     STD_ON
#define STBM_TIMELEAPCONFIGOFPCCONFIG                                                               STD_ON
#define STBM_TIMELEAPSTATEOFPCCONFIG                                                                STD_ON
#define STBM_TIMEOUTCONFIGOFPCCONFIG                                                                STD_ON
#define STBM_TIMEOUTSTATEOFPCCONFIG                                                                 STD_ON
#define STBM_USERDATASTATEOFPCCONFIG                                                                STD_ON
#define STBM_VIRTUALLOCALTIMESTATEOFPCCONFIG                                                        STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCMinNumericValueDefines  StbM Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define STBM_MIN_FRACTIONALPARTOFLOCALCLOCKSTATE                                                    0u
#define STBM_MIN_LOCALTIMEUPDATEDOFLOCALTIMESTATE                                                   0u
#define STBM_MIN_TIMELEAPOFLOCALTIMESTATE                                                           -2147483648
#define STBM_MIN_UPDATECOUNTEROFTIMEBASESTATE                                                       0u
#define STBM_MIN_CURRENTRATEMEASUREMENTINDEXOFTIMECORRECTIONSLAVESTATE                              0u
#define STBM_MIN_CLEARCOUNTOFTIMELEAPSTATE                                                          0u
#define STBM_MIN_SYNCLOSSTIMEOUTCOUNTEROFTIMEOUTSTATE                                               0u
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCMaxNumericValueDefines  StbM Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define STBM_MAX_FRACTIONALPARTOFLOCALCLOCKSTATE                                                    18446744073709551615u
#define STBM_MAX_LOCALTIMEUPDATEDOFLOCALTIMESTATE                                                   255u
#define STBM_MAX_TIMELEAPOFLOCALTIMESTATE                                                           2147483647
#define STBM_MAX_UPDATECOUNTEROFTIMEBASESTATE                                                       255u
#define STBM_MAX_CURRENTRATEMEASUREMENTINDEXOFTIMECORRECTIONSLAVESTATE                              4294967295u
#define STBM_MAX_CLEARCOUNTOFTIMELEAPSTATE                                                          65535u
#define STBM_MAX_SYNCLOSSTIMEOUTCOUNTEROFTIMEOUTSTATE                                               4294967295u
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCNoReferenceDefines  StbM No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define STBM_NO_ETHCLOCKCONFIGIDXOFLOCALCLOCKCONFIG                                                 255u
#define STBM_NO_LOCALCLOCKCONFIGIDXOFLOCALTIMECONFIG                                                255u
#define STBM_NO_LOCALTIMECONFIGIDXOFTIMEBASECONFIG                                                  255u
#define STBM_NO_TIMEBASEIDOFTIMEBASECONFIG                                                          255u
#define STBM_NO_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG                                        255u
#define STBM_NO_TIMELEAPCONFIGIDXOFTIMEBASECONFIG                                                   255u
#define STBM_NO_TIMEOUTCONFIGIDXOFTIMEBASECONFIG                                                    255u
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCEnumExistsDefines  StbM Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define STBM_EXISTS_NONE_LOCALCLOCK_CLOCKTYPEOFLOCALCLOCKCONFIG                                     STD_OFF
#define STBM_EXISTS_OS_LOCALCLOCK_CLOCKTYPEOFLOCALCLOCKCONFIG                                       STD_OFF
#define STBM_EXISTS_GPT_LOCALCLOCK_CLOCKTYPEOFLOCALCLOCKCONFIG                                      STD_OFF
#define STBM_EXISTS_ETH_LOCALCLOCK_CLOCKTYPEOFLOCALCLOCKCONFIG                                      STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCEnumDefines  StbM Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define STBM_ETH_LOCALCLOCK_CLOCKTYPEOFLOCALCLOCKCONFIG                                             0x03u
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCIsReducedToDefineDefines  StbM Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define STBM_ISDEF_ETHIFCTRLIDXOFETHCLOCKCONFIG                                                     STD_OFF
#define STBM_ISDEF_CLOCKTYPEOFLOCALCLOCKCONFIG                                                      STD_OFF
#define STBM_ISDEF_DENOMINATOROFFACTORCLOCKTICKSTOLOCALTIMEOFLOCALCLOCKCONFIG                       STD_OFF
#define STBM_ISDEF_ETHCLOCKCONFIGIDXOFLOCALCLOCKCONFIG                                              STD_OFF
#define STBM_ISDEF_ETHCLOCKCONFIGUSEDOFLOCALCLOCKCONFIG                                             STD_OFF
#define STBM_ISDEF_HWFREQUENCYOFLOCALCLOCKCONFIG                                                    STD_OFF
#define STBM_ISDEF_HWPRESCALEROFLOCALCLOCKCONFIG                                                    STD_OFF
#define STBM_ISDEF_NUMERATOROFFACTORCLOCKTICKSTOLOCALTIMEOFLOCALCLOCKCONFIG                         STD_OFF
#define STBM_ISDEF_LOCALCLOCKCONFIGIDXOFLOCALTIMECONFIG                                             STD_OFF
#define STBM_ISDEF_LOCALCLOCKCONFIGUSEDOFLOCALTIMECONFIG                                            STD_OFF
#define STBM_ISDEF_TIMEBASECONFIGIDXOFLOCALTIMECONFIG                                               STD_OFF
#define STBM_ISDEF_GLOBALTIMEMASTEROFTIMEBASECONFIG                                                 STD_OFF
#define STBM_ISDEF_LOCALTIMECONFIGIDXOFTIMEBASECONFIG                                               STD_OFF
#define STBM_ISDEF_LOCALTIMECONFIGUSEDOFTIMEBASECONFIG                                              STD_OFF
#define STBM_ISDEF_STATUSIDXOFTIMEBASECONFIG                                                        STD_OFF
#define STBM_ISDEF_SYNCHRONIZEDTIMEBASEOFTIMEBASECONFIG                                             STD_OFF
#define STBM_ISDEF_TIMEBASEIDOFTIMEBASECONFIG                                                       STD_OFF
#define STBM_ISDEF_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG                                     STD_OFF
#define STBM_ISDEF_TIMECORRECTIONSLAVECONFIGUSEDOFTIMEBASECONFIG                                    STD_OFF
#define STBM_ISDEF_TIMELEAPCONFIGIDXOFTIMEBASECONFIG                                                STD_OFF
#define STBM_ISDEF_TIMELEAPCONFIGUSEDOFTIMEBASECONFIG                                               STD_OFF
#define STBM_ISDEF_TIMESLAVEOFTIMEBASECONFIG                                                        STD_OFF
#define STBM_ISDEF_TIMEOUTCONFIGIDXOFTIMEBASECONFIG                                                 STD_OFF
#define STBM_ISDEF_TIMEOUTCONFIGUSEDOFTIMEBASECONFIG                                                STD_OFF
#define STBM_ISDEF_USERDATASTATEIDXOFTIMEBASECONFIG                                                 STD_OFF
#define STBM_ISDEF_NUMBEROFSIMULTANEOUSRATEMEASUREMENTSOFTIMECORRECTIONSLAVECONFIG                  STD_OFF
#define STBM_ISDEF_OFFSETCORRECTIONADAPTIONINTERVALOFTIMECORRECTIONSLAVECONFIG                      STD_OFF
#define STBM_ISDEF_OFFSETCORRECTIONJUMPTHRESHOLDOFTIMECORRECTIONSLAVECONFIG                         STD_OFF
#define STBM_ISDEF_RATECORRECTIONMEASUREMENTDURATIONNANOSECONDSOFTIMECORRECTIONSLAVECONFIG          STD_OFF
#define STBM_ISDEF_RATECORRECTIONMEASUREMENTDURATIONSECONDSOFTIMECORRECTIONSLAVECONFIG              STD_OFF
#define STBM_ISDEF_RATEMEASUREMENTSENDIDXOFTIMECORRECTIONSLAVECONFIG                                STD_OFF
#define STBM_ISDEF_RATEMEASUREMENTSSTARTIDXOFTIMECORRECTIONSLAVECONFIG                              STD_OFF
#define STBM_ISDEF_SINGLERATECORRECTIONMEASUREMENTDURATIONNANOSECONDSOFTIMECORRECTIONSLAVECONFIG    STD_OFF
#define STBM_ISDEF_SINGLERATECORRECTIONMEASUREMENTDURATIONSECONDSOFTIMECORRECTIONSLAVECONFIG        STD_OFF
#define STBM_ISDEF_CLEARCOUNTOFTIMELEAPCONFIG                                                       STD_OFF
#define STBM_ISDEF_FUTURETHRESHOLDOFTIMELEAPCONFIG                                                  STD_OFF
#define STBM_ISDEF_PASTTHRESHOLDOFTIMELEAPCONFIG                                                    STD_OFF
#define STBM_ISDEF_SYNCLOSSTIMEOUTCOUNTEROFTIMEOUTCONFIG                                            STD_OFF
#define STBM_ISDEF_TIMEBASECONFIGIDXOFTIMEOUTCONFIG                                                 STD_OFF
#define STBM_ISDEF_ETHCLOCKCONFIGOFPCCONFIG                                                         STD_ON
#define STBM_ISDEF_INITIALIZEDOFPCCONFIG                                                            STD_ON
#define STBM_ISDEF_LOCALCLOCKCONFIGOFPCCONFIG                                                       STD_ON
#define STBM_ISDEF_LOCALCLOCKSTATEOFPCCONFIG                                                        STD_ON
#define STBM_ISDEF_LOCALTIMECONFIGOFPCCONFIG                                                        STD_ON
#define STBM_ISDEF_LOCALTIMESTATEOFPCCONFIG                                                         STD_ON
#define STBM_ISDEF_RATEMEASUREMENTSOFPCCONFIG                                                       STD_ON
#define STBM_ISDEF_STATUSOFPCCONFIG                                                                 STD_ON
#define STBM_ISDEF_TIMEBASECONFIGOFPCCONFIG                                                         STD_ON
#define STBM_ISDEF_TIMEBASESTATEOFPCCONFIG                                                          STD_ON
#define STBM_ISDEF_TIMECORRECTIONSLAVECONFIGOFPCCONFIG                                              STD_ON
#define STBM_ISDEF_TIMECORRECTIONSLAVESTATEOFPCCONFIG                                               STD_ON
#define STBM_ISDEF_TIMELEAPCONFIGOFPCCONFIG                                                         STD_ON
#define STBM_ISDEF_TIMELEAPSTATEOFPCCONFIG                                                          STD_ON
#define STBM_ISDEF_TIMEOUTCONFIGOFPCCONFIG                                                          STD_ON
#define STBM_ISDEF_TIMEOUTSTATEOFPCCONFIG                                                           STD_ON
#define STBM_ISDEF_USERDATASTATEOFPCCONFIG                                                          STD_ON
#define STBM_ISDEF_VIRTUALLOCALTIMESTATEOFPCCONFIG                                                  STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCEqualsAlwaysToDefines  StbM Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define STBM_EQ2_ETHIFCTRLIDXOFETHCLOCKCONFIG                                                       
#define STBM_EQ2_CLOCKTYPEOFLOCALCLOCKCONFIG                                                        
#define STBM_EQ2_DENOMINATOROFFACTORCLOCKTICKSTOLOCALTIMEOFLOCALCLOCKCONFIG                         
#define STBM_EQ2_ETHCLOCKCONFIGIDXOFLOCALCLOCKCONFIG                                                
#define STBM_EQ2_ETHCLOCKCONFIGUSEDOFLOCALCLOCKCONFIG                                               
#define STBM_EQ2_HWFREQUENCYOFLOCALCLOCKCONFIG                                                      
#define STBM_EQ2_HWPRESCALEROFLOCALCLOCKCONFIG                                                      
#define STBM_EQ2_NUMERATOROFFACTORCLOCKTICKSTOLOCALTIMEOFLOCALCLOCKCONFIG                           
#define STBM_EQ2_LOCALCLOCKCONFIGIDXOFLOCALTIMECONFIG                                               
#define STBM_EQ2_LOCALCLOCKCONFIGUSEDOFLOCALTIMECONFIG                                              
#define STBM_EQ2_TIMEBASECONFIGIDXOFLOCALTIMECONFIG                                                 
#define STBM_EQ2_GLOBALTIMEMASTEROFTIMEBASECONFIG                                                   
#define STBM_EQ2_LOCALTIMECONFIGIDXOFTIMEBASECONFIG                                                 
#define STBM_EQ2_LOCALTIMECONFIGUSEDOFTIMEBASECONFIG                                                
#define STBM_EQ2_STATUSIDXOFTIMEBASECONFIG                                                          
#define STBM_EQ2_SYNCHRONIZEDTIMEBASEOFTIMEBASECONFIG                                               
#define STBM_EQ2_TIMEBASEIDOFTIMEBASECONFIG                                                         
#define STBM_EQ2_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG                                       
#define STBM_EQ2_TIMECORRECTIONSLAVECONFIGUSEDOFTIMEBASECONFIG                                      
#define STBM_EQ2_TIMELEAPCONFIGIDXOFTIMEBASECONFIG                                                  
#define STBM_EQ2_TIMELEAPCONFIGUSEDOFTIMEBASECONFIG                                                 
#define STBM_EQ2_TIMESLAVEOFTIMEBASECONFIG                                                          
#define STBM_EQ2_TIMEOUTCONFIGIDXOFTIMEBASECONFIG                                                   
#define STBM_EQ2_TIMEOUTCONFIGUSEDOFTIMEBASECONFIG                                                  
#define STBM_EQ2_USERDATASTATEIDXOFTIMEBASECONFIG                                                   
#define STBM_EQ2_NUMBEROFSIMULTANEOUSRATEMEASUREMENTSOFTIMECORRECTIONSLAVECONFIG                    
#define STBM_EQ2_OFFSETCORRECTIONADAPTIONINTERVALOFTIMECORRECTIONSLAVECONFIG                        
#define STBM_EQ2_OFFSETCORRECTIONJUMPTHRESHOLDOFTIMECORRECTIONSLAVECONFIG                           
#define STBM_EQ2_RATECORRECTIONMEASUREMENTDURATIONNANOSECONDSOFTIMECORRECTIONSLAVECONFIG            
#define STBM_EQ2_RATECORRECTIONMEASUREMENTDURATIONSECONDSOFTIMECORRECTIONSLAVECONFIG                
#define STBM_EQ2_RATEMEASUREMENTSENDIDXOFTIMECORRECTIONSLAVECONFIG                                  
#define STBM_EQ2_RATEMEASUREMENTSSTARTIDXOFTIMECORRECTIONSLAVECONFIG                                
#define STBM_EQ2_SINGLERATECORRECTIONMEASUREMENTDURATIONNANOSECONDSOFTIMECORRECTIONSLAVECONFIG      
#define STBM_EQ2_SINGLERATECORRECTIONMEASUREMENTDURATIONSECONDSOFTIMECORRECTIONSLAVECONFIG          
#define STBM_EQ2_CLEARCOUNTOFTIMELEAPCONFIG                                                         
#define STBM_EQ2_FUTURETHRESHOLDOFTIMELEAPCONFIG                                                    
#define STBM_EQ2_PASTTHRESHOLDOFTIMELEAPCONFIG                                                      
#define STBM_EQ2_SYNCLOSSTIMEOUTCOUNTEROFTIMEOUTCONFIG                                              
#define STBM_EQ2_TIMEBASECONFIGIDXOFTIMEOUTCONFIG                                                   
#define STBM_EQ2_ETHCLOCKCONFIGOFPCCONFIG                                                           StbM_EthClockConfig
#define STBM_EQ2_INITIALIZEDOFPCCONFIG                                                              (&(StbM_Initialized))
#define STBM_EQ2_LOCALCLOCKCONFIGOFPCCONFIG                                                         StbM_LocalClockConfig
#define STBM_EQ2_LOCALCLOCKSTATEOFPCCONFIG                                                          StbM_LocalClockState.raw
#define STBM_EQ2_LOCALTIMECONFIGOFPCCONFIG                                                          StbM_LocalTimeConfig
#define STBM_EQ2_LOCALTIMESTATEOFPCCONFIG                                                           StbM_LocalTimeState.raw
#define STBM_EQ2_RATEMEASUREMENTSOFPCCONFIG                                                         StbM_RateMeasurements.raw
#define STBM_EQ2_STATUSOFPCCONFIG                                                                   StbM_Status.raw
#define STBM_EQ2_TIMEBASECONFIGOFPCCONFIG                                                           StbM_TimeBaseConfig
#define STBM_EQ2_TIMEBASESTATEOFPCCONFIG                                                            StbM_TimeBaseState.raw
#define STBM_EQ2_TIMECORRECTIONSLAVECONFIGOFPCCONFIG                                                StbM_TimeCorrectionSlaveConfig
#define STBM_EQ2_TIMECORRECTIONSLAVESTATEOFPCCONFIG                                                 StbM_TimeCorrectionSlaveState.raw
#define STBM_EQ2_TIMELEAPCONFIGOFPCCONFIG                                                           StbM_TimeLeapConfig
#define STBM_EQ2_TIMELEAPSTATEOFPCCONFIG                                                            StbM_TimeLeapState.raw
#define STBM_EQ2_TIMEOUTCONFIGOFPCCONFIG                                                            StbM_TimeoutConfig
#define STBM_EQ2_TIMEOUTSTATEOFPCCONFIG                                                             StbM_TimeoutState.raw
#define STBM_EQ2_USERDATASTATEOFPCCONFIG                                                            StbM_UserDataState.raw
#define STBM_EQ2_VIRTUALLOCALTIMESTATEOFPCCONFIG                                                    StbM_VirtualLocalTimeState.raw
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCSymbolicInitializationPointers  StbM Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define StbM_Config_Ptr                                                                             NULL_PTR  /**< symbolic identifier which shall be used to initialize 'StbM' */
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCInitializationSymbols  StbM Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define StbM_Config                                                                                 NULL_PTR  /**< symbolic identifier which could be used to initialize 'StbM */
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCGeneral  StbM General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define STBM_CHECK_INIT_POINTER                                                                     STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define STBM_FINAL_MAGIC_NUMBER                                                                     0xA01Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of StbM */
#define STBM_INDIVIDUAL_POSTBUILD                                                                   STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'StbM' is not configured to be postbuild capable. */
#define STBM_INIT_DATA                                                                              STBM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define STBM_INIT_DATA_HASH_CODE                                                                    132314632  /**< the precompile constant to validate the initialization structure at initialization time of StbM with a hashcode. The seed value is '0xA01Eu' */
#define STBM_USE_ECUM_BSW_ERROR_HOOK                                                                STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define STBM_USE_INIT_POINTER                                                                       STD_OFF  /**< STD_ON if the init pointer StbM shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  StbMLTDataSwitches  StbM Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define STBM_LTCONFIG                                                                               STD_OFF  /**< Deactivateable: 'StbM_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  StbMPBDataSwitches  StbM Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define STBM_PBCONFIG                                                                               STD_OFF  /**< Deactivateable: 'StbM_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define STBM_LTCONFIGIDXOFPBCONFIG                                                                  STD_OFF  /**< Deactivateable: 'StbM_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define STBM_PCCONFIGIDXOFPBCONFIG                                                                  STD_OFF  /**< Deactivateable: 'StbM_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
/** 
  \}
*/ 



/**********************************************************************************************************************
 *  UNIT CONFIG MACROS
 *********************************************************************************************************************/
# define STBM_CONFIG_LOCAL_TIME                         (STBM_LOCALTIMECONFIGIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_LOCAL_CLOCK                        (STBM_LOCALCLOCKCONFIGIDXOFLOCALTIMECONFIG)
# define STBM_CONFIG_OS_CLOCK                           (STBM_OSCLOCKCONFIGIDXOFLOCALCLOCKCONFIG)
# define STBM_CONFIG_GPT_CLOCK                          (STBM_GPTCLOCKCONFIGIDXOFLOCALCLOCKCONFIG)
# define STBM_CONFIG_ETH_CLOCK                          (STBM_ETHCLOCKCONFIGIDXOFLOCALCLOCKCONFIG)
# define STBM_CONFIG_STATUS                             (STBM_STATUSIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_STATUS_NOTIFICATION                (STBM_STATUSNOTIFICATIONCUSTOMERCALLBACK)              /* Callbacks are available only for pre-compile. Therefore, the feature has to be configured in order to be STD_ON. Important for post build use-case. */
# define STBM_CONFIG_MASTER_RATE_CORRECTION             (STBM_TIMECORRECTIONMASTERCONFIGIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_SLAVE_RATE_CORRECTION              (STBM_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_TIME_LEAP                          (STBM_TIMELEAPCONFIGIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_TIME_NOTIFICATION                  (STBM_TIMENOTIFICATIONCALLBACK)                        /* Callbacks are available only for pre-compile. Therefore, the feature has to be configured in order to be STD_ON. Important for post build use-case. */
# define STBM_CONFIG_TIMEOUT                            (STBM_TIMEOUTCONFIGIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_TRIGGERED_CUSTOMER                 (STBM_TRIGGEREDCUSTOMERCONFIGIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_USER_DATA                          (STBM_USERDATASTATEIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_TIME_RECORDING                     (STBM_TIMERECORDINGSYNCCALLBACK)                       /* Callbacks are available only for pre-compile. Therefore, the feature has to be configured in order to be STD_ON. Important for post build use-case. */
# define STBM_CONFIG_TIME_RECORDING_SYNC                (STBM_TIMERECORDINGSYNCCALLBACK)                       /* Callbacks are available only for pre-compile. Therefore, the feature has to be configured in order to be STD_ON. Important for post build use-case. */
# define STBM_CONFIG_TIME_RECORDING_OFFSET              (STBM_TIMERECORDINGOFFSETCALLBACK)
# define STBM_CONFIG_TIME_VALIDATION                    (STBM_TIMEVALIDATIONCONFIG)
# define STBM_CONFIG_TIME_VALIDATION_ETH_MASTER         (STBM_TIMEVALIDATIONETHMASTERCALLBACK)                 /* Callbacks are available only for pre-compile. Therefore, the feature has to be configured in order to be STD_ON. Important for post build use-case. */
# define STBM_CONFIG_TIME_VALIDATION_ETH_SLAVE          (STBM_TIMEVALIDATIONETHSLAVECALLBACK)                  /* Callbacks are available only for pre-compile. Therefore, the feature has to be configured in order to be STD_ON. Important for post build use-case. */
# define STBM_CONFIG_OFFSET_TIMEBASE                    (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG)
# define STBM_CONFIG_GLOBAL_TIME_MASTER                 (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG)
# define STBM_CONFIG_TIME_SLAVE                         (STBM_TIMESLAVEOFTIMEBASECONFIG)
# define STBM_CONFIG_GATEWAY                            (STBM_TIMEGATEWAYOFTIMEBASECONFIG)
# define STBM_CONFIG_RESERVED_TIMEBASE                  (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG)
# define STBM_CONFIG_PURE_LOCAL_TIMEBASE                (STBM_PURELOCALTIMEBASEOFTIMEBASECONFIG)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  StbMPCGetConstantDuplicatedRootDataMacros  StbM Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define StbM_GetEthClockConfigOfPCConfig()                                                          StbM_EthClockConfig  /**< the pointer to StbM_EthClockConfig */
#define StbM_GetInitializedOfPCConfig()                                                             (&(StbM_Initialized))  /**< the pointer to StbM_Initialized */
#define StbM_GetLocalClockConfigOfPCConfig()                                                        StbM_LocalClockConfig  /**< the pointer to StbM_LocalClockConfig */
#define StbM_GetLocalClockStateOfPCConfig()                                                         StbM_LocalClockState.raw  /**< the pointer to StbM_LocalClockState */
#define StbM_GetLocalTimeConfigOfPCConfig()                                                         StbM_LocalTimeConfig  /**< the pointer to StbM_LocalTimeConfig */
#define StbM_GetLocalTimeStateOfPCConfig()                                                          StbM_LocalTimeState.raw  /**< the pointer to StbM_LocalTimeState */
#define StbM_GetRateMeasurementsOfPCConfig()                                                        StbM_RateMeasurements.raw  /**< the pointer to StbM_RateMeasurements */
#define StbM_GetSizeOfEthClockConfigOfPCConfig()                                                    2u  /**< the number of accomplishable value elements in StbM_EthClockConfig */
#define StbM_GetSizeOfLocalClockConfigOfPCConfig()                                                  2u  /**< the number of accomplishable value elements in StbM_LocalClockConfig */
#define StbM_GetSizeOfLocalTimeConfigOfPCConfig()                                                   2u  /**< the number of accomplishable value elements in StbM_LocalTimeConfig */
#define StbM_GetSizeOfRateMeasurementsOfPCConfig()                                                  1u  /**< the number of accomplishable value elements in StbM_RateMeasurements */
#define StbM_GetSizeOfStatusOfPCConfig()                                                            2u  /**< the number of accomplishable value elements in StbM_Status */
#define StbM_GetSizeOfTimeBaseConfigOfPCConfig()                                                    2u  /**< the number of accomplishable value elements in StbM_TimeBaseConfig */
#define StbM_GetSizeOfTimeCorrectionSlaveConfigOfPCConfig()                                         1u  /**< the number of accomplishable value elements in StbM_TimeCorrectionSlaveConfig */
#define StbM_GetSizeOfTimeLeapConfigOfPCConfig()                                                    1u  /**< the number of accomplishable value elements in StbM_TimeLeapConfig */
#define StbM_GetSizeOfTimeoutConfigOfPCConfig()                                                     1u  /**< the number of accomplishable value elements in StbM_TimeoutConfig */
#define StbM_GetSizeOfUserDataStateOfPCConfig()                                                     2u  /**< the number of accomplishable value elements in StbM_UserDataState */
#define StbM_GetStatusOfPCConfig()                                                                  StbM_Status.raw  /**< the pointer to StbM_Status */
#define StbM_GetTimeBaseConfigOfPCConfig()                                                          StbM_TimeBaseConfig  /**< the pointer to StbM_TimeBaseConfig */
#define StbM_GetTimeBaseStateOfPCConfig()                                                           StbM_TimeBaseState.raw  /**< the pointer to StbM_TimeBaseState */
#define StbM_GetTimeCorrectionSlaveConfigOfPCConfig()                                               StbM_TimeCorrectionSlaveConfig  /**< the pointer to StbM_TimeCorrectionSlaveConfig */
#define StbM_GetTimeCorrectionSlaveStateOfPCConfig()                                                StbM_TimeCorrectionSlaveState.raw  /**< the pointer to StbM_TimeCorrectionSlaveState */
#define StbM_GetTimeLeapConfigOfPCConfig()                                                          StbM_TimeLeapConfig  /**< the pointer to StbM_TimeLeapConfig */
#define StbM_GetTimeLeapStateOfPCConfig()                                                           StbM_TimeLeapState.raw  /**< the pointer to StbM_TimeLeapState */
#define StbM_GetTimeoutConfigOfPCConfig()                                                           StbM_TimeoutConfig  /**< the pointer to StbM_TimeoutConfig */
#define StbM_GetTimeoutStateOfPCConfig()                                                            StbM_TimeoutState.raw  /**< the pointer to StbM_TimeoutState */
#define StbM_GetUserDataStateOfPCConfig()                                                           StbM_UserDataState.raw  /**< the pointer to StbM_UserDataState */
#define StbM_GetVirtualLocalTimeStateOfPCConfig()                                                   StbM_VirtualLocalTimeState.raw  /**< the pointer to StbM_VirtualLocalTimeState */
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCGetDuplicatedRootDataMacros  StbM Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define StbM_GetSizeOfLocalClockStateOfPCConfig()                                                   StbM_GetSizeOfLocalClockConfigOfPCConfig()  /**< the number of accomplishable value elements in StbM_LocalClockState */
#define StbM_GetSizeOfLocalTimeStateOfPCConfig()                                                    StbM_GetSizeOfLocalTimeConfigOfPCConfig()  /**< the number of accomplishable value elements in StbM_LocalTimeState */
#define StbM_GetSizeOfTimeBaseStateOfPCConfig()                                                     StbM_GetSizeOfTimeBaseConfigOfPCConfig()  /**< the number of accomplishable value elements in StbM_TimeBaseState */
#define StbM_GetSizeOfTimeCorrectionSlaveStateOfPCConfig()                                          StbM_GetSizeOfTimeCorrectionSlaveConfigOfPCConfig()  /**< the number of accomplishable value elements in StbM_TimeCorrectionSlaveState */
#define StbM_GetSizeOfTimeLeapStateOfPCConfig()                                                     StbM_GetSizeOfTimeLeapConfigOfPCConfig()  /**< the number of accomplishable value elements in StbM_TimeLeapState */
#define StbM_GetSizeOfTimeoutStateOfPCConfig()                                                      StbM_GetSizeOfTimeoutConfigOfPCConfig()  /**< the number of accomplishable value elements in StbM_TimeoutState */
#define StbM_GetSizeOfVirtualLocalTimeStateOfPCConfig()                                             StbM_GetSizeOfLocalTimeConfigOfPCConfig()  /**< the number of accomplishable value elements in StbM_VirtualLocalTimeState */
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCGetDataMacros  StbM Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define StbM_GetEthIfCtrlIdxOfEthClockConfig(Index)                                                 (StbM_GetEthClockConfigOfPCConfig()[(Index)].EthIfCtrlIdxOfEthClockConfig)
#define StbM_IsInitialized()                                                                        (((*(StbM_GetInitializedOfPCConfig()))) != FALSE)
#define StbM_GetClockTypeOfLocalClockConfig(Index)                                                  (StbM_GetLocalClockConfigOfPCConfig()[(Index)].ClockTypeOfLocalClockConfig)
#define StbM_GetDenominatorOfFactorClockTicksToLocalTimeOfLocalClockConfig(Index)                   (StbM_GetLocalClockConfigOfPCConfig()[(Index)].DenominatorOfFactorClockTicksToLocalTimeOfLocalClockConfig)
#define StbM_GetEthClockConfigIdxOfLocalClockConfig(Index)                                          (StbM_GetLocalClockConfigOfPCConfig()[(Index)].EthClockConfigIdxOfLocalClockConfig)
#define StbM_GetHwFrequencyOfLocalClockConfig(Index)                                                (StbM_GetLocalClockConfigOfPCConfig()[(Index)].HwFrequencyOfLocalClockConfig)
#define StbM_GetHwPrescalerOfLocalClockConfig(Index)                                                (StbM_GetLocalClockConfigOfPCConfig()[(Index)].HwPrescalerOfLocalClockConfig)
#define StbM_GetNumeratorOfFactorClockTicksToLocalTimeOfLocalClockConfig(Index)                     (StbM_GetLocalClockConfigOfPCConfig()[(Index)].NumeratorOfFactorClockTicksToLocalTimeOfLocalClockConfig)
#define StbM_GetFractionalPartOfLocalClockState(Index)                                              (StbM_GetLocalClockStateOfPCConfig()[(Index)].FractionalPartOfLocalClockState)
#define StbM_GetLastReadTimeOfLocalClockState(Index)                                                (StbM_GetLocalClockStateOfPCConfig()[(Index)].LastReadTimeOfLocalClockState)
#define StbM_GetLocalClockConfigIdxOfLocalTimeConfig(Index)                                         (StbM_GetLocalTimeConfigOfPCConfig()[(Index)].LocalClockConfigIdxOfLocalTimeConfig)
#define StbM_GetTimeBaseConfigIdxOfLocalTimeConfig(Index)                                           (StbM_GetLocalTimeConfigOfPCConfig()[(Index)].TimeBaseConfigIdxOfLocalTimeConfig)
#define StbM_GetGlobalTimeRxOfLocalTimeState(Index)                                                 (StbM_GetLocalTimeStateOfPCConfig()[(Index)].GlobalTimeRxOfLocalTimeState)
#define StbM_GetGlobalTimeSyncOfLocalTimeState(Index)                                               (StbM_GetLocalTimeStateOfPCConfig()[(Index)].GlobalTimeSyncOfLocalTimeState)
#define StbM_GetLocalTimeOfLocalTimeState(Index)                                                    (StbM_GetLocalTimeStateOfPCConfig()[(Index)].LocalTimeOfLocalTimeState)
#define StbM_GetLocalTimeSyncOfLocalTimeState(Index)                                                (StbM_GetLocalTimeStateOfPCConfig()[(Index)].LocalTimeSyncOfLocalTimeState)
#define StbM_GetLocalTimeUpdatedOfLocalTimeState(Index)                                             (StbM_GetLocalTimeStateOfPCConfig()[(Index)].LocalTimeUpdatedOfLocalTimeState)
#define StbM_GetTimeLeapOfLocalTimeState(Index)                                                     (StbM_GetLocalTimeStateOfPCConfig()[(Index)].TimeLeapOfLocalTimeState)
#define StbM_IsTimeLeapValidOfLocalTimeState(Index)                                                 ((StbM_GetLocalTimeStateOfPCConfig()[(Index)].TimeLeapValidOfLocalTimeState) != FALSE)
#define StbM_GetStartGlobalTimeOfRateMeasurements(Index)                                            (StbM_GetRateMeasurementsOfPCConfig()[(Index)].StartGlobalTimeOfRateMeasurements)
#define StbM_GetStartStatusOfRateMeasurements(Index)                                                (StbM_GetRateMeasurementsOfPCConfig()[(Index)].StartStatusOfRateMeasurements)
#define StbM_GetStartVirtualLocalTimeOfRateMeasurements(Index)                                      (StbM_GetRateMeasurementsOfPCConfig()[(Index)].StartVirtualLocalTimeOfRateMeasurements)
#define StbM_GetStopGlobalTimeOfRateMeasurements(Index)                                             (StbM_GetRateMeasurementsOfPCConfig()[(Index)].StopGlobalTimeOfRateMeasurements)
#define StbM_GetStopStatusOfRateMeasurements(Index)                                                 (StbM_GetRateMeasurementsOfPCConfig()[(Index)].StopStatusOfRateMeasurements)
#define StbM_GetStopVirtualLocalTimeOfRateMeasurements(Index)                                       (StbM_GetRateMeasurementsOfPCConfig()[(Index)].StopVirtualLocalTimeOfRateMeasurements)
#define StbM_IsValidOfRateMeasurements(Index)                                                       ((StbM_GetRateMeasurementsOfPCConfig()[(Index)].ValidOfRateMeasurements) != FALSE)
#define StbM_GetGlobalTimeStatusOfStatus(Index)                                                     (StbM_GetStatusOfPCConfig()[(Index)].GlobalTimeStatusOfStatus)
#define StbM_GetLocalTimeStatusOfStatus(Index)                                                      (StbM_GetStatusOfPCConfig()[(Index)].LocalTimeStatusOfStatus)
#define StbM_IsGlobalTimeMasterOfTimeBaseConfig(Index)                                              ((StbM_GetTimeBaseConfigOfPCConfig()[(Index)].GlobalTimeMasterOfTimeBaseConfig) != FALSE)
#define StbM_GetLocalTimeConfigIdxOfTimeBaseConfig(Index)                                           (StbM_GetTimeBaseConfigOfPCConfig()[(Index)].LocalTimeConfigIdxOfTimeBaseConfig)
#define StbM_GetStatusIdxOfTimeBaseConfig(Index)                                                    (StbM_GetTimeBaseConfigOfPCConfig()[(Index)].StatusIdxOfTimeBaseConfig)
#define StbM_IsSynchronizedTimeBaseOfTimeBaseConfig(Index)                                          ((StbM_GetTimeBaseConfigOfPCConfig()[(Index)].SynchronizedTimeBaseOfTimeBaseConfig) != FALSE)
#define StbM_GetTimeBaseIdOfTimeBaseConfig(Index)                                                   (StbM_GetTimeBaseConfigOfPCConfig()[(Index)].TimeBaseIdOfTimeBaseConfig)
#define StbM_GetTimeCorrectionSlaveConfigIdxOfTimeBaseConfig(Index)                                 (StbM_GetTimeBaseConfigOfPCConfig()[(Index)].TimeCorrectionSlaveConfigIdxOfTimeBaseConfig)
#define StbM_GetTimeLeapConfigIdxOfTimeBaseConfig(Index)                                            (StbM_GetTimeBaseConfigOfPCConfig()[(Index)].TimeLeapConfigIdxOfTimeBaseConfig)
#define StbM_IsTimeSlaveOfTimeBaseConfig(Index)                                                     ((StbM_GetTimeBaseConfigOfPCConfig()[(Index)].TimeSlaveOfTimeBaseConfig) != FALSE)
#define StbM_GetTimeoutConfigIdxOfTimeBaseConfig(Index)                                             (StbM_GetTimeBaseConfigOfPCConfig()[(Index)].TimeoutConfigIdxOfTimeBaseConfig)
#define StbM_GetUserDataStateIdxOfTimeBaseConfig(Index)                                             (StbM_GetTimeBaseConfigOfPCConfig()[(Index)].UserDataStateIdxOfTimeBaseConfig)
#define StbM_GetUpdateCounterOfTimeBaseState(Index)                                                 (StbM_GetTimeBaseStateOfPCConfig()[(Index)].UpdateCounterOfTimeBaseState)
#define StbM_GetNumberOfSimultaneousRateMeasurementsOfTimeCorrectionSlaveConfig(Index)              (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].NumberOfSimultaneousRateMeasurementsOfTimeCorrectionSlaveConfig)
#define StbM_GetOffsetCorrectionAdaptionIntervalOfTimeCorrectionSlaveConfig(Index)                  (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].OffsetCorrectionAdaptionIntervalOfTimeCorrectionSlaveConfig)
#define StbM_GetOffsetCorrectionJumpThresholdOfTimeCorrectionSlaveConfig(Index)                     (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].OffsetCorrectionJumpThresholdOfTimeCorrectionSlaveConfig)
#define StbM_GetRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig(Index)      (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].RateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig)
#define StbM_GetRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig(Index)          (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].RateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig)
#define StbM_GetRateMeasurementsEndIdxOfTimeCorrectionSlaveConfig(Index)                            (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].RateMeasurementsEndIdxOfTimeCorrectionSlaveConfig)
#define StbM_GetRateMeasurementsStartIdxOfTimeCorrectionSlaveConfig(Index)                          (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].RateMeasurementsStartIdxOfTimeCorrectionSlaveConfig)
#define StbM_GetSingleRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig(Index) (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].SingleRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig)
#define StbM_GetSingleRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig(Index)    (StbM_GetTimeCorrectionSlaveConfigOfPCConfig()[(Index)].SingleRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig)
#define StbM_GetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index)                        (StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].CurrentRateMeasurementIndexOfTimeCorrectionSlaveState)
#define StbM_IsOffsetCorrectionRateValidOfTimeCorrectionSlaveState(Index)                           ((StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].OffsetCorrectionRateValidOfTimeCorrectionSlaveState) != FALSE)
#define StbM_GetOffsetRateCorrectionOfTimeCorrectionSlaveState(Index)                               (StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].OffsetRateCorrectionOfTimeCorrectionSlaveState)
#define StbM_GetRateCorrectionOfTimeCorrectionSlaveState(Index)                                     (StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].RateCorrectionOfTimeCorrectionSlaveState)
#define StbM_IsRateDeviationValidOfTimeCorrectionSlaveState(Index)                                  ((StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].RateDeviationValidOfTimeCorrectionSlaveState) != FALSE)
#define StbM_GetClearCountOfTimeLeapConfig(Index)                                                   (StbM_GetTimeLeapConfigOfPCConfig()[(Index)].ClearCountOfTimeLeapConfig)
#define StbM_GetFutureThresholdOfTimeLeapConfig(Index)                                              (StbM_GetTimeLeapConfigOfPCConfig()[(Index)].FutureThresholdOfTimeLeapConfig)
#define StbM_GetPastThresholdOfTimeLeapConfig(Index)                                                (StbM_GetTimeLeapConfigOfPCConfig()[(Index)].PastThresholdOfTimeLeapConfig)
#define StbM_GetClearCountOfTimeLeapState(Index)                                                    (StbM_GetTimeLeapStateOfPCConfig()[(Index)].ClearCountOfTimeLeapState)
#define StbM_GetSyncLossTimeoutCounterOfTimeoutConfig(Index)                                        (StbM_GetTimeoutConfigOfPCConfig()[(Index)].SyncLossTimeoutCounterOfTimeoutConfig)
#define StbM_GetTimeBaseConfigIdxOfTimeoutConfig(Index)                                             (StbM_GetTimeoutConfigOfPCConfig()[(Index)].TimeBaseConfigIdxOfTimeoutConfig)
#define StbM_GetSyncLossTimeoutCounterOfTimeoutState(Index)                                         (StbM_GetTimeoutStateOfPCConfig()[(Index)].SyncLossTimeoutCounterOfTimeoutState)
#define StbM_GetUserDataOfUserDataState(Index)                                                      (StbM_GetUserDataStateOfPCConfig()[(Index)].UserDataOfUserDataState)
#define StbM_GetVirtualLocalTimeOfVirtualLocalTimeState(Index)                                      (StbM_GetVirtualLocalTimeStateOfPCConfig()[(Index)].VirtualLocalTimeOfVirtualLocalTimeState)
#define StbM_GetVirtualLocalTimeRxOfVirtualLocalTimeState(Index)                                    (StbM_GetVirtualLocalTimeStateOfPCConfig()[(Index)].VirtualLocalTimeRxOfVirtualLocalTimeState)
#define StbM_GetVirtualLocalTimeSyncOfVirtualLocalTimeState(Index)                                  (StbM_GetVirtualLocalTimeStateOfPCConfig()[(Index)].VirtualLocalTimeSyncOfVirtualLocalTimeState)
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCGetDeduplicatedDataMacros  StbM Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define StbM_IsEthClockConfigUsedOfLocalClockConfig(Index)                                          (((boolean)(StbM_GetEthClockConfigIdxOfLocalClockConfig(Index) != STBM_NO_ETHCLOCKCONFIGIDXOFLOCALCLOCKCONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to StbM_EthClockConfig */
#define StbM_IsLocalClockConfigUsedOfLocalTimeConfig(Index)                                         (((boolean)(StbM_GetLocalClockConfigIdxOfLocalTimeConfig(Index) != STBM_NO_LOCALCLOCKCONFIGIDXOFLOCALTIMECONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to StbM_LocalClockConfig */
#define StbM_GetSizeOfEthClockConfig()                                                              StbM_GetSizeOfEthClockConfigOfPCConfig()
#define StbM_GetSizeOfLocalClockConfig()                                                            StbM_GetSizeOfLocalClockConfigOfPCConfig()
#define StbM_GetSizeOfLocalClockState()                                                             StbM_GetSizeOfLocalClockStateOfPCConfig()
#define StbM_GetSizeOfLocalTimeConfig()                                                             StbM_GetSizeOfLocalTimeConfigOfPCConfig()
#define StbM_GetSizeOfLocalTimeState()                                                              StbM_GetSizeOfLocalTimeStateOfPCConfig()
#define StbM_GetSizeOfRateMeasurements()                                                            StbM_GetSizeOfRateMeasurementsOfPCConfig()
#define StbM_GetSizeOfStatus()                                                                      StbM_GetSizeOfStatusOfPCConfig()
#define StbM_GetSizeOfTimeBaseConfig()                                                              StbM_GetSizeOfTimeBaseConfigOfPCConfig()
#define StbM_GetSizeOfTimeBaseState()                                                               StbM_GetSizeOfTimeBaseStateOfPCConfig()
#define StbM_GetSizeOfTimeCorrectionSlaveConfig()                                                   StbM_GetSizeOfTimeCorrectionSlaveConfigOfPCConfig()
#define StbM_GetSizeOfTimeCorrectionSlaveState()                                                    StbM_GetSizeOfTimeCorrectionSlaveStateOfPCConfig()
#define StbM_GetSizeOfTimeLeapConfig()                                                              StbM_GetSizeOfTimeLeapConfigOfPCConfig()
#define StbM_GetSizeOfTimeLeapState()                                                               StbM_GetSizeOfTimeLeapStateOfPCConfig()
#define StbM_GetSizeOfTimeoutConfig()                                                               StbM_GetSizeOfTimeoutConfigOfPCConfig()
#define StbM_GetSizeOfTimeoutState()                                                                StbM_GetSizeOfTimeoutStateOfPCConfig()
#define StbM_GetSizeOfUserDataState()                                                               StbM_GetSizeOfUserDataStateOfPCConfig()
#define StbM_GetSizeOfVirtualLocalTimeState()                                                       StbM_GetSizeOfVirtualLocalTimeStateOfPCConfig()
#define StbM_IsLocalTimeConfigUsedOfTimeBaseConfig(Index)                                           (((boolean)(StbM_GetLocalTimeConfigIdxOfTimeBaseConfig(Index) != STBM_NO_LOCALTIMECONFIGIDXOFTIMEBASECONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to StbM_LocalTimeConfig */
#define StbM_IsTimeCorrectionSlaveConfigUsedOfTimeBaseConfig(Index)                                 (((boolean)(StbM_GetTimeCorrectionSlaveConfigIdxOfTimeBaseConfig(Index) != STBM_NO_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to StbM_TimeCorrectionSlaveConfig */
#define StbM_IsTimeLeapConfigUsedOfTimeBaseConfig(Index)                                            (((boolean)(StbM_GetTimeLeapConfigIdxOfTimeBaseConfig(Index) != STBM_NO_TIMELEAPCONFIGIDXOFTIMEBASECONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to StbM_TimeLeapConfig */
#define StbM_IsTimeoutConfigUsedOfTimeBaseConfig(Index)                                             (((boolean)(StbM_GetTimeoutConfigIdxOfTimeBaseConfig(Index) != STBM_NO_TIMEOUTCONFIGIDXOFTIMEBASECONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to StbM_TimeoutConfig */
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCSetDataMacros  StbM Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define StbM_SetInitialized(Value)                                                                  (*(StbM_GetInitializedOfPCConfig())) = (Value)
#define StbM_SetFractionalPartOfLocalClockState(Index, Value)                                       StbM_GetLocalClockStateOfPCConfig()[(Index)].FractionalPartOfLocalClockState = (Value)
#define StbM_SetLastReadTimeOfLocalClockState(Index, Value)                                         StbM_GetLocalClockStateOfPCConfig()[(Index)].LastReadTimeOfLocalClockState = (Value)
#define StbM_SetGlobalTimeRxOfLocalTimeState(Index, Value)                                          StbM_GetLocalTimeStateOfPCConfig()[(Index)].GlobalTimeRxOfLocalTimeState = (Value)
#define StbM_SetGlobalTimeSyncOfLocalTimeState(Index, Value)                                        StbM_GetLocalTimeStateOfPCConfig()[(Index)].GlobalTimeSyncOfLocalTimeState = (Value)
#define StbM_SetLocalTimeOfLocalTimeState(Index, Value)                                             StbM_GetLocalTimeStateOfPCConfig()[(Index)].LocalTimeOfLocalTimeState = (Value)
#define StbM_SetLocalTimeSyncOfLocalTimeState(Index, Value)                                         StbM_GetLocalTimeStateOfPCConfig()[(Index)].LocalTimeSyncOfLocalTimeState = (Value)
#define StbM_SetLocalTimeUpdatedOfLocalTimeState(Index, Value)                                      StbM_GetLocalTimeStateOfPCConfig()[(Index)].LocalTimeUpdatedOfLocalTimeState = (Value)
#define StbM_SetTimeLeapOfLocalTimeState(Index, Value)                                              StbM_GetLocalTimeStateOfPCConfig()[(Index)].TimeLeapOfLocalTimeState = (Value)
#define StbM_SetTimeLeapValidOfLocalTimeState(Index, Value)                                         StbM_GetLocalTimeStateOfPCConfig()[(Index)].TimeLeapValidOfLocalTimeState = (Value)
#define StbM_SetStartGlobalTimeOfRateMeasurements(Index, Value)                                     StbM_GetRateMeasurementsOfPCConfig()[(Index)].StartGlobalTimeOfRateMeasurements = (Value)
#define StbM_SetStartStatusOfRateMeasurements(Index, Value)                                         StbM_GetRateMeasurementsOfPCConfig()[(Index)].StartStatusOfRateMeasurements = (Value)
#define StbM_SetStartVirtualLocalTimeOfRateMeasurements(Index, Value)                               StbM_GetRateMeasurementsOfPCConfig()[(Index)].StartVirtualLocalTimeOfRateMeasurements = (Value)
#define StbM_SetStopGlobalTimeOfRateMeasurements(Index, Value)                                      StbM_GetRateMeasurementsOfPCConfig()[(Index)].StopGlobalTimeOfRateMeasurements = (Value)
#define StbM_SetStopStatusOfRateMeasurements(Index, Value)                                          StbM_GetRateMeasurementsOfPCConfig()[(Index)].StopStatusOfRateMeasurements = (Value)
#define StbM_SetStopVirtualLocalTimeOfRateMeasurements(Index, Value)                                StbM_GetRateMeasurementsOfPCConfig()[(Index)].StopVirtualLocalTimeOfRateMeasurements = (Value)
#define StbM_SetValidOfRateMeasurements(Index, Value)                                               StbM_GetRateMeasurementsOfPCConfig()[(Index)].ValidOfRateMeasurements = (Value)
#define StbM_SetGlobalTimeStatusOfStatus(Index, Value)                                              StbM_GetStatusOfPCConfig()[(Index)].GlobalTimeStatusOfStatus = (Value)
#define StbM_SetLocalTimeStatusOfStatus(Index, Value)                                               StbM_GetStatusOfPCConfig()[(Index)].LocalTimeStatusOfStatus = (Value)
#define StbM_SetUpdateCounterOfTimeBaseState(Index, Value)                                          StbM_GetTimeBaseStateOfPCConfig()[(Index)].UpdateCounterOfTimeBaseState = (Value)
#define StbM_SetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index, Value)                 StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].CurrentRateMeasurementIndexOfTimeCorrectionSlaveState = (Value)
#define StbM_SetOffsetCorrectionRateValidOfTimeCorrectionSlaveState(Index, Value)                   StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].OffsetCorrectionRateValidOfTimeCorrectionSlaveState = (Value)
#define StbM_SetOffsetRateCorrectionOfTimeCorrectionSlaveState(Index, Value)                        StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].OffsetRateCorrectionOfTimeCorrectionSlaveState = (Value)
#define StbM_SetRateCorrectionOfTimeCorrectionSlaveState(Index, Value)                              StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].RateCorrectionOfTimeCorrectionSlaveState = (Value)
#define StbM_SetRateDeviationValidOfTimeCorrectionSlaveState(Index, Value)                          StbM_GetTimeCorrectionSlaveStateOfPCConfig()[(Index)].RateDeviationValidOfTimeCorrectionSlaveState = (Value)
#define StbM_SetClearCountOfTimeLeapState(Index, Value)                                             StbM_GetTimeLeapStateOfPCConfig()[(Index)].ClearCountOfTimeLeapState = (Value)
#define StbM_SetSyncLossTimeoutCounterOfTimeoutState(Index, Value)                                  StbM_GetTimeoutStateOfPCConfig()[(Index)].SyncLossTimeoutCounterOfTimeoutState = (Value)
#define StbM_SetUserDataOfUserDataState(Index, Value)                                               StbM_GetUserDataStateOfPCConfig()[(Index)].UserDataOfUserDataState = (Value)
#define StbM_SetVirtualLocalTimeOfVirtualLocalTimeState(Index, Value)                               StbM_GetVirtualLocalTimeStateOfPCConfig()[(Index)].VirtualLocalTimeOfVirtualLocalTimeState = (Value)
#define StbM_SetVirtualLocalTimeRxOfVirtualLocalTimeState(Index, Value)                             StbM_GetVirtualLocalTimeStateOfPCConfig()[(Index)].VirtualLocalTimeRxOfVirtualLocalTimeState = (Value)
#define StbM_SetVirtualLocalTimeSyncOfVirtualLocalTimeState(Index, Value)                           StbM_GetVirtualLocalTimeStateOfPCConfig()[(Index)].VirtualLocalTimeSyncOfVirtualLocalTimeState = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCGetAddressOfDataMacros  StbM Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define StbM_GetAddrUserDataOfUserDataState(Index)                                                  (&StbM_GetUserDataOfUserDataState(Index))
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCHasMacros  StbM Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define StbM_HasEthClockConfig()                                                                    (TRUE != FALSE)
#define StbM_HasEthIfCtrlIdxOfEthClockConfig()                                                      (TRUE != FALSE)
#define StbM_HasInitialized()                                                                       (TRUE != FALSE)
#define StbM_HasLocalClockConfig()                                                                  (TRUE != FALSE)
#define StbM_HasClockTypeOfLocalClockConfig()                                                       (TRUE != FALSE)
#define StbM_HasDenominatorOfFactorClockTicksToLocalTimeOfLocalClockConfig()                        (TRUE != FALSE)
#define StbM_HasEthClockConfigIdxOfLocalClockConfig()                                               (TRUE != FALSE)
#define StbM_HasEthClockConfigUsedOfLocalClockConfig()                                              (TRUE != FALSE)
#define StbM_HasHwFrequencyOfLocalClockConfig()                                                     (TRUE != FALSE)
#define StbM_HasHwPrescalerOfLocalClockConfig()                                                     (TRUE != FALSE)
#define StbM_HasNumeratorOfFactorClockTicksToLocalTimeOfLocalClockConfig()                          (TRUE != FALSE)
#define StbM_HasLocalClockState()                                                                   (TRUE != FALSE)
#define StbM_HasFractionalPartOfLocalClockState()                                                   (TRUE != FALSE)
#define StbM_HasLastReadTimeOfLocalClockState()                                                     (TRUE != FALSE)
#define StbM_HasLocalTimeConfig()                                                                   (TRUE != FALSE)
#define StbM_HasLocalClockConfigIdxOfLocalTimeConfig()                                              (TRUE != FALSE)
#define StbM_HasLocalClockConfigUsedOfLocalTimeConfig()                                             (TRUE != FALSE)
#define StbM_HasTimeBaseConfigIdxOfLocalTimeConfig()                                                (TRUE != FALSE)
#define StbM_HasLocalTimeState()                                                                    (TRUE != FALSE)
#define StbM_HasGlobalTimeRxOfLocalTimeState()                                                      (TRUE != FALSE)
#define StbM_HasGlobalTimeSyncOfLocalTimeState()                                                    (TRUE != FALSE)
#define StbM_HasLocalTimeOfLocalTimeState()                                                         (TRUE != FALSE)
#define StbM_HasLocalTimeSyncOfLocalTimeState()                                                     (TRUE != FALSE)
#define StbM_HasLocalTimeUpdatedOfLocalTimeState()                                                  (TRUE != FALSE)
#define StbM_HasTimeLeapOfLocalTimeState()                                                          (TRUE != FALSE)
#define StbM_HasTimeLeapValidOfLocalTimeState()                                                     (TRUE != FALSE)
#define StbM_HasRateMeasurements()                                                                  (TRUE != FALSE)
#define StbM_HasStartGlobalTimeOfRateMeasurements()                                                 (TRUE != FALSE)
#define StbM_HasStartStatusOfRateMeasurements()                                                     (TRUE != FALSE)
#define StbM_HasStartVirtualLocalTimeOfRateMeasurements()                                           (TRUE != FALSE)
#define StbM_HasStopGlobalTimeOfRateMeasurements()                                                  (TRUE != FALSE)
#define StbM_HasStopStatusOfRateMeasurements()                                                      (TRUE != FALSE)
#define StbM_HasStopVirtualLocalTimeOfRateMeasurements()                                            (TRUE != FALSE)
#define StbM_HasValidOfRateMeasurements()                                                           (TRUE != FALSE)
#define StbM_HasSizeOfEthClockConfig()                                                              (TRUE != FALSE)
#define StbM_HasSizeOfLocalClockConfig()                                                            (TRUE != FALSE)
#define StbM_HasSizeOfLocalClockState()                                                             (TRUE != FALSE)
#define StbM_HasSizeOfLocalTimeConfig()                                                             (TRUE != FALSE)
#define StbM_HasSizeOfLocalTimeState()                                                              (TRUE != FALSE)
#define StbM_HasSizeOfRateMeasurements()                                                            (TRUE != FALSE)
#define StbM_HasSizeOfStatus()                                                                      (TRUE != FALSE)
#define StbM_HasSizeOfTimeBaseConfig()                                                              (TRUE != FALSE)
#define StbM_HasSizeOfTimeBaseState()                                                               (TRUE != FALSE)
#define StbM_HasSizeOfTimeCorrectionSlaveConfig()                                                   (TRUE != FALSE)
#define StbM_HasSizeOfTimeCorrectionSlaveState()                                                    (TRUE != FALSE)
#define StbM_HasSizeOfTimeLeapConfig()                                                              (TRUE != FALSE)
#define StbM_HasSizeOfTimeLeapState()                                                               (TRUE != FALSE)
#define StbM_HasSizeOfTimeoutConfig()                                                               (TRUE != FALSE)
#define StbM_HasSizeOfTimeoutState()                                                                (TRUE != FALSE)
#define StbM_HasSizeOfUserDataState()                                                               (TRUE != FALSE)
#define StbM_HasSizeOfVirtualLocalTimeState()                                                       (TRUE != FALSE)
#define StbM_HasStatus()                                                                            (TRUE != FALSE)
#define StbM_HasGlobalTimeStatusOfStatus()                                                          (TRUE != FALSE)
#define StbM_HasLocalTimeStatusOfStatus()                                                           (TRUE != FALSE)
#define StbM_HasTimeBaseConfig()                                                                    (TRUE != FALSE)
#define StbM_HasGlobalTimeMasterOfTimeBaseConfig()                                                  (TRUE != FALSE)
#define StbM_HasLocalTimeConfigIdxOfTimeBaseConfig()                                                (TRUE != FALSE)
#define StbM_HasLocalTimeConfigUsedOfTimeBaseConfig()                                               (TRUE != FALSE)
#define StbM_HasStatusIdxOfTimeBaseConfig()                                                         (TRUE != FALSE)
#define StbM_HasSynchronizedTimeBaseOfTimeBaseConfig()                                              (TRUE != FALSE)
#define StbM_HasTimeBaseIdOfTimeBaseConfig()                                                        (TRUE != FALSE)
#define StbM_HasTimeCorrectionSlaveConfigIdxOfTimeBaseConfig()                                      (TRUE != FALSE)
#define StbM_HasTimeCorrectionSlaveConfigUsedOfTimeBaseConfig()                                     (TRUE != FALSE)
#define StbM_HasTimeLeapConfigIdxOfTimeBaseConfig()                                                 (TRUE != FALSE)
#define StbM_HasTimeLeapConfigUsedOfTimeBaseConfig()                                                (TRUE != FALSE)
#define StbM_HasTimeSlaveOfTimeBaseConfig()                                                         (TRUE != FALSE)
#define StbM_HasTimeoutConfigIdxOfTimeBaseConfig()                                                  (TRUE != FALSE)
#define StbM_HasTimeoutConfigUsedOfTimeBaseConfig()                                                 (TRUE != FALSE)
#define StbM_HasUserDataStateIdxOfTimeBaseConfig()                                                  (TRUE != FALSE)
#define StbM_HasTimeBaseState()                                                                     (TRUE != FALSE)
#define StbM_HasUpdateCounterOfTimeBaseState()                                                      (TRUE != FALSE)
#define StbM_HasTimeCorrectionSlaveConfig()                                                         (TRUE != FALSE)
#define StbM_HasNumberOfSimultaneousRateMeasurementsOfTimeCorrectionSlaveConfig()                   (TRUE != FALSE)
#define StbM_HasOffsetCorrectionAdaptionIntervalOfTimeCorrectionSlaveConfig()                       (TRUE != FALSE)
#define StbM_HasOffsetCorrectionJumpThresholdOfTimeCorrectionSlaveConfig()                          (TRUE != FALSE)
#define StbM_HasRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig()           (TRUE != FALSE)
#define StbM_HasRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig()               (TRUE != FALSE)
#define StbM_HasRateMeasurementsEndIdxOfTimeCorrectionSlaveConfig()                                 (TRUE != FALSE)
#define StbM_HasRateMeasurementsStartIdxOfTimeCorrectionSlaveConfig()                               (TRUE != FALSE)
#define StbM_HasSingleRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig()     (TRUE != FALSE)
#define StbM_HasSingleRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig()         (TRUE != FALSE)
#define StbM_HasTimeCorrectionSlaveState()                                                          (TRUE != FALSE)
#define StbM_HasCurrentRateMeasurementIndexOfTimeCorrectionSlaveState()                             (TRUE != FALSE)
#define StbM_HasOffsetCorrectionRateValidOfTimeCorrectionSlaveState()                               (TRUE != FALSE)
#define StbM_HasOffsetRateCorrectionOfTimeCorrectionSlaveState()                                    (TRUE != FALSE)
#define StbM_HasRateCorrectionOfTimeCorrectionSlaveState()                                          (TRUE != FALSE)
#define StbM_HasRateDeviationValidOfTimeCorrectionSlaveState()                                      (TRUE != FALSE)
#define StbM_HasTimeLeapConfig()                                                                    (TRUE != FALSE)
#define StbM_HasClearCountOfTimeLeapConfig()                                                        (TRUE != FALSE)
#define StbM_HasFutureThresholdOfTimeLeapConfig()                                                   (TRUE != FALSE)
#define StbM_HasPastThresholdOfTimeLeapConfig()                                                     (TRUE != FALSE)
#define StbM_HasTimeLeapState()                                                                     (TRUE != FALSE)
#define StbM_HasClearCountOfTimeLeapState()                                                         (TRUE != FALSE)
#define StbM_HasTimeoutConfig()                                                                     (TRUE != FALSE)
#define StbM_HasSyncLossTimeoutCounterOfTimeoutConfig()                                             (TRUE != FALSE)
#define StbM_HasTimeBaseConfigIdxOfTimeoutConfig()                                                  (TRUE != FALSE)
#define StbM_HasTimeoutState()                                                                      (TRUE != FALSE)
#define StbM_HasSyncLossTimeoutCounterOfTimeoutState()                                              (TRUE != FALSE)
#define StbM_HasUserDataState()                                                                     (TRUE != FALSE)
#define StbM_HasUserDataOfUserDataState()                                                           (TRUE != FALSE)
#define StbM_HasVirtualLocalTimeState()                                                             (TRUE != FALSE)
#define StbM_HasVirtualLocalTimeOfVirtualLocalTimeState()                                           (TRUE != FALSE)
#define StbM_HasVirtualLocalTimeRxOfVirtualLocalTimeState()                                         (TRUE != FALSE)
#define StbM_HasVirtualLocalTimeSyncOfVirtualLocalTimeState()                                       (TRUE != FALSE)
#define StbM_HasPCConfig()                                                                          (TRUE != FALSE)
#define StbM_HasEthClockConfigOfPCConfig()                                                          (TRUE != FALSE)
#define StbM_HasInitializedOfPCConfig()                                                             (TRUE != FALSE)
#define StbM_HasLocalClockConfigOfPCConfig()                                                        (TRUE != FALSE)
#define StbM_HasLocalClockStateOfPCConfig()                                                         (TRUE != FALSE)
#define StbM_HasLocalTimeConfigOfPCConfig()                                                         (TRUE != FALSE)
#define StbM_HasLocalTimeStateOfPCConfig()                                                          (TRUE != FALSE)
#define StbM_HasRateMeasurementsOfPCConfig()                                                        (TRUE != FALSE)
#define StbM_HasSizeOfEthClockConfigOfPCConfig()                                                    (TRUE != FALSE)
#define StbM_HasSizeOfLocalClockConfigOfPCConfig()                                                  (TRUE != FALSE)
#define StbM_HasSizeOfLocalClockStateOfPCConfig()                                                   (TRUE != FALSE)
#define StbM_HasSizeOfLocalTimeConfigOfPCConfig()                                                   (TRUE != FALSE)
#define StbM_HasSizeOfLocalTimeStateOfPCConfig()                                                    (TRUE != FALSE)
#define StbM_HasSizeOfRateMeasurementsOfPCConfig()                                                  (TRUE != FALSE)
#define StbM_HasSizeOfStatusOfPCConfig()                                                            (TRUE != FALSE)
#define StbM_HasSizeOfTimeBaseConfigOfPCConfig()                                                    (TRUE != FALSE)
#define StbM_HasSizeOfTimeBaseStateOfPCConfig()                                                     (TRUE != FALSE)
#define StbM_HasSizeOfTimeCorrectionSlaveConfigOfPCConfig()                                         (TRUE != FALSE)
#define StbM_HasSizeOfTimeCorrectionSlaveStateOfPCConfig()                                          (TRUE != FALSE)
#define StbM_HasSizeOfTimeLeapConfigOfPCConfig()                                                    (TRUE != FALSE)
#define StbM_HasSizeOfTimeLeapStateOfPCConfig()                                                     (TRUE != FALSE)
#define StbM_HasSizeOfTimeoutConfigOfPCConfig()                                                     (TRUE != FALSE)
#define StbM_HasSizeOfTimeoutStateOfPCConfig()                                                      (TRUE != FALSE)
#define StbM_HasSizeOfUserDataStateOfPCConfig()                                                     (TRUE != FALSE)
#define StbM_HasSizeOfVirtualLocalTimeStateOfPCConfig()                                             (TRUE != FALSE)
#define StbM_HasStatusOfPCConfig()                                                                  (TRUE != FALSE)
#define StbM_HasTimeBaseConfigOfPCConfig()                                                          (TRUE != FALSE)
#define StbM_HasTimeBaseStateOfPCConfig()                                                           (TRUE != FALSE)
#define StbM_HasTimeCorrectionSlaveConfigOfPCConfig()                                               (TRUE != FALSE)
#define StbM_HasTimeCorrectionSlaveStateOfPCConfig()                                                (TRUE != FALSE)
#define StbM_HasTimeLeapConfigOfPCConfig()                                                          (TRUE != FALSE)
#define StbM_HasTimeLeapStateOfPCConfig()                                                           (TRUE != FALSE)
#define StbM_HasTimeoutConfigOfPCConfig()                                                           (TRUE != FALSE)
#define StbM_HasTimeoutStateOfPCConfig()                                                            (TRUE != FALSE)
#define StbM_HasUserDataStateOfPCConfig()                                                           (TRUE != FALSE)
#define StbM_HasVirtualLocalTimeStateOfPCConfig()                                                   (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCIncrementDataMacros  StbM Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define StbM_IncFractionalPartOfLocalClockState(Index)                                              StbM_GetFractionalPartOfLocalClockState(Index)++
#define StbM_IncLocalTimeUpdatedOfLocalTimeState(Index)                                             StbM_GetLocalTimeUpdatedOfLocalTimeState(Index)++
#define StbM_IncTimeLeapOfLocalTimeState(Index)                                                     StbM_GetTimeLeapOfLocalTimeState(Index)++
#define StbM_IncStartStatusOfRateMeasurements(Index)                                                StbM_GetStartStatusOfRateMeasurements(Index)++
#define StbM_IncStopStatusOfRateMeasurements(Index)                                                 StbM_GetStopStatusOfRateMeasurements(Index)++
#define StbM_IncGlobalTimeStatusOfStatus(Index)                                                     StbM_GetGlobalTimeStatusOfStatus(Index)++
#define StbM_IncLocalTimeStatusOfStatus(Index)                                                      StbM_GetLocalTimeStatusOfStatus(Index)++
#define StbM_IncUpdateCounterOfTimeBaseState(Index)                                                 StbM_GetUpdateCounterOfTimeBaseState(Index)++
#define StbM_IncCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index)                        StbM_GetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index)++
#define StbM_IncClearCountOfTimeLeapState(Index)                                                    StbM_GetClearCountOfTimeLeapState(Index)++
#define StbM_IncSyncLossTimeoutCounterOfTimeoutState(Index)                                         StbM_GetSyncLossTimeoutCounterOfTimeoutState(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCDecrementDataMacros  StbM Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define StbM_DecFractionalPartOfLocalClockState(Index)                                              StbM_GetFractionalPartOfLocalClockState(Index)--
#define StbM_DecLocalTimeUpdatedOfLocalTimeState(Index)                                             StbM_GetLocalTimeUpdatedOfLocalTimeState(Index)--
#define StbM_DecTimeLeapOfLocalTimeState(Index)                                                     StbM_GetTimeLeapOfLocalTimeState(Index)--
#define StbM_DecStartStatusOfRateMeasurements(Index)                                                StbM_GetStartStatusOfRateMeasurements(Index)--
#define StbM_DecStopStatusOfRateMeasurements(Index)                                                 StbM_GetStopStatusOfRateMeasurements(Index)--
#define StbM_DecGlobalTimeStatusOfStatus(Index)                                                     StbM_GetGlobalTimeStatusOfStatus(Index)--
#define StbM_DecLocalTimeStatusOfStatus(Index)                                                      StbM_GetLocalTimeStatusOfStatus(Index)--
#define StbM_DecUpdateCounterOfTimeBaseState(Index)                                                 StbM_GetUpdateCounterOfTimeBaseState(Index)--
#define StbM_DecCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index)                        StbM_GetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index)--
#define StbM_DecClearCountOfTimeLeapState(Index)                                                    StbM_GetClearCountOfTimeLeapState(Index)--
#define StbM_DecSyncLossTimeoutCounterOfTimeoutState(Index)                                         StbM_GetSyncLossTimeoutCounterOfTimeoutState(Index)--
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCAddDataMacros  StbM Add Data Macros (PRE_COMPILE)
  \brief  These macros can be used to add VAR data with numerical nature.
  \{
*/ 
#define StbM_AddFractionalPartOfLocalClockState(Index, Value)                                       StbM_SetFractionalPartOfLocalClockState(Index, (StbM_GetFractionalPartOfLocalClockState(Index) + Value))
#define StbM_AddLocalTimeUpdatedOfLocalTimeState(Index, Value)                                      StbM_SetLocalTimeUpdatedOfLocalTimeState(Index, (StbM_GetLocalTimeUpdatedOfLocalTimeState(Index) + Value))
#define StbM_AddTimeLeapOfLocalTimeState(Index, Value)                                              StbM_SetTimeLeapOfLocalTimeState(Index, (StbM_GetTimeLeapOfLocalTimeState(Index) + Value))
#define StbM_AddStartStatusOfRateMeasurements(Index, Value)                                         StbM_SetStartStatusOfRateMeasurements(Index, (StbM_GetStartStatusOfRateMeasurements(Index) + Value))
#define StbM_AddStopStatusOfRateMeasurements(Index, Value)                                          StbM_SetStopStatusOfRateMeasurements(Index, (StbM_GetStopStatusOfRateMeasurements(Index) + Value))
#define StbM_AddGlobalTimeStatusOfStatus(Index, Value)                                              StbM_SetGlobalTimeStatusOfStatus(Index, (StbM_GetGlobalTimeStatusOfStatus(Index) + Value))
#define StbM_AddLocalTimeStatusOfStatus(Index, Value)                                               StbM_SetLocalTimeStatusOfStatus(Index, (StbM_GetLocalTimeStatusOfStatus(Index) + Value))
#define StbM_AddUpdateCounterOfTimeBaseState(Index, Value)                                          StbM_SetUpdateCounterOfTimeBaseState(Index, (StbM_GetUpdateCounterOfTimeBaseState(Index) + Value))
#define StbM_AddCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index, Value)                 StbM_SetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index, (StbM_GetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index) + Value))
#define StbM_AddClearCountOfTimeLeapState(Index, Value)                                             StbM_SetClearCountOfTimeLeapState(Index, (StbM_GetClearCountOfTimeLeapState(Index) + Value))
#define StbM_AddSyncLossTimeoutCounterOfTimeoutState(Index, Value)                                  StbM_SetSyncLossTimeoutCounterOfTimeoutState(Index, (StbM_GetSyncLossTimeoutCounterOfTimeoutState(Index) + Value))
/** 
  \}
*/ 

/** 
  \defgroup  StbMPCSubstractDataMacros  StbM Substract Data Macros (PRE_COMPILE)
  \brief  These macros can be used to substract VAR data with numerical nature.
  \{
*/ 
#define StbM_SubFractionalPartOfLocalClockState(Index, Value)                                       StbM_SetFractionalPartOfLocalClockState(Index, (StbM_GetFractionalPartOfLocalClockState(Index) - Value))
#define StbM_SubLocalTimeUpdatedOfLocalTimeState(Index, Value)                                      StbM_SetLocalTimeUpdatedOfLocalTimeState(Index, (StbM_GetLocalTimeUpdatedOfLocalTimeState(Index) - Value))
#define StbM_SubTimeLeapOfLocalTimeState(Index, Value)                                              StbM_SetTimeLeapOfLocalTimeState(Index, (StbM_GetTimeLeapOfLocalTimeState(Index) - Value))
#define StbM_SubStartStatusOfRateMeasurements(Index, Value)                                         StbM_SetStartStatusOfRateMeasurements(Index, (StbM_GetStartStatusOfRateMeasurements(Index) - Value))
#define StbM_SubStopStatusOfRateMeasurements(Index, Value)                                          StbM_SetStopStatusOfRateMeasurements(Index, (StbM_GetStopStatusOfRateMeasurements(Index) - Value))
#define StbM_SubGlobalTimeStatusOfStatus(Index, Value)                                              StbM_SetGlobalTimeStatusOfStatus(Index, (StbM_GetGlobalTimeStatusOfStatus(Index) - Value))
#define StbM_SubLocalTimeStatusOfStatus(Index, Value)                                               StbM_SetLocalTimeStatusOfStatus(Index, (StbM_GetLocalTimeStatusOfStatus(Index) - Value))
#define StbM_SubUpdateCounterOfTimeBaseState(Index, Value)                                          StbM_SetUpdateCounterOfTimeBaseState(Index, (StbM_GetUpdateCounterOfTimeBaseState(Index) - Value))
#define StbM_SubCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index, Value)                 StbM_SetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index, (StbM_GetCurrentRateMeasurementIndexOfTimeCorrectionSlaveState(Index) - Value))
#define StbM_SubClearCountOfTimeLeapState(Index, Value)                                             StbM_SetClearCountOfTimeLeapState(Index, (StbM_GetClearCountOfTimeLeapState(Index) - Value))
#define StbM_SubSyncLossTimeoutCounterOfTimeoutState(Index, Value)                                  StbM_SetSyncLossTimeoutCounterOfTimeoutState(Index, (StbM_GetSyncLossTimeoutCounterOfTimeoutState(Index) - Value))
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
typedef uint32 StbM_NanosecondsType;
typedef uint32 StbM_SecondsType;
typedef uint16 StbM_SecondsHiType;

typedef struct
{
    StbM_NanosecondsType nanoseconds;
    StbM_SecondsType seconds;
    StbM_SecondsHiType secondsHi;
} StbM_InternalTimeStampType;

typedef uint64 StbM_InternalVirtualLocalTimeType;

typedef struct
{
  StbM_TimeStampType StartGlobalTime;
  StbM_TimeStampType StartLocalTime;
  StbM_InternalVirtualLocalTimeType StartVirtualLocalTime;
  boolean Discard;
} StbM_RateMeasurementType;

 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  StbMPCIterableTypes  StbM Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate StbM_EthClockConfig */
typedef uint8_least StbM_EthClockConfigIterType;

/**   \brief  type used to iterate StbM_LocalClockConfig */
typedef uint8_least StbM_LocalClockConfigIterType;

/**   \brief  type used to iterate StbM_LocalTimeConfig */
typedef uint8_least StbM_LocalTimeConfigIterType;

/**   \brief  type used to iterate StbM_RateMeasurements */
typedef uint8_least StbM_RateMeasurementsIterType;

/**   \brief  type used to iterate StbM_Status */
typedef uint8_least StbM_StatusIterType;

/**   \brief  type used to iterate StbM_TimeBaseConfig */
typedef uint8_least StbM_TimeBaseConfigIterType;

/**   \brief  type used to iterate StbM_TimeCorrectionSlaveConfig */
typedef uint8_least StbM_TimeCorrectionSlaveConfigIterType;

/**   \brief  type used to iterate StbM_TimeLeapConfig */
typedef uint8_least StbM_TimeLeapConfigIterType;

/**   \brief  type used to iterate StbM_TimeoutConfig */
typedef uint8_least StbM_TimeoutConfigIterType;

/**   \brief  type used to iterate StbM_UserDataState */
typedef uint8_least StbM_UserDataStateIterType;

/** 
  \}
*/ 

/** 
  \defgroup  StbMPCIterableTypesWithSizeRelations  StbM Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate StbM_LocalClockState */
typedef StbM_LocalClockConfigIterType StbM_LocalClockStateIterType;

/**   \brief  type used to iterate StbM_LocalTimeState */
typedef StbM_LocalTimeConfigIterType StbM_LocalTimeStateIterType;

/**   \brief  type used to iterate StbM_TimeBaseState */
typedef StbM_TimeBaseConfigIterType StbM_TimeBaseStateIterType;

/**   \brief  type used to iterate StbM_TimeCorrectionSlaveState */
typedef StbM_TimeCorrectionSlaveConfigIterType StbM_TimeCorrectionSlaveStateIterType;

/**   \brief  type used to iterate StbM_TimeLeapState */
typedef StbM_TimeLeapConfigIterType StbM_TimeLeapStateIterType;

/**   \brief  type used to iterate StbM_TimeoutState */
typedef StbM_TimeoutConfigIterType StbM_TimeoutStateIterType;

/**   \brief  type used to iterate StbM_VirtualLocalTimeState */
typedef StbM_LocalTimeConfigIterType StbM_VirtualLocalTimeStateIterType;

/** 
  \}
*/ 

/** 
  \defgroup  StbMPCValueTypes  StbM Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for StbM_EthIfCtrlIdxOfEthClockConfig */
typedef uint8 StbM_EthIfCtrlIdxOfEthClockConfigType;

/**   \brief  value based type definition for StbM_Initialized */
typedef boolean StbM_InitializedType;

/**   \brief  value based type definition for StbM_ClockTypeOfLocalClockConfig */
typedef uint8 StbM_ClockTypeOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_DenominatorOfFactorClockTicksToLocalTimeOfLocalClockConfig */
typedef uint8 StbM_DenominatorOfFactorClockTicksToLocalTimeOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_EthClockConfigIdxOfLocalClockConfig */
typedef uint8 StbM_EthClockConfigIdxOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_EthClockConfigUsedOfLocalClockConfig */
typedef boolean StbM_EthClockConfigUsedOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_HwFrequencyOfLocalClockConfig */
typedef uint32 StbM_HwFrequencyOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_HwPrescalerOfLocalClockConfig */
typedef uint8 StbM_HwPrescalerOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_NumeratorOfFactorClockTicksToLocalTimeOfLocalClockConfig */
typedef uint32 StbM_NumeratorOfFactorClockTicksToLocalTimeOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_FractionalPartOfLocalClockState */
typedef uint64 StbM_FractionalPartOfLocalClockStateType;

/**   \brief  value based type definition for StbM_LocalClockConfigIdxOfLocalTimeConfig */
typedef uint8 StbM_LocalClockConfigIdxOfLocalTimeConfigType;

/**   \brief  value based type definition for StbM_LocalClockConfigUsedOfLocalTimeConfig */
typedef boolean StbM_LocalClockConfigUsedOfLocalTimeConfigType;

/**   \brief  value based type definition for StbM_TimeBaseConfigIdxOfLocalTimeConfig */
typedef uint8 StbM_TimeBaseConfigIdxOfLocalTimeConfigType;

/**   \brief  value based type definition for StbM_LocalTimeUpdatedOfLocalTimeState */
typedef uint8 StbM_LocalTimeUpdatedOfLocalTimeStateType;

/**   \brief  value based type definition for StbM_TimeLeapOfLocalTimeState */
typedef sint32 StbM_TimeLeapOfLocalTimeStateType;

/**   \brief  value based type definition for StbM_TimeLeapValidOfLocalTimeState */
typedef boolean StbM_TimeLeapValidOfLocalTimeStateType;

/**   \brief  value based type definition for StbM_ValidOfRateMeasurements */
typedef boolean StbM_ValidOfRateMeasurementsType;

/**   \brief  value based type definition for StbM_SizeOfEthClockConfig */
typedef uint8 StbM_SizeOfEthClockConfigType;

/**   \brief  value based type definition for StbM_SizeOfLocalClockConfig */
typedef uint8 StbM_SizeOfLocalClockConfigType;

/**   \brief  value based type definition for StbM_SizeOfLocalClockState */
typedef uint8 StbM_SizeOfLocalClockStateType;

/**   \brief  value based type definition for StbM_SizeOfLocalTimeConfig */
typedef uint8 StbM_SizeOfLocalTimeConfigType;

/**   \brief  value based type definition for StbM_SizeOfLocalTimeState */
typedef uint8 StbM_SizeOfLocalTimeStateType;

/**   \brief  value based type definition for StbM_SizeOfRateMeasurements */
typedef uint8 StbM_SizeOfRateMeasurementsType;

/**   \brief  value based type definition for StbM_SizeOfStatus */
typedef uint8 StbM_SizeOfStatusType;

/**   \brief  value based type definition for StbM_SizeOfTimeBaseConfig */
typedef uint8 StbM_SizeOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_SizeOfTimeBaseState */
typedef uint8 StbM_SizeOfTimeBaseStateType;

/**   \brief  value based type definition for StbM_SizeOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_SizeOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_SizeOfTimeCorrectionSlaveState */
typedef uint8 StbM_SizeOfTimeCorrectionSlaveStateType;

/**   \brief  value based type definition for StbM_SizeOfTimeLeapConfig */
typedef uint8 StbM_SizeOfTimeLeapConfigType;

/**   \brief  value based type definition for StbM_SizeOfTimeLeapState */
typedef uint8 StbM_SizeOfTimeLeapStateType;

/**   \brief  value based type definition for StbM_SizeOfTimeoutConfig */
typedef uint8 StbM_SizeOfTimeoutConfigType;

/**   \brief  value based type definition for StbM_SizeOfTimeoutState */
typedef uint8 StbM_SizeOfTimeoutStateType;

/**   \brief  value based type definition for StbM_SizeOfUserDataState */
typedef uint8 StbM_SizeOfUserDataStateType;

/**   \brief  value based type definition for StbM_SizeOfVirtualLocalTimeState */
typedef uint8 StbM_SizeOfVirtualLocalTimeStateType;

/**   \brief  value based type definition for StbM_GlobalTimeMasterOfTimeBaseConfig */
typedef boolean StbM_GlobalTimeMasterOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_LocalTimeConfigIdxOfTimeBaseConfig */
typedef uint8 StbM_LocalTimeConfigIdxOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_LocalTimeConfigUsedOfTimeBaseConfig */
typedef boolean StbM_LocalTimeConfigUsedOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_StatusIdxOfTimeBaseConfig */
typedef uint8 StbM_StatusIdxOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_SynchronizedTimeBaseOfTimeBaseConfig */
typedef boolean StbM_SynchronizedTimeBaseOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeBaseIdOfTimeBaseConfig */
typedef uint8 StbM_TimeBaseIdOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeCorrectionSlaveConfigIdxOfTimeBaseConfig */
typedef uint8 StbM_TimeCorrectionSlaveConfigIdxOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeCorrectionSlaveConfigUsedOfTimeBaseConfig */
typedef boolean StbM_TimeCorrectionSlaveConfigUsedOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeLeapConfigIdxOfTimeBaseConfig */
typedef uint8 StbM_TimeLeapConfigIdxOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeLeapConfigUsedOfTimeBaseConfig */
typedef boolean StbM_TimeLeapConfigUsedOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeSlaveOfTimeBaseConfig */
typedef boolean StbM_TimeSlaveOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeoutConfigIdxOfTimeBaseConfig */
typedef uint8 StbM_TimeoutConfigIdxOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_TimeoutConfigUsedOfTimeBaseConfig */
typedef boolean StbM_TimeoutConfigUsedOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_UserDataStateIdxOfTimeBaseConfig */
typedef uint8 StbM_UserDataStateIdxOfTimeBaseConfigType;

/**   \brief  value based type definition for StbM_UpdateCounterOfTimeBaseState */
typedef uint8 StbM_UpdateCounterOfTimeBaseStateType;

/**   \brief  value based type definition for StbM_NumberOfSimultaneousRateMeasurementsOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_NumberOfSimultaneousRateMeasurementsOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_OffsetCorrectionAdaptionIntervalOfTimeCorrectionSlaveConfig */
typedef uint32 StbM_OffsetCorrectionAdaptionIntervalOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_OffsetCorrectionJumpThresholdOfTimeCorrectionSlaveConfig */
typedef uint32 StbM_OffsetCorrectionJumpThresholdOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_RateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_RateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_RateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_RateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_RateMeasurementsEndIdxOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_RateMeasurementsEndIdxOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_RateMeasurementsStartIdxOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_RateMeasurementsStartIdxOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_SingleRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_SingleRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_SingleRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig */
typedef uint8 StbM_SingleRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfigType;

/**   \brief  value based type definition for StbM_CurrentRateMeasurementIndexOfTimeCorrectionSlaveState */
typedef uint32 StbM_CurrentRateMeasurementIndexOfTimeCorrectionSlaveStateType;

/**   \brief  value based type definition for StbM_OffsetCorrectionRateValidOfTimeCorrectionSlaveState */
typedef boolean StbM_OffsetCorrectionRateValidOfTimeCorrectionSlaveStateType;

/**   \brief  value based type definition for StbM_OffsetRateCorrectionOfTimeCorrectionSlaveState */
typedef float64 StbM_OffsetRateCorrectionOfTimeCorrectionSlaveStateType;

/**   \brief  value based type definition for StbM_RateCorrectionOfTimeCorrectionSlaveState */
typedef float64 StbM_RateCorrectionOfTimeCorrectionSlaveStateType;

/**   \brief  value based type definition for StbM_RateDeviationValidOfTimeCorrectionSlaveState */
typedef boolean StbM_RateDeviationValidOfTimeCorrectionSlaveStateType;

/**   \brief  value based type definition for StbM_ClearCountOfTimeLeapConfig */
typedef uint8 StbM_ClearCountOfTimeLeapConfigType;

/**   \brief  value based type definition for StbM_FutureThresholdOfTimeLeapConfig */
typedef uint32 StbM_FutureThresholdOfTimeLeapConfigType;

/**   \brief  value based type definition for StbM_PastThresholdOfTimeLeapConfig */
typedef uint32 StbM_PastThresholdOfTimeLeapConfigType;

/**   \brief  value based type definition for StbM_ClearCountOfTimeLeapState */
typedef uint16 StbM_ClearCountOfTimeLeapStateType;

/**   \brief  value based type definition for StbM_SyncLossTimeoutCounterOfTimeoutConfig */
typedef uint8 StbM_SyncLossTimeoutCounterOfTimeoutConfigType;

/**   \brief  value based type definition for StbM_TimeBaseConfigIdxOfTimeoutConfig */
typedef uint8 StbM_TimeBaseConfigIdxOfTimeoutConfigType;

/**   \brief  value based type definition for StbM_SyncLossTimeoutCounterOfTimeoutState */
typedef uint32 StbM_SyncLossTimeoutCounterOfTimeoutStateType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  StbMPCStructTypes  StbM Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in StbM_EthClockConfig */
typedef struct sStbM_EthClockConfigType
{
  StbM_EthIfCtrlIdxOfEthClockConfigType EthIfCtrlIdxOfEthClockConfig;  /**< Index of the ethernet communication controller used as local clock. */
} StbM_EthClockConfigType;

/**   \brief  type used in StbM_LocalClockConfig */
/*! \spec weak type invariant () { 
 * (!((self.EthClockConfigIdxOfLocalClockConfig != STBM_NO_ETHCLOCKCONFIGIDXOFLOCALCLOCKCONFIG)) || (self.EthClockConfigIdxOfLocalClockConfig < StbM_GetSizeOfEthClockConfig()))
 * } */
typedef struct sStbM_LocalClockConfigType
{
  StbM_HwFrequencyOfLocalClockConfigType HwFrequencyOfLocalClockConfig;  /**< Frequency of the hardware reference clock in Hz. */
  StbM_NumeratorOfFactorClockTicksToLocalTimeOfLocalClockConfigType NumeratorOfFactorClockTicksToLocalTimeOfLocalClockConfig;  /**< Pre calculated numerator of the rational number of the calculation: (StbMClockPrescaler * 10^15) / StbMClockFrequency. */
  StbM_ClockTypeOfLocalClockConfigType ClockTypeOfLocalClockConfig;  /**< The type of local clock, which is used as hardware clock */
  StbM_DenominatorOfFactorClockTicksToLocalTimeOfLocalClockConfigType DenominatorOfFactorClockTicksToLocalTimeOfLocalClockConfig;  /**< Pre calculated denominator of the rational number of the calculation: (StbMClockPrescaler * 10^15) / StbMClockFrequency. */
  StbM_EthClockConfigIdxOfLocalClockConfigType EthClockConfigIdxOfLocalClockConfig;  /**< the index of the 0:1 relation pointing to StbM_EthClockConfig */
  StbM_HwPrescalerOfLocalClockConfigType HwPrescalerOfLocalClockConfig;  /**< Prescaler of hardware reference clock. */
} StbM_LocalClockConfigType;

/**   \brief  type used in StbM_LocalClockState */
typedef struct sStbM_LocalClockStateType
{
  StbM_FractionalPartOfLocalClockStateType FractionalPartOfLocalClockState;  /**< The fractional part of the VirtualLocalTime * (HWPrescaler / HWFrequency) calculation in order to increase the precision. */
  StbM_InternalTimeStampType LastReadTimeOfLocalClockState;  /**< Last read time of the lock clock. This can be either a counter value or a real time. */
} StbM_LocalClockStateType;

/**   \brief  type used in StbM_LocalTimeConfig */
/*! \spec weak type invariant () { 
 * (self.TimeBaseConfigIdxOfLocalTimeConfig < StbM_GetSizeOfTimeBaseConfig()) &&
 * (!((self.LocalClockConfigIdxOfLocalTimeConfig != STBM_NO_LOCALCLOCKCONFIGIDXOFLOCALTIMECONFIG)) || (self.LocalClockConfigIdxOfLocalTimeConfig < StbM_GetSizeOfLocalClockConfig()))
 * } */
typedef struct sStbM_LocalTimeConfigType
{
  StbM_LocalClockConfigIdxOfLocalTimeConfigType LocalClockConfigIdxOfLocalTimeConfig;  /**< the index of the 0:1 relation pointing to StbM_LocalClockConfig */
  StbM_TimeBaseConfigIdxOfLocalTimeConfigType TimeBaseConfigIdxOfLocalTimeConfig;  /**< the index of the 1:1 relation pointing to StbM_TimeBaseConfig */
} StbM_LocalTimeConfigType;

/**   \brief  type used in StbM_LocalTimeState */
typedef struct sStbM_LocalTimeStateType
{
  StbM_TimeLeapOfLocalTimeStateType TimeLeapOfLocalTimeState;  /**< The last calculated time leap TGrx - TL. */
  StbM_LocalTimeUpdatedOfLocalTimeStateType LocalTimeUpdatedOfLocalTimeState;  /**< Indicate if LocalTime is updated and therefore valid, hence can be used without recalculating it. (E_OK | E_NOT_OK) */
  StbM_TimeLeapValidOfLocalTimeStateType TimeLeapValidOfLocalTimeState;  /**< Flag which indicates if the calculated time leap is valid. */
  StbM_InternalTimeStampType GlobalTimeRxOfLocalTimeState;  /**< TGrx (received global time). */
  StbM_InternalTimeStampType GlobalTimeSyncOfLocalTimeState;  /**< TGsync (local time after update). */
  StbM_InternalTimeStampType LocalTimeOfLocalTimeState;  /**< TL (current corrected local time). */
  StbM_InternalTimeStampType LocalTimeSyncOfLocalTimeState;  /**< TLsync (local time before update). */
} StbM_LocalTimeStateType;

/**   \brief  type used in StbM_RateMeasurements */
typedef struct sStbM_RateMeasurementsType
{
  StbM_ValidOfRateMeasurementsType ValidOfRateMeasurements;  /**< True if the measurement is valid. */
  StbM_InternalTimeStampType StartGlobalTimeOfRateMeasurements;  /**< Global time at the start of a measurement. */
  StbM_TimeBaseStatusType StartStatusOfRateMeasurements;  /**< Status of the start time snapshot */
  StbM_InternalVirtualLocalTimeType StartVirtualLocalTimeOfRateMeasurements;  /**< Virtual local time at the start of a measurement. */
  StbM_InternalTimeStampType StopGlobalTimeOfRateMeasurements;  /**< Global time at the stop of a measurement. */
  StbM_TimeBaseStatusType StopStatusOfRateMeasurements;  /**< Status of the stop time snapshot */
  StbM_InternalVirtualLocalTimeType StopVirtualLocalTimeOfRateMeasurements;  /**< Virtual local time at the stop of a measurement. */
} StbM_RateMeasurementsType;

/**   \brief  type used in StbM_Status */
typedef struct sStbM_StatusType
{
  StbM_TimeBaseStatusType GlobalTimeStatusOfStatus;  /**< Status of received global time. */
  StbM_TimeBaseStatusType LocalTimeStatusOfStatus;  /**< Status of local time. */
} StbM_StatusType;

/**   \brief  type used in StbM_TimeBaseConfig */
/*! \spec weak type invariant () { 
 * (self.StatusIdxOfTimeBaseConfig < StbM_GetSizeOfStatus()) &&
 * (self.UserDataStateIdxOfTimeBaseConfig < StbM_GetSizeOfUserDataState()) &&
 * (!((self.LocalTimeConfigIdxOfTimeBaseConfig != STBM_NO_LOCALTIMECONFIGIDXOFTIMEBASECONFIG)) || (self.LocalTimeConfigIdxOfTimeBaseConfig < StbM_GetSizeOfLocalTimeConfig())) &&
 * (!((self.TimeCorrectionSlaveConfigIdxOfTimeBaseConfig != STBM_NO_TIMECORRECTIONSLAVECONFIGIDXOFTIMEBASECONFIG)) || (self.TimeCorrectionSlaveConfigIdxOfTimeBaseConfig < StbM_GetSizeOfTimeCorrectionSlaveConfig())) &&
 * (!((self.TimeoutConfigIdxOfTimeBaseConfig != STBM_NO_TIMEOUTCONFIGIDXOFTIMEBASECONFIG)) || (self.TimeoutConfigIdxOfTimeBaseConfig < StbM_GetSizeOfTimeoutConfig())) &&
 * (!((self.TimeLeapConfigIdxOfTimeBaseConfig != STBM_NO_TIMELEAPCONFIGIDXOFTIMEBASECONFIG)) || (self.TimeLeapConfigIdxOfTimeBaseConfig < StbM_GetSizeOfTimeLeapConfig()))
 * } */
typedef struct sStbM_TimeBaseConfigType
{
  StbM_GlobalTimeMasterOfTimeBaseConfigType GlobalTimeMasterOfTimeBaseConfig;  /**< true if time base has the role of a global time master */
  StbM_SynchronizedTimeBaseOfTimeBaseConfigType SynchronizedTimeBaseOfTimeBaseConfig;  /**< Indicates if the time base is a synchronized time base. */
  StbM_TimeSlaveOfTimeBaseConfigType TimeSlaveOfTimeBaseConfig;  /**< true if timebase has the role of a time slave */
  StbM_LocalTimeConfigIdxOfTimeBaseConfigType LocalTimeConfigIdxOfTimeBaseConfig;  /**< the index of the 0:1 relation pointing to StbM_LocalTimeConfig */
  StbM_StatusIdxOfTimeBaseConfigType StatusIdxOfTimeBaseConfig;  /**< the index of the 1:1 relation pointing to StbM_Status */
  StbM_TimeBaseIdOfTimeBaseConfigType TimeBaseIdOfTimeBaseConfig;  /**< Id of the timebase. */
  StbM_TimeCorrectionSlaveConfigIdxOfTimeBaseConfigType TimeCorrectionSlaveConfigIdxOfTimeBaseConfig;  /**< the index of the 0:1 relation pointing to StbM_TimeCorrectionSlaveConfig */
  StbM_TimeLeapConfigIdxOfTimeBaseConfigType TimeLeapConfigIdxOfTimeBaseConfig;  /**< the index of the 0:1 relation pointing to StbM_TimeLeapConfig */
  StbM_TimeoutConfigIdxOfTimeBaseConfigType TimeoutConfigIdxOfTimeBaseConfig;  /**< the index of the 0:1 relation pointing to StbM_TimeoutConfig */
  StbM_UserDataStateIdxOfTimeBaseConfigType UserDataStateIdxOfTimeBaseConfig;  /**< the index of the 1:1 relation pointing to StbM_UserDataState */
} StbM_TimeBaseConfigType;

/**   \brief  type used in StbM_TimeBaseState */
typedef struct sStbM_TimeBaseStateType
{
  StbM_UpdateCounterOfTimeBaseStateType UpdateCounterOfTimeBaseState;  /**< Actual counter value for immediate time synchronisation. */
} StbM_TimeBaseStateType;

/**   \brief  type used in StbM_TimeCorrectionSlaveConfig */
/*! \spec weak type invariant () { 
 * (self.RateMeasurementsStartIdxOfTimeCorrectionSlaveConfig < StbM_GetSizeOfRateMeasurements()) &&
 * (self.RateMeasurementsEndIdxOfTimeCorrectionSlaveConfig < StbM_GetSizeOfRateMeasurements())
 * } */
typedef struct sStbM_TimeCorrectionSlaveConfigType
{
  StbM_OffsetCorrectionAdaptionIntervalOfTimeCorrectionSlaveConfigType OffsetCorrectionAdaptionIntervalOfTimeCorrectionSlaveConfig;  /**< Defines the interval during which the adaptive rate correction cancels out the rate- and time deviation. */
  StbM_OffsetCorrectionJumpThresholdOfTimeCorrectionSlaveConfigType OffsetCorrectionJumpThresholdOfTimeCorrectionSlaveConfig;  /**< Threshold for the correction method. Deviations below this value will be corrected by a linear reduction over a defined timespan. Values equal- and greater than this value will be corrected by immediately setting the correct time- and rate in form of a jump. */
  StbM_NumberOfSimultaneousRateMeasurementsOfTimeCorrectionSlaveConfigType NumberOfSimultaneousRateMeasurementsOfTimeCorrectionSlaveConfig;  /**< Number of simultaneous rate measurements to determine the current rate deviation. */
  StbM_RateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfigType RateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig;  /**< Nanoseconds part of definition of the time span which is used to calculate the rate deviation. */
  StbM_RateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfigType RateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig;  /**< Seconds part of definition of the time span which is used to calculate the rate deviation. */
  StbM_RateMeasurementsEndIdxOfTimeCorrectionSlaveConfigType RateMeasurementsEndIdxOfTimeCorrectionSlaveConfig;  /**< the end index of the 1:n relation pointing to StbM_RateMeasurements */
  StbM_RateMeasurementsStartIdxOfTimeCorrectionSlaveConfigType RateMeasurementsStartIdxOfTimeCorrectionSlaveConfig;  /**< the start index of the 1:n relation pointing to StbM_RateMeasurements */
  StbM_SingleRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfigType SingleRateCorrectionMeasurementDurationNanosecondsOfTimeCorrectionSlaveConfig;  /**< Nanoseconds part of single duration of measurement: RateCorrectionMeasurementDuration / NumberOfSimultaneousRateMeasurements. */
  StbM_SingleRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfigType SingleRateCorrectionMeasurementDurationSecondsOfTimeCorrectionSlaveConfig;  /**< Seconds part of single duration of measurement: RateCorrectionMeasurementDuration / NumberOfSimultaneousRateMeasurements. */
} StbM_TimeCorrectionSlaveConfigType;

/**   \brief  type used in StbM_TimeCorrectionSlaveState */
typedef struct sStbM_TimeCorrectionSlaveStateType
{
  StbM_OffsetRateCorrectionOfTimeCorrectionSlaveStateType OffsetRateCorrectionOfTimeCorrectionSlaveState;  /**< Current rate for time offset elimination via rate adaption denoted as: r_oc. */
  StbM_RateCorrectionOfTimeCorrectionSlaveStateType RateCorrectionOfTimeCorrectionSlaveState;  /**< Current rate for rate correction denoted as: r_rc. */
  StbM_CurrentRateMeasurementIndexOfTimeCorrectionSlaveStateType CurrentRateMeasurementIndexOfTimeCorrectionSlaveState;  /**< The index of the current used rate measurement storage. */
  StbM_OffsetCorrectionRateValidOfTimeCorrectionSlaveStateType OffsetCorrectionRateValidOfTimeCorrectionSlaveState;  /**< True, if valid offset correction rate has been calculated and shall be applied. */
  StbM_RateDeviationValidOfTimeCorrectionSlaveStateType RateDeviationValidOfTimeCorrectionSlaveState;  /**< True, if at least one valid rate deviation has been calculated. */
} StbM_TimeCorrectionSlaveStateType;

/**   \brief  type used in StbM_TimeLeapConfig */
typedef struct sStbM_TimeLeapConfigType
{
  StbM_FutureThresholdOfTimeLeapConfigType FutureThresholdOfTimeLeapConfig;  /**< Time leap threshold after which a future time leap is detected. */
  StbM_PastThresholdOfTimeLeapConfigType PastThresholdOfTimeLeapConfig;  /**< Time leap threshold after which a past time leap is detected. */
  StbM_ClearCountOfTimeLeapConfigType ClearCountOfTimeLeapConfig;  /**< Counter after which the a time leap is deleted. */
} StbM_TimeLeapConfigType;

/**   \brief  type used in StbM_TimeLeapState */
typedef struct sStbM_TimeLeapStateType
{
  StbM_ClearCountOfTimeLeapStateType ClearCountOfTimeLeapState;  /**< Clear counter to count until a detected timeleap is reset. */
} StbM_TimeLeapStateType;

/**   \brief  type used in StbM_TimeoutConfig */
/*! \spec weak type invariant () { 
 * (self.TimeBaseConfigIdxOfTimeoutConfig < StbM_GetSizeOfTimeBaseConfig())
 * } */
typedef struct sStbM_TimeoutConfigType
{
  StbM_SyncLossTimeoutCounterOfTimeoutConfigType SyncLossTimeoutCounterOfTimeoutConfig;  /**< Represents the amount of main functions until the timeout is expired. Calculated by Timeout(ns)/MainFunction(ns). */
  StbM_TimeBaseConfigIdxOfTimeoutConfigType TimeBaseConfigIdxOfTimeoutConfig;  /**< the index of the 1:1 relation pointing to StbM_TimeBaseConfig */
} StbM_TimeoutConfigType;

/**   \brief  type used in StbM_TimeoutState */
typedef struct sStbM_TimeoutStateType
{
  StbM_SyncLossTimeoutCounterOfTimeoutStateType SyncLossTimeoutCounterOfTimeoutState;  /**< Timeout for the synchronisation of the Time Base. */
} StbM_TimeoutStateType;

/**   \brief  type used in StbM_UserDataState */
typedef struct sStbM_UserDataStateType
{
  StbM_UserDataType UserDataOfUserDataState;  /**< User data. */
} StbM_UserDataStateType;

/**   \brief  type used in StbM_VirtualLocalTimeState */
typedef struct sStbM_VirtualLocalTimeStateType
{
  StbM_InternalVirtualLocalTimeType VirtualLocalTimeOfVirtualLocalTimeState;  /**< TV (current virtual local time). */
  StbM_InternalVirtualLocalTimeType VirtualLocalTimeRxOfVirtualLocalTimeState;  /**< TVrx (received virtual local time). */
  StbM_InternalVirtualLocalTimeType VirtualLocalTimeSyncOfVirtualLocalTimeState;  /**< TVsync (virtual local time at last synchronization event). */
} StbM_VirtualLocalTimeStateType;

/** 
  \}
*/ 

/** 
  \defgroup  StbMPCSymbolicStructTypes  StbM Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to StbM_LocalClockState */
typedef struct StbM_LocalClockStateStructSTag
{
  StbM_LocalClockStateType StbMSynchronizedTimeBase_MAIN0;
  StbM_LocalClockStateType StbMSynchronizedTimeBase_MAIN6;
} StbM_LocalClockStateStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_LocalTimeState */
typedef struct StbM_LocalTimeStateStructSTag
{
  StbM_LocalTimeStateType StbMSynchronizedTimeBase_MAIN0;
  StbM_LocalTimeStateType StbMSynchronizedTimeBase_MAIN6;
} StbM_LocalTimeStateStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_RateMeasurements */
typedef struct StbM_RateMeasurementsStructSTag
{
  StbM_RateMeasurementsType StbMSynchronizedTimeBase_MAIN0;
} StbM_RateMeasurementsStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_Status */
typedef struct StbM_StatusStructSTag
{
  StbM_StatusType StbMSynchronizedTimeBase_MAIN0;
  StbM_StatusType StbMSynchronizedTimeBase_MAIN6;
} StbM_StatusStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_TimeBaseState */
typedef struct StbM_TimeBaseStateStructSTag
{
  StbM_TimeBaseStateType StbMSynchronizedTimeBase_MAIN0;
  StbM_TimeBaseStateType StbMSynchronizedTimeBase_MAIN6;
} StbM_TimeBaseStateStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_TimeCorrectionSlaveState */
typedef struct StbM_TimeCorrectionSlaveStateStructSTag
{
  StbM_TimeCorrectionSlaveStateType StbMSynchronizedTimeBase_MAIN0;
} StbM_TimeCorrectionSlaveStateStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_TimeLeapState */
typedef struct StbM_TimeLeapStateStructSTag
{
  StbM_TimeLeapStateType StbMSynchronizedTimeBase_MAIN0;
} StbM_TimeLeapStateStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_TimeoutState */
typedef struct StbM_TimeoutStateStructSTag
{
  StbM_TimeoutStateType StbMSynchronizedTimeBase_MAIN0;
} StbM_TimeoutStateStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_UserDataState */
typedef struct StbM_UserDataStateStructSTag
{
  StbM_UserDataStateType StbMSynchronizedTimeBase_MAIN0;
  StbM_UserDataStateType StbMSynchronizedTimeBase_MAIN6;
} StbM_UserDataStateStructSType;

/**   \brief  type to be used as symbolic data element access to StbM_VirtualLocalTimeState */
typedef struct StbM_VirtualLocalTimeStateStructSTag
{
  StbM_VirtualLocalTimeStateType StbMSynchronizedTimeBase_MAIN0;
  StbM_VirtualLocalTimeStateType StbMSynchronizedTimeBase_MAIN6;
} StbM_VirtualLocalTimeStateStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  StbMPCUnionIndexAndSymbolTypes  StbM Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access StbM_LocalClockState in an index and symbol based style. */
typedef union StbM_LocalClockStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_LocalClockStateType raw[2];
  StbM_LocalClockStateStructSType str;
} StbM_LocalClockStateUType;

/**   \brief  type to access StbM_LocalTimeState in an index and symbol based style. */
typedef union StbM_LocalTimeStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_LocalTimeStateType raw[2];
  StbM_LocalTimeStateStructSType str;
} StbM_LocalTimeStateUType;

/**   \brief  type to access StbM_RateMeasurements in an index and symbol based style. */
typedef union StbM_RateMeasurementsUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_RateMeasurementsType raw[1];
  StbM_RateMeasurementsStructSType str;
} StbM_RateMeasurementsUType;

/**   \brief  type to access StbM_Status in an index and symbol based style. */
typedef union StbM_StatusUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_StatusType raw[2];
  StbM_StatusStructSType str;
} StbM_StatusUType;

/**   \brief  type to access StbM_TimeBaseState in an index and symbol based style. */
typedef union StbM_TimeBaseStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_TimeBaseStateType raw[2];
  StbM_TimeBaseStateStructSType str;
} StbM_TimeBaseStateUType;

/**   \brief  type to access StbM_TimeCorrectionSlaveState in an index and symbol based style. */
typedef union StbM_TimeCorrectionSlaveStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_TimeCorrectionSlaveStateType raw[1];
  StbM_TimeCorrectionSlaveStateStructSType str;
} StbM_TimeCorrectionSlaveStateUType;

/**   \brief  type to access StbM_TimeLeapState in an index and symbol based style. */
typedef union StbM_TimeLeapStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_TimeLeapStateType raw[1];
  StbM_TimeLeapStateStructSType str;
} StbM_TimeLeapStateUType;

/**   \brief  type to access StbM_TimeoutState in an index and symbol based style. */
typedef union StbM_TimeoutStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_TimeoutStateType raw[1];
  StbM_TimeoutStateStructSType str;
} StbM_TimeoutStateUType;

/**   \brief  type to access StbM_UserDataState in an index and symbol based style. */
typedef union StbM_UserDataStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_UserDataStateType raw[2];
  StbM_UserDataStateStructSType str;
} StbM_UserDataStateUType;

/**   \brief  type to access StbM_VirtualLocalTimeState in an index and symbol based style. */
typedef union StbM_VirtualLocalTimeStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  StbM_VirtualLocalTimeStateType raw[2];
  StbM_VirtualLocalTimeStateStructSType str;
} StbM_VirtualLocalTimeStateUType;

/** 
  \}
*/ 

/** 
  \defgroup  StbMPCRootPointerTypes  StbM Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to StbM_EthClockConfig */
typedef P2CONST(StbM_EthClockConfigType, TYPEDEF, STBM_CONST) StbM_EthClockConfigPtrType;

/**   \brief  type used to point to StbM_Initialized */
typedef P2VAR(StbM_InitializedType, TYPEDEF, STBM_VAR_ZERO_INIT) StbM_InitializedPtrType;

/**   \brief  type used to point to StbM_LocalClockConfig */
typedef P2CONST(StbM_LocalClockConfigType, TYPEDEF, STBM_CONST) StbM_LocalClockConfigPtrType;

/**   \brief  type used to point to StbM_LocalClockState */
typedef P2VAR(StbM_LocalClockStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_LocalClockStatePtrType;

/**   \brief  type used to point to StbM_LocalTimeConfig */
typedef P2CONST(StbM_LocalTimeConfigType, TYPEDEF, STBM_CONST) StbM_LocalTimeConfigPtrType;

/**   \brief  type used to point to StbM_LocalTimeState */
typedef P2VAR(StbM_LocalTimeStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_LocalTimeStatePtrType;

/**   \brief  type used to point to StbM_RateMeasurements */
typedef P2VAR(StbM_RateMeasurementsType, TYPEDEF, STBM_VAR_NOINIT) StbM_RateMeasurementsPtrType;

/**   \brief  type used to point to StbM_Status */
typedef P2VAR(StbM_StatusType, TYPEDEF, STBM_VAR_NOINIT) StbM_StatusPtrType;

/**   \brief  type used to point to StbM_TimeBaseConfig */
typedef P2CONST(StbM_TimeBaseConfigType, TYPEDEF, STBM_CONST) StbM_TimeBaseConfigPtrType;

/**   \brief  type used to point to StbM_TimeBaseState */
typedef P2VAR(StbM_TimeBaseStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_TimeBaseStatePtrType;

/**   \brief  type used to point to StbM_TimeCorrectionSlaveConfig */
typedef P2CONST(StbM_TimeCorrectionSlaveConfigType, TYPEDEF, STBM_CONST) StbM_TimeCorrectionSlaveConfigPtrType;

/**   \brief  type used to point to StbM_TimeCorrectionSlaveState */
typedef P2VAR(StbM_TimeCorrectionSlaveStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_TimeCorrectionSlaveStatePtrType;

/**   \brief  type used to point to StbM_TimeLeapConfig */
typedef P2CONST(StbM_TimeLeapConfigType, TYPEDEF, STBM_CONST) StbM_TimeLeapConfigPtrType;

/**   \brief  type used to point to StbM_TimeLeapState */
typedef P2VAR(StbM_TimeLeapStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_TimeLeapStatePtrType;

/**   \brief  type used to point to StbM_TimeoutConfig */
typedef P2CONST(StbM_TimeoutConfigType, TYPEDEF, STBM_CONST) StbM_TimeoutConfigPtrType;

/**   \brief  type used to point to StbM_TimeoutState */
typedef P2VAR(StbM_TimeoutStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_TimeoutStatePtrType;

/**   \brief  type used to point to StbM_UserDataState */
typedef P2VAR(StbM_UserDataStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_UserDataStatePtrType;

/**   \brief  type used to point to StbM_UserDataOfUserDataState */
typedef P2VAR(StbM_UserDataType, TYPEDEF, STBM_VAR_NOINIT) StbM_UserDataOfUserDataStatePtrType;

/**   \brief  type used to point to StbM_VirtualLocalTimeState */
typedef P2VAR(StbM_VirtualLocalTimeStateType, TYPEDEF, STBM_VAR_NOINIT) StbM_VirtualLocalTimeStatePtrType;

/** 
  \}
*/ 

/** 
  \defgroup  StbMPCRootValueTypes  StbM Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in StbM_PCConfig */
typedef struct sStbM_PCConfigType
{
  uint8 StbM_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} StbM_PCConfigType;

typedef StbM_PCConfigType StbM_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
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
extern CONST(StbM_EthClockConfigType, STBM_CONST) StbM_EthClockConfig[2];
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
extern CONST(StbM_LocalClockConfigType, STBM_CONST) StbM_LocalClockConfig[2];
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
extern CONST(StbM_LocalTimeConfigType, STBM_CONST) StbM_LocalTimeConfig[2];
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
extern CONST(StbM_TimeBaseConfigType, STBM_CONST) StbM_TimeBaseConfig[2];
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
extern CONST(StbM_TimeCorrectionSlaveConfigType, STBM_CONST) StbM_TimeCorrectionSlaveConfig[1];
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
extern CONST(StbM_TimeLeapConfigType, STBM_CONST) StbM_TimeLeapConfig[1];
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
extern CONST(StbM_TimeoutConfigType, STBM_CONST) StbM_TimeoutConfig[1];
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
extern VAR(StbM_InitializedType, STBM_VAR_ZERO_INIT) StbM_Initialized;
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
extern VAR(StbM_LocalClockStateUType, STBM_VAR_NOINIT) StbM_LocalClockState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_LocalTimeStateUType, STBM_VAR_NOINIT) StbM_LocalTimeState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_RateMeasurementsUType, STBM_VAR_NOINIT) StbM_RateMeasurements;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_StatusUType, STBM_VAR_NOINIT) StbM_Status;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_TimeBaseStateUType, STBM_VAR_NOINIT) StbM_TimeBaseState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_TimeCorrectionSlaveStateUType, STBM_VAR_NOINIT) StbM_TimeCorrectionSlaveState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_TimeLeapStateUType, STBM_VAR_NOINIT) StbM_TimeLeapState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_TimeoutStateUType, STBM_VAR_NOINIT) StbM_TimeoutState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_UserDataStateUType, STBM_VAR_NOINIT) StbM_UserDataState;  /* PRQA S 0759 */  /* MD_CSL_Union */
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
extern VAR(StbM_VirtualLocalTimeStateUType, STBM_VAR_NOINIT) StbM_VirtualLocalTimeState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/



#endif  /* STBM_CFG_H */
/**********************************************************************************************************************
 *  END OF FILE: StbM_Cfg.h
 *********************************************************************************************************************/
