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
 *            Module: DoIP
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: DoIP_Lcfg.c
 *   Generation Time: 2026-07-05 10:57:29
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#define DOIP_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
#include "DoIP.h"
#include "PduR_DoIP.h"
#include "Appl_DoIp.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

#ifndef STATIC
# define STATIC static
#endif /* STATIC */

#define DoIPRoutingActivation_DoIPRoutingActivation 0u

#define DoIPChannel_DoIPChannel_DOIP_Phy_REQ 0u
#define DoIPChannel_DoIPChannel_DOIP_FUNC_REQ 1u

#define DoIPTester_DoIPTester_x0E80 0u

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
  DoIP_Channel
**********************************************************************************************************************/
/** 
  \var    DoIP_Channel
  \brief  contains static channel data
  \details
  Element            Description
  EcuAddr            logical ecu addr
  TpMaxLen           maximum TP length
  PduRRxPduId        PduR PduId for reception
  PduRTxConfPduId    PduR PduId for transmission confirmation
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_ChannelType, DOIP_CONST) DoIP_Channel[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    EcuAddr  TpMaxLen  PduRRxPduId                                   PduRTxConfPduId                                      Referable Keys */
  { /*     0 */ 0x1212u,    4095u, PduRConf_PduRSrcPdu_PduRSrcPdu__DOIPPhyReqRx, PduRConf_PduRDestPdu_PduRDestPdu_DOIPPhyResTx },  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPChannel_DOIP_Phy_REQ, /ActiveEcuC/DoIP/DoIPConfigSet/DoIPRoutingActivation] */
  { /*     1 */ 0xEE80u,    4095u, PduRConf_PduRSrcPdu_PduRSrcPdu_DOIPFuncReqRx,              DOIP_NO_PDURTXCONFPDUIDOFCHANNEL }   /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPChannel_DOIP_FUNC_REQ, /ActiveEcuC/DoIP/DoIPConfigSet/DoIPRoutingActivation] */
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_Connection
**********************************************************************************************************************/
/** 
  \var    DoIP_Connection
  \brief  contains static TCP connection Data. List of DoIPConnections. The RxPduId as well as the TxPduId can be used to access the array.
  \details
  Element          Description
  LocalAddrIdx     the index of the 1:1 relation pointing to DoIP_LocalAddr
  RxCancelPduId    PduId used for reception cancelation
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_ConnectionType, DOIP_CONST) DoIP_Connection[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    LocalAddrIdx  RxCancelPduId                                               Referable Keys */
  { /*     0 */           0u,     SoAdConf_SoAdSocketRouteDest_SoAdSocketRouteDest },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     1 */           0u, SoAdConf_SoAdSocketRouteDest_SoAdSocketRouteDest_001 },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     2 */           0u,   SoAdConf_SoAdSocketRouteDest_SoAdSocketRouteDest_1 },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     3 */           0u,                    DOIP_NO_RXCANCELPDUIDOFCONNECTION }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ConnectionTcp
**********************************************************************************************************************/
/** 
  \var    DoIP_ConnectionTcp
  \brief  contains static TCP connection data
  \details
  Element               Description
  SecurityRequired      security required
  ConnectionGroupIdx    the index of the 1:1 relation pointing to DoIP_ConnectionGroup
  RxHdrBufStartIdx      the start index of the 1:n relation pointing to DoIP_RxHdrBuf
  TxTcpMgtStartIdx      the start index of the 1:n relation pointing to DoIP_TxTcpMgt
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_ConnectionTcpType, DOIP_CONST) DoIP_ConnectionTcp[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    SecurityRequired  ConnectionGroupIdx  RxHdrBufStartIdx  TxTcpMgtStartIdx        Referable Keys */
  { /*     0 */            FALSE,                 0u,               0u,               0u },  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400] */
  { /*     1 */            FALSE,                 0u,              19u,               2u }   /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400] */
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_EId
**********************************************************************************************************************/
/** 
  \var    DoIP_EId
  \brief  the EID
*/ 
#define DOIP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_EIdType, DOIP_CONST) DoIP_EId[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     EId    */
  /*     0 */  0x01u,
  /*     1 */  0x01u,
  /*     2 */  0x01u,
  /*     3 */  0x01u,
  /*     4 */  0x01u,
  /*     5 */  0x01u
};
#define DOIP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_GId
**********************************************************************************************************************/
/** 
  \var    DoIP_GId
  \brief  the GID
*/ 
#define DOIP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_GIdType, DOIP_CONST) DoIP_GId[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     GId    */
  /*     0 */  0x01u,
  /*     1 */  0x01u,
  /*     2 */  0x01u,
  /*     3 */  0x01u,
  /*     4 */  0x01u,
  /*     5 */  0x01u
};
#define DOIP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_IpAddrAssignment
**********************************************************************************************************************/
/** 
  \var    DoIP_IpAddrAssignment
  \brief  contains static IP address assignment data
  \details
  Element                Description
  ControlIpAssignment    indicates if IP address assigment shall be requested/released
  AssignmentType         ip addresss assignment type
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_IpAddrAssignmentType, DOIP_CONST) DoIP_IpAddrAssignment[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ControlIpAssignment  AssignmentType                        Referable Keys */
  { /*     0 */               FALSE, DOIP_IPADDR_ASSIGN_TYPE_DHCP   },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  { /*     1 */               FALSE, DOIP_IPADDR_ASSIGN_TYPE_STATIC }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_LocalAddr
