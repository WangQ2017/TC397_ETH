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
 *              File: EthTSyn_Lcfg.c
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#define ETHTSYN_LCFG_SOURCE

/* PRQA S 1257 EOF */ /* MD_EthTSyn_1257_Snv */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Lcfg.h" /* PRQA S 0883 */ /* MD_EthTSyn_0883 */
#include "StbM.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (ETHTSYN_LOCAL)
# define ETHTSYN_LOCAL static
#endif
 
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthTSyn_Ctrl
**********************************************************************************************************************/
/** 
  \var    EthTSyn_Ctrl
  \brief  Configuration of the EthTSyn controllers (i.e. Abstraction of the underlying EthIf controller)
  \details
  Element            Description
  EthIfCtrlIdx       Index of the underlying EthIf controller
  PortIndEndIdx      the end index of the 1:n relation pointing to EthTSyn_PortInd
  PortIndStartIdx    the start index of the 1:n relation pointing to EthTSyn_PortInd
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_CtrlType, ETHTSYN_CONST) EthTSyn_Ctrl[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    EthIfCtrlIdx                                      PortIndEndIdx                                                                 PortIndStartIdx                                                                       Referable Keys */
  { /*     0 */ EthIfConf_EthIfController_EthIfController_Vlan10,            1u  /* /ActiveEcuC/EthIf/EthIfConfigSet/EthIfController_Vlan10 */,              0u  /* /ActiveEcuC/EthIf/EthIfConfigSet/EthIfController_Vlan10 */ }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig, Dummy] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_DestinationMac
