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
/*!        \file  EthTSyn_Util_Int.h
 *        \brief  EthTSyn Util internal header file
 *      \details  Contains internal definitions and declarations used by EthTSyn
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

#if !defined(ETHTSYN_UTIL_INT_H)
# define ETHTSYN_UTIL_INT_H

/* PRQA S 3219 EOF */ /* MD_MSR_Unreachable */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "IpBase.h"
# include "EthTSyn_GeneratedCfgAccess.h"
# include "EthTSyn_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETHTSYN_INV_BUF_IDX                                          (0xFFu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# define ETHTSYN_ENTER_CRITICAL_SECTION_0()                      SchM_Enter_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0()
# define ETHTSYN_LEAVE_CRITICAL_SECTION_0()                      SchM_Exit_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0()

# define ETHTSYN_ENTER_CRITICAL_SECTION_GET_TS()                 SchM_Enter_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_GET_TS()
# define ETHTSYN_LEAVE_CRITICAL_SECTION_GET_TS()                 SchM_Exit_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_GET_TS()

# define ETHTSYN_ENTER_CRITICAL_SECTION_TIME_VALID()             SchM_Enter_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_TIME_VALID()
# define ETHTSYN_LEAVE_CRITICAL_SECTION_TIME_VALID()             SchM_Exit_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_TIME_VALID()

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampPlusTimediff
 *********************************************************************************************************************/
/*! \brief          Adds the passed Timediff to the provided Timestamp.
 *  \details        -
 *  \param[in,out]  DestTimestampPtr   In:  The Timestamp the passed Timediff should be added too
 *                                     Out: The provided Timestamps with the added Timediff
 *  \param[in]      TimediffPtr        Pointer to where the time difference is stored
 *  \return         E_OK - Sum of added timestamps is valid
 *  \return         E_NOT_OK - Sum of added timestamps is invalid
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different Timestamps
 *  \note           DestTimestampPtr is only modified for return value of E_OK.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampPlusTimediff(
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) DestTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)        TimediffPtr);

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampMinusTimestamp
 *********************************************************************************************************************/
/*! \brief         Calculates the time difference between two passed Timestamps.
 *  \details       -
 *  \param[in]     Timestamp1Ptr          Pointer to first timestamp of the first timestamp
 *  \param[in]     Timestamp2Ptr          Pointer to second timestamp of the second timestamp
 *  \param[out]    TimediffPtr            Pointer to time difference between Timestamp1 and Timestamp2
 *  \return        E_OK - Timediff is valid
 *  \return        E_NOT_OK - Timediff is invalid
 *  \pre           -
 *  \context       TAKS|ISR2
 *  \reentrant     TRUE
 *  \note          Timediff = Timestamp1 - Timestamp2
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampMinusTimestamp(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp1Ptr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp2Ptr,
    ETHTSYN_P2VAR(EthTSyn_TimediffType)        TimediffPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_TsToIntVlt
 *********************************************************************************************************************/
/*! \brief         Converts a global time stamp into a virtual local time (internal representation)
 *  \details       -
 *  \param[in]     TsPtr  The global timestamp
 *  \return        The passed global timestamp as virtual local time in internal representation
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \note          It is assumed that the passed timestamp does not exceed the value range of the
 *                 internal virtual local time (2^64 - 1 nanoseconds)
 *********************************************************************************************************************/
FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_UtilVlt_TsToIntVlt(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) TsPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_IntVltToTs
 *********************************************************************************************************************/
/*! \brief         Converts a virtual local time (internal representation) into a global time stamp
 *  \details       -
 *  \param[in]     IntVlt  The virtual local time in internal representation
 *  \return        The passed internal virtual local time converted to a global timestamp
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_UtilVlt_IntVltToTs(
  EthTSyn_IntVltType IntVlt);

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_VltToIntVlt
 *********************************************************************************************************************/
/*! \brief         Converts a virtual local time into a virtual local time in internal representation
 *  \details       -
 *  \param[in]     VltPtr  The virtual local time
 *  \return        The passed virtual local time in internal representation
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_UtilVlt_VltToIntVlt(
  ETHTSYN_P2CONST(StbM_VirtualLocalTimeType) VltPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_IntVltToVlt
 *********************************************************************************************************************/
