/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTSyn_Pdelay_Int.c
 *        \brief  EthTSyn Path Delay source file - Internal Functions
 *      \details  EthTSyn Path Delay source file containing the EthTSyn Path Delay implementation of the EthTSyn
 *                module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define ETHTSYN_PDELAY_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Pdelay_Int.h" /* PRQA S 0883, 3219 */ /* MD_EthTSyn_0883, MD_EthTSyn_3219 */
#include "EthTSyn_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
#include "EthTSyn_Util_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
# include "EthTSyn_TimeValidation_Int.h"
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (2u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn_Pdelay_Int.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (2u)) )
# error "Version numbers of EthTSyn_Pdelay_Int.c and EthTSyn_Cfg.h are inconsistent!"
#endif

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
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInternal
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Pdelay.
 *  \details    Initializes all component variables directly related to the passed Pdelay.
 *  \param[in]  PdelayIdx  Index of the Pdelay
 *                         [range: PdelayIdx < EthTSyn_GetSizeOfPdelayConfig()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInternal(
  EthTSyn_PdelayConfigIterType PdelayIdx);

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY INITIATOR
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInitiator
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Pdelay initiator.
 *  \details    Initializes all component variables directly related to the passed Pdelay initiator.
 *  \param[in]  PdelayInitiatorIdx  Index of the Pdelay initiator
 *                                  [range: PdelayInitiatorIdx < EthTSyn_GetSizeOfPdelayInitiator()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInitiator(
  EthTSyn_PdelayInitiatorIterType PdelayInitiatorIdx);


/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayReqMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a Pdelay Request message.
 *  \details    Transmits a Pdelay Request message on the passed Port. This includes getting a TxBuffer.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraints for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                       EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                       EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayReqMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer
 *********************************************************************************************************************/
/*! \brief      Copies a PdelayReq message to the given Tx buffer in Network-Byte-Order.
 *  \details    -
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out] TxBufPtr        The assembled PdelayReq message in Network-Byte-Order
 *              the PdelayReq message.
 *  \pre        Constraints for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                       EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                       EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer(
  EthTSyn_IntPortIdxType PortIdx, ETHTSYN_P2VAR(uint8) TxBufPtr);


/**********************************************************************************************************************
 *  EthTSyn_Pdelay_CheckForPdelayRespTimeout
 *********************************************************************************************************************/
/*! \brief      Checks if a PdelayResp or PdelayRespFollowUp timeout occurred and handles the timeout.
 *  \details    -
 *  \param[in]  PortIdx         Index of the used port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Transmission of new PdelayReq should be triggered
 *  \return     FALSE - No transmission of new PdelayReq required
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Pdelay_CheckForPdelayRespTimeout(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TriggerPdelayCalculation
 *********************************************************************************************************************/
/*! \brief      Triggers the calculation of a new Pdelay.
 *  \details    Checks if a new Pdelay value can be computed. If so triggers the calculation of the new Pdelay.
 *  \param[in]  PortIdx         Index of the port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_TriggerPdelayCalculation(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ComputePdelay
 *********************************************************************************************************************/
/*! \brief      Calculates the path delay for the passed Port.
 *  \details    -
 *  \param[in]  PortIdx         Index of the used port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Calculation was successful
 *  \return     E_NOT_OK - Calculation was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_ComputePdelay(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayResp
 *********************************************************************************************************************/
/*! \brief      Checks if a Pdelay response message reception is possible.
 *  \details    Checks if a Pdelay response message can currently be received on the passed Port without respect to the
 *              Pdelay request state machine state, i.e. if the passed Port is an active Pdelay initiator.
 *  \param[in]  PortIdx   Index of the port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Ready to receive Pdelay response message
 *  \return     FALSE - Not ready to receive Pdelay response message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_ReceivePdelayResp
 *********************************************************************************************************************/
/*! \brief      Receives a Pdelay response message.
 *  \details    Checks the state of the Pdelay request state machine and performs required action for the reception
 *              of the Pdelay response message.
 *  \param[in]  PortIdx     Index of the Port the Pdelay request was received on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgPtr      Pointer to the received Pdelay response message
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       The preconditions for PortIdx can be ensured by EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(PortIdx)
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayRx_ReceivePdelayResp(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  MsgPtr);

/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup
 *********************************************************************************************************************/
/*! \brief      Checks if a Pdelay response follow up message reception is possible.
 *  \details    Checks if a Pdelay response follow up message can currently be received on the passed Port including
 *              state check of the Pdelay request state machine.
 *  \param[in]  PortIdx   Index of the port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Ready to receive Pdelay response follow up message
 *  \return     FALSE - Not ready to receive Pdelay response follow up message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  END: PDELAY INITIATOR
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY RESPONDER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayResponder
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Pdelay responder.
 *  \details    Initializes all component variables directly related to the passed Pdelay responder.
 *  \param[in]  PdelayResponderIdx  Index of the Pdelay responder
 *                                  [range: PdelayResponderIdx < EthTSyn_GetSizeOfPdelayResponder()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayResponder(
  EthTSyn_PdelayResponderIterType PdelayResponderIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a PdelayResp message.
 *  \details    Transmits a PdelayResp message on the passed port. This includes getting a TxBuffer.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer
 *********************************************************************************************************************/
/*! \brief      Copies a PdelayResp message to the provided TxBuffer in Network-Byte-Order.
 *  \details    -
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out] TxBufPtr        The assembled PdelayResp message in Network-Byte-Order
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespFupMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a PdelayResp FollowUp message.
 *  \details    Transmits a PdelayResp FollowUp message on the passed port. This includes getting a TxBuffer.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespFupMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer
 *********************************************************************************************************************/
/*! \brief      Copies a PdelayResp FollowUp message to the provided TxBuffer in Network-Byte-Order.
 *  \details    -
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *  \param[out] TxBufPtr        The assembled PdelayResp FollowUp message in Network-Byte-Order
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr);

/**********************************************************************************************************************
 *  END PDELAY RESPONDER
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInternal(
  EthTSyn_PdelayConfigIterType PdelayIdx)
{
  /* #10 Set default pdelay values. */
  EthTSyn_SetAsCapableOfPdelayInfo(PdelayIdx, (boolean)EthTSyn_IsAlwaysAsCapableOfPdelayConfig(PdelayIdx));            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
  EthTSyn_SetPdelayValueNsOfPdelayInfo(PdelayIdx, EthTSyn_GetInitialPdelayNsOfPdelayConfig(PdelayIdx));                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
  EthTSyn_SetUseAverageOfPdelayInfo(PdelayIdx, FALSE);                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */

  /* #20 Initialize Pdelay initiator. */
#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  if(EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(PdelayIdx) == TRUE)
  {
    EthTSyn_Pdelay_InitPdelayInitiator(EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(PdelayIdx));
  }
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

  /* #30 Initialize Pdelay responder. */
#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  if(EthTSyn_IsPdelayResponderUsedOfPdelayConfig(PdelayIdx) == TRUE)
  {
    EthTSyn_Pdelay_InitPdelayResponder(EthTSyn_GetPdelayResponderIdxOfPdelayConfig(PdelayIdx));
  }
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */
} /* EthTSyn_Pdelay_InitPdelayInternal() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY INITIATOR
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInitiator
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInitiator(
  EthTSyn_PdelayInitiatorIterType PdelayInitiatorIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr =
      EthTSyn_GetAddrPdelayReqSm(EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(PdelayInitiatorIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set Pdelay request state machine state to NOT_ENABLED. */
  pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_DISABLED;                                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

  /* #20 Set default values of Pdelay request state machine. */
  pDelayReqSmPtr->PdelayReq.TxIntervalCnt = EthTSyn_GetTxIntervalMfOfPdelayInitiator(PdelayInitiatorIdx);              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  pDelayReqSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  pDelayReqSmPtr->TxBuf.Address = NULL_PTR;                                                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  pDelayReqSmPtr->PdelayReq.SequenceId = 0u;                                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  pDelayReqSmPtr->TxConfirmationPending = 0;                                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  pDelayReqSmPtr->LostResponses = 0u;                                                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
} /* EthTSyn_Pdelay_InitPdelayInitiator() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayReqMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayReqMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  EthTSyn_EthTxBufferStructType txBuffer;


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is ready for transmission and get an Ethernet TxBuffer. */
  txBuffer.Length = ETHTSYN_MSG_P_DELAY_REQ_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(PortIdx, &txBuffer) == E_OK)                                                       /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    EthTSyn_PdelayReqSmPtrType pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
    ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0();

    /* #20 Reload timeout interval and increment SequenceId. */
    pDelayReqSmPtr->PdelayReq.TxIntervalCnt = EthTSyn_GetTxIntervalMfOfPdelayInitiator(pDelayInitiatorIdx);            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    pDelayReqSmPtr->PdelayReq.SequenceId++;                                                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

    /* #30 Copy PdelayReq to Ethernet TxBuffer. */
    EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer(PortIdx, txBuffer.BufferPtr);                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    /* #40 Get switch management info and frame id if applicable. */
    if(EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                      /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      mgmtInfoPtr = &mgmtInfo;
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
    pDelayReqSmPtr->PdelayReq.EgressTsMgmt.State = ETHTSYN_TS_S_PENDING;                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

    /* #50 Map the Ethernet Tx buffer for TxConfirmation. */
    pDelayReqSmPtr->TxConfirmationPending++;                                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    pDelayReqSmPtr->TxBuf.Index = txBuffer.BufferIdx;                                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    pDelayReqSmPtr->TxBuf.Address = txBuffer.BufferPtr;                                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0();

# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
    /* #60 Start a new Pdelay initiator cycle and take Pdelay reference time (if slave TimeValidation is enabled). */
    EthTSyn_TimeValid_PdReqStartCycle(PortIdx, pDelayReqSmPtr->PdelayReq.SequenceId);
    EthTSyn_TimeValid_PdReqTakeRefTimes(PortIdx);
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

    /* #70 Try to enable egress timestamp. */
    retVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS,
      mgmtInfoPtr);                                                                                                    /* SBSW_ETHTSYN_LOCAL_PTR_VAR */
    if(retVal == E_OK)
    {
      /* #700 Successfully enabled egress timestamp. */
      retVal = EthTSyn_UtilTx_Transmit(PortIdx, txBuffer.BufferIdx, ETHTSYN_MSG_P_DELAY_REQ_LENGTH);
    }

    /* #80 If transmission failed. */
    if(retVal != E_OK)
    {
      /* #800 Unmap and release Ethernet transmission buffer. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0();
      pDelayReqSmPtr->TxConfirmationPending--;                                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      pDelayReqSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      pDelayReqSmPtr->TxBuf.Address = NULL_PTR;                                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      ETHTSYN_LEAVE_CRITICAL_SECTION_0();
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_Pdelay_TxPdelayReqMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* #10 Set common header message attributes. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(TxBufPtr, ETHTSYN_MSG_TYPE_PDELAY_REQ, PortIdx);                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

  /* Pdelay request message only included reserved fields as message specific field. The hole Ethernet transmission
   * buffer is initialized with '0' by the EthTSyn therefore no action is required here. */

} /* EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_CheckForPdelayRespTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Pdelay_CheckForPdelayRespTimeout(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean txPdelayReq = FALSE;
  boolean lostResponse = FALSE;
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Pdelay request transmission interval elapsed. */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  if (pDelayReqSmPtr->PdelayReq.TxIntervalCnt == 0u)
  {
    /* #100 Interval elapsed -> mark lost response and transmission. */
    txPdelayReq = TRUE;
    lostResponse = TRUE;
  }
  else
  {
    /* #101 Interval not elapsed -> Check for Pdelay response timeout. */
    if(EthTSyn_GetRespRespFollowUpTimeoutOfPdelayInitiator(pDelayInitiatorIdx) > 0u)
    {
      if(pDelayReqSmPtr->PdelayRespRespFollowUpTimeout == 0u)
      {
        lostResponse = TRUE;
      }
    }
  }

  /* #20 Check for lost response. */
  if(lostResponse == TRUE)
  {
    /* #200 Lost response -> reset PdelayReqSm state to WAITING_FOR_PDELAY_INTERVAL_COUNTER */
    pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER;                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

    /* #201 Check for lost response limit. */
    if(pDelayReqSmPtr->LostResponses < EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(pDelayInitiatorIdx))
    {
      /* #2010 Lost response limit not exceeded -> Increment lost response counter. */
      pDelayReqSmPtr->LostResponses++;                                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
    else
    {
      /* #2011 Lost response limit exceeded -> Set AsCapable to FALSE if AlwaysAsCapable is FALSE for the Port. */
      EthTSyn_Util_SetAsCapable(PortIdx, FALSE);
    }
  }

  ETHTSYN_LEAVE_CRITICAL_SECTION_0();


  return txPdelayReq;
} /* EthTSyn_Pdelay_CheckForPdelayRespTimeout() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TriggerPdelayCalculation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_TriggerPdelayCalculation(EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that TxConfirmation for sent Pdelay request occurred. */
  if(pDelayReqSmPtr->TxConfirmationPending == 0)
  {
    /* #20 Verify that Pdelay request egress timestamp is ready for processing. */
    if(EthTSyn_Util_IsTsReadyToProc(pDelayReqSmPtr->PdelayReq.EgressTsMgmt.State) == TRUE)
    {
      /* #30 If Pdelay request egress timestamp is available. */
      if(pDelayReqSmPtr->PdelayReq.EgressTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
      {
        boolean newAsCapable = TRUE;

      /* #300 All values of Pdelay request sequence are available --> Compute new Pdelay, set AsCapable and
       *      change the state of the PdelayReqSm to WAITING_FOR_PDELAY_INTERVAL_COUNTER. */
        if(EthTSyn_IsUseStaticPdelayOfPdelayConfig(pDelayIdx) == FALSE)
        {
          newAsCapable = (boolean)(EthTSyn_Pdelay_ComputePdelay(PortIdx) == E_OK); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
        }
        EthTSyn_Util_SetAsCapable(PortIdx, newAsCapable);
      }

      /* #40 Set state of Pdelay request state machine to WAIT_TX_COUNTER. */
      pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER;                                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
  }
} /* EthTSyn_Pdelay_TriggerPdelayCalculation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ComputePdelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_ComputePdelay(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_TimediffType localResidenceTime = 0;
  EthTSyn_TimediffType remoteResidenceTime = 0;
  EthTSyn_TimediffType currentPdelay;
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* computes the mean propagation delay on the link (see also IEEE802.1AS-2011 Figure 11-1) */
  /* t1: Pdelay_Req egress timestamp (initiator), t2: Pdelay_Req ingress timestamp (responder) */
  /* t3: Pdelay_Resp egress timestamp (responder), t4: Pdelay_Resp ingress timestamp (initiator) */
  /*      (t4 - t1) - (t3 - t2)                      */
  /* D = ___________________________                 */
  /*              2                                  */

  /* #10 Compute local residence time. */
  if(EthTSyn_Util_TimestampMinusTimestamp(&pDelayReqSmPtr->PdelayResp.IngressTsMgmt.Ts,
      &pDelayReqSmPtr->PdelayReq.EgressTsMgmt.Ts, &localResidenceTime) == E_OK)                                        /* SBSW_ETHTSYN_PTR_FORWARD_STRUCT_MEMBER_AND_LOC_VAR */
  {
    /* #20 Successfully computed local residence time -> compute remote residence time. */
    if(EthTSyn_Util_TimestampMinusTimestamp(&pDelayReqSmPtr->PdelayRespFollowUp.RespOrgTs,
        &pDelayReqSmPtr->PdelayResp.RequestReceiptTimestamp, &remoteResidenceTime) == E_OK)                            /* SBSW_ETHTSYN_PTR_FORWARD_STRUCT_MEMBER_AND_LOC_VAR */
    {
      /* #30 Successfully computed remote residence time --> calculate current path delay. */
      currentPdelay = (localResidenceTime - remoteResidenceTime) / 2;
      /* #40 Perform sanity and threshold check of path delay. */
      /* PRQA S 3415 6 */ /* MD_EthTSyn_3415_CslReadOnly */
      if(
        (remoteResidenceTime >= 0) &&
        (localResidenceTime >= 0) &&
        (currentPdelay >= 0) &&
        (currentPdelay < (EthTSyn_TimediffType)EthTSyn_GetPdelayThresholdOfPdelayInitiator(pDelayInitiatorIdx))
        )
      {
        /* #50 Valid Pdelay -> apply weighted averaging. */
        const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
        EthTSyn_PdelayType tmpPdelay;

        if (EthTSyn_IsUseAverageOfPdelayInfo(pDelayIdx) == TRUE)
        {
          EthTSyn_PdelayType averageWeight = (EthTSyn_PdelayType)
            EthTSyn_GetAverageWeightOfPdelayInitiator(pDelayInitiatorIdx);
          tmpPdelay = EthTSyn_GetPdelayValueNsOfPdelayInfo(pDelayIdx);
          tmpPdelay = (EthTSyn_PdelayType)(
            (((averageWeight - 1u) * tmpPdelay) + (EthTSyn_PdelayType)currentPdelay) / averageWeight);
        }
        else
        {
          tmpPdelay = (EthTSyn_PdelayType)currentPdelay;
          EthTSyn_SetUseAverageOfPdelayInfo(pDelayIdx, TRUE);                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        }

        EthTSyn_SetPdelayValueNsOfPdelayInfo(pDelayIdx, tmpPdelay);                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
        /* #60 Store Pdelay initiator data for later reporting to the StbM (if slave TimeValidation is enabled). */
        EthTSyn_TimeValid_PdReqCopyDataFromSm(PortIdx, pDelayReqSmPtr, tmpPdelay);                                     /* SBSW_ETHTSYN_LOCAL_PTR_VAR */
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

        retVal = E_OK;
      }
    }
  }

  return retVal;
}/* EthTSyn_Pdelay_ComputePdelay() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayResp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */

ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* #10 Return TRUE if port is active pdelay port and pdelay initiator is enabled. Otherwise return FALSE. */
  return EthTSyn_Util_IsPdelayInitiator(PortIdx);
} /* EthTSyn_PdelayRx_IsReadyToReceivePdelayResp() */

