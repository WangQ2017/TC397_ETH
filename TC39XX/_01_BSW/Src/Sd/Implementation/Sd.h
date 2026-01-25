/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Sd.h
 *        \brief  Service Discovery header file
 *
 *      \details  Vector static code implementation for AUTOSAR Service Discovery (SD) module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2013-08-16  vispcn                Created.
 *            2014-02-04  vispcn  ESCAN00071631 AR4-509: New module: Service Discovery according to ASR 4.1.1
 *  01.00.01  2014-02-17  vispcn  ESCAN00073762 SocketConnection Handling for provided Methods
 *                                ESCAN00074160 Missing response for malformed messages
 *                                ESCAN00074257 Tcp Handling of multiple/shared Connections
 *  01.00.02  2014-03-26  vispcn  ESCAN00074567 Tcp Handling of provided Methods and EventGroups in parallel
 *  01.00.03  2014-04-08  vispcn  ESCAN00075044 Wrong number of referenced options
 *                                ESCAN00075045 Check if requested IP Address is within the Subnet
 *                                ESCAN00075046 Shared SocketConnections
 *                                ESCAN00075057 Serialization of Sd messages can lead to buffer overflow
 *                                ESCAN00075492 Implementation of TriggerTransmit functionality
 *  01.00.04  2014-05-12  vispcn  ESCAN00075528 Compiler error: Sd_Lcfg.h: cannot allocate an array of constant size 0
 *  01.00.05  2014-05-13  vispcn  ESCAN00075584 Wrong initialization of provided methods
 *  01.00.06  2014-05-20  vispcn  ESCAN00075654 Missing SubscribeAcknowledge after startup without transceiver link
 *                                ESCAN00075767 Differentiation of received messages between unicast and multicast
 *                                ESCAN00075877 Support of dynamically assigned multicast addresses
 *                                ESCAN00075898 Illegal memory access in Sd_ClientServiceSetState
 *                                ESCAN00075971 Ignore redundant or conflicting options
 *                                ESCAN00076210 Missing response for Sd messages containing multiple entries
 *  01.01.00  2014-07-10  vispcn  ESCAN00076392 Messages can be overwritten in the Sd_SendEntriesList
 *                                ESCAN00076409 Set the ReservedField of subscribe(N)Ack messages as defined in the
 *                                              subscribe message
 *                                ESCAN00076561 Process received messages within the Sd_MainFunction() and not the
 *                                              Sd_RxIndication()
 *                                ESCAN00076785 Add DET error code SD_E_INV_ID
 *                                ESCAN00076790 Remove DEM error for SoAd_IfTransmit()
 *                                ESCAN00076906 Implementation of Sd_SoConModeChg() callback
 *                                ESCAN00076907 Support of predefined SoAdSocketRemoteAddress parameters
 *  01.01.01  2014-08-04  vispcn  ESCAN00077574 Pending TCP connection delays messages which are not involved
 *                                ESCAN00077659 Lost TCP connection is not noticed by a Client
 *  01.01.02  2014-08-11  vispcn  ESCAN00077703 Compiler warning: Several warnings when the component is compiled with
 *                                              Visual Studio
 *                                ESCAN00077913 Added DET checks for Sd_RxIndication and Sd_LocalIpAddrAssignmentChg
 *                                ESCAN00078153 Initialization of global values
 *                                ESCAN00078247 Dynamic assignment of multicast addresses
 *                                ESCAN00078338 Sd_Init() deletes IP address information if directly called after
 *                                              Sd_LocalIpAddrAssignmentChg()
 *                                ESCAN00078342 Illegal memory access in Sd_UpdateClientServiceServiceSoCons
 *                                ESCAN00078843 Delayed message transmission because of a pending TCP connection
 *                                              establishment
 *                                ESCAN00079254 Wrong TTL in Subscribe Messages
 *                                ESCAN00080129 Fehlendes SD_START_SEC_CODE in Sd.h
 *  01.02.00  2014-11-24  vispcn  ESCAN00079865 FEAT-24: Support new EventGroup Entries format,
 *                                              new IPv4/IPv6 SD Endpoint Option and new DETs. [AR4-1028]
 *                                ESCAN00080374 Transmission of SomeIp messages by unicast and multicast in parallel
 *  02.00.00  2015-01-28  vispcn  ESCAN00080068 FEAT-1001: Sd Enhanced Config for Asr4.2.1
 *                                ESCAN00080965 Client should accept SubscribeACK message, if the multicast endpoint
 *                                              is missing and unicast is configured
 *                                ESCAN00080975 Missing UDP endpoint option for multicast-only server services
 *                                ESCAN00081011 Client handling does not detect identical clients
 *                                ESCAN00081539 Sd_SockAddrIsEqual() causes null pointer exception
 *                                ESCAN00081554 Wrong subscription triggers duplicated SubscribeEventgroupNack message
 *                                ESCAN00081565 Ignore topologically incorrect SD Endpoint Options
 *                                ESCAN00081816 Link state change of single SdInstance leads to global
 *                                              re-initialization
 *  02.01.00  2015-03-30  vispcn  ESCAN00082152 Execute State Machines based on an Event Driven approach
 *  03.00.00  2015-08-26  vispcn  ESCAN00084466 FindService messages containing wildcards may be answered incompletely
 *                                ESCAN00084789 Remove race condition according to RFC 68309
 *                                ESCAN00085492 FEAT-1505: Postbuild Loadable for Socket Adaptor and Service Discovery
 *                                ESCAN00085589 Resolve review findings in Implementation and TechRef. (No Defects)
 *                                ESCAN00085641 Inconsistent timing for client or server services.
 *                                ESCAN00086182 Ignored request-response delay for subscriptions received via multicast
 *                                ESCAN00087312 IPv6 TCP endpoint options are labeled as UDP
 *  03.00.01  2016-02-22  vispcn  ESCAN00088302 SdClientServiceMinorVersion wildcards are not supported
 *                                ESCAN00087685 FEAT-1449: Release of FEAT-1253 (ETH Stack)
 *  03.00.02  2016-05-04  vispcn  ESCAN00089620 last line of file ends without a newline
 *                                ESCAN00089765 Ignore OfferService messages with MajorVersion set to Wildcard
 *                                ESCAN00089124 EventHandler should use received TTL, even if bigger than configured TTL
 *  04.00.00  2016-05-12  vispcn  ESCAN00089350 FEAT-1641: Service Discovery enhancements and bugfixing according to
 *                                              AR 4.3
 *                                ESCAN00090516 Sd_State is not correct if Sd_Init() is called with invalid ConfigPtr
 *                                              after correct initialization
 *            2016-06-30  vismda  ESCAN00090759 FEAT-1413: Extension of BSD Socket API to support SOME/IP-SD under
 *                                              Linux
 *            2016-07-11  vispcn  ESCAN00090929 Repetition phase starts with delay of one MainFunction cycle
 *  04.01.00  2016-07-19  vispcn  ESCAN00091013 Add deduplication of endpoint options
 *                                ESCAN00091057 Add transmission retry mechanism in case of insufficient Tx buffer
 *                                ESCAN00092255 Wrong StopSubscribeEventgroup - SubscribeEventgroup entries order
 *                                              within single message
 *                                ESCAN00092615 Messages with unicast flag set to 0 are not ignored
 *                                ESCAN00092717 Reboot detection does not renew connections
 *                                ESCAN00093386 Missing StopSubscribeEventgroup messages
 *  04.01.01  2017-01-11  vispcn  ESCAN00093506 OTHERSERV server does not attach Configuration Option at
 *                                              SubscribeEventgroupNack messages.
 *                                ESCAN00092847 Request-response delay exceeds maximum value
 *  04.02.00  2017-01-13  vispcn  FEATC-938     FEAT-1824: Support a component-specific SafeBSW configuration switch
 *  05.00.00  2017-02-16  vispcn  ESCAN00094039 Serialize hostname to a separated configuration option
 *                                STORYC-326    SAFE Code Refactoring and CDD
 *  05.01.00  2017-05-22  vispcn  STORYC-327    SAFE Silent Analysis
 *  05.02.00  2017-06-23  vispcn  STORYC-1206   SAFE Deactivate unused code by preprocessor
 *  05.03.00  2017-07-10  vispcn  ESCAN00095806 Compiler warning: C4310: cast truncates constant value
 *                                ESCAN00096142 Access violation in Sd_TriggerTransmit_Process()
 *  05.04.00  2017-08-23  vispcn                Use new ComStackLib features. (STORY-876, STORY-982, STORY-983)
 *  06.00.00  2017-10-26  vispcn  ESCAN00096821 SD ignores endpoint options of the wrong subnet, but does not ignore
 *                                              the referencing entry.
 *                                ESCAN00097055 Multiple Sd_ServerServiceSetState() calls to disable server may close
 *                                              connection of independent service
 *                                ESCAN00096814 TTL value of 0xFFFFFF is not considered valid until the next reboot.
 *                                ESCAN00097046 Reboot of remote client causes DET error
 *                                ESCAN00097325 Transmission of unexpected configuration options and/or insufficient
 *                                              TX buffer.
 *                                STORYC-3330   Implementation of binary search algorithm
 *                                ESCAN00097723 Sd_ServerServiceSetState() calls to disable server may close connection
 *                                              of independent services.
 *  06.01.00  2017-12-01  vispcn  ESCAN00097622 SD_BEGIN_CRITICAL_SECTION called in Sd_InitMemory
 *                                ESCAN00097505 Client replies SubscribeEventgroup(N)Ack message by repeated
 *                                              SubscribeEventgroup message.
 *                                STORYC-3535   Provide configuration option to not set Unicast remote address when
 *                                              receiving SD SubAck with Multicast Endpoint option
 *                                ESCAN00097937 State of client is reported as available while TCP connection is not
 *                                              established.
 *                                ESCAN00098039 Consumed eventgroup overwrites multicast endpoint information.
 *  06.02.00  2018-01-17  vispcn  STORYC-4346   Remove redundant checks and unreachable code parts.
 *                                ESCAN00098177 Client uses SdClientTimerTTL instead of offered TTL if client is in
 *                                              initial wait or repetition phase.
 *                                ESCAN00098692 Sd causes DET error in SoAd module.
 *  06.03.00  2018-02-20  vispcn  STORYC-4577   Create static Sd_Cbk header file.
 *  07.00.00  2018-03-20  vispcn  ESCAN00098831 Client does not retry failed SoAd configuration of consumed methods.
 *                                STORYC-4743   Remove redundant checks and unreachable code parts. (R21S1)
 *                                ESCAN00098906 SessionIDs used for unicast communication are not reset in case of
 *                                              local IP address assignment change.
 *                                ESCAN00098914 Client ignores first OfferService message after local IP address
 *                                              assignment state has changed.
 *                                ESCAN00099073 Client does not detect changed server endpoint address.
 *                                ESCAN00099456 Event handler does not transmit messages via multicast.
 *                                ESCAN00099578 Consumed eventgroup does not ignore redundant SubscribeEventgroupAck
 *                                              entries.
 *                                ESCAN00097297 Reboot of remote client leads to rejection of its next subscription.
 *  07.00.01  2018-10-31  vispcn  ESCAN00101207 Client does not receive multicast events if IP address assignment of
 *                                              dynamic multicast address has changed.
 *  07.00.02  2019-04-15  vispcn  ESCAN00102819 SdServer does not answer FindService and SubscribeEventgroup entries
 *                                              under high load.
 *  07.00.03  2019-04-26  vispcn  STORYC-7612   Integration of SafetyCheck findings
 *                                STORYC-4510   MISRA-C:2012 Compliance
 *                                ESCAN00102448 Sd transmits invalid packets which are truncated.
 *  07.00.04  2019-06-11  vispcn  ESCAN00102191 Received SubscribeEventgroupNAck-Ack sequence disables routing of
 *                                              received notification events.
 *            2019-06-12  vispcn  ESCAN00103168 SendEntry list is not cleared if IP address assignment state is lost.
 *  08.00.00  2019-06-21  vispcn  STORYC-7036   Introduce retry subscription mechanism for requested eventgroups.
 *  08.00.01  2019-07-16  vispcn  ESCAN00103384 BswM_Sd_EventHandlerCurrentState() is called twice if server is set
 *                                              to DOWN.
 *  08.00.02  2019-09-30  vispcn  SAA-282       Analyze and Fix R23 MISRA deviations
 *  08.00.03  2019-10-29  vispcn  ESCAN00104521 Configure SdEventTriggeringRef in combination with
 *                                              SdEventHandlerMulticastThreshold == 1
 *  08.00.04  2019-11-15  vispcn  ESCAN00104917 Received (Stop)OfferService message may get ignored by ClientService
 *            2019-12-18  vispcn  ESCAN00105227 SdEventHandler does not enable routing for subscribed remote client
 *  08.00.05  2020-01-17  vispcn  ESCAN00105388 Detected remote reboot closes RX multicast SocketConnection of
 *                                              uninvolved ConsumedEventgroup
 *  08.00.06  2020-01-30  vispcn  ESCAN00105124 Transmission of StopSubscribe-Subscribe sequence is not triggered if
 *                                              server rejected the previous subscription.
 *  08.00.07  2020-03-20  viskjs  ESCAN00105882 StopSubscribeEventgroup Entries do not contain any Endpoint Options
 *  09.00.00  2020-04-14  viskjs  SAA-586       Improve initialization procedure
 *                                SAA-425       Speed up handling of StopSubscribe-SubscribeEventgroup sequence
 *  09.01.00  2020-06-16  viskjs  SAA-413       Process a limited amount of entries per MainFunction
 *                                ESCAN00105971 StopSubscribeEventgroup entry is sent twice when releasing client service
 *                                ESCAN00106286 Runtime error reporting shall not be deactivatable
 *                                ESCAN00106272 Subscription retry mechanism stops after first Acknowledge
 *                                ESCAN00103469 Provided method calls over UDP do not work if remote address is preconfigured
 *                                SAA-417       Improve serialization of oversized messages
 *  09.02.00  2020-06-22  viskjs  SAA-423       Improve handling of RoutingGroups
 *                                SAA-415       Trigger state machine execution only for services which have to be processed.
 *                                ESCAN00106582 Compiler warning: Enumerated type mixed with another type.
 *                                ESCAN00106778 SdServerService rejects valid subscription of remote client.
 *  09.02.01  2020-10-06  viskjs  ESCAN00107106 Timer values might get changed to unexpected values by a context switch.
 *                                ESCAN00107107 Processing an event might get delayed until the next state machine execution.
 *                                ESCAN00107105 Tx-Queue might become inconsistent, leading to sending of duplicated or wrong Sd Entries.
 *                                ESCAN00107544 StopSubscribe entries are not sent in as few SdMessages as possible when ClientServices are released.
 *  09.02.02  2020-11-03  viskjs  ESCAN00107513 Sending initial events is not triggered by a StopSubscribe-Subscribe sequence.
 *                                SAA-866       Update to QAC Helix
 *  09.03.00  2020-11-25  viskjs  SAA-519       Support SdServiceGroupS as defined in AUTOSAR R19-11
 *  09.03.01  2020-12-21  viskjs  ESCAN00108192 SdMessages with corrupt OptionArray are being sent
 *********************************************************************************************************************/