/*! \brief         Converts a virtual local time in internal representation into a virtual local time
 *  \details       -
 *  \param[in]     IntVlt  The virtual local time in internal representation
 *  \return        The passed internal virtual local time as virtual local time
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(StbM_VirtualLocalTimeType, ETHTSYN_CODE) EthTSyn_UtilVlt_IntVltToVlt(
  EthTSyn_IntVltType IntVlt);

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_IntVltMgmtToTsMgmt
 *********************************************************************************************************************/
/*! \brief         Converts a virtual local time in internal representation with validity information into a
 *                 global time stamp with availability information
 *  \details       -
 *  \param[in]     IntVltMgmtPtr  The virtual local time in internal representation with validity information
 *  \return        The passed internal virtual local time with validity information as global time stamp with
 *                  availability information
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IntVltMgmtPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_TsMgmtToIntVltMgmt
 *********************************************************************************************************************/
/*! \brief         Converts a global time stamp with availability information into a virtual local time in internal
 *                 representation with validity information
 *  \details       -
 *  \param[in]     TsMgmtPtr  The global time stamp with availability information
 *  \return        The converted internal virtual local time with validity information
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_UtilVlt_TsMgmtToIntVltMgmt(
  ETHTSYN_P2CONST(EthTSyn_TsMgmtStructType) TsMgmtPtr);

/**********************************************************************************************************************
 *  RX UTILS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageGeneral
 *********************************************************************************************************************/
/*! \brief      Performs general message checks.
 *  \details    Checks the Frame length and Message length carried in the header for plausibility and verifies the
 *              Protocol version.
 *  \param[in]  RxBufPtr         Pointer to the Ethernet reception buffer of the received message to be checked
 *  \param[in]  LenByte          Length of the message in Byte
 *  \return     ETHTSYN_E_NO_ERROR - Message checks passed. No error occurred.
 *  \return     other value - Message checks failed. Corresponding error id is returned.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageGeneral(
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint16  LenByte);

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageTypeAndLength
 *********************************************************************************************************************/
/*! \brief      Checks if the frame length and the message length of the common message header matches the message type.
 *  \details    Checks if the message type is valid and if the frame length and message length of the common header
 *              matches the message type.
 *  \param[in]  RxBufPtr        Pointer to the Ethernet reception buffer of the received message to be checked
 *  \param[in]  LenByte         Length of the message in Byte
 *  \return     ETHTSYN_E_NO_ERROR - Message checks passed. No error occurred.
 *  \return     other value - Message checks failed. Corresponding error id is returned.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageTypeAndLength(
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint16  LenByte);

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_QualifyAnnounceMsg
 *********************************************************************************************************************/
/*! \brief      Validates the passed Announce message.
 *  \details    Checks the Announce message field for plausibility and verifies the GrandMaster identity as well as the
 *              path trace sequence.
 *  \param[in]  RxBufPtr    Pointer to the Ethernet reception buffer of the received Announce message
 *  \param[in]  PortIdx     Index of EthTSyn port that received the Announce message
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Announce message is valid
 *  \return     E_NOT_OK - Announce message is not valid
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilRx_QualifyAnnounceMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx);
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection
 *********************************************************************************************************************/
/*! \brief      Performs Port Role check and handles Master-Slave conflict detection.
 *  \details    Verifies that the passed Port is a Slave Port and handles the Master-Slave conflict detection
 *              including optional announce and source port identity checks as well as the report of the possible
 *              runtime error.
 *  \param[in]  PortIdx            Index of EthTSyn port that received the Sync message
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SrcClockIdentity   The source clock identity of the received Sync message
 *  \return     TRUE - Sync message was received on a Slave Port and no Master-Slave conflict was detected
 *  \return     FALSE - Sync message was received on a Master Port or a Master-Slave conflict was detected
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(
  EthTSyn_IntPortIdxType  PortIdx,
  uint64                  SrcClockIdentity);

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_PortIdentityIsEqual
 *********************************************************************************************************************/
/*! \brief      Checks if a passed local port identity and a port identity from a received message are equal.
 *  \details    -
 *  \param[in]  LocalPortIdentityPtr  The locally stored Port Identity used for comparison
 *  \param[in]  MsgPortIdentStartPtr  Clock Identity of the second Port Identity
 *  \return     TRUE - The Port Identities are equal
 *  \return     FALSE - The Port Identities are not equal
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_PortIdentityIsEqual(
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType)  LocalPortIdentityPtr,
  ETHTSYN_P2CONST(uint8)                     MsgPortIdentStartPtr);

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_PortIdentityIsEqualLocalPort
 *********************************************************************************************************************/
