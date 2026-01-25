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
 *            Module: Sd
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Sd_Lcfg.c
 *   Generation Time: 2026-01-24 23:52:00
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#define SD_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* PRQA S 0857 MACRO_LIMIT */ /* MD_MSR_1.1_857 */
#include "Sd.h"

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
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  Sd_Client
**********************************************************************************************************************/
/** 
  \var    Sd_Client
  \brief  Configuration data of SdClientService. List is sorted by ServiceId (and HandleId if ServiceId is not unique) per SdInstance.
  \details
  Element                                  Description
  ServiceId                                Service ID
  AutoRequire                              Auto require flag
  MinorVersionWildcard                     Indicates if MinorVersion is configured to wildcard.
  ServiceGroupMember                       Specifies if service is member of a ServiceGroup.
  CapabilityRecordEndIdx                   the end index of the 0:n relation pointing to Sd_CapabilityRecord
  CapabilityRecordFunctionCalloutPtrIdx    the index of the 0:1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr
  CapabilityRecordStartIdx                 the start index of the 0:n relation pointing to Sd_CapabilityRecord
  ClientTimerIdx                           the index of the 1:1 relation pointing to Sd_ClientTimer
  CommonInitialDelayIdx                    the index of the 0:1 relation pointing to Sd_CommonInitialDelay
  ConsumedEventgroupEndIdx                 the end index of the 0:n relation pointing to Sd_ConsumedEventgroup
  ConsumedEventgroupStartIdx               the start index of the 0:n relation pointing to Sd_ConsumedEventgroup
  HandleId                                 Handle ID
  InstanceId                               Instance ID
  InstanceIdx                              the index of the 1:1 relation pointing to Sd_Instance
  MajorVersion                             Major Version
  MethodIdx                                the index of the 0:1 relation pointing to Sd_Method
  MinorVersion                             Minor Version
  TcpSoConIdEndIdx                         the end index of the 0:n relation pointing to Sd_TcpSoConId
  TcpSoConIdStartIdx                       the start index of the 0:n relation pointing to Sd_TcpSoConId
  UdpSoConEndIdx                           the end index of the 0:n relation pointing to Sd_UdpSoCon
  UdpSoConStartIdx                         the start index of the 0:n relation pointing to Sd_UdpSoCon
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ClientType, SD_CONST) Sd_Client[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ServiceId  AutoRequire  MinorVersionWildcard  ServiceGroupMember  CapabilityRecordEndIdx                CapabilityRecordFunctionCalloutPtrIdx                CapabilityRecordStartIdx                ClientTimerIdx  CommonInitialDelayIdx                ConsumedEventgroupEndIdx  ConsumedEventgroupStartIdx  HandleId  InstanceId  InstanceIdx  MajorVersion  MethodIdx                MinorVersion  TcpSoConIdEndIdx                TcpSoConIdStartIdx                UdpSoConEndIdx                UdpSoConStartIdx                      Referable Keys */
  { /*     0 */    50123u,       FALSE,                FALSE,              FALSE, SD_NO_CAPABILITYRECORDENDIDXOFCLIENT, SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT, SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT,             0u, SD_NO_COMMONINITIALDELAYIDXOFCLIENT,                       1u,                         0u,       0u,         1u,          0u,           1u, SD_NO_METHODIDXOFCLIENT,           0u, SD_NO_TCPSOCONIDENDIDXOFCLIENT, SD_NO_TCPSOCONIDSTARTIDXOFCLIENT,                           3u,                             0u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
  { /*     1 */    50124u,       FALSE,                FALSE,              FALSE, SD_NO_CAPABILITYRECORDENDIDXOFCLIENT, SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT, SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT,             0u, SD_NO_COMMONINITIALDELAYIDXOFCLIENT,                       3u,                         2u,       2u,         1u,          0u,           1u, SD_NO_METHODIDXOFCLIENT,           0u,                             2u,                               1u, SD_NO_UDPSOCONENDIDXOFCLIENT, SD_NO_UDPSOCONSTARTIDXOFCLIENT },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_33_47842] */
  { /*     2 */    50125u,       FALSE,                FALSE,              FALSE, SD_NO_CAPABILITYRECORDENDIDXOFCLIENT, SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT, SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT,             0u, SD_NO_COMMONINITIALDELAYIDXOFCLIENT,                       2u,                         1u,       1u,         1u,          0u,           1u, SD_NO_METHODIDXOFCLIENT,           0u, SD_NO_TCPSOCONIDENDIDXOFCLIENT, SD_NO_TCPSOCONIDSTARTIDXOFCLIENT,                           3u,                             0u }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientMap
**********************************************************************************************************************/
/** 
  \var    Sd_ClientMap
  \brief  Handle ID map for SdClientServices
  \details
  Element       Description
  InvalidHnd    FALSE, if the handle of Sd_ClientMap is valid and can be used in the embedded code for further processing in the embedded code.
  ClientIdx     the index of the 0:1 relation pointing to Sd_Client
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ClientMapType, SD_CONST) Sd_ClientMap[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  ClientIdx */
  { /*     0 */      FALSE,        0u },
  { /*     1 */      FALSE,        2u },
  { /*     2 */      FALSE,        1u }
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientTimer
**********************************************************************************************************************/
/** 
  \var    Sd_ClientTimer
  \brief  Timer parameter for SdClientService and SdConsumedEventgroup
  \details
  Element                           Description
  TTL                               Time To Live
  InitialFindDelayMax               Maximal initial delay for FindService message
  InitialFindDelayMin               Minimal initial delay for FindService message
  InitialFindRepetitionBaseDelay    Base delay for FindService messages during initial find phase. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS.
  InitialFindRepetitionsMax         Amount of FindService messages transmitted during initial find phase
  RequestResponseMaxDelay           Maximal request-response delay
  RequestResponseMinDelay           Minimal request-response delay
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ClientTimerType, SD_CONST) Sd_ClientTimer[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TTL        InitialFindDelayMax  InitialFindDelayMin  InitialFindRepetitionBaseDelay  InitialFindRepetitionsMax  RequestResponseMaxDelay  RequestResponseMinDelay        Referable Keys */
  { /*     0 */ 16777215u,                 10u,                 10u,                            55u,                        9u,                      0u,                      0u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientServiceTimer] */
  { /*     1 */ 16777215u,                  0u,                  0u,                             0u,                        0u,                     20u,                      0u }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientEventGroupTimer] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ConsumedEventgroup
