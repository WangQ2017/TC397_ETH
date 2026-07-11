/**********************************************************************************************************************
 *  FILE REQUIRES USER MODIFICATIONS
 *  Template Scope: sections marked with Start and End comments
 *  -------------------------------------------------------------------------------------------------------------------
 *  This file includes template code that must be completed and/or adapted during BSW integration.
 *  The template code is incomplete and only intended for providing a signature and an empty implementation.
 *  It is neither intended nor qualified for use in series production without applying suitable quality measures.
 *  The template code must be completed as described in the instructions given within this file and/or in the.
 *  Technical Reference.
 *  The completed implementation must be tested with diligent care and must comply with all quality requirements which.
 *  are necessary according to the state of the art before its use.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Cdd_SomeIP.c
 *           Config:  G:/TC397_ETH/BSW_Config/TC397_BSW.dpa
 *        SW-C Type:  Cdd_SomeIP
 *  Generation Time:  2026-07-05 22:45:09
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  C-Code implementation template for SW-C <Cdd_SomeIP>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Cdd_SomeIP.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Cdd_Log.h"
#include "Com.h"
#include "LdCom.h"
#include "vstdlib.h"

static uint32 Cdd_SomeIP_ComRxVechicleInfoCnt = 0;
static uint32 Cdd_SomeIP_LdComRxVechicleSpeedCnt = 0;
static uint32 Cdd_SomeIP_LdComRxVechicleStatusCnt = 0;

static uint32 Cdd_SomeIP_ComTxFaultInfoCnt = 0;
static uint32 Cdd_SomeIP_LdComTxSenStateCnt = 0;
static uint32 Cdd_SomeIP_LdComTxEcuStateCnt = 0;

volatile static uint8 Cdd_SomeIP_ComRxVechicleInfoPayload[4] = {0};
volatile static uint8 Cdd_SomeIP_LdComRxVechicleSpeedPayload[16] = {0};
volatile static uint8 Cdd_SomeIP_LdComRxVechicleStatusPayload[16] = {0};
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#define Cdd_SomeIP_START_SEC_CODE
#include "Cdd_SomeIP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_SomeIP_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_SomeIP_Init_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_SomeIP_CODE) Cdd_SomeIP_Init(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_SomeIP_Init
 *********************************************************************************************************************/
    Cdd_SomeIP_ComRxVechicleInfoCnt = 0;
    Cdd_SomeIP_LdComRxVechicleSpeedCnt = 0;
    Cdd_SomeIP_LdComRxVechicleStatusCnt = 0;

    Cdd_SomeIP_ComTxFaultInfoCnt = 0;
    Cdd_SomeIP_LdComTxSenStateCnt = 0;
    Cdd_SomeIP_LdComTxEcuStateCnt = 0;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_SomeIP_Runnable100ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 100ms
 *
 **********************************************************************************************************************
 *
 * Mode Interfaces:
 * ================
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdClientServiceState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdClientServiceState(void)
 *   Modes of Rte_ModeType_SDC_SdClientServiceState:
 *   - RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE
 *   - RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN
 *   - RTE_TRANSITION_SDC_SdClientServiceState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdClientServiceState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdClientServiceState(void)
 *   Modes of Rte_ModeType_SDC_SdClientServiceState:
 *   - RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE
 *   - RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN
 *   - RTE_TRANSITION_SDC_SdClientServiceState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdClientServiceState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdClientServiceState(void)
 *   Modes of Rte_ModeType_SDC_SdClientServiceState:
 *   - RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE
 *   - RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN
 *   - RTE_TRANSITION_SDC_SdClientServiceState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CB_VechicleSpeed_CEG_BswM_MDGP_SDC_SdConsumedEventGroupState(void)
 *   Modes of Rte_ModeType_SDC_SdConsumedEventGroupState:
 *   - RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE
 *   - RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN
 *   - RTE_TRANSITION_SDC_SdConsumedEventGroupState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CC_VechicleStatus_CEG_BswM_MDGP_SDC_SdConsumedEventGroupState(void)
 *   Modes of Rte_ModeType_SDC_SdConsumedEventGroupState:
 *   - RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE
 *   - RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN
 *   - RTE_TRANSITION_SDC_SdConsumedEventGroupState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CD_VechicleInfo_CEG_BswM_MDGP_SDC_SdConsumedEventGroupState(void)
 *   Modes of Rte_ModeType_SDC_SdConsumedEventGroupState:
 *   - RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE
 *   - RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN
 *   - RTE_TRANSITION_SDC_SdConsumedEventGroupState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C0_FaultInfo_EH_BswM_MDGP_SDC_SdEventHandlerState(void)
 *   Modes of Rte_ModeType_SDC_SdEventHandlerState:
 *   - RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED
 *   - RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED
 *   - RTE_TRANSITION_SDC_SdEventHandlerState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C1_SenState_EH_BswM_MDGP_SDC_SdEventHandlerState(void)
 *   Modes of Rte_ModeType_SDC_SdEventHandlerState:
 *   - RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED
 *   - RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED
 *   - RTE_TRANSITION_SDC_SdEventHandlerState
 *   uint8 Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C2_EcuState_EH_BswM_MDGP_SDC_SdEventHandlerState(void)
 *   Modes of Rte_ModeType_SDC_SdEventHandlerState:
 *   - RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED
 *   - RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED
 *   - RTE_TRANSITION_SDC_SdEventHandlerState
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_SomeIP_Runnable100ms_doc
 *********************************************************************************************************************/
