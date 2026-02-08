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
 *            Module: Dcm
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Dcm_Callout_Stubs.c
 *   Generation Time: 2025-12-20 18:14:00
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK User Version>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/*********************************************************************************************************************
    INCLUDES
 *********************************************************************************************************************/
#include "Dcm.h"
#include "Dcm_Cfg.h"


FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(
  Dcm_ProgConditionsPtrType progConditions
  )
{
    return DCM_E_OK;
}

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(
  Dcm_ProgConditionsPtrType progConditions
  )
{
    return DCM_E_OK;
}

FUNC(void, DCM_CALLOUT_CODE) Dcm_Confirmation(
  Dcm_IdContextType idContext,
  PduIdType dcmRxPduId,
  Dcm_ConfirmationStatusType status
  )
{
    return;
}

/**********************************************************************************************************************
 *  END OF FILE: ECUM_CALLOUT_STUBS.C
 *********************************************************************************************************************/