/*! \brief      Checks if the port identity of the passed EthTSyn port and from a port identity from a received message
 *              are equal.
 *  \details    -
 *  \param[in]  PortIdx               Index of the EthTSyn port
 *                                    [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgPortIdentStartPtr  Clock Identity of the second Port Identity
 *  \return     TRUE - The Port Identities are equal
 *  \return     FALSE - The Port Identities are not equal
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_PortIdentityIsEqualLocalPort(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  MsgPortIdentStartPtr);
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  TX UTILS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ProvideTxBuffer
 *********************************************************************************************************************/
/*! \brief          Allocates an Ethernet transmission buffer.
 *  \details        Allocates an Ethernet transmission buffer and initialize the buffer with '0' (requested length) in
 *                  case the debounce timer expired for the physical port.
 *  \param[in]      PortIdx       Index of the EthTSyn Port
 *                                [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in,out]  TxBufferPtr   In: Requested length of the Tx buffer
 *                               Out: Index and Pointer of the allocated Tx buffer. The FrameId.
 *                                    The Length is not modified.
 *  \return     E_OK - Ethernet buffer allocated and initialized. All out parameters are valid.
 *  \return     E_NOT_OK - Failed to allocate an Ethernet buffer. Out parameters are not valid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffer pointers
 *  \note       TxBufferPtr->Length is not modified and therefore can be used to trigger the transmission later.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_ProvideTxBuffer(
                EthTSyn_IntPortIdxType          PortIdx,
  ETHTSYN_P2VAR(EthTSyn_EthTxBufferStructType)  TxBufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareTransmission
 *********************************************************************************************************************/
/*! \brief      Prepares an Ethernet TxBuffer for transmission.
 *  \details    Prepares an Ethernet TxBuffer for transmission, i.e. set switch management info and enable egress
 *              timestamping if required.
 *  \param[in]  EthIfCtrlIdx       Index of the underlying EthIf controller
 *  \param[in]  TxBufferIdx        Index of the Ethernet tx buffer to be prepared
 *  \param[in]  EnableTsFlags      Bit field indicating which timestamps should be enabled
 *  \param[in]  SwtMgmtInfoPtr  The switch management information which should be set
 *  \return     E_OK - Ethernet buffer is ready for transmission.
 *  \return     E_NOT_OK - Failed to set up the Ethernet buffer for transmission. Release of the buffer required.
 *  \pre        TxBuffer was allocated by EthTSyn_UtilTx_ProvideTxBuffer()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *  \note       Depending on the value of EnableTsFlags and SwtMgmtInfoPtr the following egress timestamps are enabled:
 *              ETHTSYN_ENABLE_TS_HW_XOR_SWT_MASK == TRUE ->  SwtTs is enabled for SwtMgmtInfoPtr != NULL_PTR and
 *                                                            HwTs is enabled for SwtMgmtInfoPtr == NULL_PTR
 *              ETHTSYN_ENABLE_TS_HW_XOR_SWT_MASK == FALSE -> SwtTs is enabled for SwtmgmtInfoPtr != NULL_PTR &&
 *                                                            ETHTSYN_ENABLE_TS_SWT_TS_MASK == TRUE
 *                                                            HwTs is enabled for ETHTSYN_ENABLE_TS_HW_TS_MASK == TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareTransmission(
                  EthTSyn_EthIfCtrlIdxOfCtrlType   EthIfCtrlIdx,
                  uint8                            TxBufferIdx,
                  EthTSyn_EnableTimestampFlagsType EnableTsFlags,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType)         SwtMgmtInfoPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_Transmit
 *********************************************************************************************************************/
/*! \brief      Triggers the transmission of an Ethernet TxBuffer.
 *  \details    Triggers the transmission of a former allocated (EthTSyn_UtilTx_ProvideTxBuffer) and prepared
 *              (EthTSyn_UtilTx_PrepareTransmission) Ethernet TxBufferuffer. Recharges the debounce time of the
 *              physical port in case of successful transmission.
 *  \param[in]  PortIdx       Index of the EthTSyn port
 *                            [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  TxBufferIdx   The Ethernet Tx buffer index for transmission
 *  \param[in]  TxLength      The length to be transmitted in bytes
 *  \return     E_OK - Ethernet buffer successfully transmitted.
 *  \return     E_NOT_OK - Failed to transmit the Ethernet Tx buffer
 *  \pre        TxBuffer was allocated by EthTSyn_UtilTx_ProvideTxBuffer()
 *  \pre        TxBuffer was prepared for transmission by EthTSyn_UtilTx_PrepareTransmission()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_Transmit(
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  TxBufferIdx,
  uint16                 TxLength);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ReleaseTxBuffer
 *********************************************************************************************************************/
