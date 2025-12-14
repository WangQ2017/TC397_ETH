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
 *              File: EthTSyn_GeneratedSimpleTypes.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef ETHTSYN_GENERATED_SIMPLE_TYPES_H
#define ETHTSYN_GENERATED_SIMPLE_TYPES_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 * GENERATED TYPES (NOT ComStackLib)
 *********************************************************************************************************************/
/**   \brief EthTSyn_TxCrcSecuredEnumType */
typedef enum eEthTSyn_TxCrcSecuredEnumType
{
  ETHTSYN_TX_CRC_SECURED_CRC_NOT_SUPPORTED = 0u,
  ETHTSYN_TX_CRC_SECURED_CRC_SUPPORTED = 1u
} EthTSyn_TxCrcSecuredEnumType;

/**   \brief EthTSyn_RxCrcValidatedEnumType */
typedef enum eEthTSyn_RxCrcValidatedEnumType
{
  ETHTSYN_RX_CRC_VALIDATED_CRC_IGNORED = 0u,
  ETHTSYN_RX_CRC_VALIDATED_CRC_NOT_VALIDATED = 1u,
  ETHTSYN_RX_CRC_VALIDATED_CRC_OPTIONAL = 2u,
  ETHTSYN_RX_CRC_VALIDATED_CRC_VALIDATED = 3u
} EthTSyn_RxCrcValidatedEnumType;

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthTSynPCIterableTypes  EthTSyn Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate EthTSyn_AnnounceInfo */
typedef uint8_least EthTSyn_AnnounceInfoIterType;

/**   \brief  type used to iterate EthTSyn_AnnounceSendSmCfg */
typedef uint8_least EthTSyn_AnnounceSendSmCfgIterType;

/**   \brief  type used to iterate EthTSyn_Ctrl */
typedef uint8_least EthTSyn_CtrlIterType;

/**   \brief  type used to iterate EthTSyn_DestinationMac */
typedef uint8_least EthTSyn_DestinationMacIterType;

/**   \brief  type used to iterate EthTSyn_FollowUpDataIdList */
typedef uint8_least EthTSyn_FollowUpDataIdListIterType;

/**   \brief  type used to iterate EthTSyn_MasterPort */
typedef uint8_least EthTSyn_MasterPortIterType;

/**   \brief  type used to iterate EthTSyn_MasterPortIdentity */
typedef uint8_least EthTSyn_MasterPortIdentityIterType;

/**   \brief  type used to iterate EthTSyn_OffsetTimeDomain */
typedef uint8_least EthTSyn_OffsetTimeDomainIterType;

/**   \brief  type used to iterate EthTSyn_PdelayConfig */
typedef uint8_least EthTSyn_PdelayConfigIterType;

/**   \brief  type used to iterate EthTSyn_PdelayInitiator */
typedef uint8_least EthTSyn_PdelayInitiatorIterType;

/**   \brief  type used to iterate EthTSyn_PdelayReqSm */
typedef uint8_least EthTSyn_PdelayReqSmIterType;

/**   \brief  type used to iterate EthTSyn_PdelayRespSm */
typedef uint8_least EthTSyn_PdelayRespSmIterType;

/**   \brief  type used to iterate EthTSyn_PdelayResponder */
typedef uint8_least EthTSyn_PdelayResponderIterType;

/**   \brief  type used to iterate EthTSyn_PhysPortCfg */
typedef uint8_least EthTSyn_PhysPortCfgIterType;

/**   \brief  type used to iterate EthTSyn_Port */
typedef uint8_least EthTSyn_PortIterType;

/**   \brief  type used to iterate EthTSyn_PortInd */
typedef uint8_least EthTSyn_PortIndIterType;

/**   \brief  type used to iterate EthTSyn_RateMeasurement */
typedef uint8_least EthTSyn_RateMeasurementIterType;

/**   \brief  type used to iterate EthTSyn_SlavePort */
typedef uint8_least EthTSyn_SlavePortIterType;

/**   \brief  type used to iterate EthTSyn_SlaveSwitchIdxList */
typedef uint8_least EthTSyn_SlaveSwitchIdxListIterType;

/**   \brief  type used to iterate EthTSyn_SwitchPortMgmt */
typedef uint8_least EthTSyn_SwitchPortMgmtIterType;

/**   \brief  type used to iterate EthTSyn_SwitchSyncFrameCfg */
typedef uint8_least EthTSyn_SwitchSyncFrameCfgIterType;

/**   \brief  type used to iterate EthTSyn_SwitchTimeSyncCfg */
typedef uint8_least EthTSyn_SwitchTimeSyncCfgIterType;

