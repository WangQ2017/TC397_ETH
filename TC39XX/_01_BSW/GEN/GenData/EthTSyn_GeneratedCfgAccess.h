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
 *              File: EthTSyn_GeneratedCfgAccess.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef ETHTSYN_GENERATED_CFG_ACCESS_H
#define ETHTSYN_GENERATED_CFG_ACCESS_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Lcfg.h" 

/**********************************************************************************************************************
 * GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined(ETHTSYN_LOCAL)
# define ETHTSYN_LOCAL static
#endif

#if !defined(ETHTSYN_LOCAL_INLINE)
# define ETHTSYN_LOCAL_INLINE LOCAL_INLINE
#endif

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  EthTSynPCGetRootDataMacros  EthTSyn Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define EthTSyn_GetAnnounceInfoOfPCConfig()                                                         EthTSyn_ConfigDataPtr->AnnounceInfoOfPCConfig
#define EthTSyn_GetAnnounceReceiveSmOfPCConfig()                                                    EthTSyn_ConfigDataPtr->AnnounceReceiveSmOfPCConfig
#define EthTSyn_GetAnnounceSendSmCfgOfPCConfig()                                                    EthTSyn_ConfigDataPtr->AnnounceSendSmCfgOfPCConfig
#define EthTSyn_GetAnnounceSendSmOfPCConfig()                                                       EthTSyn_ConfigDataPtr->AnnounceSendSmOfPCConfig
#define EthTSyn_GetCtrlOfPCConfig()                                                                 EthTSyn_ConfigDataPtr->CtrlOfPCConfig
#define EthTSyn_GetCtrlStateOfPCConfig()                                                            EthTSyn_ConfigDataPtr->CtrlStateOfPCConfig
#define EthTSyn_GetDestinationMacOfPCConfig()                                                       EthTSyn_ConfigDataPtr->DestinationMacOfPCConfig
#define EthTSyn_GetFollowUpDataIdListOfPCConfig()                                                   EthTSyn_ConfigDataPtr->FollowUpDataIdListOfPCConfig
#define EthTSyn_GetMasterPortIdentityOfPCConfig()                                                   EthTSyn_ConfigDataPtr->MasterPortIdentityOfPCConfig
#define EthTSyn_GetMasterPortOfPCConfig()                                                           EthTSyn_ConfigDataPtr->MasterPortOfPCConfig
#define EthTSyn_GetOffsetTimeDomainOfPCConfig()                                                     EthTSyn_ConfigDataPtr->OffsetTimeDomainOfPCConfig
#define EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()                                          EthTSyn_ConfigDataPtr->OfsCorrDurationInSyncCyclesOfPCConfig
#define EthTSyn_GetPdelayConfigOfPCConfig()                                                         EthTSyn_ConfigDataPtr->PdelayConfigOfPCConfig
#define EthTSyn_GetPdelayInfoOfPCConfig()                                                           EthTSyn_ConfigDataPtr->PdelayInfoOfPCConfig
#define EthTSyn_GetPdelayInitiatorOfPCConfig()                                                      EthTSyn_ConfigDataPtr->PdelayInitiatorOfPCConfig
#define EthTSyn_GetPdelayReqSmOfPCConfig()                                                          EthTSyn_ConfigDataPtr->PdelayReqSmOfPCConfig
#define EthTSyn_GetPdelayRespSmOfPCConfig()                                                         EthTSyn_ConfigDataPtr->PdelayRespSmOfPCConfig
#define EthTSyn_GetPdelayResponderOfPCConfig()                                                      EthTSyn_ConfigDataPtr->PdelayResponderOfPCConfig
#define EthTSyn_GetPhysPortCfgOfPCConfig()                                                          EthTSyn_ConfigDataPtr->PhysPortCfgOfPCConfig
#define EthTSyn_GetPhysPortOfPCConfig()                                                             EthTSyn_ConfigDataPtr->PhysPortOfPCConfig
#define EthTSyn_GetPortIndOfPCConfig()                                                              EthTSyn_ConfigDataPtr->PortIndOfPCConfig
#define EthTSyn_GetPortOfPCConfig()                                                                 EthTSyn_ConfigDataPtr->PortOfPCConfig
#define EthTSyn_GetPortSyncSendSmOfPCConfig()                                                       EthTSyn_ConfigDataPtr->PortSyncSendSmOfPCConfig
#define EthTSyn_GetRateMeasurementOfPCConfig()                                                      EthTSyn_ConfigDataPtr->RateMeasurementOfPCConfig
#define EthTSyn_GetSizeOfAnnounceInfoOfPCConfig()                                                   EthTSyn_ConfigDataPtr->SizeOfAnnounceInfoOfPCConfig
#define EthTSyn_GetSizeOfAnnounceSendSmCfgOfPCConfig()                                              EthTSyn_ConfigDataPtr->SizeOfAnnounceSendSmCfgOfPCConfig
#define EthTSyn_GetSizeOfCtrlOfPCConfig()                                                           EthTSyn_ConfigDataPtr->SizeOfCtrlOfPCConfig
#define EthTSyn_GetSizeOfDestinationMacOfPCConfig()                                                 EthTSyn_ConfigDataPtr->SizeOfDestinationMacOfPCConfig
#define EthTSyn_GetSizeOfFollowUpDataIdListOfPCConfig()                                             EthTSyn_ConfigDataPtr->SizeOfFollowUpDataIdListOfPCConfig
#define EthTSyn_GetSizeOfMasterPortIdentityOfPCConfig()                                             EthTSyn_ConfigDataPtr->SizeOfMasterPortIdentityOfPCConfig
#define EthTSyn_GetSizeOfMasterPortOfPCConfig()                                                     EthTSyn_ConfigDataPtr->SizeOfMasterPortOfPCConfig
#define EthTSyn_GetSizeOfOffsetTimeDomainOfPCConfig()                                               EthTSyn_ConfigDataPtr->SizeOfOffsetTimeDomainOfPCConfig
#define EthTSyn_GetSizeOfPdelayConfigOfPCConfig()                                                   EthTSyn_ConfigDataPtr->SizeOfPdelayConfigOfPCConfig
#define EthTSyn_GetSizeOfPdelayInitiatorOfPCConfig()                                                EthTSyn_ConfigDataPtr->SizeOfPdelayInitiatorOfPCConfig
#define EthTSyn_GetSizeOfPdelayReqSmOfPCConfig()                                                    EthTSyn_ConfigDataPtr->SizeOfPdelayReqSmOfPCConfig
#define EthTSyn_GetSizeOfPdelayRespSmOfPCConfig()                                                   EthTSyn_ConfigDataPtr->SizeOfPdelayRespSmOfPCConfig
#define EthTSyn_GetSizeOfPdelayResponderOfPCConfig()                                                EthTSyn_ConfigDataPtr->SizeOfPdelayResponderOfPCConfig
#define EthTSyn_GetSizeOfPhysPortCfgOfPCConfig()                                                    EthTSyn_ConfigDataPtr->SizeOfPhysPortCfgOfPCConfig
#define EthTSyn_GetSizeOfPortIndOfPCConfig()                                                        EthTSyn_ConfigDataPtr->SizeOfPortIndOfPCConfig
#define EthTSyn_GetSizeOfPortOfPCConfig()                                                           EthTSyn_ConfigDataPtr->SizeOfPortOfPCConfig
#define EthTSyn_GetSizeOfRateMeasurementOfPCConfig()                                                EthTSyn_ConfigDataPtr->SizeOfRateMeasurementOfPCConfig
#define EthTSyn_GetSizeOfSlavePortOfPCConfig()                                                      EthTSyn_ConfigDataPtr->SizeOfSlavePortOfPCConfig
#define EthTSyn_GetSizeOfSlaveSwitchIdxListOfPCConfig()                                             EthTSyn_ConfigDataPtr->SizeOfSlaveSwitchIdxListOfPCConfig
#define EthTSyn_GetSizeOfSwitchPortMgmtOfPCConfig()                                                 EthTSyn_ConfigDataPtr->SizeOfSwitchPortMgmtOfPCConfig
#define EthTSyn_GetSizeOfSwitchSyncFrameCfgOfPCConfig()                                             EthTSyn_ConfigDataPtr->SizeOfSwitchSyncFrameCfgOfPCConfig
#define EthTSyn_GetSizeOfSwitchTimeSyncCfgOfPCConfig()                                              EthTSyn_ConfigDataPtr->SizeOfSwitchTimeSyncCfgOfPCConfig
#define EthTSyn_GetSizeOfSwtMgmtRcvdMsgBufOfPCConfig()                                              EthTSyn_ConfigDataPtr->SizeOfSwtMgmtRcvdMsgBufOfPCConfig
#define EthTSyn_GetSizeOfSwtTimeSyncRateRegulatorCfgOfPCConfig()                                    EthTSyn_ConfigDataPtr->SizeOfSwtTimeSyncRateRegulatorCfgOfPCConfig
#define EthTSyn_GetSizeOfTimeDomainOfPCConfig()                                                     EthTSyn_ConfigDataPtr->SizeOfTimeDomainOfPCConfig
#define EthTSyn_GetSizeOfTimeValidMasterCfgOfPCConfig()                                             EthTSyn_ConfigDataPtr->SizeOfTimeValidMasterCfgOfPCConfig
#define EthTSyn_GetSizeOfTimeValidPdReqCfgOfPCConfig()                                              EthTSyn_ConfigDataPtr->SizeOfTimeValidPdReqCfgOfPCConfig
#define EthTSyn_GetSizeOfTimeValidPdRespCfgOfPCConfig()                                             EthTSyn_ConfigDataPtr->SizeOfTimeValidPdRespCfgOfPCConfig
#define EthTSyn_GetSizeOfTimeValidSlaveCfgOfPCConfig()                                              EthTSyn_ConfigDataPtr->SizeOfTimeValidSlaveCfgOfPCConfig
#define EthTSyn_GetSlavePortOfPCConfig()                                                            EthTSyn_ConfigDataPtr->SlavePortOfPCConfig
#define EthTSyn_GetSlaveSwitchIdxListOfPCConfig()                                                   EthTSyn_ConfigDataPtr->SlaveSwitchIdxListOfPCConfig
#define EthTSyn_GetSwitchPortMgmtOfPCConfig()                                                       EthTSyn_ConfigDataPtr->SwitchPortMgmtOfPCConfig
#define EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()                                                   EthTSyn_ConfigDataPtr->SwitchSyncFrameCfgOfPCConfig
#define EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()                                                  EthTSyn_ConfigDataPtr->SwitchSyncFrameInfoOfPCConfig
#define EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()                                           EthTSyn_ConfigDataPtr->SwitchSyncFrameTxFrameInfoOfPCConfig
#define EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()                                                    EthTSyn_ConfigDataPtr->SwitchTimeSyncCfgOfPCConfig
#define EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()                                                   EthTSyn_ConfigDataPtr->SwitchTimeSyncInfoOfPCConfig
#define EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()                                                    EthTSyn_ConfigDataPtr->SwtMgmtRcvdMsgBufOfPCConfig
#define EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig()                                         EthTSyn_ConfigDataPtr->SwtMgmtRxBufQueueCurrProcIdxOfPCConfig
#define EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig()                                             EthTSyn_ConfigDataPtr->SwtMgmtRxBufQueueFreeIdxOfPCConfig
#define EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig()                                     EthTSyn_ConfigDataPtr->SwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig
#define EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig()                                         EthTSyn_ConfigDataPtr->SwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig
#define EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()                                          EthTSyn_ConfigDataPtr->SwtTimeSyncRateRegulatorCfgOfPCConfig
#define EthTSyn_GetSyncReceiveSmOfPCConfig()                                                        EthTSyn_ConfigDataPtr->SyncReceiveSmOfPCConfig
#define EthTSyn_GetSyncSendSmOfPCConfig()                                                           EthTSyn_ConfigDataPtr->SyncSendSmOfPCConfig
#define EthTSyn_GetSystemStateOfPCConfig()                                                          EthTSyn_ConfigDataPtr->SystemStateOfPCConfig
#define EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()                                                EthTSyn_ConfigDataPtr->TimeBaseUpdateCounterOfPCConfig
#define EthTSyn_GetTimeDomainOfPCConfig()                                                           EthTSyn_ConfigDataPtr->TimeDomainOfPCConfig
#define EthTSyn_GetTimeValidMasterCfgOfPCConfig()                                                   EthTSyn_ConfigDataPtr->TimeValidMasterCfgOfPCConfig
#define EthTSyn_GetTimeValidMasterDataOfPCConfig()                                                  EthTSyn_ConfigDataPtr->TimeValidMasterDataOfPCConfig
#define EthTSyn_GetTimeValidPdReqCfgOfPCConfig()                                                    EthTSyn_ConfigDataPtr->TimeValidPdReqCfgOfPCConfig
#define EthTSyn_GetTimeValidPdReqDataOfPCConfig()                                                   EthTSyn_ConfigDataPtr->TimeValidPdReqDataOfPCConfig
#define EthTSyn_GetTimeValidPdRespCfgOfPCConfig()                                                   EthTSyn_ConfigDataPtr->TimeValidPdRespCfgOfPCConfig
#define EthTSyn_GetTimeValidPdRespDataOfPCConfig()                                                  EthTSyn_ConfigDataPtr->TimeValidPdRespDataOfPCConfig
#define EthTSyn_GetTimeValidSlaveCfgOfPCConfig()                                                    EthTSyn_ConfigDataPtr->TimeValidSlaveCfgOfPCConfig
#define EthTSyn_GetTimeValidSlaveDataOfPCConfig()                                                   EthTSyn_ConfigDataPtr->TimeValidSlaveDataOfPCConfig
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCGetDuplicatedRootDataMacros  EthTSyn Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define EthTSyn_GetSizeOfAnnounceReceiveSmOfPCConfig()                                              EthTSyn_GetSizeOfAnnounceInfoOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_AnnounceReceiveSm */
#define EthTSyn_GetSizeOfAnnounceSendSmOfPCConfig()                                                 EthTSyn_GetSizeOfAnnounceSendSmCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_AnnounceSendSm */
#define EthTSyn_GetSizeOfCtrlStateOfPCConfig()                                                      EthTSyn_GetSizeOfCtrlOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_CtrlState */
#define EthTSyn_GetSizeOfOfsCorrDurationInSyncCyclesOfPCConfig()                                    EthTSyn_GetSizeOfSwtTimeSyncRateRegulatorCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_OfsCorrDurationInSyncCycles */
#define EthTSyn_GetSizeOfPdelayInfoOfPCConfig()                                                     EthTSyn_GetSizeOfPdelayConfigOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_PdelayInfo */
#define EthTSyn_GetSizeOfPhysPortOfPCConfig()                                                       EthTSyn_GetSizeOfPhysPortCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_PhysPort */
#define EthTSyn_GetSizeOfPortSyncSendSmOfPCConfig()                                                 EthTSyn_GetSizeOfMasterPortOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_PortSyncSendSm */
#define EthTSyn_GetSizeOfSwitchSyncFrameInfoOfPCConfig()                                            EthTSyn_GetSizeOfSwitchSyncFrameCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_SwitchSyncFrameInfo */
#define EthTSyn_GetSizeOfSwitchSyncFrameTxFrameInfoOfPCConfig()                                     EthTSyn_GetSizeOfSwitchSyncFrameCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_SwitchSyncFrameTxFrameInfo */
#define EthTSyn_GetSizeOfSwitchTimeSyncInfoOfPCConfig()                                             EthTSyn_GetSizeOfSwitchTimeSyncCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_SwitchTimeSyncInfo */
#define EthTSyn_GetSizeOfSyncReceiveSmOfPCConfig()                                                  EthTSyn_GetSizeOfSlavePortOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_SyncReceiveSm */
#define EthTSyn_GetSizeOfSyncSendSmOfPCConfig()                                                     EthTSyn_GetSizeOfMasterPortOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_SyncSendSm */
#define EthTSyn_GetSizeOfSystemStateOfPCConfig()                                                    EthTSyn_GetSizeOfTimeDomainOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_SystemState */
#define EthTSyn_GetSizeOfTimeBaseUpdateCounterOfPCConfig()                                          EthTSyn_GetSizeOfTimeDomainOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_TimeBaseUpdateCounter */
#define EthTSyn_GetSizeOfTimeValidMasterDataOfPCConfig()                                            EthTSyn_GetSizeOfTimeValidMasterCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_TimeValidMasterData */
#define EthTSyn_GetSizeOfTimeValidPdReqDataOfPCConfig()                                             EthTSyn_GetSizeOfTimeValidPdReqCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_TimeValidPdReqData */
#define EthTSyn_GetSizeOfTimeValidPdRespDataOfPCConfig()                                            EthTSyn_GetSizeOfTimeValidPdRespCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_TimeValidPdRespData */
#define EthTSyn_GetSizeOfTimeValidSlaveDataOfPCConfig()                                             EthTSyn_GetSizeOfTimeValidSlaveCfgOfPCConfig()  /**< the number of accomplishable value elements in EthTSyn_TimeValidSlaveData */
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/* PRQA S 0779 IDENTIFIERS_0779 */ /* MD_EthTSyn_0779_CslAccessName */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCGetDataInlineFunctionPrototypes  Get Data Inline Function Prototypes
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceAllowedRxDelayOfAnnounceInfoType, ETHTSYN_CODE) EthTSyn_GetAnnounceAllowedRxDelayOfAnnounceInfo(EthTSyn_AnnounceInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MaxeStepsRemovedOfAnnounceInfoType, ETHTSYN_CODE) EthTSyn_GetMaxeStepsRemovedOfAnnounceInfo(EthTSyn_AnnounceInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceReceiveSmType, ETHTSYN_CODE) EthTSyn_GetAnnounceReceiveSm(EthTSyn_AnnounceReceiveSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType, ETHTSYN_CODE) EthTSyn_GetAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfAnnounceSendSmType, ETHTSYN_CODE) EthTSyn_GetStateOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceTxCycleOfAnnounceSendSmCfgType, ETHTSYN_CODE) EthTSyn_GetAnnounceTxCycleOfAnnounceSendSmCfg(EthTSyn_AnnounceSendSmCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthIfCtrlIdxOfCtrlType, ETHTSYN_CODE) EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSyn_CtrlIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIndEndIdxOfCtrlType, ETHTSYN_CODE) EthTSyn_GetPortIndEndIdxOfCtrl(EthTSyn_CtrlIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIndStartIdxOfCtrlType, ETHTSYN_CODE) EthTSyn_GetPortIndStartIdxOfCtrl(EthTSyn_CtrlIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CtrlStateType, ETHTSYN_CODE) EthTSyn_GetCtrlState(EthTSyn_CtrlStateIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_DestinationMacType, ETHTSYN_CODE) EthTSyn_GetDestinationMac(EthTSyn_DestinationMacIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListType, ETHTSYN_CODE) EthTSyn_GetFollowUpDataIdList(EthTSyn_FollowUpDataIdListIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetAnnounceSendSmCfgIdxOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CrcTimeFlagsOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetCrcTimeFlagsOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CyclicMsgResumeCntOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetCyclicMsgResumeCntOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpMsgLengthOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetFollowUpMsgLengthOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpSentCbkPtrType, ETHTSYN_CODE) EthTSyn_GetFollowUpSentCbkPtrOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ImmediateTimeSyncOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsImmediateTimeSyncOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OfsSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsOfsSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StatusSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsStatusSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncLogMsgIntervalOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetSyncLogMsgIntervalOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSendIntervalOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetSyncSendIntervalOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSentCbkPtrType, ETHTSYN_CODE) EthTSyn_GetSyncSentCbkPtrOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsTimeSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxCrcSecuredEnumType, ETHTSYN_CODE) EthTSyn_GetTxCrcSecuredOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UserDataSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsUserDataSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ClockIdentityOfMasterPortIdentityType, ETHTSYN_CODE) EthTSyn_GetClockIdentityOfMasterPortIdentity(EthTSyn_MasterPortIdentityIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IdOfOffsetTimeDomainType, ETHTSYN_CODE) EthTSyn_GetIdOfOffsetTimeDomain(EthTSyn_OffsetTimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfOffsetTimeDomain(EthTSyn_OffsetTimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType, ETHTSYN_CODE) EthTSyn_GetCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RestartedOfOfsCorrDurationInSyncCyclesType, ETHTSYN_CODE) EthTSyn_IsRestartedOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AlwaysAsCapableOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsAlwaysAsCapableOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_InitialPdelayNsOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetInitialPdelayNsOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayInitiatorIdxOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayResponderIdxOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetPdelayResponderIdxOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UseStaticPdelayOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsUseStaticPdelayOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AsCapableOfPdelayInfoType, ETHTSYN_CODE) EthTSyn_IsAsCapableOfPdelayInfo(EthTSyn_PdelayInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayType, ETHTSYN_CODE) EthTSyn_GetPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UseAverageOfPdelayInfoType, ETHTSYN_CODE) EthTSyn_IsUseAverageOfPdelayInfo(EthTSyn_PdelayInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AllowedLostResponsesOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AverageWeightOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetAverageWeightOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_LogMessageIntervalOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetLogMessageIntervalOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayThresholdOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetPdelayThresholdOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RespRespFollowUpTimeoutOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetRespRespFollowUpTimeoutOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxIntervalMfOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetTxIntervalMfOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayReqSmType, ETHTSYN_CODE) EthTSyn_GetPdelayReqSm(EthTSyn_PdelayReqSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayRespSmType, ETHTSYN_CODE) EthTSyn_GetPdelayRespSm(EthTSyn_PdelayRespSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayRespSmIdxOfPdelayResponderType, ETHTSYN_CODE) EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(EthTSyn_PdelayResponderIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_DebounceTimerOfPhysPortType, ETHTSYN_CODE) EthTSyn_GetDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_DebounceTimeOfPhysPortCfgType, ETHTSYN_CODE) EthTSyn_GetDebounceTimeOfPhysPortCfg(EthTSyn_PhysPortCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CtrlIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetCtrlIdxOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FramePrioOfPortType, ETHTSYN_CODE) EthTSyn_GetFramePrioOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetMasterPortIdxOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_NumberOfPortType, ETHTSYN_CODE) EthTSyn_GetNumberOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayConfigIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetPdelayConfigIdxOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PhysPortCfgIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetPhysPortCfgIdxOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetSlavePortIdxOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StbMTimeSrcEqualOfPortType, ETHTSYN_CODE) EthTSyn_IsStbMTimeSrcEqualOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchPortMgmtIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetSwitchPortMgmtIdxOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeDomainIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetTimeDomainIdxOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIndType, ETHTSYN_CODE) EthTSyn_GetPortInd(EthTSyn_PortIndIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetStateOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_GetSyncHostEgrIntVltMgmtOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncTxConfCalledOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_IsSyncTxConfCalledOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxBufIdxOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthConstBufferPtrType, ETHTSYN_CODE) EthTSyn_GetTxBufPtrOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetAccumulatedMasterTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetAccumulatedSwtTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ActiveOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_IsActiveOfRateMeasurement(EthTSyn_RateMeasurementIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceInfoIdxOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetAnnounceInfoIdxOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CrcFlagsRxValidatedOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetCrcFlagsRxValidatedOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpAllowedRxDelayOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetFollowUpAllowedRxDelayOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortIdentityIdxOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetMasterPortIdentityIdxOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RxCrcValidatedEnumType, ETHTSYN_CODE) EthTSyn_GetRxCrcValidatedOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListType, ETHTSYN_CODE) EthTSyn_GetSlaveSwitchIdxList(EthTSyn_SlaveSwitchIdxListIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfSwitchPortMgmtType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfSwitchPortMgmt(EthTSyn_SwitchPortMgmtIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchIdxOfSwitchPortMgmtType, ETHTSYN_CODE) EthTSyn_GetSwitchIdxOfSwitchPortMgmt(EthTSyn_SwitchPortMgmtIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FramePrioOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetFramePrioOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MgmtPortSwitchPortIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncTxIntervalOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetSyncTxIntervalOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_GetPreciseOriginTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetStateOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_GetSwtIngressTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthBufferPtrType, ETHTSYN_CODE) EthTSyn_GetBufAddrOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType, ETHTSYN_CODE) EthTSyn_GetBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_GetGlobalTimeOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_IsApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthIfSwitchIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetEthIfSwitchIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MaxOutOfSyncCntOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetMaxOutOfSyncCntOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_SwtSyncStateChgFctPtrType, ETHTSYN_CODE) EthTSyn_GetSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncEventTimeoutOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncPrecisionLimitNsOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSyncPrecisionLimitNsOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_TimestampInfoStructType, ETHTSYN_CODE) EthTSyn_GetPrevTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncStateType, ETHTSYN_CODE) EthTSyn_GetSwtSyncStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_TimestampInfoStructType, ETHTSYN_CODE) EthTSyn_GetTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_WasSyncReachedOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_IsWasSyncReachedOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRcvdMsgBufType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueFreeIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtRxBufQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetNrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetNrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetOfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateMeasurementLengthOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateRatioMaxOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateRatioMinOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_IsUseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncReceiveSmType, ETHTSYN_CODE) EthTSyn_GetSyncReceiveSm(EthTSyn_SyncReceiveSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSendSmType, ETHTSYN_CODE) EthTSyn_GetSyncSendSm(EthTSyn_SyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GmClockIdentityOfSystemStateType, ETHTSYN_CODE) EthTSyn_GetGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GmPresentOfSystemStateType, ETHTSYN_CODE) EthTSyn_IsGmPresentOfSystemState(EthTSyn_SystemStateIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ValidOfTimeBaseUpdateCounterType, ETHTSYN_CODE) EthTSyn_IsValidOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ValueOfTimeBaseUpdateCounterType, ETHTSYN_CODE) EthTSyn_GetValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetFollowUpDataIdListEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetFollowUpDataIdListStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IdOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetIdOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ImmediateTimeSyncOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsImmediateTimeSyncOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetMasterPortEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortLengthOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetMasterPortLengthOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetMasterPortStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OffsetTimeDomainEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetOffsetTimeDomainEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OffsetTimeDomainStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSlavePortEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSlavePortStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidMasterCfg(EthTSyn_TimeValidMasterCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CorrectionFieldOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPreciseOriginTimestampOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcClockIdOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcPortNumOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdReqCfg(EthTSyn_TimeValidPdReqCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CurrPdelayOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPdReqRcvdTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdRespClockIdOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdRespPortNumOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPdRespSentTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetRefTimeGlobalOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_VirtualLocalTimeType, ETHTSYN_CODE) EthTSyn_GetRefTimeVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcClockIdOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcPortNumOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdRespCfg(EthTSyn_TimeValidPdRespCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdReqClockIdOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdReqPortNumOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetRefTimeGlobalOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_VirtualLocalTimeType, ETHTSYN_CODE) EthTSyn_GetRefTimeVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcClockIdOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcPortNumOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidSlaveCfg(EthTSyn_TimeValidSlaveCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CorrectionFieldOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CurrPdelayOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterClockIdOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortNumOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPreciseOriginTimestampOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCGetDeduplicatedInlineFunctionPrototypes  Get Deduplicated Inline Function Prototypes
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceSendSmCfgUsedOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsAnnounceSendSmCfgUsedOfMasterPort(EthTSyn_MasterPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayInitiatorUsedOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayResponderUsedOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsPdelayResponderUsedOfPdelayConfig(EthTSyn_PdelayConfigIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsMasterPortUsedOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayConfigUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsPdelayConfigUsedOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsSlavePortUsedOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchPortMgmtUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsSwitchPortMgmtUsedOfPort(EthTSyn_PortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceReceiveSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceReceiveSm(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceSendSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceSendSmCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceSendSmCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfCtrlType, ETHTSYN_CODE) EthTSyn_GetSizeOfCtrl(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfCtrlStateType, ETHTSYN_CODE) EthTSyn_GetSizeOfCtrlState(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfDestinationMacType, ETHTSYN_CODE) EthTSyn_GetSizeOfDestinationMac(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfFollowUpDataIdListType, ETHTSYN_CODE) EthTSyn_GetSizeOfFollowUpDataIdList(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetSizeOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfMasterPortIdentityType, ETHTSYN_CODE) EthTSyn_GetSizeOfMasterPortIdentity(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfOffsetTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSizeOfOffsetTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfOfsCorrDurationInSyncCyclesType, ETHTSYN_CODE) EthTSyn_GetSizeOfOfsCorrDurationInSyncCycles(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayReqSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayReqSm(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayRespSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayRespSm(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayResponderType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayResponder(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPhysPortType, ETHTSYN_CODE) EthTSyn_GetSizeOfPhysPort(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPhysPortCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfPhysPortCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPortType, ETHTSYN_CODE) EthTSyn_GetSizeOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPortIndType, ETHTSYN_CODE) EthTSyn_GetSizeOfPortInd(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetSizeOfRateMeasurement(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetSizeOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSlaveSwitchIdxListType, ETHTSYN_CODE) EthTSyn_GetSizeOfSlaveSwitchIdxList(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchPortMgmtType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchPortMgmt(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchSyncFrameTxFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchSyncFrameTxFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwtMgmtRcvdMsgBufType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwtMgmtRcvdMsgBuf(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSyncReceiveSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfSyncReceiveSm(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSystemStateType, ETHTSYN_CODE) EthTSyn_GetSizeOfSystemState(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeBaseUpdateCounterType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeBaseUpdateCounter(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidMasterCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidMasterCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdReqCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdReqCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdRespCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdRespCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidSlaveCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidSlaveCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceInfoUsedOfSlavePortType, ETHTSYN_CODE) EthTSyn_IsAnnounceInfoUsedOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortIdentityUsedOfSlavePortType, ETHTSYN_CODE) EthTSyn_IsMasterPortIdentityUsedOfSlavePort(EthTSyn_SlavePortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListUsedOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_IsSlaveSwitchIdxListUsedOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchSyncFrameCfgUsedOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_IsSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsFollowUpDataIdListUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsMasterPortUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OffsetTimeDomainUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsOffsetTimeDomainUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsSlavePortUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCSetDataInlineFunctionPrototypes  Set Data Inline Function Prototypes
  \brief  These inline functions can be used to write data.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAnnounceReceiveSm(EthTSyn_AnnounceReceiveSmIterType Index, EthTSyn_AnnounceReceiveSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_StateOfAnnounceSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCtrlState(EthTSyn_CtrlStateIterType Index, EthTSyn_CtrlStateType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRestartedOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_RestartedOfOfsCorrDurationInSyncCyclesType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAsCapableOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_AsCapableOfPdelayInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_PdelayType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetUseAverageOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_UseAverageOfPdelayInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdelayReqSm(EthTSyn_PdelayReqSmIterType Index, EthTSyn_PdelayReqSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdelayRespSm(EthTSyn_PdelayRespSmIterType Index, EthTSyn_PdelayRespSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index, EthTSyn_DebounceTimerOfPhysPortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_StateOfPortSyncSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncHostEgrIntVltMgmtOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_IntVltMgmtType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncTxConfCalledOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_SyncTxConfCalledOfPortSyncSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_TxBufIdxOfPortSyncSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetTxBufPtrOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_EthConstBufferPtrType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAccumulatedMasterTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurementType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAccumulatedSwtTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurementType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetActiveOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveOfRateMeasurementType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPreciseOriginTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_TsMgmtStructType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SequenceIdOfSwitchSyncFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_StateOfSwitchSyncFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtIngressTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_TsMgmtStructType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetBufAddrOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_EthBufferPtrType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetGlobalTimeOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_GlobalTimestampType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPrevTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SwtTimeSync_TimestampInfoStructType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_StateOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtSyncStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncStateType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SwtTimeSync_TimestampInfoStructType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetWasSyncReachedOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_WasSyncReachedOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index, EthTSyn_SwtMgmtRcvdMsgBufType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtRxBufQueueCurrProcIdx(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtRxBufQueueFreeIdx(EthTSyn_SwtMgmtRxBufQueueFreeIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtTxMgmtObjQueueCurrProcIdx(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtTxMgmtObjQueueFreeIdx(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncReceiveSm(EthTSyn_SyncReceiveSmIterType Index, EthTSyn_SyncReceiveSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncSendSm(EthTSyn_SyncSendSmIterType Index, EthTSyn_SyncSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmClockIdentityOfSystemStateType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetGmPresentOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmPresentOfSystemStateType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetValidOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValidOfTimeBaseUpdateCounterType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValueOfTimeBaseUpdateCounterType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPreciseOriginTimestampOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, StbM_TimeStampShortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SequenceIdOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcClockIdOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcPortNumOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_StateFlagsOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_CurrPdelayOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqRcvdTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_TimeStampShortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespClockIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespPortNumOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespSentTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_TimeStampShortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeGlobalOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_TimeStampShortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_VirtualLocalTimeType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqClockIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqPortNumOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeGlobalOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, StbM_TimeStampShortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, StbM_VirtualLocalTimeType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CurrPdelayOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterClockIdOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterPortNumOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPreciseOriginTimestampOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, StbM_TimeStampShortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_SequenceIdOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_StateFlagsOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_IntVltType Value);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCGetAddressOfDataInlineFunctionPrototypes  Get Address Of Data Inline Function Prototypes
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceReceiveSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrAnnounceReceiveSm(EthTSyn_AnnounceReceiveSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CtrlStatePtrType, ETHTSYN_CODE) EthTSyn_GetAddrCtrlState(EthTSyn_CtrlStateIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayReqSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdelayReqSm(EthTSyn_PdelayReqSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayRespSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdelayRespSm(EthTSyn_PdelayRespSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncHostEgrIntVltMgmtOfPortSyncSendSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSyncHostEgrIntVltMgmtOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxBufPtrOfPortSyncSendSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrTxBufPtrOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PreciseOriginTsMgmtOfSwitchSyncFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtIngressTsMgmtOfSwitchSyncFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_BufAddrOfSwitchSyncFrameTxFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrBufAddrOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GlobalTimeOfSwitchSyncFrameTxFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrGlobalTimeOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PrevTimeStampInfoOfSwitchTimeSyncInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPrevTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtSyncStateOfSwitchTimeSyncInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtSyncStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeStampInfoOfSwitchTimeSyncInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRcvdMsgBufPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtRxBufQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueFreeIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtRxBufQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncReceiveSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSyncReceiveSm(EthTSyn_SyncReceiveSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSendSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSyncSendSm(EthTSyn_SyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PreciseOriginTimestampOfTimeValidMasterDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPreciseOriginTimestampOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdReqRcvdTsOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdReqRcvdTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdRespSentTsOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdRespSentTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeGlobalOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeGlobalOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeVltOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeGlobalOfTimeValidPdRespDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeGlobalOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeVltOfTimeValidPdRespDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PreciseOriginTimestampOfTimeValidSlaveDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPreciseOriginTimestampOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCHasInlineFunctionPrototypes  Has Inline Function Prototypes
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceAllowedRxDelayOfAnnounceInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMaxeStepsRemovedOfAnnounceInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceReceiveSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceCycleTimerOfAnnounceSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfAnnounceSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceTxCycleOfAnnounceSendSmCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrl(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasEthIfCtrlIdxOfCtrl(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIndEndIdxOfCtrl(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIndStartIdxOfCtrl(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlState(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDestinationMac(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdList(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfgIdxOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfgUsedOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCrcTimeFlagsOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCyclicMsgResumeCntOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpMsgLengthOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpSentCbkPtrOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasImmediateTimeSyncOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsSubTlvOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStatusSubTlvOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncLogMsgIntervalOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSendIntervalOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSentCbkPtrOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeSubTlvOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxCrcSecuredOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUserDataSubTlvOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentity(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasClockIdentityOfMasterPortIdentity(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasIdOfOffsetTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfOffsetTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsCorrDurationInSyncCycles(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCounterOfOfsCorrDurationInSyncCycles(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRestartedOfOfsCorrDurationInSyncCycles(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAlwaysAsCapableOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasInitialPdelayNsOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiatorIdxOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiatorUsedOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponderIdxOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponderUsedOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUseStaticPdelayOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAsCapableOfPdelayInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayValueNsOfPdelayInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUseAverageOfPdelayInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAllowedLostResponsesOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAverageWeightOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasLogMessageIntervalOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayReqSmIdxOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayThresholdOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRespRespFollowUpTimeoutOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxIntervalMfOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayReqSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayRespSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponder(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayRespSmIdxOfPdelayResponder(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDebounceTimerOfPhysPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDebounceTimeOfPhysPortCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlIdxOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFramePrioOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdxOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortUsedOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasNumberOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfigIdxOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfigUsedOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortCfgIdxOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortIdxOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortUsedOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStbMTimeSrcEqualOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmtIdxOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmtUsedOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomainIdxOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortInd(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncHostEgrIntVltMgmtOfPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncTxConfCalledOfPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxBufIdxOfPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxBufPtrOfPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurement(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAccumulatedMasterTimeDiffOfRateMeasurement(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAccumulatedSwtTimeDiffOfRateMeasurement(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasActiveNrOfSyncCyclesOfRateMeasurement(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasActiveOfRateMeasurement(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceReceiveSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSmCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrl(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrlState(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfDestinationMac(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfFollowUpDataIdList(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPortIdentity(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOffsetTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOfsCorrDurationInSyncCycles(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInitiator(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayReqSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayRespSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayResponder(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPortCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortInd(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfRateMeasurement(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlaveSwitchIdxList(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchPortMgmt(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameTxFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtMgmtRcvdMsgBuf(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncReceiveSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSystemState(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeBaseUpdateCounter(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfoIdxOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfoUsedOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCrcFlagsRxValidatedOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpAllowedRxDelayOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentityIdxOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentityUsedOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRxCrcValidatedOfSlavePort(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxList(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmt(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfSwitchPortMgmt(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchIdxOfSwitchPortMgmt(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasEthIfCtrlIdxOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFramePrioOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncTxIntervalOfSwitchSyncFrameCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPreciseOriginTsMgmtOfSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtIngressTsMgmtOfSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncTxCntOfSwitchSyncFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameTxFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasBufAddrOfSwitchSyncFrameTxFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasBufIdxOfSwitchSyncFrameTxFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasGlobalTimeOfSwitchSyncFrameTxFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasIntVltOfSwitchSyncFrameTxFrameInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasEthIfSwitchIdxOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMaxOutOfSyncCntOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListUsedOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncEventTimeoutOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncPrecisionLimitNsOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomainIdxOfSwitchTimeSyncCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCurrentOffsetNsOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasLastCorrectedOffsetNsOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOutOfSyncCntOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPrevTimeStampInfoOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtSyncStateOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncEventTimeoutCntOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeStampInfoOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasWasSyncReachedOfSwitchTimeSyncInfo(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRcvdMsgBuf(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasNrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasNrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementLengthOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateRatioMinOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncReceiveSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSendSm(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSystemState(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasGmClockIdentityOfSystemState(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasGmPresentOfSystemState(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeBaseUpdateCounter(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasValidOfTimeBaseUpdateCounter(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasValueOfTimeBaseUpdateCounter(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListEndIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListStartIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListUsedOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasIdOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasImmediateTimeSyncOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortEndIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortLengthOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortStartIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortUsedOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainEndIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainStartIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainUsedOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortEndIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortStartIdxOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortUsedOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeDomain(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidMasterCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCorrectionFieldOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPreciseOriginTimestampOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcClockIdOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcPortNumOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncEgressTsVltOfTimeValidMasterData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidPdReqCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCurrPdelayOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqEgressTsVltOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqRcvdTsOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespClockIdOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespIngressTsVltOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespPortNumOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespSentTsOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeGlobalOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeVltOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcClockIdOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcPortNumOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidPdReqData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidPdRespCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqClockIdOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqIngressTsVltOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqPortNumOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespEgressTsVltOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeGlobalOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeVltOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcClockIdOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcPortNumOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidPdRespData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidSlaveCfg(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCorrectionFieldOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCurrPdelayOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterClockIdOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortNumOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPreciseOriginTimestampOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncIngressTsVltOfTimeValidSlaveData(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceReceiveSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlStateOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDestinationMacOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentityOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsCorrDurationInSyncCyclesOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfigOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiatorOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayReqSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayRespSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponderOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIndOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortSyncSendSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceReceiveSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSmCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrlOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrlStateOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfDestinationMacOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfFollowUpDataIdListOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPortIdentityOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOffsetTimeDomainOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOfsCorrDurationInSyncCyclesOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayConfigOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInitiatorOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayReqSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayRespSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayResponderOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPortCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortIndOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortSyncSendSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfRateMeasurementOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlavePortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlaveSwitchIdxListOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchPortMgmtOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameTxFrameInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtMgmtRcvdMsgBufOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtTimeSyncRateRegulatorCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncReceiveSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncSendSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSystemStateOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeBaseUpdateCounterOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeDomainOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterDataOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqDataOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespDataOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveDataOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmtOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameTxFrameInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncInfoOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRcvdMsgBufOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueCurrProcIdxOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueFreeIdxOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtTimeSyncRateRegulatorCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncReceiveSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSendSmOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSystemStateOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeBaseUpdateCounterOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomainOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterDataOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqDataOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespDataOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveCfgOfPCConfig(void);
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveDataOfPCConfig(void);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCIncrementInlineFunctionPrototypes  Increment Inline Function Prototypes
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtRxBufQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtRxBufQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtTxMgmtObjQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtTxMgmtObjQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCDecrementInlineFunctionPrototypes  Decrement Inline Function Prototypes
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtRxBufQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtRxBufQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtTxMgmtObjQueueCurrProcIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtTxMgmtObjQueueFreeIdx(void);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCAddInlineFunctionPrototypes  Add Inline Function Prototypes
  \brief  These inline functions can be used to add VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_PdelayType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index, EthTSyn_DebounceTimerOfPhysPortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_TxBufIdxOfPortSyncSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SequenceIdOfSwitchSyncFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index, EthTSyn_SwtMgmtRcvdMsgBufType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtRxBufQueueCurrProcIdx(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtRxBufQueueFreeIdx(EthTSyn_SwtMgmtRxBufQueueFreeIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtTxMgmtObjQueueCurrProcIdx(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtTxMgmtObjQueueFreeIdx(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmClockIdentityOfSystemStateType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValueOfTimeBaseUpdateCounterType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SequenceIdOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcClockIdOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcPortNumOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_StateFlagsOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_CurrPdelayOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespClockIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespPortNumOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqClockIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqPortNumOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CurrPdelayOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterClockIdOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterPortNumOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_SequenceIdOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_StateFlagsOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_IntVltType Value);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCSubstractInlineFunctionPrototypes  Substract Inline Function Prototypes
  \brief  These inline functions can be used to substract VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_PdelayType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index, EthTSyn_DebounceTimerOfPhysPortType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_TxBufIdxOfPortSyncSendSmType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SequenceIdOfSwitchSyncFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index, EthTSyn_SwtMgmtRcvdMsgBufType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtRxBufQueueCurrProcIdx(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtRxBufQueueFreeIdx(EthTSyn_SwtMgmtRxBufQueueFreeIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtTxMgmtObjQueueCurrProcIdx(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtTxMgmtObjQueueFreeIdx(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmClockIdentityOfSystemStateType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValueOfTimeBaseUpdateCounterType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SequenceIdOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcClockIdOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcPortNumOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_StateFlagsOfTimeValidMasterDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_CurrPdelayOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespClockIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespPortNumOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdReqDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqClockIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqPortNumOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdRespDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CurrPdelayOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterClockIdOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterPortNumOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_SequenceIdOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_StateFlagsOfTimeValidSlaveDataType Value);
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_IntVltType Value);
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


# if !defined(ETHTSYN_UNIT_TEST) /* COV_ETHTSYN_TESTSUITE_INSTRUMENTATION */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTIONS
**********************************************************************************************************************/
#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCGetDataInlineFunctions  EthTSyn Get Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceAllowedRxDelayOfAnnounceInfoType, ETHTSYN_CODE) EthTSyn_GetAnnounceAllowedRxDelayOfAnnounceInfo(EthTSyn_AnnounceInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AnnounceAllowedRxDelayOfAnnounceInfoType) (EthTSyn_GetAnnounceInfoOfPCConfig()[(Index)].AnnounceAllowedRxDelayOfAnnounceInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MaxeStepsRemovedOfAnnounceInfoType, ETHTSYN_CODE) EthTSyn_GetMaxeStepsRemovedOfAnnounceInfo(EthTSyn_AnnounceInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MaxeStepsRemovedOfAnnounceInfoType) (EthTSyn_GetAnnounceInfoOfPCConfig()[(Index)].MaxeStepsRemovedOfAnnounceInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceReceiveSmType, ETHTSYN_CODE) EthTSyn_GetAnnounceReceiveSm(EthTSyn_AnnounceReceiveSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetAnnounceReceiveSmOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType, ETHTSYN_CODE) EthTSyn_GetAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType) (EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].AnnounceCycleTimerOfAnnounceSendSm);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfAnnounceSendSmType, ETHTSYN_CODE) EthTSyn_GetStateOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateOfAnnounceSendSmType) (EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].StateOfAnnounceSendSm);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceTxCycleOfAnnounceSendSmCfgType, ETHTSYN_CODE) EthTSyn_GetAnnounceTxCycleOfAnnounceSendSmCfg(EthTSyn_AnnounceSendSmCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AnnounceTxCycleOfAnnounceSendSmCfgType) (EthTSyn_GetAnnounceSendSmCfgOfPCConfig()[(Index)].AnnounceTxCycleOfAnnounceSendSmCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthIfCtrlIdxOfCtrlType, ETHTSYN_CODE) EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSyn_CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_EthIfCtrlIdxOfCtrlType) (EthTSyn_GetCtrlOfPCConfig()[(Index)].EthIfCtrlIdxOfCtrl);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIndEndIdxOfCtrlType, ETHTSYN_CODE) EthTSyn_GetPortIndEndIdxOfCtrl(EthTSyn_CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIndEndIdxOfCtrlType) (EthTSyn_GetCtrlOfPCConfig()[(Index)].PortIndEndIdxOfCtrl);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIndStartIdxOfCtrlType, ETHTSYN_CODE) EthTSyn_GetPortIndStartIdxOfCtrl(EthTSyn_CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIndStartIdxOfCtrlType) (EthTSyn_GetCtrlOfPCConfig()[(Index)].PortIndStartIdxOfCtrl);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CtrlStateType, ETHTSYN_CODE) EthTSyn_GetCtrlState(EthTSyn_CtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetCtrlStateOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_DestinationMacType, ETHTSYN_CODE) EthTSyn_GetDestinationMac(EthTSyn_DestinationMacIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_DestinationMacType) (EthTSyn_GetDestinationMacOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListType, ETHTSYN_CODE) EthTSyn_GetFollowUpDataIdList(EthTSyn_FollowUpDataIdListIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FollowUpDataIdListType) (EthTSyn_GetFollowUpDataIdListOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetAnnounceSendSmCfgIdxOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AnnounceSendSmCfgIdxOfMasterPortType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].AnnounceSendSmCfgIdxOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CrcTimeFlagsOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetCrcTimeFlagsOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CrcTimeFlagsOfMasterPortType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].CrcTimeFlagsOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CyclicMsgResumeCntOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetCyclicMsgResumeCntOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CyclicMsgResumeCntOfMasterPortType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].CyclicMsgResumeCntOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpMsgLengthOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetFollowUpMsgLengthOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FollowUpMsgLengthOfMasterPortType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].FollowUpMsgLengthOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpSentCbkPtrType, ETHTSYN_CODE) EthTSyn_GetFollowUpSentCbkPtrOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetMasterPortOfPCConfig()[(Index)].FollowUpSentCbkPtrOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ImmediateTimeSyncOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsImmediateTimeSyncOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ImmediateTimeSyncOfMasterPortType) ((EthTSyn_GetMasterPortOfPCConfig()[(Index)].ImmediateTimeSyncOfMasterPort) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OfsSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsOfsSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_OfsSubTlvOfMasterPortType) ((EthTSyn_GetMasterPortOfPCConfig()[(Index)].OfsSubTlvOfMasterPort) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIdxOfMasterPortType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].PortIdxOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StatusSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsStatusSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StatusSubTlvOfMasterPortType) ((EthTSyn_GetMasterPortOfPCConfig()[(Index)].StatusSubTlvOfMasterPort) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncLogMsgIntervalOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetSyncLogMsgIntervalOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncLogMsgIntervalOfMasterPortType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].SyncLogMsgIntervalOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSendIntervalOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetSyncSendIntervalOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncSendIntervalOfMasterPortType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].SyncSendIntervalOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSentCbkPtrType, ETHTSYN_CODE) EthTSyn_GetSyncSentCbkPtrOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetMasterPortOfPCConfig()[(Index)].SyncSentCbkPtrOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsTimeSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_TimeSubTlvOfMasterPortType) ((EthTSyn_GetMasterPortOfPCConfig()[(Index)].TimeSubTlvOfMasterPort) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxCrcSecuredEnumType, ETHTSYN_CODE) EthTSyn_GetTxCrcSecuredOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_TxCrcSecuredEnumType) (EthTSyn_GetMasterPortOfPCConfig()[(Index)].TxCrcSecuredOfMasterPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UserDataSubTlvOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsUserDataSubTlvOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_UserDataSubTlvOfMasterPortType) ((EthTSyn_GetMasterPortOfPCConfig()[(Index)].UserDataSubTlvOfMasterPort) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ClockIdentityOfMasterPortIdentityType, ETHTSYN_CODE) EthTSyn_GetClockIdentityOfMasterPortIdentity(EthTSyn_MasterPortIdentityIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ClockIdentityOfMasterPortIdentityType) (EthTSyn_GetMasterPortIdentityOfPCConfig()[(Index)].ClockIdentityOfMasterPortIdentity);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IdOfOffsetTimeDomainType, ETHTSYN_CODE) EthTSyn_GetIdOfOffsetTimeDomain(EthTSyn_OffsetTimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IdOfOffsetTimeDomainType) (EthTSyn_GetOffsetTimeDomainOfPCConfig()[(Index)].IdOfOffsetTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfOffsetTimeDomain(EthTSyn_OffsetTimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (StbM_SynchronizedTimeBaseType) (EthTSyn_GetOffsetTimeDomainOfPCConfig()[(Index)].SynchronizedTimeBaseIdOfOffsetTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType, ETHTSYN_CODE) EthTSyn_GetCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType) (EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].CounterOfOfsCorrDurationInSyncCycles);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RestartedOfOfsCorrDurationInSyncCyclesType, ETHTSYN_CODE) EthTSyn_IsRestartedOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RestartedOfOfsCorrDurationInSyncCyclesType) ((EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].RestartedOfOfsCorrDurationInSyncCycles) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AlwaysAsCapableOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsAlwaysAsCapableOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AlwaysAsCapableOfPdelayConfigType) ((EthTSyn_GetPdelayConfigOfPCConfig()[(Index)].AlwaysAsCapableOfPdelayConfig) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_InitialPdelayNsOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetInitialPdelayNsOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_InitialPdelayNsOfPdelayConfigType) (EthTSyn_GetPdelayConfigOfPCConfig()[(Index)].InitialPdelayNsOfPdelayConfig);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayInitiatorIdxOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayInitiatorIdxOfPdelayConfigType) (EthTSyn_GetPdelayConfigOfPCConfig()[(Index)].PdelayInitiatorIdxOfPdelayConfig);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayResponderIdxOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetPdelayResponderIdxOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayResponderIdxOfPdelayConfigType) (EthTSyn_GetPdelayConfigOfPCConfig()[(Index)].PdelayResponderIdxOfPdelayConfig);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIdxOfPdelayConfigType) (EthTSyn_GetPdelayConfigOfPCConfig()[(Index)].PortIdxOfPdelayConfig);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UseStaticPdelayOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsUseStaticPdelayOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_UseStaticPdelayOfPdelayConfigType) ((EthTSyn_GetPdelayConfigOfPCConfig()[(Index)].UseStaticPdelayOfPdelayConfig) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AsCapableOfPdelayInfoType, ETHTSYN_CODE) EthTSyn_IsAsCapableOfPdelayInfo(EthTSyn_PdelayInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AsCapableOfPdelayInfoType) ((EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].AsCapableOfPdelayInfo) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayType, ETHTSYN_CODE) EthTSyn_GetPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayType) (EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].PdelayValueNsOfPdelayInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UseAverageOfPdelayInfoType, ETHTSYN_CODE) EthTSyn_IsUseAverageOfPdelayInfo(EthTSyn_PdelayInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_UseAverageOfPdelayInfoType) ((EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].UseAverageOfPdelayInfo) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AllowedLostResponsesOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AllowedLostResponsesOfPdelayInitiatorType) (EthTSyn_GetPdelayInitiatorOfPCConfig()[(Index)].AllowedLostResponsesOfPdelayInitiator);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AverageWeightOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetAverageWeightOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AverageWeightOfPdelayInitiatorType) (EthTSyn_GetPdelayInitiatorOfPCConfig()[(Index)].AverageWeightOfPdelayInitiator);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_LogMessageIntervalOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetLogMessageIntervalOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_LogMessageIntervalOfPdelayInitiatorType) (EthTSyn_GetPdelayInitiatorOfPCConfig()[(Index)].LogMessageIntervalOfPdelayInitiator);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType) (EthTSyn_GetPdelayInitiatorOfPCConfig()[(Index)].PdelayReqSmIdxOfPdelayInitiator);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayThresholdOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetPdelayThresholdOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayThresholdOfPdelayInitiatorType) (EthTSyn_GetPdelayInitiatorOfPCConfig()[(Index)].PdelayThresholdOfPdelayInitiator);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RespRespFollowUpTimeoutOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetRespRespFollowUpTimeoutOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RespRespFollowUpTimeoutOfPdelayInitiatorType) (EthTSyn_GetPdelayInitiatorOfPCConfig()[(Index)].RespRespFollowUpTimeoutOfPdelayInitiator);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxIntervalMfOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetTxIntervalMfOfPdelayInitiator(EthTSyn_PdelayInitiatorIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_TxIntervalMfOfPdelayInitiatorType) (EthTSyn_GetPdelayInitiatorOfPCConfig()[(Index)].TxIntervalMfOfPdelayInitiator);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayReqSmType, ETHTSYN_CODE) EthTSyn_GetPdelayReqSm(EthTSyn_PdelayReqSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetPdelayReqSmOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayRespSmType, ETHTSYN_CODE) EthTSyn_GetPdelayRespSm(EthTSyn_PdelayRespSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetPdelayRespSmOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayRespSmIdxOfPdelayResponderType, ETHTSYN_CODE) EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(EthTSyn_PdelayResponderIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayRespSmIdxOfPdelayResponderType) (EthTSyn_GetPdelayResponderOfPCConfig()[(Index)].PdelayRespSmIdxOfPdelayResponder);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_DebounceTimerOfPhysPortType, ETHTSYN_CODE) EthTSyn_GetDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_DebounceTimerOfPhysPortType) (EthTSyn_GetPhysPortOfPCConfig()[(Index)].DebounceTimerOfPhysPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_DebounceTimeOfPhysPortCfgType, ETHTSYN_CODE) EthTSyn_GetDebounceTimeOfPhysPortCfg(EthTSyn_PhysPortCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_DebounceTimeOfPhysPortCfgType) (EthTSyn_GetPhysPortCfgOfPCConfig()[(Index)].DebounceTimeOfPhysPortCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CtrlIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetCtrlIdxOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CtrlIdxOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].CtrlIdxOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FramePrioOfPortType, ETHTSYN_CODE) EthTSyn_GetFramePrioOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FramePrioOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].FramePrioOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetMasterPortIdxOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortIdxOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].MasterPortIdxOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_NumberOfPortType, ETHTSYN_CODE) EthTSyn_GetNumberOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_NumberOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].NumberOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayConfigIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetPdelayConfigIdxOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayConfigIdxOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].PdelayConfigIdxOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PhysPortCfgIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetPhysPortCfgIdxOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PhysPortCfgIdxOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].PhysPortCfgIdxOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetSlavePortIdxOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlavePortIdxOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].SlavePortIdxOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StbMTimeSrcEqualOfPortType, ETHTSYN_CODE) EthTSyn_IsStbMTimeSrcEqualOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StbMTimeSrcEqualOfPortType) ((EthTSyn_GetPortOfPCConfig()[(Index)].StbMTimeSrcEqualOfPort) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchPortMgmtIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetSwitchPortMgmtIdxOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwitchPortMgmtIdxOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].SwitchPortMgmtIdxOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeDomainIdxOfPortType, ETHTSYN_CODE) EthTSyn_GetTimeDomainIdxOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_TimeDomainIdxOfPortType) (EthTSyn_GetPortOfPCConfig()[(Index)].TimeDomainIdxOfPort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIndType, ETHTSYN_CODE) EthTSyn_GetPortInd(EthTSyn_PortIndIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIndType) (EthTSyn_GetPortIndOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetStateOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateOfPortSyncSendSmType) (EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].StateOfPortSyncSendSm);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_GetSyncHostEgrIntVltMgmtOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].SyncHostEgrIntVltMgmtOfPortSyncSendSm);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncTxConfCalledOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_IsSyncTxConfCalledOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncTxConfCalledOfPortSyncSendSmType) ((EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].SyncTxConfCalledOfPortSyncSendSm) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxBufIdxOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_TxBufIdxOfPortSyncSendSmType) (EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufIdxOfPortSyncSendSm);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthConstBufferPtrType, ETHTSYN_CODE) EthTSyn_GetTxBufPtrOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufPtrOfPortSyncSendSm);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetAccumulatedMasterTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurementType) (EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].AccumulatedMasterTimeDiffOfRateMeasurement);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetAccumulatedSwtTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurementType) (EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].AccumulatedSwtTimeDiffOfRateMeasurement);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType) (EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveNrOfSyncCyclesOfRateMeasurement);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ActiveOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_IsActiveOfRateMeasurement(EthTSyn_RateMeasurementIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ActiveOfRateMeasurementType) ((EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveOfRateMeasurement) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceInfoIdxOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetAnnounceInfoIdxOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AnnounceInfoIdxOfSlavePortType) (EthTSyn_GetSlavePortOfPCConfig()[(Index)].AnnounceInfoIdxOfSlavePort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CrcFlagsRxValidatedOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetCrcFlagsRxValidatedOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CrcFlagsRxValidatedOfSlavePortType) (EthTSyn_GetSlavePortOfPCConfig()[(Index)].CrcFlagsRxValidatedOfSlavePort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpAllowedRxDelayOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetFollowUpAllowedRxDelayOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FollowUpAllowedRxDelayOfSlavePortType) (EthTSyn_GetSlavePortOfPCConfig()[(Index)].FollowUpAllowedRxDelayOfSlavePort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortIdentityIdxOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetMasterPortIdentityIdxOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortIdentityIdxOfSlavePortType) (EthTSyn_GetSlavePortOfPCConfig()[(Index)].MasterPortIdentityIdxOfSlavePort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIdxOfSlavePortType) (EthTSyn_GetSlavePortOfPCConfig()[(Index)].PortIdxOfSlavePort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RxCrcValidatedEnumType, ETHTSYN_CODE) EthTSyn_GetRxCrcValidatedOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RxCrcValidatedEnumType) (EthTSyn_GetSlavePortOfPCConfig()[(Index)].RxCrcValidatedOfSlavePort);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListType, ETHTSYN_CODE) EthTSyn_GetSlaveSwitchIdxList(EthTSyn_SlaveSwitchIdxListIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlaveSwitchIdxListType) (EthTSyn_GetSlaveSwitchIdxListOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfSwitchPortMgmtType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfSwitchPortMgmt(EthTSyn_SwitchPortMgmtIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIdxOfSwitchPortMgmtType) (EthTSyn_GetSwitchPortMgmtOfPCConfig()[(Index)].PortIdxOfSwitchPortMgmt);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchIdxOfSwitchPortMgmtType, ETHTSYN_CODE) EthTSyn_GetSwitchIdxOfSwitchPortMgmt(EthTSyn_SwitchPortMgmtIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwitchIdxOfSwitchPortMgmtType) (EthTSyn_GetSwitchPortMgmtOfPCConfig()[(Index)].SwitchIdxOfSwitchPortMgmt);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfgType) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()[(Index)].EthIfCtrlIdxOfSwitchSyncFrameCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FramePrioOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetFramePrioOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FramePrioOfSwitchSyncFrameCfgType) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()[(Index)].FramePrioOfSwitchSyncFrameCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfgType) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()[(Index)].MgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MgmtPortSwitchPortIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MgmtPortSwitchPortIdxOfSwitchSyncFrameCfgType) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()[(Index)].MgmtPortSwitchPortIdxOfSwitchSyncFrameCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetPortIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PortIdxOfSwitchSyncFrameCfgType) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()[(Index)].PortIdxOfSwitchSyncFrameCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()[(Index)].SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncTxIntervalOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetSyncTxIntervalOfSwitchSyncFrameCfg(EthTSyn_SwitchSyncFrameCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncTxIntervalOfSwitchSyncFrameCfgType) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig()[(Index)].SyncTxIntervalOfSwitchSyncFrameCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_GetPreciseOriginTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].PreciseOriginTsMgmtOfSwitchSyncFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SequenceIdOfSwitchSyncFrameInfoType) (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SequenceIdOfSwitchSyncFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetStateOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateOfSwitchSyncFrameInfoType) (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].StateOfSwitchSyncFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_GetSwtIngressTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SwtIngressTsMgmtOfSwitchSyncFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType) (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SyncTxCntOfSwitchSyncFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthBufferPtrType, ETHTSYN_CODE) EthTSyn_GetBufAddrOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufAddrOfSwitchSyncFrameTxFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType, ETHTSYN_CODE) EthTSyn_GetBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType) (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufIdxOfSwitchSyncFrameTxFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_GetGlobalTimeOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].GlobalTimeOfSwitchSyncFrameTxFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IntVltType) (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].IntVltOfSwitchSyncFrameTxFrameInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_IsApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfgType) ((EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].ApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_EthIfSwitchIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetEthIfSwitchIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_EthIfSwitchIdxOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].EthIfSwitchIdxOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MaxOutOfSyncCntOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetMaxOutOfSyncCntOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MaxOutOfSyncCntOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].MaxOutOfSyncCntOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].SlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].SlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_SwtSyncStateChgFctPtrType, ETHTSYN_CODE) EthTSyn_GetSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].SwtSyncStateChgFctPtrOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncEventTimeoutOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncEventTimeoutOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].SyncEventTimeoutOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncPrecisionLimitNsOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSyncPrecisionLimitNsOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncPrecisionLimitNsOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].SyncPrecisionLimitNsOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig()[(Index)].TimeDomainIdxOfSwitchTimeSyncCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType) (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].CurrentOffsetNsOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType) (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].LastCorrectedOffsetNsOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType) (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].OutOfSyncCntOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_TimestampInfoStructType, ETHTSYN_CODE) EthTSyn_GetPrevTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].PrevTimeStampInfoOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateOfSwitchTimeSyncInfoType) (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].StateOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncStateType, ETHTSYN_CODE) EthTSyn_GetSwtSyncStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SwtSyncStateOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType) (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SyncEventTimeoutCntOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_TimestampInfoStructType, ETHTSYN_CODE) EthTSyn_GetTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].TimeStampInfoOfSwitchTimeSyncInfo);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_WasSyncReachedOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_IsWasSyncReachedOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_WasSyncReachedOfSwitchTimeSyncInfoType) ((EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].WasSyncReachedOfSwitchTimeSyncInfo) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRcvdMsgBufType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtRcvdMsgBufType) (EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType) ((*(EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig())));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueFreeIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtRxBufQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtRxBufQueueFreeIdxType) ((*(EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig())));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType) ((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig())));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType, ETHTSYN_CODE) EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType) ((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig())));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetNrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].NrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetNrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].NrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetOfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].OfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].RateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateMeasurementLengthOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].RateMeasurementLengthOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].RateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateRatioMaxOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RateRatioMaxOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].RateRatioMaxOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RateRatioMinOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_RateRatioMinOfSwtTimeSyncRateRegulatorCfgType) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].RateRatioMinOfSwtTimeSyncRateRegulatorCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_IsUseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg(EthTSyn_SwtTimeSyncRateRegulatorCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfgType) ((EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig()[(Index)].UseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncReceiveSmType, ETHTSYN_CODE) EthTSyn_GetSyncReceiveSm(EthTSyn_SyncReceiveSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSyncReceiveSmOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSendSmType, ETHTSYN_CODE) EthTSyn_GetSyncSendSm(EthTSyn_SyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetSyncSendSmOfPCConfig()[(Index)]);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GmClockIdentityOfSystemStateType, ETHTSYN_CODE) EthTSyn_GetGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GmClockIdentityOfSystemStateType) (EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmClockIdentityOfSystemState);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GmPresentOfSystemStateType, ETHTSYN_CODE) EthTSyn_IsGmPresentOfSystemState(EthTSyn_SystemStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GmPresentOfSystemStateType) ((EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmPresentOfSystemState) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ValidOfTimeBaseUpdateCounterType, ETHTSYN_CODE) EthTSyn_IsValidOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ValidOfTimeBaseUpdateCounterType) ((EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValidOfTimeBaseUpdateCounter) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ValueOfTimeBaseUpdateCounterType, ETHTSYN_CODE) EthTSyn_GetValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ValueOfTimeBaseUpdateCounterType) (EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValueOfTimeBaseUpdateCounter);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetFollowUpDataIdListEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FollowUpDataIdListEndIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].FollowUpDataIdListEndIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetFollowUpDataIdListStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FollowUpDataIdListStartIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].FollowUpDataIdListStartIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IdOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetIdOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IdOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].IdOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_ImmediateTimeSyncOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsImmediateTimeSyncOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_ImmediateTimeSyncOfTimeDomainType) ((EthTSyn_GetTimeDomainOfPCConfig()[(Index)].ImmediateTimeSyncOfTimeDomain) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetMasterPortEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortEndIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].MasterPortEndIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortLengthOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetMasterPortLengthOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortLengthOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].MasterPortLengthOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetMasterPortStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortStartIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].MasterPortStartIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OffsetTimeDomainEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetOffsetTimeDomainEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_OffsetTimeDomainEndIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].OffsetTimeDomainEndIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OffsetTimeDomainStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_OffsetTimeDomainStartIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].OffsetTimeDomainStartIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortEndIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSlavePortEndIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlavePortEndIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].SlavePortEndIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortStartIdxOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSlavePortStartIdxOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlavePortStartIdxOfTimeDomainType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].SlavePortStartIdxOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (StbM_SynchronizedTimeBaseType) (EthTSyn_GetTimeDomainOfPCConfig()[(Index)].SynchronizedTimeBaseIdOfTimeDomain);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidMasterCfg(EthTSyn_TimeValidMasterCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (StbM_SynchronizedTimeBaseType) (EthTSyn_GetTimeValidMasterCfgOfPCConfig()[(Index)].SynchronizedTimeBaseIdOfTimeValidMasterCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CorrectionFieldOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CorrectionFieldOfTimeValidMasterDataType) (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidMasterData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPreciseOriginTimestampOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].PreciseOriginTimestampOfTimeValidMasterData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SequenceIdOfTimeValidMasterDataType) (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SequenceIdOfTimeValidMasterData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcClockIdOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SrcClockIdOfTimeValidMasterDataType) (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidMasterData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcPortNumOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SrcPortNumOfTimeValidMasterDataType) (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidMasterData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateFlagsOfTimeValidMasterDataType) (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].StateFlagsOfTimeValidMasterData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IntVltType) (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SyncEgressTsVltOfTimeValidMasterData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdReqCfg(EthTSyn_TimeValidPdReqCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (StbM_SynchronizedTimeBaseType) (EthTSyn_GetTimeValidPdReqCfgOfPCConfig()[(Index)].SynchronizedTimeBaseIdOfTimeValidPdReqCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CurrPdelayOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CurrPdelayOfTimeValidPdReqDataType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IntVltType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqEgressTsVltOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPdReqRcvdTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqRcvdTsOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdRespClockIdOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdRespClockIdOfTimeValidPdReqDataType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespClockIdOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IntVltType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespIngressTsVltOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdRespPortNumOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdRespPortNumOfTimeValidPdReqDataType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespPortNumOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPdRespSentTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespSentTsOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetRefTimeGlobalOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].RefTimeGlobalOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_VirtualLocalTimeType, ETHTSYN_CODE) EthTSyn_GetRefTimeVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].RefTimeVltOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SequenceIdOfTimeValidPdReqDataType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcClockIdOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SrcClockIdOfTimeValidPdReqDataType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcPortNumOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SrcPortNumOfTimeValidPdReqDataType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateFlagsOfTimeValidPdReqDataType) (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdReqData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidPdRespCfg(EthTSyn_TimeValidPdRespCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (StbM_SynchronizedTimeBaseType) (EthTSyn_GetTimeValidPdRespCfgOfPCConfig()[(Index)].SynchronizedTimeBaseIdOfTimeValidPdRespCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdReqClockIdOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdReqClockIdOfTimeValidPdRespDataType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqClockIdOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IntVltType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqIngressTsVltOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdReqPortNumOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdReqPortNumOfTimeValidPdRespDataType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqPortNumOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IntVltType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdRespEgressTsVltOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetRefTimeGlobalOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].RefTimeGlobalOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_VirtualLocalTimeType, ETHTSYN_CODE) EthTSyn_GetRefTimeVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].RefTimeVltOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SequenceIdOfTimeValidPdRespDataType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcClockIdOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SrcClockIdOfTimeValidPdRespDataType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SrcPortNumOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SrcPortNumOfTimeValidPdRespDataType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateFlagsOfTimeValidPdRespDataType) (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdRespData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_SynchronizedTimeBaseType, ETHTSYN_CODE) EthTSyn_GetSynchronizedTimeBaseIdOfTimeValidSlaveCfg(EthTSyn_TimeValidSlaveCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (StbM_SynchronizedTimeBaseType) (EthTSyn_GetTimeValidSlaveCfgOfPCConfig()[(Index)].SynchronizedTimeBaseIdOfTimeValidSlaveCfg);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CorrectionFieldOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CorrectionFieldOfTimeValidSlaveDataType) (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidSlaveData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CurrPdelayOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_CurrPdelayOfTimeValidSlaveDataType) (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidSlaveData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterClockIdOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterClockIdOfTimeValidSlaveDataType) (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterClockIdOfTimeValidSlaveData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortNumOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortNumOfTimeValidSlaveDataType) (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterPortNumOfTimeValidSlaveData);
}
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeStampShortType, ETHTSYN_CODE) EthTSyn_GetPreciseOriginTimestampOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].PreciseOriginTimestampOfTimeValidSlaveData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SequenceIdOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SequenceIdOfTimeValidSlaveDataType) (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SequenceIdOfTimeValidSlaveData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_StateFlagsOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_StateFlagsOfTimeValidSlaveDataType) (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].StateFlagsOfTimeValidSlaveData);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_GetSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_IntVltType) (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SyncIngressTsVltOfTimeValidSlaveData);
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCGetDeduplicatedInlineFunctions  EthTSyn Get Deduplicated Inline Functions (PRE_COMPILE)
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceSendSmCfgUsedOfMasterPortType, ETHTSYN_CODE) EthTSyn_IsAnnounceSendSmCfgUsedOfMasterPort(EthTSyn_MasterPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AnnounceSendSmCfgUsedOfMasterPortType) (((boolean)(EthTSyn_GetAnnounceSendSmCfgIdxOfMasterPort(Index) != ETHTSYN_NO_ANNOUNCESENDSMCFGIDXOFMASTERPORT)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayInitiatorUsedOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayInitiatorUsedOfPdelayConfigType) (((boolean)(EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(Index) != ETHTSYN_NO_PDELAYINITIATORIDXOFPDELAYCONFIG)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayResponderUsedOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_IsPdelayResponderUsedOfPdelayConfig(EthTSyn_PdelayConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayResponderUsedOfPdelayConfigType) (((boolean)(EthTSyn_GetPdelayResponderIdxOfPdelayConfig(Index) != ETHTSYN_NO_PDELAYRESPONDERIDXOFPDELAYCONFIG)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsMasterPortUsedOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortUsedOfPortType) (((boolean)(EthTSyn_GetMasterPortIdxOfPort(Index) != ETHTSYN_NO_MASTERPORTIDXOFPORT)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayConfigUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsPdelayConfigUsedOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_PdelayConfigUsedOfPortType) (((boolean)(EthTSyn_GetPdelayConfigIdxOfPort(Index) != ETHTSYN_NO_PDELAYCONFIGIDXOFPORT)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsSlavePortUsedOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlavePortUsedOfPortType) (((boolean)(EthTSyn_GetSlavePortIdxOfPort(Index) != ETHTSYN_NO_SLAVEPORTIDXOFPORT)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchPortMgmtUsedOfPortType, ETHTSYN_CODE) EthTSyn_IsSwitchPortMgmtUsedOfPort(EthTSyn_PortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwitchPortMgmtUsedOfPortType) (((boolean)(EthTSyn_GetSwitchPortMgmtIdxOfPort(Index) != ETHTSYN_NO_SWITCHPORTMGMTIDXOFPORT)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfAnnounceInfoType) EthTSyn_GetSizeOfAnnounceInfoOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceReceiveSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceReceiveSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfAnnounceReceiveSmType) EthTSyn_GetSizeOfAnnounceReceiveSmOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceSendSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfAnnounceSendSmType) EthTSyn_GetSizeOfAnnounceSendSmOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfAnnounceSendSmCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfAnnounceSendSmCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfAnnounceSendSmCfgType) EthTSyn_GetSizeOfAnnounceSendSmCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfCtrlType, ETHTSYN_CODE) EthTSyn_GetSizeOfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfCtrlType) EthTSyn_GetSizeOfCtrlOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfCtrlStateType, ETHTSYN_CODE) EthTSyn_GetSizeOfCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfCtrlStateType) EthTSyn_GetSizeOfCtrlStateOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfDestinationMacType, ETHTSYN_CODE) EthTSyn_GetSizeOfDestinationMac(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfDestinationMacType) EthTSyn_GetSizeOfDestinationMacOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfFollowUpDataIdListType, ETHTSYN_CODE) EthTSyn_GetSizeOfFollowUpDataIdList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfFollowUpDataIdListType) EthTSyn_GetSizeOfFollowUpDataIdListOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfMasterPortType, ETHTSYN_CODE) EthTSyn_GetSizeOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfMasterPortType) EthTSyn_GetSizeOfMasterPortOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfMasterPortIdentityType, ETHTSYN_CODE) EthTSyn_GetSizeOfMasterPortIdentity(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfMasterPortIdentityType) EthTSyn_GetSizeOfMasterPortIdentityOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfOffsetTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSizeOfOffsetTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfOffsetTimeDomainType) EthTSyn_GetSizeOfOffsetTimeDomainOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfOfsCorrDurationInSyncCyclesType, ETHTSYN_CODE) EthTSyn_GetSizeOfOfsCorrDurationInSyncCycles(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfOfsCorrDurationInSyncCyclesType) EthTSyn_GetSizeOfOfsCorrDurationInSyncCyclesOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayConfigType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPdelayConfigType) EthTSyn_GetSizeOfPdelayConfigOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPdelayInfoType) EthTSyn_GetSizeOfPdelayInfoOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayInitiatorType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPdelayInitiatorType) EthTSyn_GetSizeOfPdelayInitiatorOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayReqSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayReqSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPdelayReqSmType) EthTSyn_GetSizeOfPdelayReqSmOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayRespSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayRespSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPdelayRespSmType) EthTSyn_GetSizeOfPdelayRespSmOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPdelayResponderType, ETHTSYN_CODE) EthTSyn_GetSizeOfPdelayResponder(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPdelayResponderType) EthTSyn_GetSizeOfPdelayResponderOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPhysPortType, ETHTSYN_CODE) EthTSyn_GetSizeOfPhysPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPhysPortType) EthTSyn_GetSizeOfPhysPortOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPhysPortCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfPhysPortCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPhysPortCfgType) EthTSyn_GetSizeOfPhysPortCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPortType, ETHTSYN_CODE) EthTSyn_GetSizeOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPortType) EthTSyn_GetSizeOfPortOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPortIndType, ETHTSYN_CODE) EthTSyn_GetSizeOfPortInd(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPortIndType) EthTSyn_GetSizeOfPortIndOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfPortSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfPortSyncSendSmType) EthTSyn_GetSizeOfPortSyncSendSmOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfRateMeasurementType, ETHTSYN_CODE) EthTSyn_GetSizeOfRateMeasurement(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfRateMeasurementType) EthTSyn_GetSizeOfRateMeasurementOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSlavePortType, ETHTSYN_CODE) EthTSyn_GetSizeOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSlavePortType) EthTSyn_GetSizeOfSlavePortOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSlaveSwitchIdxListType, ETHTSYN_CODE) EthTSyn_GetSizeOfSlaveSwitchIdxList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSlaveSwitchIdxListType) EthTSyn_GetSizeOfSlaveSwitchIdxListOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchPortMgmtType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchPortMgmt(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwitchPortMgmtType) EthTSyn_GetSizeOfSwitchPortMgmtOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchSyncFrameCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwitchSyncFrameCfgType) EthTSyn_GetSizeOfSwitchSyncFrameCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchSyncFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwitchSyncFrameInfoType) EthTSyn_GetSizeOfSwitchSyncFrameInfoOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchSyncFrameTxFrameInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchSyncFrameTxFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwitchSyncFrameTxFrameInfoType) EthTSyn_GetSizeOfSwitchSyncFrameTxFrameInfoOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwitchTimeSyncCfgType) EthTSyn_GetSizeOfSwitchTimeSyncCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwitchTimeSyncInfoType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwitchTimeSyncInfoType) EthTSyn_GetSizeOfSwitchTimeSyncInfoOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwtMgmtRcvdMsgBufType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwtMgmtRcvdMsgBuf(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwtMgmtRcvdMsgBufType) EthTSyn_GetSizeOfSwtMgmtRcvdMsgBufOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSwtTimeSyncRateRegulatorCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSwtTimeSyncRateRegulatorCfgType) EthTSyn_GetSizeOfSwtTimeSyncRateRegulatorCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSyncReceiveSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfSyncReceiveSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSyncReceiveSmType) EthTSyn_GetSizeOfSyncReceiveSmOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSyncSendSmType, ETHTSYN_CODE) EthTSyn_GetSizeOfSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSyncSendSmType) EthTSyn_GetSizeOfSyncSendSmOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfSystemStateType, ETHTSYN_CODE) EthTSyn_GetSizeOfSystemState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfSystemStateType) EthTSyn_GetSizeOfSystemStateOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeBaseUpdateCounterType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeBaseUpdateCounter(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeBaseUpdateCounterType) EthTSyn_GetSizeOfTimeBaseUpdateCounterOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeDomainType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeDomainType) EthTSyn_GetSizeOfTimeDomainOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidMasterCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidMasterCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidMasterCfgType) EthTSyn_GetSizeOfTimeValidMasterCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidMasterDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidMasterDataType) EthTSyn_GetSizeOfTimeValidMasterDataOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdReqCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdReqCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidPdReqCfgType) EthTSyn_GetSizeOfTimeValidPdReqCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdReqDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidPdReqDataType) EthTSyn_GetSizeOfTimeValidPdReqDataOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdRespCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdRespCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidPdRespCfgType) EthTSyn_GetSizeOfTimeValidPdRespCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidPdRespDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidPdRespDataType) EthTSyn_GetSizeOfTimeValidPdRespDataOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidSlaveCfgType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidSlaveCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidSlaveCfgType) EthTSyn_GetSizeOfTimeValidSlaveCfgOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SizeOfTimeValidSlaveDataType, ETHTSYN_CODE) EthTSyn_GetSizeOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SizeOfTimeValidSlaveDataType) EthTSyn_GetSizeOfTimeValidSlaveDataOfPCConfig();
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceInfoUsedOfSlavePortType, ETHTSYN_CODE) EthTSyn_IsAnnounceInfoUsedOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_AnnounceInfoUsedOfSlavePortType) (((boolean)(EthTSyn_GetAnnounceInfoIdxOfSlavePort(Index) != ETHTSYN_NO_ANNOUNCEINFOIDXOFSLAVEPORT)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortIdentityUsedOfSlavePortType, ETHTSYN_CODE) EthTSyn_IsMasterPortIdentityUsedOfSlavePort(EthTSyn_SlavePortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortIdentityUsedOfSlavePortType) (((boolean)(EthTSyn_GetMasterPortIdentityIdxOfSlavePort(Index) != ETHTSYN_NO_MASTERPORTIDENTITYIDXOFSLAVEPORT)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlaveSwitchIdxListUsedOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_IsSlaveSwitchIdxListUsedOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlaveSwitchIdxListUsedOfSwitchTimeSyncCfgType) (((boolean)(EthTSyn_GetSlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg(Index) != ETHTSYN_NO_SLAVESWITCHIDXLISTSTARTIDXOFSWITCHTIMESYNCCFG)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwitchSyncFrameCfgUsedOfSwitchTimeSyncCfgType, ETHTSYN_CODE) EthTSyn_IsSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(EthTSyn_SwitchTimeSyncCfgIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwitchSyncFrameCfgUsedOfSwitchTimeSyncCfgType) (((boolean)(EthTSyn_GetSwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg(Index) != ETHTSYN_NO_SWITCHSYNCFRAMECFGIDXOFSWITCHTIMESYNCCFG)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FollowUpDataIdListUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsFollowUpDataIdListUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_FollowUpDataIdListUsedOfTimeDomainType) (((boolean)(EthTSyn_GetFollowUpDataIdListStartIdxOfTimeDomain(Index) != ETHTSYN_NO_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_MasterPortUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsMasterPortUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_MasterPortUsedOfTimeDomainType) (((boolean)(EthTSyn_GetMasterPortLengthOfTimeDomain(Index) != 0u)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_OffsetTimeDomainUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsOffsetTimeDomainUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_OffsetTimeDomainUsedOfTimeDomainType) (((boolean)(EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(Index) != ETHTSYN_NO_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN)) != FALSE);
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SlavePortUsedOfTimeDomainType, ETHTSYN_CODE) EthTSyn_IsSlavePortUsedOfTimeDomain(EthTSyn_TimeDomainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SlavePortUsedOfTimeDomainType) (((boolean)(EthTSyn_GetSlavePortStartIdxOfTimeDomain(Index) != ETHTSYN_NO_SLAVEPORTSTARTIDXOFTIMEDOMAIN)) != FALSE);
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCSetDataInlineFunctions  EthTSyn Set Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to write data.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAnnounceReceiveSm(EthTSyn_AnnounceReceiveSmIterType Index, EthTSyn_AnnounceReceiveSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetAnnounceReceiveSmOfPCConfig()[(Index)] = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].AnnounceCycleTimerOfAnnounceSendSm = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_StateOfAnnounceSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].StateOfAnnounceSendSm = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCtrlState(EthTSyn_CtrlStateIterType Index, EthTSyn_CtrlStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetCtrlStateOfPCConfig()[(Index)] = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].CounterOfOfsCorrDurationInSyncCycles = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRestartedOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_RestartedOfOfsCorrDurationInSyncCyclesType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].RestartedOfOfsCorrDurationInSyncCycles = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAsCapableOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_AsCapableOfPdelayInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].AsCapableOfPdelayInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_PdelayType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].PdelayValueNsOfPdelayInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetUseAverageOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_UseAverageOfPdelayInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].UseAverageOfPdelayInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdelayReqSm(EthTSyn_PdelayReqSmIterType Index, EthTSyn_PdelayReqSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPdelayReqSmOfPCConfig()[(Index)] = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdelayRespSm(EthTSyn_PdelayRespSmIterType Index, EthTSyn_PdelayRespSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPdelayRespSmOfPCConfig()[(Index)] = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index, EthTSyn_DebounceTimerOfPhysPortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPhysPortOfPCConfig()[(Index)].DebounceTimerOfPhysPort = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_StateOfPortSyncSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].StateOfPortSyncSendSm = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncHostEgrIntVltMgmtOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_IntVltMgmtType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].SyncHostEgrIntVltMgmtOfPortSyncSendSm = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncTxConfCalledOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_SyncTxConfCalledOfPortSyncSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].SyncTxConfCalledOfPortSyncSendSm = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_TxBufIdxOfPortSyncSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufIdxOfPortSyncSendSm = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetTxBufPtrOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_EthConstBufferPtrType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufPtrOfPortSyncSendSm = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAccumulatedMasterTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_AccumulatedMasterTimeDiffOfRateMeasurementType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].AccumulatedMasterTimeDiffOfRateMeasurement = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetAccumulatedSwtTimeDiffOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_AccumulatedSwtTimeDiffOfRateMeasurementType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].AccumulatedSwtTimeDiffOfRateMeasurement = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveNrOfSyncCyclesOfRateMeasurement = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetActiveOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveOfRateMeasurementType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveOfRateMeasurement = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPreciseOriginTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_TsMgmtStructType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].PreciseOriginTsMgmtOfSwitchSyncFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SequenceIdOfSwitchSyncFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SequenceIdOfSwitchSyncFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_StateOfSwitchSyncFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].StateOfSwitchSyncFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtIngressTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_TsMgmtStructType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SwtIngressTsMgmtOfSwitchSyncFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SyncTxCntOfSwitchSyncFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetBufAddrOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_EthBufferPtrType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufAddrOfSwitchSyncFrameTxFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufIdxOfSwitchSyncFrameTxFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetGlobalTimeOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_GlobalTimestampType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].GlobalTimeOfSwitchSyncFrameTxFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].IntVltOfSwitchSyncFrameTxFrameInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].CurrentOffsetNsOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].LastCorrectedOffsetNsOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].OutOfSyncCntOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPrevTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SwtTimeSync_TimestampInfoStructType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].PrevTimeStampInfoOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_StateOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].StateOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtSyncStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SwtSyncStateOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SyncEventTimeoutCntOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SwtTimeSync_TimestampInfoStructType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].TimeStampInfoOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetWasSyncReachedOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_WasSyncReachedOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].WasSyncReachedOfSwitchTimeSyncInfo = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index, EthTSyn_SwtMgmtRcvdMsgBufType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()[(Index)] = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtRxBufQueueCurrProcIdx(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig())) = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtRxBufQueueFreeIdx(EthTSyn_SwtMgmtRxBufQueueFreeIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig())) = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtTxMgmtObjQueueCurrProcIdx(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig())) = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSwtMgmtTxMgmtObjQueueFreeIdx(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig())) = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncReceiveSm(EthTSyn_SyncReceiveSmIterType Index, EthTSyn_SyncReceiveSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSyncReceiveSmOfPCConfig()[(Index)] = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncSendSm(EthTSyn_SyncSendSmIterType Index, EthTSyn_SyncSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSyncSendSmOfPCConfig()[(Index)] = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmClockIdentityOfSystemStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmClockIdentityOfSystemState = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetGmPresentOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmPresentOfSystemStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmPresentOfSystemState = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetValidOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValidOfTimeBaseUpdateCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValidOfTimeBaseUpdateCounter = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValueOfTimeBaseUpdateCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValueOfTimeBaseUpdateCounter = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidMasterData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPreciseOriginTimestampOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, StbM_TimeStampShortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].PreciseOriginTimestampOfTimeValidMasterData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SequenceIdOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SequenceIdOfTimeValidMasterData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcClockIdOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidMasterData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcPortNumOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidMasterData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_StateFlagsOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].StateFlagsOfTimeValidMasterData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SyncEgressTsVltOfTimeValidMasterData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_CurrPdelayOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqEgressTsVltOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqRcvdTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_TimeStampShortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqRcvdTsOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespClockIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespClockIdOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespIngressTsVltOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespPortNumOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespPortNumOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespSentTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_TimeStampShortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespSentTsOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeGlobalOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_TimeStampShortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].RefTimeGlobalOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, StbM_VirtualLocalTimeType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].RefTimeVltOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdReqData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqClockIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqClockIdOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqIngressTsVltOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqPortNumOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqPortNumOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdRespEgressTsVltOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeGlobalOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, StbM_TimeStampShortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].RefTimeGlobalOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetRefTimeVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, StbM_VirtualLocalTimeType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].RefTimeVltOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdRespData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidSlaveData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CurrPdelayOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidSlaveData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterClockIdOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterClockIdOfTimeValidSlaveData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterPortNumOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterPortNumOfTimeValidSlaveData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetPreciseOriginTimestampOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, StbM_TimeStampShortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].PreciseOriginTimestampOfTimeValidSlaveData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_SequenceIdOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SequenceIdOfTimeValidSlaveData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_StateFlagsOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].StateFlagsOfTimeValidSlaveData = (Value);
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SyncIngressTsVltOfTimeValidSlaveData = (Value);
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCGetAddressOfDataInlineFunctions  EthTSyn Get Address Of Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_AnnounceReceiveSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrAnnounceReceiveSm(EthTSyn_AnnounceReceiveSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetAnnounceReceiveSmOfPCConfig()[(Index)]));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_CtrlStatePtrType, ETHTSYN_CODE) EthTSyn_GetAddrCtrlState(EthTSyn_CtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetCtrlStateOfPCConfig()[(Index)]));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayReqSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdelayReqSm(EthTSyn_PdelayReqSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetPdelayReqSmOfPCConfig()[(Index)]));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdelayRespSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdelayRespSm(EthTSyn_PdelayRespSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetPdelayRespSmOfPCConfig()[(Index)]));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncHostEgrIntVltMgmtOfPortSyncSendSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSyncHostEgrIntVltMgmtOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].SyncHostEgrIntVltMgmtOfPortSyncSendSm));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TxBufPtrOfPortSyncSendSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrTxBufPtrOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufPtrOfPortSyncSendSm));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PreciseOriginTsMgmtOfSwitchSyncFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].PreciseOriginTsMgmtOfSwitchSyncFrameInfo));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtIngressTsMgmtOfSwitchSyncFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SwtIngressTsMgmtOfSwitchSyncFrameInfo));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_BufAddrOfSwitchSyncFrameTxFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrBufAddrOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufAddrOfSwitchSyncFrameTxFrameInfo));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_GlobalTimeOfSwitchSyncFrameTxFrameInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrGlobalTimeOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].GlobalTimeOfSwitchSyncFrameTxFrameInfo));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PrevTimeStampInfoOfSwitchTimeSyncInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPrevTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].PrevTimeStampInfoOfSwitchTimeSyncInfo));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtSyncStateOfSwitchTimeSyncInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtSyncStateOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SwtSyncStateOfSwitchTimeSyncInfo));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeStampInfoOfSwitchTimeSyncInfoPtrType, ETHTSYN_CODE) EthTSyn_GetAddrTimeStampInfoOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].TimeStampInfoOfSwitchTimeSyncInfo));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRcvdMsgBufPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtRcvdMsgBufPtrType) (&(EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()[(Index)]));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtRxBufQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtRxBufQueueCurrProcIdxPtrType) (&((*(EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig()))));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtRxBufQueueFreeIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtRxBufQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtRxBufQueueFreeIdxPtrType) (&((*(EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig()))));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxPtrType) (&((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig()))));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxPtrType) (&((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig()))));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncReceiveSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSyncReceiveSm(EthTSyn_SyncReceiveSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSyncReceiveSmOfPCConfig()[(Index)]));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncSendSmPtrType, ETHTSYN_CODE) EthTSyn_GetAddrSyncSendSm(EthTSyn_SyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetSyncSendSmOfPCConfig()[(Index)]));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PreciseOriginTimestampOfTimeValidMasterDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPreciseOriginTimestampOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].PreciseOriginTimestampOfTimeValidMasterData));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdReqRcvdTsOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdReqRcvdTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqRcvdTsOfTimeValidPdReqData));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PdRespSentTsOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPdRespSentTsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespSentTsOfTimeValidPdReqData));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeGlobalOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeGlobalOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].RefTimeGlobalOfTimeValidPdReqData));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeVltOfTimeValidPdReqDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].RefTimeVltOfTimeValidPdReqData));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeGlobalOfTimeValidPdRespDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeGlobalOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].RefTimeGlobalOfTimeValidPdRespData));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_RefTimeVltOfTimeValidPdRespDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrRefTimeVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].RefTimeVltOfTimeValidPdRespData));
}
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PreciseOriginTimestampOfTimeValidSlaveDataPtrType, ETHTSYN_CODE) EthTSyn_GetAddrPreciseOriginTimestampOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].PreciseOriginTimestampOfTimeValidSlaveData));
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCHasInlineFunctions  EthTSyn Has Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetAnnounceInfoOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceAllowedRxDelayOfAnnounceInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMaxeStepsRemovedOfAnnounceInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceReceiveSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetAnnounceReceiveSmOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetAnnounceSendSmOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceCycleTimerOfAnnounceSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfAnnounceSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetAnnounceSendSmCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceTxCycleOfAnnounceSendSmCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetCtrlOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasEthIfCtrlIdxOfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIndEndIdxOfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIndStartIdxOfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetCtrlStateOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDestinationMac(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetDestinationMacOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetFollowUpDataIdListOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetMasterPortOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfgIdxOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfgUsedOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCrcTimeFlagsOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCyclicMsgResumeCntOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpMsgLengthOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpSentCbkPtrOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasImmediateTimeSyncOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsSubTlvOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStatusSubTlvOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncLogMsgIntervalOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSendIntervalOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSentCbkPtrOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeSubTlvOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxCrcSecuredOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUserDataSubTlvOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentity(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetMasterPortIdentityOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasClockIdentityOfMasterPortIdentity(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetOffsetTimeDomainOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasIdOfOffsetTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfOffsetTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsCorrDurationInSyncCycles(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCounterOfOfsCorrDurationInSyncCycles(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRestartedOfOfsCorrDurationInSyncCycles(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPdelayConfigOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAlwaysAsCapableOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasInitialPdelayNsOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiatorIdxOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiatorUsedOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponderIdxOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponderUsedOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUseStaticPdelayOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPdelayInfoOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAsCapableOfPdelayInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayValueNsOfPdelayInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUseAverageOfPdelayInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPdelayInitiatorOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAllowedLostResponsesOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAverageWeightOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasLogMessageIntervalOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayReqSmIdxOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayThresholdOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRespRespFollowUpTimeoutOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxIntervalMfOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayReqSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPdelayReqSmOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayRespSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPdelayRespSmOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponder(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPdelayResponderOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayRespSmIdxOfPdelayResponder(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPhysPortOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDebounceTimerOfPhysPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPhysPortCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDebounceTimeOfPhysPortCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPortOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlIdxOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFramePrioOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdxOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortUsedOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasNumberOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfigIdxOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfigUsedOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortCfgIdxOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortIdxOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortUsedOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStbMTimeSrcEqualOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmtIdxOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmtUsedOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomainIdxOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortInd(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPortIndOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetPortSyncSendSmOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncHostEgrIntVltMgmtOfPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncTxConfCalledOfPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxBufIdxOfPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTxBufPtrOfPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurement(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetRateMeasurementOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAccumulatedMasterTimeDiffOfRateMeasurement(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAccumulatedSwtTimeDiffOfRateMeasurement(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasActiveNrOfSyncCyclesOfRateMeasurement(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasActiveOfRateMeasurement(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceReceiveSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSmCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfDestinationMac(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfFollowUpDataIdList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPortIdentity(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOffsetTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOfsCorrDurationInSyncCycles(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInitiator(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayReqSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayRespSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayResponder(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPortCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortInd(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfRateMeasurement(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlaveSwitchIdxList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchPortMgmt(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameTxFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtMgmtRcvdMsgBuf(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncReceiveSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSystemState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeBaseUpdateCounter(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSlavePortOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfoIdxOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfoUsedOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCrcFlagsRxValidatedOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpAllowedRxDelayOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentityIdxOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentityUsedOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRxCrcValidatedOfSlavePort(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSlaveSwitchIdxListOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmt(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwitchPortMgmtOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfSwitchPortMgmt(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchIdxOfSwitchPortMgmt(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwitchSyncFrameCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasEthIfCtrlIdxOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFramePrioOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIdxOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncTxIntervalOfSwitchSyncFrameCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPreciseOriginTsMgmtOfSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtIngressTsMgmtOfSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncTxCntOfSwitchSyncFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameTxFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasBufAddrOfSwitchSyncFrameTxFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasBufIdxOfSwitchSyncFrameTxFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasGlobalTimeOfSwitchSyncFrameTxFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasIntVltOfSwitchSyncFrameTxFrameInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwitchTimeSyncCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasEthIfSwitchIdxOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMaxOutOfSyncCntOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListUsedOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncEventTimeoutOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncPrecisionLimitNsOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomainIdxOfSwitchTimeSyncCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCurrentOffsetNsOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasLastCorrectedOffsetNsOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOutOfSyncCntOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPrevTimeStampInfoOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtSyncStateOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncEventTimeoutCntOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeStampInfoOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasWasSyncReachedOfSwitchTimeSyncInfo(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRcvdMsgBuf(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSwtTimeSyncRateRegulatorCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasNrParallelRateMeasurementsOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasNrSyncCyclesForOfsCorrOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsJumpCorrThresholdNsOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementEndIdxOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementLengthOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementStartIdxOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateRatioMinOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasUseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncReceiveSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSyncReceiveSmOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSendSm(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSyncSendSmOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSystemState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetSystemStateOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasGmClockIdentityOfSystemState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasGmPresentOfSystemState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeBaseUpdateCounter(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeBaseUpdateCounterOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasValidOfTimeBaseUpdateCounter(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasValueOfTimeBaseUpdateCounter(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeDomainOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListEndIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListStartIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListUsedOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasIdOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasImmediateTimeSyncOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortEndIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortLengthOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortStartIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortUsedOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainEndIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainStartIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainUsedOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortEndIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortStartIdxOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortUsedOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeDomain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidMasterCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidMasterCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidMasterDataOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCorrectionFieldOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPreciseOriginTimestampOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcClockIdOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcPortNumOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncEgressTsVltOfTimeValidMasterData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidPdReqCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidPdReqCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidPdReqDataOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCurrPdelayOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqEgressTsVltOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqRcvdTsOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespClockIdOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespIngressTsVltOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespPortNumOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespSentTsOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeGlobalOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeVltOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcClockIdOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcPortNumOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidPdReqData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidPdRespCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidPdRespCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidPdRespDataOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqClockIdOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqIngressTsVltOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdReqPortNumOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdRespEgressTsVltOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeGlobalOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRefTimeVltOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcClockIdOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSrcPortNumOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidPdRespData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidSlaveCfgOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSynchronizedTimeBaseIdOfTimeValidSlaveCfg(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (EthTSyn_GetTimeValidSlaveDataOfPCConfig() != NULL_PTR);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCorrectionFieldOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCurrPdelayOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterClockIdOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortNumOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPreciseOriginTimestampOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSequenceIdOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasStateFlagsOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncIngressTsVltOfTimeValidSlaveData(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceReceiveSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasAnnounceSendSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasCtrlStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasDestinationMacOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasFollowUpDataIdListOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortIdentityOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasMasterPortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOffsetTimeDomainOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasOfsCorrDurationInSyncCyclesOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayInitiatorOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayReqSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayRespSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPdelayResponderOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPhysPortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortIndOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasPortSyncSendSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasRateMeasurementOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceReceiveSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSmCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfAnnounceSendSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfCtrlStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfDestinationMacOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfFollowUpDataIdListOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPortIdentityOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfMasterPortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOffsetTimeDomainOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfOfsCorrDurationInSyncCyclesOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayInitiatorOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayReqSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayRespSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPdelayResponderOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPortCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPhysPortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortIndOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfPortSyncSendSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfRateMeasurementOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlavePortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSlaveSwitchIdxListOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchPortMgmtOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchSyncFrameTxFrameInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwitchTimeSyncInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtMgmtRcvdMsgBufOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSwtTimeSyncRateRegulatorCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncReceiveSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSyncSendSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfSystemStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeBaseUpdateCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeDomainOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidMasterDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdReqDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidPdRespDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSizeOfTimeValidSlaveDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlavePortOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSlaveSwitchIdxListOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchPortMgmtOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchSyncFrameTxFrameInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwitchTimeSyncInfoOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRcvdMsgBufOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueCurrProcIdxOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtRxBufQueueFreeIdxOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSwtTimeSyncRateRegulatorCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncReceiveSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSyncSendSmOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasSystemStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeBaseUpdateCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeDomainOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidMasterDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdReqDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidPdRespDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveCfgOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_HasTimeValidSlaveDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995 */  /* MD_MSR_ConstantCondition */
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCIncrementInlineFunctions  EthTSyn Increment Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].AnnounceCycleTimerOfAnnounceSendSm++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].CounterOfOfsCorrDurationInSyncCycles++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].PdelayValueNsOfPdelayInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPhysPortOfPCConfig()[(Index)].DebounceTimerOfPhysPort++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufIdxOfPortSyncSendSm++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveNrOfSyncCyclesOfRateMeasurement++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SequenceIdOfSwitchSyncFrameInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SyncTxCntOfSwitchSyncFrameInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufIdxOfSwitchSyncFrameTxFrameInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].IntVltOfSwitchSyncFrameTxFrameInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].CurrentOffsetNsOfSwitchTimeSyncInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].LastCorrectedOffsetNsOfSwitchTimeSyncInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].OutOfSyncCntOfSwitchTimeSyncInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SyncEventTimeoutCntOfSwitchTimeSyncInfo++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()[(Index)]++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtRxBufQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig()))++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtRxBufQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig()))++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtTxMgmtObjQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig()))++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSwtMgmtTxMgmtObjQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig()))++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmClockIdentityOfSystemState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValueOfTimeBaseUpdateCounter++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidMasterData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SequenceIdOfTimeValidMasterData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidMasterData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidMasterData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].StateFlagsOfTimeValidMasterData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SyncEgressTsVltOfTimeValidMasterData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqEgressTsVltOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespClockIdOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespIngressTsVltOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespPortNumOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdReqData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqClockIdOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqIngressTsVltOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqPortNumOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdRespEgressTsVltOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdRespData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidSlaveData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidSlaveData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterClockIdOfTimeValidSlaveData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterPortNumOfTimeValidSlaveData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SequenceIdOfTimeValidSlaveData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].StateFlagsOfTimeValidSlaveData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_IncSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SyncIngressTsVltOfTimeValidSlaveData++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCDecrementInlineFunctions  EthTSyn Decrement Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].AnnounceCycleTimerOfAnnounceSendSm--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].CounterOfOfsCorrDurationInSyncCycles--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].PdelayValueNsOfPdelayInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPhysPortOfPCConfig()[(Index)].DebounceTimerOfPhysPort--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufIdxOfPortSyncSendSm--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveNrOfSyncCyclesOfRateMeasurement--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SequenceIdOfSwitchSyncFrameInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SyncTxCntOfSwitchSyncFrameInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufIdxOfSwitchSyncFrameTxFrameInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].IntVltOfSwitchSyncFrameTxFrameInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].CurrentOffsetNsOfSwitchTimeSyncInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].LastCorrectedOffsetNsOfSwitchTimeSyncInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].OutOfSyncCntOfSwitchTimeSyncInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SyncEventTimeoutCntOfSwitchTimeSyncInfo--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()[(Index)]--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtRxBufQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig()))--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtRxBufQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig()))--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtTxMgmtObjQueueCurrProcIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig()))--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSwtMgmtTxMgmtObjQueueFreeIdx(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  (*(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig()))--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmClockIdentityOfSystemState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValueOfTimeBaseUpdateCounter--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidMasterData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SequenceIdOfTimeValidMasterData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidMasterData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidMasterData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].StateFlagsOfTimeValidMasterData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SyncEgressTsVltOfTimeValidMasterData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqEgressTsVltOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespClockIdOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespIngressTsVltOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespPortNumOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdReqData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqClockIdOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqIngressTsVltOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqPortNumOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdRespEgressTsVltOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdRespData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidSlaveData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidSlaveData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterClockIdOfTimeValidSlaveData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterPortNumOfTimeValidSlaveData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SequenceIdOfTimeValidSlaveData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].StateFlagsOfTimeValidSlaveData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_DecSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SyncIngressTsVltOfTimeValidSlaveData--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCAddInlineFunctions  EthTSyn Add Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to add VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetAnnounceCycleTimerOfAnnounceSendSm(Index, (EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].AnnounceCycleTimerOfAnnounceSendSm + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(Index, (EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].CounterOfOfsCorrDurationInSyncCycles + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_PdelayType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdelayValueNsOfPdelayInfo(Index, (EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].PdelayValueNsOfPdelayInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index, EthTSyn_DebounceTimerOfPhysPortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetDebounceTimerOfPhysPort(Index, (EthTSyn_GetPhysPortOfPCConfig()[(Index)].DebounceTimerOfPhysPort + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_TxBufIdxOfPortSyncSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetTxBufIdxOfPortSyncSendSm(Index, (EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufIdxOfPortSyncSendSm + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetActiveNrOfSyncCyclesOfRateMeasurement(Index, (EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveNrOfSyncCyclesOfRateMeasurement + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SequenceIdOfSwitchSyncFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfSwitchSyncFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SequenceIdOfSwitchSyncFrameInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SyncTxCntOfSwitchSyncFrameInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufIdxOfSwitchSyncFrameTxFrameInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetIntVltOfSwitchSyncFrameTxFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].IntVltOfSwitchSyncFrameTxFrameInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].CurrentOffsetNsOfSwitchTimeSyncInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].LastCorrectedOffsetNsOfSwitchTimeSyncInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].OutOfSyncCntOfSwitchTimeSyncInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SyncEventTimeoutCntOfSwitchTimeSyncInfo + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index, EthTSyn_SwtMgmtRcvdMsgBufType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtRcvdMsgBuf(Index, (EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()[(Index)] + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtRxBufQueueCurrProcIdx(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtRxBufQueueCurrProcIdx(((*(EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig())) + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtRxBufQueueFreeIdx(EthTSyn_SwtMgmtRxBufQueueFreeIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtRxBufQueueFreeIdx(((*(EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig())) + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtTxMgmtObjQueueCurrProcIdx(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtTxMgmtObjQueueCurrProcIdx(((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig())) + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSwtMgmtTxMgmtObjQueueFreeIdx(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtTxMgmtObjQueueFreeIdx(((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig())) + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmClockIdentityOfSystemStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetGmClockIdentityOfSystemState(Index, (EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmClockIdentityOfSystemState + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValueOfTimeBaseUpdateCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetValueOfTimeBaseUpdateCounter(Index, (EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValueOfTimeBaseUpdateCounter + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCorrectionFieldOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidMasterData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SequenceIdOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SequenceIdOfTimeValidMasterData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcClockIdOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcClockIdOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidMasterData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcPortNumOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcPortNumOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidMasterData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_StateFlagsOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].StateFlagsOfTimeValidMasterData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncEgressTsVltOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SyncEgressTsVltOfTimeValidMasterData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_CurrPdelayOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCurrPdelayOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqEgressTsVltOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqEgressTsVltOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespClockIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespClockIdOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespClockIdOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespIngressTsVltOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespIngressTsVltOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespPortNumOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespPortNumOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespPortNumOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcClockIdOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcPortNumOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdReqData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqClockIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqClockIdOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqClockIdOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqIngressTsVltOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqIngressTsVltOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqPortNumOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqPortNumOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqPortNumOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespEgressTsVltOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdRespEgressTsVltOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcClockIdOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcPortNumOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdRespData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCorrectionFieldOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidSlaveData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CurrPdelayOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCurrPdelayOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidSlaveData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterClockIdOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetMasterClockIdOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterClockIdOfTimeValidSlaveData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterPortNumOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetMasterPortNumOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterPortNumOfTimeValidSlaveData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_SequenceIdOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SequenceIdOfTimeValidSlaveData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_StateFlagsOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].StateFlagsOfTimeValidSlaveData + Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_AddSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncIngressTsVltOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SyncIngressTsVltOfTimeValidSlaveData + Value));
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define ETHTSYN_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  EthTSynPCSubstractInlineFunctions  EthTSyn Substract Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to substract VAR data with numerical nature.
  \{
*/ 
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubAnnounceCycleTimerOfAnnounceSendSm(EthTSyn_AnnounceSendSmIterType Index, EthTSyn_AnnounceCycleTimerOfAnnounceSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetAnnounceCycleTimerOfAnnounceSendSm(Index, (EthTSyn_GetAnnounceSendSmOfPCConfig()[(Index)].AnnounceCycleTimerOfAnnounceSendSm - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCounterOfOfsCorrDurationInSyncCycles(EthTSyn_OfsCorrDurationInSyncCyclesIterType Index, EthTSyn_CounterOfOfsCorrDurationInSyncCyclesType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCounterOfOfsCorrDurationInSyncCycles(Index, (EthTSyn_GetOfsCorrDurationInSyncCyclesOfPCConfig()[(Index)].CounterOfOfsCorrDurationInSyncCycles - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdelayValueNsOfPdelayInfo(EthTSyn_PdelayInfoIterType Index, EthTSyn_PdelayType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdelayValueNsOfPdelayInfo(Index, (EthTSyn_GetPdelayInfoOfPCConfig()[(Index)].PdelayValueNsOfPdelayInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubDebounceTimerOfPhysPort(EthTSyn_PhysPortIterType Index, EthTSyn_DebounceTimerOfPhysPortType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetDebounceTimerOfPhysPort(Index, (EthTSyn_GetPhysPortOfPCConfig()[(Index)].DebounceTimerOfPhysPort - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubTxBufIdxOfPortSyncSendSm(EthTSyn_PortSyncSendSmIterType Index, EthTSyn_TxBufIdxOfPortSyncSendSmType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetTxBufIdxOfPortSyncSendSm(Index, (EthTSyn_GetPortSyncSendSmOfPCConfig()[(Index)].TxBufIdxOfPortSyncSendSm - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubActiveNrOfSyncCyclesOfRateMeasurement(EthTSyn_RateMeasurementIterType Index, EthTSyn_ActiveNrOfSyncCyclesOfRateMeasurementType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetActiveNrOfSyncCyclesOfRateMeasurement(Index, (EthTSyn_GetRateMeasurementOfPCConfig()[(Index)].ActiveNrOfSyncCyclesOfRateMeasurement - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SequenceIdOfSwitchSyncFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfSwitchSyncFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SequenceIdOfSwitchSyncFrameInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncTxCntOfSwitchSyncFrameInfo(EthTSyn_SwitchSyncFrameInfoIterType Index, EthTSyn_SyncTxCntOfSwitchSyncFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameInfoOfPCConfig()[(Index)].SyncTxCntOfSwitchSyncFrameInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubBufIdxOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_BufIdxOfSwitchSyncFrameTxFrameInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].BufIdxOfSwitchSyncFrameTxFrameInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubIntVltOfSwitchSyncFrameTxFrameInfo(EthTSyn_SwitchSyncFrameTxFrameInfoIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetIntVltOfSwitchSyncFrameTxFrameInfo(Index, (EthTSyn_GetSwitchSyncFrameTxFrameInfoOfPCConfig()[(Index)].IntVltOfSwitchSyncFrameTxFrameInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCurrentOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_CurrentOffsetNsOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].CurrentOffsetNsOfSwitchTimeSyncInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubLastCorrectedOffsetNsOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_LastCorrectedOffsetNsOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].LastCorrectedOffsetNsOfSwitchTimeSyncInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubOutOfSyncCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_OutOfSyncCntOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].OutOfSyncCntOfSwitchTimeSyncInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncEventTimeoutCntOfSwitchTimeSyncInfo(EthTSyn_SwitchTimeSyncInfoIterType Index, EthTSyn_SyncEventTimeoutCntOfSwitchTimeSyncInfoType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(Index, (EthTSyn_GetSwitchTimeSyncInfoOfPCConfig()[(Index)].SyncEventTimeoutCntOfSwitchTimeSyncInfo - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtRcvdMsgBuf(EthTSyn_SwtMgmtRcvdMsgBufIterType Index, EthTSyn_SwtMgmtRcvdMsgBufType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtRcvdMsgBuf(Index, (EthTSyn_GetSwtMgmtRcvdMsgBufOfPCConfig()[(Index)] - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtRxBufQueueCurrProcIdx(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtRxBufQueueCurrProcIdx(((*(EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdxOfPCConfig())) - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtRxBufQueueFreeIdx(EthTSyn_SwtMgmtRxBufQueueFreeIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtRxBufQueueFreeIdx(((*(EthTSyn_GetSwtMgmtRxBufQueueFreeIdxOfPCConfig())) - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtTxMgmtObjQueueCurrProcIdx(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtTxMgmtObjQueueCurrProcIdx(((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdxOfPCConfig())) - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSwtMgmtTxMgmtObjQueueFreeIdx(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSwtMgmtTxMgmtObjQueueFreeIdx(((*(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdxOfPCConfig())) - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubGmClockIdentityOfSystemState(EthTSyn_SystemStateIterType Index, EthTSyn_GmClockIdentityOfSystemStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetGmClockIdentityOfSystemState(Index, (EthTSyn_GetSystemStateOfPCConfig()[(Index)].GmClockIdentityOfSystemState - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubValueOfTimeBaseUpdateCounter(EthTSyn_TimeBaseUpdateCounterIterType Index, EthTSyn_ValueOfTimeBaseUpdateCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetValueOfTimeBaseUpdateCounter(Index, (EthTSyn_GetTimeBaseUpdateCounterOfPCConfig()[(Index)].ValueOfTimeBaseUpdateCounter - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCorrectionFieldOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCorrectionFieldOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidMasterData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SequenceIdOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SequenceIdOfTimeValidMasterData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcClockIdOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcClockIdOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcClockIdOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidMasterData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcPortNumOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_SrcPortNumOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcPortNumOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidMasterData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_StateFlagsOfTimeValidMasterDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].StateFlagsOfTimeValidMasterData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncEgressTsVltOfTimeValidMasterData(EthTSyn_TimeValidMasterDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncEgressTsVltOfTimeValidMasterData(Index, (EthTSyn_GetTimeValidMasterDataOfPCConfig()[(Index)].SyncEgressTsVltOfTimeValidMasterData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCurrPdelayOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_CurrPdelayOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCurrPdelayOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqEgressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqEgressTsVltOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdReqEgressTsVltOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespClockIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespClockIdOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespClockIdOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespIngressTsVltOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespIngressTsVltOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespIngressTsVltOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_PdRespPortNumOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespPortNumOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].PdRespPortNumOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcClockIdOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcClockIdOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcPortNumOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcPortNumOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidPdReqData(EthTSyn_TimeValidPdReqDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdReqDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidPdReqData(Index, (EthTSyn_GetTimeValidPdReqDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdReqData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqClockIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqClockIdOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqClockIdOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqIngressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqIngressTsVltOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqIngressTsVltOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdReqPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_PdReqPortNumOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdReqPortNumOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdReqPortNumOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubPdRespEgressTsVltOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetPdRespEgressTsVltOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].PdRespEgressTsVltOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SequenceIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SequenceIdOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcClockIdOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcClockIdOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcClockIdOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcClockIdOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSrcPortNumOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_SrcPortNumOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSrcPortNumOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].SrcPortNumOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidPdRespData(EthTSyn_TimeValidPdRespDataIterType Index, EthTSyn_StateFlagsOfTimeValidPdRespDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidPdRespData(Index, (EthTSyn_GetTimeValidPdRespDataOfPCConfig()[(Index)].StateFlagsOfTimeValidPdRespData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCorrectionFieldOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CorrectionFieldOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCorrectionFieldOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CorrectionFieldOfTimeValidSlaveData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubCurrPdelayOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_CurrPdelayOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetCurrPdelayOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].CurrPdelayOfTimeValidSlaveData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubMasterClockIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterClockIdOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetMasterClockIdOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterClockIdOfTimeValidSlaveData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubMasterPortNumOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_MasterPortNumOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetMasterPortNumOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].MasterPortNumOfTimeValidSlaveData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSequenceIdOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_SequenceIdOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSequenceIdOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SequenceIdOfTimeValidSlaveData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubStateFlagsOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_StateFlagsOfTimeValidSlaveDataType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetStateFlagsOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].StateFlagsOfTimeValidSlaveData - Value));
}
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SubSyncIngressTsVltOfTimeValidSlaveData(EthTSyn_TimeValidSlaveDataIterType Index, EthTSyn_IntVltType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  EthTSyn_SetSyncIngressTsVltOfTimeValidSlaveData(Index, (EthTSyn_GetTimeValidSlaveDataOfPCConfig()[(Index)].SyncIngressTsVltOfTimeValidSlaveData - Value));
}
/** 
  \}
*/ 

#define ETHTSYN_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


# endif /* !defined(ETHTSYN_UNIT_TEST) */
/* PRQA L: IDENTIFIERS_0779 */
#endif  /* ETHTSYN_GENERATED_CFG_ACCESS_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_GeneratedCfgAccess.h
 *********************************************************************************************************************/

