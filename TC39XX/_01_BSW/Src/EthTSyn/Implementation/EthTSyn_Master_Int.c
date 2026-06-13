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
/*!       \file  EthTSyn_Master_Int.c
 *        \brief  EthTSyn Master source file - Internal Functions
 *      \details  EthTSyn Master source file containing the EthTSyn Master implementation of the EthTSyn module.
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

#define ETHTSYN_MASTER_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Master_Int.h" /* PRQA S 0883, 3219 */ /* MD_EthTSyn_0883, MD_EthTSyn_3219 */

#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
# include "EthTSyn_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
# include "EthTSyn_Crc_Int.h"

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
#  include "EthTSyn_SwtMgmt_Int.h"
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#   include "EthTSyn_SwtTimeSync_Int.h"
#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
#  include "EthTSyn_TimeValidation_Int.h"
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (13u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (2u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_Master_Int.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (13u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (2u)) )
#  error "Version numbers of EthTSyn_Master_Int.c and EthTSyn_Cfg.h are inconsistent!"
# endif

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

# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_Master_InitPortInternal
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Master port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Master Port.
 *  \param[in]  MasterPortIdx   Index of the Master port
 *                              [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPortInternal(
  EthTSyn_MasterPortIterType MasterPortIdx);

# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_IsFollowUpTxLengthValid
 *********************************************************************************************************************/
/*! \brief      Checks if the generated FollowUp Tx length is valid for the passed master port.
 *  \details    -
 *  \param[in]  MasterPortIdx   Index of the Master port
 *                              [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     TRUE - Generated FollowUp Tx length is valid.
 *  \return     FALSE - Generated FollowUp Tx length is invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsFollowUpTxLengthValid(
  EthTSyn_MasterPortIterType MasterPortIdx);
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Master_IsImmediateTimeSyncRequired
 *********************************************************************************************************************/
/*! \brief      Checks if the an immediate time sync should be triggered for the given time domain.
 *  \details    Checks if immediate time sync feature is enabled for the passed time domain and if so, checks if an
 *              immediate time sync is required according to SynchronizedTimeBaseStatus and TimeBaseUpdateCounter
 *              (both retrieved from StbM).
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     TRUE - Trigger immediate time sync
 *  \return     FALSE - Do not trigger immediate time sync
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsImmediateTimeSyncRequired(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_IsGlobalTimeBaseStatusBit
 *********************************************************************************************************************/
/*! \brief      Checks if the GLOBAL_TIME_BASE status bit of the StbM_TimeBaseStatus is set for the passed time domain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     TRUE - GLOBAL_TIME_BASE status bit is set
 *  \return     FALSE - GLOBAL_TIME_BASE status bit is not set
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsGlobalTimeBaseStatusBit(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_HasTimeBaseUpdateCounterChanged
 *********************************************************************************************************************/
/*! \brief      Check if the time base update counter has changed since last check for the passed time domain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     TRUE - Time base update counter has changed since last check
 *  \return     FALSE - Time base update counter has not changed since last check
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_HasTimeBaseUpdateCounterChanged(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_ProcSm
 *********************************************************************************************************************/
/*! \brief      Handles the processing of the Sync Send state-machine for the given Port.
 *  \details    -
 *  \param[in]  PortIdx    Index of the Port that state-machine should be processed
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_ProcSm(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_CpySync
 *********************************************************************************************************************/
/*! \brief      Copies the Sync message from the SyncSendSm of the provided master port to the provided TxBuffer
 *  \details    -
 *  \param[in]  MasterPortIdx   Index of the master port
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[out] TxBufPtr        The Sync message in Network-Byte-Order
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_CpySync(
                EthTSyn_MasterPortIterType MasterPortIdx,
  ETHTSYN_P2VAR(uint8)                     TxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_IsFupTxReady
 *********************************************************************************************************************/
/*! \brief      Checks if FollowUp message is ready for transmission on the given master Port.
 *  \details    -
 *  \param[in]  PortIdx      Index of the port
 *                           [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - FollowUp message is ready for transmission
 *  \return     FALSE - FollowUp message is not ready for transmission
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_SyncSend_IsFupTxReady(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_CpyFup
 *********************************************************************************************************************/
/*! \brief      Copies a FollowUp message to the provided TxBuffer.
 *  \details    Assembles the FollowUp message for the given Port and copies it to the provided TxBuffer in
 *              Network-Byte-Order.
 *  \param[in]  PortIdx         Index of the port
 *                              [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[out] TxBufPtr        The Assembled FollowUp message in network byte order
 *  \return     Actual length of the FollowUp message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_Master_SyncSend_CpyFup(
                EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2VAR(uint8)                  TxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_CalcFupCorrVal
 *********************************************************************************************************************/
/*! \brief      Calculates the value of the FollowUp correction field for a transmitted FollowUp message.
 *  \details    -
 *  \param[in]  MasterPortIdx   Index of the master port
 *                              [range: PortIdx = EthTSyn_GetSizeOfMasterPort()]
 *  \return     Value of the FollowUp correction field.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimediffType, ETHTSYN_CODE) EthTSyn_Master_SyncSend_CalcFupCorrVal(
  EthTSyn_IntMasterPortIdxType MasterPortIdx);

# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_ProvideSwtTimeSyncTs
 *********************************************************************************************************************/
 /*! \brief      Provides the timestamps required for switch time synchronization to the SwtTimeSync sub-module.
  *  \details    -
  *  \param[in]  MasterPortIdx   Index of the master port
  *                              [range: PortIdx = EthTSyn_GetSizeOfMasterPort()]
  *  \pre        -
  *  \context    TASK|ISR2
  *  \reentrant  TRUE
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_ProvideSwtTimeSyncTs(
  EthTSyn_IntMasterPortIdxType MasterPortIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTlvs
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Tlvs.
 *  \details       Appends the optional AUTSAR (Sub)-Tlvs to an already assembled FollowUp message.
 *  \param[in]     PortIdx   Index of the port the FollowUp is transmitted on
 *                           [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in,out] TxBufPtr  In:  The assembled FollowUp message in Network-Byte-Order
 *                           Out: The appended FollowUp Ar Tlvs in Network-Byte-Order
 *  \return        The total length of all appended TLVs (including the Ar TLV Header) in Bytes
 *  \pre           The FollowUp message was already copied to the provided TxBuffer in Network-Byte-Order
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
/* AR4.3 message format */
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTlvs(
                  EthTSyn_IntPortIdxType  PortIdx,
    ETHTSYN_P2VAR(uint8)                  TxBufPtr);

#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTimeTlv
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Time TLV.
 *  \details       Appends the option AUTOSAR Sub-Tlv TimeSecured to an already assembled FollowUp message.
 *  \param[in]     PortIdx         Index of the port the FollowUp is transmitted on
 *                                 [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId          DataId used for Crc calculation
 *  \param[in,out] TxBufPtr        In:  Pointer to the Ethernet transmission buffer of the FollowUp message
 *                                 Out: The appended Time Sub-Tlv
 *  \param[in,out] OffsetPtr       In:  Offset in the given buffer where to store the Sub-Tlv
 *                                 Out: New offset which has to be used for the next Sub-Tlv
 *  \return        0 - Time Sub-Tlv was omitted
 *  \return        other values - Length of the appended Time Sub-Tlv
 *  \pre           The FollowUp message was already copied to the provided TxBuffer in Network-Byte-Order
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTimeTlv(
                EthTSyn_IntPortIdxType  PortIdx,
                uint8                   DataId,
  ETHTSYN_P2VAR(uint8)                  TxBufPtr,
  ETHTSYN_P2VAR(uint16)                 OffsetPtr);
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpStatusTlv
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Status TLV.
 *  \details       Appends the optional AUTOSAR Sub-Tlv Status (Secured) to an already assembled FollowUp message.
 *  \param[in]     PortIdx         Index of the port the FollowUp is transmitted on
 *                                 [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId          DataId used for Crc calculation
 *  \param[in,out] TxBufPtr        In:  Pointer to the Ethernet transmission buffer of the FollowUp message
 *                                 Out: The appended Status Sub-Tlv
 *  \param[in,out] OffsetPtr       In:  Offset in the given buffer where to store the Tlv
 *                                 Out: New offset which has to be used for the next Tlv
 *  \return        0 - Status Sub-Tlv was omitted
 *  \return        other values - Length of the appended Status Sub-Tlv
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpStatusTlv(
                EthTSyn_IntPortIdxType  PortIdx,
                uint8                   DataId,
  ETHTSYN_P2VAR(uint8)                  TxBufPtr,
  ETHTSYN_P2VAR(uint16)                 OffsetPtr);

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpUserDataTlv
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR UserData TLV.
 *  \details       Append the optional AUTOSAR Sub-Tlv UserData (Secured) to an already assembled FollowUp message.
 *  \param[in]     PortIdx        Index of the port the FollowUp is transmitted on
 *                                [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId         DataId used for Crc calculation
 *  \param[in,out] TxBufPtr       In:  Pointer to the Ethernet transmission buffer of the FollowUp message
 *                                Out: The appended UserData Sub-Tlv
 *  \param[in,out] OffsetPtr      In:  Offset in the given buffer where to store the Tlv
 *                                Out: New offset which has to be used for the next Tlv
 *  \return        0 - UserData Sub-Tlv was omitted
 *  \return        other values - Length of the appended UserData Sub-Tlv
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpUserDataTlv(
                EthTSyn_IntPortIdxType  PortIdx,
                uint8                   DataId,
  ETHTSYN_P2VAR(uint8)                  TxBufPtr,
  ETHTSYN_P2VAR(uint16)                 OffsetPtr);

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpOfsTlvs
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Ofs TLVs.
 *  \details       Appends the optional AUTOSAR Sub-Tlv(s) Ofs (Secured) to an already assembled FollowUp message.
 *  \param[in]     PortIdx        Index of the port the FollowUp is transmitted on
 *                                [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId         DataId used for Crc calculation
 *  \param[in,out] TxBufPtr       In:  Pointer to the Ethernet transmission buffer of the FollowUp message
 *                                Out: The appended Ofs Sub-Tlv(s)
 *  \param[in,out] OffsetPtr      In:  Offset in the given buffer where to store the Tlv
 *                                Out: New offset which has to be used for the next Tlv
 *  \return        0 - Ofs Sub-Tlv was omitted
 *  \return        other values - Length of the appended Ofs Sub-Tlv(s)
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpOfsTlvs(
                EthTSyn_IntPortIdxType  PortIdx,
                uint8                   DataId,
  ETHTSYN_P2VAR(uint8)                  TxBufPtr,
  ETHTSYN_P2VAR(uint16)                 OffsetPtr);
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_TimeBaseStatusToArSubTlvStatus
 *********************************************************************************************************************/
/*! \brief         Converts the passes StbmTimeBaseStatus into the AUTOSAR Sub-TLV status.
 *  \details       -
 *  \param[in]     StbmTimeBaseStatus  The StbM Time Base Status
 *  \return        The passed StbmTimeBaseStatus as AUTOSAR Sub-TLV status field.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_MasterTx_TimeBaseStatusToArSubTlvStatus(
  StbM_TimeBaseStatusType StbmTimeBaseStatus);

/**********************************************************************************************************************
 *  END: MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_TxSync
 *********************************************************************************************************************/
/*! \brief      Handles the Sync message transmission of the sync send state machine (triggered by
 *              EthTSyn_Master_SyncSend_ProcSm() ).
 *  \details    Triggers the (immediate) sync message transmission and handles the state machine accordingly.
 *  \param[in]  PortIdx          Index of the master port, the sync message should be transmitted on
 *                               [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  IsImmediateSync  Indicating if the sync is an immediate sync
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_TxSync(
  EthTSyn_IntPortIdxType  PortIdx,
  boolean                 IsImmediateSync);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_HndlWaitSyncEgrTsState
 *********************************************************************************************************************/
/*! \brief      Handles the state WAIT_SYNC_EGR_TS of the SyncSendSm.
 *  \details    Checks if the sync egress timestamp of the passed port is ready for processing. Calculates the POT
 *              in case the sync egress timestamp is ready for processing and is available. In addition it checks for
 *              an expired sync cycle and takes care of the state transition to leave the WAIT_SYNC_EGR_TS state.
 *  \param[in]  PortIdx   Index of the master port, the sync message should be transmitted on
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different PortIdx.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_HndlWaitSyncEgrTsState(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_UpdateAndAssignPot
 *********************************************************************************************************************/
/*! \brief      Updates the precise origin timestamp (i.e. sync egress timestamp) and assigns it to the corresponding
 *              sync send state machine.
 *  \details    -
 *  \param[in]  PortIdx               Index of the EthTSyn port
 *                                    [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SyncEgrIntVltMgmtPtr  The sync egress timestamp as internal virtual local time and its validity info
 *  \return     E_OK - POT is valid and calculation succeeded. POT and its state are assigned to the SyncSendSm
 *  \return     E_NOT_OK - POT is invalid or calculation failed. Only the POT state is assigned to the SyncSendSm.
 *  \pre        For PortIdx the following constraint apply: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_SyncSend_UpdateAndAssignPot(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) SyncEgrIntVltMgmtPtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_TxFup
 *********************************************************************************************************************/
/*! \brief      Handles the FollowUp message transmission of the sync send state machine (triggered by
 *              EthTSyn_Master_SyncSend_ProcSm() ).
 *  \details    Triggers the FollowUp message transmission, as well as the optional transmission of an Announce message,
 *              and handles the state machine accordingly.
 *  \param[in]  PortIdx    Index of the master port, the follow up message should be transmitted on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_TxFup(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  ANNOUNCE SEND SM
 *********************************************************************************************************************/
# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_Init
 *********************************************************************************************************************/
/*! \brief      Initializes the Announce send state machine of the passed master port.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        Has to be called in context of the EthTSyn_Init()
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_Init(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_ProcSm
 *********************************************************************************************************************/
/*! \brief      Processes the Announce send state machine of the passed master port.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        Has to be called cyclically in context of the EthTSyn_MainFunction() only
 *  \context    TASK
 *  \reentrant  TRUE for different master ports.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_ProcSm(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_DecTimer
 *********************************************************************************************************************/
/*! \brief      Decrements the announce cycle timer if it is not expired.
 *  \details    -
 *  \param[in]  AnnounceSmCfgIdx  Index of the AnnounceSendSm
 *                                [range: AnnounceSmCfgIdx < EthTSyn_GetSizeOfAnnounceSendSmCfg()]
 *  \pre        Has to be called cyclically in context of the EthTSyn_MainFunction()
 *  \return     TRUE - Announce cycle timer expired with this cycle
 *  \return     FALSE  Announce cycle timer was already expired before this cycle or is not yet expired
 *  \context    TASK
 *  \reentrant  TRUE for different AnnounceSend state machines.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_DecTimer(
  EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType AnnounceSmCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_TxAnnounce
 *********************************************************************************************************************/
/*! \brief      Triggers transmits of an Announce message.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     E_OK - Succeeded to trigger Announce message transmission
 *  \return     E_NOT_OK - Failed to trigger Announce message transmission
 *  \pre        Has to be called cyclically in context of the EthTSyn_MainFunction()
 *  \pre        Constraint for MasterPortIdx: EthTSyn_IsAnnounceSendSmCfgUsedOfMasterPort() == TRUE
 *  \context    TASK
 *  \reentrant  TRUE for different master ports
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_TxAnnounce(
  EthTSyn_MasterPortIterType MasterPortIdx);
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  PORT SYNC SEND SM
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_InitInternal
 *********************************************************************************************************************/
/*! \brief      Initializes the PortSyncSendSm of the passed master port.
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_InitInternal(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CpySync
 *********************************************************************************************************************/
/*! \brief      Copies the Sync message from the SiteSyncSync or SyncSendSm to the Ethernet TxBuffer
 *              (in Network-Byte-Order).
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[out] EthTxBufPtr    Pointer to the Ethernet Tx-Buffer. The Sync message will be copied here
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CpySync(
                EthTSyn_MasterPortIterType MasterPortIdx,
  ETHTSYN_P2VAR(uint8)                     EthTxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CpyFup
 *********************************************************************************************************************/
/*! \brief      Copies the FollowUp message from the SiteSyncSync or SyncSendSm to the Ethernet TxBuffer
 *              (in Network-Byte-Order).
 *  \details    -
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  MaxFupLen      Maximum length of the FollowUp message in byte
 *  \param[out] EthTxBufPtr    Pointer to the Ethernet Tx-Buffer. The FollowUp message will be copied here
 *  \return     Actual length of the FollowUp message in byte
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CpyFup(
                EthTSyn_MasterPortIterType MasterPortIdx,
                uint16                     MaxFupLen,
  ETHTSYN_P2VAR(uint8)                     EthTxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_Transmit
 *********************************************************************************************************************/
/*! \brief      Prepares and triggers message transmission on the passed master port.
 *  \details    Prepares message transmission (i.e. sets switch management info and enables timestamping if required).
 *              Triggers the transmission of the Ethernet TxBuffer in case of successful preparation.
 *              Releases the Ethernet TxBuffer in case any error occurs.
 *  \param[in]  MasterPortIdx  Index of the master port
 *                             [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  MsgTxLen       Length of the message to be transmitted in byte
 *  \param[in]  EnableTsFlags  Bit field indicating which timestamps should be enabled
 *  \param[in]  TxBufPtr       Pointer to the Ethernet TxBuffer information
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different master ports
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_Transmit(
                  EthTSyn_MasterPortIterType       MasterPortIdx,
                  uint16                           MsgTxLen,
                  EthTSyn_EnableTimestampFlagsType EnableTsFlags,
  ETHTSYN_P2CONST(EthTSyn_EthTxBufferStructType)   TxBufPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Master_InitPortInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPortInternal(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(MasterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set sync send state machine values. */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  /* Bridge */
  {
    const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
#  if (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT)
#   if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
    if(EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(timeDomainIdx) == TRUE)
    {
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_DISABLED;                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
    else
#   endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
#  endif /* (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT) */
    {
      if(EthTSyn_Util_IsSwitchPort(portIdx) == TRUE)
      {
        /* Switch Port -> Initialize sync send state machine. */
        syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_INITIALIZING;                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        syncSendSmPtr->SequenceId = 0u;                                                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        syncSendSmPtr->TxIntervalCnt = 0u;                                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        syncSendSmPtr->LogMessageInterval = EthTSyn_GetSyncLogMsgIntervalOfMasterPort(MasterPortIdx);                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      }
      else
      {
        /* End-Station Port -> Disable sync send state machine by setting the state to 'DISABLED'. */
        syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_DISABLED;                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      }
    }
  }
# else
  /* End-Station */
  syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_INITIALIZING;                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  syncSendSmPtr->SequenceId = 0u;                                                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  syncSendSmPtr->TxIntervalCnt = 0u;                                                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  syncSendSmPtr->LogMessageInterval = EthTSyn_GetSyncLogMsgIntervalOfMasterPort(MasterPortIdx);                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  /* #20 Initialize the PortSyncSendSm. */
  EthTSyn_Master_PortSyncSend_Init(MasterPortIdx);

  /* #30 Initialize the AnnounceSendSm if applicable. */
# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
  EthTSyn_Master_AnnounceSend_Init(MasterPortIdx);
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */
} /* EthTSyn_Master_InitPortInternal() */

# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_IsFollowUpTxLengthValid
 *********************************************************************************************************************/
/*!
 *
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
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsFollowUpTxLengthValid(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 expectedFollowUpMsgLength = ETHTSYN_MSG_FOLLOW_UP_TX_LENGTH;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute the expected FollowUp Tx length. */
#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_ON)
  /* #30 The expected length is ETHTSYN_MSG_FOLLOW_UP_TX_LENGTH in case ETHTSYN_MESSAGE_COMPLIANCE == STD_ON. */
#  else
  /* #40 In case of ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF the expected length is calculated by
   *      ETHTSYN_MSG_FOLLOW_UP_TX_LENGTH + [ArTlvHdr length] + [sum of all possibly used Sub-Tlvs]. */

#   if (ETHTSYN_CRC_SUPPORT == STD_ON)
  if(EthTSyn_IsTimeSubTlvOfMasterPort(MasterPortIdx) == TRUE)
  {
    /* #400 Add ETHTSYN_AR_SUB_TLV_TIME_LENGTH in case Time Sub-Tlv is used. */
    expectedFollowUpMsgLength += ETHTSYN_AR_SUB_TLV_TIME_LENGTH;
  }
#   endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
  if(EthTSyn_IsStatusSubTlvOfMasterPort(MasterPortIdx) == TRUE)
  {
    /* #401 Add ETHTSYN_AR_SUB_TLV_STATUS_LENGTH in case Status Sub-Tlv is used. */
    expectedFollowUpMsgLength += ETHTSYN_AR_SUB_TLV_STATUS_LENGTH;
  }
  if(EthTSyn_IsUserDataSubTlvOfMasterPort(MasterPortIdx) == TRUE)
  {
    /* #402 Add ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH in case UserData Sub-Tlv is used. */
    expectedFollowUpMsgLength += ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH;
  }
#   if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
  if(EthTSyn_IsOfsSubTlvOfMasterPort(MasterPortIdx) == TRUE)
  {
    /* #403 Add ETHTSYN_AR_SUB_TLV_OFS_LENGTH for each offset time domain in case Ofs Sub-Tlv is used. */
    const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
    EthTSyn_OffsetTimeDomainIterType ofsTimeDomainIter;

    for(ofsTimeDomainIter = EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(timeDomainIdx);
        ofsTimeDomainIter < EthTSyn_GetOffsetTimeDomainEndIdxOfTimeDomain(timeDomainIdx);
        ofsTimeDomainIter++)
    {
      expectedFollowUpMsgLength += ETHTSYN_AR_SUB_TLV_OFS_LENGTH;
    }
  }
#   endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

  if(expectedFollowUpMsgLength > ETHTSYN_MSG_FOLLOW_UP_TX_LENGTH)
  {
    /* #404 Add the ArTlvHdr length in case any Sub-Tlv is used. */
    expectedFollowUpMsgLength += ETHTSYN_AR_TLV_HEADER_LENGTH;
  }
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_ON) */

  /* #50 Return TRUE in case the generated length is greater or equal the expected length. Otherwise return FALSE. */
  /* Note: The generated length is used to allocate an Ethernet Tx buffer for the FollowUp message. Therefore there
   *       is no risk when the generated length is greater than expected. */
  return ((EthTSyn_GetFollowUpMsgLengthOfMasterPort(MasterPortIdx) >= expectedFollowUpMsgLength) ? TRUE : FALSE);
} /* EthTSyn_Master_IsFollowUpTxLengthValid() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Master_IsImmediateTimeSyncRequired
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsImmediateTimeSyncRequired(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean triggerImmediateTimeSync = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if immediate time sync is activated for the time domain. */
  if(EthTSyn_IsImmediateTimeSyncOfTimeDomain(TimeDomainIdx) == TRUE)
  {
    /* #20 Check global time base status bit. */
    if(EthTSyn_Master_IsGlobalTimeBaseStatusBit(TimeDomainIdx) == TRUE)
    {
      /* #30 Check if time base update counter has changed. */
      triggerImmediateTimeSync = EthTSyn_Master_HasTimeBaseUpdateCounterChanged(TimeDomainIdx);
    }
  }

  return triggerImmediateTimeSync;
} /* EthTSyn_Master_IsImmediateTimeSyncRequired() */

/**********************************************************************************************************************
 *  EthTSyn_Master_IsGlobalTimeBaseStatusBit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsGlobalTimeBaseStatusBit(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isGlobalTimeBase = FALSE;
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(TimeDomainIdx);
  StbM_TimeBaseStatusType timeBaseStatusLoc;
  StbM_TimeBaseStatusType ofsTimeBaseStatusLoc;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the time base status from Stbm. */
  if(StbM_GetTimeBaseStatus(timeBaseId, &timeBaseStatusLoc, &ofsTimeBaseStatusLoc) == E_OK)                            /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    /* #100 Check if the Global Time Base bit is set. */
    if((timeBaseStatusLoc & ETHTSYN_TIME_BASE_STATUS_GLOBAL_TIME_BASE_MASK) != 0u)
    {
      isGlobalTimeBase = TRUE;
    }
  }

  return isGlobalTimeBase;
} /* EthTSyn_Master_IsGlobalTimeBaseStatusBit() */

/**********************************************************************************************************************
 *  EthTSyn_Master_HasTimeBaseUpdateCounterChanged
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_HasTimeBaseUpdateCounterChanged(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean updateCounterHasChanged = FALSE;
  uint8 updateCounter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get current time base update counter from StbM. */
  updateCounter = StbM_GetTimeBaseUpdateCounter(EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(TimeDomainIdx));

  /* #20 Check if time base update counter has been read before. */
  if(EthTSyn_IsValidOfTimeBaseUpdateCounter(TimeDomainIdx) == TRUE)
  {
    /* #200 Check if value has changed. */
    if(updateCounter != EthTSyn_GetValueOfTimeBaseUpdateCounter(TimeDomainIdx))
    {
      EthTSyn_SetValueOfTimeBaseUpdateCounter(TimeDomainIdx, updateCounter);                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
      updateCounterHasChanged = TRUE;
    }
  }
  else
  {
    /* #201 Store initial value. */
    EthTSyn_SetValueOfTimeBaseUpdateCounter(TimeDomainIdx, updateCounter);                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
    EthTSyn_SetValidOfTimeBaseUpdateCounter(TimeDomainIdx, TRUE);                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_01 */
  }

  return updateCounterHasChanged;
} /* EthTSyn_Master_HasTimeBaseUpdateCounterChanged() */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_ProcSm
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_ProcSm(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Check state of the sync send state machine. */
  switch(syncSendSmPtr->State)
  {
  case ETHTSYN_S_SYNC_SEND_SM_INITIALIZING:
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);

    /* #200 State: Initializing -> Check if GLOBAL_TIME_BASE bit of StbM_TimeBaseStatus is set. */
    if (EthTSyn_Master_IsGlobalTimeBaseStatusBit(timeDomainIdx) == TRUE)
    {
      /* #2000 Change state to TX_SYNC. */
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_SYNC;                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
    break;
  }

  case ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER:
  {
    /* #201 State: Waiting for Sync send -> Check sync tx interval counter. */
    if(syncSendSmPtr->TxIntervalCnt == 0u)
    {
      EthTSyn_Master_SyncSend_TxSync(PortIdx, FALSE);
    } /* END: if(EthTSyn_SyncSendSm(PortIdx).TxIntervalCnt == 0) */
    break;
  }

  case ETHTSYN_S_SYNC_SEND_SM_TX_SYNC:
  {
    /* #202 State: Send Sync -> Transmit sync message. */
    EthTSyn_Master_SyncSend_TxSync(PortIdx, FALSE);
    break;
  }

  case ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC:
  {
    /* #203 State: Send Immediate Sync -> Transmit sync message. */
    EthTSyn_Master_SyncSend_TxSync(PortIdx, TRUE);
    break;
  }

  case ETHTSYN_S_SYNC_SEND_SM_WAIT_SYNC_EGR_TS:
  {
    /* #204 State: Wait for sync egress timestamp -> Check availability of sync egress timestamp. */
    EthTSyn_Master_SyncSend_HndlWaitSyncEgrTsState(PortIdx);
    break;
  }

  case ETHTSYN_S_SYNC_SEND_SM_TX_FUP:
  {
    /* #205 State: Send FollowUp -> Transmit follow up message. */
    /* #2050 Check if Sync cycle already expired. If so, increment sequence id and change state to TX_SYNC. */
    if(syncSendSmPtr->TxIntervalCnt == 0u)
    {
      syncSendSmPtr->SequenceId++;                                                                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_SYNC;                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
    /* #2051 Transmit follow up message otherwise. */
    else
    {
      EthTSyn_Master_SyncSend_TxFup(PortIdx);
    }
    break;
  }

  default:
  {
    /* Nothing to do here. */;
    break;
  }
  } /* END: Switch(SyncSendSm State) */

} /* EthTSyn_Master_SyncSend_ProcSm() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_CpySync
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_CpySync(
                EthTSyn_MasterPortIterType MasterPortIdx,
  ETHTSYN_P2VAR(uint8)                     TxBufPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the common message header. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(TxBufPtr, ETHTSYN_MSG_TYPE_SYNC, EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx));  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
  /* Sync message does not contain any additional field, so no more steps are required. */
} /* EthTSyn_Master_SyncSend_CpySync() */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_IsFupTxReady
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
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_SyncSend_IsFupTxReady(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isTxReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if Port is ready for transmission. */
  if(EthTSyn_IsTxReady(PortIdx) == TRUE)
  {
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    /* #20 If switch timestamping is enabled. */
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      /* #200 Check if Switch Timestamps are ready for processing (if switch timestamping is enabled). */
      if(
          (EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc(masterPortIdx) == TRUE) &&
          (EthTSyn_Master_PortSyncSend_IsSyncSwtIngrTsReadyToProc(masterPortIdx) == TRUE) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
      ) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
      {
        /* #2000 Consider port as ready to transmit the FollowUp message. */
        isTxReady = TRUE;
      }
    }
# else
    /* #30 Otherwise, consider port as ready to transmit the FollowUp message */
    isTxReady = TRUE;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();

  return isTxReady;
} /* EthTSyn_Master_SyncSend_IsFupTxReady() */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_CpyFup
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
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_Master_SyncSend_CpyFup(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
  uint16 actualFollowUpMsgLength = ETHTSYN_MSG_FOLLOW_UP_TX_LENGTH;
  EthTSyn_GlobalTimestampType pot;
  EthTSyn_TimediffType fupCorrValueNs;

  /* ----- Implementation ----------------------------------------------- */
  pot = syncSendSmPtr->FollowUpPreciseOriginTsMgmt.Ts;

  /* #10 Prepare the common message header. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(TxBufPtr, ETHTSYN_MSG_TYPE_FOLLOW_UP, PortIdx);                                   /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  /* #20 Set FollowUp message specific values. */
  /* Set IEEE Tlv values. */ /*lint -e572 */
  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_FUP_INFO_TLV_TYPE_OFS, ETHTSYN_FOLLOW_UP_TLV_TYPE);                           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_FUP_INFO_TLV_LEN_OFS, ETHTSYN_FOLLOW_UP_TLV_LENGTH_FIELD);                    /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint24(TxBufPtr, ETHTSYN_MSG_FUP_INFO_TLV_ORGA_ID_OFS, ETHTSYN_FOLLOW_UP_ORGANISATION_ID);                 /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint24(TxBufPtr, ETHTSYN_MSG_FUP_INFO_TLV_ORGA_SUB_TYPE_OFS, ETHTSYN_FOLLOW_UP_ORGANISATION_SUBTYPE);      /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  /*lint +e572 */

  /* #30 Compute follow up correction field if possible. */
  fupCorrValueNs = EthTSyn_Master_SyncSend_CalcFupCorrVal(masterPortIdx);