/**   \brief  type used to iterate EthTSyn_SwtMgmtRcvdMsgBuf */
typedef uint8_least EthTSyn_SwtMgmtRcvdMsgBufIterType;

/**   \brief  type used to iterate EthTSyn_SwtTimeSyncRateRegulatorCfg */
typedef uint8_least EthTSyn_SwtTimeSyncRateRegulatorCfgIterType;

/**   \brief  type used to iterate EthTSyn_TimeDomain */
typedef uint8_least EthTSyn_TimeDomainIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidMasterCfg */
typedef uint8_least EthTSyn_TimeValidMasterCfgIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidPdReqCfg */
typedef uint8_least EthTSyn_TimeValidPdReqCfgIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidPdRespCfg */
typedef uint8_least EthTSyn_TimeValidPdRespCfgIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidSlaveCfg */
typedef uint8_least EthTSyn_TimeValidSlaveCfgIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCIterableTypesWithSizeRelations  EthTSyn Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate EthTSyn_AnnounceReceiveSm */
typedef EthTSyn_AnnounceInfoIterType EthTSyn_AnnounceReceiveSmIterType;

/**   \brief  type used to iterate EthTSyn_AnnounceSendSm */
typedef EthTSyn_AnnounceSendSmCfgIterType EthTSyn_AnnounceSendSmIterType;

/**   \brief  type used to iterate EthTSyn_CtrlState */
typedef EthTSyn_CtrlIterType EthTSyn_CtrlStateIterType;

/**   \brief  type used to iterate EthTSyn_OfsCorrDurationInSyncCycles */
typedef EthTSyn_SwtTimeSyncRateRegulatorCfgIterType EthTSyn_OfsCorrDurationInSyncCyclesIterType;

/**   \brief  type used to iterate EthTSyn_PdelayInfo */
typedef EthTSyn_PdelayConfigIterType EthTSyn_PdelayInfoIterType;

/**   \brief  type used to iterate EthTSyn_PhysPort */
typedef EthTSyn_PhysPortCfgIterType EthTSyn_PhysPortIterType;

/**   \brief  type used to iterate EthTSyn_PortSyncSendSm */
typedef EthTSyn_MasterPortIterType EthTSyn_PortSyncSendSmIterType;

/**   \brief  type used to iterate EthTSyn_SwitchSyncFrameInfo */
typedef EthTSyn_SwitchSyncFrameCfgIterType EthTSyn_SwitchSyncFrameInfoIterType;

/**   \brief  type used to iterate EthTSyn_SwitchSyncFrameTxFrameInfo */
typedef EthTSyn_SwitchSyncFrameCfgIterType EthTSyn_SwitchSyncFrameTxFrameInfoIterType;

/**   \brief  type used to iterate EthTSyn_SwitchTimeSyncInfo */
typedef EthTSyn_SwitchTimeSyncCfgIterType EthTSyn_SwitchTimeSyncInfoIterType;

/**   \brief  type used to iterate EthTSyn_SyncReceiveSm */
typedef EthTSyn_SlavePortIterType EthTSyn_SyncReceiveSmIterType;

/**   \brief  type used to iterate EthTSyn_SyncSendSm */
typedef EthTSyn_MasterPortIterType EthTSyn_SyncSendSmIterType;

/**   \brief  type used to iterate EthTSyn_SystemState */
typedef EthTSyn_TimeDomainIterType EthTSyn_SystemStateIterType;

/**   \brief  type used to iterate EthTSyn_TimeBaseUpdateCounter */
typedef EthTSyn_TimeDomainIterType EthTSyn_TimeBaseUpdateCounterIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidMasterData */
typedef EthTSyn_TimeValidMasterCfgIterType EthTSyn_TimeValidMasterDataIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidPdReqData */
typedef EthTSyn_TimeValidPdReqCfgIterType EthTSyn_TimeValidPdReqDataIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidPdRespData */
typedef EthTSyn_TimeValidPdRespCfgIterType EthTSyn_TimeValidPdRespDataIterType;

/**   \brief  type used to iterate EthTSyn_TimeValidSlaveData */
typedef EthTSyn_TimeValidSlaveCfgIterType EthTSyn_TimeValidSlaveDataIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCValueTypes  EthTSyn Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for EthTSyn_AnnounceAllowedRxDelayOfAnnounceInfo */
typedef uint8 EthTSyn_AnnounceAllowedRxDelayOfAnnounceInfoType;

/**   \brief  value based type definition for EthTSyn_MaxeStepsRemovedOfAnnounceInfo */
typedef uint8 EthTSyn_MaxeStepsRemovedOfAnnounceInfoType;

