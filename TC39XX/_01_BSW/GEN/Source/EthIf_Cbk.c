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

#include "EthIf_Cbk.h"
#include "Cdd_Log.h"

void EthIf_RxIndication(
        uint8                                     CtrlIdx,
        Eth_FrameType                             FrameType,
        boolean                                   IsBroadcast,
        uint8 *                                   PhysAddrPtr,
        Eth_DataType*                             DataPtr,
        uint16                                    LenByte)
{
    CDD_LOG_DEBUG("\n=== EthIf_RxIndication ===\n");
    CDD_LOG_DEBUG("Frame Type: 0x%x\n", FrameType);
    CDD_LOG_DEBUG("Is Broadcast: %s\n", IsBroadcast ? "Yes" : "No");
    CDD_LOG_DEBUG("MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", PhysAddrPtr[0], PhysAddrPtr[1], PhysAddrPtr[2], PhysAddrPtr[3], PhysAddrPtr[4], PhysAddrPtr[5]);
    CDD_LOG_DEBUG("Data Length: %u bytes\n", LenByte);
}

void EthIf_TxConfirmation(
  uint8  CtrlIdx,
  uint8  BufIdx)
{
    CDD_LOG_DEBUG("\n=== EthIf_TxConfirmation ===\n");
}