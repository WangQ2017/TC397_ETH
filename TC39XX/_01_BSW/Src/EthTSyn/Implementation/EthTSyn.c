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
/*!        \file  EthTSyn.c
 *        \brief  EthTSyn implementation
 *      \details  Contains the main implementation of the Time Sync over Ethernet (EthTSyn) AUTOSAR module
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


#define ETHTSYN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
#include "EthTSyn_Master_Int.h"
#include "EthTSyn_Slave_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
#include "EthTSyn_Pdelay_Int.h"
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# include "EthTSyn_SwtMgmt_Int.h"
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#  include "EthTSyn_SwtTimeSync_Int.h" /* PRQA S 0777 */ /* MD_MSR_Rule5.1 */
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
# include "EthTSyn_TimeValidation_Int.h"
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (2u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (2u)) )
# error "Version numbers of EthTSyn.c and EthTSyn_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_3                   0xFFu
#define ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_4                   0xFEu

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(EthTSyn_StateEnumType, ETHTSYN_VAR_ZERO_INIT) EthTSyn_State = ETHTSYN_STATE_UNINIT;

#define ETHTSYN_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_SetLocalClockIdentity
 *********************************************************************************************************************/
/*! \brief      Sets the local clock identity of the EthTSyn controller.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller the clock identity should be set
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLocalClockIdentity(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_InitPort
 *********************************************************************************************************************/
/*! \brief      Initializes an EthTSyn Port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Port.
 *  \param[in]  PortIdx   Index of the Port that should be initialized
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitPort(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_InitCtrl
 *********************************************************************************************************************/
/*! \brief      Initializes an EthTSyn controller.
 *  \details    Initializes all component variables directly related to the passed EthTSyn controller.
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitCtrl(
  EthTSyn_CtrlIterType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_ResetPortsAndPdelayOfCtrl
 *********************************************************************************************************************/
/*! \brief      Initializes all Ports of the passed EthTSyn controller.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller the Ports should be initialized for.
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_ResetPortsAndPdelayOfCtrl(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

#if (ETHTSYN_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetTxPortAndMsgType
 *********************************************************************************************************************/
/*! \brief      Get EthTSyn-Port and message type the TxConfirmation was called for.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx  Pointer to the common message header
 *  \param[in]  TxBufIdx        Transmission buffer index
 *  \param[out] PortIdxPtr      Index of the Port the message was transmitted on
 *  \param[out] MsgTypePtr      Type of the message the TxConfirmation was called for
 *  \return     E_OK - Port and message type found. All out parameters are valid.
 *  \return     E_NOT_OK - Port or message type not found. Out parameters are invalid.
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \note       Out parameters are only modified in case of succuss (i.e. return == E_OK)
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TxConf_GetTxPortAndMsgType(
                EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                uint8                   TxBufIdx,
  ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr,
  ETHTSYN_P2VAR(uint8)                  MsgTypePtr);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetEgressTsAsVlt
 *********************************************************************************************************************/
/*! \brief      Get the egress timestamp as internal virtual local time.
 *  \details    Gets either the HW egress timestamp converted to internal virtual local time or the current SW
 *              virtual local time.
 *  \param[in]  EthIfCtrlIdx   Index of the EthIf controller
 *  \param[in]  BufIdx         Index of the Ethernet Tx buffer
 *  \param[in]  TimeBaseId     The synchronized time base id for which the egress timestamp is required
 *  \return     The egress timestamp as internal virtual local time and its validity information
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_TxConf_GetEgressTsAsVlt(
  uint8                         EthIfCtrlIdx,
  uint8                         BufIdx,
  StbM_SynchronizedTimeBaseType TimeBaseId);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_AssignEgressTs
 *********************************************************************************************************************/
/*! \brief      Assigns the egress timestamp to state machine.
 *  \details    Assigns the passed egress timestamp to the state machine (and message of the state machine) which
 *              triggered the transmission of the message.
 *  \param[in]  PortIdx              Index of the EthTSyn port the message was transmitted on
 *                                   [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgType              The type of the transmitted message
 *  \param[in]  EgressIntVltMgmtPtr  The egress timestamp as internal virtual local time and its validity info
 *  \pre        For PortIdx the following constraints apply depending on MsgType
 *              ETHTSYN_MSG_TYPE_SYNC: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_REQ: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                           EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                           EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_RESP: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                            EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                            EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different PortIdx - MsgType tuples
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_AssignEgressTs(
                  EthTSyn_IntPortIdxType  PortIdx,
                  uint8                   MsgType,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) EgressIntVltMgmtPtr);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessTxConfirmation
 *********************************************************************************************************************/
/*! \brief      Process the TxConfirmation, i.e. handle state machines.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx  Index of the EthIf controller
 *  \param[in]  BufIdx        Index of the Ethernet Tx buffer
 *  \param[in]  PortIdx       Index of the Port the message was transmitted on
 *                            [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgType       Type of the message the TxConfirmation was called for
 *  \pre        For PortIdx the following constraints apply depending on MsgType
 *              ETHTSYN_MSG_TYPE_SYNC: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_FOLLOW_UP: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_REQ: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                           EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                           EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_RESP: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                            EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                            EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different PortIdx - MsgType tuples.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessTxConfirmation(
  uint8                   EthIfCtrlIdx,
  uint8                   BufIdx,
  EthTSyn_IntPortIdxType  PortIdx,
  uint8                   MsgType);
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_IntRxIndication
 *********************************************************************************************************************/
/*! \brief      Processing of an received Ethernet EthTSyn frame.
 *  \details    -
 *  \param[in]  CtrlIdx      Index of the EthIf controller
 *  \param[in]  DataPtr      The Ethernet Rx buffer pointer
 *  \param[in]  LenByte      Length of received data
 *  \return     ETHTSYN_E_NO_ERROR - No DET error detected
 *  \return     other values - DET error code in case an DET error was detected
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \note       Internal implementation of the EthTSyn_RxIndication
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_IntRxIndication(
                  uint8  CtrlIdx,
  ETHTSYN_P2CONST(uint8) DataPtr,
                  uint16 LenByte);

/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetIngressTsAsVlt
 *********************************************************************************************************************/
/*! \brief      Gets the ingress timestamp as internal virtual local time.
 *  \details    Gets either the HW ingress timestamp converted to internal virtual local time or the current SW
 *              virtual local time.
 *  \param[in]  EthIfCtrlIdx  Index of the EthIf controller
 *  \param[in]  RxBufPtr      The Ethernet Rx buffer pointer
 *  \return     The ingress timestamp as internal virtual local time and its validity information
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_RxInd_GetIngressTsAsVlt(
                  uint8  EthIfCtrlIdx,
  ETHTSYN_P2CONST(uint8) RxBufPtr);

#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg
 *********************************************************************************************************************/
 /*! \brief         Gets the time domain idx from a received emssage.
  *  \details       -
  *  \param[in]     RxBufPtr     The ethernet Rx buffer pointer
  *  \return        EthTSyn_GetSizeOfTimeDomain() - No valid time domain found
  *  \return        other values - Index of the corresponding time domain
  *  \pre           -
  *  \context       TASK|ISR2
  *  \reentrant     TRUE
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg(
  ETHTSYN_P2CONST(uint8) RxBufPtr);
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_ProcRcvdMsg
 *********************************************************************************************************************/
/*! \brief      Processes a received message.
 *  \details    Performs basic message checks, retrieves the port index on which the message was received and triggers
 *              the actual processing of the message.
 *  \param[in]  RxBufPtr             Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \param[in]  LenByte              The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]  EthTSynCtrlIdx       Index of the EthTSyn Ctrl the message was received on
 *  \param[in]  IngressTsVltMgmtPtr  The ingress timestamp as internal virtual local time and its validity info
 *  \return     ETHTSYN_E_NO_ERROR - Message was passed to sub-component for reception
 *  \return     other values - Any error occurred and message was not received. Corresponding error id is returned
 *  \pre        Has to be called in the context of EthTSyn_RxIndication()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different EthTSyn controller indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_ProcRcvdMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  uint16                  LenByte,
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressTsVltMgmtPtr);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort
 *********************************************************************************************************************/
/*! \brief      Performs basic message checks and gets the EthTSyn Port the message was received on.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx  Index of the EthTSyn Ctrl the message was received on
 *  \param[in]  LenByte         The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]  RxBufPtr        Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \param[out] PortIdxPtr      Index of the EthTSyn Port the message was received on
 *  \return     ETHTSYN_E_NO_ERROR - Basic message checks passed. Out parameter is valid.
 *  \return     other values - Basic message check failed. Corresponding error id is returned.
 *  \pre        Has to be called in the context of EthTSyn_RxIndication()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \note       Verification of message type, length and protocol version.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(
                  EthTSyn_IntCtrlIdxType   EthTSynCtrlIdx,
                  uint16                   LenByte,
  ETHTSYN_P2CONST(uint8)                   RxBufPtr,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType)  PortIdxPtr);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SetLocalClockIdentity
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLocalClockIdentity(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_PhysAddrType physAddr;
  ETHTSYN_P2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(EthTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the physical address for the EthIf controller of the passed EthTSyn controller. */
  EthIf_GetPhysAddr(EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSynCtrlIdx), &physAddr[0]);                                      /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */

  /* #20 Derive the clock identity from the physical address according to IEEE802.1As and store it. */
  /* According to IEEE802.1As the clock identity is an EUI-64 derived by the EUI-48 MAC address in the following way:
   * 1. Assign higher three bytes of MAC address (OUI) to higher three of the clock identity
   * 2. Assign 0xFF and 0xFE to bytes 3 respectively 4 to clock identity
   * 3. Assign lower three bytes of MAC address to lower three bytes of the clock identity */
  ctrlStatePtr->ClockIdentity = (uint64)(
    ((uint64)physAddr[0u] << 56u) | ((uint64)physAddr[1u] << 48u) | ((uint64)physAddr[2u] << 40u) |
    ((uint64)ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_3 << 32u) |
    ((uint64)ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_4 << 24u) |
    ((uint64)physAddr[3u] << 16u) | ((uint64)physAddr[4u] << 8u) | ((uint64)physAddr[5u])
    );                                                                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_SetLocalClockIdentity() */

