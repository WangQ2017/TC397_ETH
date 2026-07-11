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
 *            Module: SoAd
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: SoAd_Lcfg.c
 *   Generation Time: 2026-07-11 17:41:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#define SOAD_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "SoAd.h"
#include "TcpIp.h"
#include "PduR_SoAd.h" 
#include "DoIP_Cbk.h" 
#include "Sd_Cbk.h" 


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if defined (STATIC)
#else
# define STATIC static
#endif

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
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
  SoAd_EventQueue
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueue
  \brief  the configuration struct of all event queues
  \details
  Element       Description
  Limit         the limit of events handled in a single main function call
  BitPattern    the bit pattern for event queue
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_EventQueueType, SOAD_CONST) SoAd_EventQueue[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Limit  BitPattern                                           Referable Keys */
  { /*     0 */    2u, SOAD_EVENT_QUEUE_BIT_PATTERN_TP_RX_SO_CON     },  /* [SoAdEventQueueTpRxSoCon] */
  { /*     1 */   13u, SOAD_EVENT_QUEUE_BIT_PATTERN_STATE_SO_CON     },  /* [SoAdEventQueueStateSoCon] */
  { /*     2 */    2u, SOAD_EVENT_QUEUE_BIT_PATTERN_TP_TX_SO_CON     },  /* [SoAdEventQueueTpTxSoCon] */
  { /*     3 */    7u, SOAD_EVENT_QUEUE_BIT_PATTERN_IF_UDP_PDU_ROUTE }   /* [SoAdEventQueueIfUdpPduRoute] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueIdent
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueIdent
  \brief  the event queue identification to get the index of a specific event queue
  \details
  Element                       Description
  EventQueueIfTxRouteGrpIdx     the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueIfUdpPduRouteIdx    the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueLocalAddrIdx        the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueSockIdxIdx          the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueStateSoConIdx       the index of the 1:1 relation pointing to SoAd_EventQueue
  EventQueueTcpTxSoConIdx       the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueTpRxSoConIdx        the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueTpTxSoConIdx        the index of the 0:1 relation pointing to SoAd_EventQueue
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_EventQueueIdentType, SOAD_CONST) SoAd_EventQueueIdent[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    EventQueueIfTxRouteGrpIdx                           EventQueueIfUdpPduRouteIdx  EventQueueLocalAddrIdx                           EventQueueSockIdxIdx                           EventQueueStateSoConIdx  EventQueueTcpTxSoConIdx                           EventQueueTpRxSoConIdx  EventQueueTpTxSoConIdx */
  { /*     0 */ SOAD_NO_EVENTQUEUEIFTXROUTEGRPIDXOFEVENTQUEUEIDENT,                         3u, SOAD_NO_EVENTQUEUELOCALADDRIDXOFEVENTQUEUEIDENT, SOAD_NO_EVENTQUEUESOCKIDXIDXOFEVENTQUEUEIDENT,                      1u, SOAD_NO_EVENTQUEUETCPTXSOCONIDXOFEVENTQUEUEIDENT,                     0u,                     2u }
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddr
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddr
  \brief  the local address configurations
  \details
  Element          Description
  TcpIpCtrlIdx     the index of the 1:1 relation pointing to SoAd_TcpIpCtrl
  AddressType      address type (unicast/multicast)
  AssignTrigger    assignment trigger (automatic/manual)
  Domain           the IP domain (IPv4/6)
  AssignType       assignment type (e.g. static/link-local/DHCP)
  AddrId           the address identifier to identify the local address at TcpIp
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_LocalAddrType, SOAD_CONST) SoAd_LocalAddr[8] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TcpIpCtrlIdx  AddressType                  AssignTrigger                  Domain        AssignType                     AddrId                                                                          Referable Keys */
  { /*     0 */           0u, SOAD_ADDRESS_TYPE_UNICAST  , SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_Fixed_192_168_1_123           },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_192_168_1_123, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_untagged] */
  { /*     1 */           0u, SOAD_ADDRESS_TYPE_MULTICAST, SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpV4LocalAddr_TcpIpCtrl_untagged_Broadcast   },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_untagged_Broadcast] */
  { /*     2 */           1u, SOAD_ADDRESS_TYPE_UNICAST  , SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_DHCP  , TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33     },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan1] */
  { /*     3 */           1u, SOAD_ADDRESS_TYPE_MULTICAST, SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpV4LocalAddr_TcpIpCtrl_Vlan1_Broadcast      },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_Vlan1_Broadcast] */
  { /*     4 */           2u, SOAD_ADDRESS_TYPE_UNICAST  , SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_Fixed_10_23_0_23              },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan23] */
  { /*     5 */           2u, SOAD_ADDRESS_TYPE_MULTICAST, SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_Multicast_Rx_Fixed_239_23_0_2 },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_Fixed_239_23_0_2] */
  { /*     6 */           2u, SOAD_ADDRESS_TYPE_MULTICAST, SOAD_ASSIGN_TRIGGER_MANUAL   , SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_Multicast_Any_Vlan23             },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_Multicast_Any_Vlan23] */
  { /*     7 */           2u, SOAD_ADDRESS_TYPE_MULTICAST, SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpV4LocalAddr_TcpIpCtrl_Vlan23_Broadcast     }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_Vlan23_Broadcast] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddrByTcpIpCtrlInd
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddrByTcpIpCtrlInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_LocalAddr
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_LocalAddrByTcpIpCtrlIndType, SOAD_CONST) SoAd_LocalAddrByTcpIpCtrlInd[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     LocalAddrByTcpIpCtrlInd      Referable Keys */
  /*     0 */                       0u,  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_untagged] */
  /*     1 */                       2u,  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan1] */
  /*     2 */                       4u   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan23] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddrIdMap
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddrIdMap
  \brief  the LocalAddrId to LocalAddr mapping
  \details
  Element         Description
  InvalidHnd      FALSE, if the handle of SoAd_LocalAddrIdMap is valid and can be used in the embedded code for further processing in the embedded code.
  LocalAddrIdx    the index of the 1:1 relation pointing to SoAd_LocalAddr
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_LocalAddrIdMapType, SOAD_CONST) SoAd_LocalAddrIdMap[8] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  LocalAddrIdx        Referable Keys */
  { /*     0 */      FALSE,           0u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_192_168_1_123] */
  { /*     1 */      FALSE,           1u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_untagged_Broadcast] */
  { /*     2 */      FALSE,           2u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     3 */      FALSE,           3u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_Vlan1_Broadcast] */
  { /*     4 */      FALSE,           4u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  { /*     5 */      FALSE,           5u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_Fixed_239_23_0_2] */
  { /*     6 */      FALSE,           6u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_Multicast_Any_Vlan23] */
  { /*     7 */      FALSE,           7u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_Vlan23_Broadcast] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalIpAddrAssignmentChgCbk
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalIpAddrAssignmentChgCbk
  \brief  the callback Up_LocalIpAddrAssignmentChg
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_LocalIpAddrAssignmentChgCbkType, SOAD_CONST) SoAd_LocalIpAddrAssignmentChgCbk[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     LocalIpAddrAssignmentChgCbk        Referable Keys */
  /*     0 */ DoIP_LocalIpAddrAssignmentChg ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  /*     1 */ Sd_LocalIpAddrAssignmentChg      /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalIpAddrAssignmentChgCbkInd
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalIpAddrAssignmentChgCbkInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_LocalIpAddrAssignmentChgCbk
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_LocalIpAddrAssignmentChgCbkIndType, SOAD_CONST) SoAd_LocalIpAddrAssignmentChgCbkInd[12] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     LocalIpAddrAssignmentChgCbkInd      Referable Keys */
  /*     0 */                              0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     1 */                              0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     2 */                              0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  /*     3 */                              0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  /*     4 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  /*     5 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
  /*     6 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     7 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*     8 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     9 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    10 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    11 */                              1u   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRoute
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRoute
  \brief  the SoAdPduRoutes configuration
  \details
  Element                      Description
  TxConfPduId                  the TxPduId used to call upper layer
  AllPduRouteDestWithPduHdr    indicates if all related SoAdPduRouteDests have a SoAdTxPduHeaderId
  MetaDataTxEnabled            indicates if transmission on specific socket connection via meta data is enabled
  TxConfEnabled                indicates if TxConfirmation is enabled
  TxOptimized                  indicates if Tx optimized is enabled
  PduRouteDestEndIdx           the end index of the 1:n relation pointing to SoAd_PduRouteDest
  PduRouteDestStartIdx         the start index of the 1:n relation pointing to SoAd_PduRouteDest
  UpperLayerIdx                the index of the 1:1 relation pointing to SoAd_UpperLayer
  IfTriggerTransmitMode        the trigger transmit mode
  UpperLayerApi                the upper layer API type (IF/TP)
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_PduRouteType, SOAD_CONST) SoAd_PduRoute[10] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxConfPduId                                                                       AllPduRouteDestWithPduHdr  MetaDataTxEnabled  TxConfEnabled  TxOptimized  PduRouteDestEndIdx  PduRouteDestStartIdx  UpperLayerIdx  IfTriggerTransmitMode               UpperLayerApi         Referable Keys */
  { /*     0 */ PduRConf_PduRDestPdu_PduRDestPdu_4                                              ,                      TRUE,             FALSE,          TRUE,       FALSE,                 3u,                   0u,            0u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx] */
  { /*     1 */ DoIPConf_DoIPSoAdTcpTxPdu_DoIPSoAdTcpTxPdu                                      ,                     FALSE,             FALSE,          TRUE,       FALSE,                 4u,                   3u,            1u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_TP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA0_TX] */
  { /*     2 */ DoIPConf_DoIPSoAdTcpTxPdu_DoIPSoAdTcpTxPdu_1                                    ,                     FALSE,             FALSE,          TRUE,       FALSE,                 5u,                   4u,            1u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_TP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA1_TX] */
  { /*     3 */ DoIPConf_DoIPSoAdUdpTxPdu_DoIPSoAdUdpTxPdu                                      ,                     FALSE,             FALSE,          TRUE,       FALSE,                 6u,                   5u,            1u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TEST_EQUIPMENT_REQUEST_Tx] */
  { /*     4 */ DoIPConf_DoIPSoAdUdpVehicleAnnouncementTxPdu_DoIPSoAdUdpVehicleAnnouncementTxPdu,                     FALSE,             FALSE,          TRUE,       FALSE,                 7u,                   6u,            1u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_UDP_DISCOVERY_Tx] */
  { /*     5 */ 0u                                                                              ,                      TRUE,             FALSE,         FALSE,       FALSE,                 8u,                   7u,            2u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_Ctrl_Tx] */
  { /*     6 */ PduRConf_PduRDestPdu_PduRDestPdu_5                                              ,                      TRUE,             FALSE,          TRUE,       FALSE,                 9u,                   8u,            0u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_TCP_EcuStateTx] */
  { /*     7 */ PduRConf_PduRDestPdu_PduRDestPdu_3                                              ,                      TRUE,             FALSE,          TRUE,       FALSE,                12u,                   9u,            0u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx] */
  { /*     8 */ 0u                                                                              ,                     FALSE,             FALSE,         FALSE,       FALSE,                13u,                  12u,            0u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_TimeSyncStatus_Tx] */
  { /*     9 */ PduRConf_PduRDestPdu_PduRDestPdu_udplog_Tx_SoAd                                 ,                     FALSE,             FALSE,          TRUE,       FALSE,                14u,                  13u,            0u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_udplog_Tx] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRouteDest
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRouteDest
  \brief  the PduRouteDests configuraion
  \details
  Element                                   Description
  TxPduHdrId                                the PDU header ID
  PduRouteIdx                               the index of the 1:1 relation pointing to SoAd_PduRoute
  RouteGrpSoConByPduRouteDestIndEndIdx      the end index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd
  RouteGrpSoConByPduRouteDestIndStartIdx    the start index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd
  SoConIdx                                  the index of the 1:1 relation pointing to SoAd_SoCon
  UdpTriggerTimeout                         the PduRouteDest specific timeout to send a nPdu
  TxUdpTriggerMode                          indicates if nPdu shall be sent on transmission request always or never
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_PduRouteDestType, SOAD_CONST) SoAd_PduRouteDest[14] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxPduHdrId                        PduRouteIdx  RouteGrpSoConByPduRouteDestIndEndIdx                        RouteGrpSoConByPduRouteDestIndStartIdx                        SoConIdx  UdpTriggerTimeout  TxUdpTriggerMode                Referable Keys */
  { /*     0 */                      0xC3C18001u,          0u,                                                         2u,                                                           0u,       9u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  { /*     1 */                      0xC3C18001u,          0u,                                                         4u,                                                           2u,      10u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  { /*     2 */                      0xC3C18001u,          0u,                                                         6u,                                                           4u,      11u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  { /*     3 */ SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST,          1u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       1u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA0_TX, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  { /*     4 */ SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST,          2u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       2u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA1_TX, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  { /*     5 */ SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST,          3u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       4u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TEST_EQUIPMENT_REQUEST_Tx, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  { /*     6 */ SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST,          4u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       3u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_UDP_DISCOVERY_Tx, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  { /*     7 */                      0xFFFF8100u,          5u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       5u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_Ctrl_Tx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  { /*     8 */                      0xC3C28001u,          6u,                                                         7u,                                                           6u,       7u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_TCP_EcuStateTx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC] */
  { /*     9 */                      0xC3C08001u,          7u,                                                         9u,                                                           7u,       9u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  { /*    10 */                      0xC3C08001u,          7u,                                                        11u,                                                           9u,      10u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  { /*    11 */                      0xC3C08001u,          7u,                                                        13u,                                                          11u,      11u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  { /*    12 */ SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST,          8u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       0u,                0u, SOAD_TX_UDP_TRIGGER_NONE },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_TimeSyncStatus_Tx, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
  { /*    13 */ SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST,          9u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       0u,                0u, SOAD_TX_UDP_TRIGGER_NONE }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_udplog_Tx, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRouteDestBySoConInd
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRouteDestBySoConInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_PduRouteDest
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_PduRouteDestBySoConIndType, SOAD_CONST) SoAd_PduRouteDestBySoConInd[14] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     PduRouteDestBySoConInd      Referable Keys */
  /*     0 */                     12u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
  /*     1 */                     13u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
  /*     2 */                      3u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     3 */                      4u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     4 */                      6u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  /*     5 */                      5u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  /*     6 */                      7u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  /*     7 */                      8u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     8 */                      0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     9 */                      9u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*    10 */                      1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    11 */                     10u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    12 */                      2u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    13 */                     11u   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRouteDestInd
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRouteDestInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_PduRouteDest
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_PduRouteDestIndType, SOAD_CONST) SoAd_PduRouteDestInd[13] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     PduRouteDestInd      Referable Keys */
  /*     0 */               8u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC] */
  /*     1 */               9u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC] */
  /*     2 */              10u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC] */
  /*     3 */              11u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC] */
  /*     4 */               9u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  /*     5 */              10u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  /*     6 */              11u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  /*     7 */               0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC] */
  /*     8 */               1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC] */
  /*     9 */               2u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC] */
  /*    10 */               0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  /*    11 */               1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  /*    12 */               2u   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RemAddrIpV4
**********************************************************************************************************************/
/** 
  \var    SoAd_RemAddrIpV4
  \brief  the configured IPv4 remote addresses for each IPv4 socket connection
  \details
  Element    Description
  Addr       the remote IPv4 address
  Port       the remote port
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RemAddrIpV4Type, SOAD_CONST) SoAd_RemAddrIpV4[13] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Addr                                                 Port           Referable Keys */
  { /*     0 */ 0xFFFFFFFFuL /*  255.255.255.255 LITTLE_ENDIAN  */ , 0xD711U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
  { /*     1 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  { /*     2 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  { /*     3 */ 0xFFFFFFFFuL /*  255.255.255.255 LITTLE_ENDIAN  */ , 0x5834U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  { /*     4 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  { /*     5 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  { /*     6 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
  { /*     7 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  { /*     8 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  { /*     9 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*    10 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    11 */ 0x010017EFuL /*  239.23.0.1 LITTLE_ENDIAN  */      , 0x409CU },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    12 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */         , 0x0000U }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RouteGrp
**********************************************************************************************************************/
/** 
  \var    SoAd_RouteGrp
  \brief  the routing group configuration
  \details
  Element                    Description
  EnabledAtInit              indicates if RoutingGroup is initially enabled
  MultiInstanceOnGrp         indicates if RoutingGroup is used for the multi service instance use case on socket connection groups
  TxTriggerable              indicates if RoutingGroup can be sent
  PduRouteDestIndEndIdx      the end index of the 0:n relation pointing to SoAd_PduRouteDestInd
  PduRouteDestIndStartIdx    the start index of the 0:n relation pointing to SoAd_PduRouteDestInd
  RouteGrpSoConEndIdx        the end index of the 0:n relation pointing to SoAd_RouteGrpSoCon
  RouteGrpSoConStartIdx      the start index of the 0:n relation pointing to SoAd_RouteGrpSoCon
  SocketRouteIndEndIdx       the end index of the 0:n relation pointing to SoAd_SocketRouteInd
  SocketRouteIndStartIdx     the start index of the 0:n relation pointing to SoAd_SocketRouteInd
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RouteGrpType, SOAD_CONST) SoAd_RouteGrp[10] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    EnabledAtInit  MultiInstanceOnGrp  TxTriggerable  PduRouteDestIndEndIdx                    PduRouteDestIndStartIdx                    RouteGrpSoConEndIdx  RouteGrpSoConStartIdx  SocketRouteIndEndIdx                    SocketRouteIndStartIdx                          Referable Keys */
  { /*     0 */         FALSE,              FALSE,         FALSE,                                      1u,                                        0u,                  1u,                    0u, SOAD_NO_SOCKETROUTEINDENDIDXOFROUTEGRP, SOAD_NO_SOCKETROUTEINDSTARTIDXOFROUTEGRP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC] */
  { /*     1 */         FALSE,              FALSE,         FALSE,                                      4u,                                        1u,                  4u,                    1u, SOAD_NO_SOCKETROUTEINDENDIDXOFROUTEGRP, SOAD_NO_SOCKETROUTEINDSTARTIDXOFROUTEGRP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC] */
  { /*     2 */         FALSE,              FALSE,         FALSE,                                      7u,                                        4u,                  7u,                    4u, SOAD_NO_SOCKETROUTEINDENDIDXOFROUTEGRP, SOAD_NO_SOCKETROUTEINDSTARTIDXOFROUTEGRP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  { /*     3 */         FALSE,              FALSE,         FALSE,                                     10u,                                        7u,                 10u,                    7u, SOAD_NO_SOCKETROUTEINDENDIDXOFROUTEGRP, SOAD_NO_SOCKETROUTEINDSTARTIDXOFROUTEGRP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC] */
  { /*     4 */         FALSE,              FALSE,         FALSE,                                     13u,                                       10u,                 13u,                   10u, SOAD_NO_SOCKETROUTEINDENDIDXOFROUTEGRP, SOAD_NO_SOCKETROUTEINDSTARTIDXOFROUTEGRP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  { /*     5 */         FALSE,              FALSE,         FALSE, SOAD_NO_PDUROUTEDESTINDENDIDXOFROUTEGRP, SOAD_NO_PDUROUTEDESTINDSTARTIDXOFROUTEGRP,                 14u,                   13u,                                     1u,                                       0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC] */
  { /*     6 */         FALSE,              FALSE,         FALSE, SOAD_NO_PDUROUTEDESTINDENDIDXOFROUTEGRP, SOAD_NO_PDUROUTEDESTINDSTARTIDXOFROUTEGRP,                 17u,                   14u,                                     4u,                                       1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC] */
  { /*     7 */         FALSE,              FALSE,         FALSE, SOAD_NO_PDUROUTEDESTINDENDIDXOFROUTEGRP, SOAD_NO_PDUROUTEDESTINDSTARTIDXOFROUTEGRP,                 21u,                   17u,                                     8u,                                       4u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  { /*     8 */         FALSE,              FALSE,         FALSE, SOAD_NO_PDUROUTEDESTINDENDIDXOFROUTEGRP, SOAD_NO_PDUROUTEDESTINDSTARTIDXOFROUTEGRP,                 24u,                   21u,                                    11u,                                       8u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC] */
  { /*     9 */         FALSE,              FALSE,         FALSE, SOAD_NO_PDUROUTEDESTINDENDIDXOFROUTEGRP, SOAD_NO_PDUROUTEDESTINDSTARTIDXOFROUTEGRP,                 28u,                   24u,                                    15u,                                      11u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RouteGrpIdMap
**********************************************************************************************************************/
/** 
  \var    SoAd_RouteGrpIdMap
  \brief  the handle ID map for SoAdRoutingGroupId
  \details
  Element        Description
  InvalidHnd     FALSE, if the handle of SoAd_RouteGrpIdMap is valid and can be used in the embedded code for further processing in the embedded code.
  RouteGrpIdx    the index of the 1:1 relation pointing to SoAd_RouteGrp
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RouteGrpIdMapType, SOAD_CONST) SoAd_RouteGrpIdMap[10] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  RouteGrpIdx        Referable Keys */
  { /*     0 */      FALSE,          0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC] */
  { /*     1 */      FALSE,          1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC] */
  { /*     2 */      FALSE,          2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  { /*     3 */      FALSE,          3u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC] */
  { /*     4 */      FALSE,          4u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  { /*     5 */      FALSE,          5u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC] */
  { /*     6 */      FALSE,          6u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC] */
  { /*     7 */      FALSE,          7u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  { /*     8 */      FALSE,          8u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC] */
  { /*     9 */      FALSE,          9u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RouteGrpSoCon
**********************************************************************************************************************/
/** 
  \var    SoAd_RouteGrpSoCon
  \brief  the routing groups on the socket connections
  \details
  Element        Description
  RouteGrpIdx    the index of the 1:1 relation pointing to SoAd_RouteGrp
  SoConIdx       the index of the 1:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RouteGrpSoConType, SOAD_CONST) SoAd_RouteGrpSoCon[28] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RouteGrpIdx  SoConIdx        Referable Keys */
  { /*     0 */          0u,       7u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_TCP_EcuStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  { /*     1 */          1u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*     2 */          1u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*     3 */          1u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*     4 */          2u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*     5 */          2u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*     6 */          2u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*     7 */          3u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*     8 */          3u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*     9 */          3u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    10 */          4u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*    11 */          4u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    12 */          4u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    13 */          5u,       8u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_RX_Fixed_10_23_0_33_47842/SoAdSocketRouteDest_VechicleInfo_001>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  { /*    14 */          6u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*    15 */          6u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    16 */          6u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    17 */          7u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*    18 */          7u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    19 */          7u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    20 */          7u,      12u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_1/SoAdSocketRouteDest_VechicleSpeed_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
  { /*    21 */          8u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*    22 */          8u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    23 */          8u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    24 */          9u,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*    25 */          9u,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    26 */          9u,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    27 */          9u,      12u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_2/SoAdSocketRouteDest_VechicleStatus_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RouteGrpSoConByPduRouteDestInd
**********************************************************************************************************************/
/** 
  \var    SoAd_RouteGrpSoConByPduRouteDestInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_RouteGrpSoCon
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RouteGrpSoConByPduRouteDestIndType, SOAD_CONST) SoAd_RouteGrpSoConByPduRouteDestInd[13] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RouteGrpSoConByPduRouteDestInd      Referable Keys */
  /*     0 */                              7u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     1 */                             10u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     2 */                              8u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     3 */                             11u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     4 */                              9u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*     5 */                             12u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*     6 */                              0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_TCP_EcuStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     7 */                              1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     8 */                              4u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     9 */                              2u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    10 */                              5u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    11 */                              3u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    12 */                              6u   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RouteGrpSoConBySocketRouteDestInd
**********************************************************************************************************************/
/** 
  \var    SoAd_RouteGrpSoConBySocketRouteDestInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_RouteGrpSoCon
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RouteGrpSoConBySocketRouteDestIndType, SOAD_CONST) SoAd_RouteGrpSoConBySocketRouteDestInd[15] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RouteGrpSoConBySocketRouteDestInd      Referable Keys */
  /*     0 */                                13u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_RX_Fixed_10_23_0_33_47842/SoAdSocketRouteDest_VechicleInfo_001>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*     1 */                                14u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     2 */                                17u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     3 */                                21u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     4 */                                24u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     5 */                                15u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     6 */                                18u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     7 */                                22u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     8 */                                25u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     9 */                                16u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    10 */                                19u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    11 */                                23u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    12 */                                26u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    13 */                                20u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_1/SoAdSocketRouteDest_VechicleSpeed_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
  /*    14 */                                27u   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_2/SoAdSocketRouteDest_VechicleStatus_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxBufferConfig
**********************************************************************************************************************/
/** 
  \var    SoAd_RxBufferConfig
  \brief  the reception buffer configurations
  \details
  Element               Description
  IfRxBufferEndIdx      the end index of the 0:n relation pointing to SoAd_IfRxBuffer
  IfRxBufferStartIdx    the start index of the 0:n relation pointing to SoAd_IfRxBuffer
  TpRxBufferEndIdx      the end index of the 0:n relation pointing to SoAd_TpRxBuffer
  TpRxBufferStartIdx    the start index of the 0:n relation pointing to SoAd_TpRxBuffer
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RxBufferConfigType, SOAD_CONST) SoAd_RxBufferConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IfRxBufferEndIdx  IfRxBufferStartIdx  TpRxBufferEndIdx                          TpRxBufferStartIdx                                Referable Keys */
  { /*     0 */              12u,                 0u, SOAD_NO_TPRXBUFFERENDIDXOFRXBUFFERCONFIG, SOAD_NO_TPRXBUFFERSTARTIDXOFRXBUFFERCONFIG }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxPduIdIdMap
**********************************************************************************************************************/
/** 
  \var    SoAd_RxPduIdIdMap
  \brief  the handle ID map for RxPduId
  \details
  Element               Description
  InvalidHnd            FALSE, if the handle of SoAd_RxPduIdIdMap is valid and can be used in the embedded code for further processing in the embedded code.
  SocketRouteDestIdx    the index of the 1:1 relation pointing to SoAd_SocketRouteDest
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RxPduIdIdMapType, SOAD_CONST) SoAd_RxPduIdIdMap[10] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  SocketRouteDestIdx        Referable Keys */
  { /*     0 */      FALSE,                 0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA0_Rx] */
  { /*     1 */      FALSE,                 1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA1_Rx] */
  { /*     2 */      FALSE,                 2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_UDP_TEST_EQUIPMENT_REQUEST_Rx] */
  { /*     3 */      FALSE,                 3u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx] */
  { /*     4 */      FALSE,                 4u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx_ticast] */
  { /*     5 */      FALSE,                 5u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_RX_Fixed_10_23_0_33_47842] */
  { /*     6 */      FALSE,                10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1] */
  { /*     7 */      FALSE,                11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2] */
  { /*     8 */      FALSE,                12u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_1] */
  { /*     9 */      FALSE,                13u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_2] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoCon
**********************************************************************************************************************/
/** 
  \var    SoAd_SoCon
  \brief  the socket connection configuration
  \details
  Element                                   Description
  IpFragMgtIdx                              the index of the 0:1 relation pointing to SoAd_IpFragMgt
  LocalIpAddrAssignmentChgCbkIndEndIdx      the end index of the 0:n relation pointing to SoAd_LocalIpAddrAssignmentChgCbkInd
  LocalIpAddrAssignmentChgCbkIndStartIdx    the start index of the 0:n relation pointing to SoAd_LocalIpAddrAssignmentChgCbkInd
  NPduUdpTxIdx                              the index of the 0:1 relation pointing to SoAd_NPduUdpTx
  PduRouteDestBySoConIndEndIdx              the end index of the 0:n relation pointing to SoAd_PduRouteDestBySoConInd
  PduRouteDestBySoConIndStartIdx            the start index of the 0:n relation pointing to SoAd_PduRouteDestBySoConInd
  RcvRemAddrIdx                             the index of the 0:1 relation pointing to SoAd_RcvRemAddr
  RemAddrIpV4Idx                            the index of the 0:1 relation pointing to SoAd_RemAddrIpV4
  RemAddrIpV6Idx                            the index of the 0:1 relation pointing to SoAd_RemAddrIpV6
  RxBufStructMgtIdx                         the index of the 0:1 relation pointing to SoAd_RxBufStructMgt
  RxBufStructSegEndIdx                      the end index of the 0:n relation pointing to SoAd_RxBufStructSeg
  RxBufStructSegStartIdx                    the start index of the 0:n relation pointing to SoAd_RxBufStructSeg
  RxBufferConfigIdx                         the index of the 0:1 relation pointing to SoAd_RxBufferConfig
  RxMgtIdx                                  the index of the 0:1 relation pointing to SoAd_RxMgt
  SoConGrpIdx                               the index of the 1:1 relation pointing to SoAd_SoConGrp
  SoConId                                   the SocketConnection identifier used in SoAd API
  SoConModeChgCbkIndEndIdx                  the end index of the 0:n relation pointing to SoAd_SoConModeChgCbkInd
  SoConModeChgCbkIndStartIdx                the start index of the 0:n relation pointing to SoAd_SoConModeChgCbkInd
  SocketIdx                                 the index of the 1:1 relation pointing to SoAd_Socket
  SocketRouteEndIdx                         the end index of the 0:n relation pointing to SoAd_SocketRoute
  SocketRouteStartIdx                       the start index of the 0:n relation pointing to SoAd_SocketRoute
  TcpTxQueueIdx                             the index of the 0:1 relation pointing to SoAd_TcpTxQueue
  TlsConfigIdx                              the index of the 0:1 relation pointing to SoAd_TlsConfig
  TpTxBufferConfigIdx                       the index of the 0:1 relation pointing to SoAd_TpTxBufferConfig
  TxMgtIdx                                  the index of the 0:1 relation pointing to SoAd_TxMgt
  RemAddrState                              the configured remote address state
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SoConType, SOAD_CONST) SoAd_SoCon[13] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IpFragMgtIdx                 LocalIpAddrAssignmentChgCbkIndEndIdx                 LocalIpAddrAssignmentChgCbkIndStartIdx                 NPduUdpTxIdx                 PduRouteDestBySoConIndEndIdx                 PduRouteDestBySoConIndStartIdx                 RcvRemAddrIdx                 RemAddrIpV4Idx  RemAddrIpV6Idx                 RxBufStructMgtIdx                 RxBufStructSegEndIdx                 RxBufStructSegStartIdx                 RxBufferConfigIdx                 RxMgtIdx                 SoConGrpIdx  SoConId  SoConModeChgCbkIndEndIdx                 SoConModeChgCbkIndStartIdx                 SocketIdx  SocketRouteEndIdx                 SocketRouteStartIdx                 TcpTxQueueIdx                 TlsConfigIdx                 TpTxBufferConfigIdx                 TxMgtIdx                 RemAddrState                      Referable Keys */
  { /*     0 */ SOAD_NO_IPFRAGMGTIDXOFSOCON, SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDENDIDXOFSOCON, SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          2u,                                            0u, SOAD_NO_RCVREMADDRIDXOFSOCON,             0u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON, SOAD_NO_RXMGTIDXOFSOCON,          0u,     11u, SOAD_NO_SOCONMODECHGCBKINDENDIDXOFSOCON, SOAD_NO_SOCONMODECHGCBKINDSTARTIDXOFSOCON,        0u, SOAD_NO_SOCKETROUTEENDIDXOFSOCON, SOAD_NO_SOCKETROUTESTARTIDXOFSOCON, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      0u, SOAD_SOCON_IP_SET_PORT_SET },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567] */
  { /*     1 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  1u,                                                    0u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          3u,                                            2u, SOAD_NO_RCVREMADDRIDXOFSOCON,             1u, SOAD_NO_REMADDRIPV6IDXOFSOCON,                               0u,                                  2u,                                    0u, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      0u,          1u,      0u,                                      1u,                                        0u,        2u,                               1u,                                 0u,                           0u, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      1u, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0>>DATA] */
  { /*     2 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  2u,                                                    1u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          4u,                                            3u, SOAD_NO_RCVREMADDRIDXOFSOCON,             2u, SOAD_NO_REMADDRIPV6IDXOFSOCON,                               1u,                                  4u,                                    2u, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      1u,          1u,      1u,                                      2u,                                        1u,        3u,                               2u,                                 1u,                           1u, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      2u, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1>>DATA] */
  { /*     3 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  3u,                                                    2u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          5u,                                            4u, SOAD_NO_RCVREMADDRIDXOFSOCON,             3u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON, SOAD_NO_RXMGTIDXOFSOCON,          2u,      3u,                                      3u,                                        2u,        4u, SOAD_NO_SOCKETROUTEENDIDXOFSOCON, SOAD_NO_SOCKETROUTESTARTIDXOFSOCON, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      3u, SOAD_SOCON_IP_SET_PORT_SET },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400] */
  { /*     4 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  4u,                                                    3u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          6u,                                            5u, SOAD_NO_RCVREMADDRIDXOFSOCON,             4u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      2u,          2u,      2u,                                      4u,                                        3u,        4u,                               3u,                                 2u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      4u, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400] */
  { /*     5 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  5u,                                                    4u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          7u,                                            6u,                           0u,             5u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      3u,          3u,      5u,                                      5u,                                        4u,        5u,                               4u,                                 3u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      5u, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490] */
  { /*     6 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  6u,                                                    5u, SOAD_NO_NPDUUDPTXIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON,                           1u,             6u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      4u,          4u,      4u,                                      6u,                                        5u,        6u,                               5u,                                 4u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON, SOAD_NO_TXMGTIDXOFSOCON, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490] */
  { /*     7 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  7u,                                                    6u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          8u,                                            7u, SOAD_NO_RCVREMADDRIDXOFSOCON,             7u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON, SOAD_NO_RXMGTIDXOFSOCON,          5u,      7u,                                      7u,                                        6u,        8u, SOAD_NO_SOCKETROUTEENDIDXOFSOCON, SOAD_NO_SOCKETROUTESTARTIDXOFSOCON,                           2u, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      6u, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort>>DATA] */
  { /*     8 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  8u,                                                    7u, SOAD_NO_NPDUUDPTXIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON, SOAD_NO_RCVREMADDRIDXOFSOCON,             8u, SOAD_NO_REMADDRIPV6IDXOFSOCON,                               2u,                                  6u,                                    4u,                               0u,                      5u,          6u,      6u,                                      8u,                                        7u,        9u,                               6u,                                 5u,                           3u, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON, SOAD_NO_TXMGTIDXOFSOCON, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842] */
  { /*     9 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                  9u,                                                    8u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                         10u,                                            8u, SOAD_NO_RCVREMADDRIDXOFSOCON,             9u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      6u,          7u,      8u,                                      9u,                                        8u,       10u,                               8u,                                 6u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      7u, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000] */
  { /*    10 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                 10u,                                                    9u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                         12u,                                           10u, SOAD_NO_RCVREMADDRIDXOFSOCON,            10u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      7u,          7u,      9u,                                     10u,                                        9u,       10u,                              10u,                                 8u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      8u, SOAD_SOCON_IP_ANY_PORT_ANY },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000] */
  { /*    11 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                 11u,                                                   10u, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                         14u,                                           12u, SOAD_NO_RCVREMADDRIDXOFSOCON,            11u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      8u,          7u,     10u,                                     11u,                                       10u,       10u,                              12u,                                10u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      9u, SOAD_SOCON_IP_SET_PORT_SET },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000] */
  { /*    12 */ SOAD_NO_IPFRAGMGTIDXOFSOCON,                                                 12u,                                                   11u, SOAD_NO_NPDUUDPTXIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON, SOAD_NO_RCVREMADDRIDXOFSOCON,            12u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      9u,          8u,     12u,                                     12u,                                       11u,       11u,                              14u,                                12u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON, SOAD_NO_TXMGTIDXOFSOCON, SOAD_SOCON_IP_ANY_PORT_ANY }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConGrp
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConGrp
  \brief  the socket connection group configuration
  \details
  Element                          Description
  BestMatchWithPduHeaderEnabled    indicates if best match algorithm considers PDU Header ID
  BestMatchWithSockRouteEnabled    indicates if best match algorithm considers socket route availability
  MsgAcceptFilterEnabled           indicates if message acceptance filter is enabled
  PduHdrEnabled                    indicates if PDU header is enabled
  SockAutoSoConSetup               indicates if automatic socket connection setup is enabled
  SockAutoSoConSetupKeepOnline     indicates if it is enabled that socket connection stays online after transmission
  FramePriority                    the frame priority (VLAN)
  LocalAddrIdx                     the index of the 0:1 relation pointing to SoAd_LocalAddr
  SoConEndIdx                      the end index of the 1:n relation pointing to SoAd_SoCon
  SoConStartIdx                    the start index of the 1:n relation pointing to SoAd_SoCon
  SocketIdx                        the index of the 0:1 relation pointing to SoAd_Socket
  SocketTcpIdx                     the index of the 0:1 relation pointing to SoAd_SocketTcp
  SocketUdpIdx                     the index of the 0:1 relation pointing to SoAd_SocketUdp
  LocalPort                        the local port
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SoConGrpType, SOAD_CONST) SoAd_SoConGrp[9] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    BestMatchWithPduHeaderEnabled  BestMatchWithSockRouteEnabled  MsgAcceptFilterEnabled  PduHdrEnabled  SockAutoSoConSetup  SockAutoSoConSetupKeepOnline  FramePriority                    LocalAddrIdx  SoConEndIdx  SoConStartIdx  SocketIdx                    SocketTcpIdx                    SocketUdpIdx                    LocalPort        Referable Keys */
  { /*     0 */                         FALSE,                         FALSE,                   TRUE,         FALSE,               TRUE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           0u,          1u,            0u,                          0u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,                             0u, 0xD711U   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
  { /*     1 */                         FALSE,                         FALSE,                   TRUE,         FALSE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           2u,          3u,            1u,                          1u,                             0u, SOAD_NO_SOCKETUDPIDXOFSOCONGRP, 0x5834U   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  { /*     2 */                         FALSE,                         FALSE,                   TRUE,         FALSE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           2u,          5u,            3u,                          4u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,                             1u, 0x5834U   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  { /*     3 */                         FALSE,                         FALSE,                  FALSE,          TRUE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           4u,          6u,            5u,                          5u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,                             2u, 0x1A77U   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  { /*     4 */                         FALSE,                         FALSE,                  FALSE,          TRUE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           5u,          7u,            6u,                          6u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,                             3u, 0x1A77U   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
  { /*     5 */                         FALSE,                         FALSE,                   TRUE,          TRUE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           4u,          8u,            7u,                          7u,                             1u, SOAD_NO_SOCKETUDPIDXOFSOCONGRP, 0xE3BAU   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  { /*     6 */                         FALSE,                         FALSE,                   TRUE,          TRUE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           4u,          9u,            8u, SOAD_NO_SOCKETIDXOFSOCONGRP,                             2u, SOAD_NO_SOCKETUDPIDXOFSOCONGRP, 0xE2BAU   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  { /*     7 */                         FALSE,                         FALSE,                   TRUE,          TRUE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           4u,         12u,            9u,                         10u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,                             4u, 0x409CU   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*     8 */                         FALSE,                         FALSE,                   TRUE,          TRUE,              FALSE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           6u,         13u,           12u,                         11u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,                             5u, 0x409CU   }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConMap
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConMap
  \brief  the handle ID map for SoAdSocketId
  \details
  Element       Description
  InvalidHnd    FALSE, if the handle of SoAd_SoConMap is valid and can be used in the embedded code for further processing in the embedded code.
  SoConIdx      the index of the 1:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SoConMapType, SOAD_CONST) SoAd_SoConMap[13] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  SoConIdx        Referable Keys */
  { /*     0 */      FALSE,       1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  { /*     1 */      FALSE,       2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  { /*     2 */      FALSE,       4u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  { /*     3 */      FALSE,       3u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  { /*     4 */      FALSE,       6u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
  { /*     5 */      FALSE,       5u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  { /*     6 */      FALSE,       8u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  { /*     7 */      FALSE,       7u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  { /*     8 */      FALSE,       9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*     9 */      FALSE,      10u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    10 */      FALSE,      11u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    11 */      FALSE,       0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
  { /*    12 */      FALSE,      12u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConModeChgCbk
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConModeChgCbk
  \brief  the callback Up_SoConModeChg
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SoConModeChgCbkType, SOAD_CONST) SoAd_SoConModeChgCbk[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     SoConModeChgCbk        Referable Keys */
  /*     0 */ DoIP_SoConModeChg ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  /*     1 */ Sd_SoConModeChg      /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConModeChgCbkInd
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConModeChgCbkInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_SoConModeChgCbk
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SoConModeChgCbkIndType, SOAD_CONST) SoAd_SoConModeChgCbkInd[12] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     SoConModeChgCbkInd      Referable Keys */
  /*     0 */                  0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     1 */                  0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     2 */                  0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  /*     3 */                  0u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  /*     4 */                  1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  /*     5 */                  1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
  /*     6 */                  1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     7 */                  1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*     8 */                  1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     9 */                  1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    10 */                  1u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    11 */                  1u   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_Socket
**********************************************************************************************************************/
/** 
  \var    SoAd_Socket
  \brief  the socket configuration
  \details
  Element          Description
  SoConEndIdx      the end index of the 1:n relation pointing to SoAd_SoCon
  SoConStartIdx    the start index of the 1:n relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SocketType, SOAD_CONST) SoAd_Socket[12] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    SoConEndIdx  SoConStartIdx        Referable Keys */
  { /*     0 */          1u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_192_168_1_123] */
  { /*     1 */          3u,            1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     2 */          2u,            1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0>>DATA, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     3 */          3u,            2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1>>DATA, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     4 */          5u,            3u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     5 */          6u,            5u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  { /*     6 */          7u,            6u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_Fixed_239_23_0_2] */
  { /*     7 */          8u,            7u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  { /*     8 */          8u,            7u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort>>DATA, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  { /*     9 */          9u,            8u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  { /*    10 */         12u,            9u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  { /*    11 */         13u,           12u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_Multicast_Any_Vlan23] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketRoute
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketRoute
  \brief  the socket route configuration
  \details
  Element                    Description
  RxPduHdrId                 the PDU header ID
  MetaDataRxEnabled          indicates if SoConId is forwarded as meta data on reception
  SoConIdx                   the index of the 1:1 relation pointing to SoAd_SoCon
  SocketRouteDestEndIdx      the end index of the 1:n relation pointing to SoAd_SocketRouteDest
  SocketRouteDestStartIdx    the start index of the 1:n relation pointing to SoAd_SocketRouteDest
  UpperLayerApi              the upper layer API type (IF/TP)
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SocketRouteType, SOAD_CONST) SoAd_SocketRoute[14] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxPduHdrId                       MetaDataRxEnabled  SoConIdx  SocketRouteDestEndIdx  SocketRouteDestStartIdx  UpperLayerApi         Referable Keys */
  { /*     0 */ SOAD_NO_RXPDUHDRIDOFSOCKETROUTE,             FALSE,       1u,                    1u,                      0u, SOAD_UL_API_TP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA0_Rx] */
  { /*     1 */ SOAD_NO_RXPDUHDRIDOFSOCKETROUTE,             FALSE,       2u,                    2u,                      1u, SOAD_UL_API_TP },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA1_Rx] */
  { /*     2 */ SOAD_NO_RXPDUHDRIDOFSOCKETROUTE,             FALSE,       4u,                    3u,                      2u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_UDP_TEST_EQUIPMENT_REQUEST_Rx] */
  { /*     3 */                     0xFFFF8100u,             FALSE,       5u,                    4u,                      3u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx] */
  { /*     4 */                     0xFFFF8100u,             FALSE,       6u,                    5u,                      4u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx_ticast] */
  { /*     5 */                     0xC3CD8001u,             FALSE,       8u,                    6u,                      5u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_RX_Fixed_10_23_0_33_47842, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC] */
  { /*     6 */                     0xC3CB8001u,             FALSE,       9u,                    7u,                      6u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  { /*     7 */                     0xC3CC8001u,             FALSE,       9u,                    8u,                      7u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
  { /*     8 */                     0xC3CB8001u,             FALSE,      10u,                    9u,                      8u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  { /*     9 */                     0xC3CC8001u,             FALSE,      10u,                   10u,                      9u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
  { /*    10 */                     0xC3CB8001u,             FALSE,      11u,                   11u,                     10u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  { /*    11 */                     0xC3CC8001u,             FALSE,      11u,                   12u,                     11u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
  { /*    12 */                     0xC3CB8001u,             FALSE,      12u,                   13u,                     12u, SOAD_UL_API_IF },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  { /*    13 */                     0xC3CC8001u,             FALSE,      12u,                   14u,                     13u, SOAD_UL_API_IF }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_2, /ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketRouteDest
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketRouteDest
  \brief  the socket route destination configuration
  \details
  Element                                      Description
  RxPduId                                      the RxPduId used to call the upper layer
  RouteGrpSoConBySocketRouteDestIndEndIdx      the end index of the 0:n relation pointing to SoAd_RouteGrpSoConBySocketRouteDestInd
  RouteGrpSoConBySocketRouteDestIndStartIdx    the start index of the 0:n relation pointing to SoAd_RouteGrpSoConBySocketRouteDestInd
  SocketRouteIdx                               the index of the 1:1 relation pointing to SoAd_SocketRoute
  UpperLayerIdx                                the index of the 1:1 relation pointing to SoAd_UpperLayer
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SocketRouteDestType, SOAD_CONST) SoAd_SocketRouteDest[14] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxPduId                                                   RouteGrpSoConBySocketRouteDestIndEndIdx                           RouteGrpSoConBySocketRouteDestIndStartIdx                           SocketRouteIdx  UpperLayerIdx        Referable Keys */
  { /*     0 */ DoIPConf_DoIPSoAdTcpRxPdu_DoIPSoAdTcpRxPdu              , SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST,             0u,            1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA0_Rx>>/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA0_Rx/SoAdSocketRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  { /*     1 */ DoIPConf_DoIPSoAdTcpRxPdu_DoIPSoAdTcpRxPdu_1            , SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST,             1u,            1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA1_Rx>>/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_TCP_DATA1_Rx/SoAdSocketRouteDest_001>>/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  { /*     2 */ DoIPConf_DoIPSoAdUdpRxPdu_DoIPSoAdUdpRxPdu              , SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST,             2u,            1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_UDP_TEST_EQUIPMENT_REQUEST_Rx>>/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_DOIP_UDP_TEST_EQUIPMENT_REQUEST_Rx/SoAdSocketRouteDest_1>>/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  { /*     3 */ SdConf_SdInstanceUnicastRxPdu_SdInstanceUnicastRxPdu    , SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST,             3u,            2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx/SoAdSocketRouteDest_2>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  { /*     4 */ SdConf_SdInstanceMulticastRxPdu_SdInstanceMulticastRxPdu, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST,             4u,            2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx_ticast>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_Ctrl_Rx_ticast/SoAdSocketRouteDest_3>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
  { /*     5 */ PduRConf_PduRSrcPdu_PduRSrcPdu_3                        ,                                                               1u,                                                                 0u,             5u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_RX_Fixed_10_23_0_33_47842>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_RX_Fixed_10_23_0_33_47842/SoAdSocketRouteDest_VechicleInfo_001>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  { /*     6 */ PduRConf_PduRSrcPdu_PduRSrcPdu_1                        ,                                                               3u,                                                                 1u,             6u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*     7 */ PduRConf_PduRSrcPdu_PduRSrcPdu_2                        ,                                                               5u,                                                                 3u,             7u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  { /*     8 */ PduRConf_PduRSrcPdu_PduRSrcPdu_1                        ,                                                               7u,                                                                 5u,             6u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*     9 */ PduRConf_PduRSrcPdu_PduRSrcPdu_2                        ,                                                               9u,                                                                 7u,             7u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  { /*    10 */ PduRConf_PduRSrcPdu_PduRSrcPdu_1                        ,                                                              11u,                                                                 9u,             6u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    11 */ PduRConf_PduRSrcPdu_PduRSrcPdu_2                        ,                                                              13u,                                                                11u,             7u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  { /*    12 */ PduRConf_PduRSrcPdu_PduRSrcPdu_1                        ,                                                              14u,                                                                13u,            12u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_1>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_1/SoAdSocketRouteDest_VechicleSpeed_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
  { /*    13 */ PduRConf_PduRSrcPdu_PduRSrcPdu_2                        ,                                                              15u,                                                                14u,            13u,            0u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_2>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_2/SoAdSocketRouteDest_VechicleStatus_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketRouteInd
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketRouteInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_SocketRoute
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SocketRouteIndType, SOAD_CONST) SoAd_SocketRouteInd[15] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     SocketRouteInd      Referable Keys */
  /*     0 */              5u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC] */
  /*     1 */              6u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC] */
  /*     2 */              8u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC] */
  /*     3 */             10u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC] */
  /*     4 */              6u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  /*     5 */              8u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  /*     6 */             10u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  /*     7 */             12u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  /*     8 */              7u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC] */
  /*     9 */              9u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC] */
  /*    10 */             11u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC] */
  /*    11 */              7u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
  /*    12 */              9u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
  /*    13 */             11u,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
  /*    14 */             13u   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM] */
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketTcp
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketTcp
  \brief  the TCP socket configuration
  \details
  Element                  Description
  TcpRxBufMin              the size of TCP reception buffer
  TcpTxBufMin              the size of TCP transmission buffer
  ImmedTpTxConf            indicates if TP immediate TxConfirmation is used
  TcpInitiate              indicates if TCP connection is initiated by SoAd
  TcpKeepAlive             indicates if keepalive mechanism is used
  TcpKeepAliveInterval     the interval time between keepalive probes
  TcpKeepAliveProbesMax    the maximum number of keepalive probes
  TcpKeepAliveTime         the time between the last data packet sent and the first keepalive probe
  TcpNoDelay               indicates not to use the congestion control mechanism
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SocketTcpType, SOAD_CONST) SoAd_SocketTcp[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TcpRxBufMin  TcpTxBufMin  ImmedTpTxConf  TcpInitiate  TcpKeepAlive  TcpKeepAliveInterval                     TcpKeepAliveProbesMax                     TcpKeepAliveTime                     TcpNoDelay                             Referable Keys */
  { /*     0 */       1024u,       1024u,         FALSE,       FALSE,        FALSE, SOAD_NO_TCPKEEPALIVEINTERVALOFSOCKETTCP, SOAD_NO_TCPKEEPALIVEPROBESMAXOFSOCKETTCP, SOAD_NO_TCPKEEPALIVETIMEOFSOCKETTCP, SOAD_TCP_NO_DELAY_ENABLED       },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400] */
  { /*     1 */        512u,        512u,         FALSE,       FALSE,        FALSE, SOAD_NO_TCPKEEPALIVEINTERVALOFSOCKETTCP, SOAD_NO_TCPKEEPALIVEPROBESMAXOFSOCKETTCP, SOAD_NO_TCPKEEPALIVETIMEOFSOCKETTCP, SOAD_TCP_NO_DELAY_NOT_SPECIFIED },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843] */
  { /*     2 */        512u,        512u,         FALSE,        TRUE,        FALSE, SOAD_NO_TCPKEEPALIVEINTERVALOFSOCKETTCP, SOAD_NO_TCPKEEPALIVEPROBESMAXOFSOCKETTCP, SOAD_NO_TCPKEEPALIVETIMEOFSOCKETTCP, SOAD_TCP_NO_DELAY_NOT_SPECIFIED }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketUdp
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketUdp
  \brief  the UDP socket configuration
  \details
  Element                        Description
  ImmedIfTxConf              
  UdpListenOnly              
  UdpStrictHdrLenCheckEnabled
  AliveTimeoutMaxCnt         
  ImmedIfTxConfListSize      
  NPduUdpTxBufferMin         
  NPduUdpTxQueueSize         
  RetryQueueLimit            
  UdpTriggerTimeout          
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SocketUdpType, SOAD_CONST) SoAd_SocketUdp[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ImmedIfTxConf  UdpListenOnly  UdpStrictHdrLenCheckEnabled  AliveTimeoutMaxCnt  ImmedIfTxConfListSize  NPduUdpTxBufferMin  NPduUdpTxQueueSize  RetryQueueLimit  UdpTriggerTimeout        Referable Keys */
  { /*     0 */         FALSE,         FALSE,                       FALSE,                 0u,                    0u,                 0u,                 0u,              1u,                0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567] */
  { /*     1 */         FALSE,         FALSE,                       FALSE,                 0u,                    0u,                 0u,                 0u,              1u,                0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400] */
  { /*     2 */         FALSE,         FALSE,                       FALSE,                 0u,                    0u,                 0u,                 0u,              1u,                0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490] */
  { /*     3 */         FALSE,         FALSE,                       FALSE,                 0u,                    0u,                 0u,                 0u,              1u,                0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490] */
  { /*     4 */         FALSE,         FALSE,                       FALSE,               200u,                    0u,                 0u,                 0u,              1u,                0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000] */
  { /*     5 */         FALSE,          TRUE,                       FALSE,               200u,                    0u,                 0u,                 0u,              1u,                0u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TcpIpCtrl
**********************************************************************************************************************/
/** 
  \var    SoAd_TcpIpCtrl
  \brief  the TcpIp controller/interface
  \details
  Element                            Description
  RetryEnabled                       indicates if transmission retry is available on controller/interface
  LocalAddrByTcpIpCtrlIndEndIdx      the end index of the 0:n relation pointing to SoAd_LocalAddrByTcpIpCtrlInd
  LocalAddrByTcpIpCtrlIndStartIdx    the start index of the 0:n relation pointing to SoAd_LocalAddrByTcpIpCtrlInd
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_TcpIpCtrlType, SOAD_CONST) SoAd_TcpIpCtrl[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RetryEnabled  LocalAddrByTcpIpCtrlIndEndIdx  LocalAddrByTcpIpCtrlIndStartIdx        Referable Keys */
  { /*     0 */         TRUE,                            1u,                              0u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_untagged] */
  { /*     1 */         TRUE,                            2u,                              1u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan1] */
  { /*     2 */         TRUE,                            3u,                              2u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan23] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TcpKeepAliveGloballyEnabled
**********************************************************************************************************************/
/** 
  \var    SoAd_TcpKeepAliveGloballyEnabled
  \brief  indicates if TCP keep alive is enabled at all
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_TcpKeepAliveGloballyEnabledType, SOAD_CONST) SoAd_TcpKeepAliveGloballyEnabled[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TcpKeepAliveGloballyEnabled  */
  /*     0 */                        FALSE
};
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TcpTxQueue
**********************************************************************************************************************/
/** 
  \var    SoAd_TcpTxQueue
  \brief  the Tx TCP queues configuration
  \details
  Element                   Description
  TcpTxQueueDataEndIdx      the end index of the 1:n relation pointing to SoAd_TcpTxQueueData
  TcpTxQueueDataStartIdx    the start index of the 1:n relation pointing to SoAd_TcpTxQueueData
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_TcpTxQueueType, SOAD_CONST) SoAd_TcpTxQueue[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TcpTxQueueDataEndIdx  TcpTxQueueDataStartIdx        Referable Keys */
  { /*     0 */                   2u,                     0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  { /*     1 */                   4u,                     2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  { /*     2 */                   5u,                     4u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  { /*     3 */                   6u,                     5u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TimeoutListIdent
**********************************************************************************************************************/
/** 
  \var    SoAd_TimeoutListIdent
  \brief  the timeout list identification to get the index of a specific timeout list
  \details
  Element                       Description
  TimeoutListDynNPduUdpTxIdx    the index of the 0:1 relation pointing to SoAd_TimeoutListDyn
  TimeoutListDynUdpAliveIdx     the index of the 0:1 relation pointing to SoAd_TimeoutListDyn
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_TimeoutListIdentType, SOAD_CONST) SoAd_TimeoutListIdent[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TimeoutListDynNPduUdpTxIdx                            TimeoutListDynUdpAliveIdx */
  { /*     0 */ SOAD_NO_TIMEOUTLISTDYNNPDUUDPTXIDXOFTIMEOUTLISTIDENT,                        0u }
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TxPduIdMap
**********************************************************************************************************************/
/** 
  \var    SoAd_TxPduIdMap
  \brief  the handle ID map for TxPduId
  \details
  Element        Description
  InvalidHnd     FALSE, if the handle of SoAd_TxPduIdMap is valid and can be used in the embedded code for further processing in the embedded code.
  PduRouteIdx    the index of the 1:1 relation pointing to SoAd_PduRoute
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_TxPduIdMapType, SOAD_CONST) SoAd_TxPduIdMap[10] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  PduRouteIdx        Referable Keys */
  { /*     0 */      FALSE,          0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx] */
  { /*     1 */      FALSE,          1u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA0_TX] */
  { /*     2 */      FALSE,          2u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA1_TX] */
  { /*     3 */      FALSE,          3u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TEST_EQUIPMENT_REQUEST_Tx] */
  { /*     4 */      FALSE,          4u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_UDP_DISCOVERY_Tx] */
  { /*     5 */      FALSE,          5u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_Ctrl_Tx] */
  { /*     6 */      FALSE,          6u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_TCP_EcuStateTx] */
  { /*     7 */      FALSE,          7u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx] */
  { /*     8 */      FALSE,          8u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_TimeSyncStatus_Tx] */
  { /*     9 */      FALSE,          9u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_udplog_Tx] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_UpperLayer
**********************************************************************************************************************/
/** 
  \var    SoAd_UpperLayer
  \brief  the upper layer configuration
  \details
  Element                       Description
  IfRxIndicationCbk             the callback Up_[SoAd][If]RxIndication
  IfTriggerTransmitCbk          the callback Up_[SoAd][If]TriggerTransmit
  IfTxConfirmationCbk           the callback Up_[SoAd][If]TxConfirmation
  TpCopyRxDataCbk               the callback Up_[SoAd][Tp]CopyRxData
  TpCopyRxDataConstCbk          the callback Up_[SoAd][Tp]CopyRxData with const data pointer
  TpCopyTxDataCbk               the callback Up_[SoAd][Tp]CopyTxData
  TpCopyTxDataConstCbk          the callback Up_[SoAd][Tp]CopyTxData with const data pointer
  TpRxIndicationCbk             the callback Up_[SoAd][Tp]RxIndication
  TpStartOfReceptionCbk         the callback Up_[SoAd][Tp]StartOfReception
  TpStartOfReceptionConstCbk    the callback Up_[SoAd][Tp]StartOfReception with const data pointer
  TpTxConfirmationCbk           the callback Up_[SoAd][Tp]TxConfirmation
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_UpperLayerType, SOAD_CONST) SoAd_UpperLayer[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IfRxIndicationCbk        IfTriggerTransmitCbk  IfTxConfirmationCbk        TpCopyRxDataCbk        TpCopyRxDataConstCbk  TpCopyTxDataCbk        TpCopyTxDataConstCbk  TpRxIndicationCbk        TpStartOfReceptionCbk        TpStartOfReceptionConstCbk  TpTxConfirmationCbk              Referable Keys */
  { /*     0 */ PduR_SoAdIfRxIndication, NULL_PTR            , PduR_SoAdIfTxConfirmation, NULL_PTR             , NULL_PTR            , NULL_PTR             , NULL_PTR            , NULL_PTR               , NULL_PTR                   , NULL_PTR                  , NULL_PTR                  },  /* [/ActiveEcuC/SoAd/PduR] */
  { /*     1 */ DoIP_SoAdIfRxIndication, NULL_PTR            , DoIP_SoAdIfTxConfirmation, DoIP_SoAdTpCopyRxData, NULL_PTR            , DoIP_SoAdTpCopyTxData, NULL_PTR            , DoIP_SoAdTpRxIndication, DoIP_SoAdTpStartOfReception, NULL_PTR                  , DoIP_SoAdTpTxConfirmation },  /* [/ActiveEcuC/SoAd/DoIP] */
  { /*     2 */ Sd_RxIndication        , NULL_PTR            , NULL_PTR                 , NULL_PTR             , NULL_PTR            , NULL_PTR             , NULL_PTR            , NULL_PTR               , NULL_PTR                   , NULL_PTR                  , NULL_PTR                  }   /* [/ActiveEcuC/SoAd/Sd] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_BestMatchSoConIdxList
**********************************************************************************************************************/
/** 
  \var    SoAd_BestMatchSoConIdxList
  \brief  the global list to store all matching socket connections if best match alogorithm is used
  \details
  Element     Description
  SoConIdx    the index of the 1:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_BestMatchSoConIdxListType, SOAD_VAR_NOINIT) SoAd_BestMatchSoConIdxList[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueDyn
  \brief  the management struct of all event queues
  \details
  Element    Description
  Idx        the index of oldest pending event.
  Lvl        the level of pending events
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_EventQueueDynUType, SOAD_VAR_NOINIT) SoAd_EventQueueDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [SoAdEventQueueTpRxSoCon] */
  /*     1 */  /* [SoAdEventQueueStateSoCon] */
  /*     2 */  /* [SoAdEventQueueTpTxSoCon] */
  /*     3 */  /* [SoAdEventQueueIfUdpPduRoute] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueFlag
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueFlag
  \brief  stores a flag for each handle index and event queue type to indicate if handle is in event queue (i.e. event active for handle)
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_EventQueueFlagType, SOAD_VAR_NOINIT) SoAd_EventQueueFlag[13];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueIfUdpPduRoute
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueIfUdpPduRoute
  \brief  indicates if a IF confirmation is pending on a UDP socket connection
  \details
  Element        Description
  PduRouteIdx    the index of the 0:1 relation pointing to SoAd_PduRoute
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_EventQueueIfUdpPduRouteUType, SOAD_VAR_NOINIT) SoAd_EventQueueIfUdpPduRoute;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd] */
  /*   ... */  /* [/ActiveEcuC/SoAd] */
  /*     6 */  /* [/ActiveEcuC/SoAd] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueStateSoCon
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueStateSoCon
  \brief  indicates if an event is active for socket connection state
  \details
  Element     Description
  SoConIdx    the index of the 0:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_EventQueueStateSoConUType, SOAD_VAR_NOINIT) SoAd_EventQueueStateSoCon;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd] */
  /*   ... */  /* [/ActiveEcuC/SoAd] */
  /*    12 */  /* [/ActiveEcuC/SoAd] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueTpRxSoCon
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueTpRxSoCon
  \brief  indicates if TP reception is active on a socket connection with TP SoAdSocketRoute
  \details
  Element     Description
  SoConIdx    the index of the 0:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_EventQueueTpRxSoConUType, SOAD_VAR_NOINIT) SoAd_EventQueueTpRxSoCon;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd] */
  /*     1 */  /* [/ActiveEcuC/SoAd] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueTpTxSoCon
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueTpTxSoCon
  \brief  indicates if TP transmission is active on a socket connection with TP SoAdPduRoute
  \details
  Element     Description
  SoConIdx    the index of the 0:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_EventQueueTpTxSoConUType, SOAD_VAR_NOINIT) SoAd_EventQueueTpTxSoCon;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd] */
  /*     1 */  /* [/ActiveEcuC/SoAd] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_IfRxBuffer
**********************************************************************************************************************/
/** 
  \var    SoAd_IfRxBuffer
  \brief  the reception buffer for IF-API
*/ 
#define SOAD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_IfRxBufferUType, SOAD_VAR_NOINIT) SoAd_IfRxBuffer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*   ... */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*    11 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */

#define SOAD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddrDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddrDyn
  \details
  Element        Description
  IpAddrState    the local IP address assignment state
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_LocalAddrDynType, SOAD_VAR_NOINIT) SoAd_LocalAddrDyn[8];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_192_168_1_123, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_untagged] */
  /*     1 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_untagged_Broadcast] */
  /*     2 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan1] */
  /*     3 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_Vlan1_Broadcast] */
  /*     4 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan23] */
  /*     5 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_Fixed_239_23_0_2] */
  /*     6 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_Multicast_Any_Vlan23] */
  /*     7 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpV4LocalAddr_TcpIpCtrl_Vlan23_Broadcast] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRouteDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRouteDyn
  \brief  the SoAdPduRoute management structs
  \details
  Element              Description
  PendingTxConfMain    indicates if transmission confirmation in main function context is pending
  PendingTxConfNum     the number of pending transmission confirmation
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_PduRouteDynUType, SOAD_VAR_NOINIT) SoAd_PduRouteDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA0_TX] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TCP_DATA1_TX] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_TEST_EQUIPMENT_REQUEST_Tx] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_DOIP_UDP_DISCOVERY_Tx] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_Ctrl_Tx] */
  /*     6 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_TCP_EcuStateTx] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx] */
  /*     8 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_TimeSyncStatus_Tx] */
  /*     9 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_udplog_Tx] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RcvRemAddr
**********************************************************************************************************************/
/** 
  \var    SoAd_RcvRemAddr
  \brief  stores remote address on reception
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_RcvRemAddrUType, SOAD_VAR_NOINIT) SoAd_RcvRemAddr;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RouteGrpSoConDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_RouteGrpSoConDyn
  \brief  the routing groups on the socket connections management struct
  \details
  Element    Description
  Enabled    the routing group state on the socket connection
  Sent       the state which indicates if a routing group transmission is done for the socket connection
  Trigger    the state which indicates if a routing group transmission is triggered for the socket connection
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_RouteGrpSoConDynType, SOAD_VAR_NOINIT) SoAd_RouteGrpSoConDyn[28];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_TCP_EcuStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     6 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_Sd_UDP_FaultInfoTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     8 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     9 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    10 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*    11 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    12 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_SD_UDP_SenStateTx/SoAdPduRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    13 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_RX_Fixed_10_23_0_33_47842/SoAdSocketRouteDest_VechicleInfo_001>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*    14 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*    15 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    16 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    17 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*    18 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    19 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_1/SoAdSocketRouteDest_VechicleSpeed>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    20 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_1/SoAdSocketRouteDest_VechicleSpeed_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */
  /*    21 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*    22 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    23 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    24 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*    25 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*    26 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Fixed_10_23_0_33_40000_2/SoAdSocketRouteDest_VechicleStatus>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*    27 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AM, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_SD_UDP_Multicast_Rx_Any_2/SoAdSocketRouteDest_VechicleStatus_multi>>/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxBufStructMgt
**********************************************************************************************************************/
/** 
  \var    SoAd_RxBufStructMgt
  \brief  the Rx buffer struct management struct
  \details
  Element              Description
  RxBufStructSegIdx    the index of the 1:1 relation pointing to SoAd_RxBufStructSeg
  RxBufStructSegLvl    the lvl of used SoAd_RxBufStructSegs
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_RxBufStructMgtUType, SOAD_VAR_NOINIT) SoAd_RxBufStructMgt;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxBufStructSeg
**********************************************************************************************************************/
/** 
  \var    SoAd_RxBufStructSeg
  \brief  the Rx buffer struct segment struct to store data segment
  \details
  Element    Description
  Len        the length of segment
  DataPtr    the pointer to segment data
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_RxBufStructSegUType, SOAD_VAR_NOINIT) SoAd_RxBufStructSeg;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxBufferConfigDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_RxBufferConfigDyn
  \brief  the management structs to handle reception buffer
  \details
  Element          Description
  IfRxBufferIdx    the index of the 0:1 relation pointing to SoAd_IfRxBuffer
  TpRxBufferIdx    the index of the 0:1 relation pointing to SoAd_TpRxBuffer
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_RxBufferConfigDynUType, SOAD_VAR_NOINIT) SoAd_RxBufferConfigDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxMgt
**********************************************************************************************************************/
/** 
  \var    SoAd_RxMgt
  \brief  the Rx management structs
  \details
  Element               Description
  RxBytesPending        the length of pending data to be received
  CancelRequested       indicates if reception cancellation is requested
  SocketRouteDestIdx    the index of the 1:1 relation pointing to SoAd_SocketRouteDest
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_RxMgtUType, SOAD_VAR_NOINIT) SoAd_RxMgt;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*     6 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     8 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */
  /*     9 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConDyn
  \brief  the socket connection managment structs
  \details
  Element             Description
  OpenCloseCounter    the open and close sequence counter
  Abort               indicates if abort is requested
  CloseMode           the mode of socket connection
  Mode                the mode of socket connection
  RemAddrDyn          the remote address for each socket connection
  RemAddrStateDyn     the remote address state on socket connection
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_SoConDynType, SOAD_VAR_NOINIT) SoAd_SoConDyn[13];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0>>DATA] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1>>DATA] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490] */
  /*     6 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote1, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort>>DATA] */
  /*     8 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842] */
  /*     9 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000] */
  /*    10 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000] */
  /*    11 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000] */
  /*    12 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000/SC_UDP_Multicast_Rx_Any, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketDyn
  \brief  the socket management structs
  \details
  Element             Description
  SkipBytes           the number of bytes to be skipped
  SoConTxActiveIdx    the index of the 0:1 relation pointing to SoAd_SoCon
  LocalPort           the local port
  SocketId            the socket identifier
  State               the socket state
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_SocketDynType, SOAD_VAR_NOINIT) SoAd_SocketDyn[12];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_192_168_1_123] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0>>DATA, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1>>DATA, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  /*     6 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_Multicast_Rx_239_23_0_2_30490, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_Fixed_239_23_0_2] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  /*     8 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort>>DATA, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  /*     9 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  /*    10 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_23_0_23] */
  /*    11 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_Multicast_Any_Vlan23] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TcpTxQueueData
**********************************************************************************************************************/
/** 
  \var    SoAd_TcpTxQueueData
  \brief  the Tx TCP queue elements
  \details
  Element        Description
  Len            the length of the queue element
  PduRouteIdx    the index of the 1:1 relation pointing to SoAd_PduRoute
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TcpTxQueueDataUType, SOAD_VAR_NOINIT) SoAd_TcpTxQueueData;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TcpTxQueueMgt
**********************************************************************************************************************/
/** 
  \var    SoAd_TcpTxQueueMgt
  \brief  the Tx TCP queue management structs
  \details
  Element              Description
  TotLen               the total length of all used elements
  Lvl                  the level of used elements
  TcpTxQueueDataIdx    the index of the 1:1 relation pointing to SoAd_TcpTxQueueData
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TcpTxQueueMgtUType, SOAD_VAR_NOINIT) SoAd_TcpTxQueueMgt;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TimeoutListDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_TimeoutListDyn
  \brief  the management struct of all timeout lists
  \details
  Element    Description
  Lvl        the level of pending timeouts
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TimeoutListDynUType, SOAD_VAR_NOINIT) SoAd_TimeoutListDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [SoAdTimeoutListUdpAlive] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TimeoutListUdpAlive
**********************************************************************************************************************/
/** 
  \var    SoAd_TimeoutListUdpAlive
  \brief  the timeout list for UDP Alive supervision timeout
  \details
  Element     Description
  Timeout     the timeout value
  SoConIdx    the index of the 0:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TimeoutListUdpAliveUType, SOAD_VAR_NOINIT) SoAd_TimeoutListUdpAlive;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd] */
  /*   ... */  /* [/ActiveEcuC/SoAd] */
  /*     3 */  /* [/ActiveEcuC/SoAd] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TimeoutListUdpAliveMap
**********************************************************************************************************************/
/** 
  \var    SoAd_TimeoutListUdpAliveMap
  \brief  maps all socket connections to the timeout list index for UDP Alive supervision timeout if timeout is running
  \details
  Element                   Description
  TimeoutListUdpAliveIdx    the index of the 0:1 relation pointing to SoAd_TimeoutListUdpAlive
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TimeoutListUdpAliveMapUType, SOAD_VAR_NOINIT) SoAd_TimeoutListUdpAliveMap;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd] */
  /*   ... */  /* [/ActiveEcuC/SoAd] */
  /*    12 */  /* [/ActiveEcuC/SoAd] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TpRxBuffer
**********************************************************************************************************************/
/** 
  \var    SoAd_TpRxBuffer
  \brief  the reception buffer for TP-API
*/ 
#define SOAD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TpRxBufferUType, SOAD_VAR_NOINIT) SoAd_TpRxBuffer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*   ... */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_23_47842/SC_TCP_TX_Any_IP_DynamincPort_001] */

#define SOAD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TxMgt
**********************************************************************************************************************/
/** 
  \var    SoAd_TxMgt
  \brief  the Tx management structs
  \details
  Element            Description
  TxBytesLen         the length of data to be transmitted
  TxBytesPending     the length of pending data to be transmitted
  CancelRequested    indicates if transmission cancellation is requested
  PduRouteDestIdx    the index of the 1:1 relation pointing to SoAd_PduRouteDest
  TxBufPtr           the pointer to transmission data buffer
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TxMgtUType, SOAD_VAR_NOINIT) SoAd_TxMgt;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_192_168_1_123_4567/SoAdSocketConnection] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_0] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400/SoAdSocketConnection_TCP_DhcpV4_Fixed_169_254_1_33_13400_Remote_Any_1] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_Broad__255_255_255_255_13400_remote] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_UDP_DHCP_169_254_1_33_13400/SoAdSocketConnection_DOIP_UDP_ANY_remote] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_Ctrl_UDP_fixed_10_23_0_33_30490/SC_SD_Ctrl_UDP_Any_DynamicPort_Remote] */
  /*     6 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_23_47843/SC_TCP_TX_Any_IP_DynamincPort] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_0] */
  /*     8 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_IP_Any_DynamicPort_1] */
  /*     9 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixe_10_23_0_33_40000/SC_UDP_Multicast_Fixed_239_23_0_1_40000_remote] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PCConfig
**********************************************************************************************************************/
/** 
  \var    SoAd_PCConfig
  \details
  Element                                     Description
  BestMatchSoConIdxList                       the pointer to SoAd_BestMatchSoConIdxList
  DhcpEventCbk                                the pointer to SoAd_DhcpEventCbk
  EventQueue                                  the pointer to SoAd_EventQueue
  EventQueueDyn                               the pointer to SoAd_EventQueueDyn
  EventQueueFlag                              the pointer to SoAd_EventQueueFlag
  EventQueueIdent                             the pointer to SoAd_EventQueueIdent
  EventQueueIfTxRouteGrp                      the pointer to SoAd_EventQueueIfTxRouteGrp
  EventQueueIfUdpPduRoute                     the pointer to SoAd_EventQueueIfUdpPduRoute
  EventQueueLocalAddr                         the pointer to SoAd_EventQueueLocalAddr
  EventQueueSocketIdx                         the pointer to SoAd_EventQueueSocketIdx
  EventQueueStateSoCon                        the pointer to SoAd_EventQueueStateSoCon
  EventQueueTcpTxSoCon                        the pointer to SoAd_EventQueueTcpTxSoCon
  EventQueueTpRxSoCon                         the pointer to SoAd_EventQueueTpRxSoCon
  EventQueueTpTxSoCon                         the pointer to SoAd_EventQueueTpTxSoCon
  IfRxBuffer                                  the pointer to SoAd_IfRxBuffer
  IpFragBuf                                   the pointer to SoAd_IpFragBuf
  IpFragBufConfig                             the pointer to SoAd_IpFragBufConfig
  IpFragBufConfigDyn                          the pointer to SoAd_IpFragBufConfigDyn
  IpFragMgt                                   the pointer to SoAd_IpFragMgt
  LocalAddr                                   the pointer to SoAd_LocalAddr
  LocalAddrByTcpIpCtrlInd                     the pointer to SoAd_LocalAddrByTcpIpCtrlInd
  LocalAddrDyn                                the pointer to SoAd_LocalAddrDyn
  LocalAddrIdMap                              the pointer to SoAd_LocalAddrIdMap
  LocalIpAddrAssignmentChgCbk                 the pointer to SoAd_LocalIpAddrAssignmentChgCbk
  LocalIpAddrAssignmentChgCbkInd              the pointer to SoAd_LocalIpAddrAssignmentChgCbkInd
  MetaDataRxBuf                               the pointer to SoAd_MetaDataRxBuf
  NPduUdpTx                                   the pointer to SoAd_NPduUdpTx
  NPduUdpTxBuffer                             the pointer to SoAd_NPduUdpTxBuffer
  NPduUdpTxDyn                                the pointer to SoAd_NPduUdpTxDyn
  NPduUdpTxQueue                              the pointer to SoAd_NPduUdpTxQueue
  PduRoute                                    the pointer to SoAd_PduRoute
  PduRouteDest                                the pointer to SoAd_PduRouteDest
  PduRouteDestBySoConInd                      the pointer to SoAd_PduRouteDestBySoConInd
  PduRouteDestInd                             the pointer to SoAd_PduRouteDestInd
  PduRouteDyn                                 the pointer to SoAd_PduRouteDyn
  RcvRemAddr                                  the pointer to SoAd_RcvRemAddr
  RemAddrIpV4                                 the pointer to SoAd_RemAddrIpV4
  RemAddrIpV6                                 the pointer to SoAd_RemAddrIpV6
  RouteGrp                                    the pointer to SoAd_RouteGrp
  RouteGrpIdMap                               the pointer to SoAd_RouteGrpIdMap
  RouteGrpSoCon                               the pointer to SoAd_RouteGrpSoCon
  RouteGrpSoConByPduRouteDestInd              the pointer to SoAd_RouteGrpSoConByPduRouteDestInd
  RouteGrpSoConBySocketRouteDestInd           the pointer to SoAd_RouteGrpSoConBySocketRouteDestInd
  RouteGrpSoConDyn                            the pointer to SoAd_RouteGrpSoConDyn
  RxBufStructMgt                              the pointer to SoAd_RxBufStructMgt
  RxBufStructSeg                              the pointer to SoAd_RxBufStructSeg
  RxBufferConfig                              the pointer to SoAd_RxBufferConfig
  RxBufferConfigDyn                           the pointer to SoAd_RxBufferConfigDyn
  RxMgt                                       the pointer to SoAd_RxMgt
  RxPduIdIdMap                                the pointer to SoAd_RxPduIdIdMap
  ShutdownFinishedCbk                         the pointer to SoAd_ShutdownFinishedCbk
  SoCon                                       the pointer to SoAd_SoCon
  SoConDyn                                    the pointer to SoAd_SoConDyn
  SoConGrp                                    the pointer to SoAd_SoConGrp
  SoConMap                                    the pointer to SoAd_SoConMap
  SoConModeChgCbk                             the pointer to SoAd_SoConModeChgCbk
  SoConModeChgCbkInd                          the pointer to SoAd_SoConModeChgCbkInd
  Socket                                      the pointer to SoAd_Socket
  SocketDyn                                   the pointer to SoAd_SocketDyn
  SocketReportErrorCbk                        the pointer to SoAd_SocketReportErrorCbk
  SocketRoute                                 the pointer to SoAd_SocketRoute
  SocketRouteDest                             the pointer to SoAd_SocketRouteDest
  SocketRouteInd                              the pointer to SoAd_SocketRouteInd
  SocketTcp                                   the pointer to SoAd_SocketTcp
  SocketUdp                                   the pointer to SoAd_SocketUdp
  TcpIpCtrl                                   the pointer to SoAd_TcpIpCtrl
  TcpKeepAliveGloballyEnabled                 the pointer to SoAd_TcpKeepAliveGloballyEnabled
  TcpTlsSocketCreatedNotificationCbk          the pointer to SoAd_TcpTlsSocketCreatedNotificationCbk
  TcpTxQueue                                  the pointer to SoAd_TcpTxQueue
  TcpTxQueueData                              the pointer to SoAd_TcpTxQueueData
  TcpTxQueueMgt                               the pointer to SoAd_TcpTxQueueMgt
  TimeoutListDyn                              the pointer to SoAd_TimeoutListDyn
  TimeoutListIdent                            the pointer to SoAd_TimeoutListIdent
  TimeoutListNPduUdpTx                        the pointer to SoAd_TimeoutListNPduUdpTx
  TimeoutListNPduUdpTxMap                     the pointer to SoAd_TimeoutListNPduUdpTxMap
  TimeoutListUdpAlive                         the pointer to SoAd_TimeoutListUdpAlive
  TimeoutListUdpAliveMap                      the pointer to SoAd_TimeoutListUdpAliveMap
  TlsConfig                                   the pointer to SoAd_TlsConfig
  TpRxBuffer                                  the pointer to SoAd_TpRxBuffer
  TpTxBuffer                                  the pointer to SoAd_TpTxBuffer
  TpTxBufferConfig                            the pointer to SoAd_TpTxBufferConfig
  TpTxBufferConfigDyn                         the pointer to SoAd_TpTxBufferConfigDyn
  TriggerBuf                                  the pointer to SoAd_TriggerBuf
  TriggerBufConfig                            the pointer to SoAd_TriggerBufConfig
  TriggerBufConfigDyn                         the pointer to SoAd_TriggerBufConfigDyn
  TxMgt                                       the pointer to SoAd_TxMgt
  TxPduIdMap                                  the pointer to SoAd_TxPduIdMap
  UpperLayer                                  the pointer to SoAd_UpperLayer
  MaxIfRouteGrpTransmitPduSize                the maximum length of all PDUs which can be sent via routing group transmit
  SizeOfBestMatchSoConIdxList                 the number of accomplishable value elements in SoAd_BestMatchSoConIdxList
  SizeOfDhcpEventCbk                          the number of accomplishable value elements in SoAd_DhcpEventCbk
  SizeOfEventQueue                            the number of accomplishable value elements in SoAd_EventQueue
  SizeOfEventQueueFlag                        the number of accomplishable value elements in SoAd_EventQueueFlag
  SizeOfEventQueueIdent                       the number of accomplishable value elements in SoAd_EventQueueIdent
  SizeOfEventQueueIfTxRouteGrp                the number of accomplishable value elements in SoAd_EventQueueIfTxRouteGrp
  SizeOfEventQueueIfUdpPduRoute               the number of accomplishable value elements in SoAd_EventQueueIfUdpPduRoute
  SizeOfEventQueueLocalAddr                   the number of accomplishable value elements in SoAd_EventQueueLocalAddr
  SizeOfEventQueueSocketIdx                   the number of accomplishable value elements in SoAd_EventQueueSocketIdx
  SizeOfEventQueueStateSoCon                  the number of accomplishable value elements in SoAd_EventQueueStateSoCon
  SizeOfEventQueueTcpTxSoCon                  the number of accomplishable value elements in SoAd_EventQueueTcpTxSoCon
  SizeOfEventQueueTpRxSoCon                   the number of accomplishable value elements in SoAd_EventQueueTpRxSoCon
  SizeOfEventQueueTpTxSoCon                   the number of accomplishable value elements in SoAd_EventQueueTpTxSoCon
  SizeOfIfRxBuffer                            the number of accomplishable value elements in SoAd_IfRxBuffer
  SizeOfIpFragBuf                             the number of accomplishable value elements in SoAd_IpFragBuf
  SizeOfIpFragBufConfig                       the number of accomplishable value elements in SoAd_IpFragBufConfig
  SizeOfIpFragMgt                             the number of accomplishable value elements in SoAd_IpFragMgt
  SizeOfLocalAddr                             the number of accomplishable value elements in SoAd_LocalAddr
  SizeOfLocalAddrByTcpIpCtrlInd               the number of accomplishable value elements in SoAd_LocalAddrByTcpIpCtrlInd
  SizeOfLocalAddrIdMap                        the number of accomplishable value elements in SoAd_LocalAddrIdMap
  SizeOfLocalIpAddrAssignmentChgCbk           the number of accomplishable value elements in SoAd_LocalIpAddrAssignmentChgCbk
  SizeOfLocalIpAddrAssignmentChgCbkInd        the number of accomplishable value elements in SoAd_LocalIpAddrAssignmentChgCbkInd
  SizeOfMetaDataRxBuf                         the number of accomplishable value elements in SoAd_MetaDataRxBuf
  SizeOfNPduUdpTx                             the number of accomplishable value elements in SoAd_NPduUdpTx
  SizeOfNPduUdpTxBuffer                       the number of accomplishable value elements in SoAd_NPduUdpTxBuffer
  SizeOfNPduUdpTxQueue                        the number of accomplishable value elements in SoAd_NPduUdpTxQueue
  SizeOfPduRoute                              the number of accomplishable value elements in SoAd_PduRoute
  SizeOfPduRouteDest                          the number of accomplishable value elements in SoAd_PduRouteDest
  SizeOfPduRouteDestBySoConInd                the number of accomplishable value elements in SoAd_PduRouteDestBySoConInd
  SizeOfPduRouteDestInd                       the number of accomplishable value elements in SoAd_PduRouteDestInd
  SizeOfRcvRemAddr                            the number of accomplishable value elements in SoAd_RcvRemAddr
  SizeOfRemAddrIpV4                           the number of accomplishable value elements in SoAd_RemAddrIpV4
  SizeOfRemAddrIpV6                           the number of accomplishable value elements in SoAd_RemAddrIpV6
  SizeOfRouteGrp                              the number of accomplishable value elements in SoAd_RouteGrp
  SizeOfRouteGrpIdMap                         the number of accomplishable value elements in SoAd_RouteGrpIdMap
  SizeOfRouteGrpSoCon                         the number of accomplishable value elements in SoAd_RouteGrpSoCon
  SizeOfRouteGrpSoConByPduRouteDestInd        the number of accomplishable value elements in SoAd_RouteGrpSoConByPduRouteDestInd
  SizeOfRouteGrpSoConBySocketRouteDestInd     the number of accomplishable value elements in SoAd_RouteGrpSoConBySocketRouteDestInd
  SizeOfRxBufStructMgt                        the number of accomplishable value elements in SoAd_RxBufStructMgt
  SizeOfRxBufStructSeg                        the number of accomplishable value elements in SoAd_RxBufStructSeg
  SizeOfRxBufferConfig                        the number of accomplishable value elements in SoAd_RxBufferConfig
  SizeOfRxMgt                                 the number of accomplishable value elements in SoAd_RxMgt
  SizeOfRxPduIdIdMap                          the number of accomplishable value elements in SoAd_RxPduIdIdMap
  SizeOfShutdownFinishedCbk                   the number of accomplishable value elements in SoAd_ShutdownFinishedCbk
  SizeOfSoCon                                 the number of accomplishable value elements in SoAd_SoCon
  SizeOfSoConGrp                              the number of accomplishable value elements in SoAd_SoConGrp
  SizeOfSoConMap                              the number of accomplishable value elements in SoAd_SoConMap
  SizeOfSoConModeChgCbk                       the number of accomplishable value elements in SoAd_SoConModeChgCbk
  SizeOfSoConModeChgCbkInd                    the number of accomplishable value elements in SoAd_SoConModeChgCbkInd
  SizeOfSocket                                the number of accomplishable value elements in SoAd_Socket
  SizeOfSocketReportErrorCbk                  the number of accomplishable value elements in SoAd_SocketReportErrorCbk
  SizeOfSocketRoute                           the number of accomplishable value elements in SoAd_SocketRoute
  SizeOfSocketRouteDest                       the number of accomplishable value elements in SoAd_SocketRouteDest
  SizeOfSocketRouteInd                        the number of accomplishable value elements in SoAd_SocketRouteInd
  SizeOfSocketTcp                             the number of accomplishable value elements in SoAd_SocketTcp
  SizeOfSocketUdp                             the number of accomplishable value elements in SoAd_SocketUdp
  SizeOfTcpIpCtrl                             the number of accomplishable value elements in SoAd_TcpIpCtrl
  SizeOfTcpKeepAliveGloballyEnabled           the number of accomplishable value elements in SoAd_TcpKeepAliveGloballyEnabled
  SizeOfTcpTlsSocketCreatedNotificationCbk    the number of accomplishable value elements in SoAd_TcpTlsSocketCreatedNotificationCbk
  SizeOfTcpTxQueue                            the number of accomplishable value elements in SoAd_TcpTxQueue
  SizeOfTcpTxQueueData                        the number of accomplishable value elements in SoAd_TcpTxQueueData
  SizeOfTimeoutListDyn                        the number of accomplishable value elements in SoAd_TimeoutListDyn
  SizeOfTimeoutListIdent                      the number of accomplishable value elements in SoAd_TimeoutListIdent
  SizeOfTimeoutListNPduUdpTx                  the number of accomplishable value elements in SoAd_TimeoutListNPduUdpTx
  SizeOfTimeoutListNPduUdpTxMap               the number of accomplishable value elements in SoAd_TimeoutListNPduUdpTxMap
  SizeOfTimeoutListUdpAlive                   the number of accomplishable value elements in SoAd_TimeoutListUdpAlive
  SizeOfTimeoutListUdpAliveMap                the number of accomplishable value elements in SoAd_TimeoutListUdpAliveMap
  SizeOfTlsConfig                             the number of accomplishable value elements in SoAd_TlsConfig
  SizeOfTpRxBuffer                            the number of accomplishable value elements in SoAd_TpRxBuffer
  SizeOfTpTxBuffer                            the number of accomplishable value elements in SoAd_TpTxBuffer
  SizeOfTpTxBufferConfig                      the number of accomplishable value elements in SoAd_TpTxBufferConfig
  SizeOfTriggerBuf                            the number of accomplishable value elements in SoAd_TriggerBuf
  SizeOfTriggerBufConfig                      the number of accomplishable value elements in SoAd_TriggerBufConfig
  SizeOfTxMgt                                 the number of accomplishable value elements in SoAd_TxMgt
  SizeOfTxPduIdMap                            the number of accomplishable value elements in SoAd_TxPduIdMap
  SizeOfUpperLayer                            the number of accomplishable value elements in SoAd_UpperLayer
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_PCConfigsType, SOAD_CONST) SoAd_PCConfig = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  { /* Index: 0 Keys: [Config] */
      SoAd_BestMatchSoConIdxList                /**< the pointer to SoAd_BestMatchSoConIdxList */
    , NULL_PTR                                  /**< the pointer to SoAd_DhcpEventCbk */
    , SoAd_EventQueue                           /**< the pointer to SoAd_EventQueue */
    , SoAd_EventQueueDyn.raw                    /**< the pointer to SoAd_EventQueueDyn */
    , SoAd_EventQueueFlag                       /**< the pointer to SoAd_EventQueueFlag */
    , SoAd_EventQueueIdent                      /**< the pointer to SoAd_EventQueueIdent */
    , NULL_PTR                                  /**< the pointer to SoAd_EventQueueIfTxRouteGrp */
    , SoAd_EventQueueIfUdpPduRoute.raw          /**< the pointer to SoAd_EventQueueIfUdpPduRoute */
    , NULL_PTR                                  /**< the pointer to SoAd_EventQueueLocalAddr */
    , NULL_PTR                                  /**< the pointer to SoAd_EventQueueSocketIdx */
    , SoAd_EventQueueStateSoCon.raw             /**< the pointer to SoAd_EventQueueStateSoCon */
    , NULL_PTR                                  /**< the pointer to SoAd_EventQueueTcpTxSoCon */
    , SoAd_EventQueueTpRxSoCon.raw              /**< the pointer to SoAd_EventQueueTpRxSoCon */
    , SoAd_EventQueueTpTxSoCon.raw              /**< the pointer to SoAd_EventQueueTpTxSoCon */
    , SoAd_IfRxBuffer.raw                       /**< the pointer to SoAd_IfRxBuffer */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragBuf */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragBufConfig */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragBufConfigDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragMgt */
    , SoAd_LocalAddr                            /**< the pointer to SoAd_LocalAddr */
    , SoAd_LocalAddrByTcpIpCtrlInd              /**< the pointer to SoAd_LocalAddrByTcpIpCtrlInd */
    , SoAd_LocalAddrDyn                         /**< the pointer to SoAd_LocalAddrDyn */
    , SoAd_LocalAddrIdMap                       /**< the pointer to SoAd_LocalAddrIdMap */
    , SoAd_LocalIpAddrAssignmentChgCbk          /**< the pointer to SoAd_LocalIpAddrAssignmentChgCbk */
    , SoAd_LocalIpAddrAssignmentChgCbkInd       /**< the pointer to SoAd_LocalIpAddrAssignmentChgCbkInd */
    , NULL_PTR                                  /**< the pointer to SoAd_MetaDataRxBuf */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTx */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTxBuffer */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTxDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTxQueue */
    , SoAd_PduRoute                             /**< the pointer to SoAd_PduRoute */
    , SoAd_PduRouteDest                         /**< the pointer to SoAd_PduRouteDest */
    , SoAd_PduRouteDestBySoConInd               /**< the pointer to SoAd_PduRouteDestBySoConInd */
    , SoAd_PduRouteDestInd                      /**< the pointer to SoAd_PduRouteDestInd */
    , SoAd_PduRouteDyn.raw                      /**< the pointer to SoAd_PduRouteDyn */
    , SoAd_RcvRemAddr.raw                       /**< the pointer to SoAd_RcvRemAddr */
    , SoAd_RemAddrIpV4                          /**< the pointer to SoAd_RemAddrIpV4 */
    , NULL_PTR                                  /**< the pointer to SoAd_RemAddrIpV6 */
    , SoAd_RouteGrp                             /**< the pointer to SoAd_RouteGrp */
    , SoAd_RouteGrpIdMap                        /**< the pointer to SoAd_RouteGrpIdMap */
    , SoAd_RouteGrpSoCon                        /**< the pointer to SoAd_RouteGrpSoCon */
    , SoAd_RouteGrpSoConByPduRouteDestInd       /**< the pointer to SoAd_RouteGrpSoConByPduRouteDestInd */
    , SoAd_RouteGrpSoConBySocketRouteDestInd    /**< the pointer to SoAd_RouteGrpSoConBySocketRouteDestInd */
    , SoAd_RouteGrpSoConDyn                     /**< the pointer to SoAd_RouteGrpSoConDyn */
    , SoAd_RxBufStructMgt.raw                   /**< the pointer to SoAd_RxBufStructMgt */
    , SoAd_RxBufStructSeg.raw                   /**< the pointer to SoAd_RxBufStructSeg */
    , SoAd_RxBufferConfig                       /**< the pointer to SoAd_RxBufferConfig */
    , SoAd_RxBufferConfigDyn.raw                /**< the pointer to SoAd_RxBufferConfigDyn */
    , SoAd_RxMgt.raw                            /**< the pointer to SoAd_RxMgt */
    , SoAd_RxPduIdIdMap                         /**< the pointer to SoAd_RxPduIdIdMap */
    , NULL_PTR                                  /**< the pointer to SoAd_ShutdownFinishedCbk */
    , SoAd_SoCon                                /**< the pointer to SoAd_SoCon */
    , SoAd_SoConDyn                             /**< the pointer to SoAd_SoConDyn */
    , SoAd_SoConGrp                             /**< the pointer to SoAd_SoConGrp */
    , SoAd_SoConMap                             /**< the pointer to SoAd_SoConMap */
    , SoAd_SoConModeChgCbk                      /**< the pointer to SoAd_SoConModeChgCbk */
    , SoAd_SoConModeChgCbkInd                   /**< the pointer to SoAd_SoConModeChgCbkInd */
    , SoAd_Socket                               /**< the pointer to SoAd_Socket */
    , SoAd_SocketDyn                            /**< the pointer to SoAd_SocketDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_SocketReportErrorCbk */
    , SoAd_SocketRoute                          /**< the pointer to SoAd_SocketRoute */
    , SoAd_SocketRouteDest                      /**< the pointer to SoAd_SocketRouteDest */
    , SoAd_SocketRouteInd                       /**< the pointer to SoAd_SocketRouteInd */
    , SoAd_SocketTcp                            /**< the pointer to SoAd_SocketTcp */
    , SoAd_SocketUdp                            /**< the pointer to SoAd_SocketUdp */
    , SoAd_TcpIpCtrl                            /**< the pointer to SoAd_TcpIpCtrl */
    , SoAd_TcpKeepAliveGloballyEnabled          /**< the pointer to SoAd_TcpKeepAliveGloballyEnabled */
    , NULL_PTR                                  /**< the pointer to SoAd_TcpTlsSocketCreatedNotificationCbk */
    , SoAd_TcpTxQueue                           /**< the pointer to SoAd_TcpTxQueue */
    , SoAd_TcpTxQueueData.raw                   /**< the pointer to SoAd_TcpTxQueueData */
    , SoAd_TcpTxQueueMgt.raw                    /**< the pointer to SoAd_TcpTxQueueMgt */
    , SoAd_TimeoutListDyn.raw                   /**< the pointer to SoAd_TimeoutListDyn */
    , SoAd_TimeoutListIdent                     /**< the pointer to SoAd_TimeoutListIdent */
    , NULL_PTR                                  /**< the pointer to SoAd_TimeoutListNPduUdpTx */
    , NULL_PTR                                  /**< the pointer to SoAd_TimeoutListNPduUdpTxMap */
    , SoAd_TimeoutListUdpAlive.raw              /**< the pointer to SoAd_TimeoutListUdpAlive */
    , SoAd_TimeoutListUdpAliveMap.raw           /**< the pointer to SoAd_TimeoutListUdpAliveMap */
    , NULL_PTR                                  /**< the pointer to SoAd_TlsConfig */
    , SoAd_TpRxBuffer.raw                       /**< the pointer to SoAd_TpRxBuffer */
    , NULL_PTR                                  /**< the pointer to SoAd_TpTxBuffer */
    , NULL_PTR                                  /**< the pointer to SoAd_TpTxBufferConfig */
    , NULL_PTR                                  /**< the pointer to SoAd_TpTxBufferConfigDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_TriggerBuf */
    , NULL_PTR                                  /**< the pointer to SoAd_TriggerBufConfig */
    , NULL_PTR                                  /**< the pointer to SoAd_TriggerBufConfigDyn */
    , SoAd_TxMgt.raw                            /**< the pointer to SoAd_TxMgt */
    , SoAd_TxPduIdMap                           /**< the pointer to SoAd_TxPduIdMap */
    , SoAd_UpperLayer                           /**< the pointer to SoAd_UpperLayer */
    , 0u
    , 3u                                        /**< the number of elements in SoAd_BestMatchSoConIdxList */
    , 0u                                        /**< the number of elements in SoAd_DhcpEventCbk */
    , 4u                                        /**< the number of elements in SoAd_EventQueue */
    , 13u                                       /**< the number of elements in SoAd_EventQueueFlag */
    , 1u                                        /**< the number of elements in SoAd_EventQueueIdent */
    , 0u                                        /**< the number of elements in SoAd_EventQueueIfTxRouteGrp */
    , 7u                                        /**< the number of elements in SoAd_EventQueueIfUdpPduRoute */
    , 0u                                        /**< the number of elements in SoAd_EventQueueLocalAddr */
    , 0u                                        /**< the number of elements in SoAd_EventQueueSocketIdx */
    , 13u                                       /**< the number of elements in SoAd_EventQueueStateSoCon */
    , 0u                                        /**< the number of elements in SoAd_EventQueueTcpTxSoCon */
    , 2u                                        /**< the number of elements in SoAd_EventQueueTpRxSoCon */
    , 2u                                        /**< the number of elements in SoAd_EventQueueTpTxSoCon */
    , 12u                                       /**< the number of elements in SoAd_IfRxBuffer */
    , 0u                                        /**< the number of elements in SoAd_IpFragBuf */
    , 0u                                        /**< the number of elements in SoAd_IpFragBufConfig */
    , 0u                                        /**< the number of elements in SoAd_IpFragMgt */
    , 8u                                        /**< the number of elements in SoAd_LocalAddr */
    , 3u                                        /**< the number of elements in SoAd_LocalAddrByTcpIpCtrlInd */
    , 8u                                        /**< the number of elements in SoAd_LocalAddrIdMap */
    , 2u                                        /**< the number of elements in SoAd_LocalIpAddrAssignmentChgCbk */
    , 12u                                       /**< the number of elements in SoAd_LocalIpAddrAssignmentChgCbkInd */
    , 0u                                        /**< the number of elements in SoAd_MetaDataRxBuf */
    , 0u                                        /**< the number of elements in SoAd_NPduUdpTx */
    , 0u                                        /**< the number of elements in SoAd_NPduUdpTxBuffer */
    , 0u                                        /**< the number of elements in SoAd_NPduUdpTxQueue */
    , 10u                                       /**< the number of elements in SoAd_PduRoute */
    , 14u                                       /**< the number of elements in SoAd_PduRouteDest */
    , 14u                                       /**< the number of elements in SoAd_PduRouteDestBySoConInd */
    , 13u                                       /**< the number of elements in SoAd_PduRouteDestInd */
    , 2u                                        /**< the number of elements in SoAd_RcvRemAddr */
    , 13u                                       /**< the number of elements in SoAd_RemAddrIpV4 */
    , 0u                                        /**< the number of elements in SoAd_RemAddrIpV6 */
    , 10u                                       /**< the number of elements in SoAd_RouteGrp */
    , 10u                                       /**< the number of elements in SoAd_RouteGrpIdMap */
    , 28u                                       /**< the number of elements in SoAd_RouteGrpSoCon */
    , 13u                                       /**< the number of elements in SoAd_RouteGrpSoConByPduRouteDestInd */
    , 15u                                       /**< the number of elements in SoAd_RouteGrpSoConBySocketRouteDestInd */
    , 3u                                        /**< the number of elements in SoAd_RxBufStructMgt */
    , 6u                                        /**< the number of elements in SoAd_RxBufStructSeg */
    , 1u                                        /**< the number of elements in SoAd_RxBufferConfig */
    , 10u                                       /**< the number of elements in SoAd_RxMgt */
    , 10u                                       /**< the number of elements in SoAd_RxPduIdIdMap */
    , 0u                                        /**< the number of elements in SoAd_ShutdownFinishedCbk */
    , 13u                                       /**< the number of elements in SoAd_SoCon */
    , 9u                                        /**< the number of elements in SoAd_SoConGrp */
    , 13u                                       /**< the number of elements in SoAd_SoConMap */
    , 2u                                        /**< the number of elements in SoAd_SoConModeChgCbk */
    , 12u                                       /**< the number of elements in SoAd_SoConModeChgCbkInd */
    , 12u                                       /**< the number of elements in SoAd_Socket */
    , 0u                                        /**< the number of elements in SoAd_SocketReportErrorCbk */
    , 14u                                       /**< the number of elements in SoAd_SocketRoute */
    , 14u                                       /**< the number of elements in SoAd_SocketRouteDest */
    , 15u                                       /**< the number of elements in SoAd_SocketRouteInd */
    , 3u                                        /**< the number of elements in SoAd_SocketTcp */
    , 6u                                        /**< the number of elements in SoAd_SocketUdp */
    , 3u                                        /**< the number of elements in SoAd_TcpIpCtrl */
    , 1u                                        /**< the number of elements in SoAd_TcpKeepAliveGloballyEnabled */
    , 0u                                        /**< the number of elements in SoAd_TcpTlsSocketCreatedNotificationCbk */
    , 4u                                        /**< the number of elements in SoAd_TcpTxQueue */
    , 6u                                        /**< the number of elements in SoAd_TcpTxQueueData */
    , 1u                                        /**< the number of elements in SoAd_TimeoutListDyn */
    , 1u                                        /**< the number of elements in SoAd_TimeoutListIdent */
    , 0u                                        /**< the number of elements in SoAd_TimeoutListNPduUdpTx */
    , 0u                                        /**< the number of elements in SoAd_TimeoutListNPduUdpTxMap */
    , 4u                                        /**< the number of elements in SoAd_TimeoutListUdpAlive */
    , 13u                                       /**< the number of elements in SoAd_TimeoutListUdpAliveMap */
    , 0u                                        /**< the number of elements in SoAd_TlsConfig */
    , 8u                                        /**< the number of elements in SoAd_TpRxBuffer */
    , 0u                                        /**< the number of elements in SoAd_TpTxBuffer */
    , 0u                                        /**< the number of elements in SoAd_TpTxBufferConfig */
    , 0u                                        /**< the number of elements in SoAd_TriggerBuf */
    , 0u                                        /**< the number of elements in SoAd_TriggerBufConfig */
    , 10u                                       /**< the number of elements in SoAd_TxMgt */
    , 10u                                       /**< the number of elements in SoAd_TxPduIdMap */
    , 3u                                        /**< the number of elements in SoAd_UpperLayer */
  }
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
 *  END OF FILE: SoAd_Lcfg.c
 *********************************************************************************************************************/

