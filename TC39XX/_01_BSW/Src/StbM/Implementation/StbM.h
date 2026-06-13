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
/*!        \file  StbM.h
 *        \brief  Vector AUTOSAR StbM header file
 *
 *      \details  This is the main header file of the Vector AUTOSAR module StbM.

 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Stephanie Schaaf              visssf        Vector Informatik GmbH
 *  Anant Gupta                   visgut        Vector Informatik GmbH
 *  Thilo Rachlitz                vistra        Vector Informatik GmbH
 *  Bernd Sigle                   vissi         Vector Informatik GmbH
 *  Giovanni Alessandro Giusa     visgig        Vector Informatik GmbH
 *  Jochen Werling                visjwe        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2012-11-05  visssf  ESCAN00060987 AR4-165: Provide AR4 compliant module StbM
 *  01.01.00  2013-04-12  visssf  ESCAN00066630 Compiler error: Missing FrIf.h when the configuration contains no FlexRay
 *            2013-05-03  visssf  ESCAN00067123 Missing exclusive area protection may lead to data inconsistency
 *  02.00.00  2013-09-06  visssf  ESCAN00070221 Compiler warning: file does not end in newline
 *  03.00.00  2014-09-18  visssf  ESCAN00077484 AR4-664: Support new global time synchronization concept
 *  03.01.00  2014-12-02  visssf  ESCAN00079950 FEAT-971: Complete support of new global time synchronization concept
 *  03.01.01  2015-03-02  visssf  ESCAN00081461 Compiler error: 'Boolean' : name in formal parameter list illegal
 *            2015-03-20  visssf  ESCAN00081652 Wrong calculation of time difference for setting timeleap bit
 *  03.02.00  2015-07-14  visssf  ESCAN00083401 StbM_TimeStampRawType is not compatible to AR 4.2.1
 *  04.00.00  2015-12-22  visssf  ESCAN00085766 FEAT-1531: Support of High Resolution Time Base Reference Clock based on GPT
 *            2016-01-05  visssf  ESCAN00083451 Missing call of EthTSyn_SetGlobalTime() in StbM_SetGlobalTime() if EthTSynHardwareTimestampSupport is set to True
 *  04.01.00  2016-02-26  visssf  ESCAN00088200 FEAT-1694: Support Time Gateway
 *            2016-03-14  visssf  ESCAN00088690 TimeStamp is updated with wrong value when OsCounter is used as local time
 *            2016-03-15  visssf  ESCAN00088923 Missing interrupt locks
 *            2016-03-18  visssf  ESCAN00087326 MISRA deviation: MISRA-C:2004 Rules 12.8, 5.6, 14.3, 16.10, 13.2, 12.1, 12.5, 19.10, 19.7, 12.6 and HIS Metrics
 *            2016-03-30  visssf  ESCAN00089136 TimeBaseStatus is cleared when EthGlobalTimeDomain referenced as local time is in state ETHTSYN_UNCERTAIN
 *            2016-03-30  visssf  ESCAN00089139 SyncScheduleTable is called with <Value> out of range
 *  04.01.01  2016-04-12  visssf  ESCAN00089411 StbM_GetCurrentTimeRaw() and StbM_GetCurrentTimeDiff() return wrong time values
 *            2016-04-13  visssf  ESCAN00089428 SyncScheduleTable is called with <Value> out of range
 *  04.02.00  2017-03-07  visssf  FEATC-644     FEAT-2279: Time Synchronization acc. to AR 4.3 [Feature Pack 1]
 *            2017-03-14  visssf  ESCAN00094362 Already running GPT channel is started again
 *  05.00.00  2017-04-07  visssf  -             No changes, only generator version increased
 *  05.01.00  2017-06-19  visgut  STORYC-1016   Refactor Code taking MISRA into account
 *            2017-06-21  visgut  ESCAN00095102 Offset Time Base can not reference Synchronized Time Base with ID 0
 *            2017-06-21  visssf  STORYC-120    Global Time Precision Measurement Support
 *            2017-06-22  visssf  ESCAN00095043 Time Base gets an invalid status
 *            2017-06-28  visssf  ESCAN00095665 OS API called with disabled interrupts
 *  05.02.00  2017-07-26  visgut  STORYC-122    New Notifications for time expiration events and status changed events
 *            2017-08-02  visssf  STORYC-107    Immediate Time Synchronization
 *            2017-08-15  vistra  STORYC-2200   STORY-2225: Support handling of time leaps according AR 4.3
 *            2017-08-30  visssf  ESCAN00095280 Rate correction factor can not be calculated for time differences bigger than two seconds
 *            2017-08-31  visssf  ESCAN00096484 Overflow not correctly handled
 *            2017-09-01  vistra  ESCAN00093360 Encapsulate optional calls of OS functions
 *  05.03.00  2017-09-19  vistra  STORYC-1351   STORY-130: AR4.3 extensions not covered by separate story
 *            2017-10-12  visssf  STORYC-123    STORY-134: Virtual Local Time / Pure Local Timebase
 *            2017-10-23  visssf  ESCAN00095004 Rate correction uses integer factors
 *            2017-10-25  vistra  ESCAN00097192 Time leap bits are not reset properly
 *  05.04.00  2017-11-16  visssf  ESCAN00097278 Rate correction measurement is erroneously not discarded
 *            2017-11-17  visssf  ESCAN00097454 Compiler warning: unreferenced formal parameter 'customerId'
 *            2017-12-04  vistra  STORYC-2518   STORY-2566: Usage of ComStackLib for StbM
 *            2018-01-11  vistra  STORYC-2498   STORY-2544: SafeBSW for StbM (Step 1)
 *            2018-01-29  visssf  ESCAN00098031 Time Notification Customer is not notified if an alarm expires
 *            2018-02-22  visssf  ESCAN00097488 Conversion between ticks and time not precise enough
 *            2018-03-02  visssf  ESCAN00098557 MISRA deviation: MISRA-C:2004 Rule 16.4
 *            2018-03-09  visssf  ESCAN00097537 Rate correction does not use Virtual Local Time
 *            2018-03-16  visssf  ESCAN00097500 Rate correction uses wrong starting point
 *            2018-03-28  visssf  ESCAN00097091 Improve accuracy of local time
 *  05.05.00  2018-04-25  visssf  ESCAN00099204 Schedule table synchronization counter may jump
 *            2018-04-26  visssf  STORYC-5063   STORY-4924: Support schedule table synchronisation for different counter resolutions
 *            2018-05-27  vissi   STORYC-5072   STORY-4927: Support Measurement (MC Data)
 *            2018-05-04  vistra  ESCAN00099128 Compiler error: value cannot be used to initialize an entity of type "StbM_LocalTimeIDOfTimeBaseConfigType"
 *            2018-05-07  visssf  STORYC-5000   STORY-4846: Support time base specific time difference calculation acc. ASR4.3.1
 *            2018-05-14  vistra  STORYC-5068   STORY-4926: Improve accuracy of the global time by rework of exclusive areas around OS API calls
 *            2018-05-18  visssf  ESCAN00099380 Compiler error: incompatible declaration of functions "StbM_GetRecordTableStartIdx" and "StbM_GetRecordTableEndIdx"
 *  05.06.00  2018-06-15  visssf  ESCAN00099185 Wrong master time value caused by rate correction
 *            2018-07-06  visssf  ESCAN00099911 Compiler error: Cannot open include file 'Det.h'
 *  05.07.00  2018-08-10  visssf  ESCAN00100318 StbM_GetCurrentTime() does not return the current time base status
 *            2018-08-13  visssf  ESCAN00100107 Compiler warning: unreferenced formal parameter 'timeBaseId'
 *            2018-08-13  vistra  STORYC-6054   STORY-7100: [GTS] StbM shall avoid accessing an uncertain Ethernet clock source
 *            2018-08-16  vistra  ESCAN00100402 Compiler warning: unused variable 'elapsedCounterValue'
 *            2018-08-17  visssf  ESCAN00100279 Value range of StbMRateCorrectionMeasurementDuration too limited
 *            2018-08-21  vistra  ESCAN00100403 Compiler warning: function declared 'static' but never defined
 *  05.08.00  2018-09-05  visssf  STORYC-6148   STORY-7249: Increase code coverage of StbM
 *            2018-09-25  vistra  STORYC-6397   STORY-4942: MISRA-C2012: SysService_AsrStbM
 *            2018-09-28  visssf  ESCAN00100874 Rate correction of master time never applied
 *            2018-10-02  visssf  ESCAN00100878 Wrong calculation of rate corrected master time for offset time bases
 *  05.08.01  2018-10-30  visssf  ESCAN00101186 StbM_GetRateDeviation() shall be available for Offset Time Bases
 *            2018-11-16  visssf  ESCAN00101309 Error during re-adjustment of expire time not reported via return value
 *            2018-12-13  visgig  STORYC-6147   STORY-7248: Fix open review and safety check findings of previous releases
 *            2018-12-19  visgig  ESCAN00101588 Linker error: unresolved external symbol "StbM_CheckAndSetRatecorrectionEv"
 *            2019-01-18  vistra  ESCAN00101604 Rate correction measurement erroneously dropped after timeout
 *            2019-01-18  vistra  ESCAN00101614 Even distribution of parallel rate correction measurements can be destroyed
 *  06.00.00  2019-02-15  visgig  STORYC-6931   STORY-8704: Support functional safety
 *            2019-04-29  visgig  ESCAN00102854 Synchronization of OS Schedule Tables is not working properly for Offset Time Bases
 *            2019-06-05  vistra  ESCAN00102187 Time leap checks don't consider Time Correction
 *            2019-06-05  vistra  ESCAN00102183 Time Recording without applied Time Correction
 *            2019-06-13  vistra  ESCAN00103378 Triggered Customers don't consider Time Correction
 *            2019-09-05  visgig  STORYC-8104   STORY-11754: Rework of StbM with unit structure
 *  06.00.01  2019-10-31  visgig  ESCAN00104700 StbM_GetRateDeviation and StbM_SetRateCorrection do not convert rate to ppm format
 *            2019-11-06  visgig  ESCAN00104814 Jump correction not applied correctly
 *            2019-11-11  visgig  ESCAN00104845 Missing exclusive areas during update of Timeout, TriggeredCustomer, TimeNotification and TimeRecording
 *            2019-11-11  visgig  ESCAN00104847 Activation of task for calling StbM_NotificationFunction is done more than one time when one timer needs to be called immediately during the process of StbM_TimerCallback
 *  07.00.00  2020-01-20  visgig  ESCAN00105384 TSYNC-1191: Offset time calculation affects time calculation of referred synchronized timebase
 *            2020-01-28  visgig  ESCAN00105501 StbM_SetRateCorrection sets the given rate before the synchronization event is captured
 *            2020-01-28  visgig  ESCAN00105502 StbM_GetTimeLeap returns E_OK before second invocation of StbM_BusSetGlobalTime
 *            2020-01-28  visgig  ESCAN00105445 No negative deviations for Time Notification Customers
 *            2020-01-28  visgig  ESCAN00105451 Exceeding deviation time handling of Time Notification Customer
 *            2020-01-31  visssf  MSR4-193      Enhance precision of Global Time (AR RfC 79959)
 *            2020-01-31  visgig  ESCAN00105503 Block content of Time Recording is not correct
 *            2020-01-31  visgig  ESCAN00105534 StbM_GetOffset returns wrong timebase status
 *            2020-02-03  visgig  ESCAN00105094 StbM might not  reported time recorded blocks properly
 *            2020-02-17  visssf  ESCAN00105629 Wrong calculation of rate corrected time for offset time bases
 *            2020-03-28  visgig  ESCAN00105966 Initialization of StbM clock info with reference to the local time hardware using ethernet is not working properly
 *  08.00.00  2020-04-07  visjwe  MSR4-29714    [GTS] SafeCarTime acc. to BugZilla RfC 77436 for Ethernet UseCase (Beta)
 *  08.01.00  2020-06-10  visjwe  MSR4-1394     [GTS] SafeCarTime acc. to BugZilla RfC 77436 for Ethernet UseCase (Production)
 *            2020-06-15  visjwe  TSYNC-1425    Rework QAC justifications for Helix QAC 2019-2
 *            2020-06-26  visgig  ESCAN00106637 Schedule table synchronization fails for times greater than 4294967295 microseconds.
 *            2020-07-30  visgig  ESCAN00106982 Virtual Local Time should be the same as the raw clock source time in case of ethernet based clock source.
 *            2020-08-05  visgig  ESCAN00107049 Incorrect offset in virtual local time before first synchronization event
 *            2020-08-19  visgig  MSR4-30311    Make StbM postbuild selectable (and loadable only for AMSR)
 *            2020-08-27  visgig  ESCAN00107219 Usage of wrong literal for long long unsigned integer constant for Time Correction
 *********************************************************************************************************************/