**********************************************************************************************************************/
/** 
  \var    Sd_ConsumedEventgroup
  \brief  Configuration data of SdConsumedEventgroup
  \details
  Element                           Description
  AutoRequire                       Auto require flag
  ClientIdx                         the index of the 1:1 relation pointing to Sd_Client
  ClientTimerIdx                    the index of the 1:1 relation pointing to Sd_ClientTimer
  EventGroupId                      Eventgroup ID
  HandleId                          Handle ID
  MulticastEndpointAddrIdx          the index of the 0:1 relation pointing to Sd_MulticastEndpointAddr
  MulticastSoConIdEndIdx            the end index of the 0:n relation pointing to Sd_MulticastSoConId
  MulticastSoConIdStartIdx          the start index of the 0:n relation pointing to Sd_MulticastSoConId
  RoutingGroupMulticastActRefIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupTcpActRefIdx          the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupUdpActRefIdx          the index of the 0:1 relation pointing to Sd_RoutingGroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ConsumedEventgroupType, SD_CONST) Sd_ConsumedEventgroup[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    AutoRequire  ClientIdx  ClientTimerIdx  EventGroupId  HandleId  MulticastEndpointAddrIdx                            MulticastSoConIdEndIdx                            MulticastSoConIdStartIdx                            RoutingGroupMulticastActRefIdx                            RoutingGroupTcpActRefIdx                            RoutingGroupUdpActRefIdx                                  Referable Keys */
  { /*     0 */       FALSE,        0u,             1u,           1u,       0u,                                                 0u,                                               1u,                                                 0u,                                                       5u, SD_NO_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP,                                                 6u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed/SdConsumedEventGroup_0xC3CB_VechicleSpeed, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed] */
  { /*     1 */       FALSE,        2u,             1u,           1u,       1u,                                                 1u,                                               2u,                                                 1u,                                                       7u, SD_NO_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP,                                                 8u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo/SdConsumedEventGroup_0xC3CD_VechicleInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo] */
  { /*     2 */       FALSE,        1u,             1u,           1u,       2u, SD_NO_MULTICASTENDPOINTADDRIDXOFCONSUMEDEVENTGROUP, SD_NO_MULTICASTSOCONIDENDIDXOFCONSUMEDEVENTGROUP, SD_NO_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP, SD_NO_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP,                                                 9u, SD_NO_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus/SdConsumedEventGroup_0xC3CC_VechicleStatus, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ConsumedEventgroupMap
**********************************************************************************************************************/
/** 
  \var    Sd_ConsumedEventgroupMap
  \brief  Handle ID map for SdConsumedEventgroups
  \details
  Element                  Description
  InvalidHnd               FALSE, if the handle of Sd_ConsumedEventgroupMap is valid and can be used in the embedded code for further processing in the embedded code.
  ConsumedEventgroupIdx    the index of the 0:1 relation pointing to Sd_ConsumedEventgroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ConsumedEventgroupMapType, SD_CONST) Sd_ConsumedEventgroupMap[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  ConsumedEventgroupIdx */
  { /*     0 */      FALSE,                    0u },
  { /*     1 */      FALSE,                    1u },
  { /*     2 */      FALSE,                    2u }
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandler
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandler
  \brief  Configuration data of SdEventHandler
  \details
  Element                       Description
  ClientListEndIdx              the end index of the 1:n relation pointing to Sd_ClientList
  ClientListStartIdx            the start index of the 1:n relation pointing to Sd_ClientList
  EventGroupId                  Eventgroup ID
  EventHandlerMulticastIdx      the index of the 0:1 relation pointing to Sd_EventHandlerMulticast
  EventHandlerTcpIdx            the index of the 0:1 relation pointing to Sd_EventHandlerTcp
  EventHandlerUdpIdx            the index of the 0:1 relation pointing to Sd_EventHandlerUdp
  HandleId                      Handle ID
  MulticastThreshold            Multicast threshold
  ServerIdx                     the index of the 1:1 relation pointing to Sd_Server
  ServerTimerIdx                the index of the 1:1 relation pointing to Sd_ServerTimer
  SoConActivationMapEndIdx      the end index of the 0:n relation pointing to Sd_SoConActivationMap
  SoConActivationMapStartIdx    the start index of the 0:n relation pointing to Sd_SoConActivationMap
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_EventHandlerType, SD_CONST) Sd_EventHandler[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ClientListEndIdx  ClientListStartIdx  EventGroupId  EventHandlerMulticastIdx                      EventHandlerTcpIdx                      EventHandlerUdpIdx                      HandleId  MulticastThreshold  ServerIdx  ServerTimerIdx  SoConActivationMapEndIdx  SoConActivationMapStartIdx        Referable Keys */
  { /*     0 */               2u,                 0u,           1u,                                           0u, SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER,                                     0u,       0u,                 2u,        0u,             0u,                       2u,                         0u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo] */
  { /*     1 */               4u,                 2u,           1u,                                           1u, SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER,                                     1u,       2u,                 2u,        2u,             0u,                       4u,                         2u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState] */
  { /*     2 */               5u,                 4u,           1u, SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER,                                     0u, SD_NO_EVENTHANDLERUDPIDXOFEVENTHANDLER,       1u,                 0u,        1u,             0u,                       5u,                         4u }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState/SdEventHandler_0xC3C1_EcuState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerMulticast
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerMulticast
  \brief  Configuration of SdEventHandlerMulticast
  \details
  Element                  Description
  RoutingGroupActRefIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
  SoConId                  SocketConnection used for multicast transmittsion
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_EventHandlerMulticastType, SD_CONST) Sd_EventHandlerMulticast[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RoutingGroupActRefIdx  SoConId                                                                             Referable Keys */
  { /*     0 */                    1u, SoAdConf_SoAdSocketConnection_SC_UDP_Multicast_Fixed_239_23_0_1_40000_Remote },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo] */
  { /*     1 */                    3u, SoAdConf_SoAdSocketConnection_SC_UDP_Multicast_Fixed_239_23_0_1_40000_Remote }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerTcp
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerTcp
  \brief  Configuration of SdEventHandlerTcp
  \details
  Element                   Description
  RoutingGroupActRefIdx     the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupTriggerIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_EventHandlerTcpType, SD_CONST) Sd_EventHandlerTcp[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RoutingGroupActRefIdx  RoutingGroupTriggerIdx                               Referable Keys */
  { /*     0 */                    4u, SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState/SdEventHandler_0xC3C1_EcuState] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerUdp
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerUdp
  \brief  Configuration of SdEventHandlerUdp
  \details
  Element                   Description
  RoutingGroupActRefIdx     the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupTriggerIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_EventHandlerUdpType, SD_CONST) Sd_EventHandlerUdp[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RoutingGroupActRefIdx  RoutingGroupTriggerIdx                               Referable Keys */
  { /*     0 */                    0u, SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo] */
  { /*     1 */                    2u, SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_Instance
**********************************************************************************************************************/
/** 
  \var    Sd_Instance
  \brief  Configuration data for SdInstance
  \details
  Element                     Description
  MulticastRxPduId            RX PDU ID used for multicast reception
  TxPduId                     TX PDU ID used for message transmission
  UnicastRxPduId              RX PDU ID used for unicast reception
  AddressStorageEndIdx        the end index of the 1:n relation pointing to Sd_AddressStorage
  AddressStorageStartIdx      the start index of the 1:n relation pointing to Sd_AddressStorage
  CapabilityRecordEndIdx      the end index of the 0:n relation pointing to Sd_CapabilityRecord
  CapabilityRecordStartIdx    the start index of the 0:n relation pointing to Sd_CapabilityRecord
  ClientEndIdx                the end index of the 0:n relation pointing to Sd_Client
  ClientStartIdx              the start index of the 0:n relation pointing to Sd_Client
  EndpointStorageEndIdx       the end index of the 1:n relation pointing to Sd_EndpointStorage
  EndpointStorageStartIdx     the start index of the 1:n relation pointing to Sd_EndpointStorage
  QueueProcessLimit           Maximum number of Rx Queue Entries which shall be processed during one MainFunction cycle.
  RetryDelay                  Delay when a not answered subscription will be retriggered.
  RetryMax                    Maximum count of subscription retries.
  RxEventEndIdx               the end index of the 0:n relation pointing to Sd_RxEvent
  RxEventStartIdx             the start index of the 0:n relation pointing to Sd_RxEvent
  SendEntryEndIdx             the end index of the 1:n relation pointing to Sd_SendEntry
  SendEntryStartIdx           the start index of the 1:n relation pointing to Sd_SendEntry
  ServerEndIdx                the end index of the 0:n relation pointing to Sd_Server
  ServerStartIdx              the start index of the 0:n relation pointing to Sd_Server
  TcpSoConIdEndIdx            the end index of the 0:n relation pointing to Sd_TcpSoConId
  TcpSoConIdStartIdx          the start index of the 0:n relation pointing to Sd_TcpSoConId
  UdpSoConEndIdx              the end index of the 0:n relation pointing to Sd_UdpSoCon
  UdpSoConStartIdx            the start index of the 0:n relation pointing to Sd_UdpSoCon
  EMalformedMsgId             DEM Event ID for malformed messages
  ENackRecvId                 DEM Event ID for received SubscribeEventgroupNack messages
  EOutOfResId                 DEM Event ID for too few available resources
  MulticastRxSoConId          RX SocketConnection ID used for multicast reception
  TxSoConId                   TX SocketConnection ID used for message transmission
  UnicastRxSoConId            RX SocketConnection ID used for unicast reception
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_InstanceType, SD_CONST) Sd_Instance[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MulticastRxPduId                                          TxPduId                                        UnicastRxPduId                                        AddressStorageEndIdx  AddressStorageStartIdx  CapabilityRecordEndIdx                  CapabilityRecordStartIdx                  ClientEndIdx  ClientStartIdx  EndpointStorageEndIdx  EndpointStorageStartIdx  QueueProcessLimit  RetryDelay  RetryMax  RxEventEndIdx  RxEventStartIdx  SendEntryEndIdx  SendEntryStartIdx  ServerEndIdx  ServerStartIdx  TcpSoConIdEndIdx  TcpSoConIdStartIdx  UdpSoConEndIdx  UdpSoConStartIdx  EMalformedMsgId  ENackRecvId    EOutOfResId    MulticastRxSoConId                                                       TxSoConId                                                            UnicastRxSoConId                                                           Referable Keys */
  { /*     0 */ SdConf_SdInstanceMulticastRxPdu_SdInstanceMulticastRxPdu, SoAdConf_SoAdPduRoute_SoAdPduRoute_SD_Ctrl_Tx, SdConf_SdInstanceUnicastRxPdu_SdInstanceUnicastRxPdu,                  10u,                     0u, SD_NO_CAPABILITYRECORDENDIDXOFINSTANCE, SD_NO_CAPABILITYRECORDSTARTIDXOFINSTANCE,           3u,             0u,                   20u,                      0u,               32u,         0u,       0u,           32u,              0u,             32u,                0u,           3u,             0u,               2u,                 0u,             3u,               0u, SD_INV_DEM_ID  , SD_INV_DEM_ID, SD_INV_DEM_ID, SoAdConf_SoAdSocketConnection_SC_SD_CTRL_UDP_Any_DynamicPort_Remote_001, SoAdConf_SoAdSocketConnection_SC_SD_CTRL_UDP_Any_DynamicPort_Remote, SoAdConf_SoAdSocketConnection_SC_SD_CTRL_UDP_Any_DynamicPort_Remote }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_IpAddrRequest
**********************************************************************************************************************/
/** 
  \var    Sd_IpAddrRequest
  \brief  Management structure for IP address requests of multicast IP addresses
  \details
  Element                    Description
  StaticIpConfiguration      Indicates if a static IP address is configured
  StaticPortConfiguration    Indicates is a static port is configured
  PortSetIdx                 the index of the 1:1 relation pointing to Sd_PortSet
  RequestCntIdx              the index of the 1:1 relation pointing to Sd_RequestCnt
  SoConId                    SocketConnection ID
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_IpAddrRequestType, SD_CONST) Sd_IpAddrRequest[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    StaticIpConfiguration  StaticPortConfiguration  PortSetIdx  RequestCntIdx  SoConId                                                     */
  { /*     0 */                 FALSE,                    TRUE,         0u,            0u, SoAdConf_SoAdSocketConnection_SC_UDP_Multicast_Rx_Any_40000 }
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_MulticastSoConId
**********************************************************************************************************************/
/** 
  \var    Sd_MulticastSoConId
  \brief  SocketConnections used for multicast communication
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SoConIdType, SD_CONST) Sd_MulticastSoConId[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     MulticastSoConId                                                 Referable Keys */
  /*     0 */ SoAdConf_SoAdSocketConnection_SC_UDP_Multicast_Rx_Any_40000 ,  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed/SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  /*     1 */ SoAdConf_SoAdSocketConnection_SC_UDP_Multicast_Rx_Any_40000    /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo/SdConsumedEventGroup_0xC3CD_VechicleInfo] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RoutingGroup
**********************************************************************************************************************/
/** 
  \var    Sd_RoutingGroup
  \brief  SoAd RoutingGroups relevant for SD
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_RoutingGroupIdType, SD_CONST) Sd_RoutingGroup[10] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RoutingGroup                                                      Referable Keys */
  /*     0 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_FaultInfo_AC      ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC] */
  /*     1 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_FaultInfo_AM      ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  /*     2 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_SenState_AC       ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC] */
  /*     3 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_SenState_AM       ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  /*     4 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_EcuState_AC       ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC] */
  /*     5 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_VechicleSpeed_AM  ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  /*     6 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_VechicleSpeed_AC  ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC] */
  /*     7 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_VechicleInfo_AM   ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AM] */
  /*     8 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_VechicleInfo_AC   ,  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC] */
  /*     9 */ SoAdConf_SoAdRoutingGroup_SoAdRoutingGroup_VechicleStatus_AC    /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_Server
**********************************************************************************************************************/
/** 
  \var    Sd_Server
  \brief  Configuration data of SdServerService. List is sorted by ServiceId (and HandleId if ServiceId is not unique) per SdInstance.
  \details
  Element                                  Description
  ServiceId                                Service ID
  AutoAvailable                            Auto available flag
  ServiceGroupMember                       Specifies if service is member of a ServiceGroup.
  CapabilityRecordEndIdx                   the end index of the 0:n relation pointing to Sd_CapabilityRecord
  CapabilityRecordFunctionCalloutPtrIdx    the index of the 0:1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr
  CapabilityRecordStartIdx                 the start index of the 0:n relation pointing to Sd_CapabilityRecord
  CommonInitialDelayIdx                    the index of the 0:1 relation pointing to Sd_CommonInitialDelay
  EventHandlerEndIdx                       the end index of the 0:n relation pointing to Sd_EventHandler
  EventHandlerStartIdx                     the start index of the 0:n relation pointing to Sd_EventHandler
  HandleId                                 Handle ID
  InstanceId                               Instance ID
  InstanceIdx                              the index of the 1:1 relation pointing to Sd_Instance
  MajorVersion                             Major Version
  MethodIdx                                the index of the 0:1 relation pointing to Sd_Method
  MinorVersion                             Minor Version
  ServerTimerIdx                           the index of the 1:1 relation pointing to Sd_ServerTimer
  TcpSoConIdEndIdx                         the end index of the 0:n relation pointing to Sd_TcpSoConId
  TcpSoConIdStartIdx                       the start index of the 0:n relation pointing to Sd_TcpSoConId
  UdpSoConEndIdx                           the end index of the 0:n relation pointing to Sd_UdpSoCon
  UdpSoConStartIdx                         the start index of the 0:n relation pointing to Sd_UdpSoCon
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ServerType, SD_CONST) Sd_Server[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ServiceId  AutoAvailable  ServiceGroupMember  CapabilityRecordEndIdx                CapabilityRecordFunctionCalloutPtrIdx                CapabilityRecordStartIdx                CommonInitialDelayIdx                EventHandlerEndIdx  EventHandlerStartIdx  HandleId  InstanceId  InstanceIdx  MajorVersion  MethodIdx                MinorVersion  ServerTimerIdx  TcpSoConIdEndIdx                TcpSoConIdStartIdx                UdpSoConEndIdx                UdpSoConStartIdx                      Referable Keys */
  { /*     0 */    50112u,         FALSE,              FALSE, SD_NO_CAPABILITYRECORDENDIDXOFSERVER, SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER, SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER, SD_NO_COMMONINITIALDELAYIDXOFSERVER,                 1u,                   0u,       1u,        23u,          0u,           1u, SD_NO_METHODIDXOFSERVER,           0u,             1u, SD_NO_TCPSOCONIDENDIDXOFSERVER, SD_NO_TCPSOCONIDSTARTIDXOFSERVER,                           3u,                             0u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
  { /*     1 */    50113u,         FALSE,              FALSE, SD_NO_CAPABILITYRECORDENDIDXOFSERVER, SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER, SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER, SD_NO_COMMONINITIALDELAYIDXOFSERVER,                 3u,                   2u,       0u,         1u,          0u,           1u, SD_NO_METHODIDXOFSERVER,           0u,             1u,                             1u,                               0u, SD_NO_UDPSOCONENDIDXOFSERVER, SD_NO_UDPSOCONSTARTIDXOFSERVER },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_33_47843] */
  { /*     2 */    50113u,         FALSE,              FALSE, SD_NO_CAPABILITYRECORDENDIDXOFSERVER, SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER, SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER, SD_NO_COMMONINITIALDELAYIDXOFSERVER,                 2u,                   1u,       2u,        23u,          0u,           1u, SD_NO_METHODIDXOFSERVER,           0u,             1u, SD_NO_TCPSOCONIDENDIDXOFSERVER, SD_NO_TCPSOCONIDSTARTIDXOFSERVER,                           3u,                             0u }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ServerMap
**********************************************************************************************************************/
/** 
  \var    Sd_ServerMap
  \brief  Handle ID map for SdServerServices
  \details
  Element       Description
  InvalidHnd    FALSE, if the handle of Sd_ServerMap is valid and can be used in the embedded code for further processing in the embedded code.
  ServerIdx     the index of the 0:1 relation pointing to Sd_Server
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ServerMapType, SD_CONST) Sd_ServerMap[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InvalidHnd  ServerIdx */
  { /*     0 */      FALSE,        1u },
  { /*     1 */      FALSE,        0u },
  { /*     2 */      FALSE,        2u }
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ServerTimer
**********************************************************************************************************************/
/** 
  \var    Sd_ServerTimer
  \brief  Timer parameter for SdServerService and SdEventHandler
  \details
  Element                            Description
  TTL                                Time To Live
  InitialOfferDelayMax               Initial maximal Offer delay
  InitialOfferDelayMin               Initial minimal Offer delay
  InitialOfferRepetitionBaseDelay    Base delay used for timing of OfferServices messages during repetition phase. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS.
  InitialOfferRepetitionsMax         Amount of OfferService messages transmitted during repetition phase
  OfferCyclicDelay                   Delay used for cyclic transmission of OfferService messages. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS.
  RequestResponseMaxDelay            Maximal request-response delay
  RequestResponseMinDelay            Minimal request-response delay
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_ServerTimerType, SD_CONST) Sd_ServerTimer[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TTL        InitialOfferDelayMax  InitialOfferDelayMin  InitialOfferRepetitionBaseDelay  InitialOfferRepetitionsMax  OfferCyclicDelay  RequestResponseMaxDelay  RequestResponseMinDelay        Referable Keys */
  { /*     0 */        5u,                   0u,                   0u,                              0u,                         0u,               0u,                    100u,                     10u },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerEventHandlerTimer] */
  { /*     1 */ 16777215u,                  10u,                  10u,                            220u,                         2u,               0u,                      0u,                      0u }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerServiceTimer] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TcpSoConId
