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
 *            Module: TcpIp
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: TcpIp_Lcfg.c
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 1257 EOF */ /* MD_CSL_Rule10.3_OldValidLib */

/*lint -e552 */

#define TCPIP_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_Lcfg.h"
#include "TcpIp_Cfg.h"
#include "TcpIp.h"
#include "Det.h"
#include "Appl_Rand.h" 
#include "SoAd_Cbk.h" 


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if defined (STATIC)
#else
# define STATIC static
#endif

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
#define TCPIP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

TCPIP_P2C(TcpIp_ConfigType) TcpIp_ConfigDataPtr = NULL_PTR;

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 0612 OBJECT_SIZE */ /* MD_TcpIp_0612_BufferSize */

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  TcpIp_AddrAssignmentCfgByPrio
**********************************************************************************************************************/
/** 
  \var    TcpIp_AddrAssignmentCfgByPrio
  \brief  -
*/ 
#define TCPIP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_AddrAssignmentCfgByPrioType, TCPIP_CONST) TcpIp_AddrAssignmentCfgByPrio[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     AddrAssignmentCfgByPrio               Referable Keys */
  /*     0 */ (TCPIP_IPADDR_ASSIGNMENT_STATIC)    /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10/TcpIpIpVXCtrl/TcpIpIpV4Ctrl] */
};
#define TCPIP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_ArpConfig
**********************************************************************************************************************/
/** 
  \var    TcpIp_ArpConfig
  \details
  Element                      Description
  EntryTimeout                 Table Entry Timeout - Value of configuration parameter TcpIpArpTableEntryTimeout [MAIN_FUNCTION_CYCLES]
  RetryInterval                Retry Interval - Value of configuration parameter TcpIpArpRetryInterval [MAIN_FUNCTION_CYCLES]
  RetryTime                    Retry Timeout - Value of configuration parameter TcpIpArpRetryTime [MAIN_FUNCTION_CYCLES]
  PacketQueueEnabled           Packet Queue Enabled - Value of configuration parameter TcpIpArpPacketQueueEnabled [BOOLEAN]
  NumGratuitousArpOnStartup    Num Gratuitous ARP On Startup - Value of configuration parameter TcpIpArpNumGratuitousARPonStartup
  RequestTimeout               Value of configuration parameter TcpIpArpRequestTimeout [MAIN_FUNCTION_CYCLES]
  TableSize                    Table Size Max - Value of configuration parameter TcpIpArpTableSizeMax
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_ArpConfigType, TCPIP_CONST) TcpIp_ArpConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    EntryTimeout  RetryInterval  RetryTime  PacketQueueEnabled  NumGratuitousArpOnStartup  RequestTimeout  TableSize        Referable Keys */
  { /*     0 */        6000u,          400u,     1000u,               TRUE,                        0u,            20u,       10u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpIpConfig/TcpIpIpV4Config/TcpIpArpConfig] */
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_DefaultMulticastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_DefaultMulticastAddrV4
  \brief  -
  \details
  Element    Description
  NetAddr    -
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_DefaultMulticastAddrV4Type, TCPIP_CONST) TcpIp_DefaultMulticastAddrV4[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    NetAddr                                               Referable Keys */
  { /*     0 */ 0x01000AEFuL /*  239.10.0.1 LITTLE_ENDIAN  */  }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1] */
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_DefaultUnicastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_DefaultUnicastAddrV4
  \brief  -
  \details
  Element      Description
  DefGwAddr    -
  NetAddr      -
  NetMask      -
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_DefaultUnicastAddrV4Type, TCPIP_CONST) TcpIp_DefaultUnicastAddrV4[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DefGwAddr                                    NetAddr                                         NetMask                                                Referable Keys */
  { /*     0 */ 0x00000000uL /*  0.0.0.0 LITTLE_ENDIAN  */ , 0x21070A0AuL /*  10.10.7.33 LITTLE_ENDIAN  */ , 0x0000FFFFuL /*  255.255.0.0 LITTLE_ENDIAN  */  }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33] */
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_DuplicateAddrDetectionFctPtr
**********************************************************************************************************************/
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_DuplicateAddrDetectionCbkType, TCPIP_CONST) TcpIp_DuplicateAddrDetectionFctPtr = NULL_PTR;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_EthIfCtrl
**********************************************************************************************************************/
/** 
  \var    TcpIp_EthIfCtrl
  \brief  Array mapping from EthIfCtrlIdx to IpCtrlIdx
  \details
  Element        Description
  IpV4CtrlIdx    the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_EthIfCtrlType, TCPIP_CONST) TcpIp_EthIfCtrl[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IpV4CtrlIdx */
  { /*     0 */          0u }
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IcmpMsgHandlerCbkFctPtr
**********************************************************************************************************************/
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_IcmpMsgHandlerCbkType, TCPIP_CONST) TcpIp_IcmpMsgHandlerCbkFctPtr = NULL_PTR;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4Ctrl
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4Ctrl
  \details
  Element                            Description
  MaxTxMsgSize                       -
  MtuTx                              Value of configuration parameter EthIfCtrlMtu
  AutoIpConfigUsed                   TRUE, if the 0:1 relation has minimum 1 relation pointing to TcpIp_AutoIpConfig
  HwChecksumIcmp                     Defines if harware supports calculation of IPv4 ICMP checksum.
  AddrAssignmentCfgByPrioEndIdx      the end index of the 1:n relation pointing to TcpIp_AddrAssignmentCfgByPrio
  AddrAssignmentCfgByPrioStartIdx    the start index of the 1:n relation pointing to TcpIp_AddrAssignmentCfgByPrio
  AddrAssignmentPrioByType           -
  ArpConfigIdx                       the index of the 0:1 relation pointing to TcpIp_ArpConfig
  ArpTableEntryEndIdx                the end index of the 0:n relation pointing to TcpIp_ArpTableEntry
  ArpTableEntryStartIdx              the start index of the 0:n relation pointing to TcpIp_ArpTableEntry
  AutoIpConfigIdx                    the index of the 0:1 relation pointing to TcpIp_AutoIpConfig
  Buf2TxReqMapEndIdx                 the end index of the 1:n relation pointing to TcpIp_Buf2TxReqMap
  Buf2TxReqMapStartIdx               the start index of the 1:n relation pointing to TcpIp_Buf2TxReqMap
  DefaultTtl                         Default Time To Live - Value of configuration parameter TcpIpIpDefaultTtl
  DhcpConfigIdx                      the index of the 0:1 relation pointing to TcpIp_DhcpConfig
  DhcpStatusIdx                      the index of the 0:1 relation pointing to TcpIp_DhcpStatus
  DhcpUserOptionEndIdx               the end index of the 0:n relation pointing to TcpIp_DhcpUserOption
  DhcpUserOptionStartIdx             the start index of the 0:n relation pointing to TcpIp_DhcpUserOption
  EthIfCtrlIdx                       -
  FragmentationConfigIdx             the index of the 0:1 relation pointing to TcpIp_FragmentationConfig
  FramePrioDefault                   IP Frame Prio Default - Value of configuration parameter TcpIpIpFramePrioDefault
  GratuitousArpIdx                   the index of the 0:1 relation pointing to TcpIp_GratuitousArp
  LlAddrStateIdx                     the index of the 0:1 relation pointing to TcpIp_LlAddrState
  LocalAddrV4BroadcastIdx            the index of the 1:1 relation pointing to TcpIp_LocalAddrV4
  LocalAddrV4UnicastIdx              the index of the 1:1 relation pointing to TcpIp_LocalAddrV4
  MulticastAddrV4EndIdx              the end index of the 0:n relation pointing to TcpIp_MulticastAddrV4
  MulticastAddrV4StartIdx            the start index of the 0:n relation pointing to TcpIp_MulticastAddrV4
  StaticArpTableIdx                  the index of the 0:1 relation pointing to TcpIp_StaticArpTable
  TypeOfServiceDefault               IP Type Of Service Default - Value of configuration parameter TcpIpIpTypeOfServiceDefault
  UnicastAddrV4Idx                   the index of the 1:1 relation pointing to TcpIp_UnicastAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_IpV4CtrlType, TCPIP_CONST) TcpIp_IpV4Ctrl[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaxTxMsgSize  MtuTx  AutoIpConfigUsed  HwChecksumIcmp  AddrAssignmentCfgByPrioEndIdx  AddrAssignmentCfgByPrioStartIdx  AddrAssignmentPrioByType                                          ArpConfigIdx  ArpTableEntryEndIdx  ArpTableEntryStartIdx  AutoIpConfigIdx                     Buf2TxReqMapEndIdx  Buf2TxReqMapStartIdx  DefaultTtl  DhcpConfigIdx                     DhcpStatusIdx                     DhcpUserOptionEndIdx                     DhcpUserOptionStartIdx                     EthIfCtrlIdx                                      FragmentationConfigIdx                     FramePrioDefault  GratuitousArpIdx                     LlAddrStateIdx                     LocalAddrV4BroadcastIdx  LocalAddrV4UnicastIdx  MulticastAddrV4EndIdx  MulticastAddrV4StartIdx  StaticArpTableIdx                     TypeOfServiceDefault  UnicastAddrV4Idx        Referable Keys */
  { /*     0 */        1500u, 1500u,            FALSE,           TRUE,                            1u,                              0u,                    0x04u  /* DHCP(-), LINKLOCAL(-), STATIC(1) */,           0u,                 10u,                    0u, TCPIP_NO_AUTOIPCONFIGIDXOFIPV4CTRL,                 4u,                   0u,        64u, TCPIP_NO_DHCPCONFIGIDXOFIPV4CTRL, TCPIP_NO_DHCPSTATUSIDXOFIPV4CTRL, TCPIP_NO_DHCPUSEROPTIONENDIDXOFIPV4CTRL, TCPIP_NO_DHCPUSEROPTIONSTARTIDXOFIPV4CTRL, EthIfConf_EthIfController_EthIfController_Vlan10, TCPIP_NO_FRAGMENTATIONCONFIGIDXOFIPV4CTRL,               0u, TCPIP_NO_GRATUITOUSARPIDXOFIPV4CTRL, TCPIP_NO_LLADDRSTATEIDXOFIPV4CTRL,                      2u,                    0u,                    1u,                      0u, TCPIP_NO_STATICARPTABLEIDXOFIPV4CTRL,                   0u,               0u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4General
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4General
  \details
  Element                   Description
  IpV4CtrlDefaultIdx        the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl
  IpV4SocketDynDhcpIdx      the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn
  IpV4SocketDynIcmpIdx      the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn
  IpV4SocketDynTcpRstIdx    the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_IpV4GeneralType, TCPIP_CONST) TcpIp_IpV4General[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IpV4CtrlDefaultIdx                        IpV4SocketDynDhcpIdx                        IpV4SocketDynIcmpIdx                        IpV4SocketDynTcpRstIdx                       */
  { /*     0 */ TCPIP_NO_IPV4CTRLDEFAULTIDXOFIPV4GENERAL, TCPIP_NO_IPV4SOCKETDYNDHCPIDXOFIPV4GENERAL, TCPIP_NO_IPV4SOCKETDYNICMPIDXOFIPV4GENERAL, TCPIP_NO_IPV4SOCKETDYNTCPRSTIDXOFIPV4GENERAL }
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_LocalAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_LocalAddrV4
  \brief  -
  \details
  Element               Description
  IpV4CtrlIdx           the index of the 1:1 relation pointing to TcpIp_IpV4Ctrl
  MulticastAddrV4Idx    the index of the 0:1 relation pointing to TcpIp_MulticastAddrV4
  UnicastAddrV4Idx      the index of the 0:1 relation pointing to TcpIp_UnicastAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_LocalAddrV4Type, TCPIP_CONST) TcpIp_LocalAddrV4[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IpV4CtrlIdx  MulticastAddrV4Idx                        UnicastAddrV4Idx                              Referable Keys */
  { /*     0 */          0u, TCPIP_NO_MULTICASTADDRV4IDXOFLOCALADDRV4,                                     0u },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10/TcpIpIpVXCtrl/TcpIpIpV4Ctrl] */
  { /*     1 */          0u,                                       0u, TCPIP_NO_UNICASTADDRV4IDXOFLOCALADDRV4 },  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10/TcpIpIpVXCtrl/TcpIpIpV4Ctrl] */
  { /*     2 */          0u, TCPIP_NO_MULTICASTADDRV4IDXOFLOCALADDRV4, TCPIP_NO_UNICASTADDRV4IDXOFLOCALADDRV4 }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10/TcpIpIpVXCtrl/TcpIpIpV4Ctrl] */
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_MulticastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_MulticastAddrV4
  \brief  Structure containing all statically configured IP address information.
  \details
  Element                      Description
  DefaultMulticastAddrV4Idx    the index of the 1:1 relation pointing to TcpIp_DefaultMulticastAddrV4
  LocalAddrV4Idx               the index of the 1:1 relation pointing to TcpIp_LocalAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_MulticastAddrV4Type, TCPIP_CONST) TcpIp_MulticastAddrV4[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DefaultMulticastAddrV4Idx  LocalAddrV4Idx        Referable Keys */
  { /*     0 */                        0u,             1u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_RandomNumberFctPtr
**********************************************************************************************************************/
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_GetRandomNumberType, TCPIP_CONST) TcpIp_RandomNumberFctPtr = Appl_Crypto_GetRandNo;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_SocketOwnerConfig
**********************************************************************************************************************/
/** 
  \var    TcpIp_SocketOwnerConfig
  \brief  -
  \details
  Element                            Description
  CopyTxDataDynFuncPtr               [User]_CopyTxDataDyn Callback Function. (only required if socket owner uses indirect data provistion in Tcp/UdpTransmit.)
  CopyTxDataFuncPtr                  [User]_CopyTxData Callback Function. (only required if socket owner uses indirect data provistion in Tcp/UdpTransmit.)
  DhcpEventFuncPtr                   Callout triggered on reception and transmission of client DHCP messages.
  LocalIpAddrAssignmentChgFuncPtr    -
  RxIndicationFuncPtr                [User]_RxIndication Callback Function. (required for socket owner that recieves packets.)
  TcpAcceptedFuncPtr                 [User]_TcpAccepted Callback Function. (only required if socker passively accepts TCP connections.)
  TcpConnectedFuncPtr                [User]_TcpConnected Callback Function. (only required if socker owner actively opens TCP connections.)
  TcpIpEventFuncPtr                  [User]_TcpIpEvent Callback Function. (required for every socket owner)
  TlsValidationResultFuncPtr         [User]_TlsValidationResult Callback Function.
  TxConfirmationFuncPtr              [User]_TxConfirmation Callback Function. (optional for every socket owner)
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_SocketOwnerConfigType, TCPIP_CONST) TcpIp_SocketOwnerConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    CopyTxDataDynFuncPtr  CopyTxDataFuncPtr  DhcpEventFuncPtr  LocalIpAddrAssignmentChgFuncPtr  RxIndicationFuncPtr  TcpAcceptedFuncPtr  TcpConnectedFuncPtr  TcpIpEventFuncPtr  TlsValidationResultFuncPtr  TxConfirmationFuncPtr */
  { /*     0 */ NULL_PTR            , SoAd_CopyTxData  , NULL_PTR        , SoAd_LocalIpAddrAssignmentChg  , SoAd_RxIndication  , SoAd_TcpAccepted  , SoAd_TcpConnected  , SoAd_TcpIpEvent  , NULL_PTR                  , SoAd_TxConfirmation   }
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UnicastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_UnicastAddrV4
  \brief  Structure containing all statically configured IP address information.
  \details
  Element                            Description
  DefaultUnicastAddrV4Idx            the index of the 0:1 relation pointing to TcpIp_DefaultUnicastAddrV4
  StaticUnicastAddrV4RequestedIdx    the index of the 0:1 relation pointing to TcpIp_StaticUnicastAddrV4Requested
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_UnicastAddrV4Type, TCPIP_CONST) TcpIp_UnicastAddrV4[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DefaultUnicastAddrV4Idx  StaticUnicastAddrV4RequestedIdx        Referable Keys */
  { /*     0 */                      0u,                              0u }   /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_ArpTableEntry
**********************************************************************************************************************/
/** 
  \var    TcpIp_ArpTableEntry
  \brief  -
  \details
  Element              Description
  CreationTimeStamp    Time when this entry was created [MAIN_FUNCTION_CYCLES]
  TimeStamp            Time when this entry was marked as valid [MAIN_FUNCTION_CYCLES]
  Status               Status of this ARP entry (INVALID, INPROGRESS, VALID, PROBE)
  NetAddr              Network (IP) address of the neighbor node
  PhysAddr             Physical (MAC) address of the neighbor node
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_ArpTableEntryUType, TCPIP_VAR_NOINIT) TcpIp_ArpTableEntry;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
  /*   ... */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */
  /*     9 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_Buf2TxReqMap
**********************************************************************************************************************/
/** 
  \var    TcpIp_Buf2TxReqMap
  \brief  -
  \details
  Element          Description
  EthBufLen        -
  EthBufIdxNext    -
  SocketDynIdx     the index of the 0:1 relation pointing to TcpIp_SocketDyn
  UlTxReqIdx       -
  EthBufPtr        -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_Buf2TxReqMapUType, TCPIP_VAR_NOINIT) TcpIp_Buf2TxReqMap;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig] */
  /*   ... */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig] */
  /*     3 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4CtrlDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4CtrlDyn
  \brief  -
  \details
  Element                         Description
  ActiveAddrAssignmentMethod      -
  AddrAssignmentReadyChanged      -
  AddrAssignmentTriggeredFlags    -
  PhysLinkActive                  -
  State                           -
  ActiveDefGwAddr                 -
  ActiveNetAddr                   -
  ActiveNetMask                   -
  LastBcAddr                      -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_IpV4CtrlDynUType, TCPIP_VAR_NOINIT) TcpIp_IpV4CtrlDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4SocketDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4SocketDyn
  \brief  -
  \details
  Element                 Description
  ArpTableEntryIdx        the index of the 0:1 relation pointing to TcpIp_ArpTableEntry
  EthIfFramePrio          -
  Flags                   -
  IpV4CtrlIdx             the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl
  Protocol                -
  TimeToLive              -
  TxDescriptorProtocol    -
  TypeOfService           -
  LocSock             
  PhysDestAddr            -
  TransferBlock           -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_IpV4SocketDynUType, TCPIP_VAR_NOINIT) TcpIp_IpV4SocketDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [UDP] */
  /*     1 */  /* [UDP] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_LocalAddr
**********************************************************************************************************************/
/** 
  \var    TcpIp_LocalAddr
  \details
  Element            Description
  AssignmentState    -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_LocalAddrUType, TCPIP_VAR_NOINIT) TcpIp_LocalAddr;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33] */
  /*     1 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1] */
  /*     2 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_MulticastAddrV4Requested
**********************************************************************************************************************/
/** 
  \var    TcpIp_MulticastAddrV4Requested
  \brief  -
  \details
  Element    Description
  NetAddr    -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_MulticastAddrV4RequestedType, TCPIP_VAR_NOINIT) TcpIp_MulticastAddrV4Requested[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1, /ActiveEcuC/TcpIp/TcpIpConfig/TcpIpCtrl_Vlan10] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_SocketDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_SocketDyn
  \brief  Generic (TCP/UDP) socket variables
  \details
  Element                 Description
  ListenActiveConnStat    Current state of the socket
  LocalAddrBindIdx        the index of the 0:1 relation pointing to TcpIp_LocalAddr
  SocketOwnerConfigIdx    the index of the 0:1 relation pointing to TcpIp_SocketOwnerConfig
  TxBufRequested          TX buffer request semaphore
  TxIpAddrIdx             Index of local IPxV address that is used for transmission
  LocSock                 IP address and port of the local host
  RemSock                 IP address and port of the remote host
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_SocketDynUType, TCPIP_VAR_NOINIT) TcpIp_SocketDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [UDP] */
  /*     1 */  /* [UDP] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_SocketUdpDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_SocketUdpDyn
  \brief  UDP socket specific variables
  \details
  Element                  Description
  TxReqElemListIdx         the index of the 0:1 relation pointing to TcpIp_TxReqElemList
  TxRetrQueueMaxNum        Maximum number of TX retry queue elements for the socket.
  IpTxRequestDescriptor    TX request descriptor required for the IP layer
  TxReqIpBufPtr            Pointer to the provided TX buffer of the IP layer
  TxRetrQueue              TX retry queue
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_SocketUdpDynType, TCPIP_VAR_NOINIT) TcpIp_SocketUdpDyn[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_StaticUnicastAddrV4Requested
**********************************************************************************************************************/
/** 
  \var    TcpIp_StaticUnicastAddrV4Requested
  \brief  -
  \details
  Element      Description
  DefGwAddr    -
  NetAddr      -
  NetMask      -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_StaticUnicastAddrV4RequestedUType, TCPIP_VAR_NOINIT) TcpIp_StaticUnicastAddrV4Requested;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_NE_Fixed_10_10_7_33] */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UdpTxRetryQueueElementChain