# if (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_BOUNDARY)
  /* #40 Add the correction field to the POT and set the correction field to '0' (if BridgeMode is BOUNDARY). */
  if(EthTSyn_Util_TimestampPlusTimediff(&pot, &fupCorrValueNs) == E_OK)                                                /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    fupCorrValueNs = 0;
  }
# endif /* (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_BOUNDARY) */

  /* #50 Provide timestamps for switch time synchronization if required. */
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
  EthTSyn_Master_SyncSend_ProvideSwtTimeSyncTs(masterPortIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

  /* #60 Set the precise origin timestamp and the follow up correction field. */
  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_FUP_POT_SEC_HI_OFS, pot.secondsHi);                                           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint32(TxBufPtr, ETHTSYN_MSG_FUP_POT_SEC_LOW_OFS, pot.seconds);                                            /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint32(TxBufPtr, ETHTSYN_MSG_FUP_POT_NSEC_OFS, pot.nanoseconds);                                           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint48(TxBufPtr, ETHTSYN_MSG_HDR_CORR_FIELD_OFS, (uint64)fupCorrValueNs);                                  /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  /* #70 Append FollowUp Ar TLVs if applicable. */
# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
  actualFollowUpMsgLength += EthTSyn_MasterTx_AppendArFollowUpTlvs(PortIdx, TxBufPtr);                                 /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  /* Correct message length field value. */
  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_HDR_LENGTH_FIELD_OFFSET, actualFollowUpMsgLength);                            /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

  return actualFollowUpMsgLength;
} /* EthTSyn_Master_SyncSend_CpyFup() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_CalcFupCorrVal
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
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimediffType, ETHTSYN_CODE) EthTSyn_Master_SyncSend_CalcFupCorrVal(
  EthTSyn_IntMasterPortIdxType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimediffType fupCorrValueNs;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Switch timestamping is enabled. */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  {
    /* #100 Check if switch and host are considered as one time-aware system. */
#  if (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON)
    {
      /* #1000 Set the FollowUp correction field to '0'. */
      fupCorrValueNs = 0;
      ETHTSYN_DUMMY_STATEMENT(MasterPortIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    }
#  else
    /* #101 Otherwise, use the switch residence time as FollowUp correction field. */
    {
      EthTSyn_TsMgmtStructType syncSwtIngrTsMgmt;
      EthTSyn_TsMgmtStructType syncSwtEgrTsMgmt;

      syncSwtIngrTsMgmt = EthTSyn_Master_PortSyncSend_GetSyncSwtIngrTsMgmt(MasterPortIdx);
      syncSwtEgrTsMgmt = EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt(MasterPortIdx);
      /* #1010 Used default value for the residence time in case calculation is not possible or fails. */
      fupCorrValueNs = (EthTSyn_TimediffType)ETHTSYN_SWT_UPLINK_TO_TX_RESIDENCE_TIME_NS;

      /* #1011 Check if residence time calculation is possible. */
      if(
        (syncSwtIngrTsMgmt.State == ETHTSYN_TS_S_AVAILABLE) &&
        (syncSwtEgrTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
        )
      {
        EthTSyn_TimediffType swtResTime;

        /* #10110 Try to compute the residence time. */
        if(EthTSyn_Util_TimestampMinusTimestamp(&syncSwtEgrTsMgmt.Ts, &syncSwtIngrTsMgmt.Ts, &swtResTime) == E_OK)     /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        {
          /* #101100 Use the residence time in case calculation succeeded and the value is positive. */
          if(swtResTime >= 0)
          {
            fupCorrValueNs = swtResTime;
          }
        }
      }
    }
#  endif /* (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON) */
  }
  /* #20 Otherwise, set the FollowUp correction field to '0'. */
# else
  {
    fupCorrValueNs = 0;
    ETHTSYN_DUMMY_STATEMENT(MasterPortIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  }
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

  return fupCorrValueNs;
} /* EthTSyn_Master_SyncSend_CalcFupCorrVal() */

# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_ProvideSwtTimeSyncTs
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_ProvideSwtTimeSyncTs(
  EthTSyn_IntMasterPortIdxType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if master port is used for synchronization of the switch. */
  if(EthTSyn_IsValidForSwtTimeSyncOfMasterPort(MasterPortIdx) == TRUE)
  {
    EthTSyn_TsMgmtStructType swtIngrTsMgmt;

    /* #20 Check if the switch ingress timestamp is available. */
    swtIngrTsMgmt = EthTSyn_Master_PortSyncSend_GetSyncSwtIngrTsMgmt(MasterPortIdx);
    if(swtIngrTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
    {
      const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
      const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(portIdx);
      const EthTSyn_SwitchIdxOfSwitchPortMgmtType ethIfSwitchIdx =
        EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(MasterPortIdx);

      /* #30 Provide the timestamps required for switch time synchronization to the SwtTimeSync sub-module. */
      EthTSyn_SwtTimeSync_ProvideTimestamps(                                                                           /* SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_SUB_MEMBER_AS_PTR_AND_REF_OF_LOC_VAR */
        ethIfSwitchIdx,
        syncSendSmPtr->SequenceId,
        &syncSendSmPtr->FollowUpPreciseOriginTsMgmt.Ts,
        &swtIngrTsMgmt.Ts);
    }
  }
} /* EthTSyn_Master_SyncSend_ProvideSwtTimeSyncTs() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTlvs
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
/* AR4.3 message format */
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTlvs(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 arTlvHdrLengthField = ETHTSYN_AR_TLV_HEADER_LENGTH_FIELD_VALUE; /* Add length sum of Sub-Tlvs later */
  uint16 totalArTlvLength = 0u;
  uint16 nextSubTlvOfs = ETHTSYN_MSG_FUP_FIRST_AR_SUB_TLV_OFS;
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
  uint8 dataId = EthTSyn_Util_GetFollowUpDataIdListEntry(EthTSyn_GetTimeDomainIdxOfPort(PortIdx),
    IpBase_GetUint16(TxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS));                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
#  else
  uint8 dataId = 0;
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Append the Time Secured Sub-Tlv if applicable. */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
  arTlvHdrLengthField += EthTSyn_MasterTx_AppendArFollowUpTimeTlv(PortIdx, dataId, TxBufPtr, &nextSubTlvOfs);          /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD_AND_LOC_VAR_REF */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

  /* #20 Append the Status (Not) Secured Sub-Tlv if applicable. */
  arTlvHdrLengthField += EthTSyn_MasterTx_AppendArFollowUpStatusTlv(PortIdx, dataId, TxBufPtr, &nextSubTlvOfs);        /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD_AND_LOC_VAR_REF */

  /* #30 Append the User Data (Not) Secured Sub-Tlv if applicable. */
  arTlvHdrLengthField += EthTSyn_MasterTx_AppendArFollowUpUserDataTlv(PortIdx, dataId, TxBufPtr, &nextSubTlvOfs);      /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD_AND_LOC_VAR_REF */

  /* #40 Append the Ofs (Not) Secured Sub-Tlv if applicable. */
#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
  arTlvHdrLengthField += EthTSyn_MasterTx_AppendArFollowUpOfsTlvs(PortIdx, dataId, TxBufPtr, &nextSubTlvOfs);          /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD_AND_LOC_VAR_REF */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

  /* #50 Init ArTlvHdr if any ArTlv was appended. */
  if(arTlvHdrLengthField > ETHTSYN_AR_TLV_HEADER_LENGTH_FIELD_VALUE)
  {
    /* Set Tlv Type */
    IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_FUP_AR_TLV_HDR_TYPE_OFS, ETHTSYN_AR_TLV_TYPE);                              /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    /* Set length field */
    IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_FUP_AR_TLV_HDR_LEN_OFS, arTlvHdrLengthField);                               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    /* Set Organization Id and SubType */
    IpBase_PutUint24(TxBufPtr, ETHTSYN_MSG_FUP_AR_TLV_HDR_ORGA_ID_OFS, ETHTSYN_AR_TLV_ORGANIZATION_ID);                /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
    IpBase_PutUint24(TxBufPtr, ETHTSYN_MSG_FUP_AR_TLV_HDR_ORGA_SUB_TYPE_OFS,
      ETHTSYN_AR_TLV_ORGANIZATION_SUB_TYPE);                                                                           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    /* Compute the total ArTlv length. */
    totalArTlvLength = arTlvHdrLengthField + ETHTSYN_AR_TLV_HEADER_TYPE_LENGTH_FIELDS_LENGTH;
  }

  return totalArTlvLength;
} /* EthTSyn_MasterTx_AppendArFollowUpTlvs() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTimeTlv
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
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTimeTlv(
                EthTSyn_IntPortIdxType  PortIdx,
                uint8                   DataId,
  ETHTSYN_P2VAR(uint8)                  TxBufPtr,
  ETHTSYN_P2VAR(uint16)                 OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_P2VAR(uint8) subTlvStartPtr = &TxBufPtr[(*OffsetPtr)];
  uint16 timeSecuredSubTlvSize = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If Time Tlv is required. */
  if(EthTSyn_IsTimeSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    /* #20 Append Time Secured Tlv. */
    const uint8 crcTimeFlags = EthTSyn_GetCrcTimeFlagsOfMasterPort(masterPortIdx);

    /* #200 Set Type and length */
    IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS, ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED);        /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
    IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS, ETHTSYN_AR_SUB_TLV_TIME_LENGTH_FIELD_VALUE);   /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

    /* #201 Set CRC_Time_Flags */
    IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_FLAGS_OFS, crcTimeFlags);                  /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

    /* #202 Calculate and set CRC_Time_0/1 */
    IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_0_OFS,                                 /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      EthTSyn_Crc_ComputeTime0Crc(DataId, crcTimeFlags, TxBufPtr));                                                    /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */
    IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_1_OFS,                                 /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      EthTSyn_Crc_ComputeTime1Crc(DataId, crcTimeFlags, TxBufPtr));                                                    /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */

    /* #30 Increase offset for further Sub-Tlvs and set return value to size of the TimeSecured Sub-Tlv. */
    (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_TIME_LENGTH;                                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    timeSecuredSubTlvSize = ETHTSYN_AR_SUB_TLV_TIME_LENGTH;
  }

  return timeSecuredSubTlvSize;
} /* EthTSyn_MasterTx_AppendArFollowUpTimeTlv() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpStatusTlv
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
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpStatusTlv(
                EthTSyn_IntPortIdxType PortIdx,
                uint8                  DataId,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr,
  ETHTSYN_P2VAR(uint16)                OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_P2VAR(uint8) subTlvStartPtr = &TxBufPtr[(*OffsetPtr)];
  uint16 statusSubTlvSize = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If Status Tlv is required. */
  if(EthTSyn_IsStatusSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
    StbM_TimeBaseStatusType timeBaseStatusLoc;
    StbM_TimeBaseStatusType ofsTimeBaseStatusLoc;
    uint8 statusSubTlvStatus = 0u;

    /* #20 Get the synchronized time base status. */
    if(StbM_GetTimeBaseStatus(timeBaseId, &timeBaseStatusLoc, &ofsTimeBaseStatusLoc) == E_OK)                          /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      statusSubTlvStatus = EthTSyn_MasterTx_TimeBaseStatusToArSubTlvStatus(timeBaseStatusLoc);
    }

    /* #30 Append the Status Tlv. */
    /* #300 Write length and status. */
    IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS, ETHTSYN_AR_SUB_TLV_STATUS_LENGTH_FIELD_VALUE); /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
    IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_STATUS_OFS, statusSubTlvStatus);                 /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

    /* #301 Write Type Secured/NotSecured and Crc (if applicable) */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
    if(EthTSyn_GetTxCrcSecuredOfMasterPort(masterPortIdx) == ETHTSYN_TX_CRC_SECURED_CRC_SUPPORTED)
    {
      /* Secured */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS, ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED);    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_CRC_OFS,                                       /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
        EthTSyn_Crc_ComputeStatusCrc(DataId, TxBufPtr, (*OffsetPtr)));                                                 /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */
    }
    else