**********************************************************************************************************************/
/** 
  \var    Sd_TcpSoConId
  \brief  Available TCP SocketConnections
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(SoAd_SoConIdType, SD_CONST) Sd_TcpSoConId[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TcpSoConId                                                          Referable Keys */
  /*     0 */ SoAdConf_SoAdSocketConnection_SC_TCP_TX_fixed_10_23_0_33_47843 ,  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_33_47843] */
  /*     1 */ SoAdConf_SoAdSocketConnection_SC_TCP_TX_fixed_10_23_0_33_47842    /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_33_47842] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_UdpSoCon
**********************************************************************************************************************/
/** 
  \var    Sd_UdpSoCon
  \brief  Available UDP SocketConnections
  \details
  Element          Description
  Preconfigured    Specifies if SoCon is preconfigured with IP and Port or not
  Id               IDs of UDP SocketConnections
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_UdpSoConType, SD_CONST) Sd_UdpSoCon[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Preconfigured  Id                                                                                  Referable Keys */
  { /*     0 */         FALSE, SoAdConf_SoAdSocketConnection_SC_UDP_Multicast_Fixed_239_23_0_1_40000_Remote },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
  { /*     1 */         FALSE, SoAdConf_SoAdSocketConnection_SC_UDP_Fixed_10_23_0_33_40000_0                },  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
  { /*     2 */         FALSE, SoAdConf_SoAdSocketConnection_SC_UDP_Fixed_10_23_0_33_40000_1                }   /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_AddressStorage
