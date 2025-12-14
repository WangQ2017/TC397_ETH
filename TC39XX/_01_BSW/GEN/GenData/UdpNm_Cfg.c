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
 *            Module: UdpNm
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: UdpNm_Cfg.c
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#define UDPNM_CFG_SOURCE

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_CSL_0779 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "UdpNm_Cfg.h"
#if ( UDPNM_COM_USER_DATA_SUPPORT == STD_ON ) || defined ( UDPNM_PN_CALC_FEATURE_ENABLED )
#include "PduR_Cfg.h"
#endif
#include "SoAd_Cfg.h"
#include "Nm.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  UdpNm_ChannelConfig
**********************************************************************************************************************/
/** 
  \var    UdpNm_ChannelConfig
  \details
  Element                           Description
  TimeoutTime                       Timeout for the NM messages [ms].
  ActiveWakeUpBitEnabled            Determines if Active WUP Bit Handling is active or not
  AllMessagesKeepAwake              Determines if all NM PDUs are relevant or not
  ComControlEnabled                 Determines if Com Control is active or not
  PnHandleMultipleNetworkRequest    Determines whether a call of UdpNm_NetworkRequest leads to a transition to Repeat Message from Network Mode
  RetryFirstMessageRequest          Determines if Retry First Message Request feature is active or not
  ChannelId                         Channel ID configured for the respective instance of the NM.
  ImmediateNmCycleTime              Fast NM PDU Transmission Time during WUP
  ImmediateNmTransmissions          Number of fast NM PDU Transmissions during WUP
  MsgCycleTime                      Period of a NM message [ms]. It determines the periodic rate in the periodic transmission mode.
  MsgTimeoutTime                    Transmission Timeout [ms] of NM message. If there is no transmission confirmation within this timeout, the UDP NM module shall give an error notification.
  PduCbvPosition                    Control Bit Vector Position in the PDU
  RepeatMessageTime                 Timeout for Repeat Message State [ms].
  WaitBusSleepTime                  Timeout for bus calm down phase [ms].
*/ 
#define UDPNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(UdpNm_ChannelConfigType, UDPNM_CONST) UdpNm_ChannelConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TimeoutTime  ActiveWakeUpBitEnabled  AllMessagesKeepAwake  ComControlEnabled  PnHandleMultipleNetworkRequest  RetryFirstMessageRequest  ChannelId                                      ImmediateNmCycleTime  ImmediateNmTransmissions  MsgCycleTime  MsgTimeoutTime  PduCbvPosition    RepeatMessageTime  WaitBusSleepTime        Referable Keys */
  { /*     0 */        420u,                   TRUE,                 TRUE,              TRUE,                           TRUE,                     TRUE, NmConf_NmChannelConfig_NmChannelConfig_Vlan10,                   4u,                       5u,          20u,            12u, UDPNM_PDU_BYTE_0,               80u,             151u }   /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */
};
#define UDPNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PbChannelConfig
**********************************************************************************************************************/
/** 
  \var    UdpNm_PbChannelConfig
  \brief  Structure for post-build channel configuration parameters
  \details
  Element                               Description
  PnEnabled                             Partial Networking Enabled on this cluster
  MsgCycleOffset                    
  PnResetTime                           PnResetTimer value
  TxMessageDataEndIdx                   the end index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageDataLength                   the number of relations pointing to UdpNm_TxMessageData
  TxMessageDataStartIdx                 the start index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_CBVIdx                  the index of the 0:1 relation pointing to UdpNm_TxMessageData
  TxMessageData_PnFilterMaskEndIdx      the end index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_PnFilterMaskStartIdx    the start index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_UserDataEndIdx          the end index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_UserDataLength          the number of relations pointing to UdpNm_TxMessageData
  TxMessageData_UserDataStartIdx        the start index of the 0:n relation pointing to UdpNm_TxMessageData
  TxPduId                               PDU ID for the UdpNm TX Data PDU
  TxUserDataPduId                       PDU handle for the user data PDU
*/ 
#define UDPNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(UdpNm_PbChannelConfigType, UDPNM_CONST) UdpNm_PbChannelConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PnEnabled  MsgCycleOffset  PnResetTime  TxMessageDataEndIdx  TxMessageDataLength  TxMessageDataStartIdx  TxMessageData_CBVIdx  TxMessageData_PnFilterMaskEndIdx  TxMessageData_PnFilterMaskStartIdx  TxMessageData_UserDataEndIdx  TxMessageData_UserDataLength  TxMessageData_UserDataStartIdx  TxPduId                                   TxUserDataPduId                         Referable Keys */
  { /*     0 */      TRUE,             0u,        200u,                  8u,                  8u,                    0u,                   0u,                               8u,                                 1u,                           8u,                           7u,                             1u, SoAdConf_SoAdPduRoute_SoAdPduRoute_NM_Tx, PduRConf_PduRDestPdu_PduRDestPdu }   /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10] */
};
#define UDPNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnInfoByteConfig
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnInfoByteConfig
  \details
  Element                        Description
  PnClusterResetTimerEndIdx      the end index of the 0:n relation pointing to UdpNm_PnClusterResetTimer
  PnClusterResetTimerStartIdx    the start index of the 0:n relation pointing to UdpNm_PnClusterResetTimer
  PnFilterMask                   PnFilterMask for PnInfoBytes