#if !defined (STBM_H)
# define STBM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "StbM_Cfg.h"

# if (STBM_CONFIG_TIME_VALIDATION_ETH_MASTER == STD_ON || STBM_CONFIG_TIME_VALIDATION_ETH_SLAVE == STD_ON)
#  include "StbM_EthTSyn.h"
# endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Vendor and module identification */
# define STBM_VENDOR_ID                                (30U)
# define STBM_MODULE_ID                                (0xA0U)

/* AUTOSAR Software specification version information */
# define STBM_AR_RELEASE_MAJOR_VERSION                 (0x04U)
# define STBM_AR_RELEASE_MINOR_VERSION                 (0x05U)
# define STBM_AR_RELEASE_REVISION_VERSION              (0x00U)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define STBM_SW_MAJOR_VERSION                         (8U)
# define STBM_SW_MINOR_VERSION                         (1U)
# define STBM_SW_PATCH_VERSION                         (0U)

/* ----- API service IDs ----- */
# define STBM_SID_INIT                                 (0x00U)  /* !< Service ID: StbM_Init(StbM_Config_Ptr) */
# define STBM_SID_MAIN_FUNCTION                        (0x04U)  /* !< Service ID: StbM_MainFunction() */
# define STBM_SID_GET_VERSION_INFO                     (0x05U)  /* !< Service ID: StbM_GetVersionInfo() */
# define STBM_SID_GET_CURRENT_TIME                     (0x07U)  /* !< Service ID: StbM_GetCurrentTime() */
# define STBM_SID_GET_CURRENT_TIME_EXTENDED            (0x08U)  /* !< Service ID: StbM_GetCurrentTimeExtended() */
# define STBM_SID_SET_GLOBAL_TIME                      (0x0BU)  /* !< Service ID: StbM_SetGlobalTime() */
# define STBM_SID_SET_USER_DATA                        (0x0CU)  /* !< Service ID: StbM_SetUserData() */
# define STBM_SID_SET_OFFSET                           (0x0DU)  /* !< Service ID: StbM_SetOffset() */
# define STBM_SID_GET_OFFSET                           (0x0EU)  /* !< Service ID: StbM_GetOffset() */
# define STBM_SID_BUS_SET_GLOBAL_TIME                  (0x0FU)  /* !< Service ID: StbM_BusSetGlobalTime() */
# define STBM_SID_UPDATE_GLOBAL_TIME                   (0x10U)  /* !< Service ID: StbM_UpdateGlobalTime() */
# define STBM_SID_GET_RATE_DEVIATION                   (0x11U)  /* !< Service ID: StbM_GetRateDeviation() */
# define STBM_SID_SET_RATE_CORRECTION                  (0x12U)  /* !< Service ID: StbM_SetRateCorrection() */
# define STBM_SID_GET_TIMELEAP                         (0x13U)  /* !< Service ID: StbM_GetTimeLeap() */
# define STBM_SID_GET_TIME_BASE_STATUS                 (0x14U)  /* !< Service ID: StbM_GetTimeBaseStatus() */
# define STBM_SID_START_TIMER                          (0x15U)  /* !< Service ID: StbM_StartTimer() */
# define STBM_SID_GET_SYNC_TIME_RECORD_HEAD            (0x16U)  /* !< Service ID: StbM_GetSyncTimeRecordHead() */
# define STBM_SID_GET_OFFSET_TIME_RECORD_HEAD          (0x17U)  /* !< Service ID: StbM_GetOffsetTimeRecordHead() */
# define STBM_SID_GET_TIME_BASE_UPDATE_COUNTER         (0x1BU)  /* !< Service ID: StbM_GetTimeBaseUpdateCounter() */
# define STBM_SID_TRIGGER_TIME_TRANSMISSION            (0x1CU)  /* !< Service ID: StbM_TriggerTimeTransmission() */
# define STBM_SID_GET_MASTER_CONFIG                    (0x1DU)  /* !< Service ID: StbM_GetMasterConfig() */
# define STBM_SID_GET_CURRENT_VIRTUAL_LOCAL_TIME       (0x1EU)  /* !< Service ID: StbM_GetCurrentVirtualLocalTime() */
# define STBM_SID_BUS_GET_CURRENT_TIME                 (0x1FU)  /* !< Service ID: StbM_BusGetCurrentTime() */
# define STBM_SID_ETH_SET_MASTER_TIMINIG_DATA          (0x22U)  /* !< Service ID: StbM_EthSetMasterTimingData() */
# define STBM_SID_ETH_SET_PDELAY_INITIATOR_DATA        (0x23U)  /* !< Service ID: StbM_EthSetPdelayInitiatorData() */
# define STBM_SID_ETH_SET_PDELAY_RESPONDER_DATA        (0x24U)  /* !< Service ID: StbM_EthSetPdelayResponderData() */
# define STBM_SID_ETH_SET_SLAVE_TIMING_DATA            (0x28U)  /* !< Service ID: StbM_EthSetSlaveTimingData() */

