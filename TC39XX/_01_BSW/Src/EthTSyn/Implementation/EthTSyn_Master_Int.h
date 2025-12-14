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
/*!        \file  EthTSyn_Master_Int.h
 *        \brief  EthTSyn Master internal header file
 *      \details  Contains internal definitions and declarations used by EthTSyn (Master role) only
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined(ETHTSYN_MASTER_INT_H)
# define ETHTSYN_MASTER_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Util_Int.h"

# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

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

#  define ETHTSYN_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_Master_Init
 *********************************************************************************************************************/
/*! \brief      Initializes the Master sub-module.
 *  \details    Initializes all component variables directly related to the Master sub-module.
 *  \return     ETHTSYN_E_NO_ERROR - Master sub-module was initialized successfully
 *  \return     other values - Initialization of master sub-module failed. The error code is returned.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Master_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_Master_InitPort
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Master-Port.
 *  \details    Initializes all component variables directly related to the passed Master-Port.
 *  \param[in]  MasterPortIdx    Index of the Master port to be initialized
 *                               [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPort(
  EthTSyn_IntMasterPortIdxType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_CalcPot
 *********************************************************************************************************************/
/*! \brief      Updates the precise origin timestamp (i.e. sync egress timestamp).
 *  \details    Retrieves the current Ethernet and Stbm time (if required, i.e. Stbm does not use Ethernet clock and
 *              HW-Timestamping is used). These reference times together with the actual egress timestamp and the
 *              time tuple retrieved upon transmission of the sync message are used to calculate the actual
 *              precise origin timestamp.
 *  \param[in]  PortIdx                    Index of the EthTSyn port
 *                                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SyncEgressIntVlt           The sync egress timestamp as internal virtual local time
 *  \param[in]  SyncTxIntVlt               Internal virtual local time that corresponds to the precise origin timestamp
 *  \param[out] PreciseOriginTimestampPtr  The precise origin timestamp
 *  \return     E_OK - Calculation of POT succeeded
 *  \return     E_NOT_OK - Calculation of POT failed
 *  \pre        For PortIdx the following constraint apply: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_CalcPot(
                EthTSyn_IntPortIdxType        PortIdx,
                EthTSyn_IntVltType            SyncEgressIntVlt,
                EthTSyn_IntVltType            SyncTxIntVlt,
  ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType)  PotPtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_HandleCyclicTasks
 *********************************************************************************************************************/
/*! \brief      Handles the cyclic tasks of each Master-Port of the passed TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx    Index of the TimeDomain
 *                               [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Has to be called in context of the EthTSyn_MainFunction() only
 *  \context    TASK
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_HandleCyclicTasks(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  PORT SYNC SEND SM
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_Init
 *********************************************************************************************************************/
/*! \brief      Initializes the PortSyncSendSm of the passed master port.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_Init(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_TxSync
 *********************************************************************************************************************/
/*! \brief      Triggers the transmission of a Sync message.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  MaxSyncLen     Maximum length of the sync message in byte
 *  \return     E_OK - Sync message transmission triggered successfully.
 *  \return     E_NOT_OK - PortSyncSendSm is not in state PENDING or triggering the Sync message transmission failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different master ports
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_TxSync(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint16                     MaxSyncLen);

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_IsSyncSwtIngrTsReadyToProc
 *********************************************************************************************************************/
/*! \brief      Checks if the switch ingress timestamp of the transmitted sync message is ready for processing.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     TRUE - Switch ingress timestamp of the transmitted sync message is ready for processing
 *  \return     FALSE - Switch ingress timestamp of the transmitted sync message is not ready for processing
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_IsSyncSwtIngrTsReadyToProc(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc
 *********************************************************************************************************************/
/*! \brief      Checks if the switch egress timestamp of the transmitted sync message is ready for processing.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     TRUE - Switch egress timestamp of the transmitted sync message is ready for processing
 *  \return     FALSE - Switch egress timestamp of the transmitted sync message is not ready for processing
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc(
  EthTSyn_MasterPortIterType MasterPortIdx);
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_GetSyncHostEgrIntVltMgmt
 *********************************************************************************************************************/