**********************************************************************************************************************/
/** 
  \var    DoIP_LocalAddr
  \brief  contains static local address data
  \details
  Element            Description
  UdpAliveTimeout    indicates if UDP alive timeout is enabled
  DomainType         domain type
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_LocalAddrType, DOIP_CONST) DoIP_LocalAddr[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    UdpAliveTimeout  DomainType          Referable Keys */
  { /*     0 */           FALSE, SOAD_AF_INET }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_RoutingActivation
**********************************************************************************************************************/
/** 
  \var    DoIP_RoutingActivation
  \brief  contains static routing activation data
  \details
  Element                   Description
  AuthFuncPtr               pointer to authentification function
  AuthWithRemAddrFuncPtr    pointer to authentification function with remote address
  ConfFuncPtr               pointer to confirmation function
  ConfWithRemAddrFuncPtr    pointer to confirmation function with remote address
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_RoutingActivationType, DOIP_CONST) DoIP_RoutingActivation[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    AuthFuncPtr  AuthWithRemAddrFuncPtr  ConfFuncPtr  ConfWithRemAddrFuncPtr        Referable Keys */
  { /*     0 */ NULL_PTR   , NULL_PTR              , NULL_PTR   , NULL_PTR               }   /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPRoutingActivation, /ActiveEcuC/DoIP/DoIPConfigSet/DoIPTester_x0E80] */
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxTcpMgt
**********************************************************************************************************************/
/** 
  \var    DoIP_TxTcpMgt
  \brief  contains static TCP transmission queue management data
  \details
  Element             Description
  TxHdrBufStartIdx    the start index of the 1:n relation pointing to DoIP_TxHdrBuf
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_TxTcpMgtType, DOIP_CONST) DoIP_TxTcpMgt[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxHdrBufStartIdx        Referable Keys */
  { /*     0 */               0u },  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0] */
  { /*     1 */              21u },  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0] */
  { /*     2 */              42u },  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1] */
  { /*     3 */              63u }   /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1] */
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_AliveCheckList
**********************************************************************************************************************/
/** 
  \var    DoIP_AliveCheckList
  \brief  list of connections with pending alive checks
  \details
  Element             Description
  ConnectionTcpIdx    the index of the 1:1 relation pointing to DoIP_ConnectionTcp
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_AliveCheckListType, DOIP_VAR_NOINIT) DoIP_AliveCheckList[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ChannelDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_ChannelDyn
  \brief  contains dynamic channel data
  \details
  Element     Description
  TxMsgLen    message length to transmit
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_ChannelDynType, DOIP_VAR_NOINIT) DoIP_ChannelDyn[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPChannel_DOIP_Phy_REQ, /ActiveEcuC/DoIP/DoIPConfigSet/DoIPRoutingActivation] */
  /*     1 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPChannel_DOIP_FUNC_REQ, /ActiveEcuC/DoIP/DoIPConfigSet/DoIPRoutingActivation] */