static void Cdd_SomeIP_ComTxFaultInfo(void)
{
    uint8 payload[4] = {0xA5, 0xA5, 0xA5, 0xA5};

    (void)Com_SendSignal(ComConf_ComGroupSignal_ComGroupSignal_FaultInfoTx_Byte0, &payload[0]);
    (void)Com_SendSignal(ComConf_ComGroupSignal_ComGroupSignal_FaultInfoTx_Byte1, &payload[1]);
    (void)Com_SendSignal(ComConf_ComGroupSignal_ComGroupSignal_FaultInfoTx_Byte2, &payload[2]);
    (void)Com_SendSignal(ComConf_ComGroupSignal_ComGroupSignal_FaultInfoTx_Byte3, &payload[3]);

    if (Com_SendSignalGroup(ComConf_ComSignalGroup_ComSignalGroup_FaultInfoTx) == E_OK)
    {
      Com_TriggerIPDUSend(ComConf_ComIPdu_ComIPdu_FaultInfoTx);
      Cdd_SomeIP_ComTxFaultInfoCnt++;
    }
    else
    {
      CDD_LOG_ERROR("Cdd_SomeIP_ComRxVechicleInfo Send Fail!");
    }
}

static void Cdd_SomeIP_LdComTxSenState(void)
{
    PduInfoType pduInfo;
    Std_ReturnType retVal;
    uint8 payload[16] = {0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE};

    pduInfo.SduDataPtr = payload;
    pduInfo.SduLength = sizeof(payload);

    retVal = LdCom_Transmit(LdComConf_LdComIPdu_LdComIPdu_SenStateTx, &pduInfo);
    if (retVal == E_OK)
    {
      Cdd_SomeIP_LdComTxSenStateCnt++;
    }
    else
    {
        CDD_LOG_ERROR("Cdd_SomeIP_LdComTxSenState Send Fail!");
    }
}