/**********************************************************************************************************************
 *  EthTSyn_InitPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitPort(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) )
  /* #10 Check Port role. */
  if(EthTSyn_IsMasterPortUsedOfPort(PortIdx) == TRUE)
#endif /* ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) ) */
  {
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    /* #100 Master Port -> Trigger initialization of master port. */
    EthTSyn_Master_InitPort(EthTSyn_GetMasterPortIdxOfPort(PortIdx));
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
  }
#if ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) )
  else
#endif /* ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) ) */
  {
    /* #101 Slave Port -> Trigger initialization of slave port. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    EthTSyn_Slave_InitPort(EthTSyn_GetSlavePortIdxOfPort(PortIdx));
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
  }

  /* #20 Initialize the debounce timer (if EthTSyn transmits any message). */
#if (ETHTSYN_TX_SUPPORT == STD_ON)
  EthTSyn_UtilTx_InitDebounceTimer(EthTSyn_GetPhysPortCfgIdxOfPort(PortIdx));
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */
} /* End of EthTSyn_InitPort() */

/**********************************************************************************************************************
 * EthTSyn_InitCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitCtrl(
  EthTSyn_CtrlIterType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(EthTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* If module was not initialized yet, initialize transceiver link state. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_DOWN;                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
  }
  ctrlStatePtr->TransmissionMode = ETHTSYN_TX_ON;                                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
  ctrlStatePtr->ClockIdentity = 0u;                                                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
} /* EthTSyn_InitCtrl() */

/**********************************************************************************************************************
 * EthTSyn_ResetPortsAndPdelayOfCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_ResetPortsAndPdelayOfCtrl(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all EthTSyn ports of the given EthTSyn controller. */
  for(portIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
      portIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
      portIter++)
  {
    const EthTSyn_IntPortIdxType portIdx = EthTSyn_GetPortInd(portIter);

    /* #100 Init the current EthTSyn port. */
    EthTSyn_InitPort(portIdx);

    /* #101 Trigger Pdelay initialization. */
    if(EthTSyn_IsPdelayConfigUsedOfPort(portIdx) == TRUE)
    {
      EthTSyn_Pdelay_InitPdelayOfPort(portIdx);
    }
  }
} /* EthTSyn_ResetPortsAndPdelayOfCtrl() */

#if (ETHTSYN_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetTxPortAndMsgType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TxConf_GetTxPortAndMsgType(
                EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                uint8                   TxBufIdx,
  ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr,
  ETHTSYN_P2VAR(uint8)                  MsgTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIndIter;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all Ports of the EthTSyn controller. */
  for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
      portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
      portIndIter++)
  {
    const EthTSyn_PortIndType portIdx = EthTSyn_GetPortInd(portIndIter);
    uint8 msgType = ETHTSYN_MSG_TYPE_INVALID;

    /* #100 Check if any message was transmitted on the current port using the given Tx-Buffer. */
# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayInitiator(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      if(pDelayReqSmPtr->TxBuf.Index == TxBufIdx)
      {
        /* Port and message type found */
        msgType = ETHTSYN_MSG_TYPE_PDELAY_REQ;
      }
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayResponder(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      if(pDelayRespSmPtr->TxBuf.Index == TxBufIdx)
      {
        msgType = ETHTSYN_MSG_TYPE_PDELAY_RESP;
      }
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    if(EthTSyn_IsMasterPortUsedOfPort(portIdx) == TRUE)
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(portIdx);
      EthTSyn_Master_PortSyncSend_CheckForMatchingTxConf(masterPortIdx, TxBufIdx, &msgType);                           /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    }
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

    if(msgType != ETHTSYN_MSG_TYPE_INVALID)
    {
      /* #20 Port and message type found. Set out parameters and stop iteration of Ports. */
      (*PortIdxPtr) = portIdx;                                                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
      (*MsgTypePtr) = msgType;                                                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
      retVal = E_OK;
      break;
    }
  } /* END: Iteration of Ports for the given Controller */

  return retVal;
} /* EthTSyn_TxConf_GetTxPortAndMsgType() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetEgressTsAsVlt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_TxConf_GetEgressTsAsVlt(
  uint8                         EthIfCtrlIdx,
  uint8                         BufIdx,
  StbM_SynchronizedTimeBaseType TimeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltMgmtType intVltMgmt = {0u, FALSE};
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampType ethEgressTs = { 0u, 0u, 0u };
  Eth_TimeStampQualType ethEgressTsQual = ETH_INVALID;
# else
  StbM_VirtualLocalTimeType currVlt = { 0u, 0u };
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 If HW-Timestamping is used, get the Ethernet egress timestamp via EthIf_GetEgressTimestamp() and convert it
   *     into an internal virtual local time. */
  if(EthIf_GetEgressTimestamp(EthIfCtrlIdx, BufIdx, &ethEgressTs, &ethEgressTsQual) == E_OK)                           /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    if(ethEgressTsQual == ETH_VALID)
    {
      intVltMgmt.IntVlt = EthTSyn_UtilVlt_TsToIntVlt(&ethEgressTs);                                                    /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      intVltMgmt.IntVltValid = TRUE;
    }
  }
  ETHTSYN_DUMMY_STATEMENT(TimeBaseId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# else
  /* #20 Other, SW-Timestamping is used. Get the current virtual local time from the StbM via
   *     StbM_GetCurrentVirtualLocalTime() and convert it into an internal virtual local time. */
  if(StbM_GetCurrentVirtualLocalTime(TimeBaseId, &currVlt) == E_OK)                                                    /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    intVltMgmt.IntVlt = EthTSyn_UtilVlt_VltToIntVlt(&currVlt);                                                         /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    intVltMgmt.IntVltValid = TRUE;
  }
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(BufIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /*  (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  return intVltMgmt;
} /* EthTSyn_TxConf_GetEgressTsAsVlt() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_AssignEgressTs
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_AssignEgressTs(
                  EthTSyn_IntPortIdxType  PortIdx,
                  uint8                   MsgType,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) EgressIntVltMgmtPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the message type. */
  switch(MsgType)
  {
# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    /* #20 If message type is Sync (if Master support is enabled). */
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      /* #200 Handle the sync egress timestamp. */
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      EthTSyn_Master_PortSyncSend_ProvideSyncHostEgrIntVlt(masterPortIdx, EgressIntVltMgmtPtr);                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      break;
    }
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
    /* #30 If message type is Pdelay_Req (if Pdelay initiator support is enabled). */
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      /* #300 Assign the egress timestamp to the corresponding PdelayReqSm. */
      const EthTSyn_PdelayConfigIdxOfPortType pdelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pdelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pdelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pdelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pdelayInitiatorIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pdelayReqSmIdx);

      pDelayReqSmPtr->PdelayReq.EgressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(EgressIntVltMgmtPtr);                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      break;
    }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
    /* #40 If message type is Pdelay_Resp (if Pdelay responder support is enabled). */
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      /* #400 Assign the egress timestamp to the corresponding PdelayRespSm. */
      const EthTSyn_PdelayConfigIdxOfPortType pdelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pdelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pdelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pdelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pdelayResponderIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pdelayRespSmIdx);

      pDelayRespSmPtr->PdelayResp.EgressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(EgressIntVltMgmtPtr);              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      break;
    }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

    /* #50 Otherwise, do nothing and discard egress timestamp. */
  default:
    {
      /* Nothing to do here. */
      break;
    }
  }
} /* EthTSyn_TxConf_AssignEgressTs() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessTxConfirmation(
  uint8                  EthIfCtrlIdx,
  uint8                  BufIdx,
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  MsgType)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform required actions for the message type. */
  switch(MsgType)
  {
# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
          EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
          EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);

      EthTSyn_PdelayReqSmPtrType pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(EthIfCtrlIdx, BufIdx, NULL_PTR, &pDelayReqSmPtr->PdelayReq.EgressTsMgmt);      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_AS_PTR */
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

      pDelayReqSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      pDelayReqSmPtr->TxConfirmationPending--;                                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

      break;
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
          EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
          EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);

      EthTSyn_PdelayRespSmPtrType pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(EthIfCtrlIdx, BufIdx, NULL_PTR, &pDelayRespSmPtr->PdelayResp.EgressTsMgmt);    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_AS_PTR */
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

      pDelayRespSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      pDelayRespSmPtr->TxConfirmationPending--;                                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

      break;
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      EthTSyn_Master_PortSyncSend_ProcSyncTxConf(EthTSyn_GetMasterPortIdxOfPort(PortIdx), EthIfCtrlIdx);
      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      EthTSyn_Master_PortSyncSend_ProcFupTxConf(EthTSyn_GetMasterPortIdxOfPort(PortIdx));
      break;
    }
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  } /* PRQA S 3315 */ /* MD_EthTSyn_3315 */

# if (ETHTSYN_MASTER_SUPPORT == STD_OFF)
  /* EthIfCtrlIdx is also used when Switch timestamping is enabled. However, a bridge configuration without
   * Master-Support is not sensible. Therefore a subsequent check if Switch timestamping is disabled as well is not
   * required. */
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_OFF) */
  ETHTSYN_DUMMY_STATEMENT(BufIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

} /* EthTSyn_TxConf_ProcessTxConfirmation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_IntRxIndication
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
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_IntRxIndication(
                  uint8  CtrlIdx,
  ETHTSYN_P2CONST(uint8) DataPtr,
                  uint16 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  EthTSyn_IntVltMgmtType ingressVltMgmt;
  EthTSyn_IntCtrlIdxType ethTSynCtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  /* Critical section is used to ensure that the time between invocation of RxIndication and getting the
     software ingress timestamp is minimized. */
  ETHTSYN_ENTER_CRITICAL_SECTION_GET_TS();
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

  /* #10 Get the ingress timestamp. */
  ingressVltMgmt = EthTSyn_RxInd_GetIngressTsAsVlt(CtrlIdx, DataPtr);                                                  /* SBSW_ETHTSYN_POINTER_FORWARD */