/* ----- Error codes ----- */
# define STBM_E_NO_ERROR                               (0x00U)  /* !< used to check if no error occurred */
# define STBM_E_INIT_FAILED                            (0x11U)  /* !< Error code: API service called with an invalid configuration pointer */
# define STBM_E_PARAM                                  (0x0AU)  /* !< Error code: API service called with wrong parameter */
# define STBM_E_UNINIT                                 (0x0BU)  /* !< Error code: API service used without module initialization */
# define STBM_E_NOT_INITIALIZED                        (0x0BU)  /* !< Error code: API service used without module initialization */ /* for compatibility until AR 4.3.x */
# define STBM_E_PARAM_POINTER                          (0x10U)  /* !< Error code: API service called with NULL_PTR as parameter */
# define STBM_E_SERVICE_DISABLED                       (0x12U)  /* !< Error code: API service called that is disabled by configuration */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define STBM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if(STBM_USE_INIT_POINTER == STD_ON)
extern P2CONST(StbM_ConfigType, STBM_VAR_ZERO_INIT, STBM_INIT_DATA) StbM_ConfigDataPtr;
#endif

#define STBM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define STBM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  StbM_InitMemory
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function can be used to initialize the
 *               variables in *_INIT_* sections in case they are not initialized by the startup code.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
