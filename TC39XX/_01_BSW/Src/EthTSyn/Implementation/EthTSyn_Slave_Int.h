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
/*!        \file  EthTSyn_Slave_Int.h
 *        \brief  EthTSyn Slave internal header file
 *      \details  Contains internal definitions and declarations used by EthTSyn (Slave role) only
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

#if !defined(ETHTSYN_SLAVE_INT_H)
# define ETHTSYN_SLAVE_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
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
 *  EthTSyn_Slave_Init
 *********************************************************************************************************************/
/*! \brief      Initializes the Slave sub-module.
 *  \details    Initializes all component variables directly related to the Slave sub-module.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_Slave_InitPort
 *********************************************************************************************************************/
/*! \brief      Initializes the given Slave port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Slave-Port.
 *  \param[in]  SlavePortIdx  Index of the slave port
 *                            [range: SlavePortIdx < EthTSyn_GetSizeOfSlavePort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_InitPort(
  EthTSyn_IntSlavePortIdxType SlavePortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Slave_HandleCyclicTasks
 *********************************************************************************************************************/
/*! \brief      Handles the cyclic tasks of each Slave-Port of the passed TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx    Index of the TimeDomain
 *                               [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_HandleCyclicTasks(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcRcvdSyncMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Sync message.
 *  \details    Checks if passed port is ready to receive a Sync message and optionally processes the message.
 *  \param[in]  RxBufPtr             Pointer to the Ethernet reception buffer of the received Sync message
 *  \param[in]  PortIdx              Index of the Port the message was received on
 *                                   [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  IngressTsVltMgmtPtr  The ingress timestamp as internal virtual local time and its validity info
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcRcvdSyncMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressTsVltMgmtPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_WriteSyncMsgToSyncReceiveSm
 *********************************************************************************************************************/
/*! \brief      Verifies sequence Id and writes relevant information of a received Sync message to the sync receive SM
 *              of the given port.
 *  \details    -
 *  \param[in]  RxBufPtr             Pointer to the Ethernet reception buffer of the received Sync message
 *  \param[in]  PortIdx              Index of the Port the message was received on
 *                                   [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK     - Sequence Id is valid.
 *  \return     E_NOT_OK - Sequence Id is invalid.
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_WriteSyncMsgToSyncReceiveSm(
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
  EthTSyn_IntPortIdxType  PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcRcvdFupMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received FollowUp message.
 *  \details    Check if passed port is ready to receive a FollowUp message and optionally processes the message.
 *  \param[in]  RxBufPtr    Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  PortIdx     Index of the Port the message was received on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcRcvdFupMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_IsFupMatchingSync
 *********************************************************************************************************************/
/*! \brief      Verify received FollowUp message.
  *  \details    Check that sync receive SM is waiting for FollowUp message and that sequence id and source port
  *              match the previous sync message.
  *  \param[in]  RxBufPtr    Pointer to the Ethernet reception buffer of the received FollowUp message
  *  \param[in]  PortIdx     Index of the Port the message was received on
  *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return      TRUE  - Received FollowUp message is valid.
 *  \return      FALSE - Received FollowUp message is invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_SlaveRx_IsFupMatchingSync(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx);

#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
#   if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcRcvdAnnounceMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Announce message.
 *  \details    Checks if passed port is ready to receive an Announce message and optionally processes the message.
 *  \param[in]  RxBufPtr    Pointer to the Ethernet reception buffer of the received announce message
 *  \param[in]  PortIdx     Index of the Port the message was received on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcRcvdAnnounceMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx);
#   endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)) */

#  if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_SetMasterPriorityVector
 *********************************************************************************************************************/
/*! \brief      Sets the EthTSyn system state of the master priority vector for the passed TimeDomain.
 *  \details    -
 *  \param[in]  RxBufPtr          Pointer to the Ethernet reception buffer of the received announce message
 *  \param[in]  TimeDomainIdx     Index of the TimeDomain the master priority should be set for
 *                                [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SetMasterPriorityVector(
  ETHTSYN_P2CONST(uint8)                        RxBufPtr,
                  EthTSyn_IntTimeDomainIdxType  TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_Slave_ResetMasterPriorityVector
 *********************************************************************************************************************/
/*! \brief      Resets the EthTSyn system state of the master priority vector for the passed TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx  Index of the TimeDomain the master priority should be reseted for
 *                             [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ResetMasterPriorityVector(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx);
#  endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
#endif /* ETHTSYN_SLAVE_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Slave_Int.h
 *********************************************************************************************************************/
