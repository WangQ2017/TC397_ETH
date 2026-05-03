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
 *             File:  Cdd_Core0.c
 *           Config:  G:/class/TC397_ETH/BSW_Config/TC397_BSW.dpa
 *        SW-C Type:  Cdd_Core0
 *  Generation Time:  2026-05-02 16:57:47
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  C-Code implementation template for SW-C <Cdd_Core0>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Cdd_Core0.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Dio.h"
#include "EthTrcv_30_Tja1100_Hw_Int.h"
#include "Cdd_Log.h"
#include "Eth_30_Tc3xx.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#define Cdd_Core0_START_SEC_CODE
#include "Cdd_Core0_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Core0_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Init_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_Core0_CODE) Cdd_Core0_Init(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Init
 *********************************************************************************************************************/
  Eth_30_Tc3xx_Init(Eth_30_Tc3xx_Config_Ptr);
  Eth_30_Tc3xx_ControllerInit(0, 0);
  Eth_30_Tc3xx_SetControllerMode(0, ETH_MODE_ACTIVE);
  EthTrcv_30_Tja1100_Init(EthTrcv_30_Tja1100_Config_Ptr);
  EthTrcv_30_Tja1100_TransceiverInit(0, 0);
  EthTrcv_30_Tja1100_SetTransceiverMode(0, ETHTRCV_MODE_ACTIVE);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Core0_Runnable10ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable10ms_doc
 *********************************************************************************************************************/

volatile uint32 Cdd_Core0_Task_10ms_Cnt = 0;
/* 以太网配置参数 */
#define ETH_CTRL_IDX            (0U)           /* 使用控制器0 */
#define ETH_MAC_HEADER_LEN      (14U)          /* MAC头部长度（目标MAC 6 + 源MAC 6 + 类型 2） */
#define ETH_MIN_PAYLOAD_LEN     (46U)          /* 以太网最小负载长度（不含FCS） */
#define ETH_MAX_FRAME_LEN       (1518U)        /* 标准以太网最大帧长（不含FCS） */

/* 测试用的MAC地址（示例） */
static const uint8 srcMacAddr[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
static const uint8 dstMacAddr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /* 广播地址 */
Std_ReturnType Eth_IntegratedTransmit(
    const uint8* sendData,
    uint16       dataLen,
    uint16       etherType,
    boolean        needConfirm)
{
    BufReq_ReturnType  bufRet;
    Std_ReturnType     txRet = E_NOT_OK;
    
    uint8*           txBufPtr = NULL_PTR;
    uint8            txBufIdx = 0U;
    uint16           txBufSize = 0U;
    
    uint16           totalFrameLen;
    uint16           actualPayloadLen;
    static uint32    internalCounter = 0U;  /* 内部计数器（用于演示） */
    
    /* ========== 步骤1: 获取发送缓冲区 ========== */
    bufRet = Eth_30_Tc3xx_ProvideTxBuffer(ETH_CTRL_IDX, &txBufIdx, &txBufPtr, &txBufSize);
    
    /* 检查是否成功获取缓冲区 */
    if (bufRet != BUFREQ_OK)
    {
        return E_NOT_OK;
    }
    /* 检查缓冲区指针有效性 */
    if ((txBufPtr == NULL_PTR) || (txBufSize < ETH_MAC_HEADER_LEN))
    {
        return E_NOT_OK;
    }
  
    /* ========== 步骤2: 计算实际负载长度并校验 ========== */
    /* 计算可用于负载的最大长度（总缓冲区大小 - MAC头部长度） */
    uint16 maxPayloadLen = txBufSize - ETH_MAC_HEADER_LEN;
    if (sendData != NULL_PTR)
    {
        actualPayloadLen = (dataLen < maxPayloadLen) ? dataLen : maxPayloadLen;
    }
    else
    {
        actualPayloadLen = 46; /* 最小46字节（不含FCS 4字节） */
    }   
    totalFrameLen = ETH_MAC_HEADER_LEN + actualPayloadLen;
    /* ========== 步骤3: 填充MAC头部 ========== */
    /* 填充目标MAC地址（6字节） */
    for (uint16 i = 0; i < 6U; i++)
    {
        txBufPtr[i] = dstMacAddr[i];
    }
    /* 填充源MAC地址（6字节） */
    for (uint16 i = 0; i < 6U; i++)
    {
        txBufPtr[6U + i] = srcMacAddr[i];
    }
    /* 填充以太网类型（2字节，网络字节序） */
    txBufPtr[12U] = (uint8)((etherType >> 8U) & 0xFFU);
    txBufPtr[13U] = (uint8)(etherType & 0xFFU);
    /* ========== 步骤4: 填充负载数据 ========== */
    if (sendData != NULL_PTR)
    {
        (void)memcpy(txBufPtr + ETH_MAC_HEADER_LEN, sendData, actualPayloadLen);
    }
    /* ========== 步骤5: 发送以太网帧 ========== */
    txRet = Eth_30_Tc3xx_Transmit(ETH_CTRL_IDX,
                                  txBufIdx,             /* 缓冲区ID */
                                  0x800,                /* 普通数据帧类型 */
                                  needConfirm,          /* 是否需要发送确认 */
                                  totalFrameLen,        /* 帧总长度（字节） */
                                  txBufPtr);            /* 缓冲区指针 */
    if (txRet != E_OK)
    {
        return E_NOT_OK;
    }
    
    return txRet;
}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_Core0_CODE) Cdd_Core0_Runnable10ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable10ms
 *********************************************************************************************************************/
    Cdd_Core0_Task_10ms_Cnt++;
  
    uint8 testData[46] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0};
    Std_ReturnType ret;
    
    /* 发送自定义数据，以太网类型为0x1234（自定义协议），不需要确认 */
    ret = Eth_IntegratedTransmit(testData, sizeof(testData), 0x1134, FALSE);


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Core0_Runnable1ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 1ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable1ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_Core0_CODE) Cdd_Core0_Runnable1ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable1ms
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Core0_Runnable20ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 20ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable20ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_Core0_CODE) Cdd_Core0_Runnable20ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable20ms
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Cdd_Core0_Runnable5ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 5ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable5ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_Core0_CODE) Cdd_Core0_Runnable5ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Cdd_Core0_Runnable5ms
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define Cdd_Core0_STOP_SEC_CODE
#include "Cdd_Core0_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


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