**********************************************************************************************************************/
/** 
  \var    Sd_AddressStorage
  \brief  State information of communication partner
  \details
  Element                  Description
  RxMulticastSessionId     RX multicast session ID
  RxUnicastSessionId       RX unicast session ID
  SessionIdCounter         TX session ID
  Flags                    TX flags
  RxMulticastFlags         RX multicast flags
  RxUnicastFlags           RX unicast flags
  SendEntryNrPendingIdx    the index of the 1:1 relation pointing to Sd_SendEntry
  Addr                     Address of the communication partner
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_AddressStorageUType, SD_VAR_NOINIT) Sd_AddressStorage;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*   ... */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*     9 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientDyn
**********************************************************************************************************************/
/** 
  \var    Sd_ClientDyn
  \brief  Dynamic configuration data for SdClientService
  \details
  Element                           Description
  OfferedTTL                        Offered Time To Live
  AddressStorageServerIdx           the index of the 0:1 relation pointing to Sd_AddressStorage
  RepetitionRun                     Repetition run counter
  RetryCounter                      Counter for subscribe eventgroup retry handling.
  ServiceGroupReqCounter            Client request counter for ServiceGroup service API
  StateMachineExecutionRequested    Flag if State machine shall be executed for this client
  CurrentState                      Current state
  EventMain                         Event processed in MainFunction.
  EventRx                           Received event
  MethodTcpSoConId                  TCP method SoConId
  MethodUdpSoConId                  UDP method SoConId
  RetryTimer                        Timer for subscribe eventgroup retry handling.
  ServerTcpEndpointAddr             Server TCP endpoint address
  ServerUdpEndpointAddr             Server UDP endpoint address
  StateMachine                      State machine
  StateSwc                          Requested state
  TimeToTriggerSend                 Time to trigger next message transmission
  TimerTTL                          Time To Live
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_ClientDynType, SD_VAR_NOINIT) Sd_ClientDyn[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_33_47842] */
  /*     2 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientList
**********************************************************************************************************************/
/** 
  \var    Sd_ClientList
  \brief  Dynamic data of subscribed clients
  \details
  Element                  Description
  RequestedTTL             Requested TimeToLive
  RxReserved               Received reserved field
  AddressStorageIdx        the index of the 0:1 relation pointing to Sd_AddressStorage
  EndpointStorageTcpIdx    the index of the 0:1 relation pointing to Sd_EndpointStorage
  EndpointStorageUdpIdx    the index of the 0:1 relation pointing to Sd_EndpointStorage
  NrOfReferences           Number of simultaneous subscriptions
  AssignedTcpSoConId       Used TCP SocketConnection ID
  AssignedUdpSoConId       Used UDP SocketConnection ID
  ClientState              State of the client
  SubscribedUntil          Point in time till the client is subscribed
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_ClientListUType, SD_VAR_NOINIT) Sd_ClientList;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo] */
  /*     2 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState] */
  /*     3 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState] */
  /*     4 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState/SdEventHandler_0xC3C1_EcuState] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ConsumedEventgroupDyn
**********************************************************************************************************************/
/** 
  \var    Sd_ConsumedEventgroupDyn
  \brief  Dynamic configuration of SdConsumedEventgroup
  \details
  Element                  Description
  AcknowledgedTTL          Acknowledge Time To Live
  RxIndicationCount        Counter to differentiate RxIndication calls.
  SoConMarkedForClosure    Flag if EventGroup has been unconfigured and SoCon can be closed.
  TriggerSubscription      Flag indicating if a subscription shall be triggered.
  CurrentState             Current state
  Event                    Received event
  MulticastSoConId         Configured multicast SocketConnection
  ServiceModeRequest       Requested state
  StateMachine             State machine
  TcpSoConId               Configured TCP SocketConnection
  TimerTTL                 Time To Live
  UdpSoConId               Configured UDP SocketConnection
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_ConsumedEventgroupDynType, SD_VAR_NOINIT) Sd_ConsumedEventgroupDyn[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed/SdConsumedEventGroup_0xC3CB_VechicleSpeed, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo/SdConsumedEventGroup_0xC3CD_VechicleInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo] */
  /*     2 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus/SdConsumedEventGroup_0xC3CC_VechicleStatus, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EndpointStorage
**********************************************************************************************************************/
/** 
  \var    Sd_EndpointStorage
  \brief  Received endpoint options
  \details
  Element           Description
  NrOfReferences    Number of external references
  Addr              Endpoint address
  Type              Endpoint type
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_EndpointStorageUType, SD_VAR_NOINIT) Sd_EndpointStorage;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*   ... */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*    19 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerDyn
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerDyn
  \brief  Dynamic configuration of SdEventHandler
  \details
  Element         Description
  NrOfClients     Nr of subscribed clients
  RequestState    Request state
  StateMachine    State machine
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_EventHandlerDynType, SD_VAR_NOINIT) Sd_EventHandlerDyn[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState] */
  /*     2 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState/SdEventHandler_0xC3C1_EcuState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_InstanceDyn
**********************************************************************************************************************/
/** 
  \var    Sd_InstanceDyn
  \brief  Variable data for each SdInstance
  \details
  Element                  Description
  RxEventEndIdx            the index of the 1:1 relation pointing to Sd_RxEvent
  RxEventListFull          Full flag of dynamic queue
  RxEventStartIdx          the index of the 1:1 relation pointing to Sd_RxEvent
  SendEntryEndIdx          the index of the 0:1 relation pointing to Sd_SendEntry
  SendEntryNrPendingIdx    the index of the 1:1 relation pointing to Sd_SendEntry
  SendEntryStartIdx        the index of the 0:1 relation pointing to Sd_SendEntry
  NextStateMachineRun      Time indicating next execution of state machines
  RunMode                  Communication mode
  State                    State
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_InstanceDynType, SD_VAR_NOINIT) Sd_InstanceDyn[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdClientService_0xC3CC_VechicleStatus] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_MulticastEndpointAddr
**********************************************************************************************************************/
/** 
  \var    Sd_MulticastEndpointAddr
  \brief  Server multicast endpoint address
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_MulticastEndpointAddrUType, SD_VAR_NOINIT) Sd_MulticastEndpointAddr;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CB_VechicleSpeed/SdConsumedEventGroup_0xC3CB_VechicleSpeed] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdCLientService_0xC3CD_VechicleInfo/SdConsumedEventGroup_0xC3CD_VechicleInfo] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_NrOfOptions
**********************************************************************************************************************/
/** 
  \var    Sd_NrOfOptions
  \brief  Number of options saved in the OptionIndex
*/ 
#define SD_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_NrOfOptionsType, SD_VAR_NOINIT) Sd_NrOfOptions;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define SD_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_OptionIndex
**********************************************************************************************************************/
/** 
  \var    Sd_OptionIndex
  \brief  Payload offset of options
*/ 
#define SD_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_OptionIndexType, SD_VAR_NOINIT) Sd_OptionIndex[10];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define SD_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_Payload
**********************************************************************************************************************/
/** 
  \var    Sd_Payload
  \brief  Buffer used for message transmission
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_PayloadType, SD_VAR_NOINIT) Sd_Payload[1464];  /* PRQA S 1514, 1533, 0612, 0613 */  /* MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_BigStructure, MD_CSL_BigStructure */
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_PortSet
**********************************************************************************************************************/
/** 
  \var    Sd_PortSet
  \brief  Indicates if the port is already set
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_PortSetUType, SD_VAR_NOINIT) Sd_PortSet;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_Multicast_Rx_Any_40000] */