#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ConnectionDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_ConnectionDyn
  \brief  contains dynamic connection data
  \details
  Element         Description
  SoConClosing    indicates if socket connection is closing
  IpAddrState     ip address state
  SoConId         socket connection id
  SoConState      socket connection state
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_ConnectionDynUType, DOIP_VAR_NOINIT) DoIP_ConnectionDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  /*   ... */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  /*     3 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */

#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ConnectionTcpDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_ConnectionTcpDyn
  \brief  contains dynamic TCP connection data
  \details
  Element                 Description
  RxMsgOffset             number of already copied bytes
  InactivCnt              inactivity timeout
  LastRxBufSize           buffer size of previous message part
  LastRxTgtAddr           ast used target address
  LastTxBufSize           buffer size of previous message part
  TesterAddr              tester address
  TxBytesCopied           number of already copied bytes
  VerifyRxPduOffset       offset in header buffer. This user data can be used for rx pdu verification
  ChannelRxActive         indicates if reception channel is still active
  ChannelRxLastIdx        the index of the 0:1 relation pointing to DoIP_Channel
  RoutingActivationIdx    the index of the 0:1 relation pointing to DoIP_RoutingActivation
  RxTpSessionActive       lock for TP session
  SkipRxMsg               indicates if message should be skiped
  TesterIdx               the index of the 0:1 relation pointing to DoIP_Tester
  TxTcpMgtQueIdx          manamgement queue index
  TxTcpMgtQueLvl          managment queue fill level
  TxTpSessionActive       lock for TP session
  ActivState              state of routing activation indicates next action
  TpTxPreCloseSocket      indicates if socket should be cosed after transmission
  TpTxPreHdrType          header type of prepared transmission
  TpTxPreParam1           parameter depends on header type of prepared transmission
  TpTxPreParam2           parameter depends on header type of prepared transmission
  TpTxPreParam3           parameter depends on header type of prepared transmission
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_ConnectionTcpDynType, DOIP_VAR_NOINIT) DoIP_ConnectionTcpDyn[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400] */
  /*     1 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1, /ActiveEcuC/SoAd/SoAdConfig/SCG_DOIP_TCP_DHCP_169_254_1_33_13400] */

#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_DiagNAckBuf
**********************************************************************************************************************/
/** 
  \var    DoIP_DiagNAckBuf
  \brief  diagnostic nack data buffer
*/ 
#define DOIP_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_DiagNAckBufUType, DOIP_VAR_NOINIT) DoIP_DiagNAckBuf;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
#define DOIP_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_IpAddrAssignmentDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_IpAddrAssignmentDyn
  \brief  contains dynamic IP address assignment data
  \details
  Element           Description
  IpAddrReqState    IP address request state
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_IpAddrAssignmentDynUType, DOIP_VAR_NOINIT) DoIP_IpAddrAssignmentDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */
  /*     1 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33] */

#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_RoutActivHandler
**********************************************************************************************************************/
/** 
  \var    DoIP_RoutActivHandler
  \brief  single routing activation handler
  \details
  Element                 Description
  OemSpecReq              handlers oem specific request buffer
  OemSpecRes              handlers oem specific response buffer
  AliveCheckCnt           alive check timeout
  TesterAddr              handlers active testser address
  AliveCheckElemNum       number of pending alive checks
  ConnectionTcpIdx        the index of the 0:1 relation pointing to DoIP_ConnectionTcp
  OemSpecUsed             indicates if oem specific payload type is used
  RoutingActivationIdx    the index of the 0:1 relation pointing to DoIP_RoutingActivation
  TesterIdx               the index of the 0:1 relation pointing to DoIP_Tester
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_RoutActivHandlerType, DOIP_VAR_NOINIT) DoIP_RoutActivHandler[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_RxHdrBuf
**********************************************************************************************************************/
/** 
  \var    DoIP_RxHdrBuf
  \brief  buffer which stores the received message header
*/ 
#define DOIP_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_RxHdrBufUType, DOIP_VAR_NOINIT) DoIP_RxHdrBuf;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0] */
  /*   ... */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0] */
  /*    18 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0] */
  /*    19 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1] */
  /*   ... */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1] */
  /*    37 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1] */

