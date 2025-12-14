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
 *            Module: EthIf
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthIf_GenTypes.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (ETHIF_GENTYPES_H)
# define ETHIF_GENTYPES_H

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1977
 *********************************************************************************************************/
/* \trace SPEC-2393859 */
# include "EthIf_Cfg.h"
# include "EthIf_HwTypes.h"

/*********************************************************************************************************
 * Dynamic includes depending on configuration
 *********************************************************************************************************/
# include "EcuM_Generated_Types.h"

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA TYPES AND STRUCTURES (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/** 
  \defgroup  EthIfPCNonComStackLibTypes  EthIf Non ComStackLib Types (PRE_COMPILE)
  \brief  These type definitions are provided by the EthIf itself.
  \{
*/ 
/**   \brief  enumeration type defintion for initialization states of EthIf controller */
typedef enum EthIf_EthIfCtrlInitStateEnum
{
  ETHIF_ETHIFCTRL_INIT_STATE_UNINIT = 0, /**< EthIf controller is in uninitialized state */
  ETHIF_ETHIFCTRL_INIT_STATE_INIT   = 1  /**< EthIf controller is in initialized state */
} EthIf_EthIfCtrlInitStateType;

/**   \brief  enumeration type defintion for link state of EthIf controller */
typedef enum EthIf_EthIfCtrlLinkStateEnum
{
  ETHIF_ETHIFCTRL_LINK_STATE_NO_LINK          = 0, /**< EthIf controller has no link */
  ETHIF_ETHIFCTRL_LINK_STATE_LINK_CHANGE_DOWN = 1, /**< EthIf controller has a link change from up to down */
  ETHIF_ETHIFCTRL_LINK_STATE_LINK_CHANGE_UP   = 2, /**< EthIf controller has a link change from down to up */
  ETHIF_ETHIFCTRL_LINK_STATE_LINK             = 3  /**< EthIf controller has link */
} EthIf_EthIfCtrlLinkStateType;

/**   \brief  enumeration type defintion for link state of EthIf port group */
typedef enum EthIf_PortGroupLinkStateEnum
{
  ETHIF_PORTGROUP_LINK_STATE_NO_LINK          = 0, /**< EthIf port group has no link */
  ETHIF_PORTGROUP_LINK_STATE_LINK_CHANGE_DOWN = 1, /**< EthIf port group has a link change from up to down */
  ETHIF_PORTGROUP_LINK_STATE_LINK_CHANGE_UP   = 2, /**< EthIf port group has a link change from down to up */
  ETHIF_PORTGROUP_LINK_STATE_LINK             = 3  /**< EthIf port group has link */
} EthIf_PortGroupLinkStateType;

/**   \brief  the invalid VLAN ID */
# define ETHIF_INV_VLAN_ID  (4095u)

/**   \brief  flags for usage of EthIf_SwtTsPRocFlagsType */
# define ETHIF_SWT_TIMESTAMP_PROC_FLAG_INGRESS_TS_PENDING  (0x01U)
# define ETHIF_SWT_TIMESTAMP_PROC_FLAG_EGRESS_TS_PENDING   (0x02U)

/**   \brief  pointer type defintion for internal usage of Eth buffers */
typedef P2VAR(uint8, TYPEDEF, ETHIF_APPL_VAR) EthIf_FrameBufferPtrType;

/**   \brief  bitfield type defintion for Ethernet switch timestamp handling */
typedef uint8 EthIf_SwtTsProcFlagsType;

/**   \brief  value based type definition for EthIf_ActualSignalQualityOfSignalQualityResult */
typedef uint32 EthIf_ActualSignalQualityOfSignalQualityResultType;

/**   \brief  value based type definition for EthIf_HighestSignalQualityOfSignalQualityResult */
typedef uint32 EthIf_HighestSignalQualityOfSignalQualityResultType;

/**   \brief  value based type definition for EthIf_LowestSignalQualityOfSignalQualityResult */
typedef uint32 EthIf_LowestSignalQualityOfSignalQualityResultType;

/**   \brief  Ethernet header information on VLAN level */
typedef struct
{
  P2CONST(uint8, TYPEDEF, ETHIF_APPL_DATA) DstMacAddrPtr;  /**< Destionation MAC address contained in Ethernet header */
  P2CONST(uint8, TYPEDEF, ETHIF_APPL_DATA) SrcMacAddrPtr;  /**< Soruce MAC address contained in Ethernet header */
          Eth_FrameType                     EtherType;     /**< EtherType contained in Ethernet header */
          uint16                            VlanId;        /**< VLAN ID contained in VLAN tag of Ethernet header - if not VLAN tagged it holds ETHIF_INV_VLAN_ID */
          uint8                             Priority;      /**< VLAN PCP contained in VLAN tag of Ethernet header - only valid if VlanId is not equal ETHIF_INV_VLAN_ID */
} EthIf_FrameHdrType;

 /* Signal Quality Signal Type */
 typedef struct sEthIf_SignalQualityResultType
{
  EthIf_HighestSignalQualityOfSignalQualityResultType HighestSignalQuality;  /**< The highest signal quality of a link since last clear */
  EthIf_LowestSignalQualityOfSignalQualityResultType LowestSignalQuality;  /**< The lowest link signal quality of a link since last clear */
  EthIf_ActualSignalQualityOfSignalQualityResultType ActualSignalQuality;  /**< The actual signal quality */
}EthIf_SignalQualityResultType;

/**   \brief  function pointer type defintion for Eth_ControllerInit() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthCtrlInitFctPtrType)(uint8, uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_SetControllerMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSetCtrlModeFctPtrType)(uint8, Eth_ModeType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetControllerMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetCtrlModeFctPtrType)(uint8, P2VAR(Eth_ModeType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_SetPhysAddr() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_EthSetPhysAddrFctPtrType)(uint8, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetPhysAddr() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_EthGetPhysAddrFctPtrType)(uint8, P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_UpdatePhysAddrFilter() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthUpdatePhysAddrFilterFctPtrType)(uint8, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA), Eth_FilterActionType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_ProvideTxBuffer() */
typedef P2FUNC(BufReq_ReturnType, ETHIF_APPL_CODE, EthIf_EthProvideTxBufferFctPtrType)(uint8, P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA), AUTOMATIC, ETHIF_APPL_DATA), P2VAR(uint16, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_ProvideExtTxBuffer() */
typedef P2FUNC(BufReq_ReturnType, ETHIF_APPL_CODE, EthIf_EthProvideExtTxBufferFctPtrType)(uint8, P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA), AUTOMATIC, ETHIF_APPL_DATA), P2VAR(uint16, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_ReleaseRxBuffer() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthReleaseRxBufferFctPtrType)(uint8, P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetTxHeaderPtr() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetTxHeaderPtrFctPtrType)(uint8, uint8, P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA), AUTOMATIC, ETHIF_APPL_DATA), P2VAR(uint16, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetRxHeaderPtr() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetRxHeaderPtrFctPtrType)(uint8, P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA), AUTOMATIC, ETHIF_APPL_DATA), P2VAR(uint16, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_Transmit() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTransmitFctPtrType)(uint8, uint8, Eth_FrameType, boolean, uint16, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_VTransmit() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthVTransmitFctPtrType)(uint8, uint8, Eth_FrameType, boolean, uint16, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA), P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_Receive() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_EthReceiveFctPtrType)(uint8, P2VAR(Eth_RxStatusType, AUTOMATIC, ETHIF_VAR_NOINIT)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_TxConfirmation() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_EthTxConfFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetCurrentTime() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetCurrentTimeFctPtrType)(uint8, P2VAR(Eth_TimeStampType, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(Eth_TimestampQualityType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_EnableEgressTimeStamp() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthEnableEgressTimeStampFctPtrType)(uint8, uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetEgressTimeStamp() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetEgressTimeStampFctPtrType)(uint8, uint8, P2VAR(Eth_TimeStampType, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(Eth_TimestampQualityType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetIngressTimeStamp() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetIngressTimeStampFctPtrType)(uint8, P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(Eth_TimeStampType, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(Eth_TimestampQualityType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_SetBandwidthLimit() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSetBandwidthLimitFctPtrType)(uint8, uint8, uint32); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetBandwidthLimit() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetBandwidthLimitFctPtrType)(uint8, uint8, P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetTxStats() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetTxStatsFctPtrType)(uint8, P2VAR(Eth_TxStatsType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for Eth_GetRxStats() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthGetRxStatsFctPtrType)(uint8, P2VAR(Eth_RxStatsType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_TransceiverInit() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvTrcvInitFctPtrType)(uint8, uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_SetTransceiverMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvSetTrcvModeFctPtrType)(uint8, EthTrcv_ModeType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_GetTransceiverMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvGetTrcvModeFctPtrType)(uint8, P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_StartAutoNegotiation() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvStartAutoNegFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_GetLinkState() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvGetLinkStateFctPtrType)(uint8, P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_GetBaudRate() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvGetBaudRateFctPtrType)(uint8, P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_GetDuplexMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvGetDuplexModeFctPtrType)(uint8, P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_SetTransceiverWakeupMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvSetTrcvWakeupModeFctPtrType)(uint8, EthTrcv_WakeupModeType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_GetTransceiverWakeupMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvGetTrcvWakeupModeFctPtrType)(uint8, P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_CheckWakeup() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvCheckWakeupFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_SetPhyTxMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvSetPhyTxModeFctPtrType)(uint8, uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_GetPhySignalQuality() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvGetPhySignalQualityFctPtrType)(uint8, P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_GetCableDiagnosticsResult() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvGetCableDiagnosticsResultFctPtrType)(uint8, P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthTrcv_SetPhyTestMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthTrcvSetPhyTestModeFctPtrType)(uint8, uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_SwitchInit() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtSwtInitFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_SetSwitchPortMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtSetSwtPortModeFctPtrType)(uint8, uint8, EthTrcv_ModeType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetSwitchPortMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetSwtPortModeFctPtrType)(uint8, uint8, P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_StartSwitchPortAutoNegotiation() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtStartSwtPortAutoNegFctPtrType)(uint8, uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetLinkState() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetLinkStateFctPtrType)(uint8, uint8, P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetBaudRate() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetBaudRateFctPtrType)(uint8, uint8, P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetDuplexMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetDuplexModeFctPtrType)(uint8, uint8, P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetPortMacAddr() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetPortMacAddrFctPtrType)(P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA), P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetPortSignalQuality() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetPortSignalQualityFctPtrType)(uint8, uint8, P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetArlTable() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetArlTableFctPtrType)(uint8, P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(EthSwt_MacVlanType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetBufferLevel() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetBufferLevelFctPtrType)(uint8, P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetDropCount() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetDropCountFctPtrType)(uint8, P2VAR(uint16, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_EnableVlan() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtEnableVlanFctPtrType)(uint8, uint8, uint16, boolean); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_StoreConfiguration() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtStoreConfigFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_ResetConfiguration() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtResetConfigFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_SetMacLearningMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtSetMacLearningModeFctPtrType)(uint8, uint8, EthSwt_MacLearningType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetMacLearningMode() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetMacLearningModeFctPtrType)(uint8, uint8, P2VAR(EthSwt_MacLearningType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_SetMgmtInfo() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtSetSwtMgmtInfoFctPtrType)(uint8, Eth_BufIdxType, P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetRxMgmtObject() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetRxMgmtObjectFctPtrType)(uint8, P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(P2VAR(EthSwt_MgmtObjectType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_GetTxMgmtObject() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtGetTxMgmtObjectFctPtrType)(uint8, Eth_BufIdxType, P2VAR(P2VAR(EthSwt_MgmtObjectType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_PortEnableTimeStamp() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtPortEnableTimeStampFctPtrType)(uint8, Eth_BufIdxType, P2VAR(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_VAR)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for EthSwt_UpdateMCastPortAssignment() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtUpdateMCastPortAssignmentFctPtrType)(uint8, uint8, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA), EthSwt_MCastPortAssignActionType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type definition for EthSwt_SetCorrectionTime() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtSetCorrectionTimeFctPtrType)(uint8, P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETHIF_APPL_DATA), P2CONST(float64, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type definition for EthSwt_StartQbvSchedule() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtStartQbvScheduleFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type definition for EthSwt_StopQbvSchedule() */
typedef P2FUNC(Std_ReturnType,    ETHIF_APPL_CODE, EthIf_EthSwtStopQbvScheduleFctPtrType)(uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for <User>_RxIndication() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_RxIndFctPtrType)(uint8, uint16, boolean, P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR), P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR), uint16); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for <User>_TxConfirmation() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_TxConfFctPtrType)(uint8, uint8); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for <User>_TrcvLinkStateChg() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_LinkStateChgIndFctPtrType)(uint8, EthTrcv_LinkStateType); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for <User>_MgmtInfoIndication() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_MgmtInfoIndFctPtrType)(uint8, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA), P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for <User>_IngressTimeStampIndication() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_IngressTsIndFctPtrType)(uint8, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA), P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA), P2CONST(Eth_TimeStampType, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/**   \brief  function pointer type defintion for <User>_EgressTimeStampIndication() */
typedef P2FUNC(void,              ETHIF_APPL_CODE, EthIf_EgressTsIndFctPtrType)(uint8, P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA), P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA), P2CONST(Eth_TimeStampType, AUTOMATIC, ETHIF_APPL_DATA)); /* PRQA S 1336 */ /* MD_EthIf_1336 */

/** 
  \}
*/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  EthIfPCDataSwitches  EthIf Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define ETHIF_ETHCTRL                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHDRVAPIIDXOFETHCTRL                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SNVOFETHCTRL                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONTEXTENDIDXOFETHCTRL                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONTEXTSTARTIDXOFETHCTRL                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLINITCNT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLMODECNT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLRXFRAMECNT                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHDRVAPI                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_CTRLINITOFETHDRVAPI                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ENABLEEGRESSTIMESTAMPOFETHDRVAPI                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETBANDWIDTHLIMITOFETHDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETCTRLMODEOFETHDRVAPI                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETCURRENTTIMEOFETHDRVAPI                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETEGRESSTIMESTAMPOFETHDRVAPI                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETINGRESSTIMESTAMPOFETHDRVAPI                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETPHYSADDROFETHDRVAPI                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETRXHEADERPTROFETHDRVAPI                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETRXSTATSOFETHDRVAPI                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETTXHEADERPTROFETHDRVAPI                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETTXSTATSOFETHDRVAPI                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PROVIDEEXTTXBUFFEROFETHDRVAPI                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PROVIDETXBUFFEROFETHDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RECEIVEOFETHDRVAPI                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RELEASERXBUFFEROFETHDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETBANDWIDTHLIMITOFETHDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETCTRLMODEOFETHDRVAPI                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETPHYSADDROFETHDRVAPI                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TRANSMITOFETHDRVAPI                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFOFETHDRVAPI                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_UPDATEPHYSADDRFILTEROFETHDRVAPI                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_VTRANSMITOFETHDRVAPI                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRL                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLIDXOFETHIFCTRL                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTDRVAPIIDXOFETHIFCTRL                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTDRVAPIUSEDOFETHIFCTRL                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GATEWAYDESTETHIFCTRLIDXIDXOFETHIFCTRL                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GATEWAYDESTETHIFCTRLIDXUSEDOFETHIFCTRL                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_LINKAGGRTHRESHOLDOFETHIFCTRL                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORRXDESTIDXIDXOFETHIFCTRL                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORRXDESTIDXUSEDOFETHIFCTRL                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORTXDESTIDXIDXOFETHIFCTRL                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORTXDESTIDXUSEDOFETHIFCTRL                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MTUOFETHIFCTRL                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PHYSLAYERINITELEMSIDXOFETHIFCTRL                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PHYSLAYERMODEELEMSIDXOFETHIFCTRL                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SNVOFETHIFCTRL                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TYPEOFETHIFCTRL                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_VLANIDOFETHIFCTRL                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLINITSTATE                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLLINKCOUNT                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLLINKSTATE                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLMODE                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFETHTRCVIND                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFPORTGROUPIND                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLRXSTATS                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_NUMRXBYTESOFETHIFCTRLRXSTATS                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_NUMRXPKTSOFETHIFCTRLRXSTATS                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLTXSTATS                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_NUMTXBYTESOFETHIFCTRLTXSTATS                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_NUMTXPKTSOFETHIFCTRLTXSTATS                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFMEASUREMENTDATA                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_DROPCTRLIDXOFETHIFMEASUREMENTDATA                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_UNKNOWNETHERTYPEOFETHIFMEASUREMENTDATA                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_VLANDOUBLETAGGEDOFETHIFMEASUREMENTDATA                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWT                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTDRVAPIIDXOFETHSWT                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SNVOFETHSWT                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTDRV                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTENDIDXOFETHSWTDRV                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTSTARTIDXOFETHSWTDRV                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTDRVAPI                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ENABLEVLANOFETHSWTDRVAPI                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETARLTABLEOFETHSWTDRVAPI                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETBAUDRATEOFETHSWTDRVAPI                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETBUFFERLEVELOFETHSWTDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETDROPCOUNTOFETHSWTDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETDUPLEXMODEOFETHSWTDRVAPI                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETLINKSTATEOFETHSWTDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETMACLEARNINGMODEOFETHSWTDRVAPI                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETPORTMACADDROFETHSWTDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETPORTSIGNALQUALITYOFETHSWTDRVAPI                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETRXMGMTOBJECTOFETHSWTDRVAPI                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETSWTPORTMODEOFETHSWTDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETTXMGMTOBJECTOFETHSWTDRVAPI                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTENABLETIMESTAMPOFETHSWTDRVAPI                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RESETCONFIGOFETHSWTDRVAPI                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETCORRECTIONTIMEOFETHSWTDRVAPI                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETMACLEARNINGMODEOFETHSWTDRVAPI                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETSWTMGMTINFOOFETHSWTDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETSWTPORTMODEOFETHSWTDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_STARTQBVSCHEDULEOFETHSWTDRVAPI                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_STARTSWTPORTAUTONEGOFETHSWTDRVAPI                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_STOPQBVSCHEDULEOFETHSWTDRVAPI                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_STORECONFIGOFETHSWTDRVAPI                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SWTINITOFETHSWTDRVAPI                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_UPDATEMCASTPORTASSIGNMENTOFETHSWTDRVAPI                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTIND                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTINITCNT                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORT                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTIDXOFETHSWTPORT                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPINDENDIDXOFETHSWTPORT                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPINDSTARTIDXOFETHSWTPORT                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SNVOFETHSWTPORT                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORTIND                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORTMODECNT                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCV                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFETHTRCVINDENDIDXOFETHTRCV                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFETHTRCVINDSTARTIDXOFETHTRCV                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFETHTRCVINDUSEDOFETHTRCV                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVDRVAPIIDXOFETHTRCV                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SNVOFETHTRCV                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVDRVAPI                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_CHECKWAKEUPOFETHTRCVDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETBAUDRATEOFETHTRCVDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETCABLEDIAGNOSTICSRESULTOFETHTRCVDRVAPI                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETDUPLEXMODEOFETHTRCVDRVAPI                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETLINKSTATEOFETHTRCVDRVAPI                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETPHYSIGNALQUALITYOFETHTRCVDRVAPI                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETTRCVMODEOFETHTRCVDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_GETTRCVWAKEUPMODEOFETHTRCVDRVAPI                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETPHYTESTMODEOFETHTRCVDRVAPI                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETPHYTXMODEOFETHTRCVDRVAPI                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETTRCVMODEOFETHTRCVDRVAPI                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SETTRCVWAKEUPMODEOFETHTRCVDRVAPI                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_STARTAUTONEGOFETHTRCVDRVAPI                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TRCVINITOFETHTRCVDRVAPI                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVINITCNT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVMODECNT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_EXPLICITBUFRELEASEFILTER                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLIDXOFEXPLICITBUFRELEASEFILTER                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_USERIDXOFEXPLICITBUFRELEASEFILTER                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_USERUSEDOFEXPLICITBUFRELEASEFILTER                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_FINALMAGICNUMBER                                        STD_OFF  /**< Deactivateable: 'EthIf_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHIF_GATEWAYSRCMACBLACKLIST                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MACADDROFGATEWAYSRCMACBLACKLIST                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_INITDATAHASHCODE                                        STD_OFF  /**< Deactivateable: 'EthIf_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHIF_INITLOCKED                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_LINKSTATECHGINDICATIONS                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_LINKSTATECHGMAINRELOAD                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MAINFUNCSTATEDECOUPLEFREQCNT                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MAXFRAMERXPERETHCTRL                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MAXTXBUFPERETHCTRL                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORDEST                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLIDXOFMIRRORDEST                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_KEEPSRCMACENABLEDOFMIRRORDEST                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORTXINFO                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_DESTETHTXBUFFERIDXOFMIRRORTXINFO                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_DESTPAYLOADPTROFMIRRORTXINFO                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLIDXOFMIRRORTXINFO                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_INFOVALIDOFMIRRORTXINFO                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SRCETHTXBUFFERIDXOFMIRRORTXINFO                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SRCPAYLOADPTROFMIRRORTXINFO                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_USEDOFMIRRORTXINFO                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MODECHANGELOCKED                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PHYSLAYERINITELEMS                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTINDENDIDXOFPHYSLAYERINITELEMS                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTINDSTARTIDXOFPHYSLAYERINITELEMS                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTINDUSEDOFPHYSLAYERINITELEMS                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVIDXOFPHYSLAYERINITELEMS                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVUSEDOFPHYSLAYERINITELEMS                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PHYSLAYERMODEELEMS                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVIDXOFPHYSLAYERMODEELEMS                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVUSEDOFPHYSLAYERMODEELEMS                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPIDXOFPHYSLAYERMODEELEMS                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPUSEDOFPHYSLAYERMODEELEMS                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUP                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFPORTGROUPINDENDIDXOFPORTGROUP                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFPORTGROUPINDSTARTIDXOFPORTGROUP              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFPORTGROUPINDUSEDOFPORTGROUP                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORTINDENDIDXOFPORTGROUP                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORTINDSTARTIDXOFPORTGROUP                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_LINKAGGRTHRESHOLDOFPORTGROUP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SEMANTICOFPORTGROUP                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SNVOFPORTGROUP                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPIND                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPLINKCOUNT                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPLINKSTATE                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPMODE                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTSIGNALQUALITYRESULT                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RXINDICATIONS                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RXINDICATIONSIND                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIGNALQUALITYCHGMAINRELOAD                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIGNALQUALITYDECOUPLEFREQCNT                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIGNALQUALITYRESULT                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRL                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRLINITCNT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRLMODECNT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRLRXFRAMECNT                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHDRVAPI                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRL                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLINITSTATE                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLLINKCOUNT                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLLINKSTATE                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLMODE                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLOFETHTRCVIND                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLOFPORTGROUPIND                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLRXSTATS                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLTXSTATS                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFMEASUREMENTDATA                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWT                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTDRV                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTDRVAPI                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTIND                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTINITCNT                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTPORT                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTPORTIND                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTPORTMODECNT                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCV                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCVDRVAPI                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCVINITCNT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCVMODECNT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFEXPLICITBUFRELEASEFILTER                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFGATEWAYSRCMACBLACKLIST                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFLINKSTATECHGINDICATIONS                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFMIRRORDEST                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFMIRRORTXINFO                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPHYSLAYERINITELEMS                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPHYSLAYERMODEELEMS                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUP                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPIND                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPLINKCOUNT                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPLINKSTATE                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPMODE                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTSIGNALQUALITYRESULT                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFRXINDICATIONS                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFRXINDICATIONSIND                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFSIGNALQUALITYRESULT                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFSRCMACADDRBUFFER                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFTXCONFIRMATIONS                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFTXCONFIRMATIONSIND                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFTXCONTEXT                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFUSER                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFWAKEUPMAP                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SRCMACADDRBUFFER                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SRCMACOFSRCMACADDRBUFFER                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_VALIDOFSRCMACADDRBUFFER                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFIRMATIONS                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFIRMATIONSIND                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONTEXT                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLIDXOFTXCONTEXT                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_FRAMEHDROFTXCONTEXT                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PAYLOADLENOFTXCONTEXT                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PAYLOADPTROFTXCONTEXT                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXPENDINGOFTXCONTEXT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_USERIDXOFTXCONTEXT                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_VALIDOFTXCONTEXT                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_USER                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHERTYPEOFUSER                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RXINDICATIONSINDENDIDXOFUSER                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RXINDICATIONSINDSTARTIDXOFUSER                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RXINDICATIONSINDUSEDOFUSER                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFIRMATIONSINDENDIDXOFUSER                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFIRMATIONSINDSTARTIDXOFUSER                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFIRMATIONSINDUSEDOFUSER                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_WAKEUPMAP                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVIDXOFWAKEUPMAP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_WAKEUPSOURCEOFWAKEUPMAP                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLINITCNTOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLMODECNTOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHCTRLRXFRAMECNTOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHDRVAPIOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLINITSTATEOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLLINKCOUNTOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLLINKSTATEOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLMODEOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFETHTRCVINDOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLOFPORTGROUPINDOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLRXSTATSOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFCTRLTXSTATSOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHIFMEASUREMENTDATAOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTDRVAPIOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTDRVOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTINDOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTINITCNTOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTOFPCCONFIG                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORTINDOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORTMODECNTOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHSWTPORTOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVDRVAPIOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVINITCNTOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVMODECNTOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_ETHTRCVOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_EXPLICITBUFRELEASEFILTEROFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_FINALMAGICNUMBEROFPCCONFIG                              STD_OFF  /**< Deactivateable: 'EthIf_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHIF_GATEWAYSRCMACBLACKLISTOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_INITDATAHASHCODEOFPCCONFIG                              STD_OFF  /**< Deactivateable: 'EthIf_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHIF_INITLOCKEDOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_LINKSTATECHGINDICATIONSOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_LINKSTATECHGMAINRELOADOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MAINFUNCSTATEDECOUPLEFREQCNTOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MAXFRAMERXPERETHCTRLOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MAXTXBUFPERETHCTRLOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORDESTOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MIRRORTXINFOOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_MODECHANGELOCKEDOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PHYSLAYERINITELEMSOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PHYSLAYERMODEELEMSOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPINDOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPLINKCOUNTOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPLINKSTATEOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPMODEOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTGROUPOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_PORTSIGNALQUALITYRESULTOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RXINDICATIONSINDOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_RXINDICATIONSOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIGNALQUALITYCHGMAINRELOADOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIGNALQUALITYDECOUPLEFREQCNTOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIGNALQUALITYRESULTOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRLINITCNTOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRLMODECNTOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRLOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHCTRLRXFRAMECNTOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHDRVAPIOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLINITSTATEOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLLINKCOUNTOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLLINKSTATEOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLMODEOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLOFETHTRCVINDOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLOFPORTGROUPINDOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLRXSTATSOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFCTRLTXSTATSOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHIFMEASUREMENTDATAOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTDRVAPIOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTDRVOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTINDOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTINITCNTOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTPORTINDOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTPORTMODECNTOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHSWTPORTOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCVDRVAPIOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCVINITCNTOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCVMODECNTOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFETHTRCVOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFEXPLICITBUFRELEASEFILTEROFPCCONFIG                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFGATEWAYSRCMACBLACKLISTOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFLINKSTATECHGINDICATIONSOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFMIRRORDESTOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFMIRRORTXINFOOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPHYSLAYERINITELEMSOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPHYSLAYERMODEELEMSOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPINDOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPLINKCOUNTOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPLINKSTATEOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPMODEOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTGROUPOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFPORTSIGNALQUALITYRESULTOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFRXINDICATIONSINDOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFRXINDICATIONSOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFSIGNALQUALITYRESULTOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFSRCMACADDRBUFFEROFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFTXCONFIRMATIONSINDOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFTXCONFIRMATIONSOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFTXCONTEXTOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFUSEROFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SIZEOFWAKEUPMAPOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_SRCMACADDRBUFFEROFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFIRMATIONSINDOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONFIRMATIONSOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_TXCONTEXTOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_USEROFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHIF_WAKEUPMAPOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCMinNumericValueDefines  EthIf Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define ETHIF_MIN_ETHCTRLINITCNT                                      0u
#define ETHIF_MIN_ETHCTRLMODECNT                                      0u
#define ETHIF_MIN_ETHCTRLRXFRAMECNT                                   0u
#define ETHIF_MIN_ETHIFCTRLLINKCOUNT                                  0u
#define ETHIF_MIN_NUMRXBYTESOFETHIFCTRLRXSTATS                        0u
#define ETHIF_MIN_NUMRXPKTSOFETHIFCTRLRXSTATS                         0u
#define ETHIF_MIN_NUMTXBYTESOFETHIFCTRLTXSTATS                        0u
#define ETHIF_MIN_NUMTXPKTSOFETHIFCTRLTXSTATS                         0u
#define ETHIF_MIN_DROPCTRLIDXOFETHIFMEASUREMENTDATA                   0u
#define ETHIF_MIN_UNKNOWNETHERTYPEOFETHIFMEASUREMENTDATA              0u
#define ETHIF_MIN_VLANDOUBLETAGGEDOFETHIFMEASUREMENTDATA              0u
#define ETHIF_MIN_ETHSWTINITCNT                                       0u
#define ETHIF_MIN_ETHSWTPORTMODECNT                                   0u
#define ETHIF_MIN_ETHTRCVINITCNT                                      0u
#define ETHIF_MIN_ETHTRCVMODECNT                                      0u
#define ETHIF_MIN_MAINFUNCSTATEDECOUPLEFREQCNT                        0u
#define ETHIF_MIN_DESTETHTXBUFFERIDXOFMIRRORTXINFO                    0u
#define ETHIF_MIN_ETHIFCTRLIDXOFMIRRORTXINFO                          0u
#define ETHIF_MIN_SRCETHTXBUFFERIDXOFMIRRORTXINFO                     0u
#define ETHIF_MIN_PORTGROUPLINKCOUNT                                  0u
#define ETHIF_MIN_SIGNALQUALITYDECOUPLEFREQCNT                        0u
#define ETHIF_MIN_ETHIFCTRLIDXOFTXCONTEXT                             0u
#define ETHIF_MIN_PAYLOADLENOFTXCONTEXT                               0u
#define ETHIF_MIN_USERIDXOFTXCONTEXT                                  0u
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCMaxNumericValueDefines  EthIf Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define ETHIF_MAX_ETHCTRLINITCNT                                      255u
#define ETHIF_MAX_ETHCTRLMODECNT                                      255u
#define ETHIF_MAX_ETHCTRLRXFRAMECNT                                   255u
#define ETHIF_MAX_ETHIFCTRLLINKCOUNT                                  255u
#define ETHIF_MAX_NUMRXBYTESOFETHIFCTRLRXSTATS                        4294967295u
#define ETHIF_MAX_NUMRXPKTSOFETHIFCTRLRXSTATS                         4294967295u
#define ETHIF_MAX_NUMTXBYTESOFETHIFCTRLTXSTATS                        4294967295u
#define ETHIF_MAX_NUMTXPKTSOFETHIFCTRLTXSTATS                         4294967295u
#define ETHIF_MAX_DROPCTRLIDXOFETHIFMEASUREMENTDATA                   4294967295u
#define ETHIF_MAX_UNKNOWNETHERTYPEOFETHIFMEASUREMENTDATA              4294967295u
#define ETHIF_MAX_VLANDOUBLETAGGEDOFETHIFMEASUREMENTDATA              4294967295u
#define ETHIF_MAX_ETHSWTINITCNT                                       255u
#define ETHIF_MAX_ETHSWTPORTMODECNT                                   255u
#define ETHIF_MAX_ETHTRCVINITCNT                                      255u
#define ETHIF_MAX_ETHTRCVMODECNT                                      255u
#define ETHIF_MAX_MAINFUNCSTATEDECOUPLEFREQCNT                        65535u
#define ETHIF_MAX_DESTETHTXBUFFERIDXOFMIRRORTXINFO                    255u
#define ETHIF_MAX_ETHIFCTRLIDXOFMIRRORTXINFO                          255u
#define ETHIF_MAX_SRCETHTXBUFFERIDXOFMIRRORTXINFO                     255u
#define ETHIF_MAX_PORTGROUPLINKCOUNT                                  255u
#define ETHIF_MAX_SIGNALQUALITYDECOUPLEFREQCNT                        65535u
#define ETHIF_MAX_ETHIFCTRLIDXOFTXCONTEXT                             255u
#define ETHIF_MAX_PAYLOADLENOFTXCONTEXT                               65535u
#define ETHIF_MAX_USERIDXOFTXCONTEXT                                  255u
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCNoReferenceDefines  EthIf No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define ETHIF_NO_ETHSWTDRVAPIIDXOFETHIFCTRL                           255u
#define ETHIF_NO_GATEWAYDESTETHIFCTRLIDXIDXOFETHIFCTRL                255u
#define ETHIF_NO_LINKAGGRTHRESHOLDOFETHIFCTRL                         255u
#define ETHIF_NO_MIRRORRXDESTIDXIDXOFETHIFCTRL                        255u
#define ETHIF_NO_MIRRORTXDESTIDXIDXOFETHIFCTRL                        255u
#define ETHIF_NO_MTUOFETHIFCTRL                                       65535u
#define ETHIF_NO_VLANIDOFETHIFCTRL                                    255u
#define ETHIF_NO_ETHIFCTRLOFETHTRCVINDENDIDXOFETHTRCV                 255u
#define ETHIF_NO_ETHIFCTRLOFETHTRCVINDSTARTIDXOFETHTRCV               255u
#define ETHIF_NO_USERIDXOFEXPLICITBUFRELEASEFILTER                    255u
#define ETHIF_NO_ETHSWTINDENDIDXOFPHYSLAYERINITELEMS                  255u
#define ETHIF_NO_ETHSWTINDSTARTIDXOFPHYSLAYERINITELEMS                255u
#define ETHIF_NO_ETHTRCVIDXOFPHYSLAYERINITELEMS                       255u
#define ETHIF_NO_ETHTRCVIDXOFPHYSLAYERMODEELEMS                       255u
#define ETHIF_NO_PORTGROUPIDXOFPHYSLAYERMODEELEMS                     255u
#define ETHIF_NO_ETHIFCTRLOFPORTGROUPINDENDIDXOFPORTGROUP             255u
#define ETHIF_NO_ETHIFCTRLOFPORTGROUPINDSTARTIDXOFPORTGROUP           255u
#define ETHIF_NO_LINKAGGRTHRESHOLDOFPORTGROUP                         255u
#define ETHIF_NO_ETHERTYPEOFUSER                                      65535u
#define ETHIF_NO_RXINDICATIONSINDENDIDXOFUSER                         255u
#define ETHIF_NO_RXINDICATIONSINDSTARTIDXOFUSER                       255u
#define ETHIF_NO_TXCONFIRMATIONSINDENDIDXOFUSER                       255u
#define ETHIF_NO_TXCONFIRMATIONSINDSTARTIDXOFUSER                     255u
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCEnumExistsDefines  EthIf Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define ETHIF_EXISTS_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL          STD_ON
#define ETHIF_EXISTS_ETHIFCTRL_TYPE_Q_TAGGED_VLAN_TYPEOFETHIFCTRL     STD_ON
#define ETHIF_EXISTS_ETHIFCTRL_TYPE_Q_TAGGED_PRIO_TYPEOFETHIFCTRL     STD_ON
#define ETHIF_EXISTS_PORTGROUP_SEMANTIC_CONTROL_SEMANTICOFPORTGROUP   STD_ON
#define ETHIF_EXISTS_PORTGROUP_SEMANTIC_LINK_INFO_SEMANTICOFPORTGROUP STD_ON
#define ETHIF_EXISTS_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCIsReducedToDefineDefines  EthIf Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define ETHIF_ISDEF_ETHDRVAPIIDXOFETHCTRL                             STD_OFF
#define ETHIF_ISDEF_SNVOFETHCTRL                                      STD_OFF
#define ETHIF_ISDEF_TXCONTEXTENDIDXOFETHCTRL                          STD_OFF
#define ETHIF_ISDEF_TXCONTEXTSTARTIDXOFETHCTRL                        STD_OFF
#define ETHIF_ISDEF_CTRLINITOFETHDRVAPI                               STD_OFF
#define ETHIF_ISDEF_ENABLEEGRESSTIMESTAMPOFETHDRVAPI                  STD_OFF
#define ETHIF_ISDEF_GETBANDWIDTHLIMITOFETHDRVAPI                      STD_OFF
#define ETHIF_ISDEF_GETCTRLMODEOFETHDRVAPI                            STD_OFF
#define ETHIF_ISDEF_GETCURRENTTIMEOFETHDRVAPI                         STD_OFF
#define ETHIF_ISDEF_GETEGRESSTIMESTAMPOFETHDRVAPI                     STD_OFF
#define ETHIF_ISDEF_GETINGRESSTIMESTAMPOFETHDRVAPI                    STD_OFF
#define ETHIF_ISDEF_GETPHYSADDROFETHDRVAPI                            STD_OFF
#define ETHIF_ISDEF_GETRXHEADERPTROFETHDRVAPI                         STD_OFF
#define ETHIF_ISDEF_GETRXSTATSOFETHDRVAPI                             STD_OFF
#define ETHIF_ISDEF_GETTXHEADERPTROFETHDRVAPI                         STD_OFF
#define ETHIF_ISDEF_GETTXSTATSOFETHDRVAPI                             STD_OFF
#define ETHIF_ISDEF_PROVIDEEXTTXBUFFEROFETHDRVAPI                     STD_OFF
#define ETHIF_ISDEF_PROVIDETXBUFFEROFETHDRVAPI                        STD_OFF
#define ETHIF_ISDEF_RECEIVEOFETHDRVAPI                                STD_OFF
#define ETHIF_ISDEF_RELEASERXBUFFEROFETHDRVAPI                        STD_OFF
#define ETHIF_ISDEF_SETBANDWIDTHLIMITOFETHDRVAPI                      STD_OFF
#define ETHIF_ISDEF_SETCTRLMODEOFETHDRVAPI                            STD_OFF
#define ETHIF_ISDEF_SETPHYSADDROFETHDRVAPI                            STD_OFF
#define ETHIF_ISDEF_TRANSMITOFETHDRVAPI                               STD_OFF
#define ETHIF_ISDEF_TXCONFOFETHDRVAPI                                 STD_OFF
#define ETHIF_ISDEF_UPDATEPHYSADDRFILTEROFETHDRVAPI                   STD_OFF
#define ETHIF_ISDEF_VTRANSMITOFETHDRVAPI                              STD_OFF
#define ETHIF_ISDEF_ETHCTRLIDXOFETHIFCTRL                             STD_OFF
#define ETHIF_ISDEF_ETHSWTDRVAPIIDXOFETHIFCTRL                        STD_OFF
#define ETHIF_ISDEF_ETHSWTDRVAPIUSEDOFETHIFCTRL                       STD_OFF
#define ETHIF_ISDEF_GATEWAYDESTETHIFCTRLIDXIDXOFETHIFCTRL             STD_OFF
#define ETHIF_ISDEF_GATEWAYDESTETHIFCTRLIDXUSEDOFETHIFCTRL            STD_OFF
#define ETHIF_ISDEF_LINKAGGRTHRESHOLDOFETHIFCTRL                      STD_OFF
#define ETHIF_ISDEF_MIRRORRXDESTIDXIDXOFETHIFCTRL                     STD_OFF
#define ETHIF_ISDEF_MIRRORRXDESTIDXUSEDOFETHIFCTRL                    STD_OFF
#define ETHIF_ISDEF_MIRRORTXDESTIDXIDXOFETHIFCTRL                     STD_OFF
#define ETHIF_ISDEF_MIRRORTXDESTIDXUSEDOFETHIFCTRL                    STD_OFF
#define ETHIF_ISDEF_MTUOFETHIFCTRL                                    STD_OFF
#define ETHIF_ISDEF_PHYSLAYERINITELEMSIDXOFETHIFCTRL                  STD_OFF
#define ETHIF_ISDEF_PHYSLAYERMODEELEMSIDXOFETHIFCTRL                  STD_OFF
#define ETHIF_ISDEF_SNVOFETHIFCTRL                                    STD_OFF
#define ETHIF_ISDEF_TYPEOFETHIFCTRL                                   STD_OFF
#define ETHIF_ISDEF_VLANIDOFETHIFCTRL                                 STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFETHTRCVIND                             STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFPORTGROUPIND                           STD_OFF
#define ETHIF_ISDEF_ETHSWTDRVAPIIDXOFETHSWT                           STD_OFF
#define ETHIF_ISDEF_SNVOFETHSWT                                       STD_OFF
#define ETHIF_ISDEF_ETHSWTENDIDXOFETHSWTDRV                           STD_OFF
#define ETHIF_ISDEF_ETHSWTSTARTIDXOFETHSWTDRV                         STD_OFF
#define ETHIF_ISDEF_ENABLEVLANOFETHSWTDRVAPI                          STD_OFF
#define ETHIF_ISDEF_GETARLTABLEOFETHSWTDRVAPI                         STD_OFF
#define ETHIF_ISDEF_GETBAUDRATEOFETHSWTDRVAPI                         STD_OFF
#define ETHIF_ISDEF_GETBUFFERLEVELOFETHSWTDRVAPI                      STD_OFF
#define ETHIF_ISDEF_GETDROPCOUNTOFETHSWTDRVAPI                        STD_OFF
#define ETHIF_ISDEF_GETDUPLEXMODEOFETHSWTDRVAPI                       STD_OFF
#define ETHIF_ISDEF_GETLINKSTATEOFETHSWTDRVAPI                        STD_OFF
#define ETHIF_ISDEF_GETMACLEARNINGMODEOFETHSWTDRVAPI                  STD_OFF
#define ETHIF_ISDEF_GETPORTMACADDROFETHSWTDRVAPI                      STD_OFF
#define ETHIF_ISDEF_GETPORTSIGNALQUALITYOFETHSWTDRVAPI                STD_OFF
#define ETHIF_ISDEF_GETRXMGMTOBJECTOFETHSWTDRVAPI                     STD_OFF
#define ETHIF_ISDEF_GETSWTPORTMODEOFETHSWTDRVAPI                      STD_OFF
#define ETHIF_ISDEF_GETTXMGMTOBJECTOFETHSWTDRVAPI                     STD_OFF
#define ETHIF_ISDEF_PORTENABLETIMESTAMPOFETHSWTDRVAPI                 STD_OFF
#define ETHIF_ISDEF_RESETCONFIGOFETHSWTDRVAPI                         STD_OFF
#define ETHIF_ISDEF_SETCORRECTIONTIMEOFETHSWTDRVAPI                   STD_OFF
#define ETHIF_ISDEF_SETMACLEARNINGMODEOFETHSWTDRVAPI                  STD_OFF
#define ETHIF_ISDEF_SETSWTMGMTINFOOFETHSWTDRVAPI                      STD_OFF
#define ETHIF_ISDEF_SETSWTPORTMODEOFETHSWTDRVAPI                      STD_OFF
#define ETHIF_ISDEF_STARTQBVSCHEDULEOFETHSWTDRVAPI                    STD_OFF
#define ETHIF_ISDEF_STARTSWTPORTAUTONEGOFETHSWTDRVAPI                 STD_OFF
#define ETHIF_ISDEF_STOPQBVSCHEDULEOFETHSWTDRVAPI                     STD_OFF
#define ETHIF_ISDEF_STORECONFIGOFETHSWTDRVAPI                         STD_OFF
#define ETHIF_ISDEF_SWTINITOFETHSWTDRVAPI                             STD_OFF
#define ETHIF_ISDEF_UPDATEMCASTPORTASSIGNMENTOFETHSWTDRVAPI           STD_OFF
#define ETHIF_ISDEF_ETHSWTIND                                         STD_OFF
#define ETHIF_ISDEF_ETHSWTIDXOFETHSWTPORT                             STD_OFF
#define ETHIF_ISDEF_PORTGROUPINDENDIDXOFETHSWTPORT                    STD_OFF
#define ETHIF_ISDEF_PORTGROUPINDSTARTIDXOFETHSWTPORT                  STD_OFF
#define ETHIF_ISDEF_SNVOFETHSWTPORT                                   STD_OFF
#define ETHIF_ISDEF_ETHSWTPORTIND                                     STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFETHTRCVINDENDIDXOFETHTRCV              STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFETHTRCVINDSTARTIDXOFETHTRCV            STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFETHTRCVINDUSEDOFETHTRCV                STD_OFF
#define ETHIF_ISDEF_ETHTRCVDRVAPIIDXOFETHTRCV                         STD_OFF
#define ETHIF_ISDEF_SNVOFETHTRCV                                      STD_OFF
#define ETHIF_ISDEF_CHECKWAKEUPOFETHTRCVDRVAPI                        STD_OFF
#define ETHIF_ISDEF_GETBAUDRATEOFETHTRCVDRVAPI                        STD_OFF
#define ETHIF_ISDEF_GETCABLEDIAGNOSTICSRESULTOFETHTRCVDRVAPI          STD_OFF
#define ETHIF_ISDEF_GETDUPLEXMODEOFETHTRCVDRVAPI                      STD_OFF
#define ETHIF_ISDEF_GETLINKSTATEOFETHTRCVDRVAPI                       STD_OFF
#define ETHIF_ISDEF_GETPHYSIGNALQUALITYOFETHTRCVDRVAPI                STD_OFF
#define ETHIF_ISDEF_GETTRCVMODEOFETHTRCVDRVAPI                        STD_OFF
#define ETHIF_ISDEF_GETTRCVWAKEUPMODEOFETHTRCVDRVAPI                  STD_OFF
#define ETHIF_ISDEF_SETPHYTESTMODEOFETHTRCVDRVAPI                     STD_OFF
#define ETHIF_ISDEF_SETPHYTXMODEOFETHTRCVDRVAPI                       STD_OFF
#define ETHIF_ISDEF_SETTRCVMODEOFETHTRCVDRVAPI                        STD_OFF
#define ETHIF_ISDEF_SETTRCVWAKEUPMODEOFETHTRCVDRVAPI                  STD_OFF
#define ETHIF_ISDEF_STARTAUTONEGOFETHTRCVDRVAPI                       STD_OFF
#define ETHIF_ISDEF_TRCVINITOFETHTRCVDRVAPI                           STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLIDXOFEXPLICITBUFRELEASEFILTER            STD_OFF
#define ETHIF_ISDEF_USERIDXOFEXPLICITBUFRELEASEFILTER                 STD_OFF
#define ETHIF_ISDEF_USERUSEDOFEXPLICITBUFRELEASEFILTER                STD_OFF
#define ETHIF_ISDEF_MACADDROFGATEWAYSRCMACBLACKLIST                   STD_OFF
#define ETHIF_ISDEF_LINKSTATECHGINDICATIONS                           STD_OFF
#define ETHIF_ISDEF_ETHCTRLIDXOFMIRRORDEST                            STD_OFF
#define ETHIF_ISDEF_KEEPSRCMACENABLEDOFMIRRORDEST                     STD_OFF
#define ETHIF_ISDEF_ETHSWTINDENDIDXOFPHYSLAYERINITELEMS               STD_OFF
#define ETHIF_ISDEF_ETHSWTINDSTARTIDXOFPHYSLAYERINITELEMS             STD_OFF
#define ETHIF_ISDEF_ETHSWTINDUSEDOFPHYSLAYERINITELEMS                 STD_OFF
#define ETHIF_ISDEF_ETHTRCVIDXOFPHYSLAYERINITELEMS                    STD_OFF
#define ETHIF_ISDEF_ETHTRCVUSEDOFPHYSLAYERINITELEMS                   STD_OFF
#define ETHIF_ISDEF_ETHTRCVIDXOFPHYSLAYERMODEELEMS                    STD_OFF
#define ETHIF_ISDEF_ETHTRCVUSEDOFPHYSLAYERMODEELEMS                   STD_OFF
#define ETHIF_ISDEF_PORTGROUPIDXOFPHYSLAYERMODEELEMS                  STD_OFF
#define ETHIF_ISDEF_PORTGROUPUSEDOFPHYSLAYERMODEELEMS                 STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFPORTGROUPINDENDIDXOFPORTGROUP          STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFPORTGROUPINDSTARTIDXOFPORTGROUP        STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFPORTGROUPINDUSEDOFPORTGROUP            STD_OFF
#define ETHIF_ISDEF_ETHSWTPORTINDENDIDXOFPORTGROUP                    STD_OFF
#define ETHIF_ISDEF_ETHSWTPORTINDSTARTIDXOFPORTGROUP                  STD_OFF
#define ETHIF_ISDEF_LINKAGGRTHRESHOLDOFPORTGROUP                      STD_OFF
#define ETHIF_ISDEF_SEMANTICOFPORTGROUP                               STD_OFF
#define ETHIF_ISDEF_SNVOFPORTGROUP                                    STD_OFF
#define ETHIF_ISDEF_PORTGROUPIND                                      STD_OFF
#define ETHIF_ISDEF_RXINDICATIONS                                     STD_OFF
#define ETHIF_ISDEF_RXINDICATIONSIND                                  STD_OFF
#define ETHIF_ISDEF_TXCONFIRMATIONS                                   STD_OFF
#define ETHIF_ISDEF_TXCONFIRMATIONSIND                                STD_OFF
#define ETHIF_ISDEF_ETHERTYPEOFUSER                                   STD_OFF
#define ETHIF_ISDEF_RXINDICATIONSINDENDIDXOFUSER                      STD_OFF
#define ETHIF_ISDEF_RXINDICATIONSINDSTARTIDXOFUSER                    STD_OFF
#define ETHIF_ISDEF_RXINDICATIONSINDUSEDOFUSER                        STD_OFF
#define ETHIF_ISDEF_TXCONFIRMATIONSINDENDIDXOFUSER                    STD_OFF
#define ETHIF_ISDEF_TXCONFIRMATIONSINDSTARTIDXOFUSER                  STD_OFF
#define ETHIF_ISDEF_TXCONFIRMATIONSINDUSEDOFUSER                      STD_OFF
#define ETHIF_ISDEF_ETHTRCVIDXOFWAKEUPMAP                             STD_OFF
#define ETHIF_ISDEF_WAKEUPSOURCEOFWAKEUPMAP                           STD_OFF
#define ETHIF_ISDEF_ETHCTRLINITCNTOFPCCONFIG                          STD_OFF
#define ETHIF_ISDEF_ETHCTRLMODECNTOFPCCONFIG                          STD_OFF
#define ETHIF_ISDEF_ETHCTRLOFPCCONFIG                                 STD_OFF
#define ETHIF_ISDEF_ETHCTRLRXFRAMECNTOFPCCONFIG                       STD_OFF
#define ETHIF_ISDEF_ETHDRVAPIOFPCCONFIG                               STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLINITSTATEOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLLINKCOUNTOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLLINKSTATEOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLMODEOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFETHTRCVINDOFPCCONFIG                   STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFPCCONFIG                               STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLOFPORTGROUPINDOFPCCONFIG                 STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLRXSTATSOFPCCONFIG                        STD_OFF
#define ETHIF_ISDEF_ETHIFCTRLTXSTATSOFPCCONFIG                        STD_OFF
#define ETHIF_ISDEF_ETHIFMEASUREMENTDATAOFPCCONFIG                    STD_OFF
#define ETHIF_ISDEF_ETHSWTDRVAPIOFPCCONFIG                            STD_OFF
#define ETHIF_ISDEF_ETHSWTDRVOFPCCONFIG                               STD_OFF
#define ETHIF_ISDEF_ETHSWTINDOFPCCONFIG                               STD_OFF
#define ETHIF_ISDEF_ETHSWTINITCNTOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_ETHSWTOFPCCONFIG                                  STD_OFF
#define ETHIF_ISDEF_ETHSWTPORTINDOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_ETHSWTPORTMODECNTOFPCCONFIG                       STD_OFF
#define ETHIF_ISDEF_ETHSWTPORTOFPCCONFIG                              STD_OFF
#define ETHIF_ISDEF_ETHTRCVDRVAPIOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_ETHTRCVINITCNTOFPCCONFIG                          STD_OFF
#define ETHIF_ISDEF_ETHTRCVMODECNTOFPCCONFIG                          STD_OFF
#define ETHIF_ISDEF_ETHTRCVOFPCCONFIG                                 STD_OFF
#define ETHIF_ISDEF_EXPLICITBUFRELEASEFILTEROFPCCONFIG                STD_OFF
#define ETHIF_ISDEF_GATEWAYSRCMACBLACKLISTOFPCCONFIG                  STD_OFF
#define ETHIF_ISDEF_INITLOCKEDOFPCCONFIG                              STD_OFF
#define ETHIF_ISDEF_LINKSTATECHGINDICATIONSOFPCCONFIG                 STD_OFF
#define ETHIF_ISDEF_LINKSTATECHGMAINRELOADOFPCCONFIG                  STD_OFF
#define ETHIF_ISDEF_MAINFUNCSTATEDECOUPLEFREQCNTOFPCCONFIG            STD_OFF
#define ETHIF_ISDEF_MAXFRAMERXPERETHCTRLOFPCCONFIG                    STD_OFF
#define ETHIF_ISDEF_MAXTXBUFPERETHCTRLOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_MIRRORDESTOFPCCONFIG                              STD_OFF
#define ETHIF_ISDEF_MIRRORTXINFOOFPCCONFIG                            STD_OFF
#define ETHIF_ISDEF_MODECHANGELOCKEDOFPCCONFIG                        STD_OFF
#define ETHIF_ISDEF_PHYSLAYERINITELEMSOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_PHYSLAYERMODEELEMSOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_PORTGROUPINDOFPCCONFIG                            STD_OFF
#define ETHIF_ISDEF_PORTGROUPLINKCOUNTOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_PORTGROUPLINKSTATEOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_PORTGROUPMODEOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_PORTGROUPOFPCCONFIG                               STD_OFF
#define ETHIF_ISDEF_PORTSIGNALQUALITYRESULTOFPCCONFIG                 STD_OFF
#define ETHIF_ISDEF_RXINDICATIONSINDOFPCCONFIG                        STD_OFF
#define ETHIF_ISDEF_RXINDICATIONSOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_SIGNALQUALITYCHGMAINRELOADOFPCCONFIG              STD_OFF
#define ETHIF_ISDEF_SIGNALQUALITYDECOUPLEFREQCNTOFPCCONFIG            STD_OFF
#define ETHIF_ISDEF_SIGNALQUALITYRESULTOFPCCONFIG                     STD_OFF
#define ETHIF_ISDEF_SIZEOFETHCTRLOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_SIZEOFETHDRVAPIOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_SIZEOFETHIFCTRLOFETHTRCVINDOFPCCONFIG             STD_OFF
#define ETHIF_ISDEF_SIZEOFETHIFCTRLOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_SIZEOFETHIFCTRLOFPORTGROUPINDOFPCCONFIG           STD_OFF
#define ETHIF_ISDEF_SIZEOFETHIFMEASUREMENTDATAOFPCCONFIG              STD_OFF
#define ETHIF_ISDEF_SIZEOFETHSWTDRVAPIOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_SIZEOFETHSWTDRVOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_SIZEOFETHSWTINDOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_SIZEOFETHSWTOFPCCONFIG                            STD_OFF
#define ETHIF_ISDEF_SIZEOFETHSWTPORTINDOFPCCONFIG                     STD_OFF
#define ETHIF_ISDEF_SIZEOFETHSWTPORTOFPCCONFIG                        STD_OFF
#define ETHIF_ISDEF_SIZEOFETHTRCVDRVAPIOFPCCONFIG                     STD_OFF
#define ETHIF_ISDEF_SIZEOFETHTRCVOFPCCONFIG                           STD_OFF
#define ETHIF_ISDEF_SIZEOFEXPLICITBUFRELEASEFILTEROFPCCONFIG          STD_OFF
#define ETHIF_ISDEF_SIZEOFGATEWAYSRCMACBLACKLISTOFPCCONFIG            STD_OFF
#define ETHIF_ISDEF_SIZEOFLINKSTATECHGINDICATIONSOFPCCONFIG           STD_OFF
#define ETHIF_ISDEF_SIZEOFMIRRORDESTOFPCCONFIG                        STD_OFF
#define ETHIF_ISDEF_SIZEOFMIRRORTXINFOOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_SIZEOFPHYSLAYERINITELEMSOFPCCONFIG                STD_OFF
#define ETHIF_ISDEF_SIZEOFPHYSLAYERMODEELEMSOFPCCONFIG                STD_OFF
#define ETHIF_ISDEF_SIZEOFPORTGROUPINDOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_SIZEOFPORTGROUPOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_SIZEOFRXINDICATIONSINDOFPCCONFIG                  STD_OFF
#define ETHIF_ISDEF_SIZEOFRXINDICATIONSOFPCCONFIG                     STD_OFF
#define ETHIF_ISDEF_SIZEOFTXCONFIRMATIONSINDOFPCCONFIG                STD_OFF
#define ETHIF_ISDEF_SIZEOFTXCONFIRMATIONSOFPCCONFIG                   STD_OFF
#define ETHIF_ISDEF_SIZEOFTXCONTEXTOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_SIZEOFUSEROFPCCONFIG                              STD_OFF
#define ETHIF_ISDEF_SIZEOFWAKEUPMAPOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_SRCMACADDRBUFFEROFPCCONFIG                        STD_OFF
#define ETHIF_ISDEF_TXCONFIRMATIONSINDOFPCCONFIG                      STD_OFF
#define ETHIF_ISDEF_TXCONFIRMATIONSOFPCCONFIG                         STD_OFF
#define ETHIF_ISDEF_TXCONTEXTOFPCCONFIG                               STD_OFF
#define ETHIF_ISDEF_USEROFPCCONFIG                                    STD_OFF
#define ETHIF_ISDEF_WAKEUPMAPOFPCCONFIG                               STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCEqualsAlwaysToDefines  EthIf Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define ETHIF_EQ2_ETHDRVAPIIDXOFETHCTRL                               
#define ETHIF_EQ2_SNVOFETHCTRL                                        
#define ETHIF_EQ2_TXCONTEXTENDIDXOFETHCTRL                            
#define ETHIF_EQ2_TXCONTEXTSTARTIDXOFETHCTRL                          
#define ETHIF_EQ2_CTRLINITOFETHDRVAPI                                 
#define ETHIF_EQ2_ENABLEEGRESSTIMESTAMPOFETHDRVAPI                    
#define ETHIF_EQ2_GETBANDWIDTHLIMITOFETHDRVAPI                        
#define ETHIF_EQ2_GETCTRLMODEOFETHDRVAPI                              
#define ETHIF_EQ2_GETCURRENTTIMEOFETHDRVAPI                           
#define ETHIF_EQ2_GETEGRESSTIMESTAMPOFETHDRVAPI                       
#define ETHIF_EQ2_GETINGRESSTIMESTAMPOFETHDRVAPI                      
#define ETHIF_EQ2_GETPHYSADDROFETHDRVAPI                              
#define ETHIF_EQ2_GETRXHEADERPTROFETHDRVAPI                           
#define ETHIF_EQ2_GETRXSTATSOFETHDRVAPI                               
#define ETHIF_EQ2_GETTXHEADERPTROFETHDRVAPI                           
#define ETHIF_EQ2_GETTXSTATSOFETHDRVAPI                               
#define ETHIF_EQ2_PROVIDEEXTTXBUFFEROFETHDRVAPI                       
#define ETHIF_EQ2_PROVIDETXBUFFEROFETHDRVAPI                          
#define ETHIF_EQ2_RECEIVEOFETHDRVAPI                                  
#define ETHIF_EQ2_RELEASERXBUFFEROFETHDRVAPI                          
#define ETHIF_EQ2_SETBANDWIDTHLIMITOFETHDRVAPI                        
#define ETHIF_EQ2_SETCTRLMODEOFETHDRVAPI                              
#define ETHIF_EQ2_SETPHYSADDROFETHDRVAPI                              
#define ETHIF_EQ2_TRANSMITOFETHDRVAPI                                 
#define ETHIF_EQ2_TXCONFOFETHDRVAPI                                   
#define ETHIF_EQ2_UPDATEPHYSADDRFILTEROFETHDRVAPI                     
#define ETHIF_EQ2_VTRANSMITOFETHDRVAPI                                
#define ETHIF_EQ2_ETHCTRLIDXOFETHIFCTRL                               
#define ETHIF_EQ2_ETHSWTDRVAPIIDXOFETHIFCTRL                          
#define ETHIF_EQ2_ETHSWTDRVAPIUSEDOFETHIFCTRL                         
#define ETHIF_EQ2_GATEWAYDESTETHIFCTRLIDXIDXOFETHIFCTRL               
#define ETHIF_EQ2_GATEWAYDESTETHIFCTRLIDXUSEDOFETHIFCTRL              
#define ETHIF_EQ2_LINKAGGRTHRESHOLDOFETHIFCTRL                        
#define ETHIF_EQ2_MIRRORRXDESTIDXIDXOFETHIFCTRL                       
#define ETHIF_EQ2_MIRRORRXDESTIDXUSEDOFETHIFCTRL                      
#define ETHIF_EQ2_MIRRORTXDESTIDXIDXOFETHIFCTRL                       
#define ETHIF_EQ2_MIRRORTXDESTIDXUSEDOFETHIFCTRL                      
#define ETHIF_EQ2_MTUOFETHIFCTRL                                      
#define ETHIF_EQ2_PHYSLAYERINITELEMSIDXOFETHIFCTRL                    
#define ETHIF_EQ2_PHYSLAYERMODEELEMSIDXOFETHIFCTRL                    
#define ETHIF_EQ2_SNVOFETHIFCTRL                                      
#define ETHIF_EQ2_TYPEOFETHIFCTRL                                     
#define ETHIF_EQ2_VLANIDOFETHIFCTRL                                   
#define ETHIF_EQ2_ETHIFCTRLOFETHTRCVIND                               
#define ETHIF_EQ2_ETHIFCTRLOFPORTGROUPIND                             
#define ETHIF_EQ2_ETHSWTDRVAPIIDXOFETHSWT                             
#define ETHIF_EQ2_SNVOFETHSWT                                         
#define ETHIF_EQ2_ETHSWTENDIDXOFETHSWTDRV                             
#define ETHIF_EQ2_ETHSWTSTARTIDXOFETHSWTDRV                           
#define ETHIF_EQ2_ENABLEVLANOFETHSWTDRVAPI                            
#define ETHIF_EQ2_GETARLTABLEOFETHSWTDRVAPI                           
#define ETHIF_EQ2_GETBAUDRATEOFETHSWTDRVAPI                           
#define ETHIF_EQ2_GETBUFFERLEVELOFETHSWTDRVAPI                        
#define ETHIF_EQ2_GETDROPCOUNTOFETHSWTDRVAPI                          
#define ETHIF_EQ2_GETDUPLEXMODEOFETHSWTDRVAPI                         
#define ETHIF_EQ2_GETLINKSTATEOFETHSWTDRVAPI                          
#define ETHIF_EQ2_GETMACLEARNINGMODEOFETHSWTDRVAPI                    
#define ETHIF_EQ2_GETPORTMACADDROFETHSWTDRVAPI                        
#define ETHIF_EQ2_GETPORTSIGNALQUALITYOFETHSWTDRVAPI                  
#define ETHIF_EQ2_GETRXMGMTOBJECTOFETHSWTDRVAPI                       
#define ETHIF_EQ2_GETSWTPORTMODEOFETHSWTDRVAPI                        
#define ETHIF_EQ2_GETTXMGMTOBJECTOFETHSWTDRVAPI                       
#define ETHIF_EQ2_PORTENABLETIMESTAMPOFETHSWTDRVAPI                   
#define ETHIF_EQ2_RESETCONFIGOFETHSWTDRVAPI                           
#define ETHIF_EQ2_SETCORRECTIONTIMEOFETHSWTDRVAPI                     
#define ETHIF_EQ2_SETMACLEARNINGMODEOFETHSWTDRVAPI                    
#define ETHIF_EQ2_SETSWTMGMTINFOOFETHSWTDRVAPI                        
#define ETHIF_EQ2_SETSWTPORTMODEOFETHSWTDRVAPI                        
#define ETHIF_EQ2_STARTQBVSCHEDULEOFETHSWTDRVAPI                      
#define ETHIF_EQ2_STARTSWTPORTAUTONEGOFETHSWTDRVAPI                   
#define ETHIF_EQ2_STOPQBVSCHEDULEOFETHSWTDRVAPI                       
#define ETHIF_EQ2_STORECONFIGOFETHSWTDRVAPI                           
#define ETHIF_EQ2_SWTINITOFETHSWTDRVAPI                               
#define ETHIF_EQ2_UPDATEMCASTPORTASSIGNMENTOFETHSWTDRVAPI             
#define ETHIF_EQ2_ETHSWTIND                                           
#define ETHIF_EQ2_ETHSWTIDXOFETHSWTPORT                               
#define ETHIF_EQ2_PORTGROUPINDENDIDXOFETHSWTPORT                      
#define ETHIF_EQ2_PORTGROUPINDSTARTIDXOFETHSWTPORT                    
#define ETHIF_EQ2_SNVOFETHSWTPORT                                     
#define ETHIF_EQ2_ETHSWTPORTIND                                       
#define ETHIF_EQ2_ETHIFCTRLOFETHTRCVINDENDIDXOFETHTRCV                
#define ETHIF_EQ2_ETHIFCTRLOFETHTRCVINDSTARTIDXOFETHTRCV              
#define ETHIF_EQ2_ETHIFCTRLOFETHTRCVINDUSEDOFETHTRCV                  
#define ETHIF_EQ2_ETHTRCVDRVAPIIDXOFETHTRCV                           
#define ETHIF_EQ2_SNVOFETHTRCV                                        
#define ETHIF_EQ2_CHECKWAKEUPOFETHTRCVDRVAPI                          
#define ETHIF_EQ2_GETBAUDRATEOFETHTRCVDRVAPI                          
#define ETHIF_EQ2_GETCABLEDIAGNOSTICSRESULTOFETHTRCVDRVAPI            
#define ETHIF_EQ2_GETDUPLEXMODEOFETHTRCVDRVAPI                        
#define ETHIF_EQ2_GETLINKSTATEOFETHTRCVDRVAPI                         
#define ETHIF_EQ2_GETPHYSIGNALQUALITYOFETHTRCVDRVAPI                  
#define ETHIF_EQ2_GETTRCVMODEOFETHTRCVDRVAPI                          
#define ETHIF_EQ2_GETTRCVWAKEUPMODEOFETHTRCVDRVAPI                    
#define ETHIF_EQ2_SETPHYTESTMODEOFETHTRCVDRVAPI                       
#define ETHIF_EQ2_SETPHYTXMODEOFETHTRCVDRVAPI                         
#define ETHIF_EQ2_SETTRCVMODEOFETHTRCVDRVAPI                          
#define ETHIF_EQ2_SETTRCVWAKEUPMODEOFETHTRCVDRVAPI                    
#define ETHIF_EQ2_STARTAUTONEGOFETHTRCVDRVAPI                         
#define ETHIF_EQ2_TRCVINITOFETHTRCVDRVAPI                             
#define ETHIF_EQ2_ETHIFCTRLIDXOFEXPLICITBUFRELEASEFILTER              
#define ETHIF_EQ2_USERIDXOFEXPLICITBUFRELEASEFILTER                   
#define ETHIF_EQ2_USERUSEDOFEXPLICITBUFRELEASEFILTER                  
#define ETHIF_EQ2_MACADDROFGATEWAYSRCMACBLACKLIST                     
#define ETHIF_EQ2_LINKSTATECHGINDICATIONS                             
#define ETHIF_EQ2_ETHCTRLIDXOFMIRRORDEST                              
#define ETHIF_EQ2_KEEPSRCMACENABLEDOFMIRRORDEST                       
#define ETHIF_EQ2_ETHSWTINDENDIDXOFPHYSLAYERINITELEMS                 
#define ETHIF_EQ2_ETHSWTINDSTARTIDXOFPHYSLAYERINITELEMS               
#define ETHIF_EQ2_ETHSWTINDUSEDOFPHYSLAYERINITELEMS                   
#define ETHIF_EQ2_ETHTRCVIDXOFPHYSLAYERINITELEMS                      
#define ETHIF_EQ2_ETHTRCVUSEDOFPHYSLAYERINITELEMS                     
#define ETHIF_EQ2_ETHTRCVIDXOFPHYSLAYERMODEELEMS                      
#define ETHIF_EQ2_ETHTRCVUSEDOFPHYSLAYERMODEELEMS                     
#define ETHIF_EQ2_PORTGROUPIDXOFPHYSLAYERMODEELEMS                    
#define ETHIF_EQ2_PORTGROUPUSEDOFPHYSLAYERMODEELEMS                   
#define ETHIF_EQ2_ETHIFCTRLOFPORTGROUPINDENDIDXOFPORTGROUP            
#define ETHIF_EQ2_ETHIFCTRLOFPORTGROUPINDSTARTIDXOFPORTGROUP          
#define ETHIF_EQ2_ETHIFCTRLOFPORTGROUPINDUSEDOFPORTGROUP              
#define ETHIF_EQ2_ETHSWTPORTINDENDIDXOFPORTGROUP                      
#define ETHIF_EQ2_ETHSWTPORTINDSTARTIDXOFPORTGROUP                    
#define ETHIF_EQ2_LINKAGGRTHRESHOLDOFPORTGROUP                        
#define ETHIF_EQ2_SEMANTICOFPORTGROUP                                 
#define ETHIF_EQ2_SNVOFPORTGROUP                                      
#define ETHIF_EQ2_PORTGROUPIND                                        
#define ETHIF_EQ2_RXINDICATIONS                                       
#define ETHIF_EQ2_RXINDICATIONSIND                                    
#define ETHIF_EQ2_TXCONFIRMATIONS                                     
#define ETHIF_EQ2_TXCONFIRMATIONSIND                                  
#define ETHIF_EQ2_ETHERTYPEOFUSER                                     
#define ETHIF_EQ2_RXINDICATIONSINDENDIDXOFUSER                        
#define ETHIF_EQ2_RXINDICATIONSINDSTARTIDXOFUSER                      
#define ETHIF_EQ2_RXINDICATIONSINDUSEDOFUSER                          
#define ETHIF_EQ2_TXCONFIRMATIONSINDENDIDXOFUSER                      
#define ETHIF_EQ2_TXCONFIRMATIONSINDSTARTIDXOFUSER                    
#define ETHIF_EQ2_TXCONFIRMATIONSINDUSEDOFUSER                        
#define ETHIF_EQ2_ETHTRCVIDXOFWAKEUPMAP                               
#define ETHIF_EQ2_WAKEUPSOURCEOFWAKEUPMAP                             
#define ETHIF_EQ2_ETHCTRLINITCNTOFPCCONFIG                            
#define ETHIF_EQ2_ETHCTRLMODECNTOFPCCONFIG                            
#define ETHIF_EQ2_ETHCTRLOFPCCONFIG                                   
#define ETHIF_EQ2_ETHCTRLRXFRAMECNTOFPCCONFIG                         
#define ETHIF_EQ2_ETHDRVAPIOFPCCONFIG                                 
#define ETHIF_EQ2_ETHIFCTRLINITSTATEOFPCCONFIG                        
#define ETHIF_EQ2_ETHIFCTRLLINKCOUNTOFPCCONFIG                        
#define ETHIF_EQ2_ETHIFCTRLLINKSTATEOFPCCONFIG                        
#define ETHIF_EQ2_ETHIFCTRLMODEOFPCCONFIG                             
#define ETHIF_EQ2_ETHIFCTRLOFETHTRCVINDOFPCCONFIG                     
#define ETHIF_EQ2_ETHIFCTRLOFPCCONFIG                                 
#define ETHIF_EQ2_ETHIFCTRLOFPORTGROUPINDOFPCCONFIG                   
#define ETHIF_EQ2_ETHIFCTRLRXSTATSOFPCCONFIG                          
#define ETHIF_EQ2_ETHIFCTRLTXSTATSOFPCCONFIG                          
#define ETHIF_EQ2_ETHIFMEASUREMENTDATAOFPCCONFIG                      
#define ETHIF_EQ2_ETHSWTDRVAPIOFPCCONFIG                              
#define ETHIF_EQ2_ETHSWTDRVOFPCCONFIG                                 
#define ETHIF_EQ2_ETHSWTINDOFPCCONFIG                                 
#define ETHIF_EQ2_ETHSWTINITCNTOFPCCONFIG                             
#define ETHIF_EQ2_ETHSWTOFPCCONFIG                                    
#define ETHIF_EQ2_ETHSWTPORTINDOFPCCONFIG                             
#define ETHIF_EQ2_ETHSWTPORTMODECNTOFPCCONFIG                         
#define ETHIF_EQ2_ETHSWTPORTOFPCCONFIG                                
#define ETHIF_EQ2_ETHTRCVDRVAPIOFPCCONFIG                             
#define ETHIF_EQ2_ETHTRCVINITCNTOFPCCONFIG                            
#define ETHIF_EQ2_ETHTRCVMODECNTOFPCCONFIG                            
#define ETHIF_EQ2_ETHTRCVOFPCCONFIG                                   
#define ETHIF_EQ2_EXPLICITBUFRELEASEFILTEROFPCCONFIG                  
#define ETHIF_EQ2_GATEWAYSRCMACBLACKLISTOFPCCONFIG                    
#define ETHIF_EQ2_INITLOCKEDOFPCCONFIG                                
#define ETHIF_EQ2_LINKSTATECHGINDICATIONSOFPCCONFIG                   
#define ETHIF_EQ2_LINKSTATECHGMAINRELOADOFPCCONFIG                    
#define ETHIF_EQ2_MAINFUNCSTATEDECOUPLEFREQCNTOFPCCONFIG              
#define ETHIF_EQ2_MAXFRAMERXPERETHCTRLOFPCCONFIG                      
#define ETHIF_EQ2_MAXTXBUFPERETHCTRLOFPCCONFIG                        
#define ETHIF_EQ2_MIRRORDESTOFPCCONFIG                                
#define ETHIF_EQ2_MIRRORTXINFOOFPCCONFIG                              
#define ETHIF_EQ2_MODECHANGELOCKEDOFPCCONFIG                          
#define ETHIF_EQ2_PHYSLAYERINITELEMSOFPCCONFIG                        
#define ETHIF_EQ2_PHYSLAYERMODEELEMSOFPCCONFIG                        
#define ETHIF_EQ2_PORTGROUPINDOFPCCONFIG                              
#define ETHIF_EQ2_PORTGROUPLINKCOUNTOFPCCONFIG                        
#define ETHIF_EQ2_PORTGROUPLINKSTATEOFPCCONFIG                        
#define ETHIF_EQ2_PORTGROUPMODEOFPCCONFIG                             
#define ETHIF_EQ2_PORTGROUPOFPCCONFIG                                 
#define ETHIF_EQ2_PORTSIGNALQUALITYRESULTOFPCCONFIG                   
#define ETHIF_EQ2_RXINDICATIONSINDOFPCCONFIG                          
#define ETHIF_EQ2_RXINDICATIONSOFPCCONFIG                             
#define ETHIF_EQ2_SIGNALQUALITYCHGMAINRELOADOFPCCONFIG                
#define ETHIF_EQ2_SIGNALQUALITYDECOUPLEFREQCNTOFPCCONFIG              
#define ETHIF_EQ2_SIGNALQUALITYRESULTOFPCCONFIG                       
#define ETHIF_EQ2_SIZEOFETHCTRLOFPCCONFIG                             
#define ETHIF_EQ2_SIZEOFETHDRVAPIOFPCCONFIG                           
#define ETHIF_EQ2_SIZEOFETHIFCTRLOFETHTRCVINDOFPCCONFIG               
#define ETHIF_EQ2_SIZEOFETHIFCTRLOFPCCONFIG                           
#define ETHIF_EQ2_SIZEOFETHIFCTRLOFPORTGROUPINDOFPCCONFIG             
#define ETHIF_EQ2_SIZEOFETHIFMEASUREMENTDATAOFPCCONFIG                
#define ETHIF_EQ2_SIZEOFETHSWTDRVAPIOFPCCONFIG                        
#define ETHIF_EQ2_SIZEOFETHSWTDRVOFPCCONFIG                           
#define ETHIF_EQ2_SIZEOFETHSWTINDOFPCCONFIG                           
#define ETHIF_EQ2_SIZEOFETHSWTOFPCCONFIG                              
#define ETHIF_EQ2_SIZEOFETHSWTPORTINDOFPCCONFIG                       
#define ETHIF_EQ2_SIZEOFETHSWTPORTOFPCCONFIG                          
#define ETHIF_EQ2_SIZEOFETHTRCVDRVAPIOFPCCONFIG                       
#define ETHIF_EQ2_SIZEOFETHTRCVOFPCCONFIG                             
#define ETHIF_EQ2_SIZEOFEXPLICITBUFRELEASEFILTEROFPCCONFIG            
#define ETHIF_EQ2_SIZEOFGATEWAYSRCMACBLACKLISTOFPCCONFIG              
#define ETHIF_EQ2_SIZEOFLINKSTATECHGINDICATIONSOFPCCONFIG             
#define ETHIF_EQ2_SIZEOFMIRRORDESTOFPCCONFIG                          
#define ETHIF_EQ2_SIZEOFMIRRORTXINFOOFPCCONFIG                        
#define ETHIF_EQ2_SIZEOFPHYSLAYERINITELEMSOFPCCONFIG                  
#define ETHIF_EQ2_SIZEOFPHYSLAYERMODEELEMSOFPCCONFIG                  
#define ETHIF_EQ2_SIZEOFPORTGROUPINDOFPCCONFIG                        
#define ETHIF_EQ2_SIZEOFPORTGROUPOFPCCONFIG                           
#define ETHIF_EQ2_SIZEOFRXINDICATIONSINDOFPCCONFIG                    
#define ETHIF_EQ2_SIZEOFRXINDICATIONSOFPCCONFIG                       
#define ETHIF_EQ2_SIZEOFTXCONFIRMATIONSINDOFPCCONFIG                  
#define ETHIF_EQ2_SIZEOFTXCONFIRMATIONSOFPCCONFIG                     
#define ETHIF_EQ2_SIZEOFTXCONTEXTOFPCCONFIG                           
#define ETHIF_EQ2_SIZEOFUSEROFPCCONFIG                                
#define ETHIF_EQ2_SIZEOFWAKEUPMAPOFPCCONFIG                           
#define ETHIF_EQ2_SRCMACADDRBUFFEROFPCCONFIG                          
#define ETHIF_EQ2_TXCONFIRMATIONSINDOFPCCONFIG                        
#define ETHIF_EQ2_TXCONFIRMATIONSOFPCCONFIG                           
#define ETHIF_EQ2_TXCONTEXTOFPCCONFIG                                 
#define ETHIF_EQ2_USEROFPCCONFIG                                      
#define ETHIF_EQ2_WAKEUPMAPOFPCCONFIG                                 
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCSymbolicInitializationPointers  EthIf Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define EthIf_Config_Ptr                                              &(EthIf_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'EthIf' */
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCInitializationSymbols  EthIf Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define EthIf_Config                                                  EthIf_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'EthIf */
/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCGeneral  EthIf General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define ETHIF_CHECK_INIT_POINTER                                      STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define ETHIF_FINAL_MAGIC_NUMBER                                      0x891Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of EthIf */
#define ETHIF_INDIVIDUAL_POSTBUILD                                    STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'EthIf' is not configured to be postbuild capable. */
#define ETHIF_INIT_DATA                                               ETHIF_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define ETHIF_INIT_DATA_HASH_CODE                                     549217577  /**< the precompile constant to validate the initialization structure at initialization time of EthIf with a hashcode. The seed value is '0x891Eu' */
#define ETHIF_USE_ECUM_BSW_ERROR_HOOK                                 STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define ETHIF_USE_INIT_POINTER                                        STD_ON  /**< STD_ON if the init pointer EthIf shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthIfPCIterableTypes  EthIf Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate EthIf_EthCtrl */
typedef uint8_least EthIf_EthCtrlIterType;

/**   \brief  type used to iterate EthIf_EthDrvApi */
typedef uint8_least EthIf_EthDrvApiIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrl */
typedef uint8_least EthIf_EthIfCtrlIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlOfEthTrcvInd */
typedef uint8_least EthIf_EthIfCtrlOfEthTrcvIndIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlOfPortGroupInd */
typedef uint8_least EthIf_EthIfCtrlOfPortGroupIndIterType;

/**   \brief  type used to iterate EthIf_EthIfMeasurementData */
typedef uint8_least EthIf_EthIfMeasurementDataIterType;

/**   \brief  type used to iterate EthIf_EthSwt */
typedef uint8_least EthIf_EthSwtIterType;

/**   \brief  type used to iterate EthIf_EthSwtDrv */
typedef uint8_least EthIf_EthSwtDrvIterType;

/**   \brief  type used to iterate EthIf_EthSwtDrvApi */
typedef uint8_least EthIf_EthSwtDrvApiIterType;

/**   \brief  type used to iterate EthIf_EthSwtInd */
typedef uint8_least EthIf_EthSwtIndIterType;

/**   \brief  type used to iterate EthIf_EthSwtPort */
typedef uint8_least EthIf_EthSwtPortIterType;

/**   \brief  type used to iterate EthIf_EthSwtPortInd */
typedef uint8_least EthIf_EthSwtPortIndIterType;

/**   \brief  type used to iterate EthIf_EthTrcv */
typedef uint8_least EthIf_EthTrcvIterType;

/**   \brief  type used to iterate EthIf_EthTrcvDrvApi */
typedef uint8_least EthIf_EthTrcvDrvApiIterType;

/**   \brief  type used to iterate EthIf_ExplicitBufReleaseFilter */
typedef uint8_least EthIf_ExplicitBufReleaseFilterIterType;

/**   \brief  type used to iterate EthIf_GatewaySrcMacBlackList */
typedef uint8_least EthIf_GatewaySrcMacBlackListIterType;

/**   \brief  type used to iterate EthIf_LinkStateChgIndications */
typedef uint8_least EthIf_LinkStateChgIndicationsIterType;

/**   \brief  type used to iterate EthIf_MirrorDest */
typedef uint8_least EthIf_MirrorDestIterType;

/**   \brief  type used to iterate EthIf_MirrorTxInfo */
typedef uint8_least EthIf_MirrorTxInfoIterType;

/**   \brief  type used to iterate EthIf_PhysLayerInitElems */
typedef uint8_least EthIf_PhysLayerInitElemsIterType;

/**   \brief  type used to iterate EthIf_PhysLayerModeElems */
typedef uint8_least EthIf_PhysLayerModeElemsIterType;

/**   \brief  type used to iterate EthIf_PortGroup */
typedef uint8_least EthIf_PortGroupIterType;

/**   \brief  type used to iterate EthIf_PortGroupInd */
typedef uint8_least EthIf_PortGroupIndIterType;

/**   \brief  type used to iterate EthIf_RxIndications */
typedef uint8_least EthIf_RxIndicationsIterType;

/**   \brief  type used to iterate EthIf_RxIndicationsInd */
typedef uint8_least EthIf_RxIndicationsIndIterType;

/**   \brief  type used to iterate EthIf_TxConfirmations */
typedef uint8_least EthIf_TxConfirmationsIterType;

/**   \brief  type used to iterate EthIf_TxConfirmationsInd */
typedef uint8_least EthIf_TxConfirmationsIndIterType;

/**   \brief  type used to iterate EthIf_TxContext */
typedef uint8_least EthIf_TxContextIterType;

/**   \brief  type used to iterate EthIf_User */
typedef uint8_least EthIf_UserIterType;

/**   \brief  type used to iterate EthIf_WakeupMap */
typedef uint8_least EthIf_WakeupMapIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCIterableTypesWithSizeRelations  EthIf Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate EthIf_EthCtrlInitCnt */
typedef EthIf_EthCtrlIterType EthIf_EthCtrlInitCntIterType;

/**   \brief  type used to iterate EthIf_EthCtrlModeCnt */
typedef EthIf_EthCtrlIterType EthIf_EthCtrlModeCntIterType;

/**   \brief  type used to iterate EthIf_EthCtrlRxFrameCnt */
typedef EthIf_EthCtrlIterType EthIf_EthCtrlRxFrameCntIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlInitState */
typedef EthIf_EthIfCtrlIterType EthIf_EthIfCtrlInitStateIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlLinkCount */
typedef EthIf_EthIfCtrlIterType EthIf_EthIfCtrlLinkCountIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlLinkState */
typedef EthIf_EthIfCtrlIterType EthIf_EthIfCtrlLinkStateIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlMode */
typedef EthIf_EthIfCtrlIterType EthIf_EthIfCtrlModeIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlRxStats */
typedef EthIf_EthIfCtrlIterType EthIf_EthIfCtrlRxStatsIterType;

/**   \brief  type used to iterate EthIf_EthIfCtrlTxStats */
typedef EthIf_EthIfCtrlIterType EthIf_EthIfCtrlTxStatsIterType;

/**   \brief  type used to iterate EthIf_EthSwtInitCnt */
typedef EthIf_EthSwtIterType EthIf_EthSwtInitCntIterType;

/**   \brief  type used to iterate EthIf_EthSwtPortModeCnt */
typedef EthIf_EthSwtPortIterType EthIf_EthSwtPortModeCntIterType;

/**   \brief  type used to iterate EthIf_EthTrcvInitCnt */
typedef EthIf_EthTrcvIterType EthIf_EthTrcvInitCntIterType;

/**   \brief  type used to iterate EthIf_EthTrcvModeCnt */
typedef EthIf_EthTrcvIterType EthIf_EthTrcvModeCntIterType;

/**   \brief  type used to iterate EthIf_PortGroupLinkCount */
typedef EthIf_PortGroupIterType EthIf_PortGroupLinkCountIterType;

/**   \brief  type used to iterate EthIf_PortGroupLinkState */
typedef EthIf_PortGroupIterType EthIf_PortGroupLinkStateIterType;

/**   \brief  type used to iterate EthIf_PortGroupMode */
typedef EthIf_PortGroupIterType EthIf_PortGroupModeIterType;

/**   \brief  type used to iterate EthIf_PortSignalQualityResult */
typedef EthIf_EthSwtPortIterType EthIf_PortSignalQualityResultIterType;

/**   \brief  type used to iterate EthIf_SignalQualityResult */
typedef EthIf_EthTrcvIterType EthIf_SignalQualityResultIterType;

/**   \brief  type used to iterate EthIf_SrcMacAddrBuffer */
typedef EthIf_EthCtrlIterType EthIf_SrcMacAddrBufferIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCValueTypes  EthIf Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for EthIf_EthDrvApiIdxOfEthCtrl */
typedef uint8 EthIf_EthDrvApiIdxOfEthCtrlType;

/**   \brief  value based type definition for EthIf_SnvOfEthCtrl */
typedef uint32 EthIf_SnvOfEthCtrlType;

/**   \brief  value based type definition for EthIf_TxContextEndIdxOfEthCtrl */
typedef uint8 EthIf_TxContextEndIdxOfEthCtrlType;

/**   \brief  value based type definition for EthIf_TxContextStartIdxOfEthCtrl */
typedef uint8 EthIf_TxContextStartIdxOfEthCtrlType;

/**   \brief  value based type definition for EthIf_EthCtrlInitCnt */
typedef uint8 EthIf_EthCtrlInitCntType;

/**   \brief  value based type definition for EthIf_EthCtrlModeCnt */
typedef uint8 EthIf_EthCtrlModeCntType;

/**   \brief  value based type definition for EthIf_EthCtrlRxFrameCnt */
typedef uint8 EthIf_EthCtrlRxFrameCntType;

/**   \brief  value based type definition for EthIf_EthCtrlIdxOfEthIfCtrl */
typedef uint8 EthIf_EthCtrlIdxOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_EthSwtDrvApiIdxOfEthIfCtrl */
typedef uint8 EthIf_EthSwtDrvApiIdxOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_EthSwtDrvApiUsedOfEthIfCtrl */
typedef boolean EthIf_EthSwtDrvApiUsedOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_GatewayDestEthIfCtrlIdxIdxOfEthIfCtrl */
typedef uint8 EthIf_GatewayDestEthIfCtrlIdxIdxOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_GatewayDestEthIfCtrlIdxUsedOfEthIfCtrl */
typedef boolean EthIf_GatewayDestEthIfCtrlIdxUsedOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_LinkAggrThresholdOfEthIfCtrl */
typedef uint8 EthIf_LinkAggrThresholdOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_MirrorRxDestIdxIdxOfEthIfCtrl */
typedef uint8 EthIf_MirrorRxDestIdxIdxOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_MirrorRxDestIdxUsedOfEthIfCtrl */
typedef boolean EthIf_MirrorRxDestIdxUsedOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_MirrorTxDestIdxIdxOfEthIfCtrl */
typedef uint8 EthIf_MirrorTxDestIdxIdxOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_MirrorTxDestIdxUsedOfEthIfCtrl */
typedef boolean EthIf_MirrorTxDestIdxUsedOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_MtuOfEthIfCtrl */
typedef uint16 EthIf_MtuOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_PhysLayerInitElemsIdxOfEthIfCtrl */
typedef uint8 EthIf_PhysLayerInitElemsIdxOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_PhysLayerModeElemsIdxOfEthIfCtrl */
typedef uint8 EthIf_PhysLayerModeElemsIdxOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_SnvOfEthIfCtrl */
typedef uint32 EthIf_SnvOfEthIfCtrlType;

/**   \brief  type used in EthIf_TypeOfEthIfCtrl */
typedef enum eEthIf_TypeOfEthIfCtrlType
{
  ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL = 0u,
  ETHIF_ETHIFCTRL_TYPE_Q_TAGGED_VLAN_TYPEOFETHIFCTRL = 1u,
  ETHIF_ETHIFCTRL_TYPE_Q_TAGGED_PRIO_TYPEOFETHIFCTRL = 2u
} EthIf_TypeOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_VlanIdOfEthIfCtrl */
typedef uint8 EthIf_VlanIdOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_EthIfCtrlLinkCount */
typedef uint8 EthIf_EthIfCtrlLinkCountType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfEthTrcvInd */
typedef uint8 EthIf_EthIfCtrlOfEthTrcvIndType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfPortGroupInd */
typedef uint8 EthIf_EthIfCtrlOfPortGroupIndType;

/**   \brief  value based type definition for EthIf_NumRxBytesOfEthIfCtrlRxStats */
typedef uint32 EthIf_NumRxBytesOfEthIfCtrlRxStatsType;

/**   \brief  value based type definition for EthIf_NumRxPktsOfEthIfCtrlRxStats */
typedef uint32 EthIf_NumRxPktsOfEthIfCtrlRxStatsType;

/**   \brief  value based type definition for EthIf_NumTxBytesOfEthIfCtrlTxStats */
typedef uint32 EthIf_NumTxBytesOfEthIfCtrlTxStatsType;

/**   \brief  value based type definition for EthIf_NumTxPktsOfEthIfCtrlTxStats */
typedef uint32 EthIf_NumTxPktsOfEthIfCtrlTxStatsType;

/**   \brief  value based type definition for EthIf_DropCtrlIdxOfEthIfMeasurementData */
typedef uint32 EthIf_DropCtrlIdxOfEthIfMeasurementDataType;

/**   \brief  value based type definition for EthIf_UnknownEtherTypeOfEthIfMeasurementData */
typedef uint32 EthIf_UnknownEtherTypeOfEthIfMeasurementDataType;

/**   \brief  value based type definition for EthIf_VlanDoubleTaggedOfEthIfMeasurementData */
typedef uint32 EthIf_VlanDoubleTaggedOfEthIfMeasurementDataType;

/**   \brief  value based type definition for EthIf_EthSwtDrvApiIdxOfEthSwt */
typedef uint8 EthIf_EthSwtDrvApiIdxOfEthSwtType;

/**   \brief  value based type definition for EthIf_SnvOfEthSwt */
typedef uint32 EthIf_SnvOfEthSwtType;

/**   \brief  value based type definition for EthIf_EthSwtEndIdxOfEthSwtDrv */
typedef uint8 EthIf_EthSwtEndIdxOfEthSwtDrvType;

/**   \brief  value based type definition for EthIf_EthSwtStartIdxOfEthSwtDrv */
typedef uint8 EthIf_EthSwtStartIdxOfEthSwtDrvType;

/**   \brief  value based type definition for EthIf_EthSwtInd */
typedef uint8 EthIf_EthSwtIndType;

/**   \brief  value based type definition for EthIf_EthSwtInitCnt */
typedef uint8 EthIf_EthSwtInitCntType;

/**   \brief  value based type definition for EthIf_EthSwtIdxOfEthSwtPort */
typedef uint8 EthIf_EthSwtIdxOfEthSwtPortType;

/**   \brief  value based type definition for EthIf_PortGroupIndEndIdxOfEthSwtPort */
typedef uint8 EthIf_PortGroupIndEndIdxOfEthSwtPortType;

/**   \brief  value based type definition for EthIf_PortGroupIndStartIdxOfEthSwtPort */
typedef uint8 EthIf_PortGroupIndStartIdxOfEthSwtPortType;

/**   \brief  value based type definition for EthIf_SnvOfEthSwtPort */
typedef uint32 EthIf_SnvOfEthSwtPortType;

/**   \brief  value based type definition for EthIf_EthSwtPortInd */
typedef uint8 EthIf_EthSwtPortIndType;

/**   \brief  value based type definition for EthIf_EthSwtPortModeCnt */
typedef uint8 EthIf_EthSwtPortModeCntType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfEthTrcvIndEndIdxOfEthTrcv */
typedef uint8 EthIf_EthIfCtrlOfEthTrcvIndEndIdxOfEthTrcvType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfEthTrcvIndStartIdxOfEthTrcv */
typedef uint8 EthIf_EthIfCtrlOfEthTrcvIndStartIdxOfEthTrcvType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfEthTrcvIndUsedOfEthTrcv */
typedef boolean EthIf_EthIfCtrlOfEthTrcvIndUsedOfEthTrcvType;

/**   \brief  value based type definition for EthIf_EthTrcvDrvApiIdxOfEthTrcv */
typedef uint8 EthIf_EthTrcvDrvApiIdxOfEthTrcvType;

/**   \brief  value based type definition for EthIf_SnvOfEthTrcv */
typedef uint32 EthIf_SnvOfEthTrcvType;

/**   \brief  value based type definition for EthIf_EthTrcvInitCnt */
typedef uint8 EthIf_EthTrcvInitCntType;

/**   \brief  value based type definition for EthIf_EthTrcvModeCnt */
typedef uint8 EthIf_EthTrcvModeCntType;

/**   \brief  value based type definition for EthIf_EthIfCtrlIdxOfExplicitBufReleaseFilter */
typedef uint8 EthIf_EthIfCtrlIdxOfExplicitBufReleaseFilterType;

/**   \brief  value based type definition for EthIf_UserIdxOfExplicitBufReleaseFilter */
typedef uint8 EthIf_UserIdxOfExplicitBufReleaseFilterType;

/**   \brief  value based type definition for EthIf_UserUsedOfExplicitBufReleaseFilter */
typedef boolean EthIf_UserUsedOfExplicitBufReleaseFilterType;

/**   \brief  value based type definition for EthIf_InitLocked */
typedef boolean EthIf_InitLockedType;

/**   \brief  value based type definition for EthIf_LinkStateChgMainReload */
typedef uint8 EthIf_LinkStateChgMainReloadType;

/**   \brief  value based type definition for EthIf_MainFuncStateDecoupleFreqCnt */
typedef uint16 EthIf_MainFuncStateDecoupleFreqCntType;

/**   \brief  value based type definition for EthIf_MaxFrameRxPerEthCtrl */
typedef uint8 EthIf_MaxFrameRxPerEthCtrlType;

/**   \brief  value based type definition for EthIf_MaxTxBufPerEthCtrl */
typedef uint8 EthIf_MaxTxBufPerEthCtrlType;

/**   \brief  value based type definition for EthIf_EthCtrlIdxOfMirrorDest */
typedef uint8 EthIf_EthCtrlIdxOfMirrorDestType;

/**   \brief  value based type definition for EthIf_KeepSrcMacEnabledOfMirrorDest */
typedef boolean EthIf_KeepSrcMacEnabledOfMirrorDestType;

/**   \brief  value based type definition for EthIf_DestEthTxBufferIdxOfMirrorTxInfo */
typedef uint8 EthIf_DestEthTxBufferIdxOfMirrorTxInfoType;

/**   \brief  value based type definition for EthIf_EthIfCtrlIdxOfMirrorTxInfo */
typedef uint8 EthIf_EthIfCtrlIdxOfMirrorTxInfoType;

/**   \brief  value based type definition for EthIf_InfoValidOfMirrorTxInfo */
typedef boolean EthIf_InfoValidOfMirrorTxInfoType;

/**   \brief  value based type definition for EthIf_SrcEthTxBufferIdxOfMirrorTxInfo */
typedef uint8 EthIf_SrcEthTxBufferIdxOfMirrorTxInfoType;

/**   \brief  value based type definition for EthIf_UsedOfMirrorTxInfo */
typedef boolean EthIf_UsedOfMirrorTxInfoType;

/**   \brief  value based type definition for EthIf_ModeChangeLocked */
typedef boolean EthIf_ModeChangeLockedType;

/**   \brief  value based type definition for EthIf_EthSwtIndEndIdxOfPhysLayerInitElems */
typedef uint8 EthIf_EthSwtIndEndIdxOfPhysLayerInitElemsType;

/**   \brief  value based type definition for EthIf_EthSwtIndStartIdxOfPhysLayerInitElems */
typedef uint8 EthIf_EthSwtIndStartIdxOfPhysLayerInitElemsType;

/**   \brief  value based type definition for EthIf_EthSwtIndUsedOfPhysLayerInitElems */
typedef boolean EthIf_EthSwtIndUsedOfPhysLayerInitElemsType;

/**   \brief  value based type definition for EthIf_EthTrcvIdxOfPhysLayerInitElems */
typedef uint8 EthIf_EthTrcvIdxOfPhysLayerInitElemsType;

/**   \brief  value based type definition for EthIf_EthTrcvUsedOfPhysLayerInitElems */
typedef boolean EthIf_EthTrcvUsedOfPhysLayerInitElemsType;

/**   \brief  value based type definition for EthIf_EthTrcvIdxOfPhysLayerModeElems */
typedef uint8 EthIf_EthTrcvIdxOfPhysLayerModeElemsType;

/**   \brief  value based type definition for EthIf_EthTrcvUsedOfPhysLayerModeElems */
typedef boolean EthIf_EthTrcvUsedOfPhysLayerModeElemsType;

/**   \brief  value based type definition for EthIf_PortGroupIdxOfPhysLayerModeElems */
typedef uint8 EthIf_PortGroupIdxOfPhysLayerModeElemsType;

/**   \brief  value based type definition for EthIf_PortGroupUsedOfPhysLayerModeElems */
typedef boolean EthIf_PortGroupUsedOfPhysLayerModeElemsType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfPortGroupIndEndIdxOfPortGroup */
typedef uint8 EthIf_EthIfCtrlOfPortGroupIndEndIdxOfPortGroupType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfPortGroupIndStartIdxOfPortGroup */
typedef uint8 EthIf_EthIfCtrlOfPortGroupIndStartIdxOfPortGroupType;

/**   \brief  value based type definition for EthIf_EthIfCtrlOfPortGroupIndUsedOfPortGroup */
typedef boolean EthIf_EthIfCtrlOfPortGroupIndUsedOfPortGroupType;

/**   \brief  value based type definition for EthIf_EthSwtPortIndEndIdxOfPortGroup */
typedef uint8 EthIf_EthSwtPortIndEndIdxOfPortGroupType;

/**   \brief  value based type definition for EthIf_EthSwtPortIndStartIdxOfPortGroup */
typedef uint8 EthIf_EthSwtPortIndStartIdxOfPortGroupType;

/**   \brief  value based type definition for EthIf_LinkAggrThresholdOfPortGroup */
typedef uint8 EthIf_LinkAggrThresholdOfPortGroupType;

/**   \brief  type used in EthIf_SemanticOfPortGroup */
typedef enum eEthIf_SemanticOfPortGroupType
{
  ETHIF_PORTGROUP_SEMANTIC_CONTROL_SEMANTICOFPORTGROUP = 0u,
  ETHIF_PORTGROUP_SEMANTIC_LINK_INFO_SEMANTICOFPORTGROUP = 1u,
  ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP = 2u
} EthIf_SemanticOfPortGroupType;

/**   \brief  value based type definition for EthIf_SnvOfPortGroup */
typedef uint32 EthIf_SnvOfPortGroupType;

/**   \brief  value based type definition for EthIf_PortGroupInd */
typedef uint8 EthIf_PortGroupIndType;

/**   \brief  value based type definition for EthIf_PortGroupLinkCount */
typedef uint8 EthIf_PortGroupLinkCountType;

/**   \brief  value based type definition for EthIf_RxIndicationsInd */
typedef uint8 EthIf_RxIndicationsIndType;

/**   \brief  value based type definition for EthIf_SignalQualityChgMainReload */
typedef uint8 EthIf_SignalQualityChgMainReloadType;

/**   \brief  value based type definition for EthIf_SignalQualityDecoupleFreqCnt */
typedef uint16 EthIf_SignalQualityDecoupleFreqCntType;

/**   \brief  value based type definition for EthIf_SizeOfEthCtrl */
typedef uint8 EthIf_SizeOfEthCtrlType;

/**   \brief  value based type definition for EthIf_SizeOfEthCtrlInitCnt */
typedef uint8 EthIf_SizeOfEthCtrlInitCntType;

/**   \brief  value based type definition for EthIf_SizeOfEthCtrlModeCnt */
typedef uint8 EthIf_SizeOfEthCtrlModeCntType;

/**   \brief  value based type definition for EthIf_SizeOfEthCtrlRxFrameCnt */
typedef uint8 EthIf_SizeOfEthCtrlRxFrameCntType;

/**   \brief  value based type definition for EthIf_SizeOfEthDrvApi */
typedef uint8 EthIf_SizeOfEthDrvApiType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrl */
typedef uint8 EthIf_SizeOfEthIfCtrlType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlInitState */
typedef uint8 EthIf_SizeOfEthIfCtrlInitStateType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlLinkCount */
typedef uint8 EthIf_SizeOfEthIfCtrlLinkCountType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlLinkState */
typedef uint8 EthIf_SizeOfEthIfCtrlLinkStateType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlMode */
typedef uint8 EthIf_SizeOfEthIfCtrlModeType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlOfEthTrcvInd */
typedef uint8 EthIf_SizeOfEthIfCtrlOfEthTrcvIndType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlOfPortGroupInd */
typedef uint8 EthIf_SizeOfEthIfCtrlOfPortGroupIndType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlRxStats */
typedef uint8 EthIf_SizeOfEthIfCtrlRxStatsType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfCtrlTxStats */
typedef uint8 EthIf_SizeOfEthIfCtrlTxStatsType;

/**   \brief  value based type definition for EthIf_SizeOfEthIfMeasurementData */
typedef uint8 EthIf_SizeOfEthIfMeasurementDataType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwt */
typedef uint8 EthIf_SizeOfEthSwtType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwtDrv */
typedef uint8 EthIf_SizeOfEthSwtDrvType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwtDrvApi */
typedef uint8 EthIf_SizeOfEthSwtDrvApiType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwtInd */
typedef uint8 EthIf_SizeOfEthSwtIndType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwtInitCnt */
typedef uint8 EthIf_SizeOfEthSwtInitCntType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwtPort */
typedef uint8 EthIf_SizeOfEthSwtPortType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwtPortInd */
typedef uint8 EthIf_SizeOfEthSwtPortIndType;

/**   \brief  value based type definition for EthIf_SizeOfEthSwtPortModeCnt */
typedef uint8 EthIf_SizeOfEthSwtPortModeCntType;

/**   \brief  value based type definition for EthIf_SizeOfEthTrcv */
typedef uint8 EthIf_SizeOfEthTrcvType;

/**   \brief  value based type definition for EthIf_SizeOfEthTrcvDrvApi */
typedef uint8 EthIf_SizeOfEthTrcvDrvApiType;

/**   \brief  value based type definition for EthIf_SizeOfEthTrcvInitCnt */
typedef uint8 EthIf_SizeOfEthTrcvInitCntType;

/**   \brief  value based type definition for EthIf_SizeOfEthTrcvModeCnt */
typedef uint8 EthIf_SizeOfEthTrcvModeCntType;

/**   \brief  value based type definition for EthIf_SizeOfExplicitBufReleaseFilter */
typedef uint8 EthIf_SizeOfExplicitBufReleaseFilterType;

/**   \brief  value based type definition for EthIf_SizeOfGatewaySrcMacBlackList */
typedef uint8 EthIf_SizeOfGatewaySrcMacBlackListType;

/**   \brief  value based type definition for EthIf_SizeOfLinkStateChgIndications */
typedef uint8 EthIf_SizeOfLinkStateChgIndicationsType;

/**   \brief  value based type definition for EthIf_SizeOfMirrorDest */
typedef uint8 EthIf_SizeOfMirrorDestType;

/**   \brief  value based type definition for EthIf_SizeOfMirrorTxInfo */
typedef uint8 EthIf_SizeOfMirrorTxInfoType;

/**   \brief  value based type definition for EthIf_SizeOfPhysLayerInitElems */
typedef uint8 EthIf_SizeOfPhysLayerInitElemsType;

/**   \brief  value based type definition for EthIf_SizeOfPhysLayerModeElems */
typedef uint8 EthIf_SizeOfPhysLayerModeElemsType;

/**   \brief  value based type definition for EthIf_SizeOfPortGroup */
typedef uint8 EthIf_SizeOfPortGroupType;

/**   \brief  value based type definition for EthIf_SizeOfPortGroupInd */
typedef uint8 EthIf_SizeOfPortGroupIndType;

/**   \brief  value based type definition for EthIf_SizeOfPortGroupLinkCount */
typedef uint8 EthIf_SizeOfPortGroupLinkCountType;

/**   \brief  value based type definition for EthIf_SizeOfPortGroupLinkState */
typedef uint8 EthIf_SizeOfPortGroupLinkStateType;

/**   \brief  value based type definition for EthIf_SizeOfPortGroupMode */
typedef uint8 EthIf_SizeOfPortGroupModeType;

/**   \brief  value based type definition for EthIf_SizeOfPortSignalQualityResult */
typedef uint8 EthIf_SizeOfPortSignalQualityResultType;

/**   \brief  value based type definition for EthIf_SizeOfRxIndications */
typedef uint8 EthIf_SizeOfRxIndicationsType;

/**   \brief  value based type definition for EthIf_SizeOfRxIndicationsInd */
typedef uint8 EthIf_SizeOfRxIndicationsIndType;

/**   \brief  value based type definition for EthIf_SizeOfSignalQualityResult */
typedef uint8 EthIf_SizeOfSignalQualityResultType;

/**   \brief  value based type definition for EthIf_SizeOfSrcMacAddrBuffer */
typedef uint8 EthIf_SizeOfSrcMacAddrBufferType;

/**   \brief  value based type definition for EthIf_SizeOfTxConfirmations */
typedef uint8 EthIf_SizeOfTxConfirmationsType;

/**   \brief  value based type definition for EthIf_SizeOfTxConfirmationsInd */
typedef uint8 EthIf_SizeOfTxConfirmationsIndType;

/**   \brief  value based type definition for EthIf_SizeOfTxContext */
typedef uint8 EthIf_SizeOfTxContextType;

/**   \brief  value based type definition for EthIf_SizeOfUser */
typedef uint8 EthIf_SizeOfUserType;

/**   \brief  value based type definition for EthIf_SizeOfWakeupMap */
typedef uint8 EthIf_SizeOfWakeupMapType;

/**   \brief  value based type definition for EthIf_ValidOfSrcMacAddrBuffer */
typedef boolean EthIf_ValidOfSrcMacAddrBufferType;

/**   \brief  value based type definition for EthIf_TxConfirmationsInd */
typedef uint8 EthIf_TxConfirmationsIndType;

/**   \brief  value based type definition for EthIf_EthIfCtrlIdxOfTxContext */
typedef uint8 EthIf_EthIfCtrlIdxOfTxContextType;

/**   \brief  value based type definition for EthIf_PayloadLenOfTxContext */
typedef uint16 EthIf_PayloadLenOfTxContextType;

/**   \brief  value based type definition for EthIf_TxPendingOfTxContext */
typedef boolean EthIf_TxPendingOfTxContextType;

/**   \brief  value based type definition for EthIf_UserIdxOfTxContext */
typedef uint8 EthIf_UserIdxOfTxContextType;

/**   \brief  value based type definition for EthIf_ValidOfTxContext */
typedef boolean EthIf_ValidOfTxContextType;

/**   \brief  value based type definition for EthIf_EtherTypeOfUser */
typedef uint16 EthIf_EtherTypeOfUserType;

/**   \brief  value based type definition for EthIf_RxIndicationsIndEndIdxOfUser */
typedef uint8 EthIf_RxIndicationsIndEndIdxOfUserType;

/**   \brief  value based type definition for EthIf_RxIndicationsIndStartIdxOfUser */
typedef uint8 EthIf_RxIndicationsIndStartIdxOfUserType;

/**   \brief  value based type definition for EthIf_RxIndicationsIndUsedOfUser */
typedef boolean EthIf_RxIndicationsIndUsedOfUserType;

/**   \brief  value based type definition for EthIf_TxConfirmationsIndEndIdxOfUser */
typedef uint8 EthIf_TxConfirmationsIndEndIdxOfUserType;

/**   \brief  value based type definition for EthIf_TxConfirmationsIndStartIdxOfUser */
typedef uint8 EthIf_TxConfirmationsIndStartIdxOfUserType;

/**   \brief  value based type definition for EthIf_TxConfirmationsIndUsedOfUser */
typedef boolean EthIf_TxConfirmationsIndUsedOfUserType;

/**   \brief  value based type definition for EthIf_EthTrcvIdxOfWakeupMap */
typedef uint8 EthIf_EthTrcvIdxOfWakeupMapType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthIfPCStructTypes  EthIf Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in EthIf_EthCtrl */
typedef struct sEthIf_EthCtrlType
{
  EthIf_SnvOfEthCtrlType SnvOfEthCtrl;  /**< SNV of the Eth controller */
  EthIf_EthDrvApiIdxOfEthCtrlType EthDrvApiIdxOfEthCtrl;  /**< the index of the 1:1 relation pointing to EthIf_EthDrvApi */
  EthIf_TxContextEndIdxOfEthCtrlType TxContextEndIdxOfEthCtrl;  /**< the end index of the 1:n relation pointing to EthIf_TxContext */
  EthIf_TxContextStartIdxOfEthCtrlType TxContextStartIdxOfEthCtrl;  /**< the start index of the 1:n relation pointing to EthIf_TxContext */
} EthIf_EthCtrlType;

/**   \brief  type used in EthIf_EthDrvApi */
typedef struct sEthIf_EthDrvApiType
{
  EthIf_EthCtrlInitFctPtrType CtrlInitOfEthDrvApi;  /**< Eth_ControllerInit() of Eth driver */
  EthIf_EthEnableEgressTimeStampFctPtrType EnableEgressTimeStampOfEthDrvApi;  /**< Eth_EnableEgressTimeStamp() of Eth driver. */
  EthIf_EthGetBandwidthLimitFctPtrType GetBandwidthLimitOfEthDrvApi;  /**< Eth_GetBandwidthLimit() of Eth driver. */
  EthIf_EthGetCtrlModeFctPtrType GetCtrlModeOfEthDrvApi;  /**< Eth_GetControllerMode() of Eth driver */
  EthIf_EthGetCurrentTimeFctPtrType GetCurrentTimeOfEthDrvApi;  /**< Eth_GetCurrentTime() of Eth driver. */
  EthIf_EthGetEgressTimeStampFctPtrType GetEgressTimeStampOfEthDrvApi;  /**< Eth_GetEgressTimeStamp() of Eth driver. */
  EthIf_EthGetIngressTimeStampFctPtrType GetIngressTimeStampOfEthDrvApi;  /**< Eth_GetIngressTimeStamp() of Eth driver. */
  EthIf_EthGetPhysAddrFctPtrType GetPhysAddrOfEthDrvApi;  /**< Eth_GetPhysAddr() of Eth driver */
  EthIf_EthGetRxHeaderPtrFctPtrType GetRxHeaderPtrOfEthDrvApi;  /**< Eth_GetRxHeaderPtr() of Eth driver. */
  EthIf_EthGetRxStatsFctPtrType GetRxStatsOfEthDrvApi;  /**< Eth_GetRxStats() of Eth driver */
  EthIf_EthGetTxHeaderPtrFctPtrType GetTxHeaderPtrOfEthDrvApi;  /**< Eth_GetTxHeaderPtr() of Eth driver. */
  EthIf_EthGetTxStatsFctPtrType GetTxStatsOfEthDrvApi;  /**< Eth_GetTxStats() of Eth driver */
  EthIf_EthProvideExtTxBufferFctPtrType ProvideExtTxBufferOfEthDrvApi;  /**< Eth_ProvideExtTxBuffer() of Eth driver. */
  EthIf_EthProvideTxBufferFctPtrType ProvideTxBufferOfEthDrvApi;  /**< Eth_ProvideTxBuffer() of Eth driver */
  EthIf_EthReceiveFctPtrType ReceiveOfEthDrvApi;  /**< Eth_Receive() of Eth driver */
  EthIf_EthReleaseRxBufferFctPtrType ReleaseRxBufferOfEthDrvApi;  /**< Eth_ReleaseRxBuffer() of Eth driver. */
  EthIf_EthSetBandwidthLimitFctPtrType SetBandwidthLimitOfEthDrvApi;  /**< Eth_SetBandwidthLimit() of Eth driver. */
  EthIf_EthSetCtrlModeFctPtrType SetCtrlModeOfEthDrvApi;  /**< Eth_SetControllerMode() of Eth driver */
  EthIf_EthSetPhysAddrFctPtrType SetPhysAddrOfEthDrvApi;  /**< Eth_SetPhysAddr() of Eth driver */
  EthIf_EthTransmitFctPtrType TransmitOfEthDrvApi;  /**< Eth_Transmit() of Eth driver */
  EthIf_EthTxConfFctPtrType TxConfOfEthDrvApi;  /**< Eth_TxConfirmation() of Eth driver */
  EthIf_EthUpdatePhysAddrFilterFctPtrType UpdatePhysAddrFilterOfEthDrvApi;  /**< Eth_UpdatePhysAddrFilter() of Eth driver */
  EthIf_EthVTransmitFctPtrType VTransmitOfEthDrvApi;  /**< Eth_VTransmit() of Eth driver */
} EthIf_EthDrvApiType;

/**   \brief  type used in EthIf_EthIfCtrl */
typedef struct sEthIf_EthIfCtrlType
{
  EthIf_SnvOfEthIfCtrlType SnvOfEthIfCtrl;  /**< SNV of the EthIf Controller */
  EthIf_TypeOfEthIfCtrlType TypeOfEthIfCtrl;  /**< Type of the EthIf Controller */
  EthIf_MtuOfEthIfCtrlType MtuOfEthIfCtrl;  /**< Maximum transfer unit of the EthIf Controller */
  EthIf_EthCtrlIdxOfEthIfCtrlType EthCtrlIdxOfEthIfCtrl;  /**< the index of the 1:1 relation pointing to EthIf_EthCtrl */
  EthIf_EthSwtDrvApiIdxOfEthIfCtrlType EthSwtDrvApiIdxOfEthIfCtrl;  /**< the index of the 0:1 relation pointing to EthIf_EthSwtDrvApi */
  EthIf_GatewayDestEthIfCtrlIdxIdxOfEthIfCtrlType GatewayDestEthIfCtrlIdxIdxOfEthIfCtrl;  /**< the index of the 0:1 relation pointing to EthIf_EthIfCtrl */
  EthIf_LinkAggrThresholdOfEthIfCtrlType LinkAggrThresholdOfEthIfCtrl;  /**< Threshold when a link is issued on EthIf controller level. */
  EthIf_MirrorRxDestIdxIdxOfEthIfCtrlType MirrorRxDestIdxIdxOfEthIfCtrl;  /**< the index of the 0:1 relation pointing to EthIf_MirrorDest */
  EthIf_MirrorTxDestIdxIdxOfEthIfCtrlType MirrorTxDestIdxIdxOfEthIfCtrl;  /**< the index of the 0:1 relation pointing to EthIf_MirrorDest */
  EthIf_PhysLayerInitElemsIdxOfEthIfCtrlType PhysLayerInitElemsIdxOfEthIfCtrl;  /**< the index of the 1:1 relation pointing to EthIf_PhysLayerInitElems */
  EthIf_PhysLayerModeElemsIdxOfEthIfCtrlType PhysLayerModeElemsIdxOfEthIfCtrl;  /**< the index of the 1:1 relation pointing to EthIf_PhysLayerModeElems */
  EthIf_VlanIdOfEthIfCtrlType VlanIdOfEthIfCtrl;  /**< VLAN ID associated with the EthIf Controller */
} EthIf_EthIfCtrlType;

/**   \brief  type used in EthIf_EthIfCtrlRxStats */
typedef struct sEthIf_EthIfCtrlRxStatsType
{
  EthIf_NumRxBytesOfEthIfCtrlRxStatsType NumRxBytesOfEthIfCtrlRxStats;  /**< Number of bytes received on EthIf controller */
  EthIf_NumRxPktsOfEthIfCtrlRxStatsType NumRxPktsOfEthIfCtrlRxStats;  /**< Number of packets received on EthIf controller */
} EthIf_EthIfCtrlRxStatsType;

/**   \brief  type used in EthIf_EthIfCtrlTxStats */
typedef struct sEthIf_EthIfCtrlTxStatsType
{
  EthIf_NumTxBytesOfEthIfCtrlTxStatsType NumTxBytesOfEthIfCtrlTxStats;  /**< Number of bytes transmitted on EthIf controller */
  EthIf_NumTxPktsOfEthIfCtrlTxStatsType NumTxPktsOfEthIfCtrlTxStats;  /**< Number of packets transmitted on EthIf controller */
} EthIf_EthIfCtrlTxStatsType;

/**   \brief  type used in EthIf_EthIfMeasurementData */
typedef struct sEthIf_EthIfMeasurementDataType
{
  EthIf_DropCtrlIdxOfEthIfMeasurementDataType DropCtrlIdxOfEthIfMeasurementData;  /**< Number of dropped datagrams caused by invalid CtrlIdx/VLAN */
  EthIf_UnknownEtherTypeOfEthIfMeasurementDataType UnknownEtherTypeOfEthIfMeasurementData;  /**< Number of dropped datagrams caused by unknown EtherType */
  EthIf_VlanDoubleTaggedOfEthIfMeasurementDataType VlanDoubleTaggedOfEthIfMeasurementData;  /**< Number of received datagrams with detected double VLAN tag */
} EthIf_EthIfMeasurementDataType;

/**   \brief  type used in EthIf_EthSwt */
typedef struct sEthIf_EthSwtType
{
  EthIf_SnvOfEthSwtType SnvOfEthSwt;  /**< SNV of the Eth switch */
  EthIf_EthSwtDrvApiIdxOfEthSwtType EthSwtDrvApiIdxOfEthSwt;  /**< the index of the 1:1 relation pointing to EthIf_EthSwtDrvApi */
} EthIf_EthSwtType;

/**   \brief  type used in EthIf_EthSwtDrv */
typedef struct sEthIf_EthSwtDrvType
{
  EthIf_EthSwtEndIdxOfEthSwtDrvType EthSwtEndIdxOfEthSwtDrv;  /**< the end index of the 1:n relation pointing to EthIf_EthSwt */
  EthIf_EthSwtStartIdxOfEthSwtDrvType EthSwtStartIdxOfEthSwtDrv;  /**< the start index of the 1:n relation pointing to EthIf_EthSwt */
} EthIf_EthSwtDrvType;

/**   \brief  type used in EthIf_EthSwtDrvApi */
typedef struct sEthIf_EthSwtDrvApiType
{
  EthIf_EthSwtEnableVlanFctPtrType EnableVlanOfEthSwtDrvApi;  /**< EthSwt_EnableVlan() of the EthSwt driver */
  EthIf_EthSwtGetArlTableFctPtrType GetArlTableOfEthSwtDrvApi;  /**< EthSwt_GetArlTable() of the EthSwt driver */
  EthIf_EthSwtGetBaudRateFctPtrType GetBaudRateOfEthSwtDrvApi;  /**< EthSwt_GetBaudRate() of the EthSwt driver */
  EthIf_EthSwtGetBufferLevelFctPtrType GetBufferLevelOfEthSwtDrvApi;  /**< EthSwt_GetBufferLevel() of the EthSwt driver */
  EthIf_EthSwtGetDropCountFctPtrType GetDropCountOfEthSwtDrvApi;  /**< EthSwt_GetDropCount() of the EthSwt driver */
  EthIf_EthSwtGetDuplexModeFctPtrType GetDuplexModeOfEthSwtDrvApi;  /**< EthSwt_GetDuplexMode() of the EthSwt driver */
  EthIf_EthSwtGetLinkStateFctPtrType GetLinkStateOfEthSwtDrvApi;  /**< EthSwt_GetLinkState() of the EthSwt driver */
  EthIf_EthSwtGetMacLearningModeFctPtrType GetMacLearningModeOfEthSwtDrvApi;  /**< EthSwt_GetMacLearningMode() of the EthSwt driver */
  EthIf_EthSwtGetPortMacAddrFctPtrType GetPortMacAddrOfEthSwtDrvApi;  /**< EthSwt_GetPortMacAddr() of the EthSwt driver */
  EthIf_EthSwtGetPortSignalQualityFctPtrType GetPortSignalQualityOfEthSwtDrvApi;  /**< EthSwt_GetPortSignalQuality() of the EthSwt driver */
  EthIf_EthSwtGetRxMgmtObjectFctPtrType GetRxMgmtObjectOfEthSwtDrvApi;  /**< EthSwt_GetRxMgmtObject() of the EthSwt driver */
  EthIf_EthSwtGetSwtPortModeFctPtrType GetSwtPortModeOfEthSwtDrvApi;  /**< EthSwt_GetSwitchPortMode() of the EthSwt driver */
  EthIf_EthSwtGetTxMgmtObjectFctPtrType GetTxMgmtObjectOfEthSwtDrvApi;  /**< EthSwt_GetTxMgmtObject() of the EthSwt driver */
  EthIf_EthSwtPortEnableTimeStampFctPtrType PortEnableTimeStampOfEthSwtDrvApi;  /**< EthSwt_PortEnableTimeStamp() of the EthSwt driver */
  EthIf_EthSwtResetConfigFctPtrType ResetConfigOfEthSwtDrvApi;  /**< EthSwt_ResetConfig() of the EthSwt driver */
  EthIf_EthSwtSetCorrectionTimeFctPtrType SetCorrectionTimeOfEthSwtDrvApi;  /**< EthSwt_SetCorrectionTime() of the EthSwt driver */
  EthIf_EthSwtSetMacLearningModeFctPtrType SetMacLearningModeOfEthSwtDrvApi;  /**< EthSwt_SetMacLearningMode() of the EthSwt driver */
  EthIf_EthSwtSetSwtMgmtInfoFctPtrType SetSwtMgmtInfoOfEthSwtDrvApi;  /**< EthSwt_SetSwtMgmtInfo() of the EthSwt driver */
  EthIf_EthSwtSetSwtPortModeFctPtrType SetSwtPortModeOfEthSwtDrvApi;  /**< EthSwt_SetSwitchPortMode() of the EthSwt driver */
  EthIf_EthSwtStartQbvScheduleFctPtrType StartQbvScheduleOfEthSwtDrvApi;  /**< EthSwt_StartQbvSchedule() of the EthSwt driver */
  EthIf_EthSwtStartSwtPortAutoNegFctPtrType StartSwtPortAutoNegOfEthSwtDrvApi;  /**< EthSwt_StartSwitchPortAutoNegotiation() of the EthSwt driver */
  EthIf_EthSwtStopQbvScheduleFctPtrType StopQbvScheduleOfEthSwtDrvApi;  /**< EthSwt_StopQbvSchedule() of the EthSwt driver */
  EthIf_EthSwtStoreConfigFctPtrType StoreConfigOfEthSwtDrvApi;  /**< EthSwt_StoreConfig() of the EthSwt driver */
  EthIf_EthSwtSwtInitFctPtrType SwtInitOfEthSwtDrvApi;  /**< EthSwt_SwitchInit() of the EthSwt driver */
  EthIf_EthSwtUpdateMCastPortAssignmentFctPtrType UpdateMCastPortAssignmentOfEthSwtDrvApi;  /**< EthSwt_UpdateMCastPortAssignment() of the EthSwt driver */
} EthIf_EthSwtDrvApiType;

/**   \brief  type used in EthIf_EthSwtPort */
typedef struct sEthIf_EthSwtPortType
{
  EthIf_SnvOfEthSwtPortType SnvOfEthSwtPort;  /**< SNV of the EthSwt port */
  EthIf_EthSwtIdxOfEthSwtPortType EthSwtIdxOfEthSwtPort;  /**< the index of the 1:1 relation pointing to EthIf_EthSwt */
  EthIf_PortGroupIndEndIdxOfEthSwtPortType PortGroupIndEndIdxOfEthSwtPort;  /**< the end index of the 1:n relation pointing to EthIf_PortGroupInd */
  EthIf_PortGroupIndStartIdxOfEthSwtPortType PortGroupIndStartIdxOfEthSwtPort;  /**< the start index of the 1:n relation pointing to EthIf_PortGroupInd */
} EthIf_EthSwtPortType;

/**   \brief  type used in EthIf_EthTrcv */
typedef struct sEthIf_EthTrcvType
{
  EthIf_SnvOfEthTrcvType SnvOfEthTrcv;  /**< SNV of the EthTrcv */
  EthIf_EthIfCtrlOfEthTrcvIndEndIdxOfEthTrcvType EthIfCtrlOfEthTrcvIndEndIdxOfEthTrcv;  /**< the end index of the 0:n relation pointing to EthIf_EthIfCtrlOfEthTrcvInd */
  EthIf_EthIfCtrlOfEthTrcvIndStartIdxOfEthTrcvType EthIfCtrlOfEthTrcvIndStartIdxOfEthTrcv;  /**< the start index of the 0:n relation pointing to EthIf_EthIfCtrlOfEthTrcvInd */
  EthIf_EthTrcvDrvApiIdxOfEthTrcvType EthTrcvDrvApiIdxOfEthTrcv;  /**< the index of the 1:1 relation pointing to EthIf_EthTrcvDrvApi */
} EthIf_EthTrcvType;

/**   \brief  type used in EthIf_EthTrcvDrvApi */
typedef struct sEthIf_EthTrcvDrvApiType
{
  EthIf_EthTrcvCheckWakeupFctPtrType CheckWakeupOfEthTrcvDrvApi;  /**< EthTrcv_CheckWakeupe() of the EthTrcv driver */
  EthIf_EthTrcvGetBaudRateFctPtrType GetBaudRateOfEthTrcvDrvApi;  /**< EthTrcv_GetBaudRate() of the EthTrcv driver */
  EthIf_EthTrcvGetCableDiagnosticsResultFctPtrType GetCableDiagnosticsResultOfEthTrcvDrvApi;  /**< EthTrcv_GetCableDiagnosticsResult() of the EthTrcv driver */
  EthIf_EthTrcvGetDuplexModeFctPtrType GetDuplexModeOfEthTrcvDrvApi;  /**< EthTrcv_GetDuplexMode() of the EthTrcv driver */
  EthIf_EthTrcvGetLinkStateFctPtrType GetLinkStateOfEthTrcvDrvApi;  /**< EthTrcv_GetLinkState() of the EthTrcv driver */
  EthIf_EthTrcvGetPhySignalQualityFctPtrType GetPhySignalQualityOfEthTrcvDrvApi;  /**< EthTrcv_GetPhySignalQuality() of the EthTrcv driver */
  EthIf_EthTrcvGetTrcvModeFctPtrType GetTrcvModeOfEthTrcvDrvApi;  /**< EthTrcv_GetTransceiverMode() of the EthTrcv driver */
  EthIf_EthTrcvGetTrcvWakeupModeFctPtrType GetTrcvWakeupModeOfEthTrcvDrvApi;  /**< EthTrcv_GetTransceiverWakeupMode() of the EthTrcv driver */
  EthIf_EthTrcvSetPhyTestModeFctPtrType SetPhyTestModeOfEthTrcvDrvApi;  /**< EthTrcv_SetPhyTestMode() of the EthTrcv driver */
  EthIf_EthTrcvSetPhyTxModeFctPtrType SetPhyTxModeOfEthTrcvDrvApi;  /**< EthTrcv_SetPhyTxMode() of the EthTrcv driver */
  EthIf_EthTrcvSetTrcvModeFctPtrType SetTrcvModeOfEthTrcvDrvApi;  /**< EthTrcv_SetTransceiverMode() of the EthTrcv driver */
  EthIf_EthTrcvSetTrcvWakeupModeFctPtrType SetTrcvWakeupModeOfEthTrcvDrvApi;  /**< EthTrcv_SetTransceiverWakeupMode() of the EthTrcv driver */
  EthIf_EthTrcvStartAutoNegFctPtrType StartAutoNegOfEthTrcvDrvApi;  /**< EthTrcv_StartAutoNegotiation() of the EthTrcv driver */
  EthIf_EthTrcvTrcvInitFctPtrType TrcvInitOfEthTrcvDrvApi;  /**< EthTrcv_TransceiverInit() of the EthTrcv driver */
} EthIf_EthTrcvDrvApiType;

/**   \brief  type used in EthIf_ExplicitBufReleaseFilter */
typedef struct sEthIf_ExplicitBufReleaseFilterType
{
  EthIf_EthIfCtrlIdxOfExplicitBufReleaseFilterType EthIfCtrlIdxOfExplicitBufReleaseFilter;  /**< the index of the 1:1 relation pointing to EthIf_EthIfCtrl */
  EthIf_UserIdxOfExplicitBufReleaseFilterType UserIdxOfExplicitBufReleaseFilter;  /**< the index of the 0:1 relation pointing to EthIf_User */
} EthIf_ExplicitBufReleaseFilterType;

/**   \brief  type used in EthIf_GatewaySrcMacBlackList */
typedef struct sEthIf_GatewaySrcMacBlackListType
{
  Eth_PhysAddrType MacAddrOfGatewaySrcMacBlackList;  /**< Source MAC address */
} EthIf_GatewaySrcMacBlackListType;

/**   \brief  type used in EthIf_MirrorDest */
typedef struct sEthIf_MirrorDestType
{
  EthIf_KeepSrcMacEnabledOfMirrorDestType KeepSrcMacEnabledOfMirrorDest;  /**< Shall source MAC address be forwarded unchanged */
  EthIf_EthCtrlIdxOfMirrorDestType EthCtrlIdxOfMirrorDest;  /**< the index of the 1:1 relation pointing to EthIf_EthCtrl */
} EthIf_MirrorDestType;

/**   \brief  type used in EthIf_MirrorTxInfo */
typedef struct sEthIf_MirrorTxInfoType
{
  EthIf_DestEthTxBufferIdxOfMirrorTxInfoType DestEthTxBufferIdxOfMirrorTxInfo;  /**< Tx buffer index occupied for mirror frame */
  EthIf_EthIfCtrlIdxOfMirrorTxInfoType EthIfCtrlIdxOfMirrorTxInfo;  /**< EthIf controller related to mirroring */
  EthIf_InfoValidOfMirrorTxInfoType InfoValidOfMirrorTxInfo;  /**< Flag indicating if Tx traffic information is valid */
  EthIf_SrcEthTxBufferIdxOfMirrorTxInfoType SrcEthTxBufferIdxOfMirrorTxInfo;  /**< Tx buffer index used for transmission of regular frame */
  EthIf_UsedOfMirrorTxInfoType UsedOfMirrorTxInfo;  /**< Flag indicating if Tx traffic information is alread in use */
  EthIf_FrameBufferPtrType DestPayloadPtrOfMirrorTxInfo;  /**< Pointer to the payload section (after EtherType) of mirror frame */
  EthIf_FrameBufferPtrType SrcPayloadPtrOfMirrorTxInfo;  /**< Pointer to the payload section (after EtherType) of frame to be mirrored */
} EthIf_MirrorTxInfoType;

/**   \brief  type used in EthIf_PhysLayerInitElems */
typedef struct sEthIf_PhysLayerInitElemsType
{
  EthIf_EthSwtIndEndIdxOfPhysLayerInitElemsType EthSwtIndEndIdxOfPhysLayerInitElems;  /**< the end index of the 0:n relation pointing to EthIf_EthSwtInd */
  EthIf_EthSwtIndStartIdxOfPhysLayerInitElemsType EthSwtIndStartIdxOfPhysLayerInitElems;  /**< the start index of the 0:n relation pointing to EthIf_EthSwtInd */
  EthIf_EthTrcvIdxOfPhysLayerInitElemsType EthTrcvIdxOfPhysLayerInitElems;  /**< the index of the 0:1 relation pointing to EthIf_EthTrcv */
} EthIf_PhysLayerInitElemsType;

/**   \brief  type used in EthIf_PhysLayerModeElems */
typedef struct sEthIf_PhysLayerModeElemsType
{
  EthIf_EthTrcvIdxOfPhysLayerModeElemsType EthTrcvIdxOfPhysLayerModeElems;  /**< the index of the 0:1 relation pointing to EthIf_EthTrcv */
  EthIf_PortGroupIdxOfPhysLayerModeElemsType PortGroupIdxOfPhysLayerModeElems;  /**< the index of the 0:1 relation pointing to EthIf_PortGroup */
} EthIf_PhysLayerModeElemsType;

/**   \brief  type used in EthIf_PortGroup */
typedef struct sEthIf_PortGroupType
{
  EthIf_SnvOfPortGroupType SnvOfPortGroup;  /**< SNV of the EthIf port group */
  EthIf_SemanticOfPortGroupType SemanticOfPortGroup;  /**< Semantic of the EthIf port group */
  EthIf_EthIfCtrlOfPortGroupIndEndIdxOfPortGroupType EthIfCtrlOfPortGroupIndEndIdxOfPortGroup;  /**< the end index of the 0:n relation pointing to EthIf_EthIfCtrlOfPortGroupInd */
  EthIf_EthIfCtrlOfPortGroupIndStartIdxOfPortGroupType EthIfCtrlOfPortGroupIndStartIdxOfPortGroup;  /**< the start index of the 0:n relation pointing to EthIf_EthIfCtrlOfPortGroupInd */
  EthIf_EthSwtPortIndEndIdxOfPortGroupType EthSwtPortIndEndIdxOfPortGroup;  /**< the end index of the 1:n relation pointing to EthIf_EthSwtPortInd */
  EthIf_EthSwtPortIndStartIdxOfPortGroupType EthSwtPortIndStartIdxOfPortGroup;  /**< the start index of the 1:n relation pointing to EthIf_EthSwtPortInd */
  EthIf_LinkAggrThresholdOfPortGroupType LinkAggrThresholdOfPortGroup;  /**< Link aggregation threshold that must be reached by grouped ports to issue a link on the Port group */
} EthIf_PortGroupType;

/**   \brief  type used in EthIf_SrcMacAddrBuffer */
typedef struct sEthIf_SrcMacAddrBufferType
{
  EthIf_ValidOfSrcMacAddrBufferType ValidOfSrcMacAddrBuffer;  /**< Flag defining if buffer holds a vaild MAC address */
  Eth_PhysAddrType SrcMacOfSrcMacAddrBuffer;  /**< MAC address */
} EthIf_SrcMacAddrBufferType;

/**   \brief  type used in EthIf_TxContext */
typedef struct sEthIf_TxContextType
{
  EthIf_PayloadLenOfTxContextType PayloadLenOfTxContext;  /**< Length of the frames payload */
  EthIf_EthIfCtrlIdxOfTxContextType EthIfCtrlIdxOfTxContext;  /**< Index of the EthIf controller the frame shall be send on */
  EthIf_TxPendingOfTxContextType TxPendingOfTxContext;  /**< Flag indicating if transmission is pending */
  EthIf_UserIdxOfTxContextType UserIdxOfTxContext;  /**< Index of the EthIf user the frame is owned by */
  EthIf_ValidOfTxContextType ValidOfTxContext;  /**< Flag indicating if the context information is valid (buffer is in use) */
  EthIf_FrameHdrType FrameHdrOfTxContext;  /**< Ethernet frame header information */
  EthIf_FrameBufferPtrType PayloadPtrOfTxContext;  /**< Pointer to the frames payload */
} EthIf_TxContextType;

/**   \brief  type used in EthIf_User */
typedef struct sEthIf_UserType
{
  EthIf_EtherTypeOfUserType EtherTypeOfUser;  /**< EtherType of the user */
  EthIf_RxIndicationsIndEndIdxOfUserType RxIndicationsIndEndIdxOfUser;  /**< the end index of the 0:n relation pointing to EthIf_RxIndicationsInd */
  EthIf_RxIndicationsIndStartIdxOfUserType RxIndicationsIndStartIdxOfUser;  /**< the start index of the 0:n relation pointing to EthIf_RxIndicationsInd */
  EthIf_TxConfirmationsIndEndIdxOfUserType TxConfirmationsIndEndIdxOfUser;  /**< the end index of the 0:n relation pointing to EthIf_TxConfirmationsInd */
  EthIf_TxConfirmationsIndStartIdxOfUserType TxConfirmationsIndStartIdxOfUser;  /**< the start index of the 0:n relation pointing to EthIf_TxConfirmationsInd */
} EthIf_UserType;

/**   \brief  type used in EthIf_WakeupMap */
typedef struct sEthIf_WakeupMapType
{
  EthIf_EthTrcvIdxOfWakeupMapType EthTrcvIdxOfWakeupMap;  /**< the index of the 1:1 relation pointing to EthIf_EthTrcv */
  EcuM_WakeupSourceType WakeupSourceOfWakeupMap;  /**< EcuM wakeup source related to the EthTrcv */
} EthIf_WakeupMapType;

/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCSymbolicStructTypes  EthIf Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to EthIf_TxContext */
typedef struct EthIf_TxContextStructSTag
{
  EthIf_TxContextType EthCtrlConfig[4];
} EthIf_TxContextStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCUnionIndexAndSymbolTypes  EthIf Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access EthIf_TxContext in an index and symbol based style. */
typedef union EthIf_TxContextUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthIf_TxContextType raw[4];
  EthIf_TxContextStructSType str;
} EthIf_TxContextUType;

/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCRootPointerTypes  EthIf Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to EthIf_EthCtrl */
typedef P2CONST(EthIf_EthCtrlType, TYPEDEF, ETHIF_CONST) EthIf_EthCtrlPtrType;

/**   \brief  type used to point to EthIf_EthCtrlInitCnt */
typedef P2VAR(EthIf_EthCtrlInitCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthCtrlInitCntPtrType;

/**   \brief  type used to point to EthIf_EthCtrlModeCnt */
typedef P2VAR(EthIf_EthCtrlModeCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthCtrlModeCntPtrType;

/**   \brief  type used to point to EthIf_EthCtrlRxFrameCnt */
typedef P2VAR(EthIf_EthCtrlRxFrameCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthCtrlRxFrameCntPtrType;

/**   \brief  type used to point to EthIf_EthDrvApi */
typedef P2CONST(EthIf_EthDrvApiType, TYPEDEF, ETHIF_CONST) EthIf_EthDrvApiPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrl */
typedef P2CONST(EthIf_EthIfCtrlType, TYPEDEF, ETHIF_CONST) EthIf_EthIfCtrlPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlInitState */
typedef P2VAR(EthIf_EthIfCtrlInitStateType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlInitStatePtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlLinkCount */
typedef P2VAR(EthIf_EthIfCtrlLinkCountType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlLinkCountPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlLinkState */
typedef P2VAR(EthIf_EthIfCtrlLinkStateType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlLinkStatePtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlMode */
typedef P2VAR(Eth_ModeType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlModePtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlOfEthTrcvInd */
typedef P2CONST(EthIf_EthIfCtrlOfEthTrcvIndType, TYPEDEF, ETHIF_CONST) EthIf_EthIfCtrlOfEthTrcvIndPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlOfPortGroupInd */
typedef P2CONST(EthIf_EthIfCtrlOfPortGroupIndType, TYPEDEF, ETHIF_CONST) EthIf_EthIfCtrlOfPortGroupIndPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlRxStats */
typedef P2VAR(EthIf_EthIfCtrlRxStatsType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlRxStatsPtrType;

/**   \brief  type used to point to EthIf_NumRxBytesOfEthIfCtrlRxStats */
typedef P2VAR(EthIf_NumRxBytesOfEthIfCtrlRxStatsType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_NumRxBytesOfEthIfCtrlRxStatsPtrType;

/**   \brief  type used to point to EthIf_NumRxPktsOfEthIfCtrlRxStats */
typedef P2VAR(EthIf_NumRxPktsOfEthIfCtrlRxStatsType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_NumRxPktsOfEthIfCtrlRxStatsPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlTxStats */
typedef P2VAR(EthIf_EthIfCtrlTxStatsType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlTxStatsPtrType;

/**   \brief  type used to point to EthIf_NumTxBytesOfEthIfCtrlTxStats */
typedef P2VAR(EthIf_NumTxBytesOfEthIfCtrlTxStatsType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_NumTxBytesOfEthIfCtrlTxStatsPtrType;

/**   \brief  type used to point to EthIf_NumTxPktsOfEthIfCtrlTxStats */
typedef P2VAR(EthIf_NumTxPktsOfEthIfCtrlTxStatsType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_NumTxPktsOfEthIfCtrlTxStatsPtrType;

/**   \brief  type used to point to EthIf_EthIfMeasurementData */
typedef P2VAR(EthIf_EthIfMeasurementDataType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfMeasurementDataPtrType;

/**   \brief  type used to point to EthIf_DropCtrlIdxOfEthIfMeasurementData */
typedef P2VAR(EthIf_DropCtrlIdxOfEthIfMeasurementDataType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_DropCtrlIdxOfEthIfMeasurementDataPtrType;

/**   \brief  type used to point to EthIf_UnknownEtherTypeOfEthIfMeasurementData */
typedef P2VAR(EthIf_UnknownEtherTypeOfEthIfMeasurementDataType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_UnknownEtherTypeOfEthIfMeasurementDataPtrType;

/**   \brief  type used to point to EthIf_VlanDoubleTaggedOfEthIfMeasurementData */
typedef P2VAR(EthIf_VlanDoubleTaggedOfEthIfMeasurementDataType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_VlanDoubleTaggedOfEthIfMeasurementDataPtrType;

/**   \brief  type used to point to EthIf_EthSwt */
typedef P2CONST(EthIf_EthSwtType, TYPEDEF, ETHIF_CONST) EthIf_EthSwtPtrType;

/**   \brief  type used to point to EthIf_EthSwtDrv */
typedef P2CONST(EthIf_EthSwtDrvType, TYPEDEF, ETHIF_CONST) EthIf_EthSwtDrvPtrType;

/**   \brief  type used to point to EthIf_EthSwtDrvApi */
typedef P2CONST(EthIf_EthSwtDrvApiType, TYPEDEF, ETHIF_CONST) EthIf_EthSwtDrvApiPtrType;

/**   \brief  type used to point to EthIf_EthSwtInd */
typedef P2CONST(EthIf_EthSwtIndType, TYPEDEF, ETHIF_CONST) EthIf_EthSwtIndPtrType;

/**   \brief  type used to point to EthIf_EthSwtInitCnt */
typedef P2VAR(EthIf_EthSwtInitCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthSwtInitCntPtrType;

/**   \brief  type used to point to EthIf_EthSwtPort */
typedef P2CONST(EthIf_EthSwtPortType, TYPEDEF, ETHIF_CONST) EthIf_EthSwtPortPtrType;

/**   \brief  type used to point to EthIf_EthSwtPortInd */
typedef P2CONST(EthIf_EthSwtPortIndType, TYPEDEF, ETHIF_CONST) EthIf_EthSwtPortIndPtrType;

/**   \brief  type used to point to EthIf_EthSwtPortModeCnt */
typedef P2VAR(EthIf_EthSwtPortModeCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthSwtPortModeCntPtrType;

/**   \brief  type used to point to EthIf_EthTrcv */
typedef P2CONST(EthIf_EthTrcvType, TYPEDEF, ETHIF_CONST) EthIf_EthTrcvPtrType;

/**   \brief  type used to point to EthIf_EthTrcvDrvApi */
typedef P2CONST(EthIf_EthTrcvDrvApiType, TYPEDEF, ETHIF_CONST) EthIf_EthTrcvDrvApiPtrType;

/**   \brief  type used to point to EthIf_EthTrcvInitCnt */
typedef P2VAR(EthIf_EthTrcvInitCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthTrcvInitCntPtrType;

/**   \brief  type used to point to EthIf_EthTrcvModeCnt */
typedef P2VAR(EthIf_EthTrcvModeCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthTrcvModeCntPtrType;

/**   \brief  type used to point to EthIf_ExplicitBufReleaseFilter */
typedef P2CONST(EthIf_ExplicitBufReleaseFilterType, TYPEDEF, ETHIF_CONST) EthIf_ExplicitBufReleaseFilterPtrType;

/**   \brief  type used to point to EthIf_GatewaySrcMacBlackList */
typedef P2CONST(EthIf_GatewaySrcMacBlackListType, TYPEDEF, ETHIF_CONST) EthIf_GatewaySrcMacBlackListPtrType;

/**   \brief  type used to point to EthIf_InitLocked */
typedef P2VAR(EthIf_InitLockedType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_InitLockedPtrType;

/**   \brief  type used to point to EthIf_LinkStateChgIndications */
typedef P2CONST(EthIf_LinkStateChgIndFctPtrType, TYPEDEF, ETHIF_CONST) EthIf_LinkStateChgIndicationsPtrType;

/**   \brief  type used to point to EthIf_MainFuncStateDecoupleFreqCnt */
typedef P2VAR(EthIf_MainFuncStateDecoupleFreqCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_MainFuncStateDecoupleFreqCntPtrType;

/**   \brief  type used to point to EthIf_MirrorDest */
typedef P2CONST(EthIf_MirrorDestType, TYPEDEF, ETHIF_CONST) EthIf_MirrorDestPtrType;

/**   \brief  type used to point to EthIf_MirrorTxInfo */
typedef P2VAR(EthIf_MirrorTxInfoType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_MirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_DestEthTxBufferIdxOfMirrorTxInfo */
typedef P2VAR(EthIf_DestEthTxBufferIdxOfMirrorTxInfoType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_DestEthTxBufferIdxOfMirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_DestPayloadPtrOfMirrorTxInfo */
typedef P2VAR(EthIf_FrameBufferPtrType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_DestPayloadPtrOfMirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlIdxOfMirrorTxInfo */
typedef P2VAR(EthIf_EthIfCtrlIdxOfMirrorTxInfoType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlIdxOfMirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_InfoValidOfMirrorTxInfo */
typedef P2VAR(EthIf_InfoValidOfMirrorTxInfoType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_InfoValidOfMirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_SrcEthTxBufferIdxOfMirrorTxInfo */
typedef P2VAR(EthIf_SrcEthTxBufferIdxOfMirrorTxInfoType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_SrcEthTxBufferIdxOfMirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_SrcPayloadPtrOfMirrorTxInfo */
typedef P2VAR(EthIf_FrameBufferPtrType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_SrcPayloadPtrOfMirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_UsedOfMirrorTxInfo */
typedef P2VAR(EthIf_UsedOfMirrorTxInfoType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_UsedOfMirrorTxInfoPtrType;

/**   \brief  type used to point to EthIf_ModeChangeLocked */
typedef P2VAR(EthIf_ModeChangeLockedType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_ModeChangeLockedPtrType;

/**   \brief  type used to point to EthIf_PhysLayerInitElems */
typedef P2CONST(EthIf_PhysLayerInitElemsType, TYPEDEF, ETHIF_CONST) EthIf_PhysLayerInitElemsPtrType;

/**   \brief  type used to point to EthIf_PhysLayerModeElems */
typedef P2CONST(EthIf_PhysLayerModeElemsType, TYPEDEF, ETHIF_CONST) EthIf_PhysLayerModeElemsPtrType;

/**   \brief  type used to point to EthIf_PortGroup */
typedef P2CONST(EthIf_PortGroupType, TYPEDEF, ETHIF_CONST) EthIf_PortGroupPtrType;

/**   \brief  type used to point to EthIf_PortGroupInd */
typedef P2CONST(EthIf_PortGroupIndType, TYPEDEF, ETHIF_CONST) EthIf_PortGroupIndPtrType;

/**   \brief  type used to point to EthIf_PortGroupLinkCount */
typedef P2VAR(EthIf_PortGroupLinkCountType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_PortGroupLinkCountPtrType;

/**   \brief  type used to point to EthIf_PortGroupLinkState */
typedef P2VAR(EthIf_PortGroupLinkStateType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_PortGroupLinkStatePtrType;

/**   \brief  type used to point to EthIf_PortGroupMode */
typedef P2VAR(Eth_ModeType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_PortGroupModePtrType;

/**   \brief  type used to point to EthIf_PortSignalQualityResult */
typedef P2VAR(EthIf_SignalQualityResultType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_PortSignalQualityResultPtrType;

/**   \brief  type used to point to EthIf_RxIndications */
typedef P2CONST(EthIf_RxIndFctPtrType, TYPEDEF, ETHIF_CONST) EthIf_RxIndicationsPtrType;

/**   \brief  type used to point to EthIf_RxIndicationsInd */
typedef P2CONST(EthIf_RxIndicationsIndType, TYPEDEF, ETHIF_CONST) EthIf_RxIndicationsIndPtrType;

/**   \brief  type used to point to EthIf_SignalQualityDecoupleFreqCnt */
typedef P2VAR(EthIf_SignalQualityDecoupleFreqCntType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_SignalQualityDecoupleFreqCntPtrType;

/**   \brief  type used to point to EthIf_SignalQualityResult */
typedef P2VAR(EthIf_SignalQualityResultType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_SignalQualityResultPtrType;

/**   \brief  type used to point to EthIf_SrcMacAddrBuffer */
typedef P2VAR(EthIf_SrcMacAddrBufferType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_SrcMacAddrBufferPtrType;

/**   \brief  type used to point to EthIf_SrcMacOfSrcMacAddrBuffer */
typedef P2VAR(Eth_PhysAddrType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_SrcMacOfSrcMacAddrBufferPtrType;

/**   \brief  type used to point to EthIf_ValidOfSrcMacAddrBuffer */
typedef P2VAR(EthIf_ValidOfSrcMacAddrBufferType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_ValidOfSrcMacAddrBufferPtrType;

/**   \brief  type used to point to EthIf_TxConfirmations */
typedef P2CONST(EthIf_TxConfFctPtrType, TYPEDEF, ETHIF_CONST) EthIf_TxConfirmationsPtrType;

/**   \brief  type used to point to EthIf_TxConfirmationsInd */
typedef P2CONST(EthIf_TxConfirmationsIndType, TYPEDEF, ETHIF_CONST) EthIf_TxConfirmationsIndPtrType;

/**   \brief  type used to point to EthIf_TxContext */
typedef P2VAR(EthIf_TxContextType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_TxContextPtrType;

/**   \brief  type used to point to EthIf_EthIfCtrlIdxOfTxContext */
typedef P2VAR(EthIf_EthIfCtrlIdxOfTxContextType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlIdxOfTxContextPtrType;

/**   \brief  type used to point to EthIf_FrameHdrOfTxContext */
typedef P2VAR(EthIf_FrameHdrType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_FrameHdrOfTxContextPtrType;

/**   \brief  type used to point to EthIf_PayloadLenOfTxContext */
typedef P2VAR(EthIf_PayloadLenOfTxContextType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_PayloadLenOfTxContextPtrType;

/**   \brief  type used to point to EthIf_PayloadPtrOfTxContext */
typedef P2VAR(EthIf_FrameBufferPtrType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_PayloadPtrOfTxContextPtrType;

/**   \brief  type used to point to EthIf_TxPendingOfTxContext */
typedef P2VAR(EthIf_TxPendingOfTxContextType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_TxPendingOfTxContextPtrType;

/**   \brief  type used to point to EthIf_UserIdxOfTxContext */
typedef P2VAR(EthIf_UserIdxOfTxContextType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_UserIdxOfTxContextPtrType;

/**   \brief  type used to point to EthIf_ValidOfTxContext */
typedef P2VAR(EthIf_ValidOfTxContextType, TYPEDEF, ETHIF_VAR_NOINIT) EthIf_ValidOfTxContextPtrType;

/**   \brief  type used to point to EthIf_User */
typedef P2CONST(EthIf_UserType, TYPEDEF, ETHIF_CONST) EthIf_UserPtrType;

/**   \brief  type used to point to EthIf_WakeupMap */
typedef P2CONST(EthIf_WakeupMapType, TYPEDEF, ETHIF_CONST) EthIf_WakeupMapPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  EthIfPCRootValueTypes  EthIf Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in EthIf_PCConfig */
typedef struct sEthIf_PCConfigType
{
  EthIf_EthCtrlPtrType EthCtrlOfPCConfig;  /**< the pointer to EthIf_EthCtrl */
  EthIf_EthCtrlInitCntPtrType EthCtrlInitCntOfPCConfig;  /**< the pointer to EthIf_EthCtrlInitCnt */
  EthIf_EthCtrlModeCntPtrType EthCtrlModeCntOfPCConfig;  /**< the pointer to EthIf_EthCtrlModeCnt */
  EthIf_EthCtrlRxFrameCntPtrType EthCtrlRxFrameCntOfPCConfig;  /**< the pointer to EthIf_EthCtrlRxFrameCnt */
  EthIf_EthDrvApiPtrType EthDrvApiOfPCConfig;  /**< the pointer to EthIf_EthDrvApi */
  EthIf_EthIfCtrlPtrType EthIfCtrlOfPCConfig;  /**< the pointer to EthIf_EthIfCtrl */
  EthIf_EthIfCtrlInitStatePtrType EthIfCtrlInitStateOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlInitState */
  EthIf_EthIfCtrlLinkCountPtrType EthIfCtrlLinkCountOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlLinkCount */
  EthIf_EthIfCtrlLinkStatePtrType EthIfCtrlLinkStateOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlLinkState */
  EthIf_EthIfCtrlModePtrType EthIfCtrlModeOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlMode */
  EthIf_EthIfCtrlOfEthTrcvIndPtrType EthIfCtrlOfEthTrcvIndOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlOfEthTrcvInd */
  EthIf_EthIfCtrlOfPortGroupIndPtrType EthIfCtrlOfPortGroupIndOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlOfPortGroupInd */
  EthIf_EthIfCtrlRxStatsPtrType EthIfCtrlRxStatsOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlRxStats */
  EthIf_EthIfCtrlTxStatsPtrType EthIfCtrlTxStatsOfPCConfig;  /**< the pointer to EthIf_EthIfCtrlTxStats */
  EthIf_EthIfMeasurementDataPtrType EthIfMeasurementDataOfPCConfig;  /**< the pointer to EthIf_EthIfMeasurementData */
  EthIf_EthSwtPtrType EthSwtOfPCConfig;  /**< the pointer to EthIf_EthSwt */
  EthIf_EthSwtDrvPtrType EthSwtDrvOfPCConfig;  /**< the pointer to EthIf_EthSwtDrv */
  EthIf_EthSwtDrvApiPtrType EthSwtDrvApiOfPCConfig;  /**< the pointer to EthIf_EthSwtDrvApi */
  EthIf_EthSwtIndPtrType EthSwtIndOfPCConfig;  /**< the pointer to EthIf_EthSwtInd */
  EthIf_EthSwtInitCntPtrType EthSwtInitCntOfPCConfig;  /**< the pointer to EthIf_EthSwtInitCnt */
  EthIf_EthSwtPortPtrType EthSwtPortOfPCConfig;  /**< the pointer to EthIf_EthSwtPort */
  EthIf_EthSwtPortIndPtrType EthSwtPortIndOfPCConfig;  /**< the pointer to EthIf_EthSwtPortInd */
  EthIf_EthSwtPortModeCntPtrType EthSwtPortModeCntOfPCConfig;  /**< the pointer to EthIf_EthSwtPortModeCnt */
  EthIf_EthTrcvPtrType EthTrcvOfPCConfig;  /**< the pointer to EthIf_EthTrcv */
  EthIf_EthTrcvDrvApiPtrType EthTrcvDrvApiOfPCConfig;  /**< the pointer to EthIf_EthTrcvDrvApi */
  EthIf_EthTrcvInitCntPtrType EthTrcvInitCntOfPCConfig;  /**< the pointer to EthIf_EthTrcvInitCnt */
  EthIf_EthTrcvModeCntPtrType EthTrcvModeCntOfPCConfig;  /**< the pointer to EthIf_EthTrcvModeCnt */
  EthIf_ExplicitBufReleaseFilterPtrType ExplicitBufReleaseFilterOfPCConfig;  /**< the pointer to EthIf_ExplicitBufReleaseFilter */
  EthIf_GatewaySrcMacBlackListPtrType GatewaySrcMacBlackListOfPCConfig;  /**< the pointer to EthIf_GatewaySrcMacBlackList */
  EthIf_InitLockedPtrType InitLockedOfPCConfig;  /**< the pointer to EthIf_InitLocked */
  EthIf_LinkStateChgIndicationsPtrType LinkStateChgIndicationsOfPCConfig;  /**< the pointer to EthIf_LinkStateChgIndications */
  EthIf_MainFuncStateDecoupleFreqCntPtrType MainFuncStateDecoupleFreqCntOfPCConfig;  /**< the pointer to EthIf_MainFuncStateDecoupleFreqCnt */
  EthIf_MirrorDestPtrType MirrorDestOfPCConfig;  /**< the pointer to EthIf_MirrorDest */
  EthIf_MirrorTxInfoPtrType MirrorTxInfoOfPCConfig;  /**< the pointer to EthIf_MirrorTxInfo */
  EthIf_ModeChangeLockedPtrType ModeChangeLockedOfPCConfig;  /**< the pointer to EthIf_ModeChangeLocked */
  EthIf_PhysLayerInitElemsPtrType PhysLayerInitElemsOfPCConfig;  /**< the pointer to EthIf_PhysLayerInitElems */
  EthIf_PhysLayerModeElemsPtrType PhysLayerModeElemsOfPCConfig;  /**< the pointer to EthIf_PhysLayerModeElems */
  EthIf_PortGroupPtrType PortGroupOfPCConfig;  /**< the pointer to EthIf_PortGroup */
  EthIf_PortGroupIndPtrType PortGroupIndOfPCConfig;  /**< the pointer to EthIf_PortGroupInd */
  EthIf_PortGroupLinkCountPtrType PortGroupLinkCountOfPCConfig;  /**< the pointer to EthIf_PortGroupLinkCount */
  EthIf_PortGroupLinkStatePtrType PortGroupLinkStateOfPCConfig;  /**< the pointer to EthIf_PortGroupLinkState */
  EthIf_PortGroupModePtrType PortGroupModeOfPCConfig;  /**< the pointer to EthIf_PortGroupMode */
  EthIf_PortSignalQualityResultPtrType PortSignalQualityResultOfPCConfig;  /**< the pointer to EthIf_PortSignalQualityResult */
  EthIf_RxIndicationsPtrType RxIndicationsOfPCConfig;  /**< the pointer to EthIf_RxIndications */
  EthIf_RxIndicationsIndPtrType RxIndicationsIndOfPCConfig;  /**< the pointer to EthIf_RxIndicationsInd */
  EthIf_SignalQualityDecoupleFreqCntPtrType SignalQualityDecoupleFreqCntOfPCConfig;  /**< the pointer to EthIf_SignalQualityDecoupleFreqCnt */
  EthIf_SignalQualityResultPtrType SignalQualityResultOfPCConfig;  /**< the pointer to EthIf_SignalQualityResult */
  EthIf_SrcMacAddrBufferPtrType SrcMacAddrBufferOfPCConfig;  /**< the pointer to EthIf_SrcMacAddrBuffer */
  EthIf_TxConfirmationsPtrType TxConfirmationsOfPCConfig;  /**< the pointer to EthIf_TxConfirmations */
  EthIf_TxConfirmationsIndPtrType TxConfirmationsIndOfPCConfig;  /**< the pointer to EthIf_TxConfirmationsInd */
  EthIf_TxContextPtrType TxContextOfPCConfig;  /**< the pointer to EthIf_TxContext */
  EthIf_UserPtrType UserOfPCConfig;  /**< the pointer to EthIf_User */
  EthIf_WakeupMapPtrType WakeupMapOfPCConfig;  /**< the pointer to EthIf_WakeupMap */
  EthIf_LinkStateChgMainReloadType LinkStateChgMainReloadOfPCConfig;  /**< Amount of calls link state observation isn't triggerd if observation is done within EthIf_MainFunctionTx() instead of using an explicit EthIf_MainFunctionState(). */
  EthIf_MaxFrameRxPerEthCtrlType MaxFrameRxPerEthCtrlOfPCConfig;  /**< Maximum amount of frames that can be received during one call of EthIf_MainFunctionRx() in polling mode on one Ethernet controller */
  EthIf_MaxTxBufPerEthCtrlType MaxTxBufPerEthCtrlOfPCConfig;  /**< Maximum amount of Tx buffers configured for an Ethernet controller */
  EthIf_SignalQualityChgMainReloadType SignalQualityChgMainReloadOfPCConfig;  /**< Amount of calls signal quality observation in EthIf_MainFunctionState(). */
  EthIf_SizeOfEthCtrlType SizeOfEthCtrlOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthCtrl */
  EthIf_SizeOfEthDrvApiType SizeOfEthDrvApiOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthDrvApi */
  EthIf_SizeOfEthIfCtrlType SizeOfEthIfCtrlOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthIfCtrl */
  EthIf_SizeOfEthIfCtrlOfEthTrcvIndType SizeOfEthIfCtrlOfEthTrcvIndOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthIfCtrlOfEthTrcvInd */
  EthIf_SizeOfEthIfCtrlOfPortGroupIndType SizeOfEthIfCtrlOfPortGroupIndOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthIfCtrlOfPortGroupInd */
  EthIf_SizeOfEthIfMeasurementDataType SizeOfEthIfMeasurementDataOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthIfMeasurementData */
  EthIf_SizeOfEthSwtType SizeOfEthSwtOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthSwt */
  EthIf_SizeOfEthSwtDrvType SizeOfEthSwtDrvOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthSwtDrv */
  EthIf_SizeOfEthSwtDrvApiType SizeOfEthSwtDrvApiOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthSwtDrvApi */
  EthIf_SizeOfEthSwtIndType SizeOfEthSwtIndOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthSwtInd */
  EthIf_SizeOfEthSwtPortType SizeOfEthSwtPortOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthSwtPort */
  EthIf_SizeOfEthSwtPortIndType SizeOfEthSwtPortIndOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthSwtPortInd */
  EthIf_SizeOfEthTrcvType SizeOfEthTrcvOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthTrcv */
  EthIf_SizeOfEthTrcvDrvApiType SizeOfEthTrcvDrvApiOfPCConfig;  /**< the number of accomplishable value elements in EthIf_EthTrcvDrvApi */
  EthIf_SizeOfExplicitBufReleaseFilterType SizeOfExplicitBufReleaseFilterOfPCConfig;  /**< the number of accomplishable value elements in EthIf_ExplicitBufReleaseFilter */
  EthIf_SizeOfGatewaySrcMacBlackListType SizeOfGatewaySrcMacBlackListOfPCConfig;  /**< the number of accomplishable value elements in EthIf_GatewaySrcMacBlackList */
  EthIf_SizeOfLinkStateChgIndicationsType SizeOfLinkStateChgIndicationsOfPCConfig;  /**< the number of accomplishable value elements in EthIf_LinkStateChgIndications */
  EthIf_SizeOfMirrorDestType SizeOfMirrorDestOfPCConfig;  /**< the number of accomplishable value elements in EthIf_MirrorDest */
  EthIf_SizeOfMirrorTxInfoType SizeOfMirrorTxInfoOfPCConfig;  /**< the number of accomplishable value elements in EthIf_MirrorTxInfo */
  EthIf_SizeOfPhysLayerInitElemsType SizeOfPhysLayerInitElemsOfPCConfig;  /**< the number of accomplishable value elements in EthIf_PhysLayerInitElems */
  EthIf_SizeOfPhysLayerModeElemsType SizeOfPhysLayerModeElemsOfPCConfig;  /**< the number of accomplishable value elements in EthIf_PhysLayerModeElems */
  EthIf_SizeOfPortGroupType SizeOfPortGroupOfPCConfig;  /**< the number of accomplishable value elements in EthIf_PortGroup */
  EthIf_SizeOfPortGroupIndType SizeOfPortGroupIndOfPCConfig;  /**< the number of accomplishable value elements in EthIf_PortGroupInd */
  EthIf_SizeOfRxIndicationsType SizeOfRxIndicationsOfPCConfig;  /**< the number of accomplishable value elements in EthIf_RxIndications */
  EthIf_SizeOfRxIndicationsIndType SizeOfRxIndicationsIndOfPCConfig;  /**< the number of accomplishable value elements in EthIf_RxIndicationsInd */
  EthIf_SizeOfTxConfirmationsType SizeOfTxConfirmationsOfPCConfig;  /**< the number of accomplishable value elements in EthIf_TxConfirmations */
  EthIf_SizeOfTxConfirmationsIndType SizeOfTxConfirmationsIndOfPCConfig;  /**< the number of accomplishable value elements in EthIf_TxConfirmationsInd */
  EthIf_SizeOfTxContextType SizeOfTxContextOfPCConfig;  /**< the number of accomplishable value elements in EthIf_TxContext */
  EthIf_SizeOfUserType SizeOfUserOfPCConfig;  /**< the number of accomplishable value elements in EthIf_User */
  EthIf_SizeOfWakeupMapType SizeOfWakeupMapOfPCConfig;  /**< the number of accomplishable value elements in EthIf_WakeupMap */
} EthIf_PCConfigType;

typedef EthIf_PCConfigType EthIf_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access EthIf_PCConfig in a symbol based style. */
typedef struct sEthIf_PCConfigsType
{
  EthIf_PCConfigType Config;  /**< [Config] */
} EthIf_PCConfigsType;

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthIf_EthCtrl
**********************************************************************************************************************/
/** 
  \var    EthIf_EthCtrl
  \brief  Eth controllers abstracted by the EthIf
  \details
  Element              Description
  Snv                  SNV of the Eth controller
  EthDrvApiIdx         the index of the 1:1 relation pointing to EthIf_EthDrvApi
  TxContextEndIdx      the end index of the 1:n relation pointing to EthIf_TxContext
  TxContextStartIdx    the start index of the 1:n relation pointing to EthIf_TxContext
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_EthCtrlType, ETHIF_CONST) EthIf_EthCtrl[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthDrvApi
**********************************************************************************************************************/
/** 
  \var    EthIf_EthDrvApi
  \brief  APIs of the Ethernet drivers abstracted by EthIf
  \details
  Element                  Description
  CtrlInit                 Eth_ControllerInit() of Eth driver
  EnableEgressTimeStamp    Eth_EnableEgressTimeStamp() of Eth driver.
  GetBandwidthLimit        Eth_GetBandwidthLimit() of Eth driver.
  GetCtrlMode              Eth_GetControllerMode() of Eth driver
  GetCurrentTime           Eth_GetCurrentTime() of Eth driver.
  GetEgressTimeStamp       Eth_GetEgressTimeStamp() of Eth driver.
  GetIngressTimeStamp      Eth_GetIngressTimeStamp() of Eth driver.
  GetPhysAddr              Eth_GetPhysAddr() of Eth driver
  GetRxHeaderPtr           Eth_GetRxHeaderPtr() of Eth driver.
  GetRxStats               Eth_GetRxStats() of Eth driver
  GetTxHeaderPtr           Eth_GetTxHeaderPtr() of Eth driver.
  GetTxStats               Eth_GetTxStats() of Eth driver
  ProvideExtTxBuffer       Eth_ProvideExtTxBuffer() of Eth driver.
  ProvideTxBuffer          Eth_ProvideTxBuffer() of Eth driver
  Receive                  Eth_Receive() of Eth driver
  ReleaseRxBuffer          Eth_ReleaseRxBuffer() of Eth driver.
  SetBandwidthLimit        Eth_SetBandwidthLimit() of Eth driver.
  SetCtrlMode              Eth_SetControllerMode() of Eth driver
  SetPhysAddr              Eth_SetPhysAddr() of Eth driver
  Transmit                 Eth_Transmit() of Eth driver
  TxConf                   Eth_TxConfirmation() of Eth driver
  UpdatePhysAddrFilter     Eth_UpdatePhysAddrFilter() of Eth driver
  VTransmit                Eth_VTransmit() of Eth driver
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_EthDrvApiType, ETHIF_CONST) EthIf_EthDrvApi[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrl
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrl
  \brief  EthIf controllers
  \details
  Element                       Description
  Snv                           SNV of the EthIf Controller
  Type                          Type of the EthIf Controller
  Mtu                           Maximum transfer unit of the EthIf Controller
  EthCtrlIdx                    the index of the 1:1 relation pointing to EthIf_EthCtrl
  EthSwtDrvApiIdx               the index of the 0:1 relation pointing to EthIf_EthSwtDrvApi
  GatewayDestEthIfCtrlIdxIdx    the index of the 0:1 relation pointing to EthIf_EthIfCtrl
  LinkAggrThreshold             Threshold when a link is issued on EthIf controller level.
  MirrorRxDestIdxIdx            the index of the 0:1 relation pointing to EthIf_MirrorDest
  MirrorTxDestIdxIdx            the index of the 0:1 relation pointing to EthIf_MirrorDest
  PhysLayerInitElemsIdx         the index of the 1:1 relation pointing to EthIf_PhysLayerInitElems
  PhysLayerModeElemsIdx         the index of the 1:1 relation pointing to EthIf_PhysLayerModeElems
  VlanId                        VLAN ID associated with the EthIf Controller
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_EthIfCtrlType, ETHIF_CONST) EthIf_EthIfCtrl[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrlOfEthTrcvInd
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrlOfEthTrcvInd
  \brief  the indexes of the 1:1 sorted relation pointing to EthIf_EthIfCtrl
*/ 
#define ETHIF_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_EthIfCtrlOfEthTrcvIndType, ETHIF_CONST) EthIf_EthIfCtrlOfEthTrcvInd[1];
#define ETHIF_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthTrcv
**********************************************************************************************************************/
/** 
  \var    EthIf_EthTrcv
  \brief  Eth transceivers abstracted by EthIf
  \details
  Element                          Description
  Snv                              SNV of the EthTrcv
  EthIfCtrlOfEthTrcvIndEndIdx      the end index of the 0:n relation pointing to EthIf_EthIfCtrlOfEthTrcvInd
  EthIfCtrlOfEthTrcvIndStartIdx    the start index of the 0:n relation pointing to EthIf_EthIfCtrlOfEthTrcvInd
  EthTrcvDrvApiIdx                 the index of the 1:1 relation pointing to EthIf_EthTrcvDrvApi
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_EthTrcvType, ETHIF_CONST) EthIf_EthTrcv[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthTrcvDrvApi
**********************************************************************************************************************/
/** 
  \var    EthIf_EthTrcvDrvApi
  \brief  APIs of the EthTrcv drivers abstracted by EthIf
  \details
  Element                      Description
  CheckWakeup                  EthTrcv_CheckWakeupe() of the EthTrcv driver
  GetBaudRate                  EthTrcv_GetBaudRate() of the EthTrcv driver
  GetCableDiagnosticsResult    EthTrcv_GetCableDiagnosticsResult() of the EthTrcv driver
  GetDuplexMode                EthTrcv_GetDuplexMode() of the EthTrcv driver
  GetLinkState                 EthTrcv_GetLinkState() of the EthTrcv driver
  GetPhySignalQuality          EthTrcv_GetPhySignalQuality() of the EthTrcv driver
  GetTrcvMode                  EthTrcv_GetTransceiverMode() of the EthTrcv driver
  GetTrcvWakeupMode            EthTrcv_GetTransceiverWakeupMode() of the EthTrcv driver
  SetPhyTestMode               EthTrcv_SetPhyTestMode() of the EthTrcv driver
  SetPhyTxMode                 EthTrcv_SetPhyTxMode() of the EthTrcv driver
  SetTrcvMode                  EthTrcv_SetTransceiverMode() of the EthTrcv driver
  SetTrcvWakeupMode            EthTrcv_SetTransceiverWakeupMode() of the EthTrcv driver
  StartAutoNeg                 EthTrcv_StartAutoNegotiation() of the EthTrcv driver
  TrcvInit                     EthTrcv_TransceiverInit() of the EthTrcv driver
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_EthTrcvDrvApiType, ETHIF_CONST) EthIf_EthTrcvDrvApi[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_LinkStateChgIndications
**********************************************************************************************************************/
/** 
  \var    EthIf_LinkStateChgIndications
  \brief  Link State change indications of the EthIf users.
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_LinkStateChgIndFctPtrType, ETHIF_CONST) EthIf_LinkStateChgIndications[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_PhysLayerInitElems
**********************************************************************************************************************/
/** 
  \var    EthIf_PhysLayerInitElems
  \brief  Hardware that the EthIf controllers trigger initialization for
  \details
  Element              Description
  EthSwtIndEndIdx      the end index of the 0:n relation pointing to EthIf_EthSwtInd
  EthSwtIndStartIdx    the start index of the 0:n relation pointing to EthIf_EthSwtInd
  EthTrcvIdx           the index of the 0:1 relation pointing to EthIf_EthTrcv
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_PhysLayerInitElemsType, ETHIF_CONST) EthIf_PhysLayerInitElems[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_PhysLayerModeElems
**********************************************************************************************************************/
/** 
  \var    EthIf_PhysLayerModeElems
  \brief  Hardware that the EthIf controllers trigger mode changes for
  \details
  Element         Description
  EthTrcvIdx      the index of the 0:1 relation pointing to EthIf_EthTrcv
  PortGroupIdx    the index of the 0:1 relation pointing to EthIf_PortGroup
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_PhysLayerModeElemsType, ETHIF_CONST) EthIf_PhysLayerModeElems[1];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_RxIndications
**********************************************************************************************************************/
/** 
  \var    EthIf_RxIndications
  \brief  Rx indications of the EthIf users.
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_RxIndFctPtrType, ETHIF_CONST) EthIf_RxIndications[3];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_RxIndicationsInd
**********************************************************************************************************************/
/** 
  \var    EthIf_RxIndicationsInd
  \brief  the indexes of the 1:1 sorted relation pointing to EthIf_RxIndications
*/ 
#define ETHIF_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_RxIndicationsIndType, ETHIF_CONST) EthIf_RxIndicationsInd[3];
#define ETHIF_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_TxConfirmations
**********************************************************************************************************************/
/** 
  \var    EthIf_TxConfirmations
  \brief  Tx confirmations of the EthIf users.
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_TxConfFctPtrType, ETHIF_CONST) EthIf_TxConfirmations[2];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_TxConfirmationsInd
**********************************************************************************************************************/
/** 
  \var    EthIf_TxConfirmationsInd
  \brief  the indexes of the 1:1 sorted relation pointing to EthIf_TxConfirmations
*/ 
#define ETHIF_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_TxConfirmationsIndType, ETHIF_CONST) EthIf_TxConfirmationsInd[2];
#define ETHIF_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_User
**********************************************************************************************************************/
/** 
  \var    EthIf_User
  \brief  Users of the EthIf
  \details
  Element                       Description
  EtherType                     EtherType of the user
  RxIndicationsIndEndIdx        the end index of the 0:n relation pointing to EthIf_RxIndicationsInd
  RxIndicationsIndStartIdx      the start index of the 0:n relation pointing to EthIf_RxIndicationsInd
  TxConfirmationsIndEndIdx      the end index of the 0:n relation pointing to EthIf_TxConfirmationsInd
  TxConfirmationsIndStartIdx    the start index of the 0:n relation pointing to EthIf_TxConfirmationsInd
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_UserType, ETHIF_CONST) EthIf_User[3];
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthCtrlInitCnt
**********************************************************************************************************************/
/** 
  \var    EthIf_EthCtrlInitCnt
  \brief  Initialization counts for the Eth controllers abstracted by EthIf
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthCtrlInitCntType, ETHIF_VAR_NOINIT) EthIf_EthCtrlInitCnt[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthCtrlModeCnt
**********************************************************************************************************************/
/** 
  \var    EthIf_EthCtrlModeCnt
  \brief  Mode request counts for the Eth controllers abstracted by EthIf
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthCtrlModeCntType, ETHIF_VAR_NOINIT) EthIf_EthCtrlModeCnt[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthCtrlRxFrameCnt
**********************************************************************************************************************/
/** 
  \var    EthIf_EthCtrlRxFrameCnt
  \brief  Count of frames received on an Eth controller during a reception main-function cycle
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthCtrlRxFrameCntType, ETHIF_VAR_NOINIT) EthIf_EthCtrlRxFrameCnt[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrlInitState
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrlInitState
  \brief  Initialization state of the EthIf controllers
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthIfCtrlInitStateType, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlInitState[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrlLinkCount
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrlLinkCount
  \brief  Count of active links on the related hardware layer of the EthIf controllers
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthIfCtrlLinkCountType, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlLinkCount[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrlLinkState
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrlLinkState
  \brief  Link state of the EthIf controllers.
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthIfCtrlLinkStateType, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlLinkState[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrlMode
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrlMode
  \brief  Mode of the EthIf controllers
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Eth_ModeType, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlMode[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrlRxStats
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrlRxStats
  \brief  Reception statistics for the EthIf controllers
  \details
  Element       Description
  NumRxBytes    Number of bytes received on EthIf controller
  NumRxPkts     Number of packets received on EthIf controller
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthIfCtrlRxStatsType, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlRxStats[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfCtrlTxStats
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfCtrlTxStats
  \brief  Transmission statistics for the EthIf controllers
  \details
  Element       Description
  NumTxBytes    Number of bytes transmitted on EthIf controller
  NumTxPkts     Number of packets transmitted on EthIf controller
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthIfCtrlTxStatsType, ETHIF_VAR_NOINIT) EthIf_EthIfCtrlTxStats[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthIfMeasurementData
**********************************************************************************************************************/
/** 
  \var    EthIf_EthIfMeasurementData
  \brief  EthIf measurement data
  \details
  Element             Description
  DropCtrlIdx         Number of dropped datagrams caused by invalid CtrlIdx/VLAN
  UnknownEtherType    Number of dropped datagrams caused by unknown EtherType
  VlanDoubleTagged    Number of received datagrams with detected double VLAN tag
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthIfMeasurementDataType, ETHIF_VAR_NOINIT) EthIf_EthIfMeasurementData[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthTrcvInitCnt
**********************************************************************************************************************/
/** 
  \var    EthIf_EthTrcvInitCnt
  \brief  Initialization counts for the Eth transceivers abstracted by EthIf
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthTrcvInitCntType, ETHIF_VAR_NOINIT) EthIf_EthTrcvInitCnt[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_EthTrcvModeCnt
**********************************************************************************************************************/
/** 
  \var    EthIf_EthTrcvModeCnt
  \brief  Mode request counts for the Eth transceivers abstracted by EthIf
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_EthTrcvModeCntType, ETHIF_VAR_NOINIT) EthIf_EthTrcvModeCnt[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_InitLocked
**********************************************************************************************************************/
/** 
  \var    EthIf_InitLocked
  \brief  Semaphore to protect EthIf_ControllerInit() against concurrent calls.
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_InitLockedType, ETHIF_VAR_NOINIT) EthIf_InitLocked;
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_MainFuncStateDecoupleFreqCnt
**********************************************************************************************************************/
/** 
  \var    EthIf_MainFuncStateDecoupleFreqCnt
  \brief  Counter used to decouple triggers for link state change observation within EthIf_MainFunctionTx()
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_MainFuncStateDecoupleFreqCntType, ETHIF_VAR_NOINIT) EthIf_MainFuncStateDecoupleFreqCnt;  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define ETHIF_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_ModeChangeLocked
**********************************************************************************************************************/
/** 
  \var    EthIf_ModeChangeLocked
  \brief  Semaphore to protect EthIf_SetControllerMode() against concurrent calls.
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_ModeChangeLockedType, ETHIF_VAR_NOINIT) EthIf_ModeChangeLocked;
#define ETHIF_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_SignalQualityDecoupleFreqCnt
**********************************************************************************************************************/
/** 
  \var    EthIf_SignalQualityDecoupleFreqCnt
  \brief  Counter used to decouple triggers for signal quality observation within EthIf_MainFunctionState()
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_SignalQualityDecoupleFreqCntType, ETHIF_VAR_NOINIT) EthIf_SignalQualityDecoupleFreqCnt;  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define ETHIF_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_SignalQualityResult
**********************************************************************************************************************/
/** 
  \var    EthIf_SignalQualityResult
  \brief  Signal Quality of the transceiver.
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_SignalQualityResultType, ETHIF_VAR_NOINIT) EthIf_SignalQualityResult[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_SrcMacAddrBuffer
**********************************************************************************************************************/
/** 
  \var    EthIf_SrcMacAddrBuffer
  \brief  Buffer holding latest MAC address used for the Ethernet-controller
  \details
  Element    Description
  Valid      Flag defining if buffer holds a vaild MAC address
  SrcMac     MAC address
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_SrcMacAddrBufferType, ETHIF_VAR_NOINIT) EthIf_SrcMacAddrBuffer[1];
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_TxContext
**********************************************************************************************************************/
/** 
  \var    EthIf_TxContext
  \brief  Context information of each tx buffer that can be provided by the Eth drivers
  \details
  Element         Description
  PayloadLen      Length of the frames payload
  EthIfCtrlIdx    Index of the EthIf controller the frame shall be send on
  TxPending       Flag indicating if transmission is pending
  UserIdx         Index of the EthIf user the frame is owned by
  Valid           Flag indicating if the context information is valid (buffer is in use)
  FrameHdr        Ethernet frame header information
  PayloadPtr      Pointer to the frames payload
*/ 
#define ETHIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthIf_TxContextUType, ETHIF_VAR_NOINIT) EthIf_TxContext;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthIf_PCConfig
**********************************************************************************************************************/
/** 
  \var    EthIf_PCConfig
  \details
  Element                           Description
  EthCtrl                           the pointer to EthIf_EthCtrl
  EthCtrlInitCnt                    the pointer to EthIf_EthCtrlInitCnt
  EthCtrlModeCnt                    the pointer to EthIf_EthCtrlModeCnt
  EthCtrlRxFrameCnt                 the pointer to EthIf_EthCtrlRxFrameCnt
  EthDrvApi                         the pointer to EthIf_EthDrvApi
  EthIfCtrl                         the pointer to EthIf_EthIfCtrl
  EthIfCtrlInitState                the pointer to EthIf_EthIfCtrlInitState
  EthIfCtrlLinkCount                the pointer to EthIf_EthIfCtrlLinkCount
  EthIfCtrlLinkState                the pointer to EthIf_EthIfCtrlLinkState
  EthIfCtrlMode                     the pointer to EthIf_EthIfCtrlMode
  EthIfCtrlOfEthTrcvInd             the pointer to EthIf_EthIfCtrlOfEthTrcvInd
  EthIfCtrlOfPortGroupInd           the pointer to EthIf_EthIfCtrlOfPortGroupInd
  EthIfCtrlRxStats                  the pointer to EthIf_EthIfCtrlRxStats
  EthIfCtrlTxStats                  the pointer to EthIf_EthIfCtrlTxStats
  EthIfMeasurementData              the pointer to EthIf_EthIfMeasurementData
  EthSwt                            the pointer to EthIf_EthSwt
  EthSwtDrv                         the pointer to EthIf_EthSwtDrv
  EthSwtDrvApi                      the pointer to EthIf_EthSwtDrvApi
  EthSwtInd                         the pointer to EthIf_EthSwtInd
  EthSwtInitCnt                     the pointer to EthIf_EthSwtInitCnt
  EthSwtPort                        the pointer to EthIf_EthSwtPort
  EthSwtPortInd                     the pointer to EthIf_EthSwtPortInd
  EthSwtPortModeCnt                 the pointer to EthIf_EthSwtPortModeCnt
  EthTrcv                           the pointer to EthIf_EthTrcv
  EthTrcvDrvApi                     the pointer to EthIf_EthTrcvDrvApi
  EthTrcvInitCnt                    the pointer to EthIf_EthTrcvInitCnt
  EthTrcvModeCnt                    the pointer to EthIf_EthTrcvModeCnt
  ExplicitBufReleaseFilter          the pointer to EthIf_ExplicitBufReleaseFilter
  GatewaySrcMacBlackList            the pointer to EthIf_GatewaySrcMacBlackList
  InitLocked                        the pointer to EthIf_InitLocked
  LinkStateChgIndications           the pointer to EthIf_LinkStateChgIndications
  MainFuncStateDecoupleFreqCnt      the pointer to EthIf_MainFuncStateDecoupleFreqCnt
  MirrorDest                        the pointer to EthIf_MirrorDest
  MirrorTxInfo                      the pointer to EthIf_MirrorTxInfo
  ModeChangeLocked                  the pointer to EthIf_ModeChangeLocked
  PhysLayerInitElems                the pointer to EthIf_PhysLayerInitElems
  PhysLayerModeElems                the pointer to EthIf_PhysLayerModeElems
  PortGroup                         the pointer to EthIf_PortGroup
  PortGroupInd                      the pointer to EthIf_PortGroupInd
  PortGroupLinkCount                the pointer to EthIf_PortGroupLinkCount
  PortGroupLinkState                the pointer to EthIf_PortGroupLinkState
  PortGroupMode                     the pointer to EthIf_PortGroupMode
  PortSignalQualityResult           the pointer to EthIf_PortSignalQualityResult
  RxIndications                     the pointer to EthIf_RxIndications
  RxIndicationsInd                  the pointer to EthIf_RxIndicationsInd
  SignalQualityDecoupleFreqCnt      the pointer to EthIf_SignalQualityDecoupleFreqCnt
  SignalQualityResult               the pointer to EthIf_SignalQualityResult
  SrcMacAddrBuffer                  the pointer to EthIf_SrcMacAddrBuffer
  TxConfirmations                   the pointer to EthIf_TxConfirmations
  TxConfirmationsInd                the pointer to EthIf_TxConfirmationsInd
  TxContext                         the pointer to EthIf_TxContext
  User                              the pointer to EthIf_User
  WakeupMap                         the pointer to EthIf_WakeupMap
  LinkStateChgMainReload            Amount of calls link state observation isn't triggerd if observation is done within EthIf_MainFunctionTx() instead of using an explicit EthIf_MainFunctionState().
  MaxFrameRxPerEthCtrl              Maximum amount of frames that can be received during one call of EthIf_MainFunctionRx() in polling mode on one Ethernet controller
  MaxTxBufPerEthCtrl                Maximum amount of Tx buffers configured for an Ethernet controller
  SignalQualityChgMainReload        Amount of calls signal quality observation in EthIf_MainFunctionState().
  SizeOfEthCtrl                     the number of accomplishable value elements in EthIf_EthCtrl
  SizeOfEthDrvApi                   the number of accomplishable value elements in EthIf_EthDrvApi
  SizeOfEthIfCtrl                   the number of accomplishable value elements in EthIf_EthIfCtrl
  SizeOfEthIfCtrlOfEthTrcvInd       the number of accomplishable value elements in EthIf_EthIfCtrlOfEthTrcvInd
  SizeOfEthIfCtrlOfPortGroupInd     the number of accomplishable value elements in EthIf_EthIfCtrlOfPortGroupInd
  SizeOfEthIfMeasurementData        the number of accomplishable value elements in EthIf_EthIfMeasurementData
  SizeOfEthSwt                      the number of accomplishable value elements in EthIf_EthSwt
  SizeOfEthSwtDrv                   the number of accomplishable value elements in EthIf_EthSwtDrv
  SizeOfEthSwtDrvApi                the number of accomplishable value elements in EthIf_EthSwtDrvApi
  SizeOfEthSwtInd                   the number of accomplishable value elements in EthIf_EthSwtInd
  SizeOfEthSwtPort                  the number of accomplishable value elements in EthIf_EthSwtPort
  SizeOfEthSwtPortInd               the number of accomplishable value elements in EthIf_EthSwtPortInd
  SizeOfEthTrcv                     the number of accomplishable value elements in EthIf_EthTrcv
  SizeOfEthTrcvDrvApi               the number of accomplishable value elements in EthIf_EthTrcvDrvApi
  SizeOfExplicitBufReleaseFilter    the number of accomplishable value elements in EthIf_ExplicitBufReleaseFilter
  SizeOfGatewaySrcMacBlackList      the number of accomplishable value elements in EthIf_GatewaySrcMacBlackList
  SizeOfLinkStateChgIndications     the number of accomplishable value elements in EthIf_LinkStateChgIndications
  SizeOfMirrorDest                  the number of accomplishable value elements in EthIf_MirrorDest
  SizeOfMirrorTxInfo                the number of accomplishable value elements in EthIf_MirrorTxInfo
  SizeOfPhysLayerInitElems          the number of accomplishable value elements in EthIf_PhysLayerInitElems
  SizeOfPhysLayerModeElems          the number of accomplishable value elements in EthIf_PhysLayerModeElems
  SizeOfPortGroup                   the number of accomplishable value elements in EthIf_PortGroup
  SizeOfPortGroupInd                the number of accomplishable value elements in EthIf_PortGroupInd
  SizeOfRxIndications               the number of accomplishable value elements in EthIf_RxIndications
  SizeOfRxIndicationsInd            the number of accomplishable value elements in EthIf_RxIndicationsInd
  SizeOfTxConfirmations             the number of accomplishable value elements in EthIf_TxConfirmations
  SizeOfTxConfirmationsInd          the number of accomplishable value elements in EthIf_TxConfirmationsInd
  SizeOfTxContext                   the number of accomplishable value elements in EthIf_TxContext
  SizeOfUser                        the number of accomplishable value elements in EthIf_User
  SizeOfWakeupMap                   the number of accomplishable value elements in EthIf_WakeupMap
*/ 
#define ETHIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(EthIf_PCConfigsType, ETHIF_CONST) EthIf_PCConfig;
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



#endif /* ETHIF_GENTYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_GenTypes.h
 *********************************************************************************************************************/