#if !defined(SD_H)
# define SD_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Sd_Cbk.h"
# include "Sd_Cfg.h"
# include "Sd_Lcfg.h"
# include "Sd_PBcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define SYSSERVICE_SD_VERSION                        (0x0903u) /*!< BCD coded version number */
# define SYSSERVICE_SD_RELEASE_VERSION                (0x01u)   /*!< BCD coded release version number */

/* ----- Vendor and module identification ----- */
# define SD_VENDOR_ID                                 (30u)  /* Vector ID */
# define SD_MODULE_ID                                 (171u) /* Service Discovery */
# define SD_INSTANCE_ID                               (0u)   /* Vector Instance ID for Sd */

/* AUTOSAR Software specification version information */
# define SD_AR_RELEASE_MAJOR_VERSION                  (4u)
# define SD_AR_RELEASE_MINOR_VERSION                  (2u)
# define SD_AR_RELEASE_REVISION_VERSION               (2u)

/* ----- Component Version Information ----- */
# define SD_SW_MAJOR_VERSION                          (SYSSERVICE_SD_VERSION >> 8u)
# define SD_SW_MINOR_VERSION                          (SYSSERVICE_SD_VERSION & 0x00FFu)
# define SD_SW_PATCH_VERSION                          (SYSSERVICE_SD_RELEASE_VERSION)