#  else
    ETHTSYN_DUMMY_STATEMENT(DataId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
    {
      /* Not Secured */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS, ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED); /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_CRC_OFS, 0u);                                  /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
    }

    /* #40 Increase offset for further Sub-Tlvs and set return value to size of the Status Sub-Tlv. */
    (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_STATUS_LENGTH;                                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    statusSubTlvSize = ETHTSYN_AR_SUB_TLV_STATUS_LENGTH;
  } /* END: If EthTSyn_IsStatusSubTlvOfMasterPort() */

  return statusSubTlvSize;
} /* EthTSyn_MasterTx_AppendArFollowUpStatusTlv() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpUserDataTlv
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
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpUserDataTlv(
                EthTSyn_IntPortIdxType PortIdx,
                uint8                  DataId,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr,
  ETHTSYN_P2VAR(uint16)                OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_P2VAR(uint8) subTlvStartPtr = &TxBufPtr[(*OffsetPtr)];
  uint16 userDataSubTlvSize = 0u;

  StbM_UserDataType userData;
  StbM_TimeStampType timeStamp;

  /* ----- Implementation ----------------------------------------------- */
  /* Initialize userData */
  userData.userDataLength = 0;
  userData.userByte0 = 0;
  userData.userByte1 = 0;
  userData.userByte2 = 0;

  /* #10 If UserData Sub-Tlv is required. */
  if(EthTSyn_IsUserDataSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);

    /* #20 Get the synchronized time base UserData from StbM via StbM_GetCurrentTime(). */
    if(StbM_GetCurrentTime(timeBaseId, &timeStamp, &userData) != E_OK)                                                 /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      /* #200 In case retrieving the UserData failed set length to '0' to omit UserData Sub-Tlv. */
      userData.userDataLength = 0u;
    }


    /* #30 In case UserData where retrieved successfully and userDataLength is greater '0'. */
    if(userData.userDataLength > 0u)
    {
      /* #300 Set length field of the UserData Sub-Tlv. */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS,
        ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH_FIELD_VALUE);                                                              /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

      /* #301 Write the UserData to the UserData Sub-Tlv. */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_LEN_OFS, userData.userDataLength);       /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_0_OFS, userData.userByte0);         /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_1_OFS, userData.userByte1);         /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_2_OFS, userData.userByte2);         /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */


      /* #302 Write Type Secured/NotSecured to the UserData Sub-Tlv. */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
      if(EthTSyn_GetTxCrcSecuredOfMasterPort(masterPortIdx) == ETHTSYN_TX_CRC_SECURED_CRC_SUPPORTED)
      {
        /* #3020 In case of 'Secured', compute and write the Crc to the UserData Sub-Tlv. */
        IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS,
          ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED);                                                                  /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
        IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_CRC_OFS,                                  /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
          EthTSyn_Crc_ComputeUserDataCrc(DataId, TxBufPtr, (*OffsetPtr)));                                             /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */
      }
      else
