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
 *            Module: LdCom
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: LdCom_Cfg.h
 *   Generation Time: 2026-01-24 23:51:59
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * WARNING: This code has been generated with reduced-severity errors. 
 * The created output files contain errors that have been ignored. Usage of the created files can lead to unpredictable behavior of the embedded code.
 * Usage of the created files happens at own risk!
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_EcuStateTx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_SenStateTx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleSpeedRx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleStatusRx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 *********************************************************************************************************************/

#if !defined (LDCOM_CFG_H)
# define LDCOM_CFG_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* General defines */
#ifndef LDCOM_USE_DUMMY_STATEMENT
#define LDCOM_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef LDCOM_DUMMY_STATEMENT
#define LDCOM_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef LDCOM_DUMMY_STATEMENT_CONST
#define LDCOM_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef LDCOM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define LDCOM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef LDCOM_ATOMIC_VARIABLE_ACCESS
#define LDCOM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef LDCOM_PROCESSOR_TC397X_STEPB
#define LDCOM_PROCESSOR_TC397X_STEPB
#endif
#ifndef LDCOM_COMP_TASKING
#define LDCOM_COMP_TASKING
#endif
#ifndef LDCOM_GEN_GENERATOR_MSR
#define LDCOM_GEN_GENERATOR_MSR
#endif
#ifndef LDCOM_CPUTYPE_BITORDER_LSB2MSB
#define LDCOM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef LDCOM_CONFIGURATION_VARIANT_PRECOMPILE
#define LDCOM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef LDCOM_CONFIGURATION_VARIANT_LINKTIME
#define LDCOM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef LDCOM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define LDCOM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef LDCOM_CONFIGURATION_VARIANT
#define LDCOM_CONFIGURATION_VARIANT LDCOM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef LDCOM_POSTBUILD_VARIANT_SUPPORT
#define LDCOM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/* General API */
#define LDCOM_COMMUNICATION_INTERFACE  STD_ON  /**< /ActiveEcuC/PduR/LdCom[0:PduRCommunicationInterface] */
#define LDCOM_TRANSPORT_PROTOCOL       STD_OFF  /**< /ActiveEcuC/PduR/LdCom[0:PduRTransportProtocol] */
#define LDCOM_TRIGGER_TRANSMIT_API     STD_OFF  /**< /ActiveEcuC/PduR/LdCom[0:PduRTriggertransmit] */
#define LDCOM_TX_CONFIRMATION_API      STD_ON  /**< /ActiveEcuC/PduR/LdCom[0:PduRTxConfirmation] */

#define LDCOM_DEV_ERROR_DETECT         STD_ON  /**< /ActiveEcuC/LdCom/LdComGeneral[0:LdComSafeBswChecks] || /ActiveEcuC/LdCom/LdComGeneral[0:LdComDevErrorDetect] */
#define LDCOM_DEV_ERROR_REPORT         STD_ON  /**< /ActiveEcuC/LdCom/LdComGeneral[0:LdComDevErrorDetect] */
#define LDCOM_VERSION_INFO_API         STD_OFF  /**< /ActiveEcuC/LdCom/LdComGeneral[0:LdComVersionInfoApi] */

/* Symbolic name values (SNV) */



/**
 * \defgroup LdComHandleIdsLdComPdu Handle IDs of handle space LdComPdu.
 * \brief LdComPdu
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define LdComConf_LdComIPdu_LdComIPdu_EcuStateTx                      0u
#define LdComConf_LdComIPdu_LdComIPdu_SenStateTx                      1u
#define LdComConf_LdComIPdu_LdComIPdu_VechicleSpeedRx                 2u
#define LdComConf_LdComIPdu_LdComIPdu_VechicleStatusRx                3u
/**\} */
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

/**********************************************************************************************************************
 *  USER CONFIGURATION FILE
 *********************************************************************************************************************/
/* User Config File Start */

/* User Config File End */

#endif  /* LDCOM_CFG_H */
/**********************************************************************************************************************
 *  END OF FILE: LdCom_Cfg.h
 *********************************************************************************************************************/