/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_ReceivePdelayResp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayRx_ReceivePdelayResp(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  MsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
  boolean lostResponse = FALSE;
  uint16 pDelayRespSequenceId = IpBase_GetUint16(MsgPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS);                             /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Pdelay request state machine state. */
  if(pDelayReqSmPtr->State == ETHTSYN_S_PD_REQ_SM_WAIT_RESP)
  {
    /* #100 Waiting for Pdelay response -> continue message processing. */
    /* #101 Check for matching Sequence Id and requesting source port identity. */

    if(
      (EthTSyn_UtilRx_PortIdentityIsEqualLocalPort(PortIdx,
        &MsgPtr[ETHTSYN_MSG_PD_RESP_REQ_PORT_IDENT_OFS]) == TRUE) &&                                                   /* SBSW_ETHTSYN_ETH_RX_BUFFER_OFS_FWD */
      (pDelayRespSequenceId == pDelayReqSmPtr->PdelayReq.SequenceId)
      )
    {
      /* #1010 Store message attributes. */
      pDelayReqSmPtr->PdelayResp.SequenceId = pDelayRespSequenceId;                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      pDelayReqSmPtr->PdelayResp.SourcePortIdentity.ClockIdentity =
        IpBase_GetUint64(MsgPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS);                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
      pDelayReqSmPtr->PdelayResp.SourcePortIdentity.PortNumber =
        IpBase_GetUint16(MsgPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_PORT_NUM_OFS);                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

      pDelayReqSmPtr->PdelayResp.RequestReceiptTimestamp.secondsHi =
        IpBase_GetUint16(MsgPtr, ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_SEC_HI_OFS);                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
      pDelayReqSmPtr->PdelayResp.RequestReceiptTimestamp.seconds =
        IpBase_GetUint32(MsgPtr, ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_SEC_LOW_OFS);                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
      pDelayReqSmPtr->PdelayResp.RequestReceiptTimestamp.nanoseconds =
        IpBase_GetUint32(MsgPtr, ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_NSEC_OFS);                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

      /* #1011 Change state of the pdelay request state machine. */
      pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP;                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
    else
    {
      lostResponse = TRUE;
    }
  }
  /* #20 Check for double Pdelay response */
  else if(pDelayReqSmPtr->State == ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP)
  {
    if(pDelayReqSmPtr->PdelayReq.SequenceId == pDelayRespSequenceId)
    {
      /* #200 Received Pdelay response with same sequence id twice -> lost response. */
      lostResponse = TRUE;
    }
  }
  else
  {
    /* Nothing to do here. */
  }

  /* #30 Check for lost response. */
  if(lostResponse == TRUE)
  {
    /* #300 Invalid message attributes -> treat as lost response. */
    if(pDelayReqSmPtr->LostResponses < EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(pDelayInitiatorIdx))
    {
      pDelayReqSmPtr->LostResponses++;                                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
    else
    {
      /* #3000 Lost response limit exceeded -> Mark as not AsCapable if port is not set to 'AlwaysAsCapable'. */
      EthTSyn_Util_SetAsCapable(PortIdx, FALSE);
    }

    /* #301 Trigger re-transmission of the pdelay request */
    pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  }
} /* EthTSyn_PdelayRx_ReceivePdelayResp() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is an active Pdelay initiator. */
  if(EthTSyn_Util_IsPdelayInitiator(PortIdx) == TRUE)
  {
    /* #20 Pdelay initiator is enabled -> check State of Pdelay Request state machine. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

    if(pDelayReqSmPtr->State == ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP)
    {
      isReady = TRUE;
    }
  }

  return isReady;
} /* EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup() */

/**********************************************************************************************************************
 *  END: PDELAY INITIATOR
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY RESPONDER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayResponder
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayResponder(
  EthTSyn_PdelayResponderIterType PdelayResponderIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(PdelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr =
    EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set Pdelay response state machine state to NOT_ENABLED. */
  pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_DISABLED;                                                              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

  /* #20 Set default values of Pdelay response state machine. */
  pDelayRespSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  pDelayRespSmPtr->TxBuf.Address = NULL_PTR;                                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  pDelayRespSmPtr->TxConfirmationPending = 0;                                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
} /* EthTSyn_Pdelay_InitPdelayResponder() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_EthTxBufferStructType txBuffer;

  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get Ethernet transmission buffer. */
  txBuffer.Length = ETHTSYN_MSG_P_DELAY_RESP_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(PortIdx, &txBuffer) == E_OK)                                                       /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0();

    /* #20 Copy the Pdelay response to the Ethernet TxBuffer. */
    EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer(PortIdx, txBuffer.BufferPtr);                                            /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

    /* #40 Get switch management info if applicable. */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    if(EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                      /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      mgmtInfoPtr = &mgmtInfo;
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    pDelayRespSmPtr->PdelayResp.EgressTsMgmt.State = ETHTSYN_TS_S_PENDING;                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_WAIT_RESP_TS;                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

    /* #50 Map the Ethernet Tx buffer for later TxConfirmation. */
    pDelayRespSmPtr->TxConfirmationPending++;                                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    pDelayRespSmPtr->TxBuf.Index = txBuffer.BufferIdx;                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    pDelayRespSmPtr->TxBuf.Address = txBuffer.BufferPtr;                                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0();

    /* #60 Prepare message transmission (i.e. enable egress timestamping and set up switch mgmt info). */
    retVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS,
      mgmtInfoPtr);                                                                                                    /* SBSW_ETHTSYN_LOCAL_PTR_VAR */
    if(retVal == E_OK)
    {
      /* #600 Prepared message transmission. Trigger transmission. */
      retVal = EthTSyn_UtilTx_Transmit(PortIdx, txBuffer.BufferIdx, ETHTSYN_MSG_P_DELAY_RESP_LENGTH);
    }

    /* #70 If message transmission failed. */
    if(retVal != E_OK)
    {
      /* #700 Unmap and release the Ethernet Tx buffer. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0();
      pDelayRespSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      pDelayRespSmPtr->TxBuf.Address = NULL_PTR;                                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      pDelayRespSmPtr->TxConfirmationPending--;                                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      ETHTSYN_LEAVE_CRITICAL_SECTION_0();
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_Pdelay_TxPdelayRespMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_GlobalTimestampType) pDelayReqRcvdTsPtr =
    &pDelayRespSmPtr->PdelayReq.IngressTsMgmt.Ts;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize common message header. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(TxBufPtr, ETHTSYN_MSG_TYPE_PDELAY_RESP, PortIdx);                                 /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  /* #20 Set message specific attributes. */
  IpBase_PutUint64(TxBufPtr, ETHTSYN_MSG_PD_RESP_REQ_CLOCK_IDENTITY_OFS,
    pDelayRespSmPtr->PdelayReq.SourcePortIdentity.ClockIdentity);                                                      /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_PD_RESP_REQ_PORT_NUM_OFS,
    pDelayRespSmPtr->PdelayReq.SourcePortIdentity.PortNumber);                                                         /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  /* #30 Set request received timestamp. */
  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_SEC_HI_OFS, pDelayReqRcvdTsPtr->secondsHi);               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint32(TxBufPtr, ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_SEC_LOW_OFS, pDelayReqRcvdTsPtr->seconds);                /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint32(TxBufPtr, ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_NSEC_OFS, pDelayReqRcvdTsPtr->nanoseconds);               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
} /* EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespFupMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespFupMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_EthTxBufferStructType txBuffer;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get Ethernet transmission buffer. */
  txBuffer.Length = ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(PortIdx, &txBuffer) == E_OK)                                                       /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0();

    /* #20 Copy PdelayResp FollowUp message to TxBuffer. */
    EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer(PortIdx, txBuffer.BufferPtr);                                         /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    /* #30 Get Switch management info if required. */
    if(EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                      /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      /* #300 Get frame id if required. */
      mgmtInfoPtr = &mgmtInfo;
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0();

    /* #40 Prepare transmission (i.e. set switch mgmt info). */
    retVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_NONE, mgmtInfoPtr); /* SBSW_ETHTSYN_LOCAL_PTR_VAR */
    if(retVal == E_OK)
    {
      /* #50 Successfully prepared transmission. Trigger transmission. */
      retVal = EthTSyn_UtilTx_Transmit(PortIdx, txBuffer.BufferIdx, ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH);
    }

    if(retVal != E_OK)
    {
      /* #60 Transmission failed. Release Ethernet transmission buffer. */
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
    /* #70 Inform the time validation unit about successful transmission of the Pdelay_Resp_Fup message
     *     (if master time validation is enabled). */
    else
    {
      EthTSyn_TimeValid_PdRespPdRespFupSent(PortIdx);
    }
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */
  }

  return retVal;
} /* EthTSyn_Pdelay_TxPdelayRespFupMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_GlobalTimestampType) pDelayRespOrgTsPtr =
    &pDelayRespSmPtr->PdelayResp.EgressTsMgmt.Ts;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set common header message attributes. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(TxBufPtr, ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP, PortIdx);                        /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  /* #20 Set specific message type attributes. */
  IpBase_PutUint64(TxBufPtr, ETHTSYN_MSG_PD_RESP_FUP_REQ_CLOCK_IDENTITY_OFS,
    pDelayRespSmPtr->PdelayReq.SourcePortIdentity.ClockIdentity);                                                      /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_PD_RESP_FUP_REQ_PORT_NUM_OFS,
    pDelayRespSmPtr->PdelayReq.SourcePortIdentity.PortNumber);                                                         /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_SEC_HI_OFS, pDelayRespOrgTsPtr->secondsHi);           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint32(TxBufPtr, ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_SEC_LOW_OFS, pDelayRespOrgTsPtr->seconds);            /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint32(TxBufPtr, ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_NSEC_OFS, pDelayRespOrgTsPtr->nanoseconds);           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
  /* #30 Provide Pdelay_Resp egress timestamp to time validation unit (if master time validation is enabled). */
  EthTSyn_TimeValid_PdRespProvidePdRespEgressTs(PortIdx, pDelayRespOrgTsPtr);                                          /* SBSW_ETHTSYN_LOCAL_PTR_VAR */
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

} /* EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  END PDELAY RESPONDER
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayConfigIterType pdelayCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all pdelay configurations and trigger initialization. */
  for(pdelayCfgIter = 0; pdelayCfgIter < EthTSyn_GetSizeOfPdelayConfig(); pdelayCfgIter++)
  {
    EthTSyn_Pdelay_InitPdelayInternal(pdelayCfgIter);
  }
}

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayOfPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayOfPort(
  EthTSyn_PortIterType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the given port is an active pdelay port, trigger initialization of the Pdelay. */
  if(EthTSyn_Util_IsActivePdelayPort((EthTSyn_IntPortIdxType)PortIdx) == TRUE)
  {
    EthTSyn_Pdelay_InitPdelayInternal(EthTSyn_GetPdelayConfigIdxOfPort(PortIdx));
  }
} /* EthTSyn_Pdelay_InitPdelayOfPort() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_GetCurrentPdelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(EthTSyn_PdelayType, ETHTSYN_CODE) EthTSyn_Pdelay_GetCurrentPdelay(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayType pDelay = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for valid Pdelay index. */
  if(EthTSyn_IsPdelayConfigUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pdelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    /* #20 Get the current Pdelay value. */
    pDelay = EthTSyn_GetPdelayValueNsOfPdelayInfo(pdelayIdx);
  }

  return pDelay;
} /* EthTSyn_Pdelay_GetCurrentPdelay() */