/* ----- API service IDs ----- */
# define SD_SID_INIT                                  (0x01u) /*!< Service ID: Sd_Init() */
# define SD_SID_GET_VERSION_INFO                      (0x02u) /*!< Service ID: Sd_GetVersionInfo() */
# define SD_SID_LOCAL_IP_ADDR_ASSIGNMENT_CHG          (0x05u) /*!< Service ID: Sd_LocalIpAddrAssignmentChg() */
# define SD_SID_MAIN_FUNCTION                         (0x06u) /*!< Service ID: Sd_MainFunction() */
# define SD_SID_SERVER_SERVICE_SET_STATE              (0x07u) /*!< Service ID: Sd_ServerServiceSetState() */
# define SD_SID_CLIENT_SERVICE_SET_STATE              (0x08u) /*!< Service ID: Sd_ClientServiceSetState() */
# define SD_SID_CONSUMED_EVENTGROUP_SET_STATE         (0x09u) /*!< Service ID: Sd_ConsumedEventGroupSetState() */
# define SD_SID_RX_INDICATION                         (0x42u) /*!< Service ID: Sd_RxIndication() */
# define SD_SID_SOCONMODE_CHG                         (0x43u) /*!< Service ID: Sd_SoConModeChg() */
# define SD_SID_SERVICE_GROUP_START                   (0x44u) /*!< Service ID: Sd_ServiceGroupStart() */
# define SD_SID_SERVICE_GROUP_STOP                    (0x45u) /*!< Service ID: Sd_ServiceGroupStop() */