/**   \brief  value based type definition for EthTSyn_AnnounceCycleTimerOfAnnounceSendSm */
typedef uint32 EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType;

/**   \brief  value based type definition for EthTSyn_StateOfAnnounceSendSm */
typedef uint8 EthTSyn_StateOfAnnounceSendSmType;

/**   \brief  value based type definition for EthTSyn_AnnounceTxCycleOfAnnounceSendSmCfg */
typedef uint8 EthTSyn_AnnounceTxCycleOfAnnounceSendSmCfgType;

/**   \brief  value based type definition for EthTSyn_EthIfCtrlIdxOfCtrl */
typedef uint8 EthTSyn_EthIfCtrlIdxOfCtrlType;

/**   \brief  value based type definition for EthTSyn_PortIndEndIdxOfCtrl */
typedef uint8 EthTSyn_PortIndEndIdxOfCtrlType;

/**   \brief  value based type definition for EthTSyn_PortIndStartIdxOfCtrl */
typedef uint8 EthTSyn_PortIndStartIdxOfCtrlType;

/**   \brief  value based type definition for EthTSyn_DestinationMac */
typedef uint8 EthTSyn_DestinationMacType;

/**   \brief  value based type definition for EthTSyn_FollowUpDataIdList */
typedef uint8 EthTSyn_FollowUpDataIdListType;

/**   \brief  value based type definition for EthTSyn_AnnounceSendSmCfgIdxOfMasterPort */
typedef uint8 EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_AnnounceSendSmCfgUsedOfMasterPort */
typedef boolean EthTSyn_AnnounceSendSmCfgUsedOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_CrcTimeFlagsOfMasterPort */
typedef uint8 EthTSyn_CrcTimeFlagsOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_CyclicMsgResumeCntOfMasterPort */
typedef uint8 EthTSyn_CyclicMsgResumeCntOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_FollowUpMsgLengthOfMasterPort */
typedef uint8 EthTSyn_FollowUpMsgLengthOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_ImmediateTimeSyncOfMasterPort */
typedef boolean EthTSyn_ImmediateTimeSyncOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_OfsSubTlvOfMasterPort */
typedef boolean EthTSyn_OfsSubTlvOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_PortIdxOfMasterPort */
typedef uint8 EthTSyn_PortIdxOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_StatusSubTlvOfMasterPort */
typedef boolean EthTSyn_StatusSubTlvOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_SyncLogMsgIntervalOfMasterPort */
typedef sint8 EthTSyn_SyncLogMsgIntervalOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_SyncSendIntervalOfMasterPort */
typedef uint8 EthTSyn_SyncSendIntervalOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_TimeSubTlvOfMasterPort */
typedef boolean EthTSyn_TimeSubTlvOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_UserDataSubTlvOfMasterPort */
typedef boolean EthTSyn_UserDataSubTlvOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_ClockIdentityOfMasterPortIdentity */
typedef uint8 EthTSyn_ClockIdentityOfMasterPortIdentityType;

/**   \brief  value based type definition for EthTSyn_IdOfOffsetTimeDomain */
typedef uint8 EthTSyn_IdOfOffsetTimeDomainType;

/**   \brief  value based type definition for EthTSyn_CounterOfOfsCorrDurationInSyncCycles */
typedef uint8 EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType;

/**   \brief  value based type definition for EthTSyn_RestartedOfOfsCorrDurationInSyncCycles */
typedef boolean EthTSyn_RestartedOfOfsCorrDurationInSyncCyclesType;

/**   \brief  value based type definition for EthTSyn_AlwaysAsCapableOfPdelayConfig */
typedef boolean EthTSyn_AlwaysAsCapableOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_InitialPdelayNsOfPdelayConfig */
typedef uint16 EthTSyn_InitialPdelayNsOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_PdelayInitiatorIdxOfPdelayConfig */
typedef uint8 EthTSyn_PdelayInitiatorIdxOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_PdelayInitiatorUsedOfPdelayConfig */
typedef boolean EthTSyn_PdelayInitiatorUsedOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_PdelayResponderIdxOfPdelayConfig */
typedef uint8 EthTSyn_PdelayResponderIdxOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_PdelayResponderUsedOfPdelayConfig */
typedef boolean EthTSyn_PdelayResponderUsedOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_PortIdxOfPdelayConfig */
typedef uint8 EthTSyn_PortIdxOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_UseStaticPdelayOfPdelayConfig */
typedef boolean EthTSyn_UseStaticPdelayOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_AsCapableOfPdelayInfo */
typedef boolean EthTSyn_AsCapableOfPdelayInfoType;