**********************************************************************************************************************/
FUNC(void, STBM_CODE) StbM_InitMemory(void);

/**********************************************************************************************************************
 *  StbM_Init
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module StbM. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   ConfigPtr    Component configuration structure
 *  \pre         Interrupts are disabled and StbM_InitMemory has been called if required.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
FUNC(void, STBM_CODE) StbM_Init(P2CONST(StbM_ConfigType, AUTOMATIC, STBM_INIT_DATA) ConfigPtr);

/**********************************************************************************************************************
 *  StbM_MainFunction
 *********************************************************************************************************************/
/*! \brief       Main function
 *  \details     This function gets time information from providers and triggers customers.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* The StbM_MainFunction definition is localized in StbM.c. The declaration is realized by RTE */

# if (STBM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetVersionInfo
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     StbM_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo             Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      STBM_VERSION_INFO_API
 *  \trace       CREQ-126467
 *********************************************************************************************************************/
FUNC(void, STBM_CODE) StbM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, STBM_APPL_VAR) versioninfo);
# endif /* (STBM_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 *  StbM_GetCurrentTime
 *********************************************************************************************************************/
/*! \brief       Returns the current time in standard format
 *  \details     This function returns the current time of the submitted time-base in standard format.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is of interest.
 *  \param[out]  timeStampPtr            Current time stamp in standard format.
 *  \param[out]  userDataPtr             User data of the time base.
 *  \return      E_OK     - Timestamp is valid
 *  \return      E_NOT_OK - Timestamp is invalid
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
        P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr);

/**********************************************************************************************************************
 *  StbM_GetCurrentVirtualLocalTime
 *********************************************************************************************************************/
