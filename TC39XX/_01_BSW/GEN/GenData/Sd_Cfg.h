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
 *            Module: Sd
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Sd_Cfg.h
 *   Generation Time: 2026-07-05 10:57:18
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined(SD_CFG_H)
#define SD_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Appl_Rand.h"

/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
#define SD_VERSION_INFO_API                                STD_OFF
#define SD_DEV_ERROR_REPORT                                STD_ON
#define SD_DEV_ERROR_DETECT                                STD_ON
#define SD_MAIN_FCT_CYCLE_TIME_MS                          5u
#define SD_DEM_EVENTS_CONFIGURED                           STD_OFF
#define SD_SET_REM_ADDR_OF_CLIENT_RX_MULTICAST_SOCON       STD_OFF

/* Random Number Function */
#define Sd_ExternalRandomNumberFct Appl_Crypto_GetRandNo



/**
 * \defgroup SdHandleIdsUnicastRxPdu Handle IDs of handle space UnicastRxPdu.
 * \brief Parameter: SdInstanceUnicastRxPdu
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SdConf_SdInstanceUnicastRxPdu_SdInstanceUnicastRxPdu          1u
/**\} */



/**
 * \defgroup SdHandleIdsMulticastRxPdu Handle IDs of handle space MulticastRxPdu.
 * \brief Parameter: SdInstanceMulticastRxPdu
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SdConf_SdInstanceMulticastRxPdu_SdInstanceMulticastRxPdu      0u
/**\} */



/**
 * \defgroup SdHandleIdsClient Handle IDs of handle space Client.
 * \brief Parameter: SdClientServiceHandleId
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SdConf_SdClientService_SdClientService_0xC3CB_VechicleSpeed   1u
#define SdConf_SdClientService_SdClientService_0xC3CC_VechicleStatus  2u
#define SdConf_SdClientService_SdClientService_0xC3CD_VechicleInfo    0u
/**\} */



/**
 * \defgroup SdHandleIdsServer Handle IDs of handle space Server.
 * \brief Parameter: SdServerServiceHandleId
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SdConf_SdServerService_SdServerService_0xC3C0_FaultInfo       1u
#define SdConf_SdServerService_SdServerService_0xC3C1_SenState        2u
#define SdConf_SdServerService_SdServerService_0xC3C2_EcuState        0u
/**\} */



/**
 * \defgroup SdHandleIdsConsumedEventGroup Handle IDs of handle space ConsumedEventGroup.
 * \brief Parameter: SdConsumedEventGroupHandleId
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CB_VechicleSpeed 0u
#define SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CC_VechicleStatus 1u
#define SdConf_SdConsumedEventGroup_SdConsumedEventGroup_0xC3CD_VechicleInfo 2u
/**\} */



/**
 * \defgroup SdHandleIdsEventHandler Handle IDs of handle space EventHandler.
 * \brief Parameter: SdEventHandlerHandleId
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SdConf_SdEventHandler_SdEventHandler_0xC3C0_FaultInfo         0u
#define SdConf_SdEventHandler_SdEventHandler_0xC3C1_SenState          1u
#define SdConf_SdEventHandler_SdEventHandler_0xC3C2_EcuState          2u
/**\} */



/**********************************************************************************************************************
 *  MODULE SPECIFIC DEFINES
 *********************************************************************************************************************/
#ifndef SD_USE_DUMMY_STATEMENT
#define SD_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef SD_DUMMY_STATEMENT
#define SD_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef SD_DUMMY_STATEMENT_CONST
#define SD_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef SD_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define SD_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef SD_ATOMIC_VARIABLE_ACCESS
#define SD_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef SD_PROCESSOR_TC397X_STEPB
#define SD_PROCESSOR_TC397X_STEPB
#endif
#ifndef SD_COMP_TASKING
#define SD_COMP_TASKING
#endif
#ifndef SD_GEN_GENERATOR_MSR
#define SD_GEN_GENERATOR_MSR
#endif
#ifndef SD_CPUTYPE_BITORDER_LSB2MSB
#define SD_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef SD_CONFIGURATION_VARIANT_PRECOMPILE
#define SD_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef SD_CONFIGURATION_VARIANT_LINKTIME
#define SD_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef SD_CONFIGURATION_VARIANT
#define SD_CONFIGURATION_VARIANT SD_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef SD_POSTBUILD_VARIANT_SUPPORT
#define SD_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

/**********************************************************************************************************************
 *  USER CONFIG FILE CONTENT
 *********************************************************************************************************************/
/* User Config File Start */

/* User Config File End */


#endif /* SD_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Sd_Cfg.h
 *********************************************************************************************************************/