#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RequestCnt
**********************************************************************************************************************/
/** 
  \var    Sd_RequestCnt
  \brief  Nr of IP address assignment requests
*/ 
#define SD_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_RequestCntUType, SD_VAR_NOINIT) Sd_RequestCnt;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/TcpIp/TcpIpConfig/TcpIpLocalAddr_Multicast_Any_vlan23] */

#define SD_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RoutingGroupDyn
**********************************************************************************************************************/
/** 
  \var    Sd_RoutingGroupDyn
  \brief  Dynamic data of SoAd RoutingGroups relevant for SD
  \details
  Element    Description
  Status     Status (disabled/enabled/unknown) of RoutingGroup
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_RoutingGroupDynUType, SD_VAR_NOINIT) Sd_RoutingGroupDyn;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AC] */
  /*     1 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_FaultInfo_AM] */
  /*     2 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AC] */
  /*     3 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_SenState_AM] */
  /*     4 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_EcuState_AC] */
  /*     5 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AM] */
  /*     6 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleSpeed_AC] */
  /*     7 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AM] */
  /*     8 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleInfo_AC] */
  /*     9 */  /* [/ActiveEcuC/SoAd/SoAdConfig/SoAdRoutingGroup_VechicleStatus_AC] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RxEvent
**********************************************************************************************************************/
/** 
  \var    Sd_RxEvent
  \brief  Saves received server events
  \details
  Element            Description
  ClientListIdx      the index of the 0:1 relation pointing to Sd_ClientList
  EventHandlerIdx    the index of the 0:1 relation pointing to Sd_EventHandler
  Event              Received event
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_RxEventUType, SD_VAR_NOINIT) Sd_RxEvent;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*   ... */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*    31 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_SendEntry
**********************************************************************************************************************/
/** 
  \var    Sd_SendEntry
  \brief  Saves messages which shall be transmitted
  \details
  Element                  Description
  EventHandlerId           EventHandler ID
  InstanceId               Instance ID
  ReservedField            Reserved Field
  ServiceId                Service ID
  AddressStorageIdx        the index of the 0:1 relation pointing to Sd_AddressStorage
  ClientIdx                the index of the 0:1 relation pointing to Sd_Client
  ClientListIdx            the index of the 0:1 relation pointing to Sd_ClientList
  ConsumedEventgroupIdx    the index of the 0:1 relation pointing to Sd_ConsumedEventgroup
  EventHandlerIdx          the index of the 0:1 relation pointing to Sd_EventHandler
  InstanceIdx              the index of the 0:1 relation pointing to Sd_Instance
  MajorVersion             Major Version
  SendEntryNextIdx         the index of the 0:1 relation pointing to Sd_SendEntry
  ServerIdx                the index of the 0:1 relation pointing to Sd_Server
  Valid                    Flag indicating if the entry is valid
  EntryType                Type of entry
  TimeToSend               Time when message shall be sent
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_SendEntryUType, SD_VAR_NOINIT) Sd_SendEntry;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*   ... */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */
  /*    31 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ServerDyn
**********************************************************************************************************************/
/** 
  \var    Sd_ServerDyn
  \brief  Dynamic configuration data of SdServerService
  \details
  Element                           Description
  InitialOfferRepetitionRun         Counting the number of repetition runs
  ServiceGroupReqCounter            Server availability counter for ServiceGroup service API
  StateMachineExecutionRequested    Flag if State machine shall be executed for this server
  StateMachine                      State machine
  StateSwc                          Requested state
  TimeToTriggerSend                 Point in time the next message will be transmitted
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_ServerDynType, SD_VAR_NOINIT) Sd_ServerDyn[3];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_33_47843] */
  /*     2 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_UDP_fixed_10_23_0_33_40000] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_SoConActivationMap
**********************************************************************************************************************/
/** 
  \var    Sd_SoConActivationMap
  \brief  Configuration data of SocketConnections
  \details
  Element            Description
  NrOfActivations    Nr of activations
  SoConId            SocketConnection ID
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_SoConActivationMapUType, SD_VAR_NOINIT) Sd_SoConActivationMap;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C0_FaultInfo/SdEventHandler_0xC3C0_FaultInfo] */
  /*     2 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState] */
  /*     3 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_SenState/SdEventHandler_0xC3C1_SenState] */
  /*     4 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23/SdServerService_0xC3C1_EcuState/SdEventHandler_0xC3C1_EcuState] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TcpSoConModeMap
**********************************************************************************************************************/
/** 
  \var    Sd_TcpSoConModeMap
  \brief  Map to save the actual SocketConnection mode
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_SoConModeType, SD_VAR_NOINIT) Sd_TcpSoConModeMap[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_TX_fixed_10_23_0_33_47843] */
  /*     1 */  /* [/ActiveEcuC/Sd/SdConfig/SdInstance_Vlan23, /ActiveEcuC/SoAd/SoAdConfig/SCG_SD_TCP_RX_fixed_10_23_0_33_47842] */