/**   \brief  value based type definition for EthTSyn_UseAverageOfPdelayInfo */
typedef boolean EthTSyn_UseAverageOfPdelayInfoType;

/**   \brief  value based type definition for EthTSyn_AllowedLostResponsesOfPdelayInitiator */
typedef uint8 EthTSyn_AllowedLostResponsesOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_AverageWeightOfPdelayInitiator */
typedef uint8 EthTSyn_AverageWeightOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_LogMessageIntervalOfPdelayInitiator */
typedef sint8 EthTSyn_LogMessageIntervalOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_PdelayReqSmIdxOfPdelayInitiator */
typedef uint8 EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_PdelayThresholdOfPdelayInitiator */
typedef uint32 EthTSyn_PdelayThresholdOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_RespRespFollowUpTimeoutOfPdelayInitiator */
typedef uint8 EthTSyn_RespRespFollowUpTimeoutOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_TxIntervalMfOfPdelayInitiator */
typedef uint8 EthTSyn_TxIntervalMfOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_PdelayRespSmIdxOfPdelayResponder */
typedef uint8 EthTSyn_PdelayRespSmIdxOfPdelayResponderType;

/**   \brief  value based type definition for EthTSyn_DebounceTimerOfPhysPort */
typedef uint32 EthTSyn_DebounceTimerOfPhysPortType;

/**   \brief  value based type definition for EthTSyn_DebounceTimeOfPhysPortCfg */
typedef uint8 EthTSyn_DebounceTimeOfPhysPortCfgType;

/**   \brief  value based type definition for EthTSyn_CtrlIdxOfPort */
typedef uint8 EthTSyn_CtrlIdxOfPortType;

/**   \brief  value based type definition for EthTSyn_FramePrioOfPort */
typedef uint8 EthTSyn_FramePrioOfPortType;

/**   \brief  value based type definition for EthTSyn_MasterPortIdxOfPort */
typedef uint8 EthTSyn_MasterPortIdxOfPortType;

/**   \brief  value based type definition for EthTSyn_MasterPortUsedOfPort */
typedef boolean EthTSyn_MasterPortUsedOfPortType;

/**   \brief  value based type definition for EthTSyn_NumberOfPort */
typedef uint8 EthTSyn_NumberOfPortType;

/**   \brief  value based type definition for EthTSyn_PdelayConfigIdxOfPort */
typedef uint8 EthTSyn_PdelayConfigIdxOfPortType;

/**   \brief  value based type definition for EthTSyn_PdelayConfigUsedOfPort */
typedef boolean EthTSyn_PdelayConfigUsedOfPortType;

/**   \brief  value based type definition for EthTSyn_PhysPortCfgIdxOfPort */
typedef uint8 EthTSyn_PhysPortCfgIdxOfPortType;

/**   \brief  value based type definition for EthTSyn_SlavePortIdxOfPort */
typedef uint8 EthTSyn_SlavePortIdxOfPortType;

/**   \brief  value based type definition for EthTSyn_SlavePortUsedOfPort */
typedef boolean EthTSyn_SlavePortUsedOfPortType;

/**   \brief  value based type definition for EthTSyn_StbMTimeSrcEqualOfPort */
typedef boolean EthTSyn_StbMTimeSrcEqualOfPortType;

/**   \brief  value based type definition for EthTSyn_SwitchPortMgmtIdxOfPort */
typedef uint8 EthTSyn_SwitchPortMgmtIdxOfPortType;

/**   \brief  value based type definition for EthTSyn_SwitchPortMgmtUsedOfPort */
typedef boolean EthTSyn_SwitchPortMgmtUsedOfPortType;

/**   \brief  value based type definition for EthTSyn_TimeDomainIdxOfPort */
typedef uint8 EthTSyn_TimeDomainIdxOfPortType;

/**   \brief  value based type definition for EthTSyn_PortInd */
typedef uint8 EthTSyn_PortIndType;

/**   \brief  value based type definition for EthTSyn_StateOfPortSyncSendSm */
typedef uint8 EthTSyn_StateOfPortSyncSendSmType;

/**   \brief  value based type definition for EthTSyn_SyncTxConfCalledOfPortSyncSendSm */
typedef boolean EthTSyn_SyncTxConfCalledOfPortSyncSendSmType;

/**   \brief  value based type definition for EthTSyn_TxBufIdxOfPortSyncSendSm */
typedef uint8 EthTSyn_TxBufIdxOfPortSyncSendSmType;

/**   \brief  value based type definition for EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurement */
typedef float64 EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurementType;

/**   \brief  value based type definition for EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurement */
typedef float64 EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurementType;

/**   \brief  value based type definition for EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurement */
typedef uint8 EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType;