/*! \brief      Releases a former allocate Ethernet transmission buffer.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx    Index of the underlying EthIf controller
 *  \param[in]  TxBufferIndex   Index of the Ethernet Tx buffer to be released
 *  \pre        TxBuffer was allocated by EthTSyn_UtilTx_ProvideTxBuffer()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_ReleaseTxBuffer(
  EthTSyn_EthIfCtrlIdxOfCtrlType EthIfCtrlIdx,
  uint8                          TxBufferIdx);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareCommonMsgHdr
 *********************************************************************************************************************/
/*! \brief      Initializes the common message header.
 *  \details    Sets all required fields of the common message header (in Network-Byte-Order) according to the passed
 *              message type.
 *  \param[in]  TxBufPtr       Pointer to the Ethernet transmit buffer
 *  \param[in]  MsgType        The type of the message the header should be prepared for
 *  \param[in]  PortIdx        Index of the EthTSyn Port the message will be transmitted on
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareCommonMsgHdr(
  ETHTSYN_P2VAR(uint8)                  TxBufPtr,
                uint8                   MsgType,
                EthTSyn_IntPortIdxType  PortIdx);

/**********************************************************************************************************************
 *  DEBOUNCE TIMER HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_UtilTx_InitDebounceTimer
 *********************************************************************************************************************/
/*! \brief      Initializes the debounce timer with '0'.
 *  \details    -
 *  \param[in]  PyhsPortIdx   Index of the physical Port
 *                            [range: PyhsPortIdx < EthTSyn_GetSizeOfPhysPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_InitDebounceTimer(
  EthTSyn_PhysPortIterType PyhsPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_RechargeDebounceTimer
 *********************************************************************************************************************/
/*! \brief      Recharges the debounce timer to the configured start value.
 *  \details    -
 *  \param[in]  PortIdx   Index of the EthTSyn Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_RechargeDebounceTimer(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_DecDebounceTimer
 *********************************************************************************************************************/
/*! \brief      Decrement the debounce timer if it is not yet expired.
 *  \details    -
 *  \param[in]  PhyPortIdx   Index of the EthTSyn physical Port
 *                           [range: PortIdx < EthTSyn_GetSizeOfPhysPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_DecDebounceTimer(
  EthTSyn_PhysPortIterType PhyPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_IsDebounceTimerExpired
 *********************************************************************************************************************/
/*! \brief      Checks if the debounce timer is expired.
 *  \details    -
 *  \param[in]  PortIdx   Index of the EthTSyn Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Debounce timer expired
 *  \return     FALSE - Debounce timer not expired
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilTx_IsDebounceTimerExpired(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  END: TX UTILS
 *********************************************************************************************************************/
# endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_Util_IsTsReadyToProc
 *********************************************************************************************************************/
/*! \brief          Check if a timestamp is ready for processing.
 *  \details        -
 *  \param[in]      TsState   State of the timestamp
 *  \return         TRUE - Timestamp is ready for processing
 *  \return         FALSE - Timestamp is not ready for processing
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsTsReadyToProc(
  EthTSyn_TsStateEnumType TsState);

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetPortType
 *********************************************************************************************************************/
/*! \brief      Gets the Port type of the passed Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     ETHTSYN_PORT_TYPE_END_STATION_PORT - End-Station Port
 *  \return     ETHTSYN_PORT_TYPE_SWITCH_PORT - Switch-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortTypeType, ETHTSYN_CODE) EthTSyn_Util_GetPortType(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_IsSwitchPort
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is a Switch-Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is a Switch-Port
 *  \return     FALSE - Port is not a Switch-Port
 *  \pre        -
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsSwitchPort(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_IsEndStationPort
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is an EndStation-Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is an EndStation-Port
 *  \return     FALSE - Port is not an EndStation-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsEndStationPort(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilTx_GetSwtMgmtInfo
 *********************************************************************************************************************/