#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TriggerTransmitEndIdx
**********************************************************************************************************************/
/** 
  \var    Sd_TriggerTransmitEndIdx
  \brief  the index of the 1:1 relation pointing to Sd_TriggerTransmit
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_TriggerTransmitEndIdxType, SD_VAR_NOINIT) Sd_TriggerTransmitEndIdx;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TriggerTransmitFull
**********************************************************************************************************************/
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_TriggerTransmitFullType, SD_VAR_NOINIT) Sd_TriggerTransmitFull;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TriggerTransmitStartIdx
**********************************************************************************************************************/
/** 
  \var    Sd_TriggerTransmitStartIdx
  \brief  the index of the 1:1 relation pointing to Sd_TriggerTransmit
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Sd_TriggerTransmitStartIdxType, SD_VAR_NOINIT) Sd_TriggerTransmitStartIdx;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_PCConfig
**********************************************************************************************************************/
/** 
  \var    Sd_PCConfig
  \details
  Element                                     Description
  AddressStorage                              the pointer to Sd_AddressStorage
  CapabilityRecord                            the pointer to Sd_CapabilityRecord
  CapabilityRecordFunctionCalloutPtr          the pointer to Sd_CapabilityRecordFunctionCalloutPtr
  Client                                      the pointer to Sd_Client
  ClientDyn                                   the pointer to Sd_ClientDyn
  ClientList                                  the pointer to Sd_ClientList
  ClientMap                                   the pointer to Sd_ClientMap
  ClientTimer                                 the pointer to Sd_ClientTimer
  CommonInitialDelay                          the pointer to Sd_CommonInitialDelay
  ConsumedEventgroup                          the pointer to Sd_ConsumedEventgroup
  ConsumedEventgroupDyn                       the pointer to Sd_ConsumedEventgroupDyn
  ConsumedEventgroupMap                       the pointer to Sd_ConsumedEventgroupMap
  EndpointStorage                             the pointer to Sd_EndpointStorage
  EventHandler                                the pointer to Sd_EventHandler
  EventHandlerDyn                             the pointer to Sd_EventHandlerDyn
  EventHandlerMulticast                       the pointer to Sd_EventHandlerMulticast
  EventHandlerTcp                             the pointer to Sd_EventHandlerTcp
  EventHandlerUdp                             the pointer to Sd_EventHandlerUdp
  Instance                                    the pointer to Sd_Instance
  InstanceDyn                                 the pointer to Sd_InstanceDyn
  IpAddrRequest                               the pointer to Sd_IpAddrRequest
  Method                                      the pointer to Sd_Method
  MulticastEndpointAddr                       the pointer to Sd_MulticastEndpointAddr
  MulticastSoConId                            the pointer to Sd_MulticastSoConId
  NrOfOptions                                 the pointer to Sd_NrOfOptions
  OptionIndex                                 the pointer to Sd_OptionIndex
  Payload                                     the pointer to Sd_Payload
  PortSet                                     the pointer to Sd_PortSet
  RequestCnt                                  the pointer to Sd_RequestCnt
  RoutingGroup                                the pointer to Sd_RoutingGroup
  RoutingGroupDyn                             the pointer to Sd_RoutingGroupDyn
  RxEvent                                     the pointer to Sd_RxEvent
  SendEntry                                   the pointer to Sd_SendEntry
  Server                                      the pointer to Sd_Server
  ServerDyn                                   the pointer to Sd_ServerDyn
  ServerMap                                   the pointer to Sd_ServerMap
  ServerTimer                                 the pointer to Sd_ServerTimer
  ServiceGroup                                the pointer to Sd_ServiceGroup
  ServiceGroupMap                             the pointer to Sd_ServiceGroupMap
  ServiceGroupMember                          the pointer to Sd_ServiceGroupMember
  SoConActivationMap                          the pointer to Sd_SoConActivationMap
  TcpSoConId                                  the pointer to Sd_TcpSoConId
  TcpSoConModeMap                             the pointer to Sd_TcpSoConModeMap
  TriggerTransmit                             the pointer to Sd_TriggerTransmit
  TriggerTransmitEndIdx                       the pointer to Sd_TriggerTransmitEndIdx
  TriggerTransmitFull                         the pointer to Sd_TriggerTransmitFull
  TriggerTransmitStartIdx                     the pointer to Sd_TriggerTransmitStartIdx
  UdpSoCon                                    the pointer to Sd_UdpSoCon
  SizeOfPayload                               the number of accomplishable value elements in Sd_Payload
  SizeOfAddressStorage                        the number of accomplishable value elements in Sd_AddressStorage
  SizeOfCapabilityRecord                      the number of accomplishable value elements in Sd_CapabilityRecord
  SizeOfCapabilityRecordFunctionCalloutPtr    the number of accomplishable value elements in Sd_CapabilityRecordFunctionCalloutPtr
  SizeOfClient                                the number of accomplishable value elements in Sd_Client
  SizeOfClientList                            the number of accomplishable value elements in Sd_ClientList
  SizeOfClientMap                             the number of accomplishable value elements in Sd_ClientMap
  SizeOfClientTimer                           the number of accomplishable value elements in Sd_ClientTimer
  SizeOfCommonInitialDelay                    the number of accomplishable value elements in Sd_CommonInitialDelay
  SizeOfConsumedEventgroup                    the number of accomplishable value elements in Sd_ConsumedEventgroup
  SizeOfConsumedEventgroupMap                 the number of accomplishable value elements in Sd_ConsumedEventgroupMap
  SizeOfEndpointStorage                       the number of accomplishable value elements in Sd_EndpointStorage
  SizeOfEventHandler                          the number of accomplishable value elements in Sd_EventHandler
  SizeOfEventHandlerMulticast                 the number of accomplishable value elements in Sd_EventHandlerMulticast
  SizeOfEventHandlerTcp                       the number of accomplishable value elements in Sd_EventHandlerTcp
  SizeOfEventHandlerUdp                       the number of accomplishable value elements in Sd_EventHandlerUdp
  SizeOfInstance                              the number of accomplishable value elements in Sd_Instance
  SizeOfIpAddrRequest                         the number of accomplishable value elements in Sd_IpAddrRequest
  SizeOfMethod                                the number of accomplishable value elements in Sd_Method
  SizeOfMulticastEndpointAddr                 the number of accomplishable value elements in Sd_MulticastEndpointAddr
  SizeOfMulticastSoConId                      the number of accomplishable value elements in Sd_MulticastSoConId
  SizeOfOptionIndex                           the number of accomplishable value elements in Sd_OptionIndex
  SizeOfPortSet                               the number of accomplishable value elements in Sd_PortSet
  SizeOfRequestCnt                            the number of accomplishable value elements in Sd_RequestCnt
  SizeOfRoutingGroup                          the number of accomplishable value elements in Sd_RoutingGroup
  SizeOfRxEvent                               the number of accomplishable value elements in Sd_RxEvent
  SizeOfSendEntry                             the number of accomplishable value elements in Sd_SendEntry
  SizeOfServer                                the number of accomplishable value elements in Sd_Server
  SizeOfServerMap                             the number of accomplishable value elements in Sd_ServerMap
  SizeOfServerTimer                           the number of accomplishable value elements in Sd_ServerTimer
  SizeOfServiceGroup                          the number of accomplishable value elements in Sd_ServiceGroup
  SizeOfServiceGroupMap                       the number of accomplishable value elements in Sd_ServiceGroupMap
  SizeOfServiceGroupMember                    the number of accomplishable value elements in Sd_ServiceGroupMember
  SizeOfSoConActivationMap                    the number of accomplishable value elements in Sd_SoConActivationMap
  SizeOfTcpSoConId                            the number of accomplishable value elements in Sd_TcpSoConId
  SizeOfTriggerTransmit                       the number of accomplishable value elements in Sd_TriggerTransmit
  SizeOfUdpSoCon                              the number of accomplishable value elements in Sd_UdpSoCon
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Sd_PCConfigsType, SD_CONST) Sd_PCConfig = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  { /* Index: 0 Keys: [Config] */
      Sd_AddressStorage.raw                     /**< the pointer to Sd_AddressStorage */
    , NULL_PTR                                  /**< the pointer to Sd_CapabilityRecord */
    , NULL_PTR                                  /**< the pointer to Sd_CapabilityRecordFunctionCalloutPtr */
    , Sd_Client                                 /**< the pointer to Sd_Client */
    , Sd_ClientDyn                              /**< the pointer to Sd_ClientDyn */
    , Sd_ClientList.raw                         /**< the pointer to Sd_ClientList */
    , Sd_ClientMap                              /**< the pointer to Sd_ClientMap */
    , Sd_ClientTimer                            /**< the pointer to Sd_ClientTimer */
    , NULL_PTR                                  /**< the pointer to Sd_CommonInitialDelay */
    , Sd_ConsumedEventgroup                     /**< the pointer to Sd_ConsumedEventgroup */
    , Sd_ConsumedEventgroupDyn                  /**< the pointer to Sd_ConsumedEventgroupDyn */
    , Sd_ConsumedEventgroupMap                  /**< the pointer to Sd_ConsumedEventgroupMap */
    , Sd_EndpointStorage.raw                    /**< the pointer to Sd_EndpointStorage */
    , Sd_EventHandler                           /**< the pointer to Sd_EventHandler */
    , Sd_EventHandlerDyn                        /**< the pointer to Sd_EventHandlerDyn */
    , Sd_EventHandlerMulticast                  /**< the pointer to Sd_EventHandlerMulticast */
    , Sd_EventHandlerTcp                        /**< the pointer to Sd_EventHandlerTcp */
    , Sd_EventHandlerUdp                        /**< the pointer to Sd_EventHandlerUdp */
    , Sd_Instance                               /**< the pointer to Sd_Instance */
    , Sd_InstanceDyn                            /**< the pointer to Sd_InstanceDyn */
    , Sd_IpAddrRequest                          /**< the pointer to Sd_IpAddrRequest */
    , NULL_PTR                                  /**< the pointer to Sd_Method */
    , Sd_MulticastEndpointAddr.raw              /**< the pointer to Sd_MulticastEndpointAddr */
    , Sd_MulticastSoConId                       /**< the pointer to Sd_MulticastSoConId */
    , (&(Sd_NrOfOptions))                       /**< the pointer to Sd_NrOfOptions */
    , Sd_OptionIndex                            /**< the pointer to Sd_OptionIndex */
    , Sd_Payload                                /**< the pointer to Sd_Payload */
    , Sd_PortSet.raw                            /**< the pointer to Sd_PortSet */
    , Sd_RequestCnt.raw                         /**< the pointer to Sd_RequestCnt */
    , Sd_RoutingGroup                           /**< the pointer to Sd_RoutingGroup */
    , Sd_RoutingGroupDyn.raw                    /**< the pointer to Sd_RoutingGroupDyn */
    , Sd_RxEvent.raw                            /**< the pointer to Sd_RxEvent */
    , Sd_SendEntry.raw                          /**< the pointer to Sd_SendEntry */
    , Sd_Server                                 /**< the pointer to Sd_Server */
    , Sd_ServerDyn                              /**< the pointer to Sd_ServerDyn */
    , Sd_ServerMap                              /**< the pointer to Sd_ServerMap */
    , Sd_ServerTimer                            /**< the pointer to Sd_ServerTimer */
    , NULL_PTR                                  /**< the pointer to Sd_ServiceGroup */
    , NULL_PTR                                  /**< the pointer to Sd_ServiceGroupMap */
    , NULL_PTR                                  /**< the pointer to Sd_ServiceGroupMember */
    , Sd_SoConActivationMap.raw                 /**< the pointer to Sd_SoConActivationMap */
    , Sd_TcpSoConId                             /**< the pointer to Sd_TcpSoConId */
    , Sd_TcpSoConModeMap                        /**< the pointer to Sd_TcpSoConModeMap */
    , NULL_PTR                                  /**< the pointer to Sd_TriggerTransmit */
    , (&(Sd_TriggerTransmitEndIdx))             /**< the pointer to Sd_TriggerTransmitEndIdx */
    , (&(Sd_TriggerTransmitFull))               /**< the pointer to Sd_TriggerTransmitFull */
    , (&(Sd_TriggerTransmitStartIdx))           /**< the pointer to Sd_TriggerTransmitStartIdx */
    , Sd_UdpSoCon                               /**< the pointer to Sd_UdpSoCon */
    , 1464u                                     /**< the number of elements in Sd_Payload */
    , 10u                                       /**< the number of elements in Sd_AddressStorage */
    , 0u                                        /**< the number of elements in Sd_CapabilityRecord */
    , 0u                                        /**< the number of elements in Sd_CapabilityRecordFunctionCalloutPtr */
    , 3u                                        /**< the number of elements in Sd_Client */
    , 5u                                        /**< the number of elements in Sd_ClientList */
    , 3u                                        /**< the number of elements in Sd_ClientMap */
    , 2u                                        /**< the number of elements in Sd_ClientTimer */
    , 0u                                        /**< the number of elements in Sd_CommonInitialDelay */
    , 3u                                        /**< the number of elements in Sd_ConsumedEventgroup */
    , 3u                                        /**< the number of elements in Sd_ConsumedEventgroupMap */
    , 20u                                       /**< the number of elements in Sd_EndpointStorage */
    , 3u                                        /**< the number of elements in Sd_EventHandler */
    , 2u                                        /**< the number of elements in Sd_EventHandlerMulticast */
    , 1u                                        /**< the number of elements in Sd_EventHandlerTcp */
    , 2u                                        /**< the number of elements in Sd_EventHandlerUdp */
    , 1u                                        /**< the number of elements in Sd_Instance */
    , 1u                                        /**< the number of elements in Sd_IpAddrRequest */
    , 0u                                        /**< the number of elements in Sd_Method */
    , 2u                                        /**< the number of elements in Sd_MulticastEndpointAddr */
    , 2u                                        /**< the number of elements in Sd_MulticastSoConId */
    , 10u                                       /**< the number of elements in Sd_OptionIndex */
    , 1u                                        /**< the number of elements in Sd_PortSet */
    , 1u                                        /**< the number of elements in Sd_RequestCnt */
    , 10u                                       /**< the number of elements in Sd_RoutingGroup */
    , 32u                                       /**< the number of elements in Sd_RxEvent */
    , 32u                                       /**< the number of elements in Sd_SendEntry */
    , 3u                                        /**< the number of elements in Sd_Server */
    , 3u                                        /**< the number of elements in Sd_ServerMap */
    , 2u                                        /**< the number of elements in Sd_ServerTimer */
    , 0u                                        /**< the number of elements in Sd_ServiceGroup */
    , 0u                                        /**< the number of elements in Sd_ServiceGroupMap */
    , 0u                                        /**< the number of elements in Sd_ServiceGroupMember */
    , 5u                                        /**< the number of elements in Sd_SoConActivationMap */
    , 2u                                        /**< the number of elements in Sd_TcpSoConId */
    , 0u                                        /**< the number of elements in Sd_TriggerTransmit */
    , 3u                                        /**< the number of elements in Sd_UdpSoCon */
  }
};
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/* PRQA L:MACRO_LIMIT */

/**********************************************************************************************************************
 *  END OF FILE: Sd_Lcfg.c
 *********************************************************************************************************************/