/*! \brief       Returns the Virtual Local Time of the referenced Time Base
 *  \details     This function returns the virtual local time of the submitted time-base.
 *  \param[in]   timeBaseId             The synchronized time-base, whose Virtual Local Time is of interest.
 *  \param[out]  localTimePtr           Current Virtual Local Time value.
 *  \return      E_OK     - Virtual Local Time is valid
 *  \return      E_NOT_OK - Virtual Local Time is invalid
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTime(
        StbM_SynchronizedTimeBaseType timeBaseId,
        P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_VAR) localTimePtr);

# if (STBM_GET_CURRENT_TIME_EXTENDED_API == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetCurrentTimeExtended
 *********************************************************************************************************************/
/*! \brief       Returns the current time in extended format
 *  \details     This function returns the current time of the submitted time-base in extended format.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is of interest.
 *  \param[out]  timeStampPtr            Current time stamp in extended format.
 *  \param[out]  userDataPtr             User data of the time base.
 *  \return      E_OK     - Timestamp is valid
 *  \return      E_NOT_OK - Timestamp is invalid
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_GET_CURRENT_TIME_EXTENDED_API
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeExtended(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_TimeStampExtendedType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
        P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr);
# endif /* (STBM_GET_CURRENT_TIME_EXTENDED_API == STD_ON) */

# if (STBM_CONFIG_GLOBAL_TIME_MASTER == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetGlobalTime
 *********************************************************************************************************************/
/*! \brief       Sets new global time
 *  \details     This function allows the customers to set the new global time.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \param[in]   userDataPtr             Valid pointer to new user data or NULL_PTR if user data shall not be updated
 *  \return      E_OK     - New global time was set
 *  \return      E_NOT_OK - New global time was not set
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_GLOBAL_TIME_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
        P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr);

/**********************************************************************************************************************
 *  StbM_UpdateGlobalTime
 *********************************************************************************************************************/
/*! \brief       Sets new global time
 *  \details     This function allows the customers to set the new global time without leading to an immediate transmission of the global time.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStamp               New time stamp.
 *  \param[in]   userData                New user data.
 *  \return      E_OK     - New global time was set
 *  \return      E_NOT_OK - New global time was not set
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_GLOBAL_TIME_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
        P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData);

/**********************************************************************************************************************
 *  StbM_SetUserData
 *********************************************************************************************************************/