#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  /* Leave critical section (if SW-Timestamping is used). */
  ETHTSYN_LEAVE_CRITICAL_SECTION_GET_TS();
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

  /* #20 Get and verify EthTSyn controller. */
  ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

  if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
  {
    /* #30 Verify link state. */
    if(EthTSyn_GetCtrlState(ethTSynCtrlIdx).TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
    {
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
      /* #40 Switch management enabled. Pass the received Frame to the Switch management. */
      errorId = EthTSyn_SwtMgmt_Rx_HndlMsgReception(DataPtr, LenByte, ethTSynCtrlIdx, &ingressVltMgmt);                /* SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF */
#else
      /* #50 Switch management disabled. Handle message reception. */
      errorId = EthTSyn_RxInd_ProcRcvdMsg(DataPtr, LenByte, ethTSynCtrlIdx, &ingressVltMgmt);                          /* SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF */
#endif /* ETHTSYN_SWT_MGMT_SUPPORT */
    }
    else
    {
      errorId = ETHTSYN_E_TRCV_DOWN;
    }
  }
  else
  {
    errorId = ETHTSYN_E_CTRL_IDX;
  }

  return errorId;
} /* EthTSyn_RxInd_IntRxIndication() */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetIngressTsAsVlt
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
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_RxInd_GetIngressTsAsVlt(
                  uint8  EthIfCtrlIdx,
  ETHTSYN_P2CONST(uint8) RxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltMgmtType intVltMgmt = {0u, FALSE};

  /* ----- Implementation ----------------------------------------------- */
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 If HW timestamping is used. */
  {
    Eth_TimeStampType ethIngressTs = { 0u, 0u, 0u };
    Eth_TimeStampQualType ethIngressTsQual = ETH_INVALID;

    /* #100 Get the Ethernet ingress timestamp via EthIf_GetIngressTimestamp() and convert it into an internal virtual
     *      local time in case the ingress timestamp was successfully retrieved and is valid. */
    /* PRQA S 0310, 0311, 3305 1 */ /* MD_EthTSyn_PtrCast_EthBuffer */
    if(EthIf_GetIngressTimestamp(EthIfCtrlIdx, (ETHTSYN_P2VAR(Eth_DataType))RxBufPtr,                                  /* SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF */
        &ethIngressTs, &ethIngressTsQual) == E_OK)
    {
      if(ethIngressTsQual == ETH_VALID)
      {
        intVltMgmt.IntVlt = EthTSyn_UtilVlt_TsToIntVlt(&ethIngressTs);                                                 /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        intVltMgmt.IntVltValid = TRUE;
      }
    }

  }
#else
  /* #20 Otherwise, SW timestamping is used. */
  {
    /* #200 Get the time domain from the received message and check if the time domain is known by the EthTSyn. */
    EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg(RxBufPtr);                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

    if(timeDomainIdx < EthTSyn_GetSizeOfTimeDomain())
    {
      /* #2000 Get the current virtual local time from the StbM via StbM_GetCurrentVirtualLocalTime() and
       *       convert it into internal representation in case the time was retrieved successfully. */
      StbM_VirtualLocalTimeType stbmVlt = { 0u, 0u };
      StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);

      if(StbM_GetCurrentVirtualLocalTime(timeBaseId, &stbmVlt) == E_OK)                                                /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      {
        intVltMgmt.IntVlt = EthTSyn_UtilVlt_VltToIntVlt(&stbmVlt);                                                     /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        intVltMgmt.IntVltValid = TRUE;
      }
    }

    ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  }
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  return intVltMgmt;
} /* EthTSyn_RxInd_GetIngressTsAsVlt() */

#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg(
  ETHTSYN_P2CONST(uint8) RxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetSizeOfTimeDomain();
  EthTSyn_TimeDomainIterType timeDomainIter;
  uint8 timeDomainIdFromMsg;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the time domain id from the received message. */
  timeDomainIdFromMsg = IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS);                                     /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

  /* #20 Iterate all configured time domains of the EthTSyn. */
  for(timeDomainIter = 0u;
    timeDomainIter < EthTSyn_GetSizeOfTimeDomain();
    timeDomainIter++)
  {
    /* #30 If current time domain id matches the one from the received message, stop iteration and return the
     *     time domain index. */
    if(EthTSyn_GetIdOfTimeDomain(timeDomainIter) == timeDomainIdFromMsg)
    {
      timeDomainIdx = (EthTSyn_IntTimeDomainIdxType)timeDomainIter;
      break;
    }
  }

  return timeDomainIdx;
} /* EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg() */
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_ProcRcvdMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_ProcRcvdMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  uint16                  LenByte,
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressTsVltMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform basic message checks and get EthTSyn PortIdx. */
  errorId = EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(EthTSynCtrlIdx, LenByte, RxBufPtr, &portIdx);                /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD_AND_LOC_VAR_REF */
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* Port found -> continue processing of the message */
    /* #20 Get message type and process the message if applicable. */
    /* Shift of ETHTSYN_MSG_HDR_MSG_TYPE_SHIFT is not required because it is 0. */
    switch(IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_MSG_TYPE_OFS) & ETHTSYN_MSG_HDR_MSG_TYPE_MASK)                    /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
    {
# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_PDELAY_REQ:
      {
        EthTSyn_TsMgmtStructType ingressTsMgmt;
        ingressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(IngressTsVltMgmtPtr);                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
        EthTSyn_Pdelay_ProcRcvdReqMsg(RxBufPtr, &ingressTsMgmt, portIdx);                                              /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD_AND_LOC_VAR_REF */
        break;
      }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_PDELAY_RESP:
      {
        EthTSyn_TsMgmtStructType ingressTsMgmt;
        ingressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(IngressTsVltMgmtPtr);                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
        EthTSyn_Pdelay_ProcRcvdRespMsg(RxBufPtr, &ingressTsMgmt, portIdx);                                             /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD_AND_LOC_VAR_REF */
        break;
      }

    case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
      {
        EthTSyn_Pdelay_ProcRcvdRespFupMsg(RxBufPtr, portIdx);                                                          /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
        break;
      }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

    case ETHTSYN_MSG_TYPE_SYNC:
      {
        uint64 srcClockIdentity = IpBase_GetUint64(RxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS);          /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
        if (EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(portIdx, srcClockIdentity) == TRUE)
        {
          EthTSyn_SlaveRx_ProcRcvdSyncMsg(RxBufPtr, portIdx, IngressTsVltMgmtPtr);                                     /* SBSW_ETHTSYN_ETH_RX_BUF_AND_PTR_FWD */
        }
# else
        (void)EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(portIdx, srcClockIdentity);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

        break;
      }

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_FOLLOW_UP:
      {
        EthTSyn_SlaveRx_ProcRcvdFupMsg(RxBufPtr, portIdx);                                                             /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
        break;
      }
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_ANNOUNCE:
      {
        EthTSyn_Slave_ProcRcvdAnnounceMsg(RxBufPtr, portIdx);                                                          /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
        break;
      }
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

    default:
      {
        /* Nothing to do here. */
        break;
      }
    }
  }

  ETHTSYN_DUMMY_STATEMENT(IngressTsVltMgmtPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  return errorId;
} /* EthTSyn_RxInd_ProcRcvdMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_MsgReception */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                  uint16                  LenByte,
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform general message checks. */
  errorId = EthTSyn_UtilRx_CheckMessageGeneral(RxBufPtr, LenByte);                                                     /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* #20 General message checks passed. Check message type and length. */
    errorId = EthTSyn_UtilRx_CheckMessageTypeAndLength(RxBufPtr, LenByte);                                             /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
    if(errorId == ETHTSYN_E_NO_ERROR)
    {
      EthTSyn_PortIndIterType portIndIter;
      errorId = ETHTSYN_E_NO_PORT_FOUND;
      /* #30 Valid message type and length. Get the EthTSyn Port. */
      for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
          portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
          portIndIter++)
      {
        const EthTSyn_PortIndType tmpPort = EthTSyn_GetPortInd(portIndIter);
        const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(tmpPort);
        if(EthTSyn_GetIdOfTimeDomain(timeDomainIdx) == IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS))      /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
        {
          /* #300 EthTSyn Port found. */
          (*PortIdxPtr) = tmpPort;                                                                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
          errorId = ETHTSYN_E_NO_ERROR;
          break;
        }
      }
    }
  }

  return errorId;
} /* EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 3673 7 */ /* MD_EthTSyn_3673_Ar */
FUNC(void, ETHTSYN_CODE) EthTSyn_RxIndication(
                uint8                  CtrlIdx,
                Eth_FrameType          FrameType,
                boolean                IsBroadcast,
                EthTSyn_PhyAddrPtrType PhysAddrPtr,
  ETHTSYN_P2VAR(uint8)                 DataPtr,
                uint16                 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR; /* PRQA S 2981 */ /* MD_EthTSyn_2981_ErrorId */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if((DataPtr == NULL_PTR) || (PhysAddrPtr == NULL_PTR))
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else if(FrameType != ETHTSYN_FRAME_TYPE)
  {
    errorId = ETHTSYN_E_FRAME_TYPE;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Trigger the message reception. */
    errorId = EthTSyn_RxInd_IntRxIndication(CtrlIdx, DataPtr, LenByte);                                                /* SBSW_ETHTSYN_POINTER_FORWARD */
  }

#if (ETHTSYN_DEV_ERROR_DETECT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(FrameType); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(PhysAddrPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_OFF) */
  ETHTSYN_DUMMY_STATEMENT(IsBroadcast); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if (errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_RX_INDICATION, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

} /* EthTSyn_RxIndication() */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

#if (ETHTSYN_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_GetVersionInfo(
  ETHTSYN_P2VAR(Std_VersionInfoType) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check VersionInfoPtr for NULL pointer. note: no uninit check is performed. */
  if(VersionInfoPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Set version info with corresponding macros from component header. */
    VersionInfoPtr->vendorID = (uint16)ETHTSYN_VENDOR_ID;                                                              /* SBSW_ETHTSYN_POINTER_WRITE */
    VersionInfoPtr->moduleID = (uint16)ETHTSYN_MODULE_ID;                                                              /* SBSW_ETHTSYN_POINTER_WRITE */
    VersionInfoPtr->sw_major_version = (uint8)ETHTSYN_SW_MAJOR_VERSION;                                                /* SBSW_ETHTSYN_POINTER_WRITE */
    VersionInfoPtr->sw_minor_version = (uint8)ETHTSYN_SW_MINOR_VERSION;                                                /* SBSW_ETHTSYN_POINTER_WRITE */
    VersionInfoPtr->sw_patch_version = (uint8)ETHTSYN_SW_PATCH_VERSION;                                                /* SBSW_ETHTSYN_POINTER_WRITE */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif
} /* EthTSyn_GetVersionInfo() */
#endif /* (ETHTSYN_VERSION_INFO_API == STD_ON) */


/**********************************************************************************************************************
 *  EthTSyn_MainFunction
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
FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of component. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthTSyn_TimeDomainIterType timeDomainIter;
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    EthTSyn_PhysPortIterType physPortIter;
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #20 Decrement all debounce timer (if EthTSyn transmits any message). */
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    for(physPortIter = 0u; physPortIter < EthTSyn_GetSizeOfPhysPort(); physPortIter++)
    {
      EthTSyn_UtilTx_DecDebounceTimer(physPortIter);
    }
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #30 Invoke main function of time validation unit (if TimeValidation feature is enabled). */
#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
    EthTSyn_TimeValid_MainFunction();
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

    /* #40 Iterate all TimeDomains. */
    for(timeDomainIter = 0; timeDomainIter < EthTSyn_GetSizeOfTimeDomain(); timeDomainIter++)
    {
      /* #400 Handle cyclic tasks for Master-Ports. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
      EthTSyn_Master_HandleCyclicTasks(timeDomainIter);
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

      /* #401 Handle cyclic tasks for Slave-Ports. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
      EthTSyn_Slave_HandleCyclicTasks(timeDomainIter);
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

      /* #402 Process site sync sync state machine if applicable. */
#if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
      if(EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(timeDomainIter) == TRUE)
      {
        /* SiteSyncSync state machine */
        EthTSyn_SwtMgmt_SiteSyncSync_ProcSm(timeDomainIter);
      }
#endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
    } /* END: Iteration of TimeDomains */

    /* #50 Handle cyclic task for Pdelay. */
#if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
    EthTSyn_Pdelay_HandleCyclicTasks();
#endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */

    /* #60 Handle cycle tasks for switch time sync. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwtTimeSync_HandleCyclicTasks();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_MAIN_FUNCTION, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */

} /* EthTSyn_MainFunction() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE)  EthTSyn_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set module state to unitialized. */
  EthTSyn_State = ETHTSYN_STATE_UNINIT;
}