/*! \brief      Gets the host egress timestamp of the transmitted sync message as internal virtual local time and its
 *              validity information.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     The host egress timestamp of the transmitted sync message as internal virtual local time and its
 *              validity info
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_GetSyncHostEgrIntVltMgmt(
  EthTSyn_MasterPortIterType MasterPortIdx);

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_GetSyncSwtIngrTsMgmt
 *********************************************************************************************************************/
/*! \brief      Gets the switch ingress timestamp of the transmitted sync message and its state.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     The switch ingress timestamp of the transmitted sync message and its state
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_GetSyncSwtIngrTsMgmt(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt
 *********************************************************************************************************************/
/*! \brief      Gets the switch egress timestamp of the transmitted sync message and its state.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     The switch egress timestamp of the transmitted sync message and its state
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt(
  EthTSyn_MasterPortIterType MasterPortIdx);
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_ProvideSyncHostEgrIntVlt
 *********************************************************************************************************************/
/*! \brief      Provides the host egress timestamp of the transmitted sync message and its validity information to the
 *              PortSyncSendSm.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  EgrTsMgmtPtr   The host egress timestamp of the transmitted sync as internal virtual local time and its
 *                             validity info
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different master ports
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_ProvideSyncHostEgrIntVlt(
                  EthTSyn_MasterPortIterType MasterPortIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType)    EgrTsMgmtPtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_WasSyncTxConfCalled
 *********************************************************************************************************************/
/*! \brief      Checks if the TxConfirmation of the transmitted sync message was already called.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     TRUE - Sync TxConfirmation was already called
 *  \return     FALSE - Sync TxConfirmation was not yet called
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_WasSyncTxConfCalled(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_TxFup
 *********************************************************************************************************************/
/*! \brief      Triggers the transmission of a FollowUp message.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  MaxFupLen      Maximum length of the FollowUp message in byte
 *  \return     E_OK - FollowUp message transmission triggered successfully.
 *  \return     E_NOT_OK - PortSyncSendSm is not in state WAIT_FUP or triggering the FollowUp message transmission
 *                         failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different master ports
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_TxFup(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint16                     MaxFupLen);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CancelCycle
 *********************************************************************************************************************/
/*! \brief      Cancels an active Sync/FollowUp cycle.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CancelCycle(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CheckForMatchingTxConf
 *********************************************************************************************************************/
/*! \brief      Checks if a TxConfirmation was invoked for a transmitted Sync or FollowUp message.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  BufIdx         Index of the Ethernet TxBuffer the TxConfirmation was invoked for
 *  \param[out] MsgTypePtr     ETHTSYN_MSG_TYPE_SYNC - TxConfirmation was invoked for the transmitted Sync message
 *                             ETHTSYN_MSG_TYPE_FOLLOW_UP - TxConfirmation was invoked for the transmitted FollowUp
 *                                                          message
 *                             Unchanged - TxConfirmation was neither invoked for the transmitted Sync nor for the
 *                                         transmitted FollowUp message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CheckForMatchingTxConf(
                EthTSyn_MasterPortIterType MasterPortIdx,
                uint8                      BufIdx,
  ETHTSYN_P2VAR(uint8)                     MsgTypePtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_ProcSyncTxConf
 *********************************************************************************************************************/
/*! \brief      Processes the TxConfirmation for the transmitted Sync message.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  EthIfCtrlIdx   Index of the Ethernet interface controller
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different master ports
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_ProcSyncTxConf(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint8                      EthIfCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_ProcFupTxConf
 *********************************************************************************************************************/
/*! \brief      Processes the TxConfirmation for the transmitted FollowUp message.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different master ports
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_ProcFupTxConf(
  EthTSyn_MasterPortIterType MasterPortIdx);


#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
#endif /* ETHTSYN_MASTER_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Master_Int.h
 *********************************************************************************************************************/