static void Cdd_SomeIP_LdComTxEcuState(void)
{
    PduInfoType pduInfo;
    Std_ReturnType retVal;
    uint8 payload[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pduInfo.SduDataPtr = payload;
    pduInfo.SduLength = sizeof(payload);

    retVal = LdCom_Transmit(LdComConf_LdComIPdu_LdComIPdu_EcuStateTx, &pduInfo);
    if (retVal == E_OK)
    {
      Cdd_SomeIP_LdComTxEcuStateCnt++;
    }
    else
    {
        CDD_LOG_ERROR("Cdd_SomeIP_LdComTxEcuState Send Fail!");
    }
}

void Cdd_SomeIP_LdComRx_VechicleSpeed(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
    uint8 state = Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CB_VechicleSpeed_BswM_MDGP_SDC_SdConsumedEventGroupState();
    if (state == RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE)
    {
        Cdd_SomeIP_LdComRxVechicleSpeedCnt++;

        VStdMemCpy(&Cdd_SomeIP_LdComRxVechicleSpeedPayload[0], PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
        // CDD_LOG_DEBUG("Cdd_SomeIP_LdComRx_VechicleSpeed: %02X %02X %02X %02X (#%u)", 
        //    PduInfoPtr->SduDataPtr[0], PduInfoPtr->SduDataPtr[1], PduInfoPtr->SduDataPtr[2], PduInfoPtr->SduDataPtr[3], Cdd_SomeIP_LdComRxVechicleSpeedCnt);
    }
}

void Cdd_SomeIP_LdComRx_VechicleStatus(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
    uint8 state = Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CC_VechicleStatus_BswM_MDGP_SDC_SdConsumedEventGroupState();
    if (state == RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE)
    {
        Cdd_SomeIP_LdComRxVechicleStatusCnt++;

        VStdMemCpy(&Cdd_SomeIP_LdComRxVechicleStatusPayload[0], PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
        // CDD_LOG_DEBUG("Cdd_SomeIP_LdComRx_VechicleStatus: %02X %02X %02X %02X (#%u)", 
        //    PduInfoPtr->SduDataPtr[0], PduInfoPtr->SduDataPtr[1], PduInfoPtr->SduDataPtr[2], PduInfoPtr->SduDataPtr[3], Cdd_SomeIP_LdComRxVechicleStatusCnt);
    }
}

static void Cdd_SomeIP_ComRxVechicleInfo(void)
{
    uint8 byte0;
    uint8 byte1;
    uint8 byte2;
    uint8 byte3;

    if (Com_ReceiveSignalGroup(ComConf_ComSignalGroup_ComSignalGroup_VechicleInfoRx) != E_OK)
    {
      return;
    }

    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComGroupSignal_VechicleInfoRx_byte0, &byte0);
    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComGroupSignal_VechicleInfoRx_byte1, &byte1);
    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComGroupSignal_VechicleInfoRx_byte2, &byte2);
    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComGroupSignal_VechicleInfoRx_byte3, &byte3);

    Cdd_SomeIP_ComRxVechicleInfoCnt++;
    if ((Cdd_SomeIP_ComRxVechicleInfoCnt == 1) || ((Cdd_SomeIP_ComRxVechicleInfoCnt % 10) == 0))
    {
      Cdd_SomeIP_ComRxVechicleInfoPayload[0] = byte0;
      Cdd_SomeIP_ComRxVechicleInfoPayload[1] = byte1;
      Cdd_SomeIP_ComRxVechicleInfoPayload[2] = byte2;
      Cdd_SomeIP_ComRxVechicleInfoPayload[3] = byte3; 
      // CDD_LOG_DEBUG("Cdd_SomeIP_ComRxVechicleInfo : %02X %02X %02X %02X (#%u)", byte0, byte1, byte2, byte3, Cdd_SomeIP_ComRxVechicleInfoCnt);
    }
}

void Cdd_SomeIP_ComNotify_VechicleInfoRx(void)
{
    uint8 state = Rte_Mode_BswM_MSI_SDC_SdConsumedEventGroupState_0xC3CD_VechicleInfo_BswM_MDGP_SDC_SdConsumedEventGroupState();
    if (state == RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE)
    {
      Cdd_SomeIP_ComRxVechicleInfo();
    }
}
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_SomeIP_CODE) Cdd_SomeIP_Runnable_100ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_SomeIP_Runnable100ms
 *********************************************************************************************************************/
    uint8 state;

    state = Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C0_FaultInfo_BswM_MDGP_SDC_SdEventHandlerState();
    if (state == RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED)
    {
      Cdd_SomeIP_ComTxFaultInfo();
    }

    state = Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C1_SenState_BswM_MDGP_SDC_SdEventHandlerState();
    if (state == RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED)
    {
      Cdd_SomeIP_LdComTxSenState();
    }

    state = Rte_Mode_BswM_MSI_SDC_SdEventHandlerState_0xC3C2_EcuState_BswM_MDGP_SDC_SdEventHandlerState();
    if (state == RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED)
    {
      Cdd_SomeIP_LdComTxEcuState();
    }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define Cdd_SomeIP_STOP_SEC_CODE
#include "Cdd_SomeIP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0624:  MISRA rule: Rule8.3
     Reason:     This MISRA violation is a consequence from the RTE requirements [SWS_Rte_01007] [SWS_Rte_01150].
                 The typedefs are never used in the same context.
     Risk:       No functional risk. Only a cast to uint8* is performed.
     Prevention: Not required.

   MD_Rte_3206:  MISRA rule: Rule2.7
     Reason:     The parameter are not used by the code in all possible code variants.
     Risk:       No functional risk.
     Prevention: Not required.

*/
