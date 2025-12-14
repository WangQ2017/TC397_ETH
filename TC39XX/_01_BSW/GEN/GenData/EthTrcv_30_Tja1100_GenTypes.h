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
 *            Module: EthTrcv_30_Tja1100
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthTrcv_30_Tja1100_GenTypes.h
 *   Generation Time: 2025-12-14 15:58:18
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/



#if !defined (ETHTRCV_30_TJA1100_GENTYPES_H)
# define ETHTRCV_30_TJA1100_GENTYPES_H

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_Cfg.h"
# include "EthTrcv_30_Tja1100_Types.h"
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA TYPES AND STRUCTURES (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/** 
  \defgroup  EthTrcv_30_Tja1100PCNonComStackLibTypes  EthTrcv_30_Tja1100 Non ComStackLib Types (PRE_COMPILE)
  \brief  These type definitions are provided by the EthTrcv_30_Tja1100 itself.
  \{
*/ 

/**   \brief  bitfield type defintion for wakeup reason recognition */
typedef uint8 EthTrcv_30_Tja1100_WakeupReasonFlagsType;

/**   \brief  function pointer type defintion for register read accesses */
typedef P2FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_ReadTrcvRegFctPtrType)(uint8, uint8, uint8, P2VAR(uint16, AUTOMATIC, AUTOMATIC));

/**   \brief  function pointer type defintion for register write accesses */
typedef P2FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_WriteTrcvRegFctPtrType)(uint8, uint8, uint8, uint16);