# define SD_SID_ADD_CLIENT_TO_LIST                    (0xA2u) /*!< Service ID: Sd_AddClientToList() */
# define SD_SID_SERIALIZE_PENDING_MESSAGES            (0xA3u) /*!< Service ID: Sd_SerializePendingMessages() */
# define SD_SID_SAVE_SENDENTRY_IN_LIST                (0xA4u) /*!< Service ID: Sd_SaveSendEntryInList() */
# define SD_SID_HANDLERETRYSUBSCRIPTION               (0xA5u) /*!< Service ID: Sd_StateClient_HandleRetrySubscription() */

/* ----- Error codes ----- */
# define SD_E_NO_ERROR                                (0x00u) /*!< used to check if no error occurred - use a value unequal to any error code. */
# define SD_E_NOT_INITIALIZED                         (0x01u) /*!< Error code: Module has not been initialized. */
# define SD_E_PARAM_POINTER                           (0x02u) /*!< Error code: API service used with invalid pointer parameter (NULL). */
# define SD_E_INV_MODE                                (0x03u) /*!< Error code: Invalid mode request. */
# define SD_E_INV_ID                                  (0x04u) /*!< Error code: Invalid ID. */
# define SD_E_INIT_FAILED                             (0x05u) /*!< Unused error code. */
# define SD_E_COUNT_OF_RETRY_SUBSCRIPTION_EXCEEDED    (0x06u) /*!< Error code: Subscription retry was not successful. */