/*! \brief      Gets the Switch management info of the passed Port.
 *  \details    Gets the Switch management info (including the frame id if applicable) of the passed Port,
 *              if the passed Port is a Switch port.
 *  \param[in]  PortIdx       Index of the Port
 *                            [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out] MgmtInfoPtr   The retrieved switch management information including the frame id if applicable
 *  \return     E_OK - Port is a Switch-Port and switch management information was retrieved.
 *  \return     E_NOT_OK - Port is not a Switch-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_GetSwtMgmtInfo(
                  EthTSyn_IntPortIdxType    PortIdx,
    ETHTSYN_P2VAR(EthTSyn_SwtMgmtInfoType)  MgmtInfoPtr);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is ready to receive an Announce message (incl. check of PortRole == SLAVE).
 *  \details    -
 *  \param[in]  PortIdx   Index of EthTSyn port that shall receive the announce message
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is ready to receive the announce message
 *  \return     FALSE - Port is not ready to receive the announce message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsAsCapable
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is AsCapable.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is AsCapable
 *  \return     FALSE - Port is not AsCapable
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsAsCapable(
  EthTSyn_IntPortIdxType PortIdx);

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_SetAsCapable
 *********************************************************************************************************************/
/*! \brief      Sets AsCapable Flag of the passed Port.
 *  \details    -
 *  \param[in]  PortIdx     Index of the Port
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  AsCapable   The new value for AsCapable of the given Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Util_SetAsCapable(
  EthTSyn_IntPortIdxType PortIdx,
  boolean                AsCapable);
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl
 *********************************************************************************************************************/
/*! \brief      Gets the EthTSyn controller corresponding to the passed EthIf controller.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx   EthIf controller index.
 *  \return     EthTSyn_GetSizeOfCtrl() - no matching EthTSyn controller found
 *  \return     other values - index of the corresponding EthTSyn controller
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntCtrlIdxType, ETHTSYN_CODE) EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(
  uint8 EthIfCtrlIdx);

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetTimeDomainIdxFromId
 *********************************************************************************************************************/
/*! \brief      Gets the TimeDomain index of the passed TimeDomain Id.
 *  \details    -
 *  \param[in]  TimeDomainId   The TimeDomain Id
 *  \return     EthTSyn_GetSizeOfTimeDomain() - No matching time domain found
 *  \return     other value - Index of the matching time domain
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_Util_GetTimeDomainIdxFromId(
  EthTSyn_DomainNumberType TimeDomainId);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetEthIfCtrlIdxOfPort
 *********************************************************************************************************************/
/*! \brief      Gets the Ethernet interface controller index of the passed Port.
 *  \details    -
 *  \param[in]  PortIdx   EthTSyn port index
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     EthIf controller index
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetEthIfCtrlIdxOfPort(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Util_IsActivePdelayPort
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is an active Pdelay Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is active Pdelay port
 *  \return     FALSE - Port is no active Pdelay port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsActivePdelayPort(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Util_AreBitsSet
 *********************************************************************************************************************/
/*! \brief      Checks if all bits of the passed bit mask are set in the passed bit field.
 *  \details    -
 *  \param[in]  BitField   The bit field to check
 *  \param[in]  BitMask    The bits which to check
 *  \return     TRUE - All bits of the passed bit mask are set in the passed bit field
 *  \return     FALSE - At least one bit of the passed bit mask is not set in the passed bit field
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_AreBitsSet(
  uint8 BitField,
  uint8 BitMask);

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayInitiator
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is an active Pdelay Initiator.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is Pdelay initiator
 *  \return     FALSE - Port is no Pdelay initiator
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayInitiator(
  EthTSyn_IntPortIdxType PortIdx);

/***********************************************************************************************************************
 * END: PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayResponder
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is a Pdelay Responder.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is Pdelay responder
 *  \return     FALSE - Port is no Pdelay responder
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayResponder(
  EthTSyn_IntPortIdxType PortIdx);

/***********************************************************************************************************************
 *END: PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_CRC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetFollowUpDataIdListEntry
 *********************************************************************************************************************/
/*! \brief      Gets the value of the FollowUp Data Id list for the passed FollowUp Sequence Id.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the DataId is requested for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  SequenceId      The SequenceId
 *  \return     The value of the FollowUp Data Id list for the given Sequence Id
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetFollowUpDataIdListEntry(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  uint16                       SequenceId);
# endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL INLINE FUNCTIONS
 *********************************************************************************************************************/