/**********************************************************************************************************************
 *  EthTSyn_Init
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
FUNC(void, ETHTSYN_CODE) EthTSyn_Init(
  P2CONST(EthTSyn_ConfigType, AUTOMATIC, ETHTSYN_INIT_DATA) CfgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  EthTSyn_ConfigDataPtr = CfgPtr;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(CfgPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    EthTSyn_CtrlIterType ethTSynCtrlIter;
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    EthTSyn_PhysPortIterType physPortIter;
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #100 Initialize Master sub module. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    errorId = EthTSyn_Master_Init();
# else
    (void)EthTSyn_Master_Init();
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

    /* #101 Initialize Slave sub module. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    EthTSyn_Slave_Init();
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

    /* #102 Initialize Pdelay sub module. */
    EthTSyn_Pdelay_Init();

    /* #103 Initialize SwtMgmt sub module. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmt_Init();

    /* #1030 Initialize SwtTimeSync sub module. */
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwtTimeSync_Init();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
    /* #104 Initialize time validation sub module (if TimeValidation feature is enabled). */
    EthTSyn_TimeValid_Init();
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

    /* #105 Initialize all EthTSyn controllers. */
    for(ethTSynCtrlIter = 0u; ethTSynCtrlIter < EthTSyn_GetSizeOfCtrl(); ethTSynCtrlIter++)
    {
      EthTSyn_InitCtrl(ethTSynCtrlIter);
    }

    /* #106 Initialize the debounce timers of all ports if applicable. */
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    for(physPortIter = 0u; physPortIter < EthTSyn_GetSizeOfPhysPort(); physPortIter++)
    {
      EthTSyn_UtilTx_InitDebounceTimer(physPortIter);
    }
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #107 Set module state to initialized in case no error occurred during initialization. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    if(errorId == ETHTSYN_E_NO_ERROR)
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
    {
      EthTSyn_State = ETHTSYN_STATE_INIT;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_INIT, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
} /* EthTSyn_Init() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TrcvLinkStateChg
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
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TrcvLinkStateChg(
  uint8                 CtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Get EthTSyn Controller of the passed EthIf Controller. */
    const EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      ETHTSYN_CONSTP2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ethTSynCtrlIdx);

      /* #30 Check the passed transceiver link state. */
      switch(TrcvLinkState)
      {
        /* #40 Handle transceiver link state down. */
      case ETHTRCV_LINK_STATE_DOWN:
        {
          /* #400 In case transceiver link state changed from active to down. */
          if(ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
          {
            /* #4000 Store new transceiver link state. */
            ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_DOWN;                                                     /* SBSW_ETHTSYN_CSL02 */

            /* #4001 Remove multicast frame reception via EthIf_UpdatePhysAddrFilter(). */
            (void)EthIf_UpdatePhysAddrFilter(CtrlIdx, EthTSyn_DestinationMac, ETH_REMOVE_FROM_FILTER);                 /* SBSW_ETHTSYN_GLOBAL_VAR_AS_PTR */
            /* #4002 Reset Ports and Pdelay values of the controller. */
            EthTSyn_ResetPortsAndPdelayOfCtrl(ethTSynCtrlIdx);
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
            /* #4003 Disable switch sync frame (if ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON). */
            EthTSyn_SwtTimeSync_SwtSyncFrameStop(CtrlIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

            /* #4004 Release all pending switch management objects mapped to the passed EthIf controller
             *      (if ETHTSYN_SWT_MGMT_SUPPORT == STD_ON). */
            EthTSyn_SwtMgmt_ReleasePendingSwtMgmtObj(ethTSynCtrlIdx);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
          }

          break;
        }

        /* #50 Handle transceiver link state up. */
      case ETHTRCV_LINK_STATE_ACTIVE:
        {
          /* #500 In case transceiver link state changed from down to active. */
          if(ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_DOWN)
          {
            /* #5000 Store new transceiver link state. */
            ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_ACTIVE;                                                   /* SBSW_ETHTSYN_CSL02 */

            /* #5001 Initialize EthTSyn controller and the local clock identity. */
            EthTSyn_InitCtrl(ethTSynCtrlIdx);
            EthTSyn_SetLocalClockIdentity(ethTSynCtrlIdx);
            /* #5002 Add multicast frame reception via EthIf_UpdatePhysAddrFilter(). */
            (void)EthIf_UpdatePhysAddrFilter(CtrlIdx, EthTSyn_DestinationMac, ETH_ADD_TO_FILTER);                      /* SBSW_ETHTSYN_GLOBAL_VAR_AS_PTR */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
            /* #5003 Enable switch sync frame. */
            EthTSyn_SwtTimeSync_SwtSyncFrameStart(CtrlIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
          }

          break;
        }

        /* #60 Handle other values of transceiver link state. */
      default:
        {
          /* #600 Invalid value of transceiver link state. Optionally set errorId to ETHTSYN_E_PARAM and do nothing. */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
          errorId = ETHTSYN_E_PARAM;
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
          break;
        }
      }
    }
    /* No DET for invalid Ctrl Idx, because EthIf calls TrcvLinkStateChg functions for every registered UpperLayer
       and each configured EthIf controller. */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_TRCV_LINK_STATE_CHG, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
} /* EthTSyn_TrcvLinkStateChg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TxConfirmation
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
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_TxConfirmation(
  uint8 CtrlIdx,
  uint8 BufIdx)
{
#if (ETHTSYN_TX_SUPPORT == STD_ON)
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    EthTSyn_IntCtrlIdxType ethtsynCtrlIdx;
    EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();
    uint8 msgType = ETHTSYN_MSG_TYPE_INVALID;
    EthTSyn_IntVltMgmtType egressVltMgmt = {0u, FALSE};
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameIdx = EthTSyn_GetSizeOfSwitchSyncFrameCfg();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
    /* For SW-Timestamping the critical section is used to ensure a minimal delay between EthTSyn_TxConfirmation
     * Invocation and collecting the egress timestamp */
    ETHTSYN_ENTER_CRITICAL_SECTION_GET_TS();
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

    /* #20 Get the corresponding EthTSyn controller. */
    ethtsynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);
    if(ethtsynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetSizeOfTimeDomain();

      /* #30 Try to find a matching EthTSyn Port and Message type. */
      if(EthTSyn_TxConf_GetTxPortAndMsgType(ethtsynCtrlIdx, BufIdx, &portIdx, &msgType) == E_OK)                       /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      {
        /* #300 Mark port and message type as found and get the time domain of the port. */
        timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
      }
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
      /* #40 Otherwise, try to find a matching switch sync frame and get the corresponding time domain. */
      else
      {
        swtSyncFrameIdx = EthTSyn_SwtTimeSync_TxConfGetSwtSyncFrameIdx(CtrlIdx, BufIdx);

        if(swtSyncFrameIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg())
        {
          EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType swtTimeSyncCfgIdx =
            EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(swtSyncFrameIdx);
          timeDomainIdx = EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIdx);
        }
      }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

      /* #50 Get the egress timestamp in case a valid time domain was found. */
      if(timeDomainIdx < EthTSyn_GetSizeOfTimeDomain())
      {
        StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
        egressVltMgmt = EthTSyn_TxConf_GetEgressTsAsVlt(CtrlIdx, BufIdx, timeBaseId);
      }
    }
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
# endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */

# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
    /* Leave the critical section after the SW egress timestamp was retrieved and before further processing of the
     * TxConfirmation. */
    ETHTSYN_LEAVE_CRITICAL_SECTION_GET_TS();
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

    /* #60 If a matching port and transmitted message was found. */
    if(portIdx < EthTSyn_GetSizeOfPort())
    {
      /* #600 Assign the egress timestamp. */
      EthTSyn_TxConf_AssignEgressTs(portIdx, msgType, &egressVltMgmt);                                                 /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */

      /* #601 Process TxConfirmation. */
      EthTSyn_TxConf_ProcessTxConfirmation(CtrlIdx, BufIdx, portIdx, msgType); /*lint !e522 */
    }
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    /* #70 If a matching switch sync frame was found. */
    else if (swtSyncFrameIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg())
    {
      /* #700 Process the switch sync frame TxConfirmation. */
      EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation(swtSyncFrameIdx, &egressVltMgmt);                                 /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    }
    /* #80 Otherwise. */
    else
    {
      /* #800 No matching transmitted message was found. Discard the TxConfirmation.*/
    }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #90 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_TX_CONFIRMATION, errorId);
  }