**********************************************************************************************************************/
/** 
  \var    TcpIp_UdpTxRetryQueueElementChain
  \brief  UDP TX retry queue element chain
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_DListNodeType, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueueElementChain[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UdpTxRetryQueueElements
**********************************************************************************************************************/
/** 
  \var    TcpIp_UdpTxRetryQueueElements
  \brief  UDP TX retry queue elements
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_Udp_RetryQueueElementType, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueueElements[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UdpTxRetryQueuePoolDesc
**********************************************************************************************************************/
/** 
  \var    TcpIp_UdpTxRetryQueuePoolDesc
  \brief  UDP TX retry queue element pool
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(TcpIp_DListDescType, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueuePoolDesc[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_PCConfig
**********************************************************************************************************************/
/** 
  \var    TcpIp_PCConfig
  \details
  Element                               Description
  ArpConfig                             the pointer to TcpIp_ArpConfig
  ArpTableEntry                         the pointer to TcpIp_ArpTableEntry
  AutoIpConfig                          the pointer to TcpIp_AutoIpConfig
  DefaultMulticastAddrV4                the pointer to TcpIp_DefaultMulticastAddrV4
  DefaultUnicastAddrV4                  the pointer to TcpIp_DefaultUnicastAddrV4
  DhcpUserOption                        the pointer to TcpIp_DhcpUserOption
  DhcpUserOptionBuffer                  the pointer to TcpIp_DhcpUserOptionBuffer
  DhcpUserOptionDyn                     the pointer to TcpIp_DhcpUserOptionDyn
  FragmentationConfig                   the pointer to TcpIp_FragmentationConfig
  GratuitousArp                         the pointer to TcpIp_GratuitousArp
  LlAddrState                           the pointer to TcpIp_LlAddrState
  MulticastAddrV4                       the pointer to TcpIp_MulticastAddrV4
  MulticastAddrV4Requested              the pointer to TcpIp_MulticastAddrV4Requested
  PhysAddrConfig                        the pointer to TcpIp_PhysAddrConfig
  ReassemblyBuffer                      the pointer to TcpIp_ReassemblyBuffer
  ReassemblyBufferDesc                  the pointer to TcpIp_ReassemblyBufferDesc
  ReassemblyBufferDescDyn               the pointer to TcpIp_ReassemblyBufferDescDyn
  StaticArpEntry                        the pointer to TcpIp_StaticArpEntry
  StaticArpTable                        the pointer to TcpIp_StaticArpTable
  StaticUnicastAddrV4Requested          the pointer to TcpIp_StaticUnicastAddrV4Requested
  TxReqElem                             the pointer to TcpIp_TxReqElem
  TxReqElemList                         the pointer to TcpIp_TxReqElemList
  TxReqElemListDyn                      the pointer to TcpIp_TxReqElemListDyn
  UdpTxRetryQueueElementChain           the pointer to TcpIp_UdpTxRetryQueueElementChain
  UdpTxRetryQueueElements               the pointer to TcpIp_UdpTxRetryQueueElements
  UdpTxRetryQueuePoolDesc               the pointer to TcpIp_UdpTxRetryQueuePoolDesc
  UnicastAddrV4                         the pointer to TcpIp_UnicastAddrV4
  SizeOfArpConfig                       the number of accomplishable value elements in TcpIp_ArpConfig
  SizeOfArpTableEntry                   the number of accomplishable value elements in TcpIp_ArpTableEntry
  SizeOfAutoIpConfig                    the number of accomplishable value elements in TcpIp_AutoIpConfig
  SizeOfDefaultMulticastAddrV4          the number of accomplishable value elements in TcpIp_DefaultMulticastAddrV4
  SizeOfDefaultUnicastAddrV4            the number of accomplishable value elements in TcpIp_DefaultUnicastAddrV4
  SizeOfDhcpUserOption                  the number of accomplishable value elements in TcpIp_DhcpUserOption
  SizeOfDhcpUserOptionBuffer            the number of accomplishable value elements in TcpIp_DhcpUserOptionBuffer
  SizeOfFragmentationConfig             the number of accomplishable value elements in TcpIp_FragmentationConfig
  SizeOfGratuitousArp                   the number of accomplishable value elements in TcpIp_GratuitousArp
  SizeOfLlAddrState                     the number of accomplishable value elements in TcpIp_LlAddrState
  SizeOfMulticastAddrV4                 the number of accomplishable value elements in TcpIp_MulticastAddrV4
  SizeOfPhysAddrConfig                  the number of accomplishable value elements in TcpIp_PhysAddrConfig
  SizeOfReassemblyBuffer                the number of accomplishable value elements in TcpIp_ReassemblyBuffer
  SizeOfReassemblyBufferDesc            the number of accomplishable value elements in TcpIp_ReassemblyBufferDesc
  SizeOfStaticArpEntry                  the number of accomplishable value elements in TcpIp_StaticArpEntry
  SizeOfStaticArpTable                  the number of accomplishable value elements in TcpIp_StaticArpTable
  SizeOfStaticUnicastAddrV4Requested    the number of accomplishable value elements in TcpIp_StaticUnicastAddrV4Requested
  SizeOfTxReqElem                       the number of accomplishable value elements in TcpIp_TxReqElem
  SizeOfTxReqElemList                   the number of accomplishable value elements in TcpIp_TxReqElemList
  SizeOfUdpTxRetryQueueElementChain     the number of accomplishable value elements in TcpIp_UdpTxRetryQueueElementChain
  SizeOfUdpTxRetryQueueElements         the number of accomplishable value elements in TcpIp_UdpTxRetryQueueElements
  SizeOfUdpTxRetryQueuePoolDesc         the number of accomplishable value elements in TcpIp_UdpTxRetryQueuePoolDesc
  SizeOfUnicastAddrV4                   the number of accomplishable value elements in TcpIp_UnicastAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(TcpIp_PCConfigsType, TCPIP_CONST) TcpIp_PCConfig = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  { /* Index: 0 Keys: [Config] */
      TcpIp_ArpConfig                         /**< the pointer to TcpIp_ArpConfig */
    , TcpIp_ArpTableEntry.raw                 /**< the pointer to TcpIp_ArpTableEntry */
    , NULL_PTR                                /**< the pointer to TcpIp_AutoIpConfig */
    , TcpIp_DefaultMulticastAddrV4            /**< the pointer to TcpIp_DefaultMulticastAddrV4 */
    , TcpIp_DefaultUnicastAddrV4              /**< the pointer to TcpIp_DefaultUnicastAddrV4 */
    , NULL_PTR                                /**< the pointer to TcpIp_DhcpUserOption */
    , NULL_PTR                                /**< the pointer to TcpIp_DhcpUserOptionBuffer */
    , NULL_PTR                                /**< the pointer to TcpIp_DhcpUserOptionDyn */
    , NULL_PTR                                /**< the pointer to TcpIp_FragmentationConfig */
    , NULL_PTR                                /**< the pointer to TcpIp_GratuitousArp */
    , NULL_PTR                                /**< the pointer to TcpIp_LlAddrState */
    , TcpIp_MulticastAddrV4                   /**< the pointer to TcpIp_MulticastAddrV4 */
    , TcpIp_MulticastAddrV4Requested          /**< the pointer to TcpIp_MulticastAddrV4Requested */
    , NULL_PTR                                /**< the pointer to TcpIp_PhysAddrConfig */
    , NULL_PTR                                /**< the pointer to TcpIp_ReassemblyBuffer */
    , NULL_PTR                                /**< the pointer to TcpIp_ReassemblyBufferDesc */
    , NULL_PTR                                /**< the pointer to TcpIp_ReassemblyBufferDescDyn */
    , NULL_PTR                                /**< the pointer to TcpIp_StaticArpEntry */
    , NULL_PTR                                /**< the pointer to TcpIp_StaticArpTable */
    , TcpIp_StaticUnicastAddrV4Requested.raw  /**< the pointer to TcpIp_StaticUnicastAddrV4Requested */
    , NULL_PTR                                /**< the pointer to TcpIp_TxReqElem */
    , NULL_PTR                                /**< the pointer to TcpIp_TxReqElemList */
    , NULL_PTR                                /**< the pointer to TcpIp_TxReqElemListDyn */
    , TcpIp_UdpTxRetryQueueElementChain       /**< the pointer to TcpIp_UdpTxRetryQueueElementChain */
    , TcpIp_UdpTxRetryQueueElements           /**< the pointer to TcpIp_UdpTxRetryQueueElements */
    , TcpIp_UdpTxRetryQueuePoolDesc           /**< the pointer to TcpIp_UdpTxRetryQueuePoolDesc */
    , TcpIp_UnicastAddrV4                     /**< the pointer to TcpIp_UnicastAddrV4 */
    , 1u                                      /**< the number of elements in TcpIp_ArpConfig */
    , 10u                                     /**< the number of elements in TcpIp_ArpTableEntry */
    , 0u                                      /**< the number of elements in TcpIp_AutoIpConfig */
    , 1u                                      /**< the number of elements in TcpIp_DefaultMulticastAddrV4 */
    , 1u                                      /**< the number of elements in TcpIp_DefaultUnicastAddrV4 */
    , 0u                                      /**< the number of elements in TcpIp_DhcpUserOption */
    , 0u                                      /**< the number of elements in TcpIp_DhcpUserOptionBuffer */
    , 0u                                      /**< the number of elements in TcpIp_FragmentationConfig */
    , 0u                                      /**< the number of elements in TcpIp_GratuitousArp */
    , 0u                                      /**< the number of elements in TcpIp_LlAddrState */
    , 1u                                      /**< the number of elements in TcpIp_MulticastAddrV4 */
    , 0u                                      /**< the number of elements in TcpIp_PhysAddrConfig */
    , 0u                                      /**< the number of elements in TcpIp_ReassemblyBuffer */
    , 0u                                      /**< the number of elements in TcpIp_ReassemblyBufferDesc */
    , 0u                                      /**< the number of elements in TcpIp_StaticArpEntry */
    , 0u                                      /**< the number of elements in TcpIp_StaticArpTable */
    , 1u                                      /**< the number of elements in TcpIp_StaticUnicastAddrV4Requested */
    , 0u                                      /**< the number of elements in TcpIp_TxReqElem */
    , 0u                                      /**< the number of elements in TcpIp_TxReqElemList */
    , 3u                                      /**< the number of elements in TcpIp_UdpTxRetryQueueElementChain */
    , 3u                                      /**< the number of elements in TcpIp_UdpTxRetryQueueElements */
    , 1u                                      /**< the number of elements in TcpIp_UdpTxRetryQueuePoolDesc */
    , 1u                                      /**< the number of elements in TcpIp_UnicastAddrV4 */
  }
};
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/* PRQA L:OBJECT_SIZE */

