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
 *            Module: EcuM
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EcuM_Callout_Stubs.c
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

#include "Rte_Cbk.h"
#include "Appl_Cbk.h"

/* ldcom cbk */
FUNC(void, RTE_CODE) Rte_LdComCbkRxIndication_VechicleSpeedRx(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{

}

FUNC(void, RTE_CODE) Rte_LdComCbkRxIndication_VechicleStatusRx(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{

}

/* com cbk */
FUNC(void, COM_APPL_CODE) Com_Cbk_FalutInfoTx(void)
{

}

FUNC(void, COM_APPL_CODE) Com_Cbk_VechicleInfoRx(void)
{

}