/**   \brief  value based type definition for EthTSyn_ActiveOfRateMeasurement */
typedef boolean EthTSyn_ActiveOfRateMeasurementType;

/**   \brief  value based type definition for EthTSyn_SizeOfAnnounceInfo */
typedef uint8 EthTSyn_SizeOfAnnounceInfoType;

/**   \brief  value based type definition for EthTSyn_SizeOfAnnounceReceiveSm */
typedef uint8 EthTSyn_SizeOfAnnounceReceiveSmType;

/**   \brief  value based type definition for EthTSyn_SizeOfAnnounceSendSm */
typedef uint8 EthTSyn_SizeOfAnnounceSendSmType;

/**   \brief  value based type definition for EthTSyn_SizeOfAnnounceSendSmCfg */
typedef uint8 EthTSyn_SizeOfAnnounceSendSmCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfCtrl */
typedef uint8 EthTSyn_SizeOfCtrlType;

/**   \brief  value based type definition for EthTSyn_SizeOfCtrlState */
typedef uint8 EthTSyn_SizeOfCtrlStateType;

/**   \brief  value based type definition for EthTSyn_SizeOfDestinationMac */
typedef uint8 EthTSyn_SizeOfDestinationMacType;

/**   \brief  value based type definition for EthTSyn_SizeOfFollowUpDataIdList */
typedef uint8 EthTSyn_SizeOfFollowUpDataIdListType;

/**   \brief  value based type definition for EthTSyn_SizeOfMasterPort */
typedef uint8 EthTSyn_SizeOfMasterPortType;

/**   \brief  value based type definition for EthTSyn_SizeOfMasterPortIdentity */
typedef uint8 EthTSyn_SizeOfMasterPortIdentityType;

/**   \brief  value based type definition for EthTSyn_SizeOfOffsetTimeDomain */
typedef uint8 EthTSyn_SizeOfOffsetTimeDomainType;

/**   \brief  value based type definition for EthTSyn_SizeOfOfsCorrDurationInSyncCycles */
typedef uint8 EthTSyn_SizeOfOfsCorrDurationInSyncCyclesType;

/**   \brief  value based type definition for EthTSyn_SizeOfPdelayConfig */
typedef uint8 EthTSyn_SizeOfPdelayConfigType;

/**   \brief  value based type definition for EthTSyn_SizeOfPdelayInfo */
typedef uint8 EthTSyn_SizeOfPdelayInfoType;

/**   \brief  value based type definition for EthTSyn_SizeOfPdelayInitiator */
typedef uint8 EthTSyn_SizeOfPdelayInitiatorType;

/**   \brief  value based type definition for EthTSyn_SizeOfPdelayReqSm */
typedef uint8 EthTSyn_SizeOfPdelayReqSmType;

/**   \brief  value based type definition for EthTSyn_SizeOfPdelayRespSm */
typedef uint8 EthTSyn_SizeOfPdelayRespSmType;

/**   \brief  value based type definition for EthTSyn_SizeOfPdelayResponder */
typedef uint8 EthTSyn_SizeOfPdelayResponderType;

/**   \brief  value based type definition for EthTSyn_SizeOfPhysPort */
typedef uint8 EthTSyn_SizeOfPhysPortType;

/**   \brief  value based type definition for EthTSyn_SizeOfPhysPortCfg */
typedef uint8 EthTSyn_SizeOfPhysPortCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfPort */
typedef uint8 EthTSyn_SizeOfPortType;

/**   \brief  value based type definition for EthTSyn_SizeOfPortInd */
typedef uint8 EthTSyn_SizeOfPortIndType;

/**   \brief  value based type definition for EthTSyn_SizeOfPortSyncSendSm */
typedef uint8 EthTSyn_SizeOfPortSyncSendSmType;

/**   \brief  value based type definition for EthTSyn_SizeOfRateMeasurement */
typedef uint8 EthTSyn_SizeOfRateMeasurementType;

/**   \brief  value based type definition for EthTSyn_SizeOfSlavePort */
typedef uint8 EthTSyn_SizeOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_SizeOfSlaveSwitchIdxList */
typedef uint8 EthTSyn_SizeOfSlaveSwitchIdxListType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwitchPortMgmt */
typedef uint8 EthTSyn_SizeOfSwitchPortMgmtType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_SizeOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwitchSyncFrameInfo */
typedef uint8 EthTSyn_SizeOfSwitchSyncFrameInfoType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwitchSyncFrameTxFrameInfo */
typedef uint8 EthTSyn_SizeOfSwitchSyncFrameTxFrameInfoType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_SizeOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwitchTimeSyncInfo */
typedef uint8 EthTSyn_SizeOfSwitchTimeSyncInfoType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwtMgmtRcvdMsgBuf */
typedef uint8 EthTSyn_SizeOfSwtMgmtRcvdMsgBufType;