#define TCPIP_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
 *  USER FUNCTIONS
 *********************************************************************************************************************/
/* TcpIp_<Up>GetSocket ----------------------------------------------------- */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_SoAdGetSocket(
    TcpIp_DomainType                                      Domain,
    TcpIp_ProtocolType                                    Protocol,
    P2VAR(TcpIp_SocketIdType, AUTOMATIC, TCPIP_APPL_DATA) SocketIdPtr)
{
    return TcpIp_GetSocketForUser(Domain, Protocol, SocketIdPtr, TcpIpConf_TcpIpSocketOwner_SoAd);  /* SBSW_TCPIP_NonNullPtrParameter */
}
 

#define TCPIP_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* PRQA L:MACRO_LIMIT */

/* Justification for module-specific MISRA deviations:

  MD_TEST_Rule5.5_Wrapper: Identifier '%s' is also used as a macro name.
    Reason:     Redefinition allows execution of foreign code.
    Risk:       Code is more difficult to read and to debug.
    Prevention: Code is only present in test environment and not in productive builds.
  
  MD_CSL_Rule10.3_OldValidLib: The value of an expression shall not be assigned to an object with a narrower essential
                               type or of a different essential type category.
    Reason:     Other Autosar modules generates narrow datatypes for the symbolic name values.
    Risk:       None.
    Prevention: Other modules need to change their SNV generation
  
  MD_TCPIP_CERT-DCL40-C_0789: Identifier matches other identifier(s) (e.g. '%s') in first 63 characters.
    Reason:     The rule 0789 checks if all internal identifiers are different within the first 63 characters.
    Risk:       A compiler might not correctly pre-process the software what might result in incorrect code.
    Prevention: Each delivery is integrated and tested on the real target system. In addition, preprocessors and
                compilers used in current MICROSAR projects are not expected to suffer from this (historic) limitation. 
                Compiler selection and validation is done by ECU supplier. 
  
  MD_TCPIP_CERT-ARR30-C_2842: Apparent: Dereference of an invalid pointer value.
    Reason:     A function parameter is used to access an array element. The parameter is passed by an internal TcpIp 
                function that ensures that the parameter is in a valid range. This is ensured by SafeBSW measures.
                The parameter cannot be written by other BSW module or the application.
    Risk:       None.
    Prevention: Covered by code review.
      
*/
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Lcfg.c
 *********************************************************************************************************************/