#define DOIP_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TesterDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_TesterDyn
  \brief  contains static dynamic data
  \details
  Element             Description
  DiagNAckOffset      diagnostic nack data buffer offset
  ConnectionTcpIdx    the index of the 0:1 relation pointing to DoIP_ConnectionTcp
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_TesterDynUType, DOIP_VAR_NOINIT) DoIP_TesterDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPTester_x0E80] */

#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxHdrBuf
**********************************************************************************************************************/
/** 
  \var    DoIP_TxHdrBuf
  \brief  buffer which stores the message header for transmission
*/ 
#define DOIP_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_TxHdrBufType, DOIP_VAR_NOINIT) DoIP_TxHdrBuf[84];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0->QueueIdx_0] */
  /*   ... */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0->QueueIdx_0] */
  /*    20 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0->QueueIdx_0] */
  /*    21 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0->QueueIdx_1] */
  /*   ... */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0->QueueIdx_1] */
  /*    41 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0->QueueIdx_1] */
  /*    42 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1->QueueIdx_0] */
  /*   ... */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1->QueueIdx_0] */
  /*    62 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1->QueueIdx_0] */
  /*    63 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1->QueueIdx_1] */
  /*   ... */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1->QueueIdx_1] */
  /*    83 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1->QueueIdx_1] */

#define DOIP_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxTcpMgtDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_TxTcpMgtDyn
  \brief  contains dynamic TCP transmission queue management data
  \details
  Element        Description
  TxHdrBufLen    length of header buffer used for transmission
  ChannelIdx     the index of the 0:1 relation pointing to DoIP_Channel
  Msg            message buffer
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_TxTcpMgtDynUType, DOIP_VAR_NOINIT) DoIP_TxTcpMgtDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0] */
  /*     1 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA0] */
  /*     2 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1] */
  /*     3 */  /* [/ActiveEcuC/DoIP/DoIPConfigSet/DoIPConnections/DoIPTcpConnection_TCP_DATA1] */