/**   \brief  value based type definition for EthTSyn_SizeOfSwtTimeSyncRateRegulatorCfg */
typedef uint8 EthTSyn_SizeOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfSyncReceiveSm */
typedef uint8 EthTSyn_SizeOfSyncReceiveSmType;

/**   \brief  value based type definition for EthTSyn_SizeOfSyncSendSm */
typedef uint8 EthTSyn_SizeOfSyncSendSmType;

/**   \brief  value based type definition for EthTSyn_SizeOfSystemState */
typedef uint8 EthTSyn_SizeOfSystemStateType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeBaseUpdateCounter */
typedef uint8 EthTSyn_SizeOfTimeBaseUpdateCounterType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeDomain */
typedef uint8 EthTSyn_SizeOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidMasterCfg */
typedef uint8 EthTSyn_SizeOfTimeValidMasterCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidMasterData */
typedef uint8 EthTSyn_SizeOfTimeValidMasterDataType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidPdReqCfg */
typedef uint8 EthTSyn_SizeOfTimeValidPdReqCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidPdReqData */
typedef uint8 EthTSyn_SizeOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidPdRespCfg */
typedef uint8 EthTSyn_SizeOfTimeValidPdRespCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidPdRespData */
typedef uint8 EthTSyn_SizeOfTimeValidPdRespDataType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidSlaveCfg */
typedef uint8 EthTSyn_SizeOfTimeValidSlaveCfgType;

/**   \brief  value based type definition for EthTSyn_SizeOfTimeValidSlaveData */
typedef uint8 EthTSyn_SizeOfTimeValidSlaveDataType;

/**   \brief  value based type definition for EthTSyn_AnnounceInfoIdxOfSlavePort */
typedef uint8 EthTSyn_AnnounceInfoIdxOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_AnnounceInfoUsedOfSlavePort */
typedef boolean EthTSyn_AnnounceInfoUsedOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_CrcFlagsRxValidatedOfSlavePort */
typedef uint8 EthTSyn_CrcFlagsRxValidatedOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_FollowUpAllowedRxDelayOfSlavePort */
typedef uint8 EthTSyn_FollowUpAllowedRxDelayOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_MasterPortIdentityIdxOfSlavePort */
typedef uint8 EthTSyn_MasterPortIdentityIdxOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_MasterPortIdentityUsedOfSlavePort */
typedef boolean EthTSyn_MasterPortIdentityUsedOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_PortIdxOfSlavePort */
typedef uint8 EthTSyn_PortIdxOfSlavePortType;

/**   \brief  value based type definition for EthTSyn_SlaveSwitchIdxList */
typedef uint8 EthTSyn_SlaveSwitchIdxListType;

/**   \brief  value based type definition for EthTSyn_PortIdxOfSwitchPortMgmt */
typedef uint8 EthTSyn_PortIdxOfSwitchPortMgmtType;

/**   \brief  value based type definition for EthTSyn_SwitchIdxOfSwitchPortMgmt */
typedef uint8 EthTSyn_SwitchIdxOfSwitchPortMgmtType;

/**   \brief  value based type definition for EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_FramePrioOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_FramePrioOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_MgmtPortSwitchPortIdxOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_MgmtPortSwitchPortIdxOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_PortIdxOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_PortIdxOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_SyncTxIntervalOfSwitchSyncFrameCfg */
typedef uint8 EthTSyn_SyncTxIntervalOfSwitchSyncFrameCfgType;

/**   \brief  value based type definition for EthTSyn_SequenceIdOfSwitchSyncFrameInfo */
typedef uint16 EthTSyn_SequenceIdOfSwitchSyncFrameInfoType;

/**   \brief  value based type definition for EthTSyn_StateOfSwitchSyncFrameInfo */
typedef uint8 EthTSyn_StateOfSwitchSyncFrameInfoType;

/**   \brief  value based type definition for EthTSyn_SyncTxCntOfSwitchSyncFrameInfo */
typedef uint32 EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType;

/**   \brief  value based type definition for EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfo */
typedef uint8 EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType;

/**   \brief  value based type definition for EthTSyn_ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg */
typedef boolean EthTSyn_ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_EthIfSwitchIdxOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_EthIfSwitchIdxOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_MaxOutOfSyncCntOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_MaxOutOfSyncCntOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SlaveSwitchIdxListUsedOfSwitchTimeSyncCfg */
typedef boolean EthTSyn_SlaveSwitchIdxListUsedOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg */
typedef boolean EthTSyn_SwitchSyncFrameCfgUsedOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SyncEventTimeoutOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_SyncEventTimeoutOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_SyncPrecisionLimitNsOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_SyncPrecisionLimitNsOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfg */
typedef uint8 EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType;