*/ 
#define UDPNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(UdpNm_PnInfoByteConfigType, UDPNM_CONST) UdpNm_PnInfoByteConfig[7] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PnClusterResetTimerEndIdx  PnClusterResetTimerStartIdx  PnFilterMask        Referable Keys */
  { /*     0 */                        8u,                          0u,           1u },  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte0] */
  { /*     1 */                       16u,                          8u,           0u },  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte1] */
  { /*     2 */                       24u,                         16u,           0u },  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte2] */
  { /*     3 */                       32u,                         24u,           0u },  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte3] */
  { /*     4 */                       40u,                         32u,           0u },  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte4] */
  { /*     5 */                       48u,                         40u,           0u },  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte5] */
  { /*     6 */                       56u,                         48u,           0u }   /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte6] */
};
#define UDPNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_SysToNmChInd
**********************************************************************************************************************/
/** 
  \var    UdpNm_SysToNmChInd
  \brief  Channel indirection: System Channel handle to NM channel handle
*/ 
#define UDPNM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(UdpNm_SysToNmChIndType, UDPNM_CONST) UdpNm_SysToNmChInd[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     SysToNmChInd  */
  /*     0 */            0u
};
#define UDPNM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_CommState
**********************************************************************************************************************/
/** 
  \var    UdpNm_CommState
  \brief  Internal state for the application's need for communication.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_CommStateUType, UDPNM_VAR_NOINIT) UdpNm_CommState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_CoordReadyToSleepState
**********************************************************************************************************************/
/** 
  \var    UdpNm_CoordReadyToSleepState
  \brief  State for Rx of Coordinator Sleep Ready Bit:
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_CoordReadyToSleepStateUType, UDPNM_VAR_NOINIT) UdpNm_CoordReadyToSleepState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_ImmediateNmMsgCount
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_ImmediateNmMsgCountUType, UDPNM_VAR_NOINIT) UdpNm_ImmediateNmMsgCount;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_ModuleInitialized
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_ModuleInitializedType, UDPNM_VAR_ZERO_INIT) UdpNm_ModuleInitialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define UDPNM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgConfirmationFlag
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgConfirmationFlag
  \brief  Message Confirmation Flag
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_MsgConfirmationFlagUType, UDPNM_VAR_NOINIT) UdpNm_MsgConfirmationFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgIndicationFlag
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgIndicationFlag
  \brief  Message Indication Flag
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_MsgIndicationFlagUType, UDPNM_VAR_NOINIT) UdpNm_MsgIndicationFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgRequest
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgRequest
  \brief  Internal Message Request Variable
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_MsgRequestUType, UDPNM_VAR_NOINIT) UdpNm_MsgRequest;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgTimeoutTimer
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_MsgTimeoutTimerUType, UDPNM_VAR_NOINIT) UdpNm_MsgTimeoutTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgTimer
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgTimer
  \brief  Timer for NM message transmission.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_MsgTimerUType, UDPNM_VAR_NOINIT) UdpNm_MsgTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_NetworkRestartFlag
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_NetworkRestartFlagUType, UDPNM_VAR_NOINIT) UdpNm_NetworkRestartFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_NmState
**********************************************************************************************************************/
/** 
  \var    UdpNm_NmState
  \brief  Current state of the state machine
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_NmStateUType, UDPNM_VAR_NOINIT) UdpNm_NmState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnClusterReq
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnClusterReq
  \brief  Internal Cluster Request Buffer
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_PnClusterReqUType, UDPNM_VAR_NOINIT) UdpNm_PnClusterReq;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte0] */
  /*     1 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte1] */
  /*     2 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte2] */
  /*     3 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte3] */
  /*     4 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte4] */
  /*     5 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte5] */
  /*     6 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte6] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnClusterReqNew
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnClusterReqNew
  \brief  Internal Cluster Request Buffer
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_PnClusterReqNewUType, UDPNM_VAR_NOINIT) UdpNm_PnClusterReqNew;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte0] */
  /*     1 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte1] */
  /*     2 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte2] */
  /*     3 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte3] */
  /*     4 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte4] */
  /*     5 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte5] */
  /*     6 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte6] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnClusterResetTimer
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnClusterResetTimer
  \brief  Pn Cluster Reset Timer
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_PnClusterResetTimerUType, UDPNM_VAR_NOINIT) UdpNm_PnClusterResetTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte0] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte0] */
  /*     7 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte0] */
  /*     8 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte1] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte1] */
  /*    15 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte1] */
  /*    16 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte2] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte2] */
  /*    23 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte2] */
  /*    24 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte3] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte3] */
  /*    31 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte3] */
  /*    32 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte4] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte4] */
  /*    39 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte4] */
  /*    40 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte5] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte5] */
  /*    47 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte5] */
  /*    48 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte6] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte6] */
  /*    55 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmPnInfo/UdpNmPnFilterMaskByte6] */

