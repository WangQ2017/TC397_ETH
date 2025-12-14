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
 *            Module: SoAd
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: SoAd_Cfg.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined(SOAD_CFG_H)
#define SOAD_CFG_H

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
#include "Std_Types.h"


/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES (EXTERNAL USE): SOCKET CONNECTION
 *********************************************************************************************************************/



/**
 * \defgroup SoAdHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SoAdConf_SoAdSocketConnection_SC_UDP_ANY_DynPort_Remote       1u
#define SoAdConf_SoAdSocketConnection_SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote 0u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES (EXTERNAL USE): PDU ROUTE PDU
 *********************************************************************************************************************/



/**
 * \defgroup SoAdHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SoAdConf_SoAdPduRoute_SoAdPduRoute_NM_Tx                      0u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES (EXTERNAL USE): SOCKET ROUTE PDU
 *********************************************************************************************************************/



/**
 * \defgroup SoAdHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define SoAdConf_SoAdSocketRouteDest_SoAdSocketRouteDest              0u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES (EXTERNAL USE): ROUTING GROUP
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES (INTERNAL USE): ADDRESS IDS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
#define SOAD_VERSION_INFO_API                   STD_OFF
#define SOAD_DEV_ERROR_REPORT                   STD_ON
#define SOAD_DEV_ERROR_DETECT                   STD_ON
#define SOAD_MAIN_FCT_CYCLE_TIME_MS             5u
#define SOAD_GET_RESET_MEASUREMENT_DATA_API     STD_OFF

/**********************************************************************************************************************
 *  MODULE SPECIFIC DEFINES
 *********************************************************************************************************************/
#ifndef SOAD_USE_DUMMY_STATEMENT
#define SOAD_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef SOAD_DUMMY_STATEMENT
#define SOAD_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef SOAD_DUMMY_STATEMENT_CONST
#define SOAD_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef SOAD_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define SOAD_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef SOAD_ATOMIC_VARIABLE_ACCESS
#define SOAD_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef SOAD_PROCESSOR_TC397X_STEPB
#define SOAD_PROCESSOR_TC397X_STEPB
#endif
#ifndef SOAD_COMP_TASKING
#define SOAD_COMP_TASKING
#endif
#ifndef SOAD_GEN_GENERATOR_MSR
#define SOAD_GEN_GENERATOR_MSR
#endif
#ifndef SOAD_CPUTYPE_BITORDER_LSB2MSB
#define SOAD_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef SOAD_CONFIGURATION_VARIANT_PRECOMPILE
#define SOAD_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef SOAD_CONFIGURATION_VARIANT_LINKTIME
#define SOAD_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef SOAD_CONFIGURATION_VARIANT
#define SOAD_CONFIGURATION_VARIANT SOAD_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef SOAD_POSTBUILD_VARIANT_SUPPORT
#define SOAD_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/* User Config File Start */

/* User Config File End */


#define SOAD_SOCKET_API_AUTOSAR                 0u
#define SOAD_SOCKET_API_LINUX                   1u
#define SOAD_SOCKET_API_QNX                     2u
#define SOAD_SOCKET_API_INTEGRITY               3u

#define SOAD_SOCKET_API                         SOAD_SOCKET_API_AUTOSAR
#define SOAD_SINGLE_MAIN_FUNCTION               STD_ON
#define SOAD_TX_DYN_LEN                         STD_OFF
#define SOAD_IPV6                               STD_OFF
#define SOAD_TCP                                STD_OFF
#define SOAD_DHCPV4_CLIENT_ENABLED              STD_OFF
#define SOAD_DHCPV6_CLIENT_ENABLED              STD_OFF
#define SOAD_SOCKET_REPORT_ERROR_ENABLED        STD_OFF

#define SOAD_SHUTDOWN_FINISHED_WAIT             400u
#define SOAD_N_PDU_UDP_TX_QUEUE_RETRY_CNT_MAIN  300u
#define SOAD_RX_BUF_SEG_SIZE_TOTAL              2u
#define SOAD_MAX_PDU_LEN                        0x000000FFuL

#endif /* SOAD_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Cfg.h
 *********************************************************************************************************************/