/**   \brief  function pointer type defintion for <User>_PreTransceiverInitCallout() */
typedef P2FUNC(void,           ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_UserPreTrcvInitCalloutFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_PostTransceiverInitCallout() */
typedef P2FUNC(void,           ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_UserPostTrcvInitCalloutFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_WakeupCallout() */
typedef P2FUNC(void,           ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_UserWakeupCalloutFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_WakeupVerificationCallout() */
typedef P2FUNC(void,           ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_UserWakeupVerificationCalloutFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_HwAccessMonitorFailureCalloutFctPtrType() */
typedef P2FUNC(void,           ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_UserHwAccessMonitorFailureCalloutFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_PreTrcvReadCalloutsFctPtrType() */
typedef P2FUNC(void,           ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_UserPreTrcvReadCalloutsFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_PreTrcvWriteCalloutsFctPtrType() */
typedef P2FUNC(void,           ETHTRCV_30_TJA1100_APPL_CODE, EthTrcv_30_Tja1100_UserPreTrcvWriteCalloutsFctPtrType)(uint8);



/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  EthTrcv_30_Tja1100PCDataSwitches  EthTrcv_30_Tja1100 Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define ETHTRCV_30_TJA1100_ACCESSENTITYFCTS                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_READTRCVREGOFACCESSENTITYFCTS              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WRITETRCVREGOFACCESSENTITYFCTS             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_CABLEDIAGLOOPCYCLES                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ETHTRCV                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ACCESSENTITYFCTSIDXOFETHTRCV               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ACCESSENTITYSNVOFETHTRCV                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ADDRESSINGIDXOFETHTRCV                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_AUTONEGENABLEDOFETHTRCV                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_BASICCTRLREGVALOFETHTRCV                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_CONNECTIONNEGOFETHTRCV                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_DEMEACCESSEVENTIDOFETHTRCV                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_MIIMODEOFETHTRCV                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_PHYSIGNALQUALITYMEANOFETHTRCV              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SOCBASEREGADDROFETHTRCV                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SOFTRESETONINITENABLEDOFETHTRCV            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SOFTRESETWAITCYCLESOFETHTRCV               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SPEEDOFETHTRCV                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPIDXOFETHTRCV                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPUSEDOFETHTRCV                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ETHTRCVTJA1100                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_CLKMODEOFETHTRCVTJA1100                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_DERIVATIVEOFETHTRCVTJA1100                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_EXTLINKSTATECHECKENABLEDOFETHTRCVTJA1100   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_INTREVMIIOFETHTRCVTJA1100                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LDOMODEOFETHTRCVTJA1100                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKFAILCOUNTERRESETVALOFETHTRCVTJA1100    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTARTUPDELAYOFETHTRCVTJA1100           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_P0MIIADDRESSOFETHTRCVTJA1100               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_P0PORTSNVOFETHTRCVTJA1100                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_P0SWITCHSNVOFETHTRCVTJA1100                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_PHYENABLEOFETHTRCVTJA1100                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_FINALMAGICNUMBER                           STD_OFF  /**< Deactivateable: 'EthTrcv_30_Tja1100_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTRCV_30_TJA1100_HWACCESSLOOPCOUNT                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORCYCLECOUNTER                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORFAILURECALLOUT              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORFAILUREDEBOUNCECOUNTER      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORFAILUREDEBOUNCELIMITER      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORLOOPLIMITER                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORRECOVERYDEBOUNCECOUNTER     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORRECOVERYDEBOUNCELIMITER     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_INITDATAHASHCODE                           STD_OFF  /**< Deactivateable: 'EthTrcv_30_Tja1100_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTRCV_30_TJA1100_LINKFAILCOUNTER                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTARTUPDELAYCOUNTER                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTARTUPSTATE                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTATEDELAYCOUNTER                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTATETIMEOUTCOUNTER                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_MAINFUNCTIONLINKHANDLINGMS                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_MAXPHYSIGNALQUALITYMEAN                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFACCESSENTITYFCTS                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFETHTRCV                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFETHTRCVTJA1100                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFHWACCESSMONITORFAILURECALLOUT        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFHWACCESSMONITORFAILUREDEBOUNCECOUNTER STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFHWACCESSMONITORRECOVERYDEBOUNCECOUNTER STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKFAILCOUNTER                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTARTUPDELAYCOUNTER              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTARTUPSTATE                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTATEDELAYCOUNTER                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTATETIMEOUTCOUNTER              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVHWACCESSIBILITY                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVLINKSTATE                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVMODE                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVSTATE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFUSERACCESSCALLOUTS                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFUSERINITCALLOUTS                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUP                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPCALLOUT                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPMAP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPMODE                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPREASONFLAGS                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPVERIFICATIONCALLOUT            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVHWACCESSIBILITY                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVLINKSTATE                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVMODE                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVSTATE                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_USERACCESSCALLOUTS                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_PRETRCVREADACCESSCALLOUTOFUSERACCESSCALLOUTS STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_PRETRCVWRITEACCESSCALLOUTOFUSERACCESSCALLOUTS STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_USERINITCALLOUTS                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_POSTINITUSERCALLOUTOFUSERINITCALLOUTS      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_PREINITUSERCALLOUTOFUSERINITCALLOUTS       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUP                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ICUCHANNELOFWAKEUP                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPCALLOUTIDXOFWAKEUP                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPCALLOUTUSEDOFWAKEUP                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPINSPECTIONTYPEOFWAKEUP               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPMAPENDIDXOFWAKEUP                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPMAPSTARTIDXOFWAKEUP                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPMAPUSEDOFWAKEUP                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPVERIFICATIONCALLOUTIDXOFWAKEUP       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPVERIFICATIONCALLOUTUSEDOFWAKEUP      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPCALLOUT                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPMAP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ECUMWAKEUPSOURCEOFWAKEUPMAP                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPREASONOFWAKEUPMAP                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPMODE                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPREASONFLAGS                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPVERIFICATIONCALLOUT                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_PCCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ACCESSENTITYFCTSOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_CABLEDIAGLOOPCYCLESOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ETHTRCVOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_ETHTRCVTJA1100OFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_FINALMAGICNUMBEROFPCCONFIG                 STD_OFF  /**< Deactivateable: 'EthTrcv_30_Tja1100_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTRCV_30_TJA1100_HWACCESSLOOPCOUNTOFPCCONFIG                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORCYCLECOUNTEROFPCCONFIG      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORFAILURECALLOUTOFPCCONFIG    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORFAILUREDEBOUNCECOUNTEROFPCCONFIG STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORFAILUREDEBOUNCELIMITEROFPCCONFIG STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORLOOPLIMITEROFPCCONFIG       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORRECOVERYDEBOUNCECOUNTEROFPCCONFIG STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_HWACCESSMONITORRECOVERYDEBOUNCELIMITEROFPCCONFIG STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_INITDATAHASHCODEOFPCCONFIG                 STD_OFF  /**< Deactivateable: 'EthTrcv_30_Tja1100_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTRCV_30_TJA1100_LINKFAILCOUNTEROFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTARTUPDELAYCOUNTEROFPCCONFIG          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTARTUPSTATEOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTATEDELAYCOUNTEROFPCCONFIG            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_LINKSTATETIMEOUTCOUNTEROFPCCONFIG          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_MAINFUNCTIONLINKHANDLINGMSOFPCCONFIG       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_MAXPHYSIGNALQUALITYMEANOFPCCONFIG          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFACCESSENTITYFCTSOFPCCONFIG           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFETHTRCVOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFETHTRCVTJA1100OFPCCONFIG             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFHWACCESSMONITORFAILURECALLOUTOFPCCONFIG STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFHWACCESSMONITORFAILUREDEBOUNCECOUNTEROFPCCONFIG STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFHWACCESSMONITORRECOVERYDEBOUNCECOUNTEROFPCCONFIG STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKFAILCOUNTEROFPCCONFIG            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTARTUPDELAYCOUNTEROFPCCONFIG    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTARTUPSTATEOFPCCONFIG           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTATEDELAYCOUNTEROFPCCONFIG      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFLINKSTATETIMEOUTCOUNTEROFPCCONFIG    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVHWACCESSIBILITYOFPCCONFIG        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVLINKSTATEOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVMODEOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFTRCVSTATEOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFUSERACCESSCALLOUTSOFPCCONFIG         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFUSERINITCALLOUTSOFPCCONFIG           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPCALLOUTOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPMAPOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPMODEOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPREASONFLAGSOFPCCONFIG          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_SIZEOFWAKEUPVERIFICATIONCALLOUTOFPCCONFIG  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVHWACCESSIBILITYOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVLINKSTATEOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVMODEOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_TRCVSTATEOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_USERACCESSCALLOUTSOFPCCONFIG               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_USERINITCALLOUTSOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPCALLOUTOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPMAPOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPMODEOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPREASONFLAGSOFPCCONFIG                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTRCV_30_TJA1100_WAKEUPVERIFICATIONCALLOUTOFPCCONFIG        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCMinNumericValueDefines  EthTrcv_30_Tja1100 Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define ETHTRCV_30_TJA1100_MIN_HWACCESSMONITORCYCLECOUNTER            0u
#define ETHTRCV_30_TJA1100_MIN_LINKFAILCOUNTER                        0uL
#define ETHTRCV_30_TJA1100_MIN_LINKSTARTUPDELAYCOUNTER                0uL
#define ETHTRCV_30_TJA1100_MIN_LINKSTARTUPSTATE                       0u
#define ETHTRCV_30_TJA1100_MIN_LINKSTATEDELAYCOUNTER                  0uL
#define ETHTRCV_30_TJA1100_MIN_LINKSTATETIMEOUTCOUNTER                0uL
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCMaxNumericValueDefines  EthTrcv_30_Tja1100 Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define ETHTRCV_30_TJA1100_MAX_HWACCESSMONITORCYCLECOUNTER            65535u
#define ETHTRCV_30_TJA1100_MAX_LINKFAILCOUNTER                        4294967295uL
#define ETHTRCV_30_TJA1100_MAX_LINKSTARTUPDELAYCOUNTER                4294967295uL
#define ETHTRCV_30_TJA1100_MAX_LINKSTARTUPSTATE                       255u
#define ETHTRCV_30_TJA1100_MAX_LINKSTATEDELAYCOUNTER                  4294967295uL
#define ETHTRCV_30_TJA1100_MAX_LINKSTATETIMEOUTCOUNTER                4294967295uL
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCNoReferenceDefines  EthTrcv_30_Tja1100 No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define ETHTRCV_30_TJA1100_NO_ACCESSENTITYSNVOFETHTRCV                255u
#define ETHTRCV_30_TJA1100_NO_ADDRESSINGIDXOFETHTRCV                  255u
#define ETHTRCV_30_TJA1100_NO_BASICCTRLREGVALOFETHTRCV                65535u
#define ETHTRCV_30_TJA1100_NO_DEMEACCESSEVENTIDOFETHTRCV              255u
#define ETHTRCV_30_TJA1100_NO_PHYSIGNALQUALITYMEANOFETHTRCV           255u
#define ETHTRCV_30_TJA1100_NO_SOCBASEREGADDROFETHTRCV                 255u
#define ETHTRCV_30_TJA1100_NO_SOFTRESETWAITCYCLESOFETHTRCV            255u
#define ETHTRCV_30_TJA1100_NO_WAKEUPIDXOFETHTRCV                      255u
#define ETHTRCV_30_TJA1100_NO_LINKFAILCOUNTERRESETVALOFETHTRCVTJA1100 255u
#define ETHTRCV_30_TJA1100_NO_LINKSTARTUPDELAYOFETHTRCVTJA1100        255u
#define ETHTRCV_30_TJA1100_NO_P0MIIADDRESSOFETHTRCVTJA1100            255u
#define ETHTRCV_30_TJA1100_NO_P0PORTSNVOFETHTRCVTJA1100               255u
#define ETHTRCV_30_TJA1100_NO_P0SWITCHSNVOFETHTRCVTJA1100             255u
#define ETHTRCV_30_TJA1100_NO_ICUCHANNELOFWAKEUP                      255u
#define ETHTRCV_30_TJA1100_NO_WAKEUPCALLOUTIDXOFWAKEUP                255u
#define ETHTRCV_30_TJA1100_NO_WAKEUPMAPENDIDXOFWAKEUP                 255u
#define ETHTRCV_30_TJA1100_NO_WAKEUPMAPSTARTIDXOFWAKEUP               255u
#define ETHTRCV_30_TJA1100_NO_WAKEUPVERIFICATIONCALLOUTIDXOFWAKEUP    255u
#define ETHTRCV_30_TJA1100_NO_ECUMWAKEUPSOURCEOFWAKEUPMAP             255u
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCEnumExistsDefines  EthTrcv_30_Tja1100 Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define ETHTRCV_30_TJA1100_EXISTS_CONN_NEG_AUTO_CONNECTIONNEGOFETHTRCV STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_CONN_NEG_MASTER_CONNECTIONNEGOFETHTRCV STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_CONN_NEG_SLAVE_CONNECTIONNEGOFETHTRCV STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_INTERNAL_PHY_MIIMODEOFETHTRCV       STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_MII_MODE_MIIMODEOFETHTRCV           STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_LIGHT_MII_MODE_MIIMODEOFETHTRCV     STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_RMII_MODE_MIIMODEOFETHTRCV          STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_RGMII_MODE_MIIMODEOFETHTRCV         STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_GMII_MODE_MIIMODEOFETHTRCV          STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_RMII_XTAL_MODE_MIIMODEOFETHTRCV     STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_RGMII_XTAL_MODE_MIIMODEOFETHTRCV    STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_STRAPPING_CONFIG_ONLY_MIIMODEOFETHTRCV STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_SGMII_MODE_MIIMODEOFETHTRCV         STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_DONT_CARE_MIIMODEOFETHTRCV          STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_TRCV_SPEED_10_SPEEDOFETHTRCV        STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_TRCV_SPEED_100_SPEEDOFETHTRCV       STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_TRCV_SPEED_1000_SPEEDOFETHTRCV      STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_ETHTRCV_25_MHZ_XTAL_NO_CLOCK_CLKMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_ETHTRCV_25_MHZ_XTAL_CLOCK_OUTPUT_CLKMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_ETHTRCV_25_MHZ_EXT_CLOCK_INPUT_CLKMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_ETHTRCV_50_MHZ_REF_CLOCK_INPUT_CLKMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_INVALID_CLOCK_MODE_CLKMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_TJA1100_DERIVATIVEOFETHTRCVTJA1100  STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_TJA1102_DERIVATIVEOFETHTRCVTJA1100  STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_TJA1101_DERIVATIVEOFETHTRCVTJA1100  STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_INT_REV_MII_ENABLED_INTREVMIIOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_INT_REV_MII_DISABLED_INTREVMIIOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_INT_REV_MII_INVALID_INTREVMIIOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_LDO_ENABLED_LDOMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_LDO_DISABLED_LDOMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_LDO_INVALID_LDOMODEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_PHY_ENABLED_PHYENABLEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_PHY_DISABLED_PHYENABLEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_PHY_EN_INVALID_PHYENABLEOFETHTRCVTJA1100 STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_ICU_CHANNEL_WAKEUPINSPECTIONTYPEOFWAKEUP STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_TRCV_REGISTERS_WAKEUPINSPECTIONTYPEOFWAKEUP STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_USER_CODE_WAKEUPINSPECTIONTYPEOFWAKEUP STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_DONT_CARE_WAKEUPINSPECTIONTYPEOFWAKEUP STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_WUR_GENERAL_WAKEUPREASONOFWAKEUPMAP STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_WUR_BUS_WAKEUPREASONOFWAKEUPMAP     STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_WUR_INTERNAL_WAKEUPREASONOFWAKEUPMAP STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_WUR_RESET_WAKEUPREASONOFWAKEUPMAP   STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_WUR_POWER_ON_WAKEUPREASONOFWAKEUPMAP STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_WUR_PIN_WAKEUPREASONOFWAKEUPMAP     STD_ON
#define ETHTRCV_30_TJA1100_EXISTS_WUR_SYSERR_WAKEUPREASONOFWAKEUPMAP  STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCEnumDefines  EthTrcv_30_Tja1100 Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define ETHTRCV_30_TJA1100_CONN_NEG_AUTO_CONNECTIONNEGOFETHTRCV       0x00u
#define ETHTRCV_30_TJA1100_CONN_NEG_MASTER_CONNECTIONNEGOFETHTRCV     0x01u
#define ETHTRCV_30_TJA1100_CONN_NEG_SLAVE_CONNECTIONNEGOFETHTRCV      0x02u
#define ETHTRCV_30_TJA1100_INTERNAL_PHY_MIIMODEOFETHTRCV              0x00u
#define ETHTRCV_30_TJA1100_MII_MODE_MIIMODEOFETHTRCV                  0x01u
#define ETHTRCV_30_TJA1100_LIGHT_MII_MODE_MIIMODEOFETHTRCV            0x02u
#define ETHTRCV_30_TJA1100_RMII_MODE_MIIMODEOFETHTRCV                 0x03u
#define ETHTRCV_30_TJA1100_RGMII_MODE_MIIMODEOFETHTRCV                0x04u
#define ETHTRCV_30_TJA1100_GMII_MODE_MIIMODEOFETHTRCV                 0x05u
#define ETHTRCV_30_TJA1100_RMII_XTAL_MODE_MIIMODEOFETHTRCV            0x06u
#define ETHTRCV_30_TJA1100_RGMII_XTAL_MODE_MIIMODEOFETHTRCV           0x07u
#define ETHTRCV_30_TJA1100_STRAPPING_CONFIG_ONLY_MIIMODEOFETHTRCV     0x08u
#define ETHTRCV_30_TJA1100_SGMII_MODE_MIIMODEOFETHTRCV                0x09u
#define ETHTRCV_30_TJA1100_DONT_CARE_MIIMODEOFETHTRCV                 0x0Au
#define ETHTRCV_30_TJA1100_TRCV_SPEED_10_SPEEDOFETHTRCV               0x00u
#define ETHTRCV_30_TJA1100_TRCV_SPEED_100_SPEEDOFETHTRCV              0x01u
#define ETHTRCV_30_TJA1100_TRCV_SPEED_1000_SPEEDOFETHTRCV             0x02u
#define ETHTRCV_30_TJA1100_ETHTRCV_25_MHZ_XTAL_NO_CLOCK_CLKMODEOFETHTRCVTJA1100 0x00u
#define ETHTRCV_30_TJA1100_ETHTRCV_25_MHZ_XTAL_CLOCK_OUTPUT_CLKMODEOFETHTRCVTJA1100 0x01u
#define ETHTRCV_30_TJA1100_ETHTRCV_25_MHZ_EXT_CLOCK_INPUT_CLKMODEOFETHTRCVTJA1100 0x02u
#define ETHTRCV_30_TJA1100_ETHTRCV_50_MHZ_REF_CLOCK_INPUT_CLKMODEOFETHTRCVTJA1100 0x03u
#define ETHTRCV_30_TJA1100_INVALID_CLOCK_MODE_CLKMODEOFETHTRCVTJA1100 0x04u
#define ETHTRCV_30_TJA1100_TJA1100_DERIVATIVEOFETHTRCVTJA1100         0x00u
#define ETHTRCV_30_TJA1100_TJA1102_DERIVATIVEOFETHTRCVTJA1100         0x01u
#define ETHTRCV_30_TJA1100_TJA1101_DERIVATIVEOFETHTRCVTJA1100         0x02u
#define ETHTRCV_30_TJA1100_INT_REV_MII_ENABLED_INTREVMIIOFETHTRCVTJA1100 0x00u
#define ETHTRCV_30_TJA1100_INT_REV_MII_DISABLED_INTREVMIIOFETHTRCVTJA1100 0x01u
#define ETHTRCV_30_TJA1100_INT_REV_MII_INVALID_INTREVMIIOFETHTRCVTJA1100 0x02u
#define ETHTRCV_30_TJA1100_LDO_ENABLED_LDOMODEOFETHTRCVTJA1100        0x00u
#define ETHTRCV_30_TJA1100_LDO_DISABLED_LDOMODEOFETHTRCVTJA1100       0x01u
#define ETHTRCV_30_TJA1100_LDO_INVALID_LDOMODEOFETHTRCVTJA1100        0x02u
#define ETHTRCV_30_TJA1100_PHY_ENABLED_PHYENABLEOFETHTRCVTJA1100      0x00u
#define ETHTRCV_30_TJA1100_PHY_DISABLED_PHYENABLEOFETHTRCVTJA1100     0x01u
#define ETHTRCV_30_TJA1100_PHY_EN_INVALID_PHYENABLEOFETHTRCVTJA1100   0x02u
#define ETHTRCV_30_TJA1100_ICU_CHANNEL_WAKEUPINSPECTIONTYPEOFWAKEUP   0x00u
#define ETHTRCV_30_TJA1100_TRCV_REGISTERS_WAKEUPINSPECTIONTYPEOFWAKEUP 0x01u
#define ETHTRCV_30_TJA1100_USER_CODE_WAKEUPINSPECTIONTYPEOFWAKEUP     0x02u
#define ETHTRCV_30_TJA1100_DONT_CARE_WAKEUPINSPECTIONTYPEOFWAKEUP     0x03u
#define ETHTRCV_30_TJA1100_WUR_GENERAL_WAKEUPREASONOFWAKEUPMAP        0x01u
#define ETHTRCV_30_TJA1100_WUR_BUS_WAKEUPREASONOFWAKEUPMAP            0x02u
#define ETHTRCV_30_TJA1100_WUR_INTERNAL_WAKEUPREASONOFWAKEUPMAP       0x03u
#define ETHTRCV_30_TJA1100_WUR_RESET_WAKEUPREASONOFWAKEUPMAP          0x04u
#define ETHTRCV_30_TJA1100_WUR_POWER_ON_WAKEUPREASONOFWAKEUPMAP       0x05u
#define ETHTRCV_30_TJA1100_WUR_PIN_WAKEUPREASONOFWAKEUPMAP            0x06u
#define ETHTRCV_30_TJA1100_WUR_SYSERR_WAKEUPREASONOFWAKEUPMAP         0x07u
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCIsReducedToDefineDefines  EthTrcv_30_Tja1100 Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define ETHTRCV_30_TJA1100_ISDEF_READTRCVREGOFACCESSENTITYFCTS        STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WRITETRCVREGOFACCESSENTITYFCTS       STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ACCESSENTITYFCTSIDXOFETHTRCV         STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ACCESSENTITYSNVOFETHTRCV             STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ADDRESSINGIDXOFETHTRCV               STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_AUTONEGENABLEDOFETHTRCV              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_BASICCTRLREGVALOFETHTRCV             STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_CONNECTIONNEGOFETHTRCV               STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_DEMEACCESSEVENTIDOFETHTRCV           STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_MIIMODEOFETHTRCV                     STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_PHYSIGNALQUALITYMEANOFETHTRCV        STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SOCBASEREGADDROFETHTRCV              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SOFTRESETONINITENABLEDOFETHTRCV      STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SOFTRESETWAITCYCLESOFETHTRCV         STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SPEEDOFETHTRCV                       STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPIDXOFETHTRCV                   STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPUSEDOFETHTRCV                  STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_CLKMODEOFETHTRCVTJA1100              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_DERIVATIVEOFETHTRCVTJA1100           STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_EXTLINKSTATECHECKENABLEDOFETHTRCVTJA1100 STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_INTREVMIIOFETHTRCVTJA1100            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LDOMODEOFETHTRCVTJA1100              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LINKFAILCOUNTERRESETVALOFETHTRCVTJA1100 STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LINKSTARTUPDELAYOFETHTRCVTJA1100     STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_P0MIIADDRESSOFETHTRCVTJA1100         STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_P0PORTSNVOFETHTRCVTJA1100            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_P0SWITCHSNVOFETHTRCVTJA1100          STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_PHYENABLEOFETHTRCVTJA1100            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORFAILURECALLOUT        STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_PRETRCVREADACCESSCALLOUTOFUSERACCESSCALLOUTS STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_PRETRCVWRITEACCESSCALLOUTOFUSERACCESSCALLOUTS STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_POSTINITUSERCALLOUTOFUSERINITCALLOUTS STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_PREINITUSERCALLOUTOFUSERINITCALLOUTS STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ICUCHANNELOFWAKEUP                   STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPCALLOUTIDXOFWAKEUP             STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPCALLOUTUSEDOFWAKEUP            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPINSPECTIONTYPEOFWAKEUP         STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPMAPENDIDXOFWAKEUP              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPMAPSTARTIDXOFWAKEUP            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPMAPUSEDOFWAKEUP                STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPVERIFICATIONCALLOUTIDXOFWAKEUP STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPVERIFICATIONCALLOUTUSEDOFWAKEUP STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPCALLOUT                        STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ECUMWAKEUPSOURCEOFWAKEUPMAP          STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPREASONOFWAKEUPMAP              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPVERIFICATIONCALLOUT            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ACCESSENTITYFCTSOFPCCONFIG           STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_CABLEDIAGLOOPCYCLESOFPCCONFIG        STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ETHTRCVOFPCCONFIG                    STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_ETHTRCVTJA1100OFPCCONFIG             STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSLOOPCOUNTOFPCCONFIG          STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORCYCLECOUNTEROFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORFAILURECALLOUTOFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORFAILUREDEBOUNCECOUNTEROFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORFAILUREDEBOUNCELIMITEROFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORLOOPLIMITEROFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORRECOVERYDEBOUNCECOUNTEROFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_HWACCESSMONITORRECOVERYDEBOUNCELIMITEROFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LINKFAILCOUNTEROFPCCONFIG            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LINKSTARTUPDELAYCOUNTEROFPCCONFIG    STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LINKSTARTUPSTATEOFPCCONFIG           STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LINKSTATEDELAYCOUNTEROFPCCONFIG      STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_LINKSTATETIMEOUTCOUNTEROFPCCONFIG    STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_MAINFUNCTIONLINKHANDLINGMSOFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_MAXPHYSIGNALQUALITYMEANOFPCCONFIG    STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFACCESSENTITYFCTSOFPCCONFIG     STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFETHTRCVOFPCCONFIG              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFETHTRCVTJA1100OFPCCONFIG       STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFHWACCESSMONITORFAILURECALLOUTOFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFUSERACCESSCALLOUTSOFPCCONFIG   STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFUSERINITCALLOUTSOFPCCONFIG     STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFWAKEUPCALLOUTOFPCCONFIG        STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFWAKEUPMAPOFPCCONFIG            STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFWAKEUPOFPCCONFIG               STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_SIZEOFWAKEUPVERIFICATIONCALLOUTOFPCCONFIG STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_TRCVHWACCESSIBILITYOFPCCONFIG        STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_TRCVLINKSTATEOFPCCONFIG              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_TRCVMODEOFPCCONFIG                   STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_TRCVSTATEOFPCCONFIG                  STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_USERACCESSCALLOUTSOFPCCONFIG         STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_USERINITCALLOUTSOFPCCONFIG           STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPCALLOUTOFPCCONFIG              STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPMAPOFPCCONFIG                  STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPMODEOFPCCONFIG                 STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPOFPCCONFIG                     STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPREASONFLAGSOFPCCONFIG          STD_OFF
#define ETHTRCV_30_TJA1100_ISDEF_WAKEUPVERIFICATIONCALLOUTOFPCCONFIG  STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCEqualsAlwaysToDefines  EthTrcv_30_Tja1100 Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define ETHTRCV_30_TJA1100_EQ2_READTRCVREGOFACCESSENTITYFCTS          
#define ETHTRCV_30_TJA1100_EQ2_WRITETRCVREGOFACCESSENTITYFCTS         
#define ETHTRCV_30_TJA1100_EQ2_ACCESSENTITYFCTSIDXOFETHTRCV           
#define ETHTRCV_30_TJA1100_EQ2_ACCESSENTITYSNVOFETHTRCV               
#define ETHTRCV_30_TJA1100_EQ2_ADDRESSINGIDXOFETHTRCV                 
#define ETHTRCV_30_TJA1100_EQ2_AUTONEGENABLEDOFETHTRCV                
#define ETHTRCV_30_TJA1100_EQ2_BASICCTRLREGVALOFETHTRCV               
#define ETHTRCV_30_TJA1100_EQ2_CONNECTIONNEGOFETHTRCV                 
#define ETHTRCV_30_TJA1100_EQ2_DEMEACCESSEVENTIDOFETHTRCV             
#define ETHTRCV_30_TJA1100_EQ2_MIIMODEOFETHTRCV                       
#define ETHTRCV_30_TJA1100_EQ2_PHYSIGNALQUALITYMEANOFETHTRCV          
#define ETHTRCV_30_TJA1100_EQ2_SOCBASEREGADDROFETHTRCV                
#define ETHTRCV_30_TJA1100_EQ2_SOFTRESETONINITENABLEDOFETHTRCV        
#define ETHTRCV_30_TJA1100_EQ2_SOFTRESETWAITCYCLESOFETHTRCV           
#define ETHTRCV_30_TJA1100_EQ2_SPEEDOFETHTRCV                         
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPIDXOFETHTRCV                     
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPUSEDOFETHTRCV                    
#define ETHTRCV_30_TJA1100_EQ2_CLKMODEOFETHTRCVTJA1100                
#define ETHTRCV_30_TJA1100_EQ2_DERIVATIVEOFETHTRCVTJA1100             
#define ETHTRCV_30_TJA1100_EQ2_EXTLINKSTATECHECKENABLEDOFETHTRCVTJA1100 
#define ETHTRCV_30_TJA1100_EQ2_INTREVMIIOFETHTRCVTJA1100              
#define ETHTRCV_30_TJA1100_EQ2_LDOMODEOFETHTRCVTJA1100                
#define ETHTRCV_30_TJA1100_EQ2_LINKFAILCOUNTERRESETVALOFETHTRCVTJA1100 
#define ETHTRCV_30_TJA1100_EQ2_LINKSTARTUPDELAYOFETHTRCVTJA1100       
#define ETHTRCV_30_TJA1100_EQ2_P0MIIADDRESSOFETHTRCVTJA1100           
#define ETHTRCV_30_TJA1100_EQ2_P0PORTSNVOFETHTRCVTJA1100              
#define ETHTRCV_30_TJA1100_EQ2_P0SWITCHSNVOFETHTRCVTJA1100            
#define ETHTRCV_30_TJA1100_EQ2_PHYENABLEOFETHTRCVTJA1100              
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORFAILURECALLOUT          
#define ETHTRCV_30_TJA1100_EQ2_PRETRCVREADACCESSCALLOUTOFUSERACCESSCALLOUTS 
#define ETHTRCV_30_TJA1100_EQ2_PRETRCVWRITEACCESSCALLOUTOFUSERACCESSCALLOUTS 
#define ETHTRCV_30_TJA1100_EQ2_POSTINITUSERCALLOUTOFUSERINITCALLOUTS  
#define ETHTRCV_30_TJA1100_EQ2_PREINITUSERCALLOUTOFUSERINITCALLOUTS   
#define ETHTRCV_30_TJA1100_EQ2_ICUCHANNELOFWAKEUP                     
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPCALLOUTIDXOFWAKEUP               
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPCALLOUTUSEDOFWAKEUP              
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPINSPECTIONTYPEOFWAKEUP           
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPMAPENDIDXOFWAKEUP                
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPMAPSTARTIDXOFWAKEUP              
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPMAPUSEDOFWAKEUP                  
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPVERIFICATIONCALLOUTIDXOFWAKEUP   
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPVERIFICATIONCALLOUTUSEDOFWAKEUP  
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPCALLOUT                          
#define ETHTRCV_30_TJA1100_EQ2_ECUMWAKEUPSOURCEOFWAKEUPMAP            
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPREASONOFWAKEUPMAP                
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPVERIFICATIONCALLOUT              
#define ETHTRCV_30_TJA1100_EQ2_ACCESSENTITYFCTSOFPCCONFIG             
#define ETHTRCV_30_TJA1100_EQ2_CABLEDIAGLOOPCYCLESOFPCCONFIG          
#define ETHTRCV_30_TJA1100_EQ2_ETHTRCVOFPCCONFIG                      
#define ETHTRCV_30_TJA1100_EQ2_ETHTRCVTJA1100OFPCCONFIG               
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSLOOPCOUNTOFPCCONFIG            
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORCYCLECOUNTEROFPCCONFIG  
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORFAILURECALLOUTOFPCCONFIG 
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORFAILUREDEBOUNCECOUNTEROFPCCONFIG 
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORFAILUREDEBOUNCELIMITEROFPCCONFIG 
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORLOOPLIMITEROFPCCONFIG   
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORRECOVERYDEBOUNCECOUNTEROFPCCONFIG 
#define ETHTRCV_30_TJA1100_EQ2_HWACCESSMONITORRECOVERYDEBOUNCELIMITEROFPCCONFIG 
#define ETHTRCV_30_TJA1100_EQ2_LINKFAILCOUNTEROFPCCONFIG              
#define ETHTRCV_30_TJA1100_EQ2_LINKSTARTUPDELAYCOUNTEROFPCCONFIG      
#define ETHTRCV_30_TJA1100_EQ2_LINKSTARTUPSTATEOFPCCONFIG             
#define ETHTRCV_30_TJA1100_EQ2_LINKSTATEDELAYCOUNTEROFPCCONFIG        
#define ETHTRCV_30_TJA1100_EQ2_LINKSTATETIMEOUTCOUNTEROFPCCONFIG      
#define ETHTRCV_30_TJA1100_EQ2_MAINFUNCTIONLINKHANDLINGMSOFPCCONFIG   
#define ETHTRCV_30_TJA1100_EQ2_MAXPHYSIGNALQUALITYMEANOFPCCONFIG      
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFACCESSENTITYFCTSOFPCCONFIG       
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFETHTRCVOFPCCONFIG                
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFETHTRCVTJA1100OFPCCONFIG         
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFHWACCESSMONITORFAILURECALLOUTOFPCCONFIG 
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFUSERACCESSCALLOUTSOFPCCONFIG     
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFUSERINITCALLOUTSOFPCCONFIG       
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFWAKEUPCALLOUTOFPCCONFIG          
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFWAKEUPMAPOFPCCONFIG              
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFWAKEUPOFPCCONFIG                 
#define ETHTRCV_30_TJA1100_EQ2_SIZEOFWAKEUPVERIFICATIONCALLOUTOFPCCONFIG 
#define ETHTRCV_30_TJA1100_EQ2_TRCVHWACCESSIBILITYOFPCCONFIG          
#define ETHTRCV_30_TJA1100_EQ2_TRCVLINKSTATEOFPCCONFIG                
#define ETHTRCV_30_TJA1100_EQ2_TRCVMODEOFPCCONFIG                     
#define ETHTRCV_30_TJA1100_EQ2_TRCVSTATEOFPCCONFIG                    
#define ETHTRCV_30_TJA1100_EQ2_USERACCESSCALLOUTSOFPCCONFIG           
#define ETHTRCV_30_TJA1100_EQ2_USERINITCALLOUTSOFPCCONFIG             
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPCALLOUTOFPCCONFIG                
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPMAPOFPCCONFIG                    
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPMODEOFPCCONFIG                   
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPOFPCCONFIG                       
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPREASONFLAGSOFPCCONFIG            
#define ETHTRCV_30_TJA1100_EQ2_WAKEUPVERIFICATIONCALLOUTOFPCCONFIG    
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCSymbolicInitializationPointers  EthTrcv_30_Tja1100 Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define EthTrcv_30_Tja1100_Config_Ptr                                 &(EthTrcv_30_Tja1100_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'EthTrcv_30_Tja1100' */
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCInitializationSymbols  EthTrcv_30_Tja1100 Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define EthTrcv_30_Tja1100_Config                                     EthTrcv_30_Tja1100_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'EthTrcv_30_Tja1100 */
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCGeneral  EthTrcv_30_Tja1100 General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define ETHTRCV_30_TJA1100_CHECK_INIT_POINTER                         STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define ETHTRCV_30_TJA1100_FINAL_MAGIC_NUMBER                         0x491Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of EthTrcv_30_Tja1100 */
#define ETHTRCV_30_TJA1100_INDIVIDUAL_POSTBUILD                       STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'EthTrcv_30_Tja1100' is not configured to be postbuild capable. */
#define ETHTRCV_30_TJA1100_INIT_DATA                                  ETHTRCV_30_TJA1100_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define ETHTRCV_30_TJA1100_INIT_DATA_HASH_CODE                        411454191L  /**< the precompile constant to validate the initialization structure at initialization time of EthTrcv_30_Tja1100 with a hashcode. The seed value is '0x491Eu' */
#define ETHTRCV_30_TJA1100_USE_ECUM_BSW_ERROR_HOOK                    STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define ETHTRCV_30_TJA1100_USE_INIT_POINTER                           STD_ON  /**< STD_ON if the init pointer EthTrcv_30_Tja1100 shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthTrcv_30_Tja1100PCIterableTypes  EthTrcv_30_Tja1100 Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate EthTrcv_30_Tja1100_AccessEntityFcts */
typedef uint8_least EthTrcv_30_Tja1100_AccessEntityFctsIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_EthTrcv */
typedef uint8_least EthTrcv_30_Tja1100_EthTrcvIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_EthTrcvTja1100 */
typedef uint8_least EthTrcv_30_Tja1100_EthTrcvTja1100IterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout */
typedef uint8_least EthTrcv_30_Tja1100_HwAccessMonitorFailureCalloutIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_UserAccessCallouts */
typedef uint8_least EthTrcv_30_Tja1100_UserAccessCalloutsIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_UserInitCallouts */
typedef uint8_least EthTrcv_30_Tja1100_UserInitCalloutsIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_Wakeup */
typedef uint8_least EthTrcv_30_Tja1100_WakeupIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_WakeupCallout */
typedef uint8_least EthTrcv_30_Tja1100_WakeupCalloutIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_WakeupMap */
typedef uint8_least EthTrcv_30_Tja1100_WakeupMapIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_WakeupVerificationCallout */
typedef uint8_least EthTrcv_30_Tja1100_WakeupVerificationCalloutIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCIterableTypesWithSizeRelations  EthTrcv_30_Tja1100 Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter */
typedef EthTrcv_30_Tja1100_EthTrcvIterType EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter */
typedef EthTrcv_30_Tja1100_EthTrcvIterType EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_LinkFailCounter */
typedef EthTrcv_30_Tja1100_EthTrcvTja1100IterType EthTrcv_30_Tja1100_LinkFailCounterIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_LinkStartupDelayCounter */
typedef EthTrcv_30_Tja1100_EthTrcvTja1100IterType EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_LinkStartupState */
typedef EthTrcv_30_Tja1100_EthTrcvTja1100IterType EthTrcv_30_Tja1100_LinkStartupStateIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_LinkStateDelayCounter */
typedef EthTrcv_30_Tja1100_EthTrcvTja1100IterType EthTrcv_30_Tja1100_LinkStateDelayCounterIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_LinkStateTimeoutCounter */
typedef EthTrcv_30_Tja1100_EthTrcvTja1100IterType EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_TrcvHwAccessibility */
typedef EthTrcv_30_Tja1100_EthTrcvIterType EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_TrcvLinkState */
typedef EthTrcv_30_Tja1100_EthTrcvIterType EthTrcv_30_Tja1100_TrcvLinkStateIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_TrcvMode */
typedef EthTrcv_30_Tja1100_EthTrcvIterType EthTrcv_30_Tja1100_TrcvModeIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_TrcvState */
typedef EthTrcv_30_Tja1100_EthTrcvIterType EthTrcv_30_Tja1100_TrcvStateIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_WakeupMode */
typedef EthTrcv_30_Tja1100_WakeupIterType EthTrcv_30_Tja1100_WakeupModeIterType;

/**   \brief  type used to iterate EthTrcv_30_Tja1100_WakeupReasonFlags */
typedef EthTrcv_30_Tja1100_WakeupIterType EthTrcv_30_Tja1100_WakeupReasonFlagsIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCValueTypes  EthTrcv_30_Tja1100 Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for EthTrcv_30_Tja1100_CableDiagLoopCycles */
typedef uint16 EthTrcv_30_Tja1100_CableDiagLoopCyclesType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_AccessEntitySnvOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_AccessEntitySnvOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_AddressingIdxOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_AddressingIdxOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_AutoNegEnabledOfEthTrcv */
typedef boolean EthTrcv_30_Tja1100_AutoNegEnabledOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_BasicCtrlRegValOfEthTrcv */
typedef uint16 EthTrcv_30_Tja1100_BasicCtrlRegValOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_ConnectionNegOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_ConnectionNegOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_DemEAccessEventIdOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_DemEAccessEventIdOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_MiiModeOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_MiiModeOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SoCBaseRegAddrOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_SoCBaseRegAddrOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SoftResetOnInitEnabledOfEthTrcv */
typedef boolean EthTrcv_30_Tja1100_SoftResetOnInitEnabledOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SoftResetWaitCyclesOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_SoftResetWaitCyclesOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SpeedOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_SpeedOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupIdxOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupUsedOfEthTrcv */
typedef boolean EthTrcv_30_Tja1100_WakeupUsedOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_ClkModeOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_ClkModeOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_ExtLinkStateCheckEnabledOfEthTrcvTja1100 */
typedef boolean EthTrcv_30_Tja1100_ExtLinkStateCheckEnabledOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_IntRevMiiOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_IntRevMiiOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LdoModeOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_LdoModeOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LinkFailCounterResetValOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_LinkFailCounterResetValOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LinkStartupDelayOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_LinkStartupDelayOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_P0MiiAddressOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_P0MiiAddressOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_P0PortSnvOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_P0PortSnvOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_P0SwitchSnvOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_P0SwitchSnvOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_PhyEnableOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_PhyEnableOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_HwAccessLoopCount */
typedef uint8 EthTrcv_30_Tja1100_HwAccessLoopCountType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter */
typedef uint16 EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceLimiter */
typedef uint8 EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceLimiterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_HwAccessMonitorLoopLimiter */
typedef uint8 EthTrcv_30_Tja1100_HwAccessMonitorLoopLimiterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceLimiter */
typedef uint8 EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceLimiterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LinkFailCounter */
typedef uint32 EthTrcv_30_Tja1100_LinkFailCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LinkStartupDelayCounter */
typedef uint32 EthTrcv_30_Tja1100_LinkStartupDelayCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LinkStartupState */
typedef uint8 EthTrcv_30_Tja1100_LinkStartupStateType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LinkStateDelayCounter */
typedef uint32 EthTrcv_30_Tja1100_LinkStateDelayCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_LinkStateTimeoutCounter */
typedef uint32 EthTrcv_30_Tja1100_LinkStateTimeoutCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_MainFunctionLinkHandlingMs */
typedef uint8 EthTrcv_30_Tja1100_MainFunctionLinkHandlingMsType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_MaxPhySignalQualityMean */
typedef uint8 EthTrcv_30_Tja1100_MaxPhySignalQualityMeanType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfAccessEntityFcts */
typedef uint8 EthTrcv_30_Tja1100_SizeOfAccessEntityFctsType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfEthTrcv */
typedef uint8 EthTrcv_30_Tja1100_SizeOfEthTrcvType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfEthTrcvTja1100 */
typedef uint8 EthTrcv_30_Tja1100_SizeOfEthTrcvTja1100Type;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureCallout */
typedef uint8 EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureCalloutType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureDebounceCounter */
typedef uint8 EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureDebounceCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfHwAccessMonitorRecoveryDebounceCounter */
typedef uint8 EthTrcv_30_Tja1100_SizeOfHwAccessMonitorRecoveryDebounceCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfLinkFailCounter */
typedef uint8 EthTrcv_30_Tja1100_SizeOfLinkFailCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfLinkStartupDelayCounter */
typedef uint8 EthTrcv_30_Tja1100_SizeOfLinkStartupDelayCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfLinkStartupState */
typedef uint8 EthTrcv_30_Tja1100_SizeOfLinkStartupStateType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfLinkStateDelayCounter */
typedef uint8 EthTrcv_30_Tja1100_SizeOfLinkStateDelayCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfLinkStateTimeoutCounter */
typedef uint8 EthTrcv_30_Tja1100_SizeOfLinkStateTimeoutCounterType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfTrcvHwAccessibility */
typedef uint8 EthTrcv_30_Tja1100_SizeOfTrcvHwAccessibilityType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfTrcvLinkState */
typedef uint8 EthTrcv_30_Tja1100_SizeOfTrcvLinkStateType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfTrcvMode */
typedef uint8 EthTrcv_30_Tja1100_SizeOfTrcvModeType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfTrcvState */
typedef uint8 EthTrcv_30_Tja1100_SizeOfTrcvStateType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfUserAccessCallouts */
typedef uint8 EthTrcv_30_Tja1100_SizeOfUserAccessCalloutsType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfUserInitCallouts */
typedef uint8 EthTrcv_30_Tja1100_SizeOfUserInitCalloutsType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfWakeup */
typedef uint8 EthTrcv_30_Tja1100_SizeOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfWakeupCallout */
typedef uint8 EthTrcv_30_Tja1100_SizeOfWakeupCalloutType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfWakeupMap */
typedef uint8 EthTrcv_30_Tja1100_SizeOfWakeupMapType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfWakeupMode */
typedef uint8 EthTrcv_30_Tja1100_SizeOfWakeupModeType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfWakeupReasonFlags */
typedef uint8 EthTrcv_30_Tja1100_SizeOfWakeupReasonFlagsType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_SizeOfWakeupVerificationCallout */
typedef uint8 EthTrcv_30_Tja1100_SizeOfWakeupVerificationCalloutType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_IcuChannelOfWakeup */
typedef uint8 EthTrcv_30_Tja1100_IcuChannelOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupCalloutIdxOfWakeup */
typedef uint8 EthTrcv_30_Tja1100_WakeupCalloutIdxOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupCalloutUsedOfWakeup */
typedef boolean EthTrcv_30_Tja1100_WakeupCalloutUsedOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupInspectionTypeOfWakeup */
typedef uint8 EthTrcv_30_Tja1100_WakeupInspectionTypeOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupMapEndIdxOfWakeup */
typedef uint8 EthTrcv_30_Tja1100_WakeupMapEndIdxOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupMapStartIdxOfWakeup */
typedef uint8 EthTrcv_30_Tja1100_WakeupMapStartIdxOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupMapUsedOfWakeup */
typedef boolean EthTrcv_30_Tja1100_WakeupMapUsedOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupVerificationCalloutIdxOfWakeup */
typedef uint8 EthTrcv_30_Tja1100_WakeupVerificationCalloutIdxOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupVerificationCalloutUsedOfWakeup */
typedef boolean EthTrcv_30_Tja1100_WakeupVerificationCalloutUsedOfWakeupType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_EcuMWakeupSourceOfWakeupMap */
typedef uint8 EthTrcv_30_Tja1100_EcuMWakeupSourceOfWakeupMapType;

/**   \brief  value based type definition for EthTrcv_30_Tja1100_WakeupReasonOfWakeupMap */
typedef uint8 EthTrcv_30_Tja1100_WakeupReasonOfWakeupMapType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthTrcv_30_Tja1100PCStructTypes  EthTrcv_30_Tja1100 Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in EthTrcv_30_Tja1100_AccessEntityFcts */
typedef struct sEthTrcv_30_Tja1100_AccessEntityFctsType
{
  EthTrcv_30_Tja1100_ReadTrcvRegFctPtrType ReadTrcvRegOfAccessEntityFcts;  /**< Function to call when a read register shall be performed */
  EthTrcv_30_Tja1100_WriteTrcvRegFctPtrType WriteTrcvRegOfAccessEntityFcts;  /**< Function to call when a write register shall be performed */
} EthTrcv_30_Tja1100_AccessEntityFctsType;

/**   \brief  type used in EthTrcv_30_Tja1100_EthTrcv */
typedef struct sEthTrcv_30_Tja1100_EthTrcvType
{
  EthTrcv_30_Tja1100_BasicCtrlRegValOfEthTrcvType BasicCtrlRegValOfEthTrcv;  /**< Initialization value of basic control register */
  EthTrcv_30_Tja1100_AutoNegEnabledOfEthTrcvType AutoNegEnabledOfEthTrcv;  /**< Auto negotiation configuration */
  EthTrcv_30_Tja1100_SoftResetOnInitEnabledOfEthTrcvType SoftResetOnInitEnabledOfEthTrcv;  /**< Soft reset on initialization configuraiton */
  EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType AccessEntityFctsIdxOfEthTrcv;  /**< the index of the 1:1 relation pointing to EthTrcv_30_Tja1100_AccessEntityFcts */
  EthTrcv_30_Tja1100_AccessEntitySnvOfEthTrcvType AccessEntitySnvOfEthTrcv;  /**< Entity providing access to the transceiver hardware */
  EthTrcv_30_Tja1100_AddressingIdxOfEthTrcvType AddressingIdxOfEthTrcv;  /**< Addressing index in context of the access entity to address the transceiver hardware */
  EthTrcv_30_Tja1100_ConnectionNegOfEthTrcvType ConnectionNegOfEthTrcv;  /**< Connection negotiation configuration */
  EthTrcv_30_Tja1100_DemEAccessEventIdOfEthTrcvType DemEAccessEventIdOfEthTrcv;  /**< ETHTRCV_E_ACCESS DEM event */
  EthTrcv_30_Tja1100_MiiModeOfEthTrcvType MiiModeOfEthTrcv;  /**< Mii interface */
  EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcvType PhySignalQualityMeanOfEthTrcv;  /**< Mean value of phyisical signal quality */
  EthTrcv_30_Tja1100_SoCBaseRegAddrOfEthTrcvType SoCBaseRegAddrOfEthTrcv;  /**< Base register address within memory space of SoC in case PHY is integrated as module into SoC. */
  EthTrcv_30_Tja1100_SoftResetWaitCyclesOfEthTrcvType SoftResetWaitCyclesOfEthTrcv;  /**< Soft reset wait cycles */
  EthTrcv_30_Tja1100_SpeedOfEthTrcvType SpeedOfEthTrcv;  /**< Transceiver speed */
  EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType WakeupIdxOfEthTrcv;  /**< the index of the 0:1 relation pointing to EthTrcv_30_Tja1100_Wakeup */
} EthTrcv_30_Tja1100_EthTrcvType;

/**   \brief  type used in EthTrcv_30_Tja1100_EthTrcvTja1100 */
typedef struct sEthTrcv_30_Tja1100_EthTrcvTja1100Type
{
  EthTrcv_30_Tja1100_ExtLinkStateCheckEnabledOfEthTrcvTja1100Type ExtLinkStateCheckEnabledOfEthTrcvTja1100;  /**< Extended link state check configuration. */
  EthTrcv_30_Tja1100_ClkModeOfEthTrcvTja1100Type ClkModeOfEthTrcvTja1100;  /**< Clock mode. */
  EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100Type DerivativeOfEthTrcvTja1100;  /**< Tja110x derivative. */
  EthTrcv_30_Tja1100_IntRevMiiOfEthTrcvTja1100Type IntRevMiiOfEthTrcvTja1100;  /**< Internal Reverse MII. */
  EthTrcv_30_Tja1100_LdoModeOfEthTrcvTja1100Type LdoModeOfEthTrcvTja1100;  /**< LDO mode. */
  EthTrcv_30_Tja1100_LinkFailCounterResetValOfEthTrcvTja1100Type LinkFailCounterResetValOfEthTrcvTja1100;  /**< Initialization value for link fail counter */
  EthTrcv_30_Tja1100_LinkStartupDelayOfEthTrcvTja1100Type LinkStartupDelayOfEthTrcvTja1100;  /**< Delay till link initialization is triggered after transceiver is enabled. */
  EthTrcv_30_Tja1100_P0MiiAddressOfEthTrcvTja1100Type P0MiiAddressOfEthTrcvTja1100;  /**< MII address of P0. */
  EthTrcv_30_Tja1100_P0PortSnvOfEthTrcvTja1100Type P0PortSnvOfEthTrcvTja1100;  /**< SNV of port used to access P0. */
  EthTrcv_30_Tja1100_P0SwitchSnvOfEthTrcvTja1100Type P0SwitchSnvOfEthTrcvTja1100;  /**< SNV of switch used to access P0. */
  EthTrcv_30_Tja1100_PhyEnableOfEthTrcvTja1100Type PhyEnableOfEthTrcvTja1100;  /**< PHY Enable. */
} EthTrcv_30_Tja1100_EthTrcvTja1100Type;

/**   \brief  type used in EthTrcv_30_Tja1100_UserAccessCallouts */
typedef struct sEthTrcv_30_Tja1100_UserAccessCalloutsType
{
  EthTrcv_30_Tja1100_UserPreTrcvReadCalloutsFctPtrType PreTrcvReadAccessCalloutOfUserAccessCallouts;  /**< Pre-Transceiver Read Access callout */
  EthTrcv_30_Tja1100_UserPreTrcvWriteCalloutsFctPtrType PreTrcvWriteAccessCalloutOfUserAccessCallouts;  /**< Pre-Transceiver Write Access callout */
} EthTrcv_30_Tja1100_UserAccessCalloutsType;

/**   \brief  type used in EthTrcv_30_Tja1100_UserInitCallouts */
typedef struct sEthTrcv_30_Tja1100_UserInitCalloutsType
{
  EthTrcv_30_Tja1100_UserPostTrcvInitCalloutFctPtrType PostInitUserCalloutOfUserInitCallouts;  /**< Post-Transceiver-Initialization callout */
  EthTrcv_30_Tja1100_UserPreTrcvInitCalloutFctPtrType PreInitUserCalloutOfUserInitCallouts;  /**< Pre-Transceiver-Initialization callout */
} EthTrcv_30_Tja1100_UserInitCalloutsType;

/**   \brief  type used in EthTrcv_30_Tja1100_Wakeup */
typedef struct sEthTrcv_30_Tja1100_WakeupType
{
  EthTrcv_30_Tja1100_IcuChannelOfWakeupType IcuChannelOfWakeup;  /**< Icu channel related to wakeup signal */
  EthTrcv_30_Tja1100_WakeupCalloutIdxOfWakeupType WakeupCalloutIdxOfWakeup;  /**< the index of the 0:1 relation pointing to EthTrcv_30_Tja1100_WakeupCallout */
  EthTrcv_30_Tja1100_WakeupInspectionTypeOfWakeupType WakeupInspectionTypeOfWakeup;  /**< Inspection type method */
  EthTrcv_30_Tja1100_WakeupMapEndIdxOfWakeupType WakeupMapEndIdxOfWakeup;  /**< the end index of the 0:n relation pointing to EthTrcv_30_Tja1100_WakeupMap */
  EthTrcv_30_Tja1100_WakeupMapStartIdxOfWakeupType WakeupMapStartIdxOfWakeup;  /**< the start index of the 0:n relation pointing to EthTrcv_30_Tja1100_WakeupMap */
  EthTrcv_30_Tja1100_WakeupVerificationCalloutIdxOfWakeupType WakeupVerificationCalloutIdxOfWakeup;  /**< the index of the 0:1 relation pointing to EthTrcv_30_Tja1100_WakeupVerificationCallout */
} EthTrcv_30_Tja1100_WakeupType;

/**   \brief  type used in EthTrcv_30_Tja1100_WakeupMap */
typedef struct sEthTrcv_30_Tja1100_WakeupMapType
{
  EthTrcv_30_Tja1100_EcuMWakeupSourceOfWakeupMapType EcuMWakeupSourceOfWakeupMap;  /**< Wakeup source of EcuM */
  EthTrcv_30_Tja1100_WakeupReasonOfWakeupMapType WakeupReasonOfWakeupMap;  /**< Wakeup reason of EthTrcv */
} EthTrcv_30_Tja1100_WakeupMapType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCRootPointerTypes  EthTrcv_30_Tja1100 Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to EthTrcv_30_Tja1100_AccessEntityFcts */
typedef P2CONST(EthTrcv_30_Tja1100_AccessEntityFctsType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_AccessEntityFctsPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_EthTrcv */
typedef P2CONST(EthTrcv_30_Tja1100_EthTrcvType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_EthTrcvPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_EthTrcvTja1100 */
typedef P2CONST(EthTrcv_30_Tja1100_EthTrcvTja1100Type, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_EthTrcvTja1100PtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter */
typedef P2VAR(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout */
typedef P2CONST(EthTrcv_30_Tja1100_UserHwAccessMonitorFailureCalloutFctPtrType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_HwAccessMonitorFailureCalloutPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter */
typedef P2VAR(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter */
typedef P2VAR(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_LinkFailCounter */
typedef P2VAR(EthTrcv_30_Tja1100_LinkFailCounterType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkFailCounterPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_LinkStartupDelayCounter */
typedef P2VAR(EthTrcv_30_Tja1100_LinkStartupDelayCounterType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStartupDelayCounterPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_LinkStartupState */
typedef P2VAR(EthTrcv_30_Tja1100_LinkStartupStateType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStartupStatePtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_LinkStateDelayCounter */
typedef P2VAR(EthTrcv_30_Tja1100_LinkStateDelayCounterType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStateDelayCounterPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_LinkStateTimeoutCounter */
typedef P2VAR(EthTrcv_30_Tja1100_LinkStateTimeoutCounterType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStateTimeoutCounterPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_TrcvHwAccessibility */
typedef P2VAR(EthTrcv_30_Tja1100_HardwareAccessibilityType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvHwAccessibilityPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_TrcvLinkState */
typedef P2VAR(EthTrcv_StateType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvLinkStatePtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_TrcvMode */
typedef P2VAR(EthTrcv_ModeType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvModePtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_TrcvState */
typedef P2VAR(EthTrcv_StateType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvStatePtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_UserAccessCallouts */
typedef P2CONST(EthTrcv_30_Tja1100_UserAccessCalloutsType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_UserAccessCalloutsPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_UserInitCallouts */
typedef P2CONST(EthTrcv_30_Tja1100_UserInitCalloutsType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_UserInitCalloutsPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_Wakeup */
typedef P2CONST(EthTrcv_30_Tja1100_WakeupType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_WakeupPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_WakeupCallout */
typedef P2CONST(EthTrcv_30_Tja1100_UserWakeupCalloutFctPtrType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_WakeupCalloutPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_WakeupMap */
typedef P2CONST(EthTrcv_30_Tja1100_WakeupMapType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_WakeupMapPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_WakeupMode */
typedef P2VAR(EthTrcv_WakeupModeType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_WakeupModePtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_WakeupReasonFlags */
typedef P2VAR(EthTrcv_30_Tja1100_WakeupReasonFlagsType, TYPEDEF, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_WakeupReasonFlagsPtrType;

/**   \brief  type used to point to EthTrcv_30_Tja1100_WakeupVerificationCallout */
typedef P2CONST(EthTrcv_30_Tja1100_UserWakeupVerificationCalloutFctPtrType, TYPEDEF, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_WakeupVerificationCalloutPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCRootValueTypes  EthTrcv_30_Tja1100 Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in EthTrcv_30_Tja1100_PCConfig */
typedef struct sEthTrcv_30_Tja1100_PCConfigType
{
  EthTrcv_30_Tja1100_AccessEntityFctsPtrType AccessEntityFctsOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_AccessEntityFcts */
  EthTrcv_30_Tja1100_EthTrcvPtrType EthTrcvOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_EthTrcv */
  EthTrcv_30_Tja1100_EthTrcvTja1100PtrType EthTrcvTja1100OfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_EthTrcvTja1100 */
  EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterPtrType HwAccessMonitorCycleCounterOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter */
  EthTrcv_30_Tja1100_HwAccessMonitorFailureCalloutPtrType HwAccessMonitorFailureCalloutOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout */
  EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterPtrType HwAccessMonitorFailureDebounceCounterOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter */
  EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterPtrType HwAccessMonitorRecoveryDebounceCounterOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter */
  EthTrcv_30_Tja1100_LinkFailCounterPtrType LinkFailCounterOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_LinkFailCounter */
  EthTrcv_30_Tja1100_LinkStartupDelayCounterPtrType LinkStartupDelayCounterOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_LinkStartupDelayCounter */
  EthTrcv_30_Tja1100_LinkStartupStatePtrType LinkStartupStateOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_LinkStartupState */
  EthTrcv_30_Tja1100_LinkStateDelayCounterPtrType LinkStateDelayCounterOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_LinkStateDelayCounter */
  EthTrcv_30_Tja1100_LinkStateTimeoutCounterPtrType LinkStateTimeoutCounterOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_LinkStateTimeoutCounter */
  EthTrcv_30_Tja1100_TrcvHwAccessibilityPtrType TrcvHwAccessibilityOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_TrcvHwAccessibility */
  EthTrcv_30_Tja1100_TrcvLinkStatePtrType TrcvLinkStateOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_TrcvLinkState */
  EthTrcv_30_Tja1100_TrcvModePtrType TrcvModeOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_TrcvMode */
  EthTrcv_30_Tja1100_TrcvStatePtrType TrcvStateOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_TrcvState */
  EthTrcv_30_Tja1100_UserAccessCalloutsPtrType UserAccessCalloutsOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_UserAccessCallouts */
  EthTrcv_30_Tja1100_UserInitCalloutsPtrType UserInitCalloutsOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_UserInitCallouts */
  EthTrcv_30_Tja1100_WakeupPtrType WakeupOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_Wakeup */
  EthTrcv_30_Tja1100_WakeupCalloutPtrType WakeupCalloutOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_WakeupCallout */
  EthTrcv_30_Tja1100_WakeupMapPtrType WakeupMapOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_WakeupMap */
  EthTrcv_30_Tja1100_WakeupModePtrType WakeupModeOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_WakeupMode */
  EthTrcv_30_Tja1100_WakeupReasonFlagsPtrType WakeupReasonFlagsOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_WakeupReasonFlags */
  EthTrcv_30_Tja1100_WakeupVerificationCalloutPtrType WakeupVerificationCalloutOfPCConfig;  /**< the pointer to EthTrcv_30_Tja1100_WakeupVerificationCallout */
  EthTrcv_30_Tja1100_CableDiagLoopCyclesType CableDiagLoopCyclesOfPCConfig;  /**< Maximum tries the driver performs to get results during cable diagnostics. */
  EthTrcv_30_Tja1100_HwAccessLoopCountType HwAccessLoopCountOfPCConfig;  /**< Maximum tries the driver performs to access the hardware. */
  EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceLimiterType HwAccessMonitorFailureDebounceLimiterOfPCConfig;  /**< The debounce limiter number. The debouncing is completed when the debounce counter reaches that value */
  EthTrcv_30_Tja1100_HwAccessMonitorLoopLimiterType HwAccessMonitorLoopLimiterOfPCConfig;  /**< The loop limiter value to realize the period of the hardware access check in relation to the main function period */
  EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceLimiterType HwAccessMonitorRecoveryDebounceLimiterOfPCConfig;  /**< The debounce limiter number. The debouncing is completed when the debounce counter reaches that value */
  EthTrcv_30_Tja1100_MainFunctionLinkHandlingMsType MainFunctionLinkHandlingMsOfPCConfig;  /**< Period in milliseconds the main function for the link handling of Tja1100 is called with */
  EthTrcv_30_Tja1100_MaxPhySignalQualityMeanType MaxPhySignalQualityMeanOfPCConfig;  /**< Maximum physical signal quality mean configured for the Ethernet transceivers */
  EthTrcv_30_Tja1100_SizeOfAccessEntityFctsType SizeOfAccessEntityFctsOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_AccessEntityFcts */
  EthTrcv_30_Tja1100_SizeOfEthTrcvType SizeOfEthTrcvOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_EthTrcv */
  EthTrcv_30_Tja1100_SizeOfEthTrcvTja1100Type SizeOfEthTrcvTja1100OfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_EthTrcvTja1100 */
  EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureCalloutType SizeOfHwAccessMonitorFailureCalloutOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout */
  EthTrcv_30_Tja1100_SizeOfUserAccessCalloutsType SizeOfUserAccessCalloutsOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_UserAccessCallouts */
  EthTrcv_30_Tja1100_SizeOfUserInitCalloutsType SizeOfUserInitCalloutsOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_UserInitCallouts */
  EthTrcv_30_Tja1100_SizeOfWakeupType SizeOfWakeupOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_Wakeup */
  EthTrcv_30_Tja1100_SizeOfWakeupCalloutType SizeOfWakeupCalloutOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupCallout */
  EthTrcv_30_Tja1100_SizeOfWakeupMapType SizeOfWakeupMapOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupMap */
  EthTrcv_30_Tja1100_SizeOfWakeupVerificationCalloutType SizeOfWakeupVerificationCalloutOfPCConfig;  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupVerificationCallout */
} EthTrcv_30_Tja1100_PCConfigType;

typedef EthTrcv_30_Tja1100_PCConfigType EthTrcv_30_Tja1100_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access EthTrcv_30_Tja1100_PCConfig in a symbol based style. */
typedef struct sEthTrcv_30_Tja1100_PCConfigsType
{
  EthTrcv_30_Tja1100_PCConfigType Config;  /**< [Config] */
} EthTrcv_30_Tja1100_PCConfigsType;

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthTrcv_30_Tja1100_AccessEntityFcts
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_AccessEntityFcts
  \brief  Functions of the accesses entities to read/write transceiver registers.
  \details
  Element         Description
  ReadTrcvReg     Function to call when a read register shall be performed
  WriteTrcvReg    Function to call when a write register shall be performed
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(EthTrcv_30_Tja1100_AccessEntityFctsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_AccessEntityFcts[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_EthTrcv
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_EthTrcv
  \brief  Ethernet transceivers managed by the driver.
  \details
  Element                   Description
  BasicCtrlRegVal           Initialization value of basic control register
  AutoNegEnabled            Auto negotiation configuration
  SoftResetOnInitEnabled    Soft reset on initialization configuraiton
  AccessEntityFctsIdx       the index of the 1:1 relation pointing to EthTrcv_30_Tja1100_AccessEntityFcts
  AccessEntitySnv           Entity providing access to the transceiver hardware
  AddressingIdx             Addressing index in context of the access entity to address the transceiver hardware
  ConnectionNeg             Connection negotiation configuration
  DemEAccessEventId         ETHTRCV_E_ACCESS DEM event
  MiiMode                   Mii interface
  PhySignalQualityMean      Mean value of phyisical signal quality
  SoCBaseRegAddr            Base register address within memory space of SoC in case PHY is integrated as module into SoC.
  SoftResetWaitCycles       Soft reset wait cycles
  Speed                     Transceiver speed
  WakeupIdx                 the index of the 0:1 relation pointing to EthTrcv_30_Tja1100_Wakeup
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(EthTrcv_30_Tja1100_EthTrcvType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_EthTrcv[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_EthTrcvTja1100
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_EthTrcvTja1100
  \brief  Tja1100 specific configuration data.
  \details
  Element                     Description
  ExtLinkStateCheckEnabled    Extended link state check configuration.
  ClkMode                     Clock mode.
  Derivative                  Tja110x derivative.
  IntRevMii                   Internal Reverse MII.
  LdoMode                     LDO mode.
  LinkFailCounterResetVal     Initialization value for link fail counter
  LinkStartupDelay            Delay till link initialization is triggered after transceiver is enabled.
  P0MiiAddress                MII address of P0.
  P0PortSnv                   SNV of port used to access P0.
  P0SwitchSnv                 SNV of switch used to access P0.
  PhyEnable                   PHY Enable.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(EthTrcv_30_Tja1100_EthTrcvTja1100Type, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_EthTrcvTja1100[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
  \brief  Hardware access monitor failure callouts to application.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(EthTrcv_30_Tja1100_UserHwAccessMonitorFailureCalloutFctPtrType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_UserAccessCallouts
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_UserAccessCallouts
  \brief  pretransceiver read/write access callouts to application.
  \details
  Element                      Description
  PreTrcvReadAccessCallout     Pre-Transceiver Read Access callout
  PreTrcvWriteAccessCallout    Pre-Transceiver Write Access callout
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(EthTrcv_30_Tja1100_UserAccessCalloutsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_UserAccessCallouts[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_UserInitCallouts
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_UserInitCallouts
  \brief  Pre-/Post-Transceiver-Initialization callouts to application.
  \details
  Element                Description
  PostInitUserCallout    Post-Transceiver-Initialization callout
  PreInitUserCallout     Pre-Transceiver-Initialization callout
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(EthTrcv_30_Tja1100_UserInitCalloutsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_UserInitCallouts[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter
  \brief  The Wakeup reason cycle Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter;  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter
  \brief  Performs debouncing for the Hw access feature before triggering the error reaction
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter
  \brief  Performs debouncing for the Hw access feature before triggering the error recovery
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkFailCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkFailCounter
  \brief  Link fail counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_LinkFailCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkFailCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStartupDelayCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStartupDelayCounter
  \brief  Link Startup Delay Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_LinkStartupDelayCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStartupDelayCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStartupState
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStartupState
  \brief  Link Startup State
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_LinkStartupStateType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStartupState[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStateDelayCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStateDelayCounter
  \brief  Link State Delay Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_LinkStateDelayCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStateDelayCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStateTimeoutCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStateTimeoutCounter
  \brief  Link State Timeout Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_LinkStateTimeoutCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStateTimeoutCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvHwAccessibility
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvHwAccessibility
  \brief  Transceiver hardware accessibility
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_30_Tja1100_HardwareAccessibilityType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvHwAccessibility[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvLinkState
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvLinkState
  \brief  Transceiver link state.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_StateType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvLinkState[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvMode
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvMode
  \brief  Transceiver operating mode.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_ModeType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvMode[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvState
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvState
  \brief  Transceiver initialization state.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(EthTrcv_StateType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvState[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_PCConfig
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_PCConfig
  \details
  Element                                   Description
  AccessEntityFcts                          the pointer to EthTrcv_30_Tja1100_AccessEntityFcts
  EthTrcv                                   the pointer to EthTrcv_30_Tja1100_EthTrcv
  EthTrcvTja1100                            the pointer to EthTrcv_30_Tja1100_EthTrcvTja1100
  HwAccessMonitorCycleCounter               the pointer to EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter
  HwAccessMonitorFailureCallout             the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
  HwAccessMonitorFailureDebounceCounter     the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter
  HwAccessMonitorRecoveryDebounceCounter    the pointer to EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter
  LinkFailCounter                           the pointer to EthTrcv_30_Tja1100_LinkFailCounter
  LinkStartupDelayCounter                   the pointer to EthTrcv_30_Tja1100_LinkStartupDelayCounter
  LinkStartupState                          the pointer to EthTrcv_30_Tja1100_LinkStartupState
  LinkStateDelayCounter                     the pointer to EthTrcv_30_Tja1100_LinkStateDelayCounter
  LinkStateTimeoutCounter                   the pointer to EthTrcv_30_Tja1100_LinkStateTimeoutCounter
  TrcvHwAccessibility                       the pointer to EthTrcv_30_Tja1100_TrcvHwAccessibility
  TrcvLinkState                             the pointer to EthTrcv_30_Tja1100_TrcvLinkState
  TrcvMode                                  the pointer to EthTrcv_30_Tja1100_TrcvMode
  TrcvState                                 the pointer to EthTrcv_30_Tja1100_TrcvState
  UserAccessCallouts                        the pointer to EthTrcv_30_Tja1100_UserAccessCallouts
  UserInitCallouts                          the pointer to EthTrcv_30_Tja1100_UserInitCallouts
  Wakeup                                    the pointer to EthTrcv_30_Tja1100_Wakeup
  WakeupCallout                             the pointer to EthTrcv_30_Tja1100_WakeupCallout
  WakeupMap                                 the pointer to EthTrcv_30_Tja1100_WakeupMap
  WakeupMode                                the pointer to EthTrcv_30_Tja1100_WakeupMode
  WakeupReasonFlags                         the pointer to EthTrcv_30_Tja1100_WakeupReasonFlags
  WakeupVerificationCallout                 the pointer to EthTrcv_30_Tja1100_WakeupVerificationCallout
  CableDiagLoopCycles                       Maximum tries the driver performs to get results during cable diagnostics.
  HwAccessLoopCount                         Maximum tries the driver performs to access the hardware.
  HwAccessMonitorFailureDebounceLimiter     The debounce limiter number. The debouncing is completed when the debounce counter reaches that value
  HwAccessMonitorLoopLimiter                The loop limiter value to realize the period of the hardware access check in relation to the main function period
  HwAccessMonitorRecoveryDebounceLimiter    The debounce limiter number. The debouncing is completed when the debounce counter reaches that value
  MainFunctionLinkHandlingMs                Period in milliseconds the main function for the link handling of Tja1100 is called with
  MaxPhySignalQualityMean                   Maximum physical signal quality mean configured for the Ethernet transceivers
  SizeOfAccessEntityFcts                    the number of accomplishable value elements in EthTrcv_30_Tja1100_AccessEntityFcts
  SizeOfEthTrcv                             the number of accomplishable value elements in EthTrcv_30_Tja1100_EthTrcv
  SizeOfEthTrcvTja1100                      the number of accomplishable value elements in EthTrcv_30_Tja1100_EthTrcvTja1100
  SizeOfHwAccessMonitorFailureCallout       the number of accomplishable value elements in EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
  SizeOfUserAccessCallouts                  the number of accomplishable value elements in EthTrcv_30_Tja1100_UserAccessCallouts
  SizeOfUserInitCallouts                    the number of accomplishable value elements in EthTrcv_30_Tja1100_UserInitCallouts
  SizeOfWakeup                              the number of accomplishable value elements in EthTrcv_30_Tja1100_Wakeup
  SizeOfWakeupCallout                       the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupCallout
  SizeOfWakeupMap                           the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupMap
  SizeOfWakeupVerificationCallout           the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupVerificationCallout
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(EthTrcv_30_Tja1100_PCConfigsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_PCConfig;
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */



#endif /* ETHTRCV_30_TJA1100_GENTYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_GenTypes.h
 *********************************************************************************************************************/