#  else
        ETHTSYN_DUMMY_STATEMENT(DataId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
      {
        /* #3021 In case of 'Not Secured', set the Crc-Field (which is 'reserved' in this case) to '0'. */
        IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS,
          ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED);                                                              /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
        IpBase_PutUint8(subTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_CRC_OFS, 0u);                             /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      }

      /* #303 Increase offset for further Sub-Tlvs and set return value to size of the UserData Sub-Tlv. */
      (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH;                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
      userDataSubTlvSize = ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH;
    }
  }

  return userDataSubTlvSize;
} /* EthTSyn_MasterTx_AppendArFollowUpUserDataTlv() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_IpBase */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpOfsTlvs
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
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpOfsTlvs(
                EthTSyn_IntPortIdxType PortIdx,
                uint8                  DataId,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr,
  ETHTSYN_P2VAR(uint16)                OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  uint16 ofsSubTlvsSize = 0u;
  EthTSyn_OffsetTimeDomainIterType offsetTimeDomainIter;
  StbM_UserDataType userData;
  StbM_TimeStampType timeStamp;

  /* ----- Implementation ----------------------------------------------- */
  /* Initialize UserData and Timestamp */
  userData.userDataLength = 0;
  userData.userByte0 = 0;
  userData.userByte1 = 0;
  userData.userByte2 = 0;

  timeStamp.timeBaseStatus = 0;
  timeStamp.secondsHi = 0;
  timeStamp.seconds = 0;
  timeStamp.nanoseconds = 0;

  /* #10 If Ofs Tlv is required. */
  if(EthTSyn_IsOfsSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdxOfPort = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    /* #20 Iterate the offset TimeDomains for the given Port and append an Ofs Sub-Tlv for each of them. */
    for(offsetTimeDomainIter = EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(timeDomainIdxOfPort);
        offsetTimeDomainIter < EthTSyn_GetOffsetTimeDomainEndIdxOfTimeDomain(timeDomainIdxOfPort);
        offsetTimeDomainIter++)
    {
      const uint8 ofsTimeDomainId = EthTSyn_GetIdOfOffsetTimeDomain(offsetTimeDomainIter);
      const StbM_SynchronizedTimeBaseType timeBaseId =
        EthTSyn_GetSynchronizedTimeBaseIdOfOffsetTimeDomain(offsetTimeDomainIter);

      ETHTSYN_P2VAR(uint8) currSubTlvStartPtr = &TxBufPtr[(*OffsetPtr)];

      /* #30 Get the user data via StbM_GetCurrentTime(). */
      if(StbM_GetCurrentTime(timeBaseId, &timeStamp, &userData) != E_OK)                                               /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      {
        /* #300 Failed to retrieve the user data -> set to '0'. */
        userData.userDataLength = 0;
        userData.userByte0 = 0;
        userData.userByte1 = 0;
        userData.userByte2 = 0;
      }

      /* #40 Get the offset via StbM_GetOffset(). */
      if(StbM_GetOffset(timeBaseId, &timeStamp) != E_OK)                                                               /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      {
        /* #400 Failed to retrieve the Offset -> set to '0'. */
        timeStamp.timeBaseStatus = 0;
        timeStamp.secondsHi = 0;
        timeStamp.seconds = 0;
        timeStamp.nanoseconds = 0;
      }

      /* #50 Append Ofs Tlv. */
      /* #500 Write length field. */
      IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS,
        ETHTSYN_AR_SUB_TLV_OFS_LENGTH_FIELD_VALUE);                                                                    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

      /* #501 Write offset time domain id. */
      IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_DOMAIN_NUM_OFS, ofsTimeDomainId);         /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

      /* #502 Write Offset. */
      IpBase_PutUint16(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_SEC_HI_OFS, timeStamp.secondsHi);   /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint32(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_SEC_LOW_OFS, timeStamp.seconds);    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint32(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_NSEC_OFS, timeStamp.nanoseconds);   /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

      /* #503 Write Status. */
      IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_STATUS_OFS,
        EthTSyn_MasterTx_TimeBaseStatusToArSubTlvStatus(timeStamp.timeBaseStatus));                                    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

      /* #504 Write UserData. */
      IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_LEN_OFS, userData.userDataLength);  /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_0_OFS, userData.userByte0);    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_1_OFS, userData.userByte1);    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_2_OFS, userData.userByte2);    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

      /* #505 Write Type Secured/NotSecured and Crc (if applicable). */
