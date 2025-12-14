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
 *            Module: EthTSyn
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthTSyn_GeneratedComplexTypes.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef ETHTSYN_GENERATED_COMPLEX_TYPES_H
#define ETHTSYN_GENERATED_COMPLEX_TYPES_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Types.h"

/**********************************************************************************************************************
 * GENERATED TYPES (NOT ComStackLib)
 *********************************************************************************************************************/
/**   \brief EthTSyn_EthBufferPtrType */
typedef P2VAR(uint8, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_EthBufferPtrType;

/**   \brief EthTSyn_EthConstBufferPtrType */
typedef P2CONST(uint8, TYPEDEF, ETHTSYN_APPL_DATA) EthTSyn_EthConstBufferPtrType;

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthTSynPCStructTypes  EthTSyn Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in EthTSyn_AnnounceInfo */
typedef struct sEthTSyn_AnnounceInfoType
{
  EthTSyn_AnnounceAllowedRxDelayOfAnnounceInfoType AnnounceAllowedRxDelayOfAnnounceInfo;  /**< Allowed delay for received Announce in MainFunction cycles */
  EthTSyn_MaxeStepsRemovedOfAnnounceInfoType MaxeStepsRemovedOfAnnounceInfo;  /**< Max hops to time master */
} EthTSyn_AnnounceInfoType;

/**   \brief  type used in EthTSyn_AnnounceSendSm */
typedef struct sEthTSyn_AnnounceSendSmType
{
  EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType AnnounceCycleTimerOfAnnounceSendSm;  /**< The Announce cycle timer */
  EthTSyn_StateOfAnnounceSendSmType StateOfAnnounceSendSm;  /**< The state of the AnnounceSend state machine */
} EthTSyn_AnnounceSendSmType;

/**   \brief  type used in EthTSyn_AnnounceSendSmCfg */
typedef struct sEthTSyn_AnnounceSendSmCfgType
{
  EthTSyn_AnnounceTxCycleOfAnnounceSendSmCfgType AnnounceTxCycleOfAnnounceSendSmCfg;  /**< The Announce transmission cycle expressed in EthTSyn_MainFunction cycles. */
} EthTSyn_AnnounceSendSmCfgType;

/**   \brief  type used in EthTSyn_Ctrl */
/*! \spec weak type invariant () { 
 * (self.PortIndStartIdxOfCtrl < EthTSyn_GetSizeOfPortInd()) &&
 * (self.PortIndEndIdxOfCtrl < EthTSyn_GetSizeOfPortInd())
 * } */
typedef struct sEthTSyn_CtrlType
{
  EthTSyn_EthIfCtrlIdxOfCtrlType EthIfCtrlIdxOfCtrl;  /**< Index of the underlying EthIf controller */
  EthTSyn_PortIndEndIdxOfCtrlType PortIndEndIdxOfCtrl;  /**< the end index of the 1:n relation pointing to EthTSyn_PortInd */
  EthTSyn_PortIndStartIdxOfCtrlType PortIndStartIdxOfCtrl;  /**< the start index of the 1:n relation pointing to EthTSyn_PortInd */
} EthTSyn_CtrlType;

/**   \brief  type used in EthTSyn_MasterPort */
/*! \spec weak type invariant () { 
 * (self.PortIdxOfMasterPort < EthTSyn_GetSizeOfPort()) &&
 * (!((self.AnnounceSendSmCfgIdxOfMasterPort != ETHTSYN_NO_ANNOUNCESENDSMCFGIDXOFMASTERPORT)) || (self.AnnounceSendSmCfgIdxOfMasterPort < EthTSyn_GetSizeOfAnnounceSendSmCfg()))
 * } */
typedef struct sEthTSyn_MasterPortType
{
  EthTSyn_ImmediateTimeSyncOfMasterPortType ImmediateTimeSyncOfMasterPort;  /**< Is immediate time sync enabled */
  EthTSyn_OfsSubTlvOfMasterPortType OfsSubTlvOfMasterPort;  /**< Is offset time domain sub Tlv used */
  EthTSyn_StatusSubTlvOfMasterPortType StatusSubTlvOfMasterPort;  /**< Is status sub Tlv used */
  EthTSyn_TimeSubTlvOfMasterPortType TimeSubTlvOfMasterPort;  /**< Is time secured sub Tlv used */
  EthTSyn_UserDataSubTlvOfMasterPortType UserDataSubTlvOfMasterPort;  /**< Is user data sub Tlv used */
  EthTSyn_SyncLogMsgIntervalOfMasterPortType SyncLogMsgIntervalOfMasterPort;  /**< Log message interval of the Sync message */
  EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType AnnounceSendSmCfgIdxOfMasterPort;  /**< the index of the 0:1 relation pointing to EthTSyn_AnnounceSendSmCfg */
  EthTSyn_CrcTimeFlagsOfMasterPortType CrcTimeFlagsOfMasterPort;  /**< Flags indicating which message fields should be used for Crc calculation */
  EthTSyn_CyclicMsgResumeCntOfMasterPortType CyclicMsgResumeCntOfMasterPort;  /**< The cyclic message resume time in MainFunction cycles */
  EthTSyn_FollowUpMsgLengthOfMasterPortType FollowUpMsgLengthOfMasterPort;  /**< The length of the follow up message */
  EthTSyn_PortIdxOfMasterPortType PortIdxOfMasterPort;  /**< the index of the 1:1 relation pointing to EthTSyn_Port */
  EthTSyn_SyncSendIntervalOfMasterPortType SyncSendIntervalOfMasterPort;  /**< Sync transmit interval in MainFunction cycles */
  EthTSyn_FollowUpSentCbkPtrType FollowUpSentCbkPtrOfMasterPort;  /**< Callback for notification of FollowUp transmission */
  EthTSyn_SyncSentCbkPtrType SyncSentCbkPtrOfMasterPort;  /**< Callback for notification of Sync transmission */
  EthTSyn_TxCrcSecuredEnumType TxCrcSecuredOfMasterPort;  /**< Crc method for transmitted follow up messages */
} EthTSyn_MasterPortType;

/**   \brief  type used in EthTSyn_MasterPortIdentity */
typedef struct sEthTSyn_MasterPortIdentityType
{
  EthTSyn_ClockIdentityOfMasterPortIdentityType ClockIdentityOfMasterPortIdentity;  /**< Clock identity of the configured master */
} EthTSyn_MasterPortIdentityType;

/**   \brief  type used in EthTSyn_OffsetTimeDomain */
typedef struct sEthTSyn_OffsetTimeDomainType
{
  EthTSyn_IdOfOffsetTimeDomainType IdOfOffsetTimeDomain;  /**< Id of the offset time domain */
  StbM_SynchronizedTimeBaseType SynchronizedTimeBaseIdOfOffsetTimeDomain;  /**< The synchronize time base id used for StbM API calls */
} EthTSyn_OffsetTimeDomainType;

/**   \brief  type used in EthTSyn_OfsCorrDurationInSyncCycles */
typedef struct sEthTSyn_OfsCorrDurationInSyncCyclesType
{
  EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType CounterOfOfsCorrDurationInSyncCycles;  /**< Counts the number of sync cycles since rate regulation started */
  EthTSyn_RestartedOfOfsCorrDurationInSyncCyclesType RestartedOfOfsCorrDurationInSyncCycles;  /**< Counter was restarted since last synchronization */
} EthTSyn_OfsCorrDurationInSyncCyclesType;

/**   \brief  type used in EthTSyn_PdelayConfig */
/*! \spec weak type invariant () { 
 * (self.PortIdxOfPdelayConfig < EthTSyn_GetSizeOfPort()) &&
 * (!((self.PdelayInitiatorIdxOfPdelayConfig != ETHTSYN_NO_PDELAYINITIATORIDXOFPDELAYCONFIG)) || (self.PdelayInitiatorIdxOfPdelayConfig < EthTSyn_GetSizeOfPdelayInitiator())) &&
 * (!((self.PdelayResponderIdxOfPdelayConfig != ETHTSYN_NO_PDELAYRESPONDERIDXOFPDELAYCONFIG)) || (self.PdelayResponderIdxOfPdelayConfig < EthTSyn_GetSizeOfPdelayResponder()))
 * } */
typedef struct sEthTSyn_PdelayConfigType
{
  EthTSyn_InitialPdelayNsOfPdelayConfigType InitialPdelayNsOfPdelayConfig;  /**< The initially used Pdelay value (this value is also used as static value when (UseStaticPdelay == TRUE)) */
  EthTSyn_AlwaysAsCapableOfPdelayConfigType AlwaysAsCapableOfPdelayConfig;  /**< Indicating if the Port is always AsCapable */
  EthTSyn_UseStaticPdelayOfPdelayConfigType UseStaticPdelayOfPdelayConfig;  /**< Is static Pdelay value used */
  EthTSyn_PdelayInitiatorIdxOfPdelayConfigType PdelayInitiatorIdxOfPdelayConfig;  /**< the index of the 0:1 relation pointing to EthTSyn_PdelayInitiator */
  EthTSyn_PdelayResponderIdxOfPdelayConfigType PdelayResponderIdxOfPdelayConfig;  /**< the index of the 0:1 relation pointing to EthTSyn_PdelayResponder */
  EthTSyn_PortIdxOfPdelayConfigType PortIdxOfPdelayConfig;  /**< the index of the 1:1 relation pointing to EthTSyn_Port */
} EthTSyn_PdelayConfigType;

/**   \brief  type used in EthTSyn_PdelayInfo */
typedef struct sEthTSyn_PdelayInfoType
{
  EthTSyn_AsCapableOfPdelayInfoType AsCapableOfPdelayInfo;  /**< AsCapable Flag */
  EthTSyn_UseAverageOfPdelayInfoType UseAverageOfPdelayInfo;  /**< Indicating if weighted averaging should be used. Initialized with FALSE and set to TRUE when the first valid Pdelay was measured/calculated and set. */
  EthTSyn_PdelayType PdelayValueNsOfPdelayInfo;  /**< Current valid Pdelay value */
} EthTSyn_PdelayInfoType;

/**   \brief  type used in EthTSyn_PdelayInitiator */
/*! \spec weak type invariant () { 
 * (self.PdelayReqSmIdxOfPdelayInitiator < EthTSyn_GetSizeOfPdelayReqSm())
 * } */
typedef struct sEthTSyn_PdelayInitiatorType
{
  EthTSyn_PdelayThresholdOfPdelayInitiatorType PdelayThresholdOfPdelayInitiator;  /**< The max allowed/valid value for Pdelay in nanoseconds */
  EthTSyn_LogMessageIntervalOfPdelayInitiatorType LogMessageIntervalOfPdelayInitiator;  /**< The Log message interval of the Pdelay request */
  EthTSyn_AllowedLostResponsesOfPdelayInitiatorType AllowedLostResponsesOfPdelayInitiator;  /**< The tolerated lost responses before changing AsCapable to 'FALSE' */
  EthTSyn_AverageWeightOfPdelayInitiatorType AverageWeightOfPdelayInitiator;  /**< Weight factor used for weighted average calculation */
  EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType PdelayReqSmIdxOfPdelayInitiator;  /**< the index of the 1:1 relation pointing to EthTSyn_PdelayReqSm */
  EthTSyn_RespRespFollowUpTimeoutOfPdelayInitiatorType RespRespFollowUpTimeoutOfPdelayInitiator;  /**< The Pdelay Response/Response FollowUp timeout in MainFunction cycles */
  EthTSyn_TxIntervalMfOfPdelayInitiatorType TxIntervalMfOfPdelayInitiator;  /**< The Pdelay request transmission interval in MainFunction cycles */
} EthTSyn_PdelayInitiatorType;

/**   \brief  type used in EthTSyn_PdelayResponder */
/*! \spec weak type invariant () { 
 * (self.PdelayRespSmIdxOfPdelayResponder < EthTSyn_GetSizeOfPdelayRespSm())
 * } */
typedef struct sEthTSyn_PdelayResponderType
{
  EthTSyn_PdelayRespSmIdxOfPdelayResponderType PdelayRespSmIdxOfPdelayResponder;  /**< the index of the 1:1 relation pointing to EthTSyn_PdelayRespSm */
} EthTSyn_PdelayResponderType;

/**   \brief  type used in EthTSyn_PhysPort */
typedef struct sEthTSyn_PhysPortType
{
  EthTSyn_DebounceTimerOfPhysPortType DebounceTimerOfPhysPort;  /**< The debounce timer for the physical port */
} EthTSyn_PhysPortType;

/**   \brief  type used in EthTSyn_PhysPortCfg */
typedef struct sEthTSyn_PhysPortCfgType
{
  EthTSyn_DebounceTimeOfPhysPortCfgType DebounceTimeOfPhysPortCfg;  /**< The debounce time expressed in EthTSyn_MainFunction cycles */
} EthTSyn_PhysPortCfgType;

/**   \brief  type used in EthTSyn_Port */
/*! \spec weak type invariant () { 
 * (self.CtrlIdxOfPort < EthTSyn_GetSizeOfCtrl()) &&
 * (self.TimeDomainIdxOfPort < EthTSyn_GetSizeOfTimeDomain()) &&
 * (self.PhysPortCfgIdxOfPort < EthTSyn_GetSizeOfPhysPortCfg()) &&
 * (!((self.SwitchPortMgmtIdxOfPort != ETHTSYN_NO_SWITCHPORTMGMTIDXOFPORT)) || (self.SwitchPortMgmtIdxOfPort < EthTSyn_GetSizeOfSwitchPortMgmt())) &&
 * (!((self.PdelayConfigIdxOfPort != ETHTSYN_NO_PDELAYCONFIGIDXOFPORT)) || (self.PdelayConfigIdxOfPort < EthTSyn_GetSizeOfPdelayConfig())) &&
 * (!((self.MasterPortIdxOfPort != ETHTSYN_NO_MASTERPORTIDXOFPORT)) || (self.MasterPortIdxOfPort < EthTSyn_GetSizeOfMasterPort())) &&
 * (!((self.SlavePortIdxOfPort != ETHTSYN_NO_SLAVEPORTIDXOFPORT)) || (self.SlavePortIdxOfPort < EthTSyn_GetSizeOfSlavePort()))
 * } */
typedef struct sEthTSyn_PortType
{
  EthTSyn_StbMTimeSrcEqualOfPortType StbMTimeSrcEqualOfPort;  /**< Identifying whether StbM uses the same time source as the EthTSyn on this port (only relevant for HW-Timestamping) */
  EthTSyn_CtrlIdxOfPortType CtrlIdxOfPort;  /**< the index of the 1:1 relation pointing to EthTSyn_Ctrl */
  EthTSyn_FramePrioOfPortType FramePrioOfPort;  /**< The Frame Priority used when transmitting message on this Port */
  EthTSyn_MasterPortIdxOfPortType MasterPortIdxOfPort;  /**< the index of the 0:1 relation pointing to EthTSyn_MasterPort */
  EthTSyn_NumberOfPortType NumberOfPort;  /**< The EthTSyn Port Number */
  EthTSyn_PdelayConfigIdxOfPortType PdelayConfigIdxOfPort;  /**< the index of the 0:1 relation pointing to EthTSyn_PdelayConfig */
  EthTSyn_PhysPortCfgIdxOfPortType PhysPortCfgIdxOfPort;  /**< the index of the 1:1 relation pointing to EthTSyn_PhysPortCfg */
  EthTSyn_SlavePortIdxOfPortType SlavePortIdxOfPort;  /**< the index of the 0:1 relation pointing to EthTSyn_SlavePort */
  EthTSyn_SwitchPortMgmtIdxOfPortType SwitchPortMgmtIdxOfPort;  /**< the index of the 0:1 relation pointing to EthTSyn_SwitchPortMgmt */
  EthTSyn_TimeDomainIdxOfPortType TimeDomainIdxOfPort;  /**< the index of the 1:1 relation pointing to EthTSyn_TimeDomain */
} EthTSyn_PortType;

/**   \brief  type used in EthTSyn_PortSyncSendSm */
typedef struct sEthTSyn_PortSyncSendSmType
{
  EthTSyn_StateOfPortSyncSendSmType StateOfPortSyncSendSm;  /**< The state of the PortSyncSend state machine */
  EthTSyn_SyncTxConfCalledOfPortSyncSendSmType SyncTxConfCalledOfPortSyncSendSm;  /**< Indicating it the Sync Tx-Confirmation of the current cycle was called */
  EthTSyn_TxBufIdxOfPortSyncSendSmType TxBufIdxOfPortSyncSendSm;  /**< Index of the Ethernet TxBuffer of the last transmitted message */
  EthTSyn_IntVltMgmtType SyncHostEgrIntVltMgmtOfPortSyncSendSm;  /**< The egress timestamp of a transmitted Sync on the Host/EndStation */
  EthTSyn_EthConstBufferPtrType TxBufPtrOfPortSyncSendSm;  /**< Pointer to the Ethernet TxBuffer of the last transmitted message */
} EthTSyn_PortSyncSendSmType;

/**   \brief  type used in EthTSyn_RateMeasurement */
typedef struct sEthTSyn_RateMeasurementType
{
  EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurementType AccumulatedMasterTimeDiffOfRateMeasurement;  /**< Accumulated master time diff */
  EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurementType AccumulatedSwtTimeDiffOfRateMeasurement;  /**< Accumulated switch time diff */
  EthTSyn_ActiveOfRateMeasurementType ActiveOfRateMeasurement;  /**< Measurement is currently running */
  EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType ActiveNrOfSyncCyclesOfRateMeasurement;  /**< Duration of the measurment in sync cycles */
} EthTSyn_RateMeasurementType;

/**   \brief  type used in EthTSyn_SlavePort */
/*! \spec weak type invariant () { 
 * (self.PortIdxOfSlavePort < EthTSyn_GetSizeOfPort()) &&
 * (!((self.AnnounceInfoIdxOfSlavePort != ETHTSYN_NO_ANNOUNCEINFOIDXOFSLAVEPORT)) || (self.AnnounceInfoIdxOfSlavePort < EthTSyn_GetSizeOfAnnounceInfo())) &&
 * (!((self.MasterPortIdentityIdxOfSlavePort != ETHTSYN_NO_MASTERPORTIDENTITYIDXOFSLAVEPORT)) || (self.MasterPortIdentityIdxOfSlavePort < EthTSyn_GetSizeOfMasterPortIdentity()))
 * } */
typedef struct sEthTSyn_SlavePortType
{
  EthTSyn_AnnounceInfoIdxOfSlavePortType AnnounceInfoIdxOfSlavePort;  /**< the index of the 0:1 relation pointing to EthTSyn_AnnounceInfo */
  EthTSyn_CrcFlagsRxValidatedOfSlavePortType CrcFlagsRxValidatedOfSlavePort;  /**< Flags indicating which message fields should be used for Crc calculation */
  EthTSyn_FollowUpAllowedRxDelayOfSlavePortType FollowUpAllowedRxDelayOfSlavePort;  /**< Allowed delay for received FollowUp messages in MainFunction cycles */
  EthTSyn_MasterPortIdentityIdxOfSlavePortType MasterPortIdentityIdxOfSlavePort;  /**< the index of the 0:1 relation pointing to EthTSyn_MasterPortIdentity */
  EthTSyn_PortIdxOfSlavePortType PortIdxOfSlavePort;  /**< the index of the 1:1 relation pointing to EthTSyn_Port */
  EthTSyn_RxCrcValidatedEnumType RxCrcValidatedOfSlavePort;  /**< Crc method for received follow up messages */
} EthTSyn_SlavePortType;

/**   \brief  type used in EthTSyn_SwitchPortMgmt */
typedef struct sEthTSyn_SwitchPortMgmtType
{
  EthTSyn_PortIdxOfSwitchPortMgmtType PortIdxOfSwitchPortMgmt;  /**< Index of the Switch Port (Switch context) */
  EthTSyn_SwitchIdxOfSwitchPortMgmtType SwitchIdxOfSwitchPortMgmt;  /**< Index of the Switch (EthIf context) */
} EthTSyn_SwitchPortMgmtType;

/**   \brief  type used in EthTSyn_SwitchSyncFrameCfg */
/*! \spec weak type invariant () { 
 * (self.SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg < EthTSyn_GetSizeOfSwitchTimeSyncCfg()) &&
 * (self.PortIdxOfSwitchSyncFrameCfg < EthTSyn_GetSizeOfPort())
 * } */
typedef struct sEthTSyn_SwitchSyncFrameCfgType
{
  EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfgType EthIfCtrlIdxOfSwitchSyncFrameCfg;  /**< Index of the EthIf controller used for the Switch Sync Frame */
  EthTSyn_FramePrioOfSwitchSyncFrameCfgType FramePrioOfSwitchSyncFrameCfg;  /**< Frame priority used for the Switch Sync Frame */
  EthTSyn_MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfgType MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg;  /**< Index of the Master Switch (EthIf context) */
  EthTSyn_MgmtPortSwitchPortIdxOfSwitchSyncFrameCfgType MgmtPortSwitchPortIdxOfSwitchSyncFrameCfg;  /**< Index of the management port of the Master Switch (Eth Switch context) */
  EthTSyn_PortIdxOfSwitchSyncFrameCfgType PortIdxOfSwitchSyncFrameCfg;  /**< the index of the 1:1 relation pointing to EthTSyn_Port */
  EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg;  /**< the index of the 1:1 relation pointing to EthTSyn_SwitchTimeSyncCfg */
  EthTSyn_SyncTxIntervalOfSwitchSyncFrameCfgType SyncTxIntervalOfSwitchSyncFrameCfg;  /**< Switch Sync Frame transmission cycle in MainFunction cycles */
} EthTSyn_SwitchSyncFrameCfgType;

/**   \brief  type used in EthTSyn_SwitchSyncFrameInfo */
typedef struct sEthTSyn_SwitchSyncFrameInfoType
{
  EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType SyncTxCntOfSwitchSyncFrameInfo;  /**< Sync Tx counter */
  EthTSyn_SequenceIdOfSwitchSyncFrameInfoType SequenceIdOfSwitchSyncFrameInfo;  /**< SequenceId of the Switch Sync Frame */
  EthTSyn_StateOfSwitchSyncFrameInfoType StateOfSwitchSyncFrameInfo;  /**< The state of the SwtSyncFrame mechanism */
  EthTSyn_TsMgmtStructType PreciseOriginTsMgmtOfSwitchSyncFrameInfo;  /**< The Precise Origin Timestamp with timestamp status */
  EthTSyn_TsMgmtStructType SwtIngressTsMgmtOfSwitchSyncFrameInfo;  /**< The switch ingress timestamp with timestamp status */
} EthTSyn_SwitchSyncFrameInfoType;

/**   \brief  type used in EthTSyn_SwitchSyncFrameTxFrameInfo */
typedef struct sEthTSyn_SwitchSyncFrameTxFrameInfoType
{
  EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType BufIdxOfSwitchSyncFrameTxFrameInfo;  /**< Buffer index of the Tx frame */
  EthTSyn_EthBufferPtrType BufAddrOfSwitchSyncFrameTxFrameInfo;  /**< Buffer address of the Tx frame */
  EthTSyn_GlobalTimestampType GlobalTimeOfSwitchSyncFrameTxFrameInfo;  /**< Global time retrieved via StbM_ButGetCurrentTime() when transmitting the switch sync frame. */
  EthTSyn_IntVltType IntVltOfSwitchSyncFrameTxFrameInfo;  /**< Virtual local time retrieved via StbM_ButGetCurrentTime() when transmitting the switch sync frame in internal representation. */
} EthTSyn_SwitchSyncFrameTxFrameInfoType;

/**   \brief  type used in EthTSyn_SwitchTimeSyncCfg */
/*! \spec weak type invariant () { 
 * (self.TimeDomainIdxOfSwitchTimeSyncCfg < EthTSyn_GetSizeOfTimeDomain()) &&
 * (self.SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg < EthTSyn_GetSizeOfSwtTimeSyncRateRegulatorCfg()) &&
 * (!((self.SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg != ETHTSYN_NO_SLAVESWITCHIDXLISTSTARTIDXOFSWITCHTIMESYNCCFG)) || (self.SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg < EthTSyn_GetSizeOfSlaveSwitchIdxList())) &&
 * (!((self.SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg != ETHTSYN_NO_SLAVESWITCHIDXLISTSTARTIDXOFSWITCHTIMESYNCCFG)) || (self.SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg < EthTSyn_GetSizeOfSlaveSwitchIdxList())) &&
 * (!((self.SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg != ETHTSYN_NO_SWITCHSYNCFRAMECFGIDXOFSWITCHTIMESYNCCFG)) || (self.SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg < EthTSyn_GetSizeOfSwitchSyncFrameCfg()))
 * } */
typedef struct sEthTSyn_SwitchTimeSyncCfgType
{
  EthTSyn_ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfgType ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg;  /**< Indicating if rate ratio has to be applied to slave switches separately */
  EthTSyn_EthIfSwitchIdxOfSwitchTimeSyncCfgType EthIfSwitchIdxOfSwitchTimeSyncCfg;  /**< Index of the Master switch in the context of the EthIf */
  EthTSyn_MaxOutOfSyncCntOfSwitchTimeSyncCfgType MaxOutOfSyncCntOfSwitchTimeSyncCfg;  /**< Max out of sync count */
  EthTSyn_SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfgType SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg;  /**< the end index of the 0:n relation pointing to EthTSyn_SlaveSwitchIdxList */
  EthTSyn_SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfgType SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg;  /**< the start index of the 0:n relation pointing to EthTSyn_SlaveSwitchIdxList */
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg;  /**< the index of the 0:1 relation pointing to EthTSyn_SwitchSyncFrameCfg */
  EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg;  /**< the index of the 1:1 relation pointing to EthTSyn_SwtTimeSyncRateRegulatorCfg */
  EthTSyn_SyncEventTimeoutOfSwitchTimeSyncCfgType SyncEventTimeoutOfSwitchTimeSyncCfg;  /**< Timeout for sync event */
  EthTSyn_SyncPrecisionLimitNsOfSwitchTimeSyncCfgType SyncPrecisionLimitNsOfSwitchTimeSyncCfg;  /**< The sync precision limit in nanoseconds */
  EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType TimeDomainIdxOfSwitchTimeSyncCfg;  /**< the index of the 1:1 relation pointing to EthTSyn_TimeDomain */
  EthTSyn_SwtTimeSync_SwtSyncStateChgFctPtrType SwtSyncStateChgFctPtrOfSwitchTimeSyncCfg;  /**< User notification for changes of the sync state */
} EthTSyn_SwitchTimeSyncCfgType;

/**   \brief  type used in EthTSyn_SwitchTimeSyncInfo */
typedef struct sEthTSyn_SwitchTimeSyncInfoType
{
  EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType CurrentOffsetNsOfSwitchTimeSyncInfo;  /**< Current valid offset of the switch (cascade) */
  EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType LastCorrectedOffsetNsOfSwitchTimeSyncInfo;  /**< Switch offset which was corrected by time leap at the last synchronization event */
  EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType SyncEventTimeoutCntOfSwitchTimeSyncInfo;  /**< Sync event timeout counter */
  EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType OutOfSyncCntOfSwitchTimeSyncInfo;  /**< Current out of sync count of the switch (cascade) */
  EthTSyn_StateOfSwitchTimeSyncInfoType StateOfSwitchTimeSyncInfo;  /**< State of the switch time sync info */
  EthTSyn_WasSyncReachedOfSwitchTimeSyncInfoType WasSyncReachedOfSwitchTimeSyncInfo;  /**< Indicating if sync state SYNC was reached at least once */
  EthTSyn_SwtTimeSync_TimestampInfoStructType PrevTimeStampInfoOfSwitchTimeSyncInfo;  /**< Switch time sync timestamp info stored at last synchronization event */
  EthTSyn_SyncStateType SwtSyncStateOfSwitchTimeSyncInfo;  /**< Current valid sync state of the switch (cascade) */
  EthTSyn_SwtTimeSync_TimestampInfoStructType TimeStampInfoOfSwitchTimeSyncInfo;  /**< Switch time sync timestamp info stored at current synchronization event */
} EthTSyn_SwitchTimeSyncInfoType;

/**   \brief  type used in EthTSyn_SwtTimeSyncRateRegulatorCfg */
/*! \spec weak type invariant () { 
 * (self.RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg < EthTSyn_GetSizeOfRateMeasurement()) &&
 * (self.RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg < EthTSyn_GetSizeOfRateMeasurement())
 * } */
typedef struct sEthTSyn_SwtTimeSyncRateRegulatorCfgType
{
  EthTSyn_RateRatioMaxOfSwtTimeSyncRateRegulatorCfgType RateRatioMaxOfSwtTimeSyncRateRegulatorCfg;  /**< Max allowed RateRatio */
  EthTSyn_RateRatioMinOfSwtTimeSyncRateRegulatorCfgType RateRatioMinOfSwtTimeSyncRateRegulatorCfg;  /**< Min allowed RateRatio */
  EthTSyn_UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfgType UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg;  /**< Indicating if offset (time leap) correction should be used before SYNC state was established for the first time */
  EthTSyn_NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfgType NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg;  /**< Number of parallel running rate measurements */
  EthTSyn_NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfgType NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg;  /**< Number of sync cycles used for offset correction */
  EthTSyn_OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfgType OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg;  /**< Offset threshold to switch from rate regulator to jump correction in nanoseconds */
  EthTSyn_RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfgType RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg;  /**< the end index of the 1:n relation pointing to EthTSyn_RateMeasurement */
  EthTSyn_RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfgType RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfg;  /**< the number of relations pointing to EthTSyn_RateMeasurement */
  EthTSyn_RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfgType RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg;  /**< the start index of the 1:n relation pointing to EthTSyn_RateMeasurement */
} EthTSyn_SwtTimeSyncRateRegulatorCfgType;

/**   \brief  type used in EthTSyn_SystemState */
typedef struct sEthTSyn_SystemStateType
{
  EthTSyn_GmClockIdentityOfSystemStateType GmClockIdentityOfSystemState;  /**< The clock identity of the grand master. Only valid for GmPresent == TRUE */
  EthTSyn_GmPresentOfSystemStateType GmPresentOfSystemState;  /**< Indicating if a grand master is present */
} EthTSyn_SystemStateType;

/**   \brief  type used in EthTSyn_TimeBaseUpdateCounter */
typedef struct sEthTSyn_TimeBaseUpdateCounterType
{
  EthTSyn_ValidOfTimeBaseUpdateCounterType ValidOfTimeBaseUpdateCounter;  /**< Indicating if Value is valid. */
  EthTSyn_ValueOfTimeBaseUpdateCounterType ValueOfTimeBaseUpdateCounter;  /**< Last value of the synchronized time base update counter. */
} EthTSyn_TimeBaseUpdateCounterType;

/**   \brief  type used in EthTSyn_TimeDomain */
/*! \spec weak type invariant () { 
 * (!((self.MasterPortLengthOfTimeDomain != 0u)) || (self.MasterPortStartIdxOfTimeDomain < EthTSyn_GetSizeOfMasterPort())) &&
 * (!((self.MasterPortLengthOfTimeDomain != 0u)) || (self.MasterPortEndIdxOfTimeDomain < EthTSyn_GetSizeOfMasterPort())) &&
 * (!((self.SlavePortStartIdxOfTimeDomain != ETHTSYN_NO_SLAVEPORTSTARTIDXOFTIMEDOMAIN)) || (self.SlavePortStartIdxOfTimeDomain < EthTSyn_GetSizeOfSlavePort())) &&
 * (!((self.SlavePortStartIdxOfTimeDomain != ETHTSYN_NO_SLAVEPORTSTARTIDXOFTIMEDOMAIN)) || (self.SlavePortEndIdxOfTimeDomain < EthTSyn_GetSizeOfSlavePort())) &&
 * (!((self.OffsetTimeDomainStartIdxOfTimeDomain != ETHTSYN_NO_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN)) || (self.OffsetTimeDomainStartIdxOfTimeDomain < EthTSyn_GetSizeOfOffsetTimeDomain())) &&
 * (!((self.OffsetTimeDomainStartIdxOfTimeDomain != ETHTSYN_NO_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN)) || (self.OffsetTimeDomainEndIdxOfTimeDomain < EthTSyn_GetSizeOfOffsetTimeDomain())) &&
 * (!((self.FollowUpDataIdListStartIdxOfTimeDomain != ETHTSYN_NO_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN)) || (self.FollowUpDataIdListStartIdxOfTimeDomain < EthTSyn_GetSizeOfFollowUpDataIdList())) &&
 * (!((self.FollowUpDataIdListStartIdxOfTimeDomain != ETHTSYN_NO_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN)) || (self.FollowUpDataIdListEndIdxOfTimeDomain < EthTSyn_GetSizeOfFollowUpDataIdList()))
 * } */
typedef struct sEthTSyn_TimeDomainType
{
  EthTSyn_ImmediateTimeSyncOfTimeDomainType ImmediateTimeSyncOfTimeDomain;  /**< Is immediate time sync enabled */
  EthTSyn_FollowUpDataIdListEndIdxOfTimeDomainType FollowUpDataIdListEndIdxOfTimeDomain;  /**< the end index of the 0:n relation pointing to EthTSyn_FollowUpDataIdList */
  EthTSyn_FollowUpDataIdListStartIdxOfTimeDomainType FollowUpDataIdListStartIdxOfTimeDomain;  /**< the start index of the 0:n relation pointing to EthTSyn_FollowUpDataIdList */
  EthTSyn_IdOfTimeDomainType IdOfTimeDomain;  /**< Id of the time domain */
  EthTSyn_MasterPortEndIdxOfTimeDomainType MasterPortEndIdxOfTimeDomain;  /**< the end index of the 0:n relation pointing to EthTSyn_MasterPort */
  EthTSyn_MasterPortLengthOfTimeDomainType MasterPortLengthOfTimeDomain;  /**< the number of relations pointing to EthTSyn_MasterPort */
  EthTSyn_MasterPortStartIdxOfTimeDomainType MasterPortStartIdxOfTimeDomain;  /**< the start index of the 0:n relation pointing to EthTSyn_MasterPort */
  EthTSyn_OffsetTimeDomainEndIdxOfTimeDomainType OffsetTimeDomainEndIdxOfTimeDomain;  /**< the end index of the 0:n relation pointing to EthTSyn_OffsetTimeDomain */
  EthTSyn_OffsetTimeDomainStartIdxOfTimeDomainType OffsetTimeDomainStartIdxOfTimeDomain;  /**< the start index of the 0:n relation pointing to EthTSyn_OffsetTimeDomain */
  EthTSyn_SlavePortEndIdxOfTimeDomainType SlavePortEndIdxOfTimeDomain;  /**< the end index of the 0:n relation pointing to EthTSyn_SlavePort */
  EthTSyn_SlavePortStartIdxOfTimeDomainType SlavePortStartIdxOfTimeDomain;  /**< the start index of the 0:n relation pointing to EthTSyn_SlavePort */
  StbM_SynchronizedTimeBaseType SynchronizedTimeBaseIdOfTimeDomain;  /**< The synchronize time base id used for StbM API calls */
} EthTSyn_TimeDomainType;

/**   \brief  type used in EthTSyn_TimeValidMasterCfg */
typedef struct sEthTSyn_TimeValidMasterCfgType
{
  StbM_SynchronizedTimeBaseType SynchronizedTimeBaseIdOfTimeValidMasterCfg;  /**< The synchronize time base id used for StbM API calls */
} EthTSyn_TimeValidMasterCfgType;

/**   \brief  type used in EthTSyn_TimeValidMasterData */
typedef struct sEthTSyn_TimeValidMasterDataType
{
  EthTSyn_CorrectionFieldOfTimeValidMasterDataType CorrectionFieldOfTimeValidMasterData;  /**< Value of the FollowUp correction field */
  EthTSyn_SrcClockIdOfTimeValidMasterDataType SrcClockIdOfTimeValidMasterData;  /**< The clock identity of the underlying port */
  EthTSyn_SequenceIdOfTimeValidMasterDataType SequenceIdOfTimeValidMasterData;  /**< The sequence id of the master sync cycle */
  EthTSyn_SrcPortNumOfTimeValidMasterDataType SrcPortNumOfTimeValidMasterData;  /**< Port number of the underlying port */
  EthTSyn_StateFlagsOfTimeValidMasterDataType StateFlagsOfTimeValidMasterData;  /**< Flags indicating which master data where provided */
  StbM_TimeStampShortType PreciseOriginTimestampOfTimeValidMasterData;  /**< The precise origin timestamp as transmitted in the FollowUp */
  EthTSyn_IntVltType SyncEgressTsVltOfTimeValidMasterData;  /**< Egress timestamp of the transmitted sync message as internal virtual local time */
} EthTSyn_TimeValidMasterDataType;

/**   \brief  type used in EthTSyn_TimeValidPdReqCfg */
typedef struct sEthTSyn_TimeValidPdReqCfgType
{
  StbM_SynchronizedTimeBaseType SynchronizedTimeBaseIdOfTimeValidPdReqCfg;  /**< The synchronize time base id used for StbM API calls */
} EthTSyn_TimeValidPdReqCfgType;

/**   \brief  type used in EthTSyn_TimeValidPdReqData */
typedef struct sEthTSyn_TimeValidPdReqDataType
{
  EthTSyn_PdRespClockIdOfTimeValidPdReqDataType PdRespClockIdOfTimeValidPdReqData;  /**< Source clock identity of the received Pdelay_Resp, i.e. clock identity of the pdelay responder */
  EthTSyn_SrcClockIdOfTimeValidPdReqDataType SrcClockIdOfTimeValidPdReqData;  /**< The clock identity of the underlying port */
  EthTSyn_CurrPdelayOfTimeValidPdReqDataType CurrPdelayOfTimeValidPdReqData;  /**< The Pdelay computed with this pdelay measurement cycle */
  EthTSyn_PdRespPortNumOfTimeValidPdReqDataType PdRespPortNumOfTimeValidPdReqData;  /**< Source port number of the received Pdelay_Resp, i.e. port number of the pdelay responder */
  EthTSyn_SequenceIdOfTimeValidPdReqDataType SequenceIdOfTimeValidPdReqData;  /**< SequenceId of the Pdelay cycle received with the Pdelay_Req */
  EthTSyn_SrcPortNumOfTimeValidPdReqDataType SrcPortNumOfTimeValidPdReqData;  /**< Port number of the underlying port */
  EthTSyn_StateFlagsOfTimeValidPdReqDataType StateFlagsOfTimeValidPdReqData;  /**< Flags indicating which pdelay initiator data where provided */
  EthTSyn_IntVltType PdReqEgressTsVltOfTimeValidPdReqData;  /**< Egress timestamp of the transmitted Pdelay_Req as internal virtual local time */
  StbM_TimeStampShortType PdReqRcvdTsOfTimeValidPdReqData;  /**< The Pdelay_Req received timestamps of the responder, received with the Pdelay_Resp */
  EthTSyn_IntVltType PdRespIngressTsVltOfTimeValidPdReqData;  /**< Ingress timestamp of the received Pdelay_Resp as internal virtual local time */
  StbM_TimeStampShortType PdRespSentTsOfTimeValidPdReqData;  /**< The Pdelay_Resp sent timestamps of the responder, received with the Pdelay_Resp_Fup */
  StbM_TimeStampShortType RefTimeGlobalOfTimeValidPdReqData;  /**< The global time part of the reference time tuple (use for conversion of Pdelay times into global times) */
  StbM_VirtualLocalTimeType RefTimeVltOfTimeValidPdReqData;  /**< The virtual local time part of the reference time tuple (use for conversion of Pdelay times into global times) */
} EthTSyn_TimeValidPdReqDataType;

/**   \brief  type used in EthTSyn_TimeValidPdRespCfg */
typedef struct sEthTSyn_TimeValidPdRespCfgType
{
  StbM_SynchronizedTimeBaseType SynchronizedTimeBaseIdOfTimeValidPdRespCfg;  /**< The synchronize time base id used for StbM API calls */
} EthTSyn_TimeValidPdRespCfgType;

/**   \brief  type used in EthTSyn_TimeValidPdRespData */
typedef struct sEthTSyn_TimeValidPdRespDataType
{
  EthTSyn_PdReqClockIdOfTimeValidPdRespDataType PdReqClockIdOfTimeValidPdRespData;  /**< Source clock identity of the received Pdelay_Req, i.e. clock identity of the pdelay initiator */
  EthTSyn_SrcClockIdOfTimeValidPdRespDataType SrcClockIdOfTimeValidPdRespData;  /**< The clock identity of the underlying port */
  EthTSyn_PdReqPortNumOfTimeValidPdRespDataType PdReqPortNumOfTimeValidPdRespData;  /**< Source port number of the received Pdelay_Req, i.e. port number of the pdelay initiator */
  EthTSyn_SequenceIdOfTimeValidPdRespDataType SequenceIdOfTimeValidPdRespData;  /**< SequenceId of the Pdelay cycle received with the Pdelay_Req */
  EthTSyn_SrcPortNumOfTimeValidPdRespDataType SrcPortNumOfTimeValidPdRespData;  /**< Port number of the underlying port */
  EthTSyn_StateFlagsOfTimeValidPdRespDataType StateFlagsOfTimeValidPdRespData;  /**< Flags indicating which pdelay responder data where provided */
  EthTSyn_IntVltType PdReqIngressTsVltOfTimeValidPdRespData;  /**< Ingress timestamp of the received Pdelay_Req as internal virtual local time */
  EthTSyn_IntVltType PdRespEgressTsVltOfTimeValidPdRespData;  /**< Egress timestamp of the transmitted Pdelay_Resp as internal virtual local time */
  StbM_TimeStampShortType RefTimeGlobalOfTimeValidPdRespData;  /**< The global time part of the reference time tuple (use for conversion of Pdelay times into global times) */
  StbM_VirtualLocalTimeType RefTimeVltOfTimeValidPdRespData;  /**< The virtual local time part of the reference time tuple (use for conversion of Pdelay times into global times) */
} EthTSyn_TimeValidPdRespDataType;

/**   \brief  type used in EthTSyn_TimeValidSlaveCfg */
typedef struct sEthTSyn_TimeValidSlaveCfgType
{
  StbM_SynchronizedTimeBaseType SynchronizedTimeBaseIdOfTimeValidSlaveCfg;  /**< The synchronize time base id used for StbM API calls */
} EthTSyn_TimeValidSlaveCfgType;

/**   \brief  type used in EthTSyn_TimeValidSlaveData */
typedef struct sEthTSyn_TimeValidSlaveDataType
{
  EthTSyn_CorrectionFieldOfTimeValidSlaveDataType CorrectionFieldOfTimeValidSlaveData;  /**< Value of the received FollowUp correction field */
  EthTSyn_MasterClockIdOfTimeValidSlaveDataType MasterClockIdOfTimeValidSlaveData;  /**< The clock identity of the master received with the sync message */
  EthTSyn_CurrPdelayOfTimeValidSlaveDataType CurrPdelayOfTimeValidSlaveData;  /**< The current valid Pdelay als reported to the StbM vis StbM_BusSetGlobalTime() */
  EthTSyn_MasterPortNumOfTimeValidSlaveDataType MasterPortNumOfTimeValidSlaveData;  /**< Port number of the master received with the sync message */
  EthTSyn_SequenceIdOfTimeValidSlaveDataType SequenceIdOfTimeValidSlaveData;  /**< The sequence id of the slave sync cycle */
  EthTSyn_StateFlagsOfTimeValidSlaveDataType StateFlagsOfTimeValidSlaveData;  /**< Flags indicating which slave data where provided */
  StbM_TimeStampShortType PreciseOriginTimestampOfTimeValidSlaveData;  /**< The precise origin timestamp received in the FollowUp */
  EthTSyn_IntVltType SyncIngressTsVltOfTimeValidSlaveData;  /**< Ingress timestamp of the received sync message as internal virtual local time */
} EthTSyn_TimeValidSlaveDataType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCSymbolicStructTypes  EthTSyn Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to EthTSyn_SystemState */
typedef struct EthTSyn_SystemStateStructSTag
{
  EthTSyn_SystemStateType EthTSynGlobalTimeDomain;
} EthTSyn_SystemStateStructSType;

/**   \brief  type to be used as symbolic data element access to EthTSyn_TimeBaseUpdateCounter */
typedef struct EthTSyn_TimeBaseUpdateCounterStructSTag
{
  EthTSyn_TimeBaseUpdateCounterType EthTSynGlobalTimeDomain;
} EthTSyn_TimeBaseUpdateCounterStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCUnionIndexAndSymbolTypes  EthTSyn Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access EthTSyn_SystemState in an index and symbol based style. */
typedef union EthTSyn_SystemStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthTSyn_SystemStateType raw[1];
  EthTSyn_SystemStateStructSType str;
} EthTSyn_SystemStateUType;