**********************************************************************************************************************/
/** 
  \var    EthTSyn_DestinationMac
  \brief  Destination MAC-Address used for the EthTSyn communication
*/ 
#define ETHTSYN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_DestinationMacType, ETHTSYN_CONST) EthTSyn_DestinationMac[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     DestinationMac  */
  /*     0 */           0x01u,
  /*     1 */           0x80u,
  /*     2 */           0xC2u,
  /*     3 */           0x00u,
  /*     4 */           0x00u,
  /*     5 */           0x0Eu
};
#define ETHTSYN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PdelayConfig
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PdelayConfig
  \brief  Configuration of Path delay measurement
  \details
  Element               Description
  InitialPdelayNs       The initially used Pdelay value (this value is also used as static value when (UseStaticPdelay == TRUE))
  AlwaysAsCapable       Indicating if the Port is always AsCapable
  UseStaticPdelay       Is static Pdelay value used
  PdelayInitiatorIdx    the index of the 0:1 relation pointing to EthTSyn_PdelayInitiator
  PdelayResponderIdx    the index of the 0:1 relation pointing to EthTSyn_PdelayResponder
  PortIdx               the index of the 1:1 relation pointing to EthTSyn_Port
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_PdelayConfigType, ETHTSYN_CONST) EthTSyn_PdelayConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitialPdelayNs  AlwaysAsCapable  UseStaticPdelay  PdelayInitiatorIdx                                                                                           PdelayResponderIdx                                                                                           PortIdx                                                                             Referable Keys */
  { /*     0 */           6000u,            TRUE,           FALSE,                 0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig */,                 0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig */,      0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig */ }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PdelayInitiator
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PdelayInitiator
  \brief  Configuration of the Pdelay initiator
  \details
  Element                    Description
  PdelayThreshold            The max allowed/valid value for Pdelay in nanoseconds
  LogMessageInterval         The Log message interval of the Pdelay request
  AllowedLostResponses       The tolerated lost responses before changing AsCapable to 'FALSE'
  AverageWeight              Weight factor used for weighted average calculation
  PdelayReqSmIdx             the index of the 1:1 relation pointing to EthTSyn_PdelayReqSm
  RespRespFollowUpTimeout    The Pdelay Response/Response FollowUp timeout in MainFunction cycles
  TxIntervalMf               The Pdelay request transmission interval in MainFunction cycles
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_PdelayInitiatorType, ETHTSYN_CONST) EthTSyn_PdelayInitiator[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PdelayThreshold  LogMessageInterval  AllowedLostResponses  AverageWeight  PdelayReqSmIdx                                                                                           RespRespFollowUpTimeout                         TxIntervalMf                                       Referable Keys */
  { /*     0 */     4294967295u,                  0,                   0u,            1u,             0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig */,                      0u  /* Timer disabled. */,         200u  /* 1.0s in MF-Cycles (5ms) */ }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PdelayResponder
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PdelayResponder
  \brief  Configuration of the Pdelay responder
  \details
  Element            Description
  PdelayRespSmIdx    the index of the 1:1 relation pointing to EthTSyn_PdelayRespSm
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_PdelayResponderType, ETHTSYN_CONST) EthTSyn_PdelayResponder[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PdelayRespSmIdx                                                                                                 Referable Keys */
  { /*     0 */              0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig */ }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PhysPortCfg
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PhysPortCfg
  \brief  Configuration of the physical ports (i.e. HW-Ports) used by the EthTSyn
  \details
  Element         Description
  DebounceTime    The debounce time expressed in EthTSyn_MainFunction cycles
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_PhysPortCfgType, ETHTSYN_CONST) EthTSyn_PhysPortCfg[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DebounceTime                                        Referable Keys */
  { /*     0 */           2u  /* 0.01s in MF-Cycles (5ms) */ }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_Port
**********************************************************************************************************************/
/** 
  \var    EthTSyn_Port
  \brief  Configuration of the EthTSyn Ports
  \details
  Element              Description
  StbMTimeSrcEqual     Identifying whether StbM uses the same time source as the EthTSyn on this port (only relevant for HW-Timestamping)
  CtrlIdx              the index of the 1:1 relation pointing to EthTSyn_Ctrl
  FramePrio            The Frame Priority used when transmitting message on this Port
  MasterPortIdx        the index of the 0:1 relation pointing to EthTSyn_MasterPort
  Number               The EthTSyn Port Number
  PdelayConfigIdx      the index of the 0:1 relation pointing to EthTSyn_PdelayConfig
  PhysPortCfgIdx       the index of the 1:1 relation pointing to EthTSyn_PhysPortCfg
  SlavePortIdx         the index of the 0:1 relation pointing to EthTSyn_SlavePort
  SwitchPortMgmtIdx    the index of the 0:1 relation pointing to EthTSyn_SwitchPortMgmt
  TimeDomainIdx        the index of the 1:1 relation pointing to EthTSyn_TimeDomain
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_PortType, ETHTSYN_CONST) EthTSyn_Port[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    StbMTimeSrcEqual  CtrlIdx                                                                       FramePrio  MasterPortIdx                                                                                        Number  PdelayConfigIdx                                                                                           PhysPortCfgIdx                                                                       SlavePortIdx                                                                       SwitchPortMgmtIdx                                                                                        TimeDomainIdx                                                           Referable Keys */
  { /*     0 */             TRUE,      0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig */,        7u, ETHTSYN_NO_MASTERPORTIDXOFPORT  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig */,     1u,              0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig */,             0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig */,           0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig */, ETHTSYN_NO_SWITCHPORTMGMTIDXOFPORT  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig */,            0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */ }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig, /ActiveEcuC/EthIf/EthIfConfigSet/EthIfController_Vlan10] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PortInd
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PortInd
  \brief  the indexes of the 1:1 sorted relation pointing to EthTSyn_Port
