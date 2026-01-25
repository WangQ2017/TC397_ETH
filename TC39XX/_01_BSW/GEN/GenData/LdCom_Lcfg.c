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
 *              File: LdCom_Lcfg.c
 *   Generation Time: 2026-01-25 10:17:57
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
#define LDCOM_LCFG_SOURCE

/**********************************************************************************************************************
 *  LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "LdCom.h"
#include "LdCom_Lcfg.h"

#include "Rte_Cbk.h"

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
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  LdCom_IfRxIndicationFctPtr
**********************************************************************************************************************/
/** 
  \var    LdCom_IfRxIndicationFctPtr
  \brief  Upper layer communication interface Rx indication function pointer according DefinitionRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComRxIndication
*/ 
#define LDCOM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(LdCom_IfRxIndicationFctPtrType, LDCOM_CONST) LdCom_IfRxIndicationFctPtr[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     IfRxIndicationFctPtr                           Referable Keys */
  /*     0 */ Rte_LdComCbkRxIndication_VechicleSpeedRx  ,  /* [/ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleSpeedRx[0:LdComRxIndication]] */
  /*     1 */ Rte_LdComCbkRxIndication_VechicleStatusRx    /* [/ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleStatusRx[0:LdComRxIndication]] */
};
#define LDCOM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  LdCom_RxTxPduInfo
**********************************************************************************************************************/
/** 
  \var    LdCom_RxTxPduInfo
  \brief  Table containing mapping data from Input handles to PduR Tx handles/RTE callbacks.
  \details
  Element                    Description
  IfPdu                  
  TxPdu                  
  IfRxIndicationFctPtrIdx    the index of the 0:1 relation pointing to LdCom_IfRxIndicationFctPtr
  PduRTxHandleId             Handle ID used to call PduR_LdComTransmit()
*/ 
#define LDCOM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(LdCom_RxTxPduInfoType, LDCOM_CONST) LdCom_RxTxPduInfo[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IfPdu  TxPdu  IfRxIndicationFctPtrIdx                        PduRTxHandleId                                   Referable Keys */
  { /*     0 */  TRUE,  TRUE, LDCOM_NO_IFRXINDICATIONFCTPTRIDXOFRXTXPDUINFO, PduRConf_PduRSrcPdu_PduRSrcPdu_EcuStateTx },  /* [/ActiveEcuC/LdCom/LdComConfig/LdComIPdu_EcuStateTx] */
  { /*     1 */  TRUE,  TRUE, LDCOM_NO_IFRXINDICATIONFCTPTRIDXOFRXTXPDUINFO, PduRConf_PduRSrcPdu_PduRSrcPdu_SenStateTx },  /* [/ActiveEcuC/LdCom/LdComConfig/LdComIPdu_SenStateTx] */
  { /*     2 */  TRUE, FALSE,                                            0u,                                        0u },  /* [/ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleSpeedRx] */
  { /*     3 */  TRUE, FALSE,                                            1u,                                        0u }   /* [/ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleStatusRx] */
};
#define LDCOM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  LdCom_Initialized
**********************************************************************************************************************/
/** 
  \var    LdCom_Initialized
  \brief  Initialization state of LdCom. TRUE, if initialized.
*/ 
#define LDCOM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(LdCom_InitializedType, LDCOM_VAR_ZERO_INIT) LdCom_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define LDCOM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: LdCom_Lcfg.c
 *********************************************************************************************************************/