#   if (ETHTSYN_CRC_SUPPORT == STD_ON)
      if(EthTSyn_GetTxCrcSecuredOfMasterPort(masterPortIdx) == ETHTSYN_TX_CRC_SECURED_CRC_SUPPORTED)
      {
        /* Secured */
        IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS, ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED); /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
        IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_CRC_OFS,                                    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
          EthTSyn_Crc_ComputeOfsCrc(DataId, TxBufPtr, (*OffsetPtr)));                                                  /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */
      }
      else
#   else
      ETHTSYN_DUMMY_STATEMENT(DataId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#   endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
      {
        /* Not Secured */
        IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS,
          ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED);                                                                    /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
        IpBase_PutUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_CRC_OFS, 0u);                               /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */
      }

      /* #60 Increase offset for further Sub-Tlv and return value by the size of the Ofs Sub-Tlv. */
      (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_OFS_LENGTH;                                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
      ofsSubTlvsSize += ETHTSYN_AR_SUB_TLV_OFS_LENGTH;
    } /* END: Iteration of all Offset TimeDomains for the given Port */
  } /* END: If EthTSyn_IsOfsSubTlvOfMasterPort() */

  return ofsSubTlvsSize;
} /* EthTSyn_MasterTx_AppendArFollowUpOfsTlvs() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_TimeBaseStatusToArSubTlvStatus
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_MasterTx_TimeBaseStatusToArSubTlvStatus(
  StbM_TimeBaseStatusType StbmTimeBaseStatus)
{
  return (uint8)(
    (StbmTimeBaseStatus & ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_MASK) >> ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_SHIFT);
} /* EthTSyn_MasterTx_TimeBaseStatusToArSubTlvStatus() */