# define SD_E_PARAM_CONFIG                            (0xA1u) /*!< Error code: API service Sd_Init() called with wrong parameter. */
# define SD_E_ADDR_LIST_FULL                          (0xB1u) /*!< Error code: Internal address list/buffer is full. */
# define SD_E_CLIENT_LIST_FULL                        (0xB2u) /*!< Error code: Internal client list/buffer is full. */
# define SD_E_TX_BUFFER_FULL                          (0xB3u) /*!< Error code: Internal TX buffer is full. */
# define SD_E_SEND_ENTRY_LIST_FULL                    (0xB4u) /*!< Error code: Internal list of send entries is full. */

/* ----- Modes ----- */
# define SD_UNINIT                                    (0x00u)
# define SD_INIT                                      (0x01u)

# define SD_CONSUMEDEVENTGROUPMULTICAST               (SD_MULTICASTSOCONID)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define SD_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Sd_InitMemory()
 *********************************************************************************************************************/
/*! \brief          Power-up memory initialization.
 *  \details        Initializes component variables in *_INIT_* sections at power up.
 *  \pre            Module is uninitialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \note           This function shall be called before Sd_Init.
 *********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_InitMemory(void);

/**********************************************************************************************************************
 *  Sd_Init()
 *********************************************************************************************************************/
/*! \brief          Initializes component.
 *  \details        Initializes all component variables and sets the component state to initialized.
 *  \param[in]      ConfigPtr   Pointer to the post-build configuration data structure of the Sd. If the
 *                  configuration variant pre-compile is used, the pointer given is ignored.
 *  \pre            Sd_InitMemory has been called unless module is initialized by start-up code.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \note           This function has to be called before usage of the module.
 *********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_Init(
  P2CONST(Sd_ConfigType, AUTOMATIC, SD_INIT_DATA) ConfigPtr);

# if (SD_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Sd_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief          Returns the version information.
 *  \details        Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]     VersionInfoPtr   Pointer to a memory location where the Sd version information shall be stored.
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if SdVersionInfoApi is enabled.
 *********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SD_APPL_VAR) VersionInfoPtr);
# endif /* SD_VERSION_INFO_API */