# else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
#else
  ETHTSYN_DUMMY_STATEMENT(CtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(BufIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */
} /* EthTSyn_TxConfirmation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SetTransmissionMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SetTransmissionMode(
  uint8                        CtrlIdx,
  EthTSyn_TransmissionModeType Mode)
{
  /* ------ Local Variables -----------------------------------------------*/
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if((Mode != ETHTSYN_TX_ON) && (Mode != ETHTSYN_TX_OFF))
  {
    errorId = ETHTSYN_E_PARAM;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Set the transmission mode of the corresponding EthTSyn controller. */
    const EthTSyn_IntCtrlIdxType ethtsynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethtsynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      (EthTSyn_GetAddrCtrlState(ethtsynCtrlIdx))->TransmissionMode = Mode;                                             /* SBSW_ETHTSYN_CSL02 */
    }
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_SET_TRANSMISSION_MODE, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

} /* EthTSyn_SetTransmissionMode() */

#define ETHTSYN_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justifications for module-specific MISRA deviations:

  MD_EthTSyn_PtrCast_EthBuffer: MISRA rule 11.3 (A cast should not be performed between a pointer to object type and a
                                                  different pointer to object type)
                                MISRA rule 11.8 (A cast shall not be performed that removes any const or volatile
                                                 qualification from the type addressed by a pointer)
                                 QAC: 0310 - Casting to different object pointer type
                                      3305 - Pointer cast to stricter alignment.
                                      0311 - Dangerous pointer cast results in loss of const qualification
      Reason:     An Ethernet Rx/Tx buffer is provided to the EthTSyn as pointer to Eth_DataType. This data type is
                  Platform depended. Therefore for internal processing the EthTSyn uses an uint8 pointer and byte-wise
                  access to avoid mis-aligned access. However EthIf APIs expect a P2VAR with data type Eth_DataType.
                  Therefore when calling an EthIf API the Ethernet Rx/Tx buffer pointer is casted to P2VAR(Eth_DataType)
                  again.
      Risk:       No risk. Pointer was originally provided as pointer to Eth_DataType. In addition the object addressed
                  the pointer parameter is not modified within the called API. The parameter is specified as 'in'
                  parameter by AUTOSAR.
      Prevention: None.
  MD_EthTSyn_0311: MISRA rule 11.8 (A cast shall not be performed that removes any const or volatile qualification
                                    from the type addressed by a pointer)
                   QAC: Dangerous pointer cast results in loss of const qualification
      Reason:     Called API expects a P2VAR.
      Risk:       No risk. The object addressed by the pointer parameter is not modified within the called API.
                  The parameters is specified as 'in' parameter by AUTOSAR.
      Prevention: Covered by code review.
  MD_EthTSyn_3673_Ar: MISRA rule 8.13 (A pointer parameter in a function prototype should be declared as pointer to
                                       const if the pointer is not used to modify the addressed object)
                      QAC: The object addressed by the pointer parameter '%s' is not modified and so the pointer could
                           be of type 'pointer to const'
      Reason:     The parameter is of type P2VAR due to AUTOSAR specification
      Risk:       Unnoticed/unwilling modification of in-parameter.
      Prevention: Covered by code review
  MD_EthTSyn_3415_CslReadOnly: MISRA rule 13.5 (The right hand operand of a logical && or || operator shall not contain
                                                side effects)
                               QAC: The right hand operand of '&&' or '||' has side effects
     Reason:     No side effects possible because the (inline) function only wraps a read-only access to a
                 variable/constant. Used to justify read-only access to constants/variables via inline function
                 generated by the ComStackLib (CSL). (e.g.: EthTSyn_Get*())
     Risk:       Right hand operand does not influence the program/control flow therefor the lazy evaluation applied
                 by the compiler has no effect.
     Prevention: None.
  MD_EthTSyn_3415_ReadOnly: MISRA rule 13.5 (The right hand operand of a logical && or || shall not contain side
                                             effects)
                            QAC: The right hand operand of '&&' or '||' has side effects
      Reason:     No side effect possible because the function does not modify any variable.
                  It is intended that this function is only called if the first check failed (||) / succeeded (&&).
      Risk:       No risk. No assignments are done in conditional statements
      Prevention: Covered by code review.
  MD_EthTSyn_2003: MISRA rule 16.3 (An unconditional break statement shall terminate every non-empty switch clause)
                   QAC: The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or
                        'return' statement.
      Reason:    Fall through case to reuse code parts common among different cases.
      Risk:      Right hand operand does not influence the program/control flow therefor the lazy evaluation applied
                 by the compiler has no effect.
     Prevention: None.
  MD_EthTSyn_0883: MISRA rule 1.3: Include file code is not protected against repeated inclusion
      Reason:     Wrong MISRA Warning. Standard Include Guard is present.
      Risk:       No risk.
      Prevention: Covered by code review.
  MD_EthTSyn_3219: MISRA rule 2.1 (There shall be no unreachable code).
                   QAC: Static function '%s()' is not used within this translation unit.
      Reason:     Some internal functions are used within different sub-modules of the EthTSyn. However they might not
                  be used in every sub-module.
      Risk:       Functions which are superfluous in a specific configuration may remain undetected which leads to a
                  small resource overhead.
      Prevention: Covered by code review.
  MD_EthTSyn_2995: MISRA rule 14.3 (Boolean operations whose results are invariant shall not be permitted)
                   QAC: The result of this logical operation is always 'true'.
      Reason:     This logical operation is only 'always true' for specific preprocessor variants.
      Risk:       Possible programming error might not be detected.
      Prevention: Covered by runtime tests in different variants.
  MD_EthTSyn_2996: MISRA rule 14.3 (Boolean operations whose results are invariant shall not be permitted)
                   QAC: The result of this logical operation is always 'false'.
      Reason:     This logical operation is only 'always false' for specific preprocessor variants.
      Risk:       Possible programming error might not be detected.
      Prevention: Covered by runtime tests in different variants.
  MD_EthTSyn_6050_CslAccess: MISRA rule N/A
                             QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     Number of distinct function calls is only too high due to trivial inline functions for accessing the
                  ComStackLib data. Complexity of the function does not increase compared to ComStackLib access via
                  macros.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_6050_IpBase: MISRA rule N/A
                             QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     Number of distinct function calls is only too high due to trivial inline functions for byte-wise
                  read/write access of Ethernet Rx/Tx buffer via IpBase. Complexity of the function does not increase
                  compared to IpBase access via macros or direct buffer access.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_6050_InlineFunc: MISRA rule N/A
                              QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     Number of distinct function calls is only too high due to trivial inline functions for byte-wise
                  read/write access of Ethernet Rx/Tx buffer via IpBase or generated data access
                  (combination of MD_EthTSyn_6050_CslAccess and MD_EthTSyn_6050_IpBase). Complexity of the function
                  does not increase compared to usage of macros or direct access.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_6050_MsgReception: MISRA rule N/A
                                QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     On message reception, the message is forwarded to a corresponding sub-module depending on the
                  message type. Each message type requires an own function. In addition some preparation steps are done
                  in order to unify the message specific reception functions. This leads to more distinct function calls
                  with in the general message reception routine. However, the complexity and readability of this
                  general function is still ensured due to clearly structured and commented code.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_0779_CslAccessName: MISRA rule 1.3 (Identifiers (internal and external) shall not rely on the significance
                                                of more than 31 characters)
                                 QAC: [U] Identifier does not differ from other identifier(s) (e.g. '%s') within the
                                      specified number of significant characters
      Reason:     The identifiers are generated by the ComStackLib based on the names of the underlying data.
      Risk:       A compiler might not correctly pre-process the software what might result in incorrect code.
      Prevention: Each delivery is integrated and tested on the real target system. In addition, preprocessors and
                  compilers used in current MICROSAR projects are not expected to suffer from this (historic)
                  limitation. Compiler selection and validation is done by ECU supplier.
  MD_EthTSyn_1257_Snv: MISRA rule 10.3 (The value of an expression shall not be assigned to an object with a narrower
                                        essential type or of a different essential type category.)
                       QAC: An integer constant suffixed with L or LL is being converted to a type of lower rank on
                            assignment.
      Reason:     Symbolic name value is used in a generated structure as handle. The Snv is generated with 'uL' suffix
                  but the used data type is smaller.
      Risk:       No risk. It is ensured by the ComStackLib that the used data type can hold the SNV.
      Prevention: None.
  MD_EthTSyn_2981_ErrorId: MISRA rule 2.2 (There shall be no dead code)
                           QAC: This initialization is redundant. The value of this object is never used before being
                                modified.
      Reason:     Depending on setting of ETHTSYN_DEV_ERROR_DETECT and ETHTSYN_DEV_ERROR_REPORT the initialization
                  might be redundant.
      Risk:       The redundant initialization code might be confusing.
      Prevention: We stick to our well-known code pattern for all API functions.
  MD_EthTSyn_2981_RedundantInit: MISRA rule 2.2 (There shall be no dead code)
                                 QAC: This initialization is redundant. The value of this object is never used before
                                      being modified.
      Reason:     Modification of the variable might depend on the preprocessor settings. Initialization is always done
                  to increase readability and robustness.
      Risk:       The redundant initialization code might be confusing.
      Prevention: None.
  MD_EthTSyn_2987_GlobalDataInit: MISRA rule 2.2 (There shall be no dead code)
                                  QAC: This function call produces no side effects and is redundant.
      Reason:     Global data is initialized inside the called function by using the ComStackLib. Therefore, the
                  function call is required.
      Risk:       None.
      Prevention: None.
  MD_EthTSyn_3315: MISRA rule 16.6 (Every switch statement shall have at least two switch-clauses)
                   QAC: This 'switch' statement contains only a single path - it is redundant.
      Reason:     The amount of switch-clauses depends on the preprocessor setting. For better readability the
                  switch statement is not removed by preprocessor when all switch-clauses but the default are removed
                  by preprocessor.
      Risk:       The switch statement with a default case only might be confusing.
      Prevention: Well structured code.