/**********************************************************************************************************************
 *  END: MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_TxSync
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_TxSync(
  EthTSyn_IntPortIdxType PortIdx,
  boolean                IsImmediateSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  EthTSyn_SyncSendSmStateEnumType syncSendSmStateTxFailed;
  uint32 txIntervalCntTxSuccess;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Sync message is an immediate sync and prepare the required values accordingly. */
  if(IsImmediateSync == TRUE)
  {
    syncSendSmStateTxFailed = ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC;
    txIntervalCntTxSuccess = EthTSyn_GetCyclicMsgResumeCntOfMasterPort(masterPortIdx);
  }
  else
  {
    syncSendSmStateTxFailed = ETHTSYN_S_SYNC_SEND_SM_TX_SYNC;
    txIntervalCntTxSuccess = EthTSyn_GetSyncSendIntervalOfMasterPort(masterPortIdx);
  }

  /* #20 Verify that port is AsCapable and ready for transmission. */
  if( (EthTSyn_Util_IsAsCapable(PortIdx) == TRUE) && (EthTSyn_IsTxReady(PortIdx) == TRUE) ) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
    StbM_TimeStampType currGlobalTime = { 0u, 0u, 0u, 0u };
    StbM_VirtualLocalTimeType currVlt = { 0u, 0u };
    StbM_UserDataType userData = { 0u, 0u, 0u, 0u };
    Std_ReturnType retValTemp = E_NOT_OK;

    /* #30 Get the current global and virtual local time tuple from StbM via StbM_BusGetCurrentTime() for later
     *     calculation of the precise origin timestamp. */
    if(StbM_BusGetCurrentTime(timeBaseId, &currGlobalTime, &currVlt, &userData) == E_OK)                               /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      /* #40 Store bus get current time info and trigger sync message transmission in case of success. */
      syncSendSmPtr->SyncTxTimeInfo.TimeBaseStatus = currGlobalTime.timeBaseStatus;                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

      syncSendSmPtr->SyncTxTimeInfo.TimeTuple.GlobalTime.secondsHi = currGlobalTime.secondsHi;                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      syncSendSmPtr->SyncTxTimeInfo.TimeTuple.GlobalTime.seconds = currGlobalTime.seconds;                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      syncSendSmPtr->SyncTxTimeInfo.TimeTuple.GlobalTime.nanoseconds = currGlobalTime.nanoseconds;                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

      syncSendSmPtr->SyncTxTimeInfo.TimeTuple.IntVlt = EthTSyn_UtilVlt_VltToIntVlt(&currVlt);                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */ /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */

      syncSendSmPtr->SyncTxTimeInfo.UserData = userData;                                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

      EthTSyn_Master_PortSyncSend_CancelCycle(masterPortIdx);
      retValTemp = EthTSyn_Master_PortSyncSend_TxSync(masterPortIdx, ETHTSYN_MSG_SYNC_LENGTH);
    }

    if(retValTemp == E_OK)
    {
      /* #400 Transmission successful: Recharge tx interval counter and change state of the SyncSendSm to
       *      WAIT_SYNC_EGR_TS. */
      syncSendSmPtr->TxIntervalCnt = txIntervalCntTxSuccess;                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_WAIT_SYNC_EGR_TS;                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
    else
    {
      /* #401 Transmission failed: Retry transmission later by setting the state of the SyncSendSm. */
      syncSendSmPtr->State = syncSendSmStateTxFailed;                                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
  }
} /* EthTSyn_Master_SyncSend_TxSync() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_HndlWaitSyncEgrTsState
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_HndlWaitSyncEgrTsState(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Sync cycle already expired. If so, increment sequence id and change state to TX_SYNC. */
  if(syncSendSmPtr->TxIntervalCnt == 0u)
  {
    syncSendSmPtr->SequenceId++;                                                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_SYNC;                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  }
  /* #20 Otherwise, check if the TxConfirmation for the transmitted sync message was already invoked. */
  else
  {
    if(EthTSyn_Master_PortSyncSend_WasSyncTxConfCalled(masterPortIdx) == TRUE)
    {
# if (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON)
      /* #30 Check if switch egress timestamp is ready for processing
       *     (if host and switch are considered as one time-aware system). */
      if(EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc(masterPortIdx) == TRUE)
# endif /* (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON) */
      {
        EthTSyn_IntVltMgmtType syncEgrIntVltMgmt;
# if (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON)
        EthTSyn_TsMgmtStructType sycnSwtEgrTsMgmt;
# endif /* (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON) */

# if (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON)
        sycnSwtEgrTsMgmt = EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt(masterPortIdx);
        syncEgrIntVltMgmt = EthTSyn_UtilVlt_TsMgmtToIntVltMgmt(&sycnSwtEgrTsMgmt);                                     /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
# else
        syncEgrIntVltMgmt = EthTSyn_Master_PortSyncSend_GetSyncHostEgrIntVltMgmt(masterPortIdx);
# endif /* (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON) */

        /* #40 Try to update and assign the precise origin timestamp. */
        if(EthTSyn_Master_SyncSend_UpdateAndAssignPot(PortIdx, &syncEgrIntVltMgmt) == E_OK)                            /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        {
          /* #400 Change state of the SyncSendSm to TX_FUP in case POT was successfully updated and assigned. */
          ETHTSYN_ENTER_CRITICAL_SECTION_0();
          syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_FUP;                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
          ETHTSYN_LEAVE_CRITICAL_SECTION_0();
        }
        else
        {
          /* #401 Increment the sequence id and change state of the SyncSendSm to WAIT_TX_COUNTER otherwise. */
          ETHTSYN_ENTER_CRITICAL_SECTION_0();
          syncSendSmPtr->SequenceId++;                                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
          syncSendSmPtr->FollowUpPreciseOriginTsMgmt.State = ETHTSYN_TS_S_UNDEFINED;                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
          syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER;                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
          ETHTSYN_LEAVE_CRITICAL_SECTION_0();
        }

      }
    }
  }
} /* EthTSyn_Master_SyncSend_HndlWaitSyncEgrTsState() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_UpdateAndAssignPot
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_SyncSend_UpdateAndAssignPot(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) SyncEgrIntVltMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  const EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if sync egress timestamp is available. */
  if(SyncEgrIntVltMgmtPtr->IntVltValid == TRUE)
  {
    EthTSyn_GlobalTimestampType pot;

    pot = syncSendSmPtr->SyncTxTimeInfo.TimeTuple.GlobalTime;
    /* #100 If calculation of the precise origin timestamp succeeded, assign it to the SyncSendSm and mark it as
     *     AVAILABLE. */
    if(EthTSyn_Master_CalcPot(PortIdx, SyncEgrIntVltMgmtPtr->IntVlt, syncSendSmPtr->SyncTxTimeInfo.TimeTuple.IntVlt,   /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      &pot) == E_OK)
    {
      syncSendSmPtr->FollowUpPreciseOriginTsMgmt.Ts = pot;                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      syncSendSmPtr->FollowUpPreciseOriginTsMgmt.State = ETHTSYN_TS_S_AVAILABLE;                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      retVal = E_OK;
    }
    /* #101 Otherwise, mark the precise origin timestamp in the SyncSendSm as INVALID. */
    else
    {
      syncSendSmPtr->FollowUpPreciseOriginTsMgmt.State = ETHTSYN_TS_S_INVALID;                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
  }
  /* #20 Otherwise, mark the precise origin timestamp of the SyncSendSm as INVALID. */
  else
  {
    syncSendSmPtr->FollowUpPreciseOriginTsMgmt.State = ETHTSYN_TS_S_INVALID;                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
  }

  return retVal;
} /* EthTSyn_Master_SyncSend_UpdateAndAssignPot() */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSend_TxFup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSend_TxFup(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that port is AsCapable and ready to transmit FollowUp message. */
  if((EthTSyn_Util_IsAsCapable(PortIdx) == TRUE) && (EthTSyn_Master_SyncSend_IsFupTxReady(PortIdx) == TRUE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
  {
    const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
    const uint16 maxFupTxLen = EthTSyn_GetFollowUpMsgLengthOfMasterPort(masterPortIdx);

    /* #20 Trigger transmission of follow up message. If Fup transmission was triggered successfully. */
    if(EthTSyn_Master_PortSyncSend_TxFup(masterPortIdx, maxFupTxLen) == E_OK)
    {
      /* #30 Increment the sequence id, reset the POT state and change the state of the SyncSendSm to
       *     WAIT_TX_COUNTER. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0();

      syncSendSmPtr->SequenceId++;                                                                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      syncSendSmPtr->FollowUpPreciseOriginTsMgmt.State = ETHTSYN_TS_S_UNDEFINED;                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER;                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */

      ETHTSYN_LEAVE_CRITICAL_SECTION_0();
    }
  }
} /* EthTSyn_Master_SyncSend_TxFup() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  ANNOUNCE SEND SM
 *********************************************************************************************************************/
# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_Init
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_Init(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType announceSendSmCfgIdx =
    EthTSyn_GetAnnounceSendSmCfgIdxOfMasterPort(MasterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if AnnounceSend state machine is used by the master port. */
  if(announceSendSmCfgIdx < EthTSyn_GetSizeOfAnnounceSendSmCfg())
  {
    /* #20 Set the state of the AnnounceSend state machine to TX_ANNOUNCE in order to transmit the first Announce
     *     message without further start-up delay. */
    EthTSyn_SetStateOfAnnounceSendSm(announceSendSmCfgIdx, ETHTSYN_TX_ANNOUNCE_STATEOFANNOUNCESENDSM);                 /* SBSW_ETHTSYN_CSL02 */

    /* #30 Initialize the announce cycle timer with '0' because it will be recharged after successful transmission
     *     of the first Announce message. */
    EthTSyn_SetAnnounceCycleTimerOfAnnounceSendSm(announceSendSmCfgIdx, 0u);                                           /* SBSW_ETHTSYN_CSL02 */
  }
} /* EthTSyn_Master_AnnounceSend_Init() */

/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_ProcSm
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_ProcSm(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType announceSendSmCfgIdx =
    EthTSyn_GetAnnounceSendSmCfgIdxOfMasterPort(MasterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if AnnounceSend state machine is used by the master port. */
  if(announceSendSmCfgIdx < EthTSyn_GetSizeOfAnnounceSendSmCfg())
  {
    /* #20 Decrement the announce cycle timer and check if it expired this cycle. */
    if(EthTSyn_Master_AnnounceSend_DecTimer(announceSendSmCfgIdx) == TRUE)
    {
      /* #200 Change state of the AnnounceSend state machine to TX_ANNOUNCE */
      EthTSyn_SetStateOfAnnounceSendSm(announceSendSmCfgIdx, ETHTSYN_TX_ANNOUNCE_STATEOFANNOUNCESENDSM);               /* SBSW_ETHTSYN_CSL02 */
    }

    /* #30 Check if state of the AnnounceSend state machine is TX_ANNOUNCE. */
    if(EthTSyn_GetStateOfAnnounceSendSm(announceSendSmCfgIdx) == ETHTSYN_TX_ANNOUNCE_STATEOFANNOUNCESENDSM)
    {
      /* #300 Try to transmit an Announce message. */
      if(EthTSyn_Master_AnnounceSend_TxAnnounce(MasterPortIdx) == E_OK)
      {
        /* #3000 Change state of the AnnounceSend state machine to IDLE and recharge the announce cycle timer in case of
         *       successful Announce message transmission. */
        EthTSyn_SetStateOfAnnounceSendSm(announceSendSmCfgIdx, ETHTSYN_IDLE_STATEOFANNOUNCESENDSM);                    /* SBSW_ETHTSYN_CSL02 */
        EthTSyn_SetAnnounceCycleTimerOfAnnounceSendSm(announceSendSmCfgIdx,                                            /* SBSW_ETHTSYN_CSL02 */
            EthTSyn_GetAnnounceTxCycleOfAnnounceSendSmCfg(announceSendSmCfgIdx));
      }
    }
  }
} /* EthTSyn_Master_AnnounceSend_ProcSm() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_DecTimer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_DecTimer(
  EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType AnnounceSmCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean timerExpiredThisCycle = FALSE;

  /* #10 Check if announce cycle timer is yet not expired. */
  if(EthTSyn_GetAnnounceCycleTimerOfAnnounceSendSm(AnnounceSmCfgIdx) > 0u)
  {
    /* #20 Decrement the announce cycle timer. */
    EthTSyn_DecAnnounceCycleTimerOfAnnounceSendSm(AnnounceSmCfgIdx);                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM */

    /* #30 Check if announce cycle timer is expired now. */
    if(EthTSyn_GetAnnounceCycleTimerOfAnnounceSendSm(AnnounceSmCfgIdx) == 0u)
    {
      timerExpiredThisCycle = TRUE;
    }
  }

  return timerExpiredThisCycle;
} /* EthTSyn_Master_AnnounceSend_DecTimer() */

/**********************************************************************************************************************
 *  EthTSyn_Master_AnnounceSend_TxAnnounce
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_AnnounceSend_TxAnnounce(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
  const EthTSyn_IntCtrlIdxType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(portIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  EthTSyn_EthTxBufferStructType txBuffer;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get a transmission buffer. */
  txBuffer.Length = ETHTSYN_MSG_ANNOUNCE_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(portIdx, &txBuffer) == E_OK)                                                       /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);

    /* #20 Copy announce message to the transmission buffer. */
    ETHTSYN_ENTER_CRITICAL_SECTION_0();

    /* set common header message attributes */
    EthTSyn_UtilTx_PrepareCommonMsgHdr(txBuffer.BufferPtr, ETHTSYN_MSG_TYPE_ANNOUNCE, portIdx);                        /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

    /* set specific message type attributes */
    IpBase_PutUint8(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_GM_PRIO_1_OFS,
      ETHTSYN_ANNOUNCE_PRIORITY_1_NETWORK_INFRASTRUCTURE);                                                             /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
    IpBase_PutUint8(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_GM_CLK_QUAL_CLK_ACCURACY_OFS,
      ETHTSYN_ANNOUNCE_CLOCK_ACCURACY_UNKNOWN);                                                                        /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
    IpBase_PutUint8(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_GM_CLK_QUAL_CLK_CLASS_OFS,
      ETHTSYN_ANNOUNCE_CLOCK_CLASS_UNKNOWN);                                                                           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    IpBase_PutUint16(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_GM_CLK_QUAL_OFS_SCALED_LOG_VAR_OFS,
      ETHTSYN_ANNOUNCE_OFFSET_SCALED_LOG_UNKNOWN);                                                                     /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
    IpBase_PutUint8(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_GM_PRIO_2_OFS, ETHTSYN_ANNOUNCE_PRIORITY_2_DEFAULT);      /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    IpBase_PutUint64(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_GM_IDENTITY_OFS, ctrlStatePtr->ClockIdentity);           /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    IpBase_PutUint8(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_TIME_SRC_OFS,
      ETHTSYN_ANNOUNCE_TIME_SOURCE_INTERNAL_OSCILLATOR);                                                               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    IpBase_PutUint16(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_TYPE_OFS, ETHTSYN_ANNOUNCE_TLV_TYPE);     /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
    IpBase_PutUint16(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_LEN_OFS,
      ETHTSYN_ANNOUNCE_TLV_LENGTH_FIELD);                                                                              /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

    /* set Tlv Clock identity */
    IpBase_PutUint64(txBuffer.BufferPtr, ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_PATH_SEQ_START_OFS,
      ctrlStatePtr->ClockIdentity);                                                                                    /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();

    /* #30 Trigger transmission. */
    retVal = EthTSyn_UtilTx_Transmit(portIdx, txBuffer.BufferIdx, ETHTSYN_MSG_ANNOUNCE_LENGTH);
    if(retVal != E_OK)
    {
      /* #40 Release Ethernet transmission buffer in case of failure. */
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_Master_AnnounceSend_TxAnnounce() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_IpBase */
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  PORT SYNC SEND SM
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_InitInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_InitInternal(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  EthTSyn_TsMgmtStructType tsMgmtInitVal;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  const EthTSyn_IntVltMgmtType intVltMgmtInitVal = { 0u, FALSE };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all variables of the PortSyncSendSm. */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();

  EthTSyn_SetTxBufPtrOfPortSyncSendSm(MasterPortIdx, NULL_PTR);                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetTxBufIdxOfPortSyncSendSm(MasterPortIdx, ETHTSYN_INV_BUF_IDX);                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetSyncHostEgrIntVltMgmtOfPortSyncSendSm(MasterPortIdx, intVltMgmtInitVal);                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetSyncTxConfCalledOfPortSyncSendSm(MasterPortIdx, FALSE);                                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  tsMgmtInitVal.State = ETHTSYN_TS_S_UNDEFINED;
  tsMgmtInitVal.Ts.secondsHi = 0u;
  tsMgmtInitVal.Ts.seconds = 0u;
  tsMgmtInitVal.Ts.nanoseconds = 0u;
  EthTSyn_SetSyncSwtIngrTsMgmtOfPortSyncSendSm(MasterPortIdx, tsMgmtInitVal);                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetSyncSwtEgrTsMgmtOfPortSyncSendSm(MasterPortIdx, tsMgmtInitVal);                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

  /* #20 Set the state of the PortSyncSendSm to PENDING. */
  EthTSyn_SetStateOfPortSyncSendSm(MasterPortIdx, ETHTSYN_PENDING_STATEOFPORTSYNCSENDSM);                              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_Master_PortSyncSend_InitInternal() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CpySync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CpySync(
                EthTSyn_MasterPortIterType MasterPortIdx,
  ETHTSYN_P2VAR(uint8)                     EthTxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  /* #10 If bridge mode is TRANSPARENT and the SiteSyncSyncSm is used, copy the sync message from the SiteSyncSyncSm. */
  if(EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(EthTSyn_GetTimeDomainIdxOfPort(portIdx)) == TRUE)
  {
    EthTSyn_SwtMgmt_SiteSyncSync_CpySync(portIdx, EthTxBufPtr);                                                        /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  }
  else
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
  /* #20 Otherwise, copy the sync message from the SyncSendSm. */
  {
    EthTSyn_Master_SyncSend_CpySync(MasterPortIdx, EthTxBufPtr);                                                       /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  }
} /* EthTSyn_Master_PortSyncSend_CpySync() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CpyFup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CpyFup(
                EthTSyn_MasterPortIterType MasterPortIdx,
                uint16                     MaxFupLen,
  ETHTSYN_P2VAR(uint8)                     EthTxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 actualFupLen;
  const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  /* #10 If bridge mode is TRANSPARENT and the SiteSyncSyncSm is used, copy the FollowUp message from the
   *      SiteSyncSyncSm. */
  if(EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(EthTSyn_GetTimeDomainIdxOfPort(portIdx)) == TRUE)
  {
    EthTSyn_SwtMgmt_SiteSyncSync_CpyFup(portIdx, EthTxBufPtr, MaxFupLen);                                              /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
    actualFupLen = MaxFupLen;
  }
  else
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
  /* #20 Otherwise, copy the FollowUp message from the SyncSendSm. */
  {
    actualFupLen = EthTSyn_Master_SyncSend_CpyFup(portIdx, EthTxBufPtr);                                               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  }

# if (ETHTSYN_SITESYNCSYNCSM == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(MaxFupLen); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_OFF) */

  return actualFupLen;
} /* EthTSyn_Master_PortSyncSend_CpyFup() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_Transmit
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_Transmit(
                  EthTSyn_MasterPortIterType       MasterPortIdx,
                  uint16                           MsgTxLen,
                  EthTSyn_EnableTimestampFlagsType EnableTsFlags,
  ETHTSYN_P2CONST(EthTSyn_EthTxBufferStructType)   TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(portIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  /* #10 Get the switch port information if required (if switch management is enabled). */
  if(EthTSyn_UtilTx_GetSwtMgmtInfo(portIdx, &mgmtInfo) == E_OK)                                                        /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  {
    mgmtInfoPtr = &mgmtInfo;
  }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  /* #20 Prepare the transmission. If preparation of transmission succeeded. */
  if(EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, TxBufPtr->BufferIdx, EnableTsFlags, mgmtInfoPtr) == E_OK)        /* SBSW_ETHTSYN_LOCAL_PTR_VAR */
  {
    /* #200 Store the Ethernet TxBuffer information for later processing of the TxConfirmation. */
    EthTSyn_SetTxBufIdxOfPortSyncSendSm(MasterPortIdx, TxBufPtr->BufferIdx);                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    EthTSyn_SetTxBufPtrOfPortSyncSendSm(MasterPortIdx, TxBufPtr->BufferPtr);                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

    /* #201 Trigger the Sync message transmission. */
    retVal = EthTSyn_UtilTx_Transmit(portIdx, TxBufPtr->BufferIdx, MsgTxLen);
  }

  /* #30 Release the Ethernet TxBuffer in case any error occurred. */
  if(retVal != E_OK)
  {
    EthTSyn_SetTxBufIdxOfPortSyncSendSm(MasterPortIdx, ETHTSYN_INV_BUF_IDX);                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    EthTSyn_SetTxBufPtrOfPortSyncSendSm(MasterPortIdx, NULL_PTR);                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, TxBufPtr->BufferIdx);
  }

  return retVal;
} /* EthTSyn_Master_PortSyncSend_Transmit() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_Master_Init
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
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Master_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_MasterPortIterType masterPortIter;
  EthTSyn_TimeBaseUpdateCounterIterType timeBaseUpdateCounterIter;
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset time base updated counter handler. */
  for(timeBaseUpdateCounterIter = 0;
      timeBaseUpdateCounterIter < EthTSyn_GetSizeOfTimeBaseUpdateCounter();
      timeBaseUpdateCounterIter++)
  {
    EthTSyn_SetValueOfTimeBaseUpdateCounter(timeBaseUpdateCounterIter, 0);                                             /* SBSW_ETHTSYN_CSL01 */
    EthTSyn_SetValidOfTimeBaseUpdateCounter(timeBaseUpdateCounterIter, FALSE);                                         /* SBSW_ETHTSYN_CSL01 */
  }

  /* #20 Iterate all master ports. */
  for(masterPortIter = 0;
      masterPortIter < EthTSyn_GetSizeOfMasterPort();
      masterPortIter++)
  {
    /* #200 Initialize the current master port. */
    EthTSyn_Master_InitPortInternal(masterPortIter);
    /* #201 Verify the generated FollowUp Tx length for current master port. */
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    if(EthTSyn_Master_IsFollowUpTxLengthValid(masterPortIter) == FALSE)
    {
      /* #2010 In case of invalid FollowUp Tx length, set errorId to ETHTSYN_E_FUP_TX_LENGTH and stop iteration. */
      errorId = ETHTSYN_E_FUP_TX_LENGTH;
      break;
    }
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  }

  return errorId;
} /* EthTSyn_Master_Init() */
/**********************************************************************************************************************
 *  EthTSyn_Master_InitPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPort(
  EthTSyn_IntMasterPortIdxType MasterPortIdx)
{
  EthTSyn_Master_InitPortInternal(MasterPortIdx);
} /* EthTSyn_Master_InitPort() */

