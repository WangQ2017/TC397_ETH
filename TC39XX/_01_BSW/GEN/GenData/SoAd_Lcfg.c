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
 *   Generation Time: 2025-12-14 17:03:56
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
#include "UdpNm_Cbk.h" 


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
CONST(SoAd_EventQueueType, SOAD_CONST) SoAd_EventQueue[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Limit  BitPattern                                           Referable Keys */
  { /*     0 */    2u, SOAD_EVENT_QUEUE_BIT_PATTERN_STATE_SO_CON     },  /* [SoAdEventQueueStateSoCon] */
  { /*     1 */    1u, SOAD_EVENT_QUEUE_BIT_PATTERN_IF_UDP_PDU_ROUTE }   /* [SoAdEventQueueIfUdpPduRoute] */
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
    /* Index    EventQueueIfTxRouteGrpIdx                           EventQueueIfUdpPduRouteIdx  EventQueueLocalAddrIdx                           EventQueueSockIdxIdx                           EventQueueStateSoConIdx  EventQueueTcpTxSoConIdx                           EventQueueTpRxSoConIdx                           EventQueueTpTxSoConIdx                          */
  { /*     0 */ SOAD_NO_EVENTQUEUEIFTXROUTEGRPIDXOFEVENTQUEUEIDENT,                         1u, SOAD_NO_EVENTQUEUELOCALADDRIDXOFEVENTQUEUEIDENT, SOAD_NO_EVENTQUEUESOCKIDXIDXOFEVENTQUEUEIDENT,                      0u, SOAD_NO_EVENTQUEUETCPTXSOCONIDXOFEVENTQUEUEIDENT, SOAD_NO_EVENTQUEUETPRXSOCONIDXOFEVENTQUEUEIDENT, SOAD_NO_EVENTQUEUETPTXSOCONIDXOFEVENTQUEUEIDENT }
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
CONST(SoAd_LocalAddrType, SOAD_CONST) SoAd_LocalAddr[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TcpIpCtrlIdx  AddressType                  AssignTrigger                  Domain        AssignType                     AddrId                                                                          Referable Keys */
  { /*     0 */           0u, SOAD_ADDRESS_TYPE_UNICAST  , SOAD_ASSIGN_TRIGGER_MANUAL   , SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_Fixed_10_10_7_33              },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
  { /*     1 */           0u, SOAD_ADDRESS_TYPE_MULTICAST, SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1 },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1] */
  { /*     2 */           0u, SOAD_ADDRESS_TYPE_MULTICAST, SOAD_ASSIGN_TRIGGER_AUTOMATIC, SOAD_AF_INET, SOAD_IPADDR_ASSIGNMENT_STATIC, TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast       }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast] */
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
CONST(SoAd_LocalAddrByTcpIpCtrlIndType, SOAD_CONST) SoAd_LocalAddrByTcpIpCtrlInd[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     LocalAddrByTcpIpCtrlInd      Referable Keys */
  /*     0 */                       0u   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
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
CONST(SoAd_LocalAddrIdMapType, SOAD_CONST) SoAd_LocalAddrIdMap[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  LocalAddrIdx        Referable Keys */
  { /*     0 */      FALSE,           0u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33] */
  { /*     1 */      FALSE,           1u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1] */
  { /*     2 */      FALSE,           2u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
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
CONST(SoAd_PduRouteType, SOAD_CONST) SoAd_PduRoute[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxConfPduId                      AllPduRouteDestWithPduHdr  MetaDataTxEnabled  TxConfEnabled  TxOptimized  PduRouteDestEndIdx  PduRouteDestStartIdx  UpperLayerIdx  IfTriggerTransmitMode               UpperLayerApi         Referable Keys */
  { /*     0 */ UdpNmConf_UdpNmTxPdu_UdpNmTxPdu,                     FALSE,             FALSE,          TRUE,       FALSE,                 1u,                   0u,            0u, SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE, SOAD_UL_API_IF }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_NM_Tx] */
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
  PduRouteIdx                               the index of the 1:1 relation pointing to SoAd_PduRoute
  RouteGrpSoConByPduRouteDestIndEndIdx      the end index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd
  RouteGrpSoConByPduRouteDestIndStartIdx    the start index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd
  SoConIdx                                  the index of the 1:1 relation pointing to SoAd_SoCon
  TxPduHdrId                                the PDU header ID
  UdpTriggerTimeout                         the PduRouteDest specific timeout to send a nPdu
  TxUdpTriggerMode                          indicates if nPdu shall be sent on transmission request always or never
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_PduRouteDestType, SOAD_CONST) SoAd_PduRouteDest[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PduRouteIdx  RouteGrpSoConByPduRouteDestIndEndIdx                        RouteGrpSoConByPduRouteDestIndStartIdx                        SoConIdx  TxPduHdrId                        UdpTriggerTimeout  TxUdpTriggerMode                Referable Keys */
  { /*     0 */          0u, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST,       0u, SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST,                0u, SOAD_TX_UDP_TRIGGER_NONE }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_NM_Tx, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote] */
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
CONST(SoAd_PduRouteDestBySoConIndType, SOAD_CONST) SoAd_PduRouteDestBySoConInd[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     PduRouteDestBySoConInd      Referable Keys */
  /*     0 */                      0u   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote] */
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
CONST(SoAd_RemAddrIpV4Type, SOAD_CONST) SoAd_RemAddrIpV4[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Addr                                            Port           Referable Keys */
  { /*     0 */ 0x01000AEFuL /*  239.10.0.1 LITTLE_ENDIAN  */ , 0x3075U },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote] */
  { /*     1 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */    , 0x0000U }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote] */
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
CONST(SoAd_RxPduIdIdMapType, SOAD_CONST) SoAd_RxPduIdIdMap[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  SocketRouteDestIdx        Referable Keys */
  { /*     0 */      FALSE,                 0u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_NM_Rx] */
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
CONST(SoAd_SoConType, SOAD_CONST) SoAd_SoCon[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IpFragMgtIdx                 LocalIpAddrAssignmentChgCbkIndEndIdx                 LocalIpAddrAssignmentChgCbkIndStartIdx                 NPduUdpTxIdx                 PduRouteDestBySoConIndEndIdx                 PduRouteDestBySoConIndStartIdx                 RcvRemAddrIdx                 RemAddrIpV4Idx  RemAddrIpV6Idx                 RxBufStructMgtIdx                 RxBufStructSegEndIdx                 RxBufStructSegStartIdx                 RxBufferConfigIdx                 RxMgtIdx                 SoConGrpIdx  SoConId  SoConModeChgCbkIndEndIdx                 SoConModeChgCbkIndStartIdx                 SocketIdx  SocketRouteEndIdx                 SocketRouteStartIdx                 TcpTxQueueIdx                 TlsConfigIdx                 TpTxBufferConfigIdx                 TxMgtIdx                 RemAddrState                      Referable Keys */
  { /*     0 */ SOAD_NO_IPFRAGMGTIDXOFSOCON, SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDENDIDXOFSOCON, SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON, SOAD_NO_NPDUUDPTXIDXOFSOCON,                                          1u,                                            0u, SOAD_NO_RCVREMADDRIDXOFSOCON,             0u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON, SOAD_NO_RXMGTIDXOFSOCON,          0u,      0u, SOAD_NO_SOCONMODECHGCBKINDENDIDXOFSOCON, SOAD_NO_SOCONMODECHGCBKINDSTARTIDXOFSOCON,        0u, SOAD_NO_SOCKETROUTEENDIDXOFSOCON, SOAD_NO_SOCKETROUTESTARTIDXOFSOCON, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON,                      0u, SOAD_SOCON_IP_SET_PORT_SET },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000] */
  { /*     1 */ SOAD_NO_IPFRAGMGTIDXOFSOCON, SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDENDIDXOFSOCON, SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON, SOAD_NO_NPDUUDPTXIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON, SOAD_NO_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON, SOAD_NO_RCVREMADDRIDXOFSOCON,             1u, SOAD_NO_REMADDRIPV6IDXOFSOCON, SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON, SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON, SOAD_NO_RXBUFFERCONFIGIDXOFSOCON,                      0u,          1u,      1u, SOAD_NO_SOCONMODECHGCBKINDENDIDXOFSOCON, SOAD_NO_SOCONMODECHGCBKINDSTARTIDXOFSOCON,        1u,                               1u,                                 0u, SOAD_NO_TCPTXQUEUEIDXOFSOCON, SOAD_NO_TLSCONFIGIDXOFSOCON, SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON, SOAD_NO_TXMGTIDXOFSOCON, SOAD_SOCON_IP_ANY_PORT_ANY }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000] */
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
CONST(SoAd_SoConGrpType, SOAD_CONST) SoAd_SoConGrp[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    BestMatchWithPduHeaderEnabled  BestMatchWithSockRouteEnabled  MsgAcceptFilterEnabled  PduHdrEnabled  SockAutoSoConSetup  SockAutoSoConSetupKeepOnline  FramePriority                    LocalAddrIdx  SoConEndIdx  SoConStartIdx  SocketIdx  SocketTcpIdx                    SocketUdpIdx  LocalPort        Referable Keys */
  { /*     0 */                         FALSE,                         FALSE,                   TRUE,         FALSE,               TRUE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           0u,          1u,            0u,        0u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,           0u, 0x3075U   },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote] */
  { /*     1 */                         FALSE,                         FALSE,                   TRUE,         FALSE,               TRUE,                        FALSE, SOAD_NO_FRAMEPRIORITYOFSOCONGRP,           1u,          2u,            1u,        1u, SOAD_NO_SOCKETTCPIDXOFSOCONGRP,           1u, 0x3075U   }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote] */
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
CONST(SoAd_SoConMapType, SOAD_CONST) SoAd_SoConMap[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  SoConIdx        Referable Keys */
  { /*     0 */      FALSE,       0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote] */
  { /*     1 */      FALSE,       1u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote] */
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
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
CONST(SoAd_SocketType, SOAD_CONST) SoAd_Socket[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    SoConEndIdx  SoConStartIdx        Referable Keys */
  { /*     0 */          1u,            0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33] */
  { /*     1 */          2u,            1u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1] */
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
  MetaDataRxEnabled          indicates if SoConId is forwarded as meta data on reception
  RxPduHdrId                 the PDU header ID
  SoConIdx                   the index of the 1:1 relation pointing to SoAd_SoCon
  SocketRouteDestEndIdx      the end index of the 1:n relation pointing to SoAd_SocketRouteDest
  SocketRouteDestStartIdx    the start index of the 1:n relation pointing to SoAd_SocketRouteDest
  UpperLayerApi              the upper layer API type (IF/TP)
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SocketRouteType, SOAD_CONST) SoAd_SocketRoute[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MetaDataRxEnabled  RxPduHdrId                       SoConIdx  SocketRouteDestEndIdx  SocketRouteDestStartIdx  UpperLayerApi         Referable Keys */
  { /*     0 */             FALSE, SOAD_NO_RXPDUHDRIDOFSOCKETROUTE,       1u,                    1u,                      0u, SOAD_UL_API_IF }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_NM_Rx] */
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
CONST(SoAd_SocketRouteDestType, SOAD_CONST) SoAd_SocketRouteDest[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxPduId                          RouteGrpSoConBySocketRouteDestIndEndIdx                           RouteGrpSoConBySocketRouteDestIndStartIdx                           SocketRouteIdx  UpperLayerIdx        Referable Keys */
  { /*     0 */ UdpNmConf_UdpNmRxPdu_UdpNmRxPdu, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST, SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST,             0u,            0u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_NM_Rx>>/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SoAdSocketRoute_NM_Rx/SoAdSocketRouteDest>>/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote] */
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
CONST(SoAd_SocketUdpType, SOAD_CONST) SoAd_SocketUdp[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ImmedIfTxConf  UdpListenOnly  UdpStrictHdrLenCheckEnabled  AliveTimeoutMaxCnt  ImmedIfTxConfListSize  NPduUdpTxBufferMin  NPduUdpTxQueueSize  RetryQueueLimit  UdpTriggerTimeout        Referable Keys */
  { /*     0 */         FALSE,         FALSE,                       FALSE,                 0u,                    0u,                 0u,                 0u,              2u,                0u },  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000] */
  { /*     1 */         FALSE,         FALSE,                       FALSE,                 0u,                    0u,                 0u,                 0u,              2u,                0u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000] */
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
CONST(SoAd_TcpIpCtrlType, SOAD_CONST) SoAd_TcpIpCtrl[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RetryEnabled  LocalAddrByTcpIpCtrlIndEndIdx  LocalAddrByTcpIpCtrlIndStartIdx        Referable Keys */
  { /*     0 */         TRUE,                            1u,                              0u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
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
    /* Index    TimeoutListDynNPduUdpTxIdx                            TimeoutListDynUdpAliveIdx                           */
  { /*     0 */ SOAD_NO_TIMEOUTLISTDYNNPDUUDPTXIDXOFTIMEOUTLISTIDENT, SOAD_NO_TIMEOUTLISTDYNUDPALIVEIDXOFTIMEOUTLISTIDENT }
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
CONST(SoAd_TxPduIdMapType, SOAD_CONST) SoAd_TxPduIdMap[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  PduRouteIdx        Referable Keys */
  { /*     0 */      FALSE,          0u }   /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_NM_Tx] */
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
CONST(SoAd_UpperLayerType, SOAD_CONST) SoAd_UpperLayer[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IfRxIndicationCbk         IfTriggerTransmitCbk  IfTxConfirmationCbk         TpCopyRxDataCbk  TpCopyRxDataConstCbk  TpCopyTxDataCbk  TpCopyTxDataConstCbk  TpRxIndicationCbk  TpStartOfReceptionCbk  TpStartOfReceptionConstCbk  TpTxConfirmationCbk        Referable Keys */
  { /*     0 */ UdpNm_SoAdIfRxIndication, NULL_PTR            , UdpNm_SoAdIfTxConfirmation, NULL_PTR       , NULL_PTR            , NULL_PTR       , NULL_PTR            , NULL_PTR         , NULL_PTR             , NULL_PTR                  , NULL_PTR            }   /* [/ActiveEcuC/SoAd/UdpNm] */
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
VAR(SoAd_BestMatchSoConIdxListType, SOAD_VAR_NOINIT) SoAd_BestMatchSoConIdxList[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
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
  /*     0 */  /* [SoAdEventQueueStateSoCon] */
  /*     1 */  /* [SoAdEventQueueIfUdpPduRoute] */

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
VAR(SoAd_EventQueueFlagType, SOAD_VAR_NOINIT) SoAd_EventQueueFlag[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
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
  /*     1 */  /* [/ActiveEcuC/SoAd] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
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
VAR(SoAd_LocalAddrDynType, SOAD_VAR_NOINIT) SoAd_LocalAddrDyn[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
  /*     1 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1] */
  /*     2 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast] */

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
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdPduRoute_NM_Tx] */

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
  CancelRequested       indicates if reception cancellation is requested
  RxBytesPending        the length of pending data to be received
  SocketRouteDestIdx    the index of the 1:1 relation pointing to SoAd_SocketRouteDest
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_RxMgtUType, SOAD_VAR_NOINIT) SoAd_RxMgt;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote] */

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
VAR(SoAd_SoConDynType, SOAD_VAR_NOINIT) SoAd_SoConDyn[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000/SC_UDP_ANY_DynPort_Remote, /ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000] */

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
VAR(SoAd_SocketDynType, SOAD_VAR_NOINIT) SoAd_SocketDyn[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_Multicast_Rx_Fixed_239_10_1_30000, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1] */

#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
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
  CancelRequested    indicates if transmission cancellation is requested
  PduRouteDestIdx    the index of the 1:1 relation pointing to SoAd_PduRouteDest
  TxBytesLen         the length of data to be transmitted
  TxBytesPending     the length of pending data to be transmitted
  TxBufPtr           the pointer to transmission data buffer
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(SoAd_TxMgtUType, SOAD_VAR_NOINIT) SoAd_TxMgt;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_UDP_fixed_10_10_7_33_30000/SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote] */

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
    , NULL_PTR                                  /**< the pointer to SoAd_EventQueueTpRxSoCon */
    , NULL_PTR                                  /**< the pointer to SoAd_EventQueueTpTxSoCon */
    , NULL_PTR                                  /**< the pointer to SoAd_IfRxBuffer */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragBuf */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragBufConfig */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragBufConfigDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_IpFragMgt */
    , SoAd_LocalAddr                            /**< the pointer to SoAd_LocalAddr */
    , SoAd_LocalAddrByTcpIpCtrlInd              /**< the pointer to SoAd_LocalAddrByTcpIpCtrlInd */
    , SoAd_LocalAddrDyn                         /**< the pointer to SoAd_LocalAddrDyn */
    , SoAd_LocalAddrIdMap                       /**< the pointer to SoAd_LocalAddrIdMap */
    , NULL_PTR                                  /**< the pointer to SoAd_LocalIpAddrAssignmentChgCbk */
    , NULL_PTR                                  /**< the pointer to SoAd_LocalIpAddrAssignmentChgCbkInd */
    , NULL_PTR                                  /**< the pointer to SoAd_MetaDataRxBuf */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTx */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTxBuffer */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTxDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_NPduUdpTxQueue */
    , SoAd_PduRoute                             /**< the pointer to SoAd_PduRoute */
    , SoAd_PduRouteDest                         /**< the pointer to SoAd_PduRouteDest */
    , SoAd_PduRouteDestBySoConInd               /**< the pointer to SoAd_PduRouteDestBySoConInd */
    , NULL_PTR                                  /**< the pointer to SoAd_PduRouteDestInd */
    , SoAd_PduRouteDyn.raw                      /**< the pointer to SoAd_PduRouteDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_RcvRemAddr */
    , SoAd_RemAddrIpV4                          /**< the pointer to SoAd_RemAddrIpV4 */
    , NULL_PTR                                  /**< the pointer to SoAd_RemAddrIpV6 */
    , NULL_PTR                                  /**< the pointer to SoAd_RouteGrp */
    , NULL_PTR                                  /**< the pointer to SoAd_RouteGrpIdMap */
    , NULL_PTR                                  /**< the pointer to SoAd_RouteGrpSoCon */
    , NULL_PTR                                  /**< the pointer to SoAd_RouteGrpSoConByPduRouteDestInd */
    , NULL_PTR                                  /**< the pointer to SoAd_RouteGrpSoConBySocketRouteDestInd */
    , NULL_PTR                                  /**< the pointer to SoAd_RouteGrpSoConDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_RxBufStructMgt */
    , NULL_PTR                                  /**< the pointer to SoAd_RxBufStructSeg */
    , NULL_PTR                                  /**< the pointer to SoAd_RxBufferConfig */
    , NULL_PTR                                  /**< the pointer to SoAd_RxBufferConfigDyn */
    , SoAd_RxMgt.raw                            /**< the pointer to SoAd_RxMgt */
    , SoAd_RxPduIdIdMap                         /**< the pointer to SoAd_RxPduIdIdMap */
    , NULL_PTR                                  /**< the pointer to SoAd_ShutdownFinishedCbk */
    , SoAd_SoCon                                /**< the pointer to SoAd_SoCon */
    , SoAd_SoConDyn                             /**< the pointer to SoAd_SoConDyn */
    , SoAd_SoConGrp                             /**< the pointer to SoAd_SoConGrp */
    , SoAd_SoConMap                             /**< the pointer to SoAd_SoConMap */
    , NULL_PTR                                  /**< the pointer to SoAd_SoConModeChgCbk */
    , NULL_PTR                                  /**< the pointer to SoAd_SoConModeChgCbkInd */
    , SoAd_Socket                               /**< the pointer to SoAd_Socket */
    , SoAd_SocketDyn                            /**< the pointer to SoAd_SocketDyn */
    , NULL_PTR                                  /**< the pointer to SoAd_SocketReportErrorCbk */
    , SoAd_SocketRoute                          /**< the pointer to SoAd_SocketRoute */
    , SoAd_SocketRouteDest                      /**< the pointer to SoAd_SocketRouteDest */
    , NULL_PTR                                  /**< the pointer to SoAd_SocketRouteInd */
    , NULL_PTR                                  /**< the pointer to SoAd_SocketTcp */
    , SoAd_SocketUdp                            /**< the pointer to SoAd_SocketUdp */
    , SoAd_TcpIpCtrl                            /**< the pointer to SoAd_TcpIpCtrl */
    , SoAd_TcpKeepAliveGloballyEnabled          /**< the pointer to SoAd_TcpKeepAliveGloballyEnabled */
    , NULL_PTR                                  /**< the pointer to SoAd_TcpTlsSocketCreatedNotificationCbk */
    , NULL_PTR                                  /**< the pointer to SoAd_TcpTxQueue */
    , NULL_PTR                                  /**< the pointer to SoAd_TcpTxQueueData */
    , NULL_PTR                                  /**< the pointer to SoAd_TcpTxQueueMgt */
    , NULL_PTR                                  /**< the pointer to SoAd_TimeoutListDyn */
    , SoAd_TimeoutListIdent                     /**< the pointer to SoAd_TimeoutListIdent */
    , NULL_PTR                                  /**< the pointer to SoAd_TimeoutListNPduUdpTx */
    , NULL_PTR                                  /**< the pointer to SoAd_TimeoutListNPduUdpTxMap */
    , NULL_PTR                                  /**< the pointer to SoAd_TimeoutListUdpAlive */
    , NULL_PTR                                  /**< the pointer to SoAd_TimeoutListUdpAliveMap */
    , NULL_PTR                                  /**< the pointer to SoAd_TlsConfig */
    , NULL_PTR                                  /**< the pointer to SoAd_TpRxBuffer */
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
    , 1u                                        /**< the number of elements in SoAd_BestMatchSoConIdxList */
    , 0u                                        /**< the number of elements in SoAd_DhcpEventCbk */
    , 2u                                        /**< the number of elements in SoAd_EventQueue */
    , 2u                                        /**< the number of elements in SoAd_EventQueueFlag */
    , 1u                                        /**< the number of elements in SoAd_EventQueueIdent */
    , 0u                                        /**< the number of elements in SoAd_EventQueueIfTxRouteGrp */
    , 1u                                        /**< the number of elements in SoAd_EventQueueIfUdpPduRoute */
    , 0u                                        /**< the number of elements in SoAd_EventQueueLocalAddr */
    , 0u                                        /**< the number of elements in SoAd_EventQueueSocketIdx */
    , 2u                                        /**< the number of elements in SoAd_EventQueueStateSoCon */
    , 0u                                        /**< the number of elements in SoAd_EventQueueTcpTxSoCon */
    , 0u                                        /**< the number of elements in SoAd_EventQueueTpRxSoCon */
    , 0u                                        /**< the number of elements in SoAd_EventQueueTpTxSoCon */
    , 0u                                        /**< the number of elements in SoAd_IfRxBuffer */
    , 0u                                        /**< the number of elements in SoAd_IpFragBuf */
    , 0u                                        /**< the number of elements in SoAd_IpFragBufConfig */
    , 0u                                        /**< the number of elements in SoAd_IpFragMgt */
    , 3u                                        /**< the number of elements in SoAd_LocalAddr */
    , 1u                                        /**< the number of elements in SoAd_LocalAddrByTcpIpCtrlInd */
    , 3u                                        /**< the number of elements in SoAd_LocalAddrIdMap */
    , 0u                                        /**< the number of elements in SoAd_LocalIpAddrAssignmentChgCbk */
    , 0u                                        /**< the number of elements in SoAd_LocalIpAddrAssignmentChgCbkInd */
    , 0u                                        /**< the number of elements in SoAd_MetaDataRxBuf */
    , 0u                                        /**< the number of elements in SoAd_NPduUdpTx */
    , 0u                                        /**< the number of elements in SoAd_NPduUdpTxBuffer */
    , 0u                                        /**< the number of elements in SoAd_NPduUdpTxQueue */
    , 1u                                        /**< the number of elements in SoAd_PduRoute */
    , 1u                                        /**< the number of elements in SoAd_PduRouteDest */
    , 1u                                        /**< the number of elements in SoAd_PduRouteDestBySoConInd */
    , 0u                                        /**< the number of elements in SoAd_PduRouteDestInd */
    , 0u                                        /**< the number of elements in SoAd_RcvRemAddr */
    , 2u                                        /**< the number of elements in SoAd_RemAddrIpV4 */
    , 0u                                        /**< the number of elements in SoAd_RemAddrIpV6 */
    , 0u                                        /**< the number of elements in SoAd_RouteGrp */
    , 0u                                        /**< the number of elements in SoAd_RouteGrpIdMap */
    , 0u                                        /**< the number of elements in SoAd_RouteGrpSoCon */
    , 0u                                        /**< the number of elements in SoAd_RouteGrpSoConByPduRouteDestInd */
    , 0u                                        /**< the number of elements in SoAd_RouteGrpSoConBySocketRouteDestInd */
    , 0u                                        /**< the number of elements in SoAd_RxBufStructMgt */
    , 0u                                        /**< the number of elements in SoAd_RxBufStructSeg */
    , 0u                                        /**< the number of elements in SoAd_RxBufferConfig */
    , 1u                                        /**< the number of elements in SoAd_RxMgt */
    , 1u                                        /**< the number of elements in SoAd_RxPduIdIdMap */
    , 0u                                        /**< the number of elements in SoAd_ShutdownFinishedCbk */
    , 2u                                        /**< the number of elements in SoAd_SoCon */
    , 2u                                        /**< the number of elements in SoAd_SoConGrp */
    , 2u                                        /**< the number of elements in SoAd_SoConMap */
    , 0u                                        /**< the number of elements in SoAd_SoConModeChgCbk */
    , 0u                                        /**< the number of elements in SoAd_SoConModeChgCbkInd */
    , 2u                                        /**< the number of elements in SoAd_Socket */
    , 0u                                        /**< the number of elements in SoAd_SocketReportErrorCbk */
    , 1u                                        /**< the number of elements in SoAd_SocketRoute */
    , 1u                                        /**< the number of elements in SoAd_SocketRouteDest */
    , 0u                                        /**< the number of elements in SoAd_SocketRouteInd */
    , 0u                                        /**< the number of elements in SoAd_SocketTcp */
    , 2u                                        /**< the number of elements in SoAd_SocketUdp */
    , 1u                                        /**< the number of elements in SoAd_TcpIpCtrl */
    , 1u                                        /**< the number of elements in SoAd_TcpKeepAliveGloballyEnabled */
    , 0u                                        /**< the number of elements in SoAd_TcpTlsSocketCreatedNotificationCbk */
    , 0u                                        /**< the number of elements in SoAd_TcpTxQueue */
    , 0u                                        /**< the number of elements in SoAd_TcpTxQueueData */
    , 0u                                        /**< the number of elements in SoAd_TimeoutListDyn */
    , 1u                                        /**< the number of elements in SoAd_TimeoutListIdent */
    , 0u                                        /**< the number of elements in SoAd_TimeoutListNPduUdpTx */
    , 0u                                        /**< the number of elements in SoAd_TimeoutListNPduUdpTxMap */
    , 0u                                        /**< the number of elements in SoAd_TimeoutListUdpAlive */
    , 0u                                        /**< the number of elements in SoAd_TimeoutListUdpAliveMap */
    , 0u                                        /**< the number of elements in SoAd_TlsConfig */
    , 0u                                        /**< the number of elements in SoAd_TpRxBuffer */
    , 0u                                        /**< the number of elements in SoAd_TpTxBuffer */
    , 0u                                        /**< the number of elements in SoAd_TpTxBufferConfig */
    , 0u                                        /**< the number of elements in SoAd_TriggerBuf */
    , 0u                                        /**< the number of elements in SoAd_TriggerBufConfig */
    , 1u                                        /**< the number of elements in SoAd_TxMgt */
    , 1u                                        /**< the number of elements in SoAd_TxPduIdMap */
    , 1u                                        /**< the number of elements in SoAd_UpperLayer */
  }
};
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
 *  END OF FILE: SoAd_Lcfg.c
 *********************************************************************************************************************/