# if !defined(ETHTSYN_UNIT_TEST) /* COV_ETHTSYN_TESTSUITE_INSTRUMENTATION */
/**********************************************************************************************************************
 *  EthTSyn_Util_IsTsReadyToProc
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsTsReadyToProc(
  EthTSyn_TsStateEnumType TsState)
{
  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 4304 4 */ /* MD_MSR_AutosarBoolean */
  return (boolean)(
    (TsState == ETHTSYN_TS_S_AVAILABLE) ||
    (TsState == ETHTSYN_TS_S_INVALID)
    );
} /* EthTSyn_Util_IsTsReadyToProc() */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetPortType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortTypeType, ETHTSYN_CODE) EthTSyn_Util_GetPortType(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortTypeType portType;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_IsSwitchPortMgmtUsedOfPort(PortIdx) == TRUE)
  {
    portType = ETHTSYN_PORT_TYPE_SWITCH_PORT;
  }
  else
  {
    portType = ETHTSYN_PORT_TYPE_END_STATION_PORT;
  }

  return portType;
} /* EthTSyn_Util_GetPortType() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsSwitchPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsSwitchPort(
  EthTSyn_IntPortIdxType PortIdx)
{
  return (boolean)(EthTSyn_Util_GetPortType(PortIdx) == ETHTSYN_PORT_TYPE_SWITCH_PORT); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
} /* EthTSyn_Util_IsSwitchPort() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsEndStationPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsEndStationPort(
  EthTSyn_IntPortIdxType PortIdx)
{
  return (boolean)(EthTSyn_Util_GetPortType(PortIdx) == ETHTSYN_PORT_TYPE_END_STATION_PORT); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
} /* EthTSyn_Util_IsEndStationPort() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_GetSwtMgmtInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_GetSwtMgmtInfo(
                EthTSyn_IntPortIdxType   PortIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_Util_IsSwitchPort(PortIdx) == TRUE)
  {
    MgmtInfoPtr->PortIdx = EthTSyn_GetPortIdxOfSwitchPortMgmt(EthTSyn_GetSwitchPortMgmtIdxOfPort(PortIdx));            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    MgmtInfoPtr->SwitchIdx = EthTSyn_GetSwitchIdxOfSwitchPortMgmt(EthTSyn_GetSwitchPortMgmtIdxOfPort(PortIdx));        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_UtilTx_GetSwtMgmtInfo() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

#  if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the given Port is a Slave Port. */
  if(EthTSyn_IsSlavePortUsedOfPort(PortIdx) == TRUE)
  {
    /* #20 Check if Port is AsCapable. */
    if(EthTSyn_Util_IsAsCapable(PortIdx) == TRUE)
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      /* #30 Check if Announce is enabled for the Port. */
      if(EthTSyn_IsAnnounceInfoUsedOfSlavePort(slavePortIdx) == TRUE)
      {
        isReady = TRUE;
      }
    }
  }

  return isReady;
} /* EthTSyn_SlaveRx_IsPortReadyToReceiveAnnounce() */
#  endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsAsCapable
 *********************************************************************************************************************/
/*!
 *Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsAsCapable(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean asCapable = TRUE; /* Init as TRUE for better readability */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Pdelay is used for the port. */
  if(EthTSyn_IsPdelayConfigUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    /* #20 Pdelay is used -> get AsCapable flag. */
    asCapable = (boolean)EthTSyn_IsAsCapableOfPdelayInfo(pDelayIdx);
  }

  return asCapable;
} /* EthTSyn_Util_IsAsCapable() */

#  if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_SetAsCapable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Util_SetAsCapable(
  EthTSyn_IntPortIdxType PortIdx,
  boolean                AsCapable)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is pdelay initiator because AsCapable can only change for Pdelay initiators. */
  if(EthTSyn_Util_IsPdelayInitiator(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    /* #20 Verify that Port is not always AsCapable. */
    if(EthTSyn_IsAlwaysAsCapableOfPdelayConfig(pDelayIdx) == FALSE)
    {
      /* #30 Only set AsCapable for Ports which are not always AsCapable. */
      EthTSyn_SetAsCapableOfPdelayInfo(pDelayIdx, AsCapable);                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
    }
  }
} /* EthTSyn_Util_SetAsCapable() */
#  endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

