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
 *              File: LdCom_PBcfg.h
 *   Generation Time: 2026-05-01 18:57:24
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
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_EcuStateTx[0:LdComSystemTemplateSignalRef](value={empty}) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_SenStateTx[0:LdComSystemTemplateSignalRef](value={empty}) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleSpeedRx[0:LdComSystemTemplateSignalRef](value={empty}) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleStatusRx[0:LdComSystemTemplateSignalRef](value={empty}) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 *********************************************************************************************************************/

#if !defined (LDCOM_PBCFG_H)
# define LDCOM_PBCFG_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  LdComPBDataSwitches  LdCom Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define LDCOM_PBCONFIG                                                                              STD_OFF  /**< Deactivateable: 'LdCom_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define LDCOM_LTCONFIGIDXOFPBCONFIG                                                                 STD_OFF  /**< Deactivateable: 'LdCom_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define LDCOM_PCCONFIGIDXOFPBCONFIG                                                                 STD_OFF  /**< Deactivateable: 'LdCom_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
/** 
  \}
*/ 



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
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


#endif  /* LDCOM_PBCFG_H */
/**********************************************************************************************************************
 *  END OF FILE: LdCom_PBcfg.h
 *********************************************************************************************************************/