*/ 
#define ETHTSYN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_PortIndType, ETHTSYN_CONST) EthTSyn_PortInd[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     PortInd      Referable Keys */
  /*     0 */       0u   /* [/ActiveEcuC/EthIf/EthIfConfigSet/EthIfController_Vlan10] */
};
#define ETHTSYN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_SlavePort
**********************************************************************************************************************/
/** 
  \var    EthTSyn_SlavePort
  \brief  Configuration of the EthTSyn Slave Ports
  \details
  Element                   Description
  AnnounceInfoIdx           the index of the 0:1 relation pointing to EthTSyn_AnnounceInfo
  CrcFlagsRxValidated       Flags indicating which message fields should be used for Crc calculation
  FollowUpAllowedRxDelay    Allowed delay for received FollowUp messages in MainFunction cycles
  MasterPortIdentityIdx     the index of the 0:1 relation pointing to EthTSyn_MasterPortIdentity
  PortIdx                   the index of the 1:1 relation pointing to EthTSyn_Port
  RxCrcValidated            Crc method for received follow up messages
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_SlavePortType, ETHTSYN_CONST) EthTSyn_SlavePort[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    AnnounceInfoIdx                                                                                                                                    CrcFlagsRxValidated  FollowUpAllowedRxDelay                                   MasterPortIdentityIdx                                                                                                                                    PortIdx                                                                       RxCrcValidated                              Referable Keys */
  { /*     0 */ ETHTSYN_NO_ANNOUNCEINFOIDXOFSLAVEPORT  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPortRole/EthTSynGlobalTimeSlave */,                  0u,                    25u  /* 0.125s in MF-Cycles (5ms) */, ETHTSYN_NO_MASTERPORTIDENTITYIDXOFSLAVEPORT  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPortRole/EthTSynGlobalTimeSlave */,      0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig */, ETHTSYN_RX_CRC_VALIDATED_CRC_IGNORED }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_TimeDomain