/*! \brief       Sets new user data
 *  \details     This function allows the customers to set the new user data.
 *  \param[in]   timeBaseId              The synchronized time-base, whose user data is set.
 *  \param[in]   userDataPtr             New user data.
 *  \return      E_OK     - New user data was set
 *  \return      E_NOT_OK - New user data was not set
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_GLOBAL_TIME_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_SetUserData(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr);

/**********************************************************************************************************************
 *  StbM_SetRateCorrection
 *********************************************************************************************************************/
/*! \brief       Sets rate of a time base
 *  \details     This function allows the customers to set the rate of a synchronized time base.
 *  \param[in]   timeBaseId              The synchronized time-base, whose rate is set.
 *  \param[in]   rateDeviation           New rate.
 *  \return      E_OK     - New rate was set
 *  \return      E_NOT_OK - New rate was not set
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_GLOBAL_TIME_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_SetRateCorrection(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        StbM_RateDeviationType rateDeviation);

/**********************************************************************************************************************
 *  StbM_TriggerTimeTransmission
 *********************************************************************************************************************/
/*! \brief       Increments the update counter of a time base
 *  \details     This function allows the customers to force the Timesync module to transmit the time base again due to an incremented timeBaseUpdateCounter.
 *  \param[in]   timeBaseId               The time-base, whose update counter shall be incremented.
 *  \return      E_OK     - Update counter was incremented
 *               E_NOT_OK - Update counter was not incremented
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_GLOBAL_TIME_MASTER
 ********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_TriggerTimeTransmission(StbM_SynchronizedTimeBaseType timeBaseId); /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */

# if (STBM_HAS_ALLOW_SYSTEM_WIDE_GLOBAL_TIME_MASTER == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetMasterConfig
 *********************************************************************************************************************/
/*! \brief       Check if the given timebase of the current config is a global time master.
 *  \details     Indicates if master API is available in the current config for the given timebase.
 *  \param[in]   timeBaseId              The synchronized timebase, whose role is requested.
 *  \param[out]  masterConfig            STBM_SYSTEM_WIDE_MASTER_ENABLED if the ECU is configured as system wide
 *                                       global time master for the given timebase and STBM_SYSTEM_WIDE_MASTER_DISABLED
 *                                       otherwise.
 *  \return      E_OK     - timebase role was retrieved successfully
 *  \return      E_NOT_OK - failed occurred during timebase role retrieval
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_GLOBAL_TIME_MASTER && STBM_HAS_ALLOW_SYSTEM_WIDE_GLOBAL_TIME_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetMasterConfig(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_MasterConfigType, AUTOMATIC, STBM_APPL_VAR) masterConfig);
# endif /* STBM_HAS_ALLOW_SYSTEM_WIDE_GLOBAL_TIME_MASTER == STD_ON */

#  if (STBM_CONFIG_OFFSET_TIMEBASE == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetOffset
 *********************************************************************************************************************/
/*! \brief       Sets the offset time
 *  \details     This function allows the customers and the time base provider modules to set the offset time.
 *  \param[in]   timeBaseId              The synchronized time-base, whose offset time is set.
 *  \param[in]   timeStampPtr            New offset time stamp.
 *  \return      E_OK     - New offset time was set
 *  \return      E_NOT_OK - New offset time was not set
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_OFFSET_TIMEBASE && STBM_CONFIG_GLOBAL_TIME_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_SetOffset(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#  endif /* (STBM_CONFIG_OFFSET_TIMEBASE == STD_ON) */
# endif /* (STBM_CONFIG_GLOBAL_TIME_MASTER == STD_ON) */

# if ((STBM_CONFIG_GLOBAL_TIME_MASTER == STD_ON) || (STBM_CONFIG_GATEWAY == STD_ON))
/**********************************************************************************************************************
*  StbM_BusGetCurrentTime
*********************************************************************************************************************/
/*! \brief       Returns the current Time Tuple, status and User Data of the Time Base
 *  \details     This function allows the time base provider modules to get the current Time Tuple, status and User Data of the Time Base.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is of interest.
 *  \param[out]  globalTimePtr           Value of the local instance of the Global Time, which is sampled when the function is called.
 *  \param[out]  localTimePtr            Value of the Virtual Local Time, which is sampled when the function is called.
 *  \param[out]  userData                User Data of the Time Base.
 *  \return      E_OK     - Timestamps are valid
 *  \return      E_NOT_OK - Timestamps are invalid
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_GLOBAL_TIME_MASTER || STBM_CONFIG_GATEWAY
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_BusGetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId,
        P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) globalTimePtr,
        P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_VAR) localTimePtr,
        P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userData);
# endif /* ((STBM_CONFIG_GLOBAL_TIME_MASTER == STD_ON) || (STBM_CONFIG_GATEWAY == STD_ON)) */