/**   \brief  value based type definition for EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfo */
typedef sint64 EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType;

/**   \brief  value based type definition for EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfo */
typedef sint64 EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType;

/**   \brief  value based type definition for EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfo */
typedef uint8 EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType;

/**   \brief  value based type definition for EthTSyn_StateOfSwitchTimeSyncInfo */
typedef uint8 EthTSyn_StateOfSwitchTimeSyncInfoType;

/**   \brief  value based type definition for EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfo */
typedef uint32 EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType;

/**   \brief  value based type definition for EthTSyn_WasSyncReachedOfSwitchTimeSyncInfo */
typedef boolean EthTSyn_WasSyncReachedOfSwitchTimeSyncInfoType;

/**   \brief  value based type definition for EthTSyn_SwtMgmtRcvdMsgBuf */
typedef uint8 EthTSyn_SwtMgmtRcvdMsgBufType;

/**   \brief  value based type definition for EthTSyn_SwtMgmtRxBufQueueCurrProcIdx */
typedef uint8 EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType;

/**   \brief  value based type definition for EthTSyn_SwtMgmtRxBufQueueFreeIdx */
typedef uint8 EthTSyn_SwtMgmtRxBufQueueFreeIdxType;

/**   \brief  value based type definition for EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx */
typedef uint8 EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType;

/**   \brief  value based type definition for EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx */
typedef uint8 EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType;

/**   \brief  value based type definition for EthTSyn_NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg */
typedef uint8 EthTSyn_NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg */
typedef uint8 EthTSyn_NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg */
typedef uint8 EthTSyn_OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg */
typedef uint8 EthTSyn_RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfg */
typedef uint8 EthTSyn_RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg */
typedef uint8 EthTSyn_RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_RateRatioMaxOfSwtTimeSyncRateRegulatorCfg */
typedef float64 EthTSyn_RateRatioMaxOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_RateRatioMinOfSwtTimeSyncRateRegulatorCfg */
typedef float64 EthTSyn_RateRatioMinOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg */
typedef boolean EthTSyn_UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfgType;

/**   \brief  value based type definition for EthTSyn_GmClockIdentityOfSystemState */
typedef uint64 EthTSyn_GmClockIdentityOfSystemStateType;

/**   \brief  value based type definition for EthTSyn_GmPresentOfSystemState */
typedef boolean EthTSyn_GmPresentOfSystemStateType;

/**   \brief  value based type definition for EthTSyn_ValidOfTimeBaseUpdateCounter */
typedef boolean EthTSyn_ValidOfTimeBaseUpdateCounterType;

/**   \brief  value based type definition for EthTSyn_ValueOfTimeBaseUpdateCounter */
typedef uint8 EthTSyn_ValueOfTimeBaseUpdateCounterType;

/**   \brief  value based type definition for EthTSyn_FollowUpDataIdListEndIdxOfTimeDomain */
typedef uint8 EthTSyn_FollowUpDataIdListEndIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_FollowUpDataIdListStartIdxOfTimeDomain */
typedef uint8 EthTSyn_FollowUpDataIdListStartIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_FollowUpDataIdListUsedOfTimeDomain */
typedef boolean EthTSyn_FollowUpDataIdListUsedOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_IdOfTimeDomain */
typedef uint8 EthTSyn_IdOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_ImmediateTimeSyncOfTimeDomain */
typedef boolean EthTSyn_ImmediateTimeSyncOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_MasterPortEndIdxOfTimeDomain */
typedef uint8 EthTSyn_MasterPortEndIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_MasterPortLengthOfTimeDomain */
typedef uint8 EthTSyn_MasterPortLengthOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_MasterPortStartIdxOfTimeDomain */
typedef uint8 EthTSyn_MasterPortStartIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_MasterPortUsedOfTimeDomain */
typedef boolean EthTSyn_MasterPortUsedOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_OffsetTimeDomainEndIdxOfTimeDomain */
typedef uint8 EthTSyn_OffsetTimeDomainEndIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_OffsetTimeDomainStartIdxOfTimeDomain */
typedef uint8 EthTSyn_OffsetTimeDomainStartIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_OffsetTimeDomainUsedOfTimeDomain */
typedef boolean EthTSyn_OffsetTimeDomainUsedOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_SlavePortEndIdxOfTimeDomain */
typedef uint8 EthTSyn_SlavePortEndIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_SlavePortStartIdxOfTimeDomain */
typedef uint8 EthTSyn_SlavePortStartIdxOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_SlavePortUsedOfTimeDomain */
typedef boolean EthTSyn_SlavePortUsedOfTimeDomainType;