#if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_Pdelay_HandleCyclicTasks
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_HandleCyclicTasks(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayConfigIterType pDelayIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all Pdelay configurations */
  for(pDelayIter = 0; pDelayIter < EthTSyn_GetSizeOfPdelayConfig(); pDelayIter++)
  {
    const EthTSyn_IntPortIdxType activePdelayPortIdx = EthTSyn_GetPortIdxOfPdelayConfig(pDelayIter);
# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    /* #20 Check if Pdelay initiator is activated for the current Pdelay configuration. */
    if(EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(pDelayIter) == TRUE)
    {
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
          EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayIter);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
          EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_P2VAR(EthTSyn_PdelayReqSmType) pdelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      /* #200 Handle timers and timeouts of Pdelay request state machine. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0();
      if (pdelayReqSmPtr->PdelayReq.TxIntervalCnt > 0u)
      {
        pdelayReqSmPtr->PdelayReq.TxIntervalCnt--;                                                                     /* SBSW_ETHTSYN_CSL03 */
      }
      if (pdelayReqSmPtr->PdelayRespRespFollowUpTimeout > 0u)
      {
        pdelayReqSmPtr->PdelayRespRespFollowUpTimeout--;                                                               /* SBSW_ETHTSYN_CSL03 */
      }
      ETHTSYN_LEAVE_CRITICAL_SECTION_0();

      /* #201 Process Pdelay request state machine. */
      EthTSyn_Pdelay_ProcSmPdReq(activePdelayPortIdx);
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    /* #30 Check of Pdelay responder is activated for the current Pdelay configuration. */
    if(EthTSyn_IsPdelayResponderUsedOfPdelayConfig(pDelayIter) == TRUE)
    {
      /* #300 Process Pdelay response state machine. */
      EthTSyn_Pdelay_ProcSmPdResp(activePdelayPortIdx);
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

  } /* END: Iteration Pdelay Config */
} /* EthTSyn_Pdelay_HandleCyclicTasks() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY INITIATOR
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcSmPdReq
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcSmPdReq(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
  boolean txPdelayReq = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Pdelay request state machine state. */
  switch(pDelayReqSmPtr->State)
  {
  case ETHTSYN_S_PD_REQ_SM_DISABLED:
    {
      /* #100 State: Not enabled -> Enable state machine if port is tx ready. */
      if(EthTSyn_IsTxReady(PortIdx) == TRUE)
      {
        pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      }
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_TX_REQ:
    {
      /* #101 State: Send Pdelay request -> mark transmission of Pdelay request. */
      txPdelayReq = TRUE;
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_WAIT_RESP:
  case ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP:
    {
      /* #102 State: Waiting for Pdelay response/response follow up -> Check and handle PdelayResp or
       *      PdelayRespFollowUp timeout. */
      txPdelayReq = EthTSyn_Pdelay_CheckForPdelayRespTimeout(PortIdx);
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_COMPUTE_PDELAY:
    {
      /* #103 State: Received Pdelay response and response follow up -> trigger Pdelay calculation. */
      EthTSyn_Pdelay_TriggerPdelayCalculation(PortIdx);
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER:
    {
      /* #104 State: Waiting for Pdelay interval counter -> Handle Pdelay interval counter. */
      if(pDelayReqSmPtr->PdelayReq.TxIntervalCnt == 0u)
      {
        txPdelayReq = TRUE;
      }
      break;
    }

  default:
    {
      /* Nothing to do here. */
      break;
    }

  } /* END: switch(pDelayReqSmPtr->State) */

  /* #20 Check if Pdelay request should be transmitted. */
  if(txPdelayReq == TRUE)
  {
    /* #200 Tx Pdelay request required -> verify that port is ready for transmission. */
    if (EthTSyn_IsTxReady(PortIdx) == TRUE)
    {
      /* #2000 Port is tx ready -> transmit Pdelay request. */
      if (EthTSyn_Pdelay_TxPdelayReqMsg(PortIdx) == E_OK)
      {
        /* #20000 Transmission successful. Change state to WAIT_RESP and charge RespRespgFupTimeout. */
        pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_RESP;                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        pDelayReqSmPtr->PdelayRespRespFollowUpTimeout =
          EthTSyn_GetRespRespFollowUpTimeoutOfPdelayInitiator(pDelayInitiatorIdx);                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      }
      else
      {
        /* #20001 Transmission failed. Change state to TX_REQ. */
        pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      }
    }
    else
    {
      /* #2001 Port is not tx ready -> disable Pdelay request state machine. */
      pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_DISABLED;                                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
  }

} /* EthTSyn_Pdelay_ProcSmPdReq() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdRespMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdRespMsg(
  ETHTSYN_P2CONST(uint8)                    MsgPtr,
  ETHTSYN_P2CONST(EthTSyn_TsMgmtStructType) IngressTsMgmtPtr,
                  EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is ready to received Pdelay response. */
  if(EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(PortIdx) == TRUE)
  {
    /* #20 Pdelay initiator is enabled -> continue message processing. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

    /* #30 Assign the Ingress timestamp. */
    pDelayReqSmPtr->PdelayResp.IngressTsMgmt = (*IngressTsMgmtPtr);                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

    /* #40 Check if ingress timestamp is available. */
    if(pDelayReqSmPtr->PdelayResp.IngressTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
    {
      /* #400 Timestamp available -> receive Pdelay response. */
      EthTSyn_PdelayRx_ReceivePdelayResp(PortIdx, MsgPtr);                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
    }
  }
} /* EthTSyn_Pdelay_ProcRcvdRespMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdRespFupMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdRespFupMsg(
  ETHTSYN_P2CONST(uint8)                  MsgPtr,
                  EthTSyn_IntPortIdxType  PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is ready to receive a Pdelay response follow up message. */
  if(EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

    ETHTSYN_ENTER_CRITICAL_SECTION_0();
    /* #20 Check message attributes (Sequence Id, Matching Port Identity for PdelayResp and PdelayRespFollowUp,
     * Matching Requesting Port Identity) */
    /* Check Sequence Id */
    if(IpBase_GetUint16(MsgPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS) == pDelayReqSmPtr->PdelayReq.SequenceId)              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
    {
      /* Check Source Port Identity */
      if(EthTSyn_UtilRx_PortIdentityIsEqual(
        (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))&pDelayReqSmPtr->PdelayResp.SourcePortIdentity,
        &MsgPtr[ETHTSYN_MSG_HDR_SRC_PORT_IDENTITY_OFS]) == TRUE)                                                       /* SBSW_ETHTSYN_ETH_RX_BUFFER_OFS_FWD */
      {
        /* Check Requesting Port Identity */
        if(EthTSyn_UtilRx_PortIdentityIsEqualLocalPort(PortIdx,
          &MsgPtr[ETHTSYN_MSG_PD_RESP_FUP_REQ_PORT_IDENT_OFS]) == TRUE)                                                /* SBSW_ETHTSYN_ETH_RX_BUFFER_OFS_FWD */
        {
          /* #30 Store message attributes, reset lost responses and transit Pdelay request state machine. */
          pDelayReqSmPtr->PdelayRespFollowUp.RespOrgTs.secondsHi =
            IpBase_GetUint16(MsgPtr, ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_SEC_HI_OFS);                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
          pDelayReqSmPtr->PdelayRespFollowUp.RespOrgTs.seconds =
            IpBase_GetUint32(MsgPtr, ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_SEC_LOW_OFS);                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
          pDelayReqSmPtr->PdelayRespFollowUp.RespOrgTs.nanoseconds =
            IpBase_GetUint32(MsgPtr, ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_NSEC_OFS);                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

          /* Reset lost responses. */
          pDelayReqSmPtr->LostResponses = 0u;                                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

          /* valid PdelayResp and PdelayRespFollowUp were received -> path delay calculation in MainFunction
           * context is possible, after PdelayReq message was transmitted successfully (indicated by
           * TxConfirmationPending flag)*/

          pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_COMPUTE_PDELAY;                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        }
      }
    }
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();
  }

} /* EthTSyn_Pdelay_ProcRcvdRespFupMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  END: PDELAY INITIATOR
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY RESPONDER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcSmPdResp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcSmPdResp(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Pdelay response state machine state. */
  switch(pDelayRespSmPtr->State)
  {
  case ETHTSYN_S_PD_RESP_SM_DISABLED:
    {
      /* #100 State: Not enabled -> enable Pdelay response state machine. */
      if((EthTSyn_GetAddrCtrlState(EthTSyn_GetCtrlIdxOfPort(PortIdx)))->TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
      {
        pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_WAIT_REQ;                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      }
      break;
    }

  case ETHTSYN_S_PD_RESP_SM_TX_RESP:
    {
      /* #101 State: Send Pdelay response -> Verify that port is ready to transmit Pdelay response. */
      /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
      if(EthTSyn_IsTxReady(PortIdx) == TRUE)
      {
        /* #1010 Ready for transmission -> transmit Pdelay response message. */
        if(EthTSyn_Pdelay_TxPdelayRespMsg(PortIdx) != E_OK)
        {
          pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_TX_RESP;                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        }
      }
      break;
    }

  case ETHTSYN_S_PD_RESP_SM_WAIT_RESP_TS:
    {
      /* #102 State: Waiting for Pdelay response egress timestamp -> Check if TxConfirmation for send Pdelay response
       *      occurred */
      if((EthTSyn_Util_IsTsReadyToProc(pDelayRespSmPtr->PdelayResp.EgressTsMgmt.State) == TRUE) &&
        (pDelayRespSmPtr->TxConfirmationPending == 0))
      {
        /* #1020 If Pdelay response egress timestamp is available. */
        if(pDelayRespSmPtr->PdelayResp.EgressTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
        {
          /* #10200 Change state of the pdelay response state machine to TX_RESP_FUP. */
          pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_TX_RESP_FUP;                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        }
        /* #1021 Otherwise. */
        else
        {
          /* #10210 Change state of the pdelay response state machine to WAIT_REQ. */
          pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_WAIT_REQ;                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        }
      }
      break;
    }

  case ETHTSYN_S_PD_RESP_SM_TX_RESP_FUP:
    {
      /* #103 State: Send Pdelay response follow up ->
       *             Verify that port is ready to transmit Pdelay response follow up. */
      if(EthTSyn_IsTxReady(PortIdx) == TRUE)
      {
        /* #1030 Ready for transmission -> transmit Pdelay response follow up message. */
        if(EthTSyn_Pdelay_TxPdelayRespFupMsg(PortIdx) == E_OK)
        {
          pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_WAIT_REQ;                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        }
      }
      break;
    }

  default:
    {
      /* Nothing to do here. */
      break;
    }
  }

} /* EthTSyn_Pdelay_ProcSmPdResp() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdReqMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdReqMsg(
  ETHTSYN_P2CONST(uint8)                    RxBufPtr,
  ETHTSYN_P2CONST(EthTSyn_TsMgmtStructType) IngressTsMgmtPtr,
                  EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that Pdelay request was received on an active Pdelay responder port. */
  if (EthTSyn_Util_IsPdelayResponder(PortIdx) == TRUE)
  {
    /* #20 Pdelay responder is enabled -> continue message processing in case Pdelay response state machine is in
     *     state 'Waiting for Request'. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
      EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
      EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

    if(pDelayRespSmPtr->State == ETHTSYN_S_PD_RESP_SM_WAIT_REQ)
    {
      /* #30 If the Pdelay_Req ingress timestamp is available. */
      if(IngressTsMgmtPtr->State == ETHTSYN_TS_S_AVAILABLE)
      {
        ETHTSYN_ENTER_CRITICAL_SECTION_0();

        pDelayRespSmPtr->PdelayReq.IngressTsMgmt = (*IngressTsMgmtPtr);                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

        /* #300 Store the Pdelay_Req message information. */

        /* Store Requesting source port identity */
        pDelayRespSmPtr->PdelayReq.SourcePortIdentity.ClockIdentity =
          IpBase_GetUint64(RxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS);                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

        pDelayRespSmPtr->PdelayReq.SourcePortIdentity.PortNumber =
          IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_PORT_NUM_OFS);                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

        /* Store sequence id */
        pDelayRespSmPtr->PdelayReq.SequenceId = IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS);           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

        /* #301 Change Pdelay response state machine state to TX_RESP. */
        pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_TX_RESP;                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

        ETHTSYN_LEAVE_CRITICAL_SECTION_0();

# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
        /* #302 Start a new pdelay responder cycle in, provide the Pdelay_Req data to the time validation unit and
         *      trigger taking the pdelay reference time (if master time validation is enabled). */
        EthTSyn_TimeValid_PdRespStartCycle(PortIdx, pDelayRespSmPtr->PdelayReq.SequenceId);
        EthTSyn_TimeValid_PdRespTakeRefTimes(PortIdx);
        EthTSyn_TimeValid_PdRespProvidePdReqData(PortIdx, &pDelayRespSmPtr->PdelayReq.SourcePortIdentity,              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_AS_PTR */
            EthTSyn_UtilVlt_TsToIntVlt(&IngressTsMgmtPtr->Ts));                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */
      }
      /* #40 Otherwise, Pdelay_Req ingress timestamp is not available. Invalidate the timestamp. */
      else
      {
        pDelayRespSmPtr->PdelayReq.IngressTsMgmt.State = ETHTSYN_TS_S_INVALID;                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      }
    }
  }

} /* EthTSyn_Pdelay_ProcRcvdReqMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  END: PDELAY RESPONDER
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

#define ETHTSYN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Pdelay_Int.c
 *********************************************************************************************************************/