# if (STBM_CONFIG_OFFSET_TIMEBASE == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetOffset
 *********************************************************************************************************************/
/*! \brief       Returns the current offset time
 *  \details     This function allows the time base provider modules to get the current offset time.
 *  \param[in]   timeBaseId              The synchronized time-base, whose offset time is of interest.
 *  \param[out]  timeStampPtr            Current offset time stamp.
 *  \return      E_OK     - Timestamp is valid
 *  \return      E_NOT_OK - Timestamp is invalid
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_OFFSET_TIMEBASE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffset(StbM_SynchronizedTimeBaseType timeBaseId,
        P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr);
# endif /* (STBM_CONFIG_OFFSET_TIMEBASE == STD_ON) */

# if (STBM_CONFIG_TIME_SLAVE == STD_ON)
/**********************************************************************************************************************
 *  StbM_BusSetGlobalTime
 *********************************************************************************************************************/
/*! \brief       Sets new global time
 *  \details     This function allows the time base provider modules to set the new global time.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   globalTimePtr           New global time value.
 *  \param[in]   userDataPtr             Valid pointer to new user data or NULL_PTR if user data shall not be updated.
 *  \param[in]   measureDataPtr          New measurement data.
 *  \param[in]   localTimePtr            Value of the Virtual Local Time associated to the new Global Time.
 *  \return      E_OK     - New global time was set
 *  \return      E_NOT_OK - New global time was not set
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_SLAVE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_BusSetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId,
        P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) globalTimePtr,
        P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
        P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr,
        P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA) localTimePtr);

/**********************************************************************************************************************
 *  StbM_GetTimeLeap
 *********************************************************************************************************************/
/*! \brief       Returns the value of the last time leap
 *  \details     This function allows the customers to get the value of Time Leap, if StbMTimeLeapFuture/PastThreshold is exceeded.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time leap is of interest.
 *  \param[out]  timeJump                Time leap value.
 *  \return      E_OK     - Time leap is valid.
 *  \return      E_NOT_OK - No Time leap occurred or time leap is out of range.
 *  \pre         Application has to ensure that the TIMELEAP_FUTURE or TIMELEAP_PAST bit within timebase status has been set.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_SLAVE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeLeap(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_TimeDiffType, AUTOMATIC, STBM_APPL_VAR) timeJump);
# endif /* (STBM_CONFIG_TIME_SLAVE == STD_ON) */

/**********************************************************************************************************************
 *  StbM_GetRateDeviation
 *********************************************************************************************************************/
/*! \brief       Returns the current rate deviation
 *  \details     This function allows the customers to get the current rate deviation.
 *  \param[in]   timeBaseId              The synchronized time-base, whose rate deviation is of interest.
 *  \param[out]  rateDeviation           Current rate deviation.
 *  \return      E_OK     - Rate deviation is valid
 *  \return      E_NOT_OK - Rate deviation is invalid
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetRateDeviation(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_RateDeviationType, AUTOMATIC, STBM_APPL_VAR) rateDeviation);

# if (STBM_CONFIG_TIME_RECORDING == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetSyncTimeRecordHead
 *********************************************************************************************************************/
/*! \brief       Accesses the header of a synchronized time base
 *  \details     This function allows the customers to access the recorded snapshot data header of the table belonging to the Synchronized Time Base.
 *  \param[in]   timeBaseId              The synchronized time-base, whose header is of interest.
 *  \param[out]  syncRecordTableHead     Header of the recorded snapshot data.
 *  \return      E_OK     - Table access done
 *  \return      E_NOT_OK - Table contains no data or access invalid
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_RECORDING
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetSyncTimeRecordHead(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_SyncRecordTableHeadType, AUTOMATIC, STBM_APPL_VAR) syncRecordTableHead);
# endif /* (STBM_CONFIG_TIME_RECORDING == STD_ON) */

# if (STBM_CONFIG_TIME_RECORDING_OFFSET == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetOffsetTimeRecordHead
 *********************************************************************************************************************/
/*! \brief       Accesses the header of an offset time base
 *  \details     This function allows the customers to access the recorded snapshot data header of the table belonging to the Offset Time Base.
 *  \param[in]   timeBaseId              The offset time-base, whose header is of interest.
 *  \param[out]  offsetRecordTableHead   Header of the recorded snapshot data.
 *  \return      E_OK     - Table access done
 *  \return      E_NOT_OK - Table contains no data or access invalid
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_RECORDING_OFFSET
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffsetTimeRecordHead(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_OffsetRecordTableHeadType, AUTOMATIC, STBM_APPL_VAR) offsetRecordTableHead);
# endif /* (STBM_CONFIG_TIME_RECORDING_OFFSET == STD_ON) */