/**   \brief  type to access EthTSyn_TimeBaseUpdateCounter in an index and symbol based style. */
typedef union EthTSyn_TimeBaseUpdateCounterUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthTSyn_TimeBaseUpdateCounterType raw[1];
  EthTSyn_TimeBaseUpdateCounterStructSType str;
} EthTSyn_TimeBaseUpdateCounterUType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCRootPointerTypes  EthTSyn Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to EthTSyn_AnnounceInfo */
typedef P2CONST(EthTSyn_AnnounceInfoType, TYPEDEF, ETHTSYN_CONST) EthTSyn_AnnounceInfoPtrType;

/**   \brief  type used to point to EthTSyn_AnnounceReceiveSm */
typedef P2VAR(EthTSyn_AnnounceReceiveSmType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_AnnounceReceiveSmPtrType;

/**   \brief  type used to point to EthTSyn_AnnounceSendSm */
typedef P2VAR(EthTSyn_AnnounceSendSmType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_AnnounceSendSmPtrType;

/**   \brief  type used to point to EthTSyn_AnnounceSendSmCfg */
typedef P2CONST(EthTSyn_AnnounceSendSmCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_AnnounceSendSmCfgPtrType;

/**   \brief  type used to point to EthTSyn_Ctrl */
typedef P2CONST(EthTSyn_CtrlType, TYPEDEF, ETHTSYN_CONST) EthTSyn_CtrlPtrType;

/**   \brief  type used to point to EthTSyn_CtrlState */
typedef P2VAR(EthTSyn_CtrlStateType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_CtrlStatePtrType;

/**   \brief  type used to point to EthTSyn_DestinationMac */
typedef P2CONST(EthTSyn_DestinationMacType, TYPEDEF, ETHTSYN_CONST) EthTSyn_DestinationMacPtrType;

/**   \brief  type used to point to EthTSyn_FollowUpDataIdList */
typedef P2CONST(EthTSyn_FollowUpDataIdListType, TYPEDEF, ETHTSYN_CONST) EthTSyn_FollowUpDataIdListPtrType;

/**   \brief  type used to point to EthTSyn_MasterPort */
typedef P2CONST(EthTSyn_MasterPortType, TYPEDEF, ETHTSYN_CONST) EthTSyn_MasterPortPtrType;

/**   \brief  type used to point to EthTSyn_MasterPortIdentity */
typedef P2CONST(EthTSyn_MasterPortIdentityType, TYPEDEF, ETHTSYN_CONST) EthTSyn_MasterPortIdentityPtrType;

/**   \brief  type used to point to EthTSyn_OffsetTimeDomain */
typedef P2CONST(EthTSyn_OffsetTimeDomainType, TYPEDEF, ETHTSYN_CONST) EthTSyn_OffsetTimeDomainPtrType;

/**   \brief  type used to point to EthTSyn_OfsCorrDurationInSyncCycles */
typedef P2VAR(EthTSyn_OfsCorrDurationInSyncCyclesType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_OfsCorrDurationInSyncCyclesPtrType;

/**   \brief  type used to point to EthTSyn_PdelayConfig */
typedef P2CONST(EthTSyn_PdelayConfigType, TYPEDEF, ETHTSYN_CONST) EthTSyn_PdelayConfigPtrType;

/**   \brief  type used to point to EthTSyn_PdelayInfo */
typedef P2VAR(EthTSyn_PdelayInfoType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PdelayInfoPtrType;

/**   \brief  type used to point to EthTSyn_PdelayInitiator */
typedef P2CONST(EthTSyn_PdelayInitiatorType, TYPEDEF, ETHTSYN_CONST) EthTSyn_PdelayInitiatorPtrType;

/**   \brief  type used to point to EthTSyn_PdelayReqSm */
typedef P2VAR(EthTSyn_PdelayReqSmType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PdelayReqSmPtrType;

/**   \brief  type used to point to EthTSyn_PdelayRespSm */
typedef P2VAR(EthTSyn_PdelayRespSmType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PdelayRespSmPtrType;

/**   \brief  type used to point to EthTSyn_PdelayResponder */
typedef P2CONST(EthTSyn_PdelayResponderType, TYPEDEF, ETHTSYN_CONST) EthTSyn_PdelayResponderPtrType;

/**   \brief  type used to point to EthTSyn_PhysPort */
typedef P2VAR(EthTSyn_PhysPortType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PhysPortPtrType;

/**   \brief  type used to point to EthTSyn_PhysPortCfg */
typedef P2CONST(EthTSyn_PhysPortCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_PhysPortCfgPtrType;

/**   \brief  type used to point to EthTSyn_Port */
typedef P2CONST(EthTSyn_PortType, TYPEDEF, ETHTSYN_CONST) EthTSyn_PortPtrType;

/**   \brief  type used to point to EthTSyn_PortInd */
typedef P2CONST(EthTSyn_PortIndType, TYPEDEF, ETHTSYN_CONST) EthTSyn_PortIndPtrType;

/**   \brief  type used to point to EthTSyn_PortSyncSendSm */
typedef P2VAR(EthTSyn_PortSyncSendSmType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PortSyncSendSmPtrType;

/**   \brief  type used to point to EthTSyn_SyncHostEgrIntVltMgmtOfPortSyncSendSm */
typedef P2VAR(EthTSyn_IntVltMgmtType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SyncHostEgrIntVltMgmtOfPortSyncSendSmPtrType;

/**   \brief  type used to point to EthTSyn_TxBufPtrOfPortSyncSendSm */
typedef P2VAR(EthTSyn_EthConstBufferPtrType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TxBufPtrOfPortSyncSendSmPtrType;

/**   \brief  type used to point to EthTSyn_RateMeasurement */
typedef P2VAR(EthTSyn_RateMeasurementType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_RateMeasurementPtrType;

/**   \brief  type used to point to EthTSyn_SlavePort */
typedef P2CONST(EthTSyn_SlavePortType, TYPEDEF, ETHTSYN_CONST) EthTSyn_SlavePortPtrType;

/**   \brief  type used to point to EthTSyn_SlaveSwitchIdxList */
typedef P2CONST(EthTSyn_SlaveSwitchIdxListType, TYPEDEF, ETHTSYN_CONST) EthTSyn_SlaveSwitchIdxListPtrType;

/**   \brief  type used to point to EthTSyn_SwitchPortMgmt */
typedef P2CONST(EthTSyn_SwitchPortMgmtType, TYPEDEF, ETHTSYN_CONST) EthTSyn_SwitchPortMgmtPtrType;

/**   \brief  type used to point to EthTSyn_SwitchSyncFrameCfg */
typedef P2CONST(EthTSyn_SwitchSyncFrameCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_SwitchSyncFrameCfgPtrType;

/**   \brief  type used to point to EthTSyn_SwitchSyncFrameInfo */
typedef P2VAR(EthTSyn_SwitchSyncFrameInfoType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwitchSyncFrameInfoPtrType;

/**   \brief  type used to point to EthTSyn_PreciseOriginTsMgmtOfSwitchSyncFrameInfo */
typedef P2VAR(EthTSyn_TsMgmtStructType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PreciseOriginTsMgmtOfSwitchSyncFrameInfoPtrType;

/**   \brief  type used to point to EthTSyn_SwtIngressTsMgmtOfSwitchSyncFrameInfo */
typedef P2VAR(EthTSyn_TsMgmtStructType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtIngressTsMgmtOfSwitchSyncFrameInfoPtrType;

/**   \brief  type used to point to EthTSyn_SwitchSyncFrameTxFrameInfo */
typedef P2VAR(EthTSyn_SwitchSyncFrameTxFrameInfoType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwitchSyncFrameTxFrameInfoPtrType;

/**   \brief  type used to point to EthTSyn_BufAddrOfSwitchSyncFrameTxFrameInfo */
typedef P2VAR(EthTSyn_EthBufferPtrType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_BufAddrOfSwitchSyncFrameTxFrameInfoPtrType;

/**   \brief  type used to point to EthTSyn_GlobalTimeOfSwitchSyncFrameTxFrameInfo */
typedef P2VAR(EthTSyn_GlobalTimestampType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_GlobalTimeOfSwitchSyncFrameTxFrameInfoPtrType;

/**   \brief  type used to point to EthTSyn_SwitchTimeSyncCfg */
typedef P2CONST(EthTSyn_SwitchTimeSyncCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_SwitchTimeSyncCfgPtrType;

/**   \brief  type used to point to EthTSyn_SwitchTimeSyncInfo */
typedef P2VAR(EthTSyn_SwitchTimeSyncInfoType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwitchTimeSyncInfoPtrType;

/**   \brief  type used to point to EthTSyn_PrevTimeStampInfoOfSwitchTimeSyncInfo */
typedef P2VAR(EthTSyn_SwtTimeSync_TimestampInfoStructType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PrevTimeStampInfoOfSwitchTimeSyncInfoPtrType;

/**   \brief  type used to point to EthTSyn_SwtSyncStateOfSwitchTimeSyncInfo */
typedef P2VAR(EthTSyn_SyncStateType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtSyncStateOfSwitchTimeSyncInfoPtrType;

/**   \brief  type used to point to EthTSyn_TimeStampInfoOfSwitchTimeSyncInfo */
typedef P2VAR(EthTSyn_SwtTimeSync_TimestampInfoStructType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TimeStampInfoOfSwitchTimeSyncInfoPtrType;

/**   \brief  type used to point to EthTSyn_SwtMgmtRcvdMsgBuf */
typedef P2VAR(EthTSyn_SwtMgmtRcvdMsgBufType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtRcvdMsgBufPtrType;

/**   \brief  type used to point to EthTSyn_SwtMgmtRxBufQueueCurrProcIdx */
typedef P2VAR(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtRxBufQueueCurrProcIdxPtrType;

/**   \brief  type used to point to EthTSyn_SwtMgmtRxBufQueueFreeIdx */
typedef P2VAR(EthTSyn_SwtMgmtRxBufQueueFreeIdxType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtRxBufQueueFreeIdxPtrType;

/**   \brief  type used to point to EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx */
typedef P2VAR(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxPtrType;

/**   \brief  type used to point to EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx */
typedef P2VAR(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxPtrType;

/**   \brief  type used to point to EthTSyn_SwtTimeSyncRateRegulatorCfg */
typedef P2CONST(EthTSyn_SwtTimeSyncRateRegulatorCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_SwtTimeSyncRateRegulatorCfgPtrType;

/**   \brief  type used to point to EthTSyn_SyncReceiveSm */
typedef P2VAR(EthTSyn_SyncReceiveSmType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SyncReceiveSmPtrType;

/**   \brief  type used to point to EthTSyn_SyncSendSm */
typedef P2VAR(EthTSyn_SyncSendSmType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SyncSendSmPtrType;

/**   \brief  type used to point to EthTSyn_SystemState */
typedef P2VAR(EthTSyn_SystemStateType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SystemStatePtrType;

/**   \brief  type used to point to EthTSyn_TimeBaseUpdateCounter */
typedef P2VAR(EthTSyn_TimeBaseUpdateCounterType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TimeBaseUpdateCounterPtrType;

/**   \brief  type used to point to EthTSyn_TimeDomain */
typedef P2CONST(EthTSyn_TimeDomainType, TYPEDEF, ETHTSYN_CONST) EthTSyn_TimeDomainPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidMasterCfg */
typedef P2CONST(EthTSyn_TimeValidMasterCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_TimeValidMasterCfgPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidMasterData */
typedef P2VAR(EthTSyn_TimeValidMasterDataType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TimeValidMasterDataPtrType;

/**   \brief  type used to point to EthTSyn_PreciseOriginTimestampOfTimeValidMasterData */
typedef P2VAR(StbM_TimeStampShortType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PreciseOriginTimestampOfTimeValidMasterDataPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidPdReqCfg */
typedef P2CONST(EthTSyn_TimeValidPdReqCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_TimeValidPdReqCfgPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidPdReqData */
typedef P2VAR(EthTSyn_TimeValidPdReqDataType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TimeValidPdReqDataPtrType;

/**   \brief  type used to point to EthTSyn_PdReqRcvdTsOfTimeValidPdReqData */
typedef P2VAR(StbM_TimeStampShortType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PdReqRcvdTsOfTimeValidPdReqDataPtrType;

/**   \brief  type used to point to EthTSyn_PdRespSentTsOfTimeValidPdReqData */
typedef P2VAR(StbM_TimeStampShortType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PdRespSentTsOfTimeValidPdReqDataPtrType;

/**   \brief  type used to point to EthTSyn_RefTimeGlobalOfTimeValidPdReqData */
typedef P2VAR(StbM_TimeStampShortType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_RefTimeGlobalOfTimeValidPdReqDataPtrType;

/**   \brief  type used to point to EthTSyn_RefTimeVltOfTimeValidPdReqData */
typedef P2VAR(StbM_VirtualLocalTimeType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_RefTimeVltOfTimeValidPdReqDataPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidPdRespCfg */
typedef P2CONST(EthTSyn_TimeValidPdRespCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_TimeValidPdRespCfgPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidPdRespData */
typedef P2VAR(EthTSyn_TimeValidPdRespDataType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TimeValidPdRespDataPtrType;

/**   \brief  type used to point to EthTSyn_RefTimeGlobalOfTimeValidPdRespData */
typedef P2VAR(StbM_TimeStampShortType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_RefTimeGlobalOfTimeValidPdRespDataPtrType;

/**   \brief  type used to point to EthTSyn_RefTimeVltOfTimeValidPdRespData */
typedef P2VAR(StbM_VirtualLocalTimeType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_RefTimeVltOfTimeValidPdRespDataPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidSlaveCfg */
typedef P2CONST(EthTSyn_TimeValidSlaveCfgType, TYPEDEF, ETHTSYN_CONST) EthTSyn_TimeValidSlaveCfgPtrType;

/**   \brief  type used to point to EthTSyn_TimeValidSlaveData */
typedef P2VAR(EthTSyn_TimeValidSlaveDataType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TimeValidSlaveDataPtrType;

/**   \brief  type used to point to EthTSyn_PreciseOriginTimestampOfTimeValidSlaveData */
typedef P2VAR(StbM_TimeStampShortType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_PreciseOriginTimestampOfTimeValidSlaveDataPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCRootValueTypes  EthTSyn Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in EthTSyn_PCConfig */
typedef struct sEthTSyn_PCConfigType
{
  EthTSyn_AnnounceInfoPtrType AnnounceInfoOfPCConfig;  /**< the pointer to EthTSyn_AnnounceInfo */
  EthTSyn_AnnounceReceiveSmPtrType AnnounceReceiveSmOfPCConfig;  /**< the pointer to EthTSyn_AnnounceReceiveSm */
  EthTSyn_AnnounceSendSmPtrType AnnounceSendSmOfPCConfig;  /**< the pointer to EthTSyn_AnnounceSendSm */
  EthTSyn_AnnounceSendSmCfgPtrType AnnounceSendSmCfgOfPCConfig;  /**< the pointer to EthTSyn_AnnounceSendSmCfg */
  EthTSyn_CtrlPtrType CtrlOfPCConfig;  /**< the pointer to EthTSyn_Ctrl */
  EthTSyn_CtrlStatePtrType CtrlStateOfPCConfig;  /**< the pointer to EthTSyn_CtrlState */
  EthTSyn_DestinationMacPtrType DestinationMacOfPCConfig;  /**< the pointer to EthTSyn_DestinationMac */
  EthTSyn_FollowUpDataIdListPtrType FollowUpDataIdListOfPCConfig;  /**< the pointer to EthTSyn_FollowUpDataIdList */
  EthTSyn_MasterPortPtrType MasterPortOfPCConfig;  /**< the pointer to EthTSyn_MasterPort */
  EthTSyn_MasterPortIdentityPtrType MasterPortIdentityOfPCConfig;  /**< the pointer to EthTSyn_MasterPortIdentity */
  EthTSyn_OffsetTimeDomainPtrType OffsetTimeDomainOfPCConfig;  /**< the pointer to EthTSyn_OffsetTimeDomain */
  EthTSyn_OfsCorrDurationInSyncCyclesPtrType OfsCorrDurationInSyncCyclesOfPCConfig;  /**< the pointer to EthTSyn_OfsCorrDurationInSyncCycles */
  EthTSyn_PdelayConfigPtrType PdelayConfigOfPCConfig;  /**< the pointer to EthTSyn_PdelayConfig */
  EthTSyn_PdelayInfoPtrType PdelayInfoOfPCConfig;  /**< the pointer to EthTSyn_PdelayInfo */
  EthTSyn_PdelayInitiatorPtrType PdelayInitiatorOfPCConfig;  /**< the pointer to EthTSyn_PdelayInitiator */
  EthTSyn_PdelayReqSmPtrType PdelayReqSmOfPCConfig;  /**< the pointer to EthTSyn_PdelayReqSm */
  EthTSyn_PdelayRespSmPtrType PdelayRespSmOfPCConfig;  /**< the pointer to EthTSyn_PdelayRespSm */
  EthTSyn_PdelayResponderPtrType PdelayResponderOfPCConfig;  /**< the pointer to EthTSyn_PdelayResponder */
  EthTSyn_PhysPortPtrType PhysPortOfPCConfig;  /**< the pointer to EthTSyn_PhysPort */
  EthTSyn_PhysPortCfgPtrType PhysPortCfgOfPCConfig;  /**< the pointer to EthTSyn_PhysPortCfg */
  EthTSyn_PortPtrType PortOfPCConfig;  /**< the pointer to EthTSyn_Port */
  EthTSyn_PortIndPtrType PortIndOfPCConfig;  /**< the pointer to EthTSyn_PortInd */
  EthTSyn_PortSyncSendSmPtrType PortSyncSendSmOfPCConfig;  /**< the pointer to EthTSyn_PortSyncSendSm */
  EthTSyn_RateMeasurementPtrType RateMeasurementOfPCConfig;  /**< the pointer to EthTSyn_RateMeasurement */
  EthTSyn_SlavePortPtrType SlavePortOfPCConfig;  /**< the pointer to EthTSyn_SlavePort */
  EthTSyn_SlaveSwitchIdxListPtrType SlaveSwitchIdxListOfPCConfig;  /**< the pointer to EthTSyn_SlaveSwitchIdxList */
  EthTSyn_SwitchPortMgmtPtrType SwitchPortMgmtOfPCConfig;  /**< the pointer to EthTSyn_SwitchPortMgmt */
  EthTSyn_SwitchSyncFrameCfgPtrType SwitchSyncFrameCfgOfPCConfig;  /**< the pointer to EthTSyn_SwitchSyncFrameCfg */
  EthTSyn_SwitchSyncFrameInfoPtrType SwitchSyncFrameInfoOfPCConfig;  /**< the pointer to EthTSyn_SwitchSyncFrameInfo */
  EthTSyn_SwitchSyncFrameTxFrameInfoPtrType SwitchSyncFrameTxFrameInfoOfPCConfig;  /**< the pointer to EthTSyn_SwitchSyncFrameTxFrameInfo */
  EthTSyn_SwitchTimeSyncCfgPtrType SwitchTimeSyncCfgOfPCConfig;  /**< the pointer to EthTSyn_SwitchTimeSyncCfg */
  EthTSyn_SwitchTimeSyncInfoPtrType SwitchTimeSyncInfoOfPCConfig;  /**< the pointer to EthTSyn_SwitchTimeSyncInfo */
  EthTSyn_SwtMgmtRcvdMsgBufPtrType SwtMgmtRcvdMsgBufOfPCConfig;  /**< the pointer to EthTSyn_SwtMgmtRcvdMsgBuf */
  EthTSyn_SwtMgmtRxBufQueueCurrProcIdxPtrType SwtMgmtRxBufQueueCurrProcIdxOfPCConfig;  /**< the pointer to EthTSyn_SwtMgmtRxBufQueueCurrProcIdx */
  EthTSyn_SwtMgmtRxBufQueueFreeIdxPtrType SwtMgmtRxBufQueueFreeIdxOfPCConfig;  /**< the pointer to EthTSyn_SwtMgmtRxBufQueueFreeIdx */
  EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxPtrType SwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig;  /**< the pointer to EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx */
  EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxPtrType SwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig;  /**< the pointer to EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx */
  EthTSyn_SwtTimeSyncRateRegulatorCfgPtrType SwtTimeSyncRateRegulatorCfgOfPCConfig;  /**< the pointer to EthTSyn_SwtTimeSyncRateRegulatorCfg */
  EthTSyn_SyncReceiveSmPtrType SyncReceiveSmOfPCConfig;  /**< the pointer to EthTSyn_SyncReceiveSm */
  EthTSyn_SyncSendSmPtrType SyncSendSmOfPCConfig;  /**< the pointer to EthTSyn_SyncSendSm */
  EthTSyn_SystemStatePtrType SystemStateOfPCConfig;  /**< the pointer to EthTSyn_SystemState */
  EthTSyn_TimeBaseUpdateCounterPtrType TimeBaseUpdateCounterOfPCConfig;  /**< the pointer to EthTSyn_TimeBaseUpdateCounter */
  EthTSyn_TimeDomainPtrType TimeDomainOfPCConfig;  /**< the pointer to EthTSyn_TimeDomain */
  EthTSyn_TimeValidMasterCfgPtrType TimeValidMasterCfgOfPCConfig;  /**< the pointer to EthTSyn_TimeValidMasterCfg */
  EthTSyn_TimeValidMasterDataPtrType TimeValidMasterDataOfPCConfig;  /**< the pointer to EthTSyn_TimeValidMasterData */
  EthTSyn_TimeValidPdReqCfgPtrType TimeValidPdReqCfgOfPCConfig;  /**< the pointer to EthTSyn_TimeValidPdReqCfg */
  EthTSyn_TimeValidPdReqDataPtrType TimeValidPdReqDataOfPCConfig;  /**< the pointer to EthTSyn_TimeValidPdReqData */
  EthTSyn_TimeValidPdRespCfgPtrType TimeValidPdRespCfgOfPCConfig;  /**< the pointer to EthTSyn_TimeValidPdRespCfg */
  EthTSyn_TimeValidPdRespDataPtrType TimeValidPdRespDataOfPCConfig;  /**< the pointer to EthTSyn_TimeValidPdRespData */
  EthTSyn_TimeValidSlaveCfgPtrType TimeValidSlaveCfgOfPCConfig;  /**< the pointer to EthTSyn_TimeValidSlaveCfg */
  EthTSyn_TimeValidSlaveDataPtrType TimeValidSlaveDataOfPCConfig;  /**< the pointer to EthTSyn_TimeValidSlaveData */
  EthTSyn_SizeOfAnnounceInfoType SizeOfAnnounceInfoOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_AnnounceInfo */
  EthTSyn_SizeOfAnnounceSendSmCfgType SizeOfAnnounceSendSmCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_AnnounceSendSmCfg */
  EthTSyn_SizeOfCtrlType SizeOfCtrlOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_Ctrl */
  EthTSyn_SizeOfDestinationMacType SizeOfDestinationMacOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_DestinationMac */
  EthTSyn_SizeOfFollowUpDataIdListType SizeOfFollowUpDataIdListOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_FollowUpDataIdList */
  EthTSyn_SizeOfMasterPortType SizeOfMasterPortOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_MasterPort */
  EthTSyn_SizeOfMasterPortIdentityType SizeOfMasterPortIdentityOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_MasterPortIdentity */
  EthTSyn_SizeOfOffsetTimeDomainType SizeOfOffsetTimeDomainOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_OffsetTimeDomain */
  EthTSyn_SizeOfPdelayConfigType SizeOfPdelayConfigOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_PdelayConfig */
  EthTSyn_SizeOfPdelayInitiatorType SizeOfPdelayInitiatorOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_PdelayInitiator */
  EthTSyn_SizeOfPdelayReqSmType SizeOfPdelayReqSmOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_PdelayReqSm */
  EthTSyn_SizeOfPdelayRespSmType SizeOfPdelayRespSmOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_PdelayRespSm */
  EthTSyn_SizeOfPdelayResponderType SizeOfPdelayResponderOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_PdelayResponder */
  EthTSyn_SizeOfPhysPortCfgType SizeOfPhysPortCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_PhysPortCfg */
  EthTSyn_SizeOfPortType SizeOfPortOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_Port */
  EthTSyn_SizeOfPortIndType SizeOfPortIndOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_PortInd */
  EthTSyn_SizeOfRateMeasurementType SizeOfRateMeasurementOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_RateMeasurement */
  EthTSyn_SizeOfSlavePortType SizeOfSlavePortOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_SlavePort */
  EthTSyn_SizeOfSlaveSwitchIdxListType SizeOfSlaveSwitchIdxListOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_SlaveSwitchIdxList */
  EthTSyn_SizeOfSwitchPortMgmtType SizeOfSwitchPortMgmtOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_SwitchPortMgmt */
  EthTSyn_SizeOfSwitchSyncFrameCfgType SizeOfSwitchSyncFrameCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_SwitchSyncFrameCfg */
  EthTSyn_SizeOfSwitchTimeSyncCfgType SizeOfSwitchTimeSyncCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_SwitchTimeSyncCfg */
  EthTSyn_SizeOfSwtMgmtRcvdMsgBufType SizeOfSwtMgmtRcvdMsgBufOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_SwtMgmtRcvdMsgBuf */
  EthTSyn_SizeOfSwtTimeSyncRateRegulatorCfgType SizeOfSwtTimeSyncRateRegulatorCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_SwtTimeSyncRateRegulatorCfg */
  EthTSyn_SizeOfTimeDomainType SizeOfTimeDomainOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_TimeDomain */
  EthTSyn_SizeOfTimeValidMasterCfgType SizeOfTimeValidMasterCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_TimeValidMasterCfg */
  EthTSyn_SizeOfTimeValidPdReqCfgType SizeOfTimeValidPdReqCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_TimeValidPdReqCfg */
  EthTSyn_SizeOfTimeValidPdRespCfgType SizeOfTimeValidPdRespCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_TimeValidPdRespCfg */
  EthTSyn_SizeOfTimeValidSlaveCfgType SizeOfTimeValidSlaveCfgOfPCConfig;  /**< the number of accomplishable value elements in EthTSyn_TimeValidSlaveCfg */
} EthTSyn_PCConfigType;

typedef EthTSyn_PCConfigType EthTSyn_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access EthTSyn_PCConfig in a symbol based style. */
typedef struct sEthTSyn_PCConfigsType
{
  EthTSyn_PCConfigType Config;  /**< [Config] */
} EthTSyn_PCConfigsType;

/** 
  \}
*/ 



#endif  /* ETHTSYN_GENERATED_COMPLEX_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_GeneratedComplexTypes.h
 *********************************************************************************************************************/