**********************************************************************************************************************/
/** 
  \var    EthTSyn_TimeDomain
  \brief  Time domain configuration
  \details
  Element                       Description
  ImmediateTimeSync             Is immediate time sync enabled
  FollowUpDataIdListEndIdx      the end index of the 0:n relation pointing to EthTSyn_FollowUpDataIdList
  FollowUpDataIdListStartIdx    the start index of the 0:n relation pointing to EthTSyn_FollowUpDataIdList
  Id                            Id of the time domain
  MasterPortEndIdx              the end index of the 0:n relation pointing to EthTSyn_MasterPort
  MasterPortLength              the number of relations pointing to EthTSyn_MasterPort
  MasterPortStartIdx            the start index of the 0:n relation pointing to EthTSyn_MasterPort
  OffsetTimeDomainEndIdx        the end index of the 0:n relation pointing to EthTSyn_OffsetTimeDomain
  OffsetTimeDomainStartIdx      the start index of the 0:n relation pointing to EthTSyn_OffsetTimeDomain
  SlavePortEndIdx               the end index of the 0:n relation pointing to EthTSyn_SlavePort
  SlavePortStartIdx             the start index of the 0:n relation pointing to EthTSyn_SlavePort
  SynchronizedTimeBaseId        The synchronize time base id used for StbM API calls
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_TimeDomainType, ETHTSYN_CONST) EthTSyn_TimeDomain[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ImmediateTimeSync  FollowUpDataIdListEndIdx                                                                            FollowUpDataIdListStartIdx                                                                            Id  MasterPortEndIdx                                                                            MasterPortLength                                                     MasterPortStartIdx                                                                            OffsetTimeDomainEndIdx                                                                            OffsetTimeDomainStartIdx                                                                            SlavePortEndIdx                                                     SlavePortStartIdx                                                     SynchronizedTimeBaseId                                            Referable Keys */
  { /*     0 */             FALSE, ETHTSYN_NO_FOLLOWUPDATAIDLISTENDIDXOFTIMEDOMAIN  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */, ETHTSYN_NO_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */, 0u, ETHTSYN_NO_MASTERPORTENDIDXOFTIMEDOMAIN  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */,               0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */, ETHTSYN_NO_MASTERPORTSTARTIDXOFTIMEDOMAIN  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */, ETHTSYN_NO_OFFSETTIMEDOMAINENDIDXOFTIMEDOMAIN  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */, ETHTSYN_NO_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */,              1u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */,                0u  /* /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain */, StbMConf_StbMSynchronizedTimeBase_StbMSynchronizedTimeBase }   /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain] */
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_CtrlState
**********************************************************************************************************************/
/** 
  \var    EthTSyn_CtrlState
  \brief  EthTSyn controller state variable (Size Relation to constant Data: EthTSyn_Ctrl)
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_CtrlStateType, ETHTSYN_VAR_NOINIT) EthTSyn_CtrlState[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig, Dummy] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PdelayInfo
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PdelayInfo
  \brief  Changeable Pdelay information (Size Relation to constant Data: EthTSyn_PdelayConfig)
  \details
  Element          Description
  AsCapable        AsCapable Flag
  UseAverage       Indicating if weighted averaging should be used. Initialized with FALSE and set to TRUE when the first valid Pdelay was measured/calculated and set.
  PdelayValueNs    Current valid Pdelay value
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_PdelayInfoType, ETHTSYN_VAR_NOINIT) EthTSyn_PdelayInfo[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PdelayReqSm
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PdelayReqSm
  \brief  Pdelay request state machine
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_PdelayReqSmType, ETHTSYN_VAR_NOINIT) EthTSyn_PdelayReqSm[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PdelayRespSm
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PdelayRespSm
  \brief  Pdelay response state machine
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_PdelayRespSmType, ETHTSYN_VAR_NOINIT) EthTSyn_PdelayRespSm[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig/EthTSynPdelayConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PhysPort
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PhysPort
  \brief  Dynamic data belonging to a physical port (Size Relation to constant Data: EthTSyn_PhysPortCfg)
  \details
  Element          Description
  DebounceTimer    The debounce timer for the physical port
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_PhysPortType, ETHTSYN_VAR_NOINIT) EthTSyn_PhysPort[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_SwtMgmtRxBufQueueCurrProcIdx
**********************************************************************************************************************/
/** 
  \var    EthTSyn_SwtMgmtRxBufQueueCurrProcIdx
  \brief  The next EthTSyn reception buffer to be processed
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_SwtMgmtRxBufQueueCurrProcIdxType, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtRxBufQueueCurrProcIdx;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define ETHTSYN_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_SwtMgmtRxBufQueueFreeIdx
**********************************************************************************************************************/
/** 
  \var    EthTSyn_SwtMgmtRxBufQueueFreeIdx
  \brief  The next free EthTSyn reception buffer
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_SwtMgmtRxBufQueueFreeIdxType, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtRxBufQueueFreeIdx;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define ETHTSYN_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx
**********************************************************************************************************************/
/** 
  \var    EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx
  \brief  The next EthTSyn Tx management object to be processed
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdxType, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define ETHTSYN_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx
**********************************************************************************************************************/
/** 
  \var    EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx
  \brief  The next free EthTSyn Tx management object
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdxType, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define ETHTSYN_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_SyncReceiveSm
**********************************************************************************************************************/
/** 
  \var    EthTSyn_SyncReceiveSm
  \brief  Sync receive state machine (Size Relation to constant Data: EthTSyn_SlavePort)
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_SyncReceiveSmType, ETHTSYN_VAR_NOINIT) EthTSyn_SyncReceiveSm[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain, /ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain/EthTSynPortConfig] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_SystemState
**********************************************************************************************************************/
/** 
  \var    EthTSyn_SystemState
  \brief  Indicating the identity of the valid grand master. (Size Relation to constant Data: EthTSyn_TimeDomain)
  \details
  Element            Description
  GmClockIdentity    The clock identity of the grand master. Only valid for GmPresent == TRUE
  GmPresent          Indicating if a grand master is present
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_SystemStateUType, ETHTSYN_VAR_NOINIT) EthTSyn_SystemState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_TimeBaseUpdateCounter
**********************************************************************************************************************/
/** 
  \var    EthTSyn_TimeBaseUpdateCounter
  \brief  Information about the synchronized time base update counter required for immediate time sync feature. (Size Relation to constant Data: EthTSyn_TimeDomain)
  \details
  Element    Description
  Valid      Indicating if Value is valid.
  Value      Last value of the synchronized time base update counter.
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(EthTSyn_TimeBaseUpdateCounterUType, ETHTSYN_VAR_NOINIT) EthTSyn_TimeBaseUpdateCounter;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/EthTSyn/EthTSynGlobalTimeDomain] */