/**********************************************************************************************************************
 *  Sd_ServerServiceSetState()
 *********************************************************************************************************************/
/*! \brief          Sets the state of a server service.
 *  \details        State defines if the server shall be available or not.
 *  \param[in]      SdServerServiceHandleId   ID to identify the Server Service Instance.
 *  \param[in]      ServerServiceState        The state the Server Service Instance shall be set to.
 *  \return         E_OK      State change accepted.
 *  \return         E_NOT_OK  State change was not accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different server.
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SD_CODE) Sd_ServerServiceSetState(
  uint16 SdServerServiceHandleId,
  Sd_ServerServiceSetStateType ServerServiceState);

/**********************************************************************************************************************
 *  Sd_ClientServiceSetState()
 *********************************************************************************************************************/
/*! \brief          Sets the state of a client service.
 *  \details        State defines if the client service is requested or not.
 *  \param[in]      ClientServiceHandleId     ID to identify the Client Service Instance.
 *  \param[in]      ClientServiceState        The state the Client Service Instance shall be set to.
 *  \return         E_OK      State change accepted.
 *  \return         E_NOT_OK  State change was not accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different clients.
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SD_CODE) Sd_ClientServiceSetState(
  uint16 ClientServiceHandleId,
  Sd_ClientServiceSetStateType ClientServiceState);

/**********************************************************************************************************************
 *  Sd_ServiceGroupStart()
 *********************************************************************************************************************/
/*! \brief          Starts a preconfigured SdServiceGroup.
 *  \details        Sets all members of the specified SdServiceGroup to REQUESTED / AVAILABLE.
 *  \param[in]      ServiceGroupHandleId      ID to identify the Service Group.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different ServiceGroups.
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_ServiceGroupStart(uint16 ServiceGroupHandleId);

/**********************************************************************************************************************
 *  Sd_ServiceGroupStop()
 *********************************************************************************************************************/
/*! \brief          Stops a preconfigured SdServiceGroup.
 *  \details        Sets all members of the specified SdServiceGroup to RELEASED / DOWN
 *                  if the respective service is not requested by another SdServiceGroup which has been started.
 *  \param[in]      ServiceGroupHandleId      ID to identify the Service Group.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different ServiceGroups.
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_ServiceGroupStop(uint16 ServiceGroupHandleId);

/**********************************************************************************************************************
 *  Sd_ConsumedEventGroupSetState()
 *********************************************************************************************************************/
/*! \brief          Sets the state of a consumed eventgroup.
 *  \details        State defines if the consumed eventgroup is requested or not.
 *  \param[in]      SdConsumedEventGroupHandleId  ID to identify the ConsumedEventGroupHandleId
 *  \param[in]      ConsumedEventGroupState       The state the EventGroup shall be set to.
 *  \return         E_OK      State change accepted.
 *  \return         E_NOT_OK  State change was not accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different consumed eventgroups.
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SD_CODE) Sd_ConsumedEventGroupSetState(
  uint16 SdConsumedEventGroupHandleId,
  Sd_ConsumedEventGroupSetStateType ConsumedEventGroupState);

# define SD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \exclusivearea SD_EXCLUSIVE_AREA_0
 * Ensures consistency while performing modifications of queues and timing parameters.
 * \protects Sd_RxEvent, Sd_SendEntry, Sd_EndpointStorage, management data in Sd_InstanceDyn and Sd_ClientDyn
 *           as well as timers of type Sd_ExtendedTimeType.
 * \usedin Sd_RxServer_AddEventToRingBuffer, Sd_EventServer_RemoveFirst, Sd_State_HandleRunMode,
 *         Sd_RxServer_ProcessEntrySubscribeSaveParameters, Sd_StateClient_HandleReboot,
 *         Sd_StateClient_Process, Sd_Util_GetEmptySendEntry,
 *         Sd_Util_RemoveSendEntryFromList, Sd_Util_CheckIfTimerExceeded, Sd_Util_SetTimerOffsetSecWithTrigger,
 *         Sd_Util_SetTimerOffset, Sd_Util_ResetTimerToZero.
 * \exclude All functions provided by Sd.
 * \length SHORT The exclusive area protects only a few statements with constant maximum runtime.
 * \endexclusivearea
 */

#endif /* SD_H */

/**********************************************************************************************************************
 *  END OF FILE: Sd.h
 *********************************************************************************************************************/