# if (STBM_CONFIG_TIME_NOTIFICATION == STD_ON)
/**********************************************************************************************************************
 *  StbM_StartTimer
 *********************************************************************************************************************/
/*! \brief       Sets a time value, which the Time Base value is compared against
 *  \details     Starts a timer for a Time Base
 *  \param[in]   timeBaseId       Time Base reference
 *  \param[in]   customerId       Id of customer
 *  \param[in]   expireTime       Time value relative to current Time Base value of the Notification Customer,
 *                                when the Timer shall expire
 *  \return      E_OK       -     successful
 *               E_NOT_OK   -     failed
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_NOTIFICATION
 ********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_StartTimer(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        StbM_CustomerIdType customerId,
        P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) expireTime);

/**********************************************************************************************************************
 *  StbM_NotificationFunction
 *********************************************************************************************************************/
/*! \brief       Invokes the callback function of time notification customers
 *  \details     This function invokes the callback functions of all the time notification customers, whose timer has expired.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_NOTIFICATION
 *******************************************************************************************************************/
/* The StbM_NotificationFunction definition is localized in StbM.c. The declaration is realized by RTE */
# endif /* (STBM_CONFIG_TIME_NOTIFICATION == STD_ON) */

/**********************************************************************************************************************
 *  StbM_GetTimeBaseUpdateCounter
 *********************************************************************************************************************/
/*! \brief       Indicates if a time base has been updated
 *  \details     This function allows the Timesync modules to detect, whether a time base should be transmitted immediately in the subsequent <Bus>TSyn_MainFunction() cycle.
 *  \param[in]   timeBaseId               The time-base, whose update counter is of interest.
 *  \return      counter value - Counter value belonging to the time base, that indicates a time base update to the Timesync modules.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 ********************************************************************************************************************/
FUNC(uint8, STBM_CODE) StbM_GetTimeBaseUpdateCounter(StbM_SynchronizedTimeBaseType timeBaseId);

/**********************************************************************************************************************
 *  StbM_GetTimeBaseStatus
 *********************************************************************************************************************/
/*! \brief       Returns the detailed status of the Time Base.
 *  \details     This function allows the customers to get the status of a Time Base. For Offset Time Bases the
                 status of the underlying Synchronized Time Base is also returned.
 *  \param[in]   timeBaseId              The Time Base, whose status is of interest.
 *  \param[out]  syncTimeBaseStatus      Status of the Synchronized Time Base.
 *  \param[out]  offsetTimeBaseStatus    Status of the Offset Time Base.
 *  \return      E_OK     - Status is valid.
 *  \return      E_NOT_OK - No status could be retrieved.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeBaseStatus(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 3449, 3451 */ /* MD_StbM_Rule8.5_3449, MD_StbM_Rule8.5_3451 */
        P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_VAR) syncTimeBaseStatus,
        P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_VAR) offsetTimeBaseStatus);

# define STBM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

/*!
* \exclusivearea STBM_EXCLUSIVE_AREA_0
* Ensures consistency of global RAM variables.
* \protects All affected global RAM variables.
* \usedin StbM_GetCurrentTime, StbM_GetCurrentTimeExtended, StbM_GetCurrentVirtualLocalTime, StbM_BusGetCurrentTime,
*         StbM_SetGlobalTime, StbM_SetUserData, StbM_SetOffset, StbM_GetOffset, StbM_BusSetGlobalTime, StbM_GetRateDeviation,
*         StbM_GetSyncTimeRecordHead, StbM_GetOffsetTimeRecordHead, StbM_NotificationFunction, StbM_TimerCallback, StbM_StartTimer, StbM_StatusNotification_NotifyCustomers,
*         StbM_MainFunction, StbM_Timeout_Update, StbM_TimeRecording_NotifyCustomers, StbM_TimeValidation_NotifyEthMasterCustomers, StbM_TimeValidation_NotifyEthSlaveCustomers,
*         StbM_EthSetMasterTimingData, StbM_EthSetSlaveTimingData, StbM_EthSetPdelayInitiatorData, StbM_EthSetPdelayResponderData
* \exclude All functions provided by StbM.
* \length SHORT depending on the API and the call graph.
* \endexclusivearea
*/

#endif /* STBM_H */

/**********************************************************************************************************************
 *  END OF FILE: StbM.h
 *********************************************************************************************************************/