#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthTSyn_PCConfig
**********************************************************************************************************************/
/** 
  \var    EthTSyn_PCConfig
  \details
  Element                              Description
  AnnounceInfo                         the pointer to EthTSyn_AnnounceInfo
  AnnounceReceiveSm                    the pointer to EthTSyn_AnnounceReceiveSm
  AnnounceSendSm                       the pointer to EthTSyn_AnnounceSendSm
  AnnounceSendSmCfg                    the pointer to EthTSyn_AnnounceSendSmCfg
  Ctrl                                 the pointer to EthTSyn_Ctrl
  CtrlState                            the pointer to EthTSyn_CtrlState
  DestinationMac                       the pointer to EthTSyn_DestinationMac
  FollowUpDataIdList                   the pointer to EthTSyn_FollowUpDataIdList
  MasterPort                           the pointer to EthTSyn_MasterPort
  MasterPortIdentity                   the pointer to EthTSyn_MasterPortIdentity
  OffsetTimeDomain                     the pointer to EthTSyn_OffsetTimeDomain
  OfsCorrDurationInSyncCycles          the pointer to EthTSyn_OfsCorrDurationInSyncCycles
  PdelayConfig                         the pointer to EthTSyn_PdelayConfig
  PdelayInfo                           the pointer to EthTSyn_PdelayInfo
  PdelayInitiator                      the pointer to EthTSyn_PdelayInitiator
  PdelayReqSm                          the pointer to EthTSyn_PdelayReqSm
  PdelayRespSm                         the pointer to EthTSyn_PdelayRespSm
  PdelayResponder                      the pointer to EthTSyn_PdelayResponder
  PhysPort                             the pointer to EthTSyn_PhysPort
  PhysPortCfg                          the pointer to EthTSyn_PhysPortCfg
  Port                                 the pointer to EthTSyn_Port
  PortInd                              the pointer to EthTSyn_PortInd
  PortSyncSendSm                       the pointer to EthTSyn_PortSyncSendSm
  RateMeasurement                      the pointer to EthTSyn_RateMeasurement
  SlavePort                            the pointer to EthTSyn_SlavePort
  SlaveSwitchIdxList                   the pointer to EthTSyn_SlaveSwitchIdxList
  SwitchPortMgmt                       the pointer to EthTSyn_SwitchPortMgmt
  SwitchSyncFrameCfg                   the pointer to EthTSyn_SwitchSyncFrameCfg
  SwitchSyncFrameInfo                  the pointer to EthTSyn_SwitchSyncFrameInfo
  SwitchSyncFrameTxFrameInfo           the pointer to EthTSyn_SwitchSyncFrameTxFrameInfo
  SwitchTimeSyncCfg                    the pointer to EthTSyn_SwitchTimeSyncCfg
  SwitchTimeSyncInfo                   the pointer to EthTSyn_SwitchTimeSyncInfo
  SwtMgmtRcvdMsgBuf                    the pointer to EthTSyn_SwtMgmtRcvdMsgBuf
  SwtMgmtRxBufQueueCurrProcIdx         the pointer to EthTSyn_SwtMgmtRxBufQueueCurrProcIdx
  SwtMgmtRxBufQueueFreeIdx             the pointer to EthTSyn_SwtMgmtRxBufQueueFreeIdx
  SwtMgmtTxMgmtObjQueueCurrProcIdx     the pointer to EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx
  SwtMgmtTxMgmtObjQueueFreeIdx         the pointer to EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx
  SwtTimeSyncRateRegulatorCfg          the pointer to EthTSyn_SwtTimeSyncRateRegulatorCfg
  SyncReceiveSm                        the pointer to EthTSyn_SyncReceiveSm
  SyncSendSm                           the pointer to EthTSyn_SyncSendSm
  SystemState                          the pointer to EthTSyn_SystemState
  TimeBaseUpdateCounter                the pointer to EthTSyn_TimeBaseUpdateCounter
  TimeDomain                           the pointer to EthTSyn_TimeDomain
  TimeValidMasterCfg                   the pointer to EthTSyn_TimeValidMasterCfg
  TimeValidMasterData                  the pointer to EthTSyn_TimeValidMasterData
  TimeValidPdReqCfg                    the pointer to EthTSyn_TimeValidPdReqCfg
  TimeValidPdReqData                   the pointer to EthTSyn_TimeValidPdReqData
  TimeValidPdRespCfg                   the pointer to EthTSyn_TimeValidPdRespCfg
  TimeValidPdRespData                  the pointer to EthTSyn_TimeValidPdRespData
  TimeValidSlaveCfg                    the pointer to EthTSyn_TimeValidSlaveCfg
  TimeValidSlaveData                   the pointer to EthTSyn_TimeValidSlaveData
  SizeOfAnnounceInfo                   the number of accomplishable value elements in EthTSyn_AnnounceInfo
  SizeOfAnnounceSendSmCfg              the number of accomplishable value elements in EthTSyn_AnnounceSendSmCfg
  SizeOfCtrl                           the number of accomplishable value elements in EthTSyn_Ctrl
  SizeOfDestinationMac                 the number of accomplishable value elements in EthTSyn_DestinationMac
  SizeOfFollowUpDataIdList             the number of accomplishable value elements in EthTSyn_FollowUpDataIdList
  SizeOfMasterPort                     the number of accomplishable value elements in EthTSyn_MasterPort
  SizeOfMasterPortIdentity             the number of accomplishable value elements in EthTSyn_MasterPortIdentity
  SizeOfOffsetTimeDomain               the number of accomplishable value elements in EthTSyn_OffsetTimeDomain
  SizeOfPdelayConfig                   the number of accomplishable value elements in EthTSyn_PdelayConfig
  SizeOfPdelayInitiator                the number of accomplishable value elements in EthTSyn_PdelayInitiator
  SizeOfPdelayReqSm                    the number of accomplishable value elements in EthTSyn_PdelayReqSm
  SizeOfPdelayRespSm                   the number of accomplishable value elements in EthTSyn_PdelayRespSm
  SizeOfPdelayResponder                the number of accomplishable value elements in EthTSyn_PdelayResponder
  SizeOfPhysPortCfg                    the number of accomplishable value elements in EthTSyn_PhysPortCfg
  SizeOfPort                           the number of accomplishable value elements in EthTSyn_Port
  SizeOfPortInd                        the number of accomplishable value elements in EthTSyn_PortInd
  SizeOfRateMeasurement                the number of accomplishable value elements in EthTSyn_RateMeasurement
  SizeOfSlavePort                      the number of accomplishable value elements in EthTSyn_SlavePort
  SizeOfSlaveSwitchIdxList             the number of accomplishable value elements in EthTSyn_SlaveSwitchIdxList
  SizeOfSwitchPortMgmt                 the number of accomplishable value elements in EthTSyn_SwitchPortMgmt
  SizeOfSwitchSyncFrameCfg             the number of accomplishable value elements in EthTSyn_SwitchSyncFrameCfg
  SizeOfSwitchTimeSyncCfg              the number of accomplishable value elements in EthTSyn_SwitchTimeSyncCfg
  SizeOfSwtMgmtRcvdMsgBuf              the number of accomplishable value elements in EthTSyn_SwtMgmtRcvdMsgBuf
  SizeOfSwtTimeSyncRateRegulatorCfg    the number of accomplishable value elements in EthTSyn_SwtTimeSyncRateRegulatorCfg
  SizeOfTimeDomain                     the number of accomplishable value elements in EthTSyn_TimeDomain
  SizeOfTimeValidMasterCfg             the number of accomplishable value elements in EthTSyn_TimeValidMasterCfg
  SizeOfTimeValidPdReqCfg              the number of accomplishable value elements in EthTSyn_TimeValidPdReqCfg
  SizeOfTimeValidPdRespCfg             the number of accomplishable value elements in EthTSyn_TimeValidPdRespCfg
  SizeOfTimeValidSlaveCfg              the number of accomplishable value elements in EthTSyn_TimeValidSlaveCfg
*/ 
#define ETHTSYN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(EthTSyn_PCConfigsType, ETHTSYN_CONST) EthTSyn_PCConfig = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  { /* Index: 0 Keys: [Config] */
      NULL_PTR                                       /**< the pointer to EthTSyn_AnnounceInfo */
    , NULL_PTR                                       /**< the pointer to EthTSyn_AnnounceReceiveSm */
    , NULL_PTR                                       /**< the pointer to EthTSyn_AnnounceSendSm */
    , NULL_PTR                                       /**< the pointer to EthTSyn_AnnounceSendSmCfg */
    , EthTSyn_Ctrl                                   /**< the pointer to EthTSyn_Ctrl */
    , EthTSyn_CtrlState                              /**< the pointer to EthTSyn_CtrlState */
    , EthTSyn_DestinationMac                         /**< the pointer to EthTSyn_DestinationMac */
    , NULL_PTR                                       /**< the pointer to EthTSyn_FollowUpDataIdList */
    , NULL_PTR                                       /**< the pointer to EthTSyn_MasterPort */
    , NULL_PTR                                       /**< the pointer to EthTSyn_MasterPortIdentity */
    , NULL_PTR                                       /**< the pointer to EthTSyn_OffsetTimeDomain */
    , NULL_PTR                                       /**< the pointer to EthTSyn_OfsCorrDurationInSyncCycles */
    , EthTSyn_PdelayConfig                           /**< the pointer to EthTSyn_PdelayConfig */
    , EthTSyn_PdelayInfo                             /**< the pointer to EthTSyn_PdelayInfo */
    , EthTSyn_PdelayInitiator                        /**< the pointer to EthTSyn_PdelayInitiator */
    , EthTSyn_PdelayReqSm                            /**< the pointer to EthTSyn_PdelayReqSm */
    , EthTSyn_PdelayRespSm                           /**< the pointer to EthTSyn_PdelayRespSm */
    , EthTSyn_PdelayResponder                        /**< the pointer to EthTSyn_PdelayResponder */
    , EthTSyn_PhysPort                               /**< the pointer to EthTSyn_PhysPort */
    , EthTSyn_PhysPortCfg                            /**< the pointer to EthTSyn_PhysPortCfg */
    , EthTSyn_Port                                   /**< the pointer to EthTSyn_Port */
    , EthTSyn_PortInd                                /**< the pointer to EthTSyn_PortInd */
    , NULL_PTR                                       /**< the pointer to EthTSyn_PortSyncSendSm */
    , NULL_PTR                                       /**< the pointer to EthTSyn_RateMeasurement */
    , EthTSyn_SlavePort                              /**< the pointer to EthTSyn_SlavePort */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SlaveSwitchIdxList */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwitchPortMgmt */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwitchSyncFrameCfg */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwitchSyncFrameInfo */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwitchSyncFrameTxFrameInfo */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwitchTimeSyncCfg */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwitchTimeSyncInfo */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwtMgmtRcvdMsgBuf */
    , (&(EthTSyn_SwtMgmtRxBufQueueCurrProcIdx))      /**< the pointer to EthTSyn_SwtMgmtRxBufQueueCurrProcIdx */
    , (&(EthTSyn_SwtMgmtRxBufQueueFreeIdx))          /**< the pointer to EthTSyn_SwtMgmtRxBufQueueFreeIdx */
    , (&(EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx))  /**< the pointer to EthTSyn_SwtMgmtTxMgmtObjQueueCurrProcIdx */
    , (&(EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx))      /**< the pointer to EthTSyn_SwtMgmtTxMgmtObjQueueFreeIdx */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SwtTimeSyncRateRegulatorCfg */
    , EthTSyn_SyncReceiveSm                          /**< the pointer to EthTSyn_SyncReceiveSm */
    , NULL_PTR                                       /**< the pointer to EthTSyn_SyncSendSm */
    , EthTSyn_SystemState.raw                        /**< the pointer to EthTSyn_SystemState */
    , EthTSyn_TimeBaseUpdateCounter.raw              /**< the pointer to EthTSyn_TimeBaseUpdateCounter */
    , EthTSyn_TimeDomain                             /**< the pointer to EthTSyn_TimeDomain */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidMasterCfg */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidMasterData */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidPdReqCfg */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidPdReqData */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidPdRespCfg */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidPdRespData */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidSlaveCfg */
    , NULL_PTR                                       /**< the pointer to EthTSyn_TimeValidSlaveData */
    , 0u                                             /**< the number of elements in EthTSyn_AnnounceInfo */
    , 0u                                             /**< the number of elements in EthTSyn_AnnounceSendSmCfg */
    , 1u                                             /**< the number of elements in EthTSyn_Ctrl */
    , 6u                                             /**< the number of elements in EthTSyn_DestinationMac */
    , 0u                                             /**< the number of elements in EthTSyn_FollowUpDataIdList */
    , 0u                                             /**< the number of elements in EthTSyn_MasterPort */
    , 0u                                             /**< the number of elements in EthTSyn_MasterPortIdentity */
    , 0u                                             /**< the number of elements in EthTSyn_OffsetTimeDomain */
    , 1u                                             /**< the number of elements in EthTSyn_PdelayConfig */
    , 1u                                             /**< the number of elements in EthTSyn_PdelayInitiator */
    , 1u                                             /**< the number of elements in EthTSyn_PdelayReqSm */
    , 1u                                             /**< the number of elements in EthTSyn_PdelayRespSm */
    , 1u                                             /**< the number of elements in EthTSyn_PdelayResponder */
    , 1u                                             /**< the number of elements in EthTSyn_PhysPortCfg */
    , 1u                                             /**< the number of elements in EthTSyn_Port */
    , 1u                                             /**< the number of elements in EthTSyn_PortInd */
    , 0u                                             /**< the number of elements in EthTSyn_RateMeasurement */
    , 1u                                             /**< the number of elements in EthTSyn_SlavePort */
    , 0u                                             /**< the number of elements in EthTSyn_SlaveSwitchIdxList */
    , 0u                                             /**< the number of elements in EthTSyn_SwitchPortMgmt */
    , 0u                                             /**< the number of elements in EthTSyn_SwitchSyncFrameCfg */
    , 0u                                             /**< the number of elements in EthTSyn_SwitchTimeSyncCfg */
    , 0u                                             /**< the number of elements in EthTSyn_SwtMgmtRcvdMsgBuf */
    , 0u                                             /**< the number of elements in EthTSyn_SwtTimeSyncRateRegulatorCfg */
    , 1u                                             /**< the number of elements in EthTSyn_TimeDomain */
    , 0u                                             /**< the number of elements in EthTSyn_TimeValidMasterCfg */
    , 0u                                             /**< the number of elements in EthTSyn_TimeValidPdReqCfg */
    , 0u                                             /**< the number of elements in EthTSyn_TimeValidPdRespCfg */
    , 0u                                             /**< the number of elements in EthTSyn_TimeValidSlaveCfg */
  }
};
#define ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthTSyn_ConfigDataPtr
**********************************************************************************************************************/
/** 
  \var    EthTSyn_ConfigDataPtr
  \brief  Points to the currently active configuration for EthTSyn
  \details
  Pointer is intialized during EthTSyn_Init() and holds the active configuration for EthTSyn were all configuration data
  is retrieved from during runtime.
*/ 
#define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
P2CONST(EthTSyn_ConfigType, ETHTSYN_VAR_NOINIT, ETHTSYN_INIT_DATA) EthTSyn_ConfigDataPtr;
#define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Lcfg.c
 *********************************************************************************************************************/