#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxUdpMgtList
**********************************************************************************************************************/
/** 
  \var    DoIP_TxUdpMgtList
  \brief  UDP trasmission list
  \details
  Element          Description
  HdrType          header tpye
  RetryAttempt     retry attempts
  ConnectionIdx    the index of the 0:1 relation pointing to DoIP_Connection
  Param1           parameter depends on header type
  Param2           parameter depends on header type
  RemoteAddr       remote ip address for transmission
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(DoIP_TxUdpMgtListType, DOIP_VAR_NOINIT) DoIP_TxUdpMgtList[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_PCConfig
**********************************************************************************************************************/
/** 
  \var    DoIP_PCConfig
  \details
  Element                       Description
  AliveCheckList                the pointer to DoIP_AliveCheckList
  Channel                       the pointer to DoIP_Channel
  ChannelDyn                    the pointer to DoIP_ChannelDyn
  ChannelInd                    the pointer to DoIP_ChannelInd
  Connection                    the pointer to DoIP_Connection
  ConnectionDyn                 the pointer to DoIP_ConnectionDyn
  ConnectionGroup               the pointer to DoIP_ConnectionGroup
  ConnectionInd                 the pointer to DoIP_ConnectionInd
  ConnectionTcp                 the pointer to DoIP_ConnectionTcp
  ConnectionTcpDyn              the pointer to DoIP_ConnectionTcpDyn
  ConnectionTcpInd              the pointer to DoIP_ConnectionTcpInd
  DefaultTester                 the pointer to DoIP_DefaultTester
  DiagNAckBuf                   the pointer to DoIP_DiagNAckBuf
  EId                           the pointer to DoIP_EId
  GId                           the pointer to DoIP_GId
  IpAddrAssignment              the pointer to DoIP_IpAddrAssignment
  IpAddrAssignmentDyn           the pointer to DoIP_IpAddrAssignmentDyn
  LocalAddr                     the pointer to DoIP_LocalAddr
  PduRRxCancelPduId             the pointer to DoIP_PduRRxCancelPduId
  PduRTxPduId                   the pointer to DoIP_PduRTxPduId
  RoutActivHandler              the pointer to DoIP_RoutActivHandler
  RoutingActivation             the pointer to DoIP_RoutingActivation
  RoutingActivationInd          the pointer to DoIP_RoutingActivationInd
  RxHdrBuf                      the pointer to DoIP_RxHdrBuf
  Tester                        the pointer to DoIP_Tester
  TesterDyn                     the pointer to DoIP_TesterDyn
  TxHdrBuf                      the pointer to DoIP_TxHdrBuf
  TxTcpMgt                      the pointer to DoIP_TxTcpMgt
  TxTcpMgtDyn                   the pointer to DoIP_TxTcpMgtDyn
  TxUdpMgtList                  the pointer to DoIP_TxUdpMgtList
  SizeOfDiagNAckBuf             the number of accomplishable value elements in DoIP_DiagNAckBuf
  SizeOfAliveCheckList          the number of accomplishable value elements in DoIP_AliveCheckList
  SizeOfChannel                 the number of accomplishable value elements in DoIP_Channel
  SizeOfChannelInd              the number of accomplishable value elements in DoIP_ChannelInd
  SizeOfConnection              the number of accomplishable value elements in DoIP_Connection
  SizeOfConnectionGroup         the number of accomplishable value elements in DoIP_ConnectionGroup
  SizeOfConnectionInd           the number of accomplishable value elements in DoIP_ConnectionInd
  SizeOfConnectionTcp           the number of accomplishable value elements in DoIP_ConnectionTcp
  SizeOfConnectionTcpInd        the number of accomplishable value elements in DoIP_ConnectionTcpInd
  SizeOfDefaultTester           the number of accomplishable value elements in DoIP_DefaultTester
  SizeOfEId                     the number of accomplishable value elements in DoIP_EId
  SizeOfGId                     the number of accomplishable value elements in DoIP_GId
  SizeOfIpAddrAssignment        the number of accomplishable value elements in DoIP_IpAddrAssignment
  SizeOfLocalAddr               the number of accomplishable value elements in DoIP_LocalAddr
  SizeOfPduRRxCancelPduId       the number of accomplishable value elements in DoIP_PduRRxCancelPduId
  SizeOfPduRTxPduId             the number of accomplishable value elements in DoIP_PduRTxPduId
  SizeOfRoutActivHandler        the number of accomplishable value elements in DoIP_RoutActivHandler
  SizeOfRoutingActivation       the number of accomplishable value elements in DoIP_RoutingActivation
  SizeOfRoutingActivationInd    the number of accomplishable value elements in DoIP_RoutingActivationInd
  SizeOfRxHdrBuf                the number of accomplishable value elements in DoIP_RxHdrBuf
  SizeOfTester                  the number of accomplishable value elements in DoIP_Tester
  SizeOfTxHdrBuf                the number of accomplishable value elements in DoIP_TxHdrBuf
  SizeOfTxTcpMgt                the number of accomplishable value elements in DoIP_TxTcpMgt
  SizeOfTxUdpMgtList            the number of accomplishable value elements in DoIP_TxUdpMgtList
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(DoIP_PCConfigsType, DOIP_CONST) DoIP_PCConfig = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  { /* Index: 0 Keys: [Config] */
      DoIP_AliveCheckList           /**< the pointer to DoIP_AliveCheckList */
    , DoIP_Channel                  /**< the pointer to DoIP_Channel */
    , DoIP_ChannelDyn               /**< the pointer to DoIP_ChannelDyn */
    , DoIP_ChannelInd               /**< the pointer to DoIP_ChannelInd */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , DoIP_Connection               /**< the pointer to DoIP_Connection */
    , DoIP_ConnectionDyn.raw        /**< the pointer to DoIP_ConnectionDyn */
    , DoIP_ConnectionGroup          /**< the pointer to DoIP_ConnectionGroup */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , DoIP_ConnectionInd            /**< the pointer to DoIP_ConnectionInd */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , DoIP_ConnectionTcp            /**< the pointer to DoIP_ConnectionTcp */
    , DoIP_ConnectionTcpDyn         /**< the pointer to DoIP_ConnectionTcpDyn */
    , DoIP_ConnectionTcpInd         /**< the pointer to DoIP_ConnectionTcpInd */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , NULL_PTR                      /**< the pointer to DoIP_DefaultTester */
    , DoIP_DiagNAckBuf.raw          /**< the pointer to DoIP_DiagNAckBuf */
    , DoIP_EId                      /**< the pointer to DoIP_EId */
    , DoIP_GId                      /**< the pointer to DoIP_GId */
    , DoIP_IpAddrAssignment         /**< the pointer to DoIP_IpAddrAssignment */
    , DoIP_IpAddrAssignmentDyn.raw  /**< the pointer to DoIP_IpAddrAssignmentDyn */
    , DoIP_LocalAddr                /**< the pointer to DoIP_LocalAddr */
    , DoIP_PduRRxCancelPduId        /**< the pointer to DoIP_PduRRxCancelPduId */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , DoIP_PduRTxPduId              /**< the pointer to DoIP_PduRTxPduId */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , DoIP_RoutActivHandler         /**< the pointer to DoIP_RoutActivHandler */
    , DoIP_RoutingActivation        /**< the pointer to DoIP_RoutingActivation */
    , DoIP_RoutingActivationInd     /**< the pointer to DoIP_RoutingActivationInd */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , DoIP_RxHdrBuf.raw             /**< the pointer to DoIP_RxHdrBuf */
    , DoIP_Tester                   /**< the pointer to DoIP_Tester */  /* PRQA S 0310 */  /* MD_CSL_NonDereferentiatableValidPointer */
    , DoIP_TesterDyn.raw            /**< the pointer to DoIP_TesterDyn */
    , DoIP_TxHdrBuf                 /**< the pointer to DoIP_TxHdrBuf */
    , DoIP_TxTcpMgt                 /**< the pointer to DoIP_TxTcpMgt */
    , DoIP_TxTcpMgtDyn.raw          /**< the pointer to DoIP_TxTcpMgtDyn */
    , DoIP_TxUdpMgtList             /**< the pointer to DoIP_TxUdpMgtList */
    , 256u                          /**< the number of elements in DoIP_DiagNAckBuf */
    , 2u                            /**< the number of elements in DoIP_AliveCheckList */
    , 2u                            /**< the number of elements in DoIP_Channel */
    , 2u                            /**< the number of elements in DoIP_ChannelInd */
    , 4u                            /**< the number of elements in DoIP_Connection */
    , 1u                            /**< the number of elements in DoIP_ConnectionGroup */
    , 4u                            /**< the number of elements in DoIP_ConnectionInd */
    , 2u                            /**< the number of elements in DoIP_ConnectionTcp */
    , 2u                            /**< the number of elements in DoIP_ConnectionTcpInd */
    , 0u                            /**< the number of elements in DoIP_DefaultTester */
    , 6u                            /**< the number of elements in DoIP_EId */
    , 6u                            /**< the number of elements in DoIP_GId */
    , 2u                            /**< the number of elements in DoIP_IpAddrAssignment */
    , 1u                            /**< the number of elements in DoIP_LocalAddr */
    , 2u                            /**< the number of elements in DoIP_PduRRxCancelPduId */
    , 1u                            /**< the number of elements in DoIP_PduRTxPduId */
    , 1u                            /**< the number of elements in DoIP_RoutActivHandler */
    , 1u                            /**< the number of elements in DoIP_RoutingActivation */
    , 1u                            /**< the number of elements in DoIP_RoutingActivationInd */
    , 38u                           /**< the number of elements in DoIP_RxHdrBuf */
    , 1u                            /**< the number of elements in DoIP_Tester */
    , 84u                           /**< the number of elements in DoIP_TxHdrBuf */
    , 4u                            /**< the number of elements in DoIP_TxTcpMgt */
    , 2u                            /**< the number of elements in DoIP_TxUdpMgtList */
  }
};
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */




/**********************************************************************************************************************
 *  CALL BACK FUNCTIONS
 *********************************************************************************************************************/

#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
 *  VIN ACCESS FUNCTION
 *********************************************************************************************************************/
CONST(DoIP_GetVinFctPtrType, DOIP_CONST) DoIP_CallGetVinDirect = ApplDoIP_GetVin;

/**********************************************************************************************************************
 *  DIAGNOSTIC POWER MODE ACCESS FUNCTION
 *********************************************************************************************************************/
CONST(DoIP_PowerModeFctPtrType, DOIP_CONST) DoIP_CallPowerModeDirect = ApplDoIP_GetPowerMode; /* PRQA S 1533 */  /* MD_DoIP_ObjectOnlyAccessedOnce */

#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
 *  END OF FILE: DoIP_Lcfg.c
 *********************************************************************************************************************/