*/

/* Safe BSW assumptions:

  Runtime Checking:
    The EthTSyn makes use of the ComStackLib Runtime Checking feature. Due to this feature, the GenData access is
    modeled via a configuration pointer by the ComStackLib. For all subsequent defined countermeasures it is
    essential that the EthTSyn_Init function and the config pointer check were executed. The config pointer passed
    to the EthTSyn_Init is provided by the ComStackLib as well.

  Size Relations:
    EthTSyn_AnnounceReceiveSm <-> EthTSyn_AnnounceInfo
    EthTSyn_CtrlState <-> EthTSyn_Ctrl
    EthTSyn_PdelayInfo <-> EthTSyn_PdelayConfig
    EthTSyn_SyncReceiveSm <-> EthTSyn_SlavePort
    EthTSyn_SyncSendSm <-> EthTSyn_MasterPort
    EthTSyn_PortSyncSendSm <-> EthTSyn_MasterPort
    EthTSyn_SystemState <-> EthTSyn_TimeDomain
    EthTSyn_TimeBaseUpdateCounter <-> EthTSyn_TimeDomain
    EthTSyn_TimeValidMasterData <-> EthTSyn_TimeValidMasterCfg
    EthTSyn_TimeValidSlaveData <-> EthTSyn_TimeValidSlaveCfg
    EthTSyn_TimeValidPdReqData <-> EthTSyn_TimeValidPdReqCfg
    EthTSyn_TimeValidPdRespData <-> EthTSyn_TimeValidPdRespCfg
    EthTSyn_SwtMgmtRxBuf <-> EthTSyn_SwtMgmtRxBufCfg

  Indirections:
    EthTSyn_SwtMgmtRxBufCfg -> 1:N to EthTSyn_SwtMgmtRcvdMsgBuf
    EthTSyn_SwtTimeSyncRateRegulatorCfg -> 1:N EthTSyn_RateMeasurement

  These assumptions are modeled in ComStackLib
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_ETHTSYN_CSL01
    \DESCRIPTION      Access of array elements with index generated by ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL02
    \DESCRIPTION      Access of array element with index checked against size of different array.
                      (Arrays Xyz[] and XyzDyn[] depend on ComStackLib size relation.)
    \COUNTERMEASURE   \N Qualified use-case CSL02 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL02_PTR
    \DESCRIPTION      Pointer is generated by address of array element with index checked against size of different
                      array. (Arrays Xyz[] and XyzDyn[] depend on ComStackLib size relation.)
    \COUNTERMEASURE   \N Qualified use-case CSL02 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL03
    \DESCRIPTION      Access of array element with index modeled by indirection.
    \COUNTERMEASURE   \N Qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL03_PTR
    \DESCRIPTION      Pointer is generated by address of array element with index modeled by indirection.
    \COUNTERMEASURE   \N Qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL02_03
    \DESCRIPTION      Access of array element with index modeled by indirection to different array
                      (Arrays Xyz[] and XyzDyn[] depend on ComStackLib size relation.).
    \COUNTERMEASURE   \N Combination of qualified use-cases CSL02 and CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL02_CSL03_2
    \DESCRIPTION      Access of array element with index modeled by indirection. The index used to get the indirection
                      is checked against size of a different array.
    \COUNTERMEASURE   \N Combination of qualified use-cases CSL02 and CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE
    \DESCRIPTION      Pointer to local variable or struct member of local variable is passed as function argument.
    \COUNTERMEASURE   \N [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM
    \DESCRIPTION      Index passed to internal function is used for array write access (directly or via (multiple)
                      indirection(s)) or for pointer generation without additional check.
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_IDX_PARAM]

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01
    \DESCRIPTION      Access of array elements with index provided as function argument.
    \COUNTERMEASURE   \N The valid parameter range is defined in the function header and has to be ensured by the
                         caller. Defaults to qualified use-case CSL01 of ComStackLib.

   \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02
    \DESCRIPTION      Access of array elements with index provided as function argument and checked against size of
                      different array.
    \COUNTERMEASURE   \N The valid parameter range is defined in the function header and has to be ensured by the
                         caller. Defaults to qualified use-case CSL02 of ComStackLib.

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03
    \DESCRIPTION      Access of array elements with index provided as function argument and modeled by indirection.
    \COUNTERMEASURE   \N The valid parameter range is defined in the function header and has to be ensured by the caller.
                         Defaults to qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02
    \DESCRIPTION      Access of array elements with index provided as function argument and modeled by indirection to
                      different array.
    \COUNTERMEASURE   \N The valid parameter range is defined in the function header and has to be ensured by the caller.
                         The validity of the index is ensured by using an indirection (qualified use-case CSL03 of
                         ComStackLib) to a different array with a size relation (qualified use-case CSL02 of
                         ComStackLib)

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02_PTR
    \DESCRIPTION      Array element is passed as pointer with an index provided as function argument and modeled by
                      indirection to different array.
    \COUNTERMEASURE   \N The valid parameter range is defined in the function header and has to be ensured by the caller.
                         The validity of the index is ensured by using an indirection (qualified use-case CSL03 of
                         ComStackLib) to a different array with a size relation (qualified use-case CSL02 of
                         ComStackLib)

  \ID SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_CSL_02_MANDATORY_IND
    \DESCRIPTION      Array write access with an index modeled by ComStackLib indirection. The index
                      used to get the indirection is provided as function argument of an internal function.
                      The indirection is either a 1to1 or a 1toN indirect (i.e. it is always present)
    \COUNTERMEASURE   \N The valid parameter range for the index argument is defined in the function header and has to
                         be ensured by the caller. The index is checked against size of a different array with a size
                         relation (qualified use-case CSL02 of ComStackLib).
                         The usage of the indirection defaults to qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_CSL_02_MANDATORY_IND_PTR
    \DESCRIPTION      Array element is passed as pointer with an index modeled by ComStackLib indirection. The index
                      used to get the indirection is provided as function argument of an internal function.
                      The indirection is either a 1to1 or a 1toN indirect (i.e. it is always present)
    \COUNTERMEASURE   \N The valid parameter range for the index argument is defined in the function header and has to
                         be ensured by the caller. The index is check against size of a different array with a size
                         relation (qualified use-case CSL02 of ComStackLib).
                         The usage of the indirection defaults to qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_CSL_02_MANDATORY_IND_PTR_AND_LOC_VAR_REF
    \DESCRIPTION      Combination of SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (passing reference of local variable as
                      function argument) and SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_CSL_02_MANDATORY_IND_PTR (Array element
                      accessed via ComStackLib indirection is passed as pointer).
    \COUNTERMEASURE   \N The valid parameter range for the index argument is defined in the function header and has to
                         be ensured by the caller. The index is check against size of a different array with a size
                         relation (qualified use-case CSL02 of ComStackLib).
                         The usage of the indirection defaults to qualified use-case CSL03 of ComStackLib.
                         And [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS
    \DESCRIPTION      Access of array elements with index modeled by (optional) indirection or size relation.
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_IDX_PARAM]

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_AS_PTR
    \DESCRIPTION      Passing array element or struct member as pointer.
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_IDX_PARAM] + The pointer is generated by reference of array or struct
                         member.

  \ID SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_SUB_MEMBER_AS_PTR_AND_REF_OF_LOC_VAR
    \DESCRIPTION      Combination of SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_AS_PTR (passing array element
                      or struct member as pointer) and SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (passing reference of
                      local variable as function argument)
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_IDX_PARAM] + The pointer is generated by reference of array or struct
                         member. And [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_CSL_STRUCT_MEMBER_ARRAY_AS_POINTER_CSL_01
    \DESCRIPTION      An array member of a structure is passed as pointer to a function.
    \COUNTERMEASURE   \N The pointer is generated by providing an array member of a structure. The validity of the
                         struct is guaranteed by qualified use-case CSL01 of ComStackLib. When the used index
                         is passed as function argument, the valid parameter range is defined in the function header
                         and has to be ensured by the caller.

  \ID SBSW_ETHTSYN_CSL_STRUCT_MEMBER_ARRAY_AS_POINTER_CSL_02_AND_LOC_VAR_REF
    \DESCRIPTION      Combination of SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (passing reference of local variable as
                      function argument) and an array member of a structure passed as pointer to a function.
    \COUNTERMEASURE   \N The pointer is generated by providing an array member of a structure. The validity of the
                         struct is guaranteed by qualified use-case CSL02 of ComStackLib. When the used index
                         is passed as function argument, the valid parameter range is defined in the function header
                         and has to be ensured by the caller. And [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM
    \DESCRIPTION      Pointer write access to pointer passed as argument.
    \COUNTERMEASURE   \N It is assumed that pointers passed to internal functions are pointing to valid memory and
                         are not NULL_PTR (unless otherwise stated in function header). The validity of the pointer
                         has to be ensured by the caller.

  \ID SBSW_ETHTSYN_INT_FUNC_PTR_PARAM_STRUCT_ELE_ARRAY_WRITE
    \DESCRIPTION       Pointer write access to struct array member with fixed index is performed.
    \COUNTERMEASURE   \N Pointer to struct with array elements is passed to internal functions. It is assumed that
                         the pointer is valid. This has to be ensured by the caller. The used fixed indices used to
                         write to an array element are smaller than the size of the corresponding array.

  \ID SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD
    \DESCRIPTION      Forwarding of passed pointer or pointer element.
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW] and [CM_ETHTSYN_INT_FUNC_IDX_PARAM]

  \ID SBSW_ETHTSYN_PTR_FORWAR_STRUCT_MEMBER_AND_PTR
    \DESCRIPTION      Combination of SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD (Forwarding of passed pointer
                      or pointer element) and SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS(
                      Access of array elements with index modeled by (optional) indirection or size relation.)
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW] and [CM_ETHTSYN_INT_FUNC_IDX_PARAM]

  \ID SBSW_ETHTSYN_PTR_FORWARD_STRUCT_MEMBER_AND_LOC_VAR
    \DESCRIPTION      Combination of SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD (forwarding passed pointer
                      parameter or pointer element) and
                      SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (passing reference of local variable or struct member
                       of local variable as pointer).
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW] and [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF
    \DESCRIPTION      Combination of SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD (forwarding passed pointer
                      parameter or pointer element) and
                      SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (passing reference of local variable as pointer).
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW] and [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_PTR_FORWARD_AND_INT_FUNC_IDX_PARAM_AS_PTR_AND_LOC_VAR_REF
    \DESCRIPTION      Combination of SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD (forwarding passed pointer
                      parameter or pointer element), SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS(
                      Access of array elements with index modeled by (optional) indirection or size relation.) and
                      SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (passing reference of local variable as pointer)
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW], [CM_ETHTSYN_INT_FUNC_IDX_PARAM] and
                         [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR
    \DESCRIPTION      Passing local pointer variable as function argument. The pointer is either the original Ethernet
                      Tx buffer pointer or is generated with a constant index and reference operator.
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_BUFFER]

  \ID SBSW_ETHTSYN_ETH_BUFFER_LOC_PTR_VAR_AND_LOC_VAR_REF
    \DESCRIPTION      Combination of SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR (Passing local pointer variable as function
                      argument) SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (Pointer to local variable is passed as
                      function argument)
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_BUFFER] and [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_ETH_BUFFER_LOC_PTR_VAR_AND_INT_FUNC_IDX_PARAM_AS_PTR
    \DESCRIPTION      Combination of SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR (passing local pointer variable as function
                      argument) and SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS(
                      Access of array elements with index modeled by (optional) indirection or size relation.)
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_BUFFER] and [CM_ETHTSYN_INT_FUNC_IDX_PARAM]

  \ID SBSW_ETHTSYN_LOCAL_PTR_VAR
    \DESCRIPTION      Passing local pointer variable as function argument.
    \COUNTERMEASURE   \N [CM_ETHTSYN_LOC_PTR_VAR]

  \ID SBSW_ETHTSYN_LOC_PTR_VAR_WRITE
    \DESCRIPTION      Pointer write access to a local pointer variable referencing a local variable.
    \COUNTERMEASURE   \N Local pointer variable is set to reference a local variable (by using the address operator).

  \ID SBSW_ETHTSYN_INT_FUNC_FWD_PTR_PARAM_AND_LOC_PTR_VAR
    \DESCRIPTION      Combination of SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD (Forwarding of passed pointer
                      or pointer element) and SBSW_ETHTSYN_LOCAL_PTR_VAR (Passing local pointer variable as function
                      argument)
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW] and [CM_ETHTSYN_LOC_PTR_VAR]

  \ID SBSW_ETHTSYN_ETH_TX_BUFFER_WRITE
    \DESCRIPTION      Pointer write access to Ethernet Tx buffer without length check.
    \COUNTERMEASURE   \S [CM_ETHTSYN_ETH_TX_BUFFER_LEN]

  \ID SBSW_ETHTSYN_ETH_TX_BUFFER_FWD
    \DESCRIPTION      Pointer to Ethernet Tx buffer is forwarded to copy data into the tx buffer.
    \COUNTERMEASURE   \S [CM_ETHTSYN_ETH_TX_BUFFER_LEN]

  \ID SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD
    \DESCRIPTION      Pointer to Ethernet Tx buffer is forwarded to read back data from the Tx buffer.
    \COUNTERMEASURE   \S [CM_ETHTSYN_ETH_TX_BUFFER_LEN]

  \ID SBSW_ETHTSYN_ETH_TX_BUFFER_FWD_AND_LOC_VAR_REF
    \DESCRIPTION      Combination of SBSW_ETHTSYN_ETH_TX_BUFFER_FWD (Pointer to Ethernet Tx buffer is forwarded to copy
                      data into the tx buffer) and SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (Pointer to local variable
                      is passed as function argument)
    \COUNTERMEASURE   \S [CM_ETHTSYN_ETH_TX_BUFFER_LEN] and [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_ETH_TX_BUFFER_PTR_PARAM_WRITE
    \DESCRIPTION      Pointer write access to Ethernet Tx buffer passed as pointer parameter to internal function
                      without length check.
    \COUNTERMEASURE   \S The Ethernet Tx buffer is passed as pointer to the internal function. It is assumed that
                         the pointer is valid + [CM_ETHTSYN_ETH_TX_BUFFER_LEN]

  \ID SBSW_ETHTSYN_PROVIDE_TX_BUFFER_CLR
    \DESCRIPTION      EthTSyn_UtilTx_ProvideTxBuffer() is taking a pointer to a struct used for handling of the
                      Ethernet Tx buffer as parameter. This struct includes a pointer to the actual Ethernet Tx buffer.
                      This pointer is initialized by EthIf_ProvideTxBuffer. The initialized Tx buffer pointer is passed
                      as function argument.
    \COUNTERMEASURE   \S It is assumed that the pointer passed to EthTSyn_UtilTx_ProvideTxBuffer() is valid. In
                         addition it is assumed that the Ethernet Tx buffer pointer is set to a valid memory location
                         with a length equal or greater the requested length by the EthIf when EthIf_ProvideTxBuffer()
                         returned with BUFREQ_OK. The buffer and the initial requested length are passed as function
                         argument to clear the memory.
                         SMI-233513

  \ID SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD
    \DESCRIPTION      Pointer to Ethernet Rx buffer is forwarded to read data from the rx buffer.
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER]

  \ID SBSW_ETHTSYN_ETH_RX_BUFFER_FWD
    \DESCRIPTION      Pointer to Ethernet Rx buffer is forwarded to an internal function.
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER]

 \ID SBSW_ETHTSYN_ETH_RX_BUF_AND_PTR_FWD
   \DESCRIPTION      Pointer to Ethernet Rx buffer and another pointer passed as function argument is forwarded to an
                     internal function.
   \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER] and [CM_ETHTSYN_PTR_FWD]

  \ID SBSW_ETHTSYN_ETH_RX_BUFFER_OFS_FWD
    \DESCRIPTION      Pointer to specific message field within Ethernet Rx buffer is generated by accessing the pointer
                      with a constant index and reference operator.
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER]

  \ID SBSW_ETHTSYN_ETH_RX_BUFFER_FWD_AND_LOC_VAR_REF
    \DESCRIPTION      Combination of SBSW_ETHTSYN_ETH_RX_BUFFER_FWD (Pointer to Ethernet Rx buffer is forwarded to an
                      internal function) and SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE (Pointer to local variable is
                      passed as function argument)
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER] and [CM_ETHTSYN_LOC_VAR_REF]

  \ID SBSW_ETHTSYN_ETH_RX_BUF_FWD_AND_ETH_SWT_MGMT_OBJ_PTR
    \DESCRIPTION      Pointer to Ethernet Rx buffer and EthSwtMgmtObjPtr (this pointer is stored in a structure
                      generated by the ComStackLib. It is accessed via indirection) are forwarded/passed to an internal
                      function.
    \COUNTERMEASURE   \N Combination of [CM_ETHTSYN_ETH_RX_BUFFER] and qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_ETH_RX_BUFFER_SUB_TLV_PTR
    \DESCRIPTION      For processing of the Ar Sub Tlvs, pointers to the start of the Sub Tlv are generated by
                      accessing the Ethernet Rx buffer pointer with a calculated index and reference operator.
                      That the calculated index does not exceed the range of the buffer is ensured during message
                      reception tests and is not repeated.
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER]

  \ID SBSW_ETHTSYN_ETH_BUFFER_CRC_FWD
    \DESCRIPTION       Ethernet Rx/Tx buffer pointer is forwarded to internal function for CRC calculation/evaluation
                       as P2CONST, i.e. no write operation is performed.
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER] and [CM_ETHTSYN_ETH_TX_BUFFER_LEN]

  \ID SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY
    \DESCRIPTION      Crc data is copied from the Ethernet Rx/Tx buffer to the local crc data array via VStdMemCpy.
                      The pointers are generated as follows:
                      - Source pointer: Ethernet Rx/Tx buffer pointer is accessed with a constant or calculated index
                                        to point to the start of the crc data. No data is written to this location.
                      - Target pointer: Local crc data pointer is accessed with the index for the next crc data.
    \COUNTERMEASURE   \N [CM_ETHTSYN_ETH_RX_BUFFER] and [CM_ETHTSYN_ETH_TX_BUFFER_LEN] and [CM_ETHTSYN_CRC_DATA_LEN]

  \ID SBSW_ETHTSYN_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter.
    \COUNTERMEASURE   \N [CM_ETHTSYN_PTR_FWD]

  \ID SBSW_ETHTSYN_POINTER_WRITE
    \DESCRIPTION      Write access to pointer passed as function parameter.
    \COUNTERMEASURE   \N Pointer passed as function parameter points to valid memory location. This includes struct
                         members in case pointer points to a struct type. This is ensured by caller.

  \ID SBSW_ETHTSYN_GLOBAL_VAR_AS_PTR
    \DESCRIPTION      Reference to global variable is passed as function argument.
    \COUNTERMEASURE   \N Pointer is generated by referencing a module global variable which is always stored at a valid
                         memory location.

  \ID SBSW_ETHTSYN_CSL_GLOBAL_VAR_WRITE
    \DESCRIPTION      Pointer write access to a global variable generated with ComStackLib.
    \COUNTERMEASURE   \N Global variable is generated by ComStackLib and accessed via the configuration pointer
                         provided by the ComStackLib as well. The memory location is always valid.

  \ID SBSW_ETHTSYN_ARRAY_WRITE_WITH_OFFSET
    \DESCRIPTION      Array write access with passed offset and additional fixed offset as index.
    \COUNTERMEASURE   \N It is assumed that the passed array is valid and that the passed offset fulfills the
                         preconditions stated in the function header (i.e. Offset < Array.Length - written values).

  \ID SBSW_ETHTSYN_CRC_DATA_ARRAY
    \DESCRIPTION      Array write access is performed without validity check of the used index.
    \COUNTERMEASURE   \N [CM_ETHTSYN_CRC_DATA_LEN]

  \ID SBSW_ETHTSYN_CRC_DATA_ARRAY_PASS
    \DESCRIPTION      Local array variable is passed as pointer.
    \COUNTERMEASURE   \N The local crc data array is passed as pointer together with the length information.

  \ID SBSW_ETHTSYN_SYNC_FUP_SENT_CBK
    \DESCRIPTION      Generated function pointer is called and the pointer to the Ethernet transmission buffer is
                      passed.
    \COUNTERMEASURE   \N It is verified that the generated function pointer is not NULL_PTR (runtime check). In addition
                         it is assumed that the validity of the configured function name is ensured during compile time
                         (an unknown or mismatching symbol causes a compiler/linker error).
                         The pointer to the Ethernet transmission buffer is of type P2CONST, therefore no write
                         operation can be performed by the called function.

  \ID SBSW_ETHTSYN_SWT_SYNC_STATE_CHG_CBK
    \DESCRIPTION      Generated function pointer is called.
    \COUNTERMEASURE   \N It is verified that the generated function pointer is not NULL_PTR (runtime check). In addition
                         it is assumed that the validity of the configured function name is ensured during compile time
                         (an unknown or mismatching symbol causes a compiler/linker error).

  \ID SBSW_ETHTSYN_SYNC_RCV_SM_WRITE_ACCESS_GET_END_STATION_SLAVE_PORT_IDX
    \DESCRIPTION      Pointer write access to sync receive state machine struct member. The pointer to the sync receive
                      state machine is retrieved from the ComStackLib by using the slave port idx (0:1 indirection) of
                      the port returned by EthTSyn_SwtMgmt_GetEndStationSlavePortIdx which is checked for validity
                      (< EthTSyn_GetSizeOfPort()).
    \COUNTERMEASURE   \N When a valid port index is returned by
                         EthTSyn_SwtMgmt_GetEndStationSlavePortIdx, EthTSyn_IsSlavePortUsedOfPort of the returned port
                         is always 'true' and therefore the slave port indirection is present. The sync receive state
                         machine is modeled by a size relation to the slave port. This defaults to qualified use-case
                         CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_CPY_MSG_TO_SITE_SYNC_SYNC_SM
    \DESCRIPTION      A message is copied from an internal EthTSyn reception buffer to a buffer in the site sync sync
                      state machine or between two buffers within the site sync sync state machine via VStdLib_MemCpy.
    \COUNTERMEASURE   \N The target pointer passed to the VStdLib_MemCpy function is generated by passing the fixed
                         size message buffer byte array of the site sync sync state machine. While the site sync sync
                         state machine is retrieved via ComStackLib (qualified use-case CSL01 of ComStackLib). The
                         passed copied length matches the size of the target array. The source pointer is either
                         generated by accessing an EthTSyn internal message buffer generated via ComStackLib (
                         start index is retrieved via indirection (qualified use-case CSL03), while the index used to
                         get the indirection is passed as function argument. The valid range is defined in the function
                         header and ensured by the caller. The validity check is done against the size of a different
                         array (qualified use-case CSL02 of ComStackLib)) or by passing another fixed size message
                         buffer byte array of the same site sync sync state machine.

  \ID SBSW_ETHTSYN_CPY_MSG_TO_ETH_TX_BUF_FROM_SITE_SYNC_SYNC_SM
    \DESCRIPTION      Pointer to Ethernet TxBuffer is forwarded. In addition a pointer to a message stored in the site
                      sync sync state machine buffer is passed as pointer to VStdLib_MemCpy.
    \COUNTERMEASURE   \S [CM_ETHTSYN_ETH_TX_BUFFER_LEN] and the buffer of the site sync sync state machine is accessed
                         via optional indirection by an index passed to an internal function. The valid range of this
                         index is provided in the function header and has to be ensured by the caller. Usage of the
                         index then defaults to qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_ETH_SWT_MGMT_OBJ
    \DESCRIPTION      Pointer write access to a shared object (EthSwtMgmtObj) provided by DrvEthSwt via
                      EthIf_GetTxMgmtObj or EthIf_GetRxMgmtObj. The pointer to the EthSwtMgmtObj is stored in a global
                      EthTSyn internal RxBuf or TxMgmtObj handling structures.
    \COUNTERMEASURE   \S The EthSwtMgmtObj is retrieved via the corresponding EthIf API. When the API returns E_OK
                         it is assumed that the EthSwtMgmtObj pointer was set to a valid EthSwtMgmtObj. When the
                         EthTSyn internal handling structure is in state PENDING or WAIT_RELEASE, the corresponding
                         EthSwtMgmtObj pointer is always valid and a write operation is allowed when the state of the
                         EthSwtMgmtObj is OWNED_BY_UPPER_LAYER. [SMI-585337]

  \ID SBSW_ETHTSYN_TX_MGMT_OBJ_CPY_TS
    \DESCRIPTION      Pointer write access to a pointer stored within a global, EthTSyn internal TxMgmtObj handling
                      structure. The stored pointer is retrieved by using an index passed to an internal function.
    \COUNTERMEASURE   \N Every message transmitted by the EthTSyn is triggered by a state machine (global,
                         generated data of the EthTSyn). A state machine provides memory for the required switch
                         timestamps. Upon TxConfirmation of a transmitted frame, the TxMgmtObj is prepared for later
                         processing. In this stage, the pointer to the state machine timestamps are stored within the
                         TxMgmtObj (if the corresponding timestamp is required). In case the timestmap is not required
                         or no matching state machine was found, a NULL_PTR will be stored. So there is either a
                         NULL_PTR or a valid pointer stored in the TxMgmtObj. Before writing the timestamp to the
                         stored memory location, a NULL_PTR check is performed. The valid range for the index provided
                         as function argument and used to access the stored pointer is defined in the function header
                         and has to be ensured by the caller.

  \ID SBSW_ETHTSYN_CPY_MSG_TO_RX_BUF
    \DESCRIPTION      Pointer to EthTSyn RxBuffer and Ethernet RxBuffer are passed to VStdLib_MemCpy
    \COUNTERMEASURE   \N Access of the EthTSyn RxBuffer is modeled by indirection (qualified use-case CSL03 of
                         ComStackLib). And [CM_ETHTSYN_ETH_RX_BUFFER]

  \ID SBSW_ETHTSYN_NULL_PTR
    \DESCRIPTION      NULL_PTR is passed as function argument.
    \COUNTERMEASURE   \N When the constant NULL_PTR is passed as a function pointer argument, NULL_PTR is a valid
                         parameter value. The called function won't perform any operations with the pointer parameter in
                         case it is NULL_PTR.

SBSW_JUSTIFICATION_END */