/**********************************************************************************************************************
 *  EthTSyn_Master_CalcPot
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
  */
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_CalcPot(
                EthTSyn_IntPortIdxType        PortIdx,
                EthTSyn_IntVltType            SyncEgressIntVlt,
                EthTSyn_IntVltType            SyncTxIntVlt,
  ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType)  PotPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_EthTSyn_2981_RedundantInit */
  EthTSyn_UTimediffType timeSinceSyncTx = 0u; /* PRQA S 2981 */ /* MD_EthTSyn_2981_RedundantInit */
  EthTSyn_UTimediffType syncTxCorrTime = 0u; /* PRQA S 2981 */ /* MD_EthTSyn_2981_RedundantInit */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  boolean potCalcPossible;
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 If HW-Timestamping is used and StbM uses a different time-source than the underlying EthCtrl of the
   *     EthTSyn-Port. */
  if (EthTSyn_IsStbMTimeSrcEqualOfPort(PortIdx) == FALSE)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    const uint8 ethIfCtrlIdx = (uint8)EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
    Eth_TimeStampType currEthTime = { 0u,0u,0u };
    Eth_TimeStampQualType currEthTimeQual = ETH_VALID;
    StbM_VirtualLocalTimeType currVlt = { 0u,0u };
    Std_ReturnType ethGetCurrTimeRetVal;
    Std_ReturnType stbmGetCurrVltRetVal;

    /* #100 Get the current time from Ethernet via EthIf_GetCurrentTime() and StbM via
     *      StbM_GetCurrentVirtualLocalTime(). */
     /* Critical section is used to minimize the delay between retrieving the current time from Eth and StbM. */
    ETHTSYN_ENTER_CRITICAL_SECTION_GET_TS();
    ethGetCurrTimeRetVal = EthIf_GetCurrentTime(ethIfCtrlIdx, &currEthTimeQual, &currEthTime);                         /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    stbmGetCurrVltRetVal = StbM_GetCurrentVirtualLocalTime(timeBaseId, &currVlt);                                      /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    ETHTSYN_LEAVE_CRITICAL_SECTION_GET_TS();

    /* #101 If both times where retrieved successfully and are valid.  */
    if (
      (ethGetCurrTimeRetVal == E_OK) &&
      (stbmGetCurrVltRetVal == E_OK) &&
      (currEthTimeQual == ETH_VALID)
      )
    {
      /* #1010 Transform both timestamp into an internal virtual local time. */
      EthTSyn_IntVltType currIntVlt = EthTSyn_UtilVlt_VltToIntVlt(&currVlt);                                           /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
      EthTSyn_IntVltType currEthVlt = EthTSyn_UtilVlt_TsToIntVlt(&currEthTime);                                        /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */

      /* #1011 Calculate the time since getting the global time for sync message transmission and now.
       *       This is considered to be the time since sync message transmission. */
      timeSinceSyncTx = (currIntVlt - SyncTxIntVlt);

      /* #1012 Calculate the time since actual sync message transmission and now.
       *       This is considered as time correction. */
      syncTxCorrTime = (currEthVlt - SyncEgressIntVlt);

      /* #1013 Mark precise origin timestamp calculation as possible. */
      potCalcPossible = TRUE;
    }
    /* #102 Otherwise, mark precise origin timestamp calculation as not possible. */
    else
    {
      potCalcPossible = FALSE;
    }
  }
  else
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
  /* #20 Otherwise. */
  {
    /* #200 Calculate the time difference since getting the global time for sync message transmission and actual sync
     *      message transmission. */
    timeSinceSyncTx = (SyncEgressIntVlt - SyncTxIntVlt);

    /* #201 No time correction required. Set it to zero and mark precise origin timestamp calculation as possible. */
    syncTxCorrTime = 0;
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
    potCalcPossible = TRUE;
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
  }

  /* #30 If calculation of the precise origin timestamp is possible, calculate the precise origin timestamp. */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  if (potCalcPossible == TRUE) /* PRQA S 2991, 2995 */ /* MD_EthTSyn_2995 */
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
  {
    EthTSyn_TimediffType signedTimeSinceSyncTx = (EthTSyn_TimediffType)timeSinceSyncTx;
    EthTSyn_TimediffType signedSyncCorrTime = ((EthTSyn_TimediffType)syncTxCorrTime) * (-1);
    /* #300 Calculate the precise origin timestamp by adding the time since sync message transmission and the
     *      calculated time correction to the global time retrieved from the StbM for sync message transmission. */
    retVal = EthTSyn_Util_TimestampPlusTimediff(PotPtr, &signedTimeSinceSyncTx);                                       /* SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF */
    retVal |= EthTSyn_Util_TimestampPlusTimediff(PotPtr, &signedSyncCorrTime);                                         /* SBSW_ETHTSYN_INT_FUNC_PARAM_PTR_FWD_AND_LOC_VAR_REF */
  }

# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(PortIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

  return retVal;
} /* EthTSyn_Master_CalcPot */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_HandleCyclicTasks
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
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_HandleCyclicTasks(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  /* #10 Check that TimeDomain is not using the SiteSyncSyncSm. */
  if(EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == FALSE)
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
  {
    EthTSyn_MasterPortIterType masterPortIter;
    /* #20 Check if immediate time sync is required. */
    const boolean triggerImmediateTimeSync = EthTSyn_Master_IsImmediateTimeSyncRequired(TimeDomainIdx);

    /* ----- Implementation ----------------------------------------------- */
    /* #30 Iterate all master ports. */
    for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter++)
    {
      const EthTSyn_IntPortIdxType portIdx = (EthTSyn_IntPortIdxType)EthTSyn_GetPortIdxOfMasterPort(masterPortIter);

      /* #40 Check if Port is Tx ready */
      if(EthTSyn_IsTxReady(portIdx) == TRUE)
      {
        EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIter);

        /* #50 Handle timer/counter of the Port */
        ETHTSYN_ENTER_CRITICAL_SECTION_0();
        if(syncSendSmPtr->TxIntervalCnt > 0u)
        {
          syncSendSmPtr->TxIntervalCnt--;                                                                              /* SBSW_ETHTSYN_CSL02 */
        }

        /* #60 Handle immediate time sync. */
        if((EthTSyn_IsImmediateTimeSyncOfMasterPort(masterPortIter) == TRUE) && (triggerImmediateTimeSync == TRUE))
        {
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
          /* Only trigger immediate time sync for switch ports. */
          if(EthTSyn_Util_IsSwitchPort(portIdx) == TRUE)
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
          {
            syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC;                                           /* SBSW_ETHTSYN_CSL02 */
          }
        }
        ETHTSYN_LEAVE_CRITICAL_SECTION_0();

        /* #70 Process SyncSend state-machine */
        EthTSyn_Master_SyncSend_ProcSm(portIdx);

        /* #80 Process the AnnounceSend state machine if applicable. */
# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
        EthTSyn_Master_AnnounceSend_ProcSm(masterPortIter);
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */
      }
    } /* END: Iteration of MasterPorts */
  }

} /* EthTSyn_Master_HandleCyclicTasks() */ /* PRQA S 6050, 6080 */ /* MD_EthTSyn_6050_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  PORT SYNC SEND SM
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_Init(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the PortSyncSendSm. */
  EthTSyn_Master_PortSyncSend_InitInternal(MasterPortIdx);
} /* EthTSyn_Master_PortSyncSend_Init() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_TxSync
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_TxSync(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint16                     MaxSyncLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if current state of the PortSyncSendSm is PENDING. */
  if(EthTSyn_GetStateOfPortSyncSendSm(MasterPortIdx) == ETHTSYN_PENDING_STATEOFPORTSYNCSENDSM)
  {
    const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
    EthTSyn_EthTxBufferStructType txBuffer;

    /* #20 Change state of the PortSyncSendSm to TX_SYNC and reset Sync TxConfirmation called flag. */
    EthTSyn_SetStateOfPortSyncSendSm(MasterPortIdx, ETHTSYN_TX_SYNC_STATEOFPORTSYNCSENDSM);                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    EthTSyn_SetSyncTxConfCalledOfPortSyncSendSm(MasterPortIdx, FALSE);                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

    /* #30 Get an Ethernet TxBuffer for the sync message. */
    txBuffer.Length = MaxSyncLen;
    if(EthTSyn_UtilTx_ProvideTxBuffer(portIdx, &txBuffer) == E_OK)                                                     /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      /* #40 Copy the Sync message to the Ethernet TxBuffer. */
      EthTSyn_Master_PortSyncSend_CpySync(MasterPortIdx, txBuffer.BufferPtr);                                          /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
      /* #50 Start a new master sync cycle in the time validation unit (if master time validation is enabled). */
      EthTSyn_TimeValid_MasterStartCycle(portIdx,
        IpBase_GetUint16(txBuffer.BufferPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS));                                        /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

      /* #60 Change the state of the PortSyncSendSm to WAIT_SYNC_TX_CONF. */
      EthTSyn_SetStateOfPortSyncSendSm(MasterPortIdx, ETHTSYN_WAIT_SYNC_TX_CONF_STATEOFPORTSYNCSENDSM);                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

      /* #70 Trigger the Sync message transmission. */
      retVal = EthTSyn_Master_PortSyncSend_Transmit(                                                                   /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        MasterPortIdx, MaxSyncLen, ETHTSYN_ENABLE_TS_HW_AND_SWT_TS, &txBuffer);
    }

    /* #80 Reset PortSyncSendSm in case any error occurred during Sync transmission. */
    if(retVal != E_OK)
    {
      EthTSyn_Master_PortSyncSend_InitInternal(MasterPortIdx);
    }
  }

  return retVal;
} /* EthTSyn_Master_PortSyncSend_TxSync() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_IsSyncSwtIngrTsReadyToProc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_IsSyncSwtIngrTsReadyToProc(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return TRUE if switch ingress timestamp of the transmitted sync message is ready for processing. */
  /* #20 Otherwise, return FALSE. */
  return EthTSyn_Util_IsTsReadyToProc(EthTSyn_GetSyncSwtIngrTsMgmtOfPortSyncSendSm(MasterPortIdx).State);
} /* EthTSyn_Master_PortSyncSend_IsSyncSwtIngrTsReadyToProc() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return TRUE if switch egress timestamp of the transmitted sync message is ready for processing. */
  /* #20 Otherwise, return FALSE. */
  return EthTSyn_Util_IsTsReadyToProc(EthTSyn_GetSyncSwtEgrTsMgmtOfPortSyncSendSm(MasterPortIdx).State);
} /* EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc() */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_GetSyncHostEgrIntVltMgmt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_GetSyncHostEgrIntVltMgmt(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return the egress timestamp of the transmitted sync message as internal virtual local time and its validity
   *     info. */
  return EthTSyn_GetSyncHostEgrIntVltMgmtOfPortSyncSendSm(MasterPortIdx);
} /* EthTSyn_Master_PortSyncSend_GetSyncHostEgrIntVltMgmt() */

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_GetSyncSwtIngrTsMgmt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_GetSyncSwtIngrTsMgmt(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return the switch ingress timestamp of the transmitted sync message and its state. */
  return EthTSyn_GetSyncSwtIngrTsMgmtOfPortSyncSendSm(MasterPortIdx);
} /* EthTSyn_Master_PortSyncSend_GetSyncSwtIngrTsMgmt() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return the switch egress timestamp of the transmitted sync message and its state. */
  return EthTSyn_GetSyncSwtEgrTsMgmtOfPortSyncSendSm(MasterPortIdx);
} /* EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt() */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_ProvideSyncHostEgrIntVlt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_ProvideSyncHostEgrIntVlt(
                  EthTSyn_MasterPortIterType MasterPortIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType)    EgrTsMgmtPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store the provided sync egress timestamp as internal virtual local time and its validity info in the
   *     PortSyncSendSm for later processing. */
  EthTSyn_SetSyncHostEgrIntVltMgmtOfPortSyncSendSm(MasterPortIdx, (*EgrTsMgmtPtr));                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
} /* EthTSyn_Master_PortSyncSend_ProvideSyncHostEgrIntVlt() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_WasSyncTxConfCalled
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_WasSyncTxConfCalled(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return TRUE if the TxConfirmation for the transmitted sync message was called. */
  /* #20 Otherwise, return FALSE. */
  return EthTSyn_IsSyncTxConfCalledOfPortSyncSendSm(MasterPortIdx);
} /* EthTSyn_Master_PortSyncSend_WasSyncTxConfCalled() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_TxFup
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_TxFup(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint16                     MaxFupLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if current state of the PortSyncSendSm is WAIT_TX_FUP. */
  if(EthTSyn_GetStateOfPortSyncSendSm(MasterPortIdx) == ETHTSYN_WAIT_TX_FUP_STATEOFPORTSYNCSENDSM)
  {
    const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
    EthTSyn_EthTxBufferStructType txBuffer;

    /* #20 Change state of PortSyncSendSm to TX_FUP. */
    EthTSyn_SetStateOfPortSyncSendSm(MasterPortIdx, ETHTSYN_TX_FUP_STATEOFPORTSYNCSENDSM);                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

    /* #30 Get an Ethernet TxBuffer for the FollowUp message. */
    txBuffer.Length = MaxFupLen;
    if(EthTSyn_UtilTx_ProvideTxBuffer(portIdx, &txBuffer) == E_OK)                                                     /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    {
      uint16 actualFupLen;

      /* #40 Copy the FollowUp message to the Ethernet TxBuffer. */
      actualFupLen = EthTSyn_Master_PortSyncSend_CpyFup(MasterPortIdx, MaxFupLen, txBuffer.BufferPtr);                 /* SBSW_ETHTSYN_ETH_BUFFER_LOCAL_PTR_VAR */

# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
        /* #50 Provide time validation data (i.e. Sync egress timestamp, POT and Fup correction field) to the
         *     time validation unit (if master time validation is enabled). */
        {
          EthTSyn_GlobalTimestampType fupPot;
          sint64 fupCorrField;
          EthTSyn_IntVltType syncEgrIntVlt;

#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
          syncEgrIntVlt = EthTSyn_UtilVlt_TsToIntVlt(                                                                  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_AS_PTR */
            &EthTSyn_GetAddrSyncSwtEgrTsMgmtOfPortSyncSendSm(MasterPortIdx)->Ts);
#  else
          syncEgrIntVlt = EthTSyn_GetSyncHostEgrIntVltMgmtOfPortSyncSendSm(MasterPortIdx).IntVlt;
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

          fupPot.secondsHi = IpBase_GetUint16(txBuffer.BufferPtr, ETHTSYN_MSG_FUP_POT_SEC_HI_OFS);                     /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */
          fupPot.seconds = IpBase_GetUint32(txBuffer.BufferPtr, ETHTSYN_MSG_FUP_POT_SEC_LOW_OFS);                      /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */
          fupPot.nanoseconds = IpBase_GetUint32(txBuffer.BufferPtr, ETHTSYN_MSG_FUP_POT_NSEC_OFS);                     /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */

          fupCorrField = (sint64)IpBase_GetUint48(txBuffer.BufferPtr, ETHTSYN_MSG_HDR_CORR_FIELD_OFS);                 /* SBSW_ETHTSYN_ETH_TX_BUFFER_READ_FWD */

          EthTSyn_TimeValid_MasterProvideSyncEgressTs(portIdx, syncEgrIntVlt);
          EthTSyn_TimeValid_MasterProvideFupData(portIdx, &fupPot, fupCorrField);                                      /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
        }
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

      /* #60 Change the state of the PortSyncSendSm to WAIT_FUP_TX_CONF. */
      EthTSyn_SetStateOfPortSyncSendSm(MasterPortIdx, ETHTSYN_WAIT_FUP_TX_CONF_STATEOFPORTSYNCSENDSM);                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

      /* #70 Trigger the FollowUp message transmission. */
      retVal = EthTSyn_Master_PortSyncSend_Transmit(MasterPortIdx, actualFupLen, ETHTSYN_ENABLE_TS_NONE, &txBuffer);   /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
    }

    /* #80 If any error occurred during Fup transmission. */
    if(retVal != E_OK)
    {
      /* #700 Change the state of the PortSyncSendSm to WAIT_TX_FUP. */
      EthTSyn_SetStateOfPortSyncSendSm(MasterPortIdx, ETHTSYN_WAIT_TX_FUP_STATEOFPORTSYNCSENDSM);                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
    }
  }

  return retVal;
} /* EthTSyn_Master_PortSyncSend_TxFup() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_InlineFunc */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CancelCycle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CancelCycle(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the PortSyncSendSm. */
  EthTSyn_Master_PortSyncSend_InitInternal(MasterPortIdx);
} /* EthTSyn_Master_PortSyncSend_CancelCycle() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_CheckForMatchingTxConf
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
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_CheckForMatchingTxConf(
                EthTSyn_MasterPortIterType MasterPortIdx,
                uint8                      BufIdx,
  ETHTSYN_P2VAR(uint8)                     MsgTypePtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check If PortSyncSendSm is in state WAIT_SYNC_TX_CONF. */
  if(EthTSyn_GetStateOfPortSyncSendSm(MasterPortIdx) == ETHTSYN_WAIT_SYNC_TX_CONF_STATEOFPORTSYNCSENDSM)
  {
    /* #100 Check if TxBuffer index is matching the one of the TxConfirmation. */
    if(EthTSyn_GetTxBufIdxOfPortSyncSendSm(MasterPortIdx) == BufIdx)
    {
      /* #1000 Change MsgType to SYNC. */
      (*MsgTypePtr) = ETHTSYN_MSG_TYPE_SYNC;                                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    }
  }
  /* #20 Otherwise, if PortSyncSendSm is in state WAIT_FUP_TX_CONF. */
  else if(EthTSyn_GetStateOfPortSyncSendSm(MasterPortIdx) == ETHTSYN_WAIT_FUP_TX_CONF_STATEOFPORTSYNCSENDSM)
  {
    /* #200 Check if TxBuffer index is matching the one of the TxConfirmation. */
    if(EthTSyn_GetTxBufIdxOfPortSyncSendSm(MasterPortIdx) == BufIdx)
    {
      /* #2000 Change MsgType to FUP. */
      (*MsgTypePtr) = ETHTSYN_MSG_TYPE_FOLLOW_UP;                                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    }
  }
  /* #30 Otherwise. */
  else
  {
    /* #300 Do nothing. */
  }
} /* EthTSyn_Master_PortSyncSend_CheckForMatchingTxConf() */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_ProcSyncTxConf
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_ProcSyncTxConf(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint8                      EthIfCtrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 Setup the switch management TxMgmtObj (if switch timestamping is enabled). */
  EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(EthIfCtrlIdx,                                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_AS_PTR */
    EthTSyn_GetTxBufIdxOfPortSyncSendSm(MasterPortIdx),
    EthTSyn_GetAddrSyncSwtIngrTsMgmtOfPortSyncSendSm(MasterPortIdx),
    EthTSyn_GetAddrSyncSwtEgrTsMgmtOfPortSyncSendSm(MasterPortIdx));
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

  /* #20 Invoke the sync sent callback, if it is configured for the master port. */
  if(EthTSyn_GetSyncSentCbkPtrOfMasterPort(MasterPortIdx) != NULL_PTR)
  {
    EthTSyn_GetSyncSentCbkPtrOfMasterPort(MasterPortIdx)(                                                              /* SBSW_ETHTSYN_SYNC_FUP_SENT_CBK */
      EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx),
      EthTSyn_GetTxBufPtrOfPortSyncSendSm(MasterPortIdx));
  }

  ETHTSYN_ENTER_CRITICAL_SECTION_0();

  /* #30 Invalidate the TxBuffer index and pointer of Sync message. */
  EthTSyn_SetTxBufIdxOfPortSyncSendSm(MasterPortIdx, ETHTSYN_INV_BUF_IDX);                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetTxBufPtrOfPortSyncSendSm(MasterPortIdx, NULL_PTR);                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

  /* #40 Change state of the PortSyncSendSm to WAIT_TX_FUP and set Sync TxConfirmation called flag. */
  EthTSyn_SetStateOfPortSyncSendSm(MasterPortIdx, ETHTSYN_WAIT_TX_FUP_STATEOFPORTSYNCSENDSM);                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */
  EthTSyn_SetSyncTxConfCalledOfPortSyncSendSm(MasterPortIdx, TRUE);                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_02 */

  ETHTSYN_LEAVE_CRITICAL_SECTION_0();

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
} /* EthTSyn_Master_PortSyncSend_ProcSyncTxConf() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_PortSyncSend_ProcFupTxConf
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_PortSyncSend_ProcFupTxConf(EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Invoke the FollowUp sent callback, if it is configured for the master port. */
  if(EthTSyn_GetFollowUpSentCbkPtrOfMasterPort(MasterPortIdx) != NULL_PTR)
  {
    EthTSyn_GetFollowUpSentCbkPtrOfMasterPort(MasterPortIdx)(                                                          /* SBSW_ETHTSYN_SYNC_FUP_SENT_CBK */
      EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx),
      EthTSyn_GetTxBufPtrOfPortSyncSendSm(MasterPortIdx));
  }

# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
  /* #20 Inform the time validation unit about the successful FollowUp message transmission
   *     (if master time validation is enabled). */
  EthTSyn_TimeValid_MasterFollowUpSent(EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx));
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

  /* #30 Finalize the Sync cycle by re-initializing the PortSyncSendSm. */
  EthTSyn_Master_PortSyncSend_InitInternal(MasterPortIdx);
} /* EthTSyn_Master_PortSyncSend_ProcFupTxConf() */


# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Master_Int.c
 *********************************************************************************************************************/