/***********************************************************************************************************************
 * EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntCtrlIdxType, ETHTSYN_CODE) EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(
  uint8 EthIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_CtrlIterType ethTSynCtrlIter;
  EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_GetSizeOfCtrl();

  /* ----- Implementation ----------------------------------------------- */
  for(ethTSynCtrlIter = 0; ethTSynCtrlIter < EthTSyn_GetSizeOfCtrl(); ethTSynCtrlIter++)
  {
    if(EthTSyn_GetEthIfCtrlIdxOfCtrl(ethTSynCtrlIter) == EthIfCtrlIdx)
    {
      ethTSynCtrlIdx = (EthTSyn_IntCtrlIdxType)ethTSynCtrlIter;
      break;
    }
  }

  return ethTSynCtrlIdx;
} /* EthTSyn_GetEthTSynCtrlFromEthIfCtrl */

#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetTimeDomainIdxFromId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_Util_GetTimeDomainIdxFromId(
  EthTSyn_DomainNumberType TimeDomainId)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntTimeDomainIdxType timeDomainIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search all configured TimeDomains for the passed TimeDomain Id. If a matching TimeDomain is found,
   *     return its index. */
  for(timeDomainIdx = 0; timeDomainIdx < EthTSyn_GetSizeOfTimeDomain(); timeDomainIdx++)
  {
    if(EthTSyn_GetIdOfTimeDomain(timeDomainIdx) == TimeDomainId)
    {
      break;
    }
  }

  return timeDomainIdx;
} /* EthTSyn_Util_GetTimeDomainIdxFromId() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetEthIfCtrlIdxOfPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetEthIfCtrlIdxOfPort(EthTSyn_IntPortIdxType PortIdx)
{
  return EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSyn_GetCtrlIdxOfPort(PortIdx));
} /* EthTSyn_Util_GetEthIfCtrlIdxOfPort() */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsActivePdelayPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsActivePdelayPort(EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isActivePdelayPort = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_IsPdelayConfigUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    isActivePdelayPort = (boolean)(EthTSyn_GetPortIdxOfPdelayConfig(pDelayCfgIdx) == PortIdx); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  }

  return isActivePdelayPort;
} /* EthTSyn_Pdelay_IsActivePdelayPort() */

/**********************************************************************************************************************
 *  EthTSyn_Util_AreBitsSet
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_AreBitsSet(
  uint8 BitField,
  uint8 BitMask)
{
  return (boolean)((BitField & BitMask) == BitMask); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
} /* EthTSyn_Util_AreBitsSet() */

#  if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayInitiator
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayInitiator(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isActiveInitiator = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the passed Port is an active Pdelay Port. */
  if(EthTSyn_Util_IsActivePdelayPort(PortIdx) == TRUE)
  {
    /* #20 Check if Port is Pdelay Initiator. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    isActiveInitiator = (boolean)EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(pDelayCfgIdx);
  }

  return isActiveInitiator;
} /* EthTSyn_Util_IsPdelayInitiator() */

/***********************************************************************************************************************
 * END: PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/
#  endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#  if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayResponder
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayResponder(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isActiveResponder = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the passed Port is an active Pdelay Port. */
  if(EthTSyn_Util_IsActivePdelayPort(PortIdx) == TRUE)
  {
    /* #20 Check if Port is Pdelay Responder. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    isActiveResponder = (boolean)EthTSyn_IsPdelayResponderUsedOfPdelayConfig(pDelayCfgIdx);
  }

  return isActiveResponder;
} /* EthTSyn_Util_IsPdelayResponder() */

/***********************************************************************************************************************
 * END: PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/
#  endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetFollowUpDataIdListEntry
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetFollowUpDataIdListEntry(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx, uint16 SequenceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 dataListEntry = 0;
  uint8 dataListIdx = (uint8)(SequenceId % ETHTSYN_FOLLOW_UP_DATA_ID_LIST_SIZE);

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_IsFollowUpDataIdListUsedOfTimeDomain(TimeDomainIdx) == TRUE)
  {
    dataListEntry = EthTSyn_GetFollowUpDataIdList(
      EthTSyn_GetFollowUpDataIdListStartIdxOfTimeDomain(TimeDomainIdx) + dataListIdx);
  }

  return dataListEntry;
} /* EthTSyn_Util_GetFollowUpDataIdListEntry() */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

# endif /* !defined(ETHTSYN_UNIT_TEST) */
# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHTSYN_UTIL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Util_Int.h
 *********************************************************************************************************************/