/*
  \CM CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW It is assumed that pointers passed to internal functions are pointing to valid
                                       memory and are not NULL_PTR (unless otherwise stated in function header).
                                       The validity of the pointer has to be ensured by the caller. This also applies
                                       if the passed pointer is pointing to a struct and a specific struct member is
                                       forwarded as pointer.

  \CM CM_ETHTSYN_LOC_VAR_REF Pointer is generated by referencing a local variable or a struct member of a local variable
                             via the address operator.

  \CM CM_ETHTSYN_ETH_BUFFER A local pointer variable is passed as function argument. The Rx/Tx buffer is provided by
                            EthIf and is assumed to point to a valid memory location. By the call context (i.e. for Tx
                            starting after ProvideTxBuffer and ending after TxConfirmation and for Rx within
                            RxIndication) it is ensured that the EthTSyn only uses Buffers currently "owned" by the
                            EthTSyn. For global variables where the buffer is stored (e.g. state machines), the
                            validity is ensured when the buffer pointer is not NULL_PTR. The pointer is reseted to
                            NULL_PTR at the end of the valid context.

  \CM CM_ETHTSYN_ETH_TX_BUFFER_LEN The Tx buffer is requested with the maximum required length for the
                                   specific message type from the EthIf via EthIf_ProvideTxBuffer().
                                   The maximum message length is a fixed value for all message types except the
                                   FollowUp message. For the FollowUp message the max required length is generated.
                                   The generated value is verified during module initialization
                                   (EthTSyn_Master_Init() -> EthTSyn_Master_IsFollowUpTxLengthValid()).
                                   Therefore writing to the Tx buffer with fixed offsets is
                                   possible without additional length checks. Write access might be performed directly
                                   with indices.
                                   [SMI-233513]

  \CM CM_ETHTSYN_INT_FUNC_IDX_PARAM For internal functions it is common that only one index (e.g. PortIdx) is passed as
                                    argument. Depending on the function context and/or another parameter, specific
                                    preconditions have to be fulfilled for this index parameters. The valid range and
                                    the preconditions for the index parameter are described in the function header and
                                    have to be ensured by the caller. The usage of the index parameter then defaults
                                    to a combination of the qualified use-cases CSL01, CSL02 and CSL03 of ComStackLib.

  \CM CM_ETHTSYN_LOC_PTR_VAR A local pointer variable is passed as function argument. The pointer is either set to
                             NULL_PTR (when it is allowed by the called function) or set to reference a local/global
                             variable.

  \CM CM_ETHTSYN_ETH_RX_BUFFER The Ethernet Rx buffer is provided to the EthTSyn via EthTSyn_RxIndication().
                               Here it is verified that the pointer is not NULL_PTR. EthTSyn_RxIndication() is a public
                               API, therefore it is assumed that the pointer and the corresponding passed length
                               (LenByte) are valid. The Ethernet Rx buffer pointer is forwarded to internal functions
                               and to IpBase to read data from the buffer. The Length of the buffer is verified to
                               match the corresponding message so no out-of-bound read operation will be performed.
                               In addition no write operation is done on the Ethernet Rx buffer.

  \CM CM_ETHTSYN_PTR_FWD Pointers passed to function point to a valid memory range considering type or an additional
                         function parameter is used to describe pointer validity. This is ensured by the caller.

  \CM CM_ETHTSYN_CRC_DATA_LEN  For crc computation a local array is used for the data required for the crc. The size of
                               the array is set to the max used data elements for the corresponding crc. In addition a
                               local variable for the currently used crc data length is used as offset. This variable is
                               initialized with '0' and always incremented when new crc data is added. When accessing
                               the crc data array with the currently used length and a fixed offset, it is ensured that
                               the resulting index does not exceed the crc data array due to setting the crc data array
                               length to the max required data elements count.
 */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_ETHTSYN_TESTSUITE_INSTRUMENTATION
    \ACCEPT TX
    \REASON This code is only deactivated by test suite for unit testing purpose.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn.c
 *********************************************************************************************************************/