#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_RepeatMsgTimer
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_RepeatMsgTimerUType, UDPNM_VAR_NOINIT) UdpNm_RepeatMsgTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_RetryFirstMessageRequestFlag
**********************************************************************************************************************/
/** 
  \var    UdpNm_RetryFirstMessageRequestFlag
  \brief  Retry First Message Request Flag
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_RetryFirstMessageRequestFlagUType, UDPNM_VAR_NOINIT) UdpNm_RetryFirstMessageRequestFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TimeoutTimer
**********************************************************************************************************************/
/** 
  \var    UdpNm_TimeoutTimer
  \brief  Timer for NM Algorithm.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_TimeoutTimerUType, UDPNM_VAR_NOINIT) UdpNm_TimeoutTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TxControlState
**********************************************************************************************************************/
/** 
  \var    UdpNm_TxControlState
  \brief  Message transmission control state.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_TxControlStateUType, UDPNM_VAR_NOINIT) UdpNm_TxControlState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TxControlStateRequest
**********************************************************************************************************************/
/** 
  \var    UdpNm_TxControlStateRequest
  \brief  Message transmission control state request.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_TxControlStateRequestUType, UDPNM_VAR_NOINIT) UdpNm_TxControlStateRequest;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TxMessageData
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_TxMessageDataType, UDPNM_VAR_NOINIT) UdpNm_TxMessageData[8];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10, /ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10_CBV] */
  /*     1 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10, /ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10_UserData, /ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10_PnFilterMask] */
  /*   ... */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10, /ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10_UserData, /ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10_PnFilterMask] */
  /*     7 */  /* [/ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10, /ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10_UserData, /ActiveEcuC/UdpNm/UdpNmGlobalConfig/UdpNmChannelConfig_Vlan10_PnFilterMask] */

#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_WaitBusSleepTimer
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(UdpNm_WaitBusSleepTimerUType, UDPNM_VAR_NOINIT) UdpNm_WaitBusSleepTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */

#define UDPNM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */




/**********************************************************************************************************************
 *  FUNCTIONS
 *********************************************************************************************************************/

#define UDPNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  MAIN FUNCTIONS
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  UdpNm_MainFunction_0()
 **********************************************************************************************************************/
/*! \brief      Numbered Main function of the UdpNm 0
 *  \pre        UdpNm is initialized
 *  \context    Task level
 *  \note       Generated for each independent UdpNm channel
 *  \note       Scheduled by the BSW scheduler
 **********************************************************************************************************************/
FUNC(void, UDPNM_CODE) UdpNm_MainFunction_0(void)
{
  UdpNm_LocalMainFunctionChannelSelector( 0u );
}


#define UDPNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  END OF FILE: UdpNm_Cfg.c
**********************************************************************************************************************/