/**   \brief  value based type definition for EthTSyn_CorrectionFieldOfTimeValidMasterData */
typedef sint64 EthTSyn_CorrectionFieldOfTimeValidMasterDataType;

/**   \brief  value based type definition for EthTSyn_SequenceIdOfTimeValidMasterData */
typedef uint16 EthTSyn_SequenceIdOfTimeValidMasterDataType;

/**   \brief  value based type definition for EthTSyn_SrcClockIdOfTimeValidMasterData */
typedef uint64 EthTSyn_SrcClockIdOfTimeValidMasterDataType;

/**   \brief  value based type definition for EthTSyn_SrcPortNumOfTimeValidMasterData */
typedef uint16 EthTSyn_SrcPortNumOfTimeValidMasterDataType;

/**   \brief  value based type definition for EthTSyn_StateFlagsOfTimeValidMasterData */
typedef uint8 EthTSyn_StateFlagsOfTimeValidMasterDataType;

/**   \brief  value based type definition for EthTSyn_CurrPdelayOfTimeValidPdReqData */
typedef uint32 EthTSyn_CurrPdelayOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_PdRespClockIdOfTimeValidPdReqData */
typedef uint64 EthTSyn_PdRespClockIdOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_PdRespPortNumOfTimeValidPdReqData */
typedef uint16 EthTSyn_PdRespPortNumOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_SequenceIdOfTimeValidPdReqData */
typedef uint16 EthTSyn_SequenceIdOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_SrcClockIdOfTimeValidPdReqData */
typedef uint64 EthTSyn_SrcClockIdOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_SrcPortNumOfTimeValidPdReqData */
typedef uint16 EthTSyn_SrcPortNumOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_StateFlagsOfTimeValidPdReqData */
typedef uint8 EthTSyn_StateFlagsOfTimeValidPdReqDataType;

/**   \brief  value based type definition for EthTSyn_PdReqClockIdOfTimeValidPdRespData */
typedef uint64 EthTSyn_PdReqClockIdOfTimeValidPdRespDataType;

/**   \brief  value based type definition for EthTSyn_PdReqPortNumOfTimeValidPdRespData */
typedef uint16 EthTSyn_PdReqPortNumOfTimeValidPdRespDataType;

/**   \brief  value based type definition for EthTSyn_SequenceIdOfTimeValidPdRespData */
typedef uint16 EthTSyn_SequenceIdOfTimeValidPdRespDataType;

/**   \brief  value based type definition for EthTSyn_SrcClockIdOfTimeValidPdRespData */
typedef uint64 EthTSyn_SrcClockIdOfTimeValidPdRespDataType;

/**   \brief  value based type definition for EthTSyn_SrcPortNumOfTimeValidPdRespData */
typedef uint16 EthTSyn_SrcPortNumOfTimeValidPdRespDataType;

/**   \brief  value based type definition for EthTSyn_StateFlagsOfTimeValidPdRespData */
typedef uint8 EthTSyn_StateFlagsOfTimeValidPdRespDataType;

/**   \brief  value based type definition for EthTSyn_CorrectionFieldOfTimeValidSlaveData */
typedef sint64 EthTSyn_CorrectionFieldOfTimeValidSlaveDataType;

/**   \brief  value based type definition for EthTSyn_CurrPdelayOfTimeValidSlaveData */
typedef uint32 EthTSyn_CurrPdelayOfTimeValidSlaveDataType;

/**   \brief  value based type definition for EthTSyn_MasterClockIdOfTimeValidSlaveData */
typedef uint64 EthTSyn_MasterClockIdOfTimeValidSlaveDataType;

/**   \brief  value based type definition for EthTSyn_MasterPortNumOfTimeValidSlaveData */
typedef uint16 EthTSyn_MasterPortNumOfTimeValidSlaveDataType;

/**   \brief  value based type definition for EthTSyn_SequenceIdOfTimeValidSlaveData */
typedef uint16 EthTSyn_SequenceIdOfTimeValidSlaveDataType;

/**   \brief  value based type definition for EthTSyn_StateFlagsOfTimeValidSlaveData */
typedef uint8 EthTSyn_StateFlagsOfTimeValidSlaveDataType;

/** 
  \}
*/ 



#endif  /* ETHTSYN_GENERATED_SIMPLE_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_GeneratedSimpleTypes.h
 *********************************************************************************************************************/